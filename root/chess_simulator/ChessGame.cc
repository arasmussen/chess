#include "ChessGame.h"
#include "ChessBoard.h"
#include "ChessAlgorithm.h"
#include "ChessMove.h"
#include <iostream>

static const char *byCheckmate = "ByCheckmate";
static const char *illegalMove = "IllegalMove";

ChessGame::ChessGame(const string& whiteAlgorithm, const string& blackAlgorithm) :
	board(new ChessBoard()),
	whiteAlgorithm(new ChessAlgorithm(whiteAlgorithm, White)), 
	blackAlgorithm(new ChessAlgorithm(blackAlgorithm, Black))
{}

ChessGame::~ChessGame() {
	delete board;
	delete whiteAlgorithm;
	delete blackAlgorithm;

	for (vector<ChessMove *>::iterator it = moves.begin(); it != moves.end(); it++) {
		delete *it;
	}
}

ChessGameResult ChessGame::run() {
	whiteAlgorithm->start();
	blackAlgorithm->start();	

	ChessMove *whiteMove;
	ChessMove *blackMove;
	whiteAlgorithm->getFirstMove(whiteMove);

	while (true) {
		if (applyMove(whiteAlgorithm, blackAlgorithm, whiteMove)) {
			break;
		}
		blackAlgorithm->getMove(whiteMove, blackMove);

		if (applyMove(blackAlgorithm, whiteAlgorithm, blackMove)) {
			break;
		}
		whiteAlgorithm->getMove(blackMove, whiteMove);
	}

	whiteAlgorithm->stop();
	blackAlgorithm->stop();

	cout << "End of Game" << endl;
}

bool ChessGame::applyMove(ChessAlgorithm *applier, ChessAlgorithm *receiver, ChessMove *move) {
	moves.push_back(move);
	ChessMoveResult result = board->performMove(move);

	switch (result) {
		case Checkmate:
			applier->didFinish(WinByCheckmate);
			receiver->didFinish(LoseByCheckmate);
			return true;
		case Error:
			applier->didFinish(LoseByIllegalMove);
			receiver->didFinish(WinByIllegalMove);
			return true;
		case Continue:
			return false;
	}
}
