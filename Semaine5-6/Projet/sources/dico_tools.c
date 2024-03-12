#include "dico_tools.h"

void insertDico(dico** dictionary, mot_t* linkWord) {
  if (dictionary == NULL) {
    fprintf(stderr, "Erreur : Le dictionnaire fourni à insertDico est un pointeur nul\n");
    exit(1);
  }

  if (linkWord == NULL) {
    fprintf(stderr, "Erreur : Le mot fourni à insertDico est un pointeur nul\n");
    exit(1);
  }

  dico* newDictionary = *dictionary;
  DEBUG(DICO, "mot à ajouter : %s\n", linkWord->data.lemot);


  if (newDictionary == NULL) {
    DEBUG(DICO, "noeud courant vide\n");
    DEBUG(DICO, "Insertion dans le noeud courant\n");
    newDictionary = (dico*) malloc(sizeof(dico));
    if (newDictionary == NULL) {
      fprintf(stderr, "Erreur : L'allocation a échoué \n");
      exit(1);
    }
    newDictionary->mot = linkWord;
    newDictionary->fg = newDictionary->fd = NULL;
    *dictionary = newDictionary;
  }

  else if (compareWord(&(newDictionary->mot->data),&(linkWord->data))>0) {
    DEBUG(DICO, "mot du noeud courant : %s\n", newDictionary->mot->data.lemot);
    DEBUG(DICO, "Insertion en sous arbre gauche\n");
    insertDico(&(newDictionary->fg),linkWord);
  }
  else if (compareWord(&(newDictionary->mot->data),&(linkWord->data))<0) {
    DEBUG(DICO, "mot du noeud courant : %s\n", newDictionary->mot->data.lemot);
    DEBUG(DICO, "Insertion en sous arbre droit\n");
    insertDico(&(newDictionary->fd),linkWord);
  }
  else { 
    DEBUG(DICO, "noeud courant identique\n");
    DEBUG(DICO, "Insertion dans le noeud courant\n");
    incWord(newDictionary->mot->data.queue_liste,linkWord->data.tete_liste->line,linkWord->data.tete_liste->colonne);
    newDictionary->mot->data.queue_liste = newDictionary->mot->data.queue_liste->next;
  }
}

void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne) {
  if (dictionary == NULL) {
    fprintf(stderr, "Erreur : Le dictionnaire fourni à addToDico est un pointeur nul\n");
    exit(1);
  }
  
  mot_t* newLinkWord = (mot_t*) malloc(sizeof(mot_t));
  if (newLinkWord == NULL) {
      fprintf(stderr, "Erreur : L'allocation a échoué \n");
      exit(1);
  }
  emplacement_t* location = (emplacement_t*) malloc(sizeof(emplacement_t));
  if (location == NULL) {
      fprintf(stderr, "Erreur : L'allocation a échoué \n");
      exit(1);
  } else {
      location->next = NULL;
  }   
  strcpy(newLinkWord->data.lemot, word);
  newLinkWord->lehash = hash(word);
  location->line = *line;
  location->colonne = *colonne;
  newLinkWord->data.tete_liste = location;
  newLinkWord->data.queue_liste = location;
  if(*dictionary==NULL) {
    dico* newDictionary = (dico*) malloc(sizeof(dico));
    if (newDictionary == NULL) {
      fprintf(stderr, "Erreur : L'allocation a échoué \n");
      exit(1);
    } 
    newDictionary->mot = newLinkWord;
    newDictionary->fg = newDictionary->fd = NULL;
    *dictionary = newDictionary;
  } else if ((*dictionary)->mot == NULL) {
    (*dictionary)->mot = newLinkWord;
  } else {
    insertDico(dictionary,newLinkWord);
  }
}