#ifndef __CHESS_ALGORITHM_H_
#define __CHESS_ALGORITHM_H_

#include <string>
using namespace std;

class ChessMove;

enum Color {
	White,
	Black
};

enum EndGameResult {
	WinByCheckmate,
	WinByIllegalMove,
	LoseByCheckmate,
	LoseByIllegalMove
};

class ChessAlgorithm {
	public:
		ChessAlgorithm(const string& algorithm, Color color);
		~ChessAlgorithm();

		void start();
		void stop();

		void getFirstMove(ChessMove *&receivedMove);
		void getMove(ChessMove *sendMove, ChessMove *&receivedMove);

		void didFinish(EndGameResult result);
	private:
		string algorithm;
		Color color;
		int readPipe[2];
		int writePipe[2];

		const string& colorToString(Color c);
		const string& endGameResultToString(EndGameResult result);

		string readFromPipe();
		void writeToPipe(const string& move);
};

#endif
