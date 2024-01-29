#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "hash.h"
#include "word_tools.h"

// struct json_object *createJSON(mot_data_t **d);

void deserializeDico(dico** dic, mot_data_t *elt);

void serializeDico(dico * dictionary, mot_data_t **table);


#endif