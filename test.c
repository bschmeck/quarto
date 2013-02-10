#include <stdio.h>

#include "board.h"

static int test_is_quarto(void);
static int test_all_match(void);

#define ALL_MATCH_TEST(category, a, b, c, d, expect, name)		      \
		do {                                                          \
		    int _ret;                                                 \
			if ((_ret = ALL_MATCH(category, a, b, c, d)) != expect) { \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, ret);	      \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

#define IS_QUARTO_TEST(a, b, c, d, expect, name)   	         	      \
		do {                                                          \
		    int _ret;                                                 \
			if ((_ret = IS_QUARTO(a, b, c, d)) != expect) {           \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, ret);	      \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

static int
test_all_match()
{
		int ret;
		int pieces[NPIECES] = PIECES;

		ret = 0;

		/* Test each category */
		ALL_MATCH_TEST(COLOR, BLACK, BLACK, BLACK, BLACK, 1, "ALL_MATCH BLACK");
		ALL_MATCH_TEST(COLOR, WHITE, WHITE, WHITE, WHITE, 1, "ALL_MATCH WHITE");
		ALL_MATCH_TEST(SHAPE, ROUND, ROUND, ROUND, ROUND, 1, "ALL_MATCH ROUND");
		ALL_MATCH_TEST(SHAPE, SQUARE, SQUARE, SQUARE, SQUARE, 1, "ALL_MATCH SQUARE");
		ALL_MATCH_TEST(CENTER, HOLLOW, HOLLOW, HOLLOW, HOLLOW, 1, "ALL_MATCH HOLLOW");
		ALL_MATCH_TEST(CENTER, SOLID, SOLID, SOLID, SOLID, 1, "ALL_MATCH SOLID");
		ALL_MATCH_TEST(HEIGHT, TALL, TALL, TALL, TALL, 1, "ALL_MATCH TALL");
		ALL_MATCH_TEST(HEIGHT, SHORT, SHORT, SHORT, SHORT, 1, "ALL_MATCH SHORT");

		/* Test when one piece is missing */
		ALL_MATCH_TEST(COLOR, BLACK, BLACK, BLACK, 0, 0, "ALL_MATCH BLACK 1 ZERO");
		ALL_MATCH_TEST(COLOR, WHITE, WHITE, WHITE, 0, 0, "ALL_MATCH WHITE 1 ZERO");
		ALL_MATCH_TEST(SHAPE, ROUND, ROUND, ROUND, 0, 0, "ALL_MATCH ROUND 1 ZERO");
		ALL_MATCH_TEST(SHAPE, SQUARE, SQUARE, SQUARE, 0, 0, "ALL_MATCH SQUARE 1 ZERO");
		ALL_MATCH_TEST(CENTER, HOLLOW, HOLLOW, HOLLOW, 0, 0, "ALL_MATCH HOLLOW 1 ZERO");
		ALL_MATCH_TEST(CENTER, SOLID, SOLID, SOLID, 0, 0, "ALL_MATCH SOLID 1 ZERO");
		ALL_MATCH_TEST(HEIGHT, TALL, TALL, TALL, 0, 0, "ALL_MATCH TALL 1 ZERO");
		ALL_MATCH_TEST(HEIGHT, SHORT, SHORT, SHORT, 0, 0, "ALL_MATCH SHORT 1 ZERO");

		/* Test when two pieces are missing */
		ALL_MATCH_TEST(COLOR, BLACK, BLACK, 0, 0, 0, "ALL_MATCH BLACK 2 ZEROs");
		ALL_MATCH_TEST(COLOR, WHITE, WHITE, 0, 0, 0, "ALL_MATCH WHITE 2 ZEROs");
		ALL_MATCH_TEST(SHAPE, ROUND, ROUND, 0, 0, 0, "ALL_MATCH ROUND 2 ZEROs");
		ALL_MATCH_TEST(SHAPE, SQUARE, SQUARE, 0, 0, 0, "ALL_MATCH SQUARE 2 ZEROs");
		ALL_MATCH_TEST(CENTER, HOLLOW, HOLLOW, 0, 0, 0, "ALL_MATCH HOLLOW 2 ZEROs");
		ALL_MATCH_TEST(CENTER, SOLID, SOLID, 0, 0, 0, "ALL_MATCH SOLID 2 ZEROs");
		ALL_MATCH_TEST(HEIGHT, TALL, TALL, 0, 0, 0, "ALL_MATCH TALL 2 ZEROs");
		ALL_MATCH_TEST(HEIGHT, SHORT, SHORT, 0, 0, 0, "ALL_MATCH SHORT 2 ZEROs");

		/* Test when three pieces are missing */
		ALL_MATCH_TEST(COLOR, BLACK, 0, 0, 0, 0, "ALL_MATCH BLACK 3 ZEROs");
		ALL_MATCH_TEST(COLOR, WHITE, 0, 0, 0, 0, "ALL_MATCH WHITE 3 ZEROs");
		ALL_MATCH_TEST(SHAPE, ROUND, 0, 0, 0, 0, "ALL_MATCH ROUND 3 ZEROs");
		ALL_MATCH_TEST(SHAPE, SQUARE, 0, 0, 0, 0, "ALL_MATCH SQUARE 3 ZEROs");
		ALL_MATCH_TEST(CENTER, HOLLOW, 0, 0, 0, 0, "ALL_MATCH HOLLOW 3 ZEROs");
		ALL_MATCH_TEST(CENTER, SOLID, 0, 0, 0, 0, "ALL_MATCH SOLID 3 ZEROs");
		ALL_MATCH_TEST(HEIGHT, TALL, 0, 0, 0, 0, "ALL_MATCH TALL 3 ZEROs");
		ALL_MATCH_TEST(HEIGHT, SHORT, 0, 0, 0, 0, "ALL_MATCH SHORT 3 ZEROs");

		/* Test when all pieces are missing */
		ALL_MATCH_TEST(COLOR, 0, 0, 0, 0, 0, "ALL_MATCH SHAPE ALL ZEROs");
		ALL_MATCH_TEST(SHAPE, 0, 0, 0, 0, 0, "ALL_MATCH SHAPE ALL ZEROs");
		ALL_MATCH_TEST(CENTER, 0, 0, 0, 0, 0, "ALL_MATCH CENTER ALL ZEROs");
		ALL_MATCH_TEST(HEIGHT, 0, 0, 0, 0, 0, "ALL_MATCH HEIGHT ALL ZEROs");

		/* Test different pieces with the same characteristic */
		/* The first 8 pieces in PIECES are black. */
		ALL_MATCH_TEST(COLOR, pieces[0], pieces[1], pieces[2], pieces[3], 1, "ALL_MATCH BLACK");
		/* The first 4 pieces in PIECES are round. */
		ALL_MATCH_TEST(SHAPE, pieces[0], pieces[1], pieces[2], pieces[3], 1, "ALL_MATCH ROUND");
		/* The first and third groups of 2 pieces in PIECES are solid. */
		ALL_MATCH_TEST(CENTER, pieces[0], pieces[1], pieces[4], pieces[5], 1, "ALL_MATCH SOLID");
		/* The even pieces in PIECES are tall. */
		ALL_MATCH_TEST(HEIGHT, pieces[0], pieces[2], pieces[4], pieces[6], 1, "ALL_MATCH TALL");

		/* Test different pieces with different characteristics */
		/* The first 8 pieces in PIECES are black. */
		ALL_MATCH_TEST(COLOR, pieces[0], pieces[1], pieces[8], pieces[9], 0, "ALL_MATCH BLACK AND WHITE");
		/* The first 4 pieces in PIECES are round. */
		ALL_MATCH_TEST(SHAPE, pieces[0], pieces[1], pieces[4], pieces[5], 0, "ALL_MATCH ROUND AND SQUARE");
		/* The first and third groups of 2 pieces in PIECES are solid. */
		ALL_MATCH_TEST(CENTER, pieces[0], pieces[1], pieces[2], pieces[3], 0, "ALL_MATCH SOLID AND HOLLOW");
		/* The even pieces in PIECES are tall. */
		ALL_MATCH_TEST(HEIGHT, pieces[0], pieces[1], pieces[2], pieces[3], 0, "ALL_MATCH TALL AND SHORT");

		return ret;
}

static int
test_is_quarto()
{
		int ret;
		int pieces[NPIECES] = PIECES;

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

int 
main(argc, argv)
		char *argv;
		int argc; 
{
		int ret;

		ret = test_all_match();
		printf("ALL_MATCH %s\n", ret == 0 ? "passes" : "fails");
		ret = test_is_quarto();
		printf("IS_QUARTO %s\n", ret == 0 ? "passes" : "fails");
}
