/*
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

#ifndef DRV_FPM_H_INCLUDED
#define DRV_FPM_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*                                                                           */
/* Include files                                                             */
/*                                                                           */
/*****************************************************************************/


#define FPM_BUF_SIZE_0                      512
#define FPM_BUF_SIZE_1                      256
#define FPM_BUF_SIZE_DEFAULT                FPM_BUF_SIZE_0

#define FPM_BUF_SIZE_256                    FPM_BUF_SIZE_1
#define FPM_BUF_SIZE_512                    FPM_BUF_SIZE_0
#define FPM_BUF_SIZE_1K                     1024
#define FPM_BUF_SIZE_2K                     2048
#define FPM_BUF_MAX_BASE_BUFFS              8
#define TOTAL_FPM_TOKENS                    ((64*1024) - 1)
#define FPM_DDR_BUFFER_SIZE                 512

/** Boolean value */
typedef char bdmf_boolean;

bdmf_error_t drv_fpm_alloc_buffer(uint32_t packet_len, uint32_t *buff_num);
bdmf_error_t drv_fpm_free_buffer(uint32_t packet_len, uint32_t buff_num);
void *drv_fpm_buffer_get_address(uint32_t fpm_bn);
void drv_fpm_copy_from_host_buffer(void *data, uint32_t fpm_bn, uint32_t packet_len, uint16_t offset);



#ifdef __cplusplus
}
#endif

#endif
