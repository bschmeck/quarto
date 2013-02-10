CC=gcc

TEST_OBJS = test.o
TOP_DIR = ..
BIN_DIR = $(TOP_DIR)/bin
BUILD_DIR = .
SRC_DIR = $(TOP_DIR)/src
TEST_DIR = $(TOP_DIR)/tests
DEPS = $(SRC_DIR)/board.h
CFLAGS=-I$(SRC_DIR) -I$(BUILD_DIR)

test.o: $(TEST_DIR)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_OBJS)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)
	./$(BIN_DIR)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(BIN_DIR)/test
