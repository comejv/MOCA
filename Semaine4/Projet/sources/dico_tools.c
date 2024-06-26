#include "dico_tools.h"

void insertDico(dico** dictionary, mot_t* linkWord) {
  dico* newDictionary = (dico*) malloc(sizeof(dico));
  newDictionary = *dictionary;
  while(newDictionary != NULL && compareWord(&(newDictionary->mot->data),&(linkWord->data))>0) {
    *dictionary = newDictionary;
    insertDico(&(newDictionary->fg),linkWord);
    return;
  }
  while(newDictionary != NULL && compareWord(&(newDictionary->mot->data),&(linkWord->data))<0) {
    *dictionary = newDictionary;
    insertDico(&(newDictionary->fd),linkWord);
    return;
  }
  if (newDictionary != NULL && compareWord(&(newDictionary->mot->data),&(linkWord->data))==0) { 
    incWord(newDictionary->mot->data.queue_liste,linkWord->data.tete_liste->line,linkWord->data.tete_liste->colonne);
  }
  else { 
    newDictionary = (dico*) malloc(sizeof(dico));
    newDictionary->mot = linkWord;
    newDictionary->fg = newDictionary->fd = NULL;
    *dictionary = newDictionary;
  }
}

void addToDico(dico** dictionary, char* word, unsigned int* line, unsigned int* colonne) {
  mot_t* newLinkWord = (mot_t*) malloc(sizeof(mot_t));
  emplacement_t* location = (emplacement_t*) malloc(sizeof(emplacement_t));
  strcpy(newLinkWord->data.lemot, word);
  newLinkWord->lehash = hash(word);
  location->line = *line;
  location -> colonne = *colonne;
  newLinkWord->data.tete_liste = location;
  newLinkWord->data.queue_liste = location;
  if(*dictionary==NULL) {
    dico* newDictionary = (dico*) malloc(sizeof(dico));
    newDictionary->mot = newLinkWord;
    newDictionary->fg = newDictionary->fd = NULL;
    *dictionary = newDictionary;
  } else if ((*dictionary)->mot == NULL) {
    (*dictionary)->mot = newLinkWord;
  } else {
    insertDico(dictionary,newLinkWord);
  }
}