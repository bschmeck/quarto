CC=gcc
CFLAGS=-I.
DEPS = board.h
TEST_OBJS = test.o
BIN_DIR = bin

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_OBJS)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)
	./$(BIN_DIR)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(BIN_DIR)/test
