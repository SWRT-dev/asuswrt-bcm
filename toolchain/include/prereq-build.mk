# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/prereq.mk
include $(INCLUDE_DIR)/host.mk

PKG_NAME:=Build dependency

define Require/non-root
	[ "$$(shell whoami)" != "root" ]
endef
$(eval $(call Require,non-root, \
	Please do not compile as root. \
))

# Required for the toolchain
define Require/working-make
	$(MAKE) -v | awk '($$$$1 == "GNU") && ($$$$2 = "Make") && ($$$$3 >= "3.80") { print "ok" }' | grep ok > /dev/null
endef

$(eval $(call Require,working-make, \
	Please install GNU make v3.81 or later. (This version has bugs) \
))

define Require/case-sensitive-fs
	rm -f $(TMP_DIR)/test.*
	touch $(TMP_DIR)/test.fs
	[ \! -f $(TMP_DIR)/test.FS ]
endef

$(eval $(call Require,case-sensitive-fs, \
	Toolchain can only be built on a case-sensitive filesystem \
))

define Require/working-gcc
	echo 'int main(int argc, char **argv) { return 0; }' | \
		gcc -x c -o $(TMP_DIR)/a.out -
endef

$(eval $(call Require,working-gcc, \
	Please install the GNU C Compiler (gcc). \
))

define Require/working-g++
	echo 'int main(int argc, char **argv) { return 0; }' | \
		g++ -x c++ -o $(TMP_DIR)/a.out -lstdc++ - && \
		$(TMP_DIR)/a.out
endef

$(eval $(call Require,working-g++, \
	Please install the GNU C++ Compiler (g++). \
))

define Require/ncurses
	echo 'int main(int argc, char **argv) { initscr(); return 0; }' | \
		gcc -include ncurses.h -x c -o $(TMP_DIR)/a.out -lncurses -
endef

$(eval $(call Require,ncurses, \
	Please install ncurses. (Missing libncurses.so or ncurses.h) \
))


define Require/zlib
	echo 'int main(int argc, char **argv) { gzdopen(0, "rb"); return 0; }' | \
		gcc -include zlib.h -x c -o $(TMP_DIR)/a.out -lz -
endef

$(eval $(call Require,zlib, \
	Please install zlib. (Missing libz.so or zlib.h) \
))

$(eval $(call RequireCommand,gawk, \
	Please install GNU awk. \
))

$(eval $(call RequireCommand,bison, \
	Please install GNU bison. \
))

$(eval $(call RequireCommand,flex, \
	Please install flex. \
))

$(eval $(call RequireCommand,unzip, \
	Please install unzip. \
))

$(eval $(call RequireCommand,bzip2, \
	Please install bzip2. \
))

$(eval $(call RequireCommand,patch, \
	Please install patch. \
))

$(eval $(call RequireCommand,perl, \
	Please install perl. \
))

$(eval $(call RequireCommand,wget, \
	Please install wget. \
))

define Require/gnutar
	$(TAR) --version 2>&1 | grep GNU > /dev/null
endef

$(eval $(call Require,gnutar, \
	Please install GNU tar. \
))

$(eval $(call RequireCommand,svn, \
	Please install the subversion client. \
))

$(eval $(call RequireCommand,autoconf, \
	Please install GNU autoconf. \
))

define Require/gnu-find
	$(FIND) --version 2>/dev/null
endef

$(eval $(call Require,gnu-find, \
	Please install GNU find \
))
