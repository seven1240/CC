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


#include "acd_receive_event_manager.h"
#include "acd_tool.h"

void acd_callevent_receiver::Method() {
    while (this->mIsLoop) {
        ims::CallEventT* p_event = NULL;
        m_event_queue.BlockPop(p_event);

        if (!p_event) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "p_event is null");
            continue;
        }

        acd_tool::m_agent_manager.ProcessIMSEvent(*p_event);
        delete p_event;
        p_event = NULL;
    }
}

acd_callevent_receiver::acd_callevent_receiver() {
}

acd_callevent_receiver::~acd_callevent_receiver() {
}

void acd_callevent_receiver::push_event(const ims::CallEventT& event) {
    ims::CallEventT* p_event = new ims::CallEventT(event);
    m_event_queue.BlockPush(p_event);
}

void acd_mediaevent_receiver::Method() {
    while (this->mIsLoop) {
        ims::MediaEventT* p_event = NULL;
        m_event_queue.BlockPop(p_event);

        if (!p_event) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "p_event is null");
            continue;
        }

        acd_tool::m_agent_manager.ProcessIMSEvent(*p_event);
        delete p_event;
        p_event = NULL;
    }
}

acd_mediaevent_receiver::acd_mediaevent_receiver() {
}

acd_mediaevent_receiver::~acd_mediaevent_receiver() {
}

void acd_mediaevent_receiver::push_event(const ims::MediaEventT& event) {
    ims::MediaEventT* p_event = new ims::MediaEventT(event);
    m_event_queue.BlockPush(p_event);
}

void acd_routeevent_receiver::Method() {
    while (this->mIsLoop) {
        ims::RouteEventT* p_event = NULL;
        m_event_queue.BlockPop(p_event);

        if (!p_event) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "p_event is null");
            continue;
        }

        switch (p_event->requestType.get_value()) {
        case ims::RouteRequestTypeT::RR_TypeUnknown:
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "request type:%s",
                                        p_event->requestType.get_desc().c_str());
            break;

        case ims::RouteRequestTypeT::RR_TypeSkill:
            acd_tool::m_skill_manager.ProcessIMSEvent(*p_event);
            break;

        case ims::RouteRequestTypeT::RR_TypePrivate:
        case ims::RouteRequestTypeT::RR_TypePrivateList:
            acd_tool::m_agent_manager.ProcessIMSEvent(*p_event);
            break;

        default:
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "request type error:%s", p_event->requestType.get_desc().c_str());
            break;
        }

        delete p_event;
        p_event = NULL;
    }
}

acd_routeevent_receiver::acd_routeevent_receiver() {
}

acd_routeevent_receiver::~acd_routeevent_receiver() {
}

void acd_routeevent_receiver::push_event(const ims::RouteEventT& event) {
    ims::RouteEventT* p_event = new ims::RouteEventT(event);
    m_event_queue.BlockPush(p_event);
}

void acd_otherevent_receiver::Method() {
    while (this->mIsLoop) {
        ims::OtherEventT* p_event = NULL;
        m_event_queue.BlockPop(p_event);

        if (!p_event) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "p_event is null");
            continue;
        }

        switch (p_event->eventType.get_value()) {
        case ims::OtherEventTypeT::OG_HeartBeat:
        case ims::OtherEventTypeT::OG_SessionCreate:
            //acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "event type:%s", p_event->eventType.get_desc().c_str());
            break;

        case ims::OtherEventTypeT::OG_OperationFailed:
            acd_tool::m_agent_manager.ProcessIMSEvent(*p_event);
            break;

        default:
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "event type error:%s", p_event->eventType.get_desc().c_str());
            break;
        }

        delete p_event;
        p_event = NULL;
    }
}

acd_otherevent_receiver::acd_otherevent_receiver() {
}

acd_otherevent_receiver::~acd_otherevent_receiver() {
}

void acd_otherevent_receiver::push_event(const ims::OtherEventT& event) {
    ims::OtherEventT* p_event = new ims::OtherEventT(event);
    m_event_queue.BlockPush(p_event);
}

acd_receive_event_manager::acd_receive_event_manager() {
}

acd_receive_event_manager::~acd_receive_event_manager() {
}

void acd_receive_event_manager::Initialize() {
    m_callevent_receiver.Start();
    m_mediaevent_receiver.Start();
    m_routeevent_receiver.Start();
    m_otherevent_receiver.Start();
}

void acd_receive_event_manager::Uninitialize() {
    m_callevent_receiver.Stop();
    m_mediaevent_receiver.Stop();
    m_routeevent_receiver.Stop();
    m_otherevent_receiver.Stop();
}

void acd_receive_event_manager::push_event(const ims::CallEventT& event) {
    m_callevent_receiver.push_event(event);
}

void acd_receive_event_manager::push_event(const ims::MediaEventT& event) {
    m_mediaevent_receiver.push_event(event);
}

void acd_receive_event_manager::push_event(const ims::RouteEventT& event) {
    m_routeevent_receiver.push_event(event);
}

void acd_receive_event_manager::push_event(const ims::OtherEventT& event) {
    m_otherevent_receiver.push_event(event);
}
