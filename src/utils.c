#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "utils.h"

#define CHECK(boardp, i0, i1, i2, i3, buf, name)                        \
  do {                                                                  \
    if (IS_QUARTO(boardp[i0], boardp[i1], boardp[i2], boardp[i3])) {    \
      sprintf(buf, "%s\n", name);                                       \
      buf += strlen(name) + 1;                                          \
      found = 1;                                                        \
    }                                                                   \
  } while (0)

int
piece_string(piece, strp)
     piece_t piece;
     char *strp;
{
  strp[0] = (PIECE_COLOR(piece) == BLACK) ? 'B' : 'W';
  strp[1] = (PIECE_SHAPE(piece) == ROUND) ? 'R' : 'S';
  strp[2] = (PIECE_CENTER(piece) == SOLID) ? 'S' : 'H';
  strp[3] = (PIECE_HEIGHT(piece) == TALL) ? 'T' : 'S';
  strp[4] = '\0';

  return 0;         
}

int
explain_string(gamep, strp)
     Game *gamep;
     char **strp;
{
  char *buf;
  int found;
  
  buf = (char *)calloc(100, sizeof(char));
  *strp = buf;
  
  found = 0;
  
  CHECK(gamep->board, 0, 1, 2, 3, buf, "Row 0");
  CHECK(gamep->board, 4, 5, 6, 7, buf, "Row 1");
  CHECK(gamep->board, 8, 9, 10, 11, buf, "Row 2");
  CHECK(gamep->board, 12, 13, 14, 15, buf, "Row 3");
  CHECK(gamep->board, 0, 4, 8, 12, buf, "Col 0");
  CHECK(gamep->board, 1, 5, 9, 13, buf, "Col 1");
  CHECK(gamep->board, 2, 6, 10, 14, buf, "Col 2");
  CHECK(gamep->board, 3, 7, 11, 15, buf, "Col 3");
  CHECK(gamep->board, 0, 5, 10, 15, buf, "Diag L-R");
  CHECK(gamep->board, 3, 6, 9, 12, buf, "Diag R-L");
  
  if (!found)
    printf("No Quarto\n");
  return 0;
}
