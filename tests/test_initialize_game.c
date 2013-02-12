#include <stdio.h>

#include "test.h"

int
test_initialize_game()
{
		Game *gamep;
		int ret, t_ret;
		
		if ((ret = initialize_game(&gamep)) != 0) {
				printf("INIT_GAME INITIALIZATION fails\n");
				printf("    expected 0 got %d\n", ret);
				return ret;
		}
		if ((t_ret = COUNT_PIECES(gamep->board)) != 0) {
				printf("INIT_GAME EMPTY BOARD fails\n");
				printf("    expected 0 got %d\n", t_ret);
				ret = ret == 0 ? t_ret : ret; 
		}
		if ((t_ret = COUNT_PIECES(gamep->remaining)) != NPIECES) {
				printf("INIT_GAME ALL PIECES fails\n");
				printf("    expected %d got %d\n", NPIECES, t_ret);
				ret = ret == 0 ? t_ret : ret; 
		}

		return ret;
}
