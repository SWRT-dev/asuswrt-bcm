#***********************************************************************
#
#  Copyright (c) 2006-2007  Broadcom Corporation
#  All Rights Reserved
#
#  <:label-BRCM:2006:DUAL/GPL:standard
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License, version 2, as published by
#  the Free Software Foundation (the "GPL").
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  
#  A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
#  writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
#  Boston, MA 02111-1307, USA.
#  
#  :>
#
#***********************************************************************

LIB = ./STLport-5.2.1/build/lib/obj/$(TOOLCHAIN_PREFIX)-gcc/so/libstlport.so.5.2
LIB-SRC = STLport-5.2.1

all dynamic install: conditional_build

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(HND_SRC)

include $(BUILD_DIR)/make.common

ifeq ($(strip $(DESKTOP_LINUX)),y)
CFLAGS := $(BCM_LD_FLAGS)
CXXFLAGS := $(BCM_LD_FLAGS)
LDFLAGS := $(BCM_LD_FLAGS)
export CFLAGS CXXFLAGS LDFLAGS
MIN_GCC_VERSION = "5"
GCC_VERSION := "`$(CROSS_COMPILE)gcc -dumpversion`"
IS_GCC_ABOVE_MIN_VERSION := $(shell expr "$(GCC_VERSION)" ">=" "$(MIN_GCC_VERSION)")
endif

PREFIX=$(BCM_FSBUILD_DIR)/public
#undefined the CC and CXX from make.common as the stlport makefile is not compatible with that.
unexport CC
unexport CXX
ifneq ($(strip $(DESKTOP_LINUX)),y)
CXXFLAGS := -std=gnu++98 --sysroot=$(TOOLCHAIN_SYSROOT)
CFLAGS := -std=gnu++98 --sysroot=$(TOOLCHAIN_SYSROOT)
export CXXFLAGS
export CFLAGS
endif

# STLPORT makefiles get confused if the toolchain is not in PATH, but we don't want the toolchain's
# tar implementation in the PATH.  So, we set TPATH and add it to the PATH only where needed

TPATH := $(TOOLCHAIN)/bin:$(PATH)


clean: generic_clean
	@PATH=$(TPATH) ; if [ -e $(LIB-SRC)/Makefile ]; then \
	cd $(LIB-SRC); $(MAKE) clean; \
	fi
	rm -rf $(LIB-SRC)
	rm -rf lib
	rm -rf include
	rm -f $(INSTALL_DIR)/lib/public/$(LIB)

# The next line is a hint to our release scripts
# GLOBAL_RELEASE_SCRIPT_CALL_DISTCLEAN
distclean:
	rm -f $(LIB)
	rm -rf $(LIB-SRC)
	rm -rf lib
	rm -rf include
	rm -f $(INSTALL_DIR)/lib/public/$(LIB)

ifeq ($(strip $(DESKTOP_LINUX)),y)
ifeq "$(IS_GCC_ABOVE_MIN_VERSION)" "1"
conditional_build: sanity_check
	@echo "skipping $(LIB) for desktop build"
else
ifneq ($(strip $(BUILD_LIB_STLPORT)),)
conditional_build: $(LIB)
else
conditional_build: sanity_check
	@echo "skipping $(LIB) (not configured)"
endif
endif
else
ifneq ($(strip $(BUILD_LIB_STLPORT)),)
conditional_build: $(LIB)
else
conditional_build: sanity_check
	@echo "skipping $(LIB) (not configured)"
endif
endif

$(LIB-SRC)/Makefile:
	@echo "Untarring original $(LIB-SRC) source"
	(tar xkf $(LIB-SRC).tar.bz2 2> /dev/null || true)
	@echo "Applying patches to $(LIB-SRC)"
	patch -p1 -b -d$(LIB-SRC) < bcm_patches/$(LIB-SRC).patch
	(PATH=$(TPATH) ; cd $(LIB-SRC); ./configure --use-compiler-family=gcc --target=$(TOOLCHAIN_PREFIX) --prefix=$(PREFIX) --with-extra-cxxflags="$(CXXFLAGS)" --with-extra-cflags="$(CFLAGS)") 
	touch $@

$(LIB): $(LIB-SRC)/Makefile
	PATH=$(TPATH) ; $(MAKE) -C $(LIB-SRC) install-release-shared
	mkdir -p  $(INSTALL_DIR)/lib/public/ 
ifneq ($(strip $(TOOLCHAIN_PREFIX)),)
	for l in $(PREFIX)/$(TOOLCHAIN_PREFIX)-lib/libst* ; \
	 do f=`basename $$l` ; \
	 ln -fs ../$(TOOLCHAIN_PREFIX)-lib/$$f $(PREFIX)/lib/$$f ; \
	 cp -df $$l $(INSTALL_DIR)/lib/public/ ; \
        done
else
	for l in $(PREFIX)/lib/libst* ; \
	 do cp -df $$l $(INSTALL_DIR)/lib/public/ ; \
        done
endif

shell:
	bash -i

