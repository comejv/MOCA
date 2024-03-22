#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * \file display.h
 * \brief Fonctions d'affichage d'objets (mot, dictionnaire)
*/

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

#define DICORES "resultats/dictionnaires.txt"
#define TEXTE "exemples/hugo1.txt"

/**
 * \fn void displayWord(mot_data_t* word, FILE *filedes)
 * \brief Fonction d'écriture du contenu d'une structure de mot dans un fichier
 * \param word la structure de mot (sans hash)
 * \param filedes le fichier de destination
 * \note Pas de valeur de retour
 * 
 * Cette fonction écrit le contenu d'une structure de mot (mot_data_t) dans un fichier : contenu du mot, ainsi que tous les couples
 * (ligne, colonne) où le mot apparaît dans le texte.
*/
void displayWord(mot_data_t* word, FILE *filedes);

/**
 * \fn void displayNodes(dico *d, FILE* f)
 * \brief Fonction d'écriture du contenu d'une structure de dictionnaire (ABR) dans un fichier
 * \param d la structure de dictionnaire (ABR) à afficher
 * \param f le fichier de destination
 * \note Pas de valeur de retour
 * 
 * Cette fonction écrit le contenu d'une structure de dictionnaire (ABR) en procédant par un parcours en profondeur infixe.
*/
void displayNodes(dico *d, FILE* f);

/**
 * \fn void displayDico(dico* dictionary)
 * \brief Fonction de gestion d'un fichier pour y écrire le contenu d'une structure de dictionnaire
 * \param dictionary la structure de dictionnaire (ABR) à afficher
 * \note Pas de valeur de retour
 * 
 * Cette fonction gère l'ouverture d'un fichier et les potentielles erreurs associées dans le but d'y écrire le contenu d'une structure
 * de dictionnaire, avant d'appeler la fonction displayNodes.
*/
void displayDico(dico* dictionary);



#endif