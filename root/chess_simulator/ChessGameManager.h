#ifndef __CHESSGAME_MANAGER_H_
#define __CHESSGAME_MANAGER_H_

#include <vector>
#include <pthread.h>
using namespace std;

class ChessGame;

class ChessGameManager {
	public:
		ChessGameManager();
		~ChessGameManager();

		void startGame(const char *whiteAlgorithm,const char *blackAlgorithm);

		void finish();
	private:
		vector<ChessGame *> activeGames;
		vector<pthread_t *> activeThreads;
};

#endif
