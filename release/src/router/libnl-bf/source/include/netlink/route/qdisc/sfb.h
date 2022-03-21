/*
 * netlink/route/sch/sfb.c	SFB Qdisc
 */
/*
 **************************************************************************
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 **************************************************************************
 */

#ifndef NETLINK_SFB_H_
#define NETLINK_SFB_H_

#include <netlink/netlink.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void	rtnl_sfb_set_rehash_interval(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_rehash_interval(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_warmup_time(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_warmup_time(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_max(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_max(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_bin_size(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_bin_size(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_increment(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_increment(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_decrement(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_decrement(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_limit(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_limit(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_penalty_rate(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_penalty_rate(struct rtnl_qdisc *);

extern void	rtnl_sfb_set_penalty_burst(struct rtnl_qdisc *, int);
extern int	rtnl_sfq_get_penalty_burst(struct rtnl_qdisc *);

#ifdef __cplusplus
}
#endif

#endif
