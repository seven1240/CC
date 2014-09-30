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

#include <fs_opr.h>
#include <fs_info.h>
#include <bgcc.h>

class base_recv_t : public bgcc::Runnable {
public:
    base_recv_t(fs_info_t* info,
                fs_opr_t* opr,
                int32_t timeout) :
        _info(info),
        _opr(opr),
        _timeout(timeout),
        _shutdown(true) {
    }

    virtual ~base_recv_t() {
    }


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

    virtual int32_t operator()(const bool*, void* param);
};

typedef bgcc::SharedPointer<heartbeat_recv_t> heartbeat_recv_ptr;

class callevent_recv_t: public base_recv_t {
public:
    callevent_recv_t(fs_info_t* info, fs_opr_t* opr, int32_t _timeout) :
        base_recv_t(info, opr, _timeout) {
    }
    virtual int32_t operator()(const bool*, void* param);
private:
    int32_t log_ivrevent(const ivr_base_event_t* ivr_evt);

    int32_t compact_callevt_base(ivr_base_event_t const* ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_mediaevt_base(ivr_base_event_t const* ivr_evt, const fs_event_t& fs_evt);

    int32_t compact_ivr_answer_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_hangup_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_destroy_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_alert_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_bridge_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_unbridge_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_callfail_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);

    int32_t compact_ivr_playend_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_notfound_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_getdigits_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_dtmf_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_recordstart_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
    int32_t compact_ivr_recordstop_evt(ivr_base_event_t** ivr_evt, const fs_event_t& fs_evt);
};

typedef bgcc::SharedPointer<callevent_recv_t> callevent_recv_ptr;



#endif  //__EVENT_RECEIVER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
