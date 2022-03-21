/*
 * ASUSTeK Proprietary and Confidential. Copyright (C) 2016,
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of ASUSTeK;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of ASUSTeK.
 */


#ifdef RTCONFIG_CFGSYNC
#include <cfg_lib.h>
#include <cfg_event.h>
#endif

#include "rtk_wifi_eventd.h"
#include "json.h"
#include <wlioctl.h>
//#include <bcmendian.h>
#define MACF_UP	"%02X:%02X:%02X:%02X:%02X:%02X"
#define MACF	"%02x:%02x:%02x:%02x:%02x:%02x"

#define ETHERP_TO_MACF(ea)	((struct ether_addr *) (ea))->octet[0], \
				((struct ether_addr *) (ea))->octet[1], \
				((struct ether_addr *) (ea))->octet[2], \
				((struct ether_addr *) (ea))->octet[3], \
				((struct ether_addr *) (ea))->octet[4], \
				((struct ether_addr *) (ea))->octet[5]
#define ETHER_TO_MACF(ea)	(ea).octet[0], \
				(ea).octet[1], \
				(ea).octet[2], \
				(ea).octet[3], \
				(ea).octet[4], \
				(ea).octet[5]


typedef struct asusevent_netlink 
{
	int eventID;	
	char name[16];
	unsigned char data[0];
}asusEventHdr;

void rast_update_beacon_report(struct ether_addr *sta, struct ether_addr *bssid, char rcpi) {
	json_object *root = NULL;
	json_object *existApObj = NULL;
	json_object *reportApObj = NULL;
	int lock;
	char rcpiStr[4];
	char ap_mac[]="xx:xx:xx:xx:xx:xx";
	char path[]="/tmp/xx:xx:xx:xx:xx:xx_bcn_rpt";

	snprintf(path, sizeof(path), "/tmp/"MACF_UP"_bcn_rpt", ETHERP_TO_MACF(sta));
	snprintf(rcpiStr, sizeof(rcpiStr), "%d", rcpi);
	snprintf(ap_mac, sizeof(ap_mac), MACF_UP, ETHERP_TO_MACF(bssid));

	lock = file_lock(path+5);
	root = json_object_from_file(path);
	if(!root) {
		//RAST_DBG("%s,no file or valid content\n", path);
		goto end;
	}

	json_object_object_get_ex(root, ap_mac, &existApObj);
	if (existApObj) {
		//RAST_DBG("report AP is exist\n");
		goto end;
	}

	reportApObj = json_object_new_object();
	if (!reportApObj) {
		//RAST_DBG("reportApObj is NULL\n");
		goto end;
	}

	json_object_object_add(reportApObj, RAST_RCPI, json_object_new_string(rcpiStr));
	json_object_object_add(root, ap_mac, reportApObj);
	json_object_to_file(path, root);

end:
	json_object_put(root);
	file_unlock(lock);

}

int main() 
{	
	struct sockaddr_nl src_addr, dest_addr;
	struct nlmsghdr *nlh = NULL;
	struct iovec iov;
	int sock_fd=0;
	int retval = 0;
	char *val;
	struct msghdr msg;
	int len = 0;
#if 1
	int num = 0, i = 0;
#endif
#ifdef RTCONFIG_CFGSYNC
	char event_msg[384] = {0};
	char vsie[256] = {0};
	
#endif	
#ifdef RTCONFIG_LIBASUSLOG
	diag_syslog = nvram_get_int("diag_syslog");
	val = nvram_get("wlceventd_msglevel");
	if (val)
		wlceventd_msglevel = strtoul(val, NULL, 0);
#endif
	char msgBuf[256]={0};
	asusEventHdr *pEventdHdr=(asusEventHdr *)msgBuf;

	pEventdHdr->eventID=0;
	strcpy(pEventdHdr->name, "br0");
	strcpy(pEventdHdr->data, "ASUS EVENTD START!");	
	
	sock_fd=socket(PF_NETLINK, SOCK_RAW, NETLINK_ASUS_EVENTD);
	if(sock_fd<0)
	{
		printf("%s:%d ##create netlink socket fail!\n",__FUNCTION__,__LINE__);
		goto ERROR_EXIT;
	}
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid(); /* self pid */
	src_addr.nl_groups = 0; /* not in mcast groups */

	retval = bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));
       if(retval < 0){
           printf("bind failed: %s", __FUNCTION__);
           close(sock_fd);
           return -1;
       }
	
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0; /* For Linux Kernel */
	dest_addr.nl_groups = 0; /* unicast */
	
	nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));	
	if(nlh==NULL)
		goto ERROR_EXIT;
	
	/* Fill the netlink message header */
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
	nlh->nlmsg_pid = getpid(); /* self pid */
	nlh->nlmsg_flags = 0;	
	
	memcpy(NLMSG_DATA(nlh), msgBuf, strlen(pEventdHdr->data)+ASUS_EVENTD_HDR_LEN);

	memset(&msg, 0, sizeof(msg));
	memset(&iov, 0, sizeof(iov));
	
	iov.iov_base = (void *)nlh;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	sendmsg(sock_fd, &msg, 0);
	//apmib_init();
	/* Read message from kernel */
	while(1)
	{
		val = nvram_safe_get("wlceventd_msglevel");
		if(*val)
			wlceventd_msglevel = strtoul(val, NULL, 0);

		memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
		recvmsg(sock_fd, &msg, 0);
		
#ifdef RTCONFIG_CFGSYNC
		memset(event_msg, 0, sizeof(event_msg));
#endif
		pEventdHdr=NLMSG_DATA(nlh);		
		switch (pEventdHdr->eventID) {
			case WEVENT_DEVICE_CONNECTED:
				WLCEVENTD_EVENT("Device Connected %s %s\n", pEventdHdr->data, pEventdHdr->name);
#ifdef RTCONFIG_CFGSYNC
				snprintf(event_msg, sizeof(event_msg), WEVENT_MAC_IFNAME_MSG,
				EID_WEVENT_DEVICE_CONNECTED, pEventdHdr->data, pEventdHdr->name);
				send_cfgmnt_event(event_msg);
#endif
				break;
			case WEVENT_DEVICE_DISCONNECTED:
				WLCEVENTD_EVENT("Device DisConnected %s %s\n", pEventdHdr->data, pEventdHdr->name);
#ifdef RTCONFIG_CFGSYNC 
				snprintf(event_msg, sizeof(event_msg), WEVENT_MAC_IFNAME_MSG,
				EID_WEVENT_DEVICE_DISCONNECTED, pEventdHdr->data, pEventdHdr->name);
				send_cfgmnt_event(event_msg);
#endif
				break;
			case WEVENT_DEVICE_RADAR_DETECTED:
				WLCEVENTD_EVENT("Radar detected\n");
#ifdef RTCONFIG_CFGSYNC
				snprintf(event_msg, sizeof(event_msg), WEVENT_GENERIC_MSG, 
				EID_WEVENT_DEVICE_RADAR_DETECTED);
				send_cfgmnt_event(event_msg);
#endif
#ifdef RTCONFIG_AMAS
				nvram_set("radar_detected", "1");
#endif			
				break;
			case WEVENT_DEVICE_PROBE_REQ:
				WLCEVENTD_EVENT("Probe Req\n");
#ifdef RTCONFIG_CFGSYNC
				if(nvram_get_int("cfg_obstatus") != 2) break;
				memset(vsie, 0, sizeof(vsie));

				len = *(pEventdHdr->data+1);
				if(len < 3 ) break;
				if (hex2str(pEventdHdr->data+5, &vsie[0], len-3)) {
					snprintf(event_msg, sizeof(event_msg), WEVENT_VSIE_MSG,
							EID_WEVENT_DEVICE_PROBE_REQ, vsie);
					send_cfgmnt_event(event_msg);
				}
				WLCEVENTD_EVENT("vsie %s\n", vsie);
#endif
				break;
			case WEVENT_RRM_BEACON_REPORT:
				WLCEVENTD_DEBUG("WEVENT_RRM_BEACON_REPORT \n");
				struct ether_addr sta, bssid;
				memcpy(&sta, pEventdHdr->data, 6);
				WLCEVENTD_DEBUG("sta:"MACF_UP"\n", ETHER_TO_MACF(sta));
				num = pEventdHdr->data[6];
				WLCEVENTD_DEBUG("num %d\n", num);

				len = 7;
				for(i=0; i<num; i++) {
					memcpy(&bssid, pEventdHdr->data+len, 6);
					rast_update_beacon_report(&sta, &bssid, pEventdHdr->data[len+6]);
					WLCEVENTD_DEBUG("bssid:"MACF_UP"\n", ETHER_TO_MACF(bssid));
					WLCEVENTD_DEBUG("rcpi: %d\n", (char)pEventdHdr->data[len+6]);
					len+=7;
				}
				break;
				
			default:
				WLCEVENTD_EVENT("eventID is %d\n", pEventdHdr->eventID);
				break;
		}
		//sleep(1);
	}
ERROR_EXIT:
	/* Close Netlink Socket */
	if(sock_fd>0)
		close(sock_fd);	
	if(nlh)
		free(nlh);
	return 0;
}




