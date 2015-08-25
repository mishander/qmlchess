#include "boardmodel.h"
#include "ChessPieces/chesspiece.h"
#include "utils.h"
#include <sstream>
#include <fstream>

#include <stdexcept>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QVariant>
#include <QDebug>


BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_currentPlayer(PieceColor::White)
    , m_isGameOn(false)
	, m_eatenChessPeices()
    , m_step(-1)
{
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
	if (!m_isGameOn)
		return false;
	if (m_data.empty())
		return false;

	const std::shared_ptr<ChessPiece> item = m_data.at(index.row());
	if(!item)
       return QVariant();
	QString s;
    switch(role) {
        case NameRole:
            return QString("Cell %1").arg(index.row());
        case ImageRole:
			s = QStringLiteral("qrc:/img/") + QString::fromStdWString(item->imageName()) + QStringLiteral(".png");
			return s;
    }

    return QVariant();
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ImageRole] = "image";
    return roles;
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 64;
}

bool BoardModel::isMovePossible(int oldCell, int newCell) 
{
    if(!m_isGameOn)
        return false;
	if (oldCell < 0)
	{
		qWarning("isMovePossible: index < 0");
		return false;
	}
	if (isCellEmpty(oldCell))
		return false;

	return m_possibleMoves.find(newCell) != m_possibleMoves.end();
}

bool BoardModel::isSelectionPosible(int cellIndex) const
{
    if(!m_isGameOn)
        return false;
	if (!m_data[cellIndex])
	{
		return false;
	}
	if (m_currentPlayer != m_data[cellIndex]->Color())
		return false;

     return true;
}

bool BoardModel::move(int oldCell, int newCell)
{
    if(isCellEmpty(oldCell))
        return false;
    moveChessPiece(oldCell, newCell);
    return true;
}
Q_INVOKABLE void BoardModel::select(int index)
{
	if (index >= 0 && index < 64)
	{
		m_selected = index;
		uint8_t x = index % 8;
		uint8_t y = index / 8;
		m_possibleMoves.clear();
		m_possibleMoves = m_data[index]->getPossibleMoves(x, y);
		refreshBoard();
	}
	else
	{
		qWarning() << QString("Select index is out of bounds: %1").arg(index);
	}
}
bool BoardModel::initializeBoard()
{
	m_selected = INT_MAX;
	
	try
    {
        auto cp3 = ChessPiece::CP;
        //FIXME: capture
        chcall isBlocked = [&](uint8_t _x, uint8_t _y){ return (bool)m_data[_y * 8 + _x]; };
        chcall sameColor = [&](uint8_t _x, uint8_t _y){ return (m_data[_y * 8 + _x]->Color() == m_data[m_selected]->Color()); };
        auto CP = [&](Piece cp){return cp3(cp, isBlocked, sameColor); };
		m_data =
		{
            CP(BROOK), CP(BKNIGHT), CP(BBISHOP), CP(BQUEEN), CP(BKING), CP(BBISHOP), CP(BKNIGHT), CP(BROOK),
			CP(BPAWN), CP(BPAWN), CP(BPAWN), CP(BPAWN), CP(BPAWN), CP(BPAWN), CP(BPAWN), CP(BPAWN),
			CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY),
			CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY),
			CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY),
			CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY), CP(EMPTY),
			CP(WPAWN), CP(WPAWN), CP(WPAWN), CP(WPAWN), CP(WPAWN), CP(WPAWN), CP(WPAWN), CP(WPAWN),
			CP(WROOK), CP(WKNIGHT), CP(WBISHOP), CP(WQUEEN), CP(WKING), CP(WBISHOP), CP(WKNIGHT), CP(WROOK)
		};
	}
	catch (std::logic_error & ex)
	{
		qDebug() << ex.what();
		Q_ASSERT_X(false, "BoardModel::initializeBoard", ex.what());
		return false;
	}
	return true;
}

void BoardModel::startGame()
{
    qDebug() << "startgame";
    if(initializeBoard())
	{
		m_isGameOn = true;
		m_currentPlayer = PieceColor::White;
		refreshBoard();
		clearHistory();
	}
}

void BoardModel::stopGame()
{
    m_data.clear();
    m_movesHistory.clear();
	m_possibleMoves.clear();
	refreshBoard();
    m_isGameOn = false;
}

void BoardModel::loadGame()
{
    m_movesHistory.clear();
	const std::wstring path = Utils::GetOpenFileNameFromDialog();
	std::wifstream inputFile(path);
	std::wstring line;
	std::wistringstream numStream;
	std::getline(inputFile, line);
	numStream.str(line);
	std::copy(std::istream_iterator<uint32_t, wchar_t>(numStream), std::istream_iterator<uint32_t, wchar_t>(), std::back_inserter(m_movesHistory));

	if (m_movesHistory.size() > 0) {
		m_step = 0;
        initializeBoard();
		m_isGameOn = true;
        emit gameLoaded();
        refreshBoard();
    }
}

void BoardModel::saveGame()
{
	const std::wstring file_path = Utils::GetSaveFileNameFromDialog();
	std::wofstream outFILE(file_path, std::ios::out | std::wofstream::binary);
	if (outFILE)
	{
		std::copy(m_movesHistory.begin(), m_movesHistory.end(), std::ostream_iterator<uint32_t,wchar_t>(outFILE, L" "));
		outFILE << '\n';
	}
	outFILE.close();
}

void BoardModel::nextStep()
{
    try {
        if(m_step < m_movesHistory.size()) {
			uint8_t from = m_movesHistory[m_step] >> 16;
			uint8_t to = m_movesHistory[m_step] & 0xffff;
			moveInternal(from, to);
            ++m_step;
        }
    } catch(std::exception &e) {
        Q_ASSERT_X(false, "nextSetp", e.what());
        qDebug() << e.what();
    }
}

void BoardModel::prevStep()
{
    try {
        if(m_step > 0) {
			--m_step;
			uint8_t from = m_movesHistory[m_step] >> 16;
			uint8_t to = m_movesHistory[m_step] & 0xffff;
			
			moveInternal(to, from,true);
        }
    } catch(std::exception &e) {
        Q_ASSERT_X(false, "prevSetp", e.what());
        qDebug() << e.what();
    }
}

bool BoardModel::isCellEmpty(int cellIndex) const
{
	if (cellIndex > 0)
		return !(bool)m_data[cellIndex];
	else
		return false;
}

void BoardModel::moveInternal(int from, int to,bool moveBackwards)
{
	if (m_data[to])
	{
		m_eatenChessPeices.insert(std::make_pair(m_step, m_data[to]));
		m_data[to] = m_data[from];
		m_data[from] = NULL;
	}
	else
	{
		std::swap(m_data[from], m_data[to]);
        if (!m_eatenChessPeices.empty() && moveBackwards)
		{
			if (m_eatenChessPeices.find(m_step) != m_eatenChessPeices.end())
			{
				m_data[from] = m_eatenChessPeices[m_step];
				m_eatenChessPeices.erase(m_step);
			}
		}
	}
	m_currentPlayer = (m_currentPlayer == PieceColor::White) ? (PieceColor::Black) : (PieceColor::White);
	emit dataChanged(index(from), index(from));
	emit dataChanged(index(to), index(to));
	refreshBoard();
}
void BoardModel::moveChessPiece(int from, int to)
{
	if (m_data[from])
	m_data[from]->clearPossibles();
	if (m_data[to]) 
	m_data[to]->clearPossibles();
	if (m_possibleMoves.find(to) != m_possibleMoves.end())
	{
		moveInternal(from, to);
	}
	m_movesHistory.push_back((from << 16) + to);

}

void BoardModel::refreshBoard()
{
    emit dataChanged(index(0), index(63));
}

void BoardModel::clearHistory()
{
    m_movesHistory.clear();
}

