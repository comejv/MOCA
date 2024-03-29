#ifndef SERIALIZATION_H
#define SERIALIZATION_H

/**
 * \file serialization.h
 * \brief Fonctions de conversion entre ABR (dictionnaire) et table de hachage
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "structures.h"
#include "word_tools.h"
#include "macro.h"
#include <free.h>
// #include "json.h"

#define MaxSizeArray 16381

// struct json_object *createJSON(mot_data_t **d);

/**
 * \fn int hash(char *m)
 * \brief Fonction de calcul du hashcode d'un mot m
 * \param m le contenu du mot à transcrire en hashcode
 * \note Pas de valeur de retour
*/
uint64_t hash(char *m);

/**
 * \fn void deserializeDico(dico** dic, mot_data_t *elt)
 * \brief Fonction de désérialisation d'une structure de mot dans une structure de dictionnaire
 * \param dic la structure de dictionnaire de destination
 * \param elt la structure de mot à intégrer dans la structure de dictionnaire
 * \note Pas de valeur de retour
 * 
 * Cette fonction procède à la désérialisation d'une structure de mot dans une structure de dictionnaire (ABR), c'est-à-dire à 
 * l'insertion du mot dans l'arbre (de la même manière que insertDico ?)
*/
void deserializeDico(dico** dic, mot_data_t *elt);

/**
 * \fn void serializeDico(dico * dictionary, mot_data_t **table)
 * \brief Fonction de sérialisation d'une structure de dictionnaire dans une table
 * \param dictionary la structure de dictionnaire d'origine
 * \param table la table (pointeur sur un ensemble de structures de mots) de destination
 * \note Pas de valeur de retour
 * 
 * Cette fonction procède à la sérialisation d'une structure de dictionnaire (ABR) dans une table de hachage, où le hash de chaque mot
 * correspond à son indice dans la table, et le contenu de chaque mot correspond au contenu de chaque case de la table.
*/
void serializeDico(dico * dictionary, mot_data_t **table);

#endif