#include "free.h"
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

void freeMotData(mot_data_t **mot_data)
{
    if (mot_data != NULL)
    {
        for (int i = 0; i < MaxSizeArray; i++)
        {
            if (mot_data[i] != NULL)
            {
                freeEmplacement(mot_data[i]->tete_liste);
            }
        }

        free(mot_data);
    }
}

void freeDico(dico *dico)
{
    if (dico != NULL)
    {
        freeDico(dico->fg);
        freeDico(dico->fd);
        free(dico->mot);
        free(dico);
    }
}
