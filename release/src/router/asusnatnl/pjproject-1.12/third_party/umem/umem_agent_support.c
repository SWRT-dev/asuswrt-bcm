/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 * Portions Copyright 2006-2008 Message Systems, Inc.
 */

/* #pragma ident	"@(#)umem_agent_support.c	1.2	05/06/08 SMI" */

#include "umem_config.h"
#include "umem_base.h"

#define	AGENT_STACK_SIZE	4096

#if 0
char __umem_agent_stack_beg[AGENT_STACK_SIZE];
char *__umem_agent_stack_end = __umem_agent_stack_beg + AGENT_STACK_SIZE;

void
__umem_agent_free_bp(umem_cache_t *cp, void *buf)
{
	extern void _breakpoint(void);			/* inline asm */

	_umem_cache_free(cp, buf);
	_breakpoint();
}
#endif

