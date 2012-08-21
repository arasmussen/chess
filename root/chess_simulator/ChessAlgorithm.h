#ifndef __CHESS_ALGORITHM_H_
#define __CHESS_ALGORITHM_H_

#include <string>
using namespace std;

class ChessMove;

enum Color {
	White,
	Black
};

class ChessAlgorithm {
	public:
		ChessAlgorithm(const char *algorithm, Color color);
		~ChessAlgorithm();

		void start();
		void stop();

		void getFirstMove(ChessMove *&receivedMove);
		void getMove(ChessMove *sendMove, ChessMove *&receivedMove);

		void didWin(const char *reason);
		void didLose(const char *reason);
	private:
		char *algorithm;
		Color color;
		int readPipe[2];
		int writePipe[2];

		const char *colorToString(Color c);
		string readFromPipe();
		void writeToPipe(string move);
};

#endif
