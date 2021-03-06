#include "ChessGame.h"

#include "ChessAlgorithm.h"
#include "ChessBoard.h"
#include "ChessColor.h"
#include "ChessMove.h"

#include <boost/shared_ptr.hpp>
#include <csignal>
#include <iostream>

using boost::shared_ptr;

ChessGame::ChessGame(const string& whiteAlgorithm, const string& blackAlgorithm) :
  whiteAlgorithm(new ChessAlgorithm(whiteAlgorithm, White)),
  blackAlgorithm(new ChessAlgorithm(blackAlgorithm, Black)),
  board(new ChessBoard())
{
  struct sigaction* act = new struct sigaction;
  act->sa_handler = SIG_IGN;
  sigemptyset(&act->sa_mask);
  act->sa_flags = 0;
  sigaction(SIGPIPE, act, NULL);
}

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

  whiteMove = new ChessMove(White, whiteAlgorithm->getFirstMove());
  while (true) {
    if (applyMove(whiteAlgorithm, blackAlgorithm, whiteMove)) {
      break;
    }

    blackMove = new ChessMove(Black, blackAlgorithm->getMove(whiteMove->toString()));
    if (applyMove(blackAlgorithm, whiteAlgorithm, blackMove)) {
      break;
    }

    whiteMove = new ChessMove(White, whiteAlgorithm->getMove(blackMove->toString()));
  }

  whiteAlgorithm->stop();
  blackAlgorithm->stop();

  // Dummy return until we get win-game logic.
  return WhiteWin;
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
    default:
      cerr << "Error: Unhandled ChessMoveResult in ChessGame::ApplyMove" << endl;
      return false;
  }
}
