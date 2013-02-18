#include <stdio.h>

#include "test.h"

#define SCORE_MOVE_TEST(filename, move, expect, name) \
  do { \
  FILE *_fp; \
  Game *_mygp, *_yourgp;					  \
  int _ret, _score;				  \
  _fp = fopen(filename, "r"); \
  if ((_ret = parse(_fp, &_mygp)) != 0) { \
  printf("%s fails\n", name); \
  printf("    cannot parse %s (err %d)\n", filename, _ret); \
  ret = -1; \
  } \
  fclose(_fp); \
  if ((ret = initialize_game(&_yourgp)) != 0) {	\
  printf("%s fails\n", name); \
  printf("    cannot initialize second game\n"); \
  ret = -1; \
  } \
  memcpy(_yourgp, _mygp, sizeof(Game)); \
  if ((_ret = score_move(_mygp, &move, 1, &_score)) != 0) {	\
  printf("%s MY MOVE fails\n", name); \
  printf("    returned %d\n", _ret); \
  ret = -1; \
  } \
  if (_score != expect) { \
  printf("%s fails MY MOVE\n", name); \
  printf("    expected %d got %d\n", expect, _score);	\
  ret = -1;                               \
  } \
  if ((_ret = score_move(_yourgp, &move, 0, &_score)) != 0) {	\
  printf("%s fails YOUR MOVE\n", name); \
  printf("    returned %d\n", _ret); \
  ret = -1; \
  } \
  if (_score != -1 * expect) { \
  printf("%s fails YOUR MOVE\n", name); \
  printf("    expected %d got %d\n", expect, _score);	\
  ret = -1;                               \
  } \
  } while (0)

int
test_score_move()
{
  Move move;
  int ret;

  ret = 0;
  
  move.piece = BLACK | SQUARE | SOLID | TALL;
  move.location = 12;
  SCORE_MOVE_TEST("../tests/test_files/three_pieces.quarto", move, MAX_SCORE, "SCORE_MOVE_TEST THREE PIECES");

  return ret;
}
