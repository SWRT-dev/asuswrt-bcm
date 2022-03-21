/*
 *  Translate error code to error string
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: GPL-2.0
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf     printf
#endif

#if defined(MBEDTLS_ERROR_C) || defined(MBEDTLS_ERROR_STRERROR_DUMMY)
#include "mbedtls/error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#define USAGE \
    "\n usage: strerror <errorcode>\n" \
    "\n where <errorcode> can be a decimal or hexadecimal (starts with 0x or -0x)\n"

#if !defined(MBEDTLS_ERROR_C) && !defined(MBEDTLS_ERROR_STRERROR_DUMMY)
int main( void )
{
    mbedtls_printf("MBEDTLS_ERROR_C and/or MBEDTLS_ERROR_STRERROR_DUMMY not defined.\n");
    return( 0 );
}
#else
int main( int argc, char *argv[] )
{
    long int val;
    char *end = argv[1];

    if( argc != 2 )
    {
        mbedtls_printf( USAGE );
        return( 0 );
    }

    val = strtol( argv[1], &end, 10 );
    if( *end != '\0' )
    {
        val = strtol( argv[1], &end, 16 );
        if( *end != '\0' )
        {
            mbedtls_printf( USAGE );
            return( 0 );
        }
    }
    if( val > 0 )
        val = -val;

    if( val != 0 )
    {
        char error_buf[200];
        mbedtls_strerror( val, error_buf, 200 );
        mbedtls_printf("Last error was: -0x%04x - %s\n\n", (int) -val, error_buf );
    }

#if defined(_WIN32)
    mbedtls_printf( "  + Press Enter to exit this program.\n" );
    fflush( stdout ); getchar();
#endif

    return( val );
}
#endif /* MBEDTLS_ERROR_C */
