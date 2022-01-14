all:
	-cp ./prebuilt/nas .

install: all
	install -D nas $(INSTALLDIR)/usr/sbin/nas
	$(STRIP) $(INSTALLDIR)/usr/sbin/nas

clean:
	rm -f nas
