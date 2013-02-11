#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

#define COUNT_PIECES_TEST(boardp, expect, name)		           \
		do {                                                   \
		    int _ret;                                          \
			if ((_ret = COUNT_PIECES(boardp)) != expect) {     \
				printf("%s fails\n", name);					   \
				printf("  expected %d got %d\n", expect, _ret); \
				ret = -1;                                      \
		    }                                                  \
        } while(0)

int
test_count_pieces()
{
        char *msg;
        int i, ret;
        int *boardp;
        int pieces[NPIECES] = PIECES;
        int indexes[BOARD_SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        
        boardp = calloc(BOARD_SIZE, sizeof(int));
		ret = 0;

		/* Test an empty board */
		COUNT_PIECES_TEST(boardp, 0, "COUNT_PIECES EMPTY");

        /* TODO: Randomize indexes */
        msg = calloc(16, sizeof(char));
        for (i = 0; i < BOARD_SIZE; i++) {
          boardp[indexes[i]] = pieces[i];
          sprintf(msg, "COUNT_PIECES %d", i+1);
          COUNT_PIECES_TEST(boardp, i+1, msg); 
        }
        
		return ret;		
}
