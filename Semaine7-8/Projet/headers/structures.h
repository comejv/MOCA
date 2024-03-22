#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * \file structures.h
 * \brief Structures de données décrivant les objets manipulés
*/

#define maxSizeWord 25

typedef struct emplacement_t emplacement_t;
/**
 * \struct emplacement_t 
 * \brief Structure de liste chaînée décrivant une séquence d'emplacements
 * 
 * Liste chaînée contenant les positions successives (ligne, colonne) de plusieurs occurrences d'un même mot dans le texte.
*/
struct emplacement_t {
  unsigned int line;
  unsigned int colonne;
  emplacement_t* next;
};

typedef struct mot_data_t mot_data_t;
/**
 * \struct mot_data_t 
 * \brief Structure de données décrivant un mot
 * 
 * Structure contenant le contenu d'un mot, ainsi qu'une liste des positions successives de ce mot dans le texte (repérée par un pointeur
 * de début et un pointeur de fin).
*/
struct mot_data_t {
  char lemot[maxSizeWord];    /*!< Contenu du mot */
  emplacement_t* tete_liste;  /*!< Pointeur de début de la liste des emplacements de ce mot dans le texte */
  emplacement_t* queue_liste; /*!< Pointeur de fin de la liste des emplacements de ce mot dans le texte */
};

typedef struct mot_t mot_t;
/**
 * \struct mot_t 
 * \brief Structure de noeud de l'ABR associée à un mot
 * 
 * Noeud de l'arbre binaire de recherche, contenant le hashcode d'un mot, ainsi qu'une structure de données décrivant ce mot.
*/
struct mot_t {
  int lehash;
  mot_data_t data;
};

typedef struct dico dico;
/**
 * \struct dico
 * \brief Structure d'arbre binaire de recherche (ABR)
 * 
 * Arbre binaire de recherche servant de dictionnaire, dans lequel on place les mots lus dans le texte.
*/
struct dico {
  mot_t* mot;    /*!< Noeud de l'ABR */
  dico *fg, *fd; /*!< Fils gauche et droit */
};

#endif