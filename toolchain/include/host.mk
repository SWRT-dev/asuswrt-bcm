# 
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

TMP_DIR ?= $(TOPDIR)/tmp
-include $(TMP_DIR)/.host.mk

export TAR

ifneq ($(__host_inc),1)
__host_inc:=1
.PRECIOUS: $(TMP_DIR)/.host.mk
$(TMP_DIR)/.host.mk: $(TOPDIR)/include/host.mk
	@mkdir -p $(TMP_DIR)
	@( \
		HOST_OS=`uname`; \
		case "$$HOST_OS" in \
			Linux) HOST_ARCH=`uname -m`;; \
			*) HOST_ARCH=`uname -p`;; \
		esac; \
		GNU_HOST_NAME=`gcc -dumpmachine`; \
		[ -n "$$GNU_HOST_NAME" ] || \
			GNU_HOST_NAME=`$(SCRIPT_DIR)/config.guess`; \
		echo "HOST_OS:=$$HOST_OS" > $@; \
		echo "HOST_ARCH:=$$HOST_ARCH" >> $@; \
		echo "GNU_HOST_NAME:=$$GNU_HOST_NAME" >> $@; \
		TAR=`which gtar 2>/dev/null`; \
		[ -n "$$TAR" -a -x "$$TAR" ] || TAR=`which gnutar 2>/dev/null`; \
		[ -n "$$TAR" -a -x "$$TAR" ] || TAR=`which tar 2>/dev/null`; \
		echo "TAR:=$$TAR" >> $@; \
		FIND=`which gfind 2>/dev/null`; \
		[ -n "$$FIND" -a -x "$$FIND" ] || FIND=`which find 2>/dev/null`; \
		echo "FIND:=$$FIND" >> $@; \
		echo "BASH:=$(shell which bash)" >> $@; \
		if find -L /tmp -maxdepth 0 >/dev/null 2>/dev/null; then \
			echo 'FIND_L=find -L $$(1)' >>$@; \
		else \
			echo 'FIND_L=find $$(1) -follow' >> $@; \
		fi; \
	)

endif

ifeq ($(HOST_OS),Linux)
  XARGS:=xargs -r
else
  XARGS:=xargs
endif
