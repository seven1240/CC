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

#include <bgcc.h>
#include <esl.h>
#include "ims_core.h"
#include "fs_struct.h"

class fs_opr_t {
private:
    uint32_t _fs_no;
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
        //_handle.sock=ESL_SOCK_INVALID;
        return IMS_SUCCESS;
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
    fs_opr_t(uint32_t no):
        _fs_no(no), _address(0), _port(0) {

        _pswd[0] = '\0';
        _pswd[LEN_16] = '\0';
        _recordbase[LEN_256] = '\0';
        bzero(&_handle, sizeof(esl_handle_t));
    }
    ~fs_opr_t() {
        disconnect();
    }
    inline uint32_t get_fs_no() {
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
    /**
     * @brief mark channel with session id
     *
     * @param [in] uuid   : channel id
     * @param [in] sid    : session id
     * @return  int32_t
     * @author dangdawei
     * @date 2012/7/5 21:02:39
     **/
    int32_t mark_sessionid(const char* uuid, uint64_t sid);
    /**
     * @brief check uuid existence
     *
     * @param [in] uuid   : channel id
     * @return  int32_t
     * @author dangdawei
     * @date 2012/7/5 21:02:39
     **/
    int32_t uuid_exists(const char* uuid);

    //////////////////////////////////////////事件处理//////////////////////////////////////
    int32_t subscribe_event(const char* event);
    int32_t subscribe_event_normal();
    int32_t subscribe_event_heartbeat();
    int32_t get_event(fs_event_t& event, uint32_t timeout);

    //////////////////////////////////////////呼叫处理//////////////////////////////////////
    int32_t originate(const char* ani, const char* dnis,
                      const char* caller_disp, const char* called_disp,
                      uint64_t sessionid = 0, uint32_t timeout = 60);

    int32_t single_originate(const char* ani, const char* caller_disp,
                             uint64_t sessionid = 0, bool return_ring_ready = false, bool bgapi = false,
                             char* uuid_output = NULL, uint32_t output_len = 0,
                             char* result = NULL, uint32_t result_len = 0);
    int32_t bridge(const char* uuid, const char* called_disp, const char* dnis);
    int32_t bridge_ex(const char* uuid, const char* called_disp, const char* dnis, bool isAsync = false,
                      bool return_ring_ready = true);
    int32_t uuid_bridge(const char* uuid1, const char* uuid2, char* uuid_output = NULL,
                        uint32_t output_len = 0);
    int32_t unbridge(const char* uuid);

    int32_t answer(const char* uuid);
    int32_t hangup(const char* uuid, const char* cause = NULL);

    int32_t conference(const char* uuid, const char* name);
    int32_t join_conference(const char* name, const char* dest_disp,
                            const char* destno, CONF_MODE mode = CONF_INSERT,
                            uint64_t sessionid = 0);
    int32_t unjoin_conference(const char* name, const char* uuid);
    int32_t conference_mute(const char* name, const char* member);
    int32_t conference_unmute(const char* name, const char* member);

    //////////////////////////////////////////媒体处理//////////////////////////////////////
    int32_t stop_media(const char* uuid);
    int32_t play(const char* uuid, const char* file, uint32_t count = 1);
    int32_t record(const char* uuid, const char* file, uint32_t time_s = 0);
    int32_t send_dtmf(const char* uuid, const char* keys);

    //////////////////////////////////////////媒体处理//////////////////////////////////////

private:
    int32_t get_var(const char* key, char* val, uint32_t val_len);
    int32_t get_head_val(const char* key, char* val, uint32_t val_len);
public:
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

    const static char* EVENT_NORMAL;
    const static char* EVENT_HEARTBEAT;
    const static char* RECORD_BASEDIR;
};

#define FUNC_BEGIN() \
    int32_t ret=IMS_FAIL_GENERAL;\
    char szcmd[LEN_512+1]={0};\
    const char *fs_resp=NULL;\
    do{
//mutex_t::locker_t lock(_mutex);
//if(!lock.is_acquired()){
//    ret=IMS_FAIL_LOCK;
//    break;
//}

#define FUNC_END() \
    }while(!is_handle_valid()&&IMS_SUCCESS==connect(_address,_port,_pswd,true));\
    return ret;


#endif  //__FS_OPR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
