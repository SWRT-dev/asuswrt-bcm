/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>

#include "mmc.h"
#include "mmc_cmds.h"
#include "3rdparty/hmac_sha/hmac_sha2.h"

int read_extcsd(int fd, __u8 *ext_csd)
{
	int ret = 0;
	struct mmc_ioc_cmd idata;
	memset(&idata, 0, sizeof(idata));
	memset(ext_csd, 0, sizeof(__u8) * 512);
	idata.write_flag = 0;
	idata.opcode = MMC_SEND_EXT_CSD;
	idata.arg = 0;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blksz = 512;
	idata.blocks = 1;
	mmc_ioc_cmd_set_data(idata, ext_csd);

	ret = ioctl(fd, MMC_IOC_CMD, &idata);
	if (ret)
		perror("ioctl");

	return ret;
}

int write_extcsd_value(int fd, __u8 index, __u8 value)
{
	int ret = 0;
	struct mmc_ioc_cmd idata;

	memset(&idata, 0, sizeof(idata));
	idata.write_flag = 1;
	idata.opcode = MMC_SWITCH;
	idata.arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
			(index << 16) |
			(value << 8) |
			EXT_CSD_CMD_SET_NORMAL;
	idata.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

	ret = ioctl(fd, MMC_IOC_CMD, &idata);
	if (ret)
		perror("ioctl");

	return ret;
}

int send_status(int fd, __u32 *response)
{
	int ret = 0;
	struct mmc_ioc_cmd idata;

	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_SEND_STATUS;
	idata.arg = (1 << 16);
	idata.flags = MMC_RSP_R1 | MMC_CMD_AC;

	ret = ioctl(fd, MMC_IOC_CMD, &idata);
	if (ret)
	perror("ioctl");

	*response = idata.response[0];

	return ret;
}

void print_writeprotect_status(__u8 *ext_csd)
{
	__u8 reg;
	__u8 ext_csd_rev = ext_csd[192];

	/* A43: reserved [174:0] */
	if (ext_csd_rev >= 5) {
		printf("Boot write protection status registers"
			" [BOOT_WP_STATUS]: 0x%02x\n", ext_csd[174]);

		reg = ext_csd[EXT_CSD_BOOT_WP];
		printf("Boot Area Write protection [BOOT_WP]: 0x%02x\n", reg);
		printf(" Power ro locking: ");
		if (reg & EXT_CSD_BOOT_WP_B_PWR_WP_DIS)
			printf("not possible\n");
		else
			printf("possible\n");

		printf(" Permanent ro locking: ");
		if (reg & EXT_CSD_BOOT_WP_B_PERM_WP_DIS)
			printf("not possible\n");
		else
			printf("possible\n");

		printf(" ro lock status: ");
		if (reg & EXT_CSD_BOOT_WP_B_PWR_WP_EN)
			printf("locked until next power on\n");
		else if (reg & EXT_CSD_BOOT_WP_B_PERM_WP_EN)
			printf("locked permanently\n");
		else
			printf("not locked\n");
	}
}

int do_writeprotect_get(int nargs, char **argv)
{
	__u8 ext_csd[512];
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc writeprotect get </path/to/mmcblkX>\n",
			  exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	print_writeprotect_status(ext_csd);

	return ret;
}

int do_writeprotect_set(int nargs, char **argv)
{
	__u8 ext_csd[512], value;
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc writeprotect set </path/to/mmcblkX>\n",
			  exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	value = ext_csd[EXT_CSD_BOOT_WP] |
		EXT_CSD_BOOT_WP_B_PWR_WP_EN;
	ret = write_extcsd_value(fd, EXT_CSD_BOOT_WP, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n",
			value, EXT_CSD_BOOT_WP, device);
		exit(1);
	}

	return ret;
}

int do_disable_512B_emulation(int nargs, char **argv)
{
	__u8 ext_csd[512], native_sector_size, data_sector_size, wr_rel_param;
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc disable 512B emulation </path/to/mmcblkX>\n", exit(1));
	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	wr_rel_param = ext_csd[EXT_CSD_WR_REL_PARAM];
	native_sector_size = ext_csd[EXT_CSD_NATIVE_SECTOR_SIZE];
	data_sector_size = ext_csd[EXT_CSD_DATA_SECTOR_SIZE];

	if (native_sector_size && !data_sector_size &&
	   (wr_rel_param & EN_REL_WR)) {
		ret = write_extcsd_value(fd, EXT_CSD_USE_NATIVE_SECTOR, 1);

		if (ret) {
			fprintf(stderr, "Could not write 0x%02x to EXT_CSD[%d] in %s\n",
					1, EXT_CSD_BOOT_WP, device);
			exit(1);
		}
		printf("MMC disable 512B emulation successful.  Now reset the device to switch to 4KB native sector mode.\n");
	} else if (native_sector_size && data_sector_size) {
		printf("MMC 512B emulation mode is already disabled; doing nothing.\n");
	} else {
		printf("MMC does not support disabling 512B emulation mode.\n");
	}

	return ret;
}

int do_write_boot_en(int nargs, char **argv)
{
	__u8 ext_csd[512];
	__u8 value = 0;
	int fd, ret;
	char *device;
	int boot_area, send_ack;

	CHECK(nargs != 4, "Usage: mmc bootpart enable <partition_number> "
			  "<send_ack> </path/to/mmcblkX>\n", exit(1));

	/*
	 * If <send_ack> is 1, the device will send acknowledgment
	 * pattern "010" to the host when boot operation begins.
	 * If <send_ack> is 0, it won't.
	 */
	boot_area = strtol(argv[1], NULL, 10);
	send_ack = strtol(argv[2], NULL, 10);
	device = argv[3];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	value = ext_csd[EXT_CSD_PART_CONFIG];

	switch (boot_area) {
	case EXT_CSD_PART_CONFIG_ACC_BOOT0:
		value |= (1 << 3);
		value &= ~(3 << 4);
		break;
	case EXT_CSD_PART_CONFIG_ACC_BOOT1:
		value |= (1 << 4);
		value &= ~(1 << 3);
		value &= ~(1 << 5);
		break;
	case EXT_CSD_PART_CONFIG_ACC_USER_AREA:
		value |= (boot_area << 3);
		break;
	default:
		fprintf(stderr, "Cannot enable the boot area\n");
		exit(1);
	}
	if (send_ack)
		value |= EXT_CSD_PART_CONFIG_ACC_ACK;
	else
		value &= ~EXT_CSD_PART_CONFIG_ACC_ACK;

	ret = write_extcsd_value(fd, EXT_CSD_PART_CONFIG, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n",
			value, EXT_CSD_PART_CONFIG, device);
		exit(1);
	}
	return ret;
}

int do_write_boot_width(int nargs, char **argv)
{
	__u8 ext_csd[512];
	__u8 value = 0;
	int fd, ret;
	char *device;
	int boot_width;

	CHECK(nargs != 3, "Usage: mmc bootwidth set <boot_width> "
			  "</path/to/mmcblkX>\n", exit(1));

	/*
	 * If <send_ack> is 1, the device will send acknowledgment
	 * pattern "010" to the host when boot operation begins.
	 * If <send_ack> is 0, it won't.
	 */
	boot_width = strtol(argv[1], NULL, 10);
	device = argv[2];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	value = ext_csd[EXT_CSD_BOOT_BUS_CONDITIONS];

	switch (boot_width) {
	case 1:
		value &= ~(3);
		break;
	case 4:
		value |= (1 << 0);
		value &= ~(1 << 1);
		break;
	case 8:
		value |= (1 << 1);
		value &= ~(1 << 0);
		break;
	default:
      break;
	}

	ret = write_extcsd_value(fd, EXT_CSD_BOOT_BUS_CONDITIONS, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n",
			value, EXT_CSD_PART_CONFIG, device);
		exit(1);
	}
	return ret;
}

int do_hwreset(int value, int nargs, char **argv)
{
	__u8 ext_csd[512];
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc hwreset enable </path/to/mmcblkX>\n",
			  exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	if ((ext_csd[EXT_CSD_RST_N_FUNCTION] & EXT_CSD_RST_N_EN_MASK) ==
	    EXT_CSD_HW_RESET_EN) {
		fprintf(stderr,
			"H/W Reset is already permanently enabled on %s\n",
			device);
		exit(1);
	}
	if ((ext_csd[EXT_CSD_RST_N_FUNCTION] & EXT_CSD_RST_N_EN_MASK) ==
	    EXT_CSD_HW_RESET_DIS) {
		fprintf(stderr,
			"H/W Reset is already permanently disabled on %s\n",
			device);
		exit(1);
	}

	ret = write_extcsd_value(fd, EXT_CSD_RST_N_FUNCTION, value);
	if (ret) {
		fprintf(stderr,
			"Could not write 0x%02x to EXT_CSD[%d] in %s\n",
			value, EXT_CSD_RST_N_FUNCTION, device);
		exit(1);
	}

	return ret;
}

int do_hwreset_en(int nargs, char **argv)
{
	return do_hwreset(EXT_CSD_HW_RESET_EN, nargs, argv);
}

int do_hwreset_dis(int nargs, char **argv)
{
	return do_hwreset(EXT_CSD_HW_RESET_DIS, nargs, argv);
}

int do_write_bkops_en(int nargs, char **argv)
{
	__u8 ext_csd[512], value = 0;
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc bkops enable </path/to/mmcblkX>\n",
			exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	if (!(ext_csd[EXT_CSD_BKOPS_SUPPORT] & 0x1)) {
		fprintf(stderr, "%s doesn't support BKOPS\n", device);
		exit(1);
	}

	ret = write_extcsd_value(fd, EXT_CSD_BKOPS_EN, BKOPS_ENABLE);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to EXT_CSD[%d] in %s\n",
			value, EXT_CSD_BKOPS_EN, device);
		exit(1);
	}

	return ret;
}

int do_status_get(int nargs, char **argv)
{
	__u32 response;
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc status get </path/to/mmcblkX>\n",
		exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = send_status(fd, &response);
	if (ret) {
		fprintf(stderr, "Could not read response to SEND_STATUS from %s\n", device);
		exit(1);
	}

	printf("SEND_STATUS response: 0x%08x\n", response);

	return ret;
}

unsigned int get_sector_count(__u8 *ext_csd)
{
	return (ext_csd[EXT_CSD_SEC_COUNT_3] << 24) |
	(ext_csd[EXT_CSD_SEC_COUNT_2] << 16) |
	(ext_csd[EXT_CSD_SEC_COUNT_1] << 8)  |
	ext_csd[EXT_CSD_SEC_COUNT_0];
}

int is_blockaddresed(__u8 *ext_csd)
{
	unsigned int sectors = get_sector_count(ext_csd);

	return (sectors > (2u * 1024 * 1024 * 1024) / 512);
}

unsigned int get_hc_wp_grp_size(__u8 *ext_csd)
{
	return ext_csd[221];
}

unsigned int get_hc_erase_grp_size(__u8 *ext_csd)
{
	return ext_csd[224];
}

int set_partitioning_setting_completed(int dry_run, const char * const device,
		int fd)
{
	int ret;

	if (dry_run) {
		fprintf(stderr, "NOT setting PARTITION_SETTING_COMPLETED\n");
		fprintf(stderr, "These changes will not take effect neither "
			"now nor after a power cycle\n");
		return 1;
	}

	fprintf(stderr, "setting OTP PARTITION_SETTING_COMPLETED!\n");
	ret = write_extcsd_value(fd, EXT_CSD_PARTITION_SETTING_COMPLETED, 0x1);
	if (ret) {
		fprintf(stderr, "Could not write 0x1 to "
			"EXT_CSD[%d] in %s\n",
			EXT_CSD_PARTITION_SETTING_COMPLETED, device);
		return 1;
	}

	__u32 response;
	ret = send_status(fd, &response);
	if (ret) {
		fprintf(stderr, "Could not get response to SEND_STATUS "
			"from %s\n", device);
		return 1;
	}

	if (response & R1_SWITCH_ERROR) {
		fprintf(stderr, "Setting OTP PARTITION_SETTING_COMPLETED "
			"failed on %s\n", device);
		return 1;
	}

	fprintf(stderr, "Setting OTP PARTITION_SETTING_COMPLETED on "
		"%s SUCCESS\n", device);
	fprintf(stderr, "Device power cycle needed for settings to "
		"take effect.\n"
		"Confirm that PARTITION_SETTING_COMPLETED bit is set "
		"using 'extcsd read' after power cycle\n");

	return 0;
}

int do_enh_area_set(int nargs, char **argv)
{
	__u8 value;
	__u8 ext_csd[512];
	int fd, ret;
	char *device;
	int dry_run = 1;
	unsigned int start_kib, length_kib, enh_start_addr, enh_size_mult;
	unsigned long align;

	CHECK(nargs != 5, "Usage: mmc enh_area set <-y|-n> <start KiB> <length KiB> "
			  "</path/to/mmcblkX>\n", exit(1));

	if (!strcmp("-y", argv[1]))
		dry_run = 0;

	start_kib = strtol(argv[2], NULL, 10);
	length_kib = strtol(argv[3], NULL, 10);
	device = argv[4];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	/* assert ENH_ATTRIBUTE_EN */
	if (!(ext_csd[EXT_CSD_PARTITIONING_SUPPORT] & EXT_CSD_ENH_ATTRIBUTE_EN))
	{
		printf(" Device cannot have enhanced tech.\n");
		exit(1);
	}

	/* assert not PARTITION_SETTING_COMPLETED */
	if (ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED])
	{
		printf(" Device is already partitioned\n");
		exit(1);
	}

	align = 512l * get_hc_wp_grp_size(ext_csd) * get_hc_erase_grp_size(ext_csd);

	enh_size_mult = (length_kib + align/2l) / align;

	enh_start_addr = start_kib * 1024 / (is_blockaddresed(ext_csd) ? 512 : 1);
	enh_start_addr /= align;
	enh_start_addr *= align;

	/* set EXT_CSD_ERASE_GROUP_DEF bit 0 */
	ret = write_extcsd_value(fd, EXT_CSD_ERASE_GROUP_DEF, 0x1);
	if (ret) {
		fprintf(stderr, "Could not write 0x1 to "
			"EXT_CSD[%d] in %s\n",
			EXT_CSD_ERASE_GROUP_DEF, device);
		exit(1);
	}

	/* write to ENH_START_ADDR and ENH_SIZE_MULT and PARTITIONS_ATTRIBUTE's ENH_USR bit */
	value = (enh_start_addr >> 24) & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_START_ADDR_3, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_START_ADDR_3, device);
		exit(1);
	}
	value = (enh_start_addr >> 16) & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_START_ADDR_2, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_START_ADDR_2, device);
		exit(1);
	}
	value = (enh_start_addr >> 8) & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_START_ADDR_1, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_START_ADDR_1, device);
		exit(1);
	}
	value = enh_start_addr & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_START_ADDR_0, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_START_ADDR_0, device);
		exit(1);
	}

	value = (enh_size_mult >> 16) & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_SIZE_MULT_2, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_SIZE_MULT_2, device);
		exit(1);
	}
	value = (enh_size_mult >> 8) & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_SIZE_MULT_1, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_SIZE_MULT_1, device);
		exit(1);
	}
	value = enh_size_mult & 0xff;
	ret = write_extcsd_value(fd, EXT_CSD_ENH_SIZE_MULT_0, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to "
			"EXT_CSD[%d] in %s\n", value,
			EXT_CSD_ENH_SIZE_MULT_0, device);
		exit(1);
	}

	ret = write_extcsd_value(fd, EXT_CSD_PARTITIONS_ATTRIBUTE, EXT_CSD_ENH_USR);
	if (ret) {
		fprintf(stderr, "Could not write EXT_CSD_ENH_USR to "
			"EXT_CSD[%d] in %s\n",
			EXT_CSD_PARTITIONS_ATTRIBUTE, device);
		exit(1);
	}

	printf("Done setting ENH_USR area on %s\n", device);

	if (!set_partitioning_setting_completed(dry_run, device, fd))
		exit(1);

	return 0;
}

int do_write_reliability_set(int nargs, char **argv)
{
	__u8 value;
	__u8 ext_csd[512];
	int fd, ret;

	int dry_run = 1;
	int partition;
	char *device;

	CHECK(nargs != 4, "Usage: mmc write_reliability set <-y|-n> "
			"<partition> </path/to/mmcblkX>\n", exit(1));

	if (!strcmp("-y", argv[1]))
		dry_run = 0;

	partition = strtol(argv[2], NULL, 10);
	device = argv[3];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	/* assert not PARTITION_SETTING_COMPLETED */
	if (ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED])
	{
		printf(" Device is already partitioned\n");
		exit(1);
	}

	/* assert HS_CTRL_REL */
	if (!(ext_csd[EXT_CSD_WR_REL_PARAM] & HS_CTRL_REL)) {
		printf("Cannot set write reliability parameters, WR_REL_SET is "
				"read-only\n");
		exit(1);
	}

	value = ext_csd[EXT_CSD_WR_REL_SET] | (1<<partition);
	ret = write_extcsd_value(fd, EXT_CSD_WR_REL_SET, value);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to EXT_CSD[%d] in %s\n",
				value, EXT_CSD_WR_REL_SET, device);
		exit(1);
	}

	printf("Done setting EXT_CSD_WR_REL_SET to 0x%02x on %s\n",
		value, device);

	if (!set_partitioning_setting_completed(dry_run, device, fd))
		exit(1);

	return 0;
}

int do_read_extcsd(int nargs, char **argv)
{
	__u8 ext_csd[512], ext_csd_rev, reg;
	__u32 regl;
	int fd, ret;
	char *device;
	const char *str;

	CHECK(nargs != 2, "Usage: mmc extcsd read </path/to/mmcblkX>\n",
			  exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = read_extcsd(fd, ext_csd);
	if (ret) {
		fprintf(stderr, "Could not read EXT_CSD from %s\n", device);
		exit(1);
	}

	ext_csd_rev = ext_csd[192];

	switch (ext_csd_rev) {
	case 7:
		str = "5.0";
		break;
	case 6:
		str = "4.5";
		break;
	case 5:
		str = "4.41";
		break;
	case 3:
		str = "4.3";
		break;
	case 2:
		str = "4.2";
		break;
	case 1:
		str = "4.1";
		break;
	case 0:
		str = "4.0";
		break;
	default:
		goto out_free;
	}
	printf("=============================================\n");
	printf("  Extended CSD rev 1.%d (MMC %s)\n", ext_csd_rev, str);
	printf("=============================================\n\n");

	if (ext_csd_rev < 3)
		goto out_free; /* No ext_csd */

	/* Parse the Extended CSD registers.
	 * Reserved bit should be read as "0" in case of spec older
	 * than A441.
	 */
	reg = ext_csd[EXT_CSD_S_CMD_SET];
	printf("Card Supported Command sets [S_CMD_SET: 0x%02x]\n", reg);
	if (!reg)
		printf(" - Standard MMC command sets\n");

	reg = ext_csd[EXT_CSD_HPI_FEATURE];
	printf("HPI Features [HPI_FEATURE: 0x%02x]: ", reg);
	if (reg & EXT_CSD_HPI_SUPP) {
		if (reg & EXT_CSD_HPI_IMPL)
			printf("implementation based on CMD12\n");
		else
			printf("implementation based on CMD13\n");
	}

	printf("Background operations support [BKOPS_SUPPORT: 0x%02x]\n",
		ext_csd[502]);

	if (ext_csd_rev >= 6) {
		printf("Max Packet Read Cmd [MAX_PACKED_READS: 0x%02x]\n",
			ext_csd[501]);
		printf("Max Packet Write Cmd [MAX_PACKED_WRITES: 0x%02x]\n",
			ext_csd[500]);
		printf("Data TAG support [DATA_TAG_SUPPORT: 0x%02x]\n",
			ext_csd[499]);

		printf("Data TAG Unit Size [TAG_UNIT_SIZE: 0x%02x]\n",
			ext_csd[498]);
		printf("Tag Resources Size [TAG_RES_SIZE: 0x%02x]\n",
			ext_csd[497]);
		printf("Context Management Capabilities"
			" [CONTEXT_CAPABILITIES: 0x%02x]\n", ext_csd[496]);
		printf("Large Unit Size [LARGE_UNIT_SIZE_M1: 0x%02x]\n",
			ext_csd[495]);
		printf("Extended partition attribute support"
			" [EXT_SUPPORT: 0x%02x]\n", ext_csd[494]);
		printf("Generic CMD6 Timer [GENERIC_CMD6_TIME: 0x%02x]\n",
			ext_csd[248]);
		printf("Power off notification [POWER_OFF_LONG_TIME: 0x%02x]\n",
			ext_csd[247]);
		printf("Cache Size [CACHE_SIZE] is %d KiB\n",
			ext_csd[249] << 0 | (ext_csd[250] << 8) |
			(ext_csd[251] << 16) | (ext_csd[252] << 24));
	}

	/* A441: Reserved [501:247]
	    A43: reserved [246:229] */
	if (ext_csd_rev >= 5) {
		printf("Background operations status"
			" [BKOPS_STATUS: 0x%02x]\n", ext_csd[246]);

		/* CORRECTLY_PRG_SECTORS_NUM [245:242] TODO */

		printf("1st Initialisation Time after programmed sector"
			" [INI_TIMEOUT_AP: 0x%02x]\n", ext_csd[241]);

		/* A441: reserved [240] */
		printf("Power class for 52MHz, DDR at 3.6V"
			" [PWR_CL_DDR_52_360: 0x%02x]\n", ext_csd[239]);
		printf("Power class for 52MHz, DDR at 1.95V"
			" [PWR_CL_DDR_52_195: 0x%02x]\n", ext_csd[238]);

		/* A441: reserved [237-236] */

		if (ext_csd_rev >= 6) {
			printf("Power class for 200MHz at 3.6V"
				" [PWR_CL_200_360: 0x%02x]\n", ext_csd[237]);
			printf("Power class for 200MHz, at 1.95V"
				" [PWR_CL_200_195: 0x%02x]\n", ext_csd[236]);
		}
		printf("Minimum Performance for 8bit at 52MHz in DDR mode:\n");
		printf(" [MIN_PERF_DDR_W_8_52: 0x%02x]\n", ext_csd[235]);
		printf(" [MIN_PERF_DDR_R_8_52: 0x%02x]\n", ext_csd[234]);
		/* A441: reserved [233] */
		printf("TRIM Multiplier [TRIM_MULT: 0x%02x]\n", ext_csd[232]);
		printf("Secure Feature support [SEC_FEATURE_SUPPORT: 0x%02x]\n",
			ext_csd[231]);
	}
	if (ext_csd_rev == 5) { /* Obsolete in 4.5 */
		printf("Secure Erase Multiplier [SEC_ERASE_MULT: 0x%02x]\n",
			ext_csd[230]);
		printf("Secure TRIM Multiplier [SEC_TRIM_MULT: 0x%02x]\n",
			ext_csd[229]);
	}
	reg = ext_csd[EXT_CSD_BOOT_INFO];
	printf("Boot Information [BOOT_INFO: 0x%02x]\n", reg);
	if (reg & EXT_CSD_BOOT_INFO_ALT)
		printf(" Device supports alternative boot method\n");
	if (reg & EXT_CSD_BOOT_INFO_DDR_DDR)
		printf(" Device supports dual data rate during boot\n");
	if (reg & EXT_CSD_BOOT_INFO_HS_MODE)
		printf(" Device supports high speed timing during boot\n");

	/* A441/A43: reserved [227] */
	printf("Boot partition size [BOOT_SIZE_MULTI: 0x%02x]\n", ext_csd[226]);
	printf("Access size [ACC_SIZE: 0x%02x]\n", ext_csd[225]);

	reg = get_hc_erase_grp_size(ext_csd);
	printf("High-capacity erase unit size [HC_ERASE_GRP_SIZE: 0x%02x]\n",
		reg);
	printf(" i.e. %u KiB\n", 512 * reg);

	printf("High-capacity erase timeout [ERASE_TIMEOUT_MULT: 0x%02x]\n",
		ext_csd[223]);
	printf("Reliable write sector count [REL_WR_SEC_C: 0x%02x]\n",
		ext_csd[222]);

	reg = get_hc_wp_grp_size(ext_csd);
	printf("High-capacity W protect group size [HC_WP_GRP_SIZE: 0x%02x]\n",
		reg);
	printf(" i.e. %lu KiB\n", 512l * get_hc_erase_grp_size(ext_csd) * reg);

	printf("Sleep current (VCC) [S_C_VCC: 0x%02x]\n", ext_csd[220]);
	printf("Sleep current (VCCQ) [S_C_VCCQ: 0x%02x]\n", ext_csd[219]);
	/* A441/A43: reserved [218] */
	printf("Sleep/awake timeout [S_A_TIMEOUT: 0x%02x]\n", ext_csd[217]);
	/* A441/A43: reserved [216] */

	unsigned int sectors =	get_sector_count(ext_csd);
	printf("Sector Count [SEC_COUNT: 0x%08x]\n", sectors);
	if (is_blockaddresed(ext_csd))
		printf(" Device is block-addressed\n");
	else
		printf(" Device is NOT block-addressed\n");

	/* A441/A43: reserved [211] */
	printf("Minimum Write Performance for 8bit:\n");
	printf(" [MIN_PERF_W_8_52: 0x%02x]\n", ext_csd[210]);
	printf(" [MIN_PERF_R_8_52: 0x%02x]\n", ext_csd[209]);
	printf(" [MIN_PERF_W_8_26_4_52: 0x%02x]\n", ext_csd[208]);
	printf(" [MIN_PERF_R_8_26_4_52: 0x%02x]\n", ext_csd[207]);
	printf("Minimum Write Performance for 4bit:\n");
	printf(" [MIN_PERF_W_4_26: 0x%02x]\n", ext_csd[206]);
	printf(" [MIN_PERF_R_4_26: 0x%02x]\n", ext_csd[205]);
	/* A441/A43: reserved [204] */
	printf("Power classes registers:\n");
	printf(" [PWR_CL_26_360: 0x%02x]\n", ext_csd[203]);
	printf(" [PWR_CL_52_360: 0x%02x]\n", ext_csd[202]);
	printf(" [PWR_CL_26_195: 0x%02x]\n", ext_csd[201]);
	printf(" [PWR_CL_52_195: 0x%02x]\n", ext_csd[200]);

	/* A43: reserved [199:198] */
	if (ext_csd_rev >= 5) {
		printf("Partition switching timing "
			"[PARTITION_SWITCH_TIME: 0x%02x]\n", ext_csd[199]);
		printf("Out-of-interrupt busy timing"
			" [OUT_OF_INTERRUPT_TIME: 0x%02x]\n", ext_csd[198]);
	}

	/* A441/A43: reserved	[197] [195] [193] [190] [188]
	 * [186] [184] [182] [180] [176] */

	if (ext_csd_rev >= 6)
		printf("I/O Driver Strength [DRIVER_STRENGTH: 0x%02x]\n",
			ext_csd[197]);

	/* DEVICE_TYPE in A45, CARD_TYPE in A441 */
	reg = ext_csd[196];
	printf("Card Type [CARD_TYPE: 0x%02x]\n", reg);
	if (reg & 0x20) printf(" HS200 Single Data Rate eMMC @200MHz 1.2VI/O\n");
	if (reg & 0x10) printf(" HS200 Single Data Rate eMMC @200MHz 1.8VI/O\n");
	if (reg & 0x08) printf(" HS Dual Data Rate eMMC @52MHz 1.2VI/O\n");
	if (reg & 0x04)	printf(" HS Dual Data Rate eMMC @52MHz 1.8V or 3VI/O\n");
	if (reg & 0x02)	printf(" HS eMMC @52MHz - at rated device voltage(s)\n");
	if (reg & 0x01) printf(" HS eMMC @26MHz - at rated device voltage(s)\n");

	printf("CSD structure version [CSD_STRUCTURE: 0x%02x]\n", ext_csd[194]);
	/* ext_csd_rev = ext_csd[192] (already done!!!) */
	printf("Command set [CMD_SET: 0x%02x]\n", ext_csd[191]);
	printf("Command set revision [CMD_SET_REV: 0x%02x]\n", ext_csd[189]);
	printf("Power class [POWER_CLASS: 0x%02x]\n", ext_csd[187]);
	printf("High-speed interface timing [HS_TIMING: 0x%02x]\n",
		ext_csd[185]);
	/* bus_width: ext_csd[183] not readable */
	printf("Erased memory content [ERASED_MEM_CONT: 0x%02x]\n",
		ext_csd[181]);
	reg = ext_csd[EXT_CSD_BOOT_CFG];
	printf("Boot configuration bytes [PARTITION_CONFIG: 0x%02x]\n", reg);
	switch ((reg & EXT_CSD_BOOT_CFG_EN)>>3) {
	case 0x0:
		printf(" Not boot enable\n");
		break;
	case 0x1:
		printf(" Boot Partition 1 enabled\n");
		break;
	case 0x2:
		printf(" Boot Partition 2 enabled\n");
		break;
	case 0x7:
		printf(" User Area Enabled for boot\n");
		break;
	}
	switch (reg & EXT_CSD_BOOT_CFG_ACC) {
	case 0x0:
		printf(" No access to boot partition\n");
		break;
	case 0x1:
		printf(" R/W Boot Partition 1\n");
		break;
	case 0x2:
		printf(" R/W Boot Partition 2\n");
		break;
	case 0x3:
		printf(" R/W Replay Protected Memory Block (RPMB)\n");
		break;
	default:
		printf(" Access to General Purpose partition %d\n",
			(reg & EXT_CSD_BOOT_CFG_ACC) - 3);
		break;
	}

	printf("Boot config protection [BOOT_CONFIG_PROT: 0x%02x]\n",
		ext_csd[178]);
	printf("Boot bus Conditions [BOOT_BUS_CONDITIONS: 0x%02x]\n",
		ext_csd[177]);
	printf("High-density erase group definition"
		" [ERASE_GROUP_DEF: 0x%02x]\n", ext_csd[EXT_CSD_ERASE_GROUP_DEF]);

	print_writeprotect_status(ext_csd);

	if (ext_csd_rev >= 5) {
		/* A441]: reserved [172] */
		printf("User area write protection register"
			" [USER_WP]: 0x%02x\n", ext_csd[171]);
		/* A441]: reserved [170] */
		printf("FW configuration [FW_CONFIG]: 0x%02x\n", ext_csd[169]);
		printf("RPMB Size [RPMB_SIZE_MULT]: 0x%02x\n", ext_csd[168]);

		reg = ext_csd[EXT_CSD_WR_REL_SET];
		const char * const fast = "existing data is at risk if a power "
				"failure occurs during a write operation";
		const char * const reliable = "the device protects existing "
				"data if a power failure occurs during a write "
				"operation";
		printf("Write reliability setting register"
			" [WR_REL_SET]: 0x%02x\n", reg);

		printf(" user area: %s\n", reg & (1<<0) ? reliable : fast);
		int i;
		for (i = 1; i <= 4; i++) {
			printf(" partition %d: %s\n", i,
				reg & (1<<i) ? reliable : fast);
		}

		reg = ext_csd[EXT_CSD_WR_REL_PARAM];
		printf("Write reliability parameter register"
			" [WR_REL_PARAM]: 0x%02x\n", reg);
		if (reg & 0x01)
			printf(" Device supports writing EXT_CSD_WR_REL_SET\n");
		if (reg & 0x04)
			printf(" Device supports the enhanced def. of reliable "
				"write\n");

		/* sanitize_start ext_csd[165]]: not readable
		 * bkops_start ext_csd[164]]: only writable */
		printf("Enable background operations handshake"
			" [BKOPS_EN]: 0x%02x\n", ext_csd[163]);
		printf("H/W reset function"
			" [RST_N_FUNCTION]: 0x%02x\n", ext_csd[162]);
		printf("HPI management [HPI_MGMT]: 0x%02x\n", ext_csd[161]);
		reg = ext_csd[EXT_CSD_PARTITIONING_SUPPORT];
		printf("Partitioning Support [PARTITIONING_SUPPORT]: 0x%02x\n",
			reg);
		if (reg & EXT_CSD_PARTITIONING_EN)
			printf(" Device support partitioning feature\n");
		else
			printf(" Device NOT support partitioning feature\n");
		if (reg & EXT_CSD_ENH_ATTRIBUTE_EN)
			printf(" Device can have enhanced tech.\n");
		else
			printf(" Device cannot have enhanced tech.\n");

		regl = (ext_csd[EXT_CSD_MAX_ENH_SIZE_MULT_2] << 16) |
			(ext_csd[EXT_CSD_MAX_ENH_SIZE_MULT_1] << 8) |
			ext_csd[EXT_CSD_MAX_ENH_SIZE_MULT_0];

		printf("Max Enhanced Area Size [MAX_ENH_SIZE_MULT]: 0x%06x\n",
			   regl);
		unsigned int wp_sz = get_hc_wp_grp_size(ext_csd);
		unsigned int erase_sz = get_hc_erase_grp_size(ext_csd);
		printf(" i.e. %lu KiB\n", 512l * regl * wp_sz * erase_sz);

		printf("Partitions attribute [PARTITIONS_ATTRIBUTE]: 0x%02x\n",
			ext_csd[EXT_CSD_PARTITIONS_ATTRIBUTE]);
		reg = ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED];
		printf("Partitioning Setting"
			" [PARTITION_SETTING_COMPLETED]: 0x%02x\n",
			reg);
		if (reg)
			printf(" Device partition setting complete\n");
		else
			printf(" Device partition setting NOT complete\n");

		printf("General Purpose Partition Size\n"
			" [GP_SIZE_MULT_4]: 0x%06x\n", (ext_csd[154] << 16) |
			(ext_csd[153] << 8) | ext_csd[152]);
		printf(" [GP_SIZE_MULT_3]: 0x%06x\n", (ext_csd[151] << 16) |
			   (ext_csd[150] << 8) | ext_csd[149]);
		printf(" [GP_SIZE_MULT_2]: 0x%06x\n", (ext_csd[148] << 16) |
			   (ext_csd[147] << 8) | ext_csd[146]);
		printf(" [GP_SIZE_MULT_1]: 0x%06x\n", (ext_csd[145] << 16) |
			   (ext_csd[144] << 8) | ext_csd[143]);

		regl =	(ext_csd[EXT_CSD_ENH_SIZE_MULT_2] << 16) |
			(ext_csd[EXT_CSD_ENH_SIZE_MULT_1] << 8) |
			ext_csd[EXT_CSD_ENH_SIZE_MULT_0];
		printf("Enhanced User Data Area Size"
			" [ENH_SIZE_MULT]: 0x%06x\n", regl);
		printf(" i.e. %lu KiB\n", 512l * regl *
		       get_hc_erase_grp_size(ext_csd) *
		       get_hc_wp_grp_size(ext_csd));

		regl =	(ext_csd[EXT_CSD_ENH_START_ADDR_3] << 24) |
			(ext_csd[EXT_CSD_ENH_START_ADDR_2] << 16) |
			(ext_csd[EXT_CSD_ENH_START_ADDR_1] << 8) |
			ext_csd[EXT_CSD_ENH_START_ADDR_0];
		printf("Enhanced User Data Start Address"
			" [ENH_START_ADDR]: 0x%06x\n", regl);
		printf(" i.e. %lu bytes offset\n", (is_blockaddresed(ext_csd) ?
				1l : 512l) * regl);

		/* A441]: reserved [135] */
		printf("Bad Block Management mode"
			" [SEC_BAD_BLK_MGMNT]: 0x%02x\n", ext_csd[134]);
		/* A441: reserved [133:0] */
	}
	/* B45 */
	if (ext_csd_rev >= 6) {
		int j;
		/* tcase_support ext_csd[132] not readable */
		printf("Periodic Wake-up [PERIODIC_WAKEUP]: 0x%02x\n",
			ext_csd[131]);
		printf("Program CID/CSD in DDR mode support"
			" [PROGRAM_CID_CSD_DDR_SUPPORT]: 0x%02x\n",
			   ext_csd[130]);

		for (j = 127; j >= 64; j--)
			printf("Vendor Specific Fields"
				" [VENDOR_SPECIFIC_FIELD[%d]]: 0x%02x\n",
				j, ext_csd[j]);

		printf("Native sector size [NATIVE_SECTOR_SIZE]: 0x%02x\n",
			ext_csd[63]);
		printf("Sector size emulation [USE_NATIVE_SECTOR]: 0x%02x\n",
			ext_csd[62]);
		printf("Sector size [DATA_SECTOR_SIZE]: 0x%02x\n", ext_csd[61]);
		printf("1st initialization after disabling sector"
			" size emulation [INI_TIMEOUT_EMU]: 0x%02x\n",
			ext_csd[60]);
		printf("Class 6 commands control [CLASS_6_CTRL]: 0x%02x\n",
			ext_csd[59]);
		printf("Number of addressed group to be Released"
			"[DYNCAP_NEEDED]: 0x%02x\n", ext_csd[58]);
		printf("Exception events control"
			" [EXCEPTION_EVENTS_CTRL]: 0x%04x\n",
			(ext_csd[57] << 8) | ext_csd[56]);
		printf("Exception events status"
			"[EXCEPTION_EVENTS_STATUS]: 0x%04x\n",
			(ext_csd[55] << 8) | ext_csd[54]);
		printf("Extended Partitions Attribute"
			" [EXT_PARTITIONS_ATTRIBUTE]: 0x%04x\n",
			(ext_csd[53] << 8) | ext_csd[52]);

		for (j = 51; j >= 37; j--)
			printf("Context configuration"
				" [CONTEXT_CONF[%d]]: 0x%02x\n", j, ext_csd[j]);

		printf("Packed command status"
			" [PACKED_COMMAND_STATUS]: 0x%02x\n", ext_csd[36]);
		printf("Packed command failure index"
			" [PACKED_FAILURE_INDEX]: 0x%02x\n", ext_csd[35]);
		printf("Power Off Notification"
			" [POWER_OFF_NOTIFICATION]: 0x%02x\n", ext_csd[34]);
		printf("Control to turn the Cache ON/OFF"
			" [CACHE_CTRL]: 0x%02x\n", ext_csd[33]);
		/* flush_cache ext_csd[32] not readable */
		/*Reserved [31:0] */
	}

out_free:
	return ret;
}

int do_sanitize(int nargs, char **argv)
{
	int fd, ret;
	char *device;

	CHECK(nargs != 2, "Usage: mmc sanitize </path/to/mmcblkX>\n",
			exit(1));

	device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	ret = write_extcsd_value(fd, EXT_CSD_SANITIZE_START, 1);
	if (ret) {
		fprintf(stderr, "Could not write 0x%02x to EXT_CSD[%d] in %s\n",
			1, EXT_CSD_SANITIZE_START, device);
		exit(1);
	}

	return ret;

}

#define DO_IO(func, fd, buf, nbyte)					\
	({												\
		ssize_t ret = 0, r;							\
		do {										\
			r = func(fd, buf + ret, nbyte - ret);	\
			if (r < 0 && errno != EINTR) {			\
				ret = -1;							\
				break;								\
			}										\
			else if (r > 0)							\
				ret += r;							\
		} while (r != 0 && (size_t)ret != nbyte);	\
													\
		ret;										\
	})

enum rpmb_op_type {
	MMC_RPMB_WRITE_KEY = 0x01,
	MMC_RPMB_READ_CNT  = 0x02,
	MMC_RPMB_WRITE     = 0x03,
	MMC_RPMB_READ      = 0x04,

	/* For internal usage only, do not use it directly */
	MMC_RPMB_READ_RESP = 0x05
};

struct rpmb_frame {
	u_int8_t  stuff[196];
	u_int8_t  key_mac[32];
	u_int8_t  data[256];
	u_int8_t  nonce[16];
	u_int32_t write_counter;
	u_int16_t addr;
	u_int16_t block_count;
	u_int16_t result;
	u_int16_t req_resp;
};

/* Performs RPMB operation.
 *
 * @fd: RPMB device on which we should perform ioctl command
 * @frame_in: input RPMB frame, should be properly inited
 * @frame_out: output (result) RPMB frame. Caller is responsible for checking
 *             result and req_resp for output frame.
 * @out_cnt: count of outer frames. Used only for multiple blocks reading,
 *           in the other cases -EINVAL will be returned.
 */
static int do_rpmb_op(int fd,
					  const struct rpmb_frame *frame_in,
					  struct rpmb_frame *frame_out,
					  unsigned int out_cnt)
{
	int err;
	u_int16_t rpmb_type;

	struct mmc_ioc_cmd ioc = {
		.arg        = 0x0,
		.blksz      = 512,
		.blocks     = 1,
		.write_flag = 1,
		.opcode     = MMC_WRITE_MULTIPLE_BLOCK,
		.flags      = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC,
		.data_ptr   = (uintptr_t)frame_in
	};

	if (!frame_in || !frame_out || !out_cnt)
		return -EINVAL;

	rpmb_type = be16toh(frame_in->req_resp);

	switch(rpmb_type) {
	case MMC_RPMB_WRITE:
	case MMC_RPMB_WRITE_KEY:
		if (out_cnt != 1) {
			err = -EINVAL;
			goto out;
		}

		/* Write request */
		ioc.write_flag |= (1<<31);
		err = ioctl(fd, MMC_IOC_CMD, &ioc);
		if (err < 0) {
			err = -errno;
			goto out;
		}

		/* Result request */
		memset(frame_out, 0, sizeof(*frame_out));
		frame_out->req_resp = htobe16(MMC_RPMB_READ_RESP);
		ioc.write_flag = 1;
		ioc.data_ptr = (uintptr_t)frame_out;
		err = ioctl(fd, MMC_IOC_CMD, &ioc);
		if (err < 0) {
			err = -errno;
			goto out;
		}

		/* Get response */
		ioc.write_flag = 0;
		ioc.opcode = MMC_READ_MULTIPLE_BLOCK;
		err = ioctl(fd, MMC_IOC_CMD, &ioc);
		if (err < 0) {
			err = -errno;
			goto out;
		}

		break;
	case MMC_RPMB_READ_CNT:
		if (out_cnt != 1) {
			err = -EINVAL;
			goto out;
		}
		/* fall through */

	case MMC_RPMB_READ:
		/* Request */
		err = ioctl(fd, MMC_IOC_CMD, &ioc);
		if (err < 0) {
			err = -errno;
			goto out;
		}

		/* Get response */
		ioc.write_flag = 0;
		ioc.opcode   = MMC_READ_MULTIPLE_BLOCK;
		ioc.blocks   = out_cnt;
		ioc.data_ptr = (uintptr_t)frame_out;
		err = ioctl(fd, MMC_IOC_CMD, &ioc);
		if (err < 0) {
			err = -errno;
			goto out;
		}

		break;
	default:
		err = -EINVAL;
		goto out;
	}

out:
	return err;
}

int do_rpmb_write_key(int nargs, char **argv)
{
	int ret, dev_fd, key_fd;
	struct rpmb_frame frame_in = {
		.req_resp = htobe16(MMC_RPMB_WRITE_KEY)
	}, frame_out;

	CHECK(nargs != 3, "Usage: mmc rpmb write-key </path/to/mmcblkXrpmb> </path/to/key>\n",
			exit(1));

	dev_fd = open(argv[1], O_RDWR);
	if (dev_fd < 0) {
		perror("device open");
		exit(1);
	}

	if (0 == strcmp(argv[2], "-"))
		key_fd = STDIN_FILENO;
	else {
		key_fd = open(argv[2], O_RDONLY);
		if (key_fd < 0) {
			perror("can't open key file");
			exit(1);
		}
	}

	/* Read the auth key */
	ret = DO_IO(read, key_fd, frame_in.key_mac, sizeof(frame_in.key_mac));
	if (ret < 0) {
		perror("read the key");
		exit(1);
	} else if (ret != sizeof(frame_in.key_mac)) {
		printf("Auth key must be %lu bytes length, but we read only %d, exit\n",
			   (unsigned long)sizeof(frame_in.key_mac),
			   ret);
		exit(1);
	}

	/* Execute RPMB op */
	ret = do_rpmb_op(dev_fd, &frame_in, &frame_out, 1);
	if (ret != 0) {
		perror("RPMB ioctl failed");
		exit(1);
	}

	/* Check RPMB response */
	if (frame_out.result != 0) {
		printf("RPMB operation failed, retcode 0x%04x\n",
			   be16toh(frame_out.result));
		exit(1);
	}

	close(dev_fd);
	if (key_fd != STDIN_FILENO)
		close(key_fd);

	return ret;
}

int rpmb_read_counter(int dev_fd, unsigned int *cnt)
{
	int ret;
	struct rpmb_frame frame_in = {
		.req_resp = htobe16(MMC_RPMB_READ_CNT)
	}, frame_out;

	/* Execute RPMB op */
	ret = do_rpmb_op(dev_fd, &frame_in, &frame_out, 1);
	if (ret != 0) {
		perror("RPMB ioctl failed");
		exit(1);
	}

	/* Check RPMB response */
	if (frame_out.result != 0)
		return be16toh(frame_out.result);

	*cnt = be32toh(frame_out.write_counter);

	return 0;
}

int do_rpmb_read_counter(int nargs, char **argv)
{
	int ret, dev_fd;
	unsigned int cnt;

	CHECK(nargs != 2, "Usage: mmc rpmb read-counter </path/to/mmcblkXrpmb>\n",
			exit(1));

	dev_fd = open(argv[1], O_RDWR);
	if (dev_fd < 0) {
		perror("device open");
		exit(1);
	}

	ret = rpmb_read_counter(dev_fd, &cnt);

	/* Check RPMB response */
	if (ret != 0) {
		printf("RPMB operation failed, retcode 0x%04x\n", ret);
		exit(1);
	}

	close(dev_fd);

	printf("Counter value: 0x%08x\n", cnt);

	return ret;
}

int do_rpmb_read_block(int nargs, char **argv)
{
	int i, ret, dev_fd, data_fd, key_fd = -1;
	uint16_t addr, blocks_cnt;
	unsigned char key[32];
	struct rpmb_frame frame_in = {
		.req_resp    = htobe16(MMC_RPMB_READ),
	}, *frame_out_p;

	CHECK(nargs != 5 && nargs != 6, "Usage: mmc rpmb read-block </path/to/mmcblkXrpmb> <address> <blocks count> </path/to/output_file> [/path/to/key]\n",
			exit(1));

	dev_fd = open(argv[1], O_RDWR);
	if (dev_fd < 0) {
		perror("device open");
		exit(1);
	}

	/* Get block address */
	errno = 0;
	addr = strtol(argv[2], NULL, 0);
	if (errno) {
		perror("incorrect address");
		exit(1);
	}
	frame_in.addr = htobe16(addr);

	/* Get blocks count */
	errno = 0;
	blocks_cnt = strtol(argv[3], NULL, 0);
	if (errno) {
		perror("incorrect blocks count");
		exit(1);
	}

	if (!blocks_cnt) {
		printf("please, specify valid blocks count number\n");
		exit(1);
	}

	frame_out_p = calloc(sizeof(*frame_out_p), blocks_cnt);
	if (!frame_out_p) {
		printf("can't allocate memory for RPMB outer frames\n");
		exit(1);
	}

	/* Write 256b data */
	if (0 == strcmp(argv[4], "-"))
		data_fd = STDOUT_FILENO;
	else {
		data_fd = open(argv[4], O_WRONLY | O_CREAT | O_APPEND,
					   S_IRUSR | S_IWUSR);
		if (data_fd < 0) {
			perror("can't open output file");
			exit(1);
		}
	}

	/* Key is specified */
	if (nargs == 6) {
		if (0 == strcmp(argv[5], "-"))
			key_fd = STDIN_FILENO;
		else {
			key_fd = open(argv[5], O_RDONLY);
			if (key_fd < 0) {
				perror("can't open input key file");
				exit(1);
			}
		}

		ret = DO_IO(read, key_fd, key, sizeof(key));
		if (ret < 0) {
			perror("read the key data");
			exit(1);
		} else if (ret != sizeof(key)) {
			printf("Data must be %lu bytes length, but we read only %d, exit\n",
				   (unsigned long)sizeof(key),
				   ret);
			exit(1);
		}
	}

	/* Execute RPMB op */
	ret = do_rpmb_op(dev_fd, &frame_in, frame_out_p, blocks_cnt);
	if (ret != 0) {
		perror("RPMB ioctl failed");
		exit(1);
	}

	/* Check RPMB response */
	if (frame_out_p[blocks_cnt - 1].result != 0) {
		printf("RPMB operation failed, retcode 0x%04x\n",
			   be16toh(frame_out_p[blocks_cnt - 1].result));
		exit(1);
	}

	/* Do we have to verify data against key? */
	if (nargs == 6) {
		unsigned char mac[32];
		hmac_sha256_ctx ctx;
		struct rpmb_frame *frame_out = NULL;

		hmac_sha256_init(&ctx, key, sizeof(key));
		for (i = 0; i < blocks_cnt; i++) {
			frame_out = &frame_out_p[i];
			hmac_sha256_update(&ctx, frame_out->data,
							   sizeof(*frame_out) -
								   offsetof(struct rpmb_frame, data));
		}

		hmac_sha256_final(&ctx, mac, sizeof(mac));

		/* Impossible */
		assert(frame_out);

		/* Compare calculated MAC and MAC from last frame */
		if (memcmp(mac, frame_out->key_mac, sizeof(mac))) {
			printf("RPMB MAC missmatch\n");
			exit(1);
		}
	}

	/* Write data */
	for (i = 0; i < blocks_cnt; i++) {
		struct rpmb_frame *frame_out = &frame_out_p[i];
		ret = DO_IO(write, data_fd, frame_out->data, sizeof(frame_out->data));
		if (ret < 0) {
			perror("write the data");
			exit(1);
		} else if (ret != sizeof(frame_out->data)) {
			printf("Data must be %lu bytes length, but we wrote only %d, exit\n",
				   (unsigned long)sizeof(frame_out->data),
				   ret);
			exit(1);
		}
	}

	free(frame_out_p);
	close(dev_fd);
	if (data_fd != STDOUT_FILENO)
		close(data_fd);
	if (key_fd != -1 && key_fd != STDIN_FILENO)
		close(key_fd);

	return ret;
}

int do_rpmb_write_block(int nargs, char **argv)
{
	int ret, dev_fd, key_fd, data_fd;
	unsigned char key[32];
	uint16_t addr;
	unsigned int cnt;
	struct rpmb_frame frame_in = {
		.req_resp    = htobe16(MMC_RPMB_WRITE),
		.block_count = htobe16(1)
	}, frame_out;

	CHECK(nargs != 5, "Usage: mmc rpmb write-block </path/to/mmcblkXrpmb> <address> </path/to/input_file> </path/to/key>\n",
			exit(1));

	dev_fd = open(argv[1], O_RDWR);
	if (dev_fd < 0) {
		perror("device open");
		exit(1);
	}

	ret = rpmb_read_counter(dev_fd, &cnt);
	/* Check RPMB response */
	if (ret != 0) {
		printf("RPMB read counter operation failed, retcode 0x%04x\n", ret);
		exit(1);
	}
	frame_in.write_counter = htobe32(cnt);

	/* Get block address */
	errno = 0;
	addr = strtol(argv[2], NULL, 0);
	if (errno) {
		perror("incorrect address");
		exit(1);
	}
	frame_in.addr = htobe16(addr);

	/* Read 256b data */
	if (0 == strcmp(argv[3], "-"))
		data_fd = STDIN_FILENO;
	else {
		data_fd = open(argv[3], O_RDONLY);
		if (data_fd < 0) {
			perror("can't open input file");
			exit(1);
		}
	}

	ret = DO_IO(read, data_fd, frame_in.data, sizeof(frame_in.data));
	if (ret < 0) {
		perror("read the data");
		exit(1);
	} else if (ret != sizeof(frame_in.data)) {
		printf("Data must be %lu bytes length, but we read only %d, exit\n",
			   (unsigned long)sizeof(frame_in.data),
			   ret);
		exit(1);
	}

	/* Read the auth key */
	if (0 == strcmp(argv[4], "-"))
		key_fd = STDIN_FILENO;
	else {
		key_fd = open(argv[4], O_RDONLY);
		if (key_fd < 0) {
			perror("can't open key file");
			exit(1);
		}
	}

	ret = DO_IO(read, key_fd, key, sizeof(key));
	if (ret < 0) {
		perror("read the key");
		exit(1);
	} else if (ret != sizeof(key)) {
		printf("Auth key must be %lu bytes length, but we read only %d, exit\n",
			   (unsigned long)sizeof(key),
			   ret);
		exit(1);
	}

	/* Calculate HMAC SHA256 */
	hmac_sha256(
		key, sizeof(key),
		frame_in.data, sizeof(frame_in) - offsetof(struct rpmb_frame, data),
		frame_in.key_mac, sizeof(frame_in.key_mac));

	/* Execute RPMB op */
	ret = do_rpmb_op(dev_fd, &frame_in, &frame_out, 1);
	if (ret != 0) {
		perror("RPMB ioctl failed");
		exit(1);
	}

	/* Check RPMB response */
	if (frame_out.result != 0) {
		printf("RPMB operation failed, retcode 0x%04x\n",
			   be16toh(frame_out.result));
		exit(1);
	}

	close(dev_fd);
	if (data_fd != STDIN_FILENO)
		close(data_fd);
	if (key_fd != STDIN_FILENO)
		close(key_fd);

	return ret;
}
