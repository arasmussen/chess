#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

string player;
queue<string> moves;
ifstream input;
ofstream output;

bool getMove() {
  string move;
  cin >> move;

  output << move << endl;

  if (move.find("Win") != string::npos || move.find("Lose") != string::npos) {
    return true;
  }

  return false;
}

bool sendMove() {
  if (moves.empty()) {
    return true;
  }

  cout << moves.front();
  moves.pop();
}

int main(int argc, char** argv) {
  // Determine if we are white or black
  cin >> player;

  input.open(argv[1]);
  output.open(argv[2]);

  if (!input.is_open() || !output.is_open()) {
    cerr << "Bad File: " << argv[1] << " " << argv[2] << endl;
  } 
  
  // Get list of moves from supplied file
  bool turn = (player == "White");  
  string move;
  input >> move;
  while (input.good()) {
    moves.push(move);
    input >> move;
  }


  // White needs to play first move
  if (player == "White") {
    sendMove();
  }

  // Now play
  while (!getMove() && !sendMove()) {}  
}
