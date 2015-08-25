#ifndef QUEENPIECE_H
#define QUEENPIECE_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(PieceColor _color, chcall isBlocked, chcall isSameColor);
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) final override;
    virtual std::wstring imageName() const final { return L"queen_" + colorName(); };
};

#endif // QUEENPIECE_H
