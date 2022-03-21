

#ifndef LIB1x_COMMON_H
#define LIB1x_COMMON_H


//--------------------------------------------------
// IEEE 802.1x Implementation
//
// File		: common.h
// Programmer	: Arunesh Mishra
//
// Contains all common declarations and definitions.
// Copyright (c) Arunesh Mishra 2002
// All rights reserved.
// Maryland Information and Systems Security Lab
// University of Maryland, College Park.
//--------------------------------------------------

#include<assert.h>
#include<stdarg.h>
#include<sys/types.h>
#include<stdio.h>
#include <syslog.h>	// david+2006-03-31, for add event to syslog

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef RTL_WPA_CLIENT
#ifndef CONFIG_RTL8186_TR
#define RTL_WPA_CLIENT
	//#define DBG_WPA_CLIENT
#endif
#endif

#ifdef _RTL_WPA_WINDOWS

#else
#include "1x_types.h"
#include "1x_ethernet.h"
#include "1x_kmsm_keydef.h"
#endif

#ifdef RTL_WPA2	
#include "1x_list.h"
#endif 

#ifdef CONFIG_RTL8186_TR
#define _NOTICE	"tag:NOTICE;log_num:13;msg:"
#define _CMD "exlog /tmp/log_web.lck /tmp/log_web"

#define LOG_MSG_NOTICE(fmt, args...) { \
	char tmpbuf[400]; \	
	sprintf(tmpbuf, "%s \"%s" fmt "\"", _CMD, _NOTICE, ## args); \
	system(tmpbuf); \
}
#endif

union PN48 {
	unsigned long long val48;

	struct {
		unsigned char TSC7;
		unsigned char TSC6;
		unsigned char TSC5;
		unsigned char TSC4;
		unsigned char TSC3;
		unsigned char TSC2;
		unsigned char TSC1;
		unsigned char TSC0;
	} _byte_;
};

#define  IP_ADDRSIZE        50

#define INC(X)	{ (X) = (X) + 1; if (X > 255) X = 0; /*write(1, "\n[INC]\n", sizeof("\n[INC]\n"));*/};

#define MESS_BUF_SIZE		512
#define MESS_DBG_AUTH 		1
#define MESS_DBG_AUTHSM 	9
#define MESS_DBG_AUTHNET	8
#define MESS_DBG_KRCSM 		5
#define MESS_DBG_KXSM 		6
#define MESS_DBG_SUPP		2
#define MESS_DBG_NAL		7
#define MESS_DBG_BSM		10
#define MESS_DBG_RAD		11
#define MESS_DBG_PTSM		13
#define MESS_AUTH_LOG 		4
#define MESS_ERROR_OK		16
#define MESS_ERROR_FATAL	17
#define MESS_DBG_SPECIAL        12
#define MESS_DBG_DAEMON		18
#define MESS_DBG_KEY_MANAGE	19
#define MESS_DBG_CONTROL        20	//2003-06-13
#define MESS_DBG_RSNINFO	21
#define MESS_DBG_CONFIG		22
#define MESS_DBG_ACCT		23
#define MESS_DBG_FIFO		24


#define  MAX_SUPPLICANT     	32
#define	MAX_RCV_FIFO		2048
//#define  LIB1X_RAD_SHARED	100



#define	LIB1X_AUTH_INDEX	0xfff
struct  PKT_LSTNR_tag;
struct  PKT_XMIT_tag;

//---- Basic Timer Unit in useconds ----
//#define LIB1X_BASIC_TIMER_UNIT 	100000
// kenny
//#define LIB1X_BASIC_TIMER_UNIT 		1000000
#define LIB1X_BASIC_TIMER_UNIT 		100000
#define	SECONDS_TO_TIMERCOUNT(x)	((x*1000000)/LIB1X_BASIC_TIMER_UNIT)
#define	USECONDS_TO_TIMERCOUNT(x)	(x/LIB1X_BASIC_TIMER_UNIT)
// use the following macro to replace usleep interrupt by timer
#define LIB_USLEEP(x)			{\
						int i;\
				 		for(i=0; i < USECONDS_TO_TIMERCOUNT(x) ; i++)\
				                                 if(usleep(x) == 0)\
									break;\
					}


#define	INC_GLOBAL_SESSION_ID(X)	((X==0xffffffff)?X=0:X++)
typedef struct	Timers_tag
{
	int		authWhile;
				// Used by the Supplicant PAE to determine how long to wait for 
				// a response from the Authenticator.
	int		aWhile;
				// Used by the Backend Authentication state machine in order to
				// determine timeout conditions in the exchanges between the
				// Authenticator and Supplicant or Auth Server.
	int		heldWhile;
				// Used by Supplicant state machine to define periods of time
				// during which it will not attempt to acquire an Authenticator.
	int		quietWhile;
				// During this period Authenticator will not acquire supplicant.
	int		reAuthWhen;
				// A timer used by the Reauthentication Timer state machine in
				// order to determine when re-authentication of the Supplicant
				// takes place.
	int		startWhen;
				// Used by Supplicant PAE state machine to determine when an
				// EAPOL start PDU is to be transmitted. 
	int		txWhen;
	
} Timers;

struct Auth_Pae_tag;
struct Supp_Pae_tag;	// these here to make "# includes" consistent
struct lib1x_ptsm;

//-----------------------------------------------------------------------
// RSN Related
//-----------------------------------------------------------------------
#define DOT11_MAX_ALGORITHMS     0x0a

typedef struct _DOT11_AlgoElement
{
	u_long				Index;
        u_long  			AlgoId;
        BOOLEAN    			Enabled;
}DOT11_AlgoElement;

typedef struct _DOT11_AlgoSuit
{
        u_long                          NumOfAlgo;
        DOT11_AlgoElement               AlgoTable[DOT11_MAX_ALGORITHMS];
}DOT11_AlgoSuit;

typedef struct _DOT11_RSN_AUTHENTICATOR_VARIABLE
{

        //RSN related variable
	OCTET_STRING                    AuthInfoElement;
        BOOLEAN                         isSupportUnicastCipher;
        BOOLEAN                         isSupportMulticastCipher;
        BOOLEAN                         isSupportPreAuthentication;
        BOOLEAN                         isSupportPairwiseAsDefaultKey;
	BOOLEAN				Dot1xEnabled;
	BOOLEAN				MacAuthEnabled;
        BOOLEAN                         RSNEnabled;
#ifdef RTL_WPA2        
	BOOLEAN				WPAEnabled;
	BOOLEAN				WPA2Enabled;
#ifdef CONFIG_RTK_DEV_AP 
	int 				max_pmksa;
#endif
#endif
	BOOLEAN				TSNEnabled;
	int				WepMode;
        int                             NumOfUnicastCipher;
        int                             NumOfAuthCipher;
        DOT11_AlgoSuit                  UniCastCipherSuit;
#ifdef RTL_WPA2        
        DOT11_AlgoSuit                  WPA2UniCastCipherSuit;
#endif
        DOT11_AlgoSuit                  MulticastCipherSuit;
        DOT11_AlgoSuit                  AuthenticationSuit;
        u_char                          NumOfRxTSC;
        u_char                          MulticastCipher;
	u_char                          AuthKeyMethod;
#ifdef CONFIG_IEEE80211W
	enum mfp_options ieee80211w;
	unsigned sha256;	/*HS2_SUPPORT*/
	/* dot11AssociationSAQueryMaximumTimeout (in TUs) */
	unsigned int assoc_sa_query_max_timeout;
	/* dot11AssociationSAQueryRetryTimeout (in TUs) */
	int assoc_sa_query_retry_timeout;
#endif /* CONFIG_IEEE80211W */

	u_char				PassPhrase[64];
// size is not enough because in PasswordHash(), it will use 40 bytes long. 2005-8-8 david
//	u_char				PassPhraseKey[32];
	u_char				PassPhraseKey[40];

	u_char				ssid[64];


}DOT11_RSN_AUTHENTICATOR_VARIABLE;

typedef struct _DOT11_RSN_SUPPLICANT_VARIABLE{
        OCTET_STRING                    SuppInfoElement;
	BOOLEAN                         isSuppSupportUnicastCipher;
        BOOLEAN                         isSuppSupportMulticastCipher;
        BOOLEAN                         isSuppSupportPreAuthentication;
        BOOLEAN                         isSuppSupportPairwiseAsDefaultKey;
        BOOLEAN                         RSNEnabled;
#ifdef RTL_WPA2        
	BOOLEAN				isPreAuth;
	BOOLEAN				WPAEnabled;
	BOOLEAN				WPA2Enabled;
	BOOLEAN				PMKCached;
        struct _WPA2_PMKSA_Node*         cached_pmk_node;
#endif        
        u_char                          UnicastCipher;
        u_char                          MulticastCipher;
		u_char							mgmt_group_cipher;
        u_char                          NumOfRxTSC;
        DOT11_AlgoSuit                  AuthSupportUnicastCipherSuit;
        DOT11_AlgoSuit                  AuthSupportAuthenticationCipherSuit;
        BOOLEAN                         isAuthSupportPreAuthentication;
        BOOLEAN                         isAuthSupportPairwiseAsDefaultKey;
        u_char                          AuthSupportMaxNumOfRxTSC;
}DOT11_RSN_SUPPLICANT_VARIABLE;


//-----------------------------------------------------------------------------
// Radius Key for RSN802dot1x or nonRSN802dot1x
//-----------------------------------------------------------------------------
#define RADIUS_KEY_LEN	64

typedef enum _RADIUS_KEY_STATUS
{
	MPPE_SDRCKEY_NONAVALIABLE = 0x00,
	MPPE_SENDKEY_AVALIABLE = 0x01,
	MPPE_RECVKEY_AVALIABLE = 0x02,
	MPPE_SDRCKEY_AVALIABLE = 0x03,
}RADIUS_KEY_STATUS;

typedef struct _RADIUS_KEY
{
	RADIUS_KEY_STATUS Status;
	OCTET_STRING	  SendKey;
	OCTET_STRING	  RecvKey;
}RADIUS_KEY;





//Added to support WPA
struct Auth_PairwiseKeyManage_tag;
struct Supp_PairwiseKeyManage_tag;
struct Auth_GroupKeyManage_tag;
struct _Dot1x_Authenticator;
struct _Dot1x_Client;
//End Added

typedef struct _Dot11RSNConfigEntry {
	//dot11RSNConfigIndex                     InterfaceIndexOrZero,
	int		Version;
	int		PairwiseKeysSupported;
	OCTET_STRING	MulticastCipher;
	int		GroupRekeyMethod;
	u_long		GroupRekeyTime;
	u_long		GroupRekeyPackets;
	BOOLEAN		GroupRekeyStrict; 
	OCTET_STRING	PSKValue;        
	//u_char*	PSKPassPhrase             DisplayString,
	BOOLEAN		TSNEnabled;
	u_long		GroupMasterRekeyTime;
	u_long		GroupUpdateTimeOut;
	u_long		GroupUpdateCount;
	u_long		PairwiseUpdateTimeOut;
	u_long		PairwiseUpdateCount;
}Dot11RSNConfigEntry;

typedef struct Global_Params_tag
{
	BOOLEAN		authAbort;
	BOOLEAN		authFail;
	BOOLEAN		authStart;
	BOOLEAN		authTimeout;
	BOOLEAN		authSuccess;
	int		currentId;		// Id for current authentication session
	BOOLEAN		initialize;
	PORT_MODE_TYPE	portControl;
	BOOLEAN		portEnabled;
	PORT_STATUS_TYPE 	portStatus;
	BOOLEAN		reAuthenticate;
	int		receivedId;
	PORT_STATUS_TYPE 	suppStatus;

	struct lib1x_ptsm     * timers;

	//ROLE		 currentRole;
	int		index;

	struct Auth_Pae_tag	* theAuthenticator;
	struct Supp_Pae_tag	* theSupplicant;

	struct TxRx_Params_tag	* TxRx;

	//Added to support WPA
	struct Auth_PairwiseKeyManage_tag      *akm_sm;
	struct Supp_PairwiseKeyManage_tag      *skm_sm;

        OCTET_STRING                    EAPOLMsgRecvd;          //The Overall 802.1x message
        OCTET_STRING                    EAPOLMsgSend;           //The Overall 802.1x message
        OCTET_STRING                    EapolKeyMsgRecvd;       //The start point of eapol-key payload
        OCTET_STRING                    EapolKeyMsgSend;
	int			        AuthKeyMethod;
	RADIUS_KEY                      RadiusKey;
        BOOLEAN                         PreshareKeyAvaliable;
#ifdef RTL_WPA2
	// kenny PMK_LEN should be enough
        u_char                          PSK[PMK_LEN];
#else        
        u_char                          PSK[PMK_LEN * 2];
#endif        
        u_char                          MaxRetryCounts;
        u_char                          EventId;
        BOOLEAN                         portSecure;
        u_char                          DescriptorType; //initialize to 254 in RSN
	u_char				KeyDescriptorVer;
        u_char                          CurrentAddress[ETHER_ADDRLEN];
	BOOLEAN				bMacAuthEnabled;
#ifdef CONFIG_IEEE80211W
	BOOLEAN 		mgmt_frame_prot;
#endif

	//RSNIE related variable
	struct _DOT11_RSN_SUPPLICANT_VARIABLE   RSNVariable;
	Dot11RSNConfigEntry		Dot11RSNConfig;

	struct _Dot1x_Authenticator	*auth;
	//End Added WPA

} Global_Params;


typedef struct TxRx_Params_tag
{
	u_char			oursvr_addr[ETHER_ADDRLEN];       // ethernet address of the server interface
	u_char			oursupp_addr[ETHER_ADDRLEN];       // ethernet address of the supplicant interface
	//u_char		supp_addr[ETHER_ADDRLEN];
	u_char			svr_addr[ETHER_ADDRLEN];

	// Device name
	u_char			* device_supp;
	u_char			* device_svr;

	u_char			* device_wlan0;

	// Interface to three daemon (1)ethernet (2)wireless (3)driver
	struct lib1x_nal_intfdesc	* network_svr;
	struct lib1x_nal_intfdesc	* network_supp;
#ifdef RTL_WPA2_PREAUTH
	struct lib1x_nal_intfdesc	* network_ds; // via the DS, i.e. eth0 or br0?
#endif
	int				fd_control;

	FILE			* debugsm;
	struct in_addr	ourip_inaddr, svrip_inaddr, acctip_inaddr;
	u_short			udp_ourport;
	u_short			udp_svrport;
	u_short			udp_acctport;
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
	u_short			udp_dasport;
#endif
	struct sockaddr_in			radsvraddr;
	struct sockaddr_in			acctsvraddr;
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
	struct sockaddr_in			dasouraddr;
#endif
#ifdef RTL_RADIUS_2SET
	struct lib1x_nal_intfdesc	* network_svr2;
	struct in_addr	svrip_inaddr2;
	u_short			udp_svrport2;
	struct sockaddr_in			radsvraddr2;
	u_short			flag_replaced;
#endif

	u_char			GlobalRadId;

	// Added to support fifo architecture
	int				readfifo;
	int				dummyfd;
	u_char			RecvBuf[MAX_RCV_FIFO];
	OCTET_STRING	RListenFIFO;

} TxRx_Params;


typedef enum { DISABLE, 	ENABLE } Switch;

typedef struct  _Dot1x_Supplicant
{
 	int             index;
        BOOLEAN		isEnable;
	BOOLEAN		isEAPCapable;
        //unsigned char   addr[ETHER_ADDRLEN];
        Global_Params   *global;
} Dot1x_Supplicant;


#if 0
typedef struct
{
	unsigned short	aid;
	unsigned char	addr[6];
	unsigned long	tx_packets;
	unsigned long	rx_packets;
	unsigned long	expired_time;	// 10 msec unit
	unsigned short	flags;
	unsigned char	TxOperaRate;
	unsigned char	rssi;
	unsigned long	link_time;		// 1 sec unit
	unsigned long	tx_fail;
} RTL_STA_INFO;
#endif

typedef struct _sta_info_2_web {
	unsigned short	aid;
	unsigned char	addr[6];
	unsigned long	tx_packets;
	unsigned long	rx_packets;
	unsigned long	expired_time;	// 10 msec unit
	unsigned short	flags;
	unsigned char	TxOperaRate;
	unsigned char	rssi;
	unsigned long	link_time;		// 1 sec unit
	unsigned long	tx_fail;
	unsigned long	tx_bytes;
	unsigned long	rx_bytes;
	unsigned char 	resv[8];
} sta_info_2_web;

#define RTL_STA_INFO sta_info_2_web

typedef struct  _Dot1x_Authenticator
{
	int						MaxSupplicant;
	int						NumOfSupplicant;
	ROLE					currentRole;
	TxRx_Params				*GlobalTxRx;
	Dot1x_Supplicant		*Supp[MAX_SUPPLICANT];
	OCTET_STRING			RadShared;            	/* NAS and RADIUS */
	OCTET_STRING			AcctShared;
	LARGE_INTEGER			Dot1xKeyReplayCounter;
	u_long					UsePassphrase;
	u_long					AuthTimerCount;
	u_long					KeyManageTimerCount;
	u_long					SessionInfoTimerCount;	// Abocom
	u_long					IgnoreEAPOLStartCounter;
	u_char					svrip[IP_ADDRSIZE+1];
	u_short					udp_svrport;
#ifdef RTL_RADIUS_2SET
	u_short					use_2nd_rad;
	u_char					svrip2[IP_ADDRSIZE+1];
	u_short					udp_svrport2;
	OCTET_STRING			RadShared2;
#endif
	u_char					acctip[IP_ADDRSIZE+1];
	u_short					udp_acctport;
	u_char					WepGroupKey[32];
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
	u_short					udp_dasport;
#endif
	//Added to support WPA
	struct Auth_GroupKeyManage_tag		*gk_sm;
	OCTET32_INTEGER			Counter;
	u_char					CurrentAddress[ETHER_ADDRLEN];
	DOT11_RSN_AUTHENTICATOR_VARIABLE	RSNVariable;
	Dot11RSNConfigEntry					Dot11RSNConfig;
	u_char					IoctlBuf[1024];
	u_long					IoctlBufLen;
	BOOLEAN					IoctlFlag;
	//end Added

	//Accounting
	u_long					InterimTimeout;
	BOOLEAN					SessionTimeoutEnabled;
	BOOLEAN					IdleTimeoutEnabled;
	BOOLEAN					AccountingEnabled;
	BOOLEAN					UpdateInterimEnabled;
	u_long					GlobalSessionId;
	Dot1x_Supplicant		*authGlobal;
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
	BOOLEAN					DynamicAuthEnable;
#endif
// david, fix to 128. If support sta is greater than 128 in wlan driver,
// this value need be modified.
//	RTL_STA_INFO				StaInfo[MAX_SUPPLICANT+1];
	RTL_STA_INFO			StaInfo[128+1];
//-------------------------------------------------------------------------

	//Server config
	u_long					rsMaxReq;
	u_long					rsAWhile;
	u_long					accountRsMaxReq;
	u_long					accountRsAWhile;

#ifdef RTL_WPA_CLIENT
	struct _Dot1x_Client	*client;
#endif

#ifdef RTL_WPA2
	struct list_head		pmk_cache;
#endif
    
    BOOLEAN                 enableUserId;
    BOOLEAN                 enableCalledId;
} Dot1x_Authenticator;

void lib1x_print_etheraddr( char * s, u_char * addr );
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
int hwaddr_ascii2mac(u_char *tmp_addr, u_char *addr);
int hex2num(char c);
#endif
#ifndef DEBUG_DISABLE //sc_yang
void lib1x_message( int type, char * msg, ... );
void lib1x_hexdump( FILE * fdesc, u_char * pkt, int numBytes );
void lib1x_totext_authpaestate( FILE * fdesc, AUTH_PAE_STATE state );
void lib1x_totext_bauthsmstate( FILE * fdesc, BAUTH_SM_STATE state );
void lib1x_chardump( FILE * fdesc, u_char * pkt, int numBytes );
void lib1x_hexdump2(int type, char *fun, u_char *buf, int size, char *comment);
void lib1x_PrintAddr(u_char *ucAddr);
void DUMP_GLOBAL_PARAMS( Global_Params *g, u_char *exp );
#else
#define lib1x_message(type, msg...)  do{}while(0)
#define lib1x_hexdump(a, b, c)  do{}while(0)
#define lib1x_totext_authpaestate(a, b)  do{}while(0)
#define lib1x_totext_bauthsmstate(a, b)  do{}while(0)
#define lib1x_chardump(a, b, c)  do{}while(0)
#define lib1x_hexdump2(a, b, c, e , f)  do{}while(0)
#define lib1x_PrintAddr(a)  do{}while(0)
#define DUMP_GLOBAL_PARAMS(a, b)  do{}while(0)
#endif

#define PMFDEBUG(fmt, args...) printf("[%s %d]"fmt,__FUNCTION__,__LINE__,## args)
//#define PMFDEBUG(fmt, args...)


//sc_yang
extern void * lib1x_global_signal_info;
	// This variable points to struct lib1x_ptsm , the port timers state machine struct,
// because we need the signal handler to access some global variable.

extern u_char dev_supp[];	// david+2006-03-31, for add event to syslog
	
#ifdef _ABOCOM
#define	ABOCOM_ADD_STA	0
#define ABOCOM_DEL_STA	1
void lib1x_abocom(u_char *pucAddr,  int ulCommandType);
#endif




#define lib1x_Little_S2N(s,c)   (*((c) )=(unsigned char)(((s))&0xff), \
                         	*((c)+1)=(unsigned char)(((s)>>8)&0xff))

#define lib1x_Little_N2S(c,s)   s = 0,\
                         	(s =((unsigned long)(*((c)  ))), \
                         	s|=( (unsigned long) (*((c)+1))<<8)  )

#define lib1x_S2N(s,c)   (*((c) )=(unsigned char)(((s)>>8)&0xff), \
                         *((c)+1)=(unsigned char)(((s)    )&0xff))

#define lib1x_N2S(c,s)   s = 0,\
			 (s =((unsigned long)(*((c)  )))<<8, \
                         s|=((unsigned long)(*((c)+1))))

#define lib1x_L2N(l,c)   (*((c) )=(unsigned char)(((l)>>24)&0xff), \
                         *((c)+1)=(unsigned char)(((l)>>16)&0xff), \
                         *((c)+2)=(unsigned char)(((l)>> 8)&0xff), \
                         *((c)+3)=(unsigned char)(((l)    )&0xff))

#define lib1x_N2L(c,l)   l = 0,\
			 (l =((unsigned long)(*((c)  )))<<24, \
                         l|=((unsigned long)(*((c)+1)))<<16, \
                         l|=((unsigned long)(*((c)+2)))<< 8, \
                         l|=((unsigned long)(*((c)+3))))

//----------------------------------------------------------------
// 1x_kmsm_prf.c
//----------------------------------------------------------------
int PasswordHash (
	char *password,
	int passwordlength,
	unsigned char *ssid,
	int ssidlength,
	unsigned char *output);
	

#ifdef RTL_WPA2	
//----------------------------------------------------------------
// PMK Cache
//----------------------------------------------------------------

struct _WPA2_PMKSA
{
	u_long		SessionTimeout;
 	u_char          pmkid[PMKID_LEN];
// 	u_char          aa[6];	// Authenticator MAC Address 
 	u_char          pmk[PMK_LEN];
 //	u_long		lifetime;
 	u_char		akmp;
  	u_char          spa[ETHER_ADDRLEN];	// Supplicant MAC Address 
	
};

struct _WPA2_PMKSA_Node
{
	struct list_head node;
        struct _WPA2_PMKSA pmksa;
};



#endif /* RTL_WPA2 */

#endif /* LIB1x_COMMON_H */

