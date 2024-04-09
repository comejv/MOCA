## Changelog
Description des changements faits sur le projet. Certains commits intermédiaires sont ignorés. Le commit indiqué est le dernier commit concerné, plusieurs une description concerne plusieurs commits. Le commit indiqué ne reflette pas l'état final de la modification mais plutôt une avancée importante.

### Divers

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| fab190e6 | 2024-01-26 | Ajout d'un fichier gitignore |
| 1b07f8cb | 2024-02-02 | Modification du gitignore pour organisation hiérarchique |
| fb3b7cb | 2024-02-21 | Ajout d'une macro de débug |
| c2d1801 | 2024-02-04 | Ajout d'exemples |

### Changements dans l'organisation du code et Makefile

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| f85cbb2 | 2024-01-30 | Modularisation du projet en plusieurs fichiers, création d'un makefile pour tout compiler et création de documentation avec doxygen |
| 7f3adfd | 2024-02-02 | Changement organisation hiérarchique projet |
| 9bcb241 | 2024-02-04 | Changement du Makefile selon la nouvelle hierarchie, changement parametres doxygen doc |
| 0790230 | 2024-02-06 | Utilisation de librairies statiques ou dynamiques et makefile pour les compiler |
| 21e5ffd | 2024-02-06 | Amélioration du Makefile pour prendre en compte les librairies |
| c170f44 | 2024-02-16 | Makefile pour gcov et les exemples |
| 0831514 | 2024-02-16 | Ajout de règles pour la compilation des tests unitaires via un Makefile dédié |
| 6c251c8 | 2024-03-13 | Ajout d'une variable ASAN au makefile pour pouvoir ajouter Asan à la compilation via la command line |
| 6862bee | 2024-03-22 | Ajout d'une cible afl |
| 1f66335 | 2024-03-22 | Gestion d'afl avec gcc-fast ou sans |
| cde67e1 | 2024-04-05 | Changement makefile des libs pour gprof sur mandelbrot |

### Corrections de bugs

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| d000490 | 2024-02-22 | Correction de la valeur de retour de la fonction de hash vers un entier non signé |
| de9201c | 2024-03-13 | Correction lecture à haute addresse à cause de variables non initialiées |
| dabba4d | 2024-03-14 | Correction de l'affichage des résultats |
| feb5f7b | 2024-03-26 | Correction du bug de dico sur les caractères non ASCII |
| 4fc6a70 | 2024-04-08 | Meilleur gestion des caractères non ascii (erreur plutôt qu'ignore) |

### Tests et couverture des tests 

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| 0831514 | 2024-02-16 | Ajout de la librairie CUtest et des premières suites de tests unitaires |
| bb34d7a | 2024-02-21 | Ajout des tests unitaires de la fonction de hash |
| 1455d93 | 2024-02-21 | Tests unitaires de la sérialization |
| e5828d5 | 2024-02-22 | Changement de next_word avec ses tests |
| 7267fb6 | 2024-02-22 | Ajout d'un script de tests systèmes |
| 33cb9da | 2024-03-12 | Ajout de tests pour dico_tools.c et corrections |

### Gestion correcte de la mémoire

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| 7b494ad | 2024-03-08 | Correction des mallocs dans les dicos |
| 005ee3f | 2024-03-08 | Ajout de stack protector via le makefile |
| b8f7553 | 2024-03-11 | Initialisation de variables nonn initialisées + ajout de -fwrapv en flag pour éviter l'overflow arithmétique |
| d22fdd2 | 2024-03-13 | Correction des fuites de mémoire |
| f3d3d67 | 2024-03-14 | Fin de correction des leaks |
| e2c8b36 | 2024-03-14 | Fermeture du fichier dicores après utilisation |
| 24f8a52 | 2024-03-26 | Gestion de la fuite mémoire restante + changement de l'affichage du nom dans dictionnaires.txt |

### Performances

| Commit ID | Date       | Description                                 |
|------------|------------|---------------------------------------------|
| 6f82ecf | 2024-04-03 | Utilisation de gprof et gprof2dot |
| 3c33548 | 2024-04-03 | Optimisations des fonctions (plus de parcours de liste chaînée, moins d'appels de fonctions redondants) |

