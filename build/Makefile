topdir = ..
bindir = $(topdir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests

DEPS = $(srcdir)/board.h $(testdir)/test.h
TEST_OBJS = test.o test_all_match.o test_is_quarto.o test_is_winning_board.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir)

test.o: $(testdir)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
test%.o: $(testdir)/test%.c $(DEPS)#
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS)
	./$(bindir)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(bindir)/test
