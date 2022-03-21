#if defined(CONFIG_BCM_KF_MTD_BCMNAND)
/*
 *
 *  drivers/mtd/bcmspinand/bcm63xx-spinand.c
 *
    <:copyright-BRCM:2011:DUAL/GPL:standard
    
       Copyright (c) 2011 Broadcom 
       All Rights Reserved
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
    :> 


    File: bcm63xx-spinand.c

    Description: 
    This is a device driver for the Broadcom SPINAND flash for bcm63xxx boards.

 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <asm/io.h>
#include <linux/slab.h> 
#include <linux/version.h>
#include <generated/autoconf.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <flash_api.h>

#include <spinandflash.c>

//#undef DEBUG_NAND
//#define DEBUG_NAND
#if defined(DEBUG_NAND)
#define DBG_PRINTF printk
#else
#define DBG_PRINTF(...)
#endif


#define STATUS_DEFAULT NAND_STATUS_TRUE_READY|NAND_STATUS_READY|NAND_STATUS_WP

// device information bytes required to identify device for SPI NAND
#define SPI_NAND_ID_LENGTH  2

// device information bytes required to identify device for Linux NAND
#define NAND_ID_LENGTH  4

#define SPI_CONTROLLER_STATE_SET             (1 << 31)
#define SPI_CONTROLLER_STATE_CPHA_EXT        (1 << 30)
#define SPI_CONTROLLER_STATE_GATE_CLK_SSOFF  (1 << 29)
#define SPI_CONTROLLER_STATE_ASYNC_CLOCK     (1 << 28)

#define SPI_CONTROLLER_MAX_SYNC_CLOCK 30000000

/* set mode and controller state based on CHIP defaults
   these values do not apply to the legacy controller
   legacy controller uses SPI_MODE_3 and clock is not
   gated */

#define SPI_MODE_DEFAULT              SPI_MODE_0
#define SPI_CONTROLLER_STATE_DEFAULT  (SPI_CONTROLLER_STATE_GATE_CLK_SSOFF)


static unsigned int spi_max_op_len = SPI_BUF_LEN;

spinlock_t chip_lock;

struct SpiNandChip
{
    unsigned char *chip_name;
    unsigned char chip_device_id[SPI_NAND_ID_LENGTH];
    unsigned long chip_total_size;
    unsigned int chip_num_blocks;
    unsigned int chip_block_size;
    unsigned int chip_page_size;
    unsigned int chip_spare_size;
    unsigned int chip_ecc_offset;
    struct nand_ecclayout *ecclayout;
    unsigned short chip_block_shift;
    unsigned short chip_page_shift;
    unsigned short chip_num_planes;
    unsigned char chip_ecc_corr; // threshold to fix correctable bits
    unsigned char chip_ecc_enh; // enhanced bad bit detection by chip
    unsigned char chip_subpage_shift; // 2^ shift amount based on number of subpages, typically 4
};

static struct SpiNandChip * pchip;


static struct SpiNandChip SpiDevInfo[] =
{
    {
        .chip_name = "GigaDevice GD5F1GQ4UA",
        .chip_device_id = {GIGADEVPART, ID_GD5F1GQ4UA},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x840,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_gigadevice_2k_A,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "GigaDevice GD5F2GQ4UA",
        .chip_device_id = {GIGADEVPART, ID_GD5F2GQ4UA},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x840,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_gigadevice_2k_A,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "GigaDevice GD5F1GQ4UB",
        .chip_device_id = {GIGADEVPART, ID_GD5F1GQ4UB},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x840,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_gigadevice_2k_B,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0x10, // enhanced bad bit detection by chip (6/8)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "GigaDevice GD5F2GQ4UB",
        .chip_device_id = {GIGADEVPART, ID_GD5F2GQ4UB},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x840,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_gigadevice_2k_B,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0x10, // enhanced bad bit detection by chip (6/8)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "GigaDevice GD5F4GQ4UB",
        .chip_device_id = {GIGADEVPART, ID_GD5F4GQ4UB},
        .chip_page_size = 4096,
        .chip_page_shift = 12,
        .chip_block_size = 64 * 4096,   // 64 pages per block x chip_page_size
        .chip_block_shift = 18,
        .chip_spare_size = 256,
        .chip_ecc_offset = 0x1080,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 4096 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_gigadevice_4k,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0x10, // enhanced bad bit detection by chip (6/8)
        .chip_subpage_shift = 3, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Micron MT29F1G01AA",
        .chip_device_id = {MICRONPART, ID_MT29F1G01AA},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_micron_aa,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Micron MT29F2G01AA",
        .chip_device_id = {MICRONPART, ID_MT29F2G01AA},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 2,
        .chip_total_size = 64 * 2048 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_micron_aa,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Micron MT29F4G01AA",
        .chip_device_id = {MICRONPART, ID_MT29F4G01AA},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 4096,    // 4096 blocks total
        .chip_num_planes = 2,
        .chip_total_size = 64 * 2048 * 4096, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_micron_aa,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Micron MT29F2G01AB",
        .chip_device_id = {MICRONPART, ID_MT29F2G01AB},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 2,
        .chip_total_size = 64 * 2048 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_toshiba_micron_ab,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "ESMT F50L1G41A",
        .chip_device_id = {ESMTPART, ID_F50L1G41A},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_esmt,
        .chip_ecc_corr = 1, // threshold to fix correctable bits (1/1)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Winbond W25N01GV",
        .chip_device_id = {WINBONDPART, ID_W25N01GV},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_micron_aa,
        .chip_ecc_corr = 1, // threshold to fix correctable bits (1/1)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Macronix MX35LF1G",
        .chip_device_id = {MACRONIXPART, ID_MX35LF1G},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_mxic,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 3, // enhanced bad bit detection by chip
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Macronix MX35LF2G",
        .chip_device_id = {MACRONIXPART, ID_MX35LF2G},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 2048,    // 2048 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 2048, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_mxic,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 3, // enhanced bad bit detection by chip
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Toshiba TC58VG0S",
        .chip_device_id = {TOSHIBAPART, ID_TC58VG0S},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_toshiba_micron_ab,
        .chip_ecc_corr = 6, // threshold to fix correctable bits (6/8)
        .chip_ecc_enh = 0x60, // enhanced bad bit detection by chip
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "Etron EM73C044",
        .chip_device_id = {ETRONPART, ID_EM73C044},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 128,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_etron,
        .chip_ecc_corr = 3, // threshold to fix correctable bits (3/4)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    },
    {
        .chip_name = "default",
        .chip_device_id = {0, 0},
        .chip_page_size = 2048,
        .chip_page_shift = 11,
        .chip_block_size = 64 * 2048,   // 64 pages per block x chip_page_size
        .chip_block_shift = 17,
        .chip_spare_size = 64,
        .chip_ecc_offset = 0x800,   // location of ECC bytes
        .chip_num_blocks = 1024,    // 1024 blocks total
        .chip_num_planes = 1,
        .chip_total_size = 64 * 2048 * 1024, // chip_block_size x chip_num_blocks
        .ecclayout = &spinand_oob_micron_aa,
        .chip_ecc_corr = 1, // threshold to fix correctable bits (1/?)
        .chip_ecc_enh = 0, // enhanced bad bit detection by chip (none)
        .chip_subpage_shift = 2, // 2^ shift amount based on number of subpages (4)
    }
};


static struct spi_device * pSpiDevice; // handle for SPI NAND device

static unsigned char * pageBuf;
static unsigned int pageBufI;
static int pageAddr, pageOffset;
static int status = STATUS_DEFAULT;
static bool SpiNandDeviceRegistered = 0;

/** Prototypes. **/
static int spi_nand_read_page(unsigned long page_addr, unsigned int page_offset, unsigned char *buffer, int len);
static int spi_nand_write_page(unsigned long page_addr, unsigned int page_offset, unsigned char *buffer, int len);
static int spi_nand_is_blk_bad(unsigned long addr);
static int spi_nand_mark_blk_bad(unsigned long addr);
static int spi_nand_write_enable(void);
static int spi_nand_write_disable(void);
static void spi_nand_row_addr(unsigned int page_addr, unsigned char* buf);
static void spi_nand_col_addr(unsigned int page_addr, unsigned int page_offset, unsigned char* buf);
static void spi_nand_get_device_id(unsigned char * buf, unsigned int len);
static int spi_nand_wel(void);

static int spiRead( struct spi_transfer *xfer );
static int spiWrite( unsigned char *msg_buf, int nbytes );
static void spi_nand_read_cfg(void);

static int spi_nand_device_reset(void);
static int spi_nand_status(void);
static int spi_nand_ready(void);
static int spi_nand_ecc(void);
static int spi_nand_sector_erase_int(unsigned long addr);

static int spi_nand_get_cmd(unsigned char command, unsigned char feat_addr);
static void spi_nand_set_feat(unsigned char feat_addr, unsigned char feat_val);

static void bcm63xx_cmd(struct mtd_info *mtd, unsigned int command, int column, int page);
static unsigned char bcm63xx_read_byte(struct mtd_info *mtd);
static void bcm63xx_read_buf(struct mtd_info *mtd, uint8_t *buf, int len);
static void bcm63xx_write(struct mtd_info *mtd, const uint8_t *buf, int len);
static int bcm63xx_status(struct mtd_info *mtd, struct nand_chip *chip);
static int bcm63xx_block_isbad(struct mtd_info *mtd, loff_t ofs, int getchip);
static int bcm63xx_block_markbad(struct mtd_info *mtd, loff_t ofs);
static void bcm63xx_select(struct mtd_info *mtd, int chip);
static int bcm63xx_scan_bbt(struct mtd_info *mtd);


static int spiRead(struct spi_transfer *xfer)
{
    if (!SpiNandDeviceRegistered)
    {
        printk("ERROR!! SPI NAND read without SPI NAND Linux device registration\n");
        return(0);
    }

    {
        struct spi_message  message;

        spi_message_init(&message);
        spi_message_add_tail(xfer, &message);

        /* the controller does not support asynchronous transfer,
           when spi_async returns the transfer will be complete
           don't use spi_sync (to avoid the call to schedule),
           scheduling will conflict with atomic operations
           such as writing image from Linux */
        return(spi_async(pSpiDevice, &message));
    }
}


static int spiWrite(unsigned char *msg_buf, int nbytes)
{
    if (!SpiNandDeviceRegistered)
    {
        printk("ERROR!! SPI NAND write without SPI NAND Linux device registration\n");
        return(0);
    }

    {
        struct spi_message  message;
        struct spi_transfer xfer;

        spi_message_init(&message);
        memset(&xfer, 0, (sizeof xfer));
        xfer.prepend_cnt = 0;
        xfer.len         = nbytes;
        xfer.speed_hz    = pSpiDevice->max_speed_hz;
        xfer.rx_buf      = NULL;
        xfer.tx_buf      = msg_buf;

        spi_message_add_tail(&xfer, &message);

        /* the controller does not support asynchronous transfer
           when spi_async returns the transfer will be complete
           don't use spi_sync to avoid the call to schedule */
        return(spi_async(pSpiDevice, &message));
    }
}

static void spi_nand_read_cfg(void)
{ // search through SPI NAND devices to find match
    unsigned char buf[SPI_NAND_ID_LENGTH];
    int i = 0;

    spi_nand_get_device_id(buf, SPI_NAND_ID_LENGTH);

    do
    {
        if (!memcmp(SpiDevInfo[i].chip_device_id, buf, SPI_NAND_ID_LENGTH))
            break;
        i++;
    } while(memcmp(SpiDevInfo[i].chip_name, "default", 7));

    pchip = &SpiDevInfo[i];
    memcpy(pchip->chip_device_id, buf, SPI_NAND_ID_LENGTH);
    if (!spin_is_locked(&chip_lock)) // show status only if initial reset since Linux NAND code resets chip during every block erase
        printk("Found SPI NAND device %s\n", pchip->chip_name);
}

/***********************************************************************/
/* reset SPI NAND device and get configuration information             */
/* some devices such as Micron MT29F1G01 require explicit reset before */
/* access to the device.                                               */
/***********************************************************************/
static int spi_nand_device_reset(void)
{
    unsigned char buf[4];
#if defined(CONFIG_BRCM_IKOS)
    unsigned int i;
    for( i = 0; i < 250; i++);
#else
    udelay(300);
#endif
    if (!spin_is_locked(&chip_lock)) // show status only if initial reset since Linux NAND code resets chip during every block erase
        printk("SPI NAND device reset\n");
    buf[0]        = FLASH_RESET;
    spiWrite(buf, 1);

#if defined(CONFIG_BRCM_IKOS)
    for( i = 0; i < 3000; i++);
#else
    /* device is availabe after 5ms */
    mdelay(5);
#endif
    while(!spi_nand_ready()); // do we need this here??

    spi_nand_set_feat(FEATURE_PROT_ADDR, FEAT_DISABLE); // disable block locking

    spi_nand_read_cfg();

    return(FLASH_API_OK);
}

/*****************************************************************************************/
/*  row address is 24 bit length. so buf must be at least 3 bytes.                       */
/*  For gigadevcie GD5F1GQ4 part(2K page size, 64 page per block and 1024 blocks)        */
/*  Row Address. RA<5:0> selects a page inside a block, and RA<15:6> selects a block and */
/*  first byte is dummy byte                                                             */
/*****************************************************************************************/
static void spi_nand_row_addr(unsigned int page_addr, unsigned char* buf)
{
    buf[0] = (unsigned char)(page_addr>>(pchip->chip_page_shift+16)); //dummy byte
    buf[1] = (unsigned char)(page_addr>>(pchip->chip_page_shift+8));
    buf[2] = (unsigned char)(page_addr>>(pchip->chip_page_shift));

    return;
}

/*********************************************************************************************************************/
/*  column address select the offset within the page. For gigadevcie GD5F1GQ4 part(2K page size and 2112 with spare) */
/*  is 12 bit length. so buf must be at least 2 bytes. The 12 bit address is capable of address from 0 to 4095 bytes */
/*  however only byte 0 to 2111 are valid.                                                                           */
/*********************************************************************************************************************/
static void spi_nand_col_addr(unsigned int page_addr, unsigned int page_offset, unsigned char* buf)
{
    page_offset = page_offset&((1<<(pchip->chip_page_shift+1))-1);  /* page size + spare area size */

    /* the upper 4 bits of buf[0] is either wrap bits for gigadevice or dummy bit[3:1] + plane select bit[0] for micron
     */
    if(*pchip->chip_device_id == MICRONPART)
    {
        /* setup plane bit if more than one plane. otherwise that bit is always 0 */
        if( pchip->chip_num_planes > 1 )
            buf[0] = (unsigned char)(((page_offset>>8)&0xf)|((page_addr>>pchip->chip_block_shift)&0x1)<<4); //plane bit is the first bit of the block number RowAddr[6]
        else
            buf[0] = (unsigned char)((page_offset>>8)&0xFF);
    }
    else
    {
        /* use default wrap option 0, wrap length 2112 */
        buf[0] = (unsigned char)((page_offset>>8)&0xFF);
    }
    buf[1] = (unsigned char)(page_offset&0xFF);

    return;
}

/***************************************************************************
 * Function Name: spi_xfr
 * Description  : Commonly used SPI transfer function.
 * Returns      : nothing
 ***************************************************************************/
static void spi_xfr(unsigned long page_addr, unsigned int page_offset, unsigned char *buffer, int len)
{
    int maxread;
    unsigned char buf[4];
    struct spi_transfer xfer;

    while (len > 0)
    { // break up NAND buffer read into SPI buffer sized chunks
       /* Random data read (0Bh or 03h) command to read the page data from the cache
          The RANDOM DATA READ command requires 4 dummy bits, followed by a 12-bit column
          address for the starting byte address and a dummy byte for waiting data.
          This is only for 2K page size, the format will change for other page size.
       */

        maxread = (len < spi_max_op_len) ? len : spi_max_op_len;

        buf[0] = FLASH_READ;
        spi_nand_col_addr(page_addr, page_offset, buf+1);
        buf[3] = 0; //dummy byte

        if ((page_offset < pchip->chip_page_size) && ((maxread + page_offset) > pchip->chip_page_size))
            maxread = pchip->chip_page_size - page_offset; // snap address to OOB boundary to let chip know we want OOB

        if ((page_offset < pchip->chip_ecc_offset) && ((maxread + page_offset) > pchip->chip_ecc_offset))
            maxread = pchip->chip_ecc_offset - page_offset; // snap address to ECC boundary to let chip know we want ECC

        DBG_PRINTF("spi_xfr - spi cmd 0x%x, 0x%x, 0x%x, 0x%x\n", buf[0],buf[1],buf[2],buf[3]);
        DBG_PRINTF("spi_xfr - spi read len 0x%x, offset 0x%x, remaining 0x%x\n", maxread, page_offset, len);

        memset(&xfer, 0, sizeof(struct spi_transfer));
        xfer.tx_buf      = buf;
        xfer.rx_buf      = buffer;
        xfer.len         = maxread;
        xfer.speed_hz    = spi_flash_clock;
        xfer.prepend_cnt = 4;
        xfer.addr_len    = 3; // length of address field (max 4 bytes)
        xfer.addr_offset = 1; // offset of first addr byte in header
        xfer.hdr_len     = 4; // length of header
        xfer.unit_size   = 1; // data for each transfer will be divided into multiples of unit_size
        spiRead(&xfer);
        while (!spi_nand_ready());

        buffer += maxread;
        len -= maxread;
        page_offset += maxread;
    }
}

#if defined(COUNT_BAD_BITS)
/***************************************************************************
 * Function Name: count_bits
 * Description  : Counts the bit differences between two buffers.
 * Returns      : Bit difference count
 ***************************************************************************/
static int count_bits(unsigned char * buf1, unsigned char * buf2, int len)
{
    int i, count = 0;
    unsigned char hold;

    for(i = 0; i < len; i++)
    {
        hold = buf1[i] ^ buf2[i];
        while(hold)
        {
            hold &= (hold-1);
            count++;
        }
    }

    return(count);
}
#endif // COUNT_BAD_BITS
/***************************************************************************
 * Function Name: spi_nand_read_page
 * Description  : Reads up to a NAND block of pages into the specified buffer.
 * Returns      : FLASH_API_OK or FLASH_API_ERROR or FLASH_API_CORR
 ***************************************************************************/
static int spi_nand_read_page(unsigned long page_addr, unsigned int page_offset, unsigned char *buffer, int len)
{
    unsigned char buf[(spi_max_op_len > pchip->chip_spare_size) ? spi_max_op_len : pchip->chip_spare_size];
    int status = FLASH_API_OK;

    if ((page_offset + len) > (pchip->chip_page_size + pchip->chip_spare_size)) // check to see if reading within page/OOB boundary
    {
        printk("spi_nand_read_page(): Attempt to read past page boundary, offset 0x%x, length 0x%x, into page address 0x%x\n", page_offset, len, (unsigned int)page_addr);

        return (FLASH_API_ERROR);
    }

    spi_nand_set_feat(FEATURE_FEAT_ADDR, FEAT_ECC_EN); // reading from page, enable ECC, turn on ECC anyway even if there's a failure should still fill buffer

    /* The PAGE READ (13h) command transfers the data from the NAND Flash array to the
     * cache register.  The PAGE READ command requires a 24-bit address consisting of
     * 8 dummy bits followed by a 16-bit block/page address.
     */
    buf[0] = FLASH_PREAD;
    spi_nand_row_addr(page_addr, buf+1);
    DBG_PRINTF("spi_nand_read_page - spi cmd 0x%x, 0x%x, 0x%x, 0x%x\n", buf[0], buf[1], buf[2], buf[3]);
    spiWrite(buf, 4);

    /* GET FEATURES (0Fh)  command to read the status */
    while(!spi_nand_ready());

    if (page_offset < pchip->chip_page_size)
        status = spi_nand_ecc();

    if (!len)
        return(status);

    spi_xfr(page_addr, page_offset, buffer, len);


    if(status == FLASH_API_CORR)
    { // count bad bits to see if we exceed threshold
        if(pchip->chip_ecc_enh)
        { // chip has enhanced bad bit detection
            if (
                 ( (pchip->chip_device_id[0] == GIGADEVPART) && ( (spi_nand_get_cmd(FLASH_GFEAT, FEATURE_STAT_AUX) & STAT_ECC_MASK1) < pchip->chip_ecc_enh) ) || 
                 ( (pchip->chip_device_id[0] == MACRONIXPART) && ( (spi_nand_get_cmd(FLASH_SREAD, 0) & STAT_ECC_MASK2) < pchip->chip_ecc_enh) ) ||
                 ( (pchip->chip_device_id[0] == TOSHIBAPART) && ( (spi_nand_get_cmd(FLASH_GFEAT, FEATURE_STAT_ENH) & STAT_ECC_MASK3) < pchip->chip_ecc_enh) )
               )
                status = FLASH_API_OK;
        }
#if defined(COUNT_BAD_BITS)
        else if (pchip->chip_ecc_corr != 1) // If correctable and threshold is 1 bit then we are already at correctable threshold, no need to check
        {
            unsigned char buf_ecc[pchip->chip_page_size + pchip->chip_spare_size];
            unsigned char buf_noecc[pchip->chip_page_size + pchip->chip_spare_size];
            int i, size, count, worst = 0;

            spi_xfr(page_addr, 0, buf_ecc, pchip->chip_page_size + pchip->chip_spare_size);

            spi_nand_set_feat(FEATURE_FEAT_ADDR, FEAT_DISABLE); // now grab data with ecc turned off

            /* The PAGE READ (13h) command transfers the data from the NAND Flash array to the
             * cache register.  The PAGE READ command requires a 24-bit address consisting of
             * 8 dummy bits followed by a 16-bit block/page address.
             */
            buf[0] = FLASH_PREAD;
            spi_nand_row_addr(page_addr, buf+1);
            spiWrite(buf, 4);

            while(!spi_nand_ready());

            spi_xfr(page_addr, 0, buf_noecc, pchip->chip_page_size + pchip->chip_spare_size);

            for(i = 0; i < (1 << pchip->chip_subpage_shift); i++)
            {
                count = 0;

                size = pchip->chip_page_size >> pchip->chip_subpage_shift;
                count += count_bits(buf_ecc + (size * i), buf_noecc + (size * i), size);

                size = (pchip->chip_spare_size - (pchip->chip_ecc_offset - pchip->chip_page_size)) >> pchip->chip_subpage_shift;
                count += count_bits(buf_ecc + pchip->chip_page_size + (size * i), buf_noecc + pchip->chip_page_size + (size * i), size);

                if(pchip->chip_page_size != pchip->chip_ecc_offset)
                    count += count_bits(buf_ecc + pchip->chip_ecc_offset + (size * i), buf_noecc + pchip->chip_ecc_offset + (size * i), size);

                if (count > worst)
                    worst = count;
            }

            if (worst < pchip->chip_ecc_corr)
                status = FLASH_API_OK;
        }
#endif // COUNT_BAD_BITS
    }

    return(status);
}

/*********************************************************************/
/* Flash_status return the feature status byte                       */
/*********************************************************************/
static int spi_nand_status(void)
{
    return spi_nand_get_cmd(FLASH_GFEAT, FEATURE_STAT_ADDR);
}

/* check device ready bit */
static int spi_nand_ready(void)
{
  return (spi_nand_status()&STAT_OIP) ? 0 : 1;
}

/*********************************************************************/
/*  spi_nand_get_cmd return the resultant byte at command, address   */
/*********************************************************************/
static int spi_nand_get_cmd(unsigned char command, unsigned char feat_addr)
{
    unsigned char buf[4];
    struct spi_transfer xfer;

    /* check device is ready */
    memset(&xfer, 0, sizeof(struct spi_transfer));

    buf[0]           = command;
    buf[1]           = feat_addr;
    xfer.tx_buf      = buf;
    xfer.rx_buf      = buf;
    xfer.len         = 1;
    xfer.speed_hz    = spi_flash_clock;
    xfer.prepend_cnt = 2;
    spiRead(&xfer);


    DBG_PRINTF("spi_nand_get_cmd at 0x%x 0x%x\n", feat_addr, buf[0]);

    return buf[0];
}

/*********************************************************************/
/*  spi_nand_set_feat set the feature byte at feat_addr              */
/*********************************************************************/
static void spi_nand_set_feat(unsigned char feat_addr, unsigned char feat_val)
{
    unsigned char buf[3];

    /* check device is ready */
    buf[0]           = FLASH_SFEAT;
    buf[1]           = feat_addr;
    buf[2]           = feat_val;
    spiWrite(buf, 3);

    while(!spi_nand_ready());

    return;
}

static int spi_nand_ecc(void)
{
    int status;

    status = spi_nand_get_cmd(FLASH_GFEAT, FEATURE_STAT_ADDR);
    status = status & STAT_ECC_MASK1;

    if (status == STAT_ECC_GOOD)
        return(FLASH_API_OK);

    if (status == STAT_ECC_UNCORR) // correctable errors
        return(FLASH_API_ERROR);

     return(FLASH_API_CORR); // everything else is correctable
}

/*********************************************************************/
/* Flash_sector__int() wait until the erase is completed before      */
/* returning control to the calling function.  This can be used in   */
/* cases which require the program to hold until a sector is erased, */
/* without adding the wait check external to this function.          */
/*********************************************************************/
static int spi_nand_sector_erase_int(unsigned long addr)
{
    unsigned char buf[11];
    int status;

    addr &= ~(pchip->chip_block_size - 1);

    DBG_PRINTF("spi_nand_sector_erase_int block at address 0x%lx\n", addr);

    if (spi_nand_is_blk_bad(addr))
    {
        printk("spi_nand_sector_erase_int(): Attempt to erase failed due to bad block 0x%lx (address 0x%lx)\n", addr >> pchip->chip_block_shift, addr);
        return (FLASH_API_ERROR);
    }

    { // erase dirty block
        spi_nand_write_enable();
        buf[0] = FLASH_BERASE;
        spi_nand_row_addr(addr, buf+1);
        spiWrite(buf, 4);
        while(!spi_nand_ready()) ;

        status = spi_nand_status();
        if( status & STAT_EFAIL )
        {
            printk("spi_nand_sector_erase_int(): Erase block 0x%lx failed, sts 0x%x\n",  addr >> pchip->chip_block_shift, status);
            return(FLASH_API_ERROR);
        }

        spi_nand_write_disable();
    }

    return (FLASH_API_OK);
}

/************************************************************************/
/* flash_write_enable() must be called before any change to the         */
/* device such as write, erase. It also unlocks the blocks if they were */
/* previouly locked.                                                    */
/************************************************************************/
static int spi_nand_write_enable(void)
{
    unsigned char buf[4], prot;

    /* make sure it is not locked first */
    prot = spi_nand_get_cmd(FLASH_GFEAT, FEATURE_PROT_ADDR);
    if( prot != 0 )
    {
        prot = 0;
        spi_nand_set_feat(FEATURE_PROT_ADDR, prot);
    }

    /* send write enable cmd and check feature status WEL latch bit */
    buf[0] = FLASH_WREN;
    spiWrite(buf, 1);
    while(!spi_nand_ready());
    while(!spi_nand_wel());

    return(FLASH_API_OK);
}

static int spi_nand_write_disable(void)
{
    unsigned char buf[4];

    buf[0] = FLASH_WRDI;
    spiWrite(buf, 1);
    while(!spi_nand_ready());
    while(spi_nand_wel());

    return(FLASH_API_OK);
}

/***************************************************************************
 * Function Name: spi_nand_write_page
 * Description  : Writes up to a NAND block of pages from the specified buffer.
 * Returns      : FLASH_API_OK or FLASH_API_ERROR
 ***************************************************************************/
static int spi_nand_write_page(unsigned long page_addr, unsigned int page_offset, unsigned char *buffer, int len)
{
    unsigned char spi_buf[512];  /* HS_SPI_BUFFER_LEN SPI controller fifo size is currently 512 bytes*/
    unsigned char xfer_buf[pchip->chip_page_size + pchip->chip_spare_size];
    int maxwrite, status;
    unsigned int page_ofs = page_offset;

    if (!len)
    {
        printk("spi_nand_write_page(): Not writing any data to page addr 0x%x, page_offset 0x%x, len 0x%x\n", (unsigned int)page_addr, page_offset, len);
        return (FLASH_API_OK);
    }

    if ((page_offset + len) > (pchip->chip_page_size + pchip->chip_spare_size))
    {
        printk("spi_nand_write_page(): Attempt to write past page boundary, offset 0x%x, length 0x%x, into page address 0x%x\n", page_offset, len, (unsigned int)page_addr);
        return (FLASH_API_ERROR);
    }

    if (page_ofs < pchip->chip_page_size)
    { /* writing into page area, if writing into spare area is allowed then must read page first to fill write buffer
       * because we don't know if JFFS2 clean marker is there or not and this clean marker would initially have
       * been written with ECC off, but will now be included in the ECC calculation along with the page data */
        spi_nand_set_feat(FEATURE_FEAT_ADDR, FEAT_ECC_EN); // enable ECC if writing to page
    }
    else
    { // not writing into page area
        if (len != 1)
            return(FLASH_API_OK); // only allowed write is the bad block marker; return if not that

        spi_nand_set_feat(FEATURE_FEAT_ADDR, FEAT_DISABLE); // else don't write ECC
    }

    memset(xfer_buf, 0xff, sizeof(xfer_buf));
    memcpy(xfer_buf + page_offset, buffer, len);
    len = pchip->chip_page_size + pchip->chip_spare_size;
    page_offset = 0;

    while (len > 0)
    {
        /* Send Program Load Random Data Command (0x84) to load data to cache register.
         * PROGRAM LOAD consists of an 8-bit Op code, followed by 4 bit dummy and a
         * 12-bit column address, then the data bytes to be programmed. */
        spi_buf[0] = FLASH_PROG_RAN;
        spi_nand_col_addr(page_addr, page_offset, spi_buf + 1);

        maxwrite = (len > (spi_max_op_len - 5)) ? (spi_max_op_len - 5) : len;

        if ((page_offset < pchip->chip_page_size) && ((maxwrite + page_offset) > pchip->chip_page_size))
            maxwrite = pchip->chip_page_size - page_offset; // snap address to OOB boundary to let chip know we want OOB

        if ((page_offset < pchip->chip_ecc_offset) && ((maxwrite + page_offset) > pchip->chip_ecc_offset))
            maxwrite = pchip->chip_ecc_offset - page_offset; // snap address to ECC boundary to let chip know we want ECC

        memcpy(&spi_buf[3], xfer_buf + page_offset, maxwrite);
        DBG_PRINTF("spi_nand_write_page - spi cmd 0x%x, 0x%x, 0x%x\n", spi_buf[0], spi_buf[1], spi_buf[2]);
        DBG_PRINTF("spi_nand_write_page - spi write len 0x%x, offset 0x%x, remaining 0x%x\n", maxwrite, offset, len-maxwrite);

        spi_nand_write_enable();
        spiWrite(spi_buf, maxwrite + 3);

        len -= maxwrite;
        page_offset += maxwrite;

        while(!spi_nand_ready()); // do we need this here??
    }

    /* Send Program Execute command (0x10) to write cache data to memory array
     * Send address (24bit): 8 bit dummy + 16 bit address (page/Block)
     */
    /* Send Write enable Command (0x06) */
    spi_nand_write_enable();

    spi_buf[0] = FLASH_PEXEC;
    spi_nand_row_addr(page_addr, spi_buf + 1);
    DBG_PRINTF("spi_nand_write_page - spi cmd 0x%x, 0x%x, 0x%x, 0x%x\n", spi_buf[0], spi_buf[1], spi_buf[2], spi_buf[3]);
    spiWrite(spi_buf, 4);
    while(!spi_nand_ready());

    status = spi_nand_status();
    spi_nand_write_disable();

    if(status & STAT_PFAIL)
    {
        printk("Page program failed at address 0x%x, sts 0x%x\n", (unsigned int)page_addr, status);
        return(FLASH_API_ERROR);
    }

    if (page_ofs < pchip->chip_page_size)
    {
        unsigned char buf[pchip->chip_page_size];

        status = spi_nand_read_page(page_addr, 0, buf, pchip->chip_page_size);

        if (status == FLASH_API_ERROR)
        {
            printk("Write verify failed reading back page at address 0x%lx\n", page_addr);
            return(FLASH_API_ERROR);
        }

        if (memcmp(xfer_buf, buf, pchip->chip_page_size))
        {
            printk("Write data did not match read data at address 0x%lx\n", page_addr);
            return(FLASH_API_ERROR);
        }

        if (status == FLASH_API_CORR)
        {
            printk("Write verify correctable errors at address 0x%lx\n", page_addr);
            return(FLASH_API_CORR);
        }
    }

    return (FLASH_API_OK);
}

/* check device write enable latch bit */
static int spi_nand_wel(void)
{
  return (spi_nand_status() & STAT_WEL) ? 1 : 0;
}

/*********************************************************************/
/* flash_get_device_id() return the device id of the component.      */
/*********************************************************************/
static void spi_nand_get_device_id(unsigned char * buf, unsigned int len)
{
    unsigned char buffer[2];
    struct spi_transfer xfer;

    memset(&xfer, 0, sizeof(struct spi_transfer));
    buffer[0]        = FLASH_RDID;
    buffer[1]        = 0;
    xfer.tx_buf      = buffer;
    xfer.rx_buf      = buf;
    xfer.len         = len;
    xfer.speed_hz    = spi_flash_clock;
    xfer.prepend_cnt = 2;
    spiRead(&xfer);
    while(!spi_nand_ready());

    DBG_PRINTF("spi_nand_get_device_id 0x%x 0x%x\n", buf[0], buf[1]);
}

static int spi_nand_is_blk_bad(unsigned long addr)
{
    unsigned char buf;

    if (addr < pchip->chip_block_size)
        return 0; // always return good for block 0, because if it's a bad chip quite possibly the board is useless

    addr &= ~(pchip->chip_block_size - 1);

    spi_nand_read_page(addr, pchip->chip_page_size, &buf, 1);

    if (0xFF != buf)
    {
        printk("Bad Block 0x%lx found (address 0x%lx)\n", addr >> pchip->chip_block_shift, addr);
        return(1);
    }

    return(0);
}

static int spi_nand_mark_blk_bad(unsigned long addr)
{
    int ret1, ret2;

    addr &= ~(pchip->chip_block_size - 1);

    printk("Marking block 0x%lx bad (address 0x%lx)\n", addr >> pchip->chip_block_shift, addr);

    ret1 = spi_nand_write_page(addr, pchip->chip_page_size, "\0", 1); // write bad block marker into first page
    ret2 = spi_nand_write_page(addr + pchip->chip_page_size, pchip->chip_page_size, "\0", 1); // write bad block marker into second page

    if ((ret1 != FLASH_API_OK) && (ret2 != FLASH_API_OK))
    {
        printk("Unable to mark block 0x%lx bad\n", addr >> pchip->chip_block_shift);
        return(FLASH_API_ERROR);
    }

    return(FLASH_API_OK);
}

static void bcm63xx_cmd(struct mtd_info *mtd, unsigned int command, int column, int page)
{
    unsigned long addr = page * mtd->writesize;

    spin_lock(&chip_lock);

    switch(command)
    {
        case NAND_CMD_READ0:
        case NAND_CMD_READ1: // step 1/2 for read, execute SPI NAND read command and transfer SPI NAND data to local buffer

            status = STATUS_DEFAULT;

            if (addr > mtd->size)
            {
                printk("SPI NAND ERROR!! Trying to read past end of chip\n");
                status |= NAND_STATUS_FAIL;
            }
            else
            {
                int temp = spi_nand_read_page(page * mtd->writesize, column, pageBuf, mtd->writesize + mtd->oobsize);

                if (FLASH_API_ERROR == temp)
                {
                    printk("SPI NAND ERROR Reading page!!\n");
                    status |= NAND_STATUS_FAIL;
                    mtd->ecc_stats.failed++;
                }
                else if (FLASH_API_CORR == temp)
                    mtd->ecc_stats.corrected++;

                pageBufI = 0;
            }
            break;

        case NAND_CMD_READOOB: // step 1/2 for read, execute SPI NAND read command and transfer SPI NAND data to local buffer

            status = STATUS_DEFAULT;

            if (addr > mtd->size)
            {
                printk("SPI NAND ERROR!! Trying to read past end of chip\n");
                status |= NAND_STATUS_FAIL;
            }
            else
            {
                int temp = spi_nand_read_page(page * mtd->writesize, mtd->writesize, pageBuf + mtd->writesize, mtd->oobsize);

                if (FLASH_API_ERROR == temp)
                {
                    printk("SPI NAND ERROR Reading page OOB!!\n");
                    status |= NAND_STATUS_FAIL;
                    mtd->ecc_stats.failed++;
                }
                else if (FLASH_API_CORR == temp)
                    mtd->ecc_stats.corrected++;

                pageBufI = mtd->writesize;
            }
            break;

        case NAND_CMD_RESET:
            status = STATUS_DEFAULT;

            if (FLASH_API_ERROR == spi_nand_device_reset())
            {
                printk("ERROR resetting SPI NAND device!!\n");
                status |= NAND_STATUS_FAIL;
            }
            break;

        case NAND_CMD_READID:
            status = STATUS_DEFAULT;

            spi_nand_get_device_id(pageBuf, NAND_ID_LENGTH);

            if (*pageBuf == GIGADEVPART)
                *(pageBuf+2) = 0x80; *(pageBuf+3) = 0x1D; // provide the rest of the ID bytes that Gigadevice omits

            pageBufI = 0;
            break;

        case NAND_CMD_STATUS: // NAND infrastructure only uses this to determine if write protect is set
            *(pageBuf + mtd->writesize + mtd->oobsize - 1) = status;
            pageBufI = mtd->writesize + mtd->oobsize - 1; // set pointer to end of buffer so we have a limit to the amount of data read
            break;

        case NAND_CMD_SEQIN: // step 1/3 for write, capture address
            status = STATUS_DEFAULT;

            if (addr > mtd->size)
            {
                printk("ERROR!! Trying to program past end of chip\n");
                status |= NAND_STATUS_FAIL;
            }
            else
            {
                pageAddr = addr;
                pageOffset = column;
                pageBufI = 0;
            }
            break;

        case NAND_CMD_PAGEPROG: // step 3/3 for write, transfer local buffer to SPI NAND device and execute SPI NAND write command
        {
            int error = 0;

            addr = pageAddr & ~(mtd->erasesize - 1); // block address

            if ((status = spi_nand_write_page(pageAddr, pageOffset, pageBuf, pageBufI)) == FLASH_API_ERROR)
                error = 1;

            if (!error && (status == FLASH_API_CORR) && (pageAddr >= mtd->erasesize))
            { // read/erase/write block to see if we can get rid of the bit errors, but only if not block zero
                int offset;
                unsigned char * buffer;

                printk("Correctible errors, SPI NAND Rewriting block\n");

                buffer = kmalloc(mtd->erasesize, GFP_ATOMIC);
                if (!buffer)
                { // unfortunately can't attempt to fix block in this case
                    printk("Error allocating buffer!!\n");
                    error = 1;
                }

                // read block
                for (offset = 0; !error && (offset < mtd->erasesize); offset += mtd->writesize)
                {
                    status = spi_nand_read_page(addr + offset, 0, buffer + offset, mtd->writesize);
                    if (status == FLASH_API_ERROR)
                        error = 1;
                }

                // erase block
                if (!error)
                {
                    status = spi_nand_sector_erase_int(addr);
                    if (status == FLASH_API_ERROR)
                        error = 1;
                }

                // write block
                if (!error)
                {
                    for (offset = 0; offset < mtd->erasesize; offset += mtd->writesize)
                    {
                        status = spi_nand_write_page(addr + offset, 0, buffer + offset, mtd->writesize);
                        if (status != FLASH_API_OK)
                            error = 1; // essentially failed, but finish writing out all the data anyway to hopefully be recovered later
                    }
                }

                if(buffer)
                    kfree(buffer);
            }

            status = STATUS_DEFAULT;

            if (error)
            {
                printk("SPI NAND ERROR Writing page!!\n");
                status |= NAND_STATUS_FAIL;
                spi_nand_mark_blk_bad(addr); // JFFS2 will do this automatically
            }

            break;
        }

        case NAND_CMD_ERASE1:
            status = STATUS_DEFAULT;

            if (addr >= mtd->size)
            {
                printk("ERROR!! Trying to erase past end of chip\n");
                status |= NAND_STATUS_FAIL;
            }
            else if (FLASH_API_ERROR == spi_nand_sector_erase_int(addr))
            {
                printk("SPI NAND ERROR Erasing block!!\n");
                status |= NAND_STATUS_FAIL;
            }
        case NAND_CMD_ERASE2:
            break;

            default:
                printk("ERROR!! Unkonwn NAND command 0x%x\n", command);
                status |= NAND_STATUS_FAIL;
        }

    spin_unlock(&chip_lock);
}

static unsigned char bcm63xx_read_byte(struct mtd_info *mtd)
{
    unsigned char ret;

    spin_lock(&chip_lock);

    ret = *(pageBuf + pageBufI++);

    spin_unlock(&chip_lock);

    return(ret);
}

static void bcm63xx_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{ // step 2/2 for read, read data from local buffer
    spin_lock(&chip_lock);

    if ((pageBufI + len) > (mtd->writesize + mtd->oobsize))
        printk("ERROR!! Trying to read past end of buffer\n");
    else
    {
        memcpy(buf, pageBuf+pageBufI, len);
        pageBufI += len;
    }

    spin_unlock(&chip_lock);
}

// step 2/3 for write, fill local buffer
static void bcm63xx_write(struct mtd_info *mtd, const uint8_t *buf, int len)
{ // write to buffer
    spin_lock(&chip_lock);

    if ((pageBufI + len) > (mtd->writesize + mtd->oobsize))
        printk("ERROR!! Trying to write past end of buffer\n");
    else
    {
        memcpy(pageBuf+pageBufI, buf, len);
        pageBufI += len;
    }

    spin_unlock(&chip_lock);
}

static int bcm63xx_status(struct mtd_info *mtd, struct nand_chip *chip)
{ // NAND infrastructure used this to not only determine when a command has finished (spinlocks will take care of that)
    // but also to return the status

    spin_lock(&chip_lock);

    spin_unlock(&chip_lock);

    return(status);
}

static int bcm63xx_init_size(struct mtd_info *mtd, struct nand_chip *chip, unsigned char *id_data)
{ // overwrite possibly incorrectly detected values from Linux NAND driver
    static int splash = 0;
    int i;

    if (!splash)
    {
        printk("SPI NAND device %s\n", pchip->chip_name);
        printk("   device id    = 0x");
        for (i = 0; i < SPI_NAND_ID_LENGTH; i++)
            printk("%x", pchip->chip_device_id[i]);
        printk("\n");
        printk("   page size    = 0x%x (%d) bytes\n", pchip->chip_page_size, pchip->chip_page_size);
        printk("   block size   = 0x%x (%d) bytes\n", pchip->chip_block_size, pchip->chip_block_size);
        printk("   total blocks = 0x%x (%d)\n", pchip->chip_num_blocks, pchip->chip_num_blocks);
        printk("   total size   = 0x%lx (%ld) bytes\n", pchip->chip_total_size, pchip->chip_total_size);

        splash = 1;
    }

    mtd->writesize = pchip->chip_page_size;
    mtd->oobsize = pchip->chip_spare_size;
    mtd->erasesize = pchip->chip_block_size;
    chip->chipsize = mtd->size = pchip->chip_total_size;
    mtd->name = pchip->chip_name;

    /* no MLC for SPINAND yet */
    chip->bits_per_cell = 1;

    chip->numchips = 1;

    return(0);
}

static int bcm63xx_block_isbad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
    int ret;

    spin_lock(&chip_lock);

    ret = spi_nand_is_blk_bad(ofs);

    spin_unlock(&chip_lock);

    return(ret);
}

static int bcm63xx_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
    int ret;

    spin_lock(&chip_lock);

    ret = spi_nand_mark_blk_bad(ofs);

    spin_unlock(&chip_lock);

    return(ret);
}

static void bcm63xx_select(struct mtd_info *mtd, int chip)
{ // dummy function, chip is always selected as far as the NAND infrastructure is concerned
}

static int bcm63xx_scan_bbt(struct mtd_info *mtd)
{ // dummy function
    return(1); // this will ultimately be the return value for nand_scan
}

static struct spi_board_info bcmSpiDevInfo =
{
    .modalias      = "bcm_SpiDev",
    .chip_select   = 0,
    .max_speed_hz  = 781000,
    .bus_num       = LEG_SPI_BUS_NUM,
    .mode          = SPI_MODE_3,
};

static struct spi_driver bcmSpiDevDrv =
{
    .driver =
        {
        .name     = "bcm_SpiDev",
        .bus      = &spi_bus_type,
        .owner    = THIS_MODULE,
        },
};


void bcmspinand_probe(struct mtd_info * mtd)
{
    struct nand_chip * nand = mtd->priv;
    struct spi_master * pSpiMaster;
    unsigned int spiCtrlState;

    printk("SPI NAND Device Linux Registration\n");

    /* micron MT29F1G01 only support up to 50MHz, update to 50Mhz if it is more than that */
    spi_flash_busnum = HS_SPI_BUS_NUM;
    spi_flash_clock = 50000000;

    /* retrieve the maximum read/write transaction length from the SPI controller */
    spi_max_op_len = SPI_BUF_LEN;

    /* set the controller state, spi_mode_0 */
    spiCtrlState = (unsigned int)SPI_CONTROLLER_STATE_DEFAULT;

    if ( spi_flash_clock > SPI_CONTROLLER_MAX_SYNC_CLOCK )
       spiCtrlState |= SPI_CONTROLLER_STATE_ASYNC_CLOCK;

    bcmSpiDevInfo.max_speed_hz    = spi_flash_clock;
    bcmSpiDevInfo.controller_data = (void *)(uintptr_t)spiCtrlState;
    bcmSpiDevInfo.mode            = SPI_MODE_DEFAULT;
    bcmSpiDevInfo.chip_select     = SPI_FLASH_SLAVE_DEV_ID;
    bcmSpiDevInfo.bus_num         = spi_flash_busnum;

    pSpiMaster = spi_busnum_to_master( spi_flash_busnum );
    pSpiDevice = spi_new_device(pSpiMaster, &bcmSpiDevInfo);

    /* register as SPI device */
    spi_register_driver(&bcmSpiDevDrv);

    SpiNandDeviceRegistered = 1;

    printk("SPI NAND Linux Registration\n");

    spin_lock_init(&chip_lock);

    spi_nand_device_reset(); // reset and set configuration information

    nand->ecc.size = pchip->chip_page_size;
    nand->ecc.bytes = 0;
    nand->ecc.strength = 0;
    nand->ecc.layout = pchip->ecclayout;
    nand->page_shift = pchip->chip_page_shift;
    nand->phys_erase_shift = pchip->chip_block_shift;
    nand->chipsize = pchip->chip_total_size;

    pageBuf = kmalloc(pchip->chip_page_size + pchip->chip_spare_size, GFP_KERNEL);

    nand->options = NAND_NO_SUBPAGE_WRITE;

    nand->chip_delay = 0;
    nand->read_byte = bcm63xx_read_byte;
    nand->read_buf = bcm63xx_read_buf;
    nand->ecc.mode = NAND_ECC_NONE;

    nand->select_chip = bcm63xx_select;
    nand->write_buf  = bcm63xx_write;
    nand->scan_bbt = bcm63xx_scan_bbt;
    nand->block_bad = bcm63xx_block_isbad;
    nand->block_markbad = bcm63xx_block_markbad;
    nand->cmdfunc = bcm63xx_cmd;
    nand->waitfunc = bcm63xx_status;

    nand->init_size = bcm63xx_init_size;
}

#endif //CONFIG_BCM_KF_MTD_BCMNAND
