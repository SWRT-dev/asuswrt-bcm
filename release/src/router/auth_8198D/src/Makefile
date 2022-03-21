#
# Makefile for WPA for the Linux OS
#
#
# $Id: Makefile,v 1.4 2010/09/03 12:43:08 yachang Exp $
#

include $(LINUXDIR)/.config
include $(TOP)/.config

ARCH	= rWPA.a
NAME	= rWPA

WPA_ROOT_DIR = ..
RTL_WPA_TARGET = auth

###### WPA2 #######
ENABLE_WPA2 = true
ENABLE_WPA2_PREAUTH = true
ENABLE_WPA2_CLIENT = true

###### Client mode TLS #######
ENABLE_CLIENT_TLS = false

###### 2 set of RADIUS #######
ENABLE_RADIUS_2SET = true

###### Endian ######
ifeq ($(CONFIG_CPU_BIG_ENDIAN),y)
ENABLE_BIG_ENDIAN = true
else
ENABLE_BIG_ENDIAN = false
endif

###################
#ifeq ($(ASUS),1)
#CC	= mipsel-linux-gcc
#STRIP	= mipsel-linux-strip
#LD	= mipsel-linux-ld
#AR	= mipsel-linux-ar
#else
#CC	= mips-uclibc-gcc
#STRIP	= mips-uclibc-strip
#LD	= mips-uclibc-ld
#AR	= mips-uclibc-ar
#endif
###################


ifeq ($(CONFIG_RTL_HS2_SUPPORT),y)
RTL_WPA_CFLAG += -DHS2_SUPPORT
endif

ifeq ($(RTL8186_TR),1)
RTL_WPA_CFLAG += -DCONFIG_RTL8186_TR
ENABLE_WPA2_CLIENT = false
ENABLE_WPA2_PREAUTH = false
endif

#Dynamic authorization feature
#DYNAMIC_AUTH=-DDYNAMIC_AUTHORIZATION_SUPPORT

#kenny
DBG_FLAG=-DDEBUG_DISABLE
DOWN_SIZE=-DCOMPACK_SIZE
RTL_WPA_CFLAG += -Wall -Os $(DOWN_SIZE) $(DBG_FLAG) $(DYNAMIC_AUTH)

ifeq ($(SLINK),1)
RTL_WPA_CFLAG += -ffunction-sections -fdata-sections
RTL_WPA_LDFLAG += --static -Wl,--gc-sections
endif

#RTL_WPA_CFLAG	= -Wall -O2

#RTL_WPA_LDFLAG	= #-r

RTL_WPA_IFLAGS 	= -I${WPA_ROOT_DIR}/include 

#RTL_WPA_LIBS = ${WPA_ROOT_DIR}/Package/libnet.a \
				${WPA_ROOT_DIR}/Package/libpcap.a \
				${WPA_ROOT_DIR}/Package/libcrypto.a

ifeq ($(strip $(ENABLE_BIG_ENDIAN)),true)
RTL_WPA_DEFFLAGS = -D_ON_RTL8181_TARGET -DLIBNET_BIG_ENDIAN -DLIB1X_BIG_ENDIAN -D_DAEMON_SIDE -D_RTL_WPA_UNIX 
else
RTL_WPA_DEFFLAGS = -D_ON_RTL8181_TARGET -DLIBNET_LIL_ENDIAN -DLIB1X_LIL_ENDIAN -D_DAEMON_SIDE -D_RTL_WPA_UNIX 
endif

ifeq ($(ASUS),1)
	RTL_WPA_DEFFLAGS += -D__ASUS_DVD__ -DPSK_ONLY -DAUTH_LITTLE_ENDIAN -DSTART_AUTH_IN_LIB
else
ifeq ($(strip $(ENABLE_BIG_ENDIAN)),true)
	RTL_WPA_DEFFLAGS += -DAUTH_BIG_ENDIAN
else
	RTL_WPA_DEFFLAGS += -DAUTH_LITTLE_ENDIAN
endif
endif

ifeq ($(strip $(ENABLE_CLIENT_TLS)),true)
openssl_dir = ../Package/openssl-0.9.7d
XSUPP_LIBS =    xsup_src/xsup.a \
		${openssl_dir}/libssl.a \
		${openssl_dir}/libcrypto.a
RTL_WPA_DEFFLAGS += -DCLIENT_TLS
endif

ifeq ($(strip $(ENABLE_WPA2)),true)
RTL_WPA_DEFFLAGS +=  -DRTL_WPA2
RTL_WPA_CFLAG	+= -g
endif # ENABLE_WPA2

ifeq ($(strip $(ENABLE_WPA2_PREAUTH)),true)
RTL_WPA_DEFFLAGS +=  -DRTL_WPA2_PREAUTH
endif # ENABLE_WPA2_PREAUTH


ifeq ($(strip $(ENABLE_WPA2_CLIENT)),true)
RTL_WPA_DEFFLAGS +=  -DRTL_WPA2_CLIENT
endif # ENABLE_WPA2_CLIENT

ifeq ($(strip $(ENABLE_RADIUS_2SET)),true)
RTL_WPA_DEFFLAGS +=  -DRTL_RADIUS_2SET
endif #ENABLE_RADIUS_2SET

ifeq ($(CONFIG_RTL_11W_SUPPORT),y)
RTL_WPA_DEFFLAGS += -DCONFIG_IEEE80211W
endif

ifeq ($(CONFIG_RTL_11R_SUPPORT),y)
RTL_WPA_DEFFLAGS += -DCONFIG_IEEE80211R
endif

#------------------------------------------------------------------------
# source files
#------------------------------------------------------------------------
RTL_WPA_SRCS = auth.o \
			1x_auth_pae.o 1x_bauth_sm.o 1x_common.o 1x_krc_sm.o \
			1x_nal.o 1x_kxsm.o 1x_radius.o 1x_ptsm.o 1x_reauth_sm.o \
			1x_cdsm.o 1x_config.o 1x_ioctl.o 1x_parser.o \
			1x_kmsm_auth.o 1x_kmsm_supp.o 1x_kmsm_eapolkey.o \
			1x_info_auth.o 1x_kmsm_hmac.o 1x_kmsm_prf.o 1x_kmsm_aes.o 1x_acct_sm.o 1x_md5c.o 1x_rc4.o libnet.o  sha256.o
ifeq ($(strip $(ENABLE_WPA2)),true)
RTL_WPA_SRCS	+= 1x_pmk_cache.o
endif # ENABLE_WPA2
RTL_WPA_OBJS = ${RTL_WPA_SRCS:.c=.o}

ifeq ($(ASUS),1)
RTL_WPA_SRCS += iwcontrol.o
endif


CFLAGS += $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS)
#------------------------------------------------------------------------
#	Transition rules (add -o to put object in right directory)
#------------------------------------------------------------------------
#.c.o:
#	$(CC) $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS) -c -o $*.o $<

#ifeq ($(ASUS),1)
#iwcontrol.o: dlisten/iwcontrol.c
#	$(CC) $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS) -c -o $*.o $<
#endif

###################
#all: build_lib build_listen ${RTL_WPA_TARGET} wpa_bin pretest
#all: pretest build_listen ${RTL_WPA_TARGET} wpa_bin
ifeq ($(strip $(ENABLE_CLIENT_TLS)),true)
all:  xsup ${RTL_WPA_TARGET}
else

### ASUS library ###
ifeq ($(ASUS),1)
ASUS_WPA_LIB = auth.a

${ASUS_WPA_LIB}: ${RTL_WPA_OBJS}
	$(AR) r $@ $(RTL_WPA_OBJS)
	$(STRIP) -S $@

all: ${ASUS_WPA_LIB}

iwcontrol.o: dlisten/iwcontrol.c
	$(CC) $(RTL_WPA_CFLAG) $(RTL_WPA_IFLAGS) $(RTL_WPA_DEFFLAGS) -c -o $*.o $<

else
### 8186 daemon ###
all:  ${RTL_WPA_TARGET}

endif
endif

build_lib:
	cd ${WPA_ROOT_DIR}/Package/Libnet-1.0.2a; \
	${MAKE} clean; \
	${MAKE} -f Makefile-rtl8181 RTL_WPA_CFLAG='${RTL_WPA_CFLAG}' RTL_WPA_LDFLAG='${RTL_WPA_LDFLAG}' RTL_WPA_DEFFLAGS='${RTL_WPA_DEFFLAGS}';
	cd ${WPA_ROOT_DIR}/Package/libpcap-0.7.2; \
	${MAKE} clean; \
	${MAKE} -f Makefile-rtl8181 RTL_WPA_CFLAG='${RTL_WPA_CFLAG}' RTL_WPA_LDFLAG='${RTL_WPA_LDFLAG}' RTL_WPA_DEFFLAGS='${RTL_WPA_DEFFLAGS}';
	cd ${WPA_ROOT_DIR}/Package/openssl-0.9.7d; \
	${MAKE} clean; \
	${MAKE} -f Makefile-rtl8181 RTL_WPA_CFLAG='${RTL_WPA_CFLAG}' RTL_WPA_LDFLAG='${RTL_WPA_LDFLAG}' RTL_WPA_DEFFLAGS='${RTL_WPA_DEFFLAGS}';



build_listen:
	cd dlisten; ${MAKE} clean; \
	${MAKE} -f Makefile-rtl8181 RTL_WPA_CFLAG='${RTL_WPA_CFLAG}' RTL_WPA_LDFLAG='${RTL_WPA_LDFLAG}' ;

ifeq ($(strip $(ENABLE_CLIENT_TLS)),true)
${RTL_WPA_TARGET}: ${RTL_WPA_OBJS} ${RTL_WPA_LIBS} ${XSUPP_LIBS}
	$(CC) $(RTL_WPA_LDFLAG) -o $@ $(RTL_WPA_OBJS) ${RTL_WPA_LIBS} ${XSUPP_LIBS}
	$(STRIP) $@
else
${RTL_WPA_TARGET}: ${RTL_WPA_OBJS} ${RTL_WPA_LIBS}
	$(CC) $(RTL_WPA_LDFLAG) -o $@ $(RTL_WPA_OBJS) ${RTL_WPA_LIBS}
	$(STRIP) $@
endif

pretest: pretest.o
	$(CC) $(RTL_WPA_LDFLAG) -o $@ pretest.o 
	rm pretest.o -f

wpa_bin:
	chmod 744 ${WPA_ROOT_DIR}/bin/; \
	${STRIP} dlisten/iwcontrol; \
	cp dlisten/iwcontrol ${WPA_ROOT_DIR}/bin/; \
#	${STRIP} ${RTL_WPA_TARGET}; \
	cp ${RTL_WPA_TARGET} ${WPA_ROOT_DIR}/bin/; \
	cp pretest ${WPA_ROOT_DIR}/bin/; \
	chmod 777 ${WPA_ROOT_DIR}/bin/*;


SUBDIRS=xsup_src
xsup:
	@for d in $(SUBDIRS); do (cd $$d && $(MAKE) DESTDIR=${DESTDIR}); done


##-------------------------------------------------

clean:
	rm -f *.o; rm -f ${RTL_WPA_TARGET}; rm -f *.a
	#@for d in $(SUBDIRS); do (cd $$d && $(MAKE) DESTDIR=${DESTDIR} clean); done

install:
	install auth $(INSTALLDIR)/usr/sbin
