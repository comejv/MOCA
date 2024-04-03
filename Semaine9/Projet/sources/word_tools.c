#include "word_tools.h"
#include "macro.h"

char *separators = SEP;
unsigned int current_line = 1;
unsigned int current_col = 1;

int is_ascii(char c) {
    return ((c>='A' && c<='Z') || (c>='a' && c<='z'));
}

void skip_separators(FILE *f, char sep, unsigned int *startl, unsigned int *startc) {
    while (strchr(separators, sep) != NULL || sep == '\n' || !is_ascii(sep))
    {
        if (sep == '\n')
        {
            (*startl)++;
            *startc = 1;
        } else if (sep == EOF) {
            break;
        }
        sep = fgetc(f);
    }
    ungetc(sep, f);
}

char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol)
{
    char s[maxSizeWord+1];
    char *res;
    unsigned int i = 0, startl = current_line, startc = current_col;
    char sep, lu;
    sep = fgetc(f);
    skip_separators(f, sep, &startl, &startc);
    if (nblin != NULL)
        *nblin = startl;
    if (nbcol != NULL)
        *nbcol = startc;
    while ((strchr(separators, lu = fgetc(f)) == NULL) && lu != '\n' && is_ascii(lu))
    {
        if (i >= maxSizeWord) {
            ERROR(WORDTOOLONG, "Erreur : un mot du texte est trop long\n");
        } else {
            s[i++] = lu;
        }
    }
    startc++;
    sep = lu;
    s[i] = '\0';
    res = (char *) malloc(strlen(s) + 1);
    strcpy(res, s);
    skip_separators(f, sep, &startl, &startc);
    current_line = startl;
    current_col = startc;
    return res;
}

int compareWord(mot_data_t *w1, mot_data_t *w2)
{
    if (w1 == NULL)
    {
        return 1;
    }
    else if (w2 == NULL)
    {
        return -1;
    }
    else
    {
        char *word1 = w1->lemot;
        char *word2 = w2->lemot;
        size_t taille_word1 = strlen(word1);
        size_t taille_word2 = strlen(word2);
        int minSize = (taille_word1 < taille_word2) ? taille_word1 : taille_word2;
        int i = 0;
        int pos = 0;
        while (i < minSize && pos == 0)
        {
            pos = (word1[i] < word2[i]) ? -1 : (word1[i] > word2[i]) ? 1 : 0;
            i++;
        }
        return (pos == 0 && taille_word1 < taille_word2) ? -1 : (pos == 0 && taille_word1 > taille_word2) ? 1 : pos;
    }
}

void incWord(emplacement_t *location, unsigned int line, unsigned int colonne)
{
    if (location == NULL) {
        ERROR(NULLPOINTER, "Erreur : le pointeur location est nul\n");
    }
    
    emplacement_t *newLocation = (emplacement_t *) malloc(sizeof(emplacement_t));
    if (newLocation == NULL) {
        ERROR(MALLOCFAIL, "Erreur : l'allocation de newLocation a échoué\n");
    }

    newLocation->next = NULL;
    newLocation->line = line;
    newLocation->colonne = colonne;
    location->next = newLocation;
}
