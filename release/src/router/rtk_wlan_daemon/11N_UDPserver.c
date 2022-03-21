//=============================================================================
// Copyright (c) 2006 Realtek Semiconductor Corporation.	All Rights Reserved.
//
//	Title:
//		UDPserver.c
//	Desc:
//		UDP server : accepts MP commands from the client
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/wireless.h>
#include <fcntl.h>
//#include <rtk/options.h>
#include <unistd.h>
#include <ctype.h>

//#ifdef CONFIG_DUALBAND_CONCURRENT
//#define ENABLE_WLAN1_MP 1
//#elif defined(CONFIG_USE_PCIE_SLOT_0) && defined(CONFIG_USE_PCIE_SLOT_1)
//#define ENABLE_WLAN1_MP 1
//#endif

#if defined(CONFIG_YUEME) && defined(CONFIG_DUALBAND_CONCURRENT)
#define SWAP_WLAN_MIB_INDEX		1
#elif defined(SWAP_HW_WLAN_MIB_INDEX)
#if defined(CONFIG_CMCC) || defined(CONFIG_CU) || defined(CONFIG_YUEME)
#define SWAP_WLAN_MIB_INDEX		1
#endif
#endif

//#if defined(CONFIG_RTL_TRIBAND_SUPPORT)
//#define ENABLE_WLAN2_MP 1
//#endif

#ifndef WIN32
#define __PACK__			__attribute__ ((packed))
#else
#define __PACK__
#endif


#define MYPORT 9034                    // the port users will be connecting to
#define BUFLEN 4098                      // length of the buffer
#define MP_TX_PACKET 0x8B71
#define MP_BRX_PACKET 0x8B73
#define MP_QUERY_STATS 	0x8B6D
#define RTL8190_IOCTL_WRITE_REG				0x89f3
#define RTL8190_IOCTL_READ_REG				0x89f4
#define MP_CONTIOUS_TX	0x8B66
#define MP_TXPWR_TRACK	0x8B6E
#define MP_QUERY_TSSI	0x8B6F
#define MP_QUERY_THER 0x8B77
#define MP_SET_DPK		0x8BFD
#define MP_QUERY_RSSI 0x8BEF

#define FLASH_DEVICE_NAME		("/dev/mtd")
#define FLASH_DEVICE_NAME1		("/dev/mtdblock1")
#define HW_SETTING_HEADER_TAG		((char *)"hs")
#define HW_SETTING_OFFSET		0x6000
#define DEFAULT_SETTING_OFFSET		0x8000
#define CURRENT_SETTING_OFFSET		0xc000

/*
 * Wrapper to extract some Wireless Parameter out of the driver
 */
static inline int iw_get_ext(int skfd,    /* Socket to the kernel */
							 char *ifname,        	/* Device name */
							 int request,        		/* WE ID */
							 struct iwreq *pwrq)    /* Fixed part of the request */
{
	strncpy(pwrq->ifr_name, ifname, IFNAMSIZ);	/* Set device name */
	return(ioctl(skfd, request, pwrq));			/* Do the request */
}

int MP_get_ext(char *ifname, char *buf, unsigned int ext_num)
{
	int skfd;
	struct iwreq wrq;

	skfd = socket(AF_INET, SOCK_DGRAM, 0);
	wrq.u.data.pointer = (caddr_t)buf;
	wrq.u.data.length = strlen(buf);

	if (iw_get_ext(skfd, ifname, ext_num, &wrq) < 0) {
		printf("MP_get_ext failed\n");
		return -1;
	}
	
	close(skfd);
	return 0;
}

void reset_dev_stat(void)
{
	system("echo all > /proc/realtek/netdev_reset");
}

//the value is included in the 2nd line
//and need transfer to decimal from hex (match MP_TEST.exe's format)
void get_read_reg_value( FILE *fp, char *buf, int maxlen )
{
	int cget,value,start;
	unsigned char *p, *p2;

	p=strchr( buf, '\n' );
	if(p==NULL) return;
	p2=p;

	value=0;start=0;
	while( (cget=fgetc(fp))!=EOF )
	{
		//printf( "get=%c\n", cget );
		if( (cget=='\n') || (cget==' ') )
		{
			if(start) p2 += sprintf( p2, "%d ", value );
			//printf( "start=%d, value=%d, buf=(%s)\n", start, value, buf );
			value=0;
			start=0;
		}else if( isxdigit(cget) )
		{
			start=1;
			//printf( "value=%d,", value );
			if( cget>='0' && cget<='9' )
				value=value*16+(cget-'0');
			else if( cget>='a' && cget<='f' )
				value=value*16+(10+cget-'a');
			else if( cget>='A' && cget<='F' )
				value=value*16+(10+cget-'A');
			//printf( "new value=%d\n", value );
		}else{
			//error
			sprintf( p, "\n", value );
			return;
		}
	}
	*p2=0;
}

void get_mp_dpk_value( FILE *fp, char *buf, int maxlen )
{
	int cget;
	unsigned char *p, *p2;

	p = strchr( buf, '\n' );
	if (p == NULL) return;
	p2 = p;

	while( (cget=fgetc(fp))!=EOF )
	{
		if (cget == '\n')
			*p2++ = ' ';
		else
			*p2++ = cget;
	}
	*p2 = 0;
}

int main(void) {
	int sockfd;                     				// socket descriptors
	struct sockaddr_in my_addr;     		// my address information
	struct sockaddr_in their_addr;  			// connector¡¦s address information
	int addr_len, numbytes;
	FILE *fp;
	char buf[BUFLEN], buf_tmp[BUFLEN],
			pre_result[BUFLEN];				// buffer that stores message
	static char cmdWrap[BUFLEN];
	static int rwHW=0;
	static int ret_value=0;
	int isshortmsg;
	int dot;
	// create a socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	my_addr.sin_family = AF_INET;         		// host byte order
	my_addr.sin_port = htons(MYPORT);     	// short, network byte order
	my_addr.sin_addr.s_addr = INADDR_ANY; 	// automatically fill with my IP
	memset(&(my_addr.sin_zero), '\0', 8); 	// zero the rest of the struct

	// bind the socket with the address
	if (bind(sockfd, (struct sockaddr *)&my_addr,
			 sizeof(struct sockaddr)) == -1) {
		perror("bind");
		close(sockfd);
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	printf("MP AUTOMATION daemon (ver 1.3)\n");

	// main loop : wait for the client
	while (1) {
		//receive the command from the client
		memset(buf, 0, BUFLEN);
		memset(cmdWrap, 0, BUFLEN);
		rwHW = 0;
		isshortmsg=0;
		if ((numbytes = recvfrom(sockfd, buf, BUFLEN, 0,
								 (struct sockaddr *)&their_addr, &addr_len)) == -1) {
			fprintf(stderr,"Receive failed!!!\n");
			close(sockfd);
			exit(1);
		}
		
		fprintf(stderr,"received command (%s) from IP:%s\n", buf, inet_ntoa(their_addr.sin_addr));

		if(strncmp(buf,"cat",3) == 0)
		{
			for(dot=0;dot<strlen(buf);dot++)
				if(buf[dot] == '.')
				{
					buf[dot] = ' ';
					break;
				}
		}
#ifdef CONFIG_NO_WLAN_DRIVER
		char *offset;
		if((offset = strstr(buf, "wlan0")) != NULL)
			offset[4] = '1';
#endif
		
		if (!memcmp(buf, "ther", 4)) {
			strcpy(buf, pre_result);
		}
		if (!memcmp(buf, "tssi", 4)) {
			strcpy(buf, pre_result);
		}
		if (!memcmp(buf, "query", 5)) {

			strcpy(buf, pre_result);
		}
		if(!memcmp(buf, "cat", 3)){

			strcat(buf, " > /tmp/MP.txt");
			system(buf);
		}
#if 1
		if (!memcmp(buf, "iwpriv wlan0 mp_tssi", 20)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan0", buf_tmp, MP_QUERY_TSSI);
			strcpy(buf, buf_tmp);
			printf("buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan0 mp_ther", 20)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan0", buf_tmp, MP_QUERY_THER);

			isshortmsg=1;
			memset(buf, 0, BUFLEN);

			strcpy(buf, buf_tmp);
			printf("buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan0 mp_rssi", 20) && buf[20] == ' ') {

			memcpy(buf_tmp, buf+21, strlen(buf)-21);
			MP_get_ext("wlan0", buf_tmp, MP_QUERY_RSSI);
			strcpy(buf, buf_tmp);
			printf("rssi buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan0 mp_query", 21)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan0", buf_tmp, MP_QUERY_STATS);
			strcpy(buf, buf_tmp);
			usleep(1000);
			printf("2b= %s\n",buf);
		}
#if 1
		else if (!memcmp(buf, "iwpriv wlan1 mp_tssi", 20)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan1", buf_tmp, MP_QUERY_TSSI);
			strcpy(buf, buf_tmp);
			printf("buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan1 mp_ther", 20)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan1", buf_tmp, MP_QUERY_THER);
			strcpy(buf, buf_tmp);
			printf("buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan1 mp_rssi", 20) && buf[20] == ' ') {

			memcpy(buf_tmp, buf+21, strlen(buf)-21);
			MP_get_ext("wlan1", buf_tmp, MP_QUERY_RSSI);
			strcpy(buf, buf_tmp);
			printf("rssi buf= %s\n",buf);
			usleep(1000);
		}
		else if (!memcmp(buf, "iwpriv wlan1 mp_query", 21)) {

			strcpy(buf, pre_result);
			MP_get_ext("wlan1", buf_tmp, MP_QUERY_STATS);
			strcpy(buf, buf_tmp);
			usleep(1000);
			printf("w1 2b= %s\n",buf);
		}
#endif /*ENABLE_WLAN1_MP*/	
#if 1
       else if (!memcmp(buf, "iwpriv wlan2 mp_tssi", 20)) {

            strcpy(buf, pre_result);
            MP_get_ext("wlan2", buf_tmp, MP_QUERY_TSSI);
            strcpy(buf, buf_tmp);
            printf("buf= %s\n",buf);
            usleep(1000);
        }
        else if (!memcmp(buf, "iwpriv wlan2 mp_ther", 20)) {

            strcpy(buf, pre_result);
            MP_get_ext("wlan2", buf_tmp, MP_QUERY_THER);
            strcpy(buf, buf_tmp);
            printf("buf= %s\n",buf);
            usleep(1000);
        }
        else if (!memcmp(buf, "iwpriv wlan2 mp_rssi", 20) && buf[20] == ' ') {
                
            memcpy(buf_tmp, buf+21, strlen(buf)-21);
            MP_get_ext("wlan2", buf_tmp, MP_QUERY_RSSI);
            strcpy(buf, buf_tmp);
            printf("rssi buf= %s\n",buf);
            usleep(1000);
        }
        else if (!memcmp(buf, "iwpriv wlan2 mp_query", 21)) {

            strcpy(buf, pre_result);
            MP_get_ext("wlan2", buf_tmp, MP_QUERY_STATS);
            strcpy(buf, buf_tmp);
            usleep(1000);
            printf("w2 2b= %s\n",buf);
        }       
#endif /*ENABLE_WLAN2_MP*/  
#endif
		else {

			if ( (!memcmp(buf, "flash read", 10)) ){
				if ((fp = fopen("/tmp/MP.txt", "r")) == NULL)
					fprintf(stderr, "opening MP.txt failed !\n");
				
				if (fp) {
					fgets(buf, BUFLEN, fp);
					buf[BUFLEN-1] = '\0';
					{	//fix read_reg bug
						char strread[]="wlan0     read_reg:\n";
						char strreadrf[]="wlan0     read_rf:\n";
						char strpsd[]="wlan0     mp_psd:\n";
						char stradc[]="wlan0     mp_adc:\n";
						char strversion[]="wlan0     mp_version:\n";
						char strdpk[]="wlan0     mp_dpk:\n";
						char strreadsync[]="wlan0     read_syn:\n";
						char strreadde[]="wlan0     read_de:\n";
#if 1
						char strpsd1[]="wlan1     mp_psd:\n";
						char stradc1[]="wlan1	  mp_adc:\n";
						char strread1[]="wlan1     read_reg:\n";
						char strreadrf1[]="wlan1     read_rf:\n";
						char strversion1[]="wlan1     mp_version:\n";
						char strdpk1[]="wlan1     mp_dpk:\n";
						char strreadsync1[]="wlan1     read_syn:\n";
						char strreadde1[]="wlan1     read_de:\n";
#endif /*ENABLE_WLAN1_MP*/
#if 1
                        char strpsd2[]="wlan2     mp_psd:\n";
                        char stradc2[]="wlan2     mp_adc:\n";
                        char strread2[]="wlan2     read_reg:\n";
                        char strreadrf2[]="wlan2     read_rf:\n";
                        char strversion2[]="wlan2     mp_version:\n";
                        char strdpk2[]="wlan2     mp_dpk:\n";
                        char strreadsync2[]="wlan2     read_syn:\n";
                        char strreadde2[]="wlan2     read_de:\n";
#endif /*ENABLE_WLAN2_MP*/
						if( strncmp(buf,strread,strlen(strread))==0 )
							get_read_reg_value( fp, buf, BUFLEN );
						if( strncmp(buf,strreadrf,strlen(strreadrf))==0 )
							get_read_reg_value( fp, buf, BUFLEN );
						if( strncmp(buf,strreadde,strlen(strreadde))==0 )
							get_read_reg_value( fp, buf, BUFLEN );	
						if( strncmp(buf,strpsd,strlen(strpsd))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,stradc,strlen(stradc))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strreadsync,strlen(strreadsync))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strversion,strlen(strversion))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strdpk,strlen(strdpk))==0 ) {
							get_mp_dpk_value( fp, buf, BUFLEN );
						}
#if 1
						if( strncmp(buf,strpsd1,strlen(strpsd1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,stradc1,strlen(stradc1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strreadsync1,strlen(strreadsync1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strread1,strlen(strread1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strreadrf1,strlen(strreadrf1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strreadde1,strlen(strreadde1))==0 )
							get_read_reg_value( fp, buf, BUFLEN );
						if( strncmp(buf,strversion1,strlen(strversion1))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strdpk1,strlen(strdpk1))==0 ) {
							get_mp_dpk_value( fp, buf, BUFLEN );
						}
#endif /*ENABLE_WLAN1_MP*/
#if 1
                        if( strncmp(buf,strpsd2,strlen(strpsd2))==0 ) {
                            get_read_reg_value( fp, buf, BUFLEN );
                        }
                        if( strncmp(buf,stradc2,strlen(stradc2))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
						if( strncmp(buf,strreadsync2,strlen(strreadsync2))==0 ) {
							get_read_reg_value( fp, buf, BUFLEN );
						}
                        if( strncmp(buf,strread2,strlen(strread2))==0 ) {
                            get_read_reg_value( fp, buf, BUFLEN );
                        }
                        if( strncmp(buf,strreadrf2,strlen(strreadrf2))==0 ) {
                            get_read_reg_value( fp, buf, BUFLEN );
                        }
                        if( strncmp(buf,strreadde2,strlen(strreadde2))==0 )
							get_read_reg_value( fp, buf, BUFLEN );
                        if( strncmp(buf,strversion2,strlen(strversion2))==0 ) {
                            get_read_reg_value( fp, buf, BUFLEN );
                        }                       
                        if( strncmp(buf,strdpk2,strlen(strdpk2))==0 ) {
                            get_mp_dpk_value( fp, buf, BUFLEN );
                        }       
#endif /*ENABLE_WLAN2_MP*/
					}
					fclose(fp);
				}

#if 0
				if(!memcmp(buf, "HW_WLAN", 7)){
					if(buf[7]=='0') buf[7] = '1';
					else if (buf[7]=='1') buf[7] = '0';
				}
#endif
				if( strncmp(buf, "RF_DPK_", 7)==0 ) {
					int i, j;
					char *pch, *pdst, *token;
					const char *delim = ",";
					strcpy(buf_tmp, buf);
					if( strncmp(buf_tmp, "RF_DPK_LUT", 10)==0 ) { // remove comma, pad to 8 char
						pch = strchr(buf_tmp, '=') + 1;
						pdst = strchr(buf, '=') + 1;
						*pdst = '\0';
						token = strtok(pch, delim);
						while (token != NULL) {
							for (i=8; i>strlen(token); i--)
								strcat(pdst, "0");
							strcat(pdst, token);
							token = strtok(NULL, delim);
						}
					} else { // remove comma
						strcpy(buf_tmp, buf);
						for (i=0, j=0; i<strlen(buf_tmp); i++)
							if (buf_tmp[i] != ',')
								buf[j++] = buf_tmp[i];
						buf[j] = '\0';
					}
				}
				sprintf(pre_result, "data:%s", buf);
				printf("pre_result=%s\n",pre_result);
			}
			//ack to the client
			else if (!memcmp(buf, "flash get", 9))
				sprintf(pre_result, "%s > /tmp/MP.txt ok", buf);
			else {
				sprintf(pre_result, "%s ok", buf);;
			}
			
			if (!memcmp(buf, "iwpriv wlan0 mp_brx stop", 24)) {
				strcpy(buf, "stop");
				MP_get_ext("wlan0", buf, MP_BRX_PACKET);
			}
			else if (!memcmp(buf, "iwpriv wlan0 mp_tx", 18) && buf[18] == ' ') {
				memcpy(buf_tmp, buf+19, strlen(buf)-19);
				MP_get_ext("wlan0", buf_tmp, MP_TX_PACKET);
				strcpy(buf, buf_tmp);
			}
			
			else if (!memcmp(buf, "iwpriv wlan0 mp_ctx", 19) && buf[19] == ' ') {
				memcpy(buf_tmp, buf+20, strlen(buf)-20);
				MP_get_ext("wlan0", buf_tmp, MP_CONTIOUS_TX);
				strcpy(buf, buf_tmp);;
			}
			else if(!memcmp(buf, "iwpriv wlan0 read_reg", 21)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);
			}
			else if(!memcmp(buf, "iwpriv wlan0 read_rf", 20)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);
			}
			else if(!memcmp(buf, "iwpriv wlan0 read_de", 20)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);		
			}
			else if(!memcmp(buf, "iwpriv wlan0 read_syn", 21)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);		
			}
                        else if(!memcmp(buf, "iwpriv wlan0 efuse_get", 22)){
                                strcat(buf, " > /tmp/MP.txt");
                                system(buf);
                        }
                        else if(!memcmp(buf, "iwpriv wlan0 efuse_set", 22)){
                                strcat(buf, " > /tmp/MP.txt");
                                system(buf);
                        }
                        else if(!memcmp(buf, "iwpriv wlan0 efuse_sync", 23)){
                                strcat(buf, " > /tmp/MP.txt");
                                system(buf);
                        }
			else if(!memcmp(buf, "iwpriv wlan0 mp_psd", 19)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);
			}
			else if(!memcmp(buf, "iwpriv wlan0 mp_dpk", 19)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);
			}
			else if (!memcmp(buf, "probe", 5))
				strcpy(buf, "ack");
			else if (!memcmp(buf, "verify_flw", 10)) {
				if ((fp = fopen("/tmp/MP.txt", "r")) == NULL)
					fprintf(stderr, "opening MP.txt failed !\n");

				if (fp) {
					fgets(buf, BUFLEN, fp);
					buf[BUFLEN-1] = '\0';
					fclose(fp);
				}
			}
#if 1
			else if (!memcmp(buf, "iwpriv wlan1 mp_brx stop", 24)) {
				strcpy(buf, "stop");
				MP_get_ext("wlan1", buf, MP_BRX_PACKET);
			}
			else if (!memcmp(buf, "iwpriv wlan1 mp_tx", 18) && buf[18] == ' ') {
				memcpy(buf_tmp, buf+19, strlen(buf)-19);
				MP_get_ext("wlan1", buf_tmp, MP_TX_PACKET);
				strcpy(buf, buf_tmp);
			}
			
		else if (!memcmp(buf, "iwpriv wlan1 mp_ctx", 19) && buf[19] == ' ') {
			memcpy(buf_tmp, buf+20, strlen(buf)-20);
			MP_get_ext("wlan1", buf_tmp, MP_CONTIOUS_TX);
			strcpy(buf, buf_tmp);;
		}
		else if(!memcmp(buf, "iwpriv wlan1 read_reg", 21)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);	
		}
		else if(!memcmp(buf, "iwpriv wlan1 read_syn", 21)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);	
		}
	    else if(!memcmp(buf, "iwpriv wlan1 read_rf", 20)){
	        strcat(buf, " > /tmp/MP.txt");
	        system(buf);
	    }
	    else if(!memcmp(buf, "iwpriv wlan1 read_de", 20)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);					
		}
		else if(!memcmp(buf, "iwpriv wlan1 efuse_get", 22)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);
		}
		else if(!memcmp(buf, "iwpriv wlan1 efuse_set", 22)){
	            	strcat(buf, " > /tmp/MP.txt");
        	    	system(buf);
        	}
		else if(!memcmp(buf, "iwpriv wlan1 mp_psd", 19)){
				strcat(buf, " > /tmp/MP.txt");
				system(buf);		
		} 	
		else if(!memcmp(buf, "iwpriv wlan1 mp_dpk", 19)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);
		} 	
		else if(!memcmp(buf, "iwpriv wlan1 efuse_sync", 23)){
            strcat(buf, " > /tmp/MP.txt");
            system(buf);
        }
			else if(!memcmp(buf, "ifconfig wlan1 down" , 19))
			{
#ifdef CONFIG_VIRTUAL_WLAN_DRIVER
				memset(buf, 0 , BUFLEN);
				strcpy(buf, "echo 3 > /proc/vwlan");
#endif /*CONFIG_VIRTUAL_WLAN_DRIVER*/
				system(buf);
			}
			else if(!memcmp(buf, "ifconfig wlan1 up" , 17))
			{
#ifdef CONFIG_VIRTUAL_WLAN_DRIVER
				memset(buf,0,BUFLEN);
				strcpy(buf, "echo 2 > /proc/vwlan");
#endif /*CONFIG_VIRTUAL_WLAN_DRIVER*/
				system(buf);
			}
#endif /*ENABLE_WLAN1_MP*/
#if 1
        else if (!memcmp(buf, "iwpriv wlan2 mp_brx stop", 24)) {
            strcpy(buf, "stop");
            MP_get_ext("wlan2", buf, MP_BRX_PACKET);
        }
        else if (!memcmp(buf, "iwpriv wlan2 mp_tx", 18) && buf[18] == ' ') {
            memcpy(buf_tmp, buf+19, strlen(buf)-19);
            MP_get_ext("wlan2", buf_tmp, MP_TX_PACKET);
            strcpy(buf, buf_tmp);
        }
            
        else if (!memcmp(buf, "iwpriv wlan2 mp_ctx", 19) && buf[19] == ' ') {
            memcpy(buf_tmp, buf+20, strlen(buf)-20);
            MP_get_ext("wlan2", buf_tmp, MP_CONTIOUS_TX);
            strcpy(buf, buf_tmp);;
        }
        else if(!memcmp(buf, "iwpriv wlan2 read_reg", 21)){
            strcat(buf, " > /tmp/MP.txt");
            system(buf);    
        }
        else if(!memcmp(buf, "iwpriv wlan2 read_syn", 21)){
			strcat(buf, " > /tmp/MP.txt");
			system(buf);	
		}
        else if(!memcmp(buf, "iwpriv wlan2 read_rf", 20)){
             strcat(buf, " > /tmp/MP.txt");
             system(buf);
        }
        else if(!memcmp(buf, "iwpriv wlan2 read_de", 20)){
			 strcat(buf, " > /tmp/MP.txt");
			 system(buf);			
		}
        else if(!memcmp(buf, "iwpriv wlan2 efuse_get", 22)){
            strcat(buf, " > /tmp/MP.txt");
            system(buf);
        }
        else if(!memcmp(buf, "iwpriv wlan2 efuse_set", 22)){
                    strcat(buf, " > /tmp/MP.txt");
                    system(buf);
            }
        else if(!memcmp(buf, "iwpriv wlan2 mp_psd", 19)){
                strcat(buf, " > /tmp/MP.txt");
                system(buf);        
        }   
        else if(!memcmp(buf, "iwpriv wlan2 mp_dpk", 19)){
            strcat(buf, " > /tmp/MP.txt");
            system(buf);
        }   
        else if(!memcmp(buf, "iwpriv wlan2 efuse_sync", 23)){
            strcat(buf, " > /tmp/MP.txt");
            system(buf);
        }
#endif /*ENABLE_WLAN2_MP*/
			else if (!memcmp(buf, "irf ", 4)) {
				strcat(buf, " > /tmp/MP.txt");
				system(buf);
			}
			else {
				if (!memcmp(buf, "flash get", 9)){

					sprintf(cmdWrap, "flash gethw %s", buf+10);
					rwHW = 1;
					////strcat(buf, " > /tmp/MP.txt");
					strcat(cmdWrap, " > /tmp/MP.txt");
				}
				if (!memcmp(buf, "flash set", 9)) {
					sprintf(cmdWrap, "flash sethw %s", buf+10);
					rwHW = 1;
					//printf("1 sent command (%s) to IP:%s\n", pre_result, inet_ntoa(their_addr.sin_addr));
					if ((numbytes = sendto(sockfd, pre_result, strlen(pre_result), 0,
										   (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
						fprintf(stderr, "send failed\n");
						close(sockfd);
						exit(1);
					}
					printf("2 sent command (%s) to IP:%s\n", pre_result, inet_ntoa(their_addr.sin_addr));
				}
				if(rwHW == 1){
					printf("%s %d, cmdWrap=%s\n\n\n", __func__, __LINE__, cmdWrap);
					system(cmdWrap);
				} else {
					//printf("%s %d, buf=%s\n\n\n", __func__, __LINE__, buf);
					system(buf);
					//for reset btm
					if( !memcmp(buf, "ifconfig wlan0 up", 17) )
						reset_dev_stat();
				}
			}
			
			strcpy(buf_tmp, pre_result);
			strcpy(pre_result, buf);
			strcpy(buf, buf_tmp);
		}

		if (memcmp(buf, "flash set", 9) != 0) {
			//printf("1 sent command (%s) to IP:%s\n", buf, inet_ntoa(their_addr.sin_addr));

			size_t msglen=0;
			if(isshortmsg)
				msglen=30;
			else
				msglen=strlen(buf);

			if ((numbytes = sendto(sockfd, buf, msglen, 0,
								   (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
				fprintf(stderr, "send failed\n");
				close(sockfd);
				exit(1);
			}
			//printf("2 sent command (%s) to IP:%s\n", buf, inet_ntoa(their_addr.sin_addr));
			//printf("2 sent command (%s) to IP:%s, numbytes=%d, isshortmsg=%d\n", buf, inet_ntoa(their_addr.sin_addr), numbytes, isshortmsg );
		}
	}

	return 0;
}
