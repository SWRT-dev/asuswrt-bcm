
//--------------------------------------------------
// IEEE 802.1x Implementation
//
// File		: 1x_nal
// Programmer	: Arunesh Mishra
// This file implements the 1x-Network Abstraction
// Layer part.
// Copyright (c) Arunesh Mishra 2002
// All rights reserved.
// Maryland Information and Systems Security Lab
// University of Maryland, College Park.
//--------------------------------------------------




#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>


#include "1x_nal.h"
#include "1x_ethernet.h"
#include "1x_eapol.h"
#include "1x_auth_pae.h"
#include "1x_fifo.h"
#include "1x_ioctl.h"



#ifdef RTL_WPA_CLIENT
#include "1x_supp_pae.h"
extern Dot1x_Client		RTLClient;
#endif

#ifdef START_AUTH_IN_LIB
extern int read_wlan_evt(	int skfd, char *ifname, char *out);
#endif

#define EAP_BY_QUEUE

//--------------------------------------------------
// initialize pkt sender and receiver
// TODO: currently  cannot get our own ethernet
// addr .. needs to be fixed.
//--------------------------------------------------
struct lib1x_nal_intfdesc *  lib1x_nal_initialize( u_char * intdev , u_char * ouraddr, u_char inttype)
{
	 struct lib1x_nal_intfdesc * desc;
#ifndef EAP_BY_QUEUE
	 struct ifreq ifr;
	 int flags;
	 int retval;
#endif

	if ( intdev == NULL )
		 lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_intfdesc: Received NULL interface to open.");

	//1. General initializations
	 desc = ( struct lib1x_nal_intfdesc * ) malloc( sizeof ( struct lib1x_nal_intfdesc ) );
	 memset(desc, 0, sizeof(desc));
	 strncpy(desc->device, intdev, LIB1X_MAXDEVLEN);

	 desc->inttype = inttype;
	 memcpy( desc->ouraddr, ouraddr, ETHER_ADDRLEN);
	 //2. Specific to the listener
         desc->promisc_mode = LIB1X_LSTNR_PROMISCMODE;
	 desc->snaplen = LIB1X_LSTNR_SNAPLEN;
	 desc->read_timeout = LIB1X_LSTNR_RDTIMEOUT;
	 //desc->packet_handler = NULL ;
	//desc->global = global;	// not sure if we need this sort of backlink
	//sc_yang
#if 0
	 //desc->pcap_desc =  lib1x_nal_setup_pcap( desc );
         if ( desc->pcap_desc == NULL )
         {
              fprintf(stderr," Could not open device : %s", intdev  );
              exit(1);
         }
#endif

	/* 1. Create a socket */
#ifndef EAP_BY_QUEUE
	 desc->pf_sock = socket( PF_PACKET, SOCK_RAW, htons(ETH_P_ALL ) );	// P_ALL coz we dont have P_EAPOL yet in if_ether.h !
	 if ( desc->pf_sock > 0 ) lib1x_message( MESS_DBG_NAL,"PF_PACKET socket created ");
#endif
	// kenny
	// desc->pf_sock = pcap_fileno(desc->pcap_desc);



	 if ( inttype == LIB1X_IT_PKTSOCK )
	 {
#ifndef EAP_BY_QUEUE
	 /* 2. Bind to an eth interface */
	 /* to do the bind we need to get if_index i.e. the interface index */
		memset(&ifr, 0, sizeof(ifr));
	 	strncpy( ifr.ifr_name, desc->device, IFNAMSIZ -1  );
	 	if ( ( retval = ioctl( desc->pf_sock, SIOCGIFINDEX , & ifr )) < 0 )    /* SIOCGIFINDEX gets the if_index into the ifr struct */
			 lib1x_message( MESS_ERROR_FATAL, "nal: IOCTL failed on %s", desc->device );

	 	// prepare for bind .. : man netdevice
	 	desc->sock_device.sll_protocol = htons( ETH_P_ALL );
	 	desc->sock_device.sll_family = AF_PACKET;
	 	desc->sock_device.sll_ifindex = ifr.ifr_ifindex;
	 	if ( ( retval = bind( desc->pf_sock,  (struct sockaddr *)&desc->sock_device, sizeof(struct sockaddr_ll ))) != 0 )
		 	lib1x_message( MESS_ERROR_FATAL, "nal: BIND failed on %s retval : %d errorstr : %s", desc->device , retval, strerror(errno));


	 	flags = fcntl(desc->pf_sock, F_GETFL );
	 	if ( fcntl( desc->pf_sock, F_SETFL, flags | O_NONBLOCK) != 0 )
		 	lib1x_message( MESS_ERROR_FATAL, "nal: FCNTL failed on %s", desc->device );
#endif

		//3. Specific to the transmitter
		desc->libnet_desc = libnet_open_link_interface( intdev , desc->l_errbuf );
	 	if ( desc->libnet_desc == NULL )
		 	lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_intfdesc: Could not open libnet interface ");
	}
	 else
	 {
	 	//---- Radius Authentication Server
		desc->udpsock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP);\
		if ( desc->udpsock == -1 )
			lib1x_message(MESS_ERROR_FATAL,"lib1x_nal_initialize: Could not open Radius Authentication UDP socket !");

		/*xl_yue:20091021 record the connect status and try to connect if status is FALSE*/
		desc->udpsock_connected = 0;
		/*xl_yue:20091021 end*/

		desc->acctsock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP);\
		if ( desc->acctsock == -1 )
			lib1x_message(MESS_ERROR_FATAL,"lib1x_nal_initialize: Could not open Radius Accounting UDP socket !");
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
		desc->dassock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP);\
		if ( desc->dassock == -1 )
			lib1x_message(MESS_ERROR_FATAL,"lib1x_nal_initialize: Could not open Dynamic Authentication UDP socket !");
#endif
	 //	 flags = fcntl(desc->udpsock, F_GETFL );
	 //	if ( fcntl( desc->udpsock, F_SETFL, flags | O_NONBLOCK) != 0 )
	//	 	lib1x_message( MESS_ERROR_FATAL, "nal: FCNTL failed on UDP socket" );
	 }
	desc->packet_buffer = ( u_char * ) malloc( LIB1X_MAXEAPLEN * sizeof(u_char));


	return desc;
}

//--------------------------------------------------
// Bind to the RADIUS server, and connect: this function specifically
// for the wired interface.
// Return 0: Success, Return -1 Fail
//--------------------------------------------------
#ifdef CONFIG_YUEME
int lib1x_nal_connect( struct lib1x_nal_intfdesc * desc,  /*u_short udp_ourport,*/ struct sockaddr_in *svraddr ,
			int addrlen, int udpsock_type, const char *dev)
#else
int lib1x_nal_connect( struct lib1x_nal_intfdesc * desc,  /*u_short udp_ourport,*/ struct sockaddr_in *svraddr ,
			int addrlen, int udpsock_type)
#endif
{
	int flags;
	struct sockaddr_in myaddr;


	if ( desc->inttype != LIB1X_IT_UDPSOCK )
		return -1;

	// First bind to a local port
	memset( &myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	switch(udpsock_type)
	{
	case LIB1X_IT_UDPSOCK_AUTH:

		if ( bind( desc->udpsock, (struct sockaddr *) & myaddr, sizeof( struct sockaddr_in)) != 0){
			lib1x_message( MESS_ERROR_FATAL,"Could not BIND Authentication server UDP socket.");
			
		}

		desc->radsvraddr = svraddr;
		if (svraddr == NULL )
		{
			lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: NULL argument svraddr ");
			return -1;

		}
#ifdef CONFIG_YUEME	
		if(dev && *dev){
			if(setsockopt(desc->udpsock, SOL_SOCKET, SO_BINDTODEVICE, dev, strlen(dev)) != 0){
				lib1x_message(MESS_DBG_NAL,"%s: Cannot bind socket[%d] to interface[%s]\n", __FUNCTION__, desc->udpsock, dev);
				printf("%s: Cannot bind socket[%d] to interface[%s]\n", __FUNCTION__, desc->udpsock, dev);
			}
		}
#endif
		if ( connect( desc->udpsock, (struct sockaddr *)svraddr, addrlen ) != 0 )
		{
			lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: Could not connect to Authentication Server . ");
			return -1;

		}

		flags = fcntl(desc->udpsock, F_GETFL );
		if ( fcntl( desc->udpsock, F_SETFL, flags | O_NONBLOCK) != 0 )
			lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_connect : FCNTL failed on UDP socket" );
		break;

	case LIB1X_IT_UDPSOCK_ACCT:


		if ( bind( desc->acctsock, (struct sockaddr *) & myaddr, sizeof( struct sockaddr_in)) != 0)
			lib1x_message( MESS_ERROR_FATAL,"Could not BIND Accounting server UDP socket.");


		desc->acctsvraddr = svraddr;
		if (svraddr == NULL )
		{
			lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: NULL argument svraddr ");
			return -1;

		}
		if ( connect( desc->acctsock, (struct sockaddr *)svraddr, addrlen ) != 0 )
		{
			lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: Could not connect to Accounting Server. ");
			return -1;

		}

		flags = fcntl(desc->acctsock, F_GETFL );
		if ( fcntl( desc->acctsock, F_SETFL, flags | O_NONBLOCK) != 0 )
			lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_connect : FCNTL failed on UDP socket" );

		break;

	default:
		break;
	}

	return 0;
	//--- TESTING PART
	/*
	for ( i = 0; i < 100; i ++ )
		pkt[i] = (u_char) i % 255;

	//errcode = sendto( desc->udpsock, (u_char *) pkt, 99, 0, desc->radsvraddr, sizeof( struct sockaddr_in));
	errcode = sendto( desc->acctsock, (u_char *) pkt, 99, 0, desc->acctsvraddr, sizeof( struct sockaddr_in));
	if(errcode <= 0)
		printf("\n\n HEY the error for lib1x_nal_connect is %s", strerror(errno) );
	fflush(stdout);
	*/

}

/*xl_yue:20091021 add this function to connect auth server if udpsock connect status is failed*/
#ifdef CONFIG_YUEME
int lib1x_nal_connect_udpsock_authserver( struct lib1x_nal_intfdesc * desc,  struct sockaddr_in *svraddr, int addrlen, const char *dev)
#else
int lib1x_nal_connect_udpsock_authserver( struct lib1x_nal_intfdesc * desc,  struct sockaddr_in *svraddr, int addrlen)
#endif
{
	int flags;

	if (svraddr == NULL )
	{
		lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: NULL argument svraddr ");
		return -1;
	}
#ifdef CONFIG_YUEME	
	if(dev && *dev){
		if(setsockopt(desc->udpsock, SOL_SOCKET, SO_BINDTODEVICE, dev, strlen(dev)) != 0){
			lib1x_message(MESS_DBG_NAL,"%s: Cannot bind socket[%d] to interface[%s]\n", __FUNCTION__, desc->udpsock, dev);
			printf("%s: Cannot bind socket[%d] to interface[%s]\n", __FUNCTION__, desc->udpsock, dev);
		}
	}
#endif	
	if ( connect( desc->udpsock, (struct sockaddr *)svraddr, addrlen ) != 0 )
	{
		lib1x_message(MESS_DBG_NAL,"lib1x_nal_connect: Could not connect to Authentication Server . ");
		return -1;
	}
	printf("udpsock connect succeed!\n");
	
	flags = fcntl(desc->udpsock, F_GETFL );
	if ( fcntl( desc->udpsock, F_SETFL, flags | O_NONBLOCK) != 0 )
		lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_connect : FCNTL failed on UDP socket" );

	return 0;
}
/*xl_yue:20091021 end*/

#if 0 //sc_yang
/* just print a count every time we have a packet...                        */
void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,const u_char*
        packet)
{
    static int count = 1;
    fprintf(stdout,"%d, ",count);
    fflush(stdout);
    count++;
}
//--------------------------------------------------
// initializes pcap
//--------------------------------------------------
pcap_t *  lib1x_nal_setup_pcap( struct lib1x_nal_intfdesc * nd )
{
	 pcap_t* pcap_descr;                   /* pcap connection */
	 bpf_u_int32 pcap_maskp;               /* subnet mask */
	 bpf_u_int32 pcap_netp;                /* ip (not really sure) */
	 char pcap_filter[100];                /* filter for EAPOL pack */
	 struct bpf_program pcap_fp;           /* To hold the compiled filter */
	 u_char * eapol_src;

	 pcap_lookupnet( nd->device , &pcap_netp, &pcap_maskp, nd->p_errbuf );
	 pcap_descr = pcap_open_live( nd->device, nd->snaplen, 0, -1, nd->p_errbuf);

        /* Open Socket */
        if(pcap_descr == NULL)
	{
		    printf("pcap_open_live(): %s\n", nd->p_errbuf);
		    exit(1);
	}

	eapol_src = nd->ouraddr;
	  /* Setup filter */


	 sprintf(pcap_filter, "ether dst %x:%x:%x:%x:%x:%x and ether proto 0x%x",
		            eapol_src[0], eapol_src[1], eapol_src[2], eapol_src[3],
		              eapol_src[4], eapol_src[5],  LIB1X_ETHER_EAPOL_TYPE );

	//sprintf(pcap_filter, "ether proto 0x%x", LIB1X_ETHER_EAPOL_TYPE );


        if(pcap_compile(pcap_descr,&pcap_fp,pcap_filter,0,pcap_netp) == -1)
		          {
				  fprintf(stderr,"Error calling pcap_compile\n");
				  exit(1);
			  }


	//sprintf(pcap_filter, "src 172.20.13.220");
        //printf("SET FILTER: %s\n", pcap_filter);
	/*

        if(pcap_compile(pcap_descr,&pcap_fp,pcap_filter,0,pcap_netp) == -1)
                          {
                                  fprintf(stderr,"Error calling pcap_compile\n");
                                  exit(1);
                          }
	*/
        if(pcap_setfilter(pcap_descr,&pcap_fp) == -1)
			    {
				    fprintf(stderr,"Error setting filter\n");
				    exit(1);
			    }

	 //pcap_loop(pcap_descr,-1,my_callback,NULL);
         return pcap_descr;
}
#endif //sc_yang

//--------------------------------------------------
// lib1x_nal_receivepoll:
//   This function polls the interface for any packets
//   that might have come.
//   TODO: Currently we expose the libpcap handler to
//   the EAP layer. We need to put a level of abstraction here.
//--------------------------------------------------

int lib1x_nal_receive(Dot1x_Authenticator * auth)
{

	struct lib1x_nal_intfdesc * descSupp = auth->GlobalTxRx->network_supp;
#ifdef RTL_RADIUS_2SET
	struct lib1x_nal_intfdesc * descSvr2 = auth->GlobalTxRx->network_svr2;
#endif
	int suppid;
#ifdef PSK_ONLY
	int nRead=0;
#ifndef START_AUTH_IN_LIB
	fd_set fsRead;
#endif
#else
	struct lib1x_nal_intfdesc * descSvr = auth->GlobalTxRx->network_svr;
	int numread;
	int res;
	fd_set fsRead;
	struct timeval tvTimeOut;
	int 	iFD_SETSIZE = 0;

	tvTimeOut.tv_sec = 0;
	tvTimeOut.tv_usec = 0;
	FD_ZERO ( &fsRead);
#ifndef EAP_BY_QUEUE
	FD_SET( descSupp->pf_sock, &fsRead);
	iFD_SETSIZE = descSupp->pf_sock;
#endif

	if(auth->RSNVariable.Dot1xEnabled || auth->RSNVariable.MacAuthEnabled)
	{
		/*xl_yue:20091021 try to connect radius server again*/
		if(!descSvr->udpsock_connected){
#ifdef CONFIG_YUEME
			if(!lib1x_nal_connect_udpsock_authserver( descSvr,  &(auth->GlobalTxRx->radsvraddr), sizeof(struct sockaddr_in), auth->GlobalTxRx->device_svr )){
				descSvr->udpsock_connected = 1;
				lib1x_nal_getIpaddress(descSvr, &auth->GlobalTxRx->ourip_inaddr.s_addr);
			}
#else
			if(!lib1x_nal_connect_udpsock_authserver( descSvr,  &(auth->GlobalTxRx->radsvraddr), sizeof(struct sockaddr_in ) )){
				descSvr->udpsock_connected = 1;
			}
#endif
		}
		/*xl_yue:20091021 end*/
		
		FD_SET( descSvr->udpsock, &fsRead);
		iFD_SETSIZE = (iFD_SETSIZE > descSvr->udpsock)?iFD_SETSIZE:descSvr->udpsock;
		if(auth->AccountingEnabled)
		{
			FD_SET( descSvr->acctsock, &fsRead);
			iFD_SETSIZE = (iFD_SETSIZE > descSvr->acctsock)?iFD_SETSIZE:descSvr->acctsock;
		}
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
		if(auth->DynamicAuthEnable)
		{
 			FD_SET( descSvr->dassock, &fsRead);
 			iFD_SETSIZE = (iFD_SETSIZE > descSvr->dassock)?iFD_SETSIZE:descSvr->dassock;
 		}
#endif
#ifdef RTL_RADIUS_2SET
		if (auth->use_2nd_rad)
		{
			FD_SET( descSvr2->udpsock, &fsRead);
			iFD_SETSIZE = (iFD_SETSIZE > descSvr2->udpsock)?iFD_SETSIZE:descSvr2->udpsock;
		}
#endif
	}
	FD_SET( auth->GlobalTxRx->readfifo, &fsRead);
	iFD_SETSIZE = (iFD_SETSIZE > auth->GlobalTxRx->readfifo)?iFD_SETSIZE:auth->GlobalTxRx->readfifo;
	iFD_SETSIZE += 1;

// david
//	res = select( iFD_SETSIZE, &fsRead, NULL, NULL, &tvTimeOut);
res = select( iFD_SETSIZE, &fsRead, NULL, NULL, NULL);

	if ( res <= 0 )
	{
		return 0;
	}
	else
	{

#ifndef EAP_BY_QUEUE
		if(FD_ISSET(descSupp->pf_sock, &fsRead))
		{

			numread = recv( descSupp->pf_sock, descSupp->packet_buffer, LIB1X_MAXEAPLEN , 0);
			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after recv !");
				return 0;
			}

			descSupp->packet.caplen = numread;
			descSupp->packet.data = descSupp->packet_buffer;
#ifdef RTL_WPA_CLIENT
// david ----------------
#if 0
			if(auth->currentRole == role_Supplicant)
			{
				lib1x_suppsm_capture_auth( auth->client->global, descSupp, & descSupp->packet );
			}else
#endif

			if(auth->currentRole == role_Supplicant_infra)
			{
				lib1x_suppsm_capture_auth( auth->client->global, descSupp, & descSupp->packet );
			}else if (auth->currentRole == role_Authenticator)
//------------------------
#endif
			{
				suppid = lib1x_search_supp(auth, & descSupp->packet, descSupp->inttype);

				if(suppid != -1 && !memcmp(descSupp->packet.data, auth->GlobalTxRx->oursupp_addr, ETHER_ADDRLEN ))
				{
					lib1x_authsm_capture_supp(auth->Supp[suppid]->global, descSupp, & descSupp->packet);
					lib1x_auth_process(auth);
				}
			}


		}
#endif

		if((auth->RSNVariable.Dot1xEnabled || auth->RSNVariable.MacAuthEnabled)
		   && FD_ISSET(descSvr->udpsock, &fsRead))
		{
			numread = recv( descSvr->udpsock, descSvr->packet_buffer, LIB1X_MAXEAPLEN , 0);

			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after recv !");
				return 0;
			}

			descSvr->packet.caplen = numread;
			descSvr->packet.data = descSvr->packet_buffer;
			suppid = lib1x_search_supp(auth, & descSvr->packet, descSvr->inttype);

			if(suppid != -1)
			{
				lib1x_authsm_capture_svr(auth->Supp[suppid]->global, descSvr, & descSvr->packet);
				lib1x_auth_process(auth);
			}
		}

#ifdef RTL_RADIUS_2SET
		if((auth->RSNVariable.Dot1xEnabled || auth->RSNVariable.MacAuthEnabled)
		   && auth->use_2nd_rad && FD_ISSET(descSvr2->udpsock, &fsRead))
		{
			numread = recv( descSvr2->udpsock, descSvr2->packet_buffer, LIB1X_MAXEAPLEN , 0);

			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after recv !");
				return 0;
			}

			descSvr2->packet.caplen = numread;
			descSvr2->packet.data = descSvr2->packet_buffer;
			suppid = lib1x_search_supp(auth, & descSvr2->packet, descSvr2->inttype);

			if(suppid != -1)
			{
				lib1x_authsm_capture_svr(auth->Supp[suppid]->global, descSvr2, & descSvr2->packet);
				lib1x_auth_process(auth);
			}
		}
#endif
#endif // !PSK_ONLY

#ifndef START_AUTH_IN_LIB

		if(FD_ISSET(auth->GlobalTxRx->readfifo, &fsRead))
		{
			int nRead;
			nRead = read(auth->GlobalTxRx->readfifo, auth->GlobalTxRx->RecvBuf, RWFIFOSIZE);

			if(nRead <= 0)
				return 0;
#else
		nRead = read_wlan_evt(auth->GlobalTxRx->fd_control, auth->GlobalTxRx->device_supp, auth->GlobalTxRx->RecvBuf);
		if (nRead)
		{
#endif 
			auth->GlobalTxRx->network_supp->packet.data = auth->GlobalTxRx->RecvBuf + FIFO_HEADER_LEN;
			auth->GlobalTxRx->network_supp->packet.caplen = nRead - FIFO_HEADER_LEN;

			if(auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN - 1] == FIFO_TYPE_DLISTEN)
			{

#ifdef EAP_BY_QUEUE
#ifdef RTL_WPA2_PREAUTH
				if(auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN] == DOT11_EVENT_EAP_PACKET
				   || auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN] == DOT11_EVENT_EAP_PACKET_PREAUTH)
#else
				if(auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN] == DOT11_EVENT_EAP_PACKET)
#endif // RTL_WPA2
				{
					void *eap_packet = (void *)&(auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN]);
					unsigned short packet_len;
					memcpy(&packet_len, (void *)((unsigned int)eap_packet + (int)(&((DOT11_EAP_PACKET *)0)->packet_len)), sizeof(unsigned short));
					if (packet_len <= LIB1X_MAXEAPLEN) {
					descSupp->packet.caplen = packet_len;
					memcpy(descSupp->packet_buffer, (void *)((unsigned int)eap_packet + (int)(&((DOT11_EAP_PACKET *)0)->packet)), descSupp->packet.caplen);
					descSupp->packet.data = descSupp->packet_buffer;
					}

#ifdef RTL_WPA_CLIENT
					if(auth->currentRole == role_Supplicant_infra)
					{
						lib1x_suppsm_capture_auth( auth->client->global, descSupp, & descSupp->packet );
					}else if (auth->currentRole == role_Authenticator)
#endif
					{
						suppid = lib1x_search_supp(auth, & descSupp->packet, descSupp->inttype);
						if(suppid != -1 && !memcmp(descSupp->packet.data, auth->GlobalTxRx->oursupp_addr, ETHER_ADDRLEN ))
						{
							lib1x_authsm_capture_supp(auth->Supp[suppid]->global, descSupp, & descSupp->packet);
							lib1x_auth_process(auth);
						}
					}
				}
				else
				{
#endif
#ifdef RTL_WPA_CLIENT
// david -----------------------------
#if 0
				if(auth->currentRole == role_Supplicant)
				{
					lib1x_message(MESS_DBG_SUPP, "Receive driver indication\n");
					lib1x_suppsm_capture_control( auth->client->global, descSupp, & descSupp->packet );
				}else
#endif

				if(auth->currentRole == role_Supplicant_infra)
				{
					lib1x_message(MESS_DBG_SUPP, "Receive driver indication\n");
					lib1x_suppsm_capture_control( auth->client->global, descSupp, & descSupp->packet );
				}else if(auth->currentRole == role_Authenticator)
//------------------------------------
#endif
				{
					suppid = lib1x_search_supp(auth, (struct lib1x_packet *)& auth->GlobalTxRx->network_supp->packet, LIB1X_IT_CTLSOCK);

					if(suppid != -1)
					{
						lib1x_capture_control( auth->Supp[suppid]->global,auth->GlobalTxRx->network_supp ,& auth->GlobalTxRx->network_supp->packet);
						lib1x_auth_process(auth);
					}

				}

#ifdef EAP_BY_QUEUE
				}
#endif

			}
		}

#ifdef PSK_ONLY
		if (nRead <= 0)
			return 0;
#else
		if(((auth->RSNVariable.Dot1xEnabled || auth->RSNVariable.MacAuthEnabled)&& (auth->AccountingEnabled))
		   && FD_ISSET(descSvr->acctsock, &fsRead))
		{

			numread = recv( descSvr->acctsock, descSvr->packet_buffer, LIB1X_MAXEAPLEN , 0);

			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after recv !");
				return 0;
			}

			descSvr->packet.caplen = numread;
			descSvr->packet.data = descSvr->packet_buffer;
			suppid = lib1x_search_supp(auth, & descSvr->packet, descSvr->inttype);

			if(suppid == LIB1X_AUTH_INDEX)
				lib1x_authsm_capture_svr(auth->authGlobal->global, descSvr, & descSvr->packet);
			else if(suppid != -1)
			{
				lib1x_authsm_capture_svr(auth->Supp[suppid]->global, descSvr, & descSvr->packet);
				lib1x_auth_process(auth);
			}


		}
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
		if(((auth->RSNVariable.Dot1xEnabled || auth->RSNVariable.MacAuthEnabled)&& (auth->DynamicAuthEnable))
		   && FD_ISSET(descSvr->dassock, &fsRead))
		{
			lib1x_message(MESS_DBG_NAL, " Receive DAS packet!");

			numread = recvfrom(descSvr->dassock, descSvr->packet_buffer, LIB1X_MAXEAPLEN, 0, (struct sockaddr*)(&(descSvr->dassvraddr)), &(descSvr->dassvrlen));
			
			if ( numread < 20 )
			{
				lib1x_message(MESS_ERROR_FATAL," dassock NUMREAD = 0 after recv !");
				return 0;
			}

			descSvr->packet.caplen = numread;
			descSvr->packet.data = descSvr->packet_buffer;

			lib1x_hexdump2(MESS_DBG_RAD, "lib1x_nal_receive", descSvr->packet.data, descSvr->packet.caplen,"dump das packet");

			lib1x_authsm_capture_svr(auth->authGlobal->global, descSvr, & descSvr->packet);
		}
#endif

	}
#endif // !PSK_ONLY

	return 1; // david
}
#if 0 //sc_yang
//int lib1x_nal_receivepoll( Dot1x_Authenticator * auth, struct lib1x_nal_intfdesc * desc , lib1x_nal_genpkt_handler * pkt_handler, u_char * info)
int lib1x_nal_receivepoll( Dot1x_Authenticator * auth, struct lib1x_nal_intfdesc * desc , lib1x_nal_genpkt_handler * pkt_handler, u_char * info)
{
	struct pollfd pfd;
	int pret;
	int numread;
	int res;
	int suppid;

	struct timeval timeout;
	fd_set readfs;

	static int which = 1;

	if ( pkt_handler == NULL )
		lib1x_message( MESS_ERROR_FATAL," lib1x_nal_receivepoll called with NULL handler! ");

	timeout.tv_sec = 0;
//	timeout.tv_usec = 100;
	timeout.tv_usec = 0;

	if ( desc->inttype == LIB1X_IT_PKTSOCK )
	{

		pfd.fd = desc->pf_sock;
		pfd.events = POLLIN;
		pret = poll( &pfd, 1, 0 );
		if ( pret < 0 )
		{
			//if(pret != EINTR)
			//	lib1x_message( MESS_DBG_NAL," errno = %d%s", errno, strerror(errno));
		}
		if ( pret == 0 )
		{
			return 0;
		}

		numread = recv( desc->pf_sock, desc->packet_buffer, LIB1X_MAXEAPLEN , 0);
		if ( numread <= 0 )
		{
			return 0;
		}

		desc->packet.caplen = numread;
		desc->packet.data = desc->packet_buffer;

		suppid = lib1x_search_supp(auth, & desc->packet, desc->inttype);

		if(suppid != -1 && !memcmp(desc->packet.data, auth->GlobalTxRx->oursupp_addr, ETHER_ADDRLEN ))
			(*pkt_handler)(auth->Supp[suppid]->global, desc, & desc->packet);



	}
	else // udp socket
	{


		if(auth->AccountingEnabled)
			which = !which;
		//-------------------------------------------------------------------------
		// For UDP socket from Authentication Server
		//-------------------------------------------------------------------------
		if(which)
		{
			FD_ZERO ( &readfs);
			FD_SET( desc->udpsock, &readfs);
			res = select( desc->udpsock +1, &readfs, NULL, NULL, &timeout);
			if ( res == -1 )
			{
				return 0;
			}
			if ( res <= 0 )	 return 0;

			numread = recv( desc->udpsock, desc->packet_buffer, LIB1X_MAXEAPLEN , 0);

			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after poll !");
				return 0;
			}

			lib1x_message(MESS_DBG_SPECIAL, "Received message on UDP socket");

			desc->packet.caplen = numread;
			desc->packet.data = desc->packet_buffer;
			suppid = lib1x_search_supp(auth, & desc->packet, desc->inttype);
			//lib1x_hexdump2(MESS_DBG_NAL, "lib1x_nal_receive_poll", desc->packet.data, desc->packet.caplen, "receive UDP packet");
			if(suppid != -1)
				(*pkt_handler)(auth->Supp[suppid]->global, desc, & desc->packet);


			lib1x_message( MESS_DBG_SPECIAL, "READ %d BYTES FROM AUTH UDP SOCKET", numread );
		}else
		//-------------------------------------------------------------------------
		// For UDP socket from Accounting Server
		//-------------------------------------------------------------------------
		{
			FD_ZERO ( &readfs);
			FD_SET( desc->acctsock, &readfs);
			res = select( desc->acctsock +1, &readfs, NULL, NULL, &timeout);
			if ( res == -1 )
			{
				return 0;
			}

			if ( res <= 0 )	 return 0;
			numread = recv( desc->acctsock, desc->packet_buffer, LIB1X_MAXEAPLEN , 0);

			if ( numread <= 0 )
			{
				lib1x_message(MESS_ERROR_FATAL," NUMREAD = 0 after poll !");
				return 0;
			}

			desc->packet.caplen = numread;
			desc->packet.data = desc->packet_buffer;
			suppid = lib1x_search_supp(auth, & desc->packet, desc->inttype);
			//lib1x_hexdump2(MESS_DBG_NAL, "lib1x_nal_receive_poll", desc->packet.data, desc->packet.caplen, "receive UDP packet");

			if(suppid == LIB1X_AUTH_INDEX)
				(*pkt_handler)(auth->authGlobal->global, desc, & desc->packet);
			else if(suppid != -1)
				(*pkt_handler)(auth->Supp[suppid]->global, desc, & desc->packet);


			lib1x_message( MESS_DBG_SPECIAL, "READ %d BYTES FROM ACCT UDP SOCKET", numread );

		}
	}

	return 1; // david
}
#endif
#ifndef COMPACK_SIZE
//----------------------------------------------------------------
// lib1x_nal_receivefifo:
//	This function receive data from fifo.
//	Three sources of data are ceceived from fifo including:
//	(1) 8181 Wireless Interface
//	(2) Ethernet interface
//	(3) Ioctl return from 8181 driver
//
//	Data received from fifo(1, 2) has the header
//     _________________________________________________
//     | pid (4 bytes) | fifo type (1 byte) | data (*) |
//     -------------------------------------------------
//-----------------------------------------------------------------
int lib1x_nal_receivefifo(Dot1x_Authenticator * auth )
{

	ssize_t	nRead;
	int suppid;

	nRead = read(auth->GlobalTxRx->readfifo, auth->GlobalTxRx->RecvBuf, RWFIFOSIZE);


	if(nRead <= 0)
		return 0;
#ifdef ALLOW_DBG_NAL
	lib1x_hexdump2(MESS_DBG_NAL, "1x_daemon", auth->GlobalTxRx->RecvBuf,  nRead, "read from fifo");
	lib1x_message(MESS_DBG_FIFO, "rx event id=%d\n",  *((int *)auth->GlobalTxRx->RecvBuf));
#endif

	auth->GlobalTxRx->network_supp->packet.data = auth->GlobalTxRx->RecvBuf + FIFO_HEADER_LEN;
	auth->GlobalTxRx->network_supp->packet.caplen = nRead - FIFO_HEADER_LEN;

	switch(auth->GlobalTxRx->RecvBuf[FIFO_HEADER_LEN - 1])
	{

	case FIFO_TYPE_DLISTEN:

		suppid = lib1x_search_supp(auth, (struct lib1x_packet *)& auth->GlobalTxRx->network_supp->packet.data, LIB1X_IT_CTLSOCK);
		//lib1x_hexdump2(MESS_DBG_NAL, "lib1x_nal_receivefifo", (u_char*)&auth->GlobalTxRx->network_supp->packet.data, auth->GlobalTxRx->network_supp->packet.caplen, "receive from driver");

		if(suppid != -1)
		{
			lib1x_capture_control( auth->Supp[suppid]->global,auth->GlobalTxRx->network_supp ,& auth->GlobalTxRx->network_supp->packet);

		}else
			lib1x_message(MESS_DBG_NAL, "***********************NOT in TABLE");

		break;

	}

	return 1; // david

}
#endif
#ifndef COMPACK_SIZE
void lib1x_nal_receiveioctl(Dot1x_Authenticator * auth)
{


	int suppid = -1;

	lib1x_control_Poll(auth);

	if(auth->IoctlBufLen)
	{


		lib1x_hexdump2(MESS_DBG_NAL, "lib1x_nal_receiveioctl", auth->IoctlBuf, auth->IoctlBufLen, "receive from driver");
		auth->GlobalTxRx->network_supp->packet.data = auth->IoctlBuf;
		auth->GlobalTxRx->network_supp->packet.caplen = auth->IoctlBufLen;



		suppid = lib1x_search_supp(auth, (struct lib1x_packet *)& auth->GlobalTxRx->network_supp->packet.data, LIB1X_IT_CTLSOCK);


		if(suppid != -1)
		{

			lib1x_capture_control( auth->Supp[suppid]->global,auth->GlobalTxRx->network_supp ,& auth->GlobalTxRx->network_supp->packet);
		}

		auth->IoctlBufLen = 0;


	}

}
#endif

//--------------------------------------------------
//--------------------------------------------------
#ifndef COMPACK_SIZE
void lib1x_nal_close( struct lib1x_nal_intfdesc * desc )
{

	// Close the listener part.
	//sc_yang
//	pcap_close( desc->pcap_desc );

	// Close the xmitter part.
	if (libnet_close_link_interface( desc->libnet_desc) == -1 )
		lib1x_message( MESS_ERROR_OK,"lib1x_nal_close: Error closing libnet channel.");
}
#endif




#if 0 //sc_yang
//--------------------------------------------------
// lib1x_nal_packet_handler:
//  This function will be called by pcap for each packet.
//--------------------------------------------------
void lib1x_nal_pcappkt_handler( u_char * lib1x_data , const struct pcap_pkthdr * packet_header, const u_char * the_packet)
{
	struct lib1x_nal_intfdesc *  desc;
	struct lib1x_ethernet * ehdr;

	u_int	caplen;
	u_int	length;
	u_short	ether_type;



	desc = ( struct lib1x_nal_intfdesc * ) lib1x_data;
	caplen = packet_header->caplen;
	length = packet_header->len;

	if ( caplen < ETHER_HDRLEN )
	{
		fprintf(stderr,"\n One packet missed .. captured length too small");
		return ;
	}
	ehdr = (struct lib1x_ethernet * ) the_packet;
	ether_type = ntohs( ehdr->ether_type );

	printf("\n packet received.");

	// We need to call the appropriate handler which is
	// given by desc->packet_handler.
}
#endif


//--------------------------------------------------
// lib1x_nal_send:
//  Make sure from and to addresses are proper
//  in the ethernet header .. coz i dont check
//  that here.
//--------------------------------------------------
BOOLEAN lib1x_nal_send( struct lib1x_nal_intfdesc * desc,  char * packet , int size)
{
	int num_sent = 0;

	if ( desc->inttype == LIB1X_IT_PKTSOCK )
	{
	//	if ( size > 1499 ) size = 1499; /* needed for ethernet only if you are not handling fragmentation */
		if ( desc->libnet_desc  == NULL )
			lib1x_message( MESS_ERROR_FATAL, "lib1x_nal_send: Descriptor contains invalid network identifier.");
		num_sent = libnet_write_link_layer( desc->libnet_desc, desc->device ,
			packet, size );
		lib1x_message(MESS_DBG_NAL, "libnet_write_link_layer send packets %d\n", num_sent);

#ifdef DBG_WPA_CLIENT
		{
			struct lib1x_packet  spkt;
			spkt.data = packet;
			spkt.caplen = size;

			lib1x_suppsm_capture_auth( RTLClient.global, desc, &spkt );

		}
#endif
	}
	else
	{
		/*xl_yue:20091021 send packet to server only when udpsock connected*/
		if(desc->udpsock_connected)
		/*xl_yue:20091021 end*/
		{
#ifdef CONFIG_YUEME
			if(!lib1x_nal_checkSocket(desc)){
				lib1x_nal_reinitSocket(desc);
			}
			else
			{
#endif
			num_sent =  send( desc->udpsock, (void*) packet, size, 0); /* flags = 0 */
			lib1x_message( MESS_DBG_SPECIAL, "lib1x_nal_send: Sending UDP packet.");
#ifdef CONFIG_YUEME
			}
#endif
		}
	}
	if ( num_sent != size )
	{
		lib1x_message( MESS_ERROR_OK, "lib1x_nal_send: Mismatch in send size!");
		lib1x_message( MESS_ERROR_FATAL," NUM_SENT : %d . actual %d", num_sent, size );
		return FALSE;
	}
	return TRUE;
}
#ifdef DYNAMIC_AUTHORIZATION_SUPPORT
BOOLEAN lib1x_nal_send_das( struct lib1x_nal_intfdesc * desc,  char * packet , int size)
{
	int num_sent = 0;

	num_sent = sendto(desc->dassock, packet, size, 0, (struct sockaddr*)(&(desc->dassvraddr)), desc->dassvrlen);
	lib1x_message( MESS_DBG_SPECIAL, "lib1x_nal_send_das: Sending UDP packet.");

	lib1x_hexdump2(MESS_DBG_RAD, "lib1x_nal_send_das", packet, size,"dump das packet");
	
	if ( num_sent != size )
	{
		lib1x_message( MESS_ERROR_OK, "lib1x_nal_send_das: Mismatch in send size!");
		lib1x_message( MESS_ERROR_FATAL," NUM_SENT : %d . actual %d", num_sent, size );
		return FALSE;
	}
	return TRUE;
}
#endif


#ifdef CONFIG_YUEME
unsigned long* lib1x_nal_getIpaddress(struct lib1x_nal_intfdesc *descSvr, unsigned long *addr)
{
	static unsigned long __addr = 0;
	struct sockaddr_in tmpaddr;
	int n = sizeof(tmpaddr);
	
	if(descSvr->udpsock_connected){
		if (getsockname(descSvr->udpsock, (struct sockaddr *)&tmpaddr, (socklen_t *)&n) < 0)
			__addr = 0;
		else
			__addr = tmpaddr.sin_addr.s_addr;
	}

	if(addr){
		*addr = __addr;
		return addr;
	}
	return &__addr;
}

int lib1x_nal_reinitSocket(struct lib1x_nal_intfdesc *descSvr)
{
	int sock = -1, n;
	struct sockaddr_in myaddr;
	
	if(descSvr->udpsock_connected){
		close(descSvr->udpsock);
		descSvr->udpsock = -1;
		sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(sock >= 0){
			memset( &myaddr, 0, sizeof(myaddr));
			myaddr.sin_family = AF_INET;
			myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			myaddr.sin_port = htons(0);
			bind(sock, (struct sockaddr *) & myaddr, sizeof( struct sockaddr_in));
			descSvr->udpsock = sock;
			descSvr->udpsock_connected = 0;
			return 1;
		}
	}
	return 0;
}

int lib1x_nal_checkSocket(struct lib1x_nal_intfdesc *descSvr)
{
	unsigned long addr = 0;
	int sock = -1, n;
	struct sockaddr_in myaddr, svraddr, myaddr2;
	char dev[50] = {0};
	
	if(descSvr->udpsock_connected){
		lib1x_nal_getIpaddress(descSvr, &addr);
		getsockopt(descSvr->udpsock, SOL_SOCKET, SO_BINDTODEVICE, (void *)dev, &n);
		n = sizeof(svraddr);
		if(getpeername(descSvr->udpsock, &svraddr, &n) != 0){
			lib1x_message( MESS_ERROR_FATAL," Cannot get peer address" );
			return 0;
		}
		
		sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(sock >= 0){
			memset( &myaddr, 0, sizeof(myaddr));
			myaddr.sin_family = AF_INET;
			myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			myaddr.sin_port = htons(0);
			bind(sock, (struct sockaddr *) & myaddr, sizeof( struct sockaddr_in));
			if(dev[0]){
				if(setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, dev, strlen(dev)) != 0){
					lib1x_message( MESS_ERROR_FATAL," Cannot bind to interface : %s", dev );
				}
			}
			n = sizeof(svraddr);
			if(connect(sock, (struct sockaddr *)&svraddr, n) == 0)
			{
				n = sizeof(myaddr2);
				if (getsockname(sock, (struct sockaddr *)&myaddr2, (socklen_t *)&n) == 0){
					if(myaddr2.sin_addr.s_addr == addr){
						close(sock);
						return 1;
					}
				}
			}
			close(sock);
		}
	}
	return 0;
}

#endif

