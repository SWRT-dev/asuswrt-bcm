/*
<:copyright-BRCM:2013:DUAL/GPL:standard 

   Copyright (c) 2013 Broadcom 
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

/*****************************************************************************
 *  Description:
 *      This contains header for PMC driver.
 *****************************************************************************/

#ifndef PMC_DRV_H
#define PMC_DRV_H

#ifndef _LANGUAGE_ASSEMBLY
#include <bcmtypes.h>
#endif

#if defined(_BCM963138_) || defined(CONFIG_BCM963138) || defined(_BCM963148_) || defined(CONFIG_BCM963148) || defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM96858_) || defined(CONFIG_BCM96858)
#define PMC_LITTLE_ENDIAN	1
#endif

/* there are 32 DQM, since REPLY DQM will always be one after the REQUEST
 * DQM, we should use use 0 to 30 for REQ DQM, so RPL DQM will be 1 to 31 */
#if defined(_BCM96838_) || defined(CONFIG_BCM96838)
#define PMC_DQM_REQ_NUM		1
#else
/* 63138 has pair of DQM#0+DQM#1, #2+#3, #4+#5, and #6+#7.  We will use
 * DQM#0+DQM#1 pair */
#define PMC_DQM_REQ_NUM		0
#endif

#define PMC_DQM_RPL_NUM		(PMC_DQM_REQ_NUM + 1)
#define PMC_DQM_RPL_STS		(1 << PMC_DQM_RPL_NUM)


#if defined(_BCM96838_) || defined(CONFIG_BCM96838)
#define   PMB_BUS_MAX                   2
//--------- BPCM device addressing and structure of zones in the BPCM devices ------------------------
#define   PMB_ADDR_APM                  0       // apm_fpm_top-apm_top - No FS CTL registers
#define   PMB_ZONES_APM                 5
    enum {
        APM_Zone_Main,
        APM_Zone_Audio,
        APM_Zone_PCM,
        APM_Zone_HVG,
        APM_Zone_BMU,
    };
    
//--------- SOFT Reset bits for APM ------------------------
#define   BPCM_APM_SRESET_HARDRST_N   0x00000040	    
#define   BPCM_APM_SRESET_AUDIO_N     0x00000020	
#define   BPCM_APM_SRESET_PCM_N       0x00000010
#define   BPCM_APM_SRESET_HVGA_N      0x00000008
#define   BPCM_APM_SRESET_HVGB_N      0x00000004
#define   BPCM_APM_SRESET_BMU_N       0x00000002
#define   BPCM_APM_SRESET_200_N       0x00000001

    
#define   PMB_ADDR_FPM                  1      // apm_fpm_top-fpm_top
#define   PMB_ZONES_FPM                 1
    enum {
        FPM_Zone_Main,
    };
	
#define   PMB_ADDR_CHIP_CLKRST          2      // chip_clkrst
#define   PMB_ZONES_CHIP_CLKRST 0

#define   PMB_ADDR_CPU4355_BCM_MIPS0    3      // cpu4355_bcm_mips0 - No FS CTL register
#define   PMB_ZONES_CPU4355_BCM_MIPS0   1
    enum {
        Viper_Zone_Main,
    };
	
#define   PMB_ADDR_WAN            		4		// wan_top_wrapper
#define   PMB_ZONES_WAN            		4
    enum {
        WAN_Zone_0,
        WAN_Zone_1,
        WAN_Zone_2,
        WAN_Zone_3,
    };
	
#define   PMB_ADDR_RDP		            5      // rdp_top_wrapper
#define   PMB_ZONES_RDP		            2
    enum {
        RDP_Zone_0,
        RDP_Zone_1,
   };
   
#define   PMB_ADDR_MEMC       14     // memc23_sj_300_16b_fc_40g
#define   PMB_ZONES_MEMC       1
    enum {
        MEMC_Zone_Main,
    };
	
#define   PMB_ADDR_PERIPH               16     // periph_top -  no FS CTL registers
#define   PMB_ZONES_PERIPH               3
    enum {
        PERIPH_Zone_Main,
        PERIPH_Zone_HS_SPIM,
        PERIPH_Zone_TBUS,
    };
	
#define   PMB_ADDR_UGB                  17     // ubus_gisb_bridge_top - FS CTL register
#define   PMB_ZONES_UGB                  1
    enum {
        UGB_Zone_0,
    };
	
#define   PMB_ADDR_SYSPLL0              23     // clkrst_testif-pmb_syspll0

#define   PMB_ADDR_SYSPLL1              24     // clkrst_testif-pmb_syspll1

#define   PMB_ADDR_SYSPLL2              25     // clkrst_testif-pmb_syspll2

#define   PMB_ADDR_LCPLL0				26     // clkrst_testif-pmb_syspll3

#define   PMB_ADDR_LCPLL1				27     // clkrst_testif-pmb_syspll4

#define   PMB_ADDR_UNIMAC_MBDMA         30     // unimac_mbdma_top - FS CTL register in all zones
#define   PMB_ZONES_UNIMAC_MBDMA 3
    enum {
        UNIMAC_MBDMA_Zone_Top,
        UNIMAC_MBDMA_Zone_Unimac0,
        UNIMAC_MBDMA_Zone_Unimac1,
    };
	
#define   PMB_ADDR_PCIE_UBUS_0          33     // pcie_2x_top-pcie_ubus_top_0 - FS CTL register
#define   PMB_ADDR_PCIE0                PMB_ADDR_PCIE_UBUS_0
#define   PMB_ZONES_PCIE_UBUS_0          1
    enum {
        PCIE_UBUS_0_Zone_0,
    };
	
#define   PMB_ADDR_PCIE_UBUS_1          34     // pcie_2x_top-pcie_ubus_top_1 - FS CTL register
#define   PMB_ADDR_PCIE1                PMB_ADDR_PCIE_UBUS_1
#define   PMB_ZONES_PCIE_UBUS_1          1
    enum {
        PCIE_UBUS_1_Zone_0,
    };
	
#define   PMB_ADDR_USB30_2X             35 | (1<<8)     // usb_top - no FS CTL registers
#define   PMB_ZONES_USB30_2X             3
    enum {
        USB30_2X_Zone_Common,
        USB30_2X_Zone_USB_Host,
        USB30_2X_Zone_USB_Device,
    };
	
#define   PMB_ADDR_PSAB                 38     // ubus2_pipestage_A_B_top
#define   PMB_ZONES_PSAB                 1
    enum {
        PSAB_Zone_0,
    };
	
#define   PMB_ADDR_PSBC                 39     // ubus2_pipestage_B_C_top
#define   PMB_ZONES_PSBC                 1
    enum {
        PSBC_Zone_0,
    };
	
#define   PMB_ADDR_EGPHY                40     // egphy_wrapper
#define   PMB_ZONES_EGPHY                1
    enum {
        EGPHY_Zone_0,
    };

#endif /* defined(_BCM96838_) || defined(CONFIG_BCM96838) */

#if defined(_BCM963138_) || defined(CONFIG_BCM963138)
#define PMB_BUS_MAX			2
#define PMB_BUS_ID_SHIFT		8

#define PMB_BUS_APM			1
#define PMB_ADDR_APM			(0 | PMB_BUS_APM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_APM			5

//--------- SOFT Reset bits for APM ------------------------
#define   BPCM_APM_SRESET_HARDRST_N   0x00000040	    
#define   BPCM_APM_SRESET_AUDIO_N     0x00000020	
#define   BPCM_APM_SRESET_PCM_N       0x00000010
#define   BPCM_APM_SRESET_HVGA_N      0x00000008
#define   BPCM_APM_SRESET_HVGB_N      0x00000004
#define   BPCM_APM_SRESET_BMU_N       0x00000002
#define   BPCM_APM_SRESET_200_N       0x00000001

#define PMB_BUS_SWITCH			1
#define PMB_ADDR_SWITCH			(1 | PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SWITCH		3

#define PMB_BUS_CHIP_CLKRST		1
#define PMB_ADDR_CHIP_CLKRST		(2 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST		0

#define PMB_BUS_SATA			0
#define PMB_ADDR_SATA			(3 | PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SATA			1

#define PMB_BUS_AIP			0
#define PMB_ADDR_AIP			(4 | PMB_BUS_AIP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_AIP			1

#define PMB_BUS_DECT_UBUS		0
#define PMB_ADDR_DECT_UBUS		(5 | PMB_BUS_DECT_UBUS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_DECT_UBUS		1

#define PMB_BUS_SAR			1
#define PMB_ADDR_SAR			(6 | PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SAR			1

#define PMB_BUS_RDP			1
#define PMB_ADDR_RDP			(7 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDP			2

#define PMB_BUS_MEMC			0
#define PMB_ADDR_MEMC			(8 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC			1

#define PMB_BUS_PERIPH			0
#define PMB_ADDR_PERIPH			(9 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH		3

#define PMB_BUS_SYSPLL			1
#define PMB_ADDR_SYSPLL			(10 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL		0

#define PMB_BUS_RDPPLL			1
#define PMB_ADDR_RDPPLL			(11 | PMB_BUS_RDPPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDPPLL		0

#define PMB_BUS_SYSPLL2			0
#define PMB_ADDR_SYSPLL2		(12 | PMB_BUS_SYSPLL2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL2		0

#define PMB_BUS_SYSPLL3			0
#define PMB_ADDR_SYSPLL3		(13 | PMB_BUS_SYSPLL3 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL3		0

#define PMB_BUS_SYSPLL4			0
#define PMB_ADDR_SYSPLL4		(14 | PMB_BUS_SYSPLL4 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL4		0

#define PMB_BUS_PCIE0			0
#define PMB_ADDR_PCIE0			(15 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0			1

#define PMB_BUS_PCIE1			0
#define PMB_ADDR_PCIE1			(16 | PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE1			1

#define PMB_BUS_USB30_2X		1
#define PMB_ADDR_USB30_2X		(17 | PMB_BUS_USB30_2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB30_2X		4

#define PMB_BUS_PSAB			0
#define PMB_ADDR_PSAB			(18 | PMB_BUS_PSAB << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PSAB			1	// not shown in spreadsheet

#define PMB_BUS_PSBC			0
#define PMB_ADDR_PSBC			(19 | PMB_BUS_PSBC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PSBC			1	// not shown in spreadsheet

#define PMB_BUS_EGPHY			0
#define PMB_ADDR_EGPHY			(20 | PMB_BUS_EGPHY << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_EGPHY			1	// not shown in spreadsheet

#define PMB_BUS_VDSL3_MIPS		0
#define PMB_ADDR_VDSL3_MIPS		(21 | PMB_BUS_VDSL3_MIPS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_MIPS		1

#define PMB_BUS_VDSL3_CORE		0
#define PMB_ADDR_VDSL3_CORE		(22 | PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_CORE		3

#define AFEPLL_PMB_BUS_VDSL3_CORE	0
#define AFEPLL_PMB_ADDR_VDSL3_CORE	(23 | AFEPLL_PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define AFEPLL_PMB_ZONES_VDSL3_CORE	0

#define UBUS_PMB_BUS_VDSL3_CORE		PMB_BUS_VDSL3_CORE
#define UBUS_PMB_ADDR_VDSL3_CORE	(24 | UBUS_PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_VDSL3_CORE	0

#define UBUS_PMB_BUS_VDSL3_MIPS		PMB_BUS_VDSL3_MIPS
#define UBUS_PMB_ADDR_VDSL3_MIPS	(25 | UBUS_PMB_BUS_VDSL3_MIPS << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_VDSL3_MIPS	0

#define UBUS_PMB_BUS_DECT		PMB_BUS_DECT_UBUS
#define UBUS_PMB_ADDR_DECT		(26 | UBUS_PMB_BUS_DECT << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_DECT		0

#define UBUS_PMB_BUS_ARM		PMB_BUS_AIP
#define UBUS_PMB_ADDR_ARM		(27 | UBUS_PMB_BUS_ARM << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_ARM		0

#define UBUS_PMB_BUS_DAP		PMB_BUS_AIP
#define UBUS_PMB_ADDR_DAP		(28 | UBUS_PMB_BUS_DAP << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_DAP		0

#define UBUS_CFG0_PMB_BUS_SAR		PMB_BUS_SAR
#define UBUS_CFG0_PMB_ADDR_SAR		(29 | UBUS_CFG0_PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG0_PMB_ZONES_SAR		0

#define UBUS_CFG1_PMB_BUS_SAR		PMB_BUS_SAR
#define UBUS_CFG1_PMB_ADDR_SAR		(30 | UBUS_CFG1_PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG1_PMB_ZONES_SAR		0

#define UBUS_CFG_PMB_BUS_DBR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_DBR		(31 | UBUS_CFG_PMB_BUS_DBR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_DBR		0

#define UBUS_CFG_PMB_BUS_RABR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_RABR		(32 | UBUS_CFG_PMB_BUS_RABR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_RABR		0

#define UBUS_CFG_PMB_BUS_RBBR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_RBBR		(33 | UBUS_CFG_PMB_BUS_RBBR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_RBBR		0

#define UBUS_CFG_PMB_BUS_APM 		PMB_BUS_APM
#define UBUS_CFG_PMB_ADDR_APM 		(34 | UBUS_CFG_PMB_BUS_APM << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_APM 		0

#define UBUS_CFG_PMB_BUS_PCIE0 		PMB_BUS_PCIE0
#define UBUS_CFG_PMB_ADDR_PCIE0 	(35 | UBUS_CFG_PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PCIE0 	0

#define UBUS_CFG_PMB_BUS_PCIE1 		PMB_BUS_PCIE1
#define UBUS_CFG_PMB_ADDR_PCIE1 	(36 | UBUS_CFG_PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PCIE1 	0

#define UBUS_CFG_PMB_BUS_USBH 		PMB_BUS_USB30_2X
#define UBUS_CFG_PMB_ADDR_USBH 		(37 | UBUS_CFG_PMB_BUS_USBH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_USBH 	0

#define UBUS_CFG_PMB_BUS_USBD 		PMB_BUS_USB30_2X
#define UBUS_CFG_PMB_ADDR_USBD 		(38 | UBUS_CFG_PMB_BUS_USBD << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_USBD 	0

#define UBUS_CFG_PMB_BUS_SWITCH		PMB_BUS_SWITCH
#define UBUS_CFG_PMB_ADDR_SWITCH	(39 | UBUS_CFG_PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_SWITCH	0

#define UBUS_CFG_PMB_BUS_PERIPH		PMB_BUS_PERIPH
#define UBUS_CFG_PMB_ADDR_PERIPH	(40 | UBUS_CFG_PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PERIPH	0

#define UBUS_CFG_PMB_BUS_SATA  		PMB_BUS_SATA
#define UBUS_CFG_PMB_ADDR_SATA  	(41 | UBUS_CFG_PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_SATA  	0


/* define Zone enum for each block here */
#ifndef _LANGUAGE_ASSEMBLY
enum {
    APM_Zone_Main,
    APM_Zone_Audio,
    APM_Zone_PCM,
    APM_Zone_HVG,
    APM_Zone_BMU,
};
#endif    

#endif

#if defined(_BCM963381_) || defined(CONFIG_BCM963381) 
#define PMB_BUS_MAX			2
#define PMB_BUS_ID_SHIFT		8

#define PMB_BUS_USB2X		        0
#define PMB_ADDR_USB2X		        (0 | PMB_BUS_USB2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB2X	                3

#define PMB_BUS_USB30		        0
#define PMB_ADDR_USB30		        (1 | PMB_BUS_USB30 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB30	                1

#define PMB_BUS_PCIE0			0
#define PMB_ADDR_PCIE0			(2 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0			1

#define PMB_BUS_MIPS			0
#define PMB_ADDR_MIPS			(3 | PMB_BUS_MIPS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MIPS	                1

#define PMB_BUS_MEMC			0
#define PMB_ADDR_MEMC			(4 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC	                1

#define PMB_BUS_CHIP_CLKRST		0
#define PMB_ADDR_CHIP_CLKRST		(5 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST		0

#define PMB_BUS_SYSPLL			0
#define PMB_ADDR_SYSPLL			(6 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL		0

#define PMB_BUS_SYSPLL1			0
#define PMB_ADDR_SYSPLL1		(7 | PMB_BUS_SYSPLL1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL1		0

#define PMB_BUS_SAR			1
#define PMB_ADDR_SAR			(8 | PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SAR			1

#define PMB_BUS_SWITCH			1
#define PMB_ADDR_SWITCH			(9 | PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SWITCH		1

#define PMB_BUS_PCM			1
#define PMB_ADDR_PCM			(10 | PMB_BUS_PCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCM			2
    enum {
        PCM_Zone_Main,
        PCM_Zone_PCM,
    };
//--------- SOFT Reset bits for PCM ------------------------
#define   BPCM_PCM_SRESET_HARDRST_N   0x00000004	    
#define   BPCM_PCM_SRESET_PCM_N       0x00000002
#define   BPCM_PCM_SRESET_200_N       0x00000001


#define PMB_BUS_PERIPH			1
#define PMB_ADDR_PERIPH			(11 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH		3

#define PMB_BUS_VDSL3_MIPS		1
#define PMB_ADDR_VDSL3_MIPS		(12 | PMB_BUS_VDSL3_MIPS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_MIPS		1

#define PMB_BUS_VDSL3_CORE		1
#define PMB_ADDR_VDSL3_CORE		(13 | PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_CORE		1

#define AFEPLL_PMB_BUS_VDSL3_CORE	1
#define AFEPLL_PMB_ADDR_VDSL3_CORE	(14 | AFEPLL_PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define AFEPLL_PMB_ZONES_VDSL3_CORE	0

#endif

#if defined(_BCM963148_) || defined(CONFIG_BCM963148)
#define PMB_BUS_MAX			2
#define PMB_BUS_ID_SHIFT		8

#define PMB_BUS_APM			1
#define PMB_ADDR_APM			(0 | PMB_BUS_APM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_APM			5

//--------- SOFT Reset bits for APM ------------------------
#define   BPCM_APM_SRESET_HARDRST_N   0x00000040	    
#define   BPCM_APM_SRESET_AUDIO_N     0x00000020	
#define   BPCM_APM_SRESET_PCM_N       0x00000010
#define   BPCM_APM_SRESET_HVGA_N      0x00000008
#define   BPCM_APM_SRESET_HVGB_N      0x00000004
#define   BPCM_APM_SRESET_BMU_N       0x00000002
#define   BPCM_APM_SRESET_200_N       0x00000001

#define PMB_BUS_SWITCH			1
#define PMB_ADDR_SWITCH			(1 | PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SWITCH		3

#define PMB_BUS_CHIP_CLKRST		1
#define PMB_ADDR_CHIP_CLKRST		(2 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST		0

#define PMB_BUS_SATA			0
#define PMB_ADDR_SATA			(3 | PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SATA			1

#define PMB_BUS_URB			0
#define PMB_ADDR_URB			(4 | PMB_BUS_URB << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_URB			1

#define PMB_BUS_DECT_UBUS		0
#define PMB_ADDR_DECT_UBUS		(5 | PMB_BUS_DECT_UBUS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_DECT_UBUS		1

#define PMB_BUS_SAR			1
#define PMB_ADDR_SAR			(6 | PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SAR			1

#define PMB_BUS_RDP			1
#define PMB_ADDR_RDP			(7 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDP			2

#define PMB_BUS_MEMC			0
#define PMB_ADDR_MEMC			(8 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC			1

#define PMB_BUS_PERIPH			0
#define PMB_ADDR_PERIPH			(9 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH		1

#define PMB_BUS_SYSPLL			1
#define PMB_ADDR_SYSPLL			(10 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL		0

#define PMB_BUS_RDPPLL			1
#define PMB_ADDR_RDPPLL			(11 | PMB_BUS_RDPPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDPPLL		0

#define PMB_BUS_B15_PLL			1
#define PMB_ADDR_B15_PLL		(12 | PMB_BUS_B15_PLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_B15_PLL		0

#define PMB_BUS_SYSPLL3			0
#define PMB_ADDR_SYSPLL3		(13 | PMB_BUS_SYSPLL3 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL3		0

#define PMB_BUS_SYSPLL4			0
#define PMB_ADDR_SYSPLL4		(14 | PMB_BUS_SYSPLL4 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL4		0

#define PMB_BUS_PCIE0			0
#define PMB_ADDR_PCIE0			(15 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0			1

#define PMB_BUS_PCIE1			0
#define PMB_ADDR_PCIE1			(16 | PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE1			1

#define PMB_BUS_USB30_2X		1
#define PMB_ADDR_USB30_2X		(17 | PMB_BUS_USB30_2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB30_2X		4

#define PMB_BUS_PSAB			0
#define PMB_ADDR_PSAB			(18 | PMB_BUS_PSAB << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PSAB			1	// not shown in spreadsheet

#define PMB_BUS_PSBC			0
#define PMB_ADDR_PSBC			(19 | PMB_BUS_PSBC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PSBC			1	// not shown in spreadsheet

#define PMB_BUS_EGPHY			0
#define PMB_ADDR_EGPHY			(20 | PMB_BUS_EGPHY << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_EGPHY			1	// not shown in spreadsheet

#define PMB_BUS_VDSL3_MIPS		0
#define PMB_ADDR_VDSL3_MIPS		(21 | PMB_BUS_VDSL3_MIPS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_MIPS		1

#define PMB_BUS_VDSL3_CORE		0
#define PMB_ADDR_VDSL3_CORE		(22 | PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_VDSL3_CORE		3

#define AFEPLL_PMB_BUS_VDSL3_CORE	0
#define AFEPLL_PMB_ADDR_VDSL3_CORE	(23 | AFEPLL_PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define AFEPLL_PMB_ZONES_VDSL3_CORE	0

#define UBUS_PMB_BUS_VDSL3_CORE		PMB_BUS_VDSL3_CORE
#define UBUS_PMB_ADDR_VDSL3_CORE	(24 | UBUS_PMB_BUS_VDSL3_CORE << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_VDSL3_CORE	0

#define UBUS_PMB_BUS_VDSL3_MIPS		PMB_BUS_VDSL3_MIPS
#define UBUS_PMB_ADDR_VDSL3_MIPS	(25 | UBUS_PMB_BUS_VDSL3_MIPS << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_VDSL3_MIPS	0

#define UBUS_PMB_BUS_DECT		PMB_BUS_DECT_UBUS
#define UBUS_PMB_ADDR_DECT		(26 | UBUS_PMB_BUS_DECT << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_DECT		0

#define UBUS_PMB_BUS_ARM		PMB_BUS_URB
#define UBUS_PMB_ADDR_ARM		(27 | UBUS_PMB_BUS_ARM << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_ARM		0

#define UBUS_PMB_BUS_DAP		PMB_BUS_URB
#define UBUS_PMB_ADDR_DAP		(28 | UBUS_PMB_BUS_DAP << PMB_BUS_ID_SHIFT)
#define UBUS_PMB_ZONES_DAP		0

#define UBUS_CFG0_PMB_BUS_SAR		PMB_BUS_SAR
#define UBUS_CFG0_PMB_ADDR_SAR		(29 | UBUS_CFG0_PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG0_PMB_ZONES_SAR		0

#define UBUS_CFG1_PMB_BUS_SAR		PMB_BUS_SAR
#define UBUS_CFG1_PMB_ADDR_SAR		(30 | UBUS_CFG1_PMB_BUS_SAR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG1_PMB_ZONES_SAR		0

#define UBUS_CFG_PMB_BUS_DBR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_DBR		(31 | UBUS_CFG_PMB_BUS_DBR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_DBR		0

#define UBUS_CFG_PMB_BUS_RABR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_RABR		(32 | UBUS_CFG_PMB_BUS_RABR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_RABR		0

#define UBUS_CFG_PMB_BUS_RBBR		PMB_BUS_RDP
#define UBUS_CFG_PMB_ADDR_RBBR		(33 | UBUS_CFG_PMB_BUS_RBBR << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_RBBR		0

#define UBUS_CFG_PMB_BUS_APM 		PMB_BUS_APM
#define UBUS_CFG_PMB_ADDR_APM 		(34 | UBUS_CFG_PMB_BUS_APM << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_APM 		0

#define UBUS_CFG_PMB_BUS_PCIE0 		PMB_BUS_PCIE0
#define UBUS_CFG_PMB_ADDR_PCIE0 	(35 | UBUS_CFG_PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PCIE0 	0

#define UBUS_CFG_PMB_BUS_PCIE1 		PMB_BUS_PCIE1
#define UBUS_CFG_PMB_ADDR_PCIE1 	(36 | UBUS_CFG_PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PCIE1 	0

#define UBUS_CFG_PMB_BUS_USBH 		PMB_BUS_USB30_2X
#define UBUS_CFG_PMB_ADDR_USBH 		(37 | UBUS_CFG_PMB_BUS_USBH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_USBH 	0

#define UBUS_CFG_PMB_BUS_USBD 		PMB_BUS_USB30_2X
#define UBUS_CFG_PMB_ADDR_USBD 		(38 | UBUS_CFG_PMB_BUS_USBD << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_USBD 	0

#define UBUS_CFG_PMB_BUS_SWITCH		PMB_BUS_SWITCH
#define UBUS_CFG_PMB_ADDR_SWITCH	(39 | UBUS_CFG_PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_SWITCH	0

#define UBUS_CFG_PMB_BUS_PERIPH		PMB_BUS_PERIPH
#define UBUS_CFG_PMB_ADDR_PERIPH	(40 | UBUS_CFG_PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_PERIPH	0

#define UBUS_CFG_PMB_BUS_SATA  		PMB_BUS_SATA
#define UBUS_CFG_PMB_ADDR_SATA  	(41 | UBUS_CFG_PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define UBUS_CFG_PMB_ZONES_SATA  	0

#define PMB_BUS_B15_CPU0		0	// can't find it yet
#define PMB_ADDR_B15_CPU0  		(42 | PMB_BUS_B15_CPU0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_B15_CPU0		1

#define PMB_BUS_B15_CPU1		0	// can't find it yet
#define PMB_ADDR_B15_CPU1  		(43 | PMB_BUS_B15_CPU1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_B15_CPU1		1

#define PMB_BUS_B15_L2			0	// can't find it yet
#define PMB_ADDR_B15_L2  		(44 | PMB_BUS_B15_L2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_B15_L2		1

/* define Zone enum for each block here */
#ifndef _LANGUAGE_ASSEMBLY
enum {
    APM_Zone_Main,
    APM_Zone_Audio,
    APM_Zone_PCM,
    APM_Zone_HVG,
    APM_Zone_BMU,
};
#endif

#endif

#if defined(_BCM96848_) || defined(CONFIG_BCM96848)

#define PMB_BUS_MAX              2
#define PMB_BUS_ID_SHIFT         8

#define PMB_BUS_USB2X            0
#define PMB_ADDR_USB2X           (0 | PMB_BUS_USB2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB2X          3 

#define PMB_BUS_PCIE0            0
#define PMB_ADDR_PCIE0           (1 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0          1

#define PMB_BUS_PCM              0
#define PMB_ADDR_PCM             (2 | PMB_BUS_PCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCM            2
    enum {
        PCM_Zone_Main,
        PCM_Zone_PCM,
    };
//--------- SOFT Reset bits for PCM ------------------------
#define   BPCM_PCM_SRESET_HARDRST_N   0x00000004
#define   BPCM_PCM_SRESET_PCM_N       0x00000002
#define   BPCM_PCM_SRESET_200_N       0x00000001

#define PMB_BUS_PERIPH           0
#define PMB_ADDR_PERIPH          (3 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH         4

#define PMB_BUS_CHIP_CLKRST     0
#define PMB_ADDR_CHIP_CLKRST     (4 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST    0

#define PMB_BUS_SYSPLL0          0
#define PMB_ADDR_SYSPLL0         (5 | PMB_BUS_SYSPLL0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL0        0

#define PMB_BUS_SYSPLL1          0
#define PMB_ADDR_SYSPLL1         (6 | PMB_BUS_SYSPLL1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL1        0

#define PMB_BUS_MIPS             1
#define PMB_ADDR_MIPS            (7 | PMB_BUS_MIPS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MIPS           1

#define PMB_BUS_MEMC             1
#define PMB_ADDR_MEMC            (8 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC           1

#define PMB_BUS_RDP              1
#define PMB_ADDR_RDP             (9 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDP            2

#define PMB_BUS_WAN              1
#define PMB_ADDR_WAN             (10 | PMB_BUS_WAN << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WAN            4

#define PMB_BUS_SGMII            1
#define PMB_ADDR_SGMII           (11 | PMB_BUS_SGMII << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SGMII          1

#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)

#define PMB_BUS_MAX              2
#define PMB_BUS_ID_SHIFT         8

#define PMB_BUS_PERIPH           0
#define PMB_ADDR_PERIPH          (0 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH         3

#define PMB_BUS_CHIP_CLKRST      0
#define PMB_ADDR_CHIP_CLKRST     (1 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST    0

#define PMB_BUS_SYSPLL           0
#define PMB_ADDR_SYSPLL          (2 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL         0

#define PMB_BUS_RDPPLL           0
#define PMB_ADDR_RDPPLL          (3 | PMB_BUS_RDPPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDPPLL         0

#define PMB_BUS_UNIPLL           0
#define PMB_ADDR_UNIPLL          (5 | PMB_BUS_UNIPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_UNIPLL         0

#define PMB_BUS_APM              0
#define PMB_ADDR_APM             (7 | PMB_BUS_APM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_APM            2

#define PMB_BUS_MEMC             0
#define PMB_ADDR_MEMC            (8 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC           1

#define PMB_BUS_LPORT            1
#define PMB_ADDR_LPORT           (9 | PMB_BUS_LPORT << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_LPORT          3

#define PMB_BUS_USB30_2X         1
#define PMB_ADDR_USB30_2X        (10 | PMB_BUS_USB30_2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB30_2X       4

#define PMB_BUS_WAN              1
#define PMB_ADDR_WAN             (11 | PMB_BUS_WAN << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WAN            7

#define PMB_BUS_XRDP              1
#define PMB_ADDR_XRDP             (12 | PMB_BUS_XRDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP            3

#define PMB_BUS_XRDP_QM           1
#define PMB_ADDR_XRDP_QM          (13 | PMB_BUS_XRDP_QM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP_QM         1

#define PMB_BUS_XRDP_RC_QUAD0     1
#define PMB_ADDR_XRDP_RC_QUAD0    (14 | PMB_BUS_XRDP_RC_QUAD0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP_RC_QUAD0   1

#define PMB_BUS_XRDP_RC_QUAD1     1
#define PMB_ADDR_XRDP_RC_QUAD1    (15 | PMB_BUS_XRDP_RC_QUAD1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP_RC_QUAD1   1

#define PMB_BUS_XRDP_RC_QUAD2     1
#define PMB_ADDR_XRDP_RC_QUAD2    (16 | PMB_BUS_XRDP_RC_QUAD2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP_RC_QUAD2   1

#define PMB_BUS_XRDP_RC_QUAD3     1
#define PMB_ADDR_XRDP_RC_QUAD3    (17 | PMB_BUS_XRDP_RC_QUAD3 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP_RC_QUAD3   1

#define PMB_BUS_PCIE0              1
#define PMB_ADDR_PCIE0             (18 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0            1

#define PMB_BUS_PCIE1              1
#define PMB_ADDR_PCIE1             (19 | PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE1            1

#define PMB_BUS_SATA               1
#define PMB_ADDR_SATA             (20 | PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SATA             1

#define PMB_BUS_PCIE_UBUS          1
#define PMB_ADDR_PCIE_UBUS         (21 | PMB_BUS_PCIE_UBUS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE_UBUS        1

#define PMB_BUS_ORION_CPU0         0
#define PMB_ADDR_ORION_CPU0        (24 | PMB_BUS_ORION_CPU0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU0       1

#define PMB_BUS_ORION_CPU1         0
#define PMB_ADDR_ORION_CPU1        (25 | PMB_BUS_ORION_CPU1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU1       1

#define PMB_BUS_ORION_CPU2         0
#define PMB_ADDR_ORION_CPU2        (26 | PMB_BUS_ORION_CPU2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU2       1

#define PMB_BUS_ORION_CPU3         0
#define PMB_ADDR_ORION_CPU3        (27 | PMB_BUS_ORION_CPU3 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU3       1

#define PMB_BUS_ORION_NONCPU       0
#define PMB_ADDR_ORION_NONCPU      (28 | PMB_BUS_ORION_NONCPU << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_NONCPU     1

#define PMB_BUS_ORION_ARS          0
#define PMB_ADDR_ORION_ARS         (29 | PMB_BUS_ORION_ARS << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_ARS        1

#define PMB_BUS_BIU_PLL            0
#define PMB_ADDR_BIU_PLL           (30 | PMB_BUS_BIU_PLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_BIU_PLL          1   // FIXMET

#define PMB_BUS_BIU_BPCM           0
#define PMB_ADDR_BIU_BPCM          (31 | PMB_BUS_BIU_BPCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_BIU_BPCM         1

#define PMB_BUS_PCM                0
#define PMB_ADDR_PCM               (7 | PMB_BUS_PCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCM              2
enum {
    PCM_Zone_Main,
    PCM_Zone_PCM,
};
//--------- SOFT Reset bits for PCM ------------------------
#define   BPCM_PCM_SRESET_HARDRST_N   0x00000004
#define   BPCM_PCM_SRESET_PCM_N       0x00000002
#define   BPCM_PCM_SRESET_BUS_N       0x00000001

#endif /* defined(_BCM96858_) || defined(CONFIG_BCM96858) */

#if defined(_BCM94908_) || defined(CONFIG_BCM94908)
#define PMB_BUS_MAX			2
#define PMB_BUS_ID_SHIFT		8

#define PMB_BUS_PERIPH			0
#define PMB_ADDR_PERIPH			(0 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH		4

#define PMB_BUS_CRYPTO                  0
#define PMB_ADDR_CRYPTO                 (1 | PMB_BUS_CRYPTO << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CRYPTO                1

#define PMB_BUS_PCIE2			0
#define PMB_ADDR_PCIE2			(2 | PMB_BUS_PCIE2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE2			1

#define PMB_BUS_RDP			0
#define PMB_ADDR_RDP			(3 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDP			2

#define PMB_BUS_FPM			0
#define PMB_ADDR_FPM			(4 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_FPM			1

#define PMB_BUS_DQM			0
#define PMB_ADDR_DQM			(5 | PMB_BUS_RDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_DQM			1

#define PMB_BUS_URB			0
#define PMB_ADDR_URB			(6 | PMB_BUS_URB << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_URB			1

#define PMB_BUS_MEMC			0
#define PMB_ADDR_MEMC			(7 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC			1

#define PMB_BUS_RDPPLL			0
#define PMB_ADDR_RDPPLL			(8 | PMB_BUS_RDPPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_RDPPLL		0

#define PMB_BUS_B53PLL			0
#define PMB_ADDR_B53PLL			(9 | PMB_BUS_B53PLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_B53PLL		0

#define PMB_BUS_SWITCH			1
#define PMB_ADDR_SWITCH			(10 | PMB_BUS_SWITCH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SWITCH		3

#define PMB_BUS_PCM			1
#define PMB_ADDR_PCM			(11 | PMB_BUS_PCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCM			2
enum {
    PCM_Zone_Main,
    PCM_Zone_PCM,
};
//--------- SOFT Reset bits for PCM ------------------------
#define   BPCM_PCM_SRESET_HARDRST_N   0x00000004	    
#define   BPCM_PCM_SRESET_PCM_N       0x00000002
#define   BPCM_PCM_SRESET_200_N       0x00000001


#define PMB_BUS_SGMII  			1
#define PMB_ADDR_SGMII			(12 | PMB_BUS_SGMII << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SGMII			0

#define PMB_BUS_CHIP_CLKRST		1
#define PMB_ADDR_CHIP_CLKRST		(13 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST		0

#define PMB_BUS_PCIE0			1
#define PMB_ADDR_PCIE0			(14 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0			1

#define PMB_BUS_PCIE1			1
#define PMB_ADDR_PCIE1			(15 | PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE1			1

#define PMB_BUS_SATA			1
#define PMB_ADDR_SATA			(16 | PMB_BUS_SATA << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SATA			1

#define PMB_BUS_USB			1
#define PMB_ADDR_USB			(17 | PMB_BUS_USB << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB			4

#define PMB_BUS_SYSPLL			1
#define PMB_ADDR_SYSPLL			(18 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL		0

#define PMB_BUS_SWTPLL			1
#define PMB_ADDR_SWTPLL			(19 | PMB_BUS_SWTPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SWTPLL		0

#define PMB_BUS_I2SPLL			1
#define PMB_ADDR_I2SPLL			(20 | PMB_BUS_I2SPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_I2SPLL		0

#define PMB_BUS_GMAC			1
#define PMB_ADDR_GMAC			(21 | PMB_BUS_GMAC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_GMAC			1

#endif

#ifndef _LANGUAGE_ASSEMBLY
// ---------------------------- Returned error codes --------------------------
enum {
    // 0..15 may come from either the interface or from the PMC command handler
    // 256 or greater only come from the interface
    kPMC_NO_ERROR,
    kPMC_INVALID_ISLAND,
    kPMC_INVALID_DEVICE,
    kPMC_INVALID_ZONE,
    kPMC_INVALID_STATE,
    kPMC_INVALID_COMMAND,
    kPMC_LOG_EMPTY,
    kPMC_INVALID_PARAM,
    kPMC_BPCM_READ_TIMEOUT,
    kPMC_INVALID_BUS,
    kPMC_INVALID_QUEUE_NUMBER,
    kPMC_QUEUE_NOT_AVAILABLE,
    kPMC_INVALID_TOKEN_SIZE,
    kPMC_INVALID_WATERMARKS,
    kPMC_INSUFFICIENT_QSM_MEMORY,
    kPMC_INVALID_BOOT_COMMAND,
    kPMC_COMMAND_TIMEOUT = 256,
    kPMC_MESSAGE_ID_MISMATCH,
};

// ---------------------------- Returned log entry structure --------------------------
typedef struct {
    uint8 reserved;
    uint8 logMsgID;
    uint8 errorCode;
    uint8 logCmdID;
    uint8 srcPort;
    uint8 e_msgID;
    uint8 e_errorCode;
    uint8 e_cmdID;
    struct {
        uint32 logReplyNum : 8;
        uint32 e_Island    : 4;
        uint32 e_Bus       : 2;
        uint32 e_DevAddr   : 8;
        uint32 e_Zone      : 10;
    } s;
    uint32  e_Data0;
} TErrorLogEntry;

// ---------------------------- Power states --------------------------
enum {
    kPMCPowerState_Unknown,
    kPMCPowerState_NoPower,
    kPMCPowerState_LowPower,
    kPMCPowerState_FullPower,
};

// PMC run-state:
enum {
	kPMCRunStateExecutingBootROM = 0,
	kPMCRunStateWaitingBMUComplete,
	kPMCRunStateAVSCompleteWaitingForImage,
	kPMCRunStateAuthenticatingImage,
	kPMCRunStateAuthenticationFailed,
	kPMCRunStateReserved,
	kPMCRunStateFatalError,
	kPMCRunStateRunning
};

// the only valid "gear" values for "SetClockGear" function
enum {
    kClockGearLow,
    kClockGearHigh,
    kClockGearDynamic,
    kClockGearBypass
};

int TuneRunner(void);
int GetSelect0(void);
int GetSelect3(void);
#if !(defined(_BCM96838_) || defined(CONFIG_BCM96838))
int pmc_init(void);
void pmc_initmode(void);
int GetRevision(int *value);
int GetPVT(int sel, int *value);
int GetRCalSetting(int resistor, int* rcal);
#endif
int GetDevPresence(int devAddr, int *value);
int GetSWStrap(int devAddr, int *value);
int GetHWRev(int devAddr, int *value);
int GetNumZones(int devAddr, int *value);
int Ping(void);
int GetErrorLogEntry(TErrorLogEntry *logEntry);
int SetClockHighGear(int devAddr, int zone, int clkN);
int SetClockLowGear(int devAddr, int zone, int clkN);
int SetClockGear(int devAddr, int zone, int gear);
int SetRunState(int island, int state);
int SetPowerState(int island, int state);
void BootPmcNoRom(unsigned long physAddr);
int ReadBPCMRegister(int devAddr, int wordOffset, uint32 *value);
int WriteBPCMRegister(int devAddr, int wordOffset, uint32 value);
int ReadZoneRegister(int devAddr, int zone, int wordOffset, uint32 *value);
int WriteZoneRegister(int devAddr, int zone, int wordOffset, uint32 value);
int PowerOnDevice(int devAddr);
int PowerOffDevice(int devAddr, int repower);
int PowerOnZone(int devAddr, int zone);
int PowerOffZone(int devAddr, int zone);
int ResetDevice(int devAddr);
int ResetZone(int devAddr, int zone);
int CloseAVS(int margin1, int margin2);
#if defined CONFIG_BCM94908
int RecloseAVS(int iscold);
#endif
void WaitPmc(int runState);
#if defined(_BCM963138_) || defined(CONFIG_BCM963138) || defined(_BCM963148_) || defined(CONFIG_BCM963148) || defined(_BCM96858_) || defined(CONFIG_BCM96858) || defined(_BCM94908_) || defined(CONFIG_BCM94908)
int StallPmc(void);
int UnstallPmc(void);
#endif
#endif //_LANGUAGE_ASSEMBLY

#endif // PMC_DRV_H

