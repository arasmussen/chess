#include "ChessBoard.h"
#include "ChessPiece.h"
#include "BoardPosition.h"
#include "ChessMove.h"

int startingBoard [BOARD_SIZE][BOARD_SIZE][2] =
  {
    {{Black, Rook}, {Black, Knight}, {Black, Bishop}, {Black, Queen}, {Black, King}, {Black, Bishop}, {Black, Knight}, {Black, Rook}},
    {{Black, Pawn}, {Black, Pawn},   {Black, Pawn},   {Black, Pawn}, {Black, Pawn},  {Black, Pawn},   {Black, Pawn},   {Black, Pawn}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{White, Pawn}, {White, Pawn},   {White, Pawn},   {White, Pawn}, {White, Pawn},  {White, Pawn},   {White, Pawn},   {White, Pawn}},
    {{White, Rook}, {White, Knight}, {White, Bishop}, {White, Queen}, {White, King}, {White, Bishop}, {White, Knight}, {White, Rook}}
  };

ChessBoard::ChessBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (startingBoard[i][j][0] != -1) {
        board[i][j] = shared_ptr<ChessPiece>(new ChessPiece((ChessPieceColor)startingBoard[i][j][0],
                                                            (ChessPieceType)startingBoard[i][j][1]));
      }
    }
  }
}

ChessMoveResult ChessBoard::performMove(ChessMove *move) {
  if (move->isValid()) {
    shared_ptr<ChessPiece>& start = board[move->initialPosition->row][move->initialPosition->column];
    shared_ptr<ChessPiece>& end = board[move->finalPosition->row][move->finalPosition->column];
    if (start.get()) {
      // Are we taking a piece?
      if (end.get()) {
        // Make sure its the other color and not the king
        if (end->color == start->color || end->type == King) {
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
