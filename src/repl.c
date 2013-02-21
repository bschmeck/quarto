#include <stdio.h>

#include "board.h"
#include "move.h"

#define BUF_SZ 80

int get_piece(piece_t *);
void print_move(Move *);

#define SET_ATTRIBUTE(piece, attr, c, upper1, attr1, upper2, attr2)  \
  do {                                                               \
    if (c == upper1 || c == upper1 + 32) {                           \
      found |= attr;                                                 \
      piece |= attr1;                                                \
    } else if (c == upper2 || c == upper2 + 32) {                    \
      found |= attr;                                                 \
      piece |= attr2;                                                \
    }                                                                \
  } while (0)

int
get_piece(piecep)
     piece_t *piecep;
{
  char buf[BUF_SZ];
  int found;

  found = 0;
  *piecep = 0;
  
  while (found != (COLOR | SHAPE | CENTER | HEIGHT)) {
    if (!(found & COLOR))
      printf("[B]lack/[W]hite? ");
    else if (!(found & SHAPE))
      printf("[R]ound/[S]quare? ");
    else if (!(found & CENTER))
      printf("[H]ollow/[S]olid? ");
    else
      printf("[T]all/[S]hort? ");
    fgets(buf, BUF_SZ, stdin);

    if (!(found & COLOR))
      SET_ATTRIBUTE(*piecep, COLOR, *buf, 'B', BLACK, 'W', WHITE);
    else if (!(found & SHAPE))
      SET_ATTRIBUTE(*piecep, SHAPE, *buf, 'R', ROUND, 'S', SQUARE);
    else if (!(found & CENTER))
      SET_ATTRIBUTE(*piecep, CENTER, *buf, 'H', HOLLOW, 'S', SOLID);
    else
      SET_ATTRIBUTE(*piecep, HEIGHT, *buf, 'T', TALL, 'S', SHORT);
  }

  return 0;
}

void
print_move(movep)
     Move *movep;
{
  printf("Put piece %c%c%c%c at row %d col %d\n",
         (PIECE_COLOR(movep->piece) == BLACK) ? 'B' : 'W',
         (PIECE_SHAPE(movep->piece) == ROUND) ? 'R' : 'S',
         (PIECE_CENTER(movep->piece) == SOLID) ? 'S' : 'H',
         (PIECE_HEIGHT(movep->piece) == TALL) ? 'T' : 'S',
         movep->location / 4,
         movep->location % 4);
}

int
main(argc, argv)
     char **argv;
     int argc;
{
  Game *gamep;
  Move move;
  char buf[BUF_SZ];
  int ret, start;
    
  if ((ret = initialize_game(&gamep)) != 0) {
    printf("Cannot init game (%d)\n", ret);
    return ret;
  }

  start = -1;
  while (start < 0) {
    printf("Who goes first [m]e or [y]ou? ");
    fgets(buf, BUF_SZ, stdin);
    if (*buf == 'm' || *buf == 'M')
      start = 1;
    else if (*buf == 'y' || *buf == 'Y')
      start = 0;
  }
  
  get_piece(&move.piece);
  printf("Got piece %d\n", move.piece);


  for (move.location = 0; move.location < BOARD_SIZE; move.location++)
    print_move(&move);
  
  return 0;
}
