#include "ChessAlgorithm.h"
#include "ChessMove.h"
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <sstream>
#include <algorithm>
#include <iterator>

#define ERROR(s) { cerr << "ERROR " << s << endl; exit(1); }

using namespace std;

// Since we control syntax for moves we can set an upper limit here.
static const int maxMoveLength = 30;

static const string kWhitePlayer("White");
static const string kBlackPlayer("Black");
static const string kWinByCheckmate("Win:Checkmate");
static const string kWinByIllegalMove("Win:IllegalMove");
static const string kLoseByCheckmate("Lose:Checkmate");
static const string kLoseByIllegalMove("Lose:IllegalMove");


ChessAlgorithm::ChessAlgorithm(const string& algorithm, PlayerColor color) :
  color(color)
{
  // Tokenize string
  istringstream iss(algorithm);
  copy(istream_iterator<string>(iss),
       istream_iterator<string>(),
       back_inserter<vector<string> >(tokens));

}

ChessAlgorithm::~ChessAlgorithm() {
  close(writePipe[1]);
  close(readPipe[0]);
}

void ChessAlgorithm::start() {
  int pid;

  if (pipe(writePipe) || pipe(readPipe)) {
    ERROR("Pipe Creation Failed");
  }

  // Apparently this can happen and if it does things will break.
  // Deal with it when it does.
  if (writePipe[0] < 2 || writePipe[1] < 2 || readPipe[0] < 2 || readPipe[1] < 2) {
    ERROR("Pipe creation weird case encountered!");
  }

  pid = fork();
  if (pid < 0) {
    ERROR("Fork Failed");
  }

  if (pid == 0) { // Child
    close(writePipe[1]);
    close(readPipe[0]);

    if (dup2(writePipe[0], 0) < 0) { // Replace stdin
      ERROR("Replacing stdin failed");
    }

    if (dup2(readPipe[1], 1) < 0) { // Replace stdout
      ERROR("Replacing stdout failed");
    }

    const char** argv;
    if (tokens.size() > 0) {
      argv = new const char* [tokens.size() + 1];
      argv[tokens.size()] = NULL;
      int i = 0;
      for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++, i++) {
        argv[i] = it->c_str();
      }
    }
    // Start algorithm
    if (execv(argv[0], (char* const*)argv) < 0) {
      ERROR("Execv failed");
    }
  } else {
    close(writePipe[0]);
    close(readPipe[1]);

    // Let algorithm know which color it is.
    writeToPipe(colorToString(color));
  }
}

void ChessAlgorithm::stop() {
  int status;
  wait(&status);
}

shared_ptr<string> ChessAlgorithm::getFirstMove() {
  return readFromPipe();
}

shared_ptr<string> ChessAlgorithm::getMove(const string& sendMove) {
  writeToPipe(sendMove);

  return readFromPipe();
}

void ChessAlgorithm::didFinish(EndGameResult result) {
  writeToPipe(endGameResultToString(result));
}

const string& ChessAlgorithm::colorToString(PlayerColor c) {
  switch(c) {
    case WhitePlayer:
      return kWhitePlayer;
    case BlackPlayer:
      return kBlackPlayer;
    default:
      ERROR("Invalid Color");
  }
}

const string& ChessAlgorithm::endGameResultToString(EndGameResult result) {
  switch (result) {
    case WinByCheckmate:
      return kWinByCheckmate;
    case WinByIllegalMove:
      return kWinByIllegalMove;
    case LoseByCheckmate:
      return kLoseByCheckmate;
    case LoseByIllegalMove:
      return kLoseByIllegalMove;
    default:
      ERROR("Invalid EndGameResult");
  }
}

shared_ptr<string> ChessAlgorithm::readFromPipe() {
  char buf[30];
  int bytesRead = read(readPipe[0], buf, 30);

  if (bytesRead < 0) {
    return shared_ptr<string>(new string(""));
  }

  return shared_ptr<string>(new string(buf, bytesRead));
}

void ChessAlgorithm::writeToPipe(const string& move) {
  string sendMove = move;
  sendMove.append("\n");

  write(writePipe[1], sendMove.c_str(), sendMove.length());
}
