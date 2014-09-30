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


#include "acd_send_event_manager.h"
#include "acd_tool.h"

void acd_send_event::Method() {
    while (this->mIsLoop) {
        SendEventT* p_event = NULL;
        m_event_queue.BlockPop(p_event);

        if (!p_event) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "thread flag:%d p_event is null", m_thread_flag);
            continue;
        }

        if (!p_event->m_callback_proxy.is_valid()) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "thread flag:%d event id:%d m_callback_proxy is null", m_thread_flag, p_event->m_event_id);
            delete p_event;
            p_event = NULL;
            continue;
        }

        switch (p_event->m_event_type) {
        case AGENT_EVENT:
            p_event->m_callback_proxy->SendAgentEvent(p_event->m_agent_event);
            break;

        case MEDIA_EVENT:
            p_event->m_callback_proxy->SendMediaEvent(p_event->m_media_event);
            break;

        case ROUTE_EVENT:
            p_event->m_callback_proxy->SendQueueEvent(p_event->m_route_event);
            break;

        case OTHER_EVENT:
            p_event->m_callback_proxy->SendOtherEvent(p_event->m_other_event);
            break;

        default:
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "thread flag:%d event id:%d type error", m_thread_flag, p_event->m_event_id);
            break;
        }

        if (p_event->m_callback_proxy->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "thread flag:%d event id:%d Communication Error:%d", m_thread_flag, p_event->m_event_id,
                                        p_event->m_callback_proxy->get_errno());
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "thread flag:%d event id:%d Communication Success", m_thread_flag, p_event->m_event_id);
        }

        acd_tool::write_acd_event_log(*p_event);
        delete p_event;
        p_event = NULL;
    }
}

acd_send_event::acd_send_event(uint32_t flag) : m_thread_flag(flag) {
}

acd_send_event::~acd_send_event(void) {
}

void acd_send_event::in_queue(SendEventT* p_event) {
    assert(p_event != NULL);
    m_event_queue.BlockPush(p_event);
}

acd_send_event_manager::acd_send_event_manager(void) : m_max_thread(10) {
}

acd_send_event_manager::~acd_send_event_manager(void) {
}

void acd_send_event_manager::Initialize(uint32_t max_thread) {
    m_max_thread = max_thread;
    m_event_arrey.reserve(max_thread);

    for (uint32_t i = 0; i < max_thread; i++) {
        acd_send_event* p_acd_send_event = new acd_send_event(i);
        p_acd_send_event->Start();
        m_event_arrey.push_back(p_acd_send_event);
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "start send_event_thread count:%d", max_thread);
}

void acd_send_event_manager::Uninitialize() {
    for (vector<acd_send_event*>::iterator it = m_event_arrey.begin(); it != m_event_arrey.end();
            it++) {
        (*it)->Stop();
        delete *it;
        *it = NULL;
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "stop send_event_thread count:%d", m_max_thread);
}

void acd_send_event_manager::send_event(SendEventT* p_event, int64_t handle) {
    assert(p_event != NULL);

    vector<acd_send_event*>::size_type thread_flag = static_cast<vector<acd_send_event*>::size_type>
            (handle % m_max_thread);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "thread flag:%d event id:%d in queue", thread_flag, p_event->m_event_id);
    m_event_arrey[thread_flag]->in_queue(p_event);
}
