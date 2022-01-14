# 
# Copyright (C) 2006 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

#ifeq ($(__target_inc),)
#  include $(INCLUDE_DIR)/target.mk
#endif

ifeq ($(DUMP),1)
  KERNEL?=<KERNEL>
  BOARD?=<BOARD>
  LINUX_VERSION?=<LINUX_VERSION>
else
  export GCC_HONOUR_COPTS=s

  ifeq ($(KERNEL),2.6)
    LINUX_KMOD_SUFFIX=ko
  else
    LINUX_KMOD_SUFFIX=o
  endif

  ifneq (,$(findstring uml,$(BOARD)))
    KERNEL_CC?=$(HOSTCC)
    KERNEL_CROSS?=
  else
    KERNEL_CC?=$(TARGET_CC)
    KERNEL_CROSS?=$(TARGET_CROSS)
  endif

  PATCH_DIR ?= ./patches$(shell [ -d "./patches-$(KERNEL_PATCHVER)" ] && printf -- "-$(KERNEL_PATCHVER)" || true )
  FILES_DIR ?= ./files$(shell [ -d "./files-$(KERNEL_PATCHVER)" ] && printf -- "-$(KERNEL_PATCHVER)" || true )
  KERNEL_BUILD_DIR ?= $(BUILD_DIR_BASE)/linux-$(BOARD)$(if $(SUBTARGET),_$(SUBTARGET))$(if $(BUILD_SUFFIX),_$(BUILD_SUFFIX))
  LINUX_DIR ?= $(KERNEL_BUILD_DIR)/linux-$(LINUX_VERSION)

  MODULES_SUBDIR:=lib/modules/$(LINUX_VERSION)
  TARGET_MODULES_DIR := $(LINUX_TARGET_DIR)/$(MODULES_SUBDIR)

  LINUX_KERNEL:=$(KERNEL_BUILD_DIR)/vmlinux

  LINUX_SOURCE:=linux-$(LINUX_VERSION).tar.bz2
  TESTING:=$(if $(findstring -rc,$(LINUX_VERSION)),/testing,)
  LINUX_SITE:=@KERNEL/linux/kernel/v$(KERNEL)$(TESTING) \

  ifneq ($(TARGET_BUILD),1)
    PKG_BUILD_DIR ?= $(KERNEL_BUILD_DIR)/$(PKG_NAME)$(if $(PKG_VERSION),-$(PKG_VERSION))
  endif
endif

ifneq (,$(findstring uml,$(BOARD)))
  LINUX_KARCH:=um
else
  ifeq (,$(LINUX_KARCH))
    LINUX_KARCH:=$(shell echo $(ARCH) | sed -e 's/i[3-9]86/i386/' \
	  -e 's/mipsel/mips/' \
	  -e 's/mipseb/mips/' \
	  -e 's/sh[234]/sh/' \
	  -e 's/armeb/arm/' \
    )
  endif
endif


define KernelPackage/Defaults
  FILES:=
  AUTOLOAD:=
endef

define ModuleAutoLoad
	export modules=; \
	add_module() { \
		mkdir -p $(2)/etc/modules.d; \
		( \
			for mod in $$$$$$$$2; do \
				getvar mod; \
			done \
		) > $(2)/etc/modules.d/$$$$$$$$1-$(1); \
		modules="$$$$$$$${modules:+$$$$$$$$modules }$$$$$$$$1-$(1)"; \
	}; \
	$(3) \
	if [ -n "$$$$$$$$modules" ]; then \
		mkdir -p $(2)/etc/modules.d; \
		echo "#!/bin/sh" > $(2)/CONTROL/postinst; \
		echo "[ -z \"\$$$$$$$$IPKG_INSTROOT\" ] || exit 0" >> $(2)/CONTROL/postinst; \
		echo ". /etc/functions.sh" >> $(2)/CONTROL/postinst; \
		echo "load_modules $$$$$$$$modules" >> $(2)/CONTROL/postinst; \
		chmod 0755 $(2)/CONTROL/postinst; \
	fi
endef

ifeq ($(DUMP)$(TARGET_BUILD),)
  -include $(LINUX_DIR)/.config
endif

define KernelPackage
  NAME:=$(1)
  $(eval $(call Package/Default))
  $(eval $(call KernelPackage/Defaults))
  $(eval $(call KernelPackage/$(1)))
  $(eval $(call KernelPackage/$(1)/$(KERNEL)))
  $(eval $(call KernelPackage/$(1)/$(BOARD)-$(KERNEL)))

  define Package/kmod-$(1)
    TITLE:=$(TITLE)
    SECTION:=kernel
    CATEGORY:=Kernel modules
    DESCRIPTION:=$(DESCRIPTION)
    EXTRA_DEPENDS:=kernel (=$(LINUX_VERSION)-$(BOARD)-$(LINUX_RELEASE))
    VERSION:=$(LINUX_VERSION)$(if $(PKG_VERSION),+$(PKG_VERSION))-$(BOARD)-$(if $(PKG_RELEASE),$(PKG_RELEASE),$(LINUX_RELEASE))
    $(call KernelPackage/$(1))
    $(call KernelPackage/$(1)/$(KERNEL))
    $(call KernelPackage/$(1)/$(BOARD)-$(KERNEL))
  endef

  ifdef KernelPackage/$(1)/description
    define Package/kmod-$(1)/description
$(call KernelPackage/$(1)/description)
    endef
  endif

  ifdef KernelPackage/$(1)/config
    define Package/kmod-$(1)/config
$(call KernelPackage/$(1)/config)
    endef
  endif

  ifneq ($(if $(KCONFIG),$(filter m,$(foreach c,$(filter-out %=y %=n %=m,$(KCONFIG)),$($(c)))),.),)
    ifneq ($(strip $(FILES)),)
      define Package/kmod-$(1)/install
		  mkdir -p $$(1)/lib/modules/$(LINUX_VERSION)
		  $(CP) -L $$(FILES) $$(1)/lib/modules/$(LINUX_VERSION)/
		  $(call ModuleAutoLoad,$(1),$$(1),$(AUTOLOAD))
		  $(call KernelPackage/$(1)/install,$$(1))
      endef
    endif
  $(if $(CONFIG_PACKAGE_kmod-$(1)),
    else
      compile: kmod-$(1)-unavailable
      kmod-$(1)-unavailable:
		@echo "WARNING: kmod-$(1) is not available in the kernel config"
  )
  endif
  $$(eval $$(call BuildPackage,kmod-$(1)))

  $$(IPKG_kmod-$(1)): $$(wildcard $$(FILES))
endef

define AutoLoad
  add_module $(1) "$(2)";
endef

define CompareKernelPatchVer
  $(shell [ $$(echo $(1) | tr . 0) -$(2) $$(echo $(3) | tr . 0) ] && echo 1 || echo 0)
endef

