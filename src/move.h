#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "parse.h"

typedef struct {
  piece_t piece;
  int location;
} Move;

int count_remaining_moves(Game *);  
int make_move(Game *, Move *);
int possible_moves(Game *, Move **);
int score_move(Game *, Move *, int, int *);

/* MOVE_COUNTS is the number of moves left in the game when there are a certain number of pieces remaining.  Exact calculation is (n!)^2, but it tops out at INT32_MAX when n > 7. */
#define MAX_SCORE INT32_MAX
#define NMOVE_COUNTS 17
#define MOVE_COUNTS { \
 0, \
 1, \
 4, \
 36, \
 576, \
 14400, \
   518400, \
 25401600, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE, \
 MAX_SCORE }

#endif
