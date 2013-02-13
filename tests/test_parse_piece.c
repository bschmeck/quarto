#include <stdio.h>

#include "test.h"

#define PARSE_PIECE_TEST(piece_str, expect, name)					  \
		do {                                                          \
          int _ret;                                                   \
          piece_t _piece;                                             \
			if ((_ret = parse_piece(piece_str, &_piece)) != expect) { \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", expect, _ret);	      \
				ret = -1;                                             \
		    }                                                         \
        } while(0)
#define PARSE_PIECE_ATTRIBUTE(piece_str, attr, name)					  \
		do {                                                          \
          int _ret;                                                   \
          piece_t _piece;                                             \
          parse_piece(piece_str, &_piece);                            \
          if (_piece & attr != attr) {                                  \
				printf("%s fails\n", name);					          \
				printf("  expected %d got %d\n", attr, _piece);	      \
				ret = -1;                                             \
		    }                                                         \
        } while(0)

int
test_parse_piece()
{
  int ret;
  
  ret = 0;
  
  PARSE_PIECE_TEST("BRST", 0, "PARSE_PIECE_TEST VALID PIECE");
  PARSE_PIECE_TEST("XXXX", 0, "PARSE_PIECE_TEST VALID EMPTY");
  PARSE_PIECE_TEST("ARST", -5, "PARSE_PIECE_TEST INVALID COLOR");
  PARSE_PIECE_TEST("BAST", -5, "PARSE_PIECE_TEST INVALID SHAPE");
  PARSE_PIECE_TEST("BRAT", -5, "PARSE_PIECE_TEST INVALID CENTER");
  PARSE_PIECE_TEST("BRSA", -5, "PARSE_PIECE_TEST INVALID HEIGHT");
  PARSE_PIECE_TEST("XRST", -6, "PARSE_PIECE_TEST INVALID PIECE ONE");
  PARSE_PIECE_TEST("BXST", -6, "PARSE_PIECE_TEST INVALID PIECE TWO");
  PARSE_PIECE_TEST("BRXT", -6, "PARSE_PIECE_TEST INVALID PIECE THREE");
  PARSE_PIECE_TEST("BRSX", -6, "PARSE_PIECE_TEST INVALID PIECE FOUR");

  return ret;
 
}
