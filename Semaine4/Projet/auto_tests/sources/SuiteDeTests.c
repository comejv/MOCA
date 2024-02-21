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

  strcpy(w1->lemot, "");
  strcpy(w2->lemot, "mot");
  CuAssertIntEquals(tc, 0, compareWord(w1, w1));
  CuAssertIntEquals(tc, -1, compareWord(w2, w1));
  CuAssertIntEquals(tc, 1, compareWord(w1, w2));

  strcpy(w1->lemot, " ");
  strcpy(w2->lemot, "mot");
  CuAssertIntEquals(tc, 0, compareWord(w1, w1));
  CuAssertIntEquals(tc, 1, compareWord(w1, w2));
  CuAssertIntEquals(tc, -1, compareWord(w2, w1));
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

CuSuite *MaTestSuite (){
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_compareWord);
  SUITE_ADD_TEST (suite, test_hash);
  return suite;
}