/*
* <:copyright-BRCM:2014:DUAL/GPL:standard
* 
*    Copyright (c) 2014 Broadcom 
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

#ifndef _RDPA_TCPSPDTEST_H_
#define _RDPA_TCPSPDTEST_H_

/** \defgroup Tcp Speed Test
 * This object is used to manage the Tcp Speed Test \n
 * @{
 */

#include <rdd.h>

/** Minimum transmitted packet size for padding */
#define RDPA_TCPSPDTEST_MIN_TX_PD_LEN 60

/** Tcp Speed Test Engine Connection Information.\n
 * Contains the Connection Information to Server \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint8_t   l2_hdr_len;               /**< L2 header len */
    uint8_t   l3_hdr_len;               /**< L3 header len */
    uint8_t   l4_hdr_len;               /**< L4 header len */
    uint8_t   tx_pd_len;                /**< Tx packet descriptor len */
    uint32_t  cpu_rx_rdd_queue;         /**< CPU queue num */
    rdpa_if   port;                     /**< Destination port for method=port, source port for method=bridge */
    rdpa_flow wan_flow;                 /**< Destination flow for method=port, Source flow for method=bridge,port=wan */
    uint32_t  egress_queue_id;          /**< Egress queue id. method=port only */
    uint16_t  tx_qm_queue;              /**< Runner First Level Queue */
} rdpa_tcpspdtest_engine_conn_info_t;

/** Tcp Speed Test Engine TCB.\n
 * Contains the Task Control State of the Runner Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint32_t rx_pkts;                   /**< received packets counter */
    uint32_t txed_pkts;                 /**< num of txed packets */
    uint32_t freed_pkts;                /**< num of freed packets */
    uint32_t ack_seq;                   /**< calculated calculated ack seq */
    uint32_t tx_seq;                    /**< last transmitted seq */
    uint32_t bad_pkts;                  /**< num of received packets with unexpected seq */
    uint32_t no_credits;                /**< num of dispatcher no credits */
    uint64_t bad_bytes;                 /**< num of received bytes with unexpected seq */
    uint64_t rx_bytes;                  /**< received bytes */
    uint64_t expected_bytes;            /**< expected bytes */
} rdpa_tcpspdtest_engine_tcb_t;

/** Tcp Speed Test Engine Reference Packet.\n
 * Contains the Acknowledge Refernce Packet for Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint16_t size;                                              /**< reference packet header size */
    uint16_t offset;                                            /**< packet offset for l3 8 bytes align */
    uint8_t  hdr[RDD_TCPSPDTEST_ENGINE_REF_PKT_HDR_HDR_NUMBER]; /**< reference packet header ptr */
} rdpa_tcpspdtest_engine_ref_pkt_hdr_t;

/** Tcp Speed Test Engine Packet Drop Handling.\n
 * Contains the Packet Drop Handling State for Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint8_t   is_drop;       /**< is packets drop */
    uint8_t   is_win_full;   /**< Is sequence window full */
    uint16_t  num_errs;      /**< num of err events. one event for multiple burst lost */
    uint16_t  wr_ofs;        /**< write offset for good frames window during pkt drops */
    uint16_t  rd_ofs;        /**< read offset for good frames window during pkt drops */
} rdpa_tcpspdtest_engine_pkt_drop_t;

/** @} end of tcpspdtest Doxygen group. */

#endif /* _RDPA_TCPSPDTEST_H_ */
