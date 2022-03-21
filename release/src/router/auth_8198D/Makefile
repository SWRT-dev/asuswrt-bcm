include $(LINUXDIR)/.config
include $(TOP)/.config

SUBDIRS = src src/dlisten



all:
	${MAKE} -C src
	${MAKE} -C src/dlisten

clean:
	${MAKE} -C src clean
	${MAKE} -C src/dlisten clean

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install src/auth $(INSTALLDIR)/usr/sbin
	install src/dlisten/iwcontrol $(INSTALLDIR)/usr/sbin
