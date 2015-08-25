#include "pawnpiece.h"
#include "../utils.h"

Pawn::Pawn(PieceColor _color, chcall isBlocked, chcall isSameColor)
{
    m_color = _color;
    m_isBlocked = isBlocked;
    m_isSameColor = isSameColor;
};
std::set<uint8_t> Pawn::getPossibleMoves(uint8_t x, uint8_t y)
{
    if (m_possibleMoves.empty())
    {
        uint8_t tmpy = (m_color == PieceColor::White) ? (y - 1) : (y + 1);
        if (!m_isBlocked(x, tmpy))
        {
            m_possibleMoves.insert(tmpy * 8 + x);
            if (y == 1 || y == 6)
            {
                uint8_t tmpy2 = (m_color == PieceColor::White) ? (y - 2) : (y + 2);
                if (!m_isBlocked(x, tmpy2))
                {
                    m_possibleMoves.insert(tmpy2 * 8 + x);
                }
            }
        }

        //attack	
        if ((x != 0) && m_isBlocked(x - 1, tmpy) && !m_isSameColor(x - 1, tmpy))
            m_possibleMoves.insert(tmpy * 8 + (x - 1));
        if ((x != 8) && m_isBlocked(x + 1, tmpy) && !m_isSameColor(x + 1, tmpy))
            m_possibleMoves.insert(tmpy * 8 + (x + 1));
    }
    return m_possibleMoves;
};

