include $(SRCBASE)/router/.config

ifeq ($(RTCONFIG_CFGSYNC),y)
CFLAGS  += -I$(TOP)/cfg_mnt
LDFLAGS += -L$(TOP)/cfg_mnt -lcfgmnt
CFLAGS += -DRTCONFIG_CFGSYNC
endif

ifeq ($(RTCONFIG_LIBASUSLOG),y)
CFLAGS += -I$(TOP)/libasuslog
LDFLAGS += -L$(TOP)/libasuslog -lasuslog
endif

CFLAGS += -I$(TOP)/json-c
LDFLAGS += -L$(TOP)/json-c/.libs -ljson-c
CFLAGS += -I$(TOP)/shared -I$(SRCBASE)/include -I$(SRCBASE)/common/include

LDFLAGS += -L$(TOP)/nvram$(BCMEX)${EX7} ${EXTRA_NV_LDFLAGS} -lnvram
LDFLAGS += -L$(TOP)/shared -lshared

STAGING_DIR = $(STAGEDIR)

EXEC = wlceventd
OBJS = rtk_wifi_eventd.o

all: $(EXEC)

$(EXEC): $(OBJS)
	@echo " [$(EXEC)] CC $@"
	@$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

install: all
	@echo "[$(EXEC)] Installing..."
	@install -D $(EXEC) $(INSTALLDIR)/usr/sbin/$(EXEC)
	@$(STRIP) $(INSTALLDIR)/usr/sbin/$(EXEC)

clean:
	rm -f *.o $(EXEC)

%.o: %.c
	@echo " [$(EXEC)] CC $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

