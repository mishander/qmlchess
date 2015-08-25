#ifndef PAWNPIECE_H
#define PAWNPIECE_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(PieceColor _color, chcall isBlocked, chcall isSameColor);
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) final override;
    virtual std::wstring imageName() const final { return L"pawn_" + colorName(); };
};

#endif // PAWNPIECE_H
