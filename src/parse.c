#include "parse.h"

int
initialize_game(gamepp)
		Game **gamepp;
{
		Game *gamep;
		piece_t pieces[NPIECES] = PIECES;

		gamep = (Game *)calloc(1, sizeof(Game));
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
		int i, j, ret;
        piece_t *piecep, *remainp;

#define BUFSZ 80
		row = (char *)malloc(BUFSZ * sizeof(char));
        if ((ret = initialize_game(&gamep)) != 0)
          return ret;
		piecep = gamep->board;

		for (i = 0; i < NROWS; i++) {
				if (fgets(row, BUFSZ, fp) == NULL)
                        return -1;
				if (strlen(row) != ROWLEN)
						return -2;
				if (row[ROWLEN-1] != '\n')
						return -3;
                for (j = 0; j < NCOLS; j++) {
                  if ((ret = parse_piece(row, piecep)) != 0)
						return ret;
				  /* 
				   * Remove the piece we just parsed (if we got a piece) from
				   * the game's list of remaining pieces.  It's an error if we
				   * can't find it (meaning the file contains duplicate pieces.)
				   */
				  if (IS_PIECE(*piecep)) {
						  remainp = gamep->remaining + 16;
						  while (remainp-- > gamep->remaining) {
								  if (*remainp == *piecep) {
										  *remainp = 0;
										  break;
								  }
						  }
						  if (*remainp != 0)
								  return -4;
				  }
                  piecep++;
                  row += NCHARS;
                }
		}
		
		*gamepp = gamep;
		return 0;
}

#define SET_ATTRIBUTE(code, code1, attr1, code2, attr2, attr) \
		do {                                              \
				if (code == code1) {                      \
				        *piecep |= attr1;                    \
						attributes |= attr;                \
				} else if (code == code2) {               \
						*piecep |= attr2;                    \
						attributes |= attr;                \
				} else if (code != 'X') {                 \
						return -5;                        \
				}                                         \
		} while(0)

int
parse_piece(piece_str, piecep)
		char *piece_str;
		piece_t *piecep;
{
        piece_t attributes;

        *piecep = 0;
        attributes = 0;

        SET_ATTRIBUTE(*piece_str, 'B', BLACK, 'W', WHITE, COLOR); 
        piece_str++;
        SET_ATTRIBUTE(*piece_str, 'R', ROUND, 'S', SQUARE, SHAPE);
        piece_str++;
        SET_ATTRIBUTE(*piece_str, 'S', SOLID, 'H', HOLLOW, CENTER);
        piece_str++;
        SET_ATTRIBUTE(*piece_str, 'T', TALL, 'S', SHORT, HEIGHT);
        piece_str++;
        if (attributes != (COLOR | SHAPE | CENTER | HEIGHT) && *piecep != 0)
              /* Some, but not all, attributes were set. */
			  return -6;
		
		return 0;
}
