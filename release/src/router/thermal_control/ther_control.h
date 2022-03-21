#ifndef _THER_CONTROL_H_
#define _THER_CONTROL_H_

//-----------------------------------------------------------------------------------------
#define DBG_OUT_USER	(1 << 0)
#define DBG_OUT_KERNEL	(1 << 1)

#if defined(__KERNEL__)
    #if 1
	#define therctl_print(fmt, arg...) \
		do { \
			if (priv->pshare->rf_ft_var.dbg & DBG_OUT_KERNEL) \
				printk("%s: "fmt, priv->dev->name, ## arg); \
		}while(0)
    #else
    #define therctl_print(fmt, arg...)
    #endif
#else
    #if 1
    #define therctl_print(fmt, arg...) \
		do { \
			if (info->control.dbg & DBG_OUT_USER) \
				printf("%s: "fmt, info->name, ## arg); \
			}while(0)
    #else
    #define therctl_print(fmt, arg...)
    #endif
#endif

//-----------------------------------------------------------------------------------------
#define SIOCTHERMALCTL			0x900A

#define MAX_TP_LIMIT_LEVEL 3

#define ENABLE_CONTROL	(1 << 0)
#define ENABLE_PROTECT	(1 << 1)

enum func_id {
    THERCTL_GETVAL = 0,
    THERCTL_UPDATE_THER,

    THERCTL_BANDWIDTH,
    THERCTL_TX_DUTY,
    THERCTL_POWER,
    THERCTL_SET_PATH,
    THERCTL_FUNC_OFF,
    THERCTL_LIMIT_TP,

    THERCTL_ID_END, //end
};

enum val_id {
    THERGETVAL_DELTA = 0,
    THERGETVAL_MONITOR_TIME,
    THERGETVAL_THER_HI,
    THERGETVAL_THER_LOW,
    THERGETVAL_MAN,
    THERGETVAL_THER_DM,
    THERGETVAL_DBG,
    THERGETVAL_ALLMIB,

    THERGETVAL_END, //end
};

struct ther_func_s {
    int id;
    union {
        int  val;
        int  sint;
        char schar;
        unsigned int  uint;
        unsigned char uchar;
    };
} __attribute__((packed));

struct ther_by_limittp_s {
	unsigned char	enable;
	unsigned char	val;		//0: default, 1~2: limit level
	unsigned char	pre_val;
};

struct ther_by_funcoff_s {
	unsigned char	enable;
	unsigned char	val;		//0: default, 1: enable funcoff
	unsigned char	pre_val;
};

struct ther_by_txduty_s {
	unsigned char	enable;
	unsigned char	val;		// 0: disable, 1 ~ 10, TxDuty = TxDutyTable - (level-1) * 10
	unsigned char	level;
	unsigned char	pre_val;
};

struct ther_by_path_s {
	unsigned char	enable;
	unsigned char	val;		// 0: as default, 1: use 1T, 2: use 2T, 3: use 3T, 4: use 4T
	unsigned char	pre_val;
};

struct ther_by_power_s {
	unsigned char	enable;
	unsigned char	val;		// 0: as default, 1: turn on dynamic mechanism, 2: maually set power
	unsigned char	pre_val;
};

struct ther_by_bandwidth_s {
	unsigned char	enable;
	unsigned char	val;
	unsigned char	pre_val;
};

struct ther_para_s {
	unsigned char	dbg;
	unsigned char	man;			// 0: default, 1: manually set parameters for testing

	unsigned char	ther_dm;		// 0: turn off thermal control dynamic mechanism; 1: turn on
	unsigned char	state;			// 0: initial, 1: control, 2: protect
	int 			del_ther;		// current ther - calibration ther 
	unsigned char	ther_hi;		// if del_ther >= ther_hi, enable thermal control mechanism
	unsigned char	ther_low;		// if del_ther <= ther_low, disable thermal control mechanism
	unsigned char	ther_max;		// if del_ther >= ther_max, enable thermal protect mechanism

	unsigned int	monitor_time;	// wait monitor_time seconds to check thermal again
	unsigned int	countdown;		// currently left time to monitor
	unsigned int	hitcount_hi;
	unsigned int	hitcount_low;

	unsigned int	protect_hi;
	unsigned int	protect_low;
	
	unsigned char	update_ther;
	unsigned char	pre_ther_dm;
};

struct ther_info_s {
	struct ther_func_s			func;
	struct ther_para_s			control;
	struct ther_by_power_s		power;
	struct ther_by_path_s		txpath;
	struct ther_by_limittp_s	tp;
	struct ther_by_funcoff_s	funcoff;
	struct ther_by_bandwidth_s	bw;
	struct ther_by_txduty_s		fwduty;

	char *name; /* dev name */
} __attribute__((packed));

#if defined(__KERNEL__)
void init_ther_setting(struct rtl8192cd_priv * priv);
#endif

#endif //_THER_CONTROL_H_

