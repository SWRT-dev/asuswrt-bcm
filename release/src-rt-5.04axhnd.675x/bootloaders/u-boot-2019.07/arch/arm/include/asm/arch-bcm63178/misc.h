/* SPDX-License-Identifier: GPL-2.0+
 *
 *  Copyright 2019 Broadcom Ltd.
 */

#ifndef _63178_MISC_H
#define _63178_MISC_H

#define MISC_BASE          0xff802600

/*
 * Misc Register Set Definitions.
 */
typedef struct Misc {
    uint32_t  miscStrapBus;                       /* 0x00 */
#define MISC_STRAP_BUS_BOOT_SEL_SHIFT           0
#define MISC_STRAP_BUS_BOOT_SEL_MASK            (0x38 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_SPI_NOR             (0x38 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_SPI_NAND            (0x28 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_SEL_NAND_MASK       (0x20 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND                (0x00 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_SEL_PAGE_MASK       (0x18 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_2K_PAGE        (0x00 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_4K_PAGE        (0x08 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_8K_PAGE        (0x10 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_512_PAGE       (0x18 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_SEL_ECC_MASK        (0x7 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_DISABLE    (0x0 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_1_BIT      (0x1 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_4_BIT      (0x2 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_8_BIT      (0x3 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_12_BIT     (0x4 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_24_BIT     (0x5 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_40_BIT     (0x6 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_BOOT_NAND_ECC_60_BIT     (0x7 << MISC_STRAP_BUS_BOOT_SEL_SHIFT)
#define MISC_STRAP_BUS_PCIE0_RC_MODE            (0x1 << 6)
#define MISC_STRAP_BUS_CPU_SLOW_FREQ_SHIFT      9
#define MISC_STRAP_BUS_CPU_SLOW_FREQ            (0x1 << MISC_STRAP_BUS_CPU_SLOW_FREQ_SHIFT)
#define MISC_STRAP_BUS_BOOTROM_BOOT             (0x1 << 11)
#define MISC_STRAP_BUS_B53_NO_BOOT              (0x1 << 12) /* 1-PMC boot A53, 0-A53 boots at POR */

    uint32_t  miscStrapOverride;                  /* 0x04 */
    uint32_t  miscMaskUBUSErr;                    /* 0x08 */
    uint32_t  miscPeriphCtrl;                     /* 0x0c */
    uint32_t  miscSPImasterCtrl;                  /* 0x10 */
    uint32_t  miscDierevid;                       /* 0x14 */
    uint32_t  miscPeriphMiscCtrl;                 /* 0x18 */
    uint32_t  miscPeriphMiscStat;                 /* 0x1c */
    uint32_t  miscSoftResetB;                     /* 0x20 */
    uint32_t  reserved0;                          /* 0x24 */
    uint32_t  miscSWdebugNW[2];                   /* 0x28 */
    uint32_t  miscWDresetCtrl;                    /* 0x30 */
} Misc;

#define MISC ((volatile Misc * const) MISC_BASE)

// PERF
typedef struct PerfControl { /* GenInt */
     uint32_t        RevID;             /* (00) word 0 */
#define CHIP_ID_SHIFT   12
#define CHIP_ID_MASK    (0xfffff << CHIP_ID_SHIFT)
#define REV_ID_MASK     0xff
} PerfControl;

#define PERF_BASE              0xff800000
#define PERF ((volatile PerfControl * const) PERF_BASE)


typedef struct TopControl {
   uint32_t      reserved_00;        // 0x0
   uint32_t      Rgmii1PadCtl;       // 0x4
#define MISC_XMII_PAD_MODEHV                    (1 << 6)
#define MISC_XMII_PAD_IND                       (1 << 5) 
#define MISC_XMII_PAD_SEL_GMII                  (1 << 4)
#define MISC_XMII_PAD_AMP_EN                    (1 << 3)
#define MISC_XMII_PAD_DRIVE_STRENGTH_SHIFT      0
#define MISC_XMII_PAD_DRIVE_STRENGTH_MASK       (0x7<<MISC_XMII_PAD_DRIVE_STRENGTH_SHIFT)
   uint32_t      reserved_08;        // 0x8
   uint32_t      reserved_0c;        // 0xc
   uint32_t      MiiPullCtl;         // 0x10
   uint32_t      Rgmii1PullCtl;      // 0x14
   uint32_t      Rgmii2PullCtl;      // 0x18
   uint32_t      Rgmii3PullCtl;      // 0x1c
   uint32_t      SgmiiFiberDetect;   // 0x20
   uint32_t      DgSensePadCtl;      // 0x24
#define DG_CTRL_SHIFT   4
#define DG_EN_SHIFT     3
#define DG_TRIM_SHIFT   0
   uint32_t      TpDirOverride0;     // 0x28
   uint32_t      TpDirOverride1;     // 0x2c
   uint32_t      RescalReadData0;    // 0x30
   uint32_t      RescalReadData1;    // 0x34
   uint32_t      reserved0;          // 0x38 
   uint32_t      ResetStatus;        // 0x3c 
#define PCIE_RESET_STATUS       0x10000000
#define SW_RESET_STATUS         0x20000000
#define HW_RESET_STATUS         0x40000000
#define POR_RESET_STATUS        0x80000000
#define RESET_STATUS_MASK       0xF0000000
   uint32_t      TodSync;            // 0x40
   uint32_t      Pm0Pm1RescalSts;    // 0x44
   uint32_t      Pm2Pm3RescalSts;    // 0x48
   uint32_t      SgbRescalSts;       // 0x4c
   uint32_t      Pm0Pm1RescalCfg;    // 0x50
   uint32_t      Pm2Pm3RescalCfg;    // 0x54
   uint32_t      SgbRescalCfg;       // 0x58
   uint32_t      Pm0Pm1TmonCfg;      // 0x5c
   uint32_t      Pm2Pm3TmonCfg;      // 0x60
   uint32_t      SgbTmonCfg;         // 0x64
   uint32_t      MdioMasterSelect;   // 0x68
   uint32_t      SwControlReg;       // 0x6c
   uint32_t      Reg2P5VDectCtrl;    // 0x70
   uint32_t      OrionIntPending;    // 0x74
   uint32_t      DslClockSample;     // 0x78
   uint32_t      LdoCtl;             // 0x7c
#define LDO_VREG_CTRL_EN           0x400000
#define LDO_VREG_CTRL_SHIFT        1
#define LDO_VREG_CTRL_MASK         (0x1fffff << LDO_VREG_CTRL_SHIFT)
#define LDO_VREG_CTRL_TRIM_SHIFT   2
#define LDO_VREG_CTRL_TRIM_MASK    (0xf << LDO_VREG_CTRL_TRIM_SHIFT)
#define LDO_VREG_CTRL_SELECT_SHIFT 6
#define LDO_VREG_CTRL_SELECT_MASK  (0xf << LDO_VREG_CTRL_SELECT_SHIFT)
#define LDO_VREG_CTRL_PWRDN        0x1
} TopControl;

#define TOP_CONTROL_BASE           0xff85a000
#define TOPCTRL ((volatile TopControl * const) TOP_CONTROL_BASE)

#endif
