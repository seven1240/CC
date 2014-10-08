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

#define PHONELIB_VER "PHONELIB1.0.0.0_pjsip1.12"
#define AUDIO_NAME_MAX_LEN 256

typedef enum PHONELIB_CALL_STATE
{
	PHONELIB_CALL_STATE_READY,
	PHONELIB_CALL_STATE_IDLE,
	PHONELIB_CALL_STATE_INCOMING,
	PHONELIB_CALL_STATE_CALLING,
	PHONELIB_CALL_STATE_RINGING,
	PHONELIB_CALL_STATE_PROGRESSING,
	PHONELIB_CALL_STATE_CONNECTED,
	PHONELIB_CALL_STATE_ENDED,
	PHONELIB_CALL_STATE_TERMINATED
};

typedef enum PHONELIB_REG_STATE
{
	PHONELIB_REG_STATE_REGISTERING,
	PHONELIB_REG_STATE_REGISTERED,
	PHONELIB_REG_STATE_REJECTED,
	PHONELIB_REG_STATE_NOTFOUND,
	PHONELIB_REG_STATE_SERVERERROR,
	PHONELIB_REG_STATE_TIMEOUT,
	PHONELIB_REG_STATE_ERROR,
	PHONELIB_REG_STATE_UNREGISTERING,
	PHONELIB_REG_STATE_DETAIL,
	PHONELIB_REG_STATE_NOTREGISTERED
};

typedef enum PHONELIB_NETWORK_STATE
{
	PHONELIB_NETWORK_STATE_UNAVAILABLE,
	PHONELIB_NETWORK_STATE_UNREACHABLE,
	PHONELIB_NETWORK_STATE_CHANGED
};

typedef enum PHONELIB_MEDIA_STATE
{
	PHONELIB_CODEC_STATE_NEGOCIATED,
	PHONELIB_CODEC_STATE_CHANGED
};

typedef enum PHONELIB_DTMF_MODE
{
	PHONELIB_DTMF_AUTO,
	PHONELIB_DTMF_2833,
	PHONELIB_DTMF_INFO,
	PHONELIB_DTMF_INBAND
 
};

typedef struct phonelib_aud_dev_info	//语音设备描述
{
	//设备名字
    char name[64];

	//允许的最大输入通道数，如果为0，表示此设备只支持输出
    unsigned input_count;

	//允许的最大输出通道数，如果为0，表示此设备只支持输入
    unsigned output_count;
	
	//默认抽样率
    unsigned default_samples_per_sec;

	//语音驱动名
    char driver[32];

	//设备能力描述，比特掩码，参考pjmedia_aud_dev_cap
    unsigned caps;

	//参考 pjmedia_aud_dev_route. 暂不用
    unsigned routes;

	//暂不用
    unsigned ext_fmt_cnt;

} phonelib_aud_dev_info;

typedef void (*func_reg_state_callback)(int,PHONELIB_REG_STATE,int,const char*);	//注册事件回调函数指针
typedef void (*func_call_state_callback)(int,int,const char*,const char*,PHONELIB_CALL_STATE,int,const char*);	//呼叫事件回调函数指针
typedef void (*func_media_state_callback)(PHONELIB_MEDIA_STATE,const char*);	//媒体事件回调函数指针
typedef void (*func_network_state_callback)(PHONELIB_NETWORK_STATE,const char* );	//网络事件回调函数指针
 
int phonelib_init(int local_sip_port,const char* log_file, int log_level, bool log_b_append);
int phonelib_destroy();
int phonelib_add_account(const char* server, int server_port,const char* sip_account,const char* sip_password,int timeout,int* account_id);
int phonelib_remove_account(int account_id);
int phonelib_make_call_to(int account_id, const char* dest, int* call_id,const char* reserved);
int phonelib_answer_call(int callid);
int phonelib_drop_call(int callid);
int phonelib_get_audio_device_list(phonelib_aud_dev_info info[],unsigned* max);
int phonelib_get_active_audio_device(phonelib_aud_dev_info *mic_info,phonelib_aud_dev_info *spkr_info);
int phonelib_hold_call(int callid);
int phonelib_unhold_call(int callid);
int phonelib_send_dtmf(int callid, const char dtmf);
int phonelib_set_codecs( const char  *codec_string );
int phonelib_set_audio_device( const char  *mic_driver, const char* mic_dev_name, const char* spkr_driver, const char* spkr_dev_name);
int phonelib_adjust_tx_level(float level);//should between 0.0 to 2.0
int phonelib_adjust_rx_level(float level);//should between 0.0 to 2.0
int phonelib_mute_mic();
int phonelib_mute_spkr();
int phonelib_get_last_rx_tx_level(unsigned *rx_level, unsigned *tx_level);
char* phonelib_get_version_string();
int phonelib_set_reg_state_callback(func_reg_state_callback reg_state_callback);
int phonelib_set_call_state_callback(func_call_state_callback call_state_callback);
int phonelib_set_network_state_callback(func_network_state_callback  network_state_callback);
int phonelib_set_media_state_callback(func_media_state_callback network_media_callback);
 