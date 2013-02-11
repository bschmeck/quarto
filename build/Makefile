topdir = ..
bindir = $(topdir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests

DEPS = $(srcdir)/board.h $(testdir)/test.h
TEST_OBJS = test.o test_all_match.o test_count_pieces.o test_is_quarto.o test_is_winning_board.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir)
CFLAGS_TEST=$(CFLAGS) -ggdb3

test.o: $(testdir)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)
test%.o: $(testdir)/test%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)

test: $(TEST_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS_TEST)
	./$(bindir)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(bindir)/test
