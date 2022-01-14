# Makefile for OpenWrt
#
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

SHELL:=/usr/bin/env bash
PREP_MK= OPENWRT_BUILD= QUIET=0

include $(TOPDIR)/include/verbose.mk

ifeq ($(SDK),1)
  include $(TOPDIR)/include/version.mk
else
  REVISION:=$(shell $(TOPDIR)/scripts/getver.sh)
endif

OPENWRTVERSION:=$(if $(REVISION), ($(REVISION)))
export OPENWRTVERSION
export IS_TTY=$(shell tty -s && echo 1 || echo 0)

ifeq ($(FORCE),)
  .config scripts/config/conf scripts/config/mconf: tmp/.prereq-build
endif

SCAN_COOKIE?=$(shell echo $$$$)
export SCAN_COOKIE

prepare-mk: FORCE ;

prepare-tmpinfo: FORCE
	mkdir -p tmp/info
#	$(_SINGLE)$(NO_TRACE_MAKE) -j1 -s -f include/scan.mk SCAN_TARGET="packageinfo" SCAN_DIR="package" SCAN_NAME="package" SCAN_DEPS="$(TOPDIR)/include/package*.mk" SCAN_DEPTH=5 SCAN_EXTRA=""
#	$(_SINGLE)$(NO_TRACE_MAKE) -j1 -s -f include/scan.mk SCAN_TARGET="targetinfo" SCAN_DIR="target/linux" SCAN_NAME="target" SCAN_DEPS="profiles/*.mk $(TOPDIR)/include/kernel*.mk $(TOPDIR)/include/target.mk" SCAN_DEPTH=2 SCAN_EXTRA="" SCAN_MAKEOPTS="TARGET_BUILD=1"
#	for type in package target; do \
#		f=tmp/.$${type}info; t=tmp/.config-$${type}.in; \
#		[ "$$t" -nt "$$f" ] || ./scripts/metadata.pl $${type}_config "$$f" > "$$t" || { rm -f "$$t"; echo "Failed to build $$t"; false; break; }; \
#	done
#	./scripts/metadata.pl package_mk tmp/.packageinfo > tmp/.packagedeps || { rm -f tmp/.packagedeps; false; }
	touch $(TOPDIR)/tmp/.build

.config: ./scripts/config/conf prepare-tmpinfo
	@+if [ \! -f .config ]; then \
		[ -e defconfig ] && cp defconfig .config; \
		$(NO_TRACE_MAKE) menuconfig $(PREP_MK); \
	fi

scripts/config/mconf:
	@$(SUBMAKE) -s -j1 -C scripts/config all

$(eval $(call rdep,scripts/config,scripts/config/mconf))

scripts/config/conf:
	@$(SUBMAKE) -s -j1 -C scripts/config conf

config: scripts/config/conf prepare-tmpinfo FORCE
	$< Config.in

config-clean: FORCE
	$(NO_TRACE_MAKE) -C scripts/config clean

defconfig: scripts/config/conf prepare-tmpinfo FORCE
	touch .config
	$< -D .config Config.in

oldconfig: scripts/config/conf prepare-tmpinfo FORCE
	$< -$(if $(CONFDEFAULT),$(CONFDEFAULT),o) Config.in

menuconfig: scripts/config/mconf prepare-tmpinfo FORCE
	if [ \! -f .config -a -e defconfig ]; then \
		cp defconfig .config; \
	fi
	$< Config.in

kernel_oldconfig: .config FORCE
	$(NO_TRACE_MAKE) -C target/linux oldconfig

kernel_menuconfig: .config FORCE
	$(NO_TRACE_MAKE) -C target/linux menuconfig

tmp/.prereq-build: include/prereq-build.mk
	mkdir -p tmp
	rm -f tmp/.host.mk
	@$(_SINGLE)$(NO_TRACE_MAKE) -j1 -s -f $(TOPDIR)/include/prereq-build.mk prereq 2>/dev/null || { \
		echo "Prerequisite check failed. Use FORCE=1 to override."; \
		false; \
	}
	touch $@

download: .config FORCE
	@+$(SUBMAKE) tools/download
	@+$(SUBMAKE) toolchain/download

clean dirclean: .config
	@+$(SUBMAKE) $@ 

prereq:: .config
	@+$(MAKE) -s tmp/.prereq-build $(PREP_MK)
	@$(NO_TRACE_MAKE) -s $@

%::
	@+$(PREP_MK) $(NO_TRACE_MAKE) -s prereq
	@+$(SUBMAKE) -r $@

help:
	cat README

docs docs/compile: FORCE
	@$(_SINGLE)$(SUBMAKE) -j1 -C docs compile

docs/clean: FORCE
	@$(_SINGLE)$(SUBMAKE) -j1 -C docs clean

distclean:
	rm -rf tmp build_dir staging_dir dl .config* feeds bin
	@$(_SINGLE)$(SUBMAKE) -j1 -C scripts/config clean

ifeq ($(findstring v,$(DEBUG)),)
  .SILENT: symlinkclean clean dirclean distclean config-clean download help tmpinfo-clean .config scripts/config/mconf scripts/config/conf menuconfig tmp/.prereq-build tmp/.prereq-package prepare-tmpinfo
endif
.PHONY: help FORCE
.NOTPARALLEL:

