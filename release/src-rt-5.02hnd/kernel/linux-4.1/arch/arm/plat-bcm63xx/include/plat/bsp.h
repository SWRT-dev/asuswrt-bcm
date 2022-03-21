#if defined(CONFIG_BCM_KF_ARM_BCM963XX)
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

/*
 * Broadcom ARM BSP
 * Internal API declarations
 */


#ifndef __PLAT_BSP_H
#define __PLAT_BSP_H

struct clk;

void __init soc_fixup(void);
void __init soc_map_io(void);
void __init soc_init_clock(void);
void __init soc_init_irq(void);
void __init soc_init_early(void);
void __init soc_add_devices(void);
void __init soc_init_timer(void);
void __init soc_l2_cache_init(void);

#endif /* __PLAT_BSP_H */
#endif /* CONFIG_BCM_KF_ARM_BCM963XX */
