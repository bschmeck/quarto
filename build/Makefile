topdir = ..
bindir = $(topdir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests
benchdir = $(topdir)/bench
utildir = $(topdir)/utils

DEPS = $(srcdir)/board.h $(srcdir)/move.h $(srcdir)/parse.h $(srcdir)/quarto.h $(srcdir)/utils.h $(testdir)/test.h
QUARTO_OBJS = utils.o move.o parse.o
BENCH_OBJS = benchmark.o
TEST_OBJS = test.o test_all_match.o test_choose_piece.o test_count_pieces.o test_count_remaining_moves.o test_initialize_game.o test_is_game_over.o test_is_quarto.o test_is_winning_board.o test_make_move.o test_parse.o test_parse_piece.o test_possible_moves.o test_piece_attributes.o test_piece_string.o test_score_move.o test_take_turn.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir) -ggdb3 -Wall
CFLAGS_BENCH=$(CFLAGS)
CFLAGS_TEST=$(CFLAGS)

# Quarto Objects
move.o: $(srcdir)/move.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
parse.o: $(srcdir)/parse.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
utils.o: $(srcdir)/utils.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Quarto Utils
explain.o: $(utildir)/explain.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
explain: explain.o $(QUARTO_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS)
repl.o: $(utildir)/repl.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
repl: repl.o $(QUARTO_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS)

# Benchmarking Objects and Executables
benchmark.o: $(benchdir)/benchmark.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_BENCH)

benchmark: $(BENCH_OBJS) $(QUARTO_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS_TEST)

clean_bench:
	rm -rf $(BENCH_OBJS) $(bindir)/benchmark

# Test Objects and Executables
test.o: $(testdir)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)
test%.o: $(testdir)/test%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS_TEST)

test: $(TEST_OBJS) $(QUARTO_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS_TEST)
	./$(bindir)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(bindir)/test
