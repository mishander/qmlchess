#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <memory>
#include "ChessPieces/chesspiece.h"

class BoardModel : public QAbstractListModel
{
	Q_OBJECT
public:
    explicit BoardModel(QObject *parent = nullptr);

    enum DataRoles {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        BackgroundRole
    };

     QVariant data(const QModelIndex & index, int role) const override;
     QHash<int,QByteArray> roleNames() const override;
     int rowCount(const QModelIndex & parent = QModelIndex()) const override;

     Q_INVOKABLE bool isMovePossible(int oldCell, int newCell);
	 Q_INVOKABLE bool isSelectionPosible(int index) const;
	 Q_INVOKABLE void select(int index);
     Q_INVOKABLE int  getRectMargin()
     {
         return 11; 
     }
     Q_INVOKABLE bool isFirstStep()
     {
         return (m_step == 0);
     }
     Q_INVOKABLE bool isLastStep()
     {
         return (m_step == m_movesHistory.size());
     }
     Q_INVOKABLE bool move(int oldCell, int newCell);

     Q_INVOKABLE void startGame();
     Q_INVOKABLE void stopGame();
     Q_INVOKABLE void loadGame();
     Q_INVOKABLE void saveGame();
     Q_INVOKABLE void nextStep();
     Q_INVOKABLE void prevStep();

signals:
     void gameFinished(QString player);
     void gameLoaded();

private:
     bool initializeBoard();
     bool isCellEmpty(int index) const;
     //bool hasObstaclesOnTheWay(int firstIndex, int secondIndex) const;
     //void loadBoardFromJSON(const QJsonArray &data);
     //QJsonArray saveBoardToJSON() const;
     //QJsonObject serializeCell(int cellIndex) const;
     //void deserializeCell(const QJsonObject &obj);
     void moveInternal(int oldCell, int newCell, bool movebackwards = false);
     void moveChessPiece(int oldCell, int newCell);
     void refreshBoard();
     void clearHistory();

private:
    PieceColor m_currentPlayer;
    bool m_isGameOn;
    //QJsonArray m_moveHistory;
	uint32_t m_selected;

	std::set<uint8_t> m_possibleMoves;
	std::set<uint8_t> m_possibleChecks;
	std::vector<std::shared_ptr<ChessPiece>> m_data;
	std::vector<uint32_t> m_movesHistory;
	std::map<uint32_t, std::shared_ptr<ChessPiece>> m_eatenChessPeices;
    uint32_t m_step;
};

#endif // BOARDMODEL_H
