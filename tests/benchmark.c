#include <stdio.h>

#include "bench.h"

int
main(argc, argv)
     char *argv;
     int argc;
{
  int niters, ret;

  niters = 100;

  /*
   * Start by benchmarking take_turn.  Eventually we'll benchmark the lower level
   * operations (score_move, choose_piece,) too.
   */
  
}
