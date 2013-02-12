#ifndef BOARD_H
#define BOARD_H

typedef unsigned int piece_t;
typedef struct {
		piece_t *board;
		piece_t *remaining;
} Game;

#define PIECE 1
#define COLOR 2
#define SHAPE 4
#define CENTER 8
#define HEIGHT 16

#define IS_PIECE(a) (a & PIECE)

#define BLACK COLOR | PIECE
#define WHITE PIECE
#define ROUND SHAPE | PIECE
#define SQUARE PIECE
#define SOLID CENTER | PIECE
#define HOLLOW PIECE
#define TALL HEIGHT | PIECE
#define SHORT PIECE

#define NPIECES 16
#define PIECES {						   \
		  BLACK | ROUND | SOLID | TALL,    \
          BLACK | ROUND | SOLID | SHORT,   \
          BLACK | ROUND | HOLLOW | TALL,   \
          BLACK | ROUND | HOLLOW | SHORT,  \
          BLACK | SQUARE | SOLID | TALL,   \
          BLACK | SQUARE | SOLID | SHORT,  \
          BLACK | SQUARE | HOLLOW | TALL,  \
          BLACK | SQUARE | HOLLOW | SHORT, \
          WHITE | ROUND | SOLID | TALL,    \
          WHITE | ROUND | SOLID | SHORT,   \
          WHITE | ROUND | HOLLOW | TALL,   \
          WHITE | ROUND | HOLLOW | SHORT,  \
          WHITE | SQUARE | SOLID | TALL,   \
          WHITE | SQUARE | SOLID | SHORT,  \
          WHITE | SQUARE | HOLLOW | TALL,  \
			  WHITE | SQUARE | HOLLOW | SHORT}

#define ALL_MATCH(cat, a, b, c, d) (IS_PIECE(a) && IS_PIECE(b) && IS_PIECE(c) && IS_PIECE(d) && (((a & cat) ^ (b & cat)) == 0) && (((a & cat) ^ (c & cat)) == 0) && (((a & cat) ^ (d & cat)) == 0))

#define IS_QUARTO(a, b, c, d) \
    (ALL_MATCH(COLOR, (a), (b), (c), (d)) || ALL_MATCH(SHAPE, (a), (b), (c), (d)) || ALL_MATCH(CENTER, (a), (b), (c), (d)) || ALL_MATCH(HEIGHT, (a), (b), (c), (d)))

#define NROWS 4
#define NCOLS 4
#define BOARD_SIZE (NROWS * NCOLS)
#define IS_WINNING_BOARD(boardp) \
		(IS_QUARTO(boardp[0], boardp[1], boardp[2], boardp[3]) || IS_QUARTO(boardp[4], boardp[5], boardp[6], boardp[7]) ||      \
		IS_QUARTO(boardp[8], boardp[9], boardp[10], boardp[11]) || IS_QUARTO(boardp[12], boardp[13], boardp[14], boardp[15]) || \
		IS_QUARTO(boardp[0], boardp[4], boardp[8], boardp[12]) || IS_QUARTO(boardp[1], boardp[5], boardp[9], boardp[13]) ||     \
		IS_QUARTO(boardp[2], boardp[6], boardp[10], boardp[14]) || IS_QUARTO(boardp[3], boardp[7], boardp[11], boardp[15]) ||   \
		IS_QUARTO(boardp[0], boardp[5], boardp[10], boardp[15]) || IS_QUARTO(boardp[3], boardp[6], boardp[9], boardp[12]))

#define COUNT_PIECES(boardp) \
  ((boardp[0] & PIECE) + (boardp[1] & PIECE) + (boardp[2] & PIECE) + (boardp[3] & PIECE) + (boardp[4] & PIECE) + (boardp[5] & PIECE) + (boardp[6] & PIECE) + (boardp[7] & PIECE) + (boardp[8] & PIECE) + (boardp[9] & PIECE) + (boardp[10] & PIECE) + (boardp[11] & PIECE) + (boardp[12] & PIECE) + (boardp[13] & PIECE) + (boardp[14] & PIECE) + (boardp[15] & PIECE))

#endif
