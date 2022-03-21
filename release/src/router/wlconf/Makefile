include ../common.mak

CFLAGS	+= -I. -I$(TOP)/shared -I$(SRCBASE)/include -Wall
#CFLAGS	+= -g -DDEBUG
CFLAGS	+= -s -Os -DBCMWPA2 $(EXTRACFLAGS)
LDFLAGS	+= -L$(TOP_PLATFORM)/nvram -lnvram -L$(TOP)/shared -lshared
LDFLAGS += $(EXTRA_LDFLAGS)

ifeq ($(RTAC53U), y)
CFLAGS += -DRTAC53U
endif

OBJS := wlconf.o
ifeq ($(RTCONFIG_BCMWL6),y)
OBJS += bcmwifi_channels.o
endif

ifeq ($(RTAC53U),y)
vpath %.c $(SRCBASE)/wlconf $(SRCBASE)/shared $(WLAN_ComponentSrcDirs)
else
vpath %.c $(SRCBASE)/wlconf $(SRCBASE)/shared
endif
ifeq ($(RTCONFIG_BCMWL6),y)
vpath %.c $(SRCBASE)/shared/bcmwifi/src
endif

ifeq ($(wildcard $(SRCBASE)/wlconf/*.c),)
all:
	-cp -f $(SRCBASE)/router/wlconf/prebuilt/wlconf wlconf
else
all: wlconf
endif

clean:
	rm -f *.o wlconf

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install wlconf $(INSTALLDIR)/usr/sbin
	$(STRIP) $(INSTALLDIR)/usr/sbin/wlconf

wlconf: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
