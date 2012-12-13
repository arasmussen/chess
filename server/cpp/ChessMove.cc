#include "ChessMove.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessMove::ChessMove(const ChessPiece* piece, BoardPosition* initial, BoardPosition* final) :
  piece(piece),
  initialPosition(initial),
  finalPosition(final),
  type(Normal),
  special(NULL),
  stringRep()
{}

ChessMove::ChessMove(const ChessBoard* board, shared_ptr<string> move) :
  piece(NULL),
  initialPosition(NULL),
  finalPosition(NULL),
  special(NULL),
  type(Normal),
  stringRep(move)
{
  int indexOfSeparator = move->find_first_of(':');
  if (indexOfSeparator == 2 && move->length() == 5) {
    initialPosition = new BoardPosition(move->substr(0, 2));
    finalPosition = new BoardPosition(move->substr(indexOfSeparator+1, 2));
    piece = board->pieceAtPosition(initialPosition);
  }
}

ChessMove::~ChessMove() {
  if (initialPosition) {
    delete initialPosition;
  }

  if (finalPosition) {
    delete finalPosition;
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
