#include <stdio.h>

#include "test.h"

#define CHOOSE_PIECE_TEST(filename, expect, name) \
  do { \
  FILE *_fp; \
  Game *_gp; \
  int _ret, _score;                             \
  piece_t _piece; \
  _fp = fopen(filename, "r");             \
  if ((_ret = parse(_fp, &_gp)) != 0) { \
  printf("%s fails\n", name); \
  printf("    cannot parse %s (err %d)\n", filename, _ret); \
  ret = -1; \
  } \
  fclose(_fp); \
  if ((_ret = choose_piece(_gp, &_piece, &_score)) != 0) {	\
  printf("%s fails\n", name); \
  printf("    returned %d\n", _ret); \
  ret = -1; \
  } \
  if (_piece != expect) {     \
    printf("%s fails\n", name);                         \
    printf("    expected %d got %d\n", expect, _piece);	\
    ret = -1;                                           \
  }                                                     \
  } while (0)

int
test_choose_piece()
{
  int ret;

  ret = 0;
  
  CHOOSE_PIECE_TEST("../tests/test_files/cats_game.quarto", (WHITE | ROUND | HOLLOW | SHORT), "CHOOSE_PIECE CATS GAME");
  CHOOSE_PIECE_TEST("../tests/test_files/score_move_one.quarto", (WHITE | ROUND | SOLID | TALL), "CHOOSE_PIECE SCORE MOVE ONE");
  CHOOSE_PIECE_TEST("../tests/test_files/two_moves_left.quarto", (WHITE | ROUND | HOLLOW | SHORT), "CHOOSE_PIECE TWO MOVES LEFT");
  
  return ret;
}
