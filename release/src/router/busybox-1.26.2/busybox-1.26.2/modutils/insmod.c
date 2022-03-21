/* vi: set sw=4 ts=4: */
/*
 * Mini insmod implementation for busybox
 *
 * Copyright (C) 2008 Timo Teras <timo.teras@iki.fi>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */
//config:config INSMOD
//config:	bool "insmod"
//config:	default y
//config:	select PLATFORM_LINUX
//config:	help
//config:	  insmod is used to load specified modules in the running kernel.

//applet:IF_INSMOD(IF_NOT_MODPROBE_SMALL(APPLET(insmod, BB_DIR_SBIN, BB_SUID_DROP)))

//kbuild:ifneq ($(CONFIG_MODPROBE_SMALL),y)
//kbuild:lib-$(CONFIG_INSMOD) += insmod.o modutils.o
//kbuild:endif

#include "libbb.h"
#include "modutils.h"

/* 2.6 style insmod has no options and required filename
 * (not module name - .ko can't be omitted) */

//usage:#if !ENABLE_MODPROBE_SMALL
//usage:#define insmod_trivial_usage
//usage:	IF_FEATURE_2_4_MODULES("[OPTIONS] MODULE ")
//usage:	IF_NOT_FEATURE_2_4_MODULES("FILE ")
//usage:	"[SYMBOL=VALUE]..."
//usage:#define insmod_full_usage "\n\n"
//usage:       "Load kernel module"
//usage:	IF_FEATURE_2_4_MODULES( "\n"
//usage:     "\n	-f	Force module to load into the wrong kernel version"
//usage:     "\n	-k	Make module autoclean-able"
//usage:     "\n	-v	Verbose"
//usage:     "\n	-q	Quiet"
//usage:     "\n	-L	Lock: prevent simultaneous loads"
//usage:	IF_FEATURE_INSMOD_LOAD_MAP(
//usage:     "\n	-m	Output load map to stdout"
//usage:	)
//usage:     "\n	-x	Don't export externs"
//usage:	)
//usage:#endif

static char *m_filename;

static int FAST_FUNC check_module_name_match(const char *filename,
		struct stat *statbuf UNUSED_PARAM,
		void *userdata, int depth UNUSED_PARAM)
{
	char *fullname = (char *) userdata;
	char *tmp;

	if (fullname[0] == '\0')
		return FALSE;

	tmp = bb_get_last_path_component_nostrip(filename);
	if (strcmp(tmp, fullname) == 0) {
		/* Stop searching if we find a match */
		m_filename = xstrdup(filename);
		return FALSE;
	}
	return TRUE;
}

int insmod_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int insmod_main(int argc UNUSED_PARAM, char **argv)
{
	struct stat st;
	char *filename;
	FILE *fp = NULL;
	int rc, pos;

	/* Compat note:
	 * 2.6 style insmod has no options and required filename
	 * (not module name - .ko can't be omitted).
	 * 2.4 style insmod can take module name without .o
	 * and performs module search in default directories
	 * or in $MODPATH.
	 */

	IF_FEATURE_2_4_MODULES(
		getopt32(argv, INSMOD_OPTS INSMOD_ARGS);
		argv += optind - 1;
	);

	filename = *++argv;
	if (!filename)
		bb_show_usage();

	m_filename = NULL;

	pos = strlen(filename) - 2;
	if (get_linux_version_code() < KERNEL_VERSION(2,6,0)) {
		if (pos < 0) pos = 0;
		if (strncmp(&filename[pos], ".o", 2) !=0)
			filename = xasprintf("%s.o", filename);
	} else {
		if (--pos < 0) pos = 0;
		if (strncmp(&filename[pos], ".ko", 3) !=0)
			filename = xasprintf("%s.ko", filename);
	}

	/* Get a filedesc for the module.  Check if we have a complete path */
	if (stat(filename, &st) < 0 || !S_ISREG(st.st_mode) ||
		(fp = fopen_for_read(filename)) == NULL) {
		/* Hmm.  Could not open it. Search /lib/modules/ */
		int r;
		char *module_dir;

		module_dir = xmalloc_readlink(CONFIG_DEFAULT_MODULES_DIR);
		if (!module_dir)
			module_dir = xstrdup(CONFIG_DEFAULT_MODULES_DIR);
		r = recursive_action(module_dir, ACTION_RECURSE,
			check_module_name_match, NULL, filename, 0);
		free(module_dir);
		if (r)
			bb_error_msg_and_die("'%s': module not found", filename);
		if (m_filename == NULL || ((fp = fopen_for_read(m_filename)) == NULL))
			bb_error_msg_and_die("'%s': module not found", filename);
		filename = m_filename;
	}
	if (fp != NULL)
		fclose(fp);

	rc = bb_init_module(filename, parse_cmdline_module_options(argv, /*quote_spaces:*/ 0));
	if (rc)
		bb_error_msg("can't insert '%s': %s", filename, moderror(rc));

	return rc;
}
