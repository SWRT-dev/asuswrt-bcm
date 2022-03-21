/*
 *  Generic cache management functions. Everything is arch-specific,  
 *  but this header exists to make sure the defines/functions can be
 *  used in a generic way.
 *
 *  2000-11-13  Arjan van de Ven   <arjan@fenrus.demon.nl>
 *
 */

#ifndef _LINUX_PREFETCH_H
#define _LINUX_PREFETCH_H

#include <linux/types.h>
#include <asm/processor.h>
#include <asm/cache.h>

/*
	prefetch(x) attempts to pre-emptively get the memory pointed to
	by address "x" into the CPU L1 cache. 
	prefetch(x) should not cause any kind of exception, prefetch(0) is
	specifically ok.

	prefetch() should be defined by the architecture, if not, the 
	#define below provides a no-op define.	
	
	There are 3 prefetch() macros:
	
	prefetch(x)  	- prefetches the cacheline at "x" for read
	prefetchw(x)	- prefetches the cacheline at "x" for write
	spin_lock_prefetch(x) - prefetches the spinlock *x for taking
	
	there is also PREFETCH_STRIDE which is the architecure-preferred 
	"lookahead" size for prefetching streamed operations.
	
*/

#ifndef ARCH_HAS_PREFETCH
#define prefetch(x) __builtin_prefetch(x)
#endif

#ifndef ARCH_HAS_PREFETCHW
#define prefetchw(x) __builtin_prefetch(x,1)
#endif

#ifndef ARCH_HAS_SPINLOCK_PREFETCH
#define spin_lock_prefetch(x) prefetchw(x)
#endif

#ifndef PREFETCH_STRIDE
#define PREFETCH_STRIDE (4*L1_CACHE_BYTES)
#endif

static inline void prefetch_range(void *addr, size_t len)
{
#ifdef ARCH_HAS_PREFETCH
	char *cp;
	char *end = addr + len;

	for (cp = addr; cp < end; cp += PREFETCH_STRIDE)
		prefetch(cp);
#endif
}

#if defined(CONFIG_BCM_KF_ARM_BCM963XX) && defined(CONFIG_BCM_KF_ARM_PLD)
#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
static inline void bcm_prefetch(const void * addr, const int cachelines)
{
    switch (cachelines) {
        case 4: __asm__ __volatile__("pld\t%a0" : : "p"(addr + ((0x1 << CONFIG_ARM_L1_CACHE_SHIFT) * 3)) : "cc");
        case 3: __asm__ __volatile__("pld\t%a0" : : "p"(addr + ((0x1 << CONFIG_ARM_L1_CACHE_SHIFT) * 2)) : "cc");
        case 2: __asm__ __volatile__("pld\t%a0" : : "p"(addr + ((0x1 << CONFIG_ARM_L1_CACHE_SHIFT) * 1)) : "cc");
        case 1: __asm__ __volatile__("pld\t%a0" : : "p"(addr + ((0x1 << CONFIG_ARM_L1_CACHE_SHIFT) * 0)) : "cc");
    }
}
#else
static inline void bcm_prefetch(const void * addr, const int cachelines) { }
#endif /* CONFIG_BCM963138 || defined(CONFIG_BCM963148) */
#endif
#endif
