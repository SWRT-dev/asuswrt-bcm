# SPDX-License-Identifier: GPL-2.0
include ../config.mk

# brcm: comment out.
# CFLAGS += -fPIC

UTILOBJ = utils.o rt_names.o ll_map.o ll_types.o ll_proto.o ll_addr.o \
	inet_proto.o namespace.o json_writer.o json_print.o \
	names.o color.o bpf.o exec.o fs.o

NLOBJ=libgenl.o libnetlink.o

# brcm: rename libutil.a to libipr2util.a
all: libnetlink.a libipr2util.a

libnetlink.a: $(NLOBJ)
	$(QUIET_AR)$(AR) rcs $@ $^

libipr2util.a: $(UTILOBJ) $(ADDLIB)
	$(QUIET_AR)$(AR) rcs $@ $^

install:

clean:
	rm -f $(NLOBJ) $(UTILOBJ) $(ADDLIB) libnetlink.a libipr2util.a
