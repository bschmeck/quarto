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

/* 
 * Given an open file stream, parse a game representation
 * and create the corresponding game structure.
 */
int
parse(fp, gamepp)
		FILE *fp;
		Game **gamepp;
{
		Game *gamep;
		char *row;
		int i, ret;

		row = (char *)malloc(ROWLEN * sizeof(char));
		
		for (i = 0; i < NROWS; i++) {
				fgets(row, ROWLEN, fp);
				if (strlen(row) != ROWLEN)
						return -1;
				if (row[ROWLEN-1] != '\n')
						return -1;
				if ((ret = parse_row(row, gamep)) != 0)
						return ret;
		}
		
		*gamepp = gamep;
		return 0;
}

#define SET_CATEGORY(code, code1, cat1, code2, cat2, cat) \
		do {                                              \
				if (code == code1) {                      \
				        piece |= cat1;                    \
						categories |= cat;                \
				} else if (code == code2) {               \
						piece |= cat2;                    \
						categories |= cat;                \
				} else if (*row != 'X') {                 \
						return -1;                        \
				}                                         \
		} while(0)
int
parse_row(row, gamep)
		char *row;
		Game *gamep;
{
		int i, j;
		piece_t piece, categories;

		for (i = 0; i < NROWS; i++) {
				piece = 0;
				categories = 0;

				SET_CATEGORY(*row, 'B', BLACK, 'W', WHITE, COLOR); 
				row++;
				SET_CATEGORY(*row, 'R', ROUND, 'S', SQUARE, SHAPE);
				row++;
				SET_CATEGORY(*row, 'S', SOLID, 'H', HOLLOW, CENTER);
				row++;
				SET_CATEGORY(*row, 'T', TALL, 'S', SHORT, HEIGHT);
				row++;
				if (categories != 32 && piece != 0)
						/* Some, but not all, categories were set. */
						return -1;
		}

		return 0;
}
