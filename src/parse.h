#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

int initialize_game(Game **);
int parse(FILE *, Game **);

#define ROWLEN 17

#endif
