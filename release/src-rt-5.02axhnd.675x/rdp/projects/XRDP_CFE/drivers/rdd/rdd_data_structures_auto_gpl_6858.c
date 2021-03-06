/*
   Copyright (c) 2015 Broadcom
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



/* This is an automated file. Do not edit its contents. */


#include "rdd.h"
#include "ru_types.h"

#include "rdd_data_structures_auto.h"
/* >>>RDD_CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0x390,
	0x15b0,
};
/* <<<RDD_CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0xbb0,
	0x1620,
};
/* <<<RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0xbe0,
	0x1630,
};
/* <<<RDD_CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0xce0,
	INVALID_TABLE_ADDRESS,
};
/* <<<RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0xd28,
	0x1668,
};
/* <<<RDD_CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_FEED_RING_INTERRUPT_THRESHOLD_ADDRESS_ARR */
uint32_t RDD_CPU_FEED_RING_INTERRUPT_THRESHOLD_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0xd4c,
	INVALID_TABLE_ADDRESS,
};
/* <<<RDD_CPU_FEED_RING_INTERRUPT_THRESHOLD_ADDRESS_ARR */
/* >>>RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	0x3000,
	INVALID_TABLE_ADDRESS,
};
/* <<<RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR */
/* >>>RDD_CPU_TX_RING_TABLE_ADDRESS_ARR */
uint32_t RDD_CPU_TX_RING_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM] = {
	INVALID_TABLE_ADDRESS,
	INVALID_TABLE_ADDRESS,
	0x1380,
};
/* <<<RDD_CPU_TX_RING_TABLE_ADDRESS_ARR */
