#include "ChessGameManager.h"
#include "ChessGame.h"
#include <stdlib.h>
#include <iostream>

void *startThread(void *ptr) {
  ChessGame *game = (ChessGame *)ptr;
  game->run();
}

ChessGameManager::ChessGameManager() {

}

ChessGameManager::~ChessGameManager() {
  for (vector<ChessGame *>::iterator it = activeGames.begin(); it != activeGames.end(); it++) {
    delete *it;
  }
  for (vector<pthread_t *>::iterator it = activeThreads.begin(); it != activeThreads.end(); it++) {
    delete *it;
  }
}

void ChessGameManager::startGame(const string& whiteAlgorithm, const string& blackAlgorithm) {
  ChessGame *newGame = new ChessGame(whiteAlgorithm, blackAlgorithm);
  activeGames.push_back(newGame);

  pthread_t *newThread = new pthread_t;
  activeThreads.push_back(newThread);

  pthread_create(newThread, NULL, startThread, (void *)newGame);
}

void ChessGameManager::finish() {
  for (vector<pthread_t *>::iterator it = activeThreads.begin(); it != activeThreads.end(); it++) {
    pthread_join(**it, NULL);
  }
}

