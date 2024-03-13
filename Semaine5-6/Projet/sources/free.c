#include "structures.h"
#include <stdlib.h>

void freeEmplacement(emplacement_t *emplacement)
{
    if (emplacement != NULL)
    {
        freeEmplacement(emplacement->next);
        free(emplacement);
    }
}

void freeMot(mot_t *mot)
{
    if (mot != NULL)
    {
        freeEmplacement(mot->data.tete_liste);
        free(mot);
    }
}

void freeDico(dico *dico)
{
    if (dico != NULL)
    {
        freeDico(dico->fg);
        freeDico(dico->fd);
        freeMot(dico->mot);
        free(dico);
    }
}
