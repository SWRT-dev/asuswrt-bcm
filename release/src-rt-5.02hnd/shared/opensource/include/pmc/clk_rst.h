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

#ifndef CLK_RST_H
#define CLK_RST_H

// pll dividers 
struct PLL_DIVIDERS
{
	unsigned int pdiv;
	unsigned int ndiv_int;
	unsigned int ndiv_frac;
	unsigned int ka;
	unsigned int ki;
	unsigned int kp;
};

int pll_vco_freq_set(unsigned int pll_addr, struct PLL_DIVIDERS *divs);
int pll_ch_freq_set(unsigned int pll_addr, unsigned int ch, unsigned int mdiv);
int ddr_freq_set(unsigned long freq);
int viper_freq_set(unsigned long freq);
int rdp_freq_set(unsigned long freq);
unsigned long get_rdp_freq(unsigned int* rdp_freq);
#if defined(_BCM96848_) || defined(CONFIG_BCM96848) || defined(_BCM96858_) || defined(CONFIG_BCM96858)
int pll_vco_freq_get(unsigned int pll_addr, unsigned int* fvco);
int pll_ch_freq_get(unsigned int pll_addr, unsigned int ch, unsigned int* freq);
#endif

#if defined(_BCM96848_) || defined(CONFIG_BCM96848)
#define SYSPLL0_MIPS_CHANNEL     0
#define SYSPLL0_RUNNER_CHANNEL   1
#define SYSPLL0_UBUS_CHANNEL     2
#define SYSPLL0_HSPIM_CHANNEL    3
#define SYSPLL0_PCM_CHANNEL      4
#define SYSPLL0_RGMII_CHANNEL    5
#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
enum DCM_MODULE
{
    DCM_UBUS = 0,
    DCM_UBUS_XRDP,
};

int bcm_dcm_config(enum DCM_MODULE dcm, int min_div, int mid_div, int enable);
int pll_ch_freq_set(unsigned int pll_addr, unsigned int ch, unsigned int mdiv);
#endif
#endif //#ifndef CLK_RST_H
