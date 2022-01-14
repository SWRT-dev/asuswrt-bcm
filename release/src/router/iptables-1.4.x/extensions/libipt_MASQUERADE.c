#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <xtables.h>
#include <limits.h> /* INT_MAX in ip_tables.h */
#include <linux/netfilter_ipv4/ip_tables.h>
#include <net/netfilter/nf_nat.h>

enum {
	O_TO_PORTS = 0,
	O_RANDOM,
#ifdef BCM_KF_NETFILTER
	O_MODE,
#endif
	O_PSID,
};

static void MASQUERADE_help(void)
{
	printf(
"MASQUERADE target options:\n"
" --to-ports <port>[-<port>]\n"
"				Port (range) to map to.\n"
" --psid <offset,length,psid>\n"
"				Port Set to map to.\n"
" --random\n"
#ifndef BCM_KF_NETFILTER
"				Randomize source port.\n");
#else
"				Randomize source port.\n"
" --mode <fullcone|symmetric>\n"
"				NAT mode.\n");
#endif
}

static const struct xt_option_entry MASQUERADE_opts[] = {
	{.name = "to-ports", .id = O_TO_PORTS, .type = XTTYPE_STRING},
	{.name = "random", .id = O_RANDOM, .type = XTTYPE_NONE},
#ifdef BCM_KF_NETFILTER
	{.name = "mode", .id = O_MODE, .type = XTTYPE_STRING},
#endif
	{.name = "psid", .id = O_PSID, .type = XTTYPE_STRING},
	XTOPT_TABLEEND,
};

static void MASQUERADE_init(struct xt_entry_target *t)
{
	struct nf_nat_multi_range *mr = (struct nf_nat_multi_range *)t->data;

	/* Actually, it's 0, but it's ignored at the moment. */
	mr->rangesize = 1;
}

/* Parses ports */
static void
parse_ports(const char *arg, struct nf_nat_multi_range *mr)
{
	char *end;
	unsigned int port, maxport;

	mr->range[0].flags |= IP_NAT_RANGE_PROTO_SPECIFIED;

	if (!xtables_strtoui(arg, &end, &port, 0, UINT16_MAX))
		xtables_param_act(XTF_BAD_VALUE, "MASQUERADE", "--to-ports", arg);

	switch (*end) {
	case '\0':
		mr->range[0].min.tcp.port
			= mr->range[0].max.tcp.port
			= htons(port);
		return;
	case '-':
		if (!xtables_strtoui(end + 1, NULL, &maxport, 0, UINT16_MAX))
			break;

		if (maxport < port)
			break;

		mr->range[0].min.tcp.port = htons(port);
		mr->range[0].max.tcp.port = htons(maxport);
		return;
	default:
		break;
	}
	xtables_param_act(XTF_BAD_VALUE, "MASQUERADE", "--to-ports", arg);
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

static void MASQUERADE_parse(struct xt_option_call *cb)
{
	const struct ipt_entry *entry = cb->xt_entry;
	int portok;
	struct nf_nat_multi_range *mr = cb->data;

	if (entry->ip.proto == IPPROTO_TCP
	    || entry->ip.proto == IPPROTO_UDP
	    || entry->ip.proto == IPPROTO_SCTP
	    || entry->ip.proto == IPPROTO_DCCP
	    || entry->ip.proto == IPPROTO_ICMP)
		portok = 1;
	else
		portok = 0;

	/* Borrow this field as mode value. The default is symmetric */
#ifdef BCM_KF_NETFILTER
	mr->range[0].min_ip = 0;
#endif

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_TO_PORTS:
		if (!portok)
			xtables_error(PARAMETER_PROBLEM,
				   "Need TCP, UDP, SCTP or DCCP with port specification");
		parse_ports(cb->arg, mr);
		break;
	case O_RANDOM:
		mr->range[0].flags |=  IP_NAT_RANGE_PROTO_RANDOM;
		break;
#ifdef BCM_KF_NETFILTER
	case O_MODE:
		if (strcasecmp(cb->arg, "fullcone") == 0)
			mr->range[0].min_ip = 1;
		else if (strcasecmp(cb->arg, "symmetric") == 0)
			mr->range[0].min_ip = 0;
		else
			xtables_error(PARAMETER_PROBLEM,
				   "Unknown mode %s", cb->arg);
      break;
#endif
	case O_PSID:
		parse_psid(cb->arg, portok, mr);
		break;
	}
}

static void
MASQUERADE_print(const void *ip, const struct xt_entry_target *target,
                 int numeric)
{
	const struct nf_nat_multi_range *mr = (const void *)target->data;
	const struct nf_nat_range *r = &mr->range[0];

	if (r->flags & IP_NAT_RANGE_PROTO_SPECIFIED) {
		printf(" masq ports: ");
		printf("%hu", ntohs(r->min.tcp.port));
		if (r->max.tcp.port != r->min.tcp.port)
			printf("-%hu", ntohs(r->max.tcp.port));
	}
	if (r->flags & IP_NAT_RANGE_PROTO_PSID) {
		printf(" psid: offset %d, length %d, 0x%x",
			    r->min.psid.offset,
			    r->min.psid.length,
			    r->max.psid.psid);
	}

	if (r->flags & IP_NAT_RANGE_PROTO_RANDOM)
		printf(" random");
#ifdef BCM_KF_NETFILTER
	if (r->min_ip == 1)
		printf(" mode: fullcone ");
#endif
}

static void
MASQUERADE_save(const void *ip, const struct xt_entry_target *target)
{
	const struct nf_nat_multi_range *mr = (const void *)target->data;
	const struct nf_nat_range *r = &mr->range[0];

	if (r->flags & IP_NAT_RANGE_PROTO_SPECIFIED) {
		printf(" --to-ports %hu", ntohs(r->min.tcp.port));
		if (r->max.tcp.port != r->min.tcp.port)
			printf("-%hu", ntohs(r->max.tcp.port));
	}
	if (r->flags & IP_NAT_RANGE_PROTO_PSID) {
		printf(" --psid %d,%d,0x%x",
			    r->min.psid.offset,
			    r->min.psid.length,
			    r->max.psid.psid);
	}

	if (r->flags & IP_NAT_RANGE_PROTO_RANDOM)
		printf(" --random");
#ifdef BCM_KF_NETFILTER
	if (r->min_ip == 1)
		printf(" --mode fullcone ");
#endif
}

static struct xtables_target masquerade_tg_reg = {
	.name		= "MASQUERADE",
	.version	= XTABLES_VERSION,
	.family		= NFPROTO_IPV4,
	.size		= XT_ALIGN(sizeof(struct nf_nat_multi_range)),
	.userspacesize	= XT_ALIGN(sizeof(struct nf_nat_multi_range)),
	.help		= MASQUERADE_help,
	.init		= MASQUERADE_init,
	.x6_parse	= MASQUERADE_parse,
	.print		= MASQUERADE_print,
	.save		= MASQUERADE_save,
	.x6_options	= MASQUERADE_opts,
};

void _init(void)
{
	xtables_register_target(&masquerade_tg_reg);
}
