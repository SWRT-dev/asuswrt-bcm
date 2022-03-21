/*
 * libudev - interface to udev device information
 *
 * Copyright (C) 2008-2010 Kay Sievers <kay.sievers@vrfy.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#if defined(RTCONFIG_HND_ROUTER_AX_6756)
#include <sys/sysmacros.h>
#endif
#include <linux/sockios.h>

#include "libudev.h"
#include "libudev-private.h"

/**
 * SECTION:libudev-device
 * @short_description: kernel sys devices
 *
 * Representation of kernel sys devices. Devices are uniquely identified
 * by their syspath, every device has exactly one path in the kernel sys
 * filesystem. Devices usually belong to a kernel subsystem, and and have
 * a unique name inside that subsystem.
 */

/**
 * udev_device:
 *
 * Opaque object representing one kernel sys device.
 */
struct udev_device {
	struct udev *udev;
	struct udev_device *parent_device;
	char *syspath;
	const char *devpath;
	char *sysname;
	const char *sysnum;
	char *devnode;
	mode_t devnode_mode;
	char *subsystem;
	char *devtype;
	char *driver;
	char *action;
	char *devpath_old;
	char *knodename;
	char *id_filename;
	char **envp;
	char *monitor_buf;
	size_t monitor_buf_len;
	struct udev_list_node devlinks_list;
	struct udev_list_node properties_list;
	struct udev_list_node sysattr_value_list;
	struct udev_list_node sysattr_list;
	struct udev_list_node tags_list;
	unsigned long long int seqnum;
	unsigned long long int usec_initialized;
	int timeout;
	int devlink_priority;
	int refcount;
	dev_t devnum;
	int ifindex;
	int watch_handle;
	int maj, min;
	bool parent_set;
	bool subsystem_set;
	bool devtype_set;
	bool devlinks_uptodate;
	bool envp_uptodate;
	bool tags_uptodate;
	bool driver_set;
	bool info_loaded;
	bool db_loaded;
	bool uevent_loaded;
	bool is_initialized;
	bool sysattr_list_read;
	bool db_persist;
};

/**
 * udev_device_get_devnum:
 * @udev_device: udev device
 *
 * This is only valid if the device was received through a monitor. Devices read from
 * sys do not have a sequence number.
 *
 * Returns: the kernel event sequence number, or 0 if there is no sequence number available.
 **/
UDEV_EXPORT unsigned long long int udev_device_get_seqnum(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return 0;
	return udev_device->seqnum;
}

static int udev_device_set_seqnum(struct udev_device *udev_device, unsigned long long int seqnum)
{
	char num[32];

	udev_device->seqnum = seqnum;
	snprintf(num, sizeof(num), "%llu", seqnum);
	udev_device_add_property(udev_device, "SEQNUM", num);
	return 0;
}

int udev_device_get_ifindex(struct udev_device *udev_device)
{
	if (!udev_device->info_loaded)
		udev_device_read_uevent_file(udev_device);
	return udev_device->ifindex;
}

static int udev_device_set_ifindex(struct udev_device *udev_device, int ifindex)
{
	char num[32];

	udev_device->ifindex = ifindex;
	snprintf(num, sizeof(num), "%u", ifindex);
	udev_device_add_property(udev_device, "IFINDEX", num);
	return 0;
}

/**
 * udev_device_get_devnum:
 * @udev_device: udev device
 *
 * Returns: the device major/minor number.
 **/
UDEV_EXPORT dev_t udev_device_get_devnum(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return makedev(0, 0);
	if (!udev_device->info_loaded)
		udev_device_read_uevent_file(udev_device);
	return udev_device->devnum;
}

static int udev_device_set_devnum(struct udev_device *udev_device, dev_t devnum)
{
	char num[32];

	udev_device->devnum = devnum;

	snprintf(num, sizeof(num), "%u", major(devnum));
	udev_device_add_property(udev_device, "MAJOR", num);
	snprintf(num, sizeof(num), "%u", minor(devnum));
	udev_device_add_property(udev_device, "MINOR", num);
	return 0;
}

int udev_device_get_timeout(struct udev_device *udev_device)
{
	return udev_device->timeout;
}

static int udev_device_set_timeout(struct udev_device *udev_device, int timeout)
{
	char num[32];

	udev_device->timeout = timeout;
	snprintf(num, sizeof(num), "%u", timeout);
	udev_device_add_property(udev_device, "TIMEOUT", num);
	return 0;
}

const char *udev_device_get_knodename(struct udev_device *udev_device)
{
	return udev_device->knodename;
}

static int udev_device_set_knodename(struct udev_device *udev_device, const char *knodename)
{
	free(udev_device->knodename);
	udev_device->knodename = strdup(knodename);
	if (udev_device->knodename == NULL)
		return -ENOMEM;
	/* do not overwrite the udev property with the kernel property */
	if (udev_device->devnode == NULL)
		udev_device_add_property(udev_device, "DEVNAME", udev_device->knodename);
	return 0;
}

const char *udev_device_get_devpath_old(struct udev_device *udev_device)
{
	return udev_device->devpath_old;
}

static int udev_device_set_devpath_old(struct udev_device *udev_device, const char *devpath_old)
{
	const char *pos;

	free(udev_device->devpath_old);
	udev_device->devpath_old = strdup(devpath_old);
	if (udev_device->devpath_old == NULL)
		return -ENOMEM;
	udev_device_add_property(udev_device, "DEVPATH_OLD", udev_device->devpath_old);

	pos = strrchr(udev_device->devpath_old, '/');
	if (pos == NULL)
		return -EINVAL;
	return 0;
}

/**
 * udev_device_get_driver:
 * @udev_device: udev device
 *
 * Returns: the driver string, or #NULL if there is no driver attached.
 **/
UDEV_EXPORT const char *udev_device_get_driver(struct udev_device *udev_device)
{
	char driver[UTIL_NAME_SIZE];

	if (udev_device == NULL)
		return NULL;
	if (!udev_device->driver_set) {
		udev_device->driver_set = true;
		if (util_get_sys_driver(udev_device->udev, udev_device->syspath, driver, sizeof(driver)) > 0)
			udev_device->driver = strdup(driver);
	}
	return udev_device->driver;
}

static int udev_device_set_driver(struct udev_device *udev_device, const char *driver)
{
	free(udev_device->driver);
	udev_device->driver = strdup(driver);
	if (udev_device->driver == NULL)
		return -ENOMEM;
	udev_device->driver_set = true;
	udev_device_add_property(udev_device, "DRIVER", udev_device->driver);
	return 0;
}

/**
 * udev_device_get_devtype:
 * @udev_device: udev device
 *
 * Retrieve the devtype string of the udev device.
 *
 * Returns: the devtype name of the udev device, or #NULL if it can not be determined
 **/
UDEV_EXPORT const char *udev_device_get_devtype(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->devtype_set) {
		udev_device->devtype_set = true;
		udev_device_read_uevent_file(udev_device);
	}
	return udev_device->devtype;
}

static int udev_device_set_devtype(struct udev_device *udev_device, const char *devtype)
{
	free(udev_device->devtype);
	udev_device->devtype = strdup(devtype);
	if (udev_device->devtype == NULL)
		return -ENOMEM;
	udev_device->devtype_set = true;
	udev_device_add_property(udev_device, "DEVTYPE", udev_device->devtype);
	return 0;
}

static int udev_device_set_subsystem(struct udev_device *udev_device, const char *subsystem)
{
	free(udev_device->subsystem);
	udev_device->subsystem = strdup(subsystem);
	if (udev_device->subsystem == NULL)
		return -ENOMEM;
	udev_device->subsystem_set = true;
	udev_device_add_property(udev_device, "SUBSYSTEM", udev_device->subsystem);
	return 0;
}

/**
 * udev_device_get_subsystem:
 * @udev_device: udev device
 *
 * Retrieve the subsystem string of the udev device. The string does not
 * contain any "/".
 *
 * Returns: the subsystem name of the udev device, or #NULL if it can not be determined
 **/
UDEV_EXPORT const char *udev_device_get_subsystem(struct udev_device *udev_device)
{
	char subsystem[UTIL_NAME_SIZE];

	if (udev_device == NULL)
		return NULL;
	if (!udev_device->subsystem_set) {
		udev_device->subsystem_set = true;
		/* read "subsystem" link */
		if (util_get_sys_subsystem(udev_device->udev, udev_device->syspath, subsystem, sizeof(subsystem)) > 0) {
			udev_device_set_subsystem(udev_device, subsystem);
			return udev_device->subsystem;
		}
		/* implicit names */
		if (strncmp(udev_device->devpath, "/module/", 8) == 0) {
			udev_device_set_subsystem(udev_device, "module");
			return udev_device->subsystem;
		}
		if (strstr(udev_device->devpath, "/drivers/") != NULL) {
			udev_device_set_subsystem(udev_device, "drivers");
			return udev_device->subsystem;
		}
		if (strncmp(udev_device->devpath, "/subsystem/", 11) == 0 ||
		    strncmp(udev_device->devpath, "/class/", 7) == 0 ||
		    strncmp(udev_device->devpath, "/bus/", 5) == 0) {
			udev_device_set_subsystem(udev_device, "subsystem");
			return udev_device->subsystem;
		}
	}
	return udev_device->subsystem;
}

mode_t udev_device_get_devnode_mode(struct udev_device *udev_device)
{
	if (!udev_device->info_loaded)
		udev_device_read_uevent_file(udev_device);
	return udev_device->devnode_mode;
}

static int udev_device_set_devnode_mode(struct udev_device *udev_device, mode_t mode)
{
	char num[32];

	udev_device->devnode_mode = mode;
	snprintf(num, sizeof(num), "%#o", mode);
	udev_device_add_property(udev_device, "DEVMODE", num);
	return 0;
}

struct udev_list_entry *udev_device_add_property(struct udev_device *udev_device, const char *key, const char *value)
{
	udev_device->envp_uptodate = false;
	if (value == NULL) {
		struct udev_list_entry *list_entry;

		list_entry = udev_device_get_properties_list_entry(udev_device);
		list_entry = udev_list_entry_get_by_name(list_entry, key);
		if (list_entry != NULL)
			udev_list_entry_delete(list_entry);
		return NULL;
	}
	return udev_list_entry_add(udev_device->udev, &udev_device->properties_list, key, value, UDEV_LIST_UNIQUE);
}

static struct udev_list_entry *udev_device_add_property_from_string(struct udev_device *udev_device, const char *property)
{
	char name[UTIL_LINE_SIZE];
	char *val;

	util_strscpy(name, sizeof(name), property);
	val = strchr(name, '=');
	if (val == NULL)
		return NULL;
	val[0] = '\0';
	val = &val[1];
	if (val[0] == '\0')
		val = NULL;
	return udev_device_add_property(udev_device, name, val);
}

/*
 * parse property string, and if needed, update internal values accordingly
 *
 * udev_device_add_property_from_string_parse_finish() needs to be
 * called after adding properties, and its return value checked
 *
 * udev_device_set_info_loaded() needs to be set, to avoid trying
 * to use a device without a DEVPATH set
 */
void udev_device_add_property_from_string_parse(struct udev_device *udev_device, const char *property)
{
	if (strncmp(property, "DEVPATH=", 8) == 0) {
		char path[UTIL_PATH_SIZE];

		util_strscpyl(path, sizeof(path), udev_get_sys_path(udev_device->udev), &property[8], NULL);
		udev_device_set_syspath(udev_device, path);
	} else if (strncmp(property, "SUBSYSTEM=", 10) == 0) {
		udev_device_set_subsystem(udev_device, &property[10]);
	} else if (strncmp(property, "DEVTYPE=", 8) == 0) {
		udev_device_set_devtype(udev_device, &property[8]);
	} else if (strncmp(property, "DEVNAME=", 8) == 0) {
		if (property[8] == '/')
			udev_device_set_devnode(udev_device, &property[8]);
		else
			udev_device_set_knodename(udev_device, &property[8]);
	} else if (strncmp(property, "DEVLINKS=", 9) == 0) {
		char devlinks[UTIL_PATH_SIZE];
		char *slink;
		char *next;

		util_strscpy(devlinks, sizeof(devlinks), &property[9]);
		slink = devlinks;
		next = strchr(slink, ' ');
		while (next != NULL) {
			next[0] = '\0';
			udev_device_add_devlink(udev_device, slink, 0);
			slink = &next[1];
			next = strchr(slink, ' ');
		}
		if (slink[0] != '\0')
			udev_device_add_devlink(udev_device, slink, 0);
	} else if (strncmp(property, "TAGS=", 5) == 0) {
		char tags[UTIL_PATH_SIZE];
		char *next;

		util_strscpy(tags, sizeof(tags), &property[5]);
		next = strchr(tags, ':');
		if (next != NULL) {
			next++;
			while (next[0] != '\0') {
				char *tag;

				tag = next;
				next = strchr(tag, ':');
				if (next == NULL)
					break;
				next[0] = '\0';
				next++;
				udev_device_add_tag(udev_device, tag);
			}
		}
	} else if (strncmp(property, "DRIVER=", 7) == 0) {
		udev_device_set_driver(udev_device, &property[7]);
	} else if (strncmp(property, "ACTION=", 7) == 0) {
		udev_device_set_action(udev_device, &property[7]);
	} else if (strncmp(property, "MAJOR=", 6) == 0) {
		udev_device->maj = strtoull(&property[6], NULL, 10);
	} else if (strncmp(property, "MINOR=", 6) == 0) {
		udev_device->min = strtoull(&property[6], NULL, 10);
	} else if (strncmp(property, "DEVPATH_OLD=", 12) == 0) {
		udev_device_set_devpath_old(udev_device, &property[12]);
	} else if (strncmp(property, "SEQNUM=", 7) == 0) {
		udev_device_set_seqnum(udev_device, strtoull(&property[7], NULL, 10));
	} else if (strncmp(property, "TIMEOUT=", 8) == 0) {
		udev_device_set_timeout(udev_device, strtoull(&property[8], NULL, 10));
	} else if (strncmp(property, "IFINDEX=", 8) == 0) {
		udev_device_set_ifindex(udev_device, strtoull(&property[8], NULL, 10));
	} else if (strncmp(property, "DEVMODE=", 8) == 0) {
		udev_device_set_devnode_mode(udev_device, strtoul(&property[8], NULL, 8));
	} else {
		udev_device_add_property_from_string(udev_device, property);
	}
}

int udev_device_add_property_from_string_parse_finish(struct udev_device *udev_device)
{
	if (udev_device->maj > 0)
		udev_device_set_devnum(udev_device, makedev(udev_device->maj, udev_device->min));
	udev_device->maj = 0;
	udev_device->min = 0;

	if (udev_device->devpath == NULL || udev_device->subsystem == NULL)
		return -EINVAL;
	return 0;
}

/**
 * udev_device_get_property_value:
 * @udev_device: udev device
 * @key: property name
 *
 * Returns: the value of a device property, or #NULL if there is no such property.
 **/
UDEV_EXPORT const char *udev_device_get_property_value(struct udev_device *udev_device, const char *key)
{
	struct udev_list_entry *list_entry;

	if (udev_device == NULL)
		return NULL;
	if (key == NULL)
		return NULL;

	list_entry = udev_device_get_properties_list_entry(udev_device);
	list_entry =  udev_list_entry_get_by_name(list_entry, key);
	return udev_list_entry_get_value(list_entry);
}

int udev_device_read_db(struct udev_device *udev_device, const char *dbfile)
{
	char filename[UTIL_PATH_SIZE];
	char line[UTIL_LINE_SIZE];
	FILE *f;

	/* providing a database file will always force-load it */
	if (dbfile == NULL) {
		const char *id;

		if (udev_device->db_loaded)
			return 0;
		udev_device->db_loaded = true;

		id = udev_device_get_id_filename(udev_device);
		if (id == NULL)
			return -1;
		util_strscpyl(filename, sizeof(filename), udev_get_run_path(udev_device->udev), "/data/", id, NULL);
		dbfile = filename;
	}

	f = fopen(dbfile, "re");
	if (f == NULL) {
		info(udev_device->udev, "no db file to read %s: %m\n", dbfile);
		return -1;
	}
	udev_device->is_initialized = true;

	while (fgets(line, sizeof(line), f)) {
		ssize_t len;
		const char *val;
		struct udev_list_entry *entry;

		len = strlen(line);
		if (len < 4)
			break;
		line[len-1] = '\0';
		val = &line[2];
		switch(line[0]) {
		case 'N':
			util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev_device->udev), "/", val, NULL);
			udev_device_set_devnode(udev_device, filename);
			break;
		case 'S':
			util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev_device->udev), "/", val, NULL);
			udev_device_add_devlink(udev_device, filename, 0);
			break;
		case 'L':
			udev_device_set_devlink_priority(udev_device, atoi(val));
			break;
		case 'E':
			entry = udev_device_add_property_from_string(udev_device, val);
			udev_list_entry_set_num(entry, true);
			break;
		case 'G':
			udev_device_add_tag(udev_device, val);
			break;
		case 'W':
			udev_device_set_watch_handle(udev_device, atoi(val));
			break;
		case 'I':
			udev_device_set_usec_initialized(udev_device, strtoull(val, NULL, 10));
			break;
		}
	}
	fclose(f);

	info(udev_device->udev, "device %p filled with db file data\n", udev_device);
	return 0;
}

int udev_device_read_uevent_file(struct udev_device *udev_device)
{
	char filename[UTIL_PATH_SIZE];
	FILE *f;
	char line[UTIL_LINE_SIZE];
	int maj = 0;
	int min = 0;

	if (udev_device->uevent_loaded)
		return 0;

	util_strscpyl(filename, sizeof(filename), udev_device->syspath, "/uevent", NULL);
	f = fopen(filename, "re");
	if (f == NULL)
		return -1;
	udev_device->uevent_loaded = true;

	while (fgets(line, sizeof(line), f)) {
		char *pos;

		pos = strchr(line, '\n');
		if (pos == NULL)
			continue;
		pos[0] = '\0';

		if (strncmp(line, "DEVTYPE=", 8) == 0)
			udev_device_set_devtype(udev_device, &line[8]);
		else if (strncmp(line, "MAJOR=", 6) == 0)
			maj = strtoull(&line[6], NULL, 10);
		else if (strncmp(line, "MINOR=", 6) == 0)
			min = strtoull(&line[6], NULL, 10);
		else if (strncmp(line, "IFINDEX=", 8) == 0)
			udev_device_set_ifindex(udev_device, strtoull(&line[8], NULL, 10));
		else if (strncmp(line, "DEVNAME=", 8) == 0)
			udev_device_set_knodename(udev_device, &line[8]);
		else if (strncmp(line, "DEVMODE=", 8) == 0)
			udev_device->devnode_mode = strtoul(&line[8], NULL, 8);

		udev_device_add_property_from_string(udev_device, line);
	}

	udev_device->devnum = makedev(maj, min);
	fclose(f);
	return 0;
}

void udev_device_set_info_loaded(struct udev_device *device)
{
	device->info_loaded = true;
}

struct udev_device *udev_device_new(struct udev *udev)
{
	struct udev_device *udev_device;
	struct udev_list_entry *list_entry;

	if (udev == NULL)
		return NULL;

	udev_device = calloc(1, sizeof(struct udev_device));
	if (udev_device == NULL)
		return NULL;
	udev_device->refcount = 1;
	udev_device->udev = udev;
	udev_list_init(&udev_device->devlinks_list);
	udev_list_init(&udev_device->properties_list);
	udev_list_init(&udev_device->sysattr_value_list);
	udev_list_init(&udev_device->sysattr_list);
	udev_list_init(&udev_device->tags_list);
	udev_device->timeout = -1;
	udev_device->watch_handle = -1;
	/* copy global properties */
	udev_list_entry_foreach(list_entry, udev_get_properties_list_entry(udev))
		udev_device_add_property(udev_device,
					 udev_list_entry_get_name(list_entry),
					 udev_list_entry_get_value(list_entry));
	dbg(udev_device->udev, "udev_device: %p created\n", udev_device);
	return udev_device;
}

/**
 * udev_device_new_from_syspath:
 * @udev: udev library context
 * @syspath: sys device path including sys directory
 *
 * Create new udev device, and fill in information from the sys
 * device and the udev database entry. The syspath is the absolute
 * path to the device, including the sys mount point.
 *
 * The initial refcount is 1, and needs to be decremented to
 * release the resources of the udev device.
 *
 * Returns: a new udev device, or #NULL, if it does not exist
 **/
UDEV_EXPORT struct udev_device *udev_device_new_from_syspath(struct udev *udev, const char *syspath)
{
	size_t len;
	const char *subdir;
	char path[UTIL_PATH_SIZE];
	char *pos;
	struct stat statbuf;
	struct udev_device *udev_device;

	if (udev == NULL)
		return NULL;
	if (syspath == NULL)
		return NULL;

	/* path starts in sys */
	len = strlen(udev_get_sys_path(udev));
	if (strncmp(syspath, udev_get_sys_path(udev), len) != 0) {
		info(udev, "not in sys :%s\n", syspath);
		return NULL;
	}

	/* path is not a root directory */
	subdir = &syspath[len+1];
	pos = strrchr(subdir, '/');
	if (pos == NULL || pos[1] == '\0' || pos < &subdir[2]) {
		dbg(udev, "not a subdir :%s\n", syspath);
		return NULL;
	}

	/* resolve possible symlink to real path */
	util_strscpy(path, sizeof(path), syspath);
	util_resolve_sys_link(udev, path, sizeof(path));

	if (strncmp(&path[len], "/devices/", 9) == 0) {
		char file[UTIL_PATH_SIZE];

		/* all "devices" require a "uevent" file */
		util_strscpyl(file, sizeof(file), path, "/uevent", NULL);
		if (stat(file, &statbuf) != 0) {
			dbg(udev, "not a device: %s\n", syspath);
			return NULL;
		}
	} else {
		/* everything else just needs to be a directory */
		if (stat(path, &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
			dbg(udev, "directory not found: %s\n", syspath);
			return NULL;
		}
	}

	udev_device = udev_device_new(udev);
	if (udev_device == NULL)
		return NULL;

	udev_device_set_syspath(udev_device, path);
	info(udev, "device %p has devpath '%s'\n", udev_device, udev_device_get_devpath(udev_device));

	return udev_device;
}

/**
 * udev_device_new_from_devnum:
 * @udev: udev library context
 * @type: char or block device
 * @devnum: device major/minor number
 *
 * Create new udev device, and fill in information from the sys
 * device and the udev database entry. The device is looked-up
 * by its major/minor number and type. Character and block device
 * numbers are not unique across the two types.
 *
 * The initial refcount is 1, and needs to be decremented to
 * release the resources of the udev device.
 *
 * Returns: a new udev device, or #NULL, if it does not exist
 **/
UDEV_EXPORT struct udev_device *udev_device_new_from_devnum(struct udev *udev, char type, dev_t devnum)
{
	char path[UTIL_PATH_SIZE];
	const char *type_str;

	if (type == 'b')
		type_str = "block";
	else if (type == 'c')
		type_str = "char";
	else
		return NULL;

	/* use /sys/dev/{block,char}/<maj>:<min> link */
	snprintf(path, sizeof(path), "%s/dev/%s/%u:%u",
		 udev_get_sys_path(udev), type_str, major(devnum), minor(devnum));
	return udev_device_new_from_syspath(udev, path);
}

struct udev_device *udev_device_new_from_id_filename(struct udev *udev, char *id)
{
	char type;
	int maj, min;
	char subsys[UTIL_PATH_SIZE];
	char *sysname;

	switch(id[0]) {
	case 'b':
	case 'c':
		if (sscanf(id, "%c%i:%i", &type, &maj, &min) != 3)
			return NULL;
		return udev_device_new_from_devnum(udev, type, makedev(maj, min));
	case 'n': {
		int sk;
		struct ifreq ifr;
		struct udev_device *dev;
		int ifindex;

		ifindex = strtoul(&id[1], NULL, 10);
		if (ifindex <= 0)
			return NULL;

		sk = socket(PF_INET, SOCK_DGRAM, 0);
		if (sk < 0)
			return NULL;
		memset(&ifr, 0x00, sizeof(struct ifreq));
		ifr.ifr_ifindex = ifindex;
		if (ioctl(sk, SIOCGIFNAME, &ifr) != 0) {
			close(sk);
			return NULL;
		}
		close(sk);

		dev = udev_device_new_from_subsystem_sysname(udev, "net", ifr.ifr_name);
		if (dev == NULL)
			return NULL;
		if (udev_device_get_ifindex(dev) == ifindex)
			return dev;
		udev_device_unref(dev);
		return NULL;
	}
	case '+':
		util_strscpy(subsys, sizeof(subsys), &id[1]);
		sysname = strchr(subsys, ':');
		if (sysname == NULL)
			return NULL;
		sysname[0] = '\0';
		sysname = &sysname[1];
		return udev_device_new_from_subsystem_sysname(udev, subsys, sysname);
	default:
		return NULL;
	}
}

/**
 * udev_device_new_from_subsystem_sysname:
 * @udev: udev library context
 * @subsystem: the subsystem of the device
 * @sysname: the name of the device
 *
 * Create new udev device, and fill in information from the sys device
 * and the udev database entry. The device is looked up by the subsystem
 * and name string of the device, like "mem" / "zero", or "block" / "sda".
 *
 * The initial refcount is 1, and needs to be decremented to
 * release the resources of the udev device.
 *
 * Returns: a new udev device, or #NULL, if it does not exist
 **/
UDEV_EXPORT struct udev_device *udev_device_new_from_subsystem_sysname(struct udev *udev, const char *subsystem, const char *sysname)
{
	char path_full[UTIL_PATH_SIZE];
	char *path;
	size_t l;
	struct stat statbuf;

	path = path_full;
	l = util_strpcpyl(&path, sizeof(path_full), udev_get_sys_path(udev), NULL);

	if (strcmp(subsystem, "subsystem") == 0) {
		util_strscpyl(path, l, "/subsystem/", sysname, NULL);
		if (stat(path_full, &statbuf) == 0)
			goto found;

		util_strscpyl(path, l, "/bus/", sysname, NULL);
		if (stat(path_full, &statbuf) == 0)
			goto found;

		util_strscpyl(path, l, "/class/", sysname, NULL);
		if (stat(path_full, &statbuf) == 0)
			goto found;
		goto out;
	}

	if (strcmp(subsystem, "module") == 0) {
		util_strscpyl(path, l, "/module/", sysname, NULL);
		if (stat(path_full, &statbuf) == 0)
			goto found;
		goto out;
	}

	if (strcmp(subsystem, "drivers") == 0) {
		char subsys[UTIL_NAME_SIZE];
		char *driver;

		util_strscpy(subsys, sizeof(subsys), sysname);
		driver = strchr(subsys, ':');
		if (driver != NULL) {
			driver[0] = '\0';
			driver = &driver[1];

			util_strscpyl(path, l, "/subsystem/", subsys, "/drivers/", driver, NULL);
			if (stat(path_full, &statbuf) == 0)
				goto found;

			util_strscpyl(path, l, "/bus/", subsys, "/drivers/", driver, NULL);
			if (stat(path_full, &statbuf) == 0)
				goto found;
		}
		goto out;
	}

	util_strscpyl(path, l, "/subsystem/", subsystem, "/devices/", sysname, NULL);
	if (stat(path_full, &statbuf) == 0)
		goto found;

	util_strscpyl(path, l, "/bus/", subsystem, "/devices/", sysname, NULL);
	if (stat(path_full, &statbuf) == 0)
		goto found;

	util_strscpyl(path, l, "/class/", subsystem, "/", sysname, NULL);
	if (stat(path_full, &statbuf) == 0)
		goto found;
out:
	return NULL;
found:
	return udev_device_new_from_syspath(udev, path_full);
}

/**
 * udev_device_new_from_environment
 * @udev: udev library context
 *
 * Create new udev device, and fill in information from the
 * current process environment. This only works reliable if
 * the process is called from a udev rule. It is usually used
 * for tools executed from IMPORT= rules.
 *
 * The initial refcount is 1, and needs to be decremented to
 * release the resources of the udev device.
 *
 * Returns: a new udev device, or #NULL, if it does not exist
 **/
UDEV_EXPORT struct udev_device *udev_device_new_from_environment(struct udev *udev)
{
	int i;
	struct udev_device *udev_device;

	udev_device = udev_device_new(udev);
	if (udev_device == NULL)
		return NULL;
	udev_device_set_info_loaded(udev_device);

	for (i = 0; environ[i] != NULL; i++)
		udev_device_add_property_from_string_parse(udev_device, environ[i]);

	if (udev_device_add_property_from_string_parse_finish(udev_device) < 0) {
		info(udev, "missing values, invalid device\n");
		udev_device_unref(udev_device);
		udev_device = NULL;
	}

	return udev_device;
}

static struct udev_device *device_new_from_parent(struct udev_device *udev_device)
{
	struct udev_device *udev_device_parent = NULL;
	char path[UTIL_PATH_SIZE];
	const char *subdir;

	util_strscpy(path, sizeof(path), udev_device->syspath);
	subdir = &path[strlen(udev_get_sys_path(udev_device->udev))+1];
	for (;;) {
		char *pos;

		pos = strrchr(subdir, '/');
		if (pos == NULL || pos < &subdir[2])
			break;
		pos[0] = '\0';
		udev_device_parent = udev_device_new_from_syspath(udev_device->udev, path);
		if (udev_device_parent != NULL)
			return udev_device_parent;
	}
	return NULL;
}

/**
 * udev_device_get_parent:
 * @udev_device: the device to start searching from
 *
 * Find the next parent device, and fill in information from the sys
 * device and the udev database entry.
 *
 * The returned the device is not referenced. It is attached to the
 * child device, and will be cleaned up when the child device
 * is cleaned up.
 *
 * It is not necessarily just the upper level directory, empty or not
 * recognized sys directories are ignored.
 *
 * It can be called as many times as needed, without caring about
 * references.
 *
 * Returns: a new udev device, or #NULL, if it no parent exist.
 **/
UDEV_EXPORT struct udev_device *udev_device_get_parent(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->parent_set) {
		udev_device->parent_set = true;
		udev_device->parent_device = device_new_from_parent(udev_device);
	}
	if (udev_device->parent_device != NULL)
		dbg(udev_device->udev, "returning existing parent %p\n", udev_device->parent_device);
	return udev_device->parent_device;
}

/**
 * udev_device_get_parent_with_subsystem_devtype:
 * @udev_device: udev device to start searching from
 * @subsystem: the subsystem of the device
 * @devtype: the type (DEVTYPE) of the device
 *
 * Find the next parent device, with a matching subsystem and devtype
 * value, and fill in information from the sys device and the udev
 * database entry.
 *
 * If devtype is #NULL, only subsystem is checked, and any devtype will
 * match.
 *
 * The returned the device is not referenced. It is attached to the
 * child device, and will be cleaned up when the child device
 * is cleaned up.
 *
 * It can be called as many times as needed, without caring about
 * references.
 *
 * Returns: a new udev device, or #NULL if no matching parent exists.
 **/
UDEV_EXPORT struct udev_device *udev_device_get_parent_with_subsystem_devtype(struct udev_device *udev_device, const char *subsystem, const char *devtype)
{
	struct udev_device *parent;

	if (subsystem == NULL)
		return NULL;

	parent = udev_device_get_parent(udev_device);
	while (parent != NULL) {
		const char *parent_subsystem;
		const char *parent_devtype;

		parent_subsystem = udev_device_get_subsystem(parent);
		if (parent_subsystem != NULL && strcmp(parent_subsystem, subsystem) == 0) {
			if (devtype == NULL)
				break;
			parent_devtype = udev_device_get_devtype(parent);
			if (parent_devtype != NULL && strcmp(parent_devtype, devtype) == 0)
				break;
		}
		parent = udev_device_get_parent(parent);
	}
	return parent;
}

/**
 * udev_device_get_udev:
 * @udev_device: udev device
 *
 * Retrieve the udev library context the device was created with.
 *
 * Returns: the udev library context
 **/
UDEV_EXPORT struct udev *udev_device_get_udev(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->udev;
}

/**
 * udev_device_ref:
 * @udev_device: udev device
 *
 * Take a reference of a udev device.
 *
 * Returns: the passed udev device
 **/
UDEV_EXPORT struct udev_device *udev_device_ref(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	udev_device->refcount++;
	return udev_device;
}

/**
 * udev_device_unref:
 * @udev_device: udev device
 *
 * Drop a reference of a udev device. If the refcount reaches zero,
 * the resources of the device will be released.
 *
 **/
UDEV_EXPORT void udev_device_unref(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return;
	udev_device->refcount--;
	if (udev_device->refcount > 0)
		return;
	if (udev_device->parent_device != NULL)
		udev_device_unref(udev_device->parent_device);
	free(udev_device->syspath);
	free(udev_device->sysname);
	free(udev_device->devnode);
	free(udev_device->subsystem);
	free(udev_device->devtype);
	udev_list_cleanup_entries(udev_device->udev, &udev_device->devlinks_list);
	udev_list_cleanup_entries(udev_device->udev, &udev_device->properties_list);
	udev_list_cleanup_entries(udev_device->udev, &udev_device->sysattr_value_list);
	udev_list_cleanup_entries(udev_device->udev, &udev_device->sysattr_list);
	udev_list_cleanup_entries(udev_device->udev, &udev_device->tags_list);
	free(udev_device->action);
	free(udev_device->driver);
	free(udev_device->devpath_old);
	free(udev_device->knodename);
	free(udev_device->id_filename);
	free(udev_device->envp);
	free(udev_device->monitor_buf);
	dbg(udev_device->udev, "udev_device: %p released\n", udev_device);
	free(udev_device);
}

/**
 * udev_device_get_devpath:
 * @udev_device: udev device
 *
 * Retrieve the kernel devpath value of the udev device. The path
 * does not contain the sys mount point, and starts with a '/'.
 *
 * Returns: the devpath of the udev device
 **/
UDEV_EXPORT const char *udev_device_get_devpath(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->devpath;
}

/**
 * udev_device_get_syspath:
 * @udev_device: udev device
 *
 * Retrieve the sys path of the udev device. The path is an
 * absolute path and starts with the sys mount point.
 *
 * Returns: the sys path of the udev device
 **/
UDEV_EXPORT const char *udev_device_get_syspath(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->syspath;
}

/**
 * udev_device_get_sysname:
 * @udev_device: udev device
 *
 * Returns: the sys name of the device device
 **/
UDEV_EXPORT const char *udev_device_get_sysname(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->sysname;
}

/**
 * udev_device_get_sysnum:
 * @udev_device: udev device
 *
 * Returns: the trailing number of of the device name
 **/
UDEV_EXPORT const char *udev_device_get_sysnum(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->sysnum;
}

/**
 * udev_device_get_devnode:
 * @udev_device: udev device
 *
 * Retrieve the device node file name belonging to the udev device.
 * The path is an absolute path, and starts with the device directory.
 *
 * Returns: the device node file name of the udev device, or #NULL if no device node exists
 **/
UDEV_EXPORT const char *udev_device_get_devnode(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->info_loaded) {
		udev_device_read_uevent_file(udev_device);
		udev_device_read_db(udev_device, NULL);
	}

	/* we might get called before we handled an event and have a db, use the kernel-provided name */
	if (udev_device->devnode == NULL && udev_device_get_knodename(udev_device) != NULL) {
		char filename[UTIL_NAME_SIZE];

		util_strscpyl(filename, sizeof(filename), udev_get_dev_path(udev_device->udev), "/",
			      udev_device_get_knodename(udev_device), NULL);
		udev_device_set_devnode(udev_device, filename);
		return udev_device->devnode;
	}

	return udev_device->devnode;
}

/**
 * udev_device_get_devlinks_list_entry:
 * @udev_device: udev device
 *
 * Retrieve the list of device links pointing to the device file of
 * the udev device. The next list entry can be retrieved with
 * udev_list_entry_next(), which returns #NULL if no more entries exist.
 * The devlink path can be retrieved from the list entry by
 * udev_list_entry_get_name(). The path is an absolute path, and starts with
 * the device directory.
 *
 * Returns: the first entry of the device node link list
 **/
UDEV_EXPORT struct udev_list_entry *udev_device_get_devlinks_list_entry(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	return udev_list_get_entry(&udev_device->devlinks_list);
}

void udev_device_cleanup_devlinks_list(struct udev_device *udev_device)
{
	udev_device->devlinks_uptodate = false;
	udev_list_cleanup_entries(udev_device->udev, &udev_device->devlinks_list);
}

/**
 * udev_device_get_properties_list_entry:
 * @udev_device: udev device
 *
 * Retrieve the list of key/value device properties of the udev
 * device. The next list entry can be retrieved with udev_list_entry_next(),
 * which returns #NULL if no more entries exist. The property name
 * can be retrieved from the list entry by udev_list_get_name(),
 * the property value by udev_list_get_value().
 *
 * Returns: the first entry of the property list
 **/
UDEV_EXPORT struct udev_list_entry *udev_device_get_properties_list_entry(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->info_loaded) {
		udev_device_read_uevent_file(udev_device);
		udev_device_read_db(udev_device, NULL);
	}
	if (!udev_device->devlinks_uptodate) {
		char symlinks[UTIL_PATH_SIZE];
		struct udev_list_entry *list_entry;

		udev_device->devlinks_uptodate = true;
		list_entry = udev_device_get_devlinks_list_entry(udev_device);
		if (list_entry != NULL) {
			char *s;
			size_t l;

			s = symlinks;
			l = util_strpcpyl(&s, sizeof(symlinks), udev_list_entry_get_name(list_entry), NULL);
			udev_list_entry_foreach(list_entry, udev_list_entry_get_next(list_entry))
				l = util_strpcpyl(&s, l, " ", udev_list_entry_get_name(list_entry), NULL);
			udev_device_add_property(udev_device, "DEVLINKS", symlinks);
		}
	}
	if (!udev_device->tags_uptodate) {
		udev_device->tags_uptodate = true;
		if (udev_device_get_tags_list_entry(udev_device) != NULL) {
			char tags[UTIL_PATH_SIZE];
			struct udev_list_entry *list_entry;
			char *s;
			size_t l;

			s = tags;
			l = util_strpcpyl(&s, sizeof(tags), ":", NULL);
			udev_list_entry_foreach(list_entry, udev_device_get_tags_list_entry(udev_device))
				l = util_strpcpyl(&s, l, udev_list_entry_get_name(list_entry), ":", NULL);
			udev_device_add_property(udev_device, "TAGS", tags);
		}
	}
	return udev_list_get_entry(&udev_device->properties_list);
}

/**
 * udev_device_get_action:
 * @udev_device: udev device
 *
 * This is only valid if the device was received through a monitor. Devices read from
 * sys do not have an action string. Usual actions are: add, remove, change, online,
 * offline.
 *
 * Returns: the kernel action value, or #NULL if there is no action value available.
 **/
UDEV_EXPORT const char *udev_device_get_action(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	return udev_device->action;
}

/**
 * udev_device_get_usec_since_initialized:
 * @udev_device: udev device
 *
 * Return the number of microseconds passed since udev set up the
 * device for the first time.
 *
 * This is only implemented for devices with need to store properties
 * in the udev database. All other devices return 0 here.
 *
 * Returns: the number of microseconds since the device was first seen.
 **/
UDEV_EXPORT unsigned long long int udev_device_get_usec_since_initialized(struct udev_device *udev_device)
{
	unsigned long long now;

	if (udev_device == NULL)
		return 0;
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	if (udev_device->usec_initialized == 0)
		return 0;
	now = now_usec();
	if (now == 0)
		return 0;
	return now - udev_device->usec_initialized;
}

unsigned long long udev_device_get_usec_initialized(struct udev_device *udev_device)
{
	return udev_device->usec_initialized;
}

void udev_device_set_usec_initialized(struct udev_device *udev_device, unsigned long long usec_initialized)
{
	udev_device->usec_initialized = usec_initialized;
}

/**
 * udev_device_get_sysattr_value:
 * @udev_device: udev device
 * @sysattr: attribute name
 *
 * The retrieved value is cached in the device. Repeated calls will return the same
 * value and not open the attribute again.
 *
 * Returns: the content of a sys attribute file, or #NULL if there is no sys attribute value.
 **/
UDEV_EXPORT const char *udev_device_get_sysattr_value(struct udev_device *udev_device, const char *sysattr)
{
	struct udev_list_entry *list_entry;
	char path[UTIL_PATH_SIZE];
	char value[4096];
	struct stat statbuf;
	int fd;
	ssize_t size;
	const char *val = NULL;

	if (udev_device == NULL)
		return NULL;
	if (sysattr == NULL)
		return NULL;

	/* look for possibly already cached result */
	udev_list_entry_foreach(list_entry, udev_list_get_entry(&udev_device->sysattr_value_list)) {
		if (strcmp(udev_list_entry_get_name(list_entry), sysattr) == 0) {
			dbg(udev_device->udev, "got '%s' (%s) from cache\n",
			    sysattr, udev_list_entry_get_value(list_entry));
			return udev_list_entry_get_value(list_entry);
		}
	}

	util_strscpyl(path, sizeof(path), udev_device_get_syspath(udev_device), "/", sysattr, NULL);
	if (lstat(path, &statbuf) != 0) {
		dbg(udev_device->udev, "no attribute '%s', keep negative entry\n", path);
		udev_list_entry_add(udev_device->udev, &udev_device->sysattr_value_list, sysattr, NULL, 0);
		goto out;
	}

	if (S_ISLNK(statbuf.st_mode)) {
		char target[UTIL_NAME_SIZE];
		int len;
		char *pos;

		/* some core links return the last element of the target path */
		if (strcmp(sysattr, "driver") != 0 &&
		    strcmp(sysattr, "subsystem") != 0 &&
		    strcmp(sysattr, "module") != 0)
			goto out;

		len = readlink(path, target, sizeof(target));
		if (len <= 0 || len == sizeof(target))
			goto out;
		target[len] = '\0';

		pos = strrchr(target, '/');
		if (pos != NULL) {
			pos = &pos[1];
			dbg(udev_device->udev, "cache '%s' with link value '%s'\n", sysattr, pos);
			list_entry = udev_list_entry_add(udev_device->udev, &udev_device->sysattr_value_list, sysattr, pos, 0);
			val = udev_list_entry_get_value(list_entry);
		}

		goto out;
	}

	/* skip directories */
	if (S_ISDIR(statbuf.st_mode))
		goto out;

	/* skip non-readable files */
	if ((statbuf.st_mode & S_IRUSR) == 0)
		goto out;

	/* read attribute value */
	fd = open(path, O_RDONLY|O_CLOEXEC);
	if (fd < 0) {
		dbg(udev_device->udev, "attribute '%s' can not be opened\n", path);
		goto out;
	}
	size = read(fd, value, sizeof(value));
	close(fd);
	if (size < 0)
		goto out;
	if (size == sizeof(value))
		goto out;

	/* got a valid value, store it in cache and return it */
	value[size] = '\0';
	util_remove_trailing_chars(value, '\n');
	dbg(udev_device->udev, "'%s' has attribute value '%s'\n", path, value);
	list_entry = udev_list_entry_add(udev_device->udev, &udev_device->sysattr_value_list, sysattr, value, 0);
	val = udev_list_entry_get_value(list_entry);
out:
	return val;
}

static int udev_device_sysattr_list_read(struct udev_device *udev_device)
{
	struct dirent *dent;
	DIR *dir;
	int num = 0;

	if (udev_device == NULL)
		return -1;
	if (udev_device->sysattr_list_read)
		return 0;

	dir = opendir(udev_device_get_syspath(udev_device));
	if (!dir) {
		dbg(udev_device->udev, "sysfs dir '%s' can not be opened\n",
				udev_device_get_syspath(udev_device));
		return -1;
	}

	for (dent = readdir(dir); dent != NULL; dent = readdir(dir)) {
		char path[UTIL_PATH_SIZE];
		struct stat statbuf;

		/* only handle symlinks and regular files */
		if (dent->d_type != DT_LNK && dent->d_type != DT_REG)
			continue;

		util_strscpyl(path, sizeof(path), udev_device_get_syspath(udev_device), "/", dent->d_name, NULL);
		if (lstat(path, &statbuf) != 0)
			continue;
		if ((statbuf.st_mode & S_IRUSR) == 0)
			continue;

		udev_list_entry_add(udev_device->udev, &udev_device->sysattr_list,
				    dent->d_name, NULL, 0);
		num++;
	}

	closedir(dir);
	dbg(udev_device->udev, "found %d sysattrs for '%s'\n", num, udev_device_get_syspath(udev_device));
	udev_device->sysattr_list_read = true;

	return num;
}

/**
 * udev_device_get_sysattr_list_entry:
 * @udev_device: udev device
 *
 * Retrieve the list of available sysattrs, with value being empty;
 * This just return all available sysfs attributes for a particular
 * device without reading their values.
 *
 * Returns: the first entry of the property list
 **/
UDEV_EXPORT struct udev_list_entry *udev_device_get_sysattr_list_entry(struct udev_device *udev_device)
{
	if (!udev_device->sysattr_list_read) {
		int ret;
		ret = udev_device_sysattr_list_read(udev_device);
		if (0 > ret)
			return NULL;
	}

	return udev_list_get_entry(&udev_device->sysattr_list);
}

int udev_device_set_syspath(struct udev_device *udev_device, const char *syspath)
{
	const char *pos;
	size_t len;

	free(udev_device->syspath);
	udev_device->syspath = strdup(syspath);
	if (udev_device->syspath ==  NULL)
		return -ENOMEM;
	udev_device->devpath = &udev_device->syspath[strlen(udev_get_sys_path(udev_device->udev))];
	udev_device_add_property(udev_device, "DEVPATH", udev_device->devpath);

	pos = strrchr(udev_device->syspath, '/');
	if (pos == NULL)
		return -EINVAL;
	udev_device->sysname = strdup(&pos[1]);
	if (udev_device->sysname == NULL)
		return -ENOMEM;

	/* some devices have '!' in their name, change that to '/' */
	len = 0;
	while (udev_device->sysname[len] != '\0') {
		if (udev_device->sysname[len] == '!')
			udev_device->sysname[len] = '/';
		len++;
	}

	/* trailing number */
	while (len > 0 && isdigit(udev_device->sysname[--len]))
		udev_device->sysnum = &udev_device->sysname[len];

	/* sysname is completely numeric */
	if (len == 0)
		udev_device->sysnum = NULL;

	return 0;
}

int udev_device_set_devnode(struct udev_device *udev_device, const char *devnode)
{
	free(udev_device->devnode);
	udev_device->devnode = strdup(devnode);
	if (udev_device->devnode == NULL)
		return -ENOMEM;
	udev_device_add_property(udev_device, "DEVNAME", udev_device->devnode);
	return 0;
}

int udev_device_add_devlink(struct udev_device *udev_device, const char *devlink, int unique)
{
	struct udev_list_entry *list_entry;

	udev_device->devlinks_uptodate = false;
	list_entry = udev_list_entry_add(udev_device->udev, &udev_device->devlinks_list, devlink, NULL, UDEV_LIST_UNIQUE);
	if (list_entry == NULL)
		return -ENOMEM;
	if (unique)
		udev_list_entry_set_num(list_entry, true);
	return 0;
}

const char *udev_device_get_id_filename(struct udev_device *udev_device)
{
	if (udev_device->id_filename == NULL) {
		if (udev_device_get_subsystem(udev_device) == NULL)
			return NULL;

		if (major(udev_device_get_devnum(udev_device)) > 0) {
			/* use dev_t -- b259:131072, c254:0 */
			if (asprintf(&udev_device->id_filename, "%c%u:%u",
				     strcmp(udev_device_get_subsystem(udev_device), "block") == 0 ? 'b' : 'c',
				     major(udev_device_get_devnum(udev_device)),
				     minor(udev_device_get_devnum(udev_device))) < 0)
				udev_device->id_filename = NULL;
		} else if (udev_device_get_ifindex(udev_device) > 0) {
			/* use netdev ifindex -- n3 */
			if (asprintf(&udev_device->id_filename, "n%u", udev_device_get_ifindex(udev_device)) < 0)
				udev_device->id_filename = NULL;
		} else {
			/*
			 * use $subsys:$syname -- pci:0000:00:1f.2
			 * sysname() has '!' translated, get it from devpath
			 */
			const char *sysname;
			sysname = strrchr(udev_device->devpath, '/');
			if (sysname == NULL)
				return NULL;
			sysname = &sysname[1];
			if (asprintf(&udev_device->id_filename, "+%s:%s", udev_device_get_subsystem(udev_device), sysname) < 0)
				udev_device->id_filename = NULL;
		}
	}
	return udev_device->id_filename;
}

/**
 * udev_device_get_is_initialized:
 * @udev_device: udev device
 *
 * Check if udev has already handled the device and has set up
 * device node permissions and context, or has renamed a network
 * device.
 *
 * This is only implemented for devices with a device node
 * or network interfaces. All other devices return 1 here.
 *
 * Returns: 1 if the device is set up. 0 otherwise.
 **/
UDEV_EXPORT int udev_device_get_is_initialized(struct udev_device *udev_device)
{
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	return udev_device->is_initialized;
}

void udev_device_set_is_initialized(struct udev_device *udev_device)
{
	udev_device->is_initialized = true;
}

int udev_device_add_tag(struct udev_device *udev_device, const char *tag)
{
	if (strchr(tag, ':') != NULL || strchr(tag, ' ') != NULL)
		return -EINVAL;
	udev_device->tags_uptodate = false;
	if (udev_list_entry_add(udev_device->udev, &udev_device->tags_list, tag, NULL, UDEV_LIST_UNIQUE) != NULL)
		return 0;
	return -ENOMEM;
}

void udev_device_cleanup_tags_list(struct udev_device *udev_device)
{
	udev_device->tags_uptodate = false;
	udev_list_cleanup_entries(udev_device->udev, &udev_device->tags_list);
}

/**
 * udev_device_get_tags_list_entry:
 * @udev_device: udev device
 *
 * Retrieve the list of tags attached to the udev device. The next
 * list entry can be retrieved with udev_list_entry_next(),
 * which returns #NULL if no more entries exist. The tag string
 * can be retrieved from the list entry by udev_list_get_name().
 *
 * Returns: the first entry of the tag list
 **/
UDEV_EXPORT struct udev_list_entry *udev_device_get_tags_list_entry(struct udev_device *udev_device)
{
	if (udev_device == NULL)
		return NULL;
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	return udev_list_get_entry(&udev_device->tags_list);
}

UDEV_EXPORT int udev_device_has_tag(struct udev_device *udev_device, const char *tag)
{
	struct udev_list_entry *list_entry;

	if (udev_device == NULL)
		return false;
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	list_entry = udev_device_get_tags_list_entry(udev_device);
	if (udev_list_entry_get_by_name(list_entry, tag) != NULL)
		return true;
	return false;
}

#define ENVP_SIZE			128
#define MONITOR_BUF_SIZE		4096
static int update_envp_monitor_buf(struct udev_device *udev_device)
{
	struct udev_list_entry *list_entry;
	char *s;
	size_t l;
	unsigned int i;

	/* monitor buffer of property strings */
	free(udev_device->monitor_buf);
	udev_device->monitor_buf_len = 0;
	udev_device->monitor_buf = malloc(MONITOR_BUF_SIZE);
	if (udev_device->monitor_buf == NULL)
		return -ENOMEM;

	/* envp array, strings will point into monitor buffer */
	if (udev_device->envp == NULL)
		udev_device->envp = malloc(sizeof(char *) * ENVP_SIZE);
	if (udev_device->envp == NULL)
		return -ENOMEM;

	i = 0;
	s = udev_device->monitor_buf;
	l = MONITOR_BUF_SIZE;
	udev_list_entry_foreach(list_entry, udev_device_get_properties_list_entry(udev_device)) {
		const char *key;

		key = udev_list_entry_get_name(list_entry);
		/* skip private variables */
		if (key[0] == '.')
			continue;

		/* add string to envp array */
		udev_device->envp[i++] = s;
		if (i+1 >= ENVP_SIZE)
			return -EINVAL;

		/* add property string to monitor buffer */
		l = util_strpcpyl(&s, l, key, "=", udev_list_entry_get_value(list_entry), NULL);
		if (l == 0)
			return -EINVAL;
		/* advance past the trailing '\0' that util_strpcpyl() guarantees */
		s++;
		l--;
	}
	udev_device->envp[i] = NULL;
	udev_device->monitor_buf_len = s - udev_device->monitor_buf;
	udev_device->envp_uptodate = true;
	dbg(udev_device->udev, "filled envp/monitor buffer, %u properties, %zu bytes\n",
	    i, udev_device->monitor_buf_len);
	return 0;
}

char **udev_device_get_properties_envp(struct udev_device *udev_device)
{
	if (!udev_device->envp_uptodate)
		if (update_envp_monitor_buf(udev_device) != 0)
			return NULL;
	return udev_device->envp;
}

ssize_t udev_device_get_properties_monitor_buf(struct udev_device *udev_device, const char **buf)
{
	if (!udev_device->envp_uptodate)
		if (update_envp_monitor_buf(udev_device) != 0)
			return -EINVAL;
	*buf = udev_device->monitor_buf;
	return udev_device->monitor_buf_len;
}

int udev_device_set_action(struct udev_device *udev_device, const char *action)
{
	free(udev_device->action);
	udev_device->action = strdup(action);
	if (udev_device->action == NULL)
		return -ENOMEM;
	udev_device_add_property(udev_device, "ACTION", udev_device->action);
	return 0;
}

int udev_device_get_devlink_priority(struct udev_device *udev_device)
{
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	return udev_device->devlink_priority;
}

int udev_device_set_devlink_priority(struct udev_device *udev_device, int prio)
{
	 udev_device->devlink_priority = prio;
	return 0;
}

int udev_device_get_watch_handle(struct udev_device *udev_device)
{
	if (!udev_device->info_loaded)
		udev_device_read_db(udev_device, NULL);
	return udev_device->watch_handle;
}

int udev_device_set_watch_handle(struct udev_device *udev_device, int handle)
{
	udev_device->watch_handle = handle;
	return 0;
}

bool udev_device_get_db_persist(struct udev_device *udev_device)
{
	return udev_device->db_persist;
}

void udev_device_set_db_persist(struct udev_device *udev_device)
{
	udev_device->db_persist = true;
}
