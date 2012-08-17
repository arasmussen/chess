#include "ChessGame.h"

int main(int argc, char** argv) {
	ChessGame mainGame(argv[1], argv[2]);
	return mainGame.run(); 
}
