/*
 * HND generic pktq operation primitives
 *
 * Copyright (C) 2022, Broadcom. All Rights Reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id: hnd_pktq.h 806948 2022-01-10 10:13:03Z $
 */

#ifndef _hnd_pktq_h_
#define _hnd_pktq_h_

#include <osl_ext.h>

#ifdef __cplusplus
extern "C" {
#endif

/* mutex macros for thread safe */
#ifdef HND_PKTQ_THREAD_SAFE
#define HND_PKTQ_MUTEX_DECL(mutex)		OSL_EXT_MUTEX_DECL(mutex)
#define HND_PKTQ_MUTEX_CREATE(name, mutex)	osl_ext_mutex_create(name, mutex)
#define HND_PKTQ_MUTEX_DELETE(mutex)		osl_ext_mutex_delete(mutex)
#define HND_PKTQ_MUTEX_ACQUIRE(mutex, msec)	osl_ext_mutex_acquire(mutex, msec)
#define HND_PKTQ_MUTEX_RELEASE(mutex)		osl_ext_mutex_release(mutex)
#else
#define HND_PKTQ_MUTEX_DECL(mutex)
#define HND_PKTQ_MUTEX_CREATE(name, mutex)	OSL_EXT_SUCCESS
#define HND_PKTQ_MUTEX_DELETE(mutex)		OSL_EXT_SUCCESS
#define HND_PKTQ_MUTEX_ACQUIRE(mutex, msec)	OSL_EXT_SUCCESS
#define HND_PKTQ_MUTEX_RELEASE(mutex)		OSL_EXT_SUCCESS
#endif /* HND_PKTQ_THREAD_SAFE */

/* osl multi-precedence packet queue */
#define PKTQ_LEN_MAX            0xFFFF  /* Max uint16 65535 packets */
#ifndef PKTQ_LEN_DEFAULT
#define PKTQ_LEN_DEFAULT        256	/* Max 256 packets */
#endif
#ifndef PKTQ_MAX_PREC
#define PKTQ_MAX_PREC           16	/* Maximum precedence levels */
#endif

/**
 * HNDPQP: pktq_prec::stall_count, dequeue_count repurposed
 */
struct pqp_req; /**< HNDPQP: PQP request paired with a PQP managed pktq_prec */

/** Queue for a single precedence level */
typedef struct pktq_prec {
	void *head;     /**< first packet to dequeue */
	void *tail;     /**< last packet to dequeue */
	uint16 n_pkts;       /**< number of queued packets */
	uint16 max_pkts;     /**< maximum number of queued packets */
	uint16 stall_count;    /**< # seconds since no packets are dequeued  */
	uint16 dequeue_count;  /**< # of packets dequeued in last 1 second */
	struct pqp_req * pqp_req; /**< HNDPQP fields for PS and SupprPS Queues */
} pktq_prec_t;

#ifdef PKTQ_LOG
typedef struct {
	uint32 requested;    /**< packets requested to be stored */
	uint32 stored;	     /**< packets stored */
	uint32 saved;	     /**< packets saved,
	                            because a lowest priority queue has given away one packet
	                      */
	uint32 selfsaved;    /**< packets saved,
	                            because an older packet from the same queue has been dropped
	                      */
	uint32 full_dropped; /**< packets dropped,
	                            because pktq is full with higher precedence packets
	                      */
	uint32 dropped;      /**< packets dropped because pktq per that precedence is full */
	uint32 sacrificed;   /**< packets dropped,
	                            in order to save one from a queue of a highest priority
	                      */
	uint32 busy;         /**< packets droped because of hardware/transmission error */
	uint32 retry;        /**< packets re-sent because they were not received */
	uint32 ps_retry;     /**< packets retried again prior to moving power save mode */
	uint32 suppress;     /**< packets which were suppressed and not transmitted */
	uint32 retry_drop;   /**< packets finally dropped after retry limit */
	uint32 max_used;     /**< the high-water mark of the queue utilisation for packets -
						        increases with use ('inverse' of max_avail)
				          */
	uint32 rtsfail;        /**< count of rts attempts that failed to receive cts */
	uint32 acked;   /**< count of packets sent (acked) successfully index by NSS */
	uint64 txrate_succ;    /**< running total of phy rate of packets sent successfully */
	uint64 txrate_main;    /**< running totoal of primary phy rate of all packets */
	uint64 throughput;     /**< actual data transferred successfully */
	uint64 airtime;        /**< cumulative total medium access delay in useconds */
	uint32  _logtimelo;    /**< timestamp of last counter clear  */
	uint32  _logtimehi;
	uint64 txbw_succ;
	uint32 nss[4];
	uint32 mcs[16];
	uint32 sgi;
#ifdef WLSQS
	uint32 sqsv_requested;
	uint16 sqsv_max_used;
#endif
} pktq_counters_t;

#define PKTQ_LOG_COMMON \
	uint32			pps_time;	/**< time spent in ps pretend state */ \
	uint32			_prec_log;

typedef struct {
	PKTQ_LOG_COMMON
	pktq_counters_t*        _prec_cnt[PKTQ_MAX_PREC];     /**< Counters per queue  */
} pktq_log_t;
#else
typedef struct pktq_log pktq_log_t;
#endif /* PKTQ_LOG */

#define PKTQ_COMMON	\
	HND_PKTQ_MUTEX_DECL(mutex)							\
	pktq_log_t *pktqlog;								\
	uint16 num_prec;        /**< number of precedences in use */			\
	uint16 hi_prec;         /**< rapid dequeue hint (>= highest non-empty prec) */	\
	uint16 max_pkts;        /**< max  packets */	\
	uint16 n_pkts_tot;      /**< total (cummulative over all precedences) number of packets */ \
	uint16 v_pkts_tot;

/** multi-priority packet queue */
struct pktq {
	PKTQ_COMMON
	bool common_queue;
	/* q array must be last since # of elements can be either PKTQ_MAX_PREC or 1 */
	struct pktq_prec q[PKTQ_MAX_PREC];
};

/** simple, non-priority packet queue */
struct spktq {
	HND_PKTQ_MUTEX_DECL(mutex)
	struct pktq_prec q;
};

#define PKTQ_PREC_ITER(pq, prec)        for (prec = (pq)->num_prec - 1; prec >= 0; prec--)

/* fn(pkt, arg).  return true if pkt belongs to bsscfg */
typedef bool (*ifpkt_cb_t)(void*, int);

/* pktq_promote_cb(pkt). callback invoked during pkt queue normalization.
 * Callback is reponsible for determining which packets need to be promoted to
 * the head of the queue. E.g. during normalization suppressed packets will
 * get promoted. Packet order within non-promoted section and promoted section
 * are maintained after promotion.
 * Callback handler performs any per packet operation like clearing of tags.
 * see pktq_promote()
 */
typedef bool (*pktq_promote_cb_t)(void*);

/* operations on a specific precedence in packet queue */
#define pktqprec_max_pkts(pq, prec)		((pq)->q[prec].max_pkts)
#define pktqprec_n_pkts(pq, prec)		((pq)->q[prec].n_pkts)
#define pktqprec_empty(pq, prec)		((pq)->q[prec].n_pkts == 0)
#define pktqprec_peek(pq, prec)			((pq)->q[prec].head)
#define pktqprec_peek_tail(pq, prec)	((pq)->q[prec].tail)
#ifdef HND_PKTQ_THREAD_SAFE
extern int pktqprec_avail_pkts(struct pktq *pq, int prec);
extern bool pktqprec_full(struct pktq *pq, int prec);
#else
#define pktqprec_avail_pkts(pq, prec)	((pq)->q[prec].max_pkts - (pq)->q[prec].n_pkts)
#define pktqprec_full(pq, prec)	((pq)->q[prec].n_pkts >= (pq)->q[prec].max_pkts)
#endif	/* HND_PKTQ_THREAD_SAFE */

extern void  pktq_append(struct pktq *pq, int prec, struct spktq *list);
extern void  pktq_prepend(struct pktq *pq, int prec, struct spktq *list);
extern void *pktq_penq(struct pktq *pq, int prec, void *p);
extern void *pktq_penq_head(struct pktq *pq, int prec, void *p);
extern void *pktq_pdeq(struct pktq *pq, int prec);
extern void *pktq_pdeq_prev(struct pktq *pq, int prec, void *prev_p);
extern void *pktq_pdeq_with_fn(struct pktq *pq, int prec, ifpkt_cb_t fn, int arg);
extern void *pktq_pdeq_tail(struct pktq *pq, int prec);
/** Remove a specified packet from its queue */
extern bool pktq_pdel(struct pktq *pq, void *p, int prec);
/** Promote packets to head of queue, using the callback for determining which
 * packets to promote.
 */
extern bool pktq_promote(struct pktq *pq, pktq_promote_cb_t promote_cb);

/* operations on a set of precedences in packet queue */

extern int pktq_mlen(struct pktq *pq, uint prec_bmp);
extern void *pktq_mdeq(struct pktq *pq, uint prec_bmp, int *prec_out);
extern void *pktq_mpeek(struct pktq *pq, uint prec_bmp, int *prec_out);

/* operations on packet queue as a whole */

#define pktq_n_pkts_tot(pq)	((int)(pq)->n_pkts_tot)
#define pktq_max(pq)		((int)(pq)->max_pkts)
#define pktq_empty(pq)		((pq)->n_pkts_tot == 0)
#ifdef HND_PKTQ_THREAD_SAFE
extern int pktq_avail(struct pktq *pq);
extern bool pktq_full(struct pktq *pq);
#else
#define pktq_avail(pq)		((int)((pq)->max_pkts - (pq)->n_pkts_tot))
#define pktq_full(pq)		((pq)->n_pkts_tot >= (pq)->max_pkts)
#endif	/* HND_PKTQ_THREAD_SAFE */

/* operations for single precedence queues */
#define pktenq(pq, p)		pktq_penq((pq), 0, (p))
#define pktenq_head(pq, p)	pktq_penq_head((pq), 0, (p))
#define pktdeq(pq)		pktq_pdeq((pq), 0)
#define pktdeq_tail(pq)		pktq_pdeq_tail((pq), 0)
#define pktqflush(osh, pq, dir)	pktq_pflush(osh, (pq), 0, (dir))
#define pktqinit(pq, max_pkts)	pktq_init((pq), 1, (max_pkts))
#define pktqdeinit(pq)		pktq_deinit((pq))
#define pktqavail(pq)		pktq_avail((pq))
#define pktqfull(pq)		pktq_full((pq))
#define pktqfilter(pq, fltr, fltr_ctx, defer, defer_ctx, flush, flush_ctx) \
	pktq_pfilter((pq), 0, (fltr), (fltr_ctx), (defer), (defer_ctx), (flush), (flush_ctx))

extern bool pktq_init(struct pktq *pq, int num_prec, int max_pkts);

extern void pktq_set_max_plen(struct pktq *pq, int prec, int max_pkts);

/* prec_out may be NULL if caller is not interested in return value */
extern void *pktq_deq(struct pktq *pq, int *prec_out);
extern void *pktq_deq_tail(struct pktq *pq, int *prec_out);
extern void *pktq_peek(struct pktq *pq, int *prec_out);
extern void *pktq_peek_tail(struct pktq *pq, int *prec_out);

/** flush pktq */
extern void pktq_flush(osl_t *osh, struct pktq *pq, bool dir);
/** Empty the queue at particular precedence level */
extern void pktq_pflush(osl_t *osh, struct pktq *pq, int prec, bool dir);

/* operations for simple non-precedence queues */
extern bool spktq_init(struct spktq *spq, int max_pkts);
extern void *spktq_enq(struct spktq *spq, void *p);
extern void spktq_enq_list(struct spktq *spq, struct spktq *list);
extern void *spktq_enq_head(struct spktq *spq, void *p);
extern void spktq_enq_head_list(struct spktq *spq, struct spktq *list);
extern void *spktq_deq(struct spktq *spq);
extern void *spktq_deq_tail(struct spktq *spq);
extern void spktq_flush(osl_t *osh, struct spktq *spq, bool dir);
#ifdef HND_PKTQ_THREAD_SAFE
extern int spktq_avail(struct spktq *spq);
extern bool spktq_full(struct spktq *spq);
extern void spktq_deinit(struct spktq *spq);
extern void pktq_deinit(struct pktq *pq);
#else
#define spktq_avail(spq)	((int)((spq)->q.max_pkts - (spq)->q.n_pkts))
#define spktq_full(spq)		((spq)->q.n_pkts >= (spq)->q.max_pkts)
#define spktq_deinit(spq)	BCM_REFERENCE(spq)
#define pktq_deinit(pq)		BCM_REFERENCE(pq)
#endif	/* HND_PKTQ_THREAD_SAFE */
extern bool spktq_init_list(struct spktq *spq, uint max_pkts,
	void *head, void *tail, uint16 n_pkts);
extern void *spktq_peek(struct spktq *spq);
#define spktq_n_pkts(spq)	((int)(spq)->q.n_pkts)
#define spktq_empty(spq)	((spq)->q.n_pkts == 0)
#define spktq_max(spq)		((int)(spq)->q.max_pkts)
#define spktq_peek_head(pq)	((pq)->q.head)
#define spktq_peek_tail(pq)	((pq)->q.tail)
typedef void (*spktq_cb_t)(void *arg, struct spktq *spq);
extern void spktq_free_register(spktq_cb_t cb, void *arg);
extern void spktq_cb(void *spq);
#define SPKTQFREE	spktq_cb
#ifdef HNDPQP
/* Check for PQP ownership */
extern bool pktq_pqp_owns(struct pktq *pq, int prec);
extern bool pktq_mpqp_owns(struct pktq *pq, uint prec_bmp);

/* PQP packet counts */
#define PKTQ_PKTS_ALL		((uint32) (~0))
extern int pktq_pqp_pkt_cnt(struct pktq *pq, int prec);
extern int pktq_pqp_hbm_cnt(struct pktq *pq, int prec);
extern int pktq_pqp_dbm_cnt(struct pktq *pq, int prec);
extern int pktq_pqp_mlen(struct pktq *pq, uint prec_bmp);

/* #### PQP Page in utilities #### */
/* PQP PGI in priority order */
extern bool pktq_mpqp_pgi(struct pktq *pq, uint prec_bmp);
/* PQP PGI  from a given prec bmp */
extern void pktq_pqp_pgi(struct pktq *pq, int prec,
	int cont_pkts, int fill_pkts);
/* SPKTQ PQP page in */
extern void spktq_pqp_pgi(struct spktq* spq, int cont_pkts, int fill_pkts);

/* #### PQP Page out utilities #### */
extern void spktq_pqp_pgo(struct spktq* spq, int policy,
	void* cb_ctx);
extern void pktq_pqp_pgo(struct pktq *pq, uint prec_bmp,
	int policy, void* cb_ctx);
extern void pktq_prec_pqp_pgo(struct pktq *pq, int prec,
	int policy, void* cb_ctx);
#endif /* HNDPQP */

#ifdef __cplusplus
}
#endif

#endif /* _hnd_pktq_h_ */
