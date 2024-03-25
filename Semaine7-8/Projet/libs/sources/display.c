#include "display.h"
#include <stdlib.h>

void displayWord(mot_data_t *word, FILE *filedes)
{
    if (word == NULL)
    {
    }
    else
    {
        char *link = word->lemot;
        emplacement_t *list = word->tete_liste;
        if (link != NULL)
        {
            fprintf(filedes, "%s", link);
            fflush(stdout);
        }
        while (list != NULL)
        {
            fprintf(filedes, " (%i,%i)", list->line, list->colonne);
            list = list->next;
        }
        fprintf(filedes, "\n");
    }
}

void displayNodes(dico *d, FILE *f)
{
    if (d)
    {
        displayNodes(d->fg, f);
        displayWord(&(d->mot->data), f);
        displayNodes(d->fd, f);
    }
}

void displayDico(dico *dictionary)
{
    FILE *f = NULL;
    f = fopen(DICORES, "w+");
    if (f == NULL)
    {
        ERROR(FILEOPENFAIL, "Erreur d'ouverture du fichier %s\n", DICORES);
    }
    if (!feof(f))
        printf("Resultat existant dans le fichier resultat, on ecrase\n");
    if (dictionary == NULL)
    {
        ERROR(NULLPOINTER, "Le pointeur dictionary est NULL\n");
    }
    else
    {
        fprintf(f, "Contenu dictionnaire pour %s : \n", TEXTE);
        dico *tempDico = dictionary;
        displayNodes(tempDico, f);
        fflush(f);
    }
    fclose(f);
}
