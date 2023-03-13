/** \file
 * \brief The pseudorandom number generator interface
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * \brief The fixed byte length of the seed data for WELL512
 */
#define PRNE_RND_WELL512_SEEDLEN 64

/**
 * \brief The PRNG engine object
 */
struct prne_rnd {
	void *ctx; // The opaque context
	void (*free_ctx_f)(void*); // The function for freeing the opaque context
	// The generator function
	bool (*random)(void*, uint8_t *buf, size_t len);
};

/* Aliases and forward declarations */
typedef struct prne_rnd prne_rnd_t;


/**
 * \brief Initialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_init_rnd (prne_rnd_t *p);
/**
 * \brief Deinitialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_free_rnd (prne_rnd_t *p);
/**
 * \brief Generate random numbers using the engine
 * \param p The pointer to the engine object
 * \param[out] buf The buffer for random number output
 * \param len The requested byte length of random numbers
 * \retval true on success
 * \retval false on failure. The underlying engine may set \c errno to describe
 * 	the nature of the error
 */
bool prne_rnd (prne_rnd_t *p, uint8_t *buf, const size_t len);

/**
 * \brief Allocate resources to set up the object as an instance of the WELL512
 * 	PRNG engine
 * \param p The poiner to the object
 * \param is The seed data. Must be 64 bytes(512 bits) or more
 * \retval true on success
 * \retval false on memory allocation failure, \c errno set to \c ENOMEM
 */
bool prne_rnd_alloc_well512 (
	prne_rnd_t *p,
	const uint8_t *is);
