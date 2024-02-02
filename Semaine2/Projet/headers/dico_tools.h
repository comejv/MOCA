#ifndef DICO_TOOLS_H
#define DICO_TOOLS_H

/**
 * \file dico_tools.h
 * \brief Outils de manipulation d'une structure de dictionnaire
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "word_tools.h"
#include "serialization.h"

/**
 * \fn void insertDico(dico** dictionary, mot_t* linkWord)
 * \brief Fonction d'insertion d'un mot dans un dictionnaire
 * \param dictionary dictionnaire qui reçoit le mot
 * \param linkWord mot à ajouter dans le dictionnaire
 * \return Pas de valeur de retour
 * 
 * Cette fonction insère un mot (structure mot_t) dans un dictionnaire qui prend la forme d'un Arbre Binaire de Recherche de mot_t 
 * (type dico).
*/
void insertDico(dico** dictionary, mot_t* linkWord);

/**
 * \fn void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne)
 * \brief Fonction de création d'une structure de mot à partir de données sur son contenu et sa position dans un texte
 * \param dictionary dictionnaire qui reçoit le mot
 * \param word chaîne de caractère associée au contenu du mot
 * \param line entier associé à la ligne où se trouve le mot dans le texte
 * \param colonne entier associé à la colonne où se trouve le mot dans le texte
 * \return Pas de valeur de retour
 * 
 * Cette fonction crée une structure mot_t à partir d'une chaîne de caractères (contenu du mot) et de deux entiers
 * (numéros de ligne et de colonne où se trouve le mot), puis l'insère dans un dictionnaire dico, en créant ce dictionnaire si le 
 * pointeur est nul ou en appelant insertDico sinon.
*/
void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne);

#endif