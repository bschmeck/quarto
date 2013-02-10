CC=gcc
CFLAGS=-I.
DEPS = board.h
TEST_OBJS = test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	./$@

clean_test:
	rm -rf $(TEST_OBJS) test
