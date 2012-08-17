#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPieceColor color, ChessPieceType type, BoardPosition &position) :
	position(position)
{
	this->color = color;
	this->type = type;	
}
