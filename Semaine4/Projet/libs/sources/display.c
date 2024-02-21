#include "display.h"

void displayWord(mot_data_t *word, FILE *filedes) {
  if (word == NULL) {
  } else {
    char *link = word->lemot;
    emplacement_t *list = word->tete_liste;
    if (link != NULL) {
      fprintf(filedes, "%s", link);
      fflush(stdout);
    }
    while (list != NULL) {
      fprintf(filedes, " (%i,%i)\n", list->line, list->colonne);
      list = list->next;
    }
  }
}

void displayNodes(dico *d, FILE *f) {
  if (d) {
    displayNodes(d->fg, f);
    displayWord(&(d->mot->data), f);
    displayNodes(d->fd, f);
  }
}

void displayDico(dico *dictionary) {
  FILE *f = NULL;
  f = fopen(DICORES, "w+");
  if (f == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier %s\n", DICORES);
    exit(1);
  }
  if (!feof(f))
    printf("Resultat existant dans le fichier resultat, on ecrase\n");
  if (dictionary == NULL) {
    printf("displayDico : NULL\n");
  } else {
    fprintf(f, "Contenu dictionnaire pour %s : \n", TEXTE);
    dico *tempDico = (dico *)malloc(sizeof(dico));
    tempDico = dictionary;
    displayNodes(tempDico, f);
    fflush(f);
  }
}
