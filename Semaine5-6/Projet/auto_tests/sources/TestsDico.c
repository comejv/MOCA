#include "TestsDico.h"

void test_insertDico(CuTest *tc) {
    dico **dico_actual;

    // initialisations
    dico_actual = (dico **) malloc (sizeof(dico *));
    *dico_actual = NULL;

    // test d'insertion dans un arbre vide
    mot_t *mot_test = (mot_t *) malloc (sizeof(mot_t));
    strcpy(mot_test->data.lemot, "test");
    mot_test->data.tete_liste = (emplacement_t *) malloc (sizeof(emplacement_t));
    mot_test->data.tete_liste->next = NULL;
    mot_test->data.queue_liste = mot_test->data.tete_liste;

    mot_test->data.tete_liste->line = 3;
    mot_test->data.tete_liste->colonne = 5;

    insertDico(dico_actual, mot_test);

    CuAssertStrEquals(tc, "test", (*dico_actual)->mot->data.lemot);
    CuAssertIntEquals(tc, 3, (*dico_actual)->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 5, (*dico_actual)->mot->data.tete_liste->colonne);

    CuAssertPtrEquals(tc, NULL, (*dico_actual)->fg);
    CuAssertPtrEquals(tc, NULL, (*dico_actual)->fd);

    // test d'insertion à gauche du noeud racine
    mot_t *mot_gauche = (mot_t *) malloc (sizeof(mot_t));
    strcpy(mot_gauche->data.lemot, "salutations");
    mot_gauche->data.tete_liste = (emplacement_t *) malloc (sizeof(emplacement_t));
    mot_gauche->data.tete_liste->next = NULL;
    mot_gauche->data.queue_liste = mot_gauche->data.tete_liste;

    mot_gauche->data.tete_liste->line = 0;
    mot_gauche->data.tete_liste->colonne = 1;

    insertDico(dico_actual, mot_gauche);

    CuAssertStrEquals(tc, "test", (*dico_actual)->mot->data.lemot);
    CuAssertIntEquals(tc, 3, (*dico_actual)->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 5, (*dico_actual)->mot->data.tete_liste->colonne);

    CuAssertStrEquals(tc, "salutations", (*dico_actual)->fg->mot->data.lemot);
    CuAssertIntEquals(tc, 0, (*dico_actual)->fg->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 1, (*dico_actual)->fg->mot->data.tete_liste->colonne);

    CuAssertPtrEquals(tc, NULL, (*dico_actual)->fd);

    // test d'insertion à droite du noeud racine
    mot_t *mot_droit = (mot_t *) malloc (sizeof(mot_t));
    strcpy(mot_droit->data.lemot, "unitaire");
    mot_droit->data.tete_liste = (emplacement_t *) malloc (sizeof(emplacement_t));
    mot_droit->data.tete_liste->next = NULL;
    mot_droit->data.queue_liste = mot_droit->data.tete_liste;
    mot_droit->data.tete_liste->line = 8;
    mot_droit->data.tete_liste->colonne = 10;

    insertDico(dico_actual, mot_droit);

    CuAssertStrEquals(tc, "test", (*dico_actual)->mot->data.lemot);
    CuAssertIntEquals(tc, 3, (*dico_actual)->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 5, (*dico_actual)->mot->data.tete_liste->colonne);

    CuAssertStrEquals(tc, "salutations", (*dico_actual)->fg->mot->data.lemot);
    CuAssertIntEquals(tc, 0, (*dico_actual)->fg->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 1, (*dico_actual)->fg->mot->data.tete_liste->colonne);
    
    CuAssertStrEquals(tc, "unitaire", (*dico_actual)->fd->mot->data.lemot);
    CuAssertIntEquals(tc, 8, (*dico_actual)->fd->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 10, (*dico_actual)->fd->mot->data.tete_liste->colonne);

    // test d'insertion d'un mot équivalent au mot d'un noeud déjà existant (racine)
    mot_t *mot_test_bis = (mot_t *) malloc (sizeof(mot_t));
    strcpy(mot_test_bis->data.lemot, "test");
    mot_test_bis->data.tete_liste = (emplacement_t *) malloc (sizeof(emplacement_t));
    mot_test_bis->data.tete_liste->next = NULL;
    mot_test_bis->data.queue_liste = mot_test_bis->data.tete_liste;
    
    mot_test_bis->data.tete_liste->line = 2;
    mot_test_bis->data.tete_liste->colonne = 0;

    insertDico(dico_actual, mot_test_bis);
    CuAssertStrEquals(tc, "test", (*dico_actual)->mot->data.lemot);
    CuAssertIntEquals(tc, 3, (*dico_actual)->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 5, (*dico_actual)->mot->data.tete_liste->colonne);
    CuAssertIntEquals(tc, 2, (*dico_actual)->mot->data.tete_liste->next->line);
    CuAssertIntEquals(tc, 0, (*dico_actual)->mot->data.tete_liste->next->colonne);
    CuAssertPtrEquals(tc, (*dico_actual)->mot->data.tete_liste->next, (*dico_actual)->mot->data.queue_liste);

    CuAssertStrEquals(tc, "salutations", (*dico_actual)->fg->mot->data.lemot);
    CuAssertIntEquals(tc, 0, (*dico_actual)->fg->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 1, (*dico_actual)->fg->mot->data.tete_liste->colonne);
    
    CuAssertStrEquals(tc, "unitaire", (*dico_actual)->fd->mot->data.lemot);
    CuAssertIntEquals(tc, 8, (*dico_actual)->fd->mot->data.tete_liste->line);
    CuAssertIntEquals(tc, 10, (*dico_actual)->fd->mot->data.tete_liste->colonne);

    free_dico(*dico_actual);
    free(dico_actual);
}

void test_addToDico(CuTest *tc) {
  dico **dico_actual = (dico **) malloc (sizeof(dico *));
  unsigned int ligne, colonne;

  // test d'insertion dans un dico vide
  *dico_actual = NULL;
  ligne = 4;
  colonne = 7;
  addToDico(dico_actual, "insertion", &ligne, &colonne);
  CuAssertStrEquals(tc, "insertion", (*dico_actual)->mot->data.lemot);
  CuAssertIntEquals(tc, 4, (*dico_actual)->mot->data.tete_liste->line);
  CuAssertIntEquals(tc, 7, (*dico_actual)->mot->data.tete_liste->colonne);
  CuAssertPtrEquals(tc, (*dico_actual)->mot->data.tete_liste, (*dico_actual)->mot->data.queue_liste);

  // test d'insertion dans un noeud dont le mot est vide
  (*dico_actual)->mot = NULL;
  ligne = 25;
  colonne = 13;
  addToDico(dico_actual, "tentative", &ligne, &colonne);
  CuAssertStrEquals(tc, "tentative", (*dico_actual)->mot->data.lemot);
  CuAssertIntEquals(tc, 25, (*dico_actual)->mot->data.tete_liste->line);
  CuAssertIntEquals(tc, 13, (*dico_actual)->mot->data.tete_liste->colonne);
  CuAssertPtrEquals(tc, (*dico_actual)->mot->data.tete_liste, (*dico_actual)->mot->data.queue_liste);

  // test d'insertion standard (gauche)
  ligne = 150;
  colonne = 813;
  addToDico(dico_actual, "essai", &ligne, &colonne);
  CuAssertStrEquals(tc, "tentative", (*dico_actual)->mot->data.lemot);
  CuAssertIntEquals(tc, 25, (*dico_actual)->mot->data.tete_liste->line);
  CuAssertIntEquals(tc, 13, (*dico_actual)->mot->data.tete_liste->colonne);
  CuAssertPtrEquals(tc, (*dico_actual)->mot->data.tete_liste, (*dico_actual)->mot->data.queue_liste);

  CuAssertStrEquals(tc, "essai", (*dico_actual)->fg->mot->data.lemot);
  CuAssertIntEquals(tc, 150, (*dico_actual)->fg->mot->data.tete_liste->line);
  CuAssertIntEquals(tc, 813, (*dico_actual)->fg->mot->data.tete_liste->colonne);
  CuAssertPtrEquals(tc, (*dico_actual)->fg->mot->data.tete_liste, (*dico_actual)->fg->mot->data.queue_liste);
  free_dico(*dico_actual);
  free(dico_actual);
}

CuSuite *Tests_Dico () {
  CuSuite *suite = CuSuiteNew ();
  SUITE_ADD_TEST (suite, test_insertDico);
  SUITE_ADD_TEST (suite, test_addToDico);
  return suite;
}