
/**
 * @file free.h
 * @brief Header file for functions that free dynamically allocated memory for
 * the data structures.
 *
 * This file contains function prototypes for freeing the memory allocated for
 * the various data structures used in the program.
 */

#ifndef FREE_H
#define FREE_H

#include "structures.h" // Include the header file with data structure definitions
#include "serialization.h" // Include the header file with MaxSizeArray definitions

/**
 * @brief Frees the memory allocated for an `emplacement_t` structure.
 *
 * This function recursively frees the memory for the entire linked list of
 * `emplacement_t` structures.
 *
 * @param emplacement Pointer to the `emplacement_t` structure to be freed.
 */
void freeEmplacement(emplacement_t *emplacement);

/**
 * @brief Frees the memory allocated for a `mot_data_t` structure.
 *
 * This function frees the memory for a `mot_data_t` table, including the
 * linked list of `emplacement_t` structures pointed to by `tete_liste` for each `mot_data_t`.
 *
 * @param motData Pointer to the `mot_data_t` table structure to be freed.
 */
void freeMotData(mot_data_t **motData);

/**
 * @brief Frees the memory allocated for a `mot_t` structure.
 *
 * This function frees the memory for the `mot_t` structure, including the
 * memory allocated for the `data` member (which is a `mot_data_t` structure)
 * and the memory pointed to by `mot`.
 *
 * @param mot Pointer to the `mot_t` structure to be freed.
 */
void freeMot(mot_t *mot);

/**
 * @brief Frees the memory allocated for an entire `dico` (dictionary)
 * structure.
 *
 * This function recursively frees the memory for the entire dictionary tree,
 * including the `mot` node (a `mot_t` structure) and its left and right
 * subtrees (`fg` and `fd`).
 *
 * @param dico Pointer to the `dico` structure (root of the dictionary tree) to
 * be freed.
 */
void freeDico(dico *dico);

#endif /* FREE_H */
