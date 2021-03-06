#if defined(CONFIG_BCM_KF_MTD_BCMNAND)
/*
*
    <:copyright-BRCM:2015:DUAL/GPL:standard
    
       Copyright (c) 2015 Broadcom 
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
 */

#ifndef BCHP_NAND_21_22_H__
#define BCHP_NAND_21_22_H__

#define BRCMNAND_CTL_BASE                        ((uintptr_t)(NAND_REG_BASE & 0x0fffffff))
#define BRCMNAND_CACHE_BASE                      ((uintptr_t)(NAND_CACHE_BASE & 0x0fffffff))

#define BCHP_NAND_REG_START                     BCHP_NAND_REVISION
#define BCHP_NAND_REG_END                       BCHP_NAND_BLK_WR_PROTECT

/***************************************************************************
 *NAND - Nand Flash Control Registers
 ***************************************************************************/
#define BCHP_NAND_REVISION                       ((uintptr_t)(BRCMNAND_CTL_BASE + 0x00)) /* NAND Revision */
#define BCHP_NAND_CMD_START                      ((uintptr_t)(BRCMNAND_CTL_BASE + 0x04)) /* Nand Flash Command Start */
#define BCHP_NAND_CMD_EXT_ADDRESS                ((uintptr_t)(BRCMNAND_CTL_BASE + 0x08)) /* Nand Flash Command Extended Address */
#define BCHP_NAND_CMD_ADDRESS                    ((uintptr_t)(BRCMNAND_CTL_BASE + 0x0c)) /* Nand Flash Command Address */
#define BCHP_NAND_CMD_END_ADDRESS                ((uintptr_t)(BRCMNAND_CTL_BASE + 0x10)) /* Nand Flash Command End Address */
#define BCHP_NAND_CS_NAND_SELECT                 ((uintptr_t)(BRCMNAND_CTL_BASE + 0x14)) /* Nand Flash EBI CS Select */
#define BCHP_NAND_CS_NAND_XOR                    ((uintptr_t)(BRCMNAND_CTL_BASE + 0x18)) /* Nand Flash EBI CS Address XOR with 1FC0 Control */
#define BCHP_NAND_SPARE_AREA_READ_OFS_0          ((uintptr_t)(BRCMNAND_CTL_BASE + 0x20)) /* Nand Flash Spare Area Read Bytes 0-3 */
#define BCHP_NAND_SPARE_AREA_READ_OFS_4          ((uintptr_t)(BRCMNAND_CTL_BASE + 0x24)) /* Nand Flash Spare Area Read Bytes 4-7 */
#define BCHP_NAND_SPARE_AREA_READ_OFS_8          ((uintptr_t)(BRCMNAND_CTL_BASE + 0x28)) /* Nand Flash Spare Area Read Bytes 8-11 */
#define BCHP_NAND_SPARE_AREA_READ_OFS_C          ((uintptr_t)(BRCMNAND_CTL_BASE + 0x2c)) /* Nand Flash Spare Area Read Bytes 12-15 */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0         ((uintptr_t)(BRCMNAND_CTL_BASE + 0x30)) /* Nand Flash Spare Area Write Bytes 0-3 */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4         ((uintptr_t)(BRCMNAND_CTL_BASE + 0x34)) /* Nand Flash Spare Area Write Bytes 4-7 */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8         ((uintptr_t)(BRCMNAND_CTL_BASE + 0x38)) /* Nand Flash Spare Area Write Bytes 8-11 */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C         ((uintptr_t)(BRCMNAND_CTL_BASE + 0x3c)) /* Nand Flash Spare Area Write Bytes 12-15 */
#define BCHP_NAND_ACC_CONTROL                    ((uintptr_t)(BRCMNAND_CTL_BASE + 0x40)) /* Nand Flash Access Control */
#define BCHP_NAND_CONFIG                         ((uintptr_t)(BRCMNAND_CTL_BASE + 0x44)) /* Nand Flash Config */
#define BCHP_NAND_TIMING_1                       ((uintptr_t)(BRCMNAND_CTL_BASE + 0x48)) /* Nand Flash Timing Parameters 1 */
#define BCHP_NAND_TIMING_2                       ((uintptr_t)(BRCMNAND_CTL_BASE + 0x4c)) /* Nand Flash Timing Parameters 2 */
#define BCHP_NAND_SEMAPHORE                      ((uintptr_t)(BRCMNAND_CTL_BASE + 0x50)) /* Semaphore */
#define BCHP_NAND_FLASH_DEVICE_ID                ((uintptr_t)(BRCMNAND_CTL_BASE + 0x54)) /* Nand Flash Device ID */
#define BCHP_NAND_BLOCK_LOCK_STATUS              ((uintptr_t)(BRCMNAND_CTL_BASE + 0x58)) /* Nand Flash Block Lock Status */
#define BCHP_NAND_INTFC_STATUS                   ((uintptr_t)(BRCMNAND_CTL_BASE + 0x5c)) /* Nand Flash Interface Status */
#define BCHP_NAND_ECC_CORR_EXT_ADDR              ((uintptr_t)(BRCMNAND_CTL_BASE + 0x60)) /* ECC Correctable Error Extended Address */
#define BCHP_NAND_ECC_CORR_ADDR                  ((uintptr_t)(BRCMNAND_CTL_BASE + 0x64)) /* ECC Correctable Error Address */
#define BCHP_NAND_ECC_UNC_EXT_ADDR               ((uintptr_t)(BRCMNAND_CTL_BASE + 0x68)) /* ECC Uncorrectable Error Extended Address */
#define BCHP_NAND_ECC_UNC_ADDR                   ((uintptr_t)(BRCMNAND_CTL_BASE + 0x6c)) /* ECC Uncorrectable Error Address */
#define BCHP_NAND_FLASH_READ_EXT_ADDR            ((uintptr_t)(BRCMNAND_CTL_BASE + 0x70)) /* Flash Read Data Extended Address */
#define BCHP_NAND_FLASH_READ_ADDR                ((uintptr_t)(BRCMNAND_CTL_BASE + 0x74)) /* Flash Read Data Address */
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR          ((uintptr_t)(BRCMNAND_CTL_BASE + 0x78)) /* Page Program Extended Address */
#define BCHP_NAND_PROGRAM_PAGE_ADDR              ((uintptr_t)(BRCMNAND_CTL_BASE + 0x7c)) /* Page Program Address */
#define BCHP_NAND_COPY_BACK_EXT_ADDR             ((uintptr_t)(BRCMNAND_CTL_BASE + 0x80)) /* Copy Back Extended Address */
#define BCHP_NAND_COPY_BACK_ADDR                 ((uintptr_t)(BRCMNAND_CTL_BASE + 0x84)) /* Copy Back Address */
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR           ((uintptr_t)(BRCMNAND_CTL_BASE + 0x88)) /* Block Erase Extended Address */
#define BCHP_NAND_BLOCK_ERASE_ADDR               ((uintptr_t)(BRCMNAND_CTL_BASE + 0x8c)) /* Block Erase Address */
#define BCHP_NAND_INV_READ_EXT_ADDR              ((uintptr_t)(BRCMNAND_CTL_BASE + 0x90)) /* Flash Invalid Data Extended Address */
#define BCHP_NAND_INV_READ_ADDR                  ((uintptr_t)(BRCMNAND_CTL_BASE + 0x94)) /* Flash Invalid Data Address */
#define BCHP_NAND_BLK_WR_PROTECT                 ((uintptr_t)(BRCMNAND_CTL_BASE + 0x98)) /* Block Write Protect Enable and Size for EBI_CS0b */

/***************************************************************************
 *REVISION - NAND Revision
 ***************************************************************************/
/* NAND :: REVISION :: reserved0 [31:16] */
#define BCHP_NAND_REVISION_reserved0_MASK                          0xffff0000
#define BCHP_NAND_REVISION_reserved0_SHIFT                         16

/* NAND :: REVISION :: MAJOR [15:08] */
#define BCHP_NAND_REVISION_MAJOR_MASK                              0x0000ff00
#define BCHP_NAND_REVISION_MAJOR_SHIFT                             8

/* NAND :: REVISION :: MINOR [07:00] */
#define BCHP_NAND_REVISION_MINOR_MASK                              0x000000ff
#define BCHP_NAND_REVISION_MINOR_SHIFT                             0

/***************************************************************************
 *CMD_START - Nand Flash Command Start
 ***************************************************************************/
/* NAND :: CMD_START :: reserved0 [31:28] */
#define BCHP_NAND_CMD_START_reserved0_MASK                         0xf0000000
#define BCHP_NAND_CMD_START_reserved0_SHIFT                        28

/* NAND :: CMD_START :: OPCODE [27:24] */
#define BCHP_NAND_CMD_START_OPCODE_MASK                            0x0f000000
#define BCHP_NAND_CMD_START_OPCODE_SHIFT                           24
#define BCHP_NAND_CMD_START_OPCODE_NULL                            0
#define BCHP_NAND_CMD_START_OPCODE_PAGE_READ                       1
#define BCHP_NAND_CMD_START_OPCODE_SPARE_AREA_READ                 2
#define BCHP_NAND_CMD_START_OPCODE_STATUS_READ                     3
#define BCHP_NAND_CMD_START_OPCODE_PROGRAM_PAGE                    4
#define BCHP_NAND_CMD_START_OPCODE_PROGRAM_SPARE_AREA              5
#define BCHP_NAND_CMD_START_OPCODE_COPY_BACK                       6
#define BCHP_NAND_CMD_START_OPCODE_DEVICE_ID_READ                  7
#define BCHP_NAND_CMD_START_OPCODE_BLOCK_ERASE                     8
#define BCHP_NAND_CMD_START_OPCODE_FLASH_RESET                     9
#define BCHP_NAND_CMD_START_OPCODE_BLOCKS_LOCK                     10
#define BCHP_NAND_CMD_START_OPCODE_BLOCKS_LOCK_DOWN                11
#define BCHP_NAND_CMD_START_OPCODE_BLOCKS_UNLOCK                   12
#define BCHP_NAND_CMD_START_OPCODE_READ_BLOCKS_LOCK_STATUS         13

/* NAND :: CMD_START :: reserved1 [23:00] */
#define BCHP_NAND_CMD_START_reserved1_MASK                         0x00ffffff
#define BCHP_NAND_CMD_START_reserved1_SHIFT                        0

/***************************************************************************
 *CMD_EXT_ADDRESS - Nand Flash Command Extended Address
 ***************************************************************************/
/* NAND :: CMD_EXT_ADDRESS :: reserved0 [31:19] */
#define BCHP_NAND_CMD_EXT_ADDRESS_reserved0_MASK                   0xfff80000
#define BCHP_NAND_CMD_EXT_ADDRESS_reserved0_SHIFT                  19

/* NAND :: CMD_EXT_ADDRESS :: CS_SEL [18:16] */
#define BCHP_NAND_CMD_EXT_ADDRESS_CS_SEL_MASK                      0x00070000
#define BCHP_NAND_CMD_EXT_ADDRESS_CS_SEL_SHIFT                     16

/* NAND :: CMD_EXT_ADDRESS :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_CMD_EXT_ADDRESS_EXT_ADDRESS_MASK                 0x0000ffff
#define BCHP_NAND_CMD_EXT_ADDRESS_EXT_ADDRESS_SHIFT                0

/***************************************************************************
 *CMD_ADDRESS - Nand Flash Command Address
 ***************************************************************************/
/* NAND :: CMD_ADDRESS :: ADDRESS [31:00] */
#define BCHP_NAND_CMD_ADDRESS_ADDRESS_MASK                         0xffffffff
#define BCHP_NAND_CMD_ADDRESS_ADDRESS_SHIFT                        0

/***************************************************************************
 *CMD_END_ADDRESS - Nand Flash Command End Address
 ***************************************************************************/
/* NAND :: CMD_END_ADDRESS :: ADDRESS [31:00] */
#define BCHP_NAND_CMD_END_ADDRESS_ADDRESS_MASK                     0xffffffff
#define BCHP_NAND_CMD_END_ADDRESS_ADDRESS_SHIFT                    0

/***************************************************************************
 *CS_NAND_SELECT - Nand Flash EBI CS Select
 ***************************************************************************/
/* NAND :: CS_NAND_SELECT :: CS_LOCK [31:31] */
#define BCHP_NAND_CS_NAND_SELECT_CS_LOCK_MASK                      0x80000000
#define BCHP_NAND_CS_NAND_SELECT_CS_LOCK_SHIFT                     31

/* NAND :: CS_NAND_SELECT :: AUTO_DEVICE_ID_CONFIG [30:30] */
#define BCHP_NAND_CS_NAND_SELECT_AUTO_DEVICE_ID_CONFIG_MASK        0x40000000
#define BCHP_NAND_CS_NAND_SELECT_AUTO_DEVICE_ID_CONFIG_SHIFT       30

/* NAND :: CS_NAND_SELECT :: reserved0 [29:29] */
#define BCHP_NAND_CS_NAND_SELECT_reserved0_MASK                    0x20000000
#define BCHP_NAND_CS_NAND_SELECT_reserved0_SHIFT                   29

/* NAND :: CS_NAND_SELECT :: WR_PROTECT_BLK0 [28:28] */
#define BCHP_NAND_CS_NAND_SELECT_WR_PROTECT_BLK0_MASK              0x10000000
#define BCHP_NAND_CS_NAND_SELECT_WR_PROTECT_BLK0_SHIFT             28

/* NAND :: CS_NAND_SELECT :: reserved1 [27:16] */
#define BCHP_NAND_CS_NAND_SELECT_reserved1_MASK                    0x0fff0000
#define BCHP_NAND_CS_NAND_SELECT_reserved1_SHIFT                   16

/* NAND :: CS_NAND_SELECT :: EBI_CS_7_USES_NAND [15:15] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_7_USES_NAND_MASK           0x00008000
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_7_USES_NAND_SHIFT          15

/* NAND :: CS_NAND_SELECT :: EBI_CS_6_USES_NAND [14:14] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_6_USES_NAND_MASK           0x00004000
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_6_USES_NAND_SHIFT          14

/* NAND :: CS_NAND_SELECT :: EBI_CS_5_USES_NAND [13:13] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_USES_NAND_MASK           0x00002000
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_USES_NAND_SHIFT          13

/* NAND :: CS_NAND_SELECT :: EBI_CS_4_USES_NAND [12:12] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_USES_NAND_MASK           0x00001000
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_USES_NAND_SHIFT          12

/* NAND :: CS_NAND_SELECT :: EBI_CS_3_USES_NAND [11:11] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_USES_NAND_MASK           0x00000800
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_USES_NAND_SHIFT          11

/* NAND :: CS_NAND_SELECT :: EBI_CS_2_USES_NAND [10:10] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_USES_NAND_MASK           0x00000400
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_USES_NAND_SHIFT          10

/* NAND :: CS_NAND_SELECT :: EBI_CS_1_USES_NAND [09:09] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_USES_NAND_MASK           0x00000200
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_USES_NAND_SHIFT          9

/* NAND :: CS_NAND_SELECT :: EBI_CS_0_USES_NAND [08:08] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_USES_NAND_MASK           0x00000100
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_USES_NAND_SHIFT          8

/* NAND :: CS_NAND_SELECT :: EBI_CS_7_SEL [07:07] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_7_SEL_MASK                 0x00000080
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_7_SEL_SHIFT                7

/* NAND :: CS_NAND_SELECT :: EBI_CS_6_SEL [06:06] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_6_SEL_MASK                 0x00000040
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_6_SEL_SHIFT                6

/* NAND :: CS_NAND_SELECT :: EBI_CS_5_SEL [05:05] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_SEL_MASK                 0x00000020
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_SEL_SHIFT                5

/* NAND :: CS_NAND_SELECT :: EBI_CS_4_SEL [04:04] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_SEL_MASK                 0x00000010
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_SEL_SHIFT                4

/* NAND :: CS_NAND_SELECT :: EBI_CS_3_SEL [03:03] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_SEL_MASK                 0x00000008
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_SEL_SHIFT                3

/* NAND :: CS_NAND_SELECT :: EBI_CS_2_SEL [02:02] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_SEL_MASK                 0x00000004
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_SEL_SHIFT                2

/* NAND :: CS_NAND_SELECT :: EBI_CS_1_SEL [01:01] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_SEL_MASK                 0x00000002
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_SEL_SHIFT                1

/* NAND :: CS_NAND_SELECT :: EBI_CS_0_SEL [00:00] */
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK                 0x00000001
#define BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_SHIFT                0

/***************************************************************************
 *CS_NAND_XOR - Nand Flash EBI CS Address XOR with 1FC0 Control
 ***************************************************************************/
/* NAND :: CS_NAND_XOR :: reserved0 [31:08] */
#define BCHP_NAND_CS_NAND_XOR_reserved0_MASK                       0xffffff00
#define BCHP_NAND_CS_NAND_XOR_reserved0_SHIFT                      8

/* NAND :: CS_NAND_XOR :: EBI_CS_7_ADDR_1FC0_XOR [07:07] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_7_ADDR_1FC0_XOR_MASK          0x00000080
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_7_ADDR_1FC0_XOR_SHIFT         7

/* NAND :: CS_NAND_XOR :: EBI_CS_6_ADDR_1FC0_XOR [06:06] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_6_ADDR_1FC0_XOR_MASK          0x00000040
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_6_ADDR_1FC0_XOR_SHIFT         6

/* NAND :: CS_NAND_XOR :: EBI_CS_5_ADDR_1FC0_XOR [05:05] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_5_ADDR_1FC0_XOR_MASK          0x00000020
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_5_ADDR_1FC0_XOR_SHIFT         5

/* NAND :: CS_NAND_XOR :: EBI_CS_4_ADDR_1FC0_XOR [04:04] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_4_ADDR_1FC0_XOR_MASK          0x00000010
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_4_ADDR_1FC0_XOR_SHIFT         4

/* NAND :: CS_NAND_XOR :: EBI_CS_3_ADDR_1FC0_XOR [03:03] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_3_ADDR_1FC0_XOR_MASK          0x00000008
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_3_ADDR_1FC0_XOR_SHIFT         3

/* NAND :: CS_NAND_XOR :: EBI_CS_2_ADDR_1FC0_XOR [02:02] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_2_ADDR_1FC0_XOR_MASK          0x00000004
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_2_ADDR_1FC0_XOR_SHIFT         2

/* NAND :: CS_NAND_XOR :: EBI_CS_1_ADDR_1FC0_XOR [01:01] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_1_ADDR_1FC0_XOR_MASK          0x00000002
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_1_ADDR_1FC0_XOR_SHIFT         1

/* NAND :: CS_NAND_XOR :: EBI_CS_0_ADDR_1FC0_XOR [00:00] */
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_0_ADDR_1FC0_XOR_MASK          0x00000001
#define BCHP_NAND_CS_NAND_XOR_EBI_CS_0_ADDR_1FC0_XOR_SHIFT         0

/***************************************************************************
 *SPARE_AREA_READ_OFS_0 - Nand Flash Spare Area Read Bytes 0-3
 ***************************************************************************/
/* NAND :: SPARE_AREA_READ_OFS_0 :: BYTE_OFS_0 [31:24] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_0_MASK            0xff000000
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_0_SHIFT           24

/* NAND :: SPARE_AREA_READ_OFS_0 :: BYTE_OFS_1 [23:16] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_1_MASK            0x00ff0000
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_1_SHIFT           16

/* NAND :: SPARE_AREA_READ_OFS_0 :: BYTE_OFS_2 [15:08] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_2_MASK            0x0000ff00
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_2_SHIFT           8

/* NAND :: SPARE_AREA_READ_OFS_0 :: BYTE_OFS_3 [07:00] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_3_MASK            0x000000ff
#define BCHP_NAND_SPARE_AREA_READ_OFS_0_BYTE_OFS_3_SHIFT           0

/***************************************************************************
 *SPARE_AREA_READ_OFS_4 - Nand Flash Spare Area Read Bytes 4-7
 ***************************************************************************/
/* NAND :: SPARE_AREA_READ_OFS_4 :: BYTE_OFS_4 [31:24] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_4_MASK            0xff000000
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_4_SHIFT           24

/* NAND :: SPARE_AREA_READ_OFS_4 :: BYTE_OFS_5 [23:16] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_5_MASK            0x00ff0000
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_5_SHIFT           16

/* NAND :: SPARE_AREA_READ_OFS_4 :: BYTE_OFS_6 [15:08] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_6_MASK            0x0000ff00
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_6_SHIFT           8

/* NAND :: SPARE_AREA_READ_OFS_4 :: BYTE_OFS_7 [07:00] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_7_MASK            0x000000ff
#define BCHP_NAND_SPARE_AREA_READ_OFS_4_BYTE_OFS_7_SHIFT           0

/***************************************************************************
 *SPARE_AREA_READ_OFS_8 - Nand Flash Spare Area Read Bytes 8-11
 ***************************************************************************/
/* NAND :: SPARE_AREA_READ_OFS_8 :: BYTE_OFS_8 [31:24] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_8_MASK            0xff000000
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_8_SHIFT           24

/* NAND :: SPARE_AREA_READ_OFS_8 :: BYTE_OFS_9 [23:16] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_9_MASK            0x00ff0000
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_9_SHIFT           16

/* NAND :: SPARE_AREA_READ_OFS_8 :: BYTE_OFS_10 [15:08] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_10_MASK           0x0000ff00
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_10_SHIFT          8

/* NAND :: SPARE_AREA_READ_OFS_8 :: BYTE_OFS_11 [07:00] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_11_MASK           0x000000ff
#define BCHP_NAND_SPARE_AREA_READ_OFS_8_BYTE_OFS_11_SHIFT          0

/***************************************************************************
 *SPARE_AREA_READ_OFS_C - Nand Flash Spare Area Read Bytes 12-15
 ***************************************************************************/
/* NAND :: SPARE_AREA_READ_OFS_C :: BYTE_OFS_12 [31:24] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_12_MASK           0xff000000
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_12_SHIFT          24

/* NAND :: SPARE_AREA_READ_OFS_C :: BYTE_OFS_13 [23:16] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_13_MASK           0x00ff0000
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_13_SHIFT          16

/* NAND :: SPARE_AREA_READ_OFS_C :: BYTE_OFS_14 [15:08] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_14_MASK           0x0000ff00
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_14_SHIFT          8

/* NAND :: SPARE_AREA_READ_OFS_C :: BYTE_OFS_15 [07:00] */
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_15_MASK           0x000000ff
#define BCHP_NAND_SPARE_AREA_READ_OFS_C_BYTE_OFS_15_SHIFT          0

/***************************************************************************
 *SPARE_AREA_WRITE_OFS_0 - Nand Flash Spare Area Write Bytes 0-3
 ***************************************************************************/
/* NAND :: SPARE_AREA_WRITE_OFS_0 :: BYTE_OFS_0 [31:24] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_0_MASK           0xff000000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_0_SHIFT          24

/* NAND :: SPARE_AREA_WRITE_OFS_0 :: BYTE_OFS_1 [23:16] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_1_MASK           0x00ff0000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_1_SHIFT          16

/* NAND :: SPARE_AREA_WRITE_OFS_0 :: BYTE_OFS_2 [15:08] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_2_MASK           0x0000ff00
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_2_SHIFT          8

/* NAND :: SPARE_AREA_WRITE_OFS_0 :: BYTE_OFS_3 [07:00] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_3_MASK           0x000000ff
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_0_BYTE_OFS_3_SHIFT          0

/***************************************************************************
 *SPARE_AREA_WRITE_OFS_4 - Nand Flash Spare Area Write Bytes 4-7
 ***************************************************************************/
/* NAND :: SPARE_AREA_WRITE_OFS_4 :: BYTE_OFS_4 [31:24] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_4_MASK           0xff000000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_4_SHIFT          24

/* NAND :: SPARE_AREA_WRITE_OFS_4 :: BYTE_OFS_5 [23:16] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_5_MASK           0x00ff0000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_5_SHIFT          16

/* NAND :: SPARE_AREA_WRITE_OFS_4 :: BYTE_OFS_6 [15:08] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_6_MASK           0x0000ff00
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_6_SHIFT          8

/* NAND :: SPARE_AREA_WRITE_OFS_4 :: BYTE_OFS_7 [07:00] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_7_MASK           0x000000ff
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_4_BYTE_OFS_7_SHIFT          0

/***************************************************************************
 *SPARE_AREA_WRITE_OFS_8 - Nand Flash Spare Area Write Bytes 8-11
 ***************************************************************************/
/* NAND :: SPARE_AREA_WRITE_OFS_8 :: BYTE_OFS_8 [31:24] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_8_MASK           0xff000000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_8_SHIFT          24

/* NAND :: SPARE_AREA_WRITE_OFS_8 :: BYTE_OFS_9 [23:16] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_9_MASK           0x00ff0000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_9_SHIFT          16

/* NAND :: SPARE_AREA_WRITE_OFS_8 :: BYTE_OFS_10 [15:08] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_10_MASK          0x0000ff00
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_10_SHIFT         8

/* NAND :: SPARE_AREA_WRITE_OFS_8 :: BYTE_OFS_11 [07:00] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_11_MASK          0x000000ff
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_8_BYTE_OFS_11_SHIFT         0

/***************************************************************************
 *SPARE_AREA_WRITE_OFS_C - Nand Flash Spare Area Write Bytes 12-15
 ***************************************************************************/
/* NAND :: SPARE_AREA_WRITE_OFS_C :: BYTE_OFS_12 [31:24] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_12_MASK          0xff000000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_12_SHIFT         24

/* NAND :: SPARE_AREA_WRITE_OFS_C :: BYTE_OFS_13 [23:16] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_13_MASK          0x00ff0000
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_13_SHIFT         16

/* NAND :: SPARE_AREA_WRITE_OFS_C :: BYTE_OFS_14 [15:08] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_14_MASK          0x0000ff00
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_14_SHIFT         8

/* NAND :: SPARE_AREA_WRITE_OFS_C :: BYTE_OFS_15 [07:00] */
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_15_MASK          0x000000ff
#define BCHP_NAND_SPARE_AREA_WRITE_OFS_C_BYTE_OFS_15_SHIFT         0

/***************************************************************************
 *ACC_CONTROL - Nand Flash Access Control
 ***************************************************************************/
/* NAND :: ACC_CONTROL :: RD_ECC_EN [31:31] */
#define BCHP_NAND_ACC_CONTROL_RD_ECC_EN_MASK                       0x80000000
#define BCHP_NAND_ACC_CONTROL_RD_ECC_EN_SHIFT                      31

/* NAND :: ACC_CONTROL :: WR_ECC_EN [30:30] */
#define BCHP_NAND_ACC_CONTROL_WR_ECC_EN_MASK                       0x40000000
#define BCHP_NAND_ACC_CONTROL_WR_ECC_EN_SHIFT                      30

/* NAND :: ACC_CONTROL :: RD_ECC_BLK0_EN [29:29] */
#define BCHP_NAND_ACC_CONTROL_RD_ECC_BLK0_EN_MASK                  0x20000000
#define BCHP_NAND_ACC_CONTROL_RD_ECC_BLK0_EN_SHIFT                 29

/* NAND :: ACC_CONTROL :: FAST_PGM_RDIN [28:28] */
#define BCHP_NAND_ACC_CONTROL_FAST_PGM_RDIN_MASK                   0x10000000
#define BCHP_NAND_ACC_CONTROL_FAST_PGM_RDIN_SHIFT                  28

/* NAND :: ACC_CONTROL :: RD_ERASED_ECC_EN [27:27] */
#define BCHP_NAND_ACC_CONTROL_RD_ERASED_ECC_EN_MASK                0x08000000
#define BCHP_NAND_ACC_CONTROL_RD_ERASED_ECC_EN_SHIFT               27

/* NAND :: ACC_CONTROL :: reserved0 [26:26] */
#define BCHP_NAND_ACC_CONTROL_reserved0_MASK                       0x04000000
#define BCHP_NAND_ACC_CONTROL_reserved0_SHIFT                      26

/* NAND :: ACC_CONTROL :: WR_PREEMPT_EN [25:25] */
#define BCHP_NAND_ACC_CONTROL_WR_PREEMPT_EN_MASK                   0x02000000
#define BCHP_NAND_ACC_CONTROL_WR_PREEMPT_EN_SHIFT                  25

/* NAND :: ACC_CONTROL :: PAGE_HIT_EN [24:24] */
#define BCHP_NAND_ACC_CONTROL_PAGE_HIT_EN_MASK                     0x01000000
#define BCHP_NAND_ACC_CONTROL_PAGE_HIT_EN_SHIFT                    24

/* NAND :: ACC_CONTROL :: reserved1 [23:00] */
#define BCHP_NAND_ACC_CONTROL_reserved1_MASK                       0x00ffffff
#define BCHP_NAND_ACC_CONTROL_reserved1_SHIFT                      0

/***************************************************************************
 *CONFIG - Nand Flash Config
 ***************************************************************************/
/* NAND :: CONFIG :: CONFIG_LOCK [31:31] */
#define BCHP_NAND_CONFIG_CONFIG_LOCK_MASK                          0x80000000
#define BCHP_NAND_CONFIG_CONFIG_LOCK_SHIFT                         31

/* NAND :: CONFIG :: BLOCK_SIZE [30:28] */
#if CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_2_2
#define BCHP_NAND_CONFIG_BLOCK_SIZE_MASK                           0x70000000
#define BCHP_NAND_CONFIG_BLOCK_SIZE_SHIFT                          28
#elif CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_2_1
#define BCHP_NAND_CONFIG_BLOCK_SIZE_MASK                           0x30000000
#define BCHP_NAND_CONFIG_BLOCK_SIZE_SHIFT                          28
#endif
#define BCHP_NAND_CONFIG_BLOCK_SIZE_BK_SIZE_512KB                  3
#define BCHP_NAND_CONFIG_BLOCK_SIZE_BK_SIZE_128KB                  1
#define BCHP_NAND_CONFIG_BLOCK_SIZE_BK_SIZE_16KB                   0
#define BCHP_NAND_CONFIG_BLOCK_SIZE_BK_SIZE_8KB                    2
#define BCHP_NAND_CONFIG_BLOCK_SIZE_BK_SIZE_256KB                  4

/* NAND :: CONFIG :: DEVICE_SIZE [27:24] */
#define BCHP_NAND_CONFIG_DEVICE_SIZE_MASK                          0x0f000000
#define BCHP_NAND_CONFIG_DEVICE_SIZE_SHIFT                         24
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_4MB                  0
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_8MB                  1
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_16MB                 2
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_32MB                 3
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_64MB                 4
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_128MB                5
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_256MB                6
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_512MB                7
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_1GB                  8
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_2GB                  9
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_4GB                  10
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_8GB                  11
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_16GB                 12
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_32GB                 13
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_64GB                 14
#define BCHP_NAND_CONFIG_DEVICE_SIZE_DVC_SIZE_128GB                15

/* NAND :: CONFIG :: DEVICE_WIDTH [23:23] */
#define BCHP_NAND_CONFIG_DEVICE_WIDTH_MASK                         0x00800000
#define BCHP_NAND_CONFIG_DEVICE_WIDTH_SHIFT                        23
#define BCHP_NAND_CONFIG_DEVICE_WIDTH_DVC_WIDTH_8                  0
#define BCHP_NAND_CONFIG_DEVICE_WIDTH_DVC_WIDTH_16                 1

/* NAND :: CONFIG :: reserved0 [22:22] */
#define BCHP_NAND_CONFIG_reserved0_MASK                            0x00400000
#define BCHP_NAND_CONFIG_reserved0_SHIFT                           22

/* NAND :: CONFIG :: PAGE_SIZE [21:20] */
#if CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_2_2
#define BCHP_NAND_CONFIG_PAGE_SIZE_MASK                            0x00300000
#define BCHP_NAND_CONFIG_PAGE_SIZE_SHIFT                           20
#elif CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_2_1
#define BCHP_NAND_CONFIG_PAGE_SIZE_MASK                            0x40000000
#define BCHP_NAND_CONFIG_PAGE_SIZE_SHIFT                           30
#endif
#define BCHP_NAND_CONFIG_PAGE_SIZE_PG_SIZE_512                     0
#define BCHP_NAND_CONFIG_PAGE_SIZE_PG_SIZE_2KB                     1
#define BCHP_NAND_CONFIG_PAGE_SIZE_PG_SIZE_4KB                     2

/* NAND :: CONFIG :: reserved1 [19:19] */
#define BCHP_NAND_CONFIG_reserved1_MASK                            0x00080000
#define BCHP_NAND_CONFIG_reserved1_SHIFT                           19

/* NAND :: CONFIG :: FUL_ADR_BYTES [18:16] */
#define BCHP_NAND_CONFIG_FUL_ADR_BYTES_MASK                        0x00070000
#define BCHP_NAND_CONFIG_FUL_ADR_BYTES_SHIFT                       16

/* NAND :: CONFIG :: reserved2 [15:15] */
#define BCHP_NAND_CONFIG_reserved2_MASK                            0x00008000
#define BCHP_NAND_CONFIG_reserved2_SHIFT                           15

/* NAND :: CONFIG :: COL_ADR_BYTES [14:12] */
#define BCHP_NAND_CONFIG_COL_ADR_BYTES_MASK                        0x00007000
#define BCHP_NAND_CONFIG_COL_ADR_BYTES_SHIFT                       12

/* NAND :: CONFIG :: reserved3 [11:11] */
#define BCHP_NAND_CONFIG_reserved3_MASK                            0x00000800
#define BCHP_NAND_CONFIG_reserved3_SHIFT                           11

/* NAND :: CONFIG :: BLK_ADR_BYTES [10:08] */
#define BCHP_NAND_CONFIG_BLK_ADR_BYTES_MASK                        0x00000700
#define BCHP_NAND_CONFIG_BLK_ADR_BYTES_SHIFT                       8

/* NAND :: CONFIG :: reserved4 [07:00] */
#define BCHP_NAND_CONFIG_reserved4_MASK                            0x000000ff
#define BCHP_NAND_CONFIG_reserved4_SHIFT                           0

/***************************************************************************
 *TIMING_1 - Nand Flash Timing Parameters 1
 ***************************************************************************/
/* NAND :: TIMING_1 :: tWP [31:28] */
#define BCHP_NAND_TIMING_1_tWP_MASK                                0xf0000000
#define BCHP_NAND_TIMING_1_tWP_SHIFT                               28

/* NAND :: TIMING_1 :: tWH [27:24] */
#define BCHP_NAND_TIMING_1_tWH_MASK                                0x0f000000
#define BCHP_NAND_TIMING_1_tWH_SHIFT                               24

/* NAND :: TIMING_1 :: tRP [23:20] */
#define BCHP_NAND_TIMING_1_tRP_MASK                                0x00f00000
#define BCHP_NAND_TIMING_1_tRP_SHIFT                               20

/* NAND :: TIMING_1 :: tREH [19:16] */
#define BCHP_NAND_TIMING_1_tREH_MASK                               0x000f0000
#define BCHP_NAND_TIMING_1_tREH_SHIFT                              16

/* NAND :: TIMING_1 :: tCS [15:12] */
#define BCHP_NAND_TIMING_1_tCS_MASK                                0x0000f000
#define BCHP_NAND_TIMING_1_tCS_SHIFT                               12

/* NAND :: TIMING_1 :: tCLH [11:08] */
#define BCHP_NAND_TIMING_1_tCLH_MASK                               0x00000f00
#define BCHP_NAND_TIMING_1_tCLH_SHIFT                              8

/* NAND :: TIMING_1 :: tALH [07:04] */
#define BCHP_NAND_TIMING_1_tALH_MASK                               0x000000f0
#define BCHP_NAND_TIMING_1_tALH_SHIFT                              4

/* NAND :: TIMING_1 :: tADL [03:00] */
#define BCHP_NAND_TIMING_1_tADL_MASK                               0x0000000f
#define BCHP_NAND_TIMING_1_tADL_SHIFT                              0

/***************************************************************************
 *TIMING_2 - Nand Flash Timing Parameters 2
 ***************************************************************************/
/* NAND :: TIMING_2 :: reserved0 [31:12] */
#define BCHP_NAND_TIMING_2_reserved0_MASK                          0xfffff000
#define BCHP_NAND_TIMING_2_reserved0_SHIFT                         12

/* NAND :: TIMING_2 :: tWB [11:08] */
#define BCHP_NAND_TIMING_2_tWB_MASK                                0x00000f00
#define BCHP_NAND_TIMING_2_tWB_SHIFT                               8

/* NAND :: TIMING_2 :: tWHR [07:04] */
#define BCHP_NAND_TIMING_2_tWHR_MASK                               0x000000f0
#define BCHP_NAND_TIMING_2_tWHR_SHIFT                              4

/* NAND :: TIMING_2 :: tREAD [03:00] */
#define BCHP_NAND_TIMING_2_tREAD_MASK                              0x0000000f
#define BCHP_NAND_TIMING_2_tREAD_SHIFT                             0

/***************************************************************************
 *SEMAPHORE - Semaphore
 ***************************************************************************/
/* NAND :: SEMAPHORE :: reserved0 [31:08] */
#define BCHP_NAND_SEMAPHORE_reserved0_MASK                         0xffffff00
#define BCHP_NAND_SEMAPHORE_reserved0_SHIFT                        8

/* NAND :: SEMAPHORE :: semaphore_ctrl [07:00] */
#define BCHP_NAND_SEMAPHORE_semaphore_ctrl_MASK                    0x000000ff
#define BCHP_NAND_SEMAPHORE_semaphore_ctrl_SHIFT                   0

/***************************************************************************
 *FLASH_DEVICE_ID - Nand Flash Device ID
 ***************************************************************************/
/* NAND :: FLASH_DEVICE_ID :: BYTE_0 [31:24] */
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_0_MASK                      0xff000000
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_0_SHIFT                     24

/* NAND :: FLASH_DEVICE_ID :: BYTE_1 [23:16] */
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_1_MASK                      0x00ff0000
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_1_SHIFT                     16

/* NAND :: FLASH_DEVICE_ID :: BYTE_2 [15:08] */
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_2_MASK                      0x0000ff00
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_2_SHIFT                     8

/* NAND :: FLASH_DEVICE_ID :: BYTE_3 [07:00] */
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_3_MASK                      0x000000ff
#define BCHP_NAND_FLASH_DEVICE_ID_BYTE_3_SHIFT                     0

/***************************************************************************
 *BLOCK_LOCK_STATUS - Nand Flash Block Lock Status
 ***************************************************************************/
/* NAND :: BLOCK_LOCK_STATUS :: reserved0 [31:08] */
#define BCHP_NAND_BLOCK_LOCK_STATUS_reserved0_MASK                 0xffffff00
#define BCHP_NAND_BLOCK_LOCK_STATUS_reserved0_SHIFT                8

/* NAND :: BLOCK_LOCK_STATUS :: STATUS [07:00] */
#define BCHP_NAND_BLOCK_LOCK_STATUS_STATUS_MASK                    0x000000ff
#define BCHP_NAND_BLOCK_LOCK_STATUS_STATUS_SHIFT                   0

/***************************************************************************
 *INTFC_STATUS - Nand Flash Interface Status
 ***************************************************************************/
/* NAND :: INTFC_STATUS :: CTLR_READY [31:31] */
#define BCHP_NAND_INTFC_STATUS_CTLR_READY_MASK                     0x80000000
#define BCHP_NAND_INTFC_STATUS_CTLR_READY_SHIFT                    31

/* NAND :: INTFC_STATUS :: FLASH_READY [30:30] */
#define BCHP_NAND_INTFC_STATUS_FLASH_READY_MASK                    0x40000000
#define BCHP_NAND_INTFC_STATUS_FLASH_READY_SHIFT                   30

/* NAND :: INTFC_STATUS :: CACHE_VALID [29:29] */
#define BCHP_NAND_INTFC_STATUS_CACHE_VALID_MASK                    0x20000000
#define BCHP_NAND_INTFC_STATUS_CACHE_VALID_SHIFT                   29

/* NAND :: INTFC_STATUS :: SPARE_AREA_VALID [28:28] */
#define BCHP_NAND_INTFC_STATUS_SPARE_AREA_VALID_MASK               0x10000000
#define BCHP_NAND_INTFC_STATUS_SPARE_AREA_VALID_SHIFT              28

/* NAND :: INTFC_STATUS :: reserved0 [27:08] */
#define BCHP_NAND_INTFC_STATUS_reserved0_MASK                      0x0fffff00
#define BCHP_NAND_INTFC_STATUS_reserved0_SHIFT                     8

/* NAND :: INTFC_STATUS :: FLASH_STATUS [07:00] */
#define BCHP_NAND_INTFC_STATUS_FLASH_STATUS_MASK                   0x000000ff
#define BCHP_NAND_INTFC_STATUS_FLASH_STATUS_SHIFT                  0

/***************************************************************************
 *ECC_CORR_EXT_ADDR - ECC Correctable Error Extended Address
 ***************************************************************************/
/* NAND :: ECC_CORR_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_ECC_CORR_EXT_ADDR_reserved0_MASK                 0xfff80000
#define BCHP_NAND_ECC_CORR_EXT_ADDR_reserved0_SHIFT                19

/* NAND :: ECC_CORR_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_ECC_CORR_EXT_ADDR_CS_SEL_MASK                    0x00070000
#define BCHP_NAND_ECC_CORR_EXT_ADDR_CS_SEL_SHIFT                   16

/* NAND :: ECC_CORR_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_ECC_CORR_EXT_ADDR_EXT_ADDRESS_MASK               0x0000ffff
#define BCHP_NAND_ECC_CORR_EXT_ADDR_EXT_ADDRESS_SHIFT              0

/***************************************************************************
 *ECC_CORR_ADDR - ECC Correctable Error Address
 ***************************************************************************/
/* NAND :: ECC_CORR_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_ECC_CORR_ADDR_ADDRESS_MASK                       0xffffffff
#define BCHP_NAND_ECC_CORR_ADDR_ADDRESS_SHIFT                      0

/***************************************************************************
 *ECC_UNC_EXT_ADDR - ECC Uncorrectable Error Extended Address
 ***************************************************************************/
/* NAND :: ECC_UNC_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_ECC_UNC_EXT_ADDR_reserved0_MASK                  0xfff80000
#define BCHP_NAND_ECC_UNC_EXT_ADDR_reserved0_SHIFT                 19

/* NAND :: ECC_UNC_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_ECC_UNC_EXT_ADDR_CS_SEL_MASK                     0x00070000
#define BCHP_NAND_ECC_UNC_EXT_ADDR_CS_SEL_SHIFT                    16

/* NAND :: ECC_UNC_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_ECC_UNC_EXT_ADDR_EXT_ADDRESS_MASK                0x0000ffff
#define BCHP_NAND_ECC_UNC_EXT_ADDR_EXT_ADDRESS_SHIFT               0

/***************************************************************************
 *ECC_UNC_ADDR - ECC Uncorrectable Error Address
 ***************************************************************************/
/* NAND :: ECC_UNC_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_ECC_UNC_ADDR_ADDRESS_MASK                        0xffffffff
#define BCHP_NAND_ECC_UNC_ADDR_ADDRESS_SHIFT                       0

/***************************************************************************
 *FLASH_READ_EXT_ADDR - Flash Read Data Extended Address
 ***************************************************************************/
/* NAND :: FLASH_READ_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_FLASH_READ_EXT_ADDR_reserved0_MASK               0xfff80000
#define BCHP_NAND_FLASH_READ_EXT_ADDR_reserved0_SHIFT              19

/* NAND :: FLASH_READ_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_FLASH_READ_EXT_ADDR_CS_SEL_MASK                  0x00070000
#define BCHP_NAND_FLASH_READ_EXT_ADDR_CS_SEL_SHIFT                 16

/* NAND :: FLASH_READ_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_FLASH_READ_EXT_ADDR_EXT_ADDRESS_MASK             0x0000ffff
#define BCHP_NAND_FLASH_READ_EXT_ADDR_EXT_ADDRESS_SHIFT            0

/***************************************************************************
 *FLASH_READ_ADDR - Flash Read Data Address
 ***************************************************************************/
/* NAND :: FLASH_READ_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_FLASH_READ_ADDR_ADDRESS_MASK                     0xffffffff
#define BCHP_NAND_FLASH_READ_ADDR_ADDRESS_SHIFT                    0

/***************************************************************************
 *PROGRAM_PAGE_EXT_ADDR - Page Program Extended Address
 ***************************************************************************/
/* NAND :: PROGRAM_PAGE_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_reserved0_MASK             0xfff80000
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_reserved0_SHIFT            19

/* NAND :: PROGRAM_PAGE_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_CS_SEL_MASK                0x00070000
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_CS_SEL_SHIFT               16

/* NAND :: PROGRAM_PAGE_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_EXT_ADDRESS_MASK           0x0000ffff
#define BCHP_NAND_PROGRAM_PAGE_EXT_ADDR_EXT_ADDRESS_SHIFT          0

/***************************************************************************
 *PROGRAM_PAGE_ADDR - Page Program Address
 ***************************************************************************/
/* NAND :: PROGRAM_PAGE_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_PROGRAM_PAGE_ADDR_ADDRESS_MASK                   0xffffffff
#define BCHP_NAND_PROGRAM_PAGE_ADDR_ADDRESS_SHIFT                  0

/***************************************************************************
 *COPY_BACK_EXT_ADDR - Copy Back Extended Address
 ***************************************************************************/
/* NAND :: COPY_BACK_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_COPY_BACK_EXT_ADDR_reserved0_MASK                0xfff80000
#define BCHP_NAND_COPY_BACK_EXT_ADDR_reserved0_SHIFT               19

/* NAND :: COPY_BACK_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_COPY_BACK_EXT_ADDR_CS_SEL_MASK                   0x00070000
#define BCHP_NAND_COPY_BACK_EXT_ADDR_CS_SEL_SHIFT                  16

/* NAND :: COPY_BACK_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_COPY_BACK_EXT_ADDR_EXT_ADDRESS_MASK              0x0000ffff
#define BCHP_NAND_COPY_BACK_EXT_ADDR_EXT_ADDRESS_SHIFT             0

/***************************************************************************
 *COPY_BACK_ADDR - Copy Back Address
 ***************************************************************************/
/* NAND :: COPY_BACK_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_COPY_BACK_ADDR_ADDRESS_MASK                      0xffffffff
#define BCHP_NAND_COPY_BACK_ADDR_ADDRESS_SHIFT                     0

/***************************************************************************
 *BLOCK_ERASE_EXT_ADDR - Block Erase Extended Address
 ***************************************************************************/
/* NAND :: BLOCK_ERASE_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_reserved0_MASK              0xfff80000
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_reserved0_SHIFT             19

/* NAND :: BLOCK_ERASE_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_CS_SEL_MASK                 0x00070000
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_CS_SEL_SHIFT                16

/* NAND :: BLOCK_ERASE_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_EXT_ADDRESS_MASK            0x0000ffff
#define BCHP_NAND_BLOCK_ERASE_EXT_ADDR_EXT_ADDRESS_SHIFT           0

/***************************************************************************
 *BLOCK_ERASE_ADDR - Block Erase Address
 ***************************************************************************/
/* NAND :: BLOCK_ERASE_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_BLOCK_ERASE_ADDR_ADDRESS_MASK                    0xffffffff
#define BCHP_NAND_BLOCK_ERASE_ADDR_ADDRESS_SHIFT                   0

/***************************************************************************
 *INV_READ_EXT_ADDR - Flash Invalid Data Extended Address
 ***************************************************************************/
/* NAND :: INV_READ_EXT_ADDR :: reserved0 [31:19] */
#define BCHP_NAND_INV_READ_EXT_ADDR_reserved0_MASK                 0xfff80000
#define BCHP_NAND_INV_READ_EXT_ADDR_reserved0_SHIFT                19

/* NAND :: INV_READ_EXT_ADDR :: CS_SEL [18:16] */
#define BCHP_NAND_INV_READ_EXT_ADDR_CS_SEL_MASK                    0x00070000
#define BCHP_NAND_INV_READ_EXT_ADDR_CS_SEL_SHIFT                   16

/* NAND :: INV_READ_EXT_ADDR :: EXT_ADDRESS [15:00] */
#define BCHP_NAND_INV_READ_EXT_ADDR_EXT_ADDRESS_MASK               0x0000ffff
#define BCHP_NAND_INV_READ_EXT_ADDR_EXT_ADDRESS_SHIFT              0

/***************************************************************************
 *INV_READ_ADDR - Flash Invalid Data Address
 ***************************************************************************/
/* NAND :: INV_READ_ADDR :: ADDRESS [31:00] */
#define BCHP_NAND_INV_READ_ADDR_ADDRESS_MASK                       0xffffffff
#define BCHP_NAND_INV_READ_ADDR_ADDRESS_SHIFT                      0

/***************************************************************************
 *BLK_WR_PROTECT - Block Write Protect Enable and Size for EBI_CS0b
 ***************************************************************************/
/* NAND :: BLK_WR_PROTECT :: BLK_END_ADDR [31:00] */
#define BCHP_NAND_BLK_WR_PROTECT_BLK_END_ADDR_MASK                 0xffffffff
#define BCHP_NAND_BLK_WR_PROTECT_BLK_END_ADDR_SHIFT                0

/***************************************************************************
 *FLASH_CACHE%i - Flash Cache Buffer Read Access
 ***************************************************************************/
#define BCHP_NAND_FLASH_CACHEi_ARRAY_BASE                          BRCMNAND_CACHE_BASE
#define BCHP_NAND_FLASH_CACHEi_ARRAY_START                         0
#define BCHP_NAND_FLASH_CACHEi_ARRAY_END                           127
#define BCHP_NAND_FLASH_CACHEi_ARRAY_ELEMENT_SIZE                  32

/***************************************************************************
 *FLASH_CACHE%i - Flash Cache Buffer Read Access
 ***************************************************************************/
/* NAND :: FLASH_CACHEi :: WORD [31:00] */
#define BCHP_NAND_FLASH_CACHEi_WORD_MASK                           0xffffffff
#define BCHP_NAND_FLASH_CACHEi_WORD_SHIFT                          0

/***************************************************************************
 *Definitions not supported by this version NAND controller but defined
 *in order to compile
 ***************************************************************************/
#define BCHP_NAND_FLASH_DEVICE_ID_EXT           (BCHP_NAND_REG_END + 4)

#define BCHP_NAND_ACC_CONTROL_CS1_PARTIAL_PAGE_EN_MASK             0
#define BCHP_NAND_ACC_CONTROL_CS1_PARTIAL_PAGE_EN_SHIFT            0
#define BCHP_NAND_ACC_CONTROL_PARTIAL_PAGE_EN_MASK                 0
#define BCHP_NAND_ACC_CONTROL_PARTIAL_PAGE_EN_SHIFT                0
#define BCHP_NAND_ACC_CONTROL_ECC_LEVEL_0_MASK                     0
#define BCHP_NAND_ACC_CONTROL_ECC_LEVEL_0_SHIFT                    0
#define BCHP_NAND_ACC_CONTROL_ECC_LEVEL_MASK                       0
#define BCHP_NAND_ACC_CONTROL_ECC_LEVEL_SHIFT                      0
#define BCHP_NAND_ACC_CONTROL_SPARE_AREA_SIZE_0_MASK               0
#define BCHP_NAND_ACC_CONTROL_SPARE_AREA_SIZE_0_SHIFT              0
#define BCHP_NAND_ACC_CONTROL_SPARE_AREA_SIZE_MASK                 0
#define BCHP_NAND_ACC_CONTROL_SPARE_AREA_SIZE_SHIFT                0

#endif /* #ifndef BCHP_NAND_21_22_H__ */

/* End of File */
#endif
