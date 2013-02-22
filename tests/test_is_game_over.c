#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

#define IS_GAME_OVER_TEST(boardp, expect, name)		       \
		do {                                                   \
		    int _ret;                                          \
			if ((_ret = IS_GAME_OVER(boardp)) != expect) { \
				printf("%s fails\n", name);					   \
				printf("  expected %d got %d\n", expect, _ret); \
				ret = -1;                                      \
		    }                                                  \
        } while(0)

int
test_is_game_over()
{
		int ret;
		piece_t *boardp;
		piece_t pieces[NPIECES] = PIECES;

		boardp = calloc(BOARD_SIZE, sizeof(piece_t));
		ret = 0;

		/* Test an empty board */
		IS_GAME_OVER_TEST(boardp, 0, "IS_GAME_OVER EMPTY");

		/* Test a board with four matching pieces, but not lined up. */
		boardp[0] = pieces[0];
		boardp[1] = pieces[1];
		boardp[4] = pieces[2];
		boardp[5] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 0, "IS_GAME_OVER NO MATCH");

		/* Test matches in each row. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[1] = pieces[1];
		boardp[2] = pieces[2];
		boardp[3] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER ROW 1");
		memset(boardp, 0, BOARD_SIZE);
		boardp[4] = pieces[0];
		boardp[5] = pieces[1];
		boardp[6] = pieces[2];
		boardp[7] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER ROW 2");
		memset(boardp, 0, BOARD_SIZE);
		boardp[8] = pieces[0];
		boardp[9] = pieces[1];
		boardp[10] = pieces[2];
		boardp[11] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER ROW 3");
		memset(boardp, 0, BOARD_SIZE);
		boardp[12] = pieces[0];
		boardp[13] = pieces[1];
		boardp[14] = pieces[2];
		boardp[15] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER ROW 4");

		/* Test matches in each column. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[4] = pieces[1];
		boardp[8] = pieces[2];
		boardp[12] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 1");
		memset(boardp, 0, BOARD_SIZE);
		boardp[1] = pieces[0];
		boardp[5] = pieces[1];
		boardp[9] = pieces[2];
		boardp[13] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 2");
		memset(boardp, 0, BOARD_SIZE);
		boardp[2] = pieces[0];
		boardp[6] = pieces[1];
		boardp[10] = pieces[2];
		boardp[14] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 3");
		memset(boardp, 0, BOARD_SIZE);
		boardp[3] = pieces[0];
		boardp[7] = pieces[1];
		boardp[11] = pieces[2];
		boardp[15] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 4");

		/* Test matches in each diagonal. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[5] = pieces[1];
		boardp[10] = pieces[2];
		boardp[15] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER DIAG L TO R");
		memset(boardp, 0, BOARD_SIZE);
		boardp[3] = pieces[0];
		boardp[6] = pieces[1];
		boardp[9] = pieces[2];
		boardp[12] = pieces[3];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER DIAG R TO L");

		/* Test multiple matches in a board. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[4] = pieces[1];
		boardp[8] = pieces[2];
		boardp[12] = pieces[3];
		boardp[5] = pieces[8];
		boardp[10] = pieces[9];
		boardp[15] = pieces[10];
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 1 AND DIAG L TO R");

		/* Test a cat's game board. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = (BLACK | ROUND | SOLID | TALL);
		boardp[1] = (WHITE | SQUARE | SOLID | TALL);
		boardp[2] = (BLACK | SQUARE | SOLID | TALL);
		boardp[3] = (BLACK | ROUND | HOLLOW | SHORT);
		boardp[4] = (BLACK | ROUND | SOLID | SHORT);
		boardp[5] = (WHITE | SQUARE | SOLID | SHORT);
		boardp[6] = (BLACK | SQUARE | SOLID | SHORT);
		boardp[7] = (WHITE | ROUND | HOLLOW | TALL);
		boardp[8] = (WHITE | ROUND | SOLID | SHORT);
		boardp[9] = (BLACK | ROUND | HOLLOW | TALL);
		boardp[10] = (WHITE | SQUARE | HOLLOW | SHORT);
		boardp[11] = (BLACK | SQUARE | HOLLOW | SHORT);
		boardp[12] = (WHITE | SQUARE | HOLLOW | TALL);
		boardp[13] = (BLACK | SQUARE | HOLLOW | TALL);
		boardp[14] = (WHITE | ROUND | HOLLOW | SHORT);
		boardp[15] = (WHITE | ROUND | SOLID | TALL);
		IS_GAME_OVER_TEST(boardp, 1, "IS_GAME_OVER COL 1 AND DIAG L TO R");

		return ret;		
}
