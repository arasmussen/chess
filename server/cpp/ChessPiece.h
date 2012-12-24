#ifndef __CHESS_PIECE_H_
#define __CHESS_PIECE_H_

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

enum ChessPieceColor {
  White,
  Black
};

class ChessPiece {
 public:
  // Returns an allocated chess piece.
  static ChessPiece* makePiece(ChessPieceColor c, ChessPieceType t);  

  ChessPiece(ChessPieceColor color, ChessPieceType type);
  virtual ~ChessPiece();

  virtual bool validMove(const ChessBoard* board, const BoardPosition* start,
                         const BoardPosition* end) const = 0;

  ChessPieceColor color;
  ChessPieceType type;
};

class Pawn : public ChessPiece {
 public:
  Pawn(ChessPieceColor c);
  ~Pawn();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Knight : public ChessPiece {
 public:
  Knight(ChessPieceColor c);
  ~Knight();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Bishop : public ChessPiece {
 public:
  Bishop(ChessPieceColor c);
  ~Bishop();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Rook : public ChessPiece {
 public:
  Rook(ChessPieceColor c);
  ~Rook();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

class Queen : public ChessPiece {
 public:
  Queen(ChessPieceColor c);
  ~Queen();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;

 private:
  // A Queen is a combination of a rook and a bishop
  const Rook m_rook;
  const Bishop m_bishop;
};

class King : public ChessPiece {
 public:
  King(ChessPieceColor c);
  ~King();

  bool validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const;
};

#endif
