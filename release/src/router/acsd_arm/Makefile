all:
	-cp -f prebuilt/acsd acsd

install: all
	install -d $(INSTALLDIR)/usr/sbin/
	install acsd $(INSTALLDIR)/usr/sbin/
	$(STRIP) $(INSTALLDIR)/usr/sbin/acsd

clean:
	rm -f acsd
