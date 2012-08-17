#include "ChessGameManager.h"

int main(int argc, char** argv) {
	ChessGameManager manager;

	manager.startGame(argv[1], argv[2]);
	manager.startGame(argv[1], argv[2]);

	manager.finish();
}
