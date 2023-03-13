/** \file The bit field implementation
 *
 * \note The bit field is a convenience set of functions for representing bits
 * 	in byte arrays. It is much like \c std::bitset but with \c data()
 * 	equivalent.
 */

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "util_ct.h"

/**
 * \brief Calculate the number of bytes required to store bits
 * \param nb_bits The number of bits to store.
 * 	Must be an integer zero or greater
 * \return The number of bytes required
 */
#define prne_bf_get_size(nb_bits)\
	((nb_bits) % 8 == 0 ? (nb_bits) / 8 : (nb_bits) / 8 + 1)

/**
 * \brief Function type, to be applied to each bit in the field. See
 *	\see prne_bf_foreach()
 * \param ctx The custom context object to be used in the function
 * \param bit The index of the bit
 * \param v The value of the bit. \c True if set. \c False if unset
 */
typedef void(*prne_bf_foreach_ft)(
	void *ctx,
	const unsigned int bit,
	const bool v);

/**
 * \brief Set the bit in the bit field.
 * \param bf The bit field to manipulate
 * \param bit The index of the bit to manipulate
 * \param v The new value of the bit. \c True to set, \c false to unset
 */
void prne_bf_set (uint8_t *bf, const unsigned int bit, const bool v);
/**
 * \brief Extract the value of the bit in the bit field.
 * \param bf The bit field
 * \param size The size of the bit field in bytes
 * \param bit The index of the bit
 * \note \p size is used to determine if \p bit is out of bounds. The function
 * 	regards the bits outside the bounds of the bit field unset(false).
 * \retval True if the bit is set.
 * \retval False if the bit is unset.
 */
bool prne_bf_test (
	const uint8_t *bf,
	const size_t size,
	const unsigned int bit);
/**
 * \brief Iterate through the bit field, invoking \p f for each bit.
 * \param ctx The custom context to be passed to \p f
 * \param bf The bit field
 * \param size The size of the bit field in bytes
 * \param f The function to be invoked for each bit in the bit field
 * \note The number of times \p f is called is always a multiple of 8 regardless
 * 	of the actual number of bits in the field.
 */
void prne_bf_foreach (
	void *ctx,
	const uint8_t *bf,
	const size_t size,
	prne_bf_foreach_ft f);
