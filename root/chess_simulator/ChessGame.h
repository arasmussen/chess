#ifndef __CHESS_GAME_H_
#define __CHESS_GAME_H_

#include <vector>
using namespace std;

class ChessBoard;
class ChessMove;
class ChessAlgorithm;

enum ChessGameResult {
	WhiteWin,
	BlackWin,
	Stalemate
};

class ChessGame {
	public:
		ChessGame(const char *whiteAlgorithm, const char *blackAlgorithm);
		~ChessGame();

		ChessGameResult run();

	private:
		ChessAlgorithm *whiteAlgorithm;
		ChessAlgorithm *blackAlgorithm;

		// State of the board
		ChessBoard *board;
		vector<ChessMove *> moves;

		bool applyMove(ChessAlgorithm *applier, ChessAlgorithm *receiver, ChessMove *move);
};

#endif