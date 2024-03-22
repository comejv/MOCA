#ifndef TESTS_DICO_H
#define TESTS_DICO_H

/**
 * \file TestsDico.h
 * \brief Fonctions de tests pour le fichier dico_tools.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "structures.h"
#include "dico_tools.h"
#include "CuTest.h"
#include "AllTests.h"

void test_insertDico(CuTest *tc);

void test_addToDico(CuTest *tc);

CuSuite *Tests_Dico ();

#endif