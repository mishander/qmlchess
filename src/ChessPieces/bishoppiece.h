#ifndef BISHOPPIECE_H
#define BISHOPPIECE_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(PieceColor _color, chcall isBlocked, chcall isSameColor);
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y ) final override;
    virtual std::wstring imageName() const final { return L"bishop_" + colorName(); };
};

#endif // BISHOPPIECE_H
