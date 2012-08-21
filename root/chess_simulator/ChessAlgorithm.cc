#include "ChessAlgorithm.h"
#include "ChessMove.h"
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>

#define ERROR(s) { cerr << "ERROR " << s << endl; exit(1); }

using namespace std;

ChessAlgorithm::ChessAlgorithm(const char *algorithm, Color color) :
	color(color) 
{
	int length = strlen(algorithm);
	this->algorithm = new char[length];
	strcpy(this->algorithm, algorithm);	
}

ChessAlgorithm::~ChessAlgorithm() {
	delete [] algorithm;
	close(writePipe[1]);
	close(readPipe[0]);
}

void ChessAlgorithm::start() {
	int pid;

	if (pipe(writePipe) || pipe(readPipe)) {
		ERROR("Pipe Creation Failed");
	}

	// Apparently this can happen and if it does things will break.
	// Deal with it when it does.
	if (writePipe[0] < 2 || writePipe[1] < 2 || readPipe[0] < 2 || readPipe[1] < 2) {
		ERROR("Pipe creation weird case encountered!");
	}

	pid = fork();
	if (pid < 0) {
		ERROR("Fork Failed");
	}

	if (pid == 0) { // Child
		close(writePipe[1]);
		close(readPipe[0]);

		if (dup2(writePipe[0], 0) < 0) { // Replace stdin
			ERROR("Replacing stdin failed");
		}

		if (dup2(readPipe[1], 1) < 0) { // Replace stdout
			ERROR("Replacing stdout failed");
		}

		// Start algorithm
		if (execv(algorithm, NULL) < 0) {
			ERROR("Execv failed");
		} 
	} else {
		close(writePipe[0]);
		close(readPipe[1]);

		// Let algorithm know which color it is.
		writeToPipe(string(colorToString(color)));
	}
}

void ChessAlgorithm::stop() {
	int status;
	wait(&status);
}

void ChessAlgorithm::getFirstMove(ChessMove *&receivedMove) {
	string move = readFromPipe();
	receivedMove = new ChessMove(move);
}

void ChessAlgorithm::getMove(ChessMove *sendMove, ChessMove *&receivedMove) {
	writeToPipe(sendMove->toString());

	string move = readFromPipe();
	receivedMove = new ChessMove(move);
}

void ChessAlgorithm::didWin(const char *reason) {
	writeToPipe(string(reason));	
}

void ChessAlgorithm::didLose(const char *reason) {
	writeToPipe(string(reason));	
}

const char * ChessAlgorithm::colorToString(Color c) {
	switch(c) {
		case White:
			return "White";
		case Black:
			return "Black";
		default:
			ERROR("Invalid Color");
	}
}

string ChessAlgorithm::readFromPipe() {
	char buf[30];
	int bytesRead = read(readPipe[0], buf, 30);
	
	if (bytesRead < 0) {
		ERROR("Read error");
	}	

	return string(buf, bytesRead); 
}

void ChessAlgorithm::writeToPipe(string move) {
	move.append((char *)"\n");

	int bytesWritten = write(writePipe[1], move.c_str(), move.length()); 
	if (bytesWritten < 0) {
		ERROR("Write Error");
	}

}
