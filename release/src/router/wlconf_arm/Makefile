all:
	-cp -f $(SRCBASE)/router/wlconf$(BCMEX)/prebuilt/wlconf wlconf

clean:
	rm -f wlconf

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install wlconf $(INSTALLDIR)/usr/sbin
	$(STRIP) $(INSTALLDIR)/usr/sbin/wlconf
