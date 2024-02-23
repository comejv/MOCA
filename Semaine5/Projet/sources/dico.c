#include "dico_tools.h"
#include "display.h"
#include "serialization.h"
#include "structures.h"
#include "word_tools.h"

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
    unsigned int *colonne = (unsigned int *)malloc(sizeof(int));
    char *word = (char *)malloc(sizeof(char) * maxSizeWord);
    dico *dictionary = (dico *)malloc(sizeof(dico));
    dico *copiedico = NULL;
    mot_data_t **serialized_dico =
        (mot_data_t **)malloc(MaxSizeArray * sizeof(mot_data_t *));
    while (!feof(f))
    {
        word = next_word(f, line, colonne);
        addToDico(&dictionary, word, line, colonne);
    }
    printf("1-----Affichage du dictionnaire une fois rempli-----\n");
    displayDico(dictionary);
    for (i = 0; i < MaxSizeArray; i++)
        serialized_dico[i] = NULL;
    serializeDico(dictionary, serialized_dico);
    printf("\n2-----Affichage de la table de mots après sérialisation-----\n");
    for (i = 0; i < MaxSizeArray; i++)
        if (serialized_dico[i] != NULL)
        {
            printf("Index %d -> ", i);
            displayWord(serialized_dico[i], stdout);
        }
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
    fclose(f);
    return 0;
}
