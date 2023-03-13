/** \file
 * \brief The integer set implementation.
 * \note The C equivalent of \c std::set<uintptr_t>
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


/* Alias declaration */
typedef struct prne_iset prne_iset_t;
typedef uintptr_t prne_iset_val_t;

struct prne_iset {
	prne_iset_val_t *arr; // The set sorted in ascending order
	size_t size; // The size of the set, the number of elements in the array
};


/**
 * \brief Initialise the integer set object.
 * \param s The pointer to the integer set object.
 * \note \p s can be freed using \c prne_free_iset() once initialised.
 * \see \c prne_free_iset()
 */
void prne_init_iset (prne_iset_t *s);
/**
 * \brief Free resources allocated for the integer set object.
 * \param s The pointer to the integer set object.
 * \see \c prne_init_iset()
 */
void prne_free_iset (prne_iset_t *s);
/**
 * \brief Clear the elements of the integer set object.
 * \param s The pointer to the integer set object.
 * \warning The function call may have the exact same effect as
 *	\c prne_free_iset() but \c prne_free_iset() must always be used to free the
 *	resources allocated for the object.
 */
void prne_iset_clear (prne_iset_t *s);
/**
 * \brief Insert an integer into the integer set object.
 * \param s The pointer to the integer set object.
 * \param v The integer.
 * \retval true if the integer has been inserted into the set.
 * \retval false if a memory allocation error has occurred and \c errno is set
 *	to \c ENOMEM
 */
bool prne_iset_insert (prne_iset_t *s, const prne_iset_val_t v);
/**
 * \brief Erase the integer from the integer set object.
 * \param s The integer set object.
 * \param v The integer.
 */
void prne_iset_erase (prne_iset_t *s, const prne_iset_val_t v);
/**
 * \brief Look up the integer in the integer set object.
 * \param s The integer set object.
 * \param v The integer.
 * \retval true if the integer is in the set.
 * \retval false otherwise.
 */
bool prne_iset_lookup (prne_iset_t *s, const prne_iset_val_t v);
