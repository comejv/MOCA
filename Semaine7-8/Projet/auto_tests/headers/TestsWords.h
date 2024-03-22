#ifndef TESTS_WORDS_H
#define TESTS_WORDS_H

/**
 * \file TestsWords.h
 * \brief Fonctions de tests pour le fichier word_tools.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "CuTest.h"
#include "structures.h"
#include "word_tools.h"

void test_compareWord(CuTest * tc);

void test_next_word(CuTest * tc);

void test_incWord(CuTest * tc);

CuSuite *Tests_Words ();

#endif