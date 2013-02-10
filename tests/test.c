#include <stdio.h>

#include "test.h"

int 
main(argc, argv)
		char *argv;
		int argc; 
{
		int ret, t_ret;

		ret = t_ret = 0;

		t_ret = test_all_match();
		printf("ALL_MATCH %s\n", t_ret == 0 ? "passes" : "fails");
		ret = ret == 0 ? t_ret : ret;

		ret = test_is_quarto();
		printf("IS_QUARTO %s\n", t_ret == 0 ? "passes" : "fails");
		ret = ret == 0 ? t_ret : ret;

		return ret;
}
