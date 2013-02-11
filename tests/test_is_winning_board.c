#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

#define IS_WINNING_BOARD_TEST(boardp, expect, name)		       \
		do {                                                   \
		    int _ret;                                          \
			if ((_ret = IS_WINNING_BOARD(boardp)) != expect) { \
				printf("%s fails\n", name);					   \
				printf("  expected %d got %d\n", expect, ret); \
				ret = -1;                                      \
		    }                                                  \
        } while(0)

int
test_is_winning_board()
{
		int ret;
		piece_t *boardp;
		piece_t pieces[NPIECES] = PIECES;

		boardp = calloc(BOARD_SIZE, sizeof(piece_t));
		ret = 0;

		/* Test an empty board */
		IS_WINNING_BOARD_TEST(boardp, 0, "IS_WINNING_BOARD EMPTY");

		/* Test a board with four matching pieces, but not lined up. */
		boardp[0] = pieces[0];
		boardp[1] = pieces[1];
		boardp[4] = pieces[2];
		boardp[5] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 0, "IS_WINNING_BOARD NO MATCH");

		/* Test matches in each row. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[1] = pieces[1];
		boardp[2] = pieces[2];
		boardp[3] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD ROW 1");
		memset(boardp, 0, BOARD_SIZE);
		boardp[4] = pieces[0];
		boardp[5] = pieces[1];
		boardp[6] = pieces[2];
		boardp[7] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD ROW 2");
		memset(boardp, 0, BOARD_SIZE);
		boardp[8] = pieces[0];
		boardp[9] = pieces[1];
		boardp[10] = pieces[2];
		boardp[11] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD ROW 3");
		memset(boardp, 0, BOARD_SIZE);
		boardp[12] = pieces[0];
		boardp[13] = pieces[1];
		boardp[14] = pieces[2];
		boardp[15] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD ROW 4");

		/* Test matches in each column. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[4] = pieces[1];
		boardp[8] = pieces[2];
		boardp[12] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD COL 1");
		memset(boardp, 0, BOARD_SIZE);
		boardp[1] = pieces[0];
		boardp[5] = pieces[1];
		boardp[9] = pieces[2];
		boardp[13] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD COL 2");
		memset(boardp, 0, BOARD_SIZE);
		boardp[2] = pieces[0];
		boardp[6] = pieces[1];
		boardp[10] = pieces[2];
		boardp[14] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD COL 3");
		memset(boardp, 0, BOARD_SIZE);
		boardp[3] = pieces[0];
		boardp[7] = pieces[1];
		boardp[11] = pieces[2];
		boardp[15] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD COL 4");

		/* Test matches in each diagonal. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[5] = pieces[1];
		boardp[10] = pieces[2];
		boardp[15] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD DIAG L TO R");
		memset(boardp, 0, BOARD_SIZE);
		boardp[3] = pieces[0];
		boardp[6] = pieces[1];
		boardp[9] = pieces[2];
		boardp[12] = pieces[3];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD DIAG R TO L");

		/* Test multiple matches in a board. */
		memset(boardp, 0, BOARD_SIZE);
		boardp[0] = pieces[0];
		boardp[4] = pieces[1];
		boardp[8] = pieces[2];
		boardp[12] = pieces[3];
		boardp[5] = pieces[8];
		boardp[10] = pieces[9];
		boardp[15] = pieces[10];
		IS_WINNING_BOARD_TEST(boardp, 1, "IS_WINNING_BOARD COL 1 AND DIAG L TO R");

		return ret;		
}
