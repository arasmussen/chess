#include "ChessMove.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessMove::ChessMove(const ChessPiece* piece, BoardPosition* initial, BoardPosition* final) :
  piece(piece),
  initialPosition(initial),
  finalPosition(final),
  type(Normal),
  special(NULL)
{}

ChessMove::~ChessMove() {
  if (initialPosition) {
    delete initialPosition;
  }

  if (finalPosition) {
    delete finalPosition;
  }
}

ChessMove::ChessMove(const ChessBoard* board, shared_ptr<string> move) :
  stringRep(move),
  type(Normal),
  piece(NULL),
  special(NULL)
{
  int indexOfSeparator = move->find_first_of(':');
  if (indexOfSeparator == 2 && move->length() == 5) {
    initialPosition = new BoardPosition(move->substr(0, 2));
    finalPosition = new BoardPosition(move->substr(indexOfSeparator+1, 2));
    piece = board->pieceAtPosition(initialPosition);
  }
}

bool ChessMove::isValid() {
  return piece && initialPosition && initialPosition->isValid() &&
                  finalPosition && finalPosition->isValid();
}

const string& ChessMove::toString() {
  return *stringRep;
}
/*
ChessMove::ChessMove(ChessMoveType type) {
  // TODO: Implement.
}
*/
