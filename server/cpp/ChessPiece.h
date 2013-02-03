#ifndef __CHESS_PIECE_H_
#define __CHESS_PIECE_H_

#include "ChessColor.h"

class BoardPosition;
class ChessBoard;

enum ChessPieceType {
  tPawn,
  tKnight,
  tBishop,
  tRook,
  tQueen,
  tKing
};

class ChessPiece {
 public:
  // Returns an allocated chess piece.
  static ChessPiece* makePiece(ChessColor c, ChessPieceType t);  

  ChessPiece(ChessColor color, ChessPieceType type);
  virtual ~ChessPiece();

  virtual bool validMove(const ChessBoard* board, const BoardPosition* start,
                         const BoardPosition* end) const = 0;

  ChessColor color;
  ChessPieceType type;
};

class Pawn : public ChessPiece {
 public:
  Pawn(ChessColor c);
  ~Pawn();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Knight : public ChessPiece {
 public:
  Knight(ChessColor c);
  ~Knight();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Bishop : public ChessPiece {
 public:
  Bishop(ChessColor c);
  ~Bishop();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Rook : public ChessPiece {
 public:
  Rook(ChessColor c);
  ~Rook();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Queen : public ChessPiece {
 public:
  Queen(ChessColor c);
  ~Queen();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;

 private:
  // A Queen is a combination of a rook and a bishop
  const Rook m_rook;
  const Bishop m_bishop;
};

class King : public ChessPiece {
 public:
  King(ChessColor c);
  ~King();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

#endif
