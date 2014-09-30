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

#include <time.h>
#include "ivr_timer.h"
#include "lock.h"
#include "ivr_instance_manager.h"

IvrTimer::IvrTimer() {
}

IvrTimer::~IvrTimer() {
    clear_all_timer();
}

inline std::string timer_type_str(timer_type_t ttype) {
    switch (ttype) {
    case user_define:
        return "user_define";

    case ims_transagent:
        return "ims_transage";

    default:
        break;
    }

    return "unknown";
}

int32_t IvrTimer::add_timer(session_timer_id tid, time_t time, timer_type_t ttype) {
    double sec = difftime(time, ::time(NULL));
    IVR_DEBUG("IvrTimer::add_timer(%ld), type(%s), after(%ds)",
              tid, timer_type_str(ttype).c_str(), (int)sec);
    timer_index_t idx;
    idx.id = tid;
    idx.ttype = ttype;
    _ivr_timer_task.insert(std::make_pair(idx, time));
    return IVR_SUCCESS;
}

int32_t IvrTimer::delete_timer(session_timer_id id, timer_type_t ttype) {
    timer_index_t idx;
    idx.id = id;
    idx.ttype = ttype;

    if (_ivr_timer_task.erase(idx)) {
        IVR_TRACE("IvrTimer::delete_timer(%lu), type(%s) successful!",
                  id, timer_type_str(ttype).c_str());
    } else {
        IVR_TRACE("IvrTimer::delete_timer(%lu), type(%s) failed!",
                  id, timer_type_str(ttype).c_str());
    }

    return IVR_SUCCESS;
}

int32_t IvrTimer::check_timer(ivr_session_id_t sid) {
    time_t now = time(NULL);
    time_t when;
    double delta;
    timer_task_iterator itr, next_itr;

    IvrInstanceManager* manager;
    manager = IvrInstanceManager::get_instance();

    if (NULL == manager) {
        IVR_WARN("ivr instance manager should not be null");
        return -1;
    }

    itr = _ivr_timer_task.begin();

    while (itr != _ivr_timer_task.end()) {
        next_itr = itr;
        ++next_itr;

        when = itr->second;
        delta = difftime(when, now);

        //IVR_DEBUG("difftime %lf", delta);

        if (delta < 1e-6) {
            ivr_base_event_t* event_to_put = NULL;

            if (itr->first.ttype == user_define) {
                //·â×°IVRÊÂ¼þ
                ivr_other_event_t* event = new ivr_other_event_t;
                event->sessionId = sid;
                event->evt_type = ivr_base_event_t::OTHER_EVENT;
                event->evt_name = ivr_other_event_t::IVR_EVT_TIMEOUT;

                std::stringstream o;
                o << itr->first.id;
                o >> event->data;

                event_to_put = event;
            } else if (itr->first.ttype == ims_transagent) {
                ivr_ims_event_t* event = new ivr_ims_event_t;
                event->sessionId = sid;
                event->evt_type = ivr_base_event_t::IMS_EVENT;
                event->evt_name = ivr_ims_event_t::IVR_EVT_IMS_NOT_RESPONSE;
                //memset(&event->data, 0, sizeof(event->data));
                event->data.requstid = itr->first.id;

                event_to_put = event;
            }

            if (event_to_put) {
                if (IVR_SUCCESS != manager->put_ivr_event(event_to_put)) {
                    // insert failed, remove it from event queue
                    IVR_DEBUG("insert timer event failed!");
                    delete event_to_put;
                    event_to_put = NULL;
                }
            }

            IVR_TRACE("erase timer(%lu), type(%s)", itr->first.id, timer_type_str(itr->first.ttype).c_str());
            _ivr_timer_task.erase(itr);
        }

        itr = next_itr;
    }

    return IVR_SUCCESS;
}

int32_t IvrTimer::clear_all_timer() {
    IVR_TRACE("clear timer!");
    std::map<timer_index_t, time_t> tmp;
    _ivr_timer_task.swap(tmp);
    //_ivr_timer_task.clear();
    return IVR_SUCCESS;
}
