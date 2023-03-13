/** \file
 * \brief The linked-list implementation.
 * \note The C equivalent of \c std::list<uintptr_t>
 */

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


/* Forward and alias declarations */
struct prne_llist;
struct prne_llist_entry;
typedef struct prne_llist prne_llist_t;
typedef struct prne_llist_entry prne_llist_entry_t;
typedef uintptr_t prne_llist_element_t;

struct prne_llist {
	prne_llist_entry_t *head, *tail;
	size_t size;
};

struct prne_llist_entry {
	prne_llist_entry_t *prev, *next;
	prne_llist_element_t element;
};

/**
 * \brief Initialise the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \note \p s can be freed using \c prne_free_llist() once initialised.
 * \see \c prne_free_llist()
 */
void prne_init_llist (prne_llist_t *llist);
/**
 * \brief Free resources allocated for the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \see \c prne_init_llist()
 */
void prne_free_llist (prne_llist_t *llist);
/**
 * \brief Clear the elements of the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \warning The function call may have the exact same effect as
 *	\c prne_free_llist() but \c prne_free_llist() must always be used to free
 *	the resources allocated for the object.
 */
void prne_llist_clear (prne_llist_t *llist);
/**
 * \brief Insert an element after \p entry into the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \param entry The entry that will precede the new entry (optional)
 * \param element The element.
 * \return The pointer to the allocated internal entry object for the element.
 * \retval NULL if a memory allocation error has occurred and \c errno is set
 *	to \c ENOMEM
 * \note If \p entry is passed NULL, the behaviour of the function is the same
 *	is that of prne_llist_append()
 * \see prne_llist_append()
 */
prne_llist_entry_t *prne_llist_insert (
	prne_llist_t *llist,
	prne_llist_entry_t *entry,
	const prne_llist_element_t element);
/**
 * \brief Append an element to the tail of the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \param element The element.
 * \return The pointer to the allocated internal entry object for the element.
 * \retval NULL if a memory allocation error has occurred and \c errno is set
 *	to \c ENOMEM
 * \note This function has the same effect as calling \c prne_llist_insert()
 *	with \c llist->tail
 */
prne_llist_entry_t *prne_llist_append (
	prne_llist_t *llist,
	const prne_llist_element_t element);
/**
 * \brief Remove an element from the linked-list object.
 * \param llist The pointer to the linked-list object.
 * \param entry The pointer to the allocated internal entry object for the
 *	element.
 * \returns The next element of the removed element.
 * \retval NULL if the element removed was the tail or the head.
 */
prne_llist_entry_t *prne_llist_erase (
	prne_llist_t *llist,
	prne_llist_entry_t *entry);
