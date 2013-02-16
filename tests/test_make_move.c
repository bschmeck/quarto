#include <stdio.h>

#include "test.h"

#define MAKE_MOVE_TEST(filename, move, expect, name) \
  do { \
  FILE *_fp; \
  Game *_gp; \
  int _ret; \
  _fp = fopen(filename, "r"); \
  if ((_ret = parse(_fp, &_gp)) != 0) { \
  printf("%s fails\n", name); \
  printf("    cannot parse %s (err %d)\n", filename, _ret); \
  ret = -1; \
  } \
  fclose(_fp); \
  if ((_ret = make_move(_gp, &move)) != expect) { \
  printf("%s fails\n", name); \
  printf("    expected %d got %d\n", expect, _ret); \
  ret = -1; \
  } \
  if ((_ret = make_move(_gp, &move)) == 0) { \
  printf("%s fails\n", name); \
  printf("    moving twice succeeded\n"); \
  ret = -1;                               \
  } \
  } while (0)

int
test_make_move()
{
  Move move;
  int ret;

  ret = 0;
  
  move.piece = BLACK | ROUND | SOLID | TALL;
  move.location = 4;
  MAKE_MOVE_TEST("../tests/test_files/valid.quarto", move, -1, "MAKE_MOVE_TEST FULL BOARD");
  MAKE_MOVE_TEST("../tests/test_files/no_pieces.quarto", move, 0, "MAKE_MOVE_TEST EMPTY BOARD");
  MAKE_MOVE_TEST("../tests/test_files/in_progress.quarto", move, -1, "MAKE_MOVE_TEST IN PROGRESS TAKEN LOCATION");
  move.location = 2;
  MAKE_MOVE_TEST("../tests/test_files/in_progress.quarto", move, -2, "MAKE_MOVE_TEST IN PROGRESS TAKEN PIECE");
  move.piece = BLACK | ROUND | HOLLOW | TALL;
  MAKE_MOVE_TEST("../tests/test_files/in_progress.quarto", move, 0, "MAKE_MOVE_TEST IN PROGRESS");

  return ret;
}
