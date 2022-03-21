/*
   Copyright (c) 2015 Broadcom Corporation
   All Rights Reserved

    <:label-BRCM:2015:DUAL/GPL:standard
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
:>
*/

/*
 *  Created on: Jan 2016
 *      Author: yuval.raviv@broadcom.com
 */

#include "mac_drv.h"
#include "hwapi_mac.h"

static mac_stats_t cached_stats[rdpa_emac__num_of];

static int port_unimac_init(mac_dev_t *mac_dev)
{
    rdpa_emac emac = mac_dev->mac_id;

    mac_hwapi_init_emac(emac);
    mac_hwapi_set_external_conf(emac, 0);

    if (mac_dev->priv)
        mac_hwapi_set_unimac_cfg(emac);

    return 0;
}

static int port_unimac_enable(mac_dev_t *mac_dev)
{
    rdpa_emac emac = mac_dev->mac_id;

    mac_hwapi_set_rxtx_enable(emac, 1, 1);

    return 0;
}

static int port_unimac_disable(mac_dev_t *mac_dev)
{
    rdpa_emac emac = mac_dev->mac_id;

    mac_hwapi_set_rxtx_enable(emac, 0, 0);

    return 0;
}

static int port_unimac_cfg_get(mac_dev_t *mac_dev, mac_cfg_t *mac_cfg)
{
    rdpa_emac emac = mac_dev->mac_id;
    rdpa_emac_cfg_t emac_cfg = {};
    memset(mac_cfg, 0, sizeof(mac_cfg_t));

    mac_hwapi_get_configuration(emac, &emac_cfg);

    if (emac_cfg.rate == rdpa_emac_rate_10m)
        mac_cfg->speed = MAC_SPEED_10;
    if (emac_cfg.rate == rdpa_emac_rate_100m)
        mac_cfg->speed = MAC_SPEED_100;
    if (emac_cfg.rate == rdpa_emac_rate_1g)
        mac_cfg->speed = MAC_SPEED_1000;
    if (emac_cfg.rate == rdpa_emac_rate_2_5g)
        mac_cfg->speed = MAC_SPEED_2500;
    else
        return -1;

    mac_cfg->duplex = emac_cfg.full_duplex ? MAC_DUPLEX_FULL : MAC_DUPLEX_HALF;

    return 0;
}

static int port_unimac_cfg_set(mac_dev_t *mac_dev, mac_cfg_t *mac_cfg)
{
    rdpa_emac emac = mac_dev->mac_id;
    rdpa_emac_cfg_t emac_cfg = {};

    mac_hwapi_get_configuration(emac, &emac_cfg);

    if (mac_cfg->speed == MAC_SPEED_10)
        emac_cfg.rate = rdpa_emac_rate_10m;
    else if (mac_cfg->speed == MAC_SPEED_100)
        emac_cfg.rate = rdpa_emac_rate_100m;
    else if (mac_cfg->speed == MAC_SPEED_1000)
        emac_cfg.rate = rdpa_emac_rate_1g;
    else if (mac_cfg->speed == MAC_SPEED_2500)
        emac_cfg.rate = rdpa_emac_rate_2_5g;
    else
        return -1;

    emac_cfg.full_duplex = mac_cfg->duplex == MAC_DUPLEX_FULL ? 1: 0;

    mac_hwapi_set_configuration(emac, &emac_cfg);

    return 0;
}

static int port_unimac_pause_get(mac_dev_t *mac_dev, int *rx_enable, int *tx_enable)
{
    S_MAC_HWAPI_FLOW_CTRL flowControl;

    mac_hwapi_get_flow_control(mac_dev->mac_id, &flowControl);
    *rx_enable = flowControl.rxFlowEnable ? 1 : 0;
    *tx_enable = flowControl.txFlowEnable ? 1 : 0;

    return 0;
}

static int port_unimac_pause_set(mac_dev_t *mac_dev, int rx_enable, int tx_enable, char *src_addr)
{
    S_MAC_HWAPI_FLOW_CTRL flowControl;
    bdmf_mac_t addr = {};

    mac_hwapi_get_flow_control(mac_dev->mac_id, &flowControl);

    flowControl.rxFlowEnable = rx_enable ? 1 : 0;
    flowControl.txFlowEnable = tx_enable ? 1 : 0;

    if (src_addr)
        memcpy(addr.b, src_addr, sizeof(bdmf_mac_t));

    mac_hwapi_set_flow_control(mac_dev->mac_id, &flowControl);
    mac_hwapi_modify_flow_control_pause_pkt_addr(mac_dev->mac_id, addr);

    return 0;
}

static int port_unimac_stats_get(mac_dev_t *mac_dev, mac_stats_t *mac_stats)
{
    rdpa_emac_stat_t stats;
    rdpa_emac emac = mac_dev->mac_id;

    /* TODO: lock */
    /* rdpa counters are read and clear, need to store data into local cache */
    mac_hwapi_get_rx_counters(emac, &stats.rx);
    mac_hwapi_get_tx_counters(emac, &stats.tx);

    cached_stats[emac].rx_byte += stats.rx.byte;
    cached_stats[emac].rx_packet += stats.rx.packet;
    cached_stats[emac].rx_frame_64 += stats.rx.frame_64;
    cached_stats[emac].rx_frame_65_127 += stats.rx.frame_65_127;
    cached_stats[emac].rx_frame_128_255 += stats.rx.frame_128_255;
    cached_stats[emac].rx_frame_256_511 += stats.rx.frame_256_511;
    cached_stats[emac].rx_frame_512_1023 += stats.rx.frame_512_1023;
    cached_stats[emac].rx_frame_1024_1518 += stats.rx.frame_1024_1518;
    cached_stats[emac].rx_frame_1519_mtu += stats.rx.frame_1519_mtu;
    cached_stats[emac].rx_multicast_packet += stats.rx.multicast_packet;
    cached_stats[emac].rx_broadcast_packet += stats.rx.broadcast_packet;
    cached_stats[emac].rx_unicast_packet += stats.rx.unicast_packet;
    cached_stats[emac].rx_alignment_error += stats.rx.alignment_error;
    cached_stats[emac].rx_frame_length_error += stats.rx.frame_length_error;
    cached_stats[emac].rx_code_error += stats.rx.code_error;
    cached_stats[emac].rx_carrier_sense_error += stats.rx.carrier_sense_error;
    cached_stats[emac].rx_fcs_error += stats.rx.fcs_error;
    cached_stats[emac].rx_undersize_packet += stats.rx.undersize_packet;
    cached_stats[emac].rx_oversize_packet += stats.rx.oversize_packet;
    cached_stats[emac].rx_fragments += stats.rx.fragments;
    cached_stats[emac].rx_jabber += stats.rx.jabber;
    cached_stats[emac].rx_overflow += stats.rx.overflow;
    cached_stats[emac].rx_control_frame += stats.rx.control_frame;
    cached_stats[emac].rx_pause_control_frame += stats.rx.pause_control_frame;
    cached_stats[emac].rx_unknown_opcode += stats.rx.unknown_opcode;
    cached_stats[emac].tx_byte += stats.tx.byte;
    cached_stats[emac].tx_packet += stats.tx.packet;
    cached_stats[emac].tx_frame_64 += stats.tx.frame_64;
    cached_stats[emac].tx_frame_65_127 += stats.tx.frame_65_127;
    cached_stats[emac].tx_frame_128_255 += stats.tx.frame_128_255;
    cached_stats[emac].tx_frame_256_511 += stats.tx.frame_256_511;
    cached_stats[emac].tx_frame_512_1023 += stats.tx.frame_512_1023;
    cached_stats[emac].tx_frame_1024_1518 += stats.tx.frame_1024_1518;
    cached_stats[emac].tx_frame_1519_mtu += stats.tx.frame_1519_mtu;
    cached_stats[emac].tx_fcs_error += stats.tx.fcs_error;
    cached_stats[emac].tx_multicast_packet += stats.tx.multicast_packet;
    cached_stats[emac].tx_broadcast_packet += stats.tx.broadcast_packet;
    cached_stats[emac].tx_unicast_packet += stats.tx.unicast_packet;
    cached_stats[emac].tx_total_collision += stats.tx.total_collision;
    cached_stats[emac].tx_jabber_frame += stats.tx.jabber_frame;
    cached_stats[emac].tx_oversize_frame += stats.tx.oversize_frame;
    cached_stats[emac].tx_undersize_frame += stats.tx.undersize_frame;
    cached_stats[emac].tx_fragments_frame += stats.tx.fragments_frame;
    cached_stats[emac].tx_error += stats.tx.error;
    cached_stats[emac].tx_underrun += stats.tx.underrun;
    cached_stats[emac].tx_excessive_collision += stats.tx.excessive_collision;
    cached_stats[emac].tx_late_collision += stats.tx.late_collision;
    cached_stats[emac].tx_single_collision += stats.tx.single_collision;
    cached_stats[emac].tx_multiple_collision += stats.tx.multiple_collision;
    cached_stats[emac].tx_pause_control_frame += stats.tx.pause_control_frame;
    cached_stats[emac].tx_deferral_packet += stats.tx.deferral_packet;
    cached_stats[emac].tx_excessive_deferral_packet += stats.tx.excessive_deferral_packet;
    cached_stats[emac].tx_control_frame += stats.tx.control_frame;

    memcpy(mac_stats, &cached_stats[emac], sizeof(mac_stats_t));

    /* TODO: unlock */

    return 0;
}

static int port_unimac_stats_clear(mac_dev_t *mac_dev)
{
    rdpa_emac emac = mac_dev->mac_id;
    rdpa_emac_stat_t stats;
    
    mac_hwapi_get_rx_counters(emac, &stats.rx);
    mac_hwapi_get_tx_counters(emac, &stats.tx);

    memset(&cached_stats[emac], 0, sizeof(cached_stats[0]));

    return 0;
}

static int port_unimac_mtu_set(mac_dev_t *mac_dev, int mtu)
{
    rdpa_emac emac = mac_dev->mac_id;

    mac_hwapi_set_rx_max_frame_len(emac, mtu);

    return 0;
}

static int port_unimac_eee_set(mac_dev_t *mac_dev, int enable)
{
    rdpa_emac emac = mac_dev->mac_id;

    mac_hwapi_set_eee(emac, enable);

    return 0;
}

mac_drv_t mac_drv_unimac =
{
    .mac_type = MAC_TYPE_UNIMAC,
    .name = "UNIMAC",
    .init = port_unimac_init,
    .enable = port_unimac_enable,
    .disable = port_unimac_disable,
    .cfg_get = port_unimac_cfg_get,
    .cfg_set = port_unimac_cfg_set,
    .pause_get = port_unimac_pause_get,
    .pause_set = port_unimac_pause_set,
    .stats_get = port_unimac_stats_get,
    .stats_clear = port_unimac_stats_clear,
    .mtu_set = port_unimac_mtu_set,
    .eee_set = port_unimac_eee_set,
};

