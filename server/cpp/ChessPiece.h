#ifndef __CHESS_PIECE_H_
#define __CHESS_PIECE_H_

#include "BoardPosition.h"

enum ChessPieceType {
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King
};

enum ChessPieceColor {
  White,
  Black
};

class ChessPiece {
  public:
    ChessPieceColor color;
    ChessPieceType type;
    BoardPosition position;

    ChessPiece(ChessPieceColor color, ChessPieceType type, BoardPosition &position);
};

#endif
