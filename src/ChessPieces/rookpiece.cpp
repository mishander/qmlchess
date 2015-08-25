#include "rookpiece.h"

Rook::Rook(PieceColor _color, chcall isBlocked, chcall isSameColor)
{
    m_color = _color;
    m_isBlocked = isBlocked;
    m_isSameColor = isSameColor;
};
std::set<uint8_t> Rook::getPossibleMoves(uint8_t x, uint8_t y)
{
    if (m_possibleMoves.empty())
    {
        addXYRange(x,y);
    }
    return m_possibleMoves; 
};

