#include "ChessMove.h"
#include "ChessPiece.h"
#include "ChessBoard.h"

ChessMove::ChessMove(shared_ptr<string> move) :
  initialPosition(),
  finalPosition(),
  type(Normal),
  stringRep(*move)
{
  int indexOfSeparator = move->find_first_of(':');
  if (indexOfSeparator == 2 && move->length() == 5) {
    initialPosition.reset(new BoardPosition(move->substr(0, 2)));
    finalPosition.reset(new BoardPosition(move->substr(indexOfSeparator+1, 2)));
  }
}

bool ChessMove::isValid() {
  return initialPosition.get() && initialPosition->isValid() &&
         finalPosition.get() && finalPosition->isValid() &&
         (initialPosition->row != finalPosition->row ||
          initialPosition->column != finalPosition->column);
}

const string& ChessMove::toString() {
  return stringRep;
}
/*
ChessMove::ChessMove(ChessMoveType type) {
  // TODO: Implement.
}
*/
