#ifndef WORD_TOOLS_H
#define WORD_TOOLS_H

/**
 * \file word_tools.h
 * \brief Outils de manipulation de structures de mots
*/

#include <stdlib.h>
#include <string.h>
#include "structures.h"

/**
 * \def SEP
 * \brief Liste des caractères identifiés comme des séparateurs de mots dans le texte
*/
#define SEP " ,.-'"

/**
 * \fn char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol)
 * \brief Fonction de récupération d'un mot dans le texte d'origine
 * \param f le fichier contenant le texte d'origine
 * \param nblin l'indice de ligne actuel dans le texte, modifié par l'indice de ligne du mot si il est trouvé
 * \param nbcol l'indice de colonne actuel dans le texte, modifié par l'indice de colonne du mot si il est trouvé
 * \return Le mot lu dans le texte
 * 
 * Cette fonction lit le prochain mot dans le texte d'origine contenu dans un fichier, et le renvoie.
*/
char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol);

/**
 * \fn int compareWord(mot_data_t* w1, mot_data_t* w2)
 * \brief Fonction de comparaison de deux mots
 * \param w1 la structure du premier mot
 * \param w2 la structure du second mot
 * \return Renvoie 1 si w1 est vide, si le caractère de position i dans w1 a un code ASCII strictement supérieur au caractère
 * \return de même position dans w2, ou si w1 est strictement plus long que w2
 * \return Renvoie -1 si w2 est vide, si le caractère de position i dans w1 a un code ASCII strictement inférieur au caractère
 * \return de même position dans w2, ou si w1 est strictement moins long que w2
 * \return Renvoie 0 si w1 et w2 décrivent le même mot
 * 
 * Cette fonction compare deux mots à partir de leur représentation textuelle (chaîne de caractères).
*/
int compareWord(mot_data_t* w1, mot_data_t* w2);

/**
 * \fn void incWord(emplacement_t* location, unsigned int line, unsigned int colonne)
 * \brief Fonction d'inclusion de l'emplacement d'un mot dans une séquence d'emplacements
 * \param location la liste chaînée d'emplacements où insérer le mot
 * \param line l'indice de ligne dans le texte du mot à ajouter 
 * \param colonne l'indice de colonne dans le texte du mot à ajouter
 * \note Pas de valeur de retour
 * 
 * Cette fonction insère l'emplacement d'un mot (ligne, colonne) dans une séquence d'emplacements sous forme de liste chaînée. 
 * Pour cela, elle parcourt la séquence d'emplacements et ajoute en queue le nouvel emplacement.
*/
void incWord(emplacement_t* location, unsigned int line, unsigned int colonne);

#endif