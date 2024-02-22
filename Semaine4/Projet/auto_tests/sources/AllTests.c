#include <stdio.h>

#include "CuTest.h"
#include "AllTests.h"

CuSuite *Tests_Words();
CuSuite *Tests_Serialization();

void RunAllTests (void){
  CuString *output = CuStringNew ();
  CuSuite *suite = CuSuiteNew ();

  CuSuiteAddSuite (suite,Tests_Words());
  CuSuiteAddSuite (suite,Tests_Serialization());

  CuSuiteRun (suite);
  CuSuiteSummary (suite, output);
  CuSuiteDetails (suite, output);
  printf ("%s\n", output->buffer);
}
