#ifndef BOARD_H
#define BOARD_H

typedef unsigned int piece_t;

/* Attributes */
#define PIECE 1
#define COLOR 2
#define SHAPE 4
#define CENTER 8
#define HEIGHT 16

#define IS_PIECE(a) (a & PIECE)

#define BLACK (COLOR | PIECE)
#define WHITE (PIECE)
#define ROUND (SHAPE | PIECE)
#define SQUARE (PIECE)
#define SOLID (CENTER | PIECE)
#define HOLLOW (PIECE)
#define TALL (HEIGHT | PIECE)
#define SHORT (PIECE)

#define PIECE_COLOR(a) (a & BLACK)
#define PIECE_SHAPE(a) (a & ROUND)
#define PIECE_CENTER(a) (a & SOLID)
#define PIECE_HEIGHT(a) (a & TALL)

#define NPIECES 16
#define PIECES {						   \
		  (BLACK | ROUND | SOLID | TALL),    \
          (BLACK | ROUND | SOLID | SHORT),   \
          (BLACK | ROUND | HOLLOW | TALL),   \
          (BLACK | ROUND | HOLLOW | SHORT),  \
          (BLACK | SQUARE | SOLID | TALL),   \
          (BLACK | SQUARE | SOLID | SHORT),  \
          (BLACK | SQUARE | HOLLOW | TALL),  \
          (BLACK | SQUARE | HOLLOW | SHORT), \
          (WHITE | ROUND | SOLID | TALL),    \
          (WHITE | ROUND | SOLID | SHORT),   \
          (WHITE | ROUND | HOLLOW | TALL),   \
          (WHITE | ROUND | HOLLOW | SHORT),  \
          (WHITE | SQUARE | SOLID | TALL),   \
          (WHITE | SQUARE | SOLID | SHORT),  \
          (WHITE | SQUARE | HOLLOW | TALL),  \
		  (WHITE | SQUARE | HOLLOW | SHORT) }

/* Check whether four pieces all share a given attribute */
#define ALL_MATCH(attr, a, b, c, d) (IS_PIECE(a) && IS_PIECE(b) && IS_PIECE(c) && IS_PIECE(d) && (((a & attr) ^ (b & attr)) == 0) && (((a & attr) ^ (c & attr)) == 0) && (((a & attr) ^ (d & attr)) == 0))

/* Check whether four pieces all share a common attribute */
#define IS_QUARTO(a, b, c, d) \
    (ALL_MATCH(COLOR, (a), (b), (c), (d)) || ALL_MATCH(SHAPE, (a), (b), (c), (d)) || ALL_MATCH(CENTER, (a), (b), (c), (d)) || ALL_MATCH(HEIGHT, (a), (b), (c), (d)))

#define NROWS 4
#define NCOLS 4
#define BOARD_SIZE (NROWS * NCOLS)
/* Check whether any of the rows columns or diags on the board are a quarto */
#define IS_WINNING_BOARD(boardp) \
		(IS_QUARTO(boardp[0], boardp[1], boardp[2], boardp[3]) || IS_QUARTO(boardp[4], boardp[5], boardp[6], boardp[7]) ||      \
		IS_QUARTO(boardp[8], boardp[9], boardp[10], boardp[11]) || IS_QUARTO(boardp[12], boardp[13], boardp[14], boardp[15]) || \
		IS_QUARTO(boardp[0], boardp[4], boardp[8], boardp[12]) || IS_QUARTO(boardp[1], boardp[5], boardp[9], boardp[13]) ||     \
		IS_QUARTO(boardp[2], boardp[6], boardp[10], boardp[14]) || IS_QUARTO(boardp[3], boardp[7], boardp[11], boardp[15]) ||   \
		IS_QUARTO(boardp[0], boardp[5], boardp[10], boardp[15]) || IS_QUARTO(boardp[3], boardp[6], boardp[9], boardp[12]))

/* Count the number of pieces in the array. */
#define COUNT_PIECES(piecesp) \
  ((piecesp[0] & PIECE) + (piecesp[1] & PIECE) + (piecesp[2] & PIECE) + (piecesp[3] & PIECE) + (piecesp[4] & PIECE) + (piecesp[5] & PIECE) + (piecesp[6] & PIECE) + (piecesp[7] & PIECE) + (piecesp[8] & PIECE) + (piecesp[9] & PIECE) + (piecesp[10] & PIECE) + (piecesp[11] & PIECE) + (piecesp[12] & PIECE) + (piecesp[13] & PIECE) + (piecesp[14] & PIECE) + (piecesp[15] & PIECE))

typedef struct {
        piece_t board[BOARD_SIZE];
		piece_t remaining[NPIECES];
} Game;

#endif
