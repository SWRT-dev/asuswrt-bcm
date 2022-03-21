/*
 * ASUSTek Proprietary and Confidential. Copyright (C) 2016,
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of ASUSTeK;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of ASUSTek.
 */

#ifndef _rtk_wifi_eventd_h_
#define _rtk_wifi_eventd_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <linux/genetlink.h>
#include <sys/socket.h>
#include "shared.h"
#include "shutils.h"
#define NETLINK_ASUS_EVENTD 30
#define MAX_PAYLOAD 1024
#define ASUS_EVENTD_HDR_LEN sizeof(asusEventHdr)

enum {
	WEVENT_DEVICE_CONNECTED = 1,
	WEVENT_DEVICE_DISCONNECTED,
	WEVENT_DEVICE_PROBE_REQ,
	WEVENT_DEVICE_RADAR_DETECTED,
	WEVENT_RRM_BEACON_REPORT
};

/* Debug Print */
int wlceventd_msglevel;
#define WLCEVENTD_DEBUG_ERROR	0x000001
#define WLCEVENTD_DEBUG_WARNING	0x000002
#define WLCEVENTD_DEBUG_INFO	0x000004
#define WLCEVENTD_DEBUG_EVENT	0x000008
#define WLCEVENTD_DEBUG_DETAIL	0x000010
#define WLCEVENTD_DEBUG_DBG	0x000020

#ifdef RTCONFIG_LIBASUSLOG
#include <libasuslog.h>

int diag_syslog = 0;

#define DBG_LOG "wlcevent.log"
#define DBG

#define WLC_LOG(fmt, arg...) \
	do { \
		if (wlceventd_msglevel & WLCEVENTD_DEBUG_DBG) \
			dbG("%lu: "fmt, uptime(), ##arg); \
		if(diag_syslog) \
			asusdebuglog(LOG_INFO, DBG_LOG, LOG_CUSTOM, LOG_SHOWTIME, 0, fmt, ##arg); \
	} while (0)

#define WLCEVENTD_ERROR(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_ERROR) \
		WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_WARNING(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_WARNING) \
		WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_INFO(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_INFO) \
		WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_EVENT(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_EVENT) \
		WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_DEBUG(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_DETAIL) \
		WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_PRINT(fmt, arg...) \
	do { WLC_LOG("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)
#else
#define WLCEVENTD_ERROR(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_ERROR) \
		printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_WARNING(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_WARNING) \
		printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_INFO(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_INFO) \
		printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_EVENT(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_EVENT) \
		printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_DEBUG(fmt, arg...) \
	do { if (wlceventd_msglevel & WLCEVENTD_DEBUG_DETAIL) \
		printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)

#define WLCEVENTD_PRINT(fmt, arg...) \
	do { printf("WLCEVENTD %s(%d): "fmt, __FUNCTION__, __LINE__, ##arg); \
	} while (0)
#endif
#endif /* _wifi_assoc_eventd_h_ */
