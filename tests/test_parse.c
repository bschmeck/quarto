#include <stdio.h>

#include "test.h"

#define PARSE_TEST(filename, expect, name)   						  \
		do {                                                          \
     		FILE *_fp;                                                \
            Game *_gp;                                                \
		    int _ret;                                                 \
            _fp = fopen(filename, "r");                               \
			if ((_ret = parse(_fp, &_gp)) != expect) {				  \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, _ret);	      \
				ret = -1;                                             \
		    }                                                         \
            fclose(_fp);                                              \
        } while(0)

#define PARSE_VERIFY_TEST(index, board, expected, name)              \
  do {                                                               \
  if (board[index] != expected[index]) {                             \
  printf("%s %d fails\n", name, index);                              \
  printf("    expected %d got %d\n", expected[index], board[index]); \
  ret = -1;                                                          \
  }                                                                  \
  }while (0)
  
#define SET_ORDER(expected, indices) \
  do {                                                                  \
  piece_t *_expectedp = &expected[0]; \
  int *_indx = &indices[0]; \
  int _i, _j;                         \
  for (_i = 0; _i < NPIECES; _i++) {  \
    _j = *_indx++; \
    *_expectedp++ = _j >= 0 ? pieces[_j] : 0;   \
  } \
  } while (0)

int
test_parse()
{
        FILE *fp;
        Game *gamep;
		int i, ret;
        piece_t expected_order[NPIECES];
        int valid_indices[NPIECES] = { 0, 12, 4, 8, 1, 13, 5, 9, 2, 14, 6, 10, 3, 15, 7, 11 };
        int in_progress_indices[NPIECES] = { 0, 12, -1, 8, 1, -1, 5, 9, -1, 14, 6, -1, 3, -1, 7, -1 };
        int in_progress_remain_indices[NPIECES] = { -1, -1, 2, -1, 4, -1, -1, -1, -1, -1, 10, 11, -1, 13, -1, 15 };
        piece_t pieces[NPIECES] = PIECES;

		ret = 0;

        /* Check that valid/invalid game boards generate the correct errors. */
		PARSE_TEST("../tests/test_files/empty.quarto", -1, "PARSE_TEST EMPTY FILE");
		PARSE_TEST("../tests/test_files/long_row.quarto", -2, "PARSE_TEST LONG ROW");
		PARSE_TEST("../tests/test_files/short_row.quarto", -2, "PARSE_TEST SHORT ROW");
		PARSE_TEST("../tests/test_files/invalid_color1.quarto", -5, "PARSE_TEST INVALID COLOR PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_shape1.quarto", -5, "PARSE_TEST INVALID SHAPE PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_center1.quarto", -5, "PARSE_TEST INVALID CENTER PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_height1.quarto", -5, "PARSE_TEST INVALID HEIGHT PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_color2.quarto", -5, "PARSE_TEST INVALID COLOR PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_shape2.quarto", -5, "PARSE_TEST INVALID SHAPE PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_center2.quarto", -5, "PARSE_TEST INVALID CENTER PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_height2.quarto", -5, "PARSE_TEST INVALID HEIGHT PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_color3.quarto", -5, "PARSE_TEST INVALID COLOR PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_shape3.quarto", -5, "PARSE_TEST INVALID SHAPE PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_center3.quarto", -5, "PARSE_TEST INVALID CENTER PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_height3.quarto", -5, "PARSE_TEST INVALID HEIGHT PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_color4.quarto", -5, "PARSE_TEST INVALID COLOR PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_shape4.quarto", -5, "PARSE_TEST INVALID SHAPE PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_center4.quarto", -5, "PARSE_TEST INVALID CENTER PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_height4.quarto", -5, "PARSE_TEST INVALID HEIGHT PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_piece1.quarto", -6, "PARSE_TEST INVALID PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_piece2.quarto", -6, "PARSE_TEST INVALID PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_piece3.quarto", -6, "PARSE_TEST INVALID PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_piece4.quarto", -6, "PARSE_TEST INVALID PIECE FOUR");
		PARSE_TEST("../tests/test_files/valid.quarto", 0, "PARSE_TEST VALID");
		PARSE_TEST("../tests/test_files/no_pieces.quarto", 0, "PARSE_TEST NO PIECES");
		PARSE_TEST("../tests/test_files/in_progress.quarto", 0, "PARSE_TEST IN PROGRESS");
		PARSE_TEST("../tests/test_files/one_row.quarto", -1, "PARSE_TEST ONE ROW");
		PARSE_TEST("../tests/test_files/dup_pieces.quarto", -4, "PARSE_TEST DUP PIECES");

        /* Load up a full, valid game. */
        fp = fopen("../tests/test_files/valid.quarto", "r");
        /* Don't bother checking return value, we've already test that it parses correctly. */
        parse(fp, &gamep);
        fclose(fp);

        /* Check that pieces get placed correctly. */
        SET_ORDER(expected_order, valid_indices);
        for (i = 0; i < NPIECES; i++)
          PARSE_VERIFY_TEST(i, gamep->board, expected_order, "PARSE_VERIFY_TEST VALID LOCATION");
        /* Check that pieces are removed from the game correctly. */
        if (COUNT_PIECES(gamep->remaining) != 0) {
          printf("PARSE_VERIFY_TEST VALID REMAINING fails\n");
          printf("    expected 0 got %d\n", COUNT_PIECES(gamep->remaining));
        }

        /* Load up an empty game. */
        fp = fopen("../tests/test_files/no_pieces.quarto", "r");
        /* Don't bother checking return value, we've already test that it parses correctly. */
        parse(fp, &gamep);
        fclose(fp);

        /* Check that pieces get placed correctly. */
        memset(&expected_order, 0, NPIECES * sizeof(piece_t));
        for (i = 0; i < NPIECES; i++)
          PARSE_VERIFY_TEST(i, gamep->board, expected_order, "PARSE_VERIFY_TEST EMPTY LOCATION");
        /* Check that pieces are removed from the game correctly. */
        if (COUNT_PIECES(gamep->remaining) != NPIECES) {
          printf("PARSE_VERIFY_TEST EMPTY REMAINING fails\n");
          printf("    expected %d got %d\n", NPIECES, COUNT_PIECES(gamep->remaining));
        }

        /* Load up an in-progress game. */
        fp = fopen("../tests/test_files/in_progress.quarto", "r");
        /* Don't bother checking return value, we've already tested that it parses correctly. */
        parse(fp, &gamep);
        fclose(fp);

        /* Check that pieces get placed correctly. */
        SET_ORDER(expected_order, in_progress_indices);
        for (i = 0; i < NPIECES; i++)
          PARSE_VERIFY_TEST(i, gamep->board, expected_order, "PARSE_VERIFY_TEST IN PROGRESS LOCATION");
        /* Check that pieces are removed from the game correctly. */
        if (COUNT_PIECES(gamep->remaining) != 6) {
          printf("PARSE_VERIFY_TEST IN PROGRESS REMAINING fails\n");
          printf("    expected 6 got %d\n", COUNT_PIECES(gamep->remaining));
        }
        SET_ORDER(expected_order, in_progress_remain_indices);
        for (i = 0; i < NPIECES; i++)
          PARSE_VERIFY_TEST(i, gamep->remaining, expected_order, "PARSE_VERIFY_TEST IN PROGRESS REMAINING");

        return ret;
}
