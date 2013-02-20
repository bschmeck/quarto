#include <stdio.h>

#include "test.h"

#define TAKE_TURN_TEST(filename, piece, expect_loc, expect_piece, name)  \
  do { \
  FILE *_fp; \
  Game *_gp; \
  int _ret, _loc;                             \
  piece_t _piece; \
  _fp = fopen(filename, "r");             \
  if ((_ret = parse(_fp, &_gp)) != 0) { \
  printf("%s fails\n", name); \
  printf("    cannot parse %s (err %d)\n", filename, _ret); \
  ret = -1; \
  } \
  fclose(_fp); \
  if ((_ret = take_turn(_gp, piece, &_loc, &_piece)) != 0) {	\
  printf("%s fails\n", name); \
  printf("    returned %d\n", _ret); \
  ret = -1; \
  } \
  if (_loc != expect_loc) {     \
    printf("%s fails\n", name);                         \
    printf("    expected location %d got %d\n", expect_loc, _loc);	\
    ret = -1;                                           \
  }                                                     \
  if (_piece != expect_piece) {     \
    printf("%s fails\n", name);                         \
    printf("    expected piece %d got %d\n", expect_piece, _piece);	\
    ret = -1;                                           \
  }                                                     \
  } while (0)

int
test_take_turn()
{
  int ret;

  ret = 0;
  
  TAKE_TURN_TEST("../tests/test_files/cats_game.quarto", (WHITE | ROUND | HOLLOW | SHORT), 14, 0, "TAKE_TURN CATS GAME");
  TAKE_TURN_TEST("../tests/test_files/two_moves_left.quarto", (BLACK | SQUARE | HOLLOW | SHORT), 14, 0, "TAKE_TURN TWO MOVES LEFT WIN");
  TAKE_TURN_TEST("../tests/test_files/two_moves_left.quarto", (WHITE | ROUND | HOLLOW | SHORT), 14, (BLACK | SQUARE | HOLLOW | SHORT), "TAKE_TURN TWO MOVES LEFT DRAW");
  
  return ret;
}
