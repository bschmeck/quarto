#include <stdint.h>
#include <stdio.h>

#include "test.h"

#define COUNT_REMAINING_MOVES_TEST(filename, expect, name)			  \
		do {                                                          \
     		FILE *_fp;                                                \
            Game *_gp;                                                \
		    int _ret;                                                 \
            _fp = fopen(filename, "r");                               \
			if ((_ret = parse(_fp, &_gp)) != 0) {   				  \
				printf("%s fails\n", name);					          \
				printf("  cannot parse %s (err %d)\n", filename, _ret);    \
				ret = -1;                                             \
		    }                                                         \
            fclose(_fp);                                              \
            if ((_ret = count_remaining_moves(_gp)) != expect) { \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, _ret);    \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

int
test_count_remaining_moves()
{
  int ret;

  ret = 0;

  COUNT_REMAINING_MOVES_TEST("../tests/test_files/valid.quarto", 0, "COUNT_REMAINING_MOVES_TEST FULL BOARD");
  COUNT_REMAINING_MOVES_TEST("../tests/test_files/no_pieces.quarto", INT32_MAX - 1, "COUNT_REMAINING_MOVES_TEST EMPTY BOARD");
  COUNT_REMAINING_MOVES_TEST("../tests/test_files/in_progress.quarto", 6*6*5*5*4*4*3*3*2*2, "COUNT_REMAINING_MOVES_TEST IN PROGRESS");
 
  return ret;
}
