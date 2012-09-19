#ifndef __CHESS_MOVE_H_
#define __CHESS_MOVE_H_

#include "BoardPosition.h"
#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;
using boost::shared_ptr;

class ChessPiece;
class ChessBoard;

enum ChessMoveType {
	Normal,
	WhiteQueenSideCastle,
	WhiteKingSideCastle,
	BlackQueenSideCastle,
	BlackKindSideCastle
};

class ChessMove {
	public:
		const ChessPiece *piece;
		BoardPosition* initialPosition;
		BoardPosition* finalPosition;

		~ChessMove();

		// For special moves like castles and en passe.
		ChessMove *special;
		ChessMoveType type;

		// Normal moves
		ChessMove(const ChessBoard* board, shared_ptr<string> move);
		ChessMove(const ChessPiece* piece, BoardPosition* initial, BoardPosition* final); 
		
		// Castles
		// ChessMove(ChessMoveType type);

		// En Passent
		// TODO: Implement

		bool isValid();
		const string& toString();
	
	private:
		shared_ptr<string> stringRep;
};

#endif
