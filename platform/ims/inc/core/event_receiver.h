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

#ifndef  __EVENT_RECEIVER_H_
#define  __EVENT_RECEIVER_H_

#include <bgcc.h>
#include "common.h"
#include <fs_opr.h>
#include <fs_info.h>

namespace ims {


class base_recv_t : public bgcc::Runnable {
public:
    base_recv_t(fs_info_t* info,
                fs_opr_t* opr,
                int32_t timeout) :
        _info(info),
        _opr(opr),
        _timeout(timeout),
        _shutdown(false) {}

    virtual ~base_recv_t() {
    }

    virtual int32_t operator()(const bool* isstoped, void* param = NULL) = 0;

    void shutdown() {
        _shutdown = true;
    }

protected:
    fs_info_t*          _info;
    fs_opr_t*           _opr;
    int32_t             _timeout;
    bool                _shutdown;

};

class heartbeat_recv_t: public base_recv_t {
public:
    heartbeat_recv_t(fs_info_t* info, fs_opr_t* opr, int32_t _timeout) :
        base_recv_t(info, opr, _timeout) {
    }

    virtual int32_t operator()(const bool* isstoped, void* param = NULL);
};

typedef bgcc::SharedPointer<heartbeat_recv_t> heartbeat_recv_ptr;

class callevent_recv_t: public base_recv_t {
    std::vector<SessionIdT> manual_sessions;
public:
    callevent_recv_t(fs_info_t* info, fs_opr_t* opr, int32_t _timeout) :
        base_recv_t(info, opr, _timeout) {
    }

    virtual int32_t operator()(const bool* isstoped, void* param = NULL);
    /**
    * @brief 为每个manual session 模拟生成挂机事件
     *
     * @return  void
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/05 17:32:59
    **/
    void handle_manual_session();

private:
    void fs_inboud_handler(fs_event_t& evt);
};

typedef bgcc::SharedPointer<callevent_recv_t> callevent_recv_ptr;

}














#endif  //__EVENT_RECEIVER_H_

