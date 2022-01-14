/*

	Copyright 2005, Broadcom Corporation
	All Rights Reserved.

	THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
	KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
	SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.

*/

#include "rc.h"
#include "shared.h"
#include "interface.h"

#include <termios.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <time.h>
#include <errno.h>
#include <paths.h>
#include <sys/wait.h>
#include <sys/reboot.h>
#include <sys/klog.h>
#ifdef LINUX26
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#endif
#include <wlutils.h>
#include <bcmdevs.h>
#ifdef RTCONFIG_RTL8198D
#include "realtek.h"
#include "flash_mtd.h"
#endif
#define MKNOD(name,mode,dev)	if(mknod(name,mode,dev)) perror("## mknod " name)

void init_devs(void)
{
//	system("mknod /dev/nvram ");
	MKNOD("/dev/nvram", S_IFCHR | 0x666, makedev(228, 0));
	{
		int status;
		if((status = WEXITSTATUS(modprobe("nvram_linux"))))	printf("## modprove(nvram_linux) fail status(%d)\n", status);
	}
}

void rtl_configRps(void)
{
	system("mount -t sysfs sysfs /sys");
	system("echo 2 > /sys/class/net/eth0/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/eth1/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/eth2/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/eth3/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/eth4/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl0/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl0.0/queues/rx-0/rps_cpus");		
	system("echo 2 > /sys/class/net/wl0.1/queues/rx-0/rps_cpus");		
	system("echo 2 > /sys/class/net/wl0.2/queues/rx-0/rps_cpus");	
	system("echo 2 > /sys/class/net/wl0.3/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl1/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl1.0/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl1.1/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl1.2/queues/rx-0/rps_cpus");
	system("echo 2 > /sys/class/net/wl1.3/queues/rx-0/rps_cpus");
	system("echo 4096 > /sys/class/net/eth0/queues/rx-0/rps_flow_cnt");
	system("echo 4096 > /sys/class/net/eth1/queues/rx-0/rps_flow_cnt");
	system("echo 4096 > /sys/class/net/eth2/queues/rx-0/rps_flow_cnt");
	system("echo 4096 > /sys/class/net/eth3/queues/rx-0/rps_flow_cnt");
	system("echo 4096 > /sys/class/net/eth4/queues/rx-0/rps_flow_cnt");
	system("echo 4096 > /proc/sys/net/core/rps_sock_flow_entries");
}


#if !defined(RTCONFIG_RTL8198D)
void init_igmpsnooping()
{
    char command[32] = {0};
    //snprintf(command, sizeof(command), "echo %d > /proc/br_igmpsnoop", nvram_get_int("emf_enable"));
    snprintf(command, sizeof(command), "echo 1 > /proc/br_igmpsnoop");
    //_dprintf("init_igmpsnooping: command = %s\n", command);
    system(command);
}
#endif

/**
 * @brief      Check if the nvram value is normal.
 *
 * @return     Values are normal, return 0. Values are unusual, return 1.
 */
int rtk_check_nvram_partation(void)
{
	char buf[MAX_NVRAM_SPACE] = {0};
	char *name = NULL;
	int i = 0;
	nvram_getall(buf, sizeof(buf));

	for (name = buf; *name; name += strlen(name) + 1) {
		for (i = 0; i < strlen(name) + 1; i++) {
			if (*(name + i) == 0xffffffff) {
				printf("\nInvalid nvram...Restore default\n");
				return 1;
			}
		}
	}
	return 0;
}

void init_switch()
{
	char *mac_addr;
	char word[PATH_MAX], *next_word;
	mac_addr = nvram_safe_get("et0macaddr");

	foreach(word, nvram_safe_get("lan_ifnames"), next_word) {
		if (!strncmp(word, "eth", 3)) {
			doSystem("ifconfig %s hw ether %s", word, mac_addr);
		}
	}

#ifdef RTCONFIG_ATEFROMWAN
	if(repeater_mode() && !nvram_get_int("x_Setting")) {
		doSystem("ifconfig %s %s", nvram_safe_get("wan_ifnames"), nvram_safe_get("wan_ate_ipaddr"));
	}
#endif
	mac_addr = nvram_safe_get("et1macaddr");

	if(strlen(nvram_safe_get("wan0_ifname")))
		doSystem("ifconfig %s hw ether %s", nvram_safe_get("wan0_ifname"), mac_addr);
#ifndef RTCONFIG_RTL8198D
	if (!is_router_mode())
		doSystem("echo \"2\" > /proc/hw_nat");
	init_igmpsnooping();
#endif
}

char *get_lan_hwaddr(void)
{
	/* TODO: handle exceptional model */
        return nvram_safe_get("et0macaddr");
}

void init_syspara(void)
{

#ifdef RTCONFIG_ODMPID
	char modelname[16];
	getflashMN(modelname, sizeof(modelname));

	if (modelname[0] != 0 && (unsigned char)(modelname[0]) != 0xff
	    && is_valid_hostname(modelname)
	    && strcmp(modelname, "ASUS")) {
		nvram_set("odmpid", modelname);
	} else
#endif
		nvram_unset("odmpid");

	nvram_set("firmver", rt_version);
	nvram_set("productid", rt_buildname);
	set_basic_fw_name();

	set_country_code();
#ifdef RTCONFIG_TCODE
	set_territory_code();
#endif
#ifdef RTCONFIG_AMAS
    init_amas_bdl();
#endif
#if defined(RTCONFIG_RTL8198D)
	init_smp();
#endif
}


void init_wl(void)
{
}

void fini_wl(void)
{
}

void config_switch()
{
}

int switch_exist(void)
{
	FILE *fp;
	char out[64];

	system("echo 'physt 1' > /proc/asus_ate");
	fp = popen("cat /proc/asus_ate", "r");
	if (fp) {
		fgets(out, sizeof(out),fp);
		pclose(fp);
		if (strlen(out))
			return 1;
	}
	return 0;
}

int wl_exist(char *ifname, int band)
{
	char file[64];
	int ret = 1;
	
	memset(file, 0, sizeof(file));
	snprintf(file, sizeof(file), "/proc/%s/stats", ifname);

	if(!f_exists(file))
		ret = 0;

	return ret; 
}

char *get_wlifname(int unit, int subunit, int subunit_x, char *buf)
{
#if defined(RTCONFIG_REALTEK) && defined(RTCONFIG_AMAS)
	// for AMAS router use
	if(sw_mode() == SW_MODE_AP && nvram_match("re_mode", "1") && subunit == 1)
		sprintf(buf, "wl%d", unit);
	else
#endif
	sprintf(buf, "wl%d.%d", unit, subunit);
	return buf;
}

void generate_wl_para(int unit, int subunit)
{
}

void stop_wds_rtk(const char* lan_ifname, const char* wif)
{
}
#ifdef RTCONFIG_RTL8198D
int get_mac_2g(unsigned char dst[])
{
	int bytes = 6;
	if (FRead(dst, OFFSET_MAC_ADDR_2G, bytes) < 0) {  // ET0/WAN is same as 2.4G
		_dprintf("%s: Fread Out of scope\n", __func__);
		return -1;
	}
	if(dst[0] == 0xFF)
		return -1;
	return 0;
}

int get_mac_5g(unsigned char dst[])
{
	int bytes = 6;
	if (FRead(dst, OFFSET_MAC_ADDR_5G, bytes) < 0) { // ET1/LAN is same as 5G
		_dprintf("%s: Fread Out of scope\n", __func__);
		return -1;
	}
	if(dst[0] == 0xFF)
		return -1;
	return 0;
}

#if defined(RPAC92)
int get_mac_5g_2(unsigned char dst[])
{
	int bytes = 6;
	if (FRead(dst, OFFSET_MAC_ADDR_5G_2, bytes) < 0) { // ET1/LAN is same as 5G
		_dprintf("%s: Fread Out of scope\n", __func__);
		return -1;
	}
	if(dst[0] == 0xFF)
		return -1;
	return 0;
}
#endif

#endif


