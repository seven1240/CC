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


#include "acd_tool.h"

IDCreater::IDCreater() : m_ID(0) {
}

IDCreater::~IDCreater() {
}

int64_t IDCreater::GetID() {
    SingleLocker s(&mLocker);

    if (m_ID >= LLONG_MAX) {
        m_ID = 0;
    }

    m_ID++;
    return m_ID;
}

acd_config acd_tool::m_config;
IDCreater acd_tool::m_handle;
IDCreater acd_tool::m_eventId;
IDCreater acd_tool::m_skillId;
Logger acd_tool::m_logger;
Logger acd_tool::m_eventlogger;
Logger acd_tool::m_calllogger;
acd_log_timer acd_tool::m_calllog_timer;
acd_receive_event_manager acd_tool::m_receive_event_manager;
acd_send_event_manager acd_tool::m_send_event_manager;
acd_agent_manager acd_tool::m_agent_manager;
acd_skill_manager acd_tool::m_skill_manager;
acd_backup* acd_tool::p_m_acd_backup = NULL;
acd_ims* acd_tool::p_m_acd_ims = NULL;
acd_main_server acd_tool::m_main_server;

void acd_tool::init_log() {
    m_logger.Initialize(m_config.m_log_count, m_config.m_log_filecount, LOG_DIR, LOG_FILE, ACD_VERSION,
                        true, m_config.m_log_level);
    m_eventlogger.Initialize(m_config.m_eventlog_count, m_config.m_eventlog_filecount, EVNET_LOG_DIR,
                             EVNET_LOG_FILE, ACD_VERSION, true, m_config.m_eventlog_level);
    m_calllogger.Initialize(m_config.m_calllog_count, m_config.m_calllog_filecount, CALL_LOG_DIR,
                            CALL_LOG_FILE, ACD_VERSION, false, m_config.m_calllog_level);
    m_calllog_timer.Initialize(m_config.m_calllog_timeout, &m_calllogger);
    bgcc::log_open(BGCC_LOG_CONFIG_FILE);  // 打开bgcc日志
}

void acd_tool::un_init_log() {
    bgcc::log_close();
    m_calllog_timer.Uninitialize();
    m_calllogger.UnInitialize();
    m_eventlogger.WriteLog("Exist");
    m_eventlogger.UnInitialize();
    m_logger.WriteLog("Exist");
    m_logger.UnInitialize();
}

void acd_tool::init_manager() {
    m_receive_event_manager.Initialize();
    m_send_event_manager.Initialize(m_config.m_sendevent_threadcount);
    m_agent_manager.Initialize(m_config.m_agent_timeout, m_config.m_default_anishow,
                               m_config.m_default_destshow, m_config.m_password);
    m_skill_manager.Initialize(m_config.m_request_timespan, m_config.m_queue_timespan,
                               m_config.m_skill_count);
}

void acd_tool::un_init_manager() {
    m_skill_manager.Uninitialize();
    m_agent_manager.Uninitialize();
    m_send_event_manager.Uninitialize();
    m_receive_event_manager.Uninitialize();
}

void acd_tool::init_connect() {
    p_m_acd_backup = new acd_backup(m_config.m_other_acdhost.c_str(), m_config.m_other_acdport,
                                    m_config.m_this_acdport, m_config.m_acdheartbeat_timesmax,
                                    m_config.m_acdheartbeat_timespan);
    p_m_acd_backup->Start();
    p_m_acd_ims = new acd_ims(m_config.m_main_server_ip.c_str(), m_config.m_main_server_port,
                              m_config.m_back_server_ip.c_str(), m_config.m_back_server_port,
                              m_config.m_ims_proxy_num, m_config.m_imsheartbeat_timesmax, m_config.m_imsheartbeat_timespan);
    p_m_acd_ims->Start();
    m_main_server.start_server(m_config.m_this_agentport, m_config.m_thread_num);
}

void acd_tool::un_init_connect() {
    m_main_server.stop_server();
    p_m_acd_ims->Stop();
    delete p_m_acd_ims;
    p_m_acd_ims = NULL;
    p_m_acd_backup->Stop();
    delete p_m_acd_backup;
    p_m_acd_backup = NULL;
}

void acd_tool::init() {
    if (m_config.read_config()) {
        cout << "acd init, read config success!" << endl;
    } else {
        cout << "acd init, read config error! acd exit!" << endl;
        exit(0);
    }

    init_log();
    init_manager();
    init_connect();
}

void acd_tool::un_init() {
    un_init_connect();
    un_init_manager();
    un_init_log();
}

acd::AcdResultT acd_tool::validate_agent(const string& agentId, const string& skill) {
    return m_config.validate_agent(agentId, skill);
}

acd::AcdResultT acd_tool::validate_agent(const string& agentId, const string& agentPwd,
        const string& skill) {
    return m_config.validate_agent(agentId, agentPwd, skill);
}

void acd_tool::GetSkill(acd::StringListT& skill) {
    m_config.GetSkill(skill);
}

void acd_tool::GetRestReason(acd::StringListT& restReason) {
    m_config.GetRestReason(restReason);
}

int64_t acd_tool::CreatHandle() {
    return m_handle.GetID();
}

int64_t acd_tool::CreatEventId() {
    return m_eventId.GetID();
}

int64_t acd_tool::CreatSkillId() {
    return m_skillId.GetID();
}

uint32_t acd_tool::LocalPort() {
    if (m_config.read_config()) {
        cout << "acd init, read config success!" << endl;
        return m_config.m_this_agentport;
    } else {
        cout << "acd init, read config error! acd exit!" << endl;
        exit(0);
    }
}

bool acd_tool::ResetConfig() {
    return m_config.reset_config();
}

void acd_tool::write_ims_event_log(const ims::CallEventT& event) {
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "================ ImsCallEvent ================");
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "sessionid        : %"SHOW_LONG"d", event.sessionid);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "callid           : %s", event.callid.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "device           : %s", event.device.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "eventType        : %s",
                           event.eventType.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "state            : %s", event.state.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "originalCallid   : %s", event.originalCallid.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "partyNum         : %d", event.partyNum);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "otherDevice      : %s", event.otherDevice.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "otherAttr        : %s",
                           event.otherAttr.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "originatingParty : %s", event.originatingParty.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "originalAni      : %s", event.originalAni.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "originalDnis     : %s", event.originalDnis.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "reason           : %s", event.reason.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "timestamp        : %"SHOW_LONG"d", event.timestamp);
}

void acd_tool::write_ims_event_log(const ims::MediaEventT& event) {
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "================ ImsMediaEvent ================");
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "sessionid        : %"SHOW_LONG"d", event.sessionid);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "callid           : %s", event.callid.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "device           : %s", event.device.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "eventType        : %s",
                           event.eventType.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "state            : %s", event.state.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "reason           : %s", event.reason.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "otherDevice      : %s", event.otherDevice.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "mediaBuffer      : %s", event.mediaBuffer.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "timestamp        : %"SHOW_LONG"d", event.timestamp);
}

void acd_tool::write_ims_event_log(const ims::RouteEventT& event) {
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "================ ImsRouteEvent ================");
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "sessionid        : %"SHOW_LONG"d", event.sessionid);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "callid           : %s", event.callid.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "device           : %s", event.device.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "eventType        : %s",
                           event.eventType.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "reason           : %s", event.reason.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "requstid         : %"SHOW_LONG"d", event.requstid);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "targetDevice     : %s", event.targetDevice.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "destService      : %s",
                           event.destService.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "requestType      : %s",
                           event.requestType.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "requestArgs      : %s", event.requestArgs.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "level            : %d", event.level);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "callerDn         : %s", event.callerDn.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "calleeDn         : %s", event.calleeDn.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "validtime        : %d", event.validtime);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "timeout          : %d", event.timeout);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "buffer           : %s", event.buffer.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "timestamp        : %"SHOW_LONG"d", event.timestamp);
}

void acd_tool::write_ims_event_log(const ims::OtherEventT& event) {
    if (ims::OtherEventTypeT::OG_HeartBeat == event.eventType.get_value()) {
        return;
    }

    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "================ ImsOtherEvent ================");
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "sessionid        : %"SHOW_LONG"d", event.sessionid);
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "callid           : %s", event.callid.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "device           : %s", event.device.c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "eventType        : %s",
                           event.eventType.get_desc().c_str());
    m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "timestamp        : %"SHOW_LONG"d", event.timestamp);
}

void acd_tool::write_acd_event_log(const SendEventT& event) {
    switch (event.m_event_type) {
    case AGENT_EVENT: {
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] ================ AcdAgentEvent ================");
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] event_id         : %"SHOW_LONG"d",
                               event.m_event_id);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] m_event_type     : %d", event.m_event_type);

        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentId          : %s",
                               event.m_agent_event.agentId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] eventId          : %s",
                               event.m_agent_event.eventId.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentDn          : %s",
                               event.m_agent_event.agentDn.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] callId           : %s",
                               event.m_agent_event.callId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] sessionid        : %"SHOW_LONG"d",
                               event.m_agent_event.sessionId);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentStatus      : %s",
                               event.m_agent_event.agentStatus.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalCallid   : %s",
                               event.m_agent_event.originalCallid.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] partyNum         : %d",
                               event.m_agent_event.partyNum);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] otherParty       : %s",
                               event.m_agent_event.otherParty.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] otherAttr        : %s",
                               event.m_agent_event.otherAttr.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originatingParty : %s",
                               event.m_agent_event.originatingParty.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalAni      : %s",
                               event.m_agent_event.originalAni.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalDnis     : %s",
                               event.m_agent_event.originalDnis.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] reason           : %s",
                               event.m_agent_event.reason.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] timestamp        : %"SHOW_LONG"d",
                               event.m_agent_event.timestamp);
        break;
    }

    case MEDIA_EVENT: {
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] ================ AcdMediaEvent ================");
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] event_id         : %"SHOW_LONG"d",
                               event.m_event_id);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] m_event_type     : %d", event.m_event_type);

        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentId          : %s",
                               event.m_media_event.agentId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] eventType        : %s",
                               event.m_media_event.eventType.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentDn          : %s",
                               event.m_media_event.agentDn.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] callId           : %s",
                               event.m_media_event.callId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] sessionid        : %"SHOW_LONG"d",
                               event.m_media_event.sessionId);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] state            : %s",
                               event.m_media_event.state.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] reason           : %s",
                               event.m_media_event.reason.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] otherParty       : %s",
                               event.m_media_event.otherParty.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] buffer           : %s",
                               event.m_media_event.buffer.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] timestamp        : %"SHOW_LONG"d",
                               event.m_media_event.timestamp);
        break;
    }

    case ROUTE_EVENT: {
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] ================ AcdRouteEvent ================");
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] event_id         : %"SHOW_LONG"d",
                               event.m_event_id);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] m_event_type     : %d", event.m_event_type);

        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentId          : %s",
                               event.m_route_event.agentId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] eventType        : %s",
                               event.m_route_event.eventType.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentDn          : %s",
                               event.m_route_event.agentDn.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] callId           : %s",
                               event.m_route_event.callId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] sessionid        : %"SHOW_LONG"d",
                               event.m_route_event.sessionId);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] requestId        : %"SHOW_LONG"d",
                               event.m_route_event.requestId);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalAni      : %s",
                               event.m_route_event.originalAni.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalDnis     : %s",
                               event.m_route_event.originalDnis.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] timestamp        : %"SHOW_LONG"d",
                               event.m_route_event.timestamp);
        break;
    }

    case OTHER_EVENT: {
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] ================ AcdOtherEvent ================");
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] event_id         : %"SHOW_LONG"d",
                               event.m_event_id);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] m_event_type     : %d", event.m_event_type);

        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentId          : %s",
                               event.m_other_event.agentId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] eventType        : %s",
                               event.m_other_event.eventType.get_desc().c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] agentDn          : %s",
                               event.m_other_event.agentDn.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] callId           : %s",
                               event.m_other_event.callId.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] sessionid        : %"SHOW_LONG"d",
                               event.m_other_event.sessionId);
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalAni      : %s",
                               event.m_other_event.originalAni.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] originalDnis     : %s",
                               event.m_other_event.originalDnis.c_str());
        m_eventlogger.WriteLog(LOG_LEVEL_NOTICE, "[ACD] timestamp        : %"SHOW_LONG"d",
                               event.m_other_event.timestamp);
        break;
    }

    default: {
        m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "event type:%d error",
                          event.m_event_type);
        break;
    }
    }
}

acd::CallEventTypeT acd_tool::TranslateCallEvent(const ims::CallEventTypeT& type) {
    acd::CallEventTypeT ret = acd::CallEventTypeT::CeUnKnownEvent;

    switch (type.get_value()) {
    case ims::CallEventTypeT::SG_UnKnownEvent:
        ret = acd::CallEventTypeT::CeUnKnownEvent;
        break;

    case ims::CallEventTypeT::SG_InboundCall_InternalCall:
        ret = acd::CallEventTypeT::CeInboundCallInternalCall;
        break;

    case ims::CallEventTypeT::SG_DestSeized_InternalCall:
        ret = acd::CallEventTypeT::CeDestSeizedInternalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyAnswered_InternalCall:
        ret = acd::CallEventTypeT::CeThisPartyAnsweredInternalCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyAnswered_InternalCall:
        ret = acd::CallEventTypeT::CeOtherPartyAnsweredInternalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnected_InternalCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectedInternalCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnected_InternalCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectedInternalCall;
        break;

    case ims::CallEventTypeT::SG_InboundCall_NormalCall:
        ret = acd::CallEventTypeT::CeInboundCallNormalCall;
        break;

    case ims::CallEventTypeT::SG_DestSeized_NormalCall:
        ret = acd::CallEventTypeT::CeDestSeizedNormalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyAnswered_NormalCall:
        ret = acd::CallEventTypeT::CeThisPartyAnsweredNormalCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyAnswered_NormalCall:
        ret = acd::CallEventTypeT::CeOtherPartyAnsweredNormalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnected_NormalCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectedNormalCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnected_NormalCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectedNormalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartySuspended_NormalCall:
        ret = acd::CallEventTypeT::CeThisPartySuspendedNormalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyRetrieved_NormalCall:
        ret = acd::CallEventTypeT::CeThisPartyRetrievedNormalCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyTransferred_NormalCall:
        ret = acd::CallEventTypeT::CeThisPartyTransferredNormalCall;
        break;

    case ims::CallEventTypeT::SG_DestSeized_ConsultCall:
        ret = acd::CallEventTypeT::CeDestSeizedConsultCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyAnswered_ConsultCall:
        ret = acd::CallEventTypeT::CeOtherPartyAnsweredConsultCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnected_ConsultCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectedConsultCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnected_ConsultCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectedConsultCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyTransferred_ConsultCall:
        ret = acd::CallEventTypeT::CeThisPartyTransferredConsultCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyTransferred_ConsultCall:
        ret = acd::CallEventTypeT::CeOtherPartyTransferredConsultCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyConferenced_ConferenceCall:
        ret = acd::CallEventTypeT::CeThisPartyConferencedConferenceCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyConferenced_ConferenceCall:
        ret = acd::CallEventTypeT::CeOtherPartyConferencedConferenceCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnect_ConferenceCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectConferenceCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnect_ConferenceCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectConferenceCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyConferenced_MonitorCall:
        ret = acd::CallEventTypeT::CeThisPartyConferencedMonitorCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyConferenced_MonitorCall:
        ret = acd::CallEventTypeT::CeOtherPartyConferencedMonitorCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnect_MonitorCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectMonitorCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectMonitorCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyConferenced_IntrudeCall:
        ret = acd::CallEventTypeT::CeThisPartyConferencedIntrudeCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyConferenced_IntrudeCall:
        ret = acd::CallEventTypeT::CeOtherPartyConferencedIntrudeCall;
        break;

    case ims::CallEventTypeT::SG_ThisPartyDisconnect_IntrudeCall:
        ret = acd::CallEventTypeT::CeThisPartyDisconnectIntrudeCall;
        break;

    case ims::CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall:
        ret = acd::CallEventTypeT::CeOtherPartyDisconnectIntrudeCall;
        break;

    default:
        ret = acd::CallEventTypeT::CeUnKnownEvent;
        break;
    }

    return ret;
}

acd::PartyAttributeT acd_tool::TranslatePartyAtt(const ims::PartyAttributeT& type) {
    acd::PartyAttributeT ret = acd::PartyAttributeT::PaUnknown;

    switch (type.get_value()) {
    case ims::PartyAttributeT::P_Unknown:
        ret = acd::PartyAttributeT::PaUnknown;
        break;

    case ims::PartyAttributeT::P_Internal:
        ret = acd::PartyAttributeT::PaInternal;
        break;

    case ims::PartyAttributeT::P_Normal:
        ret = acd::PartyAttributeT::PaNormal;
        break;

    default:
        ret = acd::PartyAttributeT::PaUnknown;
        break;
    }

    return ret;
}

acd::CallEventReasonT acd_tool::TranslateCallReason(const ims::CallEventReasonT& type) {
    acd::CallEventReasonT ret = acd::CallEventReasonT::CerSuccess;

    switch (type.get_value()) {
    case ims::CallEventReasonT::ReasonSuccess:
        ret = acd::CallEventReasonT::CerSuccess;
        break;

    case ims::CallEventReasonT::ResaonInvokeComplete:
        ret = acd::CallEventReasonT::CerInvokeComplete;
        break;

    case ims::CallEventReasonT::ReasonCallDestBusy:
        ret = acd::CallEventReasonT::CerCallDestBusy;
        break;

    case ims::CallEventReasonT::ReasonCallNoAnswer:
        ret = acd::CallEventReasonT::CerCallNoAnswer;
        break;

    case ims::CallEventReasonT::ReasonCallDestUnknown:
        ret = acd::CallEventReasonT::CerCallDestUnknown;
        break;

    case ims::CallEventReasonT::ReasonCallDestInvalid:
        ret = acd::CallEventReasonT::CerCallDestInvalid;
        break;

    case ims::CallEventReasonT::ReasonCallTimeout:
        ret = acd::CallEventReasonT::CerCallTimeout;
        break;

    default:
        ret = acd::CallEventReasonT::CerSuccess;
        break;
    }

    return ret;
}

acd::MediaEventTypeT acd_tool::TranslateMediaEvent(const ims::MediaEventTypeT& type) {
    acd::MediaEventTypeT ret = acd::MediaEventTypeT::MeUnKownEvent;

    switch (type.get_value()) {
    case ims::MediaEventTypeT::MG_UnknownEvent:
        ret = acd::MediaEventTypeT::MeUnKownEvent;
        break;

    case ims::MediaEventTypeT::MG_TP_Record_Started:
        ret = acd::MediaEventTypeT::MeTpRecordStarted;
        break;

    case ims::MediaEventTypeT::MG_OP_Record_Started:
        ret = acd::MediaEventTypeT::MeOpRecordStarted;
        break;

    case ims::MediaEventTypeT::MG_TP_Record_Done:
        ret = acd::MediaEventTypeT::MeTpRecordDone;
        break;

    case ims::MediaEventTypeT::MG_OP_Record_Done:
        ret = acd::MediaEventTypeT::MeOpRecordDone;
        break;

    default:
        ret = acd::MediaEventTypeT::MeUnKownEvent;
        break;
    }

    return ret;
}

acd::MediaStateT acd_tool::TranslateMediaState(const ims::MediaStateT& type) {
    acd::MediaStateT ret = acd::MediaStateT::MsUnknownState;

    switch (type.get_value()) {
    case ims::MediaStateT::MG_UnknownState:
        ret = acd::MediaStateT::MsUnknownState;
        break;

    case ims::MediaStateT::MG_IdleState:
        ret = acd::MediaStateT::MsIdleState;
        break;

    case ims::MediaStateT::MG_RecordingState:
        ret = acd::MediaStateT::MsRecordingState;
        break;

    default:
        ret = acd::MediaStateT::MsUnknownState;
        break;
    }

    return ret;
}

acd::MediaEventReasonT acd_tool::TranslateMediaReason(const ims::MediaEventReasonT& type) {
    acd::MediaEventReasonT ret = acd::MediaEventReasonT::MerMediaEnd;

    switch (type.get_value()) {
    case ims::MediaEventReasonT::ReasonMediaUnknown:
        ret = acd::MediaEventReasonT::MerMediaUnknown;
        break;

    case ims::MediaEventReasonT::ReasonMediaEnd:
        ret = acd::MediaEventReasonT::MerMediaEnd;
        break;

    case ims::MediaEventReasonT::ReasonMediaOther:
        ret = acd::MediaEventReasonT::MerMediaOther;
        break;

    default:
        ret = acd::MediaEventReasonT::MerMediaUnknown;
        break;
    }

    return ret;
}
