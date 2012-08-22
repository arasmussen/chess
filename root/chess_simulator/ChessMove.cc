#include "ChessMove.h"
#include "ChessPiece.h"

ChessMove::ChessMove(ChessPiece *piece, BoardPosition &initial, BoardPosition &final) :
	piece(piece),
	initialPosition(initial),
	finalPosition(final),
	type(Normal),
	special(NULL)
{} 

ChessMove::ChessMove(string move) :
	stringRep(move)
{}

string& ChessMove::toString() {
	return stringRep;
}
/*
ChessMove::ChessMove(ChessMoveType type) {
	// TODO: Implement.
}
*/
