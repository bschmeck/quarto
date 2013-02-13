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

int
test_parse()
{
		int ret;

		ret = 0;

		PARSE_TEST("../tests/test_files/empty.quarto", -1, "PARSE_TEST EMPTY FILE");
		PARSE_TEST("../tests/test_files/long_row.quarto", -1, "PARSE_TEST LONG ROW");
		PARSE_TEST("../tests/test_files/short_row.quarto", -1, "PARSE_TEST SHORT ROW");
		PARSE_TEST("../tests/test_files/invalid_color1.quarto", -1, "PARSE_TEST INVALID COLOR PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_shape1.quarto", -1, "PARSE_TEST INVALID SHAPE PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_center1.quarto", -1, "PARSE_TEST INVALID CENTER PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_height1.quarto", -1, "PARSE_TEST INVALID HEIGHT PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_color2.quarto", -1, "PARSE_TEST INVALID COLOR PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_shape2.quarto", -1, "PARSE_TEST INVALID SHAPE PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_center2.quarto", -1, "PARSE_TEST INVALID CENTER PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_height2.quarto", -1, "PARSE_TEST INVALID HEIGHT PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_color3.quarto", -1, "PARSE_TEST INVALID COLOR PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_shape3.quarto", -1, "PARSE_TEST INVALID SHAPE PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_center3.quarto", -1, "PARSE_TEST INVALID CENTER PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_height3.quarto", -1, "PARSE_TEST INVALID HEIGHT PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_color4.quarto", -1, "PARSE_TEST INVALID COLOR PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_shape4.quarto", -1, "PARSE_TEST INVALID SHAPE PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_center4.quarto", -1, "PARSE_TEST INVALID CENTER PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_height4.quarto", -1, "PARSE_TEST INVALID HEIGHT PIECE FOUR");
		PARSE_TEST("../tests/test_files/invalid_piece1.quarto", -1, "PARSE_TEST INVALID PIECE ONE");
		PARSE_TEST("../tests/test_files/invalid_piece2.quarto", -1, "PARSE_TEST INVALID PIECE TWO");
		PARSE_TEST("../tests/test_files/invalid_piece3.quarto", -1, "PARSE_TEST INVALID PIECE THREE");
		PARSE_TEST("../tests/test_files/invalid_piece4.quarto", -1, "PARSE_TEST INVALID PIECE FOUR");
		PARSE_TEST("../tests/test_files/valid.quarto", 0, "PARSE_TEST VALID ROW");
		PARSE_TEST("../tests/test_files/no_pieces.quarto", 0, "PARSE_TEST NO PIECES");
		PARSE_TEST("../tests/test_files/one_row.quarto", -1, "PARSE_TEST ONE ROW");
        return ret;
}
