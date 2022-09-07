/***********************************************************************
 *
 *  Copyright (c) 2006-2007  Broadcom Corporation
 *  All Rights Reserved
 *
<:label-BRCM:2012:DUAL/GPL:standard

Unless you and Broadcom execute a separate written software license
agreement governing use of this software, this software is licensed
to you under the terms of the GNU General Public License version 2
(the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
with the following added to such license:

   As a special exception, the copyright holders of this software give
   you permission to link this software with independent modules, and
   to copy and distribute the resulting executable under terms of your
   choice, provided that you also meet, for each linked independent
   module, the terms and conditions of the license of that module.
   An independent module is a module which is not derived from this
   software.  The special exception does not apply to any modifications
   of the software.

Not withstanding the above, under no circumstances may you combine
this software in any way with any other Broadcom software provided
under a license other than the GPL, without Broadcom's express prior
written consent.

:>
 *
 ************************************************************************/

#ifndef __OS_DEFS_H__
#define __OS_DEFS_H__

#include <unistd.h>  /* for getopt */
#include <stdio.h>   /* for snprintf */
#include <stdint.h>  /* for the various integer types */
#include <stdlib.h>  /* for NULL */
#include <string.h>  /* for strlen, strncpy */
#include <ctype.h>   /* for isdigit */
#include <syslog.h>  /* for syslog */
#include <stdarg.h>  /* for va_list */
#include "cms_params.h"

/*!\file os_defs.h
 * \brief Various commonly used, but OS dependent definitions are defined here.
 *
 *  This file is for Linux.
 */

#ifndef NUMBER_TYPES_ALREADY_DEFINED
#define NUMBER_TYPES_ALREADY_DEFINED

/** Unsigned 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 */
typedef uint64_t   UINT64;

/** Signed 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 */
typedef int64_t    SINT64;

/** Unsigned 32 bit integer. */
typedef uint32_t   UINT32;

/** Signed 32 bit integer. */
typedef int32_t    SINT32;

/** Unsigned 16 bit integer. */
typedef uint16_t   UINT16;

/** Signed 16 bit integer. */
typedef int16_t    SINT16;

/** Unsigned 8 bit integer. */
typedef uint8_t    UINT8;

/** Signed 8 bit integer. */
typedef int8_t     SINT8;

#endif /* NUMBER_TYPES_ALREADY_DEFINED */


#ifndef BOOL_TYPE_ALREADY_DEFINED
#define BOOL_TYPE_ALREADY_DEFINED

/**Boolean type; use 1 byte only, possible values are TRUE(1) or FALSE(0) only.
 *
 * TRUE/FALSE defined in cms.h
 */
typedef uint8_t    UBOOL8;

#endif /* BOOL_TYPE_ALREADY_DEFINED */


/** Base64 encoded string representation of binary data.
 *
 * This is to support TR69 data types.
 */
typedef char *     BASE64;


/** Hex encoded string representation of binary data.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 *
 * This is to support TR69 data types.
 */
typedef char *     HEXBINARY;


/** String representation of date and time.
 *
 * This is to support TR69 data types.
 */
typedef char *     DATETIME;


/** Invalid file descriptor number */
#define CMS_INVALID_FD  (-1)


/** Invalid process id.
 *
 * Management entities should not need to use this constant.  It is used
 * by OS dependent code in the OAL layer.  But I put this constant here
 * to make it easier to find.
 */
#define CMS_INVALID_PID   0


/** A number to identify a MdmObject (but not the specific instance of
 *  the object).
 *
 * MdmObjectId's are defined in mdm_oid.h.
 */
typedef UINT16 MdmObjectId;


/** A structure to keep track of instance information.
 *
 * External callers can treat this as an opaque handle.
 * Note the instance array must be of type UINT32 because
 * the instance id's are constantly increasing, so we
 * cannot save space by defining instance to be
 * an array of UINT8's.
 */
typedef struct
{
   UINT8 currentDepth;                     /**< next index in the instance array 
                                            *   to fill.  0 means empty. */
   UINT32 instance[MAX_MDM_INSTANCE_DEPTH];/**< Array of instance id's. */
} InstanceIdStack;



#endif /* __OS_DEFS_H__ */

