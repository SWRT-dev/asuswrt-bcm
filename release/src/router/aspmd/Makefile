include ../.config

CFLAGS += -I. -I$(TOP)/shared -I$(SRCBASE)/include ${WLAN_StdIncPathA} -I$(SRCBASE)/common/include -Wall
CFLAGS += $(if $(WLAN_ComponentIncPath),$(WLAN_ComponentIncPath),$(addprefix -I,$(wildcard $(SRCBASE)/shared/bcmwifi/include)))
CFLAGS += -s -O2


LDFLAGS += -L$(TOP_PLATFORM)/nvram${BCMEX}${EX7} -L$(INSTALLDIR)/nvram/usr/lib -lnvram ${EXTRA_NV_LDFLAGS}
LDFLAGS += -L$(TOP)/shared -L$(INSTALLDIR)/shared/usr/lib -lshared
ifeq ($(RTCONFIG_BCM_502L07P2),y)
LDFLAGS += -L$(TOP_PLATFORM)/ethctl_lib -lethctl
endif
LDFLAGS += -lgcc_s

ifeq ($(wildcard $(SRCBASE)/router/aspmd/*.c),)
all:
	-cp -f prebuilt/aspmd aspmd
else
all: aspmd
endif

OBJS = aspmd_main.o

clean:
	rm -f *.o aspmd

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install aspmd $(INSTALLDIR)/usr/sbin
	$(STRIP) $(INSTALLDIR)/usr/sbin/aspmd

aspmd: ${OBJS}
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
