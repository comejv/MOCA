#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "CuTest.h"
#include "structures.h"
#include "word_tools.h"

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
  // CuAssertIntEquals(tc, -1, compareWord(w2, w1));(tc, -1, compareWord(w2, w1));
}

void test_next_word(CuTest * tc) {
  FILE *f;
  unsigned int l, c;
  //unsigned int *l1 = NULL, *c1 = NULL;
  f = fopen("../exemples/hugo.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier 'exemples/hugo.txt'\n");
    exit(-1);
  }
  l = 1; c = 0;

  // Faut malloc dans next_word pour l'utiliser (peut-être)
  // CuAssertStrEquals(tc, "je", next_word(f, l1, c1));
  // CuAssertIntEquals(tc, 1, *l1);
  // CuAssertIntEquals(tc, 1, *c1);
  // l = *l1;
  // c = *c1;
  
  CuAssertStrEquals(tc, "je", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 1, l);
  CuAssertIntEquals(tc, 1, c);

  CuAssertStrEquals(tc, "ne", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 1, l);
  CuAssertIntEquals(tc, 2, c);

  CuAssertStrEquals(tc, "laisserai", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 1, l);
  CuAssertIntEquals(tc, 3, c);

  CuAssertStrEquals(tc, "pas", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 1, l);
  CuAssertIntEquals(tc, 4, c);

  for (int i = 0; i < 4; i++) {
    next_word(f, &l, &c);
  }

  CuAssertStrEquals(tc, "sans", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 2, l);
  CuAssertIntEquals(tc, 1, c);

  for (int i = 0; i < 12; i++) {
    next_word(f, &l, &c);
  }

  CuAssertStrEquals(tc, "parmi", next_word(f, &l, &c));
  CuAssertIntEquals(tc, 3, l);
  CuAssertIntEquals(tc, 4, c);

}

void test_incWord(CuTest * tc) {
  emplacement_t* Location = (emplacement_t*) malloc(sizeof(emplacement_t));

  incWord(Location, 1, 1);
  CuAssertPtrNotNull(tc, Location->next);
  CuAssertIntEquals(tc, 1, Location->next->line);
  CuAssertIntEquals(tc, 1, Location->next->colonne);

  incWord(Location, 2, 2);
  CuAssertPtrNotNull(tc, Location->next->next);
  CuAssertIntEquals(tc, 2, Location->next->next->line);
  CuAssertIntEquals(tc, 2, Location->next->next->colonne);
  
}

CuSuite *Tests_Words () {
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_compareWord);
  SUITE_ADD_TEST (suite, test_next_word);
  SUITE_ADD_TEST (suite, test_incWord);
  return suite;
}