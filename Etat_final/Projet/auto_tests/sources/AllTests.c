#include "AllTests.h"

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, Tests_Words());
    CuSuiteAddSuite(suite, Tests_Serialization());
    CuSuiteAddSuite(suite, Tests_Dico());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}
