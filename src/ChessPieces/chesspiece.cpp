#include "chesspiece.h"
#include "kingpiece.h"
#include "knightpiece.h"
#include "bishoppiece.h"
#include "queenpiece.h"
#include "rookpiece.h"
#include "pawnpiece.h"

ChessPiece::ChessPiece(Piece _type, uint8_t index) :m_type(_type), m_position(index)
{
    m_color = PieceColor(_type > 6);
};
ChessPiece::ChessPiece(Piece _type) :m_type(_type)
{
    m_color = PieceColor(_type > 6);
};
ChessPiece::ChessPiece(PieceColor _color, chcall isBlocked, chcall isSameColor) :m_color(_color), m_isBlocked(isBlocked), m_isSameColor(isSameColor)
{
}
std::wstring ChessPiece::colorName() const
{
    if (m_color == PieceColor::Black) return L"black"; else return L"white";
}

bool ChessPiece::isValid(const uint8_t positionX, const uint8_t positionY)  const
{
    return (((positionX >= 0 && positionX < 8) && (positionY >= 0 && positionY < 8)));
}
bool ChessPiece::addIfNotBlocked(const uint8_t x, const uint8_t y)
{
    bool result = false;
    if (isValid(x, y))
    {
        if (m_isBlocked(x, y))
        {
            if (!m_isSameColor(x, y))
            {
                m_possibleMoves.insert(y * 8 + x);
                result = false;
            }
        }
        else
        {
            m_possibleMoves.insert(y * 8 + x);
            result = true;
        }

    }
    return result;
}
void ChessPiece::addDXYRange(const uint8_t x, const uint8_t y)
{
    uint8_t tmpx = x;
    uint8_t tmpy = y;
    while (addIfNotBlocked((--tmpx), (--tmpy)));
    tmpx = x;
    tmpy = y;
    while (addIfNotBlocked((++tmpx), (++tmpy)));
    tmpx = x;
    tmpy = y;
    while (addIfNotBlocked((--tmpx), (++tmpy)));
    tmpx = x;
    tmpy = y;
    while (addIfNotBlocked((++tmpx), (--tmpy)));
}
void ChessPiece::addXYRange(const uint8_t x, const uint8_t y)
{
    uint8_t tmpx = x;
    while (addIfNotBlocked((--tmpx), y));
    tmpx = x;
    while (addIfNotBlocked((++tmpx), y));
    uint8_t tmpy = y;
    while (addIfNotBlocked(x, (--tmpy))) {};
    tmpy = y;
    while (addIfNotBlocked(x, (++tmpy))) {};
}
void ChessPiece::clearPossibles()
{
    m_possibleMoves.clear();
}
std::shared_ptr<ChessPiece> ChessPiece::CP(Piece cp,chcall f1,chcall f2)
{
    switch (cp)
    {
    case BROOK:
        return std::make_shared<Rook>(PieceColor::Black,f1,f2);
    case WROOK:
        return std::make_shared<Rook>(PieceColor::White, f1, f2);
    case BKNIGHT:
        return std::make_shared<Knight>(PieceColor::Black, f1, f2);
    case WKNIGHT:
        return std::make_shared<Knight>(PieceColor::White, f1, f2);
    case BBISHOP:
        return std::make_shared<Bishop>(PieceColor::Black, f1, f2);
    case WBISHOP:
        return std::make_shared<Bishop>(PieceColor::White, f1, f2);
    case BQUEEN:
        return std::make_shared<Queen>(PieceColor::Black, f1, f2);
    case WQUEEN:
        return std::make_shared<Queen>(PieceColor::White, f1, f2);
    case BPAWN:
        return std::make_shared<Pawn>(PieceColor::Black, f1, f2);
    case WPAWN:
        return std::make_shared<Pawn>(PieceColor::White, f1, f2);
    case BKING:
        return std::make_shared<King>(PieceColor::Black, f1, f2);
    case WKING:
        return std::make_shared<King>(PieceColor::White, f1, f2);
    case EMPTY:
        return NULL;
    default:
        throw std::logic_error("unknown chess type!");;
    }
}