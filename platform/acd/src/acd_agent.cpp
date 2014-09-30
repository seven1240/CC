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


#include "acd_agent.h"
#include "acd_tool.h"

void acd_agent::WriteTraceLog(const string& restReason) {
    ostringstream strbuf;
    strbuf << '2'
           << ',' << m_agentId
           << ',' << m_agentDn
           << ',' << m_skill
           << ',' << m_agentStatus.get_value()
           << ',' << static_cast<int64_t>(m_currStatusTime)
           << ',' << restReason;
    acd_tool::m_calllogger.WriteLog(strbuf.str().c_str());
}

void acd_agent::SetStatus(const acd::AgentStatusT& agentStatus, const acd::CallEventReasonT& reason,
                          const string& restReason) {
    time_t lastStatusTime = m_currStatusTime;
    acd::AgentStatusT lastAgentStatus = m_agentStatus;
    m_currStatusTime = time(NULL);
    m_agentStatus = agentStatus;

    switch (lastAgentStatus.get_value()) {
    case acd::AgentStatusT::AsReadyState:
        m_freeTotalTime += m_currStatusTime - lastStatusTime;
        break;

    case acd::AgentStatusT::AsBusyState:
        m_busyTotalTime += m_currStatusTime - lastStatusTime;
        break;

    case acd::AgentStatusT::AsRestState:
        m_restTotalTime += m_currStatusTime - lastStatusTime;
        break;

    default:
        break;
    }

    SendEventT* p_agentEvent = new SendEventT;
    p_agentEvent->m_event_id                     = acd_tool::CreatEventId();
    p_agentEvent->m_callback_proxy               = m_callback_ptr;
    p_agentEvent->m_event_type                   = AGENT_EVENT;
    p_agentEvent->m_agent_event.agentId          = m_agentId;
    p_agentEvent->m_agent_event.eventId          = acd::CallEventTypeT::CeUnKnownEvent;
    p_agentEvent->m_agent_event.agentDn          = m_agentDn;
    p_agentEvent->m_agent_event.callId           = "";
    p_agentEvent->m_agent_event.sessionId        = 0;
    p_agentEvent->m_agent_event.agentStatus      = m_agentStatus;
    p_agentEvent->m_agent_event.originalCallid   = "";
    p_agentEvent->m_agent_event.partyNum         = 0;
    p_agentEvent->m_agent_event.otherParty       = "";
    p_agentEvent->m_agent_event.otherAttr        = acd::PartyAttributeT::PaUnknown;
    p_agentEvent->m_agent_event.originatingParty = "";
    p_agentEvent->m_agent_event.originalAni      = "";
    p_agentEvent->m_agent_event.originalDnis     = "";
    p_agentEvent->m_agent_event.reason           = reason;
    p_agentEvent->m_agent_event.timestamp        = bgcc::TimeUtil::get_timestamp_us();

    WriteTraceLog(restReason);
    acd_tool::m_send_event_manager.send_event(p_agentEvent, m_handle);
}

void acd_agent::Record() {
    m_recordFilename = bgcc::TimeUtil::format_time(m_currStatusTime,
                       "%Y%m%d") + "/" + m_agentId + "/" + m_callId + "_" + bgcc::TimeUtil::get_time() + ".wav";
    acd_tool::p_m_acd_ims->Record(m_sessionId, m_agentId, m_agentDn, m_recordFilename, 0, "");
}

void acd_agent::Reset() {
    m_sessionId = 0;
    m_callId.clear();
    m_recordFilename.clear();
    m_callTime = 0;
    m_answerTime = 0;
    m_origCaller.clear();
    m_origCallee.clear();
}

acd_agent::acd_agent() :
    m_agentId(""), m_agentDn(""), m_statusChangetype(acd::StatusChangeT::ScBusy), m_autoAnswer(true),
    m_skill(""), m_handle(0),
    m_sessionId(0), m_callId(""), m_requestId(0), m_validTime(0), m_heartbeatTime(0),
    m_recordFilename(""),
    m_loginTime(0), m_agentStatus(acd::AgentStatusT::AsUnLoginState), m_currStatusTime(0),
    m_callTime(0), m_answerTime(0), m_origCaller(""), m_origCallee(""), m_callTimes(0),
    m_answerTimes(0), m_freeTotalTime(0), m_busyTotalTime(0), m_restTotalTime(0), m_callTotalTime(0),
    m_answerTotalTime(0), m_agentIP("") {
}

acd_agent::~acd_agent(void) {
}

string acd_agent::GetAgentId() {
    SingleRWLocker s(&m_RWLock, false);
    return m_agentId;
}

string acd_agent::GetAgentDn() {
    SingleRWLocker s(&m_RWLock, false);
    return m_agentDn;
}

string acd_agent::GetAgentSkill() {
    SingleRWLocker s(&m_RWLock, false);
    return m_skill;
}

int64_t acd_agent::GetHandle() {
    SingleRWLocker s(&m_RWLock, false);
    return m_handle;
}

ims::SessionIdT acd_agent::GetSessionId() {
    SingleRWLocker s(&m_RWLock, false);
    return m_sessionId;
}

string acd_agent::GetRecordFileName() {
    SingleRWLocker s(&m_RWLock, false);
    return m_recordFilename;
}

void acd_agent::GetAgentDetail(acd::AgentInfoT& agentInfo) {
    SingleRWLocker s(&m_RWLock, false);

    agentInfo.agentId         = m_agentId;
    agentInfo.agentDn         = m_agentDn;
    agentInfo.loginTime       = m_loginTime;
    agentInfo.currStatus      = m_agentStatus;
    agentInfo.currStatusTime  = m_currStatusTime;
    agentInfo.answerTime      = m_answerTime;
    agentInfo.currTime        = time(NULL);
    agentInfo.origCaller      = m_origCaller;
    agentInfo.origCallee      = m_origCallee;
    agentInfo.privQueueNum    = 0;
    agentInfo.callTimes       = m_callTimes;
    agentInfo.answerTimes     = m_answerTimes;
    agentInfo.freeTotalTime   = m_freeTotalTime;
    agentInfo.busyTotalTime   = m_busyTotalTime;
    agentInfo.resetTotalTime  = m_restTotalTime;
    agentInfo.callTotalTime   = m_callTotalTime;
    agentInfo.answerTotalTime = m_answerTotalTime;
    agentInfo.agentIP         = m_agentIP;
}

void acd_agent::lock(const ims::RouteEventT& event, time_t waitbegin) {
    SingleRWLocker s(&m_RWLock, true);

    m_requestId = event.requstid;
    m_validTime = event.validtime;
    SetStatus(acd::AgentStatusT::AsLockState, acd::CallEventReasonT::CerSuccess);

    if (m_callinfo.isValid()) {
        m_callinfo.WriteCallLog();
        m_callinfo.reset();
    }

    m_callinfo.Initial(event.sessionid, event.callid, m_agentId, m_agentDn, m_skill, event.callerDn,
                       m_agentDn, waitbegin, time(NULL));
    m_callinfo.SetRoutecall();
}

bool acd_agent::unlock(const ims::RouteEventT& event) {
    SingleRWLocker s(&m_RWLock, true);

    if (m_requestId != event.requstid) {
        return false;
    }

    if (m_agentStatus == acd::AgentStatusT::AsLockState) {
        if (m_statusChangetype == acd::StatusChangeT::ScBusy) {
            SetStatus(acd::AgentStatusT::AsBusyState, acd::CallEventReasonT::CerIdleUnlock);
        } else {
            SetStatus(acd::AgentStatusT::AsReadyState, acd::CallEventReasonT::CerIdleUnlock);
        }
    }

    if (m_callinfo.isValid()) {
        m_callinfo.WriteCallLog();
        m_callinfo.reset();
    }

    return true;
}

bool acd_agent::unlockTimeout() {
    SingleRWLocker s(&m_RWLock, true);

    if (m_agentStatus == acd::AgentStatusT::AsLockState
            && m_validTime <= time(NULL) - m_currStatusTime) {
        if (m_statusChangetype == acd::StatusChangeT::ScBusy) {
            SetStatus(acd::AgentStatusT::AsBusyState, acd::CallEventReasonT::CerIdleUnlock);
        } else {
            SetStatus(acd::AgentStatusT::AsReadyState, acd::CallEventReasonT::CerIdleUnlock);
        }

        if (m_callinfo.isValid()) {
            m_callinfo.WriteCallLog();
            m_callinfo.reset();
        }

        return true;
    }

    return false;
}

bool acd_agent::isCalling() {
    SingleRWLocker s(&m_RWLock, false);
    return 0 < m_callTime;
}

time_t acd_agent::GetCurrStatusTime() {
    SingleRWLocker s(&m_RWLock, false);
    return m_currStatusTime;
}

uint64_t acd_agent::GetHeartbeatTime() {
    SingleRWLocker s(&m_RWLock, false);
    return m_heartbeatTime;
}

bool acd_agent::AssignDn() {
    return acd_tool::p_m_acd_ims->Assign(m_agentId, m_agentDn, ims::DnTypeT::AgentDn);
}

void acd_agent::ProcessIMSEvent(const ims::CallEventT& event) {
    SingleRWLocker s(&m_RWLock, true);

    m_sessionId = event.sessionid;
    m_callId = event.callid;
    time_t lastStatusTime = m_currStatusTime;
    acd::AgentStatusT lastAgentStatus = m_agentStatus;
    m_currStatusTime = time(NULL);

    switch (lastAgentStatus.get_value()) {
    case acd::AgentStatusT::AsReadyState:
        m_freeTotalTime += m_currStatusTime - lastStatusTime;
        break;

    case acd::AgentStatusT::AsBusyState:
        m_busyTotalTime += m_currStatusTime - lastStatusTime;
        break;

    case acd::AgentStatusT::AsRestState:
        m_restTotalTime += m_currStatusTime - lastStatusTime;
        break;

    default:
        break;
    }

    SendEventT* p_agentEvent = new SendEventT;
    p_agentEvent->m_event_id                     = acd_tool::CreatEventId();
    p_agentEvent->m_callback_proxy               = m_callback_ptr;
    p_agentEvent->m_event_type                   = AGENT_EVENT;
    p_agentEvent->m_agent_event.agentId          = m_agentId;
    p_agentEvent->m_agent_event.eventId          = acd_tool::TranslateCallEvent(event.eventType);
    p_agentEvent->m_agent_event.agentDn          = event.device;
    p_agentEvent->m_agent_event.callId           = event.callid;
    p_agentEvent->m_agent_event.sessionId        = event.sessionid;
    //p_agentEvent->m_agent_event.agentStatus      = m_agentStatus;
    p_agentEvent->m_agent_event.originalCallid   = event.originalCallid;
    p_agentEvent->m_agent_event.partyNum         = event.partyNum;
    p_agentEvent->m_agent_event.otherParty       = event.otherDevice;
    p_agentEvent->m_agent_event.otherAttr        = acd_tool::TranslatePartyAtt(event.otherAttr);
    p_agentEvent->m_agent_event.originatingParty = event.originatingParty;
    p_agentEvent->m_agent_event.originalAni      = event.originalAni;
    p_agentEvent->m_agent_event.originalDnis     = event.originalDnis;
    //p_agentEvent->m_agent_event.reason           = reason;
    p_agentEvent->m_agent_event.timestamp        = bgcc::TimeUtil::get_timestamp_us();
    acd::CallEventReasonT reason = acd_tool::TranslateCallReason(event.reason);

    switch (event.state.get_value()) {
    case ims::CallStateT::SG_UnknownState:
        m_agentStatus = acd::AgentStatusT::AsUnknownState;
        break;

    case ims::CallStateT::SG_IdleState: {
        if (lastAgentStatus == acd::AgentStatusT::AsAlertingState ||
                lastAgentStatus == acd::AgentStatusT::AsHalfAlertingState ||
                lastAgentStatus == acd::AgentStatusT::AsConnectingState ||
                lastAgentStatus == acd::AgentStatusT::AsHalfConnectedState ||
                lastAgentStatus == acd::AgentStatusT::AsConsultConnectingState) { // 振铃中挂断
            if (event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_InternalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_NormalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyTransferred_NormalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_ConsultCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyTransferred_ConsultCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_ConferenceCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_MonitorCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_IntrudeCall) { // 本方挂断
                reason = acd::CallEventReasonT::CerIdleErrorSelfHangup;
                m_callinfo.SetReleaseCause(ReleaseCauseT::THISPARTY);
            } else {
                reason = acd::CallEventReasonT::CerIdleErrorOtherHangup;
                m_callinfo.SetReleaseCause(ReleaseCauseT::OTHERPARTY);
            }

            if (0 < m_callTime) {
                m_callTotalTime += m_currStatusTime - m_callTime;
            }

            if (0 < m_answerTime) {
                m_answerTotalTime += m_currStatusTime - m_answerTime;
            }

            m_callinfo.SetAniDnis(event.originalAni, event.originalDnis);
            m_callinfo.SetAckEnd(m_currStatusTime);
            m_callinfo.SetCallEnd(m_currStatusTime);

            if (m_callinfo.isValid()) { // 如果话单没有起始信息，则不必要写
                m_callinfo.WriteCallLog();
                m_callinfo.reset();
            }

            Reset();
        } else if (lastAgentStatus == acd::AgentStatusT::AsConnectedState ||
                   lastAgentStatus == acd::AgentStatusT::AsInternalConnectedState ||
                   lastAgentStatus == acd::AgentStatusT::AsSuspendedState ||
                   lastAgentStatus == acd::AgentStatusT::AsConsultConnectedState ||
                   lastAgentStatus == acd::AgentStatusT::AsConferenceState ||
                   lastAgentStatus == acd::AgentStatusT::AsMonitorState ||
                   lastAgentStatus == acd::AgentStatusT::AsInsertState ||
                   lastAgentStatus == acd::AgentStatusT::AsMonitoredState ||
                   lastAgentStatus == acd::AgentStatusT::AsInsertedState) { // 通话中挂断
            if (event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_InternalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_NormalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyTransferred_NormalCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnected_ConsultCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyTransferred_ConsultCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_ConferenceCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_MonitorCall ||
                    event.eventType == ims::CallEventTypeT::SG_ThisPartyDisconnect_IntrudeCall) { // 本方挂断
                reason = acd::CallEventReasonT::CerIdleNormalSelfHangup;
                m_callinfo.SetReleaseCause(ReleaseCauseT::THISPARTY);
            } else {
                reason = acd::CallEventReasonT::CerIdleNormalOtherHangup;
                m_callinfo.SetReleaseCause(ReleaseCauseT::OTHERPARTY);
            }

            if (0 < m_callTime) {
                m_callTotalTime += m_currStatusTime - m_callTime;
            }

            if (0 < m_answerTime) {
                m_answerTotalTime += m_currStatusTime - m_answerTime;
            }

            m_callinfo.SetAniDnis(event.originalAni, event.originalDnis);
            m_callinfo.SetCallEnd(m_currStatusTime);

            if (m_callinfo.isValid()) { // 如果话单没有起始信息，则不必要写
                m_callinfo.WriteCallLog();
                m_callinfo.reset();
            }

            Reset();
        } else {
            reason = acd::CallEventReasonT::CerIdleIdle;
        }

        if (m_statusChangetype == acd::StatusChangeT::ScBusy) {
            m_agentStatus = acd::AgentStatusT::AsBusyState;
        } else {
            m_agentStatus = acd::AgentStatusT::AsReadyState;
        }

        break;
    }

    case ims::CallStateT::SG_AlertingState: {
        if (!m_callinfo.GetRoutecall()) {
            if (m_callinfo.isValid()) { // 如果话单没有结束信息，则需要写
                m_callinfo.WriteCallLog();
                m_callinfo.reset();
            }

            m_callinfo.Initial(event.sessionid, event.callid, m_agentId, m_agentDn, m_skill, event.originalAni,
                               event.originalDnis, 0, 0);
        }

        m_callinfo.SetAckBegin(m_currStatusTime);
        m_callinfo.SetCallType(event.otherAttr);
        m_callinfo.SetCallDirect(CallDirectT::INBOUND);

        m_origCaller = event.originalAni;
        m_origCallee = event.originalDnis;
        m_callTime = m_currStatusTime;
        m_callTimes++;
        m_agentStatus = acd::AgentStatusT::AsAlertingState;
        break;
    }

    case ims::CallStateT::SG_HalfAlertingState: {
        if (m_callinfo.isValid()) { // 如果话单没有结束信息，则需要写
            m_callinfo.WriteCallLog();
            m_callinfo.reset();
        }

        m_callinfo.Initial(event.sessionid, event.callid, m_agentId, m_agentDn, m_skill, event.originalAni,
                           event.originalDnis, 0, 0);
        m_callinfo.SetAckBegin(m_currStatusTime);
        m_callinfo.SetCallDirect(CallDirectT::OUTBOUND);

        m_origCaller = event.originalAni;
        m_origCallee = event.originalDnis;
        m_callTime = m_currStatusTime;
        m_callTimes++;
        m_agentStatus = acd::AgentStatusT::AsHalfAlertingState;
        break;
    }

    case ims::CallStateT::SG_ConnectingState: {
        if (event.eventType == ims::CallEventTypeT::SG_DestSeized_ConsultCall) {
            m_agentStatus = acd::AgentStatusT::AsConsultConnectingState;
        } else if (event.eventType == ims::CallEventTypeT::SG_OtherPartyDisconnected_ConsultCall) {
            m_agentStatus = acd::AgentStatusT::AsConnectingState;
        } else {
            m_callinfo.SetCallType(event.otherAttr);
            m_agentStatus = acd::AgentStatusT::AsConnectingState;
        }

        break;
    }

    case ims::CallStateT::SG_ConnectedState: {
        if (event.eventType == ims::CallEventTypeT::SG_ThisPartyAnswered_InternalCall ||
                event.eventType == ims::CallEventTypeT::SG_ThisPartyAnswered_NormalCall) {
            Record();
            m_callinfo.SetAckEnd(m_currStatusTime);
            m_callinfo.SetCallBegin(m_currStatusTime);
            m_callinfo.SetRecordFilename(m_recordFilename);
            m_answerTime = m_currStatusTime;
            m_answerTimes++;
            reason = acd::CallEventReasonT::CerTalkOtherCreat;
        } else if (event.eventType == ims::CallEventTypeT::SG_OtherPartyAnswered_InternalCall ||
                   event.eventType == ims::CallEventTypeT::SG_OtherPartyAnswered_NormalCall) {
            Record();
            m_callinfo.SetAckEnd(m_currStatusTime);
            m_callinfo.SetCallBegin(m_currStatusTime);
            m_callinfo.SetRecordFilename(m_recordFilename);
            m_answerTime = m_currStatusTime;
            m_answerTimes++;
            reason = acd::CallEventReasonT::CerTalkSelfCreat;
        } else if (event.eventType == ims::CallEventTypeT::SG_OtherPartyDisconnected_ConsultCall) {
            reason = acd::CallEventReasonT::CerTalkOtherRetrieve;
        } else {
            reason = acd::CallEventReasonT::CerTalkSelfRetrieve;
        }

        if (event.eventType == ims::CallEventTypeT::SG_OtherPartyAnswered_ConsultCall) {
            m_agentStatus = acd::AgentStatusT::AsConsultConnectedState;
        } else if (event.otherAttr == ims::PartyAttributeT::P_Internal) {
            m_agentStatus = acd::AgentStatusT::AsInternalConnectedState;
        } else {
            m_agentStatus = acd::AgentStatusT::AsConnectedState;
        }

        break;
    }

    case ims::CallStateT::SG_HalfConnectedState:
        m_agentStatus = acd::AgentStatusT::AsHalfConnectedState;
        break;

    case ims::CallStateT::SG_SuspendedState:
        m_agentStatus = acd::AgentStatusT::AsSuspendedState;
        break;

    case ims::CallStateT::SG_ConferenceState: {
        if (event.eventType == ims::CallEventTypeT::SG_ThisPartyConferenced_MonitorCall) {
            if (acd::AgentStatusT::AsHalfConnectedState == lastAgentStatus) {
                Record();
                m_callinfo.SetAckEnd(m_currStatusTime);
                m_callinfo.SetCallBegin(m_currStatusTime);
                m_callinfo.SetCallType(event.otherAttr);
                m_callinfo.SetRecordFilename(m_recordFilename);
                m_answerTime = m_currStatusTime;
                m_answerTimes++;
            }

            m_agentStatus = acd::AgentStatusT::AsMonitorState;
        } else if (event.eventType == ims::CallEventTypeT::SG_OtherPartyConferenced_MonitorCall) {
            m_agentStatus = acd::AgentStatusT::AsMonitoredState;
        } else if (event.eventType == ims::CallEventTypeT::SG_ThisPartyConferenced_IntrudeCall) {
            if (acd::AgentStatusT::AsHalfConnectedState == lastAgentStatus) {
                Record();
                m_callinfo.SetAckEnd(m_currStatusTime);
                m_callinfo.SetCallBegin(m_currStatusTime);
                m_callinfo.SetCallType(event.otherAttr);
                m_callinfo.SetRecordFilename(m_recordFilename);
                m_answerTime = m_currStatusTime;
                m_answerTimes++;
            }

            m_agentStatus = acd::AgentStatusT::AsInsertState;
        } else if (event.eventType == ims::CallEventTypeT::SG_OtherPartyConferenced_IntrudeCall) {
            m_agentStatus = acd::AgentStatusT::AsInsertedState;
        } else {
            m_agentStatus = acd::AgentStatusT::AsConferenceState;
        }

        break;
    }

    default:
        m_agentStatus = acd::AgentStatusT::AsUnknownState;
        break;
    }

    p_agentEvent->m_agent_event.agentStatus = m_agentStatus;
    p_agentEvent->m_agent_event.reason = reason;

    WriteTraceLog();
    acd_tool::m_send_event_manager.send_event(p_agentEvent, m_handle);
}

void acd_agent::ProcessIMSEvent(const ims::MediaEventT& event) {
    SingleRWLocker s(&m_RWLock, false);

    SendEventT* p_agentEvent = new SendEventT;
    p_agentEvent->m_event_id               = acd_tool::CreatEventId();
    p_agentEvent->m_callback_proxy         = m_callback_ptr;
    p_agentEvent->m_event_type             = MEDIA_EVENT;
    p_agentEvent->m_media_event.agentId    = m_agentId;
    p_agentEvent->m_media_event.eventType  = acd_tool::TranslateMediaEvent(event.eventType);
    p_agentEvent->m_media_event.agentDn    = event.device;
    p_agentEvent->m_media_event.callId     = event.callid;
    p_agentEvent->m_media_event.sessionId  = event.sessionid;
    p_agentEvent->m_media_event.state      = acd_tool::TranslateMediaState(event.state);
    p_agentEvent->m_media_event.reason     = acd_tool::TranslateMediaReason(event.reason);
    p_agentEvent->m_media_event.otherParty = event.otherDevice;
    p_agentEvent->m_media_event.buffer     = event.mediaBuffer;
    p_agentEvent->m_media_event.timestamp  = bgcc::TimeUtil::get_timestamp_us();

    acd_tool::m_send_event_manager.send_event(p_agentEvent, m_handle);
}

void acd_agent::ProcessIMSEvent(const ims::OtherEventT& event) {
    SingleRWLocker s(&m_RWLock, false);

    SendEventT* p_agentEvent = new SendEventT;
    p_agentEvent->m_event_id                 = acd_tool::CreatEventId();
    p_agentEvent->m_callback_proxy           = m_callback_ptr;
    p_agentEvent->m_event_type               = OTHER_EVENT;
    p_agentEvent->m_other_event.agentId      = m_agentId;
    p_agentEvent->m_other_event.eventType    = acd::OtherEventTypeT::IMSOperationFailed;
    p_agentEvent->m_other_event.agentDn      = event.device;
    p_agentEvent->m_other_event.callId       = event.callid;
    p_agentEvent->m_other_event.sessionId    = event.sessionid;
    p_agentEvent->m_other_event.originalAni  = m_origCaller;
    p_agentEvent->m_other_event.originalDnis = m_origCallee;
    p_agentEvent->m_other_event.timestamp    = bgcc::TimeUtil::get_timestamp_us();

    acd_tool::m_send_event_manager.send_event(p_agentEvent, m_handle);
}

void acd_agent::ProcessIMSEvent(const acd::OtherEventTypeT& type) {
    SingleRWLocker s(&m_RWLock, false);

    SendEventT* p_agentEvent = new SendEventT;
    p_agentEvent->m_event_id                 = acd_tool::CreatEventId();
    p_agentEvent->m_callback_proxy           = m_callback_ptr;
    p_agentEvent->m_event_type               = OTHER_EVENT;
    p_agentEvent->m_other_event.agentId      = m_agentId;
    p_agentEvent->m_other_event.eventType    = type;
    p_agentEvent->m_other_event.agentDn      = m_agentDn;
    p_agentEvent->m_other_event.callId       = m_callId;
    p_agentEvent->m_other_event.sessionId    = m_sessionId;
    p_agentEvent->m_other_event.originalAni  = m_origCaller;
    p_agentEvent->m_other_event.originalDnis = m_origCallee;
    p_agentEvent->m_other_event.timestamp    = bgcc::TimeUtil::get_timestamp_us();

    acd_tool::m_send_event_manager.send_event(p_agentEvent, m_handle);
}

void acd_agent::SetAgentStatus(const acd::AgentStatusT& agentStatus, const string& restReason) {
    SingleRWLocker s(&m_RWLock, true);
    SetStatus(agentStatus, acd::CallEventReasonT::CerIdleSelfSet, restReason);
}

acd::AgentStatusT acd_agent::GetAgentStatus() {
    SingleRWLocker s(&m_RWLock, false);
    return m_agentStatus;
}

void acd_agent::ResetStatuschangetype(const acd::StatusChangeT& statusChangetype) {
    SingleRWLocker s(&m_RWLock, true);
    m_statusChangetype = statusChangetype;
}

void acd_agent::ResetAutoAnswer(bool autoAnswer) {
    SingleRWLocker s(&m_RWLock, true);
    m_autoAnswer = autoAnswer;
}

void acd_agent::ResetSkill(const string& skill) {
    SingleRWLocker s(&m_RWLock, true);
    m_skill = skill;
}

acd::AcdResultT acd_agent::SignIn(const string& agentId, const string& agentDn,
                                  const acd::StatusChangeT& statusChangetype,
                                  bool autoAnswer, bool fcSignin, const string& skill, int64_t& handle,
                                  const std::map<std::string, std::string>& ctx) {
    SingleRWLocker s(&m_RWLock, true);

    // 签出
    if (fcSignin) {
        SignOut(true);
    }

    // 赋值
    m_agentId = agentId;
    m_agentDn = agentDn;
    m_statusChangetype = statusChangetype;
    m_autoAnswer = autoAnswer;
    m_skill = skill;
    //m_handle = 0;

    Reset();
    //m_sessionId = 0;
    //m_callId.clear();
    m_requestId = 0;
    m_validTime = 0;
    m_heartbeatTime = time(NULL);
    //m_recordFilename.clear();

    m_loginTime = time(NULL);
    //m_agentStatus = acd::AgentStatusT::AsUnLoginState;
    //m_currStatusTime = 0;
    //m_callTime = 0;
    //m_answerTime = 0;
    //m_origCaller.clear();
    //m_origCallee.clear();
    m_callTimes = 0;
    m_answerTimes = 0;
    m_freeTotalTime = 0;
    m_busyTotalTime = 0;
    m_restTotalTime = 0;
    m_callTotalTime = 0;
    m_answerTotalTime = 0;
    //m_agentIP.clear();
    m_callinfo.reset();

    std::map<std::string, std::string>::const_iterator it = ctx.find("ProxyName");

    if (it == ctx.end()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s create callback proxy fail", m_agentId.c_str());
        return acd::AcdResultT::ArFailed;
    }

    m_callback_ptr = acd_callback_proxy_ptr(new acd::acdcallbackProxy(it->second, 0));

    it = ctx.find("PeerIP");

    if (it == ctx.end()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s get agent ip fail", m_agentId.c_str());
        m_agentIP = "error";
    } else {
        m_agentIP = it->second;
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s get agent ip:%s", m_agentId.c_str(), m_agentIP.c_str());
    }

    if (!acd_tool::p_m_acd_ims->Assign(m_agentId, m_agentDn, ims::DnTypeT::AgentDn)) {
        return acd::AcdResultT::ArImsError;
    }

    m_handle = acd_tool::CreatHandle();
    handle = m_handle;

    if (m_statusChangetype == acd::StatusChangeT::ScBusy) {
        SetStatus(acd::AgentStatusT::AsBusyState, acd::CallEventReasonT::CerIdleSelfLogin);
    } else {
        SetStatus(acd::AgentStatusT::AsReadyState, acd::CallEventReasonT::CerIdleSelfLogin);
    }

    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_agent::SignOut(bool fcSignout) {
    acd_tool::p_m_acd_ims->DeAssign(m_agentId, m_agentDn, ims::DnTypeT::AgentDn);

    if (fcSignout) {
        SetStatus(acd::AgentStatusT::AsUnLoginState, acd::CallEventReasonT::CerUnloginOtherForceout);
    } else {
        SetStatus(acd::AgentStatusT::AsUnLoginState, acd::CallEventReasonT::CerUnloginLogout);
    }

    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_agent::OutboundCall(const string& callerId, const string& destId,
                                        const string& forCallerDispNum, const string& forCalleeDispNum, int32_t timeout,
                                        const acd::CallModeT& callMode) {
    if (acd_tool::p_m_acd_ims->OutboundCall(m_agentId, callerId, destId, forCallerDispNum,
                                            forCalleeDispNum, timeout, callMode.get_value(), m_sessionId)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::AnswerCall() {
    if (acd_tool::p_m_acd_ims->Answer(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::ReleaseCall() {
    if (acd_tool::p_m_acd_ims->Release(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Hold() {
    if (acd_tool::p_m_acd_ims->Hold(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Retrieve() {
    if (acd_tool::p_m_acd_ims->Retrieve(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Consult(const string& callerId, const string& destId,
                                   const string& forCallerDispNum, const string& forCalleeDispNum) {
    if (acd_tool::p_m_acd_ims->Consult(m_sessionId, m_agentId, callerId, destId, forCalleeDispNum)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::ConsultReconnect() {
    if (acd_tool::p_m_acd_ims->Reconnect(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::ConsultTransfer() {
    if (acd_tool::p_m_acd_ims->Transfer(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::SingleStepTransfer(const string& callerId, const string& destId,
        const string& forCallerDispNum, const string& forCalleeDispNum, bool isPassthrough) {
    if (acd_tool::p_m_acd_ims->SingleStepTransfer(m_sessionId, m_agentId, callerId, destId,
            forCalleeDispNum)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::ConsultConference() {
    if (acd_tool::p_m_acd_ims->Conference(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::ConferenceJoin(ims::SessionIdT sessionId, const string& callerId,
        const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
        const acd::ConferenceT& conferenceType) {
    if (acd_tool::p_m_acd_ims->SingleStepConference(sessionId, m_agentId, callerId, destAgentId,
            forCalleeDispNum, conferenceType.get_value())) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::SetAssociateData(const string& key, const string& value) {
    if (acd_tool::p_m_acd_ims->SetAssociateData(m_sessionId, m_agentId, key, value)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::GetAssociateData(const string& key, string& value) {
    if (acd_tool::p_m_acd_ims->GetAssociateData(m_sessionId, m_agentId, key, value)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Listen(ims::SessionIdT sessionId, const string& callerId,
                                  const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum) {
    if (acd_tool::p_m_acd_ims->SingleStepConference(sessionId, m_agentId, callerId, destAgentId,
            forCalleeDispNum, ims::SsConferenceTypeT::Monitor)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Insert(ims::SessionIdT sessionId, const string& callerId,
                                  const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum) {
    if (acd_tool::p_m_acd_ims->SingleStepConference(sessionId, m_agentId, callerId, destAgentId,
            forCalleeDispNum, ims::SsConferenceTypeT::Intrude)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::SwitchInsertorListen(const string& callerId, const string& destAgentId,
        const string& forCallerDispNum, const string& forCalleeDispNum) {
    if (acd_tool::p_m_acd_ims->SwitchListenAndIntrude(m_sessionId, m_agentId, m_agentDn)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::SendDTMF(const string& digitals) {
    if (acd_tool::p_m_acd_ims->SendDTMF(m_sessionId, m_agentId, m_agentDn, digitals)) {
        return acd::AcdResultT::ArSuccess;
    } else {
        return acd::AcdResultT::ArImsError;
    }
}

acd::AcdResultT acd_agent::Heartbeat() {
    m_heartbeatTime = time(NULL);
    return acd::AcdResultT::ArSuccess;
}
