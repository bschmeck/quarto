#include <stdio.h>

#include "board.h"
#include "parse.h"

#define CHECK(boardp, i0, i1, i2, i3, name) \
  do { \
  if (IS_QUARTO(boardp[i0], boardp[i1], boardp[i2], boardp[i3])) { \
  printf("%s\n", name);                                            \
    found = 1; \
  } \
  } while (0)
  
int
main(argc, argv)
     char **argv;
     int argc;
{
  FILE *fp;
  Game *gamep;
  char *filename;
  int found, ret;
  
  filename = argv[1];
  
  fp = fopen(filename, "r");
  if ((ret = parse(fp, &gamep)) != 0) {
    printf("Cannot parse %s (err %d)\n", filename, ret);
    return ret;
  }
  fclose(fp);

  found = 0;
  CHECK(gamep->board, 0, 1, 2, 3, "Row 0");
  CHECK(gamep->board, 4, 5, 6, 7, "Row 1");
  CHECK(gamep->board, 8, 9, 10, 11, "Row 2");
  CHECK(gamep->board, 12, 13, 14, 15, "Row 3");
  CHECK(gamep->board, 0, 4, 8, 12, "Col 0");
  CHECK(gamep->board, 1, 5, 9, 13, "Col 1");
  CHECK(gamep->board, 2, 6, 10, 14, "Col 2");
  CHECK(gamep->board, 3, 7, 11, 15, "Col 3");
  CHECK(gamep->board, 0, 5, 10, 15, "Diag L-R");
  CHECK(gamep->board, 3, 6, 9, 12, "Diag R-L");
  
  if (!found)
    printf("No Quarto\n");
  
  return 0;
}
