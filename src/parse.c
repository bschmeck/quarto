#include "parse.h"

int
initialize_game(gamepp)
		Game **gamepp;
{
		Game *gamep;
		piece_t pieces[NPIECES] = PIECES;

		gamep = (Game *)malloc(1 * sizeof(Game));
		gamep->board = calloc(BOARD_SIZE, sizeof(piece_t));
		gamep->remaining = malloc(NPIECES * sizeof(piece_t));
		memcpy(gamep->remaining, pieces, NPIECES * sizeof(piece_t));

		*gamepp = gamep;
		return 0;
}
