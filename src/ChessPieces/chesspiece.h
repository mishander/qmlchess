#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <set>
#include <stdint.h>
#include <memory>
#include <functional>


enum class PieceType {
	EMPTY,
	KING,
	QUEEN,
	KNIGHT,
	BISHOP,
	ROOK,
	PAWN
};

enum class PieceColor {
	White = 0,
	Black
};

enum Piece
{
	EMPTY, WKING, WQUEEN, WKNIGHT, WBISHOP, WROOK, WPAWN, BKING, BQUEEN, BKNIGHT, BBISHOP, BROOK, BPAWN
};


class ChessPosition
{
public:
	ChessPosition() {};
	ChessPosition(uint8_t _index)
	{
	    x = _index % 8;
	    y = _index / 8;
		index = _index;
	}
	uint8_t x, y, index;
};
typedef std::function<bool(uint8_t, uint8_t)> chcall;

class ChessPiece
{
public:
	ChessPiece() {};
    ChessPiece(Piece _type, uint8_t index);
    ChessPiece(Piece _type);
    //no inherited ctors yet :(
    ChessPiece(PieceColor _color, chcall isBlocked, chcall isSameColor);
    std::wstring colorName() const;
    virtual std::set<uint8_t> getPossibleMoves(uint8_t x, uint8_t y) = 0;
    bool isValid(const uint8_t positionX, const uint8_t positionY)  const;
    bool addIfNotBlocked(const uint8_t x, const uint8_t y);
    void addDXYRange(const uint8_t x, const uint8_t y);
    void addXYRange(const uint8_t x, const uint8_t y);
    void clearPossibles();
    static std::shared_ptr<ChessPiece> CP(Piece cp, chcall f1, chcall f2);
	virtual std::wstring imageName() const = 0;
	PieceColor Color() const { return m_color; }
	uint8_t x() { m_position.x; }
	uint8_t y() { m_position.y; }
	uint8_t index() { m_position.index; }
protected:
    chcall m_isBlocked;
    chcall m_isSameColor;
	std::set<uint8_t> m_possibleMoves;
	Piece m_type;
	ChessPosition m_position;
	PieceColor m_color;
};
#endif