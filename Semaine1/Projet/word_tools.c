#include <stdio.h>
#include "word_tools.h"
#include "structures.h"  

char *next_word(FILE *f, unsigned int *nblin, unsigned int *nbcol){
  char s[100]; 
  char *res; 
  char *separators=SEP;
  unsigned int current_line=1;
  unsigned int current_col=1;
  unsigned int i=0, startl = current_line, startc = current_col;
  char sep;
  sep = fgetc(f);
  while (strchr(separators,sep) != NULL  || sep == '\n') { 
    startc++;
    if (sep == '\n'){ 
      startl++; startc = 1;
    } 
    sep = fgetc(f);
  } 
  ungetc(sep,f);
  if (nblin != NULL) *nblin = startl;  
  if (nbcol != NULL) *nbcol = startc;
  while ((strchr(separators, s[i]=fgetc(f)) == NULL) && s[i] != '\n'){
    i++; startc++;
  }
  sep = s[i]; 
  s[i] = '\0';
  res = (char *)malloc(strlen(s)+1); 
  strcpy(res,s);
  while (strchr(separators,sep) != NULL  || sep == '\n') { 
    startc++;
    if (sep == '\n'){  
      startl++; startc = 1;
    } 
    sep = fgetc(f);
  } 
  ungetc(sep,f);
  current_line = startl;
  current_col = startc;
  return res;
}

int compareWord(mot_data_t* w1, mot_data_t* w2) {
  if (w1 == NULL) {
    return 1;
  } else if (w2 == NULL) {
    return -1;
  } else {
    char* word1 = w1->lemot;   
    char* word2 = w2->lemot;
    int minSize = (strlen(word1)<strlen(word2))?strlen(word1):strlen(word2);
    int i= 0;
    int pos = 0;
    while(i<minSize && pos == 0) {
      pos = (word1[i]<word2[i])?-1:(word1[i]>word2[i])?1:0;
      i++;
    }
    return (pos == 0 && strlen(word1) < strlen(word2))?-1:(pos == 0 && strlen(word1) > strlen(word2))?1:pos;
  }
}

void incWord(emplacement_t* location, unsigned int line, unsigned int colonne) {
  emplacement_t* newLocation = (emplacement_t*) malloc(sizeof(emplacement_t));
  emplacement_t* tempLocation = (emplacement_t*) malloc(sizeof(emplacement_t));
  tempLocation = location;
  newLocation->next = NULL;
  newLocation->line = line;
  newLocation->colonne = colonne;
  while(tempLocation->next != NULL) {
    tempLocation = tempLocation->next;
  }
  tempLocation->next = newLocation;
}