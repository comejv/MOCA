#ifndef WORD_TOOLS_H
#define WORD_TOOLS_H

#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define SEP " ,.-"

char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol);

int compareWord(mot_data_t* w1, mot_data_t* w2);

void incWord(emplacement_t* location, unsigned int line, unsigned int colonne);

#endif