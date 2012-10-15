#ifndef __CHESS_ALGORITHM_H_
#define __CHESS_ALGORITHM_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;
using boost::shared_ptr;

class ChessMove;

enum Color {
  White,
  Black
};

enum EndGameResult {
  WinByCheckmate,
  WinByIllegalMove,
  LoseByCheckmate,
  LoseByIllegalMove
};

class ChessAlgorithm {
  public:
    ChessAlgorithm(const string& algorithm, Color color);
    ~ChessAlgorithm();

    void start();
    void stop();

    shared_ptr<string> getFirstMove();
    shared_ptr<string> getMove(const string& sendMove);

    void didFinish(EndGameResult result);
  private:
    vector<string> tokens;
    Color color;
    int readPipe[2];
    int writePipe[2];

    const string& colorToString(Color c);
    const string& endGameResultToString(EndGameResult result);

    shared_ptr<string> readFromPipe();
    void writeToPipe(const string& move);
};

#endif
