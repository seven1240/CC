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

#ifndef  __FS_OPR_H_
#define  __FS_OPR_H_

#include <esl.h>
#include "common.h"
#include "fs_struct.h"

class fs_opr_t {
private:
    fw_id_t _fs_no;
    uint32_t _address;
    int32_t _port;
    char _pswd[LEN_16 + 1];
    char _recordbase[LEN_256 + 1];
    //mutex_t _mutex;       /**< 如果mgr对opr整体销毁，需要同步 */

    esl_handle_t _handle;
    /**
     * @brief 内部使用,不加锁
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/17 12:26:43
     **/
    inline int32_t disconnect() {
        esl_disconnect(&_handle);
        //bzero(&_handle,sizeof(esl_handle_t));
        return IVR_SUCCESS;
    }

    inline bool is_result_ok(const char* res)const {
        return (res && '+' == res[0] && 'o' == (0x20 | res[1]) && 'k' == (0x20 | res[2]))
               || (res && 'o' == (0x20 | res[0]) && 'k' == (0x20 | res[1]));
    }

    inline bool is_handle_valid()const {
        return _handle.connected && ESL_SOCK_INVALID != _handle.sock;
    }

    bool set_channel_attribute(const char* uuid, const char* param) {
        return esl_execute(&_handle, "set", param, uuid) == ESL_SUCCESS
               && is_result_ok(esl_event_get_header(_handle.last_sr_event, "Reply-Text"));
    }

public:
    enum CONF_MODE {
        CONF_INSERT,
        CONF_LISTEN
    };
    fs_opr_t(fw_id_t no):
        _fs_no(no), _address(0), _port(0) {

        _pswd[0] = '\0';
        _pswd[LEN_16] = '\0';
        _recordbase[LEN_256] = '\0';
        bzero(&_handle, sizeof(esl_handle_t));
    }
    ~fs_opr_t() {
        disconnect();
    }
    inline fw_id_t get_fs_no() {
        return _fs_no;
    }
    int32_t connect(uint32_t address, int32_t port, const char* pswd, bool reconnect = false);
    /**
     * @brief 配置更新，重新加载,并链接
     *
     * @param [in/out] address   : uint32_t
     * @param [in/out] port   : int32_t
     * @param [in/out] user   : const char*
     * @param [in/out] pswd   : const char*
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 20:02:39
     **/
    int32_t reset(uint32_t address, int32_t port, const char* pswd);
    int32_t register_session(const char* uuid, ivr_session_id_t sid);


    //////////////////////////////////////////事件处理//////////////////////////////////////
    int32_t subscribe_event(const char* event);
    int32_t subscribe_event_normal();
    int32_t subscribe_event_heartbeat();
    int32_t get_event(fs_event_t& event, uint32_t timeout);

    //////////////////////////////////////////呼叫处理//////////////////////////////////////
    int32_t originate(const char* ani, const char* dnis,
                      const char* caller_disp, const char* called_disp,
                      uint64_t sessionid = 0, uint32_t timeout = 60);

    int32_t bridge(const char* uuid, const char* called_disp, const char* dnis);
    int32_t uuid_bridge(const char* uuid1, const char* uuid2, char* uuid_output = NULL,
                        uint32_t output_len = 0);
    int32_t unbridge(const char* uuid);
    int32_t bridgeonly(const char* uuid1, const char* uuid2);
    int32_t bridgeex(const char* uuid, const char* caller, const char* called, bool external,
                     bool usbgm, const char* bgmfile);
    int32_t dial(ivr_session_id_t sessionid, const char* called_number,
                 const char* caller_number, uint32_t timeout = 30, bool external = true);

    int32_t answer(const char* uuid);
    int32_t hangup(const char* uuid, const char* cause = NULL);

    int32_t conference(const char* uuid, const char* name);
    int32_t join_conference(const char* name, const char* dest_disp, const char* destno,
                            CONF_MODE mode = CONF_INSERT, uint64_t sessionid = 0);
    int32_t unjoin_conference(const char* name, const char* uuid);
    int32_t conference_mute(const char* name, const char* member);
    int32_t conference_unmute(const char* name, const char* member);

    //////////////////////////////////////////媒体处理//////////////////////////////////////
    int32_t stop_media(const char* uuid);
    int32_t play(const char* uuid, const char* file, uint32_t count = 1);
    int32_t record(const char* uuid, const char* file, bool isstart);
    int32_t fs_opr_t::playnum(const char* uuid, const char* data, const char* basepath, bool isStr);
    int32_t send_dtmf(const char* uuid, const char* keys);
    int32_t collect(const char* callid, const char* playfile, uint32_t min, uint32_t max,
                    uint32_t timeout, const char* end);
    int32_t play_and_get_digits(const char* callid, const char* playfile, uint32_t min, uint32_t max,
                                uint32_t repeat, uint32_t timeout, const char* end, const char* invalidfile);

    //////////////////////////////////////////媒体处理//////////////////////////////////////

private:
    bool check_ivr_ip(const char* get_ip);
    int32_t get_var(const char* key, char* val, uint32_t val_len);
    int32_t get_head_val(const char* key, char* val, uint32_t val_len);
    int32_t eval(const char* key, char* val, uint32_t val_len);
private:
    esl_event_t*    _fs_last_event;

private:
    const static char* CMD_ORIGINATE_FMT;
    const static char* CMD_JOINCONFERENCE_FMT;
    const static char* CMD_UUIDBRIDGE_FMT;
    const static char* CMD_UNBRIDGE_FMT;
    const static char* CMD_UUIDSENDDTMF_FMT;
    const static char* CMD_RECORD_FMT;
    const static char* CMD_STOPRECORD_FMT;

    const static char* EVENT_NORMAL;
    const static char* EVENT_HEARTBEAT;
    const static char* RECORD_BASEDIR;

private:
    static inline bool check_result(const char* result);

    const static char* CMD_BRIDGE;
    const static char* CMD_BRIDGEEX;
    const static char* CMD_DIAL;
    const static char* CMD_END;
    const static char* CMD_SET;
    const static char* CMD_CREATE_UUID;
    const static char* CMD_COLLECT;
    const static char* CMD_UNDEF;
    const static char* CMD_FLUSH_DTMF;
    const static char* CMD_PLAY_WITH_COLLECT;

    const static char* RESULT_OK;
    const static char* REPLY_TEXT;

    const static char* FS_VAR_TMP;  ///< 事件临时缓冲区名称
};

#define FUNC_BEGIN() \
    int32_t ret=IVR_FAIL_GENERAL;\
    char szcmd[LEN_512+1]={0};\
    const char *fs_resp=NULL;\
    do{
//mutex_t::locker_t lock(_mutex);
//if(!lock.is_acquired()){
//    ret=IVR_FAIL_LOCK;
//    break;
//}

#define FUNC_END() \
    }while(!is_handle_valid()&&IVR_SUCCESS==connect(_address,_port,_pswd,true));\
    return ret;


#endif  //__FS_OPR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
