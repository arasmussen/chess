#include "ChessPiece.h"
#include "BoardPosition.h"
#include "ChessBoard.h"
#include <cmath>

ChessPiece* ChessPiece::makePiece(ChessColor c, ChessPieceType t) {
  switch (t) {
    case tPawn:
      return new Pawn(c);
    case tKnight:
      return new Knight(c);
    case tBishop:
      return new Bishop(c);
    case tRook:
      return new Rook(c);
    case tQueen:
      return new Queen(c);
    case tKing:
      return new King(c);
    default:
      cerr << "Error: Unhandled ChessPieceType in ChessPiece::makePiece" << endl;
      return NULL;
  }
}

ChessPiece::ChessPiece(ChessColor color, ChessPieceType type) :
  color(color),
  type(type)
{
}

ChessPiece::~ChessPiece()
{}

/*
  *** Pawn ***
*/

Pawn::Pawn(ChessColor c) :
  ChessPiece(c, tPawn)
{
}

Pawn::~Pawn()
{}

bool Pawn::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  int colorMult = (color == White ? 1 : -1);
  
  // Normal Move
  if (end->row - start->row == colorMult * 1 && end->column == start->column) {
    return true;
  }

  // Double move in beginning
  if (end->row - start->row == colorMult * 2 && end->column == start->column &&
      ((color == White && start->row == 2) ||
       (color == Black && start->row == 7)) ) {
    return true;
  }

  // Capture move
  if (end->row - start->row == colorMult * 1 && 
      abs(start->column - end->column) == 1 &&
      board->isOccupied(end) ) {
    return true;
  }
 
  // Note that ChessBoard will handle special Pawn moves like en passent and pawn advancement.
  return false;
}

/*
  *** Knight ***
*/

Knight::Knight(ChessColor c) :
  ChessPiece(c, tKnight)
{
}

Knight::~Knight()
{}

bool Knight::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  int rowDiff = abs(start->row - end->row);
  int colDiff = abs(start->column - end->column);

  return (rowDiff == 1 && colDiff == 2) || (rowDiff == 2 && colDiff == 1);
}

/*
  *** Bishop ***
*/

Bishop::Bishop(ChessColor c) :
  ChessPiece(c, tBishop)
{
}

Bishop::~Bishop()
{}

bool Bishop::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  int rowDiff = abs(start->row - end->row);
  int colDiff = abs(start->column - end->column);

  return (rowDiff == colDiff); 
}

/*
  *** Rook ***
*/

Rook::Rook(ChessColor c) :
  ChessPiece(c, tRook)
{
}

Rook::~Rook()
{}

bool Rook::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  int rowDiff = abs(start->row - end->row);
  int colDiff = abs(start->column - end->column);

  return (rowDiff == 0 || colDiff == 0);
}

/*
  *** Queen ***
*/

Queen::Queen(ChessColor c) :
  ChessPiece(c, tQueen),
  m_rook(c),
  m_bishop(c)
{
}

Queen::~Queen()
{}

bool Queen::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  return m_bishop.validMove(board, start, end) ||
         m_rook.validMove(board, start, end);
}

/*
  *** King ***
*/

King::King(ChessColor c) :
  ChessPiece(c, tKing)
{
}

King::~King()
{}

bool King::validMove(const ChessBoard* board, const BoardPosition* start, const BoardPosition* end) const {
  int rowDiff = abs(start->row - end->row);
  int colDiff = abs(start->column - end->column);

  return rowDiff <= 1 && colDiff <= 1;
}

