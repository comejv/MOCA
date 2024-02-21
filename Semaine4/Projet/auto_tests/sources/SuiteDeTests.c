#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "CuTest.h"
#include "structures.h"
#include "word_tools.h"
#include "serialization.h"

#define MAX_MSG_LEN 50

void test_compareWord(CuTest * tc) {
  mot_data_t *w1;
  mot_data_t* w2;
  w1 = (mot_data_t*) malloc(sizeof(mot_data_t));
  w2 = (mot_data_t*) malloc(sizeof(mot_data_t));

  strcpy(w1->lemot, "mot");
  strcpy(w2->lemot, "mot");
  CuAssertIntEquals(tc, 1, compareWord(NULL, w1));
  CuAssertIntEquals(tc, -1, compareWord(w1, NULL));
  CuAssertIntEquals(tc, 0, compareWord(w1, w2));

  strcpy(w1->lemot, "avec");
  strcpy(w2->lemot, "bonjour");
  CuAssertIntEquals(tc, -1, compareWord(w1, w2));
  CuAssertIntEquals(tc, 1, compareWord(w2, w1));

  strcpy(w1->lemot, "abcd");
  strcpy(w2->lemot, "abce");
  CuAssertIntEquals(tc, -1, compareWord(w1, w2));
  CuAssertIntEquals(tc, 1, compareWord(w2, w1));

  strcpy(w1->lemot, "aaa");
  strcpy(w2->lemot, "aaaaa");
  CuAssertIntEquals(tc, -1, compareWord(w1, w2));
  CuAssertIntEquals(tc, 1, compareWord(w2, w1));

  strcpy(w1->lemot, "aaa");
  strcpy(w2->lemot, "aaab");
  CuAssertIntEquals(tc, -1, compareWord(w1, w2));
  CuAssertIntEquals(tc, 1, compareWord(w2, w1));

  // strcpy(w1->lemot, "");
  // strcpy(w2->lemot, "mot");
  // CuAssertIntEquals(tc, 0, compareWord(w1, w1));
  // CuAssertIntEquals(tc, -1, compareWord(w2, w1));
  // CuAssertIntEquals(tc, 1, compareWord(w1, w2));

  // strcpy(w1->lemot, " ");
  // strcpy(w2->lemot, "mot");
  // CuAssertIntEquals(tc, 0, compareWord(w1, w1));
  // CuAssertIntEquals(tc, 1, compareWord(w1, w2));
  // CuAssertIntEquals(tc, -1, compareWord(w2, w1));
}

void test_hash(CuTest *tc) {
  // tester des cas simples (pas d'overflow)
  CuAssertIntEquals(tc, 13563, hash("je"));
  CuAssertIntEquals(tc, 14071, hash("ne"));
  CuAssertIntEquals(tc, 11768, hash("laisserai"));
  CuAssertIntEquals(tc, 591, hash("pas"));
  CuAssertIntEquals(tc, 14706, hash("se"));
  CuAssertIntEquals(tc, 136, hash("faner"));
  CuAssertIntEquals(tc, 2107, hash("les"));
  CuAssertIntEquals(tc, 16079, hash("pervenches"));
  CuAssertIntEquals(tc, 11287, hash("sans"));
  CuAssertIntEquals(tc, 2697, hash("aller"));
  CuAssertIntEquals(tc, 14537, hash("ecouter"));
  CuAssertIntEquals(tc, 12674, hash("ce"));
  CuAssertIntEquals(tc, 14468, hash("qu"));
  CuAssertIntEquals(tc, 14207, hash("on"));
  CuAssertIntEquals(tc, 4632, hash("dit"));
  CuAssertIntEquals(tc, 8648, hash("sous"));
  CuAssertIntEquals(tc, 7083, hash("branches"));
}

void free_dico(dico *dict) {
  if (dict) {
    free_dico(dict->fg);
    free_dico(dict->fd);
    free(dict->mot);
    free(dict);
  }
}

void test_serializeDico(CuTest *tc) {
  dico *main_dico;
  mot_data_t **table = (mot_data_t **) malloc(MaxSizeArray*sizeof(mot_data_t *));

  // construction d'un ABR exemple (dictionnaire) noeud par noeud
  dico *dico_bonjour = (dico *) malloc(sizeof(dico));
  dico_bonjour->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_bonjour->mot->data.lemot, "bonjour");
  dico_bonjour->mot->lehash = hash("bonjour");

  dico *dico_a = (dico *) malloc(sizeof(dico));
  dico_a->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_a->mot->data.lemot, "a");
  dico_a->mot->lehash = hash("a");

  dico *dico_ceci = (dico *) malloc(sizeof(dico));
  dico_ceci->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_ceci->mot->data.lemot, "ceci");
  dico_ceci->mot->lehash = hash("ceci");

  dico *dico_de = (dico *) malloc(sizeof(dico));
  dico_de->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_de->mot->data.lemot, "de");
  dico_de->mot->lehash = hash("de");

  dico *dico_test = (dico *) malloc(sizeof(dico));
  dico_test->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_test->mot->data.lemot, "test");
  dico_test->mot->lehash = hash("test");

  dico *dico_serialisation = (dico *) malloc(sizeof(dico));
  dico_serialisation->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_serialisation->mot->data.lemot, "serialisation");
  dico_serialisation->mot->lehash = hash("serialisation");

  dico *dico_tous = (dico *) malloc(sizeof(dico));
  dico_tous->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_tous->mot->data.lemot, "tous");
  dico_tous->mot->lehash = hash("tous");

  dico *dico_un = (dico *) malloc(sizeof(dico));
  dico_un->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_un->mot->data.lemot, "un");
  dico_un->mot->lehash = hash("un");

  dico *dico_est = (dico *) malloc(sizeof(dico));
  dico_est->mot = (mot_t *) malloc(sizeof(mot_t));
  strcpy(dico_est->mot->data.lemot, "est");
  dico_est->mot->lehash = hash("est");

  // assemblage des noeuds
  // schéma : 
  /*         test
           /      \
    bonjour          test
   /       \       /        \
  a        de serialisation  tous
          /                     \
        ceci                     un
  */

  dico_ceci->fg = dico_ceci->fd = NULL;
  dico_de->fg = dico_ceci;
  dico_de->fd = NULL;
  dico_a->fg = dico_a->fd = NULL;
  dico_bonjour->fg = dico_a;
  dico_bonjour->fd = dico_de;

  dico_un->fg = dico_un->fd = NULL;
  dico_tous->fg = NULL;
  dico_tous->fd = dico_un;
  dico_serialisation->fg = dico_serialisation->fd = NULL;
  dico_test->fg = dico_serialisation;
  dico_test->fd = dico_tous;

  dico_est->fg = dico_bonjour;
  dico_est->fd = dico_test;
  main_dico = dico_est;

  // sérialisation du dictionnaire dans une table de mots
  serializeDico(main_dico, table);

  // vérification des pointeurs de la table
  CuAssertPtrEquals(tc, &dico_a->mot->data, table[hash("a")]);
  CuAssertPtrEquals(tc, &dico_bonjour->mot->data, table[hash("bonjour")]);
  CuAssertPtrEquals(tc, &dico_ceci->mot->data, table[hash("ceci")]);
  CuAssertPtrEquals(tc, &dico_de->mot->data, table[hash("de")]);
  CuAssertPtrEquals(tc, &dico_est->mot->data, table[hash("est")]);
  CuAssertPtrEquals(tc, &dico_serialisation->mot->data, table[hash("serialisation")]);
  CuAssertPtrEquals(tc, &dico_test->mot->data, table[hash("test")]);
  CuAssertPtrEquals(tc, &dico_tous->mot->data, table[hash("tous")]);
  CuAssertPtrEquals(tc, &dico_un->mot->data, table[hash("un")]);

  free_dico(main_dico);
}

void test_deserializeDico(CuTest *tc) {
  dico **dictionary = (dico **) malloc(sizeof(dico *));
  *dictionary = NULL;
  mot_data_t **table = (mot_data_t **) calloc(MaxSizeArray, sizeof(mot_data_t *));

  // construction d'une table de mots exemple, mot par mot
  mot_data_t *mot_bonjour = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_bonjour->lemot, "bonjour");
  table[hash("bonjour")] = mot_bonjour;

  mot_data_t *mot_a = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_a->lemot, "a");
  table[hash("a")] = mot_a;

  mot_data_t *mot_tous = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_tous->lemot, "tous");
  table[hash("tous")] = mot_tous;

  mot_data_t *mot_ceci = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_ceci->lemot, "ceci");
  table[hash("ceci")] = mot_ceci;

  mot_data_t *mot_est = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_est->lemot, "est");
  table[hash("est")] = mot_est;

  mot_data_t *mot_un = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_un->lemot, "un");
  table[hash("un")] = mot_un;

  mot_data_t *mot_test = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_test->lemot, "test");
  table[hash("test")] = mot_test;

  mot_data_t *mot_de = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_de->lemot, "de");
  table[hash("de")] = mot_de;

  mot_data_t *mot_deserialisation = (mot_data_t *) malloc(sizeof(mot_data_t));
  strcpy(mot_deserialisation->lemot, "deserialisation");
  table[hash("deserialisation")] = mot_deserialisation;

  // parcours de la table et désérialisation de chaque mot dans un dictionnaire
  for (int i=0 ; i < MaxSizeArray ; i++) {
    if (table[i] != NULL) {
      deserializeDico(dictionary, table[i]);
    }
  }

  // vérification des chaînes (comparaisons entre celles du dictionnaire et celles de la table)
  // ici on ne peut pas vérifier les pointeurs car deserializeDico effectue une copie de son argument
  // dictionnaire (ABR) attendu sur cet exemple : 
  /*          a
               \ 
               est
             /     \ 
      bonjour       tous
          \         /   \
  deserialisation  test  un
       /
      de
     /
   ceci
  */
  
  CuAssertStrEquals(tc, mot_a->lemot, (*dictionary)->mot->data.lemot);
  CuAssertIntEquals(tc, hash("a"), (*dictionary)->mot->lehash);
  CuAssertPtrEquals(tc, NULL, (*dictionary)->fg);
  CuAssertStrEquals(tc, mot_est->lemot, (*dictionary)->fd->mot->data.lemot);
  CuAssertIntEquals(tc, hash("est"), (*dictionary)->fd->mot->lehash);
  CuAssertStrEquals(tc, mot_bonjour->lemot, (*dictionary)->fd->fg->mot->data.lemot);
  CuAssertIntEquals(tc, hash("bonjour"), (*dictionary)->fd->fg->mot->lehash);
  CuAssertStrEquals(tc, mot_deserialisation->lemot, (*dictionary)->fd->fg->fd->mot->data.lemot);
  CuAssertIntEquals(tc, hash("deserialisation"), (*dictionary)->fd->fg->fd->mot->lehash);
  CuAssertStrEquals(tc, mot_de->lemot, (*dictionary)->fd->fg->fd->fg->mot->data.lemot);
  CuAssertIntEquals(tc, hash("de"), (*dictionary)->fd->fg->fd->fg->mot->lehash);
  CuAssertStrEquals(tc, mot_ceci->lemot, (*dictionary)->fd->fg->fd->fg->fg->mot->data.lemot);
  CuAssertIntEquals(tc, hash("ceci"), (*dictionary)->fd->fg->fd->fg->fg->mot->lehash);

  CuAssertStrEquals(tc, mot_tous->lemot, (*dictionary)->fd->fd->mot->data.lemot);
  CuAssertIntEquals(tc, hash("tous"), (*dictionary)->fd->fd->mot->lehash);
  CuAssertStrEquals(tc, mot_test->lemot, (*dictionary)->fd->fd->fg->mot->data.lemot);
  CuAssertIntEquals(tc, hash("test"), (*dictionary)->fd->fd->fg->mot->lehash);
  CuAssertStrEquals(tc, mot_un->lemot, (*dictionary)->fd->fd->fd->mot->data.lemot);
  CuAssertIntEquals(tc, hash("un"), (*dictionary)->fd->fd->fd->mot->lehash);

  for (int i = 0 ; i < MaxSizeArray ; i++) {
    if (table[i] != NULL) {
      free(table[i]);
    }
  }
  free(table);
}

CuSuite *MaTestSuite () {
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_compareWord);
  SUITE_ADD_TEST (suite, test_hash);
  SUITE_ADD_TEST (suite, test_serializeDico);
  SUITE_ADD_TEST (suite, test_deserializeDico);
  return suite;
}