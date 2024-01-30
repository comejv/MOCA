#ifndef DICO_TOOLS_H
#define DICO_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "word_tools.h"
#include "serialization.h"

void insertDico(dico** dictionary, mot_t* linkWord);

void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne);

#endif