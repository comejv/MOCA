#include "AllTests.h"

void free_dico(dico *dict) {
  if (dict) {
    free_dico(dict->fg);
    free_dico(dict->fd);
    emplacement_t *ptr = dict->mot->data.tete_liste;
    emplacement_t *tmp = ptr;
    // libération de la liste d'emplacements du noeud courant
    while (ptr != NULL) {
      ptr = ptr->next;
      free(tmp);
      tmp = ptr;
    }
    free(dict->mot);
    free(dict);
  }
}

void RunAllTests (void){
  CuString *output = CuStringNew ();
  CuSuite *suite = CuSuiteNew ();

  CuSuiteAddSuite (suite,Tests_Words());
  CuSuiteAddSuite (suite,Tests_Serialization());
  CuSuiteAddSuite (suite,Tests_Dico());

  CuSuiteRun (suite);
  CuSuiteSummary (suite, output);
  CuSuiteDetails (suite, output);
  printf ("%s\n", output->buffer);
}
