include ../common.mak

#all: tr
ifneq ($(wildcard ./prebuild),)
all:
	-mkdir -p build/bin
	-mkdir -p test
	-mkdir -p conf/ASUSWRT
	-cp prebuild/tr build/bin/tr
	-cp prebuild/sendtocli test/sendtocli
	-cp prebuild/notify test/notify
	-cp prebuild/udpclient test/udpclient
ifeq ($(RTCONFIG_TR181),y)
ifeq ($(RTCONFIG_DSL),y)
ifeq ($(RTCONFIG_ISP_OPTUS),y)
	install -D tr069/conf/ASUSWRT/tr_181.xml.dsl.optus $(INSTALLDIR)/tr069/usr/tr/tr.xml
else
	install -D tr069/conf/ASUSWRT/tr_181.xml.dsl $(INSTALLDIR)/tr069/usr/tr/tr.xml
endif
else
ifeq ($(RTCONFIG_ISP_OPTUS),y)
	install -D tr069/conf/ASUSWRT/tr_181.xml.dsl.optus $(INSTALLDIR)/tr069/usr/tr/tr.xml
else
	install -D tr069/conf/ASUSWRT/tr_181.xml $(INSTALLDIR)/tr069/usr/tr/tr.xml
endif
endif
else
ifeq ($(RTCONFIG_DSL),y)
	-cp prebuild/tr_98.xml.dsl conf/ASUSWRT/tr_98.xml.dsl
else
	-cp prebuild/tr_98.xml conf/ASUSWRT/tr_98.xml
endif
endif

endif

