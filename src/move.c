#include "move.h"

/*
 * Given a piece, place it on the board and choose the opponent's next piece.
 */
int
take_turn(gamep, piece, locationp, next_piecep)
     Game *gamep;
     piece_t piece;
     int *locationp;
     piece_t *next_piecep;
{
  Game *mygame;
  Move move;
  int high_score, i, ret, score;
  piece_t next_piece;
  
  if ((ret = initialize_game(&mygame)) != 0)
    return ret;
  move.piece = piece;
  
  for (i = 0; i < BOARD_SIZE; i++) {
    if (IS_PIECE(gamep->board[i]))
      continue;
    memcpy(mygame, gamep, sizeof(Game));
    move.location = i;
    if ((ret = make_move(mygame, &move)) != 0)
      return ret;
    /* 
     * If we can win the game with this piece, or if the board is now full,
     * we're done.
     */
    if (IS_GAME_OVER(mygame->board)) {
      free(mygame);
      *locationp = i;
      *next_piecep = 0;
      return 0;
    }
  }

  /* 
   * We can't win with this piece.  We need to find the combination of location
   * for this piece plus next piece for our opponent with the highest score.
   */
  high_score = INT32_MIN;
  for (i = 0; i < BOARD_SIZE; i++) {
    if (IS_PIECE(gamep->board[i]))
      continue;
    memcpy(mygame, gamep, sizeof(Game));
    move.location = i;
    if ((ret = make_move(mygame, &move)) != 0)
      return ret;
    choose_piece(mygame, &next_piece, &score);
    if (score > high_score) {
      *locationp = i;
      *next_piecep = next_piece;
      high_score = score;
    }
    /* TODO: Break ties randomly. */
  }
  
  return 0;
}

/*
 * For a given game, choose the best piece to give to our opponent.
 */
int
choose_piece(gamep, piecep, scorep)
     Game *gamep;
     piece_t *piecep;
     int *scorep;
{
		Game *mygame;
  Move *moves;
  int i, indx, new_score, nmoves, ret, score;
  int scores[NPIECES];
  piece_t piece;
  
  if ((ret = initialize_game(&mygame)) != 0)
		  return ret;
  
  /* 
   * For every remaining piece, sum the scores of the possible moves our
   * opponent could make.  The piece with the highest sum is the winner.
   */
  memset(scores, 0, NPIECES * sizeof(piece_t));
  if ((nmoves = possible_moves(gamep, &moves)) < 0)
    return nmoves;
  
  /*
   * for move in possible moves:
   *  score it and update scores[move.piece >> 1] (careful for overflowing)
   * choose highest scoring piece from scores
   */
  for (i = 0; i < nmoves; i++) {
    indx = moves[i].piece >> 1;
	memcpy(mygame, gamep, sizeof(Game));
	if ((ret = score_move(mygame, &(moves[i]), 0, &score)) != 0)
      return ret;

    new_score = scores[indx] + score;
    if (score < 0 && new_score > scores[indx] )
      scores[indx] = INT32_MIN;
    else if (score > 0 && new_score < scores[indx])
      scores[indx] = MAX_SCORE;
    else
      scores[indx] = new_score;
  }

  *scorep = INT32_MIN;
  for (i = 0; i < NPIECES; i++) {
    if (!IS_PIECE(gamep->remaining[i]))
      continue;
    piece = gamep->remaining[i];
    if (scores[piece >> 1] > *scorep) {
      *scorep = scores[piece >> 1];
      *piecep = piece;
    }
    /* TODO: Break ties randomly. */
  }

  return 0;
}

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
