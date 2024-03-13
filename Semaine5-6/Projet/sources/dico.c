#include "dico_tools.h"
#include "display.h"
#include "free.h"
#include "serialization.h"
#include "structures.h"
#include "word_tools.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *f = NULL;
    int i;
    char *nom;

    if (argc == 1)
    {
        f = fopen(TEXTE, "r");
        nom = TEXTE;
    }
    else if (argc == 2)
    {
        f = fopen(argv[1], "r");
        nom = argv[1];
    }
    else
    {
        fprintf(stderr, "Erreur : nombre d'arguments incorrect\n");
        fprintf(stderr, "Usage : %s ou %s [nom_fichier]\n", argv[0], argv[0]);
        return 1;
    }
    if (f == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom);
        return 2;
    }
    unsigned int *line = (unsigned int *)malloc(sizeof(int));
    if (line == NULL)
    {
        fprintf(stderr, "Erreur : L'allocation a échoué \n");
        return 1;
    }
    unsigned int *colonne = (unsigned int *)malloc(sizeof(int));
    if (colonne == NULL)
    {
        fprintf(stderr, "Erreur : L'allocation a échoué \n");
        free(line);
        return 1;
    }
    char *word = NULL;
    dico *dictionary = (dico *)malloc(sizeof(dico));
    if (dictionary == NULL)
    {
        fprintf(stderr, "Erreur : L'allocation a échoué \n");
        free(line);
        free(colonne);
        return 1;
    }
    else
    {
        dictionary->mot = NULL;
        dictionary->fg = NULL;
        dictionary->fd = NULL;
    }

    dico *copiedico = NULL;

    mot_data_t **serialized_dico = (mot_data_t **)calloc(MaxSizeArray, sizeof(mot_data_t *));
    if (serialized_dico == NULL)
    {
        fprintf(stderr, "Erreur : L'allocation a échoué \n");
        return 1;
    }

    while (!feof(f))
    {
        word = next_word(f, line, colonne);
        addToDico(&dictionary, word, line, colonne);
        free(word);
    }
    printf("1-----Affichage du dictionnaire une fois rempli-----\n");
    displayDico(dictionary);
    serializeDico(dictionary, serialized_dico);
    printf("\n2-----Affichage de la table de mots après sérialisation-----\n");
    for (i = 0; i < MaxSizeArray; i++)
        if (serialized_dico[i] != NULL)
        {
            printf("Index %d -> ", i);
            displayWord(serialized_dico[i], stdout);
        }

    free(line);
    free(colonne);

    /*
    struct json_object *o;
    o = createJSON(serialized_dico);
    FILE *fic = fopen("monfic.json","w");
    fprintf(fic, "%s\n",
            json_object_to_json_string_ext(o,JSON_C_TO_STRING_PRETTY));
    fclose(fic);
    */
    for (i = 0; i < MaxSizeArray; i++)
        if (serialized_dico[i] != NULL)
        {
            deserializeDico(&copiedico, serialized_dico[i]);
        }
    printf("\n3-----Affichage des noeuds du dictionnaire après "
           "désérialisation-----\n");
    displayNodes(copiedico, stdout);
    free(serialized_dico);
    freeDico(dictionary);
    fclose(f);
    return 0;
}
