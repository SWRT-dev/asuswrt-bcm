
#ifndef _CONFIG_PARSE_H
#define _CONFIG_PARSE_H

#define CONFIG_PARSE_TAG 80
#define CONFIG_PARSE_VALUE 80

typedef enum {  ERROR_FILE_NOTEXIST = -1, ERROR_UNDEFINE_PARAMETER = -2,
	ERROR_UNDEFINE_TAG = -3 } CONFIG_ERROR_ID;


#define CFG_STRERROR_FILE_NOTEXIST		"Configuration file not exist"
#define CFG_STRERROR_UNDEFINE_PARAMETER		"Undefine parameter in configuration file"
#define CFG_STRERROR_UNDEFINE_TAG		"Undefine tag in configuration file"

typedef enum { tagUnicastCipher = 0, tagMulticastCipher = 1, tagAuthKeyMethod = 2} CONFIG_TAG_TABLE;

u_char ConfigTag[][32] =
{
	"ssid",
	"encryption",
	"enable1x",
	"enableMacAuth",
	"supportNonWpaClient",
	"wepKey",
	"wepGroupKey",
	"authentication",
	"unicastCipher",
#ifdef RTL_WPA2
	"wpa2UnicastCipher",
	"enablePreAuth",
#endif
	"usePassphrase",
	"groupRekeyTime",
	"psk",
	"rsPort",
	"rsIP",
	"rsPassword",
#ifdef RTL_RADIUS_2SET
	"rs2Port",
	"rs2IP",
	"rs2Password",
#endif
	"rsMaxReq",
	"rsAWhile",
	"rsNasId",
	"accountRsEnabled",
	"accountRsPort",
	"accountRsIP",
	"accountRsPassword",
	"accountRsMaxReq",
	"accountRsAWhile",
	"accountRsUpdateEnabled",
	"accountRsUpdateTime",
#ifdef CONFIG_IEEE80211W
	"ieee80211w",
	"sha256",
#endif
    "EnableUserId",
    "EnableCalledId",
};


/**
 * Reads a tag out of a file in the form
 *   tag = value
 *
 * return 0 on success -1 on fail
 */
int configParse(char *, /* File name */
		char *, /* Tag */
		char * /* value */
		);

#endif /* _CONFIG_PARSE_H_ */

/*** EOF ***/
