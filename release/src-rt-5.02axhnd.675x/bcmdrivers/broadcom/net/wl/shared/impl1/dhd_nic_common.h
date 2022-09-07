/*
    Copyright (c) 2017 Broadcom
    All Rights Reserved

    <:label-BRCM:2017:DUAL/GPL:standard

    Unless you and Broadcom execute a separate written software license
    agreement governing use of this software, this software is licensed
    to you under the terms of the GNU General Public License version 2
    (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
    with the following added to such license:

       As a special exception, the copyright holders of this software give
       you permission to link this software with independent modules, and
       to copy and distribute the resulting executable under terms of your
       choice, provided that you also meet, for each linked independent
       module, the terms and conditions of the license of that module.
       An independent module is a module which is not derived from this
       software.  The special exception does not apply to any modifications
       of the software.

    Not withstanding the above, under no circumstances may you combine
    this software in any way with any other Broadcom software provided
    under a license other than the GPL, without Broadcom's express prior
    written consent.

    :>
*/

#ifndef __DHD_NIC_COMMON_H__
#define __DHD_NIC_COMMON_H__

#include <linux/netdevice.h>
#include <linux/skbuff.h>

typedef struct {
    uint tx_tag_nobuf;
    uint tx_fkb_pool_nobuf;
    uint tx_dup_nobuf;
} nbuff_counters_t;

typedef struct {
	osl_pubinfo_t pub;
	nbuff_counters_t nbuff_counters;
	uint16 unit;
	uint16 reg_swizzle;
	int databuf_cache_idx;
	void **databuf_cache;
} osl_pubinfo_nbuff_t;

#ifdef BCM_NBUFF_WLMCAST
enum WLEMF_CMD {
    WLEMF_CMD_GETIGSC,         //get igsc instance
    WLEMF_CMD_SCBFIND,     //find scb by mac
    WLEMF_CMD_GETDEV,
    WLEMF_CMD_PKTDUP,
    WLEMF_CMD_ADD_STA_IP,
    WLEMF_CMD_STA_OFFLOAD_CHECK,   //to check if sta is using hw_ring for multicast
    WLEMF_CMD_PKTFREE
};
#endif

#ifndef netdev_wlan_set
#define netdev_wlan_set(_dev)           (_dev)->priv_flags |= IFF_BCM_WLANDEV
#endif

#ifndef netdev_wlan_unset
#define netdev_wlan_unset(_dev)         (_dev)->priv_flags &= ~IFF_BCM_WLANDEV
#endif

#ifndef is_netdev_wlan
#define is_netdev_wlan(_dev)            ((_dev)->priv_flags & IFF_BCM_WLANDEV)
#endif

#ifndef netdev_wlan_client_get_info
#define netdev_wlan_client_get_info(dev) ((dev)->wlan_client_get_info)
#endif

#ifdef bcm_netdev_ext_field_get
#define bcm_netdev_blog_stats_flags(dev)  bcm_netdev_ext_field_get(dev,blog_stats_flags)
#else
#define bcm_netdev_blog_stats_flags(dev)  (dev)->blog_stats_flags
#endif

#ifndef skbuff_bcm_ext_wlan_get
#define skbuff_bcm_ext_wlan_get(skb,f) (skb)->f
#endif

/* identify wlif type */
#define FLAG_DWDS_AP            1
#define FLAG_DWDS_CLIENT        2

#define netdev_wlan_set_dwds_ap(wlif)           ((wlif)->flags = FLAG_DWDS_AP)
#define netdev_wlan_unset_dwds_ap(wlif)         ((wlif)->flags &= ~FLAG_DWDS_AP)
#define is_netdev_wlan_dwds_ap(wlif)            ((wlif)->flags & FLAG_DWDS_AP)

#define netdev_wlan_set_dwds_client(wlif)       ((wlif)->flags = FLAG_DWDS_CLIENT)
#define netdev_wlan_unset_dwds_client(wlif)     ((wlif)->flags &= ~FLAG_DWDS_CLIENT)
#define is_netdev_wlan_dwds_client(wlif)        ((wlif)->flags & FLAG_DWDS_CLIENT)

#ifdef BCM_DHD_LOCK
#if defined(BCM_ROUTER_DHD) && defined(BCM_GMAC3)
#define DHD_LOCK(dhdp)        dhd_perim_lock(dhdp)
#define DHD_UNLOCK(dhdp)      dhd_perim_unlock(dhdp)
#else
#define DHD_LOCK(dhdp)        do {} while (0)
#define DHD_UNLOCK(dhdp)      do {} while (0)
#endif /* BCM_ROUTER_DHD && BCM_GMAC3 */
#endif /* BCM_DHD_LOCK */

/* check if virtual wlan net deivce */
#define check_virt_wlan(_dev)  ( !(_dev) || !netdev_path_is_root(_dev) || \
	((_dev)->priv_flags & IFF_BCM_VLAN) || ((_dev)->priv_flags & IFF_802_1Q_VLAN) )

#endif /* __DHD_NIC_COMMON_H__ */
