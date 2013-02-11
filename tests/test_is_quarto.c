#include <stdio.h>

#include "test.h"

#define IS_QUARTO_TEST(a, b, c, d, expect, name)   	         	      \
		do {                                                          \
		    int _ret;                                                 \
			if ((_ret = IS_QUARTO(a, b, c, d)) != expect) {           \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, ret);	      \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

int
test_is_quarto()
{
		int ret;
		piece_t pieces[NPIECES] = PIECES;

		ret = 0;

		/* Test each category */
		IS_QUARTO_TEST(BLACK, BLACK, BLACK, BLACK, 1, "IS_QUARTO BLACK");
		IS_QUARTO_TEST(WHITE, WHITE, WHITE, WHITE, 1, "IS_QUARTO WHITE");
		IS_QUARTO_TEST(ROUND, ROUND, ROUND, ROUND, 1, "IS_QUARTO ROUND");
		IS_QUARTO_TEST(SQUARE, SQUARE, SQUARE, SQUARE, 1, "IS_QUARTO SQUARE");
		IS_QUARTO_TEST(HOLLOW, HOLLOW, HOLLOW, HOLLOW, 1, "IS_QUARTO HOLLOW");
		IS_QUARTO_TEST(SOLID, SOLID, SOLID, SOLID, 1, "IS_QUARTO SOLID");
		IS_QUARTO_TEST(TALL, TALL, TALL, TALL, 1, "IS_QUARTO TALL");
		IS_QUARTO_TEST(SHORT, SHORT, SHORT, SHORT, 1, "IS_QUARTO SHORT");

		/* Test when one piece is missing */
		IS_QUARTO_TEST(BLACK, BLACK, BLACK, 0, 0, "IS_QUARTO BLACK 1 ZERO");
		IS_QUARTO_TEST(WHITE, WHITE, WHITE, 0, 0, "IS_QUARTO WHITE 1 ZERO");
		IS_QUARTO_TEST(ROUND, ROUND, ROUND, 0, 0, "IS_QUARTO ROUND 1 ZERO");
		IS_QUARTO_TEST(SQUARE, SQUARE, SQUARE, 0, 0, "IS_QUARTO SQUARE 1 ZERO");
		IS_QUARTO_TEST(HOLLOW, HOLLOW, HOLLOW, 0, 0, "IS_QUARTO HOLLOW 1 ZERO");
		IS_QUARTO_TEST(SOLID, SOLID, SOLID, 0, 0, "IS_QUARTO SOLID 1 ZERO");
		IS_QUARTO_TEST(TALL, TALL, TALL, 0, 0, "IS_QUARTO TALL 1 ZERO");
		IS_QUARTO_TEST(SHORT, SHORT, SHORT, 0, 0, "IS_QUARTO SHORT 1 ZERO");

		/* Test when two pieces are missing */
		IS_QUARTO_TEST(BLACK, BLACK, 0, 0, 0, "IS_QUARTO BLACK 2 ZEROs");
		IS_QUARTO_TEST(WHITE, WHITE, 0, 0, 0, "IS_QUARTO WHITE 2 ZEROs");
		IS_QUARTO_TEST(ROUND, ROUND, 0, 0, 0, "IS_QUARTO ROUND 2 ZEROs");
		IS_QUARTO_TEST(SQUARE, SQUARE, 0, 0, 0, "IS_QUARTO SQUARE 2 ZEROs");
		IS_QUARTO_TEST(HOLLOW, HOLLOW, 0, 0, 0, "IS_QUARTO HOLLOW 2 ZEROs");
		IS_QUARTO_TEST(SOLID, SOLID, 0, 0, 0, "IS_QUARTO SOLID 2 ZEROs");
		IS_QUARTO_TEST(TALL, TALL, 0, 0, 0, "IS_QUARTO TALL 2 ZEROs");
		IS_QUARTO_TEST(SHORT, SHORT, 0, 0, 0, "IS_QUARTO SHORT 2 ZEROs");

		/* Test when three pieces are missing */
		IS_QUARTO_TEST(BLACK, 0, 0, 0, 0, "IS_QUARTO BLACK 3 ZEROs");
		IS_QUARTO_TEST(WHITE, 0, 0, 0, 0, "IS_QUARTO WHITE 3 ZEROs");
		IS_QUARTO_TEST(ROUND, 0, 0, 0, 0, "IS_QUARTO ROUND 3 ZEROs");
		IS_QUARTO_TEST(SQUARE, 0, 0, 0, 0, "IS_QUARTO SQUARE 3 ZEROs");
		IS_QUARTO_TEST(HOLLOW, 0, 0, 0, 0, "IS_QUARTO HOLLOW 3 ZEROs");
		IS_QUARTO_TEST(SOLID, 0, 0, 0, 0, "IS_QUARTO SOLID 3 ZEROs");
		IS_QUARTO_TEST(TALL, 0, 0, 0, 0, "IS_QUARTO TALL 3 ZEROs");
		IS_QUARTO_TEST(SHORT, 0, 0, 0, 0, "IS_QUARTO SHORT 3 ZEROs");

		/* Test when all pieces are missing */
		IS_QUARTO_TEST(0, 0, 0, 0, 0, "IS_QUARTO SHAPE ALL ZEROs");
		IS_QUARTO_TEST(0, 0, 0, 0, 0, "IS_QUARTO SHAPE ALL ZEROs");
		IS_QUARTO_TEST(0, 0, 0, 0, 0, "IS_QUARTO CENTER ALL ZEROs");
		IS_QUARTO_TEST(0, 0, 0, 0, 0, "IS_QUARTO HEIGHT ALL ZEROs");

		/* Test different pieces with the same characteristic */
		/* The first 8 pieces in PIECES are black. */
		IS_QUARTO_TEST(pieces[0], pieces[1], pieces[2], pieces[3], 1, "IS_QUARTO BLACK");
		IS_QUARTO_TEST(pieces[8], pieces[9], pieces[10], pieces[11], 1, "IS_QUARTO WHITE");
		/* The first 4 pieces in PIECES are round. */
		IS_QUARTO_TEST(pieces[0], pieces[1], pieces[2], pieces[3], 1, "IS_QUARTO ROUND");
		IS_QUARTO_TEST(pieces[4], pieces[5], pieces[6], pieces[7], 1, "IS_QUARTO SQUARE");
		/* The first and third groups of 2 pieces in PIECES are solid. */
		IS_QUARTO_TEST(pieces[0], pieces[1], pieces[4], pieces[5], 1, "IS_QUARTO SOLID");
		IS_QUARTO_TEST(pieces[2], pieces[3], pieces[6], pieces[7], 1, "IS_QUARTO HOLLOW");
		/* The even pieces in PIECES are tall. */
		IS_QUARTO_TEST(pieces[0], pieces[2], pieces[4], pieces[6], 1, "IS_QUARTO TALL");
		IS_QUARTO_TEST(pieces[1], pieces[3], pieces[5], pieces[7], 1, "IS_QUARTO SHORT");

		/* Test different pieces with different characteristics */
		IS_QUARTO_TEST(pieces[0], pieces[1], pieces[14], pieces[15], 0, "IS_QUARTO MISMATCHED");

		return ret;
}
