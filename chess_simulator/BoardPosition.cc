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
	row(7 - (pos[1] - '1')),
	column(7 - (pos[0] - 'a')) 
{}

bool BoardPosition::isValid() {
	return 0 <= row && row <= 7 && 0 <= column && column <= 7;
}
