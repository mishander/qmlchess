#ifndef KNIGHTPIECE_H
#define KNIGHTPIECE_H

#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(PieceColor _color, chcall isBlocked, chcall isSameColor);
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) final;
    virtual std::wstring imageName() const final { return L"knight_" + colorName(); };
};

#endif // KNIGHTPIECE_H
