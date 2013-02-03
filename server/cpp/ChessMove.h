#ifndef __CHESS_MOVE_H_
#define __CHESS_MOVE_H_

#include "BoardPosition.h"
#include "ChessColor.h"

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
using boost::shared_ptr;
using boost::scoped_ptr;

class ChessPiece;
class ChessBoard;

enum ChessMoveType {
  Normal,
  WhiteQueenSideCastle,
  WhiteKingSideCastle,
  BlackQueenSideCastle,
  BlackKindSideCastle
};

class ChessMove {
  public:
    // Normal moves
    ChessMove(ChessColor playerColor, shared_ptr<string> move);
    
    // Castles
    // ChessMove(ChessMoveType type);

    // En Passent
    // TODO: Implement

    // Checks that the move is well-formed and doesn't stay in the 
    // same place.
    bool isValid();
    const string& toString();

    /*
      Getters
    */
    const ChessColor getPlayerColor() { return playerColor; }

    // TODO: Make these private and expose with getter;
    scoped_ptr<const BoardPosition> initialPosition;
    scoped_ptr<const BoardPosition> finalPosition;

    // For special moves like castles and en passe.
    //  ChessMove *special;
    ChessMoveType type;
   
  private:
    const string stringRep;

    // Which player is making this move.
    const ChessColor playerColor;
};

#endif
