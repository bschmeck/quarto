#include <stdio.h>
#include <time.h>

#include "bench.h"

int
main(argc, argv)
     char *argv;
     int argc;
{
  FILE *fp;
  Game *gamep;
  clock_t tic, toc;
  double elapsed;
  int i, loc, niters, ret;
  piece_t piece, next_piece;
  char *filename = "../bench/bench_files/one_piece.quarto";

  niters = 100;
  
  /*
   * Start by benchmarking take_turn.  Eventually we'll benchmark the lower level
   * operations (score_move, choose_piece,) too.
   */
  elapsed = 0;
  for (i = 0; i < niters; i++) {
    fp = fopen(filename, "r");
    if ((ret = parse(fp, &gamep)) != 0) {
      printf("Cannot parse %s (err %d)\n", filename, ret);
      return ret;
    }
    fclose(fp);
    piece = (BLACK | SQUARE | HOLLOW | SHORT);
    
    tic = clock();
    if ((ret = take_turn(gamep, piece, &loc, &next_piece)) != 0) {
      printf("take_turn fails, returned %d\n", ret);
      return ret;
    }
    toc = clock();

    elapsed += (double)(toc - tic) / CLOCKS_PER_SEC;
  }
  printf("Elapsed: %d iterations in %f seconds\n", niters, elapsed);

  return 0;
}
