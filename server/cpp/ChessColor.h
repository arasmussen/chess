#ifndef __CHESS_COLOR_H_
#define __CHESS_COLOR_H_

#include <string>

enum ChessColor {
  White,
  Black
};

const std::string& colorToString(ChessColor c);

#endif
