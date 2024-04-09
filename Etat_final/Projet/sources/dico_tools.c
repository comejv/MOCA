#include "dico_tools.h"
#include "macro.h"

void insertDico(dico **dictionary, mot_t *linkWord)
{
    int val_compare;
    if (dictionary == NULL)
    {
        ERROR(NULLPOINTER, "Erreur : Le dictionnaire fourni à insertDico est un pointeur nul\n");
    }

    if (linkWord == NULL)
    {
        ERROR(NULLPOINTER, "Erreur : Le mot fourni à insertDico est un pointeur nul\n");
    }

    dico *newDictionary = *dictionary;
    DEBUG(DICO, "mot à ajouter : %s\n", linkWord->data.lemot);

    if (newDictionary == NULL)
    {
        DEBUG(DICO, "noeud courant vide\n");
        DEBUG(DICO, "Insertion dans le noeud courant\n");
        newDictionary = (dico *) malloc(sizeof(dico));
        if (newDictionary == NULL)
        {
            ERROR(MALLOCFAIL, "Erreur : L'allocation de newDictionary a échoué\n");
        }
        newDictionary->mot = linkWord;
        newDictionary->fg = newDictionary->fd = NULL;
        *dictionary = newDictionary;
    }
    else
    {
        val_compare = compareWord(&(newDictionary->mot->data), &(linkWord->data));

        if (val_compare > 0)
        {
            DEBUG(DICO, "mot du noeud courant : %s\n", newDictionary->mot->data.lemot);
            DEBUG(DICO, "Insertion en sous arbre gauche\n");
            insertDico(&(newDictionary->fg), linkWord);
        }
        else if (val_compare < 0)
        {
            DEBUG(DICO, "mot du noeud courant : %s\n", newDictionary->mot->data.lemot);
            DEBUG(DICO, "Insertion en sous arbre droit\n");
            insertDico(&(newDictionary->fd), linkWord);
        }
        else
        {
            DEBUG(DICO, "noeud courant identique\n");
            DEBUG(DICO, "Insertion dans le noeud courant\n");
            incWord(newDictionary->mot->data.queue_liste, linkWord->data.tete_liste->line, linkWord->data.tete_liste->colonne);
            freeMot(linkWord);
            newDictionary->mot->data.queue_liste = newDictionary->mot->data.queue_liste->next;
        }
    }
}

void addToDico(dico **dictionary, char *word, unsigned int *line, unsigned int *colonne)
{
    if (dictionary == NULL)
    {
        ERROR(NULLPOINTER, "Erreur : Le dictionnaire fourni à addToDico est un pointeur nul\n");
    }

    mot_t *newLinkWord = (mot_t *) malloc(sizeof(mot_t));
    if (newLinkWord == NULL)
    {
        ERROR(MALLOCFAIL, "Erreur : L'allocation de newLinkWord a échoué\n");
    }
    emplacement_t *location = (emplacement_t *) malloc(sizeof(emplacement_t));
    if (location == NULL)
    {
        free(newLinkWord);
        ERROR(MALLOCFAIL, "Erreur : L'allocation de location a échoué\n");
    }
    else
    {
        location->next = NULL;
    }
    strcpy(newLinkWord->data.lemot, word);
    newLinkWord->lehash = hash(word);
    location->line = *line;
    location->colonne = *colonne;
    newLinkWord->data.tete_liste = location;
    newLinkWord->data.queue_liste = location;
    if (*dictionary == NULL)
    {
        dico *newDictionary = (dico *) malloc(sizeof(dico));
        if (newDictionary == NULL)
        {
            freeMot(newLinkWord);
            ERROR(MALLOCFAIL, "Erreur : l'allocation de newDictionary a échoué\n");
        }
        newDictionary->mot = newLinkWord;
        newDictionary->fg = newDictionary->fd = NULL;
        *dictionary = newDictionary;
    }
    else if ((*dictionary)->mot == NULL)
    {
        (*dictionary)->mot = newLinkWord;
    }
    else
    {
        insertDico(dictionary, newLinkWord);
    }
}
