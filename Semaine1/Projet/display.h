#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define DICORES "Resultats/dictionnaires.txt"
#define TEXTE "Exemples/hugo1.txt"

void displayWord(mot_data_t* word, FILE *filedes);

void displayNodes(dico *d, FILE* f);

void displayDico(dico* dictionary);



#endif