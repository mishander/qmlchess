#include "knightpiece.h"

Knight::Knight(PieceColor _color, chcall isBlocked, chcall isSameColor)
{
    m_color = _color;
    m_isBlocked = isBlocked;
    m_isSameColor = isSameColor;
};
std::set<uint8_t> Knight::getPossibleMoves(uint8_t x, uint8_t y)
{
    if (m_possibleMoves.empty())
    {
        addIfNotBlocked(x - 2, y - 1);
        addIfNotBlocked(x - 2, y + 1);
        addIfNotBlocked(x - 1, y - 2);
        addIfNotBlocked(x - 1, y + 2);
        addIfNotBlocked(x + 1, y - 2);
        addIfNotBlocked(x + 1, y + 2);
        addIfNotBlocked(x + 2, y - 1);
        addIfNotBlocked(x + 2, y + 1);
    }
    return m_possibleMoves;
};

