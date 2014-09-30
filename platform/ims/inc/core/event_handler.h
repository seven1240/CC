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

#ifndef  __EVENT_PROCESSER_H_
#define  __EVENT_PROCESSER_H_


#include <bgcc.h>
#include "common.h"
#include "queue.h"
#include "fs_struct.h"

namespace ims {

class event_handler_t : public bgcc::Runnable {
public:
    event_handler_t(int32_t timeout);

    virtual int32_t operator()(const bool* isstoped, void* param = NULL);

    void shutdown() {
        _shutdown = true;
    }
    void stop() {
        _stopping = true;
    }
    void push_event(const fs_event_t& ev) {
        if (_shutdown || _stopping) {
            return;
        }

        _q.put(ev);
    }
    void do_real_handle_event(const fs_event_t& evt);
    void handle_makecall_event(const fs_event_t& evt);
    void handle_hold_event(const fs_event_t& evt);
    void handle_retrieve_event(const fs_event_t& evt);
    void handle_consult_event(const fs_event_t& evt);
    void handle_reconnect_event(const fs_event_t& evt);
    void handle_transfer_event(const fs_event_t& evt);
    void handle_conference_event(const fs_event_t& evt);
    void handle_inbound_agent(const fs_event_t& evt);
    void handle_record_event(const fs_event_t& evt);
    void handle_singlesteptransfer_event(const fs_event_t& evt);
    void handle_singlestepconference_event(const fs_event_t& evt, bool binsert = true);
    void handle_ivrtransfer_event(const fs_event_t& evt);

#define debug_func(f,evt)\
    const event_data_normal_t& edata=evt.event_data.normal;\
    ims_session_manager_t *session_mgr=ims_session_manager_t::instance();\
    TRACE_LOG("process %s(sid=%lu,cid=%lu,name=%s,id=%s,othername=%s,otherid=%s) in "f" handler"\
            ,evt.name,evt.sessionid,evt.callid,\
            edata.channel_name,edata.uuid,\
            edata.other_channel_name,edata.other_uuid);

    int32_t get_queue_size() {
        return _q.size();
    }
private:
    int32_t                 _timeout;
    bool                    _shutdown;
    bool                    _stopping;
    queue_t<fs_event_t>     _q;

    void handle_hangup(const ims_session_operation_t operation, const fs_event_t& evt);
};

typedef bgcc::SharedPointer<event_handler_t> event_handler_ptr;

}

#endif  //__EVENT_PROCESSER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
