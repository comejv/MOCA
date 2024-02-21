#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "CuTest.h"
#include "date.h"

#define MAX_MSG_LEN 50

void test_compareWord(CuTest * tc) {
  CuAssertIntEquals(tc, 1, compareWord(NULL, "mot"));
  CuAssertIntEquals(tc, -1, compareWord("mot", NULL));
  CuAssertIntEquals(tc, 0, compareWord("mot", "mot"));

  CuAssertIntEquals(tc, -1, compareWord("avec", "bonjour"));
  CuAssertIntEquals(tc, 1, compareWord("bonjour", "avec"));

  CuAssertIntEquals(tc, -1, compareWord("abcd", "abce"));
  CuAssertIntEquals(tc, 1, compareWord("abce", "abcd"));

  CuAssertIntEquals(tc, 1, compareWord("aaaaa", "aaa"));
  CuAssertIntEquals(tc, -1, compareWord("aaa", "aaaaa"));

  CuAssertIntEquals(tc, 1, compareWord("aaab", "aaa"));
  CuAssertIntEquals(tc, -1, compareWord("aaa", "aaab"));

  CuAssertIntEquals(tc, 0, compareWord("", ""));
  CuAssertIntEquals(tc, -1, compareWord("mot", ""));
  CuAssertIntEquals(tc, 1, compareWord("", "mot"));

  CuAssertIntEquals(tc, 0, compareWord(" ", " "));
  CuAssertIntEquals(tc, 1, compareWord(" ", "mot"));
  CuAssertIntEquals(tc, -1, compareWord("mot", " "));
}

void test_hash(CuTest *tc) {
  // tester des cas simples (pas d'overflow)
}

CuSuite *MaTestSuite (){
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_compareWord);
  return suite;
}



