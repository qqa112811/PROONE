/** \file
 * \brief The integer map implementation.
 * \note The integer map implementation is usually used to map pointer to
 *	pointer. This is the C version of \c std::map<uintptr_t,uintptr_t>
 */

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


/* Forward and alias declarations */
struct prne_imap;
struct prne_imap_tuple;
typedef uintptr_t prne_imap_key_type_t; // The key data type
typedef uintptr_t prne_imap_val_type_t; // The value data type
typedef struct prne_imap prne_imap_t;
typedef struct prne_imap_tuple prne_imap_tuple_t;

struct prne_imap { // The integer map object
	// The table array kept in ascending order
	prne_imap_tuple_t *tbl;
	// The number of elements in the table
	size_t size;
};

struct prne_imap_tuple { // The tuple object
	prne_imap_key_type_t key; // Key
	prne_imap_val_type_t val; // Value
};


/**
 * \brief Initialise the integer map object.
 * \param im The pointer to the integer map object.
 * \note \p im can be freed using \c prne_free_imap() once initialised.
 * \see \c prne_free_imap()
 */
void prne_init_imap (prne_imap_t *im);
/**
 * \brief Free resources allocated for the integer map object.
 * \param im The pointer to the integer map object.
 * \see \c prne_init_imap()
 */
void prne_free_imap (prne_imap_t *im);

/**
 * \brief Clear the elements of the integer map object.
 * \param im The pointer to the integer map object.
 * \warning The function call may have the exact same effect as
 *	\c prne_free_imap() but \c prne_free_imap() must always be used to free the
 *	resources allocated for the object.
 */
void prne_imap_clear (prne_imap_t *im);
/**
 * \brief Insert a tuple into the integer map object.
 * \param im The pointer to the integer map object.
 * \param key The key of the new tuple.
 * \param val The value of the new tuple.
 * \return The pointer to the new tuple allocated in the map. The pointer is
 *	valid as long as the map object remains unmodified.
 * \retval NULL if memory allocation error has occurred and \c errno is set to
 *	\c ENOMEM
 * \note Calling the function invalidates the pointers previously returned by
 *	other functions.
 */
const prne_imap_tuple_t *prne_imap_insert (
	prne_imap_t *im,
	const prne_imap_key_type_t key,
	const prne_imap_val_type_t val);
/**
 * \brief Erase the tuple with the \p key from the integer map object.
 * \param im The pointer to the integer map object.
 * \param key The key of the tuple to erase.
 * \note Calling the function invalidates the pointers previously returned by
 *	other functions.
 */
void prne_imap_erase (prne_imap_t *im, const prne_imap_key_type_t key);
/**
 * \brief Look up the tuple with \p key in the integer map object.
 * \param im The pointer to the integer map object.
 * \param key The key to look for.
 * \return The pointer to the tuple in the map. The pointer is valid as long as
 *	the map object remains unmodified.
 * \retval NULL if the tuple with \p key is not found.
 */
const prne_imap_tuple_t *prne_imap_lookup (
	prne_imap_t *im,
	const prne_imap_key_type_t key);
