# 
# Copyright (C) 2007 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

DOWNLOAD_RDEP:=$(STAMP_PREPARED)

# Try to guess the download method from the URL
define dl_method 
$(strip \
  $(if $(2),$(2), \
    $(if $(filter @GNU/% @KERNEL/% @SF/% ftp://% http://%,$(1)),default, \
      $(if $(filter git://%,$(1)),git, \
        $(if $(filter svn://%,$(1)),svn, \
          $(if $(filter cvs://%,$(1)),cvs, \
            unknown \
	  ) \
        ) \
      ) \
    ) \
  ) \
)
endef

# code for creating tarballs from cvs/svn/git checkouts - useful for mirror support
dl_pack/bz2=$(TAR) cfj $(1) $(2)
dl_pack/gz=$(TAR) cfz $(1) $(2)
dl_pack/unknown=echo "ERROR: Unknown pack format for file $(1)"; false
define dl_pack
	$(if $(dl_pack/$(call ext,$(1))),$(dl_pack/$(call ext,$(1))),$(dl_pack/unknown))
endef

define DownloadMethod/unknown
	@echo "ERROR: No download method available"; false
endef

define DownloadMethod/default
	$(SCRIPT_DIR)/download.pl "$(DL_DIR)" "$(FILE)" "$(MD5SUM)" $(URL)
endef

define wrap_mirror
	@$(SCRIPT_DIR)/download.pl "$(DL_DIR)" "$(FILE)" "x" || ( $(1) )
endef

define DownloadMethod/cvs
	$(call wrap_mirror, \
		echo "Checking out files from the cvs repository..."; \
                mkdir -p $(TMP_DIR)/dl && \
                cd $(TMP_DIR)/dl && \
                rm -rf $(SUBDIR) && \
                [ \! -d $(SUBDIR) ] && \
                cvs co -r$(VERSION) $(URL) $(SUBDIR) && \
                find $(SUBDIR) -name CVS | xargs rm -rf && \
                echo "Packing checkout..." && \
                $(call dl_pack,$(TMP_DIR)/dl/$(FILE),$(SUBDIR)) && \
                mv $(TMP_DIR)/dl/$(FILE) $(DL_DIR)/; \
        )
endef


define DownloadMethod/svn
	$(call wrap_mirror, \
		echo "Checking out files from the svn repository..."; \
		mkdir -p $(TMP_DIR)/dl && \
		cd $(TMP_DIR)/dl && \
		rm -rf $(SUBDIR) && \
		[ \! -d $(SUBDIR) ] && \
		svn co -r$(VERSION) $(URL) $(SUBDIR) && \
		find $(SUBDIR) -name .svn | xargs rm -rf && \
		echo "Packing checkout..." && \
		$(call dl_pack,$(TMP_DIR)/dl/$(FILE),$(SUBDIR)) && \
		mv $(TMP_DIR)/dl/$(FILE) $(DL_DIR)/; \
	)
endef

define DownloadMethod/git
	$(call wrap_mirror, \
		echo "Checking out files from the git repository..."; \
		mkdir -p $(TMP_DIR)/dl && \
		cd $(TMP_DIR)/dl && \
		rm -rf $(SUBDIR) && \
		[ \! -d $(SUBDIR) ] && \
		git-clone $(URL) $(SUBDIR) && \
		(cd $(SUBDIR) && git-checkout $(VERSION)) && \
		echo "Packing checkout..." && \
		rm -rf $(SUBDIR)/.git && \
		$(call dl_pack,$(TMP_DIR)/dl/$(FILE),$(SUBDIR)) && \
		mv $(TMP_DIR)/dl/$(FILE) $(DL_DIR)/; \
	)
endef

Validate/cvs=VERSION SUBDIR
Validate/svn=VERSION SUBDIR
Validate/git=VERSION SUBDIR

define Download/Defaults
  URL:=
  FILE:=
  PROTO:=
  MD5SUM:=
  SUBDIR:=
  VERSION:=
endef

define Download
  $(eval $(Download/Defaults))
  $(eval $(Download/$(1)))
  $(foreach FIELD,URL FILE $(Validate/$(call dl_method,$(URL),$(PROTO))),
    ifeq ($($(FIELD)),)
      $$(error Download/$(1) is missing the $(FIELD) field.)
    endif
  )

  $(if $(DOWNLOAD_RDEP),$(DOWNLOAD_RDEP): $(DL_DIR)/$(FILE))
  download: $(DL_DIR)/$(FILE)

  $(DL_DIR)/$(FILE):
	mkdir -p $(DL_DIR)
	$(if $(DownloadMethod/$(call dl_method,$(URL),$(PROTO))),$(DownloadMethod/$(call dl_method,$(URL),$(PROTO))),$(DownloadMethod/unknown))

endef
