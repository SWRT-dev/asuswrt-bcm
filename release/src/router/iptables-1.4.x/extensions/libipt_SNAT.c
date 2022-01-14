#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <xtables.h>
#include <iptables.h>
#include <limits.h> /* INT_MAX in ip_tables.h */
#include <linux/netfilter_ipv4/ip_tables.h>
#include <net/netfilter/nf_nat.h>

enum {
	O_TO_SRC = 0,
	O_RANDOM,
	O_PERSISTENT,
	O_X_TO_SRC,
	O_PSID,
	F_TO_SRC   = 1 << O_TO_SRC,
	F_RANDOM   = 1 << O_RANDOM,
	F_X_TO_SRC = 1 << O_X_TO_SRC,
};

/* Source NAT data consists of a multi-range, indicating where to map
   to. */
struct ipt_natinfo
{
	struct xt_entry_target t;
	struct nf_nat_multi_range mr;
};

static void SNAT_help(void)
{
	printf(
"SNAT target options:\n"
" --to-source [<ipaddr>[-<ipaddr>]][:port[-port]]\n"
"				Address to map source to.\n"
"[--psid <offset,length,psid>]\n"
"				Port Set to map source to.\n"
"[--random] [--persistent]\n");
}

static const struct xt_option_entry SNAT_opts[] = {
	{.name = "to-source", .id = O_TO_SRC, .type = XTTYPE_STRING,
	 .flags = XTOPT_MAND | XTOPT_MULTI},
	{.name = "random", .id = O_RANDOM, .type = XTTYPE_NONE},
	{.name = "persistent", .id = O_PERSISTENT, .type = XTTYPE_NONE},
	{.name = "psid", .id = O_PSID, .type = XTTYPE_STRING},
	XTOPT_TABLEEND,
};

static struct ipt_natinfo *
append_range(struct ipt_natinfo *info, const struct nf_nat_range *range)
{
	unsigned int size;

	/* One rangesize already in struct ipt_natinfo */
	size = XT_ALIGN(sizeof(*info) + info->mr.rangesize * sizeof(*range));

	info = realloc(info, size);
	if (!info)
		xtables_error(OTHER_PROBLEM, "Out of memory\n");

	info->t.u.target_size = size;
	info->mr.range[info->mr.rangesize] = *range;
	info->mr.rangesize++;

	return info;
}

/* Ranges expected in network order. */
static struct xt_entry_target *
parse_to(const char *orig_arg, int portok, struct ipt_natinfo *info)
{
	struct nf_nat_range range;
	char *arg, *colon, *dash, *error;
	const struct in_addr *ip;

	arg = strdup(orig_arg);
	if (arg == NULL)
		xtables_error(RESOURCE_PROBLEM, "strdup");
	memset(&range, 0, sizeof(range));
	colon = strchr(arg, ':');

	if (colon) {
		int port;

		if (!portok)
			xtables_error(PARAMETER_PROBLEM,
				   "Need TCP, UDP, SCTP or DCCP with port specification");

		range.flags |= IP_NAT_RANGE_PROTO_SPECIFIED;

		port = atoi(colon+1);
		if (port <= 0 || port > 65535)
			xtables_error(PARAMETER_PROBLEM,
				   "Port `%s' not valid\n", colon+1);

		error = strchr(colon+1, ':');
		if (error)
			xtables_error(PARAMETER_PROBLEM,
				   "Invalid port:port syntax - use dash\n");

		dash = strchr(colon, '-');
		if (!dash) {
			range.min.tcp.port
				= range.max.tcp.port
				= htons(port);
		} else {
			int maxport;

			maxport = atoi(dash + 1);
			if (maxport <= 0 || maxport > 65535)
				xtables_error(PARAMETER_PROBLEM,
					   "Port `%s' not valid\n", dash+1);
			if (maxport < port)
				/* People are stupid. */
				xtables_error(PARAMETER_PROBLEM,
					   "Port range `%s' funky\n", colon+1);
			range.min.tcp.port = htons(port);
			range.max.tcp.port = htons(maxport);
		}
		/* Starts with a colon? No IP info...*/
		if (colon == arg) {
			free(arg);
			return &(append_range(info, &range)->t);
		}
		*colon = '\0';
	}

	range.flags |= IP_NAT_RANGE_MAP_IPS;
	dash = strchr(arg, '-');
	if (colon && dash && dash > colon)
		dash = NULL;

	if (dash)
		*dash = '\0';

	ip = xtables_numeric_to_ipaddr(arg);
	if (!ip)
		xtables_error(PARAMETER_PROBLEM, "Bad IP address \"%s\"\n",
			   arg);
	range.min_ip = ip->s_addr;
	if (dash) {
		ip = xtables_numeric_to_ipaddr(dash+1);
		if (!ip)
			xtables_error(PARAMETER_PROBLEM, "Bad IP address \"%s\"\n",
				   dash+1);
		range.max_ip = ip->s_addr;
	} else
		range.max_ip = range.min_ip;

	free(arg);
	return &(append_range(info, &range)->t);
}

static void
parse_psid(const char *arg, int portok, struct nf_nat_multi_range *mr)
{
	char *end;
	unsigned int offset, length, psid;

	if (!portok)
		xtables_error(PARAMETER_PROBLEM,
			   "Need TCP, UDP, ICMP, SCTP or DCCP with port specification");

	if (!xtables_strtoui(arg, &end, &offset, 0, 16) || *end++ != ',' ||
	    !xtables_strtoui(end, &end, &length, 0, 16) || *end++ != ',' ||
	    !xtables_strtoui(end, &end, &psid, 0, UINT16_MAX))
		xtables_error(PARAMETER_PROBLEM,
			   "Invalid --psid syntax\n");

	if (offset + length > 16 ||
	    (1 << (16 - length)) - (!!offset << (16 - offset - length)) <= 0)
		xtables_error(PARAMETER_PROBLEM,
			   "Invalid --psid range\n");

	mr->range[0].flags |= IP_NAT_RANGE_PROTO_PSID;
	mr->range[0].min.psid.offset = offset;
	mr->range[0].min.psid.length = length;
	mr->range[0].max.psid.psid = psid & ((1 << length) - 1);
}

static void SNAT_parse(struct xt_option_call *cb)
{
	const struct ipt_entry *entry = cb->xt_entry;
	struct ipt_natinfo *info = (void *)(*cb->target);
	int portok;

	if (entry->ip.proto == IPPROTO_TCP
	    || entry->ip.proto == IPPROTO_UDP
	    || entry->ip.proto == IPPROTO_SCTP
	    || entry->ip.proto == IPPROTO_DCCP
	    || entry->ip.proto == IPPROTO_ICMP)
		portok = 1;
	else
		portok = 0;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_TO_SRC:
		if (cb->xflags & F_X_TO_SRC) {
			if (!kernel_version)
				get_kernel_version();
			if (kernel_version > LINUX_VERSION(2, 6, 10))
				xtables_error(PARAMETER_PROBLEM,
					   "SNAT: Multiple --to-source not supported");
		}
		*cb->target = parse_to(cb->arg, portok, info);
		cb->xflags |= F_X_TO_SRC;
		break;
	case O_PERSISTENT:
		info->mr.range[0].flags |= IP_NAT_RANGE_PERSISTENT;
		break;
	case O_PSID:
		parse_psid(cb->arg, portok, &info->mr);
		break;
	}
}

static void SNAT_fcheck(struct xt_fcheck_call *cb)
{
	static const unsigned int f = F_TO_SRC | F_RANDOM;
	struct nf_nat_multi_range *mr = cb->data;

	if ((cb->xflags & f) == f)
		mr->range[0].flags |= IP_NAT_RANGE_PROTO_RANDOM;
}

static void print_range(const struct nf_nat_range *r)
{
	if (r->flags & IP_NAT_RANGE_MAP_IPS) {
		struct in_addr a;

		a.s_addr = r->min_ip;
		printf("%s", xtables_ipaddr_to_numeric(&a));
		if (r->max_ip != r->min_ip) {
			a.s_addr = r->max_ip;
			printf("-%s", xtables_ipaddr_to_numeric(&a));
		}
	}
	if (r->flags & IP_NAT_RANGE_PROTO_SPECIFIED) {
		printf(":");
		printf("%hu", ntohs(r->min.tcp.port));
		if (r->max.tcp.port != r->min.tcp.port)
			printf("-%hu", ntohs(r->max.tcp.port));
	}
}

static void SNAT_print(const void *ip, const struct xt_entry_target *target,
                       int numeric)
{
	const struct ipt_natinfo *info = (const void *)target;
	unsigned int i = 0;

	printf(" to:");
	for (i = 0; i < info->mr.rangesize; i++) {
		print_range(&info->mr.range[i]);
		if (info->mr.range[i].flags & IP_NAT_RANGE_PROTO_PSID) {
			printf(" psid: offset %d, length %d, 0x%x",
				    info->mr.range[i].min.psid.offset,
				    info->mr.range[i].min.psid.length,
				    info->mr.range[i].max.psid.psid);
		}
		if (info->mr.range[i].flags & IP_NAT_RANGE_PROTO_RANDOM)
			printf(" random");
		if (info->mr.range[i].flags & IP_NAT_RANGE_PERSISTENT)
			printf(" persistent");
	}
}

static void SNAT_save(const void *ip, const struct xt_entry_target *target)
{
	const struct ipt_natinfo *info = (const void *)target;
	unsigned int i = 0;

	for (i = 0; i < info->mr.rangesize; i++) {
		printf(" --to-source ");
		print_range(&info->mr.range[i]);
		if (info->mr.range[i].flags & IP_NAT_RANGE_PROTO_PSID) {
			printf(" --psid %d,%d,0x%x",
				    info->mr.range[i].min.psid.offset,
				    info->mr.range[i].min.psid.length,
				    info->mr.range[i].max.psid.psid);
		}
		if (info->mr.range[i].flags & IP_NAT_RANGE_PROTO_RANDOM)
			printf(" --random");
		if (info->mr.range[i].flags & IP_NAT_RANGE_PERSISTENT)
			printf(" --persistent");
	}
}

static struct xtables_target snat_tg_reg = {
	.name		= "SNAT",
	.version	= XTABLES_VERSION,
	.family		= NFPROTO_IPV4,
	.size		= XT_ALIGN(sizeof(struct nf_nat_multi_range)),
	.userspacesize	= XT_ALIGN(sizeof(struct nf_nat_multi_range)),
	.help		= SNAT_help,
	.x6_parse	= SNAT_parse,
	.x6_fcheck	= SNAT_fcheck,
	.print		= SNAT_print,
	.save		= SNAT_save,
	.x6_options	= SNAT_opts,
};

void _init(void)
{
	xtables_register_target(&snat_tg_reg);
}
