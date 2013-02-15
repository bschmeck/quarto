#include "move.h"

int
possible_moves(gamep, movepp)
     Game *gamep;
     Move **movepp;
{
  Move *possible_moves;
  int i, j, nmoves, possible_sz;

  nmoves = 0;
  possible_sz = 50;
  possible_moves = (Move *)calloc(possible_sz, sizeof(Move));
  
  for (i = 0; i < NPIECES; i++) {
    if (!IS_PIECE(gamep->remaining[i]))
      continue;
    for (j = 0; j < BOARD_SIZE; j++) {
      if (IS_PIECE(gamep->board[j]))
        continue;
      if (nmoves == possible_sz) {
        possible_sz *= 2;
        possible_moves = realloc(possible_moves, possible_sz * sizeof(Move));
      }
      possible_moves[nmoves].piece = gamep->remaining[i];
      possible_moves[nmoves].location = j;
      nmoves++;
    }
  }

  if (movepp)
    *movepp = possible_moves;

  return nmoves;
}

int
count_remaining_moves(gamep)
     Game *gamep;
{
  int count, remaining;
  int move_counts[NMOVE_COUNTS] = MOVE_COUNTS;
  
  return move_counts[COUNT_PIECES(gamep->remaining)];
}
