CC = g++
CFLAGS = -g
OBJS = ChessGameManager.o ChessGame.o ChessBoard.o ChessAlgorithm.o ChessMove.o ChessPiece.o BoardPosition.o
BUILD_DIR = $(CHESS_ROOT)/bin
OUT_OBJS = $(addprefix $(BUILD_DIR)/, $(OBJS))

$(BUILD_DIR)/%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/play_game.out: mainGame.cc $(BUILD_DIR)/ChessGameManager.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/play_game.out  mainGame.cc $(OUT_OBJS) -lpthread

$(BUILD_DIR)/ChessGameManager.o : ChessGameManager.h $(BUILD_DIR)/ChessGame.o
 
$(BUILD_DIR)/ChessGame.o: ChessGame.h $(BUILD_DIR)/ChessBoard.o $(BUILD_DIR)/ChessAlgorithm.o

$(BUILD_DIR)/ChessAlgorithm.o : ChessAlgorithm.h $(BUILD_DIR)/ChessMove.o

$(BUILD_DIR)/ChessBoard.o: ChessBoard.h $(BUILD_DIR)/ChessMove.o

$(BUILD_DIR)/ChessMove.o: ChessMove.h $(BUILD_DIR)/ChessPiece.o

$(BUILD_DIR)/ChessPiece.o: ChessPiece.h $(BUILD_DIR)/BoardPosition.o

