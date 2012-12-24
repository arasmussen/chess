#ifndef __CHESS_BOARD_H_
#define __CHESS_BOARD_H_

#define BOARD_SIZE 8

#include "ChessPiece.h"
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

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

  bool isOccupied(const BoardPosition* p) const;

 private:
  shared_ptr<ChessPiece>& getPiece(const BoardPosition* p);
  shared_ptr<const ChessPiece> getPiece(const BoardPosition* p) const;

  shared_ptr<ChessPiece> board [BOARD_SIZE][BOARD_SIZE];
};

#endif
