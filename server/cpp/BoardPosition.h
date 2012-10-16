#ifndef __BOARD_POSITION_H_
#define __BOARD_POSITION_H_

// For NULL, everyone includes this file...
#include <string>
#include <cstring>
using namespace std;

class BoardPosition {
  public:
    int row, column;

    BoardPosition();
    BoardPosition(int row, int column);
    BoardPosition(const string& pos);

    bool isValid();
};


#endif
