#ifndef __CHESS_MOVE_H_
#define __CHESS_MOVE_H_

#include "BoardPosition.h"
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
    ChessMove(shared_ptr<string> move);
    
    // Castles
    // ChessMove(ChessMoveType type);

    // En Passent
    // TODO: Implement

    bool isValid();
    const string& toString();

    scoped_ptr<const BoardPosition> initialPosition;
    scoped_ptr<const BoardPosition> finalPosition;

    // For special moves like castles and en passe.
    //  ChessMove *special;
    ChessMoveType type;
   
  private:
    const string stringRep;
};

#endif
