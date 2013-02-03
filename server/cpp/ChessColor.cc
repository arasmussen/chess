#include "ChessColor.h"

static const std::string kWhite("White");
static const std::string kBlack("Black");
static const std::string kError("Forgot to update colorToString function");

const std::string& colorToString(ChessColor c) {
  switch(c) {
    case White:
      return kWhite;
    case Black:
      return kBlack;
    default:
      return kError;
  }
}



