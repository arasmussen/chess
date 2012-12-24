#include "BoardPosition.h"

BoardPosition::BoardPosition() :
  row(-1),
  column(-1)
{}

BoardPosition::BoardPosition(int row, int column) :
  row(row),
  column(column)
{}

BoardPosition::BoardPosition(const string& pos) :
  row(pos[1] - '0'),
  column(pos[0] - 'a' + 1)
{}

bool BoardPosition::isValid() const {
  return 1 <= row && row <= 8 && 1 <= column && column <= 8;
}
