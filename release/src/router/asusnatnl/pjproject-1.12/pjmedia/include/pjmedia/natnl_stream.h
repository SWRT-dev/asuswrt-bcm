#ifndef __NATNL_STREAM_H__
#define __NATNL_STREAM_H__

//#include <pjmedia/stream.h>
#include <pjsua-lib/pjsua.h>
#include <pjsua-lib/pjsua_internal.h>
#include <pj/bandwidth.h>

PJ_BEGIN_DECL

typedef struct natnl_stream {
    pjsua_call                     *call;
    pjmedia_transport	        *med_tp;		/* +Roger - Current media transport.   */
	//pjmedia_stream_info *si;
	pj_sockaddr		rem_addr;   /**< Remote RTP address		    */
    pj_pool_t		    *pool;	    /**< Only created if not given  */
	pj_mutex_t		    *rbuff_mutex;
	pj_mutex_t		    *no_ctl_rbuff_mutex;
	recv_buff            rbuff;             //used buffer list
	int					 rbuff_cnt;             //used buffer count
	recv_buff            no_ctl_rbuff;             //used no flow control buffer list
	int					 no_ctl_rbuff_cnt;             //used no flow control buffer count
    pj_mutex_t		    *gcbuff_mutex;
    recv_buff            gcbuff;           //unused buffer list

	pj_mutex_t		    *sbuff_mutex;	// +Roger - Send mutex

	pj_sem_t        *rbuff_sem;
	pj_sem_t        *no_ctl_rbuff_sem;
	pj_grp_lock_t	    *grp_lock;  /**< Group lock.		*/

	//pj_thread_t         *tcp_send_thread;            /**< Thread handle.        */
	//pj_thread_t         *tcp_recv_thread;            /**< Thread handle.        */
	pj_thread_t         *send_thread;       /**< Thread handle.        */
	pj_thread_t         *recv_thread;       /**< Thread handle.        */
	pj_thread_t         *no_ctl_recv_thread;       /**< Thread handle.        */
	pj_thread_t         *sctp_recv_thread;       /**< Thread handle.        */
	pj_uint8_t           thread_quit_flag; /**< Quit signal to thread */
	pj_uint8_t           thread_suspend_flag; /**< Suspend signal to thread */

    //UDT
    int                  udt_sock;
	int                  tnl_type;
	pj_timestamp         last_data_or_ka;     // DEAN, to prevent wrong KA_TIMEOUT event
	pj_timestamp         last_data;     // DEAN, to prevent wrong KA_TIMEOUT event    

	pj_band_t            *rx_band;
	pj_band_t            *tx_band;

	void (*on_call_media_destroy)(int call_id);

} natnl_stream;

PJ_DECL(pj_status_t) pjmedia_natnl_stream_create(pjmedia_endpt *med_endpt,
												 pjsua_call *call,
												pjmedia_stream_info *si,
												natnl_stream **stream);

PJ_DECL(pj_status_t) pjmedia_natnl_stream_destroy( natnl_stream *stream );

PJ_DECL(pj_bool_t) pjmedia_natnl_disabled_flow_control(const void *pkt, int pkt_len);

PJ_DECL(pj_bool_t) pjmedia_natnl_sess_mgr_packet_is_tnl_data(const void *data, int data_len);

PJ_DECL(pj_bool_t) pjmedia_natnl_no_flow_ctl_packet_is_tnl_data(const void *data, int data_len);

PJ_DECL(pj_bool_t) pjmedia_natnl_sctp_packet_is_tnl_data(const void *data, int data_len);

PJ_DECL(pj_bool_t) pjmedia_natnl_udt_packet_is_tnl_data(const void *data, int data_len);

PJ_END_DECL


#endif	/* __NATNL_STREAM_H__ */
