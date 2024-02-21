#include "serialization.h"

/*
struct json_object *createJSON(mot_data_t **d){
  int i;
  json_object *r = json_object_new_object();
  json_object *t = json_object_new_array_ext(MaxSizeArray);
  for(i=0; i<MaxSizeArray; i++) {
    if (d[i] != NULL) {
      int j=0;
      struct json_object *newelem = json_object_new_object();
      char* mot = d[i]->lemot;   
      emplacement_t* list = d[i]->tete_liste;
      json_object *l = json_object_new_array();
      json_object_object_add(newelem, "index", json_object_new_int(i));
      json_object_object_add(newelem, "mot", json_object_new_string(mot));
      while(list != NULL) {
	struct json_object *paire = json_object_new_object();
	json_object_object_add(paire,"ligne",json_object_new_int(list->line));
	json_object_object_add(paire,"colonne",json_object_new_int(list->colonne));
	json_object_array_put_idx(l,j,paire);
	j++;
	list = list->next;
      }
      json_object_object_add(newelem, "liste", l);
      json_object_array_add(t,newelem); 
    }
  }
  json_object_object_add(r,"dico",t);
  return r;
}
*/

int hash(char *m) {
  uint64_t h;
  DEBUG(HASH, "mot : %s\n", m);
  DEBUG(HASH, "longueur : %ld\n", strlen(m));
  int l = strlen(m);
  int i;
  h = 0;
  for(i=0; i<l; i++) {
    h = h + (uint64_t) (m[i]*powl((long double) 127, (long double) l-i-1));
  }
  DEBUG(HASH, "hash pre-modulo : %ld\n", h);
  h = h % MaxSizeArray;
  DEBUG(HASH, "hash post modulo : %ld\n", h);
  return h;
}

void deserializeDico(dico** dic, mot_data_t *elt) {
  dico *temp = NULL;
  mot_t* newLinkWord = (mot_t*) malloc(sizeof(mot_t));
  newLinkWord->lehash = hash(elt->lemot);
  newLinkWord->data = *elt;
  if((*dic)==NULL) {
    temp = (dico *)malloc(sizeof(dico));
    temp->fg = temp->fd = NULL;
    temp->mot = newLinkWord;
    *dic = temp;
    return;
  }
  if (compareWord(&((*dic)->mot->data), elt)>0) {   
    deserializeDico(&(*dic)->fg, elt);
  }
  else
    deserializeDico(&(*dic)->fd, elt);
}

void serializeDico(dico * dictionary, mot_data_t **table) {
  if (dictionary) {
    serializeDico(dictionary->fg, table);
    table[abs(dictionary->mot->lehash)] = &(dictionary->mot->data); 
    serializeDico(dictionary->fd, table);
  }
}