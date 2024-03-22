#ifndef TESTS_SERIALIZATION_H
#define TESTS_SERIALIZATION_H

/**
 * \file TestsSerialization.h
 * \brief Fonctions de tests pour le fichier serialization.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "CuTest.h"
#include "structures.h"
#include "serialization.h"
#include "AllTests.h"

void test_hash(CuTest *tc);

void test_serializeDico(CuTest *tc);

void test_deserializeDico(CuTest *tc);

CuSuite *Tests_Serialization ();

#endif