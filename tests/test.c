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
		int ret, t_ret;

		ret = 0;

		RUN_TEST(test_all_match, "ALL_MATCH");
		RUN_TEST(test_is_quarto, "IS_QUARTO");
		RUN_TEST(test_is_winning_board, "IS_WINNING_BOARD");

		return ret;
}
