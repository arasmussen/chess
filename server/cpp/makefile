CC = g++
CFLAGS = -g -Wall -DHAVE_NETINET_IN_H
BUILD_DIR = $(CPP_CHESS_ROOT)/bin
OBJS = ChessGameManager.o ChessGame.o ChessBoard.o ChessAlgorithm.o ChessMove.o ChessPiece.o BoardPosition.o ChessColor.o
OUT_OBJS = $(addprefix $(BUILD_DIR)/, $(OBJS))
EXEC = startServer
LIBS = /usr/local/lib

MAIN_FILE = ChessGameServerHandler.cc

THRIFT_SRC_DIR = $(CPP_CHESS_ROOT)/server/thrift/gen-cpp
THRIFT_SRCS = $(addprefix $(THRIFT_SRC_DIR)/, ChessGameServer.cpp ChessGameServer_constants.cpp ChessGameServer_types.cpp)

$(BUILD_DIR)/%.o : %.cc %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/play_game.out: $(MAIN_FILE) $(BUILD_DIR)/ChessGameManager.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(EXEC)  -I $(THRIFT_SRC_DIR) -I$(BOOST_DIR) -I$(THRIFT_CPP_DIR)  -L $(LIBS) \
																						$(MAIN_FILE) $(OUT_OBJS) $(THRIFT_SRCS) -lpthread -lthrift 

$(BUILD_DIR)/ChessGameManager.o : $(BUILD_DIR)/ChessGame.o

$(BUILD_DIR)/ChessGame.o: $(BUILD_DIR)/ChessBoard.o $(BUILD_DIR)/ChessAlgorithm.o

$(BUILD_DIR)/ChessAlgorithm.o : $(BUILD_DIR)/ChessMove.o $(BUILD_DIR)/ChessColor.o

$(BUILD_DIR)/ChessBoard.o: $(BUILD_DIR)/ChessMove.o

$(BUILD_DIR)/ChessMove.o: $(BUILD_DIR)/ChessPiece.o

$(BUILD_DIR)/ChessPiece.o: $(BUILD_DIR)/BoardPosition.o

clean:
	rm -f $(BUILD_DIR)/$(EXEC) $(OUT_OBJS)
