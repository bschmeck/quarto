#include <stdio.h>

#include "test.h"

#define STRING_TEST(piece, expect)                                      \
  do {                                                                  \
    char str[4];                                                        \
    int _ret;                                                           \
    if ((_ret = piece_string(piece, str)) != 0) {                       \
      printf("PIECE_STRING %s fails\n", expect);                        \
      printf("    cannot parse %d\n", piece);                           \
      ret = _ret;                                                       \
    }                                                                   \
    if (strcmp(str, expect) != 0) {                                     \
      printf("PIECE_STRING %s fails\n", expect);                        \
      printf("  expected %s got %s\n", expect, str);                    \
      ret = -1;                                                         \
    }                                                                   \
  } while(0)
  
int
test_piece_string()
{
  int ret;

  ret = 0;
  STRING_TEST(BLACK | ROUND | SOLID | TALL, "BRST"); 
  STRING_TEST(BLACK | ROUND | SOLID | SHORT, "BRSS");
  STRING_TEST(BLACK | ROUND | HOLLOW | TALL, "BRHT");
  STRING_TEST(BLACK | ROUND | HOLLOW | SHORT, "BRHS");
  STRING_TEST(BLACK | SQUARE | SOLID | TALL, "BSST");
  STRING_TEST(BLACK | SQUARE | SOLID | SHORT, "BSSS");
  STRING_TEST(BLACK | SQUARE | HOLLOW | TALL, "BSHT");
  STRING_TEST(BLACK | SQUARE | HOLLOW | SHORT, "BSHS");
  STRING_TEST(WHITE | ROUND | SOLID | TALL, "WRST");
  STRING_TEST(WHITE | ROUND | SOLID | SHORT, "WRSS");
  STRING_TEST(WHITE | ROUND | HOLLOW | TALL, "WRHT");
  STRING_TEST(WHITE | ROUND | HOLLOW | SHORT, "WRHS");
  STRING_TEST(WHITE | SQUARE | SOLID | TALL, "WSST");
  STRING_TEST(WHITE | SQUARE | SOLID | SHORT, "WSSS");
  STRING_TEST(WHITE | SQUARE | HOLLOW | TALL, "WSHT");
  STRING_TEST(WHITE | SQUARE | HOLLOW | SHORT, "WSHS");

  return ret;
}
  
