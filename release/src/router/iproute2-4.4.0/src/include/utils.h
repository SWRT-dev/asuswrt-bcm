#ifndef __UTILS_H__
#define __UTILS_H__ 1

#include <sys/types.h>
#include <asm/types.h>
#include <resolv.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libnetlink.h"
#include "ll_map.h"
#include "rtm_map.h"

extern int preferred_family;
extern int human_readable;
extern int use_iec;
extern int show_stats;
extern int show_details;
extern int show_raw;
extern int resolve_hosts;
extern int oneline;
extern int brief;
extern int timestamp;
extern int timestamp_short;
extern const char * _SL_;
extern int max_flush_loops;
extern int batch_mode;
extern bool do_all;

#ifndef IPPROTO_ESP
#define IPPROTO_ESP	50
#endif
#ifndef IPPROTO_AH
#define IPPROTO_AH	51
#endif
#ifndef IPPROTO_COMP
#define IPPROTO_COMP	108
#endif
#ifndef IPSEC_PROTO_ANY
#define IPSEC_PROTO_ANY	255
#endif

#define SPRINT_BSIZE 64
#define SPRINT_BUF(x)	char x[SPRINT_BSIZE]

void incomplete_command(void) __attribute__((noreturn));

#define NEXT_ARG() do { argv++; if (--argc <= 0) incomplete_command(); } while(0)
#define NEXT_ARG_OK() (argc - 1 > 0)
#define NEXT_ARG_FWD() do { argv++; argc--; } while(0)
#define PREV_ARG() do { argv--; argc++; } while(0)

typedef struct
{
	__u16 flags;
	__u16 bytelen;
	__s16 bitlen;
	/* These next two fields match rtvia */
	__u16 family;
	__u32 data[8];
} inet_prefix;

#define PREFIXLEN_SPECIFIED 1

#define DN_MAXADDL 20
#ifndef AF_DECnet
#define AF_DECnet 12
#endif

struct dn_naddr
{
        unsigned short          a_len;
        unsigned char a_addr[DN_MAXADDL];
};

#define IPX_NODE_LEN 6

struct ipx_addr {
	u_int32_t ipx_net;
	u_int8_t  ipx_node[IPX_NODE_LEN];
};

#ifndef AF_MPLS
# define AF_MPLS 28
#endif

/* Maximum number of labels the mpls helpers support */
#define MPLS_MAX_LABELS 8

__u32 get_addr32(const char *name);
int get_addr_1(inet_prefix *dst, const char *arg, int family);
int get_prefix_1(inet_prefix *dst, char *arg, int family);
int get_addr(inet_prefix *dst, const char *arg, int family);
int get_prefix(inet_prefix *dst, char *arg, int family);
int mask2bits(__u32 netmask);
int get_addr_ila(__u64 *val, const char *arg);

int get_integer(int *val, const char *arg, int base);
int get_unsigned(unsigned *val, const char *arg, int base);
int get_time_rtt(unsigned *val, const char *arg, int *raw);
#define get_byte get_u8
#define get_ushort get_u16
#define get_short get_s16
int get_u64(__u64 *val, const char *arg, int base);
int get_u32(__u32 *val, const char *arg, int base);
int get_s32(__s32 *val, const char *arg, int base);
int get_u16(__u16 *val, const char *arg, int base);
int get_s16(__s16 *val, const char *arg, int base);
int get_u8(__u8 *val, const char *arg, int base);
int get_s8(__s8 *val, const char *arg, int base);
int get_addr64(__u64 *ap, const char *cp);

char* hexstring_n2a(const __u8 *str, int len, char *buf, int blen);
__u8* hexstring_a2n(const char *str, __u8 *buf, int blen);
#define ADDR64_BUF_SIZE sizeof("xxxx:xxxx:xxxx:xxxx")
int addr64_n2a(__u64 addr, char *buff, size_t len);

int af_bit_len(int af);
int af_byte_len(int af);

const char *format_host(int af, int len, const void *addr,
			       char *buf, int buflen);
const char *rt_addr_n2a(int af, int len, const void *addr,
			       char *buf, int buflen);

int read_family(const char *name);
const char *family_name(int family);

void missarg(const char *) __attribute__((noreturn));
void invarg(const char *, const char *) __attribute__((noreturn));
void duparg(const char *, const char *) __attribute__((noreturn));
void duparg2(const char *, const char *) __attribute__((noreturn));
int matches(const char *arg, const char *pattern);
int inet_addr_match(const inet_prefix *a, const inet_prefix *b, int bits);

const char *dnet_ntop(int af, const void *addr, char *str, size_t len);
int dnet_pton(int af, const char *src, void *addr);

const char *ipx_ntop(int af, const void *addr, char *str, size_t len);
int ipx_pton(int af, const char *src, void *addr);

const char *mpls_ntop(int af, const void *addr, char *str, size_t len);
int mpls_pton(int af, const char *src, void *addr);

extern int __iproute2_hz_internal;
int __get_hz(void);

static __inline__ int get_hz(void)
{
	if (__iproute2_hz_internal == 0)
		__iproute2_hz_internal = __get_hz();
	return __iproute2_hz_internal;
}

extern int __iproute2_user_hz_internal;
int __get_user_hz(void);

static __inline__ int get_user_hz(void)
{
	if (__iproute2_user_hz_internal == 0)
		__iproute2_user_hz_internal = __get_user_hz();
	return __iproute2_user_hz_internal;
}

static inline __u32 nl_mgrp(__u32 group)
{
	if (group > 31 ) {
		fprintf(stderr, "Use setsockopt for this group %d\n", group);
		exit(-1);
	}
	return group ? (1 << (group - 1)) : 0;
}


int print_timestamp(FILE *fp);
void print_nlmsg_timestamp(FILE *fp, const struct nlmsghdr *n);

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define BUILD_BUG_ON(cond) ((void)sizeof(char[1 - 2 * !!(cond)]))

#ifndef offsetof
# define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif

#ifndef min
# define min(x, y) ({			\
	typeof(x) _min1 = (x);		\
	typeof(y) _min2 = (y);		\
	(void) (&_min1 == &_min2);	\
	_min1 < _min2 ? _min1 : _min2; })
#endif

#ifndef __check_format_string
# define __check_format_string(pos_str, pos_args) \
	__attribute__ ((format (printf, (pos_str), (pos_args))))
#endif

#define htonll(x) ((1==htonl(1)) ? (x) : ((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define ntohll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))

extern int cmdlineno;
ssize_t getcmdline(char **line, size_t *len, FILE *in);
int makeargs(char *line, char *argv[], int maxargs);
int inet_get_addr(const char *src, __u32 *dst, struct in6_addr *dst6);

struct iplink_req;
int iplink_parse(int argc, char **argv, struct iplink_req *req,
		char **name, char **type, char **link, char **dev,
		int *group, int *index);

int do_each_netns(int (*func)(char *nsname, void *arg), void *arg,
		bool show_label);

char *int_to_str(int val, char *buf);

#endif /* __UTILS_H__ */
