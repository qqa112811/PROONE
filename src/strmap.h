/** \file
 * \brief The string map implementation
 * \note The C equivalent of \c std::map<std::string,uintptr_t>
 */

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


/* Aliases and forward declarations */
typedef struct prne_strmap prne_strmap_t;
typedef struct prne_strmap_tuple prne_strmap_tuple_t;
typedef uintptr_t prne_strmap_val_t;

// The string map object
struct prne_strmap {
	prne_strmap_tuple_t *tbl; // The table array sorted in ascending order
	size_t size; // The number of elements in the table
};

// The tuple object
struct prne_strmap_tuple {
	const char *key;
	prne_strmap_val_t val;
};

/**
 * \brief Initialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_init_strmap (prne_strmap_t *map);
/**
 * \brief Deinitialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_free_strmap (prne_strmap_t *map);

/**
 * \brief Clear the elements of the string map object.
 * \param s The pointer to the string map object.
 * \warning The function call may have the exact same effect as
 *	\c prne_free_strmap() but \c prne_free_strmap() must always be used to free
 * 	the resources allocated for the object.
 */
void prne_strmap_clear (prne_strmap_t *map);
/**
 * \brief Insert a tuple into the string map object.
 * \param im The pointer to the string map object.
 * \param key The key of the new tuple.
 * \param val The value of the new tuple.
 * \return The pointer to the new tuple allocated in the map. The pointer is
 *	valid as long as the map object remains unmodified.
 * \retval NULL if memory allocation error has occurred and \c errno is set to
 *	\c ENOMEM
 * \note Calling the function invalidates the pointers previously returned by
 *	other functions.
 */
const prne_strmap_tuple_t *prne_strmap_insert (
	prne_strmap_t *map,
	const char* key,
	const prne_strmap_val_t val);
/**
 * \brief Erase the tuple with the \p key from the string map object.
 * \param im The pointer to the string map object.
 * \param key The key of the tuple to erase.
 * \note Calling the function invalidates the pointers previously returned by
 *	other functions.
 */
void prne_strmap_erase (prne_strmap_t *map, const char* key);
/**
 * \brief Look up the tuple with \p key in the string map object.
 * \param im The pointer to the string map object.
 * \param key The key to look for.
 * \return The pointer to the tuple in the map. The pointer is valid as long as
 *	the map object remains unmodified.
 * \retval NULL if the tuple with \p key is not found.
 */
const prne_strmap_tuple_t *prne_strmap_lookup (
	prne_strmap_t *map,
	const char* key);
