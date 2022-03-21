/*
    Copyright 2000-2015 Broadcom Corporation
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

/***************************************************************************
 * File Name  : bcm_ubi.c
 *
 * Description: This file contains the universal UBI volume parser
 ***************************************************************************/


/** Includes. */

#include "bcm_ubi.h"

#ifdef _CFE_

#include "lib_types.h"
#include "lib_printf.h"
#include "lib_crc.h"
#include "lib_byteorder.h"

#define getCrc32 lib_get_crc32

#else // Linux

#define getCrc32 crc_getCrc32

#ifndef __KERNEL__
#define be32_to_cpu be32toh
#endif

#endif

#ifndef __KERNEL__
#define PRINT printf
#else
#define PRINT printk
#endif


#define CRC_INIT  -1
#define CRC_LENGTH 4

/* -------------------------------------------------------------------
   this function scans a UBI device for a particular volume and then a
   data name/value element within that volume, and either sets it
   if the write callback function pointer is non-zero, or returns
   the data. It requires a single block sized buffer created
   by the calling code
   -------------------------------------------------------------------
*/
unsigned int parse_ubi(
    unsigned char * start, // pointer to start of image buffer
    unsigned char * buf, // single block buffer created outside this function we can use
    unsigned int start_blk,
    unsigned int end_blk,
    unsigned int blk_size,
    unsigned int volume_id,
    char * name,
    char * data,
    char ** dataP, // if populated, returns pointer to location of volume_id block
    int header,
    unsigned int (*readblk)(unsigned char * start, unsigned int blk, unsigned int offset, unsigned int blk_size, unsigned char * buf, unsigned int amount, void * mtd, int mtd_fd),
    unsigned int (*writeblk)(unsigned char * start, unsigned int blk, unsigned int offset, unsigned int blk_size, unsigned char * buf, unsigned int amount, void * mtd, int mtd_fd), // leave NULL if reading
    unsigned int (*eraseblk)(unsigned int blk, unsigned int blk_size, void * mtd, int mtd_fd),
    void * mtd,
    int mtd_fd
)
{
    unsigned int i;

    struct ubi_ec_hdr *ec = (struct ubi_ec_hdr *) buf;
    struct ubi_vid_hdr *vid;

    unsigned int lnum = 0;
    unsigned int end;
    unsigned int state = 1;
    unsigned int from = 0; // file buffer
    unsigned int to = 0; // local buffers
    unsigned int next_entry = 0; // length of record (length to next entry)
    unsigned int data_point = 0; // pointer to entry data name
    unsigned int data_length = 0; // length of entry data
    unsigned int retry = 0;
    unsigned int status = 0;
    unsigned int crc_calc = -1, crc_grab = -1; // data crc

RETRY:
    for( i = start_blk; i < end_blk; i++ )
    { // read ec header
        if (!readblk(start, i, 0, blk_size, buf, UBI_EC_HDR_SIZE, mtd, mtd_fd))
            continue;

        if ( (be32_to_cpu(ec->magic) == UBI_EC_HDR_MAGIC) && (getCrc32((void *)ec, UBI_EC_HDR_SIZE-4, CRC_INIT) == be32_to_cpu(ec->hdr_crc)) )
        { // read up to vid header
            if(!readblk(start, i, UBI_EC_HDR_SIZE, blk_size, buf, be32_to_cpu(ec->vid_hdr_offset) + UBI_VID_HDR_SIZE - UBI_EC_HDR_SIZE, mtd, mtd_fd))
                continue;

            vid = (struct ubi_vid_hdr *) (buf + be32_to_cpu(ec->vid_hdr_offset));

            if( (be32_to_cpu(vid->magic) == UBI_VID_HDR_MAGIC) && (be32_to_cpu(vid->vol_id) == volume_id) && (be32_to_cpu(vid->lnum) == lnum) && (getCrc32((void *)vid, UBI_VID_HDR_SIZE-4, -1) == be32_to_cpu(vid->hdr_crc)) )
            { // read rest of block
                if(!readblk(start, i, be32_to_cpu(ec->vid_hdr_offset) + UBI_VID_HDR_SIZE, blk_size, buf, blk_size - (be32_to_cpu(ec->vid_hdr_offset) + UBI_VID_HDR_SIZE), mtd, mtd_fd))
                    continue;

                if ( (!vid->data_size) || (getCrc32((void *)buf + be32_to_cpu(ec->data_offset), be32_to_cpu(vid->data_size), CRC_INIT) == be32_to_cpu(vid->data_crc)) )
                { // if dynamic volume or data crc matches

                    retry = 1; // found our block, allow for spin through blocks again if we get to the end just in case they are out of order

                    if (vid->data_size)
                        end = be32_to_cpu(vid->data_size) + be32_to_cpu(ec->data_offset);
                    else
                        end = blk_size; // assume data takes the rest of block if not told otherwise

                    from = be32_to_cpu(ec->data_offset);
CONT:
                    switch(state)
                    {
                        default:
                            from = be32_to_cpu(ec->data_offset);
                            to = 0;
                            state = 0;

                        case 0: // advance to next entry
                            if (next_entry >= (end - from))
                            { // go to next entry
                                next_entry -= (end - from);
                                //lnum += length / (len - offset);
                                //from = length % (len - offset);
                                lnum++;
                                break;
                            }

                            from += next_entry;
                            state++;

                        case 1: // advance to next entry
                            crc_calc = -1;
                            to = 0;
                            state++;

                        case 2: // get pointer to next entry
                            while((from < end) && (to < 4))
                            {
                                crc_calc = getCrc32(&buf[from], 1, crc_calc);
                                to++;
                                next_entry <<= 8;
                                next_entry |= buf[from++];
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            if (!next_entry)
                            { // we are past the last entry which means we found our metadata block but didn't find our entry
                                return(0);
                            }

                            to = 0;
                            state++;

                        case 3: // get pointer to entry data
                            while((from < end) && (to < 4))
                            {
                                crc_calc = getCrc32(&buf[from], 1, crc_calc);
                                to++;
                                data_point <<= 8;
                                data_point |= buf[from++];
                                next_entry--;
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            if (data_point > next_entry)
                            {
                                PRINT("ERROR!!! Data pointer greater than total entry size\n");

                                return(0);
                            }

                            to = 0;
                            state++;

                        case 4: // get length of entry data
                            while((from < end) && (to < 4))
                            {
                                crc_calc = getCrc32(&buf[from], 1, crc_calc);
                                to++;
                                data_length <<= 8;
                                data_length |= buf[from++];
                                data_point--;
                                next_entry--;
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            if (data_length > next_entry)
                            {
                                PRINT("ERROR!!! Data length greater than total entry size\n");

                                return(0);
                            }

                            to = 0;
                            state++;

                        case 5: // check header crc
                            while((from < end) && (to < 4))
                            {
                                crc_grab = (crc_grab << 8) | buf[from++];
                                to++;
                                data_point--;
                                next_entry--;
                            }

                            if (crc_calc != crc_grab)
                                return(0);

                            crc_calc = -1;
                            to = 0;
                            state++;

                        case 6: // compare entry name to what we're searching for
                            while((from < end) && (buf[from] >= 0x20) && (name[to] >= 0x20) && (buf[from] == name[to]) && data_point)
                            {
                                crc_calc = getCrc32(&buf[from++], 1, crc_calc);
                                to++;
                                data_point--;
                                next_entry--;
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            if ((buf[from] >= 0x20) || (name[to] >= 0x20))
                            { // entry name doesn't match what we're searching for
                                state = 0;
                                goto CONT;
                            }

                            if (header < 0) // return data length if that's all that's requested
                                return(data_length);

                            state++;

                        case 7: // move past entry name
                            while((from < end) && data_point)
                            {
                                crc_calc = getCrc32(&buf[from++], 1, crc_calc);
                                data_point--;
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            if (header > 0)
                            { // grab just the header if requested, for example just the cferam header info instead of the whole cferam
                                data_length = header;

                                if (data_length > next_entry)
                                {
                                    PRINT("ERROR!!! Requested data header length greater than total entry size\n");

                                    return(0);
                                }
                            }

                            to = 0;
                            state++;

                        case 8: // get/put data
                            while((from < end) && data_length) // 4=crc length
                            {
                                if (writeblk)
                                    buf[from] = data[to];
                                else
                                    data[to] = buf[from];

                                crc_calc = getCrc32(&buf[from++], 1, crc_calc);

                                to++;
                                data_length--;
                            }

                            if (writeblk && to && (from >= end))
                            { // update only if we touched data and are at the end of the block
                                if (vid->data_size)
                                { // only update the CRC's if static volume, otherwise changing data CRC or size from zero on dynamic volume will cause kernel panic
                                    vid->data_crc = be32_to_cpu(getCrc32((void *)buf, be32_to_cpu(vid->data_size), CRC_INIT));
                                    vid->hdr_crc = be32_to_cpu(getCrc32((void *)vid, UBI_VID_HDR_SIZE-4, CRC_INIT));
                                }

                                if (eraseblk)
                                    if (!eraseblk(i, blk_size, mtd, mtd_fd))
                                        return(0);

                                if(!writeblk(start, i, 0, blk_size, buf, blk_size, mtd, mtd_fd))
                                    return(0); 
                            }

                            if (from >= end) // get more data
                            {
                                lnum++;
                                break;
                            }

                            status = to;
                            data_length = CRC_LENGTH;
                            state++;

                        case 9: // check/put data crc
                            while((from < end) && data_length)
                            {
                                if (writeblk)
                                {
                                    buf[from] = crc_calc >> 24;
                                    crc_calc <<= 8;
                                }
                                else
                                {
                                    crc_grab = (crc_grab << 8) | buf[from];
                                }

                                data_length--;
                                from++;
                            }

                            if (writeblk)
                            { // we fell through, write back since data would have been updated in previous state
                                if (vid->data_size)
                                { // only update the CRC's if static volume, otherwise changing data CRC or size from zero on dynamic volume will cause kernel panic
                                    vid->data_crc = be32_to_cpu(getCrc32((void *)buf, be32_to_cpu(vid->data_size), CRC_INIT));
                                    vid->hdr_crc = be32_to_cpu(getCrc32((void *)vid, UBI_VID_HDR_SIZE-4, CRC_INIT));
                                }

                                if (eraseblk)
                                    if (!eraseblk(i, blk_size, mtd, mtd_fd))
                                        return(0);

                                if(!writeblk(start, i, 0, blk_size, buf, blk_size, mtd, mtd_fd))
                                    return(0); 
                            }

                            if (data_length) // get more data, but only if we need it
                            {
                                lnum++;
                                break;
                            }

                            if (writeblk)
                            {
                                if (dataP) // return block which matches found entry
                                    *dataP = (char *)start + (i * blk_size);

                                return(status);
			    }
                            else if (crc_calc == crc_grab)
                                return(status);
                            else
                                return(0);

                    }
                }
            }
        }
    }

    if (retry) // spin through blocks again in case they are out of order
    {
        retry = 0;

        goto RETRY;
    }

    return(0);
}



