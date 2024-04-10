#include "dico_tools.h"
#include "display.h"
#include "free.h"
#include "macro.h"
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
        ERROR(FILEOPENFAIL, "Erreur d'ouverture du fichier %s\n", nom);
    }
    unsigned int *line = (unsigned int *) malloc(sizeof(int));
    if (line == NULL)
    {
        ERROR(MALLOCFAIL, "Erreur : L'allocation de line a échoué \n");
    }
    unsigned int *colonne = (unsigned int *) malloc(sizeof(int));
    if (colonne == NULL)
    {
        free(line);
        ERROR(MALLOCFAIL, "Erreur : L'allocation de colonne a échoué \n");
    }
    char *word = NULL;
    dico *dictionary = (dico *) malloc(sizeof(dico));
    if (dictionary == NULL)
    {
        free(line);
        free(colonne);
        ERROR(MALLOCFAIL, "Erreur : L'allocation de dictionary a échoué \n");
    }
    else
    {
        dictionary->mot = NULL;
        dictionary->fg = NULL;
        dictionary->fd = NULL;
    }

    dico *copiedico = NULL;

    mot_data_t **serialized_dico = (mot_data_t **) calloc(MaxSizeArray, sizeof(mot_data_t *));
    if (serialized_dico == NULL)
    {
        ERROR(MALLOCFAIL, "Erreur : L'allocation de serialized_dico a échoué \n");
    }

    while (!feof(f))
    {
        word = next_word(f, line, colonne);
        addToDico(&dictionary, word, line, colonne);
        free(word);
    }
    printf("1-----Affichage du dictionnaire une fois rempli-----\n");
    displayDico(dictionary, nom);
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

    // Stratégie de libération des blocs mémoire

    // Les noeuds (dico *) de dictionary et copiedico correspondent à des adresses différentes (parce qu'on malloc les noeuds dans deserializeDico pour
    // construire copiedico), mais les structures de mots que ces dictionnaires contiennent sont associées aux mêmes pointeurs (car dans deserializeDico,
    // on relie les noeuds de copiedico aux pointeurs de mot_data_t contenus dans la table serialized_dico) !

    // En fin de programme, on a donc l'ensemble des structures de mot_data_t (utilisées à la fois par dictionary et par copiedico)
    // contenu dans serialized_dico, tandis que les pointeurs associés aux noeuds de dictionary et copiedico sont différents.

    // Il faut donc libérer d'abord les structures de mot_data_t de serialized_dico afin de libérer les chaînes d'emplacements contenues à la fois
    // dans dictionary et copiedico, puis libérer les structures de mot_t et les noeuds des deux dictionnaires.

    // Libération des structures de mot_data_t communes aux deux dictionnaires (et leurs chaînes d'emplacements allouées)
    freeMotData(serialized_dico);

    // Les emplacements de mots ont été libérés dans les deux dictionnaires à la fois, il ne reste qu'à libérer les structures de mot_t et les noeuds
    // séparément
    freeDico(dictionary);
    freeDico(copiedico);

    fclose(f);
    return 0;
}
