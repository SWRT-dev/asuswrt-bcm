/*
 * Received frame processing for wired interface
 * Copyright (c) 2010, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "utils/includes.h"
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#include "utils/common.h"
#include "radius/radius.h"
#include "wlantest.h"


static struct wlantest_radius * radius_get(struct wlantest *wt, u32 srv,
					   u32 cli)
{
	struct wlantest_radius *r;

	dl_list_for_each(r, &wt->radius, struct wlantest_radius, list) {
		if (r->srv == srv && r->cli == cli)
			return r;
	}

	r = os_zalloc(sizeof(*r));
	if (r == NULL)
		return NULL;

	r->srv = srv;
	r->cli = cli;
	dl_list_add(&wt->radius, &r->list);

	return r;
}


static const char * radius_code_string(u8 code)
{
	switch (code) {
	case RADIUS_CODE_ACCESS_REQUEST:
		return "Access-Request";
	case RADIUS_CODE_ACCESS_ACCEPT:
		return "Access-Accept";
	case RADIUS_CODE_ACCESS_REJECT:
		return "Access-Reject";
	case RADIUS_CODE_ACCOUNTING_REQUEST:
		return "Accounting-Request";
	case RADIUS_CODE_ACCOUNTING_RESPONSE:
		return "Accounting-Response";
	case RADIUS_CODE_ACCESS_CHALLENGE:
		return "Access-Challenge";
	case RADIUS_CODE_STATUS_SERVER:
		return "Status-Server";
	case RADIUS_CODE_STATUS_CLIENT:
		return "Status-Client";
	case RADIUS_CODE_RESERVED:
		return "Reserved";
	default:
		return "?Unknown?";
	}
}


static void process_radius_access_request(struct wlantest *wt, u32 dst,
					  u32 src, const u8 *data, size_t len)
{
	struct radius_msg *msg;
	struct wlantest_radius *r;

	msg = radius_msg_parse(data, len);
	if (msg == NULL) {
		wpa_printf(MSG_DEBUG, "Failed to parse RADIUS Access-Request");
		return;
	}

	r = radius_get(wt, dst, src);
	if (r) {
		radius_msg_free(r->last_req);
		r->last_req = msg;
		return;
	}
	radius_msg_free(msg);
}


static void wlantest_add_pmk(struct wlantest *wt, const u8 *pmk)
{
	struct wlantest_pmk *p;

	p = os_zalloc(sizeof(*p));
	if (p == NULL)
		return;
	os_memcpy(p->pmk, pmk, 32);
	dl_list_add(&wt->pmk, &p->list);
	wpa_hexdump(MSG_INFO, "Add PMK", pmk, 32);
}


static void process_radius_access_accept(struct wlantest *wt, u32 dst, u32 src,
					 const u8 *data, size_t len)
{
	struct radius_msg *msg;
	struct wlantest_radius *r;
	struct radius_ms_mppe_keys *keys;
	struct wlantest_radius_secret *s;

	r = radius_get(wt, src, dst);
	if (r == NULL || r->last_req == NULL) {
		wpa_printf(MSG_DEBUG, "No RADIUS Access-Challenge found for "
			   "decrypting Access-Accept keys");
		return;
	}

	msg = radius_msg_parse(data, len);
	if (msg == NULL) {
		wpa_printf(MSG_DEBUG, "Failed to parse RADIUS Access-Accept");
		return;
	}

	dl_list_for_each(s, &wt->secret, struct wlantest_radius_secret, list) {
		int found = 0;
		keys = radius_msg_get_ms_keys(msg, r->last_req,
					      (u8 *) s->secret,
					      os_strlen(s->secret));
		if (keys && keys->send && keys->recv) {
			u8 pmk[32];
			wpa_hexdump_key(MSG_DEBUG, "MS-MPPE-Send-Key",
					keys->send, keys->send_len);
			wpa_hexdump_key(MSG_DEBUG, "MS-MPPE-Recv-Key",
					keys->recv, keys->recv_len);
			os_memcpy(pmk, keys->recv,
				  keys->recv_len > 32 ? 32 : keys->recv_len);
			if (keys->recv_len < 32) {
				os_memcpy(pmk + keys->recv_len,
					  keys->send,
					  keys->recv_len + keys->send_len > 32
					  ? 32 : 32 - keys->recv_len);
			}
			wlantest_add_pmk(wt, pmk);
			found = 1;
		}

		if (keys) {
			os_free(keys->send);
			os_free(keys->recv);
			os_free(keys);
		}

		if (found)
			break;
	}

	radius_msg_free(msg);
}


static void process_radius(struct wlantest *wt, u32 dst, u16 dport, u32 src,
			   u16 sport, const u8 *data, size_t len)
{
	struct in_addr addr;
	char buf[20];
	const struct radius_hdr *hdr;
	u16 rlen;

	if (len < sizeof(*hdr))
		return;
	hdr = (const struct radius_hdr *) data;
	rlen = be_to_host16(hdr->length);
	if (len < rlen)
		return;
	if (len > rlen)
		len = rlen;

	addr.s_addr = dst;
	snprintf(buf, sizeof(buf), "%s", inet_ntoa(addr));

	addr.s_addr = src;
	wpa_printf(MSG_DEBUG, "RADIUS %s:%u -> %s:%u id=%u %s",
		   inet_ntoa(addr), sport, buf, dport, hdr->identifier,
		   radius_code_string(hdr->code));

	switch (hdr->code) {
	case RADIUS_CODE_ACCESS_REQUEST:
		process_radius_access_request(wt, dst, src, data, len);
		break;
	case RADIUS_CODE_ACCESS_ACCEPT:
		process_radius_access_accept(wt, dst, src, data, len);
		break;
	}
}


static void process_udp(struct wlantest *wt, u32 dst, u32 src,
			const u8 *data, size_t len)
{
	const struct udphdr *udp;
	u16 sport, dport, ulen;
	const u8 *payload;
	size_t plen;

	if (len < sizeof(*udp))
		return;
	udp = (const struct udphdr *) data;
	/* TODO: check UDP checksum */
	sport = be_to_host16(udp->source);
	dport = be_to_host16(udp->dest);
	ulen = be_to_host16(udp->len);

	if (ulen > len)
		return;
	if (len < ulen)
		len = ulen;

	payload = (const u8 *) (udp + 1);
	plen = len - sizeof(*udp);

	if (sport == 1812 || dport == 1812)
		process_radius(wt, dst, dport, src, sport, payload, plen);
}


static void process_ipv4(struct wlantest *wt, const u8 *data, size_t len)
{
	const struct iphdr *ip;
	const u8 *payload;
	size_t plen;
	u16 frag_off, tot_len;

	if (len < sizeof(*ip))
		return;

	ip = (const struct iphdr *) data;
	if (ip->version != 4)
		return;
	if (ip->ihl < 5)
		return;

	/* TODO: check header checksum in ip->check */

	frag_off = be_to_host16(ip->frag_off);
	if (frag_off & 0x1fff) {
		wpa_printf(MSG_EXCESSIVE, "IP fragment reassembly not yet "
			   "supported");
		return;
	}

	tot_len = be_to_host16(ip->tot_len);
	if (tot_len > len)
		return;
	if (tot_len < len)
		len = tot_len;

	payload = data + 4 * ip->ihl;
	plen = len - 4 * ip->ihl;
	if (payload + plen > data + len)
		return;

	switch (ip->protocol) {
	case IPPROTO_UDP:
		process_udp(wt, ip->daddr, ip->saddr, payload, plen);
		break;
	}
}


void wlantest_process_wired(struct wlantest *wt, const u8 *data, size_t len)
{
	const struct ether_header *eth;
	u16 ethertype;

	wpa_hexdump(MSG_EXCESSIVE, "Process wired frame", data, len);

	if (len < sizeof(*eth))
		return;

	eth = (const struct ether_header *) data;
	ethertype = be_to_host16(eth->ether_type);

	switch (ethertype) {
	case ETHERTYPE_IP:
		process_ipv4(wt, data + sizeof(*eth), len - sizeof(*eth));
		break;
	}
}
