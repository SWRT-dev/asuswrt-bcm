/* Shared library add-on to iptables to add TOS target support. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include <iptables.h>
#include <xtables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_TOS.h>

struct tosinfo {
	struct ipt_entry_target t;
	struct ipt_tos_target_info tos;
};

/* TOS names and values. */
static
struct TOS_value
{
	unsigned char TOS;
	const char *name;
} TOS_values[] = {
	{ IPTOS_LOWDELAY,    "Minimize-Delay" },
	{ IPTOS_THROUGHPUT,  "Maximize-Throughput" },
	{ IPTOS_RELIABILITY, "Maximize-Reliability" },
	{ IPTOS_MINCOST,     "Minimize-Cost" },
	{ IPTOS_NORMALSVC,   "Normal-Service" },
};

/* Function which prints out usage message. */
static void
help(void)
{
	unsigned int i;

	printf(
"TOS target v%s options:\n"
"  --set-tos value                   Set Type of Service field to one of the\n"
"                                following numeric or descriptive values:\n",
XTABLES_VERSION);

	for (i = 0; i < sizeof(TOS_values)/sizeof(struct TOS_value);i++)
		printf("                                     %s %u (0x%02x)\n",
		       TOS_values[i].name,
                       TOS_values[i].TOS,
                       TOS_values[i].TOS);
	fputc('\n', stdout);
}

static struct option opts[] = {
	{ .name = "set-tos", .has_arg = true, .val = '1' },
	XT_GETOPT_TABLEEND
};

/* Initialize the target. */
static void
init(struct xt_entry_target *t)
{
}

static void
parse_tos(const char *s, struct ipt_tos_target_info *info)
{
	unsigned int i, tos;

	if (xtables_strtoui(s, NULL, &tos, 0, UINT8_MAX)) {
		if (tos == IPTOS_LOWDELAY
		    || tos == IPTOS_THROUGHPUT
		    || tos == IPTOS_RELIABILITY
		    || tos == IPTOS_MINCOST
		    || tos == IPTOS_NORMALSVC) {
		    	info->tos = (u_int8_t )tos;
		    	return;
		}
	} else {
		for (i = 0; i<sizeof(TOS_values)/sizeof(struct TOS_value); i++)
			if (strcasecmp(s,TOS_values[i].name) == 0) {
				info->tos = TOS_values[i].TOS;
				return;
			}
	}
	xtables_error(PARAMETER_PROBLEM, "Bad TOS value `%s'", s);
}

/* Function which parses command options; returns true if it
   ate an option */
static int
parse(int c, char **argv, int invert, unsigned int *flags,
      const void *entry,
      struct xt_entry_target **target)
{
	struct ipt_tos_target_info *tosinfo
		= (struct ipt_tos_target_info *)(*target)->data;

	switch (c) {
	case '1':
		if (*flags)
			xtables_error(PARAMETER_PROBLEM,
			           "TOS target: Cant specify --set-tos twice");
		parse_tos(optarg, tosinfo);
		*flags = 1;
		break;

	default:
		return 0;
	}

	return 1;
}

static void
final_check(unsigned int flags)
{
	if (!flags)
		xtables_error(PARAMETER_PROBLEM,
		           "TOS target: Parameter --set-tos is required");
}

static void
print_tos(u_int8_t tos, int numeric)
{
	unsigned int i;

	if (!numeric) {
		for (i = 0; i<sizeof(TOS_values)/sizeof(struct TOS_value); i++)
			if (TOS_values[i].TOS == tos) {
				printf("%s ", TOS_values[i].name);
				return;
			}
	}
	printf("0x%02x ", tos);
}

/* Prints out the targinfo. */
static void
print(const void *ip,
      const struct xt_entry_target *target,
      int numeric)
{
	const struct ipt_tos_target_info *tosinfo =
		(const struct ipt_tos_target_info *)target->data;
	printf("TOS set ");
	print_tos(tosinfo->tos, numeric);
}

/* Saves the union ipt_targinfo in parsable form to stdout. */
static void
save(const void *ip, const struct xt_entry_target *target)
{
	const struct ipt_tos_target_info *tosinfo =
		(const struct ipt_tos_target_info *)target->data;

	printf("--set-tos 0x%02x ", tosinfo->tos);
}

static struct xtables_target tos = {
	.name		= "TOS",
	.version	= XTABLES_VERSION,
	.size		= XT_ALIGN(sizeof(struct ipt_tos_target_info)),
	.userspacesize	= XT_ALIGN(sizeof(struct ipt_tos_target_info)),
	.help		= &help,
	.init		= &init,
	.parse		= &parse,
	.final_check	= &final_check,
	.print		= &print,
	.save		= &save,
	.extra_opts	= opts
};

void _init(void)
{
	xtables_register_target(&tos);
}
