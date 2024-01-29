#ifndef STRUCTURES_H
#define STRUCTURES_H

#define maxSizeWord 25

typedef struct emplacement_t emplacement_t;
struct emplacement_t {
  unsigned int line;
  unsigned int colonne;
  emplacement_t* next;
};

typedef struct mot_data_t mot_data_t;
struct mot_data_t {
  char lemot[maxSizeWord];
  emplacement_t* tete_liste;
  emplacement_t* queue_liste;
};

typedef struct mot_t mot_t;
struct mot_t {
  int lehash;
  mot_data_t data;
};

typedef struct dico dico;
struct dico {
  mot_t* mot;
  dico *fg, *fd;
};

#endif