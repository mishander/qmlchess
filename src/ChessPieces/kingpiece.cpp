#include "kingpiece.h"
#include "../utils.h"

King::King(PieceColor _color, chcall isBlocked, chcall isSameColor)
{
    m_color = _color;
    m_isBlocked = isBlocked;
    m_isSameColor = isSameColor;
};
std::set<uint8_t> King::getPossibleMoves(uint8_t x, uint8_t y)
{
    if (m_possibleMoves.empty())
    {
        addIfNotBlocked(x - 1, y - 1);
        addIfNotBlocked(x - 1, y);
        addIfNotBlocked(x - 1, y + 1);
        addIfNotBlocked(x, y - 1);
        addIfNotBlocked(x, y + 1);
        addIfNotBlocked(x + 1, y - 1);
        addIfNotBlocked(x + 1, y);
        addIfNotBlocked(x + 1, y + 1);
    }
    return m_possibleMoves;
};

