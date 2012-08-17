#ifndef __CHESS_BOARD_H_
#define __CHESS_BOARD_H_

#define BOARD_SIZE 8

class ChessPiece;
class ChessMove;

enum ChessMoveResult {
	Continue,
	Checkmate,
	Error
};

class ChessBoard {
	public:
		ChessBoard();
		~ChessBoard();
	
	ChessMoveResult performMove(ChessMove *move);	

	private:
		ChessPiece *board [BOARD_SIZE][BOARD_SIZE];
};

#endif
