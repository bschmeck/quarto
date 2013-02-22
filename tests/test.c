#include <stdio.h>

#include "test.h"

#define RUN_TEST(method, name) \
		do {                                                             \
				int _ret;						                         \
				_ret = method();						                 \
				printf("%s %s\n", name, _ret == 0 ? "passes" : "fails"); \
				ret = ret == 0 ? _ret : ret;							 \
		} while(0)
		  
int 
main(argc, argv)
		char *argv;
		int argc; 
{
		int ret;

		ret = 0;

		RUN_TEST(test_piece_attributes, "PIECE_ATTRIBUTES");
		RUN_TEST(test_all_match, "ALL_MATCH");
		RUN_TEST(test_is_quarto, "IS_QUARTO");
		RUN_TEST(test_is_winning_board, "IS_WINNING_BOARD");
		RUN_TEST(test_is_game_over, "IS_GAME_OVER");
        RUN_TEST(test_count_pieces, "COUNT_PIECES");
		RUN_TEST(test_initialize_game, "INIT_GAME");
		RUN_TEST(test_parse, "TEST_PARSE");
		RUN_TEST(test_parse_piece, "TEST_PARSE_PIECE");
		RUN_TEST(test_possible_moves, "TEST_POSSIBLE_MOVES");
		RUN_TEST(test_count_remaining_moves, "TEST_COUNT_REMAINING_MOVES");
        RUN_TEST(test_make_move, "TEST_MAKE_MOVE");
        RUN_TEST(test_score_move, "TEST_SCORE_MOVE");
        RUN_TEST(test_choose_piece, "TEST_CHOOSE_PIECE");
        RUN_TEST(test_take_turn, "TEST_TAKE_TURN");

		return ret;
}
