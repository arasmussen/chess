#include "ChessBoard.h"
#include "ChessPiece.h"
#include "BoardPosition.h"
#include "ChessMove.h"

int startingBoard [BOARD_SIZE][BOARD_SIZE][2] =
  {
    {{Black, Rook}, {Black, Knight}, {Black, Bishop}, {Black, King}, {Black, Queen}, {Black, Bishop}, {Black, Knight}, {Black, Rook}},
    {{Black, Pawn}, {Black, Pawn},   {Black, Pawn},   {Black, Pawn}, {Black, Pawn},  {Black, Pawn},   {Black, Pawn},   {Black, Pawn}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{-1,-1},       {-1,-1},         {-1,-1},         {-1,-1},       {-1,-1},        {-1,-1},         {-1,-1},         {-1,-1}},
    {{White, Pawn}, {White, Pawn},   {White, Pawn},   {White, Pawn}, {White, Pawn},  {White, Pawn},   {White, Pawn},   {White, Pawn}},
    {{White, Rook}, {White, Knight}, {White, Bishop}, {White, King}, {White, Queen}, {White, Bishop}, {White, Knight}, {White, Rook}}
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
    const BoardPosition* start = move->initialPosition.get();
    const BoardPosition* end = move->finalPosition.get();
    if (board[start->row][start->column]) {
      return Continue;
    }
  }

  return Error;
}
