#ifndef ROOKPIECE_H
#define ROOKPIECE_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(PieceColor _color, chcall isBlocked, chcall isSameColor);
	virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) final override;
	virtual std::wstring imageName() const final { return L"rook_" + colorName(); };
};

#endif // ROOKPIECE_H
