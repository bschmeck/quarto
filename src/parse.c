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
        piece_t *piecep;

		row = (char *)malloc(ROWLEN * sizeof(char));
        if ((ret = initialize_game(&gamep)) != 0)
          return ret;
		piecep = gamep->board;

		for (i = 0; i < NROWS; i++) {
				fgets(row, ROWLEN, fp);
				if (strlen(row) != ROWLEN)
						return -1;
				if (row[ROWLEN-1] != '\n')
						return -1;
				if ((ret = parse_piece(row, piecep)) != 0)
						return ret;
                piecep++;
		}
		
		*gamepp = gamep;
		return 0;
}

#define SET_CATEGORY(code, code1, cat1, code2, cat2, cat) \
		do {                                              \
				if (code == code1) {                      \
				        *piecep |= cat1;                    \
						categories |= cat;                \
				} else if (code == code2) {               \
						*piecep |= cat2;                    \
						categories |= cat;                \
				} else if (code != 'X') {                 \
						return -1;                        \
				}                                         \
		} while(0)

int
parse_piece(piece_str, piecep)
		char *piece_str;
		piece_t *piecep;
{
        piece_t categories;

        *piecep = 0;
        categories = 0;

        SET_CATEGORY(*piece_str, 'B', BLACK, 'W', WHITE, COLOR); 
        piece_str++;
        SET_CATEGORY(*piece_str, 'R', ROUND, 'S', SQUARE, SHAPE);
        piece_str++;
        SET_CATEGORY(*piece_str, 'S', SOLID, 'H', HOLLOW, CENTER);
        piece_str++;
        SET_CATEGORY(*piece_str, 'T', TALL, 'S', SHORT, HEIGHT);
        piece_str++;
        if (categories != (COLOR | SHAPE | CENTER | HEIGHT) && *piecep != 0)
              /* Some, but not all, categories were set. */
			  return -1;
		
		return 0;
}
