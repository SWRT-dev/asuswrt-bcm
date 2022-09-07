// SPDX-License-Identifier: GPL-2.0+
/*
   Copyright (c) 2015 Broadcom
   All Rights Reserved

    
*/



/* This is an automated file. Do not edit its contents. */


#ifndef _RDD_DATA_STRUCTURES_AUTO_H_
#define _RDD_DATA_STRUCTURES_AUTO_H_

#define GROUPED_EN_SEGMENTS_NUM       1
#define INVALID_TABLE_ADDRESS         0xFFFFFF

#ifdef __clang__
#define ALIGNMENT8 __attribute__((align_value(8)))
#else
#define ALIGNMENT8
#endif


/* DDR */
/* PSRAM */
/* CORE_0 */

/* >>>SRAM_PD_FIFO */

/* >>>RDD_PROCESSING_TX_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	cong_state              	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	reserved1_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flow                    	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	bn1_first               	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	stream_id               	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	reserved2_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	source_port             	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved1               	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
			uint32_t	abs_1                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lag_port                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	lan_vport               	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved3_union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_vport                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	flow_id                 	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved4_union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sop_fpm                 	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	bn_num                  	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                     	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first               	; /* Member of payload_offset_sop union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	abs_0                   	:29	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_first_level_q 	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_second_level_q	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_force_copy    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_color         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reprocess     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_mc_copy       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_dont_agg      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_headroom      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_valid         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_priority      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_serial_num    	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	bn1_first               	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
			uint32_t	flow                    	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved1_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	cong_state              	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	reserved1_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved1               	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
			uint32_t	abs_1                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of union3 union */
			uint32_t	source_port             	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved2_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	stream_id               	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cong_state_stream union */
			uint32_t	reserved2_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lag_port                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	lan_vport               	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved3_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_union3        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_vport                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	flow_id                 	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved4_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_cong_state_stream	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_drop          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	sop_fpm                 	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	reserved1_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	bn_num                  	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                     	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first               	; /* Member of payload_offset_sop union */
			uint32_t	reserved2_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	abs_0                   	:29	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	reserved3_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PROCESSING_TX_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_PROCESSING_TX_DESCRIPTOR_DTS fields;
} PROCESSING_TX_DESCRIPTOR_STRUCT;
#define RDD_PROCESSING_TX_DESCRIPTOR_VALID_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_VALID_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_VALID_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_VALID_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_HEADROOM_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_HEADROOM_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_HEADROOM_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_HEADROOM_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_DONT_AGG_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_DONT_AGG_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_DONT_AGG_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p, 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_DONT_AGG_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p, 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_MC_COPY_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 4, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_MC_COPY_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 4, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_MC_COPY_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p, 4, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_MC_COPY_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p, 4, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_REPROCESS_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_REPROCESS_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_REPROCESS_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p, 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_REPROCESS_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p, 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_COLOR_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 2, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_COLOR_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 2, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_COLOR_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p, 2, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_COLOR_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p, 2, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FORCE_COPY_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 1, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FORCE_COPY_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 1, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FORCE_COPY_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p, 1, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FORCE_COPY_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p, 1, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SECOND_LEVEL_Q_READ_G(r, g, idx)          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 0, 9, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SECOND_LEVEL_Q_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS), 0, 9, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SECOND_LEVEL_Q_READ(r, p)                 FIELD_MREAD_16((uint8_t *)p, 0, 9, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SECOND_LEVEL_Q_WRITE(v, p)                FIELD_MWRITE_16((uint8_t *)p, 0, 9, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FIRST_LEVEL_Q_READ_G(r, g, idx)           GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 2, 7, 9, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FIRST_LEVEL_Q_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 2, 7, 9, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FIRST_LEVEL_Q_READ(r, p)                  FIELD_MREAD_16((uint8_t *)p + 2, 7, 9, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FIRST_LEVEL_Q_WRITE(v, p)                 FIELD_MWRITE_16((uint8_t *)p + 2, 7, 9, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLAG_1588_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLAG_1588_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLAG_1588_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 3, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLAG_1588_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 3, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_COHERENT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_COHERENT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_COHERENT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 3, 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_COHERENT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 3, 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_HN_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 0, 5, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_HN_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 3, 0, 5, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_HN_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 3, 0, 5, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_HN_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 3, 0, 5, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SERIAL_NUM_READ_G(r, g, idx)              GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 4, 6, 10, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SERIAL_NUM_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 4, 6, 10, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SERIAL_NUM_READ(r, p)                     FIELD_MREAD_16((uint8_t *)p + 4, 6, 10, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SERIAL_NUM_WRITE(v, p)                    FIELD_MWRITE_16((uint8_t *)p + 4, 6, 10, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PRIORITY_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PRIORITY_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PRIORITY_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 5, 5, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PRIORITY_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 5, 5, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_CONG_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 4, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_CONG_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 4, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_CONG_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 5, 4, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_CONG_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 5, 4, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 5, 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 5, 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 5, 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PACKET_LENGTH_READ_G(r, g, idx)           GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 6, 0, 14, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PACKET_LENGTH_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 6, 0, 14, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PACKET_LENGTH_READ(r, p)                  FIELD_MREAD_16((uint8_t *)p + 6, 0, 14, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PACKET_LENGTH_WRITE(v, p)                 FIELD_MWRITE_16((uint8_t *)p + 6, 0, 14, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_DROP_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_DROP_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_DROP_READ(r, p)                           FIELD_MREAD_8((uint8_t *)p + 8, 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_DROP_WRITE(v, p)                          FIELD_MWRITE_8((uint8_t *)p + 8, 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_STREAM_READ_G(r, g, idx)       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 3, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_STREAM_WRITE_G(v, g, idx)      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 3, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_STREAM_READ(r, p)              FIELD_MREAD_8((uint8_t *)p + 8, 4, 3, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_STREAM_WRITE(v, p)             FIELD_MWRITE_8((uint8_t *)p + 8, 4, 3, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_1_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_1_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_1_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 8, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_1_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 8, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 2, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 2, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 8, 4, 2, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_CONG_STATE_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 8, 4, 2, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_STREAM_ID_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 3, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_STREAM_ID_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 4, 3, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_STREAM_ID_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 8, 4, 3, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_STREAM_ID_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 8, 4, 3, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 8, 3, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 8, 3, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_PORT_READ_G(r, g, idx)            GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_PORT_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_PORT_READ(r, p)                   FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_INGRESS_PORT_WRITE(v, p)                  FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_READ(r, p)                           FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_WRITE(v, p)                          FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOURCE_PORT_READ_G(r, g, idx)             GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOURCE_PORT_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOURCE_PORT_READ(r, p)                    FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOURCE_PORT_WRITE(v, p)                   FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAG_PORT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 1, 2, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAG_PORT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 1, 2, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAG_PORT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 8, 1, 2, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAG_PORT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 8, 1, 2, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_VPORT_READ_G(r, g, idx)               GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 6, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_VPORT_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 6, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_VPORT_READ(r, p)                      FIELD_MREAD_16((uint8_t *)p + 8, 3, 6, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_LAN_VPORT_WRITE(v, p)                     FIELD_MWRITE_16((uint8_t *)p + 8, 3, 6, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_IS_VPORT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 2, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_IS_VPORT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 2, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_IS_VPORT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 8, 2, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_IS_VPORT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 8, 2, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_ID_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_ID_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 3, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_ID_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 8, 3, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_FLOW_ID_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 8, 3, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_UNION3_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_UNION3_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_UNION3_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_UNION3_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN1_FIRST_READ_G(r, g, idx)               GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN1_FIRST_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN1_FIRST_READ(r, p)                      FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN1_FIRST_WRITE(v, p)                     FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_1_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 10, 0, 11, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_1_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 10, 0, 11, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_1_READ(r, p)                          FIELD_MREAD_16((uint8_t *)p + 10, 0, 11, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_1_WRITE(v, p)                         FIELD_MWRITE_16((uint8_t *)p + 10, 0, 11, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_AGG_PD_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_AGG_PD_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_AGG_PD_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 12, 7, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_AGG_PD_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 12, 7, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_0_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_0_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_0_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 12, 6, 1, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_TARGET_MEM_0_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 12, 6, 1, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ_G(r, g, idx)      GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 30, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE_G(v, g, idx)     GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 30, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ(r, p)             FIELD_MREAD_32((uint8_t *)p + 12, 0, 30, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE(v, p)            FIELD_MWRITE_32((uint8_t *)p + 12, 0, 30, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_FPM_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 3, 11, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_FPM_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 3, 11, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_FPM_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 12, 3, 11, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_FPM_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 12, 3, 11, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_FPM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_FPM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_FPM_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 12, 0, 19, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_FPM_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 12, 0, 19, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_NUM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 7, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_NUM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 7, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_NUM_READ(r, p)                         FIELD_MREAD_16((uint8_t *)p + 12, 7, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN_NUM_WRITE(v, p)                        FIELD_MWRITE_16((uint8_t *)p + 12, 7, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 13, 0, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 13, 0, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 13, 0, 7, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_SOP_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 13, 0, 7, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN0_FIRST_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 14, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN0_FIRST_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 14, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN0_FIRST_READ(r, p)                      MREAD_16((uint8_t *)p + 14, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_BN0_FIRST_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 14, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_0_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 29, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_0_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_TX_DESCRIPTOR_DTS) + 12, 0, 29, v)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_0_READ(r, p)                          FIELD_MREAD_32((uint8_t *)p + 12, 0, 29, r)
#define RDD_PROCESSING_TX_DESCRIPTOR_ABS_0_WRITE(v, p)                         FIELD_MWRITE_32((uint8_t *)p + 12, 0, 29, v)
/* <<<RDD_PROCESSING_TX_DESCRIPTOR_DTS */


#define RDD_SRAM_PD_FIFO_SIZE     16
typedef struct
{
	RDD_PROCESSING_TX_DESCRIPTOR_DTS	entry[ RDD_SRAM_PD_FIFO_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_SRAM_PD_FIFO_DTS;

extern uint32_t RDD_SRAM_PD_FIFO_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_SRAM_PD_FIFO_PTR(core_id)	( RDD_SRAM_PD_FIFO_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_SRAM_PD_FIFO_ADDRESS_ARR[core_id] ))

/* <<<SRAM_PD_FIFO */


/* >>>US_TM_BBH_TX_EGRESS_COUNTER_TABLE */

/* >>>RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint8_t	counter   	;
	uint32_t	reserved0 	:24	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved1 	;
#else
	uint32_t	reserved0 	:24	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	counter   	;
	uint32_t	reserved1 	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS fields;
} BBH_TX_EGRESS_COUNTER_ENTRY_STRUCT;
#define RDD_BBH_TX_EGRESS_COUNTER_ENTRY_COUNTER_READ_G(r, g, idx)            GROUP_MREAD_8(g, idx*sizeof(RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS), r)
#define RDD_BBH_TX_EGRESS_COUNTER_ENTRY_COUNTER_WRITE_G(v, g, idx)           GROUP_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS), v)
#define RDD_BBH_TX_EGRESS_COUNTER_ENTRY_COUNTER_READ(r, p)                   MREAD_8((uint8_t *)p, r)
#define RDD_BBH_TX_EGRESS_COUNTER_ENTRY_COUNTER_WRITE(v, p)                  MWRITE_8((uint8_t *)p, v)
/* <<<RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS */


#define RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE     8
typedef struct
{
	RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS	entry[ RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_DTS;

extern uint32_t RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_PTR(core_id)	( RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS_ARR[core_id] ))

/* <<<US_TM_BBH_TX_EGRESS_COUNTER_TABLE */


/* >>>DIRECT_PROCESSING_PD_TABLE */

/* >>>RDD_PROCESSING_RX_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	pd_info           	; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	key_index                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	fragment_type               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	options                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	reserved0                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	ctrl_key_index              	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	ctrl_fragment_type          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	sfc                         	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	reserved1                   	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	g9991_tci_sof               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_eof               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_const             	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_sid_1_0           	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint8_t	g9991_tci_sid_9_2           	; /* Member of pd_info union */
			uint16_t	g9991_length_time           	; /* Member of pd_info union */
		};
		/* Sub Union 4 */
		struct{
			uint32_t	timestamp                   	; /* Member of pd_info union */
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error_type_or_cpu_tx	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs                         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of abs_or_dsl union */
			uint32_t	reserved1_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error_type                  	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved1_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	xdsl                        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of abs_or_dsl union */
			uint32_t	reserved2_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cpu_tx                      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved2                   	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved2_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_25_28                   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved3_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_error_type_or_cpu_tx	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flow                        	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	bn1_last                    	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_last_or_abs1 union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	source_port                 	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	abs1                        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_last_or_abs1 union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sop_fpm                     	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                      	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	bn_num                      	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                         	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first                   	; /* Member of payload_offset_sop union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	pd_info           	; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	key_index                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	fragment_type               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	options                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	reserved0                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	ctrl_key_index              	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	ctrl_fragment_type          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	sfc                         	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	reserved1                   	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	g9991_tci_sof               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_eof               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_const             	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint32_t	g9991_tci_sid_1_0           	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of pd_info union */
			uint8_t	g9991_tci_sid_9_2           	; /* Member of pd_info union */
			uint16_t	g9991_length_time           	; /* Member of pd_info union */
		};
		/* Sub Union 4 */
		struct{
			uint32_t	timestamp                   	; /* Member of pd_info union */
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error_type_or_cpu_tx	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error_type                  	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved1_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs                         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of abs_or_dsl union */
			uint32_t	reserved1_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cpu_tx                      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved2                   	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved2_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	xdsl                        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of abs_or_dsl union */
			uint32_t	reserved2_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_25_28                   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of error_type_or_cpu_tx union */
			uint32_t	reserved3_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_packet_length     	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_error_type_or_cpu_tx	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_reserved          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_abs_or_dsl        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_cong      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ploam             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_serial_num        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	bn1_last                    	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_last_or_abs1 union */
			uint32_t	flow                        	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved1_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	abs1                        	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_last_or_abs1 union */
			uint32_t	source_port                 	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved2_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_bn1_last_or_abs1  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_ingress_port      	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_lan               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_cong_state        	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_1      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_error             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	sop_fpm                     	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                      	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	reserved1_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	bn_num                      	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                         	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first                   	; /* Member of payload_offset_sop union */
			uint32_t	reserved2_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 4 */
		struct{
			uint32_t	reserved4_payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_target_mem_0      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved4_agg_pd            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PROCESSING_RX_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_PROCESSING_RX_DESCRIPTOR_DTS fields;
} PROCESSING_RX_DESCRIPTOR_STRUCT;
#define RDD_PROCESSING_RX_DESCRIPTOR_PD_INFO_READ_G(r, g, idx)                     GROUP_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PD_INFO_WRITE_G(v, g, idx)                    GROUP_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PD_INFO_READ(r, p)                            MREAD_32((uint8_t *)p, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PD_INFO_WRITE(v, p)                           MWRITE_32((uint8_t *)p, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_KEY_INDEX_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_KEY_INDEX_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_KEY_INDEX_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p, 6, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_KEY_INDEX_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p, 6, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_FRAGMENT_TYPE_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_FRAGMENT_TYPE_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_FRAGMENT_TYPE_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p, 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_FRAGMENT_TYPE_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p, 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_OPTIONS_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 11, 18, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_OPTIONS_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 11, 18, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_OPTIONS_READ(r, p)                            FIELD_MREAD_32((uint8_t *)p, 11, 18, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_OPTIONS_WRITE(v, p)                           FIELD_MWRITE_32((uint8_t *)p, 11, 18, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_KEY_INDEX_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_KEY_INDEX_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_KEY_INDEX_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p, 6, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_KEY_INDEX_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p, 6, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_FRAGMENT_TYPE_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_FRAGMENT_TYPE_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_FRAGMENT_TYPE_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p, 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CTRL_FRAGMENT_TYPE_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p, 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SFC_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 3, 10, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SFC_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 3, 10, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SFC_READ(r, p)                                FIELD_MREAD_16((uint8_t *)p, 3, 10, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SFC_WRITE(v, p)                               FIELD_MWRITE_16((uint8_t *)p, 3, 10, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SOF_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SOF_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SOF_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SOF_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_EOF_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_EOF_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_EOF_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p, 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_EOF_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p, 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_CONST_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 2, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_CONST_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 2, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_CONST_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p, 2, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_CONST_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p, 2, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_1_0_READ_G(r, g, idx)           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 0, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_1_0_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), 0, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_1_0_READ(r, p)                  FIELD_MREAD_8((uint8_t *)p, 0, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_1_0_WRITE(v, p)                 FIELD_MWRITE_8((uint8_t *)p, 0, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_9_2_READ_G(r, g, idx)           GROUP_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_9_2_WRITE_G(v, g, idx)          GROUP_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_9_2_READ(r, p)                  MREAD_8((uint8_t *)p + 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_TCI_SID_9_2_WRITE(v, p)                 MWRITE_8((uint8_t *)p + 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_LENGTH_TIME_READ_G(r, g, idx)           GROUP_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_LENGTH_TIME_WRITE_G(v, g, idx)          GROUP_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_LENGTH_TIME_READ(r, p)                  MREAD_16((uint8_t *)p + 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_G9991_LENGTH_TIME_WRITE(v, p)                 MWRITE_16((uint8_t *)p + 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TIMESTAMP_READ_G(r, g, idx)                   GROUP_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TIMESTAMP_WRITE_G(v, g, idx)                  GROUP_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS), v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TIMESTAMP_READ(r, p)                          MREAD_32((uint8_t *)p, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TIMESTAMP_WRITE(v, p)                         MWRITE_32((uint8_t *)p, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SERIAL_NUM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 6, 10, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SERIAL_NUM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 6, 10, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SERIAL_NUM_READ(r, p)                         FIELD_MREAD_16((uint8_t *)p + 4, 6, 10, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SERIAL_NUM_WRITE(v, p)                        FIELD_MWRITE_16((uint8_t *)p + 4, 6, 10, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PLOAM_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PLOAM_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PLOAM_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p + 5, 5, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PLOAM_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p + 5, 5, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_CONG_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 4, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_CONG_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 4, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_CONG_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 5, 4, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_CONG_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 5, 4, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_OR_DSL_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_OR_DSL_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_OR_DSL_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_OR_DSL_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_XDSL_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_XDSL_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_XDSL_READ(r, p)                               FIELD_MREAD_8((uint8_t *)p + 5, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_XDSL_WRITE(v, p)                              FIELD_MWRITE_8((uint8_t *)p + 5, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_OR_CPU_TX_READ_G(r, g, idx)        GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_OR_CPU_TX_WRITE_G(v, g, idx)       GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_OR_CPU_TX_READ(r, p)               FIELD_MREAD_32((uint8_t *)p + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_OR_CPU_TX_WRITE(v, p)              FIELD_MWRITE_32((uint8_t *)p + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_TYPE_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CPU_TX_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 1, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CPU_TX_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 5, 1, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CPU_TX_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 5, 1, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CPU_TX_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 5, 1, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_25_28_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_25_28_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_25_28_READ(r, p)                          FIELD_MREAD_32((uint8_t *)p + 4, 14, 4, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS_25_28_WRITE(v, p)                         FIELD_MWRITE_32((uint8_t *)p + 4, 14, 4, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PACKET_LENGTH_READ_G(r, g, idx)               GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 6, 0, 14, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PACKET_LENGTH_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 6, 0, 14, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PACKET_LENGTH_READ(r, p)                      FIELD_MREAD_16((uint8_t *)p + 6, 0, 14, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PACKET_LENGTH_WRITE(v, p)                     FIELD_MWRITE_16((uint8_t *)p + 6, 0, 14, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p + 8, 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ERROR_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p + 8, 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_1_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_1_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_1_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 8, 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_1_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 8, 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CONG_STATE_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 4, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CONG_STATE_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 4, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_CONG_STATE_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 8, 4, 2, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_CONG_STATE_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 8, 4, 2, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_LAN_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_LAN_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_LAN_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p + 8, 3, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_LAN_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p + 8, 3, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_PORT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_PORT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_PORT_READ(r, p)                       FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_INGRESS_PORT_WRITE(v, p)                      FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_FLOW_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_FLOW_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_FLOW_READ(r, p)                               FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_FLOW_WRITE(v, p)                              FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOURCE_PORT_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOURCE_PORT_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOURCE_PORT_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOURCE_PORT_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_OR_ABS1_READ_G(r, g, idx)            GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_OR_ABS1_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_OR_ABS1_READ(r, p)                   FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_OR_ABS1_WRITE(v, p)                  FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_READ(r, p)                           FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN1_LAST_WRITE(v, p)                          FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS1_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS1_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS1_READ(r, p)                               FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_ABS1_WRITE(v, p)                              FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_AGG_PD_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_AGG_PD_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_AGG_PD_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 12, 7, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_AGG_PD_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 12, 7, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_0_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_0_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_0_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 12, 6, 1, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_TARGET_MEM_0_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 12, 6, 1, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ_G(r, g, idx)          GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 0, 30, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 0, 30, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ(r, p)                 FIELD_MREAD_32((uint8_t *)p + 12, 0, 30, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE(v, p)                FIELD_MWRITE_32((uint8_t *)p + 12, 0, 30, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_FPM_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 3, 11, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_FPM_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 3, 11, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_FPM_READ(r, p)                            FIELD_MREAD_16((uint8_t *)p + 12, 3, 11, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_FPM_WRITE(v, p)                           FIELD_MWRITE_16((uint8_t *)p + 12, 3, 11, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_FPM_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_FPM_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_FPM_READ(r, p)                             FIELD_MREAD_32((uint8_t *)p + 12, 0, 19, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_FPM_WRITE(v, p)                            FIELD_MWRITE_32((uint8_t *)p + 12, 0, 19, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_NUM_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 7, 7, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_NUM_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 12, 7, 7, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_NUM_READ(r, p)                             FIELD_MREAD_16((uint8_t *)p + 12, 7, 7, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN_NUM_WRITE(v, p)                            FIELD_MWRITE_16((uint8_t *)p + 12, 7, 7, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 13, 0, 7, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 13, 0, 7, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p + 13, 0, 7, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_SOP_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p + 13, 0, 7, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN0_FIRST_READ_G(r, g, idx)                   GROUP_MREAD_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 14, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN0_FIRST_WRITE_G(v, g, idx)                  GROUP_MWRITE_16(g, idx*sizeof(RDD_PROCESSING_RX_DESCRIPTOR_DTS) + 14, v)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN0_FIRST_READ(r, p)                          MREAD_16((uint8_t *)p + 14, r)
#define RDD_PROCESSING_RX_DESCRIPTOR_BN0_FIRST_WRITE(v, p)                         MWRITE_16((uint8_t *)p + 14, v)
/* <<<RDD_PROCESSING_RX_DESCRIPTOR_DTS */


#define RDD_DIRECT_PROCESSING_PD_TABLE_SIZE     2
typedef struct
{
	RDD_PROCESSING_RX_DESCRIPTOR_DTS	entry[ RDD_DIRECT_PROCESSING_PD_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_DIRECT_PROCESSING_PD_TABLE_DTS;

extern uint32_t RDD_DIRECT_PROCESSING_PD_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_DIRECT_PROCESSING_PD_TABLE_PTR(core_id)	( RDD_DIRECT_PROCESSING_PD_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_DIRECT_PROCESSING_PD_TABLE_ADDRESS_ARR[core_id] ))

/* <<<DIRECT_PROCESSING_PD_TABLE */


/* >>>CPU_RX_SCRATCHPAD */

/* >>>RDD_BYTES_4_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	bits      	;
#else
	uint32_t	bits      	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BYTES_4_DTS;

typedef union
{
    uint32_t word_val[1];
    RDD_BYTES_4_DTS fields;
} BYTES_4_STRUCT;
#define RDD_BYTES_4_BITS_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_BYTES_4_DTS), r)
#define RDD_BYTES_4_BITS_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_BYTES_4_DTS), v)
#define RDD_BYTES_4_BITS_READ(r, p)                 MREAD_32((uint8_t *)p, r)
#define RDD_BYTES_4_BITS_WRITE(v, p)                MWRITE_32((uint8_t *)p, v)
/* <<<RDD_BYTES_4_DTS */


#define RDD_CPU_RX_SCRATCHPAD_SIZE     384
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_RX_SCRATCHPAD_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_SCRATCHPAD_DTS;

extern uint32_t RDD_CPU_RX_SCRATCHPAD_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_SCRATCHPAD_PTR(core_id)	( RDD_CPU_RX_SCRATCHPAD_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_SCRATCHPAD_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_SCRATCHPAD */


/* >>>CPU_TX_SCRATCHPAD */

#define RDD_CPU_TX_SCRATCHPAD_SIZE     384
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_TX_SCRATCHPAD_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_SCRATCHPAD_DTS;

extern uint32_t RDD_CPU_TX_SCRATCHPAD_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_TX_SCRATCHPAD_PTR(core_id)	( RDD_CPU_TX_SCRATCHPAD_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_TX_SCRATCHPAD_ADDRESS_ARR[core_id] ))

/* <<<CPU_TX_SCRATCHPAD */


/* >>>BBH_TX_RING_TABLE */

/* >>>RDD_BBH_TX_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	sid_9_2       	;
			uint16_t	frag_length   	;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved1_sid_9_2       	;
			uint16_t	reserved1_frag_length   	;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved2_sid_9_2       	;
			uint16_t	reserved2_frag_length   	;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved3_sid_9_2       	;
			uint16_t	reserved3_frag_length   	;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	buffer_number_1_or_abs_2	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flow                    	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	bn1_first               	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	source_port             	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved1               	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
			uint32_t	abs_1                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_buffer_number_1_or_abs_2	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sop_fpm                 	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	bn_num                  	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                     	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first               	; /* Member of payload_offset_sop union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	abs_0                   	:29	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint16_t	frag_length   	;
			uint8_t	sid_9_2       	;
			uint32_t	sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint16_t	reserved1_frag_length   	;
			uint8_t	reserved1_sid_9_2       	;
			uint32_t	reserved1_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint16_t	reserved2_frag_length   	;
			uint8_t	reserved2_sid_9_2       	;
			uint32_t	reserved2_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint16_t	reserved3_frag_length   	;
			uint8_t	reserved3_sid_9_2       	;
			uint32_t	reserved3_sid_1_0       	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_g9991_const   	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_eof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_sof           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_packet_length 	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved0     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_cong  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_hn            	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_coherent      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_g9991_frag    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_fpm_free_dis  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_mc_header_size	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_last          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	buffer_number_1_or_abs_2	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	bn1_first               	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
			uint32_t	flow                    	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved1_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved1               	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
			uint32_t	abs_1                   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_1_or_abs_2 union */
			uint32_t	source_port             	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of ingress_port union */
			uint32_t	reserved2_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_buffer_number_1_or_abs_2	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_ingress_port  	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_cong_state    	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_1  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_error         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	payload_offset_sop	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	sop_fpm                 	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	bn_fpm                  	:19	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	reserved1_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	bn_num                  	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	sop                     	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint16_t	bn0_first               	; /* Member of payload_offset_sop union */
			uint32_t	reserved2_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	abs_0                   	:29	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_sop union */
			uint32_t	reserved3_target_mem_0  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_agg_pd        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BBH_TX_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_BBH_TX_DESCRIPTOR_DTS fields;
} BBH_TX_DESCRIPTOR_STRUCT;
#define RDD_BBH_TX_DESCRIPTOR_SOF_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_SOF_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_SOF_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_SOF_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_EOF_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_EOF_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_EOF_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_EOF_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_G9991_CONST_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 2, 4, r)
#define RDD_BBH_TX_DESCRIPTOR_G9991_CONST_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 2, 4, v)
#define RDD_BBH_TX_DESCRIPTOR_G9991_CONST_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p, 2, 4, r)
#define RDD_BBH_TX_DESCRIPTOR_G9991_CONST_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p, 2, 4, v)
#define RDD_BBH_TX_DESCRIPTOR_SID_1_0_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 0, 2, r)
#define RDD_BBH_TX_DESCRIPTOR_SID_1_0_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS), 0, 2, v)
#define RDD_BBH_TX_DESCRIPTOR_SID_1_0_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p, 0, 2, r)
#define RDD_BBH_TX_DESCRIPTOR_SID_1_0_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p, 0, 2, v)
#define RDD_BBH_TX_DESCRIPTOR_SID_9_2_READ_G(r, g, idx)                 GROUP_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 1, r)
#define RDD_BBH_TX_DESCRIPTOR_SID_9_2_WRITE_G(v, g, idx)                GROUP_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 1, v)
#define RDD_BBH_TX_DESCRIPTOR_SID_9_2_READ(r, p)                        MREAD_8((uint8_t *)p + 1, r)
#define RDD_BBH_TX_DESCRIPTOR_SID_9_2_WRITE(v, p)                       MWRITE_8((uint8_t *)p + 1, v)
#define RDD_BBH_TX_DESCRIPTOR_FRAG_LENGTH_READ_G(r, g, idx)             GROUP_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 2, r)
#define RDD_BBH_TX_DESCRIPTOR_FRAG_LENGTH_WRITE_G(v, g, idx)            GROUP_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 2, v)
#define RDD_BBH_TX_DESCRIPTOR_FRAG_LENGTH_READ(r, p)                    MREAD_16((uint8_t *)p + 2, r)
#define RDD_BBH_TX_DESCRIPTOR_FRAG_LENGTH_WRITE(v, p)                   MWRITE_16((uint8_t *)p + 2, v)
#define RDD_BBH_TX_DESCRIPTOR_LAST_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_LAST_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_LAST_READ(r, p)                           FIELD_MREAD_8((uint8_t *)p + 4, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_LAST_WRITE(v, p)                          FIELD_MWRITE_8((uint8_t *)p + 4, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_MC_HEADER_SIZE_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_MC_HEADER_SIZE_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_MC_HEADER_SIZE_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 4, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_MC_HEADER_SIZE_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 4, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_FPM_FREE_DIS_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 5, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_FPM_FREE_DIS_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 5, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_FPM_FREE_DIS_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 4, 5, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_FPM_FREE_DIS_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 4, 5, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_G9991_FRAG_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 4, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_G9991_FRAG_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 4, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_G9991_FRAG_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 4, 4, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_G9991_FRAG_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 4, 4, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_FLAG_1588_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_FLAG_1588_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_FLAG_1588_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 4, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_FLAG_1588_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 4, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_COHERENT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 2, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_COHERENT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 2, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_COHERENT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 4, 2, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_COHERENT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 4, 2, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_HN_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 5, 5, r)
#define RDD_BBH_TX_DESCRIPTOR_HN_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 4, 5, 5, v)
#define RDD_BBH_TX_DESCRIPTOR_HN_READ(r, p)                             FIELD_MREAD_16((uint8_t *)p + 4, 5, 5, r)
#define RDD_BBH_TX_DESCRIPTOR_HN_WRITE(v, p)                            FIELD_MWRITE_16((uint8_t *)p + 4, 5, 5, v)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_CONG_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 5, 4, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_CONG_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 5, 4, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_CONG_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 5, 4, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_CONG_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 5, 4, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 5, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 5, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 5, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 5, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_PACKET_LENGTH_READ_G(r, g, idx)           GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 6, 0, 14, r)
#define RDD_BBH_TX_DESCRIPTOR_PACKET_LENGTH_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 6, 0, 14, v)
#define RDD_BBH_TX_DESCRIPTOR_PACKET_LENGTH_READ(r, p)                  FIELD_MREAD_16((uint8_t *)p + 6, 0, 14, r)
#define RDD_BBH_TX_DESCRIPTOR_PACKET_LENGTH_WRITE(v, p)                 FIELD_MWRITE_16((uint8_t *)p + 6, 0, 14, v)
#define RDD_BBH_TX_DESCRIPTOR_ERROR_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_ERROR_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_ERROR_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p + 8, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_ERROR_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p + 8, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_1_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_1_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_1_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 8, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_1_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 8, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_CONG_STATE_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 4, 2, r)
#define RDD_BBH_TX_DESCRIPTOR_CONG_STATE_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 4, 2, v)
#define RDD_BBH_TX_DESCRIPTOR_CONG_STATE_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 8, 4, 2, r)
#define RDD_BBH_TX_DESCRIPTOR_CONG_STATE_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 8, 4, 2, v)
#define RDD_BBH_TX_DESCRIPTOR_LAN_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_LAN_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_LAN_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 8, 3, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_LAN_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 8, 3, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_PORT_READ_G(r, g, idx)            GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_PORT_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_PORT_READ(r, p)                   FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_INGRESS_PORT_WRITE(v, p)                  FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_FLOW_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_FLOW_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_FLOW_READ(r, p)                           FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_FLOW_WRITE(v, p)                          FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_SOURCE_PORT_READ_G(r, g, idx)             GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_SOURCE_PORT_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_SOURCE_PORT_READ(r, p)                    FIELD_MREAD_16((uint8_t *)p + 8, 3, 8, r)
#define RDD_BBH_TX_DESCRIPTOR_SOURCE_PORT_WRITE(v, p)                   FIELD_MWRITE_16((uint8_t *)p + 8, 3, 8, v)
#define RDD_BBH_TX_DESCRIPTOR_BUFFER_NUMBER_1_OR_ABS_2_READ_G(r, g, idx)GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BUFFER_NUMBER_1_OR_ABS_2_WRITE_G(v, g, idx)GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_BUFFER_NUMBER_1_OR_ABS_2_READ(r, p)       FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BUFFER_NUMBER_1_OR_ABS_2_WRITE(v, p)      FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_BN1_FIRST_READ_G(r, g, idx)               GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BN1_FIRST_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 8, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_BN1_FIRST_READ(r, p)                      FIELD_MREAD_32((uint8_t *)p + 8, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BN1_FIRST_WRITE(v, p)                     FIELD_MWRITE_32((uint8_t *)p + 8, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_1_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 10, 0, 11, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_1_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 10, 0, 11, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_1_READ(r, p)                          FIELD_MREAD_16((uint8_t *)p + 10, 0, 11, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_1_WRITE(v, p)                         FIELD_MWRITE_16((uint8_t *)p + 10, 0, 11, v)
#define RDD_BBH_TX_DESCRIPTOR_AGG_PD_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_AGG_PD_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_AGG_PD_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 12, 7, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_AGG_PD_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 12, 7, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_0_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_0_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_0_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 12, 6, 1, r)
#define RDD_BBH_TX_DESCRIPTOR_TARGET_MEM_0_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 12, 6, 1, v)
#define RDD_BBH_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ_G(r, g, idx)      GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 30, r)
#define RDD_BBH_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE_G(v, g, idx)     GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 30, v)
#define RDD_BBH_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_READ(r, p)             FIELD_MREAD_32((uint8_t *)p + 12, 0, 30, r)
#define RDD_BBH_TX_DESCRIPTOR_PAYLOAD_OFFSET_SOP_WRITE(v, p)            FIELD_MWRITE_32((uint8_t *)p + 12, 0, 30, v)
#define RDD_BBH_TX_DESCRIPTOR_SOP_FPM_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 3, 11, r)
#define RDD_BBH_TX_DESCRIPTOR_SOP_FPM_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 3, 11, v)
#define RDD_BBH_TX_DESCRIPTOR_SOP_FPM_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 12, 3, 11, r)
#define RDD_BBH_TX_DESCRIPTOR_SOP_FPM_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 12, 3, 11, v)
#define RDD_BBH_TX_DESCRIPTOR_BN_FPM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BN_FPM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_BN_FPM_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 12, 0, 19, r)
#define RDD_BBH_TX_DESCRIPTOR_BN_FPM_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 12, 0, 19, v)
#define RDD_BBH_TX_DESCRIPTOR_BN_NUM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 7, 7, r)
#define RDD_BBH_TX_DESCRIPTOR_BN_NUM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 7, 7, v)
#define RDD_BBH_TX_DESCRIPTOR_BN_NUM_READ(r, p)                         FIELD_MREAD_16((uint8_t *)p + 12, 7, 7, r)
#define RDD_BBH_TX_DESCRIPTOR_BN_NUM_WRITE(v, p)                        FIELD_MWRITE_16((uint8_t *)p + 12, 7, 7, v)
#define RDD_BBH_TX_DESCRIPTOR_SOP_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 13, 0, 7, r)
#define RDD_BBH_TX_DESCRIPTOR_SOP_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 13, 0, 7, v)
#define RDD_BBH_TX_DESCRIPTOR_SOP_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 13, 0, 7, r)
#define RDD_BBH_TX_DESCRIPTOR_SOP_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 13, 0, 7, v)
#define RDD_BBH_TX_DESCRIPTOR_BN0_FIRST_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 14, r)
#define RDD_BBH_TX_DESCRIPTOR_BN0_FIRST_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 14, v)
#define RDD_BBH_TX_DESCRIPTOR_BN0_FIRST_READ(r, p)                      MREAD_16((uint8_t *)p + 14, r)
#define RDD_BBH_TX_DESCRIPTOR_BN0_FIRST_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 14, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_0_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 29, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_0_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_BBH_TX_DESCRIPTOR_DTS) + 12, 0, 29, v)
#define RDD_BBH_TX_DESCRIPTOR_ABS_0_READ(r, p)                          FIELD_MREAD_32((uint8_t *)p + 12, 0, 29, r)
#define RDD_BBH_TX_DESCRIPTOR_ABS_0_WRITE(v, p)                         FIELD_MWRITE_32((uint8_t *)p + 12, 0, 29, v)
/* <<<RDD_BBH_TX_DESCRIPTOR_DTS */

typedef struct
{
	RDD_BBH_TX_DESCRIPTOR_DTS	entry;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BBH_TX_RING_TABLE_DTS;

extern uint32_t RDD_BBH_TX_RING_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_BBH_TX_RING_TABLE_PTR(core_id)	( RDD_BBH_TX_RING_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_BBH_TX_RING_TABLE_ADDRESS_ARR[core_id] ))

/* <<<BBH_TX_RING_TABLE */


/* >>>CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE */

#define RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_SIZE     3
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_DTS;

extern uint32_t RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_PTR(core_id)	( RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS_ARR[core_id] ))

/* <<<CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE */


/* >>>BBH_TX_BB_DESTINATION_TABLE */

/* >>>RDD_BB_DESTINATION_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	bb_destination	;
#else
	uint32_t	bb_destination	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BB_DESTINATION_ENTRY_DTS;

typedef union
{
    uint32_t word_val[1];
    RDD_BB_DESTINATION_ENTRY_DTS fields;
} BB_DESTINATION_ENTRY_STRUCT;
#define RDD_BB_DESTINATION_ENTRY_BB_DESTINATION_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_BB_DESTINATION_ENTRY_DTS), r)
#define RDD_BB_DESTINATION_ENTRY_BB_DESTINATION_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_BB_DESTINATION_ENTRY_DTS), v)
#define RDD_BB_DESTINATION_ENTRY_BB_DESTINATION_READ(r, p)                 MREAD_32((uint8_t *)p, r)
#define RDD_BB_DESTINATION_ENTRY_BB_DESTINATION_WRITE(v, p)                MWRITE_32((uint8_t *)p, v)
/* <<<RDD_BB_DESTINATION_ENTRY_DTS */

typedef struct
{
	RDD_BB_DESTINATION_ENTRY_DTS	entry;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BBH_TX_BB_DESTINATION_TABLE_DTS;

extern uint32_t RDD_BBH_TX_BB_DESTINATION_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_BBH_TX_BB_DESTINATION_TABLE_PTR(core_id)	( RDD_BBH_TX_BB_DESTINATION_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_BBH_TX_BB_DESTINATION_TABLE_ADDRESS_ARR[core_id] ))

/* <<<BBH_TX_BB_DESTINATION_TABLE */


/* >>>CPU_RX_CFE_SRAM_COUNTERS */

/* >>>RDD_PACKETS_AND_BYTES_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	packets   	;
	uint32_t	bytes     	;
#else
	uint32_t	packets   	;
	uint32_t	bytes     	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PACKETS_AND_BYTES_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_PACKETS_AND_BYTES_DTS fields;
} PACKETS_AND_BYTES_STRUCT;
#define RDD_PACKETS_AND_BYTES_PACKETS_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_PACKETS_AND_BYTES_DTS), r)
#define RDD_PACKETS_AND_BYTES_PACKETS_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_PACKETS_AND_BYTES_DTS), v)
#define RDD_PACKETS_AND_BYTES_PACKETS_READ(r, p)                 MREAD_32((uint8_t *)p, r)
#define RDD_PACKETS_AND_BYTES_PACKETS_WRITE(v, p)                MWRITE_32((uint8_t *)p, v)
#define RDD_PACKETS_AND_BYTES_BYTES_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_PACKETS_AND_BYTES_DTS) + 4, r)
#define RDD_PACKETS_AND_BYTES_BYTES_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_PACKETS_AND_BYTES_DTS) + 4, v)
#define RDD_PACKETS_AND_BYTES_BYTES_READ(r, p)                   MREAD_32((uint8_t *)p + 4, r)
#define RDD_PACKETS_AND_BYTES_BYTES_WRITE(v, p)                  MWRITE_32((uint8_t *)p + 4, v)
/* <<<RDD_PACKETS_AND_BYTES_DTS */


#define RDD_CPU_RX_CFE_SRAM_COUNTERS_SIZE     10
typedef struct
{
	RDD_PACKETS_AND_BYTES_DTS	entry[ RDD_CPU_RX_CFE_SRAM_COUNTERS_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_CFE_SRAM_COUNTERS_DTS;

extern uint32_t RDD_CPU_RX_CFE_SRAM_COUNTERS_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_CFE_SRAM_COUNTERS_PTR(core_id)	( RDD_CPU_RX_CFE_SRAM_COUNTERS_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_CFE_SRAM_COUNTERS_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_CFE_SRAM_COUNTERS */


/* >>>CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE */

#define RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_SIZE     3
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_DTS;

extern uint32_t RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_PTR(core_id)	( RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS_ARR[core_id] ))

/* <<<CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE */


/* >>>TASK_IDX */
typedef struct
{
	RDD_BYTES_4_DTS	entry;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_TASK_IDX_DTS;

extern uint32_t RDD_TASK_IDX_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_TASK_IDX_PTR(core_id)	( RDD_TASK_IDX_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_TASK_IDX_ADDRESS_ARR[core_id] ))

/* <<<TASK_IDX */


/* >>>CPU_RX_INTERRUPT_SCRATCH */

/* >>>RDD_BYTE_1_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint8_t	bits      	;
#else
	uint8_t	bits      	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BYTE_1_DTS;

#define RDD_BYTE_1_BITS_READ_G(r, g, idx)          GROUP_MREAD_8(g, idx*sizeof(RDD_BYTE_1_DTS), r)
#define RDD_BYTE_1_BITS_WRITE_G(v, g, idx)         GROUP_MWRITE_8(g, idx*sizeof(RDD_BYTE_1_DTS), v)
#define RDD_BYTE_1_BITS_READ(r, p)                 MREAD_8((uint8_t *)p, r)
#define RDD_BYTE_1_BITS_WRITE(v, p)                MWRITE_8((uint8_t *)p, v)
/* <<<RDD_BYTE_1_DTS */


#define RDD_CPU_RX_INTERRUPT_SCRATCH_SIZE     8
typedef struct
{
	RDD_BYTE_1_DTS	entry[ RDD_CPU_RX_INTERRUPT_SCRATCH_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_INTERRUPT_SCRATCH_DTS;

extern uint32_t RDD_CPU_RX_INTERRUPT_SCRATCH_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_INTERRUPT_SCRATCH_PTR(core_id)	( RDD_CPU_RX_INTERRUPT_SCRATCH_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_INTERRUPT_SCRATCH_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_INTERRUPT_SCRATCH */


/* >>>CPU_RX_INTERRUPT_ID_DDR_ADDR */

#define RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_SIZE     8
typedef struct
{
	RDD_BYTE_1_DTS	entry[ RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_DTS;

extern uint32_t RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_PTR(core_id)	( RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_INTERRUPT_ID_DDR_ADDR_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_INTERRUPT_ID_DDR_ADDR */


/* >>>PKT_BUFFER_ALLOC_MAP_TABLE */

#define RDD_PKT_BUFFER_ALLOC_MAP_TABLE_SIZE     3
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_PKT_BUFFER_ALLOC_MAP_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PKT_BUFFER_ALLOC_MAP_TABLE_DTS;

extern uint32_t RDD_PKT_BUFFER_ALLOC_MAP_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_PKT_BUFFER_ALLOC_MAP_TABLE_PTR(core_id)	( RDD_PKT_BUFFER_ALLOC_MAP_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_PKT_BUFFER_ALLOC_MAP_TABLE_ADDRESS_ARR[core_id] ))

/* <<<PKT_BUFFER_ALLOC_MAP_TABLE */


/* >>>CPU_RX_LAST_READ_INDEX */

/* >>>RDD_BYTES_2_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint16_t	bits      	;
#else
	uint16_t	bits      	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BYTES_2_DTS;

#define RDD_BYTES_2_BITS_READ_G(r, g, idx)          GROUP_MREAD_16(g, idx*sizeof(RDD_BYTES_2_DTS), r)
#define RDD_BYTES_2_BITS_WRITE_G(v, g, idx)         GROUP_MWRITE_16(g, idx*sizeof(RDD_BYTES_2_DTS), v)
#define RDD_BYTES_2_BITS_READ(r, p)                 MREAD_16((uint8_t *)p, r)
#define RDD_BYTES_2_BITS_WRITE(v, p)                MWRITE_16((uint8_t *)p, v)
/* <<<RDD_BYTES_2_DTS */

typedef struct
{
	RDD_BYTES_2_DTS	entry;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_LAST_READ_INDEX_DTS;

extern uint32_t RDD_CPU_RX_LAST_READ_INDEX_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_LAST_READ_INDEX_PTR(core_id)	( RDD_CPU_RX_LAST_READ_INDEX_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_LAST_READ_INDEX_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_LAST_READ_INDEX */


/* >>>SRAM_DUMMY_STORE */
typedef struct
{
	RDD_BYTE_1_DTS	entry;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_SRAM_DUMMY_STORE_DTS;

extern uint32_t RDD_SRAM_DUMMY_STORE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_SRAM_DUMMY_STORE_PTR(core_id)	( RDD_SRAM_DUMMY_STORE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_SRAM_DUMMY_STORE_ADDRESS_ARR[core_id] ))

/* <<<SRAM_DUMMY_STORE */


/* >>>CPU_TX_CFE_SRAM_COUNTERS */

#define RDD_CPU_TX_CFE_SRAM_COUNTERS_SIZE     10
typedef struct
{
	RDD_PACKETS_AND_BYTES_DTS	entry[ RDD_CPU_TX_CFE_SRAM_COUNTERS_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_CFE_SRAM_COUNTERS_DTS;

extern uint32_t RDD_CPU_TX_CFE_SRAM_COUNTERS_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_TX_CFE_SRAM_COUNTERS_PTR(core_id)	( RDD_CPU_TX_CFE_SRAM_COUNTERS_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_TX_CFE_SRAM_COUNTERS_ADDRESS_ARR[core_id] ))

/* <<<CPU_TX_CFE_SRAM_COUNTERS */


/* >>>CPU_RX_BB_REPLY_ADDR_TABLE */

#define RDD_CPU_RX_BB_REPLY_ADDR_TABLE_SIZE     2
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_RX_BB_REPLY_ADDR_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_BB_REPLY_ADDR_TABLE_DTS;

extern uint32_t RDD_CPU_RX_BB_REPLY_ADDR_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_RX_BB_REPLY_ADDR_TABLE_PTR(core_id)	( RDD_CPU_RX_BB_REPLY_ADDR_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_RX_BB_REPLY_ADDR_TABLE_ADDRESS_ARR[core_id] ))

/* <<<CPU_RX_BB_REPLY_ADDR_TABLE */


/* >>>CPU_TX_BB_REPLY_ADDR_TABLE */

#define RDD_CPU_TX_BB_REPLY_ADDR_TABLE_SIZE     2
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_CPU_TX_BB_REPLY_ADDR_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_BB_REPLY_ADDR_TABLE_DTS;

extern uint32_t RDD_CPU_TX_BB_REPLY_ADDR_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_CPU_TX_BB_REPLY_ADDR_TABLE_PTR(core_id)	( RDD_CPU_TX_BB_REPLY_ADDR_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_CPU_TX_BB_REPLY_ADDR_TABLE_ADDRESS_ARR[core_id] ))

/* <<<CPU_TX_BB_REPLY_ADDR_TABLE */


/* >>>DS_TM_BBH_TX_EGRESS_COUNTER_TABLE */

#define RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE     8
typedef struct
{
	RDD_BBH_TX_EGRESS_COUNTER_ENTRY_DTS	entry[ RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_DTS;

extern uint32_t RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_PTR(core_id)	( RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS_ARR[core_id] ))

/* <<<DS_TM_BBH_TX_EGRESS_COUNTER_TABLE */


/* >>>REGISTERS_BUFFER */

#define RDD_REGISTERS_BUFFER_SIZE     32
typedef struct
{
	RDD_BYTES_4_DTS	entry[ RDD_REGISTERS_BUFFER_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_REGISTERS_BUFFER_DTS;

extern uint32_t RDD_REGISTERS_BUFFER_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_REGISTERS_BUFFER_PTR(core_id)	( RDD_REGISTERS_BUFFER_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_REGISTERS_BUFFER_ADDRESS_ARR[core_id] ))

/* <<<REGISTERS_BUFFER */


/* >>>RX_FLOW_TABLE */

/* >>>RDD_RX_FLOW_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint16_t	virtual_port	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	flow_dest   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	exception   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	reserved    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	cntr_id     	;
#else
	uint8_t	cntr_id     	;
	uint16_t	reserved    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	exception   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	flow_dest   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	virtual_port	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_RX_FLOW_ENTRY_DTS;

#define RDD_RX_FLOW_ENTRY_VIRTUAL_PORT_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 3, 5, r)
#define RDD_RX_FLOW_ENTRY_VIRTUAL_PORT_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 3, 5, v)
#define RDD_RX_FLOW_ENTRY_VIRTUAL_PORT_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p, 3, 5, r)
#define RDD_RX_FLOW_ENTRY_VIRTUAL_PORT_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p, 3, 5, v)
#define RDD_RX_FLOW_ENTRY_FLOW_DEST_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 2, 1, r)
#define RDD_RX_FLOW_ENTRY_FLOW_DEST_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 2, 1, v)
#define RDD_RX_FLOW_ENTRY_FLOW_DEST_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p, 2, 1, r)
#define RDD_RX_FLOW_ENTRY_FLOW_DEST_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p, 2, 1, v)
#define RDD_RX_FLOW_ENTRY_EXCEPTION_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 1, 1, r)
#define RDD_RX_FLOW_ENTRY_EXCEPTION_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS), 1, 1, v)
#define RDD_RX_FLOW_ENTRY_EXCEPTION_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p, 1, 1, r)
#define RDD_RX_FLOW_ENTRY_EXCEPTION_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p, 1, 1, v)
#define RDD_RX_FLOW_ENTRY_CNTR_ID_READ_G(r, g, idx)               GROUP_MREAD_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS) + 1, r)
#define RDD_RX_FLOW_ENTRY_CNTR_ID_WRITE_G(v, g, idx)              GROUP_MWRITE_8(g, idx*sizeof(RDD_RX_FLOW_ENTRY_DTS) + 1, v)
#define RDD_RX_FLOW_ENTRY_CNTR_ID_READ(r, p)                      MREAD_8((uint8_t *)p + 1, r)
#define RDD_RX_FLOW_ENTRY_CNTR_ID_WRITE(v, p)                     MWRITE_8((uint8_t *)p + 1, v)
/* <<<RDD_RX_FLOW_ENTRY_DTS */


#define RDD_RX_FLOW_TABLE_SIZE     320
typedef struct
{
	RDD_RX_FLOW_ENTRY_DTS	entry[ RDD_RX_FLOW_TABLE_SIZE ];
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_RX_FLOW_TABLE_DTS;

extern uint32_t RDD_RX_FLOW_TABLE_ADDRESS_ARR[GROUPED_EN_SEGMENTS_NUM];

#define RDD_RX_FLOW_TABLE_PTR(core_id)	( RDD_RX_FLOW_TABLE_DTS * )(DEVICE_ADDRESS( rdp_runner_core_addr[core_id] + RDD_RX_FLOW_TABLE_ADDRESS_ARR[core_id] ))

/* <<<RX_FLOW_TABLE */


/* >>>RDD_DISP_REOR_VIQ */
typedef enum
{
	DISP_REOR_VIQ_FIRST             = 0,
	DISP_REOR_VIQ_BBH_RX0_NORMAL    = 0,
	DISP_REOR_VIQ_BBH_RX1_NORMAL    = 1,
	DISP_REOR_VIQ_BBH_RX2_NORMAL    = 2,
	DISP_REOR_VIQ_BBH_RX3_NORMAL    = 3,
	DISP_REOR_VIQ_BBH_RX4_NORMAL    = 4,
	DISP_REOR_VIQ_BBH_RX5_NORMAL    = 5,
	DISP_REOR_VIQ_BBH_RX0_EXCL      = 6,
	DISP_REOR_VIQ_BBH_RX1_EXCL      = 7,
	DISP_REOR_VIQ_BBH_RX2_EXCL      = 8,
	DISP_REOR_VIQ_BBH_RX3_EXCL      = 9,
	DISP_REOR_VIQ_BBH_RX4_EXCL      = 10,
	DISP_REOR_VIQ_BBH_RX5_EXCL      = 11,
	DISP_REOR_VIQ_CPU_TX_EGRESS     = 12,
	DISP_REOR_VIQ_CPU_RX_COPY       = 13,
	DISP_REOR_VIQ_LAST              = 13
} rdd_disp_reor_viq;
/* <<<RDD_DISP_REOR_VIQ */


/* >>>RDD_IMAGE_0_CFE_CORE */
typedef enum
{
	IMAGE_0_CFE_CORE_FIRST           = 0,
	IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER = 0,
	IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER = 1,
	IMAGE_0_CFE_CORE_LAST            = 1
} rdd_cfe_core;
/* <<<RDD_IMAGE_0_CFE_CORE */


/* >>>RDD_CPU_IF_RDD */
typedef enum
{
	CPU_IF_RDD_FIRST      = 0,
	CPU_IF_RDD_DATA       = 0,
	CPU_IF_RDD_RECYCLE    = 1,
	CPU_IF_RDD_FEED       = 2,
	CPU_IF_RDD_LAST       = 2
} rdd_cpu_if_rdd;
/* <<<RDD_CPU_IF_RDD */


/* >>>RDD_FLOW_DEST */
typedef enum
{
	FLOW_DEST_FIRST      = 0,
	FLOW_DEST_ETH_ID     = 0,
	FLOW_DEST_IPTV_ID    = 1,
	FLOW_DEST_LAST       = 1
} rdd_flow_dest;
/* <<<RDD_FLOW_DEST */


/* >>>RDD_PACKET_BUFFER_POOL_TABLE_ADDR */
typedef enum
{
	PACKET_BUFFER_POOL_TABLE_ADDR_FIRST = 2181087232,
	PACKET_BUFFER_POOL_TABLE_ADDR_RX    = 2181087232,
	PACKET_BUFFER_POOL_TABLE_ADDR_TX    = 2181099520,
	PACKET_BUFFER_POOL_TABLE_ADDR_LAST  = 2181099520
} rdd_packet_buffer_pool_table_addr;
/* <<<RDD_PACKET_BUFFER_POOL_TABLE_ADDR */


/* >>>RDD_PACKET_BUFFER_START_TOKEN */
typedef enum
{
	PACKET_BUFFER_START_TOKEN_FIRST = 384,
	PACKET_BUFFER_START_TOKEN_RX    = 384,
	PACKET_BUFFER_START_TOKEN_TX    = 480,
	PACKET_BUFFER_START_TOKEN_LAST  = 480
} rdd_packet_buffer_start_token;
/* <<<RDD_PACKET_BUFFER_START_TOKEN */


/* >>>RDD_ACTION */
typedef enum
{
	ACTION_FIRST        = 0,
	ACTION_FORWARD      = 0,
	ACTION_TRAP         = 1,
	ACTION_DROP         = 2,
	ACTION_MULTICAST    = 3,
	ACTION_LAST         = 3
} rdd_action;
/* <<<RDD_ACTION */


/* >>>RDD_LAYER3_IPV6_HEADER */
typedef enum
{
	LAYER3_IPV6_HEADER_FIRST            = 8,
	LAYER3_IPV6_HEADER_SRC_IP_OFFSET    = 8,
	LAYER3_IPV6_HEADER_DST_IP_OFFSET    = 24,
	LAYER3_IPV6_HEADER_LAST             = 24
} rdd_layer3_ipv6_header;
/* <<<RDD_LAYER3_IPV6_HEADER */


/* >>>RDD_LAYER3_HEADER */
typedef enum
{
	LAYER3_HEADER_FIRST                  = 0,
	LAYER3_HEADER_TRAFIC_CLASS_OFFSET    = 0,
	LAYER3_HEADER_TOS_OFFSET             = 1,
	LAYER3_HEADER_FLAGS_OFFSET           = 6,
	LAYER3_HEADER_HOP_LIMIT_OFFSET       = 7,
	LAYER3_HEADER_TTL_OFFSET             = 8,
	LAYER3_HEADER_PROTOCOL_OFFSET        = 9,
	LAYER3_HEADER_IP_CHECKSUM_OFFSET     = 10,
	LAYER3_HEADER_SRC_IP_OFFSET          = 12,
	LAYER3_HEADER_DST_IP_OFFSET          = 16,
	LAYER3_HEADER_LAST                   = 16
} rdd_layer3_header;
/* <<<RDD_LAYER3_HEADER */


/* >>>RDD_LAYER4_HEADER */
typedef enum
{
	LAYER4_HEADER_FIRST                  = 0,
	LAYER4_HEADER_SRC_PORT_OFFSET        = 0,
	LAYER4_HEADER_ESP_SPI_OFFSET         = 0,
	LAYER4_HEADER_DST_PORT_OFFSET        = 2,
	LAYER4_HEADER_UDP_CHECKSUM_OFFSET    = 6,
	LAYER4_HEADER_GRE_CALL_ID_OFFSET     = 6,
	LAYER4_HEADER_TCP_FLAGS_OFFSET       = 13,
	LAYER4_HEADER_TCP_CHECKSUM_OFFSET    = 16,
	LAYER4_HEADER_LAST                   = 16
} rdd_layer4_header;
/* <<<RDD_LAYER4_HEADER */


/* >>>RDD_PARSER_L2_PROTOCOL */
typedef enum
{
	PARSER_L2_PROTOCOL_FIRST             = 1,
	PARSER_L2_PROTOCOL_PPPOE_D           = 1,
	PARSER_L2_PROTOCOL_PPPOE_S           = 2,
	PARSER_L2_PROTOCOL_USER_DEFINED_0    = 8,
	PARSER_L2_PROTOCOL_USER_DEFINED_1    = 9,
	PARSER_L2_PROTOCOL_USER_DEFINED_2    = 10,
	PARSER_L2_PROTOCOL_USER_DEFINED_3    = 11,
	PARSER_L2_PROTOCOL_ARP               = 12,
	PARSER_L2_PROTOCOL__1588             = 13,
	PARSER_L2_PROTOCOL__802_1X           = 14,
	PARSER_L2_PROTOCOL_MASK              = 15,
	PARSER_L2_PROTOCOL__802_1AG_CFM      = 15,
	PARSER_L2_PROTOCOL_LAST              = 15
} rdd_parser_l2_protocol;
/* <<<RDD_PARSER_L2_PROTOCOL */


/* >>>RDD_PARSER_L3_PROTOCOL */
typedef enum
{
	PARSER_L3_PROTOCOL_FIRST    = 0,
	PARSER_L3_PROTOCOL_OTHER    = 0,
	PARSER_L3_PROTOCOL_IPV4     = 1,
	PARSER_L3_PROTOCOL_IPV6     = 2,
	PARSER_L3_PROTOCOL_MASK     = 3,
	PARSER_L3_PROTOCOL_LAST     = 3
} rdd_parser_l3_protocol;
/* <<<RDD_PARSER_L3_PROTOCOL */


/* >>>RDD_PARSER_L4_PROTOCOL */
typedef enum
{
	PARSER_L4_PROTOCOL_FIRST             = 0,
	PARSER_L4_PROTOCOL_OTHER             = 0,
	PARSER_L4_PROTOCOL_TCP               = 1,
	PARSER_L4_PROTOCOL_UDP               = 2,
	PARSER_L4_PROTOCOL_IGMP              = 3,
	PARSER_L4_PROTOCOL_ICMP              = 4,
	PARSER_L4_PROTOCOL_ICMPV6            = 5,
	PARSER_L4_PROTOCOL_ESP               = 6,
	PARSER_L4_PROTOCOL_GRE               = 7,
	PARSER_L4_PROTOCOL_USER_DEFINED_0    = 8,
	PARSER_L4_PROTOCOL_USER_DEFINED_1    = 9,
	PARSER_L4_PROTOCOL_USER_DEFINED_2    = 10,
	PARSER_L4_PROTOCOL_USER_DEFINED_3    = 11,
	PARSER_L4_PROTOCOL_RESERVED          = 12,
	PARSER_L4_PROTOCOL_IPV6              = 13,
	PARSER_L4_PROTOCOL_AH                = 14,
	PARSER_L4_PROTOCOL_NOT_PARSED        = 15,
	PARSER_L4_PROTOCOL_MASK              = 15,
	PARSER_L4_PROTOCOL_LAST              = 15
} rdd_parser_l4_protocol;
/* <<<RDD_PARSER_L4_PROTOCOL */


/* >>>RDD_ACTION_ECN */
typedef enum
{
	ACTION_ECN_FIRST               = 0,
	ACTION_ECN_REMARKING_OFFSET    = 0,
	ACTION_ECN_REMARKING_WIDTH     = 2,
	ACTION_ECN_LAST                = 2
} rdd_action_ecn;
/* <<<RDD_ACTION_ECN */


/* >>>RDD_ACTION_DSCP */
typedef enum
{
	ACTION_DSCP_FIRST                             = 2,
	ACTION_DSCP_REMARKING_OFFSET                  = 2,
	ACTION_DSCP_REMARKING_TRAFFIC_CLASS_OFFSET    = 4,
	ACTION_DSCP_REMARKING_WIDTH                   = 6,
	ACTION_DSCP_REMARKING_TRAFFIC_CLASS_WIDTH     = 8,
	ACTION_DSCP_LAST                              = 8
} rdd_action_dscp;
/* <<<RDD_ACTION_DSCP */


/* >>>RDD_ACTION_OUTER */
typedef enum
{
	ACTION_OUTER_FIRST                         = 14,
	ACTION_OUTER_PBITS_REMARKING_VID_OFFSET    = 14,
	ACTION_OUTER_LAST                          = 14
} rdd_action_outer;
/* <<<RDD_ACTION_OUTER */


/* >>>RDD_ACTION_INNER */
typedef enum
{
	ACTION_INNER_FIRST                         = 18,
	ACTION_INNER_PBITS_REMARKING_VID_OFFSET    = 18,
	ACTION_INNER_LAST                          = 18
} rdd_action_inner;
/* <<<RDD_ACTION_INNER */


/* >>>RDD_ACTION_PBITS */
typedef enum
{
	ACTION_PBITS_FIRST                      = 2,
	ACTION_PBITS_REMARKING_DSCP_OFFSET      = 2,
	ACTION_PBITS_REMARKING_PACKET_WIDTH     = 3,
	ACTION_PBITS_REMARKING_DSCP_WIDTH       = 6,
	ACTION_PBITS_REMARKING_PACKET_OFFSET    = 13,
	ACTION_PBITS_LAST                       = 13
} rdd_action_pbits;
/* <<<RDD_ACTION_PBITS */


/* >>>RDD_ACTION_DS_LITE */
typedef enum
{
	ACTION_DS_LITE_FIRST   = 40,
	ACTION_DS_LITE_SIZE    = 40,
	ACTION_DS_LITE_LAST    = 40
} rdd_action_ds_lite;
/* <<<RDD_ACTION_DS_LITE */


/* >>>RDD_DS_ACTION_ID */
typedef enum
{
	DS_ACTION_ID_FIRST        = 0,
	DS_ACTION_ID_TRAP         = 0,
	DS_ACTION_ID_TTL          = 2,
	DS_ACTION_ID_DSCP         = 4,
	DS_ACTION_ID_NAT          = 5,
	DS_ACTION_ID_GRE          = 6,
	DS_ACTION_ID_OPBITS       = 7,
	DS_ACTION_ID_IPBITS       = 8,
	DS_ACTION_ID_DS_LITE      = 9,
	DS_ACTION_ID_PPPOE        = 10,
	DS_ACTION_ID_TOTAL_NUM    = 17,
	DS_ACTION_ID_LAST         = 17
} rdd_ds_action_id;
/* <<<RDD_DS_ACTION_ID */


/* >>>RDD_US_ACTION_ID */
typedef enum
{
	US_ACTION_ID_FIRST        = 0,
	US_ACTION_ID_TRAP         = 0,
	US_ACTION_ID_TTL          = 2,
	US_ACTION_ID_DSCP         = 4,
	US_ACTION_ID_NAT          = 5,
	US_ACTION_ID_GRE          = 6,
	US_ACTION_ID_OPBITS       = 7,
	US_ACTION_ID_IPBITS       = 8,
	US_ACTION_ID_DS_LITE      = 9,
	US_ACTION_ID_PPPOE        = 10,
	US_ACTION_ID_TOTAL_NUM    = 17,
	US_ACTION_ID_LAST         = 17
} rdd_us_action_id;
/* <<<RDD_US_ACTION_ID */


/* >>>RDD_RDD_VPORT */
typedef enum
{
	RDD_VPORT_FIRST     = 0,
	RDD_VPORT_ID_0      = 0,
	RDD_VPORT_ID_1      = 1,
	RDD_VPORT_ID_2      = 2,
	RDD_VPORT_ID_3      = 3,
	RDD_VPORT_ID_4      = 4,
	RDD_VPORT_ID_5      = 5,
	RDD_VPORT_ID_6      = 6,
	RDD_VPORT_ID_7      = 7,
	RDD_VPORT_ID_8      = 8,
	RDD_VPORT_ID_9      = 9,
	RDD_VPORT_ID_10     = 10,
	RDD_VPORT_ID_11     = 11,
	RDD_VPORT_ID_12     = 12,
	RDD_VPORT_ID_13     = 13,
	RDD_VPORT_ID_14     = 14,
	RDD_VPORT_ID_15     = 15,
	RDD_VPORT_ID_16     = 16,
	RDD_VPORT_ID_17     = 17,
	RDD_VPORT_ID_18     = 18,
	RDD_VPORT_ID_19     = 19,
	RDD_VPORT_ID_20     = 20,
	RDD_VPORT_ID_21     = 21,
	RDD_VPORT_ID_22     = 22,
	RDD_VPORT_ID_23     = 23,
	RDD_VPORT_ID_24     = 24,
	RDD_VPORT_ID_25     = 25,
	RDD_VPORT_ID_26     = 26,
	RDD_VPORT_ID_27     = 27,
	RDD_VPORT_ID_28     = 28,
	RDD_VPORT_ID_29     = 29,
	RDD_VPORT_ID_30     = 30,
	RDD_VPORT_ID_31     = 31,
	RDD_VPORT_ID_32     = 32,
	RDD_VPORT_ID_33     = 33,
	RDD_VPORT_ID_34     = 34,
	RDD_VPORT_ID_35     = 35,
	RDD_VPORT_ID_36     = 36,
	RDD_VPORT_ID_37     = 37,
	RDD_VPORT_ID_38     = 38,
	RDD_VPORT_ID_39     = 39,
	RDD_VPORT_ID_ANY    = 40,
	RDD_VPORT_LAST      = 40
} rdd_rdd_vport;
/* <<<RDD_RDD_VPORT */


/* >>>RDD_DSCP_TO */
typedef enum
{
	DSCP_TO_FIRST                 = 6,
	DSCP_TO_PBITS_SHIFT_OFFSET    = 6,
	DSCP_TO_LAST                  = 6
} rdd_dscp_to;
/* <<<RDD_DSCP_TO */


/* >>>RDD_RESOLUTION_CONTEXT */
typedef enum
{
	RESOLUTION_CONTEXT_FIRST                          = 0,
	RESOLUTION_CONTEXT_VIRTUAL_SRC_PORT_OFFSET        = 0,
	RESOLUTION_CONTEXT_GPE_DMA_OFFSET_WIDTH           = 1,
	RESOLUTION_CONTEXT_GPE_HEADER_LENGTH_WIDTH        = 1,
	RESOLUTION_CONTEXT_GPE_HEADER_IH_PTR_WIDTH        = 2,
	RESOLUTION_CONTEXT_GPE_COMMAND_LIST_PTR_WIDTH     = 2,
	RESOLUTION_CONTEXT_GPE_PACKET_DRR_PTR_WIDTH       = 4,
	RESOLUTION_CONTEXT_GPE_HEADER_LENGTH_OFFSET       = 6,
	RESOLUTION_CONTEXT_GPE_DMA_OFFSET_OFFSET          = 7,
	RESOLUTION_CONTEXT_GPE_COMMAND_LIST_PTR_OFFSET    = 8,
	RESOLUTION_CONTEXT_GPE_HEADER_IH_PTR_OFFSET       = 10,
	RESOLUTION_CONTEXT_GPE_PACKET_DRR_PTR_OFFSET      = 12,
	RESOLUTION_CONTEXT_LAST                           = 12
} rdd_resolution_context;
/* <<<RDD_RESOLUTION_CONTEXT */


/* >>>RDD_BBMSG_TYPE */
typedef enum
{
	BBMSG_TYPE_FIRST                                              = 0,
	BBMSG_TYPE_RUNNER_BBH_RX_FLOW_CONTROL                         = 0,
	BBMSG_TYPE_QM_PD_FIFO_CREDIT_FREE                             = 0,
	BBMSG_TYPE_BBH_TX_PACKET_DESCRIPTOR                           = 1,
	BBMSG_TYPE_RUNNER_SBPM_BUFFER_ALLOC                           = 1,
	BBMSG_TYPE_QM_UPDATE_FIFO_CREDIT_FREE                         = 1,
	BBMSG_TYPE_FPM_BUFFER_ALLOC                                   = 1,
	BBMSG_TYPE_FPM_BUFFER_MCAST_INCREMENT                         = 2,
	BBMSG_TYPE_RUNNER_SBPM_MCAST_INC_REQUEST                      = 2,
	BBMSG_TYPE_BBH_TX_NACK                                        = 2,
	BBMSG_TYPE_BBH_TX_ACK                                         = 3,
	BBMSG_TYPE_FPM_BUFFER_FREE                                    = 3,
	BBMSG_TYPE_BBH_SBPM_BUFFER_FREE                               = 3,
	BBMSG_TYPE_BBH_GHOST_DBR                                      = 4,
	BBMSG_TYPE_RUNNER_SBPM_CONNECT                                = 4,
	BBMSG_TYPE_RUNNER_SBPM_GET_NEXT                               = 5,
	BBMSG_TYPE_BBH_TX_REPORT_ACK                                  = 5,
	BBMSG_TYPE_BBH_SBPM_BUFFER_FREE_WITHOUT_CONTEXT               = 6,
	BBMSG_TYPE_RUNNER_SBPM_BUFFER_FREE_WITHOUT_CONTEXT            = 6,
	BBMSG_TYPE_BBH_TX_REPORT_NACK                                 = 7,
	BBMSG_TYPE_RUNNER_SBPM_INGRESS_TO_EGRESS                      = 7,
	BBMSG_TYPE_RUNNER_REORDER_PD_WRITE                            = 8,
	BBMSG_TYPE_RUNNER_DISPATCHER_PD_ACK                           = 9,
	BBMSG_TYPE_RUNNER_DISPATCHER_PD_WRITE                         = 10,
	BBMSG_TYPE_RUNNER_REORDER_TOKEN_REQUEST                       = 11,
	BBMSG_TYPE_RUNNER_REORDER_BUFFER_CONNECT                      = 12,
	BBMSG_TYPE_RUNNER_DISPATCHER_WAKEUP_PENDING                   = 13,
	BBMSG_TYPE_RUNNER_REORDER_CONNECT_REQUEST_BUFFER_CONNECTED    = 14,
	BBMSG_TYPE_RUNNER_REORDER_BUFFER_MULTICAST_CONNECT_REQUEST    = 15,
	BBMSG_TYPE_BBH_RX_DISPATCHER_PD_WRITE                         = 24,
	BBMSG_TYPE_LAST                                               = 24
} rdd_bbmsg_type;
/* <<<RDD_BBMSG_TYPE */


/* >>>RDD_ERR_RX_PD */
typedef enum
{
	ERR_RX_PD_FIRST                 = 1,
	ERR_RX_PD_NO_SBPM               = 1,
	ERR_RX_PD_PACKET_TOO_SHORT      = 2,
	ERR_RX_PD_PACKET_TOO_LONG       = 3,
	ERR_RX_PD_CRC                   = 4,
	ERR_RX_PD_ENCRYPT               = 5,
	ERR_RX_PD_NO_SDMA_CHUNK         = 6,
	ERR_RX_PD_SOP_AFTER_SOP         = 7,
	ERR_RX_PD_THIRD_FLOW_ARRIVAL    = 8,
	ERR_RX_PD_LAST                  = 8
} rdd_err_rx_pd;
/* <<<RDD_ERR_RX_PD */


/* >>>RDD_SBPM_OPCODE */
typedef enum
{
	SBPM_OPCODE_FIRST                   = 0,
	SBPM_OPCODE_MULTI_GET_NEXT          = 0,
	SBPM_OPCODE_BN_ALLOC                = 1,
	SBPM_OPCODE_MCST_INC                = 2,
	SBPM_OPCODE_BN_FREE_WITH_CONTEXT    = 3,
	SBPM_OPCODE_BN_CONNECT              = 4,
	SBPM_OPCODE_GET_NEXT                = 5,
	SBPM_OPCODE_BN_FREE_WO_CONTEXT      = 6,
	SBPM_OPCODE_INGRESS_TO_EGRESS       = 7,
	SBPM_OPCODE_LAST                    = 7
} rdd_sbpm_opcode;
/* <<<RDD_SBPM_OPCODE */


/* >>>RDD_RDD_LAN */
typedef enum
{
	RDD_LAN_FIRST           = 1,
	RDD_LAN_BRIDGE_PORT0    = 1,
	RDD_LAN_BRIDGE_PORT1    = 2,
	RDD_LAN_BRIDGE_PORT2    = 3,
	RDD_LAN_BRIDGE_PORT3    = 4,
	RDD_LAN_BRIDGE_PORT4    = 5,
	RDD_LAN_BRIDGE_PORT5    = 6,
	RDD_LAN_LAST            = 6
} rdd_rdd_lan;
/* <<<RDD_RDD_LAN */


/* >>>RDD_MAC_TYPE */
typedef enum
{
	MAC_TYPE_FIRST    = 0,
	MAC_TYPE_EMAC     = 0,
	MAC_TYPE_GPON     = 1,
	MAC_TYPE_XGPON    = 2,
	MAC_TYPE_EPON     = 3,
	MAC_TYPE_XEPON    = 4,
	MAC_TYPE_DSL      = 5,
	MAC_TYPE_AE10G    = 6,
	MAC_TYPE_AE2P5    = 7,
	MAC_TYPE_LAST     = 7
} rdd_mac_type;
/* <<<RDD_MAC_TYPE */


/* >>>RDD_SBPM */
typedef enum
{
	SBPM_FIRST                    = 16383,
	SBPM_INVALID_BUFFER_NUMBER    = 16383,
	SBPM_LAST                     = 16383
} rdd_sbpm;
/* <<<RDD_SBPM */


/* >>>RDD_FPM_POOL_ID */
typedef enum
{
	FPM_POOL_ID_FIRST            = 0,
	FPM_POOL_ID_EIGHT_BUFFERS    = 0,
	FPM_POOL_ID_FOUR_BUFFERS     = 1,
	FPM_POOL_ID_TWO_BUFFERS      = 2,
	FPM_POOL_ID_ONE_BUFFER       = 3,
	FPM_POOL_ID_LAST             = 3
} rdd_fpm_pool_id;
/* <<<RDD_FPM_POOL_ID */


/* >>>RDD_RNR */
typedef enum
{
	RNR_FIRST       = 0,
	RNR_CORE0_ID    = 0,
	RNR_CORE1_ID    = 1,
	RNR_CORE2_ID    = 2,
	RNR_CORE3_ID    = 3,
	RNR_CORE4_ID    = 4,
	RNR_LAST        = 4
} rdd_rnr;
/* <<<RDD_RNR */


/* >>>RDD_BB_ID */
typedef enum
{
	BB_ID_FIRST                 = 0,
	BB_ID_RNR0                  = 0,
	BB_ID_RNR1                  = 1,
	BB_ID_RNR2                  = 2,
	BB_ID_RNR3                  = 3,
	BB_ID_RNR4                  = 4,
	BB_ID_BBHLB                 = 16,
	BB_ID_CNPL_0                = 17,
	BB_ID_DISPATCHER_REORDER    = 18,
	BB_ID_SDMA_COPY             = 20,
	BB_ID_QM_CP_SDMA            = 20,
	BB_ID_SDMA0                 = 21,
	BB_ID_SDMA1                 = 22,
	BB_ID_FPM                   = 23,
	BB_ID_HASH_0                = 24,
	BB_ID_NATC_0                = 25,
	BB_ID_QM_RNR_GRID           = 27,
	BB_ID_QM_BBHTX              = 28,
	BB_ID_QM_TOP                = 29,
	BB_ID_QM_CP_MACHINE         = 30,
	BB_ID_RX_BBH_0              = 31,
	BB_ID_TX_LAN                = 32,
	BB_ID_RX_BBH_1              = 33,
	BB_ID_RX_BBH_2              = 35,
	BB_ID_TX_COPY               = 36,
	BB_ID_RX_BBH_3              = 37,
	BB_ID_RX_BBH_4              = 39,
	BB_ID_RX_BBH_5              = 41,
	BB_ID_RX_BBH_6              = 43,
	BB_ID_RX_BBH_7              = 45,
	BB_ID_RX_DSL                = 53,
	BB_ID_TX_DSL                = 54,
	BB_ID_TX_DSL_STAT           = 55,
	BB_ID_SBPM                  = 56,
	BB_ID_TCAM_0                = 57,
	BB_ID_TCAM_1                = 58,
	BB_ID_HASH_1                = 59,
	BB_ID_NATC_1                = 60,
	BB_ID_CNPL_1                = 61,
	BB_ID_LAST                  = 61
} rdd_bb_id;
/* <<<RDD_BB_ID */


/* Hardware defines */

/* >>>RDD_BB_DESTINATION_ENTRY */
#define BB_DESTINATION_ENTRY_BB_DESTINATION_F_OFFSET                   0
#define BB_DESTINATION_ENTRY_BB_DESTINATION_F_WIDTH                    32
#define BB_DESTINATION_ENTRY_BB_DESTINATION_ENTRY_OFFSET               0
#define BB_DESTINATION_ENTRY_BB_DESTINATION_OFFSET                     0
#define BB_DESTINATION_ENTRY_BB_DESTINATION_WORD_OFFSET                0
/* <<<RDD_BB_DESTINATION_ENTRY */


/* >>>RDD_CPU_TX_DESCRIPTOR */
#define CPU_TX_DESCRIPTOR_VALID_F_OFFSET                            31
#define CPU_TX_DESCRIPTOR_VALID_F_WIDTH                             1
#define CPU_TX_DESCRIPTOR_CPU_TX_DESCRIPTOR_OFFSET                  0
#define CPU_TX_DESCRIPTOR_VALID_OFFSET                              0
#define CPU_TX_DESCRIPTOR_VALID_WORD_OFFSET                         0
#define CPU_TX_DESCRIPTOR_VALID_F_OFFSET_MOD8                       7
#define CPU_TX_DESCRIPTOR_VALID_F_OFFSET_MOD16                      15
#define CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_F_OFFSET                    22
#define CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_F_WIDTH                     9
#define CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_OFFSET                      0
#define CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_WORD_OFFSET                 0
#define CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_F_OFFSET_MOD16              6
#define CPU_TX_DESCRIPTOR_ABS_DATA1_F_OFFSET                        0
#define CPU_TX_DESCRIPTOR_ABS_DATA1_F_WIDTH                         22
#define CPU_TX_DESCRIPTOR_ABS_DATA1_OFFSET                          0
#define CPU_TX_DESCRIPTOR_ABS_DATA1_WORD_OFFSET                     0
#define CPU_TX_DESCRIPTOR_ABS_DATA0_F_OFFSET                        14
#define CPU_TX_DESCRIPTOR_ABS_DATA0_F_WIDTH                         18
#define CPU_TX_DESCRIPTOR_ABS_DATA0_OFFSET                          4
#define CPU_TX_DESCRIPTOR_ABS_DATA0_WORD_OFFSET                     1
#define CPU_TX_DESCRIPTOR_PACKET_LENGTH_F_OFFSET                    0
#define CPU_TX_DESCRIPTOR_PACKET_LENGTH_F_WIDTH                     14
#define CPU_TX_DESCRIPTOR_PACKET_LENGTH_OFFSET                      6
#define CPU_TX_DESCRIPTOR_PACKET_LENGTH_WORD_OFFSET                 1
#define CPU_TX_DESCRIPTOR_PACKET_LENGTH_F_OFFSET_MOD16              0
#define CPU_TX_DESCRIPTOR_DROP_F_OFFSET                             31
#define CPU_TX_DESCRIPTOR_DROP_F_WIDTH                              1
#define CPU_TX_DESCRIPTOR_DROP_OFFSET                               8
#define CPU_TX_DESCRIPTOR_DROP_WORD_OFFSET                          2
#define CPU_TX_DESCRIPTOR_DROP_F_OFFSET_MOD8                        7
#define CPU_TX_DESCRIPTOR_DROP_F_OFFSET_MOD16                       15
#define CPU_TX_DESCRIPTOR_FLAG_1588_F_OFFSET                        30
#define CPU_TX_DESCRIPTOR_FLAG_1588_F_WIDTH                         1
#define CPU_TX_DESCRIPTOR_FLAG_1588_OFFSET                          8
#define CPU_TX_DESCRIPTOR_FLAG_1588_WORD_OFFSET                     2
#define CPU_TX_DESCRIPTOR_FLAG_1588_F_OFFSET_MOD8                   6
#define CPU_TX_DESCRIPTOR_FLAG_1588_F_OFFSET_MOD16                  14
#define CPU_TX_DESCRIPTOR_COLOR_F_OFFSET                            29
#define CPU_TX_DESCRIPTOR_COLOR_F_WIDTH                             1
#define CPU_TX_DESCRIPTOR_COLOR_OFFSET                              8
#define CPU_TX_DESCRIPTOR_COLOR_WORD_OFFSET                         2
#define CPU_TX_DESCRIPTOR_COLOR_F_OFFSET_MOD8                       5
#define CPU_TX_DESCRIPTOR_COLOR_F_OFFSET_MOD16                      13
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_F_OFFSET                   28
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_F_WIDTH                    1
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_OFFSET                     8
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_WORD_OFFSET                2
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_F_OFFSET_MOD8              4
#define CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_F_OFFSET_MOD16             12
#define CPU_TX_DESCRIPTOR_LAN_F_OFFSET                              26
#define CPU_TX_DESCRIPTOR_LAN_F_WIDTH                               1
#define CPU_TX_DESCRIPTOR_LAN_OFFSET                                8
#define CPU_TX_DESCRIPTOR_LAN_WORD_OFFSET                           2
#define CPU_TX_DESCRIPTOR_LAN_F_OFFSET_MOD8                         2
#define CPU_TX_DESCRIPTOR_LAN_F_OFFSET_MOD16                        10
#define CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_F_OFFSET             18
#define CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_F_WIDTH              8
#define CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_OFFSET               8
#define CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_WORD_OFFSET          2
#define CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_F_OFFSET_MOD16       2
#define CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_F_OFFSET              0
#define CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_F_WIDTH               18
#define CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_OFFSET                8
#define CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_WORD_OFFSET           2
#define CPU_TX_DESCRIPTOR_AGG_PD_F_OFFSET                           31
#define CPU_TX_DESCRIPTOR_AGG_PD_F_WIDTH                            1
#define CPU_TX_DESCRIPTOR_AGG_PD_OFFSET                             12
#define CPU_TX_DESCRIPTOR_AGG_PD_WORD_OFFSET                        3
#define CPU_TX_DESCRIPTOR_AGG_PD_F_OFFSET_MOD8                      7
#define CPU_TX_DESCRIPTOR_AGG_PD_F_OFFSET_MOD16                     15
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_F_OFFSET                     30
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_F_WIDTH                      1
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_OFFSET                       12
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_WORD_OFFSET                  3
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_F_OFFSET_MOD8                6
#define CPU_TX_DESCRIPTOR_TARGET_MEM_0_F_OFFSET_MOD16               14
#define CPU_TX_DESCRIPTOR_ABS_F_OFFSET                              29
#define CPU_TX_DESCRIPTOR_ABS_F_WIDTH                               1
#define CPU_TX_DESCRIPTOR_ABS_OFFSET                                12
#define CPU_TX_DESCRIPTOR_ABS_WORD_OFFSET                           3
#define CPU_TX_DESCRIPTOR_ABS_F_OFFSET_MOD8                         5
#define CPU_TX_DESCRIPTOR_ABS_F_OFFSET_MOD16                        13
#define CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_F_OFFSET          18
#define CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_F_WIDTH           11
#define CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_OFFSET            12
#define CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_WORD_OFFSET       3
#define CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_F_OFFSET_MOD16    2
#define CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_F_OFFSET         0
#define CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_F_WIDTH          18
#define CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_OFFSET           12
#define CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_WORD_OFFSET      3

/* >>>RDD_CPU_TX_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	bn1_or_abs2_or_1588 	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ssid                          	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	fpm_fallback                  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	sbpm_copy                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	bn1_first                     	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	_ssid                         	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	_fpm_fallback                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	_sbpm_copy                    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	abs2                          	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	data_1588                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	payload_offset_or_abs_1	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	buffer_number_0_or_abs_0	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	sop                           	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_or_abs_1 union */
			uint32_t	bn0_first                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_0_or_abs_0 union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs1                          	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_or_abs_1 union */
			uint32_t	abs0                          	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_0_or_abs_0 union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_payload_offset_or_abs_1	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_buffer_number_0_or_abs_0	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_abs_data1           	:22	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_first_level_q       	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_valid               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_packet_length       	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs_data0           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	bn1_or_abs2_or_1588 	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	ssid                          	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	fpm_fallback                  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	sbpm_copy                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	bn1_first                     	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	reserved1_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	_ssid                         	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	_fpm_fallback                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	_sbpm_copy                    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	abs2                          	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	reserved2_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	data_1588                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of bn1_or_abs2_or_1588 union */
			uint32_t	reserved3_wan_flow_source_port	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_lan                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved1           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_do_not_recycle      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_flag_1588           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_drop                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	buffer_number_0_or_abs_0	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	payload_offset_or_abs_1	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	bn0_first                     	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_0_or_abs_0 union */
			uint32_t	sop                           	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_or_abs_1 union */
			uint32_t	reserved1_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	abs0                          	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of buffer_number_0_or_abs_0 union */
			uint32_t	abs1                          	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of payload_offset_or_abs_1 union */
			uint32_t	reserved2_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_buffer_number_0_or_abs_0	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_payload_offset_or_abs_1	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_target_mem_0        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_agg_pd              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_TX_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_CPU_TX_DESCRIPTOR_DTS fields;
} CPU_TX_DESCRIPTOR_STRUCT;
#define RDD_CPU_TX_DESCRIPTOR_VALID_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS), 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_VALID_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS), 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_VALID_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_VALID_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS), 6, 9, r)
#define RDD_CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS), 6, 9, v)
#define RDD_CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p, 6, 9, r)
#define RDD_CPU_TX_DESCRIPTOR_FIRST_LEVEL_Q_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p, 6, 9, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA1_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 0, 0, 22, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA1_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 0, 0, 22, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA1_READ(r, p)                            FIELD_MREAD_32((uint8_t *)p + 0, 0, 22, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA1_WRITE(v, p)                           FIELD_MWRITE_32((uint8_t *)p + 0, 0, 22, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA0_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 4, 14, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA0_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 4, 14, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA0_READ(r, p)                            FIELD_MREAD_32((uint8_t *)p + 4, 14, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_DATA0_WRITE(v, p)                           FIELD_MWRITE_32((uint8_t *)p + 4, 14, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_PACKET_LENGTH_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 6, 0, 14, r)
#define RDD_CPU_TX_DESCRIPTOR_PACKET_LENGTH_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 6, 0, 14, v)
#define RDD_CPU_TX_DESCRIPTOR_PACKET_LENGTH_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 6, 0, 14, r)
#define RDD_CPU_TX_DESCRIPTOR_PACKET_LENGTH_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 6, 0, 14, v)
#define RDD_CPU_TX_DESCRIPTOR_DROP_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_DROP_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_DROP_READ(r, p)                                 FIELD_MREAD_8((uint8_t *)p + 8, 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_DROP_WRITE(v, p)                                FIELD_MWRITE_8((uint8_t *)p + 8, 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_FLAG_1588_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 6, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_FLAG_1588_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 6, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_FLAG_1588_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 8, 6, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_FLAG_1588_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 8, 6, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_COLOR_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_COLOR_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_COLOR_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p + 8, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_COLOR_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p + 8, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 8, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_DO_NOT_RECYCLE_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 8, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_LAN_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 2, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_LAN_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 2, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_LAN_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 8, 2, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_LAN_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 8, 2, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_READ_G(r, g, idx)          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 2, 8, r)
#define RDD_CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 2, 8, v)
#define RDD_CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_READ(r, p)                 FIELD_MREAD_16((uint8_t *)p + 8, 2, 8, r)
#define RDD_CPU_TX_DESCRIPTOR_WAN_FLOW_SOURCE_PORT_WRITE(v, p)                FIELD_MWRITE_16((uint8_t *)p + 8, 2, 8, v)
#define RDD_CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_READ_G(r, g, idx)           GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_READ(r, p)                  FIELD_MREAD_32((uint8_t *)p + 8, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BN1_OR_ABS2_OR_1588_WRITE(v, p)                 FIELD_MWRITE_32((uint8_t *)p + 8, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_SSID_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 14, 4, r)
#define RDD_CPU_TX_DESCRIPTOR_SSID_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 14, 4, v)
#define RDD_CPU_TX_DESCRIPTOR_SSID_READ(r, p)                                 FIELD_MREAD_32((uint8_t *)p + 8, 14, 4, r)
#define RDD_CPU_TX_DESCRIPTOR_SSID_WRITE(v, p)                                FIELD_MWRITE_32((uint8_t *)p + 8, 14, 4, v)
#define RDD_CPU_TX_DESCRIPTOR_FPM_FALLBACK_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_FPM_FALLBACK_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_FPM_FALLBACK_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 10, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_FPM_FALLBACK_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 10, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_SBPM_COPY_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_SBPM_COPY_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_SBPM_COPY_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 10, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_SBPM_COPY_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 10, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_BN1_FIRST_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 0, 12, r)
#define RDD_CPU_TX_DESCRIPTOR_BN1_FIRST_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 0, 12, v)
#define RDD_CPU_TX_DESCRIPTOR_BN1_FIRST_READ(r, p)                            FIELD_MREAD_16((uint8_t *)p + 10, 0, 12, r)
#define RDD_CPU_TX_DESCRIPTOR_BN1_FIRST_WRITE(v, p)                           FIELD_MWRITE_16((uint8_t *)p + 10, 0, 12, v)
#define RDD_CPU_TX_DESCRIPTOR__SSID_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 14, 4, r)
#define RDD_CPU_TX_DESCRIPTOR__SSID_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 14, 4, v)
#define RDD_CPU_TX_DESCRIPTOR__SSID_READ(r, p)                                FIELD_MREAD_32((uint8_t *)p + 8, 14, 4, r)
#define RDD_CPU_TX_DESCRIPTOR__SSID_WRITE(v, p)                               FIELD_MWRITE_32((uint8_t *)p + 8, 14, 4, v)
#define RDD_CPU_TX_DESCRIPTOR__FPM_FALLBACK_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR__FPM_FALLBACK_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR__FPM_FALLBACK_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 10, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR__FPM_FALLBACK_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 10, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR__SBPM_COPY_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR__SBPM_COPY_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR__SBPM_COPY_READ(r, p)                           FIELD_MREAD_8((uint8_t *)p + 10, 4, 1, r)
#define RDD_CPU_TX_DESCRIPTOR__SBPM_COPY_WRITE(v, p)                          FIELD_MWRITE_8((uint8_t *)p + 10, 4, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS2_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 0, 12, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS2_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 10, 0, 12, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS2_READ(r, p)                                 FIELD_MREAD_16((uint8_t *)p + 10, 0, 12, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS2_WRITE(v, p)                                FIELD_MWRITE_16((uint8_t *)p + 10, 0, 12, v)
#define RDD_CPU_TX_DESCRIPTOR_DATA_1588_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_DATA_1588_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 8, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_DATA_1588_READ(r, p)                            FIELD_MREAD_32((uint8_t *)p + 8, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_DATA_1588_WRITE(v, p)                           FIELD_MWRITE_32((uint8_t *)p + 8, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_AGG_PD_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_AGG_PD_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_AGG_PD_READ(r, p)                               FIELD_MREAD_8((uint8_t *)p + 12, 7, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_AGG_PD_WRITE(v, p)                              FIELD_MWRITE_8((uint8_t *)p + 12, 7, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_TARGET_MEM_0_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 6, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_TARGET_MEM_0_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 6, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_TARGET_MEM_0_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 12, 6, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_TARGET_MEM_0_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 12, 6, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 12, 5, 1, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 12, 5, 1, v)
#define RDD_CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_READ_G(r, g, idx)       GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_WRITE_G(v, g, idx)      GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_READ(r, p)              FIELD_MREAD_16((uint8_t *)p + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_PAYLOAD_OFFSET_OR_ABS_1_WRITE(v, p)             FIELD_MWRITE_16((uint8_t *)p + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_SOP_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_SOP_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_SOP_READ(r, p)                                  FIELD_MREAD_16((uint8_t *)p + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_SOP_WRITE(v, p)                                 FIELD_MWRITE_16((uint8_t *)p + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS1_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS1_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS1_READ(r, p)                                 FIELD_MREAD_16((uint8_t *)p + 12, 2, 11, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS1_WRITE(v, p)                                FIELD_MWRITE_16((uint8_t *)p + 12, 2, 11, v)
#define RDD_CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_READ_G(r, g, idx)      GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_WRITE_G(v, g, idx)     GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_READ(r, p)             FIELD_MREAD_32((uint8_t *)p + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BUFFER_NUMBER_0_OR_ABS_0_WRITE(v, p)            FIELD_MWRITE_32((uint8_t *)p + 12, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_BN0_FIRST_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BN0_FIRST_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_BN0_FIRST_READ(r, p)                            FIELD_MREAD_32((uint8_t *)p + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_BN0_FIRST_WRITE(v, p)                           FIELD_MWRITE_32((uint8_t *)p + 12, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS0_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS0_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_TX_DESCRIPTOR_DTS) + 12, 0, 18, v)
#define RDD_CPU_TX_DESCRIPTOR_ABS0_READ(r, p)                                 FIELD_MREAD_32((uint8_t *)p + 12, 0, 18, r)
#define RDD_CPU_TX_DESCRIPTOR_ABS0_WRITE(v, p)                                FIELD_MWRITE_32((uint8_t *)p + 12, 0, 18, v)
/* <<<RDD_CPU_TX_DESCRIPTOR_DTS */

/* <<<RDD_CPU_TX_DESCRIPTOR */


/* >>>RDD_PARSE */
#define PARSE_PARSE_OFFSET                              0
#define PARSE_SUMMARY_OFFSET                            0
#define PARSE_SUMMARY_WORD_OFFSET                       0
#define PARSE_SUMMARY_F_OFFSET_MOD16                    0
#define PARSE_RESULTS_OFFSET                            4
#define PARSE_RESULTS_WORD_OFFSET                       1
#define PARSE_RESULTS_F_OFFSET_MOD16                    8
#define PARSE_L2_LKP_ENTRY_OFFSET                       32
#define PARSE_L2_LKP_ENTRY_WORD_OFFSET                  8
#define PARSE_L2_LKP_ENTRY_F_OFFSET_MOD16               8
#define PARSE_L3_LKP_ENTRY_OFFSET                       48
#define PARSE_L3_LKP_ENTRY_WORD_OFFSET                  12
#define PARSE_L3_LKP_ENTRY_F_OFFSET_MOD16               8
#define PARSE_IC_LKP_ENTRY_OFFSET                       64
#define PARSE_IC_LKP_ENTRY_WORD_OFFSET                  16
#define PARSE_IC_LKP_ENTRY_F_OFFSET_MOD16               8

/* >>>RDD_PARSE_DTS */
#define RDD_PARSE_SUMMARY_NUMBER	4
#define RDD_PARSE_RESULTS_NUMBER	28
#define RDD_PARSE_L2_LKP_ENTRY_NUMBER	16
#define RDD_PARSE_L3_LKP_ENTRY_NUMBER	16
#define RDD_PARSE_IC_LKP_ENTRY_NUMBER	32

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint8_t	summary[RDD_PARSE_SUMMARY_NUMBER];
	uint8_t	results[RDD_PARSE_RESULTS_NUMBER];
	uint8_t	l2_lkp_entry[RDD_PARSE_L2_LKP_ENTRY_NUMBER];
	uint8_t	l3_lkp_entry[RDD_PARSE_L3_LKP_ENTRY_NUMBER];
	uint8_t	ic_lkp_entry[RDD_PARSE_IC_LKP_ENTRY_NUMBER];
#else
	uint8_t	summary[RDD_PARSE_SUMMARY_NUMBER];
	uint8_t	results[RDD_PARSE_RESULTS_NUMBER];
	uint8_t	l2_lkp_entry[RDD_PARSE_L2_LKP_ENTRY_NUMBER];
	uint8_t	l3_lkp_entry[RDD_PARSE_L3_LKP_ENTRY_NUMBER];
	uint8_t	ic_lkp_entry[RDD_PARSE_IC_LKP_ENTRY_NUMBER];
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSE_DTS;

typedef union
{
    uint32_t word_val[24];
    uint64_t dword_val64[12];
    RDD_PARSE_DTS fields;
} PARSE_STRUCT;
#define RDD_PARSE_SUMMARY_READ_G(r, g, idx, i)            GROUP_MREAD_I_8(g, idx*sizeof(RDD_PARSE_DTS), i, r)
#define RDD_PARSE_SUMMARY_WRITE_G(v, g, idx, i)           GROUP_MWRITE_I_8(g, idx*sizeof(RDD_PARSE_DTS), i, v)
#define RDD_PARSE_SUMMARY_READ(r, p, i)                   MREAD_I_8((uint8_t *)p, i, r)
#define RDD_PARSE_SUMMARY_WRITE(v, p, i)                  MWRITE_I_8((uint8_t *)p, i, v)
#define RDD_PARSE_RESULTS_READ_G(r, g, idx, i)            GROUP_MREAD_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 4, i, r)
#define RDD_PARSE_RESULTS_WRITE_G(v, g, idx, i)           GROUP_MWRITE_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 4, i, v)
#define RDD_PARSE_RESULTS_READ(r, p, i)                   MREAD_I_8((uint8_t *)p + 4, i, r)
#define RDD_PARSE_RESULTS_WRITE(v, p, i)                  MWRITE_I_8((uint8_t *)p + 4, i, v)
#define RDD_PARSE_L2_LKP_ENTRY_READ_G(r, g, idx, i)       GROUP_MREAD_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 32, i, r)
#define RDD_PARSE_L2_LKP_ENTRY_WRITE_G(v, g, idx, i)      GROUP_MWRITE_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 32, i, v)
#define RDD_PARSE_L2_LKP_ENTRY_READ(r, p, i)              MREAD_I_8((uint8_t *)p + 32, i, r)
#define RDD_PARSE_L2_LKP_ENTRY_WRITE(v, p, i)             MWRITE_I_8((uint8_t *)p + 32, i, v)
#define RDD_PARSE_L3_LKP_ENTRY_READ_G(r, g, idx, i)       GROUP_MREAD_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 48, i, r)
#define RDD_PARSE_L3_LKP_ENTRY_WRITE_G(v, g, idx, i)      GROUP_MWRITE_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 48, i, v)
#define RDD_PARSE_L3_LKP_ENTRY_READ(r, p, i)              MREAD_I_8((uint8_t *)p + 48, i, r)
#define RDD_PARSE_L3_LKP_ENTRY_WRITE(v, p, i)             MWRITE_I_8((uint8_t *)p + 48, i, v)
#define RDD_PARSE_IC_LKP_ENTRY_READ_G(r, g, idx, i)       GROUP_MREAD_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 64, i, r)
#define RDD_PARSE_IC_LKP_ENTRY_WRITE_G(v, g, idx, i)      GROUP_MWRITE_I_8(g, idx*sizeof(RDD_PARSE_DTS) + 64, i, v)
#define RDD_PARSE_IC_LKP_ENTRY_READ(r, p, i)              MREAD_I_8((uint8_t *)p + 64, i, r)
#define RDD_PARSE_IC_LKP_ENTRY_WRITE(v, p, i)             MWRITE_I_8((uint8_t *)p + 64, i, v)
/* <<<RDD_PARSE_DTS */

/* <<<RDD_PARSE */


/* >>>RDD_PARSER_SUMMARY */
#define PARSER_SUMMARY_DA_FILTER_MATCH_F_OFFSET                  31
#define PARSER_SUMMARY_DA_FILTER_MATCH_F_WIDTH                   1
#define PARSER_SUMMARY_PARSER_SUMMARY_OFFSET                     0
#define PARSER_SUMMARY_DA_FILTER_MATCH_OFFSET                    0
#define PARSER_SUMMARY_DA_FILTER_MATCH_WORD_OFFSET               0
#define PARSER_SUMMARY_DA_FILTER_MATCH_F_OFFSET_MOD8             7
#define PARSER_SUMMARY_DA_FILTER_MATCH_F_OFFSET_MOD16            15
#define PARSER_SUMMARY_IP_FRAGMENT_F_OFFSET                      30
#define PARSER_SUMMARY_IP_FRAGMENT_F_WIDTH                       1
#define PARSER_SUMMARY_IP_FRAGMENT_OFFSET                        0
#define PARSER_SUMMARY_IP_FRAGMENT_WORD_OFFSET                   0
#define PARSER_SUMMARY_IP_FRAGMENT_F_OFFSET_MOD8                 6
#define PARSER_SUMMARY_IP_FRAGMENT_F_OFFSET_MOD16                14
#define PARSER_SUMMARY_L4_1588_F_OFFSET                          29
#define PARSER_SUMMARY_L4_1588_F_WIDTH                           1
#define PARSER_SUMMARY_L4_1588_OFFSET                            0
#define PARSER_SUMMARY_L4_1588_WORD_OFFSET                       0
#define PARSER_SUMMARY_L4_1588_F_OFFSET_MOD8                     5
#define PARSER_SUMMARY_L4_1588_F_OFFSET_MOD16                    13
#define PARSER_SUMMARY_TCP_UDP_F_OFFSET                          28
#define PARSER_SUMMARY_TCP_UDP_F_WIDTH                           1
#define PARSER_SUMMARY_TCP_UDP_OFFSET                            0
#define PARSER_SUMMARY_TCP_UDP_WORD_OFFSET                       0
#define PARSER_SUMMARY_TCP_UDP_F_OFFSET_MOD8                     4
#define PARSER_SUMMARY_TCP_UDP_F_OFFSET_MOD16                    12
#define PARSER_SUMMARY_DHCP_F_OFFSET                             27
#define PARSER_SUMMARY_DHCP_F_WIDTH                              1
#define PARSER_SUMMARY_DHCP_OFFSET                               0
#define PARSER_SUMMARY_DHCP_WORD_OFFSET                          0
#define PARSER_SUMMARY_DHCP_F_OFFSET_MOD8                        3
#define PARSER_SUMMARY_DHCP_F_OFFSET_MOD16                       11
#define PARSER_SUMMARY_BROADCAST_F_OFFSET                        26
#define PARSER_SUMMARY_BROADCAST_F_WIDTH                         1
#define PARSER_SUMMARY_BROADCAST_OFFSET                          0
#define PARSER_SUMMARY_BROADCAST_WORD_OFFSET                     0
#define PARSER_SUMMARY_BROADCAST_F_OFFSET_MOD8                   2
#define PARSER_SUMMARY_BROADCAST_F_OFFSET_MOD16                  10
#define PARSER_SUMMARY_MULTICAST_F_OFFSET                        25
#define PARSER_SUMMARY_MULTICAST_F_WIDTH                         1
#define PARSER_SUMMARY_MULTICAST_OFFSET                          0
#define PARSER_SUMMARY_MULTICAST_WORD_OFFSET                     0
#define PARSER_SUMMARY_MULTICAST_F_OFFSET_MOD8                   1
#define PARSER_SUMMARY_MULTICAST_F_OFFSET_MOD16                  9
#define PARSER_SUMMARY_DOS_ATTACK_F_OFFSET                       24
#define PARSER_SUMMARY_DOS_ATTACK_F_WIDTH                        1
#define PARSER_SUMMARY_DOS_ATTACK_OFFSET                         0
#define PARSER_SUMMARY_DOS_ATTACK_WORD_OFFSET                    0
#define PARSER_SUMMARY_DOS_ATTACK_F_OFFSET_MOD8                  0
#define PARSER_SUMMARY_DOS_ATTACK_F_OFFSET_MOD16                 8
#define PARSER_SUMMARY_MC_L3_CTL_F_OFFSET                        23
#define PARSER_SUMMARY_MC_L3_CTL_F_WIDTH                         1
#define PARSER_SUMMARY_MC_L3_CTL_OFFSET                          1
#define PARSER_SUMMARY_MC_L3_CTL_WORD_OFFSET                     0
#define PARSER_SUMMARY_MC_L3_CTL_F_OFFSET_MOD8                   7
#define PARSER_SUMMARY_MC_L3_CTL_F_OFFSET_MOD16                  7
#define PARSER_SUMMARY_IP_LENGTH_ERROR_F_OFFSET                  22
#define PARSER_SUMMARY_IP_LENGTH_ERROR_F_WIDTH                   1
#define PARSER_SUMMARY_IP_LENGTH_ERROR_OFFSET                    1
#define PARSER_SUMMARY_IP_LENGTH_ERROR_WORD_OFFSET               0
#define PARSER_SUMMARY_IP_LENGTH_ERROR_F_OFFSET_MOD8             6
#define PARSER_SUMMARY_IP_LENGTH_ERROR_F_OFFSET_MOD16            6
#define PARSER_SUMMARY_ICMPV6_F_OFFSET                           21
#define PARSER_SUMMARY_ICMPV6_F_WIDTH                            1
#define PARSER_SUMMARY_ICMPV6_OFFSET                             1
#define PARSER_SUMMARY_ICMPV6_WORD_OFFSET                        0
#define PARSER_SUMMARY_ICMPV6_F_OFFSET_MOD8                      5
#define PARSER_SUMMARY_ICMPV6_F_OFFSET_MOD16                     5
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_F_OFFSET              20
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_F_WIDTH               1
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_OFFSET                1
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_WORD_OFFSET           0
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_F_OFFSET_MOD8         4
#define PARSER_SUMMARY_HEADER_LENGTH_ERROR_F_OFFSET_MOD16        4
#define PARSER_SUMMARY_CHECKSUM_ERROR_F_OFFSET                   19
#define PARSER_SUMMARY_CHECKSUM_ERROR_F_WIDTH                    1
#define PARSER_SUMMARY_CHECKSUM_ERROR_OFFSET                     1
#define PARSER_SUMMARY_CHECKSUM_ERROR_WORD_OFFSET                0
#define PARSER_SUMMARY_CHECKSUM_ERROR_F_OFFSET_MOD8              3
#define PARSER_SUMMARY_CHECKSUM_ERROR_F_OFFSET_MOD16             3
#define PARSER_SUMMARY_VERSION_MISMATCH_F_OFFSET                 18
#define PARSER_SUMMARY_VERSION_MISMATCH_F_WIDTH                  1
#define PARSER_SUMMARY_VERSION_MISMATCH_OFFSET                   1
#define PARSER_SUMMARY_VERSION_MISMATCH_WORD_OFFSET              0
#define PARSER_SUMMARY_VERSION_MISMATCH_F_OFFSET_MOD8            2
#define PARSER_SUMMARY_VERSION_MISMATCH_F_OFFSET_MOD16           2
#define PARSER_SUMMARY_L3_PROTOCOL_F_OFFSET                      16
#define PARSER_SUMMARY_L3_PROTOCOL_F_WIDTH                       2
#define PARSER_SUMMARY_L3_PROTOCOL_OFFSET                        1
#define PARSER_SUMMARY_L3_PROTOCOL_WORD_OFFSET                   0
#define PARSER_SUMMARY_L3_PROTOCOL_F_OFFSET_MOD8                 0
#define PARSER_SUMMARY_L3_PROTOCOL_F_OFFSET_MOD16                0
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_F_OFFSET           15
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_F_WIDTH            1
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_OFFSET             2
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_WORD_OFFSET        0
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_F_OFFSET_MOD8      7
#define PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_F_OFFSET_MOD16     15
#define PARSER_SUMMARY_TCP_FLAG_F_OFFSET                         14
#define PARSER_SUMMARY_TCP_FLAG_F_WIDTH                          1
#define PARSER_SUMMARY_TCP_FLAG_OFFSET                           2
#define PARSER_SUMMARY_TCP_FLAG_WORD_OFFSET                      0
#define PARSER_SUMMARY_TCP_FLAG_F_OFFSET_MOD8                    6
#define PARSER_SUMMARY_TCP_FLAG_F_OFFSET_MOD16                   14
#define PARSER_SUMMARY_EXCEPTION_F_OFFSET                        13
#define PARSER_SUMMARY_EXCEPTION_F_WIDTH                         1
#define PARSER_SUMMARY_EXCEPTION_OFFSET                          2
#define PARSER_SUMMARY_EXCEPTION_WORD_OFFSET                     0
#define PARSER_SUMMARY_EXCEPTION_F_OFFSET_MOD8                   5
#define PARSER_SUMMARY_EXCEPTION_F_OFFSET_MOD16                  13
#define PARSER_SUMMARY_IP_MC_L2_F_OFFSET                         12
#define PARSER_SUMMARY_IP_MC_L2_F_WIDTH                          1
#define PARSER_SUMMARY_IP_MC_L2_OFFSET                           2
#define PARSER_SUMMARY_IP_MC_L2_WORD_OFFSET                      0
#define PARSER_SUMMARY_IP_MC_L2_F_OFFSET_MOD8                    4
#define PARSER_SUMMARY_IP_MC_L2_F_OFFSET_MOD16                   12
#define PARSER_SUMMARY_MC_L3_F_OFFSET                            11
#define PARSER_SUMMARY_MC_L3_F_WIDTH                             1
#define PARSER_SUMMARY_MC_L3_OFFSET                              2
#define PARSER_SUMMARY_MC_L3_WORD_OFFSET                         0
#define PARSER_SUMMARY_MC_L3_F_OFFSET_MOD8                       3
#define PARSER_SUMMARY_MC_L3_F_OFFSET_MOD16                      11
#define PARSER_SUMMARY_ERROR_F_OFFSET                            10
#define PARSER_SUMMARY_ERROR_F_WIDTH                             1
#define PARSER_SUMMARY_ERROR_OFFSET                              2
#define PARSER_SUMMARY_ERROR_WORD_OFFSET                         0
#define PARSER_SUMMARY_ERROR_F_OFFSET_MOD8                       2
#define PARSER_SUMMARY_ERROR_F_OFFSET_MOD16                      10
#define PARSER_SUMMARY_TUNNEL_F_OFFSET                           9
#define PARSER_SUMMARY_TUNNEL_F_WIDTH                            1
#define PARSER_SUMMARY_TUNNEL_OFFSET                             2
#define PARSER_SUMMARY_TUNNEL_WORD_OFFSET                        0
#define PARSER_SUMMARY_TUNNEL_F_OFFSET_MOD8                      1
#define PARSER_SUMMARY_TUNNEL_F_OFFSET_MOD16                     9
#define PARSER_SUMMARY__5_TUP_VALID_F_OFFSET                     8
#define PARSER_SUMMARY__5_TUP_VALID_F_WIDTH                      1
#define PARSER_SUMMARY__5_TUP_VALID_OFFSET                       2
#define PARSER_SUMMARY__5_TUP_VALID_WORD_OFFSET                  0
#define PARSER_SUMMARY__5_TUP_VALID_F_OFFSET_MOD8                0
#define PARSER_SUMMARY__5_TUP_VALID_F_OFFSET_MOD16               8
#define PARSER_SUMMARY_ETHERNET_VERSION_F_OFFSET                 6
#define PARSER_SUMMARY_ETHERNET_VERSION_F_WIDTH                  2
#define PARSER_SUMMARY_ETHERNET_VERSION_OFFSET                   3
#define PARSER_SUMMARY_ETHERNET_VERSION_WORD_OFFSET              0
#define PARSER_SUMMARY_ETHERNET_VERSION_F_OFFSET_MOD8            6
#define PARSER_SUMMARY_ETHERNET_VERSION_F_OFFSET_MOD16           6
#define PARSER_SUMMARY_DNS_F_OFFSET                              5
#define PARSER_SUMMARY_DNS_F_WIDTH                               1
#define PARSER_SUMMARY_DNS_OFFSET                                3
#define PARSER_SUMMARY_DNS_WORD_OFFSET                           0
#define PARSER_SUMMARY_DNS_F_OFFSET_MOD8                         5
#define PARSER_SUMMARY_DNS_F_OFFSET_MOD16                        5
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_F_OFFSET                4
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_F_WIDTH                 1
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_OFFSET                  3
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_WORD_OFFSET             0
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_F_OFFSET_MOD8           4
#define PARSER_SUMMARY_FIRST_IP_FRAGMENT_F_OFFSET_MOD16          4
#define PARSER_SUMMARY_L2_PROTOCOL_F_OFFSET                      0
#define PARSER_SUMMARY_L2_PROTOCOL_F_WIDTH                       4
#define PARSER_SUMMARY_L2_PROTOCOL_OFFSET                        3
#define PARSER_SUMMARY_L2_PROTOCOL_WORD_OFFSET                   0
#define PARSER_SUMMARY_L2_PROTOCOL_F_OFFSET_MOD8                 0
#define PARSER_SUMMARY_L2_PROTOCOL_F_OFFSET_MOD16                0

/* >>>RDD_PARSER_SUMMARY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	da_filter_match       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_fragment           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l4_1588               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_udp               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dhcp                  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	broadcast             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	multicast             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dos_attack            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	mc_l3_ctl             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_length_error       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	icmpv6                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	header_length_error   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	checksum_error        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	version_mismatch      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l3_protocol           	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6_ext_header_filter	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_flag              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	exception             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_mc_l2              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	mc_l3                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	error                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tunnel                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	_5_tup_valid          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ethernet_version      	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dns                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	first_ip_fragment     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l2_protocol           	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	l2_protocol           	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	first_ip_fragment     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dns                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ethernet_version      	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	_5_tup_valid          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tunnel                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	error                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	mc_l3                 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_mc_l2              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	exception             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_flag              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6_ext_header_filter	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l3_protocol           	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	version_mismatch      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	checksum_error        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	header_length_error   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	icmpv6                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_length_error       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	mc_l3_ctl             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dos_attack            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	multicast             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	broadcast             	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dhcp                  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_udp               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l4_1588               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_fragment           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	da_filter_match       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSER_SUMMARY_DTS;

typedef union
{
    uint32_t word_val[1];
    RDD_PARSER_SUMMARY_DTS fields;
} PARSER_SUMMARY_STRUCT;
#define RDD_PARSER_SUMMARY_DA_FILTER_MATCH_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 7, 1, r)
#define RDD_PARSER_SUMMARY_DA_FILTER_MATCH_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 7, 1, v)
#define RDD_PARSER_SUMMARY_DA_FILTER_MATCH_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_PARSER_SUMMARY_DA_FILTER_MATCH_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_PARSER_SUMMARY_IP_FRAGMENT_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 6, 1, r)
#define RDD_PARSER_SUMMARY_IP_FRAGMENT_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 6, 1, v)
#define RDD_PARSER_SUMMARY_IP_FRAGMENT_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p, 6, 1, r)
#define RDD_PARSER_SUMMARY_IP_FRAGMENT_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p, 6, 1, v)
#define RDD_PARSER_SUMMARY_L4_1588_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 5, 1, r)
#define RDD_PARSER_SUMMARY_L4_1588_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 5, 1, v)
#define RDD_PARSER_SUMMARY_L4_1588_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p, 5, 1, r)
#define RDD_PARSER_SUMMARY_L4_1588_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p, 5, 1, v)
#define RDD_PARSER_SUMMARY_TCP_UDP_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 4, 1, r)
#define RDD_PARSER_SUMMARY_TCP_UDP_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 4, 1, v)
#define RDD_PARSER_SUMMARY_TCP_UDP_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p, 4, 1, r)
#define RDD_PARSER_SUMMARY_TCP_UDP_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p, 4, 1, v)
#define RDD_PARSER_SUMMARY_DHCP_READ_G(r, g, idx)                            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 3, 1, r)
#define RDD_PARSER_SUMMARY_DHCP_WRITE_G(v, g, idx)                           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 3, 1, v)
#define RDD_PARSER_SUMMARY_DHCP_READ(r, p)                                   FIELD_MREAD_8((uint8_t *)p, 3, 1, r)
#define RDD_PARSER_SUMMARY_DHCP_WRITE(v, p)                                  FIELD_MWRITE_8((uint8_t *)p, 3, 1, v)
#define RDD_PARSER_SUMMARY_BROADCAST_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 2, 1, r)
#define RDD_PARSER_SUMMARY_BROADCAST_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 2, 1, v)
#define RDD_PARSER_SUMMARY_BROADCAST_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p, 2, 1, r)
#define RDD_PARSER_SUMMARY_BROADCAST_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p, 2, 1, v)
#define RDD_PARSER_SUMMARY_MULTICAST_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 1, 1, r)
#define RDD_PARSER_SUMMARY_MULTICAST_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 1, 1, v)
#define RDD_PARSER_SUMMARY_MULTICAST_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p, 1, 1, r)
#define RDD_PARSER_SUMMARY_MULTICAST_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p, 1, 1, v)
#define RDD_PARSER_SUMMARY_DOS_ATTACK_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 0, 1, r)
#define RDD_PARSER_SUMMARY_DOS_ATTACK_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS), 0, 1, v)
#define RDD_PARSER_SUMMARY_DOS_ATTACK_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p, 0, 1, r)
#define RDD_PARSER_SUMMARY_DOS_ATTACK_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p, 0, 1, v)
#define RDD_PARSER_SUMMARY_MC_L3_CTL_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 7, 1, r)
#define RDD_PARSER_SUMMARY_MC_L3_CTL_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 7, 1, v)
#define RDD_PARSER_SUMMARY_MC_L3_CTL_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p + 1, 7, 1, r)
#define RDD_PARSER_SUMMARY_MC_L3_CTL_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p + 1, 7, 1, v)
#define RDD_PARSER_SUMMARY_IP_LENGTH_ERROR_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 6, 1, r)
#define RDD_PARSER_SUMMARY_IP_LENGTH_ERROR_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 6, 1, v)
#define RDD_PARSER_SUMMARY_IP_LENGTH_ERROR_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 1, 6, 1, r)
#define RDD_PARSER_SUMMARY_IP_LENGTH_ERROR_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 1, 6, 1, v)
#define RDD_PARSER_SUMMARY_ICMPV6_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 5, 1, r)
#define RDD_PARSER_SUMMARY_ICMPV6_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 5, 1, v)
#define RDD_PARSER_SUMMARY_ICMPV6_READ(r, p)                                 FIELD_MREAD_8((uint8_t *)p + 1, 5, 1, r)
#define RDD_PARSER_SUMMARY_ICMPV6_WRITE(v, p)                                FIELD_MWRITE_8((uint8_t *)p + 1, 5, 1, v)
#define RDD_PARSER_SUMMARY_HEADER_LENGTH_ERROR_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 4, 1, r)
#define RDD_PARSER_SUMMARY_HEADER_LENGTH_ERROR_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 4, 1, v)
#define RDD_PARSER_SUMMARY_HEADER_LENGTH_ERROR_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p + 1, 4, 1, r)
#define RDD_PARSER_SUMMARY_HEADER_LENGTH_ERROR_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p + 1, 4, 1, v)
#define RDD_PARSER_SUMMARY_CHECKSUM_ERROR_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 3, 1, r)
#define RDD_PARSER_SUMMARY_CHECKSUM_ERROR_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 3, 1, v)
#define RDD_PARSER_SUMMARY_CHECKSUM_ERROR_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 1, 3, 1, r)
#define RDD_PARSER_SUMMARY_CHECKSUM_ERROR_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 1, 3, 1, v)
#define RDD_PARSER_SUMMARY_VERSION_MISMATCH_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 2, 1, r)
#define RDD_PARSER_SUMMARY_VERSION_MISMATCH_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 2, 1, v)
#define RDD_PARSER_SUMMARY_VERSION_MISMATCH_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 1, 2, 1, r)
#define RDD_PARSER_SUMMARY_VERSION_MISMATCH_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 1, 2, 1, v)
#define RDD_PARSER_SUMMARY_L3_PROTOCOL_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 0, 2, r)
#define RDD_PARSER_SUMMARY_L3_PROTOCOL_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 1, 0, 2, v)
#define RDD_PARSER_SUMMARY_L3_PROTOCOL_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 1, 0, 2, r)
#define RDD_PARSER_SUMMARY_L3_PROTOCOL_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 1, 0, 2, v)
#define RDD_PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 7, 1, r)
#define RDD_PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 7, 1, v)
#define RDD_PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 2, 7, 1, r)
#define RDD_PARSER_SUMMARY_IPV6_EXT_HEADER_FILTER_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 2, 7, 1, v)
#define RDD_PARSER_SUMMARY_TCP_FLAG_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 6, 1, r)
#define RDD_PARSER_SUMMARY_TCP_FLAG_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 6, 1, v)
#define RDD_PARSER_SUMMARY_TCP_FLAG_READ(r, p)                               FIELD_MREAD_8((uint8_t *)p + 2, 6, 1, r)
#define RDD_PARSER_SUMMARY_TCP_FLAG_WRITE(v, p)                              FIELD_MWRITE_8((uint8_t *)p + 2, 6, 1, v)
#define RDD_PARSER_SUMMARY_EXCEPTION_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 5, 1, r)
#define RDD_PARSER_SUMMARY_EXCEPTION_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 5, 1, v)
#define RDD_PARSER_SUMMARY_EXCEPTION_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p + 2, 5, 1, r)
#define RDD_PARSER_SUMMARY_EXCEPTION_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p + 2, 5, 1, v)
#define RDD_PARSER_SUMMARY_IP_MC_L2_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 4, 1, r)
#define RDD_PARSER_SUMMARY_IP_MC_L2_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 4, 1, v)
#define RDD_PARSER_SUMMARY_IP_MC_L2_READ(r, p)                               FIELD_MREAD_8((uint8_t *)p + 2, 4, 1, r)
#define RDD_PARSER_SUMMARY_IP_MC_L2_WRITE(v, p)                              FIELD_MWRITE_8((uint8_t *)p + 2, 4, 1, v)
#define RDD_PARSER_SUMMARY_MC_L3_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 3, 1, r)
#define RDD_PARSER_SUMMARY_MC_L3_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 3, 1, v)
#define RDD_PARSER_SUMMARY_MC_L3_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 2, 3, 1, r)
#define RDD_PARSER_SUMMARY_MC_L3_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 2, 3, 1, v)
#define RDD_PARSER_SUMMARY_ERROR_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 2, 1, r)
#define RDD_PARSER_SUMMARY_ERROR_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 2, 1, v)
#define RDD_PARSER_SUMMARY_ERROR_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 2, 2, 1, r)
#define RDD_PARSER_SUMMARY_ERROR_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 2, 2, 1, v)
#define RDD_PARSER_SUMMARY_TUNNEL_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 1, 1, r)
#define RDD_PARSER_SUMMARY_TUNNEL_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 1, 1, v)
#define RDD_PARSER_SUMMARY_TUNNEL_READ(r, p)                                 FIELD_MREAD_8((uint8_t *)p + 2, 1, 1, r)
#define RDD_PARSER_SUMMARY_TUNNEL_WRITE(v, p)                                FIELD_MWRITE_8((uint8_t *)p + 2, 1, 1, v)
#define RDD_PARSER_SUMMARY__5_TUP_VALID_READ_G(r, g, idx)                    GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 0, 1, r)
#define RDD_PARSER_SUMMARY__5_TUP_VALID_WRITE_G(v, g, idx)                   GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 2, 0, 1, v)
#define RDD_PARSER_SUMMARY__5_TUP_VALID_READ(r, p)                           FIELD_MREAD_8((uint8_t *)p + 2, 0, 1, r)
#define RDD_PARSER_SUMMARY__5_TUP_VALID_WRITE(v, p)                          FIELD_MWRITE_8((uint8_t *)p + 2, 0, 1, v)
#define RDD_PARSER_SUMMARY_ETHERNET_VERSION_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 6, 2, r)
#define RDD_PARSER_SUMMARY_ETHERNET_VERSION_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 6, 2, v)
#define RDD_PARSER_SUMMARY_ETHERNET_VERSION_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 3, 6, 2, r)
#define RDD_PARSER_SUMMARY_ETHERNET_VERSION_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 3, 6, 2, v)
#define RDD_PARSER_SUMMARY_DNS_READ_G(r, g, idx)                             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 5, 1, r)
#define RDD_PARSER_SUMMARY_DNS_WRITE_G(v, g, idx)                            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 5, 1, v)
#define RDD_PARSER_SUMMARY_DNS_READ(r, p)                                    FIELD_MREAD_8((uint8_t *)p + 3, 5, 1, r)
#define RDD_PARSER_SUMMARY_DNS_WRITE(v, p)                                   FIELD_MWRITE_8((uint8_t *)p + 3, 5, 1, v)
#define RDD_PARSER_SUMMARY_FIRST_IP_FRAGMENT_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 4, 1, r)
#define RDD_PARSER_SUMMARY_FIRST_IP_FRAGMENT_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 4, 1, v)
#define RDD_PARSER_SUMMARY_FIRST_IP_FRAGMENT_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 3, 4, 1, r)
#define RDD_PARSER_SUMMARY_FIRST_IP_FRAGMENT_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 3, 4, 1, v)
#define RDD_PARSER_SUMMARY_L2_PROTOCOL_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 0, 4, r)
#define RDD_PARSER_SUMMARY_L2_PROTOCOL_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_SUMMARY_DTS) + 3, 0, 4, v)
#define RDD_PARSER_SUMMARY_L2_PROTOCOL_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 3, 0, 4, r)
#define RDD_PARSER_SUMMARY_L2_PROTOCOL_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 3, 0, 4, v)
/* <<<RDD_PARSER_SUMMARY_DTS */

/* <<<RDD_PARSER_SUMMARY */


/* >>>RDD_PARSER_RESULTS */
#define PARSER_RESULTS_L4_PROTOCOL_F_OFFSET                      28
#define PARSER_RESULTS_L4_PROTOCOL_F_WIDTH                       4
#define PARSER_RESULTS_PARSER_RESULTS_OFFSET                     0
#define PARSER_RESULTS_L4_PROTOCOL_OFFSET                        0
#define PARSER_RESULTS_L4_PROTOCOL_WORD_OFFSET                   0
#define PARSER_RESULTS_L4_PROTOCOL_F_OFFSET_MOD8                 4
#define PARSER_RESULTS_L4_PROTOCOL_F_OFFSET_MOD16                12
#define PARSER_RESULTS_V6_AH_F_OFFSET                            27
#define PARSER_RESULTS_V6_AH_F_WIDTH                             1
#define PARSER_RESULTS_V6_AH_OFFSET                              0
#define PARSER_RESULTS_V6_AH_WORD_OFFSET                         0
#define PARSER_RESULTS_V6_AH_F_OFFSET_MOD8                       3
#define PARSER_RESULTS_V6_AH_F_OFFSET_MOD16                      11
#define PARSER_RESULTS_V6_DEST_OPT_F_OFFSET                      26
#define PARSER_RESULTS_V6_DEST_OPT_F_WIDTH                       1
#define PARSER_RESULTS_V6_DEST_OPT_OFFSET                        0
#define PARSER_RESULTS_V6_DEST_OPT_WORD_OFFSET                   0
#define PARSER_RESULTS_V6_DEST_OPT_F_OFFSET_MOD8                 2
#define PARSER_RESULTS_V6_DEST_OPT_F_OFFSET_MOD16                10
#define PARSER_RESULTS_V6_ROUTE_F_OFFSET                         25
#define PARSER_RESULTS_V6_ROUTE_F_WIDTH                          1
#define PARSER_RESULTS_V6_ROUTE_OFFSET                           0
#define PARSER_RESULTS_V6_ROUTE_WORD_OFFSET                      0
#define PARSER_RESULTS_V6_ROUTE_F_OFFSET_MOD8                    1
#define PARSER_RESULTS_V6_ROUTE_F_OFFSET_MOD16                   9
#define PARSER_RESULTS_V6_HOP_F_OFFSET                           24
#define PARSER_RESULTS_V6_HOP_F_WIDTH                            1
#define PARSER_RESULTS_V6_HOP_OFFSET                             0
#define PARSER_RESULTS_V6_HOP_WORD_OFFSET                        0
#define PARSER_RESULTS_V6_HOP_F_OFFSET_MOD8                      0
#define PARSER_RESULTS_V6_HOP_F_OFFSET_MOD16                     8
#define PARSER_RESULTS_TCP_FLAGS_F_OFFSET                        16
#define PARSER_RESULTS_TCP_FLAGS_F_WIDTH                         8
#define PARSER_RESULTS_TCP_FLAGS_OFFSET                          1
#define PARSER_RESULTS_TCP_FLAGS_WORD_OFFSET                     0
#define PARSER_RESULTS_TCP_FLAGS_F_OFFSET_MOD16                  0
#define PARSER_RESULTS_LAYER3_OFFSET_F_OFFSET                    8
#define PARSER_RESULTS_LAYER3_OFFSET_F_WIDTH                     8
#define PARSER_RESULTS_LAYER3_OFFSET_OFFSET                      2
#define PARSER_RESULTS_LAYER3_OFFSET_WORD_OFFSET                 0
#define PARSER_RESULTS_LAYER3_OFFSET_F_OFFSET_MOD16              8
#define PARSER_RESULTS_LAYER4_OFFSET_F_OFFSET                    0
#define PARSER_RESULTS_LAYER4_OFFSET_F_WIDTH                     8
#define PARSER_RESULTS_LAYER4_OFFSET_OFFSET                      3
#define PARSER_RESULTS_LAYER4_OFFSET_WORD_OFFSET                 0
#define PARSER_RESULTS_LAYER4_OFFSET_F_OFFSET_MOD16              0
#define PARSER_RESULTS_OUTER_VLAN_F_OFFSET                       16
#define PARSER_RESULTS_OUTER_VLAN_F_WIDTH                        16
#define PARSER_RESULTS_OUTER_VLAN_OFFSET                         4
#define PARSER_RESULTS_OUTER_VLAN_WORD_OFFSET                    1
#define PARSER_RESULTS_MAC_DA1_2_F_OFFSET                        0
#define PARSER_RESULTS_MAC_DA1_2_F_WIDTH                         16
#define PARSER_RESULTS_MAC_DA1_2_OFFSET                          6
#define PARSER_RESULTS_MAC_DA1_2_WORD_OFFSET                     1
#define PARSER_RESULTS_MAC_DA3_6_F_OFFSET                        0
#define PARSER_RESULTS_MAC_DA3_6_F_WIDTH                         32
#define PARSER_RESULTS_MAC_DA3_6_OFFSET                          8
#define PARSER_RESULTS_MAC_DA3_6_WORD_OFFSET                     2
#define PARSER_RESULTS_INNER_VLAN_F_OFFSET                       16
#define PARSER_RESULTS_INNER_VLAN_F_WIDTH                        16
#define PARSER_RESULTS_INNER_VLAN_OFFSET                         12
#define PARSER_RESULTS_INNER_VLAN_WORD_OFFSET                    3
#define PARSER_RESULTS_MAC_SA1_2_F_OFFSET                        0
#define PARSER_RESULTS_MAC_SA1_2_F_WIDTH                         16
#define PARSER_RESULTS_MAC_SA1_2_OFFSET                          14
#define PARSER_RESULTS_MAC_SA1_2_WORD_OFFSET                     3
#define PARSER_RESULTS_MAC_SA3_6_F_OFFSET                        0
#define PARSER_RESULTS_MAC_SA3_6_F_WIDTH                         32
#define PARSER_RESULTS_MAC_SA3_6_OFFSET                          16
#define PARSER_RESULTS_MAC_SA3_6_WORD_OFFSET                     4
#define PARSER_RESULTS_ICMPV6_TYPE_F_OFFSET                      24
#define PARSER_RESULTS_ICMPV6_TYPE_F_WIDTH                       8
#define PARSER_RESULTS_ICMPV6_TYPE_OFFSET                        20
#define PARSER_RESULTS_ICMPV6_TYPE_WORD_OFFSET                   5
#define PARSER_RESULTS_ICMPV6_TYPE_F_OFFSET_MOD16                8
#define PARSER_RESULTS_IP_TTL_F_OFFSET                           16
#define PARSER_RESULTS_IP_TTL_F_WIDTH                            8
#define PARSER_RESULTS_IP_TTL_OFFSET                             21
#define PARSER_RESULTS_IP_TTL_WORD_OFFSET                        5
#define PARSER_RESULTS_IP_TTL_F_OFFSET_MOD16                     0
#define PARSER_RESULTS_IP_LENGTH_F_OFFSET                        0
#define PARSER_RESULTS_IP_LENGTH_F_WIDTH                         16
#define PARSER_RESULTS_IP_LENGTH_OFFSET                          22
#define PARSER_RESULTS_IP_LENGTH_WORD_OFFSET                     5
#define PARSER_RESULTS_IP_FILTER_MATCH_F_OFFSET                  31
#define PARSER_RESULTS_IP_FILTER_MATCH_F_WIDTH                   1
#define PARSER_RESULTS_IP_FILTER_MATCH_OFFSET                    24
#define PARSER_RESULTS_IP_FILTER_MATCH_WORD_OFFSET               6
#define PARSER_RESULTS_IP_FILTER_MATCH_F_OFFSET_MOD8             7
#define PARSER_RESULTS_IP_FILTER_MATCH_F_OFFSET_MOD16            15
#define PARSER_RESULTS_IP_FILTER_NUM_F_OFFSET                    30
#define PARSER_RESULTS_IP_FILTER_NUM_F_WIDTH                     1
#define PARSER_RESULTS_IP_FILTER_NUM_OFFSET                      24
#define PARSER_RESULTS_IP_FILTER_NUM_WORD_OFFSET                 6
#define PARSER_RESULTS_IP_FILTER_NUM_F_OFFSET_MOD8               6
#define PARSER_RESULTS_IP_FILTER_NUM_F_OFFSET_MOD16              14
#define PARSER_RESULTS_P_TAG_F_OFFSET                            29
#define PARSER_RESULTS_P_TAG_F_WIDTH                             1
#define PARSER_RESULTS_P_TAG_OFFSET                              24
#define PARSER_RESULTS_P_TAG_WORD_OFFSET                         6
#define PARSER_RESULTS_P_TAG_F_OFFSET_MOD8                       5
#define PARSER_RESULTS_P_TAG_F_OFFSET_MOD16                      13
#define PARSER_RESULTS_VID_FILTER_HIT_F_OFFSET                   28
#define PARSER_RESULTS_VID_FILTER_HIT_F_WIDTH                    1
#define PARSER_RESULTS_VID_FILTER_HIT_OFFSET                     24
#define PARSER_RESULTS_VID_FILTER_HIT_WORD_OFFSET                6
#define PARSER_RESULTS_VID_FILTER_HIT_F_OFFSET_MOD8              4
#define PARSER_RESULTS_VID_FILTER_HIT_F_OFFSET_MOD16             12
#define PARSER_RESULTS_DA_FILTER_NUMBER_F_OFFSET                 24
#define PARSER_RESULTS_DA_FILTER_NUMBER_F_WIDTH                  4
#define PARSER_RESULTS_DA_FILTER_NUMBER_OFFSET                   24
#define PARSER_RESULTS_DA_FILTER_NUMBER_WORD_OFFSET              6
#define PARSER_RESULTS_DA_FILTER_NUMBER_F_OFFSET_MOD8            0
#define PARSER_RESULTS_DA_FILTER_NUMBER_F_OFFSET_MOD16           8
#define PARSER_RESULTS_TAG_TYPE_F_OFFSET                         22
#define PARSER_RESULTS_TAG_TYPE_F_WIDTH                          2
#define PARSER_RESULTS_TAG_TYPE_OFFSET                           25
#define PARSER_RESULTS_TAG_TYPE_WORD_OFFSET                      6
#define PARSER_RESULTS_TAG_TYPE_F_OFFSET_MOD8                    6
#define PARSER_RESULTS_TAG_TYPE_F_OFFSET_MOD16                   6
#define PARSER_RESULTS_TPID_VLAN_0_F_OFFSET                      19
#define PARSER_RESULTS_TPID_VLAN_0_F_WIDTH                       3
#define PARSER_RESULTS_TPID_VLAN_0_OFFSET                        25
#define PARSER_RESULTS_TPID_VLAN_0_WORD_OFFSET                   6
#define PARSER_RESULTS_TPID_VLAN_0_F_OFFSET_MOD8                 3
#define PARSER_RESULTS_TPID_VLAN_0_F_OFFSET_MOD16                3
#define PARSER_RESULTS_TPID_VLAN_1_F_OFFSET                      16
#define PARSER_RESULTS_TPID_VLAN_1_F_WIDTH                       3
#define PARSER_RESULTS_TPID_VLAN_1_OFFSET                        25
#define PARSER_RESULTS_TPID_VLAN_1_WORD_OFFSET                   6
#define PARSER_RESULTS_TPID_VLAN_1_F_OFFSET_MOD8                 0
#define PARSER_RESULTS_TPID_VLAN_1_F_OFFSET_MOD16                0
#define PARSER_RESULTS_VID_FILTER_MATCH_F_OFFSET                 12
#define PARSER_RESULTS_VID_FILTER_MATCH_F_WIDTH                  4
#define PARSER_RESULTS_VID_FILTER_MATCH_OFFSET                   26
#define PARSER_RESULTS_VID_FILTER_MATCH_WORD_OFFSET              6
#define PARSER_RESULTS_VID_FILTER_MATCH_F_OFFSET_MOD8            4
#define PARSER_RESULTS_VID_FILTER_MATCH_F_OFFSET_MOD16           12
#define PARSER_RESULTS_DOS_ATTACK_REASON_F_OFFSET                8
#define PARSER_RESULTS_DOS_ATTACK_REASON_F_WIDTH                 4
#define PARSER_RESULTS_DOS_ATTACK_REASON_OFFSET                  26
#define PARSER_RESULTS_DOS_ATTACK_REASON_WORD_OFFSET             6
#define PARSER_RESULTS_DOS_ATTACK_REASON_F_OFFSET_MOD8           0
#define PARSER_RESULTS_DOS_ATTACK_REASON_F_OFFSET_MOD16          8
#define PARSER_RESULTS_LAYER2_ADDRESS_F_OFFSET                   0
#define PARSER_RESULTS_LAYER2_ADDRESS_F_WIDTH                    8
#define PARSER_RESULTS_LAYER2_ADDRESS_OFFSET                     27
#define PARSER_RESULTS_LAYER2_ADDRESS_WORD_OFFSET                6
#define PARSER_RESULTS_LAYER2_ADDRESS_F_OFFSET_MOD16             0

/* >>>RDD_PARSER_RESULTS_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	l4_protocol      	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /*defined by rdd_parser_l4_protocol enumeration*/
	uint32_t	v6_ah            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_dest_opt      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_route         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_hop           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	tcp_flags        	;
	uint8_t	layer3_offset    	;
	uint8_t	layer4_offset    	;
	uint16_t	outer_vlan       	;
	uint16_t	mac_da1_2        	;
	uint32_t	mac_da3_6        	;
	uint16_t	inner_vlan       	;
	uint16_t	mac_sa1_2        	;
	uint32_t	mac_sa3_6        	;
	uint8_t	icmpv6_type      	;
	uint8_t	ip_ttl           	;
	uint16_t	ip_length        	;
	uint32_t	ip_filter_match  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_filter_num    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	p_tag            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vid_filter_hit   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	da_filter_number 	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tag_type         	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_0      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_1      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vid_filter_match 	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dos_attack_reason	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	layer2_address   	;
#else
	uint8_t	layer4_offset    	;
	uint8_t	layer3_offset    	;
	uint8_t	tcp_flags        	;
	uint32_t	v6_hop           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_route         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_dest_opt      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	v6_ah            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	l4_protocol      	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /*defined by rdd_parser_l4_protocol enumeration*/
	uint16_t	mac_da1_2        	;
	uint16_t	outer_vlan       	;
	uint32_t	mac_da3_6        	;
	uint16_t	mac_sa1_2        	;
	uint16_t	inner_vlan       	;
	uint32_t	mac_sa3_6        	;
	uint16_t	ip_length        	;
	uint8_t	ip_ttl           	;
	uint8_t	icmpv6_type      	;
	uint8_t	layer2_address   	;
	uint32_t	dos_attack_reason	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vid_filter_match 	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_1      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_0      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tag_type         	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	da_filter_number 	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vid_filter_hit   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	p_tag            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_filter_num    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ip_filter_match  	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSER_RESULTS_DTS;

typedef union
{
    uint32_t word_val[7];
    uint64_t dword_val64[3];
    RDD_PARSER_RESULTS_DTS fields;
} PARSER_RESULTS_STRUCT;
#define RDD_PARSER_RESULTS_L4_PROTOCOL_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 4, 4, r) /*defined by rdd_parser_l4_protocol enumeration*/
#define RDD_PARSER_RESULTS_L4_PROTOCOL_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 4, 4, v) /*defined by rdd_parser_l4_protocol enumeration*/
#define RDD_PARSER_RESULTS_L4_PROTOCOL_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p, 4, 4, r) /*defined by rdd_parser_l4_protocol enumeration*/
#define RDD_PARSER_RESULTS_L4_PROTOCOL_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p, 4, 4, v) /*defined by rdd_parser_l4_protocol enumeration*/
#define RDD_PARSER_RESULTS_V6_AH_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 3, 1, r)
#define RDD_PARSER_RESULTS_V6_AH_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 3, 1, v)
#define RDD_PARSER_RESULTS_V6_AH_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p, 3, 1, r)
#define RDD_PARSER_RESULTS_V6_AH_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p, 3, 1, v)
#define RDD_PARSER_RESULTS_V6_DEST_OPT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 2, 1, r)
#define RDD_PARSER_RESULTS_V6_DEST_OPT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 2, 1, v)
#define RDD_PARSER_RESULTS_V6_DEST_OPT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p, 2, 1, r)
#define RDD_PARSER_RESULTS_V6_DEST_OPT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p, 2, 1, v)
#define RDD_PARSER_RESULTS_V6_ROUTE_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 1, 1, r)
#define RDD_PARSER_RESULTS_V6_ROUTE_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 1, 1, v)
#define RDD_PARSER_RESULTS_V6_ROUTE_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p, 1, 1, r)
#define RDD_PARSER_RESULTS_V6_ROUTE_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p, 1, 1, v)
#define RDD_PARSER_RESULTS_V6_HOP_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 0, 1, r)
#define RDD_PARSER_RESULTS_V6_HOP_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS), 0, 1, v)
#define RDD_PARSER_RESULTS_V6_HOP_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p, 0, 1, r)
#define RDD_PARSER_RESULTS_V6_HOP_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p, 0, 1, v)
#define RDD_PARSER_RESULTS_TCP_FLAGS_READ_G(r, g, idx)                  GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 1, r)
#define RDD_PARSER_RESULTS_TCP_FLAGS_WRITE_G(v, g, idx)                 GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 1, v)
#define RDD_PARSER_RESULTS_TCP_FLAGS_READ(r, p)                         MREAD_8((uint8_t *)p + 1, r)
#define RDD_PARSER_RESULTS_TCP_FLAGS_WRITE(v, p)                        MWRITE_8((uint8_t *)p + 1, v)
#define RDD_PARSER_RESULTS_LAYER3_OFFSET_READ_G(r, g, idx)              GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 2, r)
#define RDD_PARSER_RESULTS_LAYER3_OFFSET_WRITE_G(v, g, idx)             GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 2, v)
#define RDD_PARSER_RESULTS_LAYER3_OFFSET_READ(r, p)                     MREAD_8((uint8_t *)p + 2, r)
#define RDD_PARSER_RESULTS_LAYER3_OFFSET_WRITE(v, p)                    MWRITE_8((uint8_t *)p + 2, v)
#define RDD_PARSER_RESULTS_LAYER4_OFFSET_READ_G(r, g, idx)              GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 3, r)
#define RDD_PARSER_RESULTS_LAYER4_OFFSET_WRITE_G(v, g, idx)             GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 3, v)
#define RDD_PARSER_RESULTS_LAYER4_OFFSET_READ(r, p)                     MREAD_8((uint8_t *)p + 3, r)
#define RDD_PARSER_RESULTS_LAYER4_OFFSET_WRITE(v, p)                    MWRITE_8((uint8_t *)p + 3, v)
#define RDD_PARSER_RESULTS_OUTER_VLAN_READ_G(r, g, idx)                 GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 4, r)
#define RDD_PARSER_RESULTS_OUTER_VLAN_WRITE_G(v, g, idx)                GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 4, v)
#define RDD_PARSER_RESULTS_OUTER_VLAN_READ(r, p)                        MREAD_16((uint8_t *)p + 4, r)
#define RDD_PARSER_RESULTS_OUTER_VLAN_WRITE(v, p)                       MWRITE_16((uint8_t *)p + 4, v)
#define RDD_PARSER_RESULTS_MAC_DA1_2_READ_G(r, g, idx)                  GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 6, r)
#define RDD_PARSER_RESULTS_MAC_DA1_2_WRITE_G(v, g, idx)                 GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 6, v)
#define RDD_PARSER_RESULTS_MAC_DA1_2_READ(r, p)                         MREAD_16((uint8_t *)p + 6, r)
#define RDD_PARSER_RESULTS_MAC_DA1_2_WRITE(v, p)                        MWRITE_16((uint8_t *)p + 6, v)
#define RDD_PARSER_RESULTS_MAC_DA3_6_READ_G(r, g, idx)                  GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 8, r)
#define RDD_PARSER_RESULTS_MAC_DA3_6_WRITE_G(v, g, idx)                 GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 8, v)
#define RDD_PARSER_RESULTS_MAC_DA3_6_READ(r, p)                         MREAD_32((uint8_t *)p + 8, r)
#define RDD_PARSER_RESULTS_MAC_DA3_6_WRITE(v, p)                        MWRITE_32((uint8_t *)p + 8, v)
#define RDD_PARSER_RESULTS_INNER_VLAN_READ_G(r, g, idx)                 GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 12, r)
#define RDD_PARSER_RESULTS_INNER_VLAN_WRITE_G(v, g, idx)                GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 12, v)
#define RDD_PARSER_RESULTS_INNER_VLAN_READ(r, p)                        MREAD_16((uint8_t *)p + 12, r)
#define RDD_PARSER_RESULTS_INNER_VLAN_WRITE(v, p)                       MWRITE_16((uint8_t *)p + 12, v)
#define RDD_PARSER_RESULTS_MAC_SA1_2_READ_G(r, g, idx)                  GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 14, r)
#define RDD_PARSER_RESULTS_MAC_SA1_2_WRITE_G(v, g, idx)                 GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 14, v)
#define RDD_PARSER_RESULTS_MAC_SA1_2_READ(r, p)                         MREAD_16((uint8_t *)p + 14, r)
#define RDD_PARSER_RESULTS_MAC_SA1_2_WRITE(v, p)                        MWRITE_16((uint8_t *)p + 14, v)
#define RDD_PARSER_RESULTS_MAC_SA3_6_READ_G(r, g, idx)                  GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 16, r)
#define RDD_PARSER_RESULTS_MAC_SA3_6_WRITE_G(v, g, idx)                 GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 16, v)
#define RDD_PARSER_RESULTS_MAC_SA3_6_READ(r, p)                         MREAD_32((uint8_t *)p + 16, r)
#define RDD_PARSER_RESULTS_MAC_SA3_6_WRITE(v, p)                        MWRITE_32((uint8_t *)p + 16, v)
#define RDD_PARSER_RESULTS_ICMPV6_TYPE_READ_G(r, g, idx)                GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 20, r)
#define RDD_PARSER_RESULTS_ICMPV6_TYPE_WRITE_G(v, g, idx)               GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 20, v)
#define RDD_PARSER_RESULTS_ICMPV6_TYPE_READ(r, p)                       MREAD_8((uint8_t *)p + 20, r)
#define RDD_PARSER_RESULTS_ICMPV6_TYPE_WRITE(v, p)                      MWRITE_8((uint8_t *)p + 20, v)
#define RDD_PARSER_RESULTS_IP_TTL_READ_G(r, g, idx)                     GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 21, r)
#define RDD_PARSER_RESULTS_IP_TTL_WRITE_G(v, g, idx)                    GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 21, v)
#define RDD_PARSER_RESULTS_IP_TTL_READ(r, p)                            MREAD_8((uint8_t *)p + 21, r)
#define RDD_PARSER_RESULTS_IP_TTL_WRITE(v, p)                           MWRITE_8((uint8_t *)p + 21, v)
#define RDD_PARSER_RESULTS_IP_LENGTH_READ_G(r, g, idx)                  GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 22, r)
#define RDD_PARSER_RESULTS_IP_LENGTH_WRITE_G(v, g, idx)                 GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 22, v)
#define RDD_PARSER_RESULTS_IP_LENGTH_READ(r, p)                         MREAD_16((uint8_t *)p + 22, r)
#define RDD_PARSER_RESULTS_IP_LENGTH_WRITE(v, p)                        MWRITE_16((uint8_t *)p + 22, v)
#define RDD_PARSER_RESULTS_IP_FILTER_MATCH_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 7, 1, r)
#define RDD_PARSER_RESULTS_IP_FILTER_MATCH_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 7, 1, v)
#define RDD_PARSER_RESULTS_IP_FILTER_MATCH_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 24, 7, 1, r)
#define RDD_PARSER_RESULTS_IP_FILTER_MATCH_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 24, 7, 1, v)
#define RDD_PARSER_RESULTS_IP_FILTER_NUM_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 6, 1, r)
#define RDD_PARSER_RESULTS_IP_FILTER_NUM_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 6, 1, v)
#define RDD_PARSER_RESULTS_IP_FILTER_NUM_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 24, 6, 1, r)
#define RDD_PARSER_RESULTS_IP_FILTER_NUM_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 24, 6, 1, v)
#define RDD_PARSER_RESULTS_P_TAG_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 5, 1, r)
#define RDD_PARSER_RESULTS_P_TAG_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 5, 1, v)
#define RDD_PARSER_RESULTS_P_TAG_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 24, 5, 1, r)
#define RDD_PARSER_RESULTS_P_TAG_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 24, 5, 1, v)
#define RDD_PARSER_RESULTS_VID_FILTER_HIT_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 4, 1, r)
#define RDD_PARSER_RESULTS_VID_FILTER_HIT_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 4, 1, v)
#define RDD_PARSER_RESULTS_VID_FILTER_HIT_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p + 24, 4, 1, r)
#define RDD_PARSER_RESULTS_VID_FILTER_HIT_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p + 24, 4, 1, v)
#define RDD_PARSER_RESULTS_DA_FILTER_NUMBER_READ_G(r, g, idx)           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 0, 4, r)
#define RDD_PARSER_RESULTS_DA_FILTER_NUMBER_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 24, 0, 4, v)
#define RDD_PARSER_RESULTS_DA_FILTER_NUMBER_READ(r, p)                  FIELD_MREAD_8((uint8_t *)p + 24, 0, 4, r)
#define RDD_PARSER_RESULTS_DA_FILTER_NUMBER_WRITE(v, p)                 FIELD_MWRITE_8((uint8_t *)p + 24, 0, 4, v)
#define RDD_PARSER_RESULTS_TAG_TYPE_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 6, 2, r)
#define RDD_PARSER_RESULTS_TAG_TYPE_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 6, 2, v)
#define RDD_PARSER_RESULTS_TAG_TYPE_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p + 25, 6, 2, r)
#define RDD_PARSER_RESULTS_TAG_TYPE_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p + 25, 6, 2, v)
#define RDD_PARSER_RESULTS_TPID_VLAN_0_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 3, 3, r)
#define RDD_PARSER_RESULTS_TPID_VLAN_0_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 3, 3, v)
#define RDD_PARSER_RESULTS_TPID_VLAN_0_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 25, 3, 3, r)
#define RDD_PARSER_RESULTS_TPID_VLAN_0_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 25, 3, 3, v)
#define RDD_PARSER_RESULTS_TPID_VLAN_1_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 0, 3, r)
#define RDD_PARSER_RESULTS_TPID_VLAN_1_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 25, 0, 3, v)
#define RDD_PARSER_RESULTS_TPID_VLAN_1_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 25, 0, 3, r)
#define RDD_PARSER_RESULTS_TPID_VLAN_1_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 25, 0, 3, v)
#define RDD_PARSER_RESULTS_VID_FILTER_MATCH_READ_G(r, g, idx)           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 26, 4, 4, r)
#define RDD_PARSER_RESULTS_VID_FILTER_MATCH_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 26, 4, 4, v)
#define RDD_PARSER_RESULTS_VID_FILTER_MATCH_READ(r, p)                  FIELD_MREAD_8((uint8_t *)p + 26, 4, 4, r)
#define RDD_PARSER_RESULTS_VID_FILTER_MATCH_WRITE(v, p)                 FIELD_MWRITE_8((uint8_t *)p + 26, 4, 4, v)
#define RDD_PARSER_RESULTS_DOS_ATTACK_REASON_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 26, 0, 4, r)
#define RDD_PARSER_RESULTS_DOS_ATTACK_REASON_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 26, 0, 4, v)
#define RDD_PARSER_RESULTS_DOS_ATTACK_REASON_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 26, 0, 4, r)
#define RDD_PARSER_RESULTS_DOS_ATTACK_REASON_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 26, 0, 4, v)
#define RDD_PARSER_RESULTS_LAYER2_ADDRESS_READ_G(r, g, idx)             GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 27, r)
#define RDD_PARSER_RESULTS_LAYER2_ADDRESS_WRITE_G(v, g, idx)            GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_RESULTS_DTS) + 27, v)
#define RDD_PARSER_RESULTS_LAYER2_ADDRESS_READ(r, p)                    MREAD_8((uint8_t *)p + 27, r)
#define RDD_PARSER_RESULTS_LAYER2_ADDRESS_WRITE(v, p)                   MWRITE_8((uint8_t *)p + 27, v)
/* <<<RDD_PARSER_RESULTS_DTS */

/* <<<RDD_PARSER_RESULTS */


/* >>>RDD_PARSER_L2_LKP_ENTRY */
#define PARSER_L2_LKP_ENTRY_DA_CRC_F_OFFSET                           0
#define PARSER_L2_LKP_ENTRY_DA_CRC_F_WIDTH                            32
#define PARSER_L2_LKP_ENTRY_PARSER_L2_LKP_ENTRY_OFFSET                0
#define PARSER_L2_LKP_ENTRY_DA_CRC_OFFSET                             0
#define PARSER_L2_LKP_ENTRY_DA_CRC_WORD_OFFSET                        0
#define PARSER_L2_LKP_ENTRY_SA_CRC_F_OFFSET                           0
#define PARSER_L2_LKP_ENTRY_SA_CRC_F_WIDTH                            32
#define PARSER_L2_LKP_ENTRY_SA_CRC_OFFSET                             4
#define PARSER_L2_LKP_ENTRY_SA_CRC_WORD_OFFSET                        1
#define PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_F_OFFSET                0
#define PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_F_WIDTH                 32
#define PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_OFFSET                  8
#define PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_WORD_OFFSET             2
#define PARSER_L2_LKP_ENTRY_TOS_F_OFFSET                              24
#define PARSER_L2_LKP_ENTRY_TOS_F_WIDTH                               8
#define PARSER_L2_LKP_ENTRY_TOS_OFFSET                                12
#define PARSER_L2_LKP_ENTRY_TOS_WORD_OFFSET                           3
#define PARSER_L2_LKP_ENTRY_TOS_F_OFFSET_MOD16                        8
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_F_OFFSET                      19
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_F_WIDTH                       5
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_OFFSET                        13
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_WORD_OFFSET                   3
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD8                 3
#define PARSER_L2_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD16                3
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_F_OFFSET                        16
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_F_WIDTH                         3
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_OFFSET                          13
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_WORD_OFFSET                     3
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD8                   0
#define PARSER_L2_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD16                  0
#define PARSER_L2_LKP_ENTRY_VALID_F_OFFSET                            15
#define PARSER_L2_LKP_ENTRY_VALID_F_WIDTH                             1
#define PARSER_L2_LKP_ENTRY_VALID_OFFSET                              14
#define PARSER_L2_LKP_ENTRY_VALID_WORD_OFFSET                         3
#define PARSER_L2_LKP_ENTRY_VALID_F_OFFSET_MOD8                       7
#define PARSER_L2_LKP_ENTRY_VALID_F_OFFSET_MOD16                      15
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET                     14
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_F_WIDTH                      1
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_OFFSET                       14
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_WORD_OFFSET                  3
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET_MOD8                6
#define PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET_MOD16               14
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET                      0
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_F_WIDTH                       4
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_OFFSET                        15
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_WORD_OFFSET                   3
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET_MOD8                 0
#define PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET_MOD16                0

/* >>>RDD_PARSER_L2_LKP_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	da_crc           	;
	uint32_t	sa_crc           	;
	uint32_t	vlan_eth_type_crc	;
	uint8_t	tos              	;
	uint32_t	lookup_port      	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vlans_num        	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	valid            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_pure_ack     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved1        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	var_len_ctx      	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	da_crc           	;
	uint32_t	sa_crc           	;
	uint32_t	vlan_eth_type_crc	;
	uint32_t	var_len_ctx      	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved1        	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_pure_ack     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	valid            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vlans_num        	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	lookup_port      	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	tos              	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSER_L2_LKP_ENTRY_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_PARSER_L2_LKP_ENTRY_DTS fields;
} PARSER_L2_LKP_ENTRY_STRUCT;
#define RDD_PARSER_L2_LKP_ENTRY_DA_CRC_READ_G(r, g, idx)                     GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS), r)
#define RDD_PARSER_L2_LKP_ENTRY_DA_CRC_WRITE_G(v, g, idx)                    GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS), v)
#define RDD_PARSER_L2_LKP_ENTRY_DA_CRC_READ(r, p)                            MREAD_32((uint8_t *)p, r)
#define RDD_PARSER_L2_LKP_ENTRY_DA_CRC_WRITE(v, p)                           MWRITE_32((uint8_t *)p, v)
#define RDD_PARSER_L2_LKP_ENTRY_SA_CRC_READ_G(r, g, idx)                     GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 4, r)
#define RDD_PARSER_L2_LKP_ENTRY_SA_CRC_WRITE_G(v, g, idx)                    GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 4, v)
#define RDD_PARSER_L2_LKP_ENTRY_SA_CRC_READ(r, p)                            MREAD_32((uint8_t *)p + 4, r)
#define RDD_PARSER_L2_LKP_ENTRY_SA_CRC_WRITE(v, p)                           MWRITE_32((uint8_t *)p + 4, v)
#define RDD_PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 8, r)
#define RDD_PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 8, v)
#define RDD_PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_READ(r, p)                 MREAD_32((uint8_t *)p + 8, r)
#define RDD_PARSER_L2_LKP_ENTRY_VLAN_ETH_TYPE_CRC_WRITE(v, p)                MWRITE_32((uint8_t *)p + 8, v)
#define RDD_PARSER_L2_LKP_ENTRY_TOS_READ_G(r, g, idx)                        GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 12, r)
#define RDD_PARSER_L2_LKP_ENTRY_TOS_WRITE_G(v, g, idx)                       GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 12, v)
#define RDD_PARSER_L2_LKP_ENTRY_TOS_READ(r, p)                               MREAD_8((uint8_t *)p + 12, r)
#define RDD_PARSER_L2_LKP_ENTRY_TOS_WRITE(v, p)                              MWRITE_8((uint8_t *)p + 12, v)
#define RDD_PARSER_L2_LKP_ENTRY_LOOKUP_PORT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 13, 3, 5, r)
#define RDD_PARSER_L2_LKP_ENTRY_LOOKUP_PORT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 13, 3, 5, v)
#define RDD_PARSER_L2_LKP_ENTRY_LOOKUP_PORT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 13, 3, 5, r)
#define RDD_PARSER_L2_LKP_ENTRY_LOOKUP_PORT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 13, 3, 5, v)
#define RDD_PARSER_L2_LKP_ENTRY_VLANS_NUM_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 13, 0, 3, r)
#define RDD_PARSER_L2_LKP_ENTRY_VLANS_NUM_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 13, 0, 3, v)
#define RDD_PARSER_L2_LKP_ENTRY_VLANS_NUM_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 13, 0, 3, r)
#define RDD_PARSER_L2_LKP_ENTRY_VLANS_NUM_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 13, 0, 3, v)
#define RDD_PARSER_L2_LKP_ENTRY_VALID_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 14, 7, 1, r)
#define RDD_PARSER_L2_LKP_ENTRY_VALID_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 14, 7, 1, v)
#define RDD_PARSER_L2_LKP_ENTRY_VALID_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 14, 7, 1, r)
#define RDD_PARSER_L2_LKP_ENTRY_VALID_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 14, 7, 1, v)
#define RDD_PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 14, 6, 1, r)
#define RDD_PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 14, 6, 1, v)
#define RDD_PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 14, 6, 1, r)
#define RDD_PARSER_L2_LKP_ENTRY_TCP_PURE_ACK_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 14, 6, 1, v)
#define RDD_PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 15, 0, 4, r)
#define RDD_PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L2_LKP_ENTRY_DTS) + 15, 0, 4, v)
#define RDD_PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 15, 0, 4, r)
#define RDD_PARSER_L2_LKP_ENTRY_VAR_LEN_CTX_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 15, 0, 4, v)
/* <<<RDD_PARSER_L2_LKP_ENTRY_DTS */

/* <<<RDD_PARSER_L2_LKP_ENTRY */


/* >>>RDD_PARSER_L3_LKP_ENTRY */
#define PARSER_L3_LKP_ENTRY_SOURCE_IP_F_OFFSET                        0
#define PARSER_L3_LKP_ENTRY_SOURCE_IP_F_WIDTH                         32
#define PARSER_L3_LKP_ENTRY_PARSER_L3_LKP_ENTRY_OFFSET                0
#define PARSER_L3_LKP_ENTRY_SOURCE_IP_OFFSET                          0
#define PARSER_L3_LKP_ENTRY_SOURCE_IP_WORD_OFFSET                     0
#define PARSER_L3_LKP_ENTRY_DESTINATION_IP_F_OFFSET                   0
#define PARSER_L3_LKP_ENTRY_DESTINATION_IP_F_WIDTH                    32
#define PARSER_L3_LKP_ENTRY_DESTINATION_IP_OFFSET                     4
#define PARSER_L3_LKP_ENTRY_DESTINATION_IP_WORD_OFFSET                1
#define PARSER_L3_LKP_ENTRY_SOURCE_PORT_F_OFFSET                      16
#define PARSER_L3_LKP_ENTRY_SOURCE_PORT_F_WIDTH                       16
#define PARSER_L3_LKP_ENTRY_SOURCE_PORT_OFFSET                        8
#define PARSER_L3_LKP_ENTRY_SOURCE_PORT_WORD_OFFSET                   2
#define PARSER_L3_LKP_ENTRY_DESTINATION_PORT_F_OFFSET                 0
#define PARSER_L3_LKP_ENTRY_DESTINATION_PORT_F_WIDTH                  16
#define PARSER_L3_LKP_ENTRY_DESTINATION_PORT_OFFSET                   10
#define PARSER_L3_LKP_ENTRY_DESTINATION_PORT_WORD_OFFSET              2
#define PARSER_L3_LKP_ENTRY_TOS_F_OFFSET                              24
#define PARSER_L3_LKP_ENTRY_TOS_F_WIDTH                               8
#define PARSER_L3_LKP_ENTRY_TOS_OFFSET                                12
#define PARSER_L3_LKP_ENTRY_TOS_WORD_OFFSET                           3
#define PARSER_L3_LKP_ENTRY_TOS_F_OFFSET_MOD16                        8
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_F_OFFSET                      19
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_F_WIDTH                       5
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_OFFSET                        13
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_WORD_OFFSET                   3
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD8                 3
#define PARSER_L3_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD16                3
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_F_OFFSET                        16
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_F_WIDTH                         3
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_OFFSET                          13
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_WORD_OFFSET                     3
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD8                   0
#define PARSER_L3_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD16                  0
#define PARSER_L3_LKP_ENTRY_VALID_F_OFFSET                            15
#define PARSER_L3_LKP_ENTRY_VALID_F_WIDTH                             1
#define PARSER_L3_LKP_ENTRY_VALID_OFFSET                              14
#define PARSER_L3_LKP_ENTRY_VALID_WORD_OFFSET                         3
#define PARSER_L3_LKP_ENTRY_VALID_F_OFFSET_MOD8                       7
#define PARSER_L3_LKP_ENTRY_VALID_F_OFFSET_MOD16                      15
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET                     14
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_F_WIDTH                      1
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_OFFSET                       14
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_WORD_OFFSET                  3
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET_MOD8                6
#define PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_F_OFFSET_MOD16               14
#define PARSER_L3_LKP_ENTRY_IPV6_F_OFFSET                             13
#define PARSER_L3_LKP_ENTRY_IPV6_F_WIDTH                              1
#define PARSER_L3_LKP_ENTRY_IPV6_OFFSET                               14
#define PARSER_L3_LKP_ENTRY_IPV6_WORD_OFFSET                          3
#define PARSER_L3_LKP_ENTRY_IPV6_F_OFFSET_MOD8                        5
#define PARSER_L3_LKP_ENTRY_IPV6_F_OFFSET_MOD16                       13
#define PARSER_L3_LKP_ENTRY_CTX_EXT_F_OFFSET                          12
#define PARSER_L3_LKP_ENTRY_CTX_EXT_F_WIDTH                           1
#define PARSER_L3_LKP_ENTRY_CTX_EXT_OFFSET                            14
#define PARSER_L3_LKP_ENTRY_CTX_EXT_WORD_OFFSET                       3
#define PARSER_L3_LKP_ENTRY_CTX_EXT_F_OFFSET_MOD8                     4
#define PARSER_L3_LKP_ENTRY_CTX_EXT_F_OFFSET_MOD16                    12
#define PARSER_L3_LKP_ENTRY_PROTOCOL_F_OFFSET                         4
#define PARSER_L3_LKP_ENTRY_PROTOCOL_F_WIDTH                          8
#define PARSER_L3_LKP_ENTRY_PROTOCOL_OFFSET                           14
#define PARSER_L3_LKP_ENTRY_PROTOCOL_WORD_OFFSET                      3
#define PARSER_L3_LKP_ENTRY_PROTOCOL_F_OFFSET_MOD16                   4
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET                      0
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_F_WIDTH                       4
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_OFFSET                        15
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_WORD_OFFSET                   3
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET_MOD8                 0
#define PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_F_OFFSET_MOD16                0

/* >>>RDD_PARSER_L3_LKP_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	source_ip       	;
	uint32_t	destination_ip  	;
	uint16_t	source_port     	;
	uint16_t	destination_port	;
	uint8_t	tos             	;
	uint32_t	lookup_port     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vlans_num       	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	valid           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_pure_ack    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ctx_ext         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	protocol        	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /*defined by rdd_parser_l3_protocol enumeration*/
	uint32_t	var_len_ctx     	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	source_ip       	;
	uint32_t	destination_ip  	;
	uint16_t	destination_port	;
	uint16_t	source_port     	;
	uint32_t	var_len_ctx     	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	protocol        	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /*defined by rdd_parser_l3_protocol enumeration*/
	uint32_t	ctx_ext         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tcp_pure_ack    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	valid           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vlans_num       	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	lookup_port     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	tos             	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSER_L3_LKP_ENTRY_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_PARSER_L3_LKP_ENTRY_DTS fields;
} PARSER_L3_LKP_ENTRY_STRUCT;
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_IP_READ_G(r, g, idx)                 GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS), r)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_IP_WRITE_G(v, g, idx)                GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS), v)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_IP_READ(r, p)                        MREAD_32((uint8_t *)p, r)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_IP_WRITE(v, p)                       MWRITE_32((uint8_t *)p, v)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_IP_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 4, r)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_IP_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 4, v)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_IP_READ(r, p)                   MREAD_32((uint8_t *)p + 4, r)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_IP_WRITE(v, p)                  MWRITE_32((uint8_t *)p + 4, v)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_PORT_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 8, r)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_PORT_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 8, v)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_PORT_READ(r, p)                      MREAD_16((uint8_t *)p + 8, r)
#define RDD_PARSER_L3_LKP_ENTRY_SOURCE_PORT_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 8, v)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_PORT_READ_G(r, g, idx)          GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 10, r)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_PORT_WRITE_G(v, g, idx)         GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 10, v)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_PORT_READ(r, p)                 MREAD_16((uint8_t *)p + 10, r)
#define RDD_PARSER_L3_LKP_ENTRY_DESTINATION_PORT_WRITE(v, p)                MWRITE_16((uint8_t *)p + 10, v)
#define RDD_PARSER_L3_LKP_ENTRY_TOS_READ_G(r, g, idx)                       GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 12, r)
#define RDD_PARSER_L3_LKP_ENTRY_TOS_WRITE_G(v, g, idx)                      GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 12, v)
#define RDD_PARSER_L3_LKP_ENTRY_TOS_READ(r, p)                              MREAD_8((uint8_t *)p + 12, r)
#define RDD_PARSER_L3_LKP_ENTRY_TOS_WRITE(v, p)                             MWRITE_8((uint8_t *)p + 12, v)
#define RDD_PARSER_L3_LKP_ENTRY_LOOKUP_PORT_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 13, 3, 5, r)
#define RDD_PARSER_L3_LKP_ENTRY_LOOKUP_PORT_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 13, 3, 5, v)
#define RDD_PARSER_L3_LKP_ENTRY_LOOKUP_PORT_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 13, 3, 5, r)
#define RDD_PARSER_L3_LKP_ENTRY_LOOKUP_PORT_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 13, 3, 5, v)
#define RDD_PARSER_L3_LKP_ENTRY_VLANS_NUM_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 13, 0, 3, r)
#define RDD_PARSER_L3_LKP_ENTRY_VLANS_NUM_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 13, 0, 3, v)
#define RDD_PARSER_L3_LKP_ENTRY_VLANS_NUM_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 13, 0, 3, r)
#define RDD_PARSER_L3_LKP_ENTRY_VLANS_NUM_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 13, 0, 3, v)
#define RDD_PARSER_L3_LKP_ENTRY_VALID_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 7, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_VALID_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 7, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_VALID_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 14, 7, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_VALID_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 14, 7, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 6, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 6, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 14, 6, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_TCP_PURE_ACK_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 14, 6, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_IPV6_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 5, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_IPV6_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 5, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_IPV6_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 14, 5, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_IPV6_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 14, 5, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_CTX_EXT_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 4, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_CTX_EXT_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 4, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_CTX_EXT_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p + 14, 4, 1, r)
#define RDD_PARSER_L3_LKP_ENTRY_CTX_EXT_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p + 14, 4, 1, v)
#define RDD_PARSER_L3_LKP_ENTRY_PROTOCOL_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 4, 8, r) /*defined by rdd_parser_l3_protocol enumeration*/
#define RDD_PARSER_L3_LKP_ENTRY_PROTOCOL_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 14, 4, 8, v) /*defined by rdd_parser_l3_protocol enumeration*/
#define RDD_PARSER_L3_LKP_ENTRY_PROTOCOL_READ(r, p)                         FIELD_MREAD_16((uint8_t *)p + 14, 4, 8, r) /*defined by rdd_parser_l3_protocol enumeration*/
#define RDD_PARSER_L3_LKP_ENTRY_PROTOCOL_WRITE(v, p)                        FIELD_MWRITE_16((uint8_t *)p + 14, 4, 8, v) /*defined by rdd_parser_l3_protocol enumeration*/
#define RDD_PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 15, 0, 4, r)
#define RDD_PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_L3_LKP_ENTRY_DTS) + 15, 0, 4, v)
#define RDD_PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 15, 0, 4, r)
#define RDD_PARSER_L3_LKP_ENTRY_VAR_LEN_CTX_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 15, 0, 4, v)
/* <<<RDD_PARSER_L3_LKP_ENTRY_DTS */

/* <<<RDD_PARSER_L3_LKP_ENTRY */


/* >>>RDD_PARSER_IC_LKP_ENTRY */
#define PARSER_IC_LKP_ENTRY_DA_CRC_F_OFFSET                           0
#define PARSER_IC_LKP_ENTRY_DA_CRC_F_WIDTH                            32
#define PARSER_IC_LKP_ENTRY_PARSER_IC_LKP_ENTRY_OFFSET                0
#define PARSER_IC_LKP_ENTRY_DA_CRC_OFFSET                             0
#define PARSER_IC_LKP_ENTRY_DA_CRC_WORD_OFFSET                        0
#define PARSER_IC_LKP_ENTRY_SA_CRC_F_OFFSET                           0
#define PARSER_IC_LKP_ENTRY_SA_CRC_F_WIDTH                            32
#define PARSER_IC_LKP_ENTRY_SA_CRC_OFFSET                             4
#define PARSER_IC_LKP_ENTRY_SA_CRC_WORD_OFFSET                        1
#define PARSER_IC_LKP_ENTRY_SOURCE_IP_F_OFFSET                        0
#define PARSER_IC_LKP_ENTRY_SOURCE_IP_F_WIDTH                         32
#define PARSER_IC_LKP_ENTRY_SOURCE_IP_OFFSET                          8
#define PARSER_IC_LKP_ENTRY_SOURCE_IP_WORD_OFFSET                     2
#define PARSER_IC_LKP_ENTRY_DESTINATION_IP_F_OFFSET                   0
#define PARSER_IC_LKP_ENTRY_DESTINATION_IP_F_WIDTH                    32
#define PARSER_IC_LKP_ENTRY_DESTINATION_IP_OFFSET                     12
#define PARSER_IC_LKP_ENTRY_DESTINATION_IP_WORD_OFFSET                3
#define PARSER_IC_LKP_ENTRY_SOURCE_PORT_F_OFFSET                      16
#define PARSER_IC_LKP_ENTRY_SOURCE_PORT_F_WIDTH                       16
#define PARSER_IC_LKP_ENTRY_SOURCE_PORT_OFFSET                        16
#define PARSER_IC_LKP_ENTRY_SOURCE_PORT_WORD_OFFSET                   4
#define PARSER_IC_LKP_ENTRY_DESTINATION_PORT_F_OFFSET                 0
#define PARSER_IC_LKP_ENTRY_DESTINATION_PORT_F_WIDTH                  16
#define PARSER_IC_LKP_ENTRY_DESTINATION_PORT_OFFSET                   18
#define PARSER_IC_LKP_ENTRY_DESTINATION_PORT_WORD_OFFSET              4
#define PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_F_OFFSET                    16
#define PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_F_WIDTH                     16
#define PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_OFFSET                      20
#define PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_WORD_OFFSET                 5
#define PARSER_IC_LKP_ENTRY_PROTOCOL_F_OFFSET                         8
#define PARSER_IC_LKP_ENTRY_PROTOCOL_F_WIDTH                          8
#define PARSER_IC_LKP_ENTRY_PROTOCOL_OFFSET                           22
#define PARSER_IC_LKP_ENTRY_PROTOCOL_WORD_OFFSET                      5
#define PARSER_IC_LKP_ENTRY_PROTOCOL_F_OFFSET_MOD16                   8
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_F_OFFSET                      5
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_F_WIDTH                       3
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_OFFSET                        23
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_WORD_OFFSET                   5
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_F_OFFSET_MOD8                 5
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_0_F_OFFSET_MOD16                5
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_F_OFFSET                      2
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_F_WIDTH                       3
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_OFFSET                        23
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_WORD_OFFSET                   5
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_F_OFFSET_MOD8                 2
#define PARSER_IC_LKP_ENTRY_TPID_VLAN_1_F_OFFSET_MOD16                2
#define PARSER_IC_LKP_ENTRY_IPV6_F_OFFSET                             1
#define PARSER_IC_LKP_ENTRY_IPV6_F_WIDTH                              1
#define PARSER_IC_LKP_ENTRY_IPV6_OFFSET                               23
#define PARSER_IC_LKP_ENTRY_IPV6_WORD_OFFSET                          5
#define PARSER_IC_LKP_ENTRY_IPV6_F_OFFSET_MOD8                        1
#define PARSER_IC_LKP_ENTRY_IPV6_F_OFFSET_MOD16                       1
#define PARSER_IC_LKP_ENTRY_IPV4_F_OFFSET                             0
#define PARSER_IC_LKP_ENTRY_IPV4_F_WIDTH                              1
#define PARSER_IC_LKP_ENTRY_IPV4_OFFSET                               23
#define PARSER_IC_LKP_ENTRY_IPV4_WORD_OFFSET                          5
#define PARSER_IC_LKP_ENTRY_IPV4_F_OFFSET_MOD8                        0
#define PARSER_IC_LKP_ENTRY_IPV4_F_OFFSET_MOD16                       0
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_F_OFFSET                       29
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_F_WIDTH                        3
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_OFFSET                         24
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_WORD_OFFSET                    6
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_F_OFFSET_MOD8                  5
#define PARSER_IC_LKP_ENTRY_OUTER_PBIT_F_OFFSET_MOD16                 13
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_F_OFFSET                        28
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_F_WIDTH                         1
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_OFFSET                          24
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_WORD_OFFSET                     6
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_F_OFFSET_MOD8                   4
#define PARSER_IC_LKP_ENTRY_OUTER_CFI_F_OFFSET_MOD16                  12
#define PARSER_IC_LKP_ENTRY_OUTER_VID_F_OFFSET                        16
#define PARSER_IC_LKP_ENTRY_OUTER_VID_F_WIDTH                         12
#define PARSER_IC_LKP_ENTRY_OUTER_VID_OFFSET                          24
#define PARSER_IC_LKP_ENTRY_OUTER_VID_WORD_OFFSET                     6
#define PARSER_IC_LKP_ENTRY_OUTER_VID_F_OFFSET_MOD16                  0
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_F_OFFSET                       13
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_F_WIDTH                        3
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_OFFSET                         26
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_WORD_OFFSET                    6
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_F_OFFSET_MOD8                  5
#define PARSER_IC_LKP_ENTRY_INNER_PBIT_F_OFFSET_MOD16                 13
#define PARSER_IC_LKP_ENTRY_INNER_CFI_F_OFFSET                        12
#define PARSER_IC_LKP_ENTRY_INNER_CFI_F_WIDTH                         1
#define PARSER_IC_LKP_ENTRY_INNER_CFI_OFFSET                          26
#define PARSER_IC_LKP_ENTRY_INNER_CFI_WORD_OFFSET                     6
#define PARSER_IC_LKP_ENTRY_INNER_CFI_F_OFFSET_MOD8                   4
#define PARSER_IC_LKP_ENTRY_INNER_CFI_F_OFFSET_MOD16                  12
#define PARSER_IC_LKP_ENTRY_INNER_VID_F_OFFSET                        0
#define PARSER_IC_LKP_ENTRY_INNER_VID_F_WIDTH                         12
#define PARSER_IC_LKP_ENTRY_INNER_VID_OFFSET                          26
#define PARSER_IC_LKP_ENTRY_INNER_VID_WORD_OFFSET                     6
#define PARSER_IC_LKP_ENTRY_INNER_VID_F_OFFSET_MOD16                  0
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_F_OFFSET                      19
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_F_WIDTH                       5
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_OFFSET                        29
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_WORD_OFFSET                   7
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD8                 3
#define PARSER_IC_LKP_ENTRY_LOOKUP_PORT_F_OFFSET_MOD16                3
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_F_OFFSET                        16
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_F_WIDTH                         3
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_OFFSET                          29
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_WORD_OFFSET                     7
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD8                   0
#define PARSER_IC_LKP_ENTRY_VLANS_NUM_F_OFFSET_MOD16                  0
#define PARSER_IC_LKP_ENTRY_TOS_F_OFFSET                              8
#define PARSER_IC_LKP_ENTRY_TOS_F_WIDTH                               8
#define PARSER_IC_LKP_ENTRY_TOS_OFFSET                                30
#define PARSER_IC_LKP_ENTRY_TOS_WORD_OFFSET                           7
#define PARSER_IC_LKP_ENTRY_TOS_F_OFFSET_MOD16                        8

/* >>>RDD_PARSER_IC_LKP_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	da_crc          	;
	uint32_t	sa_crc          	;
	uint32_t	source_ip       	;
	uint32_t	destination_ip  	;
	uint16_t	source_port     	;
	uint16_t	destination_port	;
	uint16_t	ethernet_type   	;
	uint8_t	protocol        	;
	uint32_t	tpid_vlan_0     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_1     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv4            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_pbit      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_cfi       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_vid       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	inner_pbit      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	inner_cfi       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	inner_vid       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	reserved2       	;
	uint32_t	lookup_port     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	vlans_num       	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	tos             	;
	uint8_t	reserved3       	;
#else
	uint32_t	da_crc          	;
	uint32_t	sa_crc          	;
	uint32_t	source_ip       	;
	uint32_t	destination_ip  	;
	uint16_t	destination_port	;
	uint16_t	source_port     	;
	uint32_t	ipv4            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ipv6            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_1     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	tpid_vlan_0     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	protocol        	;
	uint16_t	ethernet_type   	;
	uint32_t	inner_vid       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	inner_cfi       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	inner_pbit      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_vid       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_cfi       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	outer_pbit      	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	reserved3       	;
	uint8_t	tos             	;
	uint32_t	vlans_num       	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	lookup_port     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	reserved2       	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PARSER_IC_LKP_ENTRY_DTS;

typedef union
{
    uint32_t word_val[8];
    uint64_t dword_val64[4];
    RDD_PARSER_IC_LKP_ENTRY_DTS fields;
} PARSER_IC_LKP_ENTRY_STRUCT;
#define RDD_PARSER_IC_LKP_ENTRY_DA_CRC_READ_G(r, g, idx)                    GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS), r)
#define RDD_PARSER_IC_LKP_ENTRY_DA_CRC_WRITE_G(v, g, idx)                   GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS), v)
#define RDD_PARSER_IC_LKP_ENTRY_DA_CRC_READ(r, p)                           MREAD_32((uint8_t *)p, r)
#define RDD_PARSER_IC_LKP_ENTRY_DA_CRC_WRITE(v, p)                          MWRITE_32((uint8_t *)p, v)
#define RDD_PARSER_IC_LKP_ENTRY_SA_CRC_READ_G(r, g, idx)                    GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 4, r)
#define RDD_PARSER_IC_LKP_ENTRY_SA_CRC_WRITE_G(v, g, idx)                   GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 4, v)
#define RDD_PARSER_IC_LKP_ENTRY_SA_CRC_READ(r, p)                           MREAD_32((uint8_t *)p + 4, r)
#define RDD_PARSER_IC_LKP_ENTRY_SA_CRC_WRITE(v, p)                          MWRITE_32((uint8_t *)p + 4, v)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_IP_READ_G(r, g, idx)                 GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 8, r)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_IP_WRITE_G(v, g, idx)                GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 8, v)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_IP_READ(r, p)                        MREAD_32((uint8_t *)p + 8, r)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_IP_WRITE(v, p)                       MWRITE_32((uint8_t *)p + 8, v)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_IP_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_IP_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_IP_READ(r, p)                   MREAD_32((uint8_t *)p + 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_IP_WRITE(v, p)                  MWRITE_32((uint8_t *)p + 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_PORT_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 16, r)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_PORT_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 16, v)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_PORT_READ(r, p)                      MREAD_16((uint8_t *)p + 16, r)
#define RDD_PARSER_IC_LKP_ENTRY_SOURCE_PORT_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 16, v)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_PORT_READ_G(r, g, idx)          GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 18, r)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_PORT_WRITE_G(v, g, idx)         GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 18, v)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_PORT_READ(r, p)                 MREAD_16((uint8_t *)p + 18, r)
#define RDD_PARSER_IC_LKP_ENTRY_DESTINATION_PORT_WRITE(v, p)                MWRITE_16((uint8_t *)p + 18, v)
#define RDD_PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_READ_G(r, g, idx)             GROUP_MREAD_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 20, r)
#define RDD_PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_WRITE_G(v, g, idx)            GROUP_MWRITE_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 20, v)
#define RDD_PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_READ(r, p)                    MREAD_16((uint8_t *)p + 20, r)
#define RDD_PARSER_IC_LKP_ENTRY_ETHERNET_TYPE_WRITE(v, p)                   MWRITE_16((uint8_t *)p + 20, v)
#define RDD_PARSER_IC_LKP_ENTRY_PROTOCOL_READ_G(r, g, idx)                  GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 22, r)
#define RDD_PARSER_IC_LKP_ENTRY_PROTOCOL_WRITE_G(v, g, idx)                 GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 22, v)
#define RDD_PARSER_IC_LKP_ENTRY_PROTOCOL_READ(r, p)                         MREAD_8((uint8_t *)p + 22, r)
#define RDD_PARSER_IC_LKP_ENTRY_PROTOCOL_WRITE(v, p)                        MWRITE_8((uint8_t *)p + 22, v)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_0_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_0_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_0_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 23, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_0_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 23, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_1_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 2, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_1_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 2, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_1_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 23, 2, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_TPID_VLAN_1_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 23, 2, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_IPV6_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 1, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_IPV6_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 1, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_IPV6_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 23, 1, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_IPV6_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 23, 1, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_IPV4_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 0, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_IPV4_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 23, 0, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_IPV4_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 23, 0, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_IPV4_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 23, 0, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_PBIT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_PBIT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_PBIT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 24, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_PBIT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 24, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_CFI_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 4, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_CFI_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 4, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_CFI_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 24, 4, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_CFI_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 24, 4, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_VID_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 0, 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_VID_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 24, 0, 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_VID_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 24, 0, 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_OUTER_VID_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 24, 0, 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_PBIT_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_PBIT_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_PBIT_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 26, 5, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_PBIT_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 26, 5, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_CFI_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 4, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_CFI_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 4, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_CFI_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 26, 4, 1, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_CFI_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 26, 4, 1, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_VID_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 0, 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_VID_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 26, 0, 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_VID_READ(r, p)                        FIELD_MREAD_16((uint8_t *)p + 26, 0, 12, r)
#define RDD_PARSER_IC_LKP_ENTRY_INNER_VID_WRITE(v, p)                       FIELD_MWRITE_16((uint8_t *)p + 26, 0, 12, v)
#define RDD_PARSER_IC_LKP_ENTRY_LOOKUP_PORT_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 29, 3, 5, r)
#define RDD_PARSER_IC_LKP_ENTRY_LOOKUP_PORT_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 29, 3, 5, v)
#define RDD_PARSER_IC_LKP_ENTRY_LOOKUP_PORT_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 29, 3, 5, r)
#define RDD_PARSER_IC_LKP_ENTRY_LOOKUP_PORT_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 29, 3, 5, v)
#define RDD_PARSER_IC_LKP_ENTRY_VLANS_NUM_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 29, 0, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_VLANS_NUM_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 29, 0, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_VLANS_NUM_READ(r, p)                        FIELD_MREAD_8((uint8_t *)p + 29, 0, 3, r)
#define RDD_PARSER_IC_LKP_ENTRY_VLANS_NUM_WRITE(v, p)                       FIELD_MWRITE_8((uint8_t *)p + 29, 0, 3, v)
#define RDD_PARSER_IC_LKP_ENTRY_TOS_READ_G(r, g, idx)                       GROUP_MREAD_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 30, r)
#define RDD_PARSER_IC_LKP_ENTRY_TOS_WRITE_G(v, g, idx)                      GROUP_MWRITE_8(g, idx*sizeof(RDD_PARSER_IC_LKP_ENTRY_DTS) + 30, v)
#define RDD_PARSER_IC_LKP_ENTRY_TOS_READ(r, p)                              MREAD_8((uint8_t *)p + 30, r)
#define RDD_PARSER_IC_LKP_ENTRY_TOS_WRITE(v, p)                             MWRITE_8((uint8_t *)p + 30, v)
/* <<<RDD_PARSER_IC_LKP_ENTRY_DTS */

/* <<<RDD_PARSER_IC_LKP_ENTRY */


/* >>>RDD_NATC_CONTROL_ENTRY */
#define NATC_CONTROL_ENTRY_DONE_F_OFFSET                             31
#define NATC_CONTROL_ENTRY_DONE_F_WIDTH                              1
#define NATC_CONTROL_ENTRY_NATC_CONTROL_ENTRY_OFFSET                 0
#define NATC_CONTROL_ENTRY_DONE_OFFSET                               0
#define NATC_CONTROL_ENTRY_DONE_WORD_OFFSET                          0
#define NATC_CONTROL_ENTRY_DONE_F_OFFSET_MOD8                        7
#define NATC_CONTROL_ENTRY_DONE_F_OFFSET_MOD16                       15
#define NATC_CONTROL_ENTRY_NATC_HIT_F_OFFSET                         30
#define NATC_CONTROL_ENTRY_NATC_HIT_F_WIDTH                          1
#define NATC_CONTROL_ENTRY_NATC_HIT_OFFSET                           0
#define NATC_CONTROL_ENTRY_NATC_HIT_WORD_OFFSET                      0
#define NATC_CONTROL_ENTRY_NATC_HIT_F_OFFSET_MOD8                    6
#define NATC_CONTROL_ENTRY_NATC_HIT_F_OFFSET_MOD16                   14
#define NATC_CONTROL_ENTRY_CACHE_HIT_F_OFFSET                        29
#define NATC_CONTROL_ENTRY_CACHE_HIT_F_WIDTH                         1
#define NATC_CONTROL_ENTRY_CACHE_HIT_OFFSET                          0
#define NATC_CONTROL_ENTRY_CACHE_HIT_WORD_OFFSET                     0
#define NATC_CONTROL_ENTRY_CACHE_HIT_F_OFFSET_MOD8                   5
#define NATC_CONTROL_ENTRY_CACHE_HIT_F_OFFSET_MOD16                  13
#define NATC_CONTROL_ENTRY_HW_RESERVED0_F_OFFSET                     24
#define NATC_CONTROL_ENTRY_HW_RESERVED0_F_WIDTH                      5
#define NATC_CONTROL_ENTRY_HW_RESERVED0_OFFSET                       0
#define NATC_CONTROL_ENTRY_HW_RESERVED0_WORD_OFFSET                  0
#define NATC_CONTROL_ENTRY_HW_RESERVED0_F_OFFSET_MOD8                0
#define NATC_CONTROL_ENTRY_HW_RESERVED0_F_OFFSET_MOD16               8
#define NATC_CONTROL_ENTRY_HAS_ITER_F_OFFSET                         20
#define NATC_CONTROL_ENTRY_HAS_ITER_F_WIDTH                          4
#define NATC_CONTROL_ENTRY_HAS_ITER_OFFSET                           1
#define NATC_CONTROL_ENTRY_HAS_ITER_WORD_OFFSET                      0
#define NATC_CONTROL_ENTRY_HAS_ITER_F_OFFSET_MOD8                    4
#define NATC_CONTROL_ENTRY_HAS_ITER_F_OFFSET_MOD16                   4
#define NATC_CONTROL_ENTRY_HW_RESERVED1_F_OFFSET                     18
#define NATC_CONTROL_ENTRY_HW_RESERVED1_F_WIDTH                      2
#define NATC_CONTROL_ENTRY_HW_RESERVED1_OFFSET                       1
#define NATC_CONTROL_ENTRY_HW_RESERVED1_WORD_OFFSET                  0
#define NATC_CONTROL_ENTRY_HW_RESERVED1_F_OFFSET_MOD8                2
#define NATC_CONTROL_ENTRY_HW_RESERVED1_F_OFFSET_MOD16               2
#define NATC_CONTROL_ENTRY_HASH_VAL_F_OFFSET                         0
#define NATC_CONTROL_ENTRY_HASH_VAL_F_WIDTH                          18
#define NATC_CONTROL_ENTRY_HASH_VAL_OFFSET                           0
#define NATC_CONTROL_ENTRY_HASH_VAL_WORD_OFFSET                      0
#define NATC_CONTROL_ENTRY_HW_RESERVED2_F_OFFSET                     0
#define NATC_CONTROL_ENTRY_HW_RESERVED2_F_WIDTH                      32
#define NATC_CONTROL_ENTRY_HW_RESERVED2_OFFSET                       4
#define NATC_CONTROL_ENTRY_HW_RESERVED2_WORD_OFFSET                  1

/* >>>RDD_NATC_CONTROL_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	done        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	natc_hit    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	cache_hit   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved0	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	has_iter    	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved1	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hash_val    	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved2	;
#else
	uint32_t	hash_val    	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved1	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	has_iter    	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved0	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	cache_hit   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	natc_hit    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	done        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	hw_reserved2	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_NATC_CONTROL_ENTRY_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_NATC_CONTROL_ENTRY_DTS fields;
} NATC_CONTROL_ENTRY_STRUCT;
#define RDD_NATC_CONTROL_ENTRY_DONE_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 7, 1, r)
#define RDD_NATC_CONTROL_ENTRY_DONE_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 7, 1, v)
#define RDD_NATC_CONTROL_ENTRY_DONE_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p, 7, 1, r)
#define RDD_NATC_CONTROL_ENTRY_DONE_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p, 7, 1, v)
#define RDD_NATC_CONTROL_ENTRY_NATC_HIT_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 6, 1, r)
#define RDD_NATC_CONTROL_ENTRY_NATC_HIT_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 6, 1, v)
#define RDD_NATC_CONTROL_ENTRY_NATC_HIT_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p, 6, 1, r)
#define RDD_NATC_CONTROL_ENTRY_NATC_HIT_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p, 6, 1, v)
#define RDD_NATC_CONTROL_ENTRY_CACHE_HIT_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 5, 1, r)
#define RDD_NATC_CONTROL_ENTRY_CACHE_HIT_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 5, 1, v)
#define RDD_NATC_CONTROL_ENTRY_CACHE_HIT_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p, 5, 1, r)
#define RDD_NATC_CONTROL_ENTRY_CACHE_HIT_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p, 5, 1, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED0_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 0, 5, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED0_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS), 0, 5, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED0_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p, 0, 5, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED0_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p, 0, 5, v)
#define RDD_NATC_CONTROL_ENTRY_HAS_ITER_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 1, 4, 4, r)
#define RDD_NATC_CONTROL_ENTRY_HAS_ITER_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 1, 4, 4, v)
#define RDD_NATC_CONTROL_ENTRY_HAS_ITER_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 1, 4, 4, r)
#define RDD_NATC_CONTROL_ENTRY_HAS_ITER_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 1, 4, 4, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED1_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 1, 2, 2, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED1_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 1, 2, 2, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED1_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 1, 2, 2, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED1_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 1, 2, 2, v)
#define RDD_NATC_CONTROL_ENTRY_HASH_VAL_READ_G(r, g, idx)              GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 0, 0, 18, r)
#define RDD_NATC_CONTROL_ENTRY_HASH_VAL_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 0, 0, 18, v)
#define RDD_NATC_CONTROL_ENTRY_HASH_VAL_READ(r, p)                     FIELD_MREAD_32((uint8_t *)p + 0, 0, 18, r)
#define RDD_NATC_CONTROL_ENTRY_HASH_VAL_WRITE(v, p)                    FIELD_MWRITE_32((uint8_t *)p + 0, 0, 18, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED2_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 4, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED2_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_NATC_CONTROL_ENTRY_DTS) + 4, v)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED2_READ(r, p)                 MREAD_32((uint8_t *)p + 4, r)
#define RDD_NATC_CONTROL_ENTRY_HW_RESERVED2_WRITE(v, p)                MWRITE_32((uint8_t *)p + 4, v)
/* <<<RDD_NATC_CONTROL_ENTRY_DTS */

/* <<<RDD_NATC_CONTROL_ENTRY */


/* >>>RDD_NATC_COUNTERS_ENTRY */
#define NATC_COUNTERS_ENTRY_HIT_COUNTER_F_OFFSET                      0
#define NATC_COUNTERS_ENTRY_HIT_COUNTER_F_WIDTH                       32
#define NATC_COUNTERS_ENTRY_NATC_COUNTERS_ENTRY_OFFSET                0
#define NATC_COUNTERS_ENTRY_HIT_COUNTER_OFFSET                        0
#define NATC_COUNTERS_ENTRY_HIT_COUNTER_WORD_OFFSET                   0
#define NATC_COUNTERS_ENTRY_BYTES_COUNTER_F_OFFSET                    0
#define NATC_COUNTERS_ENTRY_BYTES_COUNTER_F_WIDTH                     32
#define NATC_COUNTERS_ENTRY_BYTES_COUNTER_OFFSET                      4
#define NATC_COUNTERS_ENTRY_BYTES_COUNTER_WORD_OFFSET                 1

/* >>>RDD_NATC_COUNTERS_ENTRY_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	hit_counter  	;
	uint32_t	bytes_counter	;
#else
	uint32_t	hit_counter  	;
	uint32_t	bytes_counter	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_NATC_COUNTERS_ENTRY_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_NATC_COUNTERS_ENTRY_DTS fields;
} NATC_COUNTERS_ENTRY_STRUCT;
#define RDD_NATC_COUNTERS_ENTRY_HIT_COUNTER_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_NATC_COUNTERS_ENTRY_DTS), r)
#define RDD_NATC_COUNTERS_ENTRY_HIT_COUNTER_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_NATC_COUNTERS_ENTRY_DTS), v)
#define RDD_NATC_COUNTERS_ENTRY_HIT_COUNTER_READ(r, p)                   MREAD_32((uint8_t *)p, r)
#define RDD_NATC_COUNTERS_ENTRY_HIT_COUNTER_WRITE(v, p)                  MWRITE_32((uint8_t *)p, v)
#define RDD_NATC_COUNTERS_ENTRY_BYTES_COUNTER_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_NATC_COUNTERS_ENTRY_DTS) + 4, r)
#define RDD_NATC_COUNTERS_ENTRY_BYTES_COUNTER_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_NATC_COUNTERS_ENTRY_DTS) + 4, v)
#define RDD_NATC_COUNTERS_ENTRY_BYTES_COUNTER_READ(r, p)                 MREAD_32((uint8_t *)p + 4, r)
#define RDD_NATC_COUNTERS_ENTRY_BYTES_COUNTER_WRITE(v, p)                MWRITE_32((uint8_t *)p + 4, v)
/* <<<RDD_NATC_COUNTERS_ENTRY_DTS */

/* <<<RDD_NATC_COUNTERS_ENTRY */


/* >>>RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE */
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_F_OFFSET                        0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_F_WIDTH                         2
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_OFFSET                          3
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_WORD_OFFSET                     0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_F_OFFSET_MOD8                   0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_F_OFFSET_MOD16                  0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_F_OFFSET                        30
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_F_WIDTH                         2
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_OFFSET                          4
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_WORD_OFFSET                     1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_F_OFFSET_MOD8                   6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_F_OFFSET_MOD16                  14
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_F_OFFSET                     16
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_F_WIDTH                      14
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_OFFSET                       4
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_WORD_OFFSET                  1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_F_OFFSET_MOD16               0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_F_OFFSET                              15
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_F_WIDTH                               1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_OFFSET                                6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_WORD_OFFSET                           1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_F_OFFSET_MOD8                         7
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_F_OFFSET_MOD16                        15
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_F_OFFSET                      14
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_F_WIDTH                       1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_OFFSET                        6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_WORD_OFFSET                   1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_F_OFFSET_MOD8                 6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_F_OFFSET_MOD16                14
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_F_OFFSET                              13
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_F_WIDTH                               1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_OFFSET                                6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_WORD_OFFSET                           1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_F_OFFSET_MOD8                         5
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_F_OFFSET_MOD16                        13
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_F_OFFSET                      12
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_F_WIDTH                       1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_OFFSET                        6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_WORD_OFFSET                   1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_F_OFFSET_MOD8                 4
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_F_OFFSET_MOD16                12
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_F_OFFSET                     0
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_F_WIDTH                      9
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_OFFSET                       6
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_WORD_OFFSET                  1
#define BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_F_OFFSET_MOD16               0

/* >>>RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	reserved0   	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	fpm_pool0   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	fpm_pool1   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bytes_popped	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	agg         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	target_mem0 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	abs         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	target_mem1 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved1   	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	queue_number	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	fpm_pool0   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved0   	:30	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	queue_number	:9	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved1   	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	target_mem1 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	abs         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	target_mem0 	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	agg         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bytes_popped	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	fpm_pool1   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS fields;
} BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_STRUCT;
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 3, 0, 2, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 3, 0, 2, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p + 3, 0, 2, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL0_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p + 3, 0, 2, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_READ_G(r, g, idx)             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 4, 6, 2, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 4, 6, 2, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_READ(r, p)                    FIELD_MREAD_8((uint8_t *)p + 4, 6, 2, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_FPM_POOL1_WRITE(v, p)                   FIELD_MWRITE_8((uint8_t *)p + 4, 6, 2, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_READ_G(r, g, idx)          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 4, 0, 14, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 4, 0, 14, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_READ(r, p)                 FIELD_MREAD_16((uint8_t *)p + 4, 0, 14, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_BYTES_POPPED_WRITE(v, p)                FIELD_MWRITE_16((uint8_t *)p + 4, 0, 14, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 7, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 7, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p + 6, 7, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_AGG_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p + 6, 7, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_READ_G(r, g, idx)           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 6, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 6, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_READ(r, p)                  FIELD_MREAD_8((uint8_t *)p + 6, 6, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM0_WRITE(v, p)                 FIELD_MWRITE_8((uint8_t *)p + 6, 6, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 5, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 5, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p + 6, 5, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_ABS_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p + 6, 5, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_READ_G(r, g, idx)           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 4, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_WRITE_G(v, g, idx)          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 4, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_READ(r, p)                  FIELD_MREAD_8((uint8_t *)p + 6, 4, 1, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_TARGET_MEM1_WRITE(v, p)                 FIELD_MWRITE_8((uint8_t *)p + 6, 4, 1, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_READ_G(r, g, idx)          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 0, 9, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS) + 6, 0, 9, v)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_READ(r, p)                 FIELD_MREAD_16((uint8_t *)p + 6, 0, 9, r)
#define RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_QUEUE_NUMBER_WRITE(v, p)                FIELD_MWRITE_16((uint8_t *)p + 6, 0, 9, v)
/* <<<RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE_DTS */

/* <<<RDD_BBMSG_RNR_TO_QM_PD_FIFO_CREDIT_FREE */


/* >>>RDD_HASH_RESULT */
#define HASH_RESULT_MATCH_F_OFFSET                            30
#define HASH_RESULT_MATCH_F_WIDTH                             2
#define HASH_RESULT_HASH_RESULT_OFFSET                        0
#define HASH_RESULT_MATCH_OFFSET                              0
#define HASH_RESULT_MATCH_WORD_OFFSET                         0
#define HASH_RESULT_MATCH_F_OFFSET_MOD8                       6
#define HASH_RESULT_MATCH_F_OFFSET_MOD16                      14
#define HASH_RESULT_MATCH_INDEX_F_OFFSET                      19
#define HASH_RESULT_MATCH_INDEX_F_WIDTH                       11
#define HASH_RESULT_MATCH_INDEX_OFFSET                        0
#define HASH_RESULT_MATCH_INDEX_WORD_OFFSET                   0
#define HASH_RESULT_MATCH_INDEX_F_OFFSET_MOD16                3
#define HASH_RESULT_MATCH_ENGINE_F_OFFSET                     17
#define HASH_RESULT_MATCH_ENGINE_F_WIDTH                      2
#define HASH_RESULT_MATCH_ENGINE_OFFSET                       1
#define HASH_RESULT_MATCH_ENGINE_WORD_OFFSET                  0
#define HASH_RESULT_MATCH_ENGINE_F_OFFSET_MOD8                1
#define HASH_RESULT_MATCH_ENGINE_F_OFFSET_MOD16               1
#define HASH_RESULT_CONTEXT0_32_47_F_OFFSET                   0
#define HASH_RESULT_CONTEXT0_32_47_F_WIDTH                    16
#define HASH_RESULT_CONTEXT0_32_47_OFFSET                     2
#define HASH_RESULT_CONTEXT0_32_47_WORD_OFFSET                0
#define HASH_RESULT_CONTEXT0_0_31_F_OFFSET                    0
#define HASH_RESULT_CONTEXT0_0_31_F_WIDTH                     32
#define HASH_RESULT_CONTEXT0_0_31_OFFSET                      4
#define HASH_RESULT_CONTEXT0_0_31_WORD_OFFSET                 1
#define HASH_RESULT_CONTEXT1_16_47_F_OFFSET                   0
#define HASH_RESULT_CONTEXT1_16_47_F_WIDTH                    32
#define HASH_RESULT_CONTEXT1_16_47_OFFSET                     8
#define HASH_RESULT_CONTEXT1_16_47_WORD_OFFSET                2
#define HASH_RESULT_CONTEXT1_0_15_F_OFFSET                    16
#define HASH_RESULT_CONTEXT1_0_15_F_WIDTH                     16
#define HASH_RESULT_CONTEXT1_0_15_OFFSET                      12
#define HASH_RESULT_CONTEXT1_0_15_WORD_OFFSET                 3
#define HASH_RESULT_CONTEXT2_32_47_F_OFFSET                   0
#define HASH_RESULT_CONTEXT2_32_47_F_WIDTH                    16
#define HASH_RESULT_CONTEXT2_32_47_OFFSET                     14
#define HASH_RESULT_CONTEXT2_32_47_WORD_OFFSET                3
#define HASH_RESULT_CONTEXT2_0_31_F_OFFSET                    0
#define HASH_RESULT_CONTEXT2_0_31_F_WIDTH                     32
#define HASH_RESULT_CONTEXT2_0_31_OFFSET                      16
#define HASH_RESULT_CONTEXT2_0_31_WORD_OFFSET                 4

/* >>>RDD_HASH_RESULT_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	match         	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	match_index   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	match_engine  	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved_0    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	context0_32_47	;
	uint32_t	context0_0_31 	;
	uint32_t	context1_16_47	;
	uint16_t	context1_0_15 	;
	uint16_t	context2_32_47	;
	uint32_t	context2_0_31 	;
	uint32_t	reserved_1    	;
#else
	uint16_t	context0_32_47	;
	uint32_t	reserved_0    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	match_engine  	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	match_index   	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	match         	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	context0_0_31 	;
	uint32_t	context1_16_47	;
	uint16_t	context2_32_47	;
	uint16_t	context1_0_15 	;
	uint32_t	context2_0_31 	;
	uint32_t	reserved_1    	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_HASH_RESULT_DTS;

typedef union
{
    uint32_t word_val[6];
    uint64_t dword_val64[3];
    RDD_HASH_RESULT_DTS fields;
} HASH_RESULT_STRUCT;
#define RDD_HASH_RESULT_MATCH_READ_G(r, g, idx)                   GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_HASH_RESULT_DTS), 6, 2, r)
#define RDD_HASH_RESULT_MATCH_WRITE_G(v, g, idx)                  GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_HASH_RESULT_DTS), 6, 2, v)
#define RDD_HASH_RESULT_MATCH_READ(r, p)                          FIELD_MREAD_8((uint8_t *)p, 6, 2, r)
#define RDD_HASH_RESULT_MATCH_WRITE(v, p)                         FIELD_MWRITE_8((uint8_t *)p, 6, 2, v)
#define RDD_HASH_RESULT_MATCH_INDEX_READ_G(r, g, idx)             GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_HASH_RESULT_DTS), 3, 11, r)
#define RDD_HASH_RESULT_MATCH_INDEX_WRITE_G(v, g, idx)            GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_HASH_RESULT_DTS), 3, 11, v)
#define RDD_HASH_RESULT_MATCH_INDEX_READ(r, p)                    FIELD_MREAD_16((uint8_t *)p, 3, 11, r)
#define RDD_HASH_RESULT_MATCH_INDEX_WRITE(v, p)                   FIELD_MWRITE_16((uint8_t *)p, 3, 11, v)
#define RDD_HASH_RESULT_MATCH_ENGINE_READ_G(r, g, idx)            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 1, 1, 2, r)
#define RDD_HASH_RESULT_MATCH_ENGINE_WRITE_G(v, g, idx)           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 1, 1, 2, v)
#define RDD_HASH_RESULT_MATCH_ENGINE_READ(r, p)                   FIELD_MREAD_8((uint8_t *)p + 1, 1, 2, r)
#define RDD_HASH_RESULT_MATCH_ENGINE_WRITE(v, p)                  FIELD_MWRITE_8((uint8_t *)p + 1, 1, 2, v)
#define RDD_HASH_RESULT_CONTEXT0_32_47_READ_G(r, g, idx)          GROUP_MREAD_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 2, r)
#define RDD_HASH_RESULT_CONTEXT0_32_47_WRITE_G(v, g, idx)         GROUP_MWRITE_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 2, v)
#define RDD_HASH_RESULT_CONTEXT0_32_47_READ(r, p)                 MREAD_16((uint8_t *)p + 2, r)
#define RDD_HASH_RESULT_CONTEXT0_32_47_WRITE(v, p)                MWRITE_16((uint8_t *)p + 2, v)
#define RDD_HASH_RESULT_CONTEXT0_0_31_READ_G(r, g, idx)           GROUP_MREAD_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 4, r)
#define RDD_HASH_RESULT_CONTEXT0_0_31_WRITE_G(v, g, idx)          GROUP_MWRITE_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 4, v)
#define RDD_HASH_RESULT_CONTEXT0_0_31_READ(r, p)                  MREAD_32((uint8_t *)p + 4, r)
#define RDD_HASH_RESULT_CONTEXT0_0_31_WRITE(v, p)                 MWRITE_32((uint8_t *)p + 4, v)
#define RDD_HASH_RESULT_CONTEXT1_16_47_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 8, r)
#define RDD_HASH_RESULT_CONTEXT1_16_47_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 8, v)
#define RDD_HASH_RESULT_CONTEXT1_16_47_READ(r, p)                 MREAD_32((uint8_t *)p + 8, r)
#define RDD_HASH_RESULT_CONTEXT1_16_47_WRITE(v, p)                MWRITE_32((uint8_t *)p + 8, v)
#define RDD_HASH_RESULT_CONTEXT1_0_15_READ_G(r, g, idx)           GROUP_MREAD_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 12, r)
#define RDD_HASH_RESULT_CONTEXT1_0_15_WRITE_G(v, g, idx)          GROUP_MWRITE_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 12, v)
#define RDD_HASH_RESULT_CONTEXT1_0_15_READ(r, p)                  MREAD_16((uint8_t *)p + 12, r)
#define RDD_HASH_RESULT_CONTEXT1_0_15_WRITE(v, p)                 MWRITE_16((uint8_t *)p + 12, v)
#define RDD_HASH_RESULT_CONTEXT2_32_47_READ_G(r, g, idx)          GROUP_MREAD_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 14, r)
#define RDD_HASH_RESULT_CONTEXT2_32_47_WRITE_G(v, g, idx)         GROUP_MWRITE_16(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 14, v)
#define RDD_HASH_RESULT_CONTEXT2_32_47_READ(r, p)                 MREAD_16((uint8_t *)p + 14, r)
#define RDD_HASH_RESULT_CONTEXT2_32_47_WRITE(v, p)                MWRITE_16((uint8_t *)p + 14, v)
#define RDD_HASH_RESULT_CONTEXT2_0_31_READ_G(r, g, idx)           GROUP_MREAD_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 16, r)
#define RDD_HASH_RESULT_CONTEXT2_0_31_WRITE_G(v, g, idx)          GROUP_MWRITE_32(g, idx*sizeof(RDD_HASH_RESULT_DTS) + 16, v)
#define RDD_HASH_RESULT_CONTEXT2_0_31_READ(r, p)                  MREAD_32((uint8_t *)p + 16, r)
#define RDD_HASH_RESULT_CONTEXT2_0_31_WRITE(v, p)                 MWRITE_32((uint8_t *)p + 16, v)
/* <<<RDD_HASH_RESULT_DTS */

/* <<<RDD_HASH_RESULT */


/* >>>RDD_TRACE_EVENT */
#define TRACE_EVENT_TIMESTAMP_F_OFFSET                        20
#define TRACE_EVENT_TIMESTAMP_F_WIDTH                         12
#define TRACE_EVENT_TRACE_EVENT_OFFSET                        0
#define TRACE_EVENT_TIMESTAMP_OFFSET                          0
#define TRACE_EVENT_TIMESTAMP_WORD_OFFSET                     0
#define TRACE_EVENT_TIMESTAMP_F_OFFSET_MOD16                  4
#define TRACE_EVENT_EVENT_ID_F_OFFSET                         18
#define TRACE_EVENT_EVENT_ID_F_WIDTH                          2
#define TRACE_EVENT_EVENT_ID_OFFSET                           1
#define TRACE_EVENT_EVENT_ID_WORD_OFFSET                      0
#define TRACE_EVENT_EVENT_ID_F_OFFSET_MOD8                    2
#define TRACE_EVENT_EVENT_ID_F_OFFSET_MOD16                   2
#define TRACE_EVENT_TRACE_EVENT_INFO_F_OFFSET                 0
#define TRACE_EVENT_TRACE_EVENT_INFO_F_WIDTH                  18
#define TRACE_EVENT_TRACE_EVENT_INFO_OFFSET                   0
#define TRACE_EVENT_TRACE_EVENT_INFO_WORD_OFFSET              0

/* >>>RDD_TRACE_EVENT_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	trace_event_info       	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	incoming_task_num                	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	reserved                         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	task_pc                          	:13	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	incoming_bbhrx_src_addr          	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_wr                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_rd                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_wr_reply                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	ramrd                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	parser                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhtx                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhrx_async                      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhrx_sync                       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	cpu                              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	fw_self                          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	fw                               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	timer                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2                        	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	acc_type                         	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	trace_event_info       	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	incoming_task_num                	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	reserved                         	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	task_pc                          	:13	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	reserved1_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	incoming_bbhrx_src_addr          	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_wr                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_rd                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	dma_wr_reply                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	ramrd                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	parser                           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhtx                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhrx_async                      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	bbhrx_sync                       	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	cpu                              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	fw_self                          	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	fw                               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	timer                            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	reserved2_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved2                        	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	acc_type                         	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of trace_event_info union */
			uint32_t	reserved3_event_id               	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_timestamp              	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_TRACE_EVENT_DTS;

typedef union
{
    uint32_t word_val[1];
    RDD_TRACE_EVENT_DTS fields;
} TRACE_EVENT_STRUCT;
#define RDD_TRACE_EVENT_TIMESTAMP_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS), 4, 12, r)
#define RDD_TRACE_EVENT_TIMESTAMP_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS), 4, 12, v)
#define RDD_TRACE_EVENT_TIMESTAMP_READ(r, p)                               FIELD_MREAD_16((uint8_t *)p, 4, 12, r)
#define RDD_TRACE_EVENT_TIMESTAMP_WRITE(v, p)                              FIELD_MWRITE_16((uint8_t *)p, 4, 12, v)
#define RDD_TRACE_EVENT_EVENT_ID_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 1, 2, 2, r)
#define RDD_TRACE_EVENT_EVENT_ID_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 1, 2, 2, v)
#define RDD_TRACE_EVENT_EVENT_ID_READ(r, p)                                FIELD_MREAD_8((uint8_t *)p + 1, 2, 2, r)
#define RDD_TRACE_EVENT_EVENT_ID_WRITE(v, p)                               FIELD_MWRITE_8((uint8_t *)p + 1, 2, 2, v)
#define RDD_TRACE_EVENT_TRACE_EVENT_INFO_READ_G(r, g, idx)                 GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 0, 18, r)
#define RDD_TRACE_EVENT_TRACE_EVENT_INFO_WRITE_G(v, g, idx)                GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 0, 18, v)
#define RDD_TRACE_EVENT_TRACE_EVENT_INFO_READ(r, p)                        FIELD_MREAD_32((uint8_t *)p + 0, 0, 18, r)
#define RDD_TRACE_EVENT_TRACE_EVENT_INFO_WRITE(v, p)                       FIELD_MWRITE_32((uint8_t *)p + 0, 0, 18, v)
#define RDD_TRACE_EVENT_INCOMING_TASK_NUM_READ_G(r, g, idx)                GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 14, 4, r)
#define RDD_TRACE_EVENT_INCOMING_TASK_NUM_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 14, 4, v)
#define RDD_TRACE_EVENT_INCOMING_TASK_NUM_READ(r, p)                       FIELD_MREAD_32((uint8_t *)p + 0, 14, 4, r)
#define RDD_TRACE_EVENT_INCOMING_TASK_NUM_WRITE(v, p)                      FIELD_MWRITE_32((uint8_t *)p + 0, 14, 4, v)
#define RDD_TRACE_EVENT_TASK_PC_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 13, r)
#define RDD_TRACE_EVENT_TASK_PC_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 13, v)
#define RDD_TRACE_EVENT_TASK_PC_READ(r, p)                                 FIELD_MREAD_16((uint8_t *)p + 2, 0, 13, r)
#define RDD_TRACE_EVENT_TASK_PC_WRITE(v, p)                                FIELD_MWRITE_16((uint8_t *)p + 2, 0, 13, v)
#define RDD_TRACE_EVENT_INCOMING_BBHRX_SRC_ADDR_READ_G(r, g, idx)          GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 12, 6, r)
#define RDD_TRACE_EVENT_INCOMING_BBHRX_SRC_ADDR_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 0, 12, 6, v)
#define RDD_TRACE_EVENT_INCOMING_BBHRX_SRC_ADDR_READ(r, p)                 FIELD_MREAD_32((uint8_t *)p + 0, 12, 6, r)
#define RDD_TRACE_EVENT_INCOMING_BBHRX_SRC_ADDR_WRITE(v, p)                FIELD_MWRITE_32((uint8_t *)p + 0, 12, 6, v)
#define RDD_TRACE_EVENT_DMA_WR_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 3, 1, r)
#define RDD_TRACE_EVENT_DMA_WR_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 3, 1, v)
#define RDD_TRACE_EVENT_DMA_WR_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 2, 3, 1, r)
#define RDD_TRACE_EVENT_DMA_WR_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 2, 3, 1, v)
#define RDD_TRACE_EVENT_DMA_RD_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 2, 1, r)
#define RDD_TRACE_EVENT_DMA_RD_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 2, 1, v)
#define RDD_TRACE_EVENT_DMA_RD_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 2, 2, 1, r)
#define RDD_TRACE_EVENT_DMA_RD_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 2, 2, 1, v)
#define RDD_TRACE_EVENT_DMA_WR_REPLY_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 1, 1, r)
#define RDD_TRACE_EVENT_DMA_WR_REPLY_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 1, 1, v)
#define RDD_TRACE_EVENT_DMA_WR_REPLY_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 2, 1, 1, r)
#define RDD_TRACE_EVENT_DMA_WR_REPLY_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 2, 1, 1, v)
#define RDD_TRACE_EVENT_RAMRD_READ_G(r, g, idx)                            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 1, r)
#define RDD_TRACE_EVENT_RAMRD_WRITE_G(v, g, idx)                           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 1, v)
#define RDD_TRACE_EVENT_RAMRD_READ(r, p)                                   FIELD_MREAD_8((uint8_t *)p + 2, 0, 1, r)
#define RDD_TRACE_EVENT_RAMRD_WRITE(v, p)                                  FIELD_MWRITE_8((uint8_t *)p + 2, 0, 1, v)
#define RDD_TRACE_EVENT_PARSER_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 7, 1, r)
#define RDD_TRACE_EVENT_PARSER_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 7, 1, v)
#define RDD_TRACE_EVENT_PARSER_READ(r, p)                                  FIELD_MREAD_8((uint8_t *)p + 3, 7, 1, r)
#define RDD_TRACE_EVENT_PARSER_WRITE(v, p)                                 FIELD_MWRITE_8((uint8_t *)p + 3, 7, 1, v)
#define RDD_TRACE_EVENT_BBHTX_READ_G(r, g, idx)                            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 6, 1, r)
#define RDD_TRACE_EVENT_BBHTX_WRITE_G(v, g, idx)                           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 6, 1, v)
#define RDD_TRACE_EVENT_BBHTX_READ(r, p)                                   FIELD_MREAD_8((uint8_t *)p + 3, 6, 1, r)
#define RDD_TRACE_EVENT_BBHTX_WRITE(v, p)                                  FIELD_MWRITE_8((uint8_t *)p + 3, 6, 1, v)
#define RDD_TRACE_EVENT_BBHRX_ASYNC_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 5, 1, r)
#define RDD_TRACE_EVENT_BBHRX_ASYNC_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 5, 1, v)
#define RDD_TRACE_EVENT_BBHRX_ASYNC_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 3, 5, 1, r)
#define RDD_TRACE_EVENT_BBHRX_ASYNC_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 3, 5, 1, v)
#define RDD_TRACE_EVENT_BBHRX_SYNC_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 4, 1, r)
#define RDD_TRACE_EVENT_BBHRX_SYNC_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 4, 1, v)
#define RDD_TRACE_EVENT_BBHRX_SYNC_READ(r, p)                              FIELD_MREAD_8((uint8_t *)p + 3, 4, 1, r)
#define RDD_TRACE_EVENT_BBHRX_SYNC_WRITE(v, p)                             FIELD_MWRITE_8((uint8_t *)p + 3, 4, 1, v)
#define RDD_TRACE_EVENT_CPU_READ_G(r, g, idx)                              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 3, 1, r)
#define RDD_TRACE_EVENT_CPU_WRITE_G(v, g, idx)                             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 3, 1, v)
#define RDD_TRACE_EVENT_CPU_READ(r, p)                                     FIELD_MREAD_8((uint8_t *)p + 3, 3, 1, r)
#define RDD_TRACE_EVENT_CPU_WRITE(v, p)                                    FIELD_MWRITE_8((uint8_t *)p + 3, 3, 1, v)
#define RDD_TRACE_EVENT_FW_SELF_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 2, 1, r)
#define RDD_TRACE_EVENT_FW_SELF_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 2, 1, v)
#define RDD_TRACE_EVENT_FW_SELF_READ(r, p)                                 FIELD_MREAD_8((uint8_t *)p + 3, 2, 1, r)
#define RDD_TRACE_EVENT_FW_SELF_WRITE(v, p)                                FIELD_MWRITE_8((uint8_t *)p + 3, 2, 1, v)
#define RDD_TRACE_EVENT_FW_READ_G(r, g, idx)                               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 1, 1, r)
#define RDD_TRACE_EVENT_FW_WRITE_G(v, g, idx)                              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 1, 1, v)
#define RDD_TRACE_EVENT_FW_READ(r, p)                                      FIELD_MREAD_8((uint8_t *)p + 3, 1, 1, r)
#define RDD_TRACE_EVENT_FW_WRITE(v, p)                                     FIELD_MWRITE_8((uint8_t *)p + 3, 1, 1, v)
#define RDD_TRACE_EVENT_TIMER_READ_G(r, g, idx)                            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 0, 1, r)
#define RDD_TRACE_EVENT_TIMER_WRITE_G(v, g, idx)                           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 3, 0, 1, v)
#define RDD_TRACE_EVENT_TIMER_READ(r, p)                                   FIELD_MREAD_8((uint8_t *)p + 3, 0, 1, r)
#define RDD_TRACE_EVENT_TIMER_WRITE(v, p)                                  FIELD_MWRITE_8((uint8_t *)p + 3, 0, 1, v)
#define RDD_TRACE_EVENT_ACC_TYPE_READ_G(r, g, idx)                         GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 12, r)
#define RDD_TRACE_EVENT_ACC_TYPE_WRITE_G(v, g, idx)                        GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_TRACE_EVENT_DTS) + 2, 0, 12, v)
#define RDD_TRACE_EVENT_ACC_TYPE_READ(r, p)                                FIELD_MREAD_16((uint8_t *)p + 2, 0, 12, r)
#define RDD_TRACE_EVENT_ACC_TYPE_WRITE(v, p)                               FIELD_MWRITE_16((uint8_t *)p + 2, 0, 12, v)
/* <<<RDD_TRACE_EVENT_DTS */

/* <<<RDD_TRACE_EVENT */


/* >>>RDD_CPU_RX_DESCRIPTOR */
#define CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_F_OFFSET           0
#define CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_F_WIDTH            32
#define CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_OFFSET             0
#define CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_WORD_OFFSET        0
#define CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_F_OFFSET          24
#define CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_F_WIDTH           8
#define CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_OFFSET            4
#define CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_WORD_OFFSET       1
#define CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_F_OFFSET_MOD16    8
#define CPU_RX_DESCRIPTOR_ABS_F_OFFSET                              16
#define CPU_RX_DESCRIPTOR_ABS_F_WIDTH                               1
#define CPU_RX_DESCRIPTOR_ABS_OFFSET                                5
#define CPU_RX_DESCRIPTOR_ABS_WORD_OFFSET                           1
#define CPU_RX_DESCRIPTOR_ABS_F_OFFSET_MOD8                         0
#define CPU_RX_DESCRIPTOR_ABS_F_OFFSET_MOD16                        0
#define CPU_RX_DESCRIPTOR_PLEN_F_OFFSET                             2
#define CPU_RX_DESCRIPTOR_PLEN_F_WIDTH                              14
#define CPU_RX_DESCRIPTOR_PLEN_OFFSET                               6
#define CPU_RX_DESCRIPTOR_PLEN_WORD_OFFSET                          1
#define CPU_RX_DESCRIPTOR_PLEN_F_OFFSET_MOD16                       2
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_F_OFFSET               1
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_F_WIDTH                1
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_OFFSET                 7
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_WORD_OFFSET            1
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_F_OFFSET_MOD8          1
#define CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_F_OFFSET_MOD16         1
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_F_OFFSET                       31
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_F_WIDTH                        1
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_OFFSET                         8
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_WORD_OFFSET                    2
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_F_OFFSET_MOD8                  7
#define CPU_RX_DESCRIPTOR_IS_SRC_LAN_F_OFFSET_MOD16                 15
#define CPU_RX_DESCRIPTOR_COLOR_F_OFFSET                            30
#define CPU_RX_DESCRIPTOR_COLOR_F_WIDTH                             1
#define CPU_RX_DESCRIPTOR_COLOR_OFFSET                              8
#define CPU_RX_DESCRIPTOR_COLOR_WORD_OFFSET                         2
#define CPU_RX_DESCRIPTOR_COLOR_F_OFFSET_MOD8                       6
#define CPU_RX_DESCRIPTOR_COLOR_F_OFFSET_MOD16                      14
#define CPU_RX_DESCRIPTOR_VPORT_F_OFFSET                            25
#define CPU_RX_DESCRIPTOR_VPORT_F_WIDTH                             5
#define CPU_RX_DESCRIPTOR_VPORT_OFFSET                              8
#define CPU_RX_DESCRIPTOR_VPORT_WORD_OFFSET                         2
#define CPU_RX_DESCRIPTOR_VPORT_F_OFFSET_MOD8                       1
#define CPU_RX_DESCRIPTOR_VPORT_F_OFFSET_MOD16                      9
#define CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_F_OFFSET                 13
#define CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_F_WIDTH                  12
#define CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_OFFSET                   8
#define CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_WORD_OFFSET              2
#define CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_F_OFFSET_MOD16           13
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_F_OFFSET                      6
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_F_WIDTH                       7
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_OFFSET                        10
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_WORD_OFFSET                   2
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_F_OFFSET_MOD8                 6
#define CPU_RX_DESCRIPTOR_DATA_OFFSET_F_OFFSET_MOD16                6
#define CPU_RX_DESCRIPTOR_REASON_F_OFFSET                           0
#define CPU_RX_DESCRIPTOR_REASON_F_WIDTH                            6
#define CPU_RX_DESCRIPTOR_REASON_OFFSET                             11
#define CPU_RX_DESCRIPTOR_REASON_WORD_OFFSET                        2
#define CPU_RX_DESCRIPTOR_REASON_F_OFFSET_MOD8                      0
#define CPU_RX_DESCRIPTOR_REASON_F_OFFSET_MOD16                     0
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_F_OFFSET                     31
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_F_WIDTH                      1
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_OFFSET                       12
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_WORD_OFFSET                  3
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_F_OFFSET_MOD8                7
#define CPU_RX_DESCRIPTOR_IS_EXCEPTION_F_OFFSET_MOD16               15
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_F_OFFSET                    30
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_F_WIDTH                     1
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_OFFSET                      12
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_WORD_OFFSET                 3
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_F_OFFSET_MOD8               6
#define CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_F_OFFSET_MOD16              14
#define CPU_RX_DESCRIPTOR_IS_UCAST_F_OFFSET                         29
#define CPU_RX_DESCRIPTOR_IS_UCAST_F_WIDTH                          1
#define CPU_RX_DESCRIPTOR_IS_UCAST_OFFSET                           12
#define CPU_RX_DESCRIPTOR_IS_UCAST_WORD_OFFSET                      3
#define CPU_RX_DESCRIPTOR_IS_UCAST_F_OFFSET_MOD8                    5
#define CPU_RX_DESCRIPTOR_IS_UCAST_F_OFFSET_MOD16                   13
#define CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_F_OFFSET              16
#define CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_F_WIDTH               13
#define CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_OFFSET                12
#define CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_WORD_OFFSET           3
#define CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_F_OFFSET_MOD16        0
#define CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_F_OFFSET            0
#define CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_F_WIDTH             16
#define CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_OFFSET              14
#define CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_WORD_OFFSET         3

/* >>>RDD_CPU_RX_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	cpu_rx_data_ptr0_union  	; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	host_buffer_data_ptr_low          	; /* Member of cpu_rx_data_ptr0_union union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	fpm_idx                           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
			uint32_t	reserved0                         	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	bn0                               	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
			uint32_t	reserved9                         	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint8_t	host_buffer_data_ptr_hi 	;
			uint32_t	reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint8_t	reserved1_host_buffer_data_ptr_hi 	;
			uint32_t	reserved1_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint8_t	reserved2_host_buffer_data_ptr_hi 	;
			uint32_t	reserved2_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint8_t	reserved3_host_buffer_data_ptr_hi 	;
			uint32_t	reserved3_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cpu_rx_src_union        	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	wan_flow_id                       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved1_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3                         	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved2_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ssid                              	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved4                         	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved3_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mcast_tx_prio_union     	:13	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint16_t	cpu_rx_metadata_union   	; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	mcast_tx_prio                     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved5                         	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint16_t	dst_ssid_vector                   	; /* Member of cpu_rx_metadata_union union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved6                         	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	metadata_0                        	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved7                         	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint16_t	metadata_1                        	; /* Member of cpu_rx_metadata_union union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	omci_enc_key_index                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved8                         	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint8_t	egress_queue                      	; /* Member of cpu_rx_metadata_union union */
			uint8_t	wan_flow                          	; /* Member of cpu_rx_metadata_union union */
		};
	};
#else
	/* Union WORD 0 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	cpu_rx_data_ptr0_union  	; /* This is a field union */
		};
		/* Sub Union 1 */
		struct{
			uint32_t	host_buffer_data_ptr_low          	; /* Member of cpu_rx_data_ptr0_union union */
		};
		/* Sub Union 2 */
		struct{
			uint32_t	fpm_idx                           	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
			uint32_t	reserved0                         	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
		};
		/* Sub Union 3 */
		struct{
			uint32_t	bn0                               	:18	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
			uint32_t	reserved9                         	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_data_ptr0_union union */
		};
	};
	/* Union WORD 1 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	host_buffer_data_ptr_hi 	;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved1_host_buffer_data_ptr_hi 	;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved2_host_buffer_data_ptr_hi 	;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_reserved2               	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_chksum_verified      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_plen                    	:14	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_abs                     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_reserved1               	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint8_t	reserved3_host_buffer_data_ptr_hi 	;
		};
	};
	/* Union WORD 2 */
	union{
		/* Sub Union 0 */
		struct{
			uint32_t	reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	cpu_rx_src_union        	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint32_t	reserved1_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	wan_flow_id                       	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved1_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint32_t	reserved2_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3                         	:12	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved2_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint32_t	reserved3_reason                  	:6	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_data_offset             	:7	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	ssid                              	:4	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved4                         	:8	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of cpu_rx_src_union union */
			uint32_t	reserved3_vport                   	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_color                   	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_src_lan              	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
	/* Union WORD 3 */
	union{
		/* Sub Union 0 */
		struct{
			uint16_t	cpu_rx_metadata_union   	; /* This is a field union */
			uint32_t	mcast_tx_prio_union     	:13	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* This is a field union */
			uint32_t	is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 1 */
		struct{
			uint16_t	dst_ssid_vector                   	; /* Member of cpu_rx_metadata_union union */
			uint32_t	mcast_tx_prio                     	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved5                         	:10	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved1_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved1_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 2 */
		struct{
			uint16_t	metadata_1                        	; /* Member of cpu_rx_metadata_union union */
			uint32_t	reserved6                         	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	metadata_0                        	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved7                         	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved2_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved2_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
		/* Sub Union 3 */
		struct{
			uint8_t	egress_queue                      	; /* Member of cpu_rx_metadata_union union */
			uint8_t	wan_flow                          	; /* Member of cpu_rx_metadata_union union */
			uint32_t	omci_enc_key_index                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved8                         	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__; /* Member of mcast_tx_prio_union union */
			uint32_t	reserved3_is_ucast                	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_rx_offload           	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
			uint32_t	reserved3_is_exception            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
		};
	};
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RX_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_CPU_RX_DESCRIPTOR_DTS fields;
} CPU_RX_DESCRIPTOR_STRUCT;
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), v)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_READ(r, p)                   MREAD_32((uint8_t *)p, r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_DATA_PTR0_UNION_WRITE(v, p)                  MWRITE_32((uint8_t *)p, v)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_LOW_READ_G(r, g, idx)          GROUP_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), r)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_LOW_WRITE_G(v, g, idx)         GROUP_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), v)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_LOW_READ(r, p)                 MREAD_32((uint8_t *)p, r)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_LOW_WRITE(v, p)                MWRITE_32((uint8_t *)p, v)
#define RDD_CPU_RX_DESCRIPTOR_FPM_IDX_READ_G(r, g, idx)                           GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), 14, 18, r)
#define RDD_CPU_RX_DESCRIPTOR_FPM_IDX_WRITE_G(v, g, idx)                          GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), 14, 18, v)
#define RDD_CPU_RX_DESCRIPTOR_FPM_IDX_READ(r, p)                                  FIELD_MREAD_32((uint8_t *)p, 14, 18, r)
#define RDD_CPU_RX_DESCRIPTOR_FPM_IDX_WRITE(v, p)                                 FIELD_MWRITE_32((uint8_t *)p, 14, 18, v)
#define RDD_CPU_RX_DESCRIPTOR_BN0_READ_G(r, g, idx)                               GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), 14, 18, r)
#define RDD_CPU_RX_DESCRIPTOR_BN0_WRITE_G(v, g, idx)                              GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS), 14, 18, v)
#define RDD_CPU_RX_DESCRIPTOR_BN0_READ(r, p)                                      FIELD_MREAD_32((uint8_t *)p, 14, 18, r)
#define RDD_CPU_RX_DESCRIPTOR_BN0_WRITE(v, p)                                     FIELD_MWRITE_32((uint8_t *)p, 14, 18, v)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_READ_G(r, g, idx)           GROUP_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 4, r)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_WRITE_G(v, g, idx)          GROUP_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 4, v)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_READ(r, p)                  MREAD_8((uint8_t *)p + 4, r)
#define RDD_CPU_RX_DESCRIPTOR_HOST_BUFFER_DATA_PTR_HI_WRITE(v, p)                 MWRITE_8((uint8_t *)p + 4, v)
#define RDD_CPU_RX_DESCRIPTOR_ABS_READ_G(r, g, idx)                               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 5, 0, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_ABS_WRITE_G(v, g, idx)                              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 5, 0, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_ABS_READ(r, p)                                      FIELD_MREAD_8((uint8_t *)p + 5, 0, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_ABS_WRITE(v, p)                                     FIELD_MWRITE_8((uint8_t *)p + 5, 0, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_PLEN_READ_G(r, g, idx)                              GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 6, 2, 14, r)
#define RDD_CPU_RX_DESCRIPTOR_PLEN_WRITE_G(v, g, idx)                             GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 6, 2, 14, v)
#define RDD_CPU_RX_DESCRIPTOR_PLEN_READ(r, p)                                     FIELD_MREAD_16((uint8_t *)p + 6, 2, 14, r)
#define RDD_CPU_RX_DESCRIPTOR_PLEN_WRITE(v, p)                                    FIELD_MWRITE_16((uint8_t *)p + 6, 2, 14, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 7, 1, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 7, 1, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 7, 1, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_CHKSUM_VERIFIED_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 7, 1, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_SRC_LAN_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 7, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_SRC_LAN_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 7, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_SRC_LAN_READ(r, p)                               FIELD_MREAD_8((uint8_t *)p + 8, 7, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_SRC_LAN_WRITE(v, p)                              FIELD_MWRITE_8((uint8_t *)p + 8, 7, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_COLOR_READ_G(r, g, idx)                             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 6, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_COLOR_WRITE_G(v, g, idx)                            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 6, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_COLOR_READ(r, p)                                    FIELD_MREAD_8((uint8_t *)p + 8, 6, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_COLOR_WRITE(v, p)                                   FIELD_MWRITE_8((uint8_t *)p + 8, 6, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_VPORT_READ_G(r, g, idx)                             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 1, 5, r)
#define RDD_CPU_RX_DESCRIPTOR_VPORT_WRITE_G(v, g, idx)                            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 1, 5, v)
#define RDD_CPU_RX_DESCRIPTOR_VPORT_READ(r, p)                                    FIELD_MREAD_8((uint8_t *)p + 8, 1, 5, r)
#define RDD_CPU_RX_DESCRIPTOR_VPORT_WRITE(v, p)                                   FIELD_MWRITE_8((uint8_t *)p + 8, 1, 5, v)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 13, 12, r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 13, 12, v)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 8, 13, 12, r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_SRC_UNION_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 8, 13, 12, v)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_ID_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 13, 12, r)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_ID_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 13, 12, v)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_ID_READ(r, p)                              FIELD_MREAD_32((uint8_t *)p + 8, 13, 12, r)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_ID_WRITE(v, p)                             FIELD_MWRITE_32((uint8_t *)p + 8, 13, 12, v)
#define RDD_CPU_RX_DESCRIPTOR_SSID_READ_G(r, g, idx)                              GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 5, 4, r)
#define RDD_CPU_RX_DESCRIPTOR_SSID_WRITE_G(v, g, idx)                             GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 8, 5, 4, v)
#define RDD_CPU_RX_DESCRIPTOR_SSID_READ(r, p)                                     FIELD_MREAD_16((uint8_t *)p + 8, 5, 4, r)
#define RDD_CPU_RX_DESCRIPTOR_SSID_WRITE(v, p)                                    FIELD_MWRITE_16((uint8_t *)p + 8, 5, 4, v)
#define RDD_CPU_RX_DESCRIPTOR_DATA_OFFSET_READ_G(r, g, idx)                       GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 10, 6, 7, r)
#define RDD_CPU_RX_DESCRIPTOR_DATA_OFFSET_WRITE_G(v, g, idx)                      GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 10, 6, 7, v)
#define RDD_CPU_RX_DESCRIPTOR_DATA_OFFSET_READ(r, p)                              FIELD_MREAD_16((uint8_t *)p + 10, 6, 7, r)
#define RDD_CPU_RX_DESCRIPTOR_DATA_OFFSET_WRITE(v, p)                             FIELD_MWRITE_16((uint8_t *)p + 10, 6, 7, v)
#define RDD_CPU_RX_DESCRIPTOR_REASON_READ_G(r, g, idx)                            GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 11, 0, 6, r)
#define RDD_CPU_RX_DESCRIPTOR_REASON_WRITE_G(v, g, idx)                           GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 11, 0, 6, v)
#define RDD_CPU_RX_DESCRIPTOR_REASON_READ(r, p)                                   FIELD_MREAD_8((uint8_t *)p + 11, 0, 6, r)
#define RDD_CPU_RX_DESCRIPTOR_REASON_WRITE(v, p)                                  FIELD_MWRITE_8((uint8_t *)p + 11, 0, 6, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_EXCEPTION_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 7, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_EXCEPTION_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 7, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_EXCEPTION_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 12, 7, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_EXCEPTION_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 12, 7, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 6, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 6, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 12, 6, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_RX_OFFLOAD_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 12, 6, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_UCAST_READ_G(r, g, idx)                          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 5, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_UCAST_WRITE_G(v, g, idx)                         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 5, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_IS_UCAST_READ(r, p)                                 FIELD_MREAD_8((uint8_t *)p + 12, 5, 1, r)
#define RDD_CPU_RX_DESCRIPTOR_IS_UCAST_WRITE(v, p)                                FIELD_MWRITE_8((uint8_t *)p + 12, 5, 1, v)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_READ_G(r, g, idx)               GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 0, 13, r)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 0, 13, v)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_READ(r, p)                      FIELD_MREAD_16((uint8_t *)p + 12, 0, 13, r)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_UNION_WRITE(v, p)                     FIELD_MWRITE_16((uint8_t *)p + 12, 0, 13, v)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 2, 3, r)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 2, 3, v)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p + 12, 2, 3, r)
#define RDD_CPU_RX_DESCRIPTOR_MCAST_TX_PRIO_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p + 12, 2, 3, v)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_0_READ_G(r, g, idx)                        GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 5, 5, r)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_0_WRITE_G(v, g, idx)                       GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 5, 5, v)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_0_READ(r, p)                               FIELD_MREAD_16((uint8_t *)p + 12, 5, 5, r)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_0_WRITE(v, p)                              FIELD_MWRITE_16((uint8_t *)p + 12, 5, 5, v)
#define RDD_CPU_RX_DESCRIPTOR_OMCI_ENC_KEY_INDEX_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 3, 2, r)
#define RDD_CPU_RX_DESCRIPTOR_OMCI_ENC_KEY_INDEX_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 12, 3, 2, v)
#define RDD_CPU_RX_DESCRIPTOR_OMCI_ENC_KEY_INDEX_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p + 12, 3, 2, r)
#define RDD_CPU_RX_DESCRIPTOR_OMCI_ENC_KEY_INDEX_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p + 12, 3, 2, v)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_READ_G(r, g, idx)             GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_WRITE_G(v, g, idx)            GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_READ(r, p)                    MREAD_16((uint8_t *)p + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_CPU_RX_METADATA_UNION_WRITE(v, p)                   MWRITE_16((uint8_t *)p + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_DST_SSID_VECTOR_READ_G(r, g, idx)                   GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_DST_SSID_VECTOR_WRITE_G(v, g, idx)                  GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_DST_SSID_VECTOR_READ(r, p)                          MREAD_16((uint8_t *)p + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_DST_SSID_VECTOR_WRITE(v, p)                         MWRITE_16((uint8_t *)p + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_1_READ_G(r, g, idx)                        GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_1_WRITE_G(v, g, idx)                       GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_1_READ(r, p)                               MREAD_16((uint8_t *)p + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_METADATA_1_WRITE(v, p)                              MWRITE_16((uint8_t *)p + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_EGRESS_QUEUE_READ_G(r, g, idx)                      GROUP_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_EGRESS_QUEUE_WRITE_G(v, g, idx)                     GROUP_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_EGRESS_QUEUE_READ(r, p)                             MREAD_8((uint8_t *)p + 14, r)
#define RDD_CPU_RX_DESCRIPTOR_EGRESS_QUEUE_WRITE(v, p)                            MWRITE_8((uint8_t *)p + 14, v)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_READ_G(r, g, idx)                          GROUP_MREAD_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 15, r)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_WRITE_G(v, g, idx)                         GROUP_MWRITE_8(g, idx*sizeof(RDD_CPU_RX_DESCRIPTOR_DTS) + 15, v)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_READ(r, p)                                 MREAD_8((uint8_t *)p + 15, r)
#define RDD_CPU_RX_DESCRIPTOR_WAN_FLOW_WRITE(v, p)                                MWRITE_8((uint8_t *)p + 15, v)
/* <<<RDD_CPU_RX_DESCRIPTOR_DTS */

/* <<<RDD_CPU_RX_DESCRIPTOR */


/* >>>RDD_CPU_FEED_DESCRIPTOR */
#define CPU_FEED_DESCRIPTOR_PTR_LOW_F_OFFSET                          0
#define CPU_FEED_DESCRIPTOR_PTR_LOW_F_WIDTH                           32
#define CPU_FEED_DESCRIPTOR_CPU_FEED_DESCRIPTOR_OFFSET                0
#define CPU_FEED_DESCRIPTOR_PTR_LOW_OFFSET                            0
#define CPU_FEED_DESCRIPTOR_PTR_LOW_WORD_OFFSET                       0
#define CPU_FEED_DESCRIPTOR_TYPE_F_OFFSET                             8
#define CPU_FEED_DESCRIPTOR_TYPE_F_WIDTH                              1
#define CPU_FEED_DESCRIPTOR_TYPE_OFFSET                               6
#define CPU_FEED_DESCRIPTOR_TYPE_WORD_OFFSET                          1
#define CPU_FEED_DESCRIPTOR_TYPE_F_OFFSET_MOD8                        0
#define CPU_FEED_DESCRIPTOR_TYPE_F_OFFSET_MOD16                       8
#define CPU_FEED_DESCRIPTOR_PTR_HI_F_OFFSET                           0
#define CPU_FEED_DESCRIPTOR_PTR_HI_F_WIDTH                            8
#define CPU_FEED_DESCRIPTOR_PTR_HI_OFFSET                             7
#define CPU_FEED_DESCRIPTOR_PTR_HI_WORD_OFFSET                        1
#define CPU_FEED_DESCRIPTOR_PTR_HI_F_OFFSET_MOD16                     0

/* >>>RDD_CPU_FEED_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	ptr_low   	;
	uint32_t	reserved0 	:23	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	type      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint8_t	ptr_hi    	;
#else
	uint32_t	ptr_low   	;
	uint8_t	ptr_hi    	;
	uint32_t	type      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved0 	:23	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_FEED_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_CPU_FEED_DESCRIPTOR_DTS fields;
} CPU_FEED_DESCRIPTOR_STRUCT;
#define RDD_CPU_FEED_DESCRIPTOR_PTR_LOW_READ_G(r, g, idx)            GROUP_MREAD_32(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS), r)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_LOW_WRITE_G(v, g, idx)           GROUP_MWRITE_32(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS), v)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_LOW_READ(r, p)                   MREAD_32((uint8_t *)p, r)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_LOW_WRITE(v, p)                  MWRITE_32((uint8_t *)p, v)
#define RDD_CPU_FEED_DESCRIPTOR_TYPE_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS) + 6, 0, 1, r)
#define RDD_CPU_FEED_DESCRIPTOR_TYPE_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS) + 6, 0, 1, v)
#define RDD_CPU_FEED_DESCRIPTOR_TYPE_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 6, 0, 1, r)
#define RDD_CPU_FEED_DESCRIPTOR_TYPE_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 6, 0, 1, v)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_HI_READ_G(r, g, idx)             GROUP_MREAD_8(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS) + 7, r)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_HI_WRITE_G(v, g, idx)            GROUP_MWRITE_8(g, idx*sizeof(RDD_CPU_FEED_DESCRIPTOR_DTS) + 7, v)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_HI_READ(r, p)                    MREAD_8((uint8_t *)p + 7, r)
#define RDD_CPU_FEED_DESCRIPTOR_PTR_HI_WRITE(v, p)                   MWRITE_8((uint8_t *)p + 7, v)
/* <<<RDD_CPU_FEED_DESCRIPTOR_DTS */

/* <<<RDD_CPU_FEED_DESCRIPTOR */


/* >>>RDD_CPU_RING_DESCRIPTOR */
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_F_OFFSET                    27
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_F_WIDTH                     5
#define CPU_RING_DESCRIPTOR_CPU_RING_DESCRIPTOR_OFFSET                0
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_OFFSET                      0
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_WORD_OFFSET                 0
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_F_OFFSET_MOD8               3
#define CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_F_OFFSET_MOD16              11
#define CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_F_OFFSET                16
#define CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_F_WIDTH                 11
#define CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_OFFSET                  0
#define CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_WORD_OFFSET             0
#define CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_F_OFFSET_MOD16          0
#define CPU_RING_DESCRIPTOR_INTERRUPT_ID_F_OFFSET                     0
#define CPU_RING_DESCRIPTOR_INTERRUPT_ID_F_WIDTH                      16
#define CPU_RING_DESCRIPTOR_INTERRUPT_ID_OFFSET                       2
#define CPU_RING_DESCRIPTOR_INTERRUPT_ID_WORD_OFFSET                  0
#define CPU_RING_DESCRIPTOR_DROP_COUNTER_F_OFFSET                     16
#define CPU_RING_DESCRIPTOR_DROP_COUNTER_F_WIDTH                      16
#define CPU_RING_DESCRIPTOR_DROP_COUNTER_OFFSET                       4
#define CPU_RING_DESCRIPTOR_DROP_COUNTER_WORD_OFFSET                  1
#define CPU_RING_DESCRIPTOR_WRITE_IDX_F_OFFSET                        0
#define CPU_RING_DESCRIPTOR_WRITE_IDX_F_WIDTH                         16
#define CPU_RING_DESCRIPTOR_WRITE_IDX_OFFSET                          6
#define CPU_RING_DESCRIPTOR_WRITE_IDX_WORD_OFFSET                     1
#define CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_F_OFFSET                    0
#define CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_F_WIDTH                     32
#define CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_OFFSET                      8
#define CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_WORD_OFFSET                 2
#define CPU_RING_DESCRIPTOR_READ_IDX_F_OFFSET                         16
#define CPU_RING_DESCRIPTOR_READ_IDX_F_WIDTH                          16
#define CPU_RING_DESCRIPTOR_READ_IDX_OFFSET                           12
#define CPU_RING_DESCRIPTOR_READ_IDX_WORD_OFFSET                      3
#define CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_F_OFFSET                   0
#define CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_F_WIDTH                    8
#define CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_OFFSET                     15
#define CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_WORD_OFFSET                3
#define CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_F_OFFSET_MOD16             0

/* >>>RDD_CPU_RING_DESCRIPTOR_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	size_of_entry    	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	number_of_entries	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	interrupt_id     	;
	uint16_t	drop_counter     	;
	uint16_t	write_idx        	;
	uint32_t	base_addr_low    	;
	uint16_t	read_idx         	;
	uint8_t	reserved0        	;
	uint8_t	base_addr_high   	;
#else
	uint16_t	interrupt_id     	;
	uint32_t	number_of_entries	:11	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	size_of_entry    	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint16_t	write_idx        	;
	uint16_t	drop_counter     	;
	uint32_t	base_addr_low    	;
	uint8_t	base_addr_high   	;
	uint8_t	reserved0        	;
	uint16_t	read_idx         	;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_CPU_RING_DESCRIPTOR_DTS;

typedef union
{
    uint32_t word_val[4];
    uint64_t dword_val64[2];
    RDD_CPU_RING_DESCRIPTOR_DTS fields;
} CPU_RING_DESCRIPTOR_STRUCT;
#define RDD_CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS), 3, 5, r)
#define RDD_CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS), 3, 5, v)
#define RDD_CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p, 3, 5, r)
#define RDD_CPU_RING_DESCRIPTOR_SIZE_OF_ENTRY_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p, 3, 5, v)
#define RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ_G(r, g, idx)          GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS), 0, 11, r)
#define RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS), 0, 11, v)
#define RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ(r, p)                 FIELD_MREAD_16((uint8_t *)p, 0, 11, r)
#define RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_WRITE(v, p)                FIELD_MWRITE_16((uint8_t *)p, 0, 11, v)
#define RDD_CPU_RING_DESCRIPTOR_INTERRUPT_ID_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 2, r)
#define RDD_CPU_RING_DESCRIPTOR_INTERRUPT_ID_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 2, v)
#define RDD_CPU_RING_DESCRIPTOR_INTERRUPT_ID_READ(r, p)                      MREAD_16((uint8_t *)p + 2, r)
#define RDD_CPU_RING_DESCRIPTOR_INTERRUPT_ID_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 2, v)
#define RDD_CPU_RING_DESCRIPTOR_DROP_COUNTER_READ_G(r, g, idx)               GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 4, r)
#define RDD_CPU_RING_DESCRIPTOR_DROP_COUNTER_WRITE_G(v, g, idx)              GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 4, v)
#define RDD_CPU_RING_DESCRIPTOR_DROP_COUNTER_READ(r, p)                      MREAD_16((uint8_t *)p + 4, r)
#define RDD_CPU_RING_DESCRIPTOR_DROP_COUNTER_WRITE(v, p)                     MWRITE_16((uint8_t *)p + 4, v)
#define RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ_G(r, g, idx)                  GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 6, r)
#define RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_WRITE_G(v, g, idx)                 GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 6, v)
#define RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ(r, p)                         MREAD_16((uint8_t *)p + 6, r)
#define RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_WRITE(v, p)                        MWRITE_16((uint8_t *)p + 6, v)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_READ_G(r, g, idx)              GROUP_MREAD_32(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 8, r)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_WRITE_G(v, g, idx)             GROUP_MWRITE_32(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 8, v)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_READ(r, p)                     MREAD_32((uint8_t *)p + 8, r)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_LOW_WRITE(v, p)                    MWRITE_32((uint8_t *)p + 8, v)
#define RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ_G(r, g, idx)                   GROUP_MREAD_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 12, r)
#define RDD_CPU_RING_DESCRIPTOR_READ_IDX_WRITE_G(v, g, idx)                  GROUP_MWRITE_16(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 12, v)
#define RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ(r, p)                          MREAD_16((uint8_t *)p + 12, r)
#define RDD_CPU_RING_DESCRIPTOR_READ_IDX_WRITE(v, p)                         MWRITE_16((uint8_t *)p + 12, v)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_READ_G(r, g, idx)             GROUP_MREAD_8(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 15, r)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_WRITE_G(v, g, idx)            GROUP_MWRITE_8(g, idx*sizeof(RDD_CPU_RING_DESCRIPTOR_DTS) + 15, v)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_READ(r, p)                    MREAD_8((uint8_t *)p + 15, r)
#define RDD_CPU_RING_DESCRIPTOR_BASE_ADDR_HIGH_WRITE(v, p)                   MWRITE_8((uint8_t *)p + 15, v)
/* <<<RDD_CPU_RING_DESCRIPTOR_DTS */

/* <<<RDD_CPU_RING_DESCRIPTOR */


/* >>>RDD_PERIPHERALS_STS */
#define PERIPHERALS_STS_SCHEDULER_DEBUG_F_OFFSET                  27
#define PERIPHERALS_STS_SCHEDULER_DEBUG_F_WIDTH                   5
#define PERIPHERALS_STS_PERIPHERALS_STS_OFFSET                    0
#define PERIPHERALS_STS_SCHEDULER_DEBUG_OFFSET                    0
#define PERIPHERALS_STS_SCHEDULER_DEBUG_WORD_OFFSET               0
#define PERIPHERALS_STS_SCHEDULER_DEBUG_F_OFFSET_MOD8             3
#define PERIPHERALS_STS_SCHEDULER_DEBUG_F_OFFSET_MOD16            11
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_F_OFFSET             26
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_F_WIDTH              1
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_OFFSET               0
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_WORD_OFFSET          0
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_F_OFFSET_MOD8        2
#define PERIPHERALS_STS_NEXT_THREAD_IS_READY_F_OFFSET_MOD16       10
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_F_OFFSET               21
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_F_WIDTH                5
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_OFFSET                 0
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_WORD_OFFSET            0
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_F_OFFSET_MOD8          5
#define PERIPHERALS_STS_NEXT_THREAD_NUMBER_F_OFFSET_MOD16         5
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_F_OFFSET            16
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_F_WIDTH             5
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_OFFSET              1
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_WORD_OFFSET         0
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_F_OFFSET_MOD8       0
#define PERIPHERALS_STS_CURRENT_THREAD_NUMBER_F_OFFSET_MOD16      0
#define PERIPHERALS_STS_TIMER_1_STATUS_F_OFFSET                   12
#define PERIPHERALS_STS_TIMER_1_STATUS_F_WIDTH                    1
#define PERIPHERALS_STS_TIMER_1_STATUS_OFFSET                     2
#define PERIPHERALS_STS_TIMER_1_STATUS_WORD_OFFSET                0
#define PERIPHERALS_STS_TIMER_1_STATUS_F_OFFSET_MOD8              4
#define PERIPHERALS_STS_TIMER_1_STATUS_F_OFFSET_MOD16             12
#define PERIPHERALS_STS_TIMER_0_STATUS_F_OFFSET                   11
#define PERIPHERALS_STS_TIMER_0_STATUS_F_WIDTH                    1
#define PERIPHERALS_STS_TIMER_0_STATUS_OFFSET                     2
#define PERIPHERALS_STS_TIMER_0_STATUS_WORD_OFFSET                0
#define PERIPHERALS_STS_TIMER_0_STATUS_F_OFFSET_MOD8              3
#define PERIPHERALS_STS_TIMER_0_STATUS_F_OFFSET_MOD16             11
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_F_OFFSET       8
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_F_WIDTH        1
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_OFFSET         2
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_WORD_OFFSET    0
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_F_OFFSET_MOD8  0
#define PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_F_OFFSET_MOD16 8
#define PERIPHERALS_STS_QUAD_ID_F_OFFSET                          6
#define PERIPHERALS_STS_QUAD_ID_F_WIDTH                           2
#define PERIPHERALS_STS_QUAD_ID_OFFSET                            3
#define PERIPHERALS_STS_QUAD_ID_WORD_OFFSET                       0
#define PERIPHERALS_STS_QUAD_ID_F_OFFSET_MOD8                     6
#define PERIPHERALS_STS_QUAD_ID_F_OFFSET_MOD16                    6
#define PERIPHERALS_STS_CORE_ID_F_OFFSET                          4
#define PERIPHERALS_STS_CORE_ID_F_WIDTH                           2
#define PERIPHERALS_STS_CORE_ID_OFFSET                            3
#define PERIPHERALS_STS_CORE_ID_WORD_OFFSET                       0
#define PERIPHERALS_STS_CORE_ID_F_OFFSET_MOD8                     4
#define PERIPHERALS_STS_CORE_ID_F_OFFSET_MOD16                    4
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_F_OFFSET               3
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_F_WIDTH                1
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_OFFSET                 3
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_WORD_OFFSET            0
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_F_OFFSET_MOD8          3
#define PERIPHERALS_STS_BB_MESSAGE_PENDING_F_OFFSET_MOD16         3
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_F_OFFSET       2
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_F_WIDTH        1
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_OFFSET         3
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_WORD_OFFSET    0
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_F_OFFSET_MOD8  2
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_F_OFFSET_MOD16 2
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_F_OFFSET           1
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_F_WIDTH            1
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_OFFSET             3
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_WORD_OFFSET        0
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_F_OFFSET_MOD8      1
#define PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_F_OFFSET_MOD16     1
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_F_OFFSET            0
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_F_WIDTH             1
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_OFFSET              3
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_WORD_OFFSET         0
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_F_OFFSET_MOD8       0
#define PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_F_OFFSET_MOD16      0

/* >>>RDD_PERIPHERALS_STS_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	scheduler_debug           	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	next_thread_is_ready      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	next_thread_number        	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	current_thread_number     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved_1                	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	timer_1_status            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	timer_0_status            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved_2                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ram_read_command_fifo_full	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	quad_id                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	core_id                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bb_message_pending        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bbtx_command_fifo_is_empty	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bbtx_command_fifo_full    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	dma_command_fifo_full     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	dma_command_fifo_full     	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bbtx_command_fifo_full    	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bbtx_command_fifo_is_empty	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	bb_message_pending        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	core_id                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	quad_id                   	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	ram_read_command_fifo_full	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved_2                	:2	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	timer_0_status            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	timer_1_status            	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	reserved_1                	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	current_thread_number     	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	next_thread_number        	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	next_thread_is_ready      	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	scheduler_debug           	:5	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PERIPHERALS_STS_DTS;

typedef union
{
    uint32_t word_val[1];
    RDD_PERIPHERALS_STS_DTS fields;
} PERIPHERALS_STS_STRUCT;
#define RDD_PERIPHERALS_STS_SCHEDULER_DEBUG_READ_G(r, g, idx)                     GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 3, 5, r)
#define RDD_PERIPHERALS_STS_SCHEDULER_DEBUG_WRITE_G(v, g, idx)                    GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 3, 5, v)
#define RDD_PERIPHERALS_STS_SCHEDULER_DEBUG_READ(r, p)                            FIELD_MREAD_8((uint8_t *)p, 3, 5, r)
#define RDD_PERIPHERALS_STS_SCHEDULER_DEBUG_WRITE(v, p)                           FIELD_MWRITE_8((uint8_t *)p, 3, 5, v)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_IS_READY_READ_G(r, g, idx)                GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 2, 1, r)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_IS_READY_WRITE_G(v, g, idx)               GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 2, 1, v)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_IS_READY_READ(r, p)                       FIELD_MREAD_8((uint8_t *)p, 2, 1, r)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_IS_READY_WRITE(v, p)                      FIELD_MWRITE_8((uint8_t *)p, 2, 1, v)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_NUMBER_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_16(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 5, 5, r)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_NUMBER_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_16(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS), 5, 5, v)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_NUMBER_READ(r, p)                         FIELD_MREAD_16((uint8_t *)p, 5, 5, r)
#define RDD_PERIPHERALS_STS_NEXT_THREAD_NUMBER_WRITE(v, p)                        FIELD_MWRITE_16((uint8_t *)p, 5, 5, v)
#define RDD_PERIPHERALS_STS_CURRENT_THREAD_NUMBER_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 1, 0, 5, r)
#define RDD_PERIPHERALS_STS_CURRENT_THREAD_NUMBER_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 1, 0, 5, v)
#define RDD_PERIPHERALS_STS_CURRENT_THREAD_NUMBER_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 1, 0, 5, r)
#define RDD_PERIPHERALS_STS_CURRENT_THREAD_NUMBER_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 1, 0, 5, v)
#define RDD_PERIPHERALS_STS_TIMER_1_STATUS_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 4, 1, r)
#define RDD_PERIPHERALS_STS_TIMER_1_STATUS_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 4, 1, v)
#define RDD_PERIPHERALS_STS_TIMER_1_STATUS_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 2, 4, 1, r)
#define RDD_PERIPHERALS_STS_TIMER_1_STATUS_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 2, 4, 1, v)
#define RDD_PERIPHERALS_STS_TIMER_0_STATUS_READ_G(r, g, idx)                      GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 3, 1, r)
#define RDD_PERIPHERALS_STS_TIMER_0_STATUS_WRITE_G(v, g, idx)                     GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 3, 1, v)
#define RDD_PERIPHERALS_STS_TIMER_0_STATUS_READ(r, p)                             FIELD_MREAD_8((uint8_t *)p + 2, 3, 1, r)
#define RDD_PERIPHERALS_STS_TIMER_0_STATUS_WRITE(v, p)                            FIELD_MWRITE_8((uint8_t *)p + 2, 3, 1, v)
#define RDD_PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 0, 1, r)
#define RDD_PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 2, 0, 1, v)
#define RDD_PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 2, 0, 1, r)
#define RDD_PERIPHERALS_STS_RAM_READ_COMMAND_FIFO_FULL_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 2, 0, 1, v)
#define RDD_PERIPHERALS_STS_QUAD_ID_READ_G(r, g, idx)                             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 6, 2, r)
#define RDD_PERIPHERALS_STS_QUAD_ID_WRITE_G(v, g, idx)                            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 6, 2, v)
#define RDD_PERIPHERALS_STS_QUAD_ID_READ(r, p)                                    FIELD_MREAD_8((uint8_t *)p + 3, 6, 2, r)
#define RDD_PERIPHERALS_STS_QUAD_ID_WRITE(v, p)                                   FIELD_MWRITE_8((uint8_t *)p + 3, 6, 2, v)
#define RDD_PERIPHERALS_STS_CORE_ID_READ_G(r, g, idx)                             GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 4, 2, r)
#define RDD_PERIPHERALS_STS_CORE_ID_WRITE_G(v, g, idx)                            GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 4, 2, v)
#define RDD_PERIPHERALS_STS_CORE_ID_READ(r, p)                                    FIELD_MREAD_8((uint8_t *)p + 3, 4, 2, r)
#define RDD_PERIPHERALS_STS_CORE_ID_WRITE(v, p)                                   FIELD_MWRITE_8((uint8_t *)p + 3, 4, 2, v)
#define RDD_PERIPHERALS_STS_BB_MESSAGE_PENDING_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 3, 1, r)
#define RDD_PERIPHERALS_STS_BB_MESSAGE_PENDING_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 3, 1, v)
#define RDD_PERIPHERALS_STS_BB_MESSAGE_PENDING_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 3, 3, 1, r)
#define RDD_PERIPHERALS_STS_BB_MESSAGE_PENDING_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 3, 3, 1, v)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 2, 1, r)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 2, 1, v)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 3, 2, 1, r)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_IS_EMPTY_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 3, 2, 1, v)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_READ_G(r, g, idx)              GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 1, 1, r)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_WRITE_G(v, g, idx)             GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 1, 1, v)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_READ(r, p)                     FIELD_MREAD_8((uint8_t *)p + 3, 1, 1, r)
#define RDD_PERIPHERALS_STS_BBTX_COMMAND_FIFO_FULL_WRITE(v, p)                    FIELD_MWRITE_8((uint8_t *)p + 3, 1, 1, v)
#define RDD_PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_READ_G(r, g, idx)               GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 0, 1, r)
#define RDD_PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_WRITE_G(v, g, idx)              GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_PERIPHERALS_STS_DTS) + 3, 0, 1, v)
#define RDD_PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_READ(r, p)                      FIELD_MREAD_8((uint8_t *)p + 3, 0, 1, r)
#define RDD_PERIPHERALS_STS_DMA_COMMAND_FIFO_FULL_WRITE(v, p)                     FIELD_MWRITE_8((uint8_t *)p + 3, 0, 1, v)
/* <<<RDD_PERIPHERALS_STS_DTS */

/* <<<RDD_PERIPHERALS_STS */


/* >>>RDD_HASH_COMMAND */
#define HASH_COMMAND_KEY_1_F_OFFSET                            0
#define HASH_COMMAND_KEY_1_F_WIDTH                             32
#define HASH_COMMAND_HASH_COMMAND_OFFSET                       0
#define HASH_COMMAND_KEY_1_OFFSET                              0
#define HASH_COMMAND_KEY_1_WORD_OFFSET                         0
#define HASH_COMMAND_KEY_0_F_OFFSET                            4
#define HASH_COMMAND_KEY_0_F_WIDTH                             28
#define HASH_COMMAND_KEY_0_OFFSET                              4
#define HASH_COMMAND_KEY_0_WORD_OFFSET                         1
#define HASH_COMMAND_CONFIGURATION_F_OFFSET                    1
#define HASH_COMMAND_CONFIGURATION_F_WIDTH                     3
#define HASH_COMMAND_CONFIGURATION_OFFSET                      7
#define HASH_COMMAND_CONFIGURATION_WORD_OFFSET                 1
#define HASH_COMMAND_CONFIGURATION_F_OFFSET_MOD8               1
#define HASH_COMMAND_CONFIGURATION_F_OFFSET_MOD16              1
#define HASH_COMMAND_AGING_F_OFFSET                            0
#define HASH_COMMAND_AGING_F_WIDTH                             1
#define HASH_COMMAND_AGING_OFFSET                              7
#define HASH_COMMAND_AGING_WORD_OFFSET                         1
#define HASH_COMMAND_AGING_F_OFFSET_MOD8                       0
#define HASH_COMMAND_AGING_F_OFFSET_MOD16                      0

/* >>>RDD_HASH_COMMAND_DTS */

typedef struct
{
#ifndef FIRMWARE_LITTLE_ENDIAN
	uint32_t	key_1        	;
	uint32_t	key_0        	:28	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	configuration	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	aging        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#else
	uint32_t	key_1        	;
	uint32_t	aging        	:1	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	configuration	:3	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
	uint32_t	key_0        	:28	__PACKING_ATTRIBUTE_FIELD_LEVEL__;
#endif
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_HASH_COMMAND_DTS;

typedef union
{
    uint32_t word_val[2];
    uint64_t dword_val64[1];
    RDD_HASH_COMMAND_DTS fields;
} HASH_COMMAND_STRUCT;
#define RDD_HASH_COMMAND_KEY_1_READ_G(r, g, idx)                  GROUP_MREAD_32(g, idx*sizeof(RDD_HASH_COMMAND_DTS), r)
#define RDD_HASH_COMMAND_KEY_1_WRITE_G(v, g, idx)                 GROUP_MWRITE_32(g, idx*sizeof(RDD_HASH_COMMAND_DTS), v)
#define RDD_HASH_COMMAND_KEY_1_READ(r, p)                         MREAD_32((uint8_t *)p, r)
#define RDD_HASH_COMMAND_KEY_1_WRITE(v, p)                        MWRITE_32((uint8_t *)p, v)
#define RDD_HASH_COMMAND_KEY_0_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_32(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 4, 4, 28, r)
#define RDD_HASH_COMMAND_KEY_0_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_32(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 4, 4, 28, v)
#define RDD_HASH_COMMAND_KEY_0_READ(r, p)                         FIELD_MREAD_32((uint8_t *)p + 4, 4, 28, r)
#define RDD_HASH_COMMAND_KEY_0_WRITE(v, p)                        FIELD_MWRITE_32((uint8_t *)p + 4, 4, 28, v)
#define RDD_HASH_COMMAND_CONFIGURATION_READ_G(r, g, idx)          GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 7, 1, 3, r)
#define RDD_HASH_COMMAND_CONFIGURATION_WRITE_G(v, g, idx)         GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 7, 1, 3, v)
#define RDD_HASH_COMMAND_CONFIGURATION_READ(r, p)                 FIELD_MREAD_8((uint8_t *)p + 7, 1, 3, r)
#define RDD_HASH_COMMAND_CONFIGURATION_WRITE(v, p)                FIELD_MWRITE_8((uint8_t *)p + 7, 1, 3, v)
#define RDD_HASH_COMMAND_AGING_READ_G(r, g, idx)                  GROUP_FIELD_MREAD_8(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 7, 0, 1, r)
#define RDD_HASH_COMMAND_AGING_WRITE_G(v, g, idx)                 GROUP_FIELD_MWRITE_8(g, idx*sizeof(RDD_HASH_COMMAND_DTS) + 7, 0, 1, v)
#define RDD_HASH_COMMAND_AGING_READ(r, p)                         FIELD_MREAD_8((uint8_t *)p + 7, 0, 1, r)
#define RDD_HASH_COMMAND_AGING_WRITE(v, p)                        FIELD_MWRITE_8((uint8_t *)p + 7, 0, 1, v)
/* <<<RDD_HASH_COMMAND_DTS */

/* <<<RDD_HASH_COMMAND */

#endif /* _RDD_DATA_STRUCTURES_AUTO_H_ */
