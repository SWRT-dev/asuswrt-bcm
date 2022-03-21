#CC=$(CROSS_COMPILE)gcc
#CFLAGS=-c -Wall
#LDFLAGS=

include ../common.mak
include $(SRCBASE)/router/.config

SOURCES=ther_control.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ther_control
#CFLAGS += -I$(ROOTDIR)/$(LINUXDIR)/include

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

INSTALL = install

install: $(EXECUTABLE)
	$(STRIP) $(EXECUTABLE)
	$(INSTALL) -d $(INSTALLDIR)/usr/sbin 
	$(INSTALL) $(EXECUTABLE) $(INSTALLDIR)/usr/sbin

clean: 
	rm -rf $(EXECUTABLE) *.o
