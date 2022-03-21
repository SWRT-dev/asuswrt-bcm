#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/wireless.h>

#include "ther_control.h"

//-----------------------------------------------------------------------------------------
#define STATE_INIT 0
#define STATE_THERMAL_CONTROL 1
#define STATE_THERMAL_PROTECT 2

#define	THER_HIT_COUNT		30
#define	PROTECT_HIT_COUNT	5

#define NUM_WLAN_INTERFACE	3

struct ther_info_s wlan0 = {
	.name = "wlan0",
	.control.ther_max = 90,
	.control.ther_hi  = 80,
	.control.ther_low = 20,
	.tp.enable = 1,
	.funcoff.enable = 1,
	.fwduty.enable = 0,
	.fwduty.level = 5,
	.txpath.enable = 0,
	.power.enable = 0,
};

#if (NUM_WLAN_INTERFACE > 1)
struct ther_info_s wlan1 = {
	.name = "wlan1",
	.control.ther_max = 90,
	.control.ther_hi  = 80,
	.control.ther_low = 20,
	.tp.enable = 1,
	.funcoff.enable = 1,
	.fwduty.enable = 0,
	.fwduty.level = 5,
	.txpath.enable = 0,
	.power.enable = 0,
};
#endif

#if (NUM_WLAN_INTERFACE > 2)
struct ther_info_s wlan2 = {
	.name = "wlan2",
	.control.ther_max = 90,
	.control.ther_hi  = 80,
	.control.ther_low = 20,
	.tp.enable = 1,
	.funcoff.enable = 1,
	.fwduty.enable = 0,
	.fwduty.level = 5,
	.txpath.enable = 0,
	.power.enable = 0,
};
#endif

//-----------------------------------------------------------------------------------------
void thermal_ctl(struct ther_info_s *info, int idx, int value)
{
	int skfd;
	struct iwreq wrq;
	struct ther_func_s *func = &info->func;
	skfd = socket(AF_INET, SOCK_DGRAM, 0);

	strncpy(wrq.ifr_name, info->name, IFNAMSIZ);
	
	/* check exist */
	if (ioctl(skfd, SIOCGIWNAME, &wrq) < 0) {
		perror("SIOCGIWNAME, Error: ");
		goto fail;
	}

	func->id = idx;
	func->val = value;

	if (idx == THERCTL_GETVAL && value == THERGETVAL_ALLMIB) {
		wrq.u.data.pointer = (void *)info;
		wrq.u.data.length = sizeof(struct ther_info_s);
	}
	else {
		wrq.u.data.pointer = (void *)func;
		wrq.u.data.length = sizeof(struct ther_func_s);
	}

	if (ioctl(skfd, SIOCTHERMALCTL, &wrq) < 0) {
		perror("SIOCTHERMALCTL, Error: ");
		goto fail;
	}

fail:
	close(skfd);
}

void set_update_ther(struct ther_info_s *info, int val)
{
	info->control.update_ther = val;
	thermal_ctl(info, THERCTL_UPDATE_THER, val);
}

void set_bandwidth(struct ther_info_s *info, int val)
{
	if (val != info->bw.pre_val) {
		therctl_print("%s Bandwidth degradation\n", val?"Enable":"Disable");
		info->bw.pre_val = val;
		thermal_ctl(info, THERCTL_BANDWIDTH, val);
	}
}

void set_txduty(struct ther_info_s *info, int val)
{
	if (val != info->fwduty.pre_val) {
		if (val)
			therctl_print("Enable FW Tx Duty Cycle, level %d\n", info->fwduty.level);
		else
			therctl_print("Disable FW Tx Duty Cycle\n");

		info->fwduty.pre_val = val;
		thermal_ctl(info, THERCTL_TX_DUTY, val);
	}
}

void set_power(struct ther_info_s *info, int val)
{
	if (val != info->power.pre_val) {
		therctl_print("%s Tx power degradation\n", val?"Enable":"Disable");
		info->power.pre_val = val;
		thermal_ctl(info, THERCTL_POWER, val);
	}
}

void set_path(struct ther_info_s *info, int val)
{
	if (val != info->txpath.pre_val) {
		therctl_print("%s 1T\n", val?"Enable":"Disable");
		info->txpath.pre_val = val;
		thermal_ctl(info, THERCTL_SET_PATH, val);
	}
}

void set_funcoff(struct ther_info_s *info, int val)
{
	if (val != info->funcoff.pre_val) {
		therctl_print("%s funcoff\n", val?"Enable":"Disable");
		info->funcoff.pre_val = val;
		thermal_ctl(info, THERCTL_FUNC_OFF, val);
	}
}

void set_limit_tp(struct ther_info_s *info, int val)
{
	if (val != info->tp.pre_val) {
		if (val)
			therctl_print("Enable Tx Duty Cycle with Level %d\n", info->tp.val);
		else
			therctl_print("Disable Tx Duty Cycle\n");
		info->tp.pre_val = val;
		thermal_ctl(info, THERCTL_LIMIT_TP, val);
	}
}

int getval_del_ther(struct ther_info_s *info)
{
	thermal_ctl(info, THERCTL_GETVAL, THERGETVAL_DELTA);
	return info->func.sint;	
}

unsigned char getval_allmib(struct ther_info_s *info)
{
	thermal_ctl(info, THERCTL_GETVAL, THERGETVAL_ALLMIB);

	return 0;
}

//-----------------------------------------------------------------------------------------
void tcd_enter_thermal_protect_state(struct ther_info_s *info)
{
	therctl_print("Enable Thermal Protect\n");
	info->control.state = STATE_THERMAL_PROTECT;
	system("echo 'ther_control_status: 2' > /var/ther_control_status");

	if (info->funcoff.enable) {
		info->funcoff.val = 1;
	}
	else {
		if (info->power.enable) {
			info->power.val = 2;
		}
		if (info->txpath.enable) {
			info->txpath.val = 1;
		}
		if (info->fwduty.enable) {
			info->fwduty.val = 1+info->fwduty.level;
		}
		if (info->bw.enable) {
			info->bw.val = 1;
		}
	}
}

void tcd_exit_thermal_protect_state(struct ther_info_s *info)
{
	therctl_print("Disable Thermal Protect\n");
	info->control.state = STATE_INIT;
	system("echo 'ther_control_status: 0' > /var/ther_control_status");

	clean_ther_dm(info);
	return 0;
}

int thermal_protect(struct ther_info_s *info)
{
	int ret = 0;

	if (!(info->control.ther_dm & ENABLE_PROTECT))
		goto exit_protect;

	if (info->control.state != STATE_THERMAL_PROTECT) {
		if (info->control.del_ther >= info->control.ther_max)
			info->control.protect_hi++;
		else
			info->control.protect_hi = 0;

		if (info->control.protect_hi > PROTECT_HIT_COUNT) {
			tcd_enter_thermal_protect_state(info);
			ret = 1;
		}
	} else {
		if (info->control.del_ther <= info->control.ther_hi)
			info->control.protect_low++;
		else
			info->control.protect_low = 0;

		if (info->control.protect_low > PROTECT_HIT_COUNT) {
			tcd_exit_thermal_protect_state(info);
			ret = 1;
		}
	}

	if (ret) {
		info->control.hitcount_hi  = 0;
		info->control.hitcount_low = 0;
		info->control.protect_hi   = 0;
		info->control.protect_low  = 0;
	}

exit_protect:
	return ret;
}

void apply_ther_dm(struct ther_info_s *info)
{
	if (info->tp.enable) {
		set_limit_tp(info, info->tp.val);
	}
	if (info->power.enable) {
		set_power(info, info->power.val);
	}
	if (info->txpath.enable) {
		set_path(info, info->txpath.val);
	}
	if (info->funcoff.enable) {
		set_funcoff(info, info->funcoff.val);
	}	
	if (info->fwduty.enable) {
		set_txduty(info, info->fwduty.val);
	}	
	if (info->bw.enable) {
		set_bandwidth(info, info->bw.val);
	}
}

void clean_ther_dm(struct ther_info_s *info)
{
	therctl_print("Clean Thermal DM\n");
	info->control.state = STATE_INIT;
	system("echo 'ther_control_status: 0' > /var/ther_control_status");

	if (info->tp.enable) {
		info->tp.val = 0;
		info->tp.pre_val = 1;
	}
	if (info->funcoff.enable) {
		info->funcoff.val = 0;
		info->funcoff.pre_val = 1;
	}
	if (info->power.enable) {
		info->power.val = 0;
		info->power.pre_val = 1;
	}
	if (info->txpath.enable) {
		info->txpath.val = 0;
		info->txpath.pre_val = 1;
	}
	if (info->fwduty.enable) {
		info->fwduty.val = 0;
		info->fwduty.pre_val = 1;
	}
	if (info->bw.enable) {
		info->bw.val = 0;
		info->bw.pre_val = 1;
	}
	info->control.hitcount_hi = 0;
	info->control.hitcount_low = 0;
}

//-----------------------------------------------------------------------------------------
void tcd_enter_init_state(struct ther_info_s *info)
{
	therctl_print("Enter Initial State\n");
	info->control.state = STATE_INIT;
	system("echo 'ther_control_status: 0' > /var/ther_control_status");

	if (info->tp.enable) {
		info->tp.val = 0;
	}
}

void tcd_enter_thermal_control_state(struct ther_info_s *info)
{
	therctl_print("Enter Thermal Control State\n");
	info->control.state = STATE_THERMAL_CONTROL;
	system("echo 'ther_control_status: 1' > /var/ther_control_status");

	if (info->tp.enable) {
		info->tp.val = 1;
	}

	info->control.countdown = info->control.monitor_time; /* wait monitor_time then to check */
}

void tcd_state_init_dm(struct ther_info_s *info)
{
	if (info->control.hitcount_hi >= THER_HIT_COUNT) {
		info->control.hitcount_hi = 0;
		tcd_enter_thermal_control_state(info);
	}
}

void tcd_state_thermal_control_dm(struct ther_info_s *info)
{
	if(info->control.countdown)
		info->control.countdown--;

	/* thermal reduced to expected ther_low, release thermal control */
	if (info->control.hitcount_low >= THER_HIT_COUNT) {
		tcd_enter_init_state(info);
		info->control.hitcount_low = 0;
	} else if(info->control.countdown == 0) {/*already monitored for monitor_time */
		info->control.countdown = info->control.monitor_time;

		if (info->tp.enable) {
			if (info->tp.val < MAX_TP_LIMIT_LEVEL) {
				info->tp.val++;
				therctl_print("Upgrade Limit Level %d\n", info->tp.val);
			}
			else {
				therctl_print("Already Limit Level %d\n", info->tp.val);
			}
		}
	}
}

void tcd_update_del_ther(struct ther_info_s *info)
{
	char str[5];
	if (info->control.update_ther == 0) {
		set_update_ther(info, 1);
	}
	else {
		set_update_ther(info, 0);
		info->control.del_ther = getval_del_ther(info);    
	}

	sprintf(str, "%d", info->control.state);
	therctl_print("[%d] Ther:%d, hit[hi-%d low-%d], pro[hi-%d low-%d] (state-%s max-%d hi-%d low-%d)\n",
		info->control.countdown, info->control.del_ther,
		info->control.hitcount_hi, info->control.hitcount_low,
		info->control.protect_hi, info->control.protect_low,
		info->control.ther_dm?str:"X", info->control.ther_max, info->control.ther_hi, info->control.ther_low);
}

void tcd_ther_dm_switch(struct ther_info_s *info)
{
	if (!(info->control.ther_dm & ENABLE_CONTROL))
		return;

	if (info->control.state == STATE_INIT) {
		if (info->control.del_ther >= info->control.ther_hi)
			info->control.hitcount_hi++;
		else if (info->control.hitcount_hi)
			info->control.hitcount_hi--;
		tcd_state_init_dm(info);
	} else if (info->control.state == STATE_THERMAL_CONTROL) {
		if (info->control.del_ther <= info->control.ther_low)
			info->control.hitcount_low++;
		else if (info->control.hitcount_low)
			info->control.hitcount_low--;
		tcd_state_thermal_control_dm(info);
	}
}

void tcd_thermal_control_dm(struct ther_info_s *info)
{
	/* get delta thermal  */
	if(!info->control.man)
		tcd_update_del_ther(info);

	/* decides mechanism on off*/
	if (info->control.ther_dm != info->control.pre_ther_dm) {
		clean_ther_dm(info);
	}
	if (info->control.ther_dm) {
		if (thermal_protect(info) == 0) {
			tcd_ther_dm_switch(info);
		}
	}
	info->control.pre_ther_dm = info->control.ther_dm;

	apply_ther_dm(info);
}
//-----------------------------------------------------------------------------------------
int iface_num = 0;
struct ther_info_s *wlan[NUM_WLAN_INTERFACE] = { 
	&wlan0
	#if (NUM_WLAN_INTERFACE > 1)
	, &wlan1
	#endif
	#if (NUM_WLAN_INTERFACE > 2)
	, &wlan2 
	#endif
	};

void read_config(char *path)
{
	struct ther_info_s *info;
	int i, ther_max=0, ther_hi=0, ther_low=0;
	int funcoff=0, fwduty=0, txpath=0, power=0;
	char name[16], buffer[1255];
	FILE* fp;

	printf("-----------------------------------------------------------------------------------\n");
	fp = fopen(path, "r");
	while(fgets(buffer, 1255, (FILE*) fp)) {
		sscanf(buffer, "%s %d %d %d %d %d %d %d %d",
				name, &i, &ther_low, &ther_hi, &ther_max, &funcoff, &fwduty, &txpath, &power);
		if (0)printf("==> { %s,  %d,	  %d,	 %d,	%d, 	   %d,		  %d,		 %d },\n",
				name, ther_low, ther_hi, ther_max, funcoff, fwduty, txpath, power);

		for (i=0; i<iface_num ; i++) {
			info = wlan[i];
			if (strcmp(name, info->name) == 0) {
				info->tp.enable = 1;
				info->funcoff.enable = funcoff;
				info->fwduty.enable = fwduty;
				info->txpath.enable = txpath;
				info->power.enable = power;
			
				info->control.ther_max = ther_max;
				info->control.ther_hi  = ther_hi;
				info->control.ther_low = ther_low;

				printf("%s: ther_low=%d, ther_hi=%d, ther_max=%d (funcoff=%d fwduty=%d txpath=%d power=%d)\n", 
					info->name, info->control.ther_low, info->control.ther_hi, info->control.ther_max,
					info->funcoff.enable, info->fwduty.enable, info->txpath.enable, info->power.enable);
				break;
			}
		}
	}
	printf("-----------------------------------------------------------------------------------\n\n\n");
	fclose(fp);

    return 0;
}

int main(int argc, char **argv)
{
	int i;
	struct ther_info_s *info;

	if (argc >= 2) {
		iface_num = atoi(argv[1]);
		read_config("/etc/ther.conf");
		for (i=0; i<iface_num ; i++) {
			info = wlan[i];
			getval_allmib(info);
			info->control.pre_ther_dm == info->control.ther_dm;
			clean_ther_dm(info);
			apply_ther_dm(info);
		}

		while (1) {
			for (i=0; i<iface_num ; i++) {
				info = wlan[i];
				getval_allmib(info);
				tcd_thermal_control_dm(info);
			}
			sleep(1);
		}
	}
	else {
		printf("Usage: ther_control WLAN_IFACE_NUM &\n");
	}

	return 0;
}

