topdir = ..
bindir = $(topdir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests

DEPS = $(srcdir)/board.h $(srcdir)/move.h $(srcdir)/parse.h $(testdir)/test.h
QUARTO_OBJS = move.o parse.o
TEST_OBJS = test.o test_all_match.o test_choose_piece.o test_count_pieces.o test_count_remaining_moves.o test_initialize_game.o test_is_quarto.o test_is_winning_board.o test_make_move.o test_parse.o test_parse_piece.o test_possible_moves.o test_score_move.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir) -ggdb3 -Wall
CFLAGS_TEST=$(CFLAGS)

move.o: $(srcdir)/move.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
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
