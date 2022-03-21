include $(SRCBASE)/router/.config

CFLAGS += -DASUS
CRYPTLIB = portingssl
WSCSRC = src

all:
	echo $(INSTALLDIR)
	make -C $(CRYPTLIB)
	make -C $(WSCSRC)

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install src/wscd $(INSTALLDIR)/usr/sbin
	install -D src/wscd.conf $(INSTALLDIR)/rom/etc/wscd.conf
	$(STRIP) $(INSTALLDIR)/usr/sbin/wscd

clean:
	make -C $(CRYPTLIB) clean
	make -C $(WSCSRC) clean