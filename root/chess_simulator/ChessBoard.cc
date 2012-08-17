#include "ChessBoard.h"
#include "ChessPiece.h"
#include "BoardPosition.h"
#include "ChessMove.h"

int startingBoard [BOARD_SIZE][BOARD_SIZE][2] =
	{ 
		{{Black, Rook}, {Black, Knight}, {Black, Bishop}, {Black, King}, {Black, Queen}, {Black, Bishop}, {Black, Knight}, {Black, Rook}},
		{{Black, Pawn}, {Black, Pawn},   {Black, Pawn},   {Black, Pawn}, {Black, Pawn},  {Black, Pawn},   {Black, Pawn},   {Black, Pawn}},
		{{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
		{{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
		{{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
		{{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
		{{White, Pawn}, {White, Pawn},   {White, Pawn},   {White, Pawn}, {White, Pawn},  {White, Pawn},   {White, Pawn},   {White, Pawn}},
	  {{White, Rook}, {White, Knight}, {White, Bishop}, {White, King}, {White, Queen}, {White, Bishop}, {White, Knight}, {White, Rook}}
	};

ChessBoard::ChessBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (startingBoard[i][j][0] != -1) {
				BoardPosition position(i,j);
				board[i][j] = new ChessPiece((ChessPieceColor)startingBoard[i][j][0], (ChessPieceType)startingBoard[i][j][1], position);
			} else {
				board[i][j] = NULL;
			}
		}
	}
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != NULL) {
				delete board[i][j];
			}
		}
	}
}

ChessMoveResult ChessBoard::performMove(ChessMove *move) {
	if (move->toString() == string("Second Move")) {
		return Checkmate;
	}
	return Continue;
}

