#include "ChessBoard.h"

#include "BoardPosition.h"
#include "ChessColor.h"
#include "ChessMove.h"

int startingBoard [BOARD_SIZE][BOARD_SIZE][2] =
  {
    {{White, tRook}, {White, tKnight}, {White, tBishop}, {White, tQueen}, {White, tKing}, {White, tBishop}, {White, tKnight}, {White, tRook}},
    {{White, tPawn}, {White, tPawn},   {White, tPawn},   {White, tPawn}, {White, tPawn},  {White, tPawn},   {White, tPawn},   {White, tPawn}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{Black, tPawn}, {Black, tPawn},   {Black, tPawn},   {Black, tPawn}, {Black, tPawn},  {Black, tPawn},   {Black, tPawn},   {Black, tPawn}},
    {{Black, tRook}, {Black, tKnight}, {Black, tBishop}, {Black, tQueen}, {Black, tKing}, {Black, tBishop}, {Black, tKnight}, {Black, tRook}}
  };

ChessBoard::ChessBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (startingBoard[i][j][0] != -1) {
        board[i][j].reset(ChessPiece::makePiece((ChessColor)startingBoard[i][j][0],
                                                (ChessPieceType)startingBoard[i][j][1]));
      }
    }
  }
}

ChessMoveResult ChessBoard::performMove(ChessMove *move) {
  if (move->isValid()) {
    shared_ptr<ChessPiece>& start = getPiece(move->initialPosition.get()); 
    shared_ptr<ChessPiece>& end = getPiece(move->finalPosition.get());
    if (start.get()) {
      // First check that we aren't moving the other player's piece
      if (start->color != move->getPlayerColor()) {
        return Error;
      }

      // First check the move is valid for the given piece.
      if (!start->validMove(this, move->initialPosition.get(), move->finalPosition.get())) {
        return Error;
      }

      // TODO: Check for en passent and pawn reaching end of board

      // Are we taking a piece?
      if (end.get()) {
        // Make sure its the other color and not the king
        if (end->color == start->color || end->type == tKing) {
          return Error;
        }
        end.reset();
      }

      // Move piece
      end.swap(start);

      return Continue;
    }
  }

  return Error;
}

bool ChessBoard::isOccupied(const BoardPosition* p) const
{
  return getPiece(p).get() != NULL;
}

shared_ptr<const ChessPiece> ChessBoard::getPiece(const BoardPosition* p) const {
  return board[p->row - 1][p->column - 1];
}

shared_ptr<ChessPiece>& ChessBoard::getPiece(const BoardPosition* p)
{
  return board[p->row - 1][p->column - 1];
}
