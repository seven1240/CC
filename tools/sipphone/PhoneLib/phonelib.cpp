/*
 * Copyright 2002-2014 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      CC/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "phonelib.h"
#include <pjlib.h>
#include <pjlib-util.h>
#include <pjnath.h>
#include <pjsip.h>
#include <pjsip_ua.h>
#include <pjsip_simple.h>
#include <pjsua-lib/pjsua.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
#include <pjsua-lib/pjsua.h>

#define THIS_FILE	"phonelib.cpp"
#define NO_LIMIT	(int)0x7FFFFFFF

/* Ringtones		    US	       UK  */
#define RINGBACK_FREQ1	    440	    /* 400 */
#define RINGBACK_FREQ2	    480	    /* 450 */
#define RINGBACK_ON	    2000    /* 400 */
#define RINGBACK_OFF	    4000    /* 200 */
#define RINGBACK_CNT	    1	    /* 2   */
#define RINGBACK_INTERVAL   4000    /* 2000 */

#define RING_FREQ1	    800
#define RING_FREQ2	    640
#define RING_ON		    200
#define RING_OFF	    100
#define RING_CNT	    3
#define RING_INTERVAL	    3000

#define MAX_AUD_DEV 15

//呼叫相关数据
struct call_data
{
	pj_timer_entry	    timer;
	pj_bool_t		    ringback_on;
	pj_bool_t		    ring_on;
};

//程序相关数据
static struct app_config
{
	pjsua_config	    cfg;
	pjsua_logging_config    log_cfg;
	pjsua_media_config	    media_cfg;
	pj_bool_t		    no_refersub;
	pj_bool_t		    ipv6;
	pj_bool_t		    enable_qos;
	pj_bool_t		    no_tcp;
	pj_bool_t		    no_udp;
	pj_bool_t		    use_tls;
	pjsua_transport_config  udp_cfg;
	pjsua_transport_config  rtp_cfg;
	pjsip_redirect_op	    redir_op;

	unsigned		    acc_cnt;
	pjsua_acc_config	    acc_cfg[PJSUA_MAX_ACC];

	unsigned		    buddy_cnt;
	pjsua_buddy_config	    buddy_cfg[PJSUA_MAX_BUDDIES];

	struct call_data	    call_data[PJSUA_MAX_CALLS];

	pj_pool_t		   *pool;
 

	unsigned		    codec_cnt;
	pj_str_t		    codec_arg[32];
	unsigned		    codec_dis_cnt;
	pj_str_t                codec_dis[32];
	pj_bool_t		    null_audio;
	unsigned		    wav_count;
	pj_str_t		    wav_files[32];
	unsigned		    tone_count;
	pjmedia_tone_desc	    tones[32];
	pjsua_conf_port_id	    tone_slots[32];
	pjsua_player_id	    wav_id;
	pjsua_conf_port_id	    wav_port;
	pj_bool_t		    auto_play;
	pj_bool_t		    auto_play_hangup;
	pj_timer_entry	    auto_hangup_timer;
	pj_bool_t		    auto_loop;
	pj_bool_t		    auto_conf;
	pj_str_t		    rec_file;
	pj_bool_t		    auto_rec;
	pjsua_recorder_id	    rec_id;
	pjsua_conf_port_id	    rec_port;
	unsigned		    auto_answer;
	unsigned		    duration;

#ifdef STEREO_DEMO
	pjmedia_snd_port	   *snd;
	pjmedia_port	   *sc, *sc_ch1;
	pjsua_conf_port_id	    sc_ch1_slot;
#endif

	float		    mic_level,speaker_level;

	int			    capture_dev, playback_dev;
	unsigned		    capture_lat, playback_lat;

	pj_bool_t		    no_tones;
	int			    ringback_slot;
	int			    ringback_cnt;
	pjmedia_port	   *ringback_port;
	int			    ring_slot;
	int			    ring_cnt;
	pjmedia_port	   *ring_port;

} app_config;


//static pjsua_acc_id	current_acc;
#define current_acc	pjsua_acc_get_default()
static pjsua_call_id	current_call = PJSUA_INVALID_ID;
static char some_buf[1024 * 3];

#ifdef STEREO_DEMO
static void stereo_demo();
#endif

static pj_status_t create_ipv6_media_transports(void);
pj_status_t app_destroy(void);
static void ringback_start(pjsua_call_id call_id);
static void ring_start(pjsua_call_id call_id);
static void ring_stop(pjsua_call_id call_id);
pj_bool_t 	app_restart;
pj_log_func     *log_cb = NULL;


//IOS 相关代码，保留
#if (defined(PJ_IPHONE_OS_HAS_MULTITASKING_SUPPORT) && \
	PJ_IPHONE_OS_HAS_MULTITASKING_SUPPORT!=0) || \
	defined(__IPHONE_4_0)
void keepAliveFunction(int timeout)
{
	int i;
	for (i=0; i<(int)pjsua_acc_get_count(); ++i) {
		if (!pjsua_acc_is_valid(i))
			continue;

		if (app_config.acc_cfg[i].reg_timeout < timeout)
			app_config.acc_cfg[i].reg_timeout = timeout;
		pjsua_acc_set_registration(i, PJ_TRUE);
	}
}
#endif

//默认设置
static void default_config(struct app_config *cfg)
{
	char tmp[80];
	unsigned i;

	pjsua_config_default(&cfg->cfg);
	//  pj_ansi_sprintf(tmp, "PJSUA v%s %s", pj_get_version(),
	//	    pj_get_sys_info()->info.ptr);

	pj_ansi_sprintf(tmp, "PJSUA v%s %s", pj_get_version(),
		"Windows");//baidu
	pj_strdup2_with_null(app_config.pool, &cfg->cfg.user_agent, tmp);

	pjsua_logging_config_default(&cfg->log_cfg);
	pjsua_media_config_default(&cfg->media_cfg);
	pjsua_transport_config_default(&cfg->udp_cfg);
	cfg->udp_cfg.port = 5060;
	pjsua_transport_config_default(&cfg->rtp_cfg);
	cfg->rtp_cfg.port = 4000;
	cfg->redir_op = PJSIP_REDIRECT_ACCEPT;
	cfg->duration = NO_LIMIT;
	cfg->wav_id = PJSUA_INVALID_ID;
	cfg->rec_id = PJSUA_INVALID_ID;
	cfg->wav_port = PJSUA_INVALID_ID;
	cfg->rec_port = PJSUA_INVALID_ID;
	cfg->mic_level = cfg->speaker_level = 1.0;
	cfg->capture_dev = PJSUA_INVALID_ID;
	cfg->playback_dev = PJSUA_INVALID_ID;
	cfg->capture_lat = PJMEDIA_SND_DEFAULT_REC_LATENCY;
	cfg->playback_lat = PJMEDIA_SND_DEFAULT_PLAY_LATENCY;
	cfg->ringback_slot = PJSUA_INVALID_ID;
	cfg->ring_slot = PJSUA_INVALID_ID;

	for (i=0; i<PJ_ARRAY_SIZE(cfg->acc_cfg); ++i)
		pjsua_acc_config_default(&cfg->acc_cfg[i]);

	for (i=0; i<PJ_ARRAY_SIZE(cfg->buddy_cfg); ++i)
		pjsua_buddy_config_default(&cfg->buddy_cfg[i]);
}
 
// Print log of call states. Since call states may be too long for logger,
// printing it is a bit tricky, it should be printed part by part as long 
// as the logger can accept.

static void log_call_dump(int call_id) 
{
	unsigned call_dump_len;
	unsigned part_len;
	unsigned part_idx;
	unsigned log_decor;

	pjsua_call_dump(call_id, PJ_TRUE, some_buf, 
		sizeof(some_buf), "  ");
	call_dump_len = strlen(some_buf);

	log_decor = pj_log_get_decor();
	pj_log_set_decor(log_decor & ~(PJ_LOG_HAS_NEWLINE | PJ_LOG_HAS_CR));
	PJ_LOG(3,(THIS_FILE, "\n"));
	pj_log_set_decor(0);

	part_idx = 0;
	part_len = PJ_LOG_MAX_SIZE-80;
	while (part_idx < call_dump_len) {
		char p_orig, *p;

		p = &some_buf[part_idx];
		if (part_idx + part_len > call_dump_len)
			part_len = call_dump_len - part_idx;
		p_orig = p[part_len];
		p[part_len] = '\0';
		PJ_LOG(3,(THIS_FILE, "%s", p));
		p[part_len] = p_orig;
		part_idx += part_len;
	}
	pj_log_set_decor(log_decor);
}

/*****************************************************************************
* Console application
*/

static void ringback_start(pjsua_call_id call_id)
{
	if (app_config.no_tones)
		return;

	if (app_config.call_data[call_id].ringback_on)
		return;

	app_config.call_data[call_id].ringback_on = PJ_TRUE;

	if (++app_config.ringback_cnt==1 && 
		app_config.ringback_slot!=PJSUA_INVALID_ID) 
	{
		pjsua_conf_connect(app_config.ringback_slot, 0);
	}
}

static void ring_stop(pjsua_call_id call_id)
{
	if (app_config.no_tones)
		return;

	if (app_config.call_data[call_id].ringback_on) {
		app_config.call_data[call_id].ringback_on = PJ_FALSE;

		pj_assert(app_config.ringback_cnt>0);
		if (--app_config.ringback_cnt == 0 && 
			app_config.ringback_slot!=PJSUA_INVALID_ID) 
		{
			pjsua_conf_disconnect(app_config.ringback_slot, 0);
			pjmedia_tonegen_rewind(app_config.ringback_port);
		}
	}

	if (app_config.call_data[call_id].ring_on) {
		app_config.call_data[call_id].ring_on = PJ_FALSE;

		pj_assert(app_config.ring_cnt>0);
		if (--app_config.ring_cnt == 0 && 
			app_config.ring_slot!=PJSUA_INVALID_ID) 
		{
			pjsua_conf_disconnect(app_config.ring_slot, 0);
			pjmedia_tonegen_rewind(app_config.ring_port);
		}
	}
}

static void ring_start(pjsua_call_id call_id)
{
	if (app_config.no_tones)
		return;

	if (app_config.call_data[call_id].ring_on)
		return;

	app_config.call_data[call_id].ring_on = PJ_TRUE;

	if (++app_config.ring_cnt==1 && 
		app_config.ring_slot!=PJSUA_INVALID_ID) 
	{
		pjsua_conf_connect(app_config.ring_slot, 0);
	}
}

#ifdef HAVE_MULTIPART_TEST
 
static void add_multipart(pjsua_msg_data *msg_data)
{
	static pjsip_multipart_part *alt_part;

	if (!alt_part) {
		pj_str_t type, subtype, content;

		alt_part = pjsip_multipart_create_part(app_config.pool);

		type = pj_str("text");
		subtype = pj_str("plain");
		content = pj_str("Sample text body of a multipart bodies");
		alt_part->body = pjsip_msg_body_create(app_config.pool, &type,
			&subtype, &content);
	}

	msg_data->multipart_ctype.type = pj_str("multipart");
	msg_data->multipart_ctype.subtype = pj_str("mixed");
	pj_list_push_back(&msg_data->multipart_parts, alt_part);
}
#  define TEST_MULTIPART(msg_data)	add_multipart(msg_data)
#else
#  define TEST_MULTIPART(msg_data)
#endif

// Find next call when current call is disconnected or when user
// press ']'
static pj_bool_t find_next_call(void)
{
	int i, max;

	max = pjsua_call_get_max_count();
	for (i=current_call+1; i<max; ++i) {
		if (pjsua_call_is_active(i)) {
			current_call = i;
			return PJ_TRUE;
		}
	}

	for (i=0; i<current_call; ++i) {
		if (pjsua_call_is_active(i)) {
			current_call = i;
			return PJ_TRUE;
		}
	}

	current_call = PJSUA_INVALID_ID;
	return PJ_FALSE;
}

//Find previous call when user press '['
static pj_bool_t find_prev_call(void)
{
	int i, max;

	max = pjsua_call_get_max_count();
	for (i=current_call-1; i>=0; --i) {
		if (pjsua_call_is_active(i)) {
			current_call = i;
			return PJ_TRUE;
		}
	}

	for (i=max-1; i>current_call; --i) {
		if (pjsua_call_is_active(i)) {
			current_call = i;
			return PJ_TRUE;
		}
	}

	current_call = PJSUA_INVALID_ID;
	return PJ_FALSE;
}
 
// Print buddy list.
static void print_buddy_list(void)
{
	pjsua_buddy_id ids[64];
	int i;
	unsigned count = PJ_ARRAY_SIZE(ids);

	puts("Buddy list:");

	pjsua_enum_buddies(ids, &count);

	if (count == 0)
		puts(" -none-");
	else {
		for (i=0; i<(int)count; ++i) {
			pjsua_buddy_info info;

			if (pjsua_buddy_get_info(ids[i], &info) != PJ_SUCCESS)
				continue;

			printf(" [%2d] <%.*s>  %.*s\n", 
				ids[i]+1, 
				(int)info.status_text.slen,
				info.status_text.ptr, 
				(int)info.uri.slen,
				info.uri.ptr);
		}
	}
	puts("");
}

// Print account status.
static void print_acc_status(int acc_id)
{
	char buf[80];
	pjsua_acc_info info;

	pjsua_acc_get_info(acc_id, &info);

	if (!info.has_registration) {
		pj_ansi_snprintf(buf, sizeof(buf), "%.*s", 
			(int)info.status_text.slen,
			info.status_text.ptr);

	} else {
		pj_ansi_snprintf(buf, sizeof(buf),
			"%d/%.*s (expires=%d)",
			info.status,
			(int)info.status_text.slen,
			info.status_text.ptr,
			info.expires);

	}

	printf(" %c[%2d] %.*s: %s\n", (acc_id==current_acc?'*':' '),
		acc_id,  (int)info.acc_uri.slen, info.acc_uri.ptr, buf);
	printf("       Online status: %.*s\n", 
		(int)info.online_status_text.slen,
		info.online_status_text.ptr);
}

// Playfile done notification, set timer to hangup calls  
pj_status_t on_playfile_done(pjmedia_port *port, void *usr_data)
{
	pj_time_val delay;

	PJ_UNUSED_ARG(port);
	PJ_UNUSED_ARG(usr_data);

	// Just rewind WAV when it is played outside of call 
	if (pjsua_call_get_count() == 0) {
		pjsua_player_set_pos(app_config.wav_id, 0);
		return PJ_SUCCESS;
	}

	// Timer is already active 
	if (app_config.auto_hangup_timer.id == 1)
		return PJ_SUCCESS;

	app_config.auto_hangup_timer.id = 1;
	delay.sec = 0;
	delay.msec = 200;	//Give 200 ms before hangup  
	pjsip_endpt_schedule_timer(pjsua_get_pjsip_endpt(), 
		&app_config.auto_hangup_timer, 
		&delay);

	return PJ_SUCCESS;
}

// Auto hangup timer callback  
static void hangup_timeout_callback(pj_timer_heap_t *timer_heap,
struct pj_timer_entry *entry)
{
	PJ_UNUSED_ARG(timer_heap);
	PJ_UNUSED_ARG(entry);

	app_config.auto_hangup_timer.id = 0;
	pjsua_call_hangup_all();
}

// List the ports in conference bridge
static void conf_list(void)
{
	unsigned i, count;
	pjsua_conf_port_id id[PJSUA_MAX_CALLS];

	printf("Conference ports:\n");

	count = PJ_ARRAY_SIZE(id);
	pjsua_enum_conf_ports(id, &count);

	for (i=0; i<count; ++i) {
		char txlist[PJSUA_MAX_CALLS*4+10];
		unsigned j;
		pjsua_conf_port_info info;

		pjsua_conf_get_port_info(id[i], &info);

		txlist[0] = '\0';
		for (j=0; j<info.listener_cnt; ++j) {
			char s[10];
			pj_ansi_sprintf(s, "#%d ", info.listeners[j]);
			pj_ansi_strcat(txlist, s);
		}
		printf("Port #%02d[%2dKHz/%dms/%d] %20.*s  transmitting to: %s\n", 
			info.slot_id, 
			info.clock_rate/1000,
			info.samples_per_frame*1000/info.channel_count/info.clock_rate,
			info.channel_count,
			(int)info.name.slen, 
			info.name.ptr,
			txlist);

	}
	puts("");
}

//	Send arbitrary request to remote host
static void send_request(char *cstr_method, const pj_str_t *dst_uri)
{
	pj_str_t str_method;
	pjsip_method method;
	pjsip_tx_data *tdata;
	pjsip_endpoint *endpt;
	pj_status_t status;

	endpt = pjsua_get_pjsip_endpt();

	str_method = pj_str(cstr_method);
	pjsip_method_init_np(&method, &str_method);

	status = pjsua_acc_create_request(current_acc, &method, dst_uri, &tdata);

	status = pjsip_endpt_send_request(endpt, tdata, -1, NULL, NULL);
	if (status != PJ_SUCCESS) {
		pjsua_perror(THIS_FILE, "Unable to send request", status);
		return;
	}
}

// Change extended online status.
static void change_online_status(void)
{
	char menuin[32];
	pj_bool_t online_status;
	pjrpid_element elem;
	int i, choice;

	enum {
		AVAILABLE, BUSY, OTP, IDLE, AWAY, BRB, OFFLINE, OPT_MAX
	};

	struct opt {
		int id;
		char *name;
	} opts[] = {
		{ AVAILABLE, "Available" },
		{ BUSY, "Busy"},
		{ OTP, "On the phone"},
		{ IDLE, "Idle"},
		{ AWAY, "Away"},
		{ BRB, "Be right back"},
		{ OFFLINE, "Offline"}
	};

	printf("\n"
		"Choices:\n");
	for (i=0; i<PJ_ARRAY_SIZE(opts); ++i) {
		printf("  %d  %s\n", opts[i].id+1, opts[i].name);
	}

	//if (!simple_input("Select status", menuin, sizeof(menuin)))
	//return;
	strcpy(menuin,"BUSY");

	choice = atoi(menuin) - 1;
	if (choice < 0 || choice >= OPT_MAX) {
		puts("Invalid selection");
		return;
	}

	pj_bzero(&elem, sizeof(elem));
	elem.type = PJRPID_ELEMENT_TYPE_PERSON;

	online_status = PJ_TRUE;

	switch (choice) {
case AVAILABLE:
	break;
case BUSY:
	elem.activity = PJRPID_ACTIVITY_BUSY;
	elem.note = pj_str("Busy");
	break;
case OTP:
	elem.activity = PJRPID_ACTIVITY_BUSY;
	elem.note = pj_str("On the phone");
	break;
case IDLE:
	elem.activity = PJRPID_ACTIVITY_UNKNOWN;
	elem.note = pj_str("Idle");
	break;
case AWAY:
	elem.activity = PJRPID_ACTIVITY_AWAY;
	elem.note = pj_str("Away");
	break;
case BRB:
	elem.activity = PJRPID_ACTIVITY_UNKNOWN;
	elem.note = pj_str("Be right back");
	break;
case OFFLINE:
	online_status = PJ_FALSE;
	break;
	}

	pjsua_acc_set_online_status2(current_acc, online_status, &elem);
}

/////////////////////////////////////////////////////////
// A simple module to handle otherwise unhandled request. We will register
// this with the lowest priority.
//
/////////////////////////////////////////////////////////
static pj_bool_t default_mod_on_rx_request(pjsip_rx_data *rdata)
{
	pjsip_tx_data *tdata;
	pjsip_status_code status_code;
	pj_status_t status;

	// Don't respond to ACK!
	if (pjsip_method_cmp(&rdata->msg_info.msg->line.req.method, 
		&pjsip_ack_method) == 0)
		return PJ_TRUE;

	// Create basic response.
	if (pjsip_method_cmp(&rdata->msg_info.msg->line.req.method, 
		&pjsip_notify_method) == 0)
	{
		// Unsolicited NOTIFY's, send with Bad Request 
		status_code = PJSIP_SC_BAD_REQUEST;
	} else {
		// Probably unknown method 
		status_code = PJSIP_SC_METHOD_NOT_ALLOWED;
	}
	status = pjsip_endpt_create_response(pjsua_get_pjsip_endpt(), 
		rdata, status_code, 
		NULL, &tdata);
	if (status != PJ_SUCCESS) {
		pjsua_perror(THIS_FILE, "Unable to create response", status);
		return PJ_TRUE;
	}

	// Add Allow if we're responding with 405 
	if (status_code == PJSIP_SC_METHOD_NOT_ALLOWED) {
		const pjsip_hdr *cap_hdr;
		cap_hdr = pjsip_endpt_get_capability(pjsua_get_pjsip_endpt(), 
			PJSIP_H_ALLOW, NULL);
		if (cap_hdr) {
			pjsip_msg_add_hdr(tdata->msg, (pjsip_hdr*)(pjsip_hdr_clone(tdata->pool, 
				cap_hdr)));
		}
	}

	// Add User-Agent header 
	{
		pj_str_t user_agent;
		char tmp[80];
		const pj_str_t USER_AGENT = { "User-Agent", 10};
		pjsip_hdr *h;

		pj_ansi_snprintf(tmp, sizeof(tmp), "PJSUA v%s/%s", 
			pj_get_version(), PJ_OS_NAME);
		pj_strdup2_with_null(tdata->pool, &user_agent, tmp);

		h = (pjsip_hdr*) pjsip_generic_string_hdr_create(tdata->pool,
			&USER_AGENT,
			&user_agent);
		pjsip_msg_add_hdr(tdata->msg, h);
	}

	pjsip_endpt_send_response2(pjsua_get_pjsip_endpt(), rdata, tdata, 
		NULL, NULL);

	return PJ_TRUE;
}


//The module instance. 
static pjsip_module mod_default_handler = 
{
	NULL, NULL,	// prev, next.
	{ "mod-default-handler", 19 },	//Name 
	-1,					//Id 
	PJSIP_MOD_PRIORITY_APPLICATION+99,	//Priority 
	NULL,	// load() 
	NULL,	// start() 
	NULL,	// stop() 
	NULL,	// unload() 
	&default_mod_on_rx_request,	// on_rx_request() 
	NULL,	// on_rx_response() 
	NULL,	// on_tx_request. 
	NULL,	// on_tx_response() 
	NULL,	// on_tsx_state()

};

pj_status_t app_destroy(void)
{
	pj_status_t status;
	unsigned i;

#ifdef STEREO_DEMO
	if (app_config.snd) {
		pjmedia_snd_port_destroy(app_config.snd);
		app_config.snd = NULL;
	}
	if (app_config.sc_ch1) {
		pjsua_conf_remove_port(app_config.sc_ch1_slot);
		app_config.sc_ch1_slot = PJSUA_INVALID_ID;
		pjmedia_port_destroy(app_config.sc_ch1);
		app_config.sc_ch1 = NULL;
	}
	if (app_config.sc) {
		pjmedia_port_destroy(app_config.sc);
		app_config.sc = NULL;
	}
#endif

	// Close ringback port 
	if (app_config.ringback_port && 
		app_config.ringback_slot != PJSUA_INVALID_ID) 
	{
		pjsua_conf_remove_port(app_config.ringback_slot);
		app_config.ringback_slot = PJSUA_INVALID_ID;
		pjmedia_port_destroy(app_config.ringback_port);
		app_config.ringback_port = NULL;
	}

	// Close ring port 
	if (app_config.ring_port && app_config.ring_slot != PJSUA_INVALID_ID) {
		pjsua_conf_remove_port(app_config.ring_slot);
		app_config.ring_slot = PJSUA_INVALID_ID;
		pjmedia_port_destroy(app_config.ring_port);
		app_config.ring_port = NULL;
	}

	// Close tone generators 
	for (i=0; i<app_config.tone_count; ++i) {
		pjsua_conf_remove_port(app_config.tone_slots[i]);
	}

	if (app_config.pool) {
		pj_pool_release(app_config.pool);
		app_config.pool = NULL;
	}

	status = pjsua_destroy();

	pj_bzero(&app_config, sizeof(app_config));

	return status;
}

#ifdef STEREO_DEMO
////////////////////////////////////////////////////////////////////
// In this stereo demo, we open the sound device in stereo mode and
// arrange the attachment to the PJSUA-LIB conference bridge as such
// so that channel0/left channel of the sound device corresponds to
// slot 0 in the bridge, and channel1/right channel of the sound
// device corresponds to slot 1 in the bridge. Then user can independently
// feed different media to/from the speakers/microphones channels, by
// connecting them to slot 0 or 1 respectively.
//
// Here's how the connection looks like:
//
/*
+-----------+ stereo +-----------------+ 2x mono +-----------+
| AUDIO DEV |<------>| SPLITCOMB   left|<------->|#0  BRIDGE |
+-----------+        |            right|<------->|#1         |
+-----------------+         +-----------+
*/
/////////////////////////////////////////////////////////////////////
static void stereo_demo()
{
	pjmedia_port *conf;
	pj_status_t status;

	/* Disable existing sound device */
	conf = pjsua_set_no_snd_dev();

	/* Create stereo-mono splitter/combiner */
	status = pjmedia_splitcomb_create(app_config.pool, 
		conf->info.clock_rate /* clock rate */,
		2	    /* stereo */,
		2 * conf->info.samples_per_frame,
		conf->info.bits_per_sample,
		0	    /* options */,
		&app_config.sc);
	pj_assert(status == PJ_SUCCESS);

	/* Connect channel0 (left channel?) to conference port slot0 */
	status = pjmedia_splitcomb_set_channel(app_config.sc, 0 /* ch0 */, 
		0 /*options*/,
		conf);
	pj_assert(status == PJ_SUCCESS);

	/* Create reverse channel for channel1 (right channel?)... */
	status = pjmedia_splitcomb_create_rev_channel(app_config.pool,
		app_config.sc,
		1  /* ch1 */,
		0  /* options */,
		&app_config.sc_ch1);
	pj_assert(status == PJ_SUCCESS);

	/* .. and register it to conference bridge (it would be slot1
	* if there's no other devices connected to the bridge)
	*/
	status = pjsua_conf_add_port(app_config.pool, app_config.sc_ch1, 
		&app_config.sc_ch1_slot);
	pj_assert(status == PJ_SUCCESS);

	/* Create sound device */
	status = pjmedia_snd_port_create(app_config.pool, -1, -1, 
		conf->info.clock_rate,
		2	    /* stereo */,
		2 * conf->info.samples_per_frame,
		conf->info.bits_per_sample,
		0, &app_config.snd);
	pj_assert(status == PJ_SUCCESS);


	/* Connect the splitter to the sound device */
	status = pjmedia_snd_port_connect(app_config.snd, app_config.sc);
	pj_assert(status == PJ_SUCCESS);

}
#endif

static pj_status_t create_ipv6_media_transports(void)
{
	pjsua_media_transport tp[PJSUA_MAX_CALLS];
	pj_status_t status;
	int port = app_config.rtp_cfg.port;
	unsigned i;

	for (i=0; i<app_config.cfg.max_calls; ++i) {
		enum { MAX_RETRY = 10 };
		pj_sock_t sock[2];
		pjmedia_sock_info si;
		unsigned j;

		/* Get rid of uninitialized var compiler warning with MSVC */
		status = PJ_SUCCESS;

		for (j=0; j<MAX_RETRY; ++j) {
			unsigned k;

			for (k=0; k<2; ++k) {
				pj_sockaddr bound_addr;

				status = pj_sock_socket(pj_AF_INET6(), pj_SOCK_DGRAM(), 0, &sock[k]);
				if (status != PJ_SUCCESS)
					break;

				status = pj_sockaddr_init(pj_AF_INET6(), &bound_addr,
					&app_config.rtp_cfg.bound_addr, 
					(unsigned short)(port+k));
				if (status != PJ_SUCCESS)
					break;

				status = pj_sock_bind(sock[k], &bound_addr, 
					pj_sockaddr_get_len(&bound_addr));
				if (status != PJ_SUCCESS)
					break;
			}
			if (status != PJ_SUCCESS) {
				if (k==1)
					pj_sock_close(sock[0]);

				if (port != 0)
					port += 10;
				else
					break;

				continue;
			}

			pj_bzero(&si, sizeof(si));
			si.rtp_sock = sock[0];
			si.rtcp_sock = sock[1];

			pj_sockaddr_init(pj_AF_INET6(), &si.rtp_addr_name, 
				&app_config.rtp_cfg.public_addr, 
				(unsigned short)(port));
			pj_sockaddr_init(pj_AF_INET6(), &si.rtcp_addr_name, 
				&app_config.rtp_cfg.public_addr, 
				(unsigned short)(port+1));

			status = pjmedia_transport_udp_attach(pjsua_get_pjmedia_endpt(),
				NULL,
				&si,
				0,
				&tp[i].transport);
			if (port != 0)
				port += 10;
			else
				break;

			if (status == PJ_SUCCESS)
				break;
		}

		if (status != PJ_SUCCESS) {
			pjsua_perror(THIS_FILE, "Error creating IPv6 UDP media transport", 
				status);
			for (j=0; j<i; ++j) {
				pjmedia_transport_close(tp[j].transport);
			}
			return status;
		}
	}

	return pjsua_media_transports_attach(tp, i, PJ_TRUE);
}

////////////////main code started//////////////////
pj_log_func     *log_cb_f = NULL;
func_reg_state_callback  reg_state_callback_f=NULL;
func_call_state_callback call_state_callback_f=NULL;
func_media_state_callback media_state_callback_f=NULL;
func_network_state_callback network_state_callback_f=NULL;

/* Callback from timer when the maximum call duration has been
* exceeded.
*/
static void call_timeout_callback_f(pj_timer_heap_t *timer_heap,
struct pj_timer_entry *entry)
{
	pjsua_call_id call_id = entry->id;
	pjsua_msg_data msg_data;
	pjsip_generic_string_hdr warn;
	pj_str_t hname = pj_str("Warning");
	pj_str_t hvalue = pj_str("399 pjsua \"Call duration exceeded\"");

	PJ_UNUSED_ARG(timer_heap);

	if (call_id == PJSUA_INVALID_ID) {
		PJ_LOG(1,(THIS_FILE, "Invalid call ID in timer callback"));
		return;
	}

	/* Add warning header */
	pjsua_msg_data_init(&msg_data);
	pjsip_generic_string_hdr_init2(&warn, &hname, &hvalue);
	pj_list_push_back(&msg_data.hdr_list, &warn);

	/* Call duration has been exceeded; disconnect the call */
	PJ_LOG(3,(THIS_FILE, "Duration (%d seconds) has been exceeded "
		"for call %d, disconnecting the call",
		app_config.duration, call_id));
	entry->id = PJSUA_INVALID_ID;
	pjsua_call_hangup(call_id, 200, NULL, &msg_data);
}

/*
* Handler when invite state has changed.
*/
static void on_call_state_f(pjsua_call_id call_id, pjsip_event *e)
{
	pjsua_call_info call_info;

	PJ_UNUSED_ARG(e);

	pjsua_call_get_info(call_id, &call_info);

	if (call_info.state == PJSIP_INV_STATE_DISCONNECTED)
	{
		if(call_state_callback_f)
			call_state_callback_f(call_info.acc_id,call_id,"",call_info.remote_info.ptr,PHONELIB_CALL_STATE_TERMINATED,		call_info.last_status,
			call_info.last_status_text.ptr);
	}
	else 
	{
		if (call_info.state == PJSIP_INV_STATE_CALLING) 
		{
			if(call_state_callback_f)
				call_state_callback_f(call_info.acc_id,call_id,"",call_info.remote_info.ptr,PHONELIB_CALL_STATE_CALLING,0,"");
		}	

		if (call_info.state == PJSIP_INV_STATE_CONFIRMED) 
		{
			if(call_state_callback_f)
				call_state_callback_f(call_info.acc_id,call_id,"",call_info.remote_info.ptr,PHONELIB_CALL_STATE_CONNECTED,0,"");
		}	



		if (call_info.state == PJSIP_INV_STATE_EARLY) 
		{
			int code;
			pj_str_t reason;
			pjsip_msg *msg;

			/* This can only occur because of TX or RX message */
			pj_assert(e->type == PJSIP_EVENT_TSX_STATE);

			if (e->body.tsx_state.type == PJSIP_EVENT_RX_MSG) 
			{
				msg = e->body.tsx_state.src.rdata->msg_info.msg;
			} 
			else 
			{
				msg = e->body.tsx_state.src.tdata->msg;
			}

			code = msg->line.status.code;
			reason = msg->line.status.reason;

			/* Start ringback for 180 for UAC unless there's SDP in 180 */
			if (call_info.role==PJSIP_ROLE_UAC && code==180 && 
				msg->body == NULL && 
				call_info.media_status==PJSUA_CALL_MEDIA_NONE) 
			{
				ringback_start(call_id);
			}



			PJ_LOG(3,(THIS_FILE, "Call %d state changed to %s (%d %.*s)", 
				call_id, call_info.state_text.ptr,
				code, (int)reason.slen, reason.ptr));

			
			if(call_state_callback_f)
			{	
				//char reason
				if (call_info.role==PJSIP_ROLE_UAC && code==183)
					call_state_callback_f(call_info.acc_id,call_id,"",call_info.remote_info.ptr,PHONELIB_CALL_STATE_PROGRESSING,code,"");
				else if (call_info.role==PJSIP_ROLE_UAC && code==180)
					call_state_callback_f(call_info.acc_id,call_id,"",call_info.remote_info.ptr,PHONELIB_CALL_STATE_RINGING,code,"");
				

			}
		} 
		else
		{
			PJ_LOG(3,(THIS_FILE, "Call %d state changed to %s", 
				call_id,
				call_info.state_text.ptr));
		}

		if (current_call==PJSUA_INVALID_ID)
			current_call = call_id;

	}

	if(call_state_callback_f!=NULL)
	{

	}

}

/**
* Handler when there is incoming call.
*/
static void on_incoming_call_f(pjsua_acc_id acc_id, pjsua_call_id call_id,
							   pjsip_rx_data *rdata)
{
	pjsua_call_info call_info;

	PJ_UNUSED_ARG(acc_id);
	PJ_UNUSED_ARG(rdata);

	pjsua_call_get_info(call_id, &call_info);

	if (current_call==PJSUA_INVALID_ID)
		current_call = call_id;

#ifdef USE_GUI
	if (!showNotification(call_id))
		return;
#endif

	/* Start ringback */
	ring_start(call_id);

	pjsua_call_answer(call_id, 180, NULL, NULL);

	/*
	if (app_config.auto_answer > 0) {
	pjsua_call_answer(call_id, app_config.auto_answer, NULL, NULL);
	}

	if (app_config.auto_answer < 200) {
	PJ_LOG(3,(THIS_FILE,
	"Incoming call for account %d!\n"
	"From: %s\n"
	"To: %s\n"
	"Press a to answer or h to reject call",
	acc_id,
	call_info.remote_info.ptr,
	call_info.local_info.ptr));
	}
	*/

	if(call_state_callback_f)
		call_state_callback_f(call_info.acc_id,call_id,call_info.local_info.ptr,call_info.remote_info.ptr,PHONELIB_CALL_STATE_INCOMING,0,"");

}

/*
* Handler when a transaction within a call has changed state.
*/
static void on_call_tsx_state_f(pjsua_call_id call_id,
								pjsip_transaction *tsx,
								pjsip_event *e)
{
	const pjsip_method info_method = 
	{
		PJSIP_OTHER_METHOD,
		{ "INFO", 4 }
	};

	if (pjsip_method_cmp(&tsx->method, &info_method)==0) {
		/*
		* Handle INFO method.
		*/
		if (tsx->role == PJSIP_ROLE_UAC && 
			(tsx->state == PJSIP_TSX_STATE_COMPLETED ||
			(tsx->state == PJSIP_TSX_STATE_TERMINATED &&
			e->body.tsx_state.prev_state != PJSIP_TSX_STATE_COMPLETED))) 
		{
			/* Status of outgoing INFO request */
			if (tsx->status_code >= 200 && tsx->status_code < 300) {
				PJ_LOG(4,(THIS_FILE, 
					"Call %d: DTMF sent successfully with INFO",
					call_id));
			} else if (tsx->status_code >= 300) {
				PJ_LOG(4,(THIS_FILE, 
					"Call %d: Failed to send DTMF with INFO: %d/%.*s",
					call_id,
					tsx->status_code,
					(int)tsx->status_text.slen,
					tsx->status_text.ptr));
			}
		} else if (tsx->role == PJSIP_ROLE_UAS &&
			tsx->state == PJSIP_TSX_STATE_TRYING)
		{
			/* Answer incoming INFO with 200/OK */
			pjsip_rx_data *rdata;
			pjsip_tx_data *tdata;
			pj_status_t status;

			rdata = e->body.tsx_state.src.rdata;

			if (rdata->msg_info.msg->body) {
				status = pjsip_endpt_create_response(tsx->endpt, rdata,
					200, NULL, &tdata);
				if (status == PJ_SUCCESS)
					status = pjsip_tsx_send_msg(tsx, tdata);

				PJ_LOG(3,(THIS_FILE, "Call %d: incoming INFO:\n%.*s", 
					call_id,
					(int)rdata->msg_info.msg->body->len,
					rdata->msg_info.msg->body->data));
			} else {
				status = pjsip_endpt_create_response(tsx->endpt, rdata,
					400, NULL, &tdata);
				if (status == PJ_SUCCESS)
					status = pjsip_tsx_send_msg(tsx, tdata);
			}
		}
	}
}

/*
* Callback on media state changed event.
* The action may connect the call to sound device, to file, or
* to loop the call.
*/
static void on_call_media_state_f(pjsua_call_id call_id)
{
	pjsua_call_info call_info;

	pjsua_call_get_info(call_id, &call_info);

	/* Stop ringback */
	ring_stop(call_id);

	/* Connect ports appropriately when media status is ACTIVE or REMOTE HOLD,
	* otherwise we should NOT connect the ports.
	*/
	if (call_info.media_status == PJSUA_CALL_MEDIA_ACTIVE ||
		call_info.media_status == PJSUA_CALL_MEDIA_REMOTE_HOLD)
	{
		pj_bool_t connect_sound = PJ_TRUE;

		/* Loopback sound, if desired */
		if (app_config.auto_loop) {
			pjsua_conf_connect(call_info.conf_slot, call_info.conf_slot);
			connect_sound = PJ_FALSE;
		}

		/* Automatically record conversation, if desired */
		if (app_config.auto_rec && app_config.rec_port != PJSUA_INVALID_ID) {
			pjsua_conf_connect(call_info.conf_slot, app_config.rec_port);
		}

		/* Stream a file, if desired */
		if ((app_config.auto_play || app_config.auto_play_hangup) && 
			app_config.wav_port != PJSUA_INVALID_ID)
		{
			pjsua_conf_connect(app_config.wav_port, call_info.conf_slot);
			connect_sound = PJ_FALSE;
		}

		/* Put call in conference with other calls, if desired */
		if (app_config.auto_conf) {
			pjsua_call_id call_ids[PJSUA_MAX_CALLS];
			unsigned call_cnt=PJ_ARRAY_SIZE(call_ids);
			unsigned i;

			/* Get all calls, and establish media connection between
			* this call and other calls.
			*/
			pjsua_enum_calls(call_ids, &call_cnt);

			for (i=0; i<call_cnt; ++i) {
				if (call_ids[i] == call_id)
					continue;

				if (!pjsua_call_has_media(call_ids[i]))
					continue;

				pjsua_conf_connect(call_info.conf_slot,
					pjsua_call_get_conf_port(call_ids[i]));
				pjsua_conf_connect(pjsua_call_get_conf_port(call_ids[i]),
					call_info.conf_slot);

				/* Automatically record conversation, if desired */
				if (app_config.auto_rec && app_config.rec_port != PJSUA_INVALID_ID) {
					pjsua_conf_connect(pjsua_call_get_conf_port(call_ids[i]), 
						app_config.rec_port);
				}

			}
			/* Also connect call to local sound device */
			connect_sound = PJ_TRUE;
		}

		/* Otherwise connect to sound device */
		if (connect_sound) {
			pjsua_conf_connect(call_info.conf_slot, 0);
			pjsua_conf_connect(0, call_info.conf_slot);

			/* Automatically record conversation, if desired */
			if (app_config.auto_rec && app_config.rec_port != PJSUA_INVALID_ID) {
				pjsua_conf_connect(call_info.conf_slot, app_config.rec_port);
				pjsua_conf_connect(0, app_config.rec_port);
			}
		}
	}

	/* Handle media status */
	switch (call_info.media_status) {
case PJSUA_CALL_MEDIA_ACTIVE:
	PJ_LOG(3,(THIS_FILE, "Media for call %d is active", call_id));
	break;

case PJSUA_CALL_MEDIA_LOCAL_HOLD:
	PJ_LOG(3,(THIS_FILE, "Media for call %d is suspended (hold) by local",
		call_id));
	break;

case PJSUA_CALL_MEDIA_REMOTE_HOLD:
	PJ_LOG(3,(THIS_FILE, 
		"Media for call %d is suspended (hold) by remote",
		call_id));
	break;

case PJSUA_CALL_MEDIA_ERROR:
	PJ_LOG(3,(THIS_FILE,
		"Media has reported error, disconnecting call"));
	{
		pj_str_t reason = pj_str("ICE negotiation failed");
		pjsua_call_hangup(call_id, 500, &reason, NULL);
	}
	break;

case PJSUA_CALL_MEDIA_NONE:
	PJ_LOG(3,(THIS_FILE, 
		"Media for call %d is inactive",
		call_id));
	break;

default:
	pj_assert(!"Unhandled media status");
	break;
	}
}

/*
* DTMF callback.
*/
static void call_on_dtmf_callback_f(pjsua_call_id call_id, int dtmf)
{
	PJ_LOG(3,(THIS_FILE, "Incoming DTMF on call %d: %c", call_id, dtmf));
}

/*
* Redirection handler.
*/
static pjsip_redirect_op call_on_redirected_f(pjsua_call_id call_id, 
											  const pjsip_uri *target,
											  const pjsip_event *e)
{
	PJ_UNUSED_ARG(e);
	if (app_config.redir_op == PJSIP_REDIRECT_PENDING) {
		char uristr[PJSIP_MAX_URL_SIZE];
		int len;

		len = pjsip_uri_print(PJSIP_URI_IN_FROMTO_HDR, target, uristr, 
			sizeof(uristr));
		if (len < 1) {
			pj_ansi_strcpy(uristr, "--URI too long--");
		}

		PJ_LOG(3,(THIS_FILE, "Call %d is being redirected to %.*s. "
			"Press 'Ra' to accept, 'Rr' to reject, or 'Rd' to "
			"disconnect.",
			call_id, len, uristr));
	}
	return app_config.redir_op;
}

/*
* Handler registration status has changed.
*/
static void on_reg_state_f(pjsua_acc_id acc_id)
{
	PJ_UNUSED_ARG(acc_id);
	pj_status_t status;
	pjsua_acc_info info;

	status = pjsua_acc_get_info(acc_id, &info);
	if (status != PJ_SUCCESS)
		return;
	PHONELIB_REG_STATE regstate=PHONELIB_REG_STATE_DETAIL;

	switch(info.status)
	{
	case 200: // OK
		regstate=PHONELIB_REG_STATE_REGISTERED;
		break;
	case 403: // registration failed
		regstate=PHONELIB_REG_STATE_REJECTED;
	case 404: // not found
		//sprintf(TheGlobalConfig.accountError, "SIP-AUTH-FAILED");
		regstate=PHONELIB_REG_STATE_NOTFOUND;
		break;
	case 503:
		regstate=PHONELIB_REG_STATE_SERVERERROR;
		break;
	default:
		// This error is caused by the realm specified in the credential doesn't match the realm challenged by the server
		//sprintf(TheGlobalConfig.accountError, "SIP-REGISTER-FAILED");
		break;
	}

	if(reg_state_callback_f)
	{
		if (info.status_text.slen)
			reg_state_callback_f(acc_id,regstate,info.status,info.status_text.ptr);
		else
			reg_state_callback_f(acc_id,regstate,info.status,"");
	}
}

/*
* Handler for incoming presence subscription request
*/
static void on_incoming_subscribe_f(pjsua_acc_id acc_id,
									pjsua_srv_pres *srv_pres,
									pjsua_buddy_id buddy_id,
									const pj_str_t *from,
									pjsip_rx_data *rdata,
									pjsip_status_code *code,
									pj_str_t *reason,
									pjsua_msg_data *msg_data)
{
	/* Just accept the request (the default behavior) */
	PJ_UNUSED_ARG(acc_id);
	PJ_UNUSED_ARG(srv_pres);
	PJ_UNUSED_ARG(buddy_id);
	PJ_UNUSED_ARG(from);
	PJ_UNUSED_ARG(rdata);
	PJ_UNUSED_ARG(code);
	PJ_UNUSED_ARG(reason);
	PJ_UNUSED_ARG(msg_data);
}

/*
* Handler on buddy state changed.
*/
static void on_buddy_state_f(pjsua_buddy_id buddy_id)
{
	pjsua_buddy_info info;
	pjsua_buddy_get_info(buddy_id, &info);

	PJ_LOG(3,(THIS_FILE, "%.*s status is %.*s, subscription state is %s "
		"(last termination reason code=%d %.*s)",
		(int)info.uri.slen,
		info.uri.ptr,
		(int)info.status_text.slen,
		info.status_text.ptr,
		info.sub_state_name,
		info.sub_term_code,
		(int)info.sub_term_reason.slen,
		info.sub_term_reason.ptr));
}


/*
* Subscription state has changed.
*/
static void on_buddy_evsub_state_f(pjsua_buddy_id buddy_id,
								   pjsip_evsub *sub,
								   pjsip_event *event)
{
	char event_info[80];
	PJ_UNUSED_ARG(sub);

	event_info[0] = '\0';

	if (event->type == PJSIP_EVENT_TSX_STATE &&
		event->body.tsx_state.type == PJSIP_EVENT_RX_MSG)
	{
		pjsip_rx_data *rdata = event->body.tsx_state.src.rdata;
		snprintf(event_info, sizeof(event_info),
			" (RX %s)",
			pjsip_rx_data_get_info(rdata));
	}

	PJ_LOG(4,(THIS_FILE,
		"Buddy %d: subscription state: %s (event: %s%s)",
		buddy_id, pjsip_evsub_get_state_name(sub),
		pjsip_event_str(event->type),
		event_info));

}

/**
* Incoming IM message (i.e. MESSAGE request)!
*/
static void on_pager_f(pjsua_call_id call_id, const pj_str_t *from, 
					   const pj_str_t *to, const pj_str_t *contact,
					   const pj_str_t *mime_type, const pj_str_t *text)
{
	/* Note: call index may be -1 */
	PJ_UNUSED_ARG(call_id);
	PJ_UNUSED_ARG(to);
	PJ_UNUSED_ARG(contact);
	PJ_UNUSED_ARG(mime_type);

	PJ_LOG(3,(THIS_FILE,"MESSAGE from %.*s: %.*s (%.*s)",
		(int)from->slen, from->ptr,
		(int)text->slen, text->ptr,
		(int)mime_type->slen, mime_type->ptr));
}


/**
* Received typing indication
*/
static void on_typing_f(pjsua_call_id call_id, const pj_str_t *from,
						const pj_str_t *to, const pj_str_t *contact,
						pj_bool_t is_typing)
{
	PJ_UNUSED_ARG(call_id);
	PJ_UNUSED_ARG(to);
	PJ_UNUSED_ARG(contact);

	PJ_LOG(3,(THIS_FILE, "IM indication: %.*s %s",
		(int)from->slen, from->ptr,
		(is_typing?"is typing..":"has stopped typing")));
}

/**
* Call transfer request status.
*/
static void on_call_transfer_status_f(pjsua_call_id call_id,
									  int status_code,
									  const pj_str_t *status_text,
									  pj_bool_t final,
									  pj_bool_t *p_cont)
{
	PJ_LOG(3,(THIS_FILE, "Call %d: transfer status=%d (%.*s) %s",
		call_id, status_code,
		(int)status_text->slen, status_text->ptr,
		(final ? "[final]" : "")));

	if (status_code/100 == 2) {
		PJ_LOG(3,(THIS_FILE, 
			"Call %d: call transfered successfully, disconnecting call",
			call_id));
		pjsua_call_hangup(call_id, PJSIP_SC_GONE, NULL, NULL);
		*p_cont = PJ_FALSE;
	}
}

/*
* Notification that call is being replaced.
*/
static void on_call_replaced_f(pjsua_call_id old_call_id,
							   pjsua_call_id new_call_id)
{
	pjsua_call_info old_ci, new_ci;

	pjsua_call_get_info(old_call_id, &old_ci);
	pjsua_call_get_info(new_call_id, &new_ci);

	PJ_LOG(3,(THIS_FILE, "Call %d with %.*s is being replaced by "
		"call %d with %.*s",
		old_call_id, 
		(int)old_ci.remote_info.slen, old_ci.remote_info.ptr,
		new_call_id,
		(int)new_ci.remote_info.slen, new_ci.remote_info.ptr));
}

/*
* NAT type detection callback.
*/
static void on_nat_detect_f(const pj_stun_nat_detect_result *res)
{
	if (res->status != PJ_SUCCESS) {
		pjsua_perror(THIS_FILE, "NAT detection failed", res->status);
	} else {
		PJ_LOG(3, (THIS_FILE, "NAT detected as %s", res->nat_type_name));
	}
}

/*
* MWI indication
*/
static void on_mwi_info_f(pjsua_acc_id acc_id, pjsua_mwi_info *mwi_info)
{
	pj_str_t body;

	PJ_LOG(3,(THIS_FILE, "Received MWI for acc %d:", acc_id));

	if (mwi_info->rdata->msg_info.ctype) {
		const pjsip_ctype_hdr *ctype = mwi_info->rdata->msg_info.ctype;

		PJ_LOG(3,(THIS_FILE, " Content-Type: %.*s/%.*s",
			(int)ctype->media.type.slen,
			ctype->media.type.ptr,
			(int)ctype->media.subtype.slen,
			ctype->media.subtype.ptr));
	}

	if (!mwi_info->rdata->msg_info.msg->body) {
		PJ_LOG(3,(THIS_FILE, "  no message body"));
		return;
	}

	body.ptr = (char*)(mwi_info->rdata->msg_info.msg->body->data);
	body.slen = mwi_info->rdata->msg_info.msg->body->len;

	PJ_LOG(3,(THIS_FILE, " Body:\n%.*s", (int)body.slen, body.ptr));
}


/*
* Transport status notification
*/
static void on_transport_state_f(pjsip_transport *tp, 
								 pjsip_transport_state state,
								 const pjsip_transport_state_info *info)
{
	char host_port[128];

	pj_ansi_snprintf(host_port, sizeof(host_port), "[%.*s:%d]",
		(int)tp->remote_name.host.slen,
		tp->remote_name.host.ptr,
		tp->remote_name.port);

	switch (state) {
case PJSIP_TP_STATE_CONNECTED:
	{
		PJ_LOG(3,(THIS_FILE, "SIP %s transport is connected to %s",
			tp->type_name, host_port));
	}
	break;

case PJSIP_TP_STATE_DISCONNECTED:
	{
		char buf[100];

		snprintf(buf, sizeof(buf), "SIP %s transport is disconnected from %s",
			tp->type_name, host_port);
		pjsua_perror(THIS_FILE, buf, info->status);
	}
	break;

default:
	break;
	}

#if defined(PJSIP_HAS_TLS_TRANSPORT) && PJSIP_HAS_TLS_TRANSPORT!=0

	if (!pj_ansi_stricmp(tp->type_name, "tls") && info->ext_info &&
		(state == PJSIP_TP_STATE_CONNECTED || 
		((pjsip_tls_state_info*)info->ext_info)->
		ssl_sock_info->verify_status != PJ_SUCCESS))
	{
		pjsip_tls_state_info *tls_info = (pjsip_tls_state_info*)info->ext_info;
		pj_ssl_sock_info *ssl_sock_info = tls_info->ssl_sock_info;
		char buf[2048];
		const char *verif_msgs[32];
		unsigned verif_msg_cnt;

		/* Dump server TLS certificate */
		pj_ssl_cert_info_dump(ssl_sock_info->remote_cert_info, "  ",
			buf, sizeof(buf));
		PJ_LOG(4,(THIS_FILE, "TLS cert info of %s:\n%s", host_port, buf));

		/* Dump server TLS certificate verification result */
		verif_msg_cnt = PJ_ARRAY_SIZE(verif_msgs);
		pj_ssl_cert_get_verify_status_strings(ssl_sock_info->verify_status,
			verif_msgs, &verif_msg_cnt);
		PJ_LOG(3,(THIS_FILE, "TLS cert verification result of %s : %s",
			host_port,
			(verif_msg_cnt == 1? verif_msgs[0]:"")));
		if (verif_msg_cnt > 1) {
			unsigned i;
			for (i = 0; i < verif_msg_cnt; ++i)
				PJ_LOG(3,(THIS_FILE, "- %s", verif_msgs[i]));
		}

		if (ssl_sock_info->verify_status &&
			!app_config.udp_cfg.tls_setting.verify_server) 
		{
			PJ_LOG(3,(THIS_FILE, "PJSUA is configured to ignore TLS cert "
				"verification errors"));
		}
	}

#endif

}

/*
* Notification on ICE error.
*/
static void on_ice_transport_error_f(int index, pj_ice_strans_op op,
									 pj_status_t status, void *param)
{
	PJ_UNUSED_ARG(op);
	PJ_UNUSED_ARG(param);
	PJ_PERROR(1,(THIS_FILE, status,
		"ICE keep alive failure for transport %d", index));
}

#ifdef TRANSPORT_ADAPTER_SAMPLE
/*
* This callback is called when media transport needs to be created.
*/
static pjmedia_transport* on_create_media_transport_f(pjsua_call_id call_id,
													  unsigned media_idx,
													  pjmedia_transport *base_tp,
													  unsigned flags)
{
	pjmedia_transport *adapter;
	pj_status_t status;

	/* Create the adapter */
	status = pjmedia_tp_adapter_create(pjsua_get_pjmedia_endpt(),
		NULL, base_tp,
		(flags & PJSUA_MED_TP_CLOSE_MEMBER),
		&adapter);
	if (status != PJ_SUCCESS) {
		PJ_PERROR(1,(THIS_FILE, status, "Error creating adapter"));
		return NULL;
	}

	PJ_LOG(3,(THIS_FILE, "Media transport is created for call %d media %d",
		call_id, media_idx));

	return adapter;
}
#endif


pj_status_t phonelib_init(int local_sip_port,const char* log_file, int log_level, bool log_b_append)
{
	pjsua_transport_id transport_id = -1;
	pjsua_transport_config tcp_cfg;
	unsigned i;
	pj_status_t status;

	app_restart = PJ_FALSE;

	/* Create pjsua */
	status = pjsua_create();
	if (status != PJ_SUCCESS)
		return 1;

	/* Create pool for application */
	app_config.pool = pjsua_pool_create("BaiduSipPhone", 1000, 1000);

	/* Initialize default config */
	default_config(&app_config);

	/* Parse the arguments */
	/*
	status = parse_args(argc, argv, &app_config, &uri_arg);
	if (status != PJ_SUCCESS)
	return status;
	*/

	if(strcmp(log_file,"")!=0)
	{
		app_config.log_cfg.log_filename = pj_str((char*)log_file);
		  
		if(log_b_append)
			app_config.log_cfg.log_file_flags |= PJ_O_APPEND;
		int c=log_level;
		if(c<0) c=0;
		if(c>6) c=6;
		app_config.log_cfg.level = c;
		pj_log_set_level( c );
	}
 
	/* Initialize application callbacks */
	app_config.cfg.cb.on_call_state = &on_call_state_f;
	app_config.cfg.cb.on_call_media_state = &on_call_media_state_f;
	app_config.cfg.cb.on_incoming_call = &on_incoming_call_f;
	app_config.cfg.cb.on_call_tsx_state = &on_call_tsx_state_f;
	app_config.cfg.cb.on_dtmf_digit = &call_on_dtmf_callback_f;
	app_config.cfg.cb.on_call_redirected = &call_on_redirected_f;
	app_config.cfg.cb.on_reg_state = &on_reg_state_f;
	app_config.cfg.cb.on_incoming_subscribe = &on_incoming_subscribe_f;
	app_config.cfg.cb.on_buddy_state = &on_buddy_state_f;
	app_config.cfg.cb.on_buddy_evsub_state = &on_buddy_evsub_state_f;
	app_config.cfg.cb.on_pager = &on_pager_f;
	app_config.cfg.cb.on_typing = &on_typing_f;
	app_config.cfg.cb.on_call_transfer_status = &on_call_transfer_status_f;
	app_config.cfg.cb.on_call_replaced = &on_call_replaced_f;
	app_config.cfg.cb.on_nat_detect = &on_nat_detect_f;
	app_config.cfg.cb.on_mwi_info = &on_mwi_info_f;
	app_config.cfg.cb.on_transport_state = &on_transport_state_f;
	app_config.cfg.cb.on_ice_transport_error = &on_ice_transport_error_f;
#ifdef TRANSPORT_ADAPTER_SAMPLE
	app_config.cfg.cb.on_create_media_transport = &on_create_media_transport_f;
#endif
	app_config.log_cfg.cb = log_cb_f;

	/* Set sound device latency */
	if (app_config.capture_lat > 0)
		app_config.media_cfg.snd_rec_latency = app_config.capture_lat;
	if (app_config.playback_lat)
		app_config.media_cfg.snd_play_latency = app_config.playback_lat;

	/* Initialize pjsua */
	status = pjsua_init(&app_config.cfg, &app_config.log_cfg,
		&app_config.media_cfg);
	if (status != PJ_SUCCESS)
		return 2;

	/* Initialize our module to handle otherwise unhandled request */
	status = pjsip_endpt_register_module(pjsua_get_pjsip_endpt(),
		&mod_default_handler);
	if (status != PJ_SUCCESS)
		return 3;

#ifdef STEREO_DEMO
	stereo_demo();
#endif

	/* Initialize calls data */
	for (i=0; i<PJ_ARRAY_SIZE(app_config.call_data); ++i) {
		app_config.call_data[i].timer.id = PJSUA_INVALID_ID;
		app_config.call_data[i].timer.cb = &call_timeout_callback_f;
	}

	/* Optionally registers WAV file */
	for (i=0; i<app_config.wav_count; ++i) {
		pjsua_player_id wav_id;
		unsigned play_options = 0;

		if (app_config.auto_play_hangup)
			play_options |= PJMEDIA_FILE_NO_LOOP;

		status = pjsua_player_create(&app_config.wav_files[i], play_options, 
			&wav_id);
		if (status != PJ_SUCCESS)
			goto on_error;

		if (app_config.wav_id == PJSUA_INVALID_ID) {
			app_config.wav_id = wav_id;
			app_config.wav_port = pjsua_player_get_conf_port(app_config.wav_id);
			if (app_config.auto_play_hangup) {
				pjmedia_port *port;

				pjsua_player_get_port(app_config.wav_id, &port);
				status = pjmedia_wav_player_set_eof_cb(port, NULL, 
					&on_playfile_done);
				if (status != PJ_SUCCESS)
					goto on_error;

				pj_timer_entry_init(&app_config.auto_hangup_timer, 0, NULL, 
					&hangup_timeout_callback);
			}
		}
	}

	/* Optionally registers tone players */
	for (i=0; i<app_config.tone_count; ++i) {
		pjmedia_port *tport;
		char name[80];
		pj_str_t label;
		pj_status_t status;

		pj_ansi_snprintf(name, sizeof(name), "tone-%d,%d",
			app_config.tones[i].freq1, 
			app_config.tones[i].freq2);
		label = pj_str(name);
		status = pjmedia_tonegen_create2(app_config.pool, &label,
			8000, 1, 160, 16, 
			PJMEDIA_TONEGEN_LOOP,  &tport);
		if (status != PJ_SUCCESS) {
			pjsua_perror(THIS_FILE, "Unable to create tone generator", status);
			goto on_error;
		}

		status = pjsua_conf_add_port(app_config.pool, tport, 
			&app_config.tone_slots[i]);
		pj_assert(status == PJ_SUCCESS);

		status = pjmedia_tonegen_play(tport, 1, &app_config.tones[i], 0);
		pj_assert(status == PJ_SUCCESS);
	}

	/* Optionally create recorder file, if any. */
	if (app_config.rec_file.slen) {
		status = pjsua_recorder_create(&app_config.rec_file, 0, NULL, 0, 0,
			&app_config.rec_id);
		if (status != PJ_SUCCESS)
			goto on_error;

		app_config.rec_port = pjsua_recorder_get_conf_port(app_config.rec_id);
	}

	pj_memcpy(&tcp_cfg, &app_config.udp_cfg, sizeof(tcp_cfg));

	/* Create ringback tones */
	if (app_config.no_tones == PJ_FALSE) {
		unsigned i, samples_per_frame;
		pjmedia_tone_desc tone[RING_CNT+RINGBACK_CNT];
		pj_str_t name;

		samples_per_frame = app_config.media_cfg.audio_frame_ptime * 
			app_config.media_cfg.clock_rate *
			app_config.media_cfg.channel_count / 1000;

		/* Ringback tone (call is ringing) */
		name = pj_str("ringback");
		status = pjmedia_tonegen_create2(app_config.pool, &name, 
			app_config.media_cfg.clock_rate,
			app_config.media_cfg.channel_count, 
			samples_per_frame,
			16, PJMEDIA_TONEGEN_LOOP, 
			&app_config.ringback_port);
		if (status != PJ_SUCCESS)
			goto on_error;

		pj_bzero(&tone, sizeof(tone));
		for (i=0; i<RINGBACK_CNT; ++i) {
			tone[i].freq1 = RINGBACK_FREQ1;
			tone[i].freq2 = RINGBACK_FREQ2;
			tone[i].on_msec = RINGBACK_ON;
			tone[i].off_msec = RINGBACK_OFF;
		}
		tone[RINGBACK_CNT-1].off_msec = RINGBACK_INTERVAL;

		pjmedia_tonegen_play(app_config.ringback_port, RINGBACK_CNT, tone,
			PJMEDIA_TONEGEN_LOOP);


		status = pjsua_conf_add_port(app_config.pool, app_config.ringback_port,
			&app_config.ringback_slot);
		if (status != PJ_SUCCESS)
			goto on_error;

		/* Ring (to alert incoming call) */
		name = pj_str("ring");
		status = pjmedia_tonegen_create2(app_config.pool, &name, 
			app_config.media_cfg.clock_rate,
			app_config.media_cfg.channel_count, 
			samples_per_frame,
			16, PJMEDIA_TONEGEN_LOOP, 
			&app_config.ring_port);
		if (status != PJ_SUCCESS)
			goto on_error;

		for (i=0; i<RING_CNT; ++i) {
			tone[i].freq1 = RING_FREQ1;
			tone[i].freq2 = RING_FREQ2;
			tone[i].on_msec = RING_ON;
			tone[i].off_msec = RING_OFF;
		}
		tone[RING_CNT-1].off_msec = RING_INTERVAL;

		pjmedia_tonegen_play(app_config.ring_port, RING_CNT, 
			tone, PJMEDIA_TONEGEN_LOOP);

		status = pjsua_conf_add_port(app_config.pool, app_config.ring_port,
			&app_config.ring_slot);
		if (status != PJ_SUCCESS)
			goto on_error;

	}

	app_config.udp_cfg.port=local_sip_port;
	if(app_config.udp_cfg.port<=0) app_config.udp_cfg.port=5060;

	/* Add UDP transport unless it's disabled. */
	if (!app_config.no_udp) {
		pjsua_acc_id aid;
		pjsip_transport_type_e type = PJSIP_TRANSPORT_UDP;

		int trytimes=0;
		while (trytimes<10000)
		{
			status = pjsua_transport_create(type,
			&app_config.udp_cfg,
			&transport_id);
			if(status==PJ_SUCCESS)
				break;
			app_config.udp_cfg.port+=1;
			trytimes++;
		}
		if (status != PJ_SUCCESS)
			goto on_error;

		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_TRUE, &aid);
		//pjsua_acc_set_transport(aid, transport_id);
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);

		if (app_config.udp_cfg.port == 0) {
			pjsua_transport_info ti;
			pj_sockaddr_in *a;

			pjsua_transport_get_info(transport_id, &ti);
			a = (pj_sockaddr_in*)&ti.local_addr;

			tcp_cfg.port = pj_ntohs(a->sin_port);
		}
	}

	/* Add UDP IPv6 transport unless it's disabled. */
	if (!app_config.no_udp && app_config.ipv6) {
		pjsua_acc_id aid;
		pjsip_transport_type_e type = PJSIP_TRANSPORT_UDP6;
		pjsua_transport_config udp_cfg;

		udp_cfg = app_config.udp_cfg;
		if (udp_cfg.port == 0)
			udp_cfg.port = 5060;
		else
			udp_cfg.port += 10;
		status = pjsua_transport_create(type,
			&udp_cfg,
			&transport_id);
		if (status != PJ_SUCCESS)
			goto on_error;

		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_TRUE, &aid);
		//pjsua_acc_set_transport(aid, transport_id);
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);

		if (app_config.udp_cfg.port == 0) {
			pjsua_transport_info ti;
			pj_sockaddr_in *a;

			pjsua_transport_get_info(transport_id, &ti);
			a = (pj_sockaddr_in*)&ti.local_addr;

			tcp_cfg.port = pj_ntohs(a->sin_port);
		}
	}

	/* Add TCP transport unless it's disabled */
	if (!app_config.no_tcp) {

		/*
		status = pjsua_transport_create(PJSIP_TRANSPORT_TCP,
			&tcp_cfg, 
			&transport_id);
		if (status != PJ_SUCCESS)
			goto on_error;
			*/

		int trytimes=0;
		while (trytimes<10000)
		{
			status = pjsua_transport_create(PJSIP_TRANSPORT_TCP,
			&tcp_cfg, 
			&transport_id);
			if(status==PJ_SUCCESS)
				break;
			tcp_cfg.port+=1;
			trytimes++;
		}
		if (status != PJ_SUCCESS)
			goto on_error;

		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_TRUE, NULL);
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);

	}

#if defined(PJSIP_HAS_TLS_TRANSPORT) && PJSIP_HAS_TLS_TRANSPORT!=0
	/* Add TLS transport when application wants one */
	if (app_config.use_tls) {

		pjsua_acc_id acc_id;

		/* Copy the QoS settings */
		tcp_cfg.tls_setting.qos_type = tcp_cfg.qos_type;
		pj_memcpy(&tcp_cfg.tls_setting.qos_params, &tcp_cfg.qos_params, 
			sizeof(tcp_cfg.qos_params));

		/* Set TLS port as TCP port+1 */
		tcp_cfg.port++;
		status = pjsua_transport_create(PJSIP_TRANSPORT_TLS,
			&tcp_cfg, 
			&transport_id);
		tcp_cfg.port--;
		if (status != PJ_SUCCESS)
			goto on_error;

		/* Add local account */
		pjsua_acc_add_local(transport_id, PJ_FALSE, &acc_id);
		pjsua_acc_set_online_status(acc_id, PJ_TRUE);
	}
#endif

	if (transport_id == -1) {
		PJ_LOG(1,(THIS_FILE, "Error: no transport is configured"));
		status = -1;
		goto on_error;
	}
	/* Add accounts */
	for (i=0; i<app_config.acc_cnt; ++i) {
		app_config.acc_cfg[i].reg_retry_interval = 300;
		app_config.acc_cfg[i].reg_first_retry_interval = 60;

		status = pjsua_acc_add(&app_config.acc_cfg[i], PJ_TRUE, NULL);
		if (status != PJ_SUCCESS)
			goto on_error;
		pjsua_acc_set_online_status(current_acc, PJ_TRUE);
	}
	/* Add buddies */
	for (i=0; i<app_config.buddy_cnt; ++i) {
		status = pjsua_buddy_add(&app_config.buddy_cfg[i], NULL);
		if (status != PJ_SUCCESS)
			goto on_error;
	}
	/* Optionally disable some codec */
	for (i=0; i<app_config.codec_dis_cnt; ++i) {
		pjsua_codec_set_priority(&app_config.codec_dis[i],PJMEDIA_CODEC_PRIO_DISABLED);
	}

	/* Optionally set codec orders */
	for (i=0; i<app_config.codec_cnt; ++i) {
		pjsua_codec_set_priority(&app_config.codec_arg[i],
			(pj_uint8_t)(PJMEDIA_CODEC_PRIO_NORMAL+i+9));
	}
	/* Add RTP transports */
	if (app_config.ipv6)
		status = create_ipv6_media_transports();
	else
		status = pjsua_media_transports_create(&app_config.rtp_cfg);

	if (status != PJ_SUCCESS)
		goto on_error;

	/* Use null sound device? */
#ifndef STEREO_DEMO
	if (app_config.null_audio) {
		status = pjsua_set_null_snd_dev();
		if (status != PJ_SUCCESS)
			return 4;
	}
#endif

	if (app_config.capture_dev  != PJSUA_INVALID_ID ||
		app_config.playback_dev != PJSUA_INVALID_ID) 
	{
		status = pjsua_set_snd_dev(app_config.capture_dev, 
			app_config.playback_dev);
		if (status != PJ_SUCCESS)
			goto on_error;
	}
	////////baidu:special
	status = pjsua_start();
	if (status != PJ_SUCCESS)  
		goto on_error;
	return 0;

on_error:
	app_destroy();
	return 44;
}


int phonelib_destroy()
{
	pj_status_t status=app_destroy();
	if(status!=PJ_SUCCESS) return 0;
	return 0;
}

int phonelib_add_account(const char* server, int server_port,const char* sip_account,const char* sip_password,int timeout,int* account_id)
{
	char id[254], registrar[128], realm[128];//, uname[80], passwd[64];
	pjsua_acc_config acc_cfg;
	pj_status_t status;

	sprintf(id,"sip:%s@%s",sip_account,server);
	sprintf(registrar,"sip:%s:%d",server,server_port);
	sprintf(realm,"sip:%s:%d",server,server_port);

	pjsua_acc_config_default(&acc_cfg);
	acc_cfg.reg_timeout=timeout;

	if (acc_cfg.reg_timeout < 1 || acc_cfg.reg_timeout > 3600) 
	{
		PJ_LOG(1,(THIS_FILE, "Error: invalid value for timeout (expecting 1-3600)"));
		return  1;
	}

	acc_cfg.id = pj_str(id);
	acc_cfg.reg_uri = pj_str(registrar);
	acc_cfg.cred_count = 1;
	acc_cfg.cred_info[0].scheme = pj_str("Digest");
	acc_cfg.cred_info[0].realm = pj_str("*");
	acc_cfg.cred_info[0].username = pj_str((char*)sip_account);
	acc_cfg.cred_info[0].data_type = 0;
	acc_cfg.cred_info[0].data = pj_str((char*)sip_password);

	status = pjsua_acc_add(&acc_cfg, PJ_TRUE, account_id);
	if (status != PJ_SUCCESS) {
		pjsua_perror(THIS_FILE, "Error adding new account", status);
		return  2;
	}

	if(*account_id>0)
	{
		if(reg_state_callback_f)
		{ 
			reg_state_callback_f(*account_id,PHONELIB_REG_STATE_REGISTERING,-1,"");
		}

	}
	return 0;
}

int phonelib_remove_account(int account_id)
{
	if (!pjsua_acc_is_valid(account_id)) 
	{
		printf("Invalid account id %d\n", account_id);
		return 0;
	} 
	else 
	{
		pjsua_acc_del(account_id);
		printf("Account %d deleted\n", account_id);
		return 0;
	}
}

int phonelib_make_call_to(int account_id, const char* dest, int* call_id, const char* reserved)
{
	char* uri = NULL;
	pjsua_msg_data msg_data;
	pjsua_acc_info acc_info;
	pj_str_t tmp;
	pjsua_acc_get_info(account_id, &acc_info);
	pjsip_uri* theuri=pjsip_parse_uri(app_config.pool,acc_info.acc_uri.ptr,acc_info.acc_uri.slen,0);
	pjsip_sip_uri *sipuri= (pjsip_sip_uri*) pjsip_uri_get_uri(theuri);

	tmp=pj_str((char*)dest);
	pjsua_msg_data_init(&msg_data);
	TEST_MULTIPART(&msg_data);
	pj_status_t status;
	    
	status = pjsua_call_make_call(account_id, &tmp, 0, NULL, &msg_data, call_id);
	if(status!=PJ_SUCCESS)
		return 1;

	return 0;

}

int phonelib_answer_call(int callid)
{
	int st_code;
	pjsua_msg_data msg_data;

	st_code = 200;//my_atoi(buf);
	pjsua_msg_data_init(&msg_data);

	pj_status_t res=pjsua_call_answer(callid, st_code, NULL, &msg_data);
	if (res != PJ_SUCCESS)
		return 1;
	return 0;
}

int phonelib_drop_call(int callid)
{
	pj_status_t res=pjsua_call_hangup(callid, 0, NULL, NULL);
	if (res != PJ_SUCCESS)
		return 1;
	return 0;
}

int phonelib_hold_call(int callid)
{
	pj_status_t res=pjsua_call_set_hold(current_call, NULL);
	if (res != PJ_SUCCESS)
		return 1;
	return 0;
}

int phonelib_unhold_call(int callid)
{
	pj_status_t res=pjsua_call_reinvite(current_call, PJ_TRUE, NULL);
	if (res != PJ_SUCCESS)
		return 1;
	return 0;
}

int phonelib_send_dtmf(int callid, const char dtmf)
{
	if (callid == -1)
	{
		PJ_LOG(3,(THIS_FILE, "No current call"));
		return 1;
	} 
	else if (!pjsua_call_has_media(callid)) 
	{
		PJ_LOG(3,(THIS_FILE, "Media is not established yet!"));
		return 2;
	} 

	else
	{
		pj_str_t digits;
		int call = callid;
		pj_status_t status;
		char buf[24];
		sprintf(buf,"%c",dtmf);
		digits = pj_str(buf);
		status = pjsua_call_dial_dtmf(callid, &digits);
		if (status != PJ_SUCCESS)
		{
			pjsua_perror(THIS_FILE, "Unable to send DTMF", status);
			return 3;
		} 
		else 
		{
			puts("DTMF digits enqueued for transmission");
			return 0;
		}
	}

}


/*
speex/8000/1 
speex/32000/1 
iLBC/8000/1 
GSM/8000/1 
PCMU/8000/1 
PCMA/8000/1 
G722/16000/1 
L16/44100/1 
L16/44100/2 
*/

int phonelib_set_codecs(const  char* codec_string )
{

	pjsua_codec_info id[50];
	unsigned max=50;
	unsigned   i=0;

	pjsua_enum_codecs( id,&max);

	/* Optionally disable some codec */
	for (i=0; i<max; ++i) {
		pjsua_codec_set_priority(&id[i].codec_id,PJMEDIA_CODEC_PRIO_DISABLED);
	}

	char seps[]   = " ,\t\n";
	char string[1024];
	strncpy(string,codec_string,1024);
	char* token = strtok(  string , seps );
	//char* token = strtok(  string , seps );
	i=1;
	bool allok=true;
	while( token != NULL )
	{
		pj_str_t codec_id=pj_str(token);

		pj_status_t status=pjsua_codec_set_priority(&codec_id,
			(pj_uint8_t)(PJMEDIA_CODEC_PRIO_NORMAL+100-i));
		if(status!=PJ_SUCCESS)
			allok=false;
		i++;
		token = strtok( NULL, seps );
	}

	if(!allok) return 1;
	return 0;

}

int phonelib_set_audio_device( const char  *mic_driver, const char* mic_dev_name, const char* spkr_driver, const char* spkr_dev_name)
{
	pjmedia_aud_dev_index spkr_idx,mic_idx;
	pj_status_t status = pjmedia_aud_dev_lookup(mic_driver, mic_dev_name, &mic_idx);
	if (status!=PJ_SUCCESS)
		return 1;

	status = pjmedia_aud_dev_lookup(spkr_driver, spkr_dev_name, &spkr_idx);
	if (status!=PJ_SUCCESS)
		return 2;

	status=pjsua_set_snd_dev( mic_idx,
				    spkr_idx);

	if(status!=PJ_SUCCESS)
		return 3;
 
	return 0;
}



char* phonelib_get_version_string()
{
	return PHONELIB_VER;
}

int phonelib_get_audio_device_list(phonelib_aud_dev_info info[],unsigned* max)
{

	unsigned m=MAX_AUD_DEV;

	if(*max<MAX_AUD_DEV)
		m=*max;

	pjmedia_aud_dev_info devinfo[MAX_AUD_DEV];
	pj_status_t status=pjsua_enum_aud_devs(devinfo,
		&m);
	if(status!=PJ_SUCCESS)
		return 1;
	*max=m;
	for(unsigned i=0; i<m; i++)
	{
		strcpy(info[i].name,devinfo[i].name);
		info[i].input_count=devinfo[i].input_count;
		info[i].output_count=devinfo[i].output_count;
		info[i].default_samples_per_sec=devinfo[i].default_samples_per_sec;
		info[i].caps=devinfo[i].caps;
		info[i].routes=devinfo[i].routes;
		info[i].ext_fmt_cnt=devinfo[i].ext_fmt_cnt;
		strcpy(info[i].driver,devinfo[i].driver);

	}

	return 0;
}

int phonelib_get_active_audio_device(phonelib_aud_dev_info *mic_info,phonelib_aud_dev_info *spkr_info)
{
	int cdev;
	int pdev;
	pjsua_get_snd_dev(&cdev,&pdev);
	pjmedia_aud_dev_info minfo;
	pjmedia_aud_dev_info sinfo;
	pj_status_t status=pjmedia_aud_dev_get_info(cdev,&minfo);
	if(status!=PJ_SUCCESS) return 1;

	status=pjmedia_aud_dev_get_info(pdev, &sinfo);
	if(status!=PJ_SUCCESS) return 2;

	{
		strcpy(mic_info->name,minfo.name);
		mic_info->input_count=minfo.input_count;
		mic_info->output_count=minfo.output_count;
		mic_info->default_samples_per_sec=minfo.default_samples_per_sec;
		mic_info->caps=minfo.caps;
		mic_info->routes=minfo.routes;
		mic_info->ext_fmt_cnt=minfo.ext_fmt_cnt;
		strcpy(mic_info->driver,minfo.driver);
	}

	{
		strcpy(spkr_info->name,sinfo.name);
		spkr_info->input_count=sinfo.input_count;
		spkr_info->output_count=sinfo.output_count;
		spkr_info->default_samples_per_sec=sinfo.default_samples_per_sec;
		spkr_info->caps=sinfo.caps;
		spkr_info->routes=sinfo.routes;
		spkr_info->ext_fmt_cnt=sinfo.ext_fmt_cnt;
		strcpy(spkr_info->driver,sinfo.driver);
	}

	return 0;

}

int phonelib_adjust_tx_level(float level)//not real spkr device
{

	pj_status_t status=pjsua_conf_adjust_tx_level(0,level);
	if(status!=PJ_SUCCESS) return 1;
	return 0;

}

int phonelib_adjust_rx_level(float level)//not real mic device
{

	pj_status_t status=pjsua_conf_adjust_rx_level(0,level);
	if(status!=PJ_SUCCESS) return 1;
	return 0;

}

int phonelib_mute_mic()
{
	pj_status_t status=pjsua_conf_adjust_rx_level(0,0);
	if(status!=PJ_SUCCESS) return 1;
	return 0;
}

int phonelib_mute_spkr()
{
	pj_status_t status=pjsua_conf_adjust_tx_level(0,0);
	if(status!=PJ_SUCCESS) return 1;
	return 0;
}

int phonelib_get_last_rx_tx_level(unsigned* rx_level, unsigned* tx_level)
{

	pjsua_conf_get_signal_level(0 ,
						 rx_level,
						 tx_level);
	return 0;
}

int phonelib_set_reg_state_callback(func_reg_state_callback reg_state_callback)
{
	reg_state_callback_f=reg_state_callback;
	return 0;
}

int phonelib_set_call_state_callback(func_call_state_callback call_state_callback)
{
	call_state_callback_f=call_state_callback;
	return 0;
}

int phonelib_set_network_state_callback(func_network_state_callback  network_state_callback)
{
	network_state_callback_f=network_state_callback;
	return 0;
}

int phonelib_set_media_state_callback(func_media_state_callback media_state_callback)
{
	media_state_callback_f=media_state_callback;
	return 0;
}