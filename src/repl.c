#include <stdio.h>

#include "board.h"
#include "move.h"

#define BUF_SZ 80

int get_piece(piece_t *);
int opponents_turn(Move *);
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

int
opponents_turn(movep)
     Move *movep;
{
  char buf[BUF_SZ];
  int col, row;
  
  printf("Chosen piece: %c%c%c%c\n",
           (PIECE_COLOR(movep->piece) == BLACK) ? 'B' : 'W',
           (PIECE_SHAPE(movep->piece) == ROUND) ? 'R' : 'S',
           (PIECE_CENTER(movep->piece) == SOLID) ? 'S' : 'H',
           (PIECE_HEIGHT(movep->piece) == TALL) ? 'T' : 'S');         
  printf("Placed at row: ");
  fgets(buf, BUF_SZ, stdin);
  row = atoi(buf);
  printf("Placed at col: ");
  fgets(buf, BUF_SZ, stdin);
  col = atoi(buf);
  
  movep->location = row * 4 + col;
    
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
  FILE *fp;
  Game *gamep;
  Move move;
  char buf[BUF_SZ];
  int ret, score, start;
  piece_t next_piece;
  
  if (argc == 2) {
    fp = fopen(argv[1], "r");
    if ((ret = parse(fp, &gamep)) != 0) {
      printf("Cannot parse %s (err %d)\n", argv[1], ret);
      return ret;
    }
    fclose(fp);
  } else {
    if ((ret = initialize_game(&gamep)) != 0) {
      printf("Cannot init game (%d)\n", ret);
      return ret;
    }
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
  
  if (start) {
    choose_piece(gamep, &move.piece, &score);
  }

  while (!IS_GAME_OVER(gamep->board)) {
    opponents_turn(&move);
    
    make_move(gamep, &move);

    if (IS_GAME_OVER(gamep->board))
      break;
    
    get_piece(&move.piece);
    take_turn(gamep, move.piece, &move.location, &next_piece);
    make_move(gamep, &move);
    print_move(&move);
  
    move.piece = next_piece;
  }
  
  return 0;
}
