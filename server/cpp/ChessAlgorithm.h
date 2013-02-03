#ifndef __CHESS_ALGORITHM_H_
#define __CHESS_ALGORITHM_H_

#include "ChessColor.h"

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;
using boost::shared_ptr;

class ChessMove;

enum EndGameResult {
  WinByCheckmate,
  WinByIllegalMove,
  LoseByCheckmate,
  LoseByIllegalMove
};

class ChessAlgorithm {
  public:
    ChessAlgorithm(const string& algorithm, ChessColor color);
    ~ChessAlgorithm();

    void start();
    void stop();

    shared_ptr<string> getFirstMove();
    shared_ptr<string> getMove(const string& sendMove);

    void didFinish(EndGameResult result);
  private:
    vector<string> tokens;
    ChessColor color;
    int readPipe[2];
    int writePipe[2];

    const string& endGameResultToString(EndGameResult result);

    shared_ptr<string> readFromPipe();
    void writeToPipe(const string& move);
};

#endif
