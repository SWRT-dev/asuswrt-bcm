#
# Makefile for WPA for the Linux OS
#
#
# $Id: Makefile,v 1.3 2010/09/03 12:43:08 yachang Exp $
#

include $(LINUXDIR)/.config
include $(TOP)/.config

WPA_ROOT_DIR = ../..

ARCH	=
NAME	= dlisten

###################
#CC	= mips-uclibc-gcc
#STRIP	= mips-uclibc-strip
#LD	= mips-uclibc-ld
#AR	= mips-uclibc-ar
###################

dlisten_SRCS = iwcontrol.c iwconfig.c iwcommon.c iwreq.c
dlisten_OBJS = ${dlisten_SRCS:.c=.o}

RTL_WPA_IFLAGS 	= -I${WPA_ROOT_DIR}/include \
				-I${WPA_ROOT_DIR}/Package/Libnet-1.0.2a/include \
				-I${WPA_ROOT_DIR}/Package/libpcap-0.7.2 \
				-I${WPA_ROOT_DIR}/Package/openssl-0.9.7b/include

#RTL_WPA_LIBS = ${WPA_ROOT_DIR}/libnet.a \
#				${WPA_ROOT_DIR}/libpcap.a \
#				${WPA_ROOT_DIR}/libcrypto.a

RTL_WPA_DEFFLAGS += -DGLIBC22_HEADERS

RTL_WPA_CFLAG = -Wall -Os

ifeq ($(SLINK),1)
RTL_WPA_CFLAG += -ffunction-sections -fdata-sections
RTL_WPA_LDFLAG += --static -Wl,--gc-sections
endif

ifeq ($(CONFIG_RTL_HS2_SUPPORT),y)
RTL_WPA_CFLAG += -DHS2_SUPPORT
endif

ifeq ($(CONFIG_RTL_TRIBAND_SUPPORT),y)
ifeq ($(CONFIG_USB_AS_WLAN1),y)
else
CFLAGS      += -DTRIBAND_WPS
endif
endif

CFLAGS += $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS)
#
#	Transition rules (add -o to put object in right directory)
#
#.c.o:
#	$(CC) $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS) -c -o $*.o $<


###################
all: iwcontrol


iwcontrol: $(dlisten_OBJS)
	$(CC) ${RTL_WPA_LDFLAG} -o iwcontrol $(dlisten_OBJS) $(RTL_WPA_LIBS)
	$(STRIP) $(STRIPFLAGS) iwcontrol



##-------------------------------------------------

clean:
	rm -f *.o; rm -f iwcontrol

romfs:
	install iwcontrol $(INSTALLDIR)/usr/sbin


