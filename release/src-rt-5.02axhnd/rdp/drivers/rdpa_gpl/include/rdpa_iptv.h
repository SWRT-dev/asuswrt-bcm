/*
* <:copyright-BRCM:2013:DUAL/GPL:standard
* 
*    Copyright (c) 2013 Broadcom 
*    All Rights Reserved
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License, version 2, as published by
* the Free Software Foundation (the "GPL").
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* 
* A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
* writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
* 
* :> 
*/


#ifndef _RDPA_IPTV_H_
#define _RDPA_IPTV_H_

#include "rdpa_types.h"
#include "rdpa_ingress_class.h"

/** \defgroup mcast Multicast Management
 *   
 *  This section describes the objects responsible for the management of multicast traffic. 
 *  
 *  The IPTV Management object is responsible for packet replication. When a packet is needed to be replicated to a 
 *  Wi-Fi station by setting the egress_port field of the ::rdpa_ic_result_t structure, the WLAN multicast Flow Management 
 *  object must also be configured with the corresponding parameters. 
 *         
 */


/** \defgroup iptv IPTV Management
 *  \ingroup mcast       
 * APIs in this group are used for IPTV management
 * - IPTV lookup method
 * - Enable/disable multicast prefix filter (for GPON platforms)
 * - Add/Remove IPTV channels (per LAN port)
 * @{
 */

/** IPTV Multicast prefix filter method */
typedef enum
{
    rdpa_mcast_filter_method_none, /**< none multicast filter method */
    rdpa_mcast_filter_method_mac, /**< For mac multicast filter method */
    rdpa_mcast_filter_method_ip, /**< For IP multicast filter method */
    rdpa_mcast_filter_method_mac_and_ip /**< For mac and IP together multicast filter method \XRDP_LIMITED*/
} rdpa_mcast_filter_method;


/** L3 group address */
typedef struct
{
    bdmf_ip_t gr_ip;    /**< Multicast Group IP address */
    bdmf_ip_t src_ip;   /**< Multicast Source IP address. Can be specific IP (IGMPv3/MLDv2) or 0 (IGMPv2/MLDv1) */
} rdpa_iptv_l3_t;

/** Multicast group address */
typedef struct
{
    bdmf_mac_t mac;     /**< Multicast Group MAC Address, used for L2 multicast support */
    rdpa_iptv_l3_t l3;  /**< Multicast L3 address, used for L3 multicast support */
} rdpa_mcast_group_t;

/** IPTV channel key.\n
  * This type is used for API's for add/delete channels.
  */
typedef struct
{
    rdpa_mcast_group_t mcast_group; /**< Multicast Group Address Can be either L2 or L3 */
    uint16_t vid;                   /**< VID used for multicast stream (channel). */
#if defined(BCM63158)
    uint16_t inner_vid;
    uint8_t num_vlan_tags;
#endif
} rdpa_iptv_channel_key_t;

/** IPTV channel request info.\n
 * This is underlying type for iptv_channel_request aggregate
 */
typedef struct
{
    rdpa_iptv_channel_key_t key; /**< IPTV channel key, identifies single channel in JOIN/LEAVE requests */
    rdpa_ic_result_t mcast_result; /**< Multicast stream (channel) classification result */
    uint16_t  wlan_mcast_index; /**< Index in WLAN multicast clients table >*/ 
} rdpa_iptv_channel_request_t;

/** IPTV channel info.\n
  * This is underlying type for iptv_channel aggregate
  */
typedef struct
{
    rdpa_iptv_channel_key_t key; /**< IPTV channel key, identifies single channel in JOIN/LEAVE requests */
    rdpa_ports ports; /**< LAN ports mask represents the ports currently watching the channel */ 
    rdpa_ic_result_t mcast_result; /**< Multicast stream (channel) classification result */
    uint16_t  wlan_mcast_index; /**< Index in WLAN multicast clients table >*/ 
} rdpa_iptv_channel_t;

/** IPTV Global statistics */
typedef struct
{
    uint32_t rx_valid_pkt; /**< Valid Received IPTV packets */
    uint32_t rx_valid_bytes; /**< Valid Received IPTV bytes */
    uint32_t rx_crc_error_pkt; /**< Received packets with CRC error */
    uint32_t discard_pkt; /**< IPTV Discard Packets */
    uint32_t iptv_lkp_miss_drop;           /**< Drop due to IPTV Hash lookup miss (DA \ DIP) */
    uint32_t iptv_src_ip_vid_lkp_miss_drop;     /**< Drop due to IPTV channel Source IP \ VID lookup miss */
    uint32_t iptv_invalid_ctx_entry_drop;       /**< Drop due to IPTV channel invalid ctx entry */
    uint32_t iptv_fpm_alloc_nack_drop;          /**< Drop due to exhaustion of FPM buffers */
    uint32_t iptv_first_repl_disp_nack_drop;    /**< Drop due to unavilable dispatcher buffer - first replication */
    uint32_t iptv_exception_drop;               /**< Drop due to IPTV exception */
    uint32_t iptv_other_repl_disp_nack_drop;    /**< Drop due to unavilable dispatcher buffer - other replication */
    uint32_t discard_bytes;                     /**< IPTV total discard packets length in bytes */
#if defined XRDP && defined G9991
    uint32_t iptv_congestion_drop;              /**< IPTV congestion drops */
#endif
} rdpa_iptv_stat_t;

typedef struct {
    bdmf_index channel_index; /**< Channel index */
    rdpa_if port; /**< Port */
} rdpa_channel_req_key_t;

#define RDPA_MAX_IPTV_CHANNELS 1024

/** @} end of iptv Doxygen group */

#endif /* _RDPA_IPTV_H_ */

