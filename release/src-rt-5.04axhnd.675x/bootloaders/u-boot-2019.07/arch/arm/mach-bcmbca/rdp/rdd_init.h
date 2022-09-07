// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2013 Broadcom
 */
/*
    
*/

#ifndef _BL_LILAC_DRV_RUNNER_INIT_H
#define _BL_LILAC_DRV_RUNNER_INIT_H


/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_init                                                                 */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - initialize the firmware driver                         */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   resets Runner memories (data, program and context), should be called     */
/*   after reset and before any other API                                     */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   none                                                                     */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_init ( void );

/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_load_microcode                                                       */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - load the microcode into the SRAM program memory        */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   Four Runners are loaded (the code is imported as a C code array)         */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   xi_runer_A_microcode_ptr - Fast Runner 0 microcode                       */
/*   xi_runer_B_microcode_ptr - Fast Runner 1 microcode                       */
/*   xi_runer_C_microcode_ptr - Pico Runner 0 microcode                       */
/*   xi_runer_D_microcode_ptr - Pico Runner 1 microcode                       */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_load_microcode ( uint8_t  *xi_runer_A_microcode_ptr,
                                            uint8_t  *xi_runer_B_microcode_ptr,
                                            uint8_t  *xi_runer_C_microcode_ptr,
                                            uint8_t  *xi_runer_D_microcode_ptr );


/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_load_prediction                                                      */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - load the jump prediction into SRAM                     */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   Four Runners are loaded (the prediction is imported as bin file)         */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   xi_runer_A_prediction_ptr - Fast Runner 0 prediction                     */
/*   xi_runer_B_prediction_ptr - Fast Runner 1 prediction                     */
/*   xi_runer_C_prediction_ptr - Pico Runner 0 prediction                     */
/*   xi_runer_D_prediction_ptr - Pico Runner 1 prediction                     */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_load_prediction ( uint8_t  *xi_runer_A_prediction_ptr,
                                             uint8_t  *xi_runer_B_prediction_ptr,
                                             uint8_t  *xi_runer_C_prediction_ptr,
                                             uint8_t  *xi_runer_D_prediction_ptr );


/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_runner_enable                                                        */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - Enables the Runner                                     */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   This API move the Runner from halt mode to running mode, firmware starts */
/*   execute.                                                                 */
/*                                                                            */
/* Registers :                                                                */
/*                                                                            */
/*   Runner_Global_Control register                                           */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   none                                                                     */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_runner_enable ( void );

/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_runner_frequency_set                                                 */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - set the frequency of the Runner timers                 */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   This API set the frequency of the Runner timers                          */
/*                                                                            */
/* Registers :                                                                */
/*                                                                            */
/*   Runner_Global_Control register                                           */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   xi_runner_frequency - Runner frequency in MHZ                            */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_runner_frequency_set ( uint16_t  xi_runner_frequency );


/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_data_structures_init                                                 */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   Firmware Driver - initialize all firmware data structures to a default   */
/*                     state, should be called after reset and                */
/*                     rdd_init() API and before any other API.               */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   This function configures the schedule mechansim of a single TCONT.       */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   xi_ddr_pool_ptr - packet DDR buffer base address                         */
/*   xi_extra_ddr_pool_ptr - packet DDR buffer base address (Multicast)       */
/*   xi_mac_table_size - Mac lookup table size                                */
/*   xi_mac_table_search_depth - Mac lookup table maximum search depth        */
/*   xi_wan_physical_port - GPON EMAC5 or EMAC4                               */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_data_structures_init ( RDD_INIT_PARAMS  *init_params );

/******************************************************************************/
/*                                                                            */
/* Name:                                                                      */
/*                                                                            */
/*   rdd_bbh_reset_firmware_fifo_init                                         */
/*                                                                            */
/* Title:                                                                     */
/*                                                                            */
/*   actions which are needed after BBH reset                                 */
/*                                                                            */
/* Abstract:                                                                  */
/*                                                                            */
/*   This function need to be called by SW after BBH reset                    */
/*   1) initialize emac ingress/egress counters                               */
/*   2) wakeup the runner to initialize BBH descriptor pointer                */
/*	                       (using error + ploam bits)                         */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   xi_src_bridge_port - bridge port                                         */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   BL_LILAC_RDD_ERROR_DTE - Return status                                   */
/*     BL_LILAC_RDD_OK - No error                                             */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_bbh_reset_firmware_fifo_init ( BL_LILAC_RDD_BRIDGE_PORT_DTE  xi_src_bridge_port );

/******************************************************************************/
/*                                                                            */
/* Description:                                                               */
/*                                                                            */
/*   This function sets the switch port for ethwan2.                          */
/*                                                                            */
/* Input:                                                                     */
/*                                                                            */
/*   None                                                                     */
/*                                                                            */
/* Output:                                                                    */
/*                                                                            */
/*   xi_switch_port - ethwan2 switch port                                     */
/*                                                                            */
/******************************************************************************/
BL_LILAC_RDD_ERROR_DTE rdd_ethwan2_switch_port_config ( uint8_t xi_switch_port );


#endif /* _BL_LILAC_DRV_RUNNER_INIT_H */

