#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "chesspiece.h"

class King : public ChessPiece
{
public:
    King(PieceColor _color, chcall isBlocked, chcall isSameColor);
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) final;
    virtual std::wstring imageName() const final { return L"king_" + colorName(); };
};

#endif // KINGPIECE_H
