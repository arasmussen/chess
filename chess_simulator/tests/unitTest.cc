#include "../ChessGame.h"

int main(int argc, char** argv) {
	ChessGame game(argv[1], argv[2]);
	game.run();
}
