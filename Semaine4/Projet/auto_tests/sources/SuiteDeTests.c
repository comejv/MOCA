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

  // On ne devrait pas considerer "" et " " comme des mots donc ces tests servent a rien
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

CuSuite *MaTestSuite (){
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_compareWord);
  return suite;
}



