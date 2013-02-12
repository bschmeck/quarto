topdir = ..
bindir = $(topdir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests

DEPS = $(srcdir)/board.h $(srcdir)/parse.h $(testdir)/test.h
QUARTO_OBJS = parse.o
TEST_OBJS = test.o test_all_match.o test_count_pieces.o test_initialize_game.o test_is_quarto.o test_is_winning_board.o test_parse.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir) -ggdb3
CFLAGS_TEST=$(CFLAGS)

parse.o: $(srcdir)/parse.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test.o: $(testdir)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)
test%.o: $(testdir)/test%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)

test: $(TEST_OBJS) $(QUARTO_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS_TEST)
	./$(bindir)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(bindir)/test
