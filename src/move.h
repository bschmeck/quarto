#ifndef MOVE_H
#define MOVE_H

#include <stdlib.h>

#include "board.h"

typedef struct {
  piece_t piece;
  int location;
} Move;
  
int possible_moves(Game *, Move **);

#endif
