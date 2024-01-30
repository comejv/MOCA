#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "structures.h"
#include "word_tools.h"
// #include "json.h"

#define MaxSizeArray 16381

// struct json_object *createJSON(mot_data_t **d);

int hash(char *m);

void deserializeDico(dico** dic, mot_data_t *elt);

void serializeDico(dico * dictionary, mot_data_t **table);

#endif