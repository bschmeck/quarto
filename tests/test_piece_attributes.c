#include <stdio.h>

#include "test.h"

#define ATTRIBUTE_TEST(color, shape, center, height, name)              \
  do {                                                                  \
          piece_t _piece;                                               \
          _piece = color | shape | center | height;                     \
          if (PIECE_COLOR(_piece) != color) {                           \
            printf("%s COLOR fails\n", name);                           \
            printf("  expected %d got %d\n", color, PIECE_COLOR(_piece)); \
            ret = -1;                                                   \
          }                                                             \
          if (PIECE_SHAPE(_piece) != shape) {                           \
            printf("%s SHAPE fails\n", name);                           \
            printf("  expected %d got %d\n", shape, PIECE_SHAPE(_piece)); \
            ret = -1;                                                   \
          }                                                             \
          if (PIECE_CENTER(_piece) != center) {                         \
            printf("%s CENTER fails\n", name);                          \
            printf("  expected %d got %d\n", center, PIECE_CENTER(_piece)); \
            ret = -1;                                                   \
          }                                                             \
          if (PIECE_HEIGHT(_piece) != height) {                         \
            printf("%s HEIGHT fails\n", name);                          \
            printf("  expected %d got %d\n", height, PIECE_HEIGHT(_piece)); \
            ret = -1;                                                   \
          }                                                             \
  } while(0)
  
int
test_piece_attributes()
{
  int ret;

  ret = 0;
  ATTRIBUTE_TEST(BLACK, ROUND, SOLID, TALL, "BRST"); 
  ATTRIBUTE_TEST(BLACK, ROUND, SOLID, SHORT, "BRSS");
  ATTRIBUTE_TEST(BLACK, ROUND, HOLLOW, TALL, "BRHT");
  ATTRIBUTE_TEST(BLACK, ROUND, HOLLOW, SHORT, "BRHS");
  ATTRIBUTE_TEST(BLACK, SQUARE, SOLID, TALL, "BSST");
  ATTRIBUTE_TEST(BLACK, SQUARE, SOLID, SHORT, "BSSS");
  ATTRIBUTE_TEST(BLACK, SQUARE, HOLLOW, TALL, "BSHT");
  ATTRIBUTE_TEST(BLACK, SQUARE, HOLLOW, SHORT, "BSHS");
  ATTRIBUTE_TEST(WHITE, ROUND, SOLID, TALL, "WRST");
  ATTRIBUTE_TEST(WHITE, ROUND, SOLID, SHORT, "WRSS");
  ATTRIBUTE_TEST(WHITE, ROUND, HOLLOW, TALL, "WRHT");
  ATTRIBUTE_TEST(WHITE, ROUND, HOLLOW, SHORT, "WRHS");
  ATTRIBUTE_TEST(WHITE, SQUARE, SOLID, TALL, "WSST");
  ATTRIBUTE_TEST(WHITE, SQUARE, SOLID, SHORT, "WSSS");
  ATTRIBUTE_TEST(WHITE, SQUARE, HOLLOW, TALL, "WSHT");
  ATTRIBUTE_TEST(WHITE, SQUARE, HOLLOW, SHORT, "WSHS");

  return ret;
}
  
