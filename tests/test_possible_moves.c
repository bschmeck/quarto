#include <stdio.h>

#include "test.h"

#define POSSIBLE_MOVES_COUNT_TEST(filename, expect, name)   						  \
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
            if ((_ret = possible_moves(_gp, NULL)) != expect) { \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, _ret);    \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

int
test_possible_moves()
{
  int ret;
  
  ret = 0;
  
  POSSIBLE_MOVES_COUNT_TEST("../tests/test_files/valid.quarto", 0, "POSSIBLE_MOVES COUNT_TEST FULL BOARD");
  POSSIBLE_MOVES_COUNT_TEST("../tests/test_files/no_pieces.quarto", 256, "POSSIBLE_MOVES_COUNT_TEST EMPTY BOARD");
  POSSIBLE_MOVES_COUNT_TEST("../tests/test_files/in_progress.quarto", 36, "POSSIBLE_MOVES_COUNT_TEST IN PROGRESS");
 
  return ret;
}
