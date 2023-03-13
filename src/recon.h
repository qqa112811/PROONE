/** \file
 * \brief The recon worker
 */

#pragma once
#include "pth.h"
#include "protocol.h"

#include <mbedtls/ctr_drbg.h>


/* Alias and forward declarations */
/**
 * \brief The opauqe handle type to an instance of the recon worker. Reserved
 * 	for future use.
 */
typedef struct prne_recon prne_recon_t;
typedef struct prne_recon_param prne_recon_param_t;
typedef struct prne_recon_network prne_recon_network_t;
typedef void(*prne_recon_evt_ft)(void *ctx, const prne_net_endpoint_t *ep);

// The recon network object
struct prne_recon_network {
	prne_ip_addr_t addr;
	uint8_t mask[16]; // The netmask bits in the network order
};

// The recon worker parameter object
struct prne_recon_param {
	// The blacklisted networks
	struct {
		prne_recon_network_t *arr;
		size_t cnt;
	} blist;
	// The target networks
	struct {
		prne_recon_network_t *arr;
		size_t cnt;
	} target;
	// The destination ports in SYN packets
	struct {
		uint16_t *arr;
		size_t cnt;
	} ports;
	prne_recon_evt_ft evt_cb; // The discovery event callback function
	void *cb_ctx; // The context object for event callbacks
	/*
	 * True if the object has the responsibility of freeing the dynamically
	 * allocated members
	 */
	bool ownership;
};

/**
 * \brief Allocate resources and start an instance of the recon worker
 * \param wkr The initialised worker object
 * \param ctr_drbg The CTR DRBG object to use for initial random values
 * \param param The recon worker parameter object
 * \return A handle to the instance
 * \retval NULL if an error occurred. \c errno set.
 */
prne_recon_t *prne_alloc_recon (
	prne_worker_t *wkr,
	mbedtls_ctr_drbg_context *ctr_drbg,
	const prne_recon_param_t *param);
/**
 * \brief Initialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_init_recon_param (prne_recon_param_t *p);
/**
 * \brief Deinitialisation function
 * \see [/doc/impl.md#Resource Allocation](/doc/impl.md#resource_allocation)
 */
void prne_free_recon_param (prne_recon_param_t *p);
/**
 * \brief Allocate dynamically allocated members in the recon worker parameter
 * 	object
 * \param p The pointer to the recon worker parameter object
 * \param blist The number of blacklisted networks
 * \param target The number of target networks
 * \param ports The number of the destination ports in SYN packets
 * \retval true if allocation was successful
 * \retval false otherwise and \c errno is set to \c ENOMEM
 */
bool prne_alloc_recon_param (
	prne_recon_param_t *p,
	const size_t blist,
	const size_t target,
	const size_t ports);
