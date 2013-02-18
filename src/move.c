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
  int move_counts[NMOVE_COUNTS] = MOVE_COUNTS;
  
  return move_counts[COUNT_PIECES(gamep->remaining)];
}

int
make_move(gamep, movep)
     Game *gamep;
     Move *movep;
{
  int i, ret;

  ret = 0;

  if (IS_PIECE(gamep->board[movep->location]))
    return -1;
  for (i = 0; i < NPIECES; i++)
    if (gamep->remaining[i] == movep->piece)
      break;
  if (i == NPIECES)
    return -2;

  gamep->board[movep->location] = movep->piece;
  gamep->remaining[i] = 0;
  
  return ret;
}

int
score_move(gamep, movep, mymove, scorep)
     Game *gamep;
     Move *movep;
     int mymove;
     int *scorep;
{
  Game *mygame;
  Move *possible;
  int i, new_score, nmoves, ret, scale, score, t_score;

  if ((ret = initialize_game(&mygame)) != 0)
    return ret;

  scale = mymove ? 1 : -1;
  
  if ((ret = make_move(gamep, movep)) != 0)
	  return ret;
  
  if (IS_WINNING_BOARD(gamep->board)) {
    score = scale * (1 + count_remaining_moves(gamep));
  } else {
    score = 0;
    nmoves = possible_moves(gamep, &possible);
    for (i = 0; i < nmoves; i++) {
      memcpy(mygame, gamep, sizeof(Game));
  
			/* Toggle mymove when scoring the next round of moves. */
			if ((ret = score_move(mygame, &possible[i], (mymove & 1) ^ 1, &t_score)) != 0)
					return ret;
			new_score = score + t_score;

			/*
			 * We're possibly dealing with large numbers.  Detect
			 * integer overflows and just cap score at INT32_{MAX|MIN}
			 */
			if (t_score < 0 && new_score > score)
					score = INT32_MIN;
			else if (t_score > 0 && new_score < score)
					score = MAX_SCORE;
			else
					score = new_score;
    }
    free(possible);
  }

  *scorep = score;

  return 0;
}
