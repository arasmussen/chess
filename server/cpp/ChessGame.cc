#include "ChessGame.h"
#include "ChessBoard.h"
#include "ChessAlgorithm.h"
#include "ChessMove.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <csignal>

using boost::shared_ptr;

static const char *byCheckmate = "ByCheckmate";
static const char *illegalMove = "IllegalMove";

ChessGame::ChessGame(const string& whiteAlgorithm, const string& blackAlgorithm) :
  board(new ChessBoard()),
  whiteAlgorithm(new ChessAlgorithm(whiteAlgorithm, WhitePlayer)),
  blackAlgorithm(new ChessAlgorithm(blackAlgorithm, BlackPlayer))
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

  whiteMove = new ChessMove(whiteAlgorithm->getFirstMove());
  while (true) {
    if (applyMove(whiteAlgorithm, blackAlgorithm, whiteMove)) {
      break;
    }

    blackMove = new ChessMove(blackAlgorithm->getMove(whiteMove->toString()));
    if (applyMove(blackAlgorithm, whiteAlgorithm, blackMove)) {
      break;
    }

    whiteMove = new ChessMove(whiteAlgorithm->getMove(blackMove->toString()));
  }

  whiteAlgorithm->stop();
  blackAlgorithm->stop();
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
