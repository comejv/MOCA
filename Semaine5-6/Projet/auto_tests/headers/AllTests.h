#ifndef ALLTEST_H
#define ALLTEST_H

#include <stdio.h>

#include "CuTest.h"
#include "structures.h"
#include "TestsDico.h"
#include "TestsWords.h"
#include "TestsSerialization.h"
#include "structures.h"

void free_dico(dico *dict);

void RunAllTests(void);

#endif //ALLTEST_H