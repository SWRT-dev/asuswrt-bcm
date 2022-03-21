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
 *  Created on: Jan 2016
 *      Author: yuval.raviv@broadcom.com
 */

/*
 * Common functions for Broadcom phy drivers
 */

#include "bus_drv.h"
#include "phy_drv.h"
#include "phy_drv_mii.h"
#include "phy_drv_brcm.h"

#define AUXSTAT                 0x19
#define BRCM_MIIEXT_BANK        0x1f

#define EXP_REG_BASE            0x0f00
#define EXP_REG_ADDRESS         0x17
#define EXP_REG_VALUE           0x15
#define RDB_REG_ADDRESS         0x1e
#define RDB_REG_VALUE           0x1f

#define CORE_SHD1C_0A           0x001a /* Auto-Power Down */
#define CORE_SHD1C_05           0x0015 /* Reserved Control 3 */

#define EEE_CONTROL             0x803d /* EEE Control */
#define EEE_RES_STAT            0x803e /* EEE Resolution Status */
#define EEE_ADV                 0x003c /* EEE Advertisement */
#define EEE_LP_ADV              0x003d /* EEE Link Partner Advertisement */

int brcm_read_status(phy_dev_t *phy_dev)
{
    int ret, mode;
    uint16_t val;

    phy_dev->link = 0;
    phy_dev->speed = PHY_SPEED_UNKNOWN;
    phy_dev->duplex = PHY_DUPLEX_UNKNOWN;

    if ((ret = phy_bus_read(phy_dev, AUXSTAT, &val)))
        return ret;

    phy_dev->link = ((val >> 2) & 0x1);

    if (!phy_dev->link)
        return 0;

    mode = ((val >> 8) & 0x7);

    if (mode == 1)
    {
        phy_dev->speed = PHY_SPEED_10;
        phy_dev->duplex = PHY_DUPLEX_HALF;
    }
    else if (mode == 2)
    {
        phy_dev->speed = PHY_SPEED_10;
        phy_dev->duplex = PHY_DUPLEX_FULL;
    }
    else if (mode == 3)
    {
        phy_dev->speed = PHY_SPEED_100;
        phy_dev->duplex = PHY_DUPLEX_HALF;
    }
    else if (mode == 5)
    {
        phy_dev->speed = PHY_SPEED_100;
        phy_dev->duplex = PHY_DUPLEX_FULL;
    }
    else if (mode == 6)
    {
        phy_dev->speed = PHY_SPEED_1000;
        phy_dev->duplex = PHY_DUPLEX_HALF;
    }
    else if (mode == 7)
    {
        phy_dev->speed = PHY_SPEED_1000;
        phy_dev->duplex = PHY_DUPLEX_FULL;
    }

    return 0;
}

static int brcm_shadow_rw(phy_dev_t *phy_dev, int write, int bank, uint16_t reg, uint16_t *val)
{
    int ret = 0;

    switch (bank)
    {
    case 1: 
        if ((ret = phy_bus_write(phy_dev, BRCM_MIIEXT_BANK, 0x8b)))
            goto Exit;
        break;
    case 2:
    case 3:
        if ((ret = phy_bus_write(phy_dev, BRCM_MIIEXT_BANK, 0x0f)))
            goto Exit;
        break;
    }

    if (bank == 3)
    {
        if (write)
        {
            if ((ret = phy_bus_write(phy_dev, 0x0e, reg)))
                goto Exit;

            if ((ret = phy_bus_write(phy_dev, 0x0f, *val)))
                goto Exit;
        }
        else
        {
            if ((ret = phy_bus_write(phy_dev, 0x0e, reg)))
                goto Exit;
            if ((ret = phy_bus_read(phy_dev, 0x0f, val)))
                goto Exit;
        }
    }
    else
    {
        if (write)
        {
            if ((ret = phy_bus_write(phy_dev, reg, *val)))
                goto Exit;
        }
        else 
        {
            if ((ret = phy_bus_read(phy_dev, reg, val)))
                goto Exit;
        }
    }

    if ((ret = phy_bus_write(phy_dev, BRCM_MIIEXT_BANK, 0x0b)))
            goto Exit;

Exit:
    return ret;
}

int brcm_shadow_read(phy_dev_t *phy_dev, int bank, uint16_t reg, uint16_t *val)
{
    return brcm_shadow_rw(phy_dev, 0, bank, reg, val);
}

int brcm_shadow_write(phy_dev_t *phy_dev, int bank, uint16_t reg, uint16_t val)
{
    return brcm_shadow_rw(phy_dev, 1, bank, reg, &val);
}

int brcm_exp_read(phy_dev_t *phy_dev, uint16_t reg, uint16_t *val)
{
    if (phy_bus_write(phy_dev, EXP_REG_ADDRESS, EXP_REG_BASE | reg))
        return -1;

    if (phy_bus_read(phy_dev, EXP_REG_VALUE, val))
        return -1;

    return 0;
}

int brcm_exp_write(phy_dev_t *phy_dev, uint16_t reg, uint16_t val)
{
    if (phy_bus_write(phy_dev, EXP_REG_ADDRESS, EXP_REG_BASE | reg))
        return -1;

    if (phy_bus_write(phy_dev, EXP_REG_VALUE, val))
        return -1;

    return 0;
}

int brcm_rdb_set(phy_dev_t *phy_dev, int enable)
{
    if (enable)
        return brcm_exp_write(phy_dev, 0x7e, 0x0000);
    else
        return brcm_rdb_write(phy_dev, 0x87, 0x8000);
}

int brcm_rdb_read(phy_dev_t *phy_dev, uint16_t reg, uint16_t *val)
{
    if (phy_bus_write(phy_dev, RDB_REG_ADDRESS, reg))
        return -1;

    if (phy_bus_read(phy_dev, RDB_REG_VALUE, val))
        return -1;

    return 0;
}

int brcm_rdb_write(phy_dev_t *phy_dev, uint16_t reg, uint16_t val)
{
    if (phy_bus_write(phy_dev, RDB_REG_ADDRESS, reg))
        return -1;

    if (phy_bus_write(phy_dev, RDB_REG_VALUE, val))
        return -1;

    return 0;
}

int brcm_egphy_read(phy_dev_t *phy_dev, uint16_t reg, uint16_t *val)
{
    int ret;

    if (reg & RDB_ACCESS)
    {
        if ((ret = brcm_rdb_set(phy_dev, 1)))
            goto Exit;

        if ((ret = brcm_rdb_read(phy_dev, reg & ~RDB_ACCESS, val))) 
            goto Exit;

        if ((ret = brcm_rdb_set(phy_dev, 0)))
            goto Exit;
    }
    else
    {
        if ((ret = phy_bus_read(phy_dev, reg, val)))
            goto Exit;
    }

Exit:
    return ret;
}

int brcm_egphy_write(phy_dev_t *phy_dev, uint16_t reg, uint16_t val)
{
    int ret;

    if (reg & RDB_ACCESS)
    {
        if ((ret = brcm_rdb_set(phy_dev, 1)))
            goto Exit;

        if ((ret = brcm_rdb_write(phy_dev, reg & ~RDB_ACCESS, val))) 
            goto Exit;

        if ((ret = brcm_rdb_set(phy_dev, 0)))
            goto Exit;
    }
    else
    {
        if ((ret = phy_bus_write(phy_dev, reg, val)))
            goto Exit;
    }

Exit:
    return ret;
}

int brcm_egphy_apd_set(phy_dev_t *phy_dev, int enable)
{
    int ret;
    uint16_t val;

    /* Auto-Power Down */
    val = 0;
    val |= (1 << 0); /* Counter for wakeup timer = 84 ms */

    if (enable)
    {
        val |= (1 << 5); /* Enable auto powerdown */
        val |= (1 << 8); /* Enable energy detect single link pulse */
    }

    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | CORE_SHD1C_0A, val)))
        goto Exit;

    /* Reserved Control 3 */
    if ((ret = phy_dev_read(phy_dev, RDB_ACCESS | CORE_SHD1C_05, &val)))
        goto Exit;

    if (enable)
    {
        val |= (1 << 0); /* Disable CLK125 output */
        val &= ~(1 << 1); /* Enable powering down of dll during auto-power down */
    }
    else
    {
        val &= ~(1 << 0); /* Enable CLK125 output */
        val |= (1 << 1); /* Disable powering down of dll during auto-power down */
    }

    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | CORE_SHD1C_05, val)))
        goto Exit;

Exit:
    return ret;
}

int brcm_egphy_eee_get(phy_dev_t *phy_dev, int *enable)
{
    int ret;
    uint16_t val;

    /* EEE Resolution Status */
    if ((ret = phy_bus_c45_read(phy_dev, 7, EEE_RES_STAT, &val)))
        goto Exit;

    /* Check if the link partner auto-negotiated EEE capability for 100BASE-TX or 1000BASE-T */
    *enable = (val & (1 << 1) || val & (1 << 2));

Exit:
    return ret;
}

int brcm_egphy_eee_set(phy_dev_t *phy_dev, int enable)
{
    int ret;
    uint16_t val;

    /* EEE Control */
    val = 0;
    if (enable)
    {
        val |= (1 << 14); /* Enable EEE capability using SGMII auto-negotiation */
        val |= (1 << 15); /* Enable EEE LPI feature */
    }

    if ((ret = phy_bus_c45_write(phy_dev, 7, EEE_CONTROL, val)))
        goto Exit;

    /* EEE Advertisement */
    val = 0;
    if (enable)
    {
        val |= (1 << 1); /* EEE support for 100BASE-TX */
        val |= (1 << 2); /* EEE support for 1000BASE-T */
    }

    if ((ret = phy_bus_c45_write(phy_dev, 7, EEE_ADV, val)))
        goto Exit;

    if ((ret = mii_autoneg_restart(phy_dev)))
        goto Exit;

Exit:
    return ret;
}

int brcm_ephy_apd_set(phy_dev_t *phy_dev, int enable)
{
    uint16_t val;

    /* Auxiliary Status 2 Register */
    val = 0;
    val |= (1 << 0); /* Wake-up timer = 40 milliseconds */
    val |= (7 << 12); /* Cable Length > 140 meters */

    if (enable)
        val |= (1 << 5); /* APD Enable */

    return brcm_shadow_write(phy_dev, 1, 0x1b, val);
}

int brcm_ephy_eee_get(phy_dev_t *phy_dev, int *enable)
{
    int ret;
    uint16_t val;

    /* Auto-Negotiation Status Register */
    if ((ret = brcm_shadow_read(phy_dev, 3, 0x0b, &val)))
        goto Exit;

    /* Auto-negotiation EEE Enable, Auto-negotiation EEE Resolution */
    *enable = (val & (1 << 1) && val & (1 << 8));

Exit:
    return ret;
}

int brcm_ephy_eee_set(phy_dev_t *phy_dev, int enable)
{
    int ret;
    uint16_t val;

    if (enable)
    {
        /* Auto-Negotiation EEE Advertisement */
        val = 0;
        val |= (1 << 1); /* EEE Auto-negotiation advertise */
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x03, val)))
            goto Exit;

        /* PCS Control */
        val = 0;
        val |= (2 << 9); /* TACF Phase Track Mode = 2 */
        val |= (1 << 14); /* TACF Beta Control = 0.5 */
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x06, val)))
            goto Exit;

        /* EEE Phase Search MSE Threshold */
        val = 0;
        val |= (0x50 << 0); /* MSE error threshold = 0x50 */
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x0e, val)))
            goto Exit;

        /* Auto-Negotiation Status Register */
        val = 0;
        val |= (1 << 0); /* Null message enabled for auto-negotiation */
        val |= (1 << 1); /* EEE auto-negotiation enabled */
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x0b, val)))
            goto Exit;
    }
    else
    {
        /* Auto-Negotiation EEE Advertisement */
        val = 0;
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x03, val)))
            goto Exit;

        /* Auto-Negotiation Status Register */
        val = 0;
        if ((ret = brcm_shadow_write(phy_dev, 3, 0x0b, val)))
            goto Exit;
    }

    if ((ret = mii_autoneg_restart(phy_dev)))
        goto Exit;

Exit:
    return ret;
}
