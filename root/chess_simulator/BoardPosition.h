#ifndef __BOARD_POSITION_H_
#define __BOARD_POSITION_H_

// For NULL, everyone includes this file...
#include <cstring>

class BoardPosition {
	public:
		int row, column;

		BoardPosition();
		BoardPosition(int row, int column);
};


#endif
