#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <shared.h>
#include <flash_mtd.h>

#include <sysdeps/realtek/realtek.h>

static void
usage(void)
{
	fprintf(stderr, "usage: flash [get name] [set name value]  [all] \n");
	exit(0);
}

/*
 *	Convert the mib data mib_buf, from mib_get(), to a string representation.
 *	Return:
		string
 */
int mib_to_string(char *string, const void *mib, TYPE_T type, int size)
{
	char tmp[16];
	int array_size, i, ret = 1;

	switch (type) {
	case BYTE_T:
		sprintf(string, "%hhu", *(unsigned char *)mib);
		break;

	case WORD_T:
		sprintf(string, "%hu", *(unsigned short *)mib);
		break;

	case DWORD_T:
		sprintf(string, "%u", *(unsigned int *)mib);
		break;

	case INTEGER_T:
		sprintf(string, "%d", *(int *)mib);
		break;

	case BYTE5_T:
	case BYTE6_T:
	case BYTE13_T:
		string[0] = '\0';
		for (i = 0; i < size; i++) {
			sprintf(tmp, "%02x", ((unsigned char *)mib)[i]);
			strcat(string, tmp);
		}
		break;

	case BYTE_ARRAY_T:
		string[0] = '\0';
		for (i = 0; i < size; i++) {
			sprintf(tmp, "%02x", ((unsigned char *)mib)[i]);
			strcat(string, tmp);
		}
		break;

	case WORD_ARRAY_T:
		array_size = size / sizeof(short);

		string[0] = '\0';
		for (i = 0; i < array_size; i++) {
			sprintf(tmp, "%04x", ((unsigned short *)mib)[i]);

			if (i != (array_size - 1))
				strcat(tmp, ",");

			strcat(string, tmp);
		}
		break;

	case INT_ARRAY_T:
		array_size = size / sizeof(int);

		string[0] = '\0';
		for (i = 0; i < array_size; i++) {
			sprintf(tmp, "%08x", ((unsigned int *)mib)[i]);

			if (i != (array_size - 1))
				strcat(tmp, ",");

			strcat(string, tmp);
		}
		break;
	case STRING_T:
		strcpy(string, mib);
		break;

	default:
		ret = -1;
		_dprintf("%s: Unknown data type %d!\n", __FUNCTION__, type);
	}

	return ret;
}

static char *to_hex_string(char *string)
{
	char *tostr;
	int i, k;
	size_t len = strlen(string);

	tostr = malloc(len + 1);
	if (tostr == NULL)
		return NULL;

	for (i = 0, k = 0; i < len; i++) {
		if (string[i] != ',' && string[i] != ' ')
			tostr[k++] = string[i];
	}
	tostr[k] = '\0';

	return tostr;
}

static int string_to_hex(char *string, unsigned char *key, int len)
{
	char tmpBuf[4];
	int idx, ii = 0;

	if (string == NULL || key == NULL)
		return 0;

	for (idx = 0; idx < len; idx += 2) {
		tmpBuf[0] = string[idx];
		tmpBuf[1] = string[idx + 1];
		tmpBuf[2] = 0;

		if (!isxdigit(tmpBuf[0]) || !isxdigit(tmpBuf[1]))
			return 0;

		key[ii++] = strtoul(tmpBuf, NULL, 16);
	}

	return 1;
}

static int string_to_short(char *string, unsigned short *key, int len)
{
	char tmpBuf[5];
	int idx, ii = 0, j;

	if (string == NULL || key == NULL)
		return 0;

	for (idx = 0; idx < len; idx += 4) {
		for (j = 0; j < 4; j++) {
			tmpBuf[j] = string[idx + j];
			if (!isxdigit(tmpBuf[j]))
				return 0;
		}

		tmpBuf[4] = 0;

		key[ii++] = strtoul(tmpBuf, NULL, 16);
	}

	return 1;
}

static int string_to_integer(char *string, unsigned int *key, int len)
{
	char tmpBuf[9];
	int idx, ii = 0, j;

	if (string == NULL || key == NULL)
		return 0;

	for (idx = 0; idx < len; idx += 8) {
		for (j = 0; j < 8; j++) {
			tmpBuf[j] = string[idx + j];
			if (!isxdigit(tmpBuf[j]))
				return 0;
		}

		tmpBuf[8] = 0;

		key[ii++] = strtoul(tmpBuf, NULL, 16);
	}

	return 1;
}

int string_to_mib(void *mib, const char *string, TYPE_T type, int size)
{
	struct in_addr *ipAddr;
	unsigned char *vChar;
	unsigned short *vShort;
	unsigned int *vUInt;
	int *vInt;
	int ret;

	ret = 1;
	switch (type) {
	case IA_T:
		if (!strlen(string)) {
			string = "0.0.0.0";
		}
		ipAddr = mib;
		if (inet_pton(AF_INET, string, ipAddr) == 0)
			ret = -1;
		break;
	case BYTE_T:
		vChar = mib;
		*vChar = strtoul(string, NULL, 0);
		break;
	case WORD_T:
		vShort = mib;
		*vShort = strtoul(string, NULL, 0);
		break;
	case DWORD_T:
		vUInt = mib;
		*vUInt = strtoul(string, NULL, 0);
		break;
	case INTEGER_T:
		vInt = mib;
		*vInt = strtol(string, NULL, 0);
		break;
	case BYTE_ARRAY_T:
		string = to_hex_string((char *)string);	// remove comma and blank
		string_to_hex((char *)string, mib, size * 2);
		free((char *)string);
		break;
	case BYTE5_T:
	case BYTE6_T:
	case BYTE13_T:
		string_to_hex((char *)string, mib, size * 2);
		break;
	case STRING_T:
		strncpy(mib, string, size);
		break;
	case WORD_ARRAY_T:
		string = to_hex_string((char *)string);	// remove comma and blank
		string_to_short((char *)string, mib, size * 2);
		free((char *)string);
		break;
	case INT_ARRAY_T:
		string = to_hex_string((char *)string);	// remove comma and blank
		string_to_integer((char *)string, mib, size * 2);
		free((char *)string);
		break;
	default:
		ret = -1;
		_dprintf("Unknown data type !\n");
		break;
	}

	return ret;
}


int flash_get(char* name)
{
	int offset = 0, size = 0;
	int ret = 0;
	TYPE_T type = 0;
	unsigned char mibvalue[1024];
	char buffer[2048];
	
	memset(buffer, 		0, sizeof(buffer));
	memset(mibvalue, 	0, sizeof(mibvalue));

	ret = flash_get_mib_info(name, &offset, &size, &type);

	if(!ret) {
		cprintf("%s: cannot find %s\n", __FUNCTION__, name);
		return -1;
	}

	if(size >= sizeof(mibvalue)){
		cprintf("mibvalue oversize, need %d but max %d\n", size, sizeof(mibvalue));
		return -1;
	}

	ret = FRead(mibvalue, offset, size);
	
	if(ret < 0)
	{
		_dprintf("flash read error\n");
		return -1;
	}
	if(strstr(name, "REG_DOMAIN")) {
		mibvalue[2] = '\0';
		int tmp = 0;
		if(strstr(name, "WLAN0"))
			tmp = 2;
		else if(strstr(name, "WLAN1"))
			tmp = 1;
		snprintf(buffer, sizeof(buffer), "%d", get_regdomain_from_countrycode(mibvalue, tmp));
		ret = 1;
	} else
		ret = mib_to_string(buffer, mibvalue, type, size);
	
	if(ret)
		printf("%s=%s\n", name, buffer);
	
	return ret;
}

int flash_set(char* name,char* value)
{
	int offset = 0, size = 0;
	int ret = 0;
	TYPE_T type = 0;
	unsigned char mibvalue[1024];
	
	memset(mibvalue, 0, sizeof(mibvalue));

	if(value == NULL) {
		cprintf("%s: invalid input %s\n", __FUNCTION__, name);
		return -1;
	}

	ret = flash_get_mib_info(name, &offset, &size, &type);
	if(!ret) {
		cprintf("%s: cannot find %s\n", __FUNCTION__, name);
		return -1;
	}
	
	ret = string_to_mib(mibvalue, value, type, size);

	if(ret)
		printf("set %s=%s\n", name, value);

	if(offset < OFFSET_MAC_ADDR_2G) { // do not update MAC address
		FWrite(mibvalue, offset, size);
	}

	return 0;
}

int flash_dump()
{
	int i=0;

	for(i=0;mib_table[i].name[0];i++){
		flash_get(mib_table[i].name);
	}

	return 0;
}

int main(int argc, char **argv)
{
	int i  = 0;
	char *name, *value;
	char mib_string[513];
	memset(mib_string, 0, sizeof(mib_string));
	/* Skip program name */
	//--argc;
	//++argv;

	if (!argv[1]) 
		usage();

		if (!strncmp(argv[1], "get", 3)) {
			if (argv[2]) {
				flash_get(argv[2]);
			}
		}
		else if (!strncmp(argv[1], "set", 3)) {
			if(argc > 4) {
				for(i = 3; i < argc; i++) {
					if(!strncmp(argv[2], "RF_DPK_LUT_2G", 13)){
						snprintf(mib_string, sizeof(mib_string), "%s%08x", mib_string, atoi(argv[i]));
					}
					else
						snprintf(mib_string, sizeof(mib_string), "%s%02x", mib_string, atoi(argv[i]));
				}
				flash_set(argv[2], mib_string);
			} else if(argc == 4){			
				flash_set(argv[2],argv[3]);
			}
		}
		else if (!strncmp(argv[1], "all", 3)) {
			flash_dump();
		}
		return 0;
}
