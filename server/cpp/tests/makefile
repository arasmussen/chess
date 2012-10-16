CC = g++
CFLAGS = -g
BUILD_DIR = $(CPP_CHESS_ROOT)/bin
OBJS = unitTest.cc ../ChessGame.cc ../ChessBoard.cc ../ChessAlgorithm.cc ../ChessMove.cc ../ChessPiece.cc ../BoardPosition.cc

all : runUnitTest algorithm

runUnitTest : $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/runUnitTest $(OBJS) 

algorithm : testAlgorithm.cc
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/algorithm testAlgorithm.cc

