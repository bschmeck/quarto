#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include <stdlib.h>

#include "board.h"

typedef struct {
  piece_t piece;
  int location;
} Move;

int count_remaining_moves(Game *);  
int possible_moves(Game *, Move **);

/* MOVE_COUNTS is the number of moves left in the game when there are a certain number of pieces remaining.  Exact calculation is (n!)^2, but it tops out at INT32_MAX when n > 7. */
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
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX, \
 INT32_MAX }

#endif
