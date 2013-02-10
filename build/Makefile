topdir = ..
bindir = $(bindir)/bin
builddir = .
srcdir = $(topdir)/src
testdir = $(topdir)/tests

DEPS = $(srcdir)/board.h
TEST_OBJS = test.o

CC=gcc
CFLAGS=-I$(srcdir) -I$(builddir)

test.o: $(testdir)/test.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(TEST_OBJS)
	$(CC) -o $(bindir)/$@ $^ $(CFLAGS)
	./$(bindir)/$@

clean_test:
	rm -rf $(TEST_OBJS) $(bindir)/test
