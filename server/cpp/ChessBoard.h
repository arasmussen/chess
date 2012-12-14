#ifndef __CHESS_BOARD_H_
#define __CHESS_BOARD_H_

#define BOARD_SIZE 8

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class ChessPiece;
class ChessMove;
class BoardPosition;

enum ChessMoveResult {
  Continue,
  Checkmate,
  Error
};

class ChessBoard {
 public:
  ChessBoard();
  
  ChessMoveResult performMove(ChessMove *move);  

 private:
  shared_ptr<ChessPiece> board [BOARD_SIZE][BOARD_SIZE];
};

#endif
