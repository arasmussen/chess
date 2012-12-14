#ifndef __CHESS_PIECE_H_
#define __CHESS_PIECE_H_

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
    ChessPiece(ChessPieceColor color, ChessPieceType type);

    ChessPieceColor color;
    ChessPieceType type;
};

#endif
