#***********************************************************************
#
# Makefile
#
#***********************************************************************

all:
ifneq ($(RTCONFIG_DHDAP),y)
	-cp -f prebuilt/wl.o ./wl_apsta.o
endif
	-cp -f prebuilt/$(BUILD_NAME)/dhd.o ./dhd.o
	-cp -f prebuilt/$(BUILD_NAME)/dhd24.o ./dhd24.o

.PHONY: clean
clean:
	-rm -rf *.o 
