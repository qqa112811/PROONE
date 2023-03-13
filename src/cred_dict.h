/** \file
 * \brief The credential dictionary implementation
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Alias declaration */
typedef struct prne_cred_dict_entry prne_cred_dict_entry_t;
typedef struct prne_cred_dict_raw_entry prne_cred_dict_raw_entry_t;
typedef struct prne_cred_dict prne_cred_dict_t;

// The index entry object
struct prne_cred_dict_entry {
	uint16_t id; // Index of start of the user name
	uint16_t pw; // Index of start of the password
	uint8_t weight; // The weight value
};

// The raw entry entry object used to build the dictionary
struct prne_cred_dict_raw_entry {
	char *id; // Pointer to the user name string
	char *pw; // Pointer to the password string
	uint8_t weight; // Weight value
};

// The dictionary object
struct prne_cred_dict {
	const char *m; // Pointer to the string pool
	prne_cred_dict_entry_t *arr;
	size_t cnt;
};

/**
 * \brief Initialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_init_cred_dict (prne_cred_dict_t *p);
/**
 * \brief Deinitialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_free_cred_dict (prne_cred_dict_t *p);

/**
 * \brief Build a credential dictionary
 * \param arr The raw entries.
 * \param cnt The number of entries in \p arr
 * \param[out] out_m The serialised credential dictionary deserialisable with
 * 	\c prne_dser_cred_dict(). The returned memory is freeable with
 * 	\c prne_free().
 * \param[out] out_l The length of \p out_m in bytes.
 * \retval True if successful.
 * \retval False on error with \c errno set to an appropriate value.
 * \note The size of the binary credential dictionary is limited to 2^16 bytes
 * 	as indices are 16-bit integers. \c E2BIG is used to indicate this error.
 */
bool prne_build_cred_dict (
	const prne_cred_dict_raw_entry_t *arr,
	const size_t cnt,
	uint8_t **out_m,
	size_t *out_l);
/**
 * \brief Deserialise the credential dictionary
 * \param[out] dict The output object. Must be initiaised with
 * 	\c prne_init_cred_dict() beforehand.
 * \param buf The pointer to the memory containing the serialised credential
 * 	dictionary.
 * \param len The readable length of \p buf in bytes.
 * \retval True on successful parsing and allocation of \p dict members.
 * \retval False otherwise with \c errno set to an appropriate value.
 */
bool prne_dser_cred_dict (
	prne_cred_dict_t *dict,
	const uint8_t *buf,
	const size_t len);
