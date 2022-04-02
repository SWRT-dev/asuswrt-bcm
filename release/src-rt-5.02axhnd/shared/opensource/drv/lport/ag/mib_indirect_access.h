/*
   Copyright (c) 2015 Broadcom Corporation
   All Rights Reserved

   <:label-BRCM:2015:DUAL/GPL:standard
   
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
 * mib_indirect_access.h
 *
 *  Created on: 6 ����� 2015
 *      Author: yonatani
 */

#ifndef SHARED_OPENSOURCE_DRV_LPORT_MIB_INDIRECT_ACCESS_H_
#define SHARED_OPENSOURCE_DRV_LPORT_MIB_INDIRECT_ACCESS_H_
#include "bcm6858_mib_conf_ag.h"

#define MIB_INDIRECT_WRITE(i,b,r,v) mib_indirect_write(i, RU_BLK(b).addr[i]+RU_REG_OFFSET(b,r),v)
#define MIB_INDIRECT_READ(i,b,r,v) mib_indirect_read(i, RU_BLK(b).addr[i]+RU_REG_OFFSET(b,r),&v)

static void mib_indirect_write(uint32_t portid, uint64_t address, uint64_t val)
{
    //fill using holding register
    uint32_t xlmacid = (portid >> 2) & 0x1;
    uint32_t holding = (uint32_t)((val >> 32) & 0xFFFFFFFF);
    uint32_t regval = (uint32_t)(val & 0xFFFFFFFF);
    ag_drv_mib_conf_mib0_write_holding_set(xlmacid, holding);

    WRITE_32(address, regval);
}

static void mib_indirect_read(uint32_t portid, uint64_t address, uint64_t *val)
{
    //fill using holding register
    uint32_t xlmacid = (portid >> 2) & 0x1;
    uint32_t value32;
    uint32_t holding;

    READ_32(address, value32);

    ag_drv_mib_conf_mib0_read_holding_get(xlmacid, &holding);

    *val = (((uint64_t)holding << 32) | value32);
}

#endif //SHARED_OPENSOURCE_DRV_LPORT_MIB_INDIRECT_ACCESS_H_
