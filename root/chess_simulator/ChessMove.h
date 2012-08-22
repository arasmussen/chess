#ifndef __CHESS_MOVE_H_
#define __CHESS_MOVE_H_

#include "BoardPosition.h"
#include <string>
using namespace std;

class ChessPiece;

enum ChessMoveType {
	Normal,
	WhiteQueenSideCastle,
	WhiteKingSideCastle,
	BlackQueenSideCastle,
	BlackKindSideCastle
};

class ChessMove {
	public:
		ChessPiece *piece;
		BoardPosition initialPosition;
		BoardPosition finalPosition;

		// For special moves like castles and en passe.
		ChessMove *special;
		ChessMoveType type;

		// Normal moves
		ChessMove(string move);
		ChessMove(ChessPiece *piece, BoardPosition &initial, BoardPosition &final); 
		
		// Castles
		// ChessMove(ChessMoveType type);

		// En Passent
		// TODO: Implement

		string& toString();
	
	private:
		string stringRep;
};

#endif
