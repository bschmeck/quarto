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

#define ALL_MATCH(cat, a, b, c, d) (IS_PIECE(a) && IS_PIECE(b) && IS_PIECE(c) && IS_PIECE(d) && ((a & cat) ^ (b & cat) == 0) && ((a & cat) ^ (c & cat) == 0) && ((a & cat) ^ (d & cat) == 0))
