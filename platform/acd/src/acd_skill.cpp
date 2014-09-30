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


#include "acd_skill.h"
#include "acd_tool.h"

requestinfo::requestinfo(const ims::RouteEventT& event) : m_transferAgent(false),
    m_waitbegin(time(NULL)), m_event(event) {
}

requestinfo::~requestinfo() {
    if (!m_transferAgent) {
        callinfo info;
        info.Initial(m_event.sessionid, m_event.callid, "", "", "", m_event.callerDn, m_event.calleeDn,
                     m_waitbegin, time(NULL));
        info.WriteCallLog();
    }
}

time_t requestinfo::GetWaitbeginTime() {
    m_transferAgent = true;
    return m_waitbegin;
}

ims::RouteEventT& requestinfo::GetEvent() {
    return m_event;
}

free_agent::free_agent() : m_t(LLONG_MAX), m_isfree(false) {
}

free_agent::~free_agent() {
}

void free_agent::setTime(uint64_t t) {
    m_t = t;
}

uint64_t free_agent::getTime() {
    return m_t;
}

void free_agent::setFree() {
    m_isfree = true;
}

bool free_agent::isFree() {
    return m_isfree;
}

void free_agent::setAgentPtr(const acd_agent_ptr& p_agent) {
    m_agent_ptr = p_agent;
}

acd_agent_ptr free_agent::GetAgentPtr() {
    return m_agent_ptr;
}

void acd_skill::Method() {
    while (this->mIsLoop) {
        ims::RouteRequestIDT requestId;
        m_queueRequest.BlockFront(requestId);

        request_ptr pRequest;

        if (!m_mapRequest.Find(requestId, pRequest)) {
            m_queueRequest.BlockPop();
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s requestId:%"SHOW_LONG"d is invalid", m_skill_flag, m_strSkill.c_str(), requestId);
            continue;
        }

        acd_agent_ptr p_agent;

        if (!GetIdleAgent(p_agent)) {
            bgcc::TimeUtil::safe_sleep_s(m_queue_timespan);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s requestId:%"SHOW_LONG"d no idle agent", m_skill_flag, m_strSkill.c_str(),
                                        requestId);
            m_mapRequest.Remove(acd_skill::isTimeoutRequest);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s erase timeout request", m_skill_flag, m_strSkill.c_str());
            continue;
        }

        if (p_agent->GetAgentStatus() != acd::AgentStatusT::AsReadyState) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s requestId:%"SHOW_LONG"d request agentId:%s fail: agent not ready", m_skill_flag,
                                        m_strSkill.c_str(), requestId, p_agent->GetAgentId().c_str());
            continue;
        }

        p_agent->lock(pRequest->GetEvent(), pRequest->GetWaitbeginTime());

        if (acd_tool::p_m_acd_ims->RouteRequestRespond(pRequest->GetEvent().sessionid,
                pRequest->GetEvent().requstid, ims::RouteEventReasonT::RouteReasonSuccess, p_agent->GetAgentDn())) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s requestId:%"SHOW_LONG"d request agentId:%s agentDn:%d success", m_skill_flag,
                                        m_strSkill.c_str(), requestId, p_agent->GetAgentId().c_str(), p_agent->GetAgentDn().c_str());
        } else {
            p_agent->unlock(pRequest->GetEvent());
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "flag:%d skill:%s requestId:%"SHOW_LONG"d request agentId:%s agentDn:%d fail", m_skill_flag,
                                        m_strSkill.c_str(), requestId, p_agent->GetAgentId().c_str(), p_agent->GetAgentDn().c_str());
        }

        m_queueRequest.BlockPop();
        m_mapRequest.Erase(requestId);
    }
}

void acd_skill::ProcessIdleAgent(const string& agentId, free_agent& agent) {
    acd_agent_ptr p_agent;

    if (acd_tool::m_agent_manager.GetAgent(agentId, p_agent)) {
        if (acd::AgentStatusT::AsReadyState == p_agent->GetAgentStatus()
                && agent.getTime() > p_agent->GetCurrStatusTime()) {
            agent.setFree();
            agent.setTime(p_agent->GetCurrStatusTime());
            agent.setAgentPtr(p_agent);
        }
    }
}

bool acd_skill::isTimeoutRequest(const request_ptr& pRequest) {
    if (bgcc::TimeUtil::get_timestamp_us() - pRequest->GetEvent().timestamp >
            pRequest->GetEvent().timeout * 1000000) {
        acd_tool::p_m_acd_ims->RouteRequestRespond(pRequest->GetEvent().sessionid,
                pRequest->GetEvent().requstid, ims::RouteEventReasonT::RouteReasonBusy, "");
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d is timeout", pRequest->GetEvent().requstid);
        return true;
    } else {
        return false;
    }
}

bool acd_skill::ProcessInvalidRequest(const request_ptr& pRequest) {
    acd_tool::p_m_acd_ims->RouteRequestRespond(pRequest->GetEvent().sessionid,
            pRequest->GetEvent().requstid, ims::RouteEventReasonT::RouteReasonWrongSkill, "");
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "requestId:%"SHOW_LONG"d invalid", pRequest->GetEvent().requstid);
    return true;
}

void acd_skill::GetFreeAgent(const string& agentId, int32_t& freeNum) {
    acd_agent_ptr p_agent;

    if (acd_tool::m_agent_manager.GetAgent(agentId, p_agent)
            && acd::AgentStatusT::AsReadyState == p_agent->GetAgentStatus()) {
        freeNum++;
    }
}

void acd_skill::GerAgentDetail(const string& agentId, acd::AgentInfoListT& agentInfoList) {
    acd_agent_ptr p_agent;

    if (acd_tool::m_agent_manager.GetAgent(agentId, p_agent)) {
        acd::AgentInfoT agentInfo;
        p_agent->GetAgentDetail(agentInfo);
        agentInfoList.push_back(agentInfo);
    }
}

void acd_skill::GetWaitingCallInfo(ims::RouteRequestIDT requestId, const request_ptr& pRequest,
                                   acd::QueueInfoListT& queueInfoList) {
    acd::QueueInfoT info;
    info.callId     = pRequest->GetEvent().callid;
    info.contactId  = pRequest->GetEvent().sessionid;
    info.requestId  = pRequest->GetEvent().requstid;
    info.origCaller = pRequest->GetEvent().callerDn;
    info.origCallee = pRequest->GetEvent().calleeDn;
    info.startTime  = pRequest->GetEvent().timestamp;
    info.currTime   = time(NULL);
    info.changeTime = 0;
    queueInfoList.push_back(info);
}

bool acd_skill::UnlockByRequestId(const string& agentId, const ims::RouteEventT& event) {
    acd_agent_ptr p_agent;

    if (acd_tool::m_agent_manager.GetAgent(agentId, p_agent)) {
        return p_agent->unlock(event);
    }

    return false;
}

bool acd_skill::GetIdleAgent(acd_agent_ptr& p_agent) {
    free_agent agent;
    m_setAgent.DoSomething(acd_skill::ProcessIdleAgent, agent);

    if (agent.isFree()) {
        p_agent = agent.GetAgentPtr();
        return true;
    }

    return false;
}

acd_skill::acd_skill(int64_t skill_flag, uint32_t queue_timespan) : m_skill_flag(skill_flag),
    m_queue_timespan(queue_timespan), m_strSkill("") {
}

acd_skill::~acd_skill() {
}

bool acd_skill::isNotUseSkill() {
    return m_strSkill.empty();
}

void acd_skill::UseSkill(const string& strSkill) {
    m_strSkill = strSkill;
}

void acd_skill::UnuseSkill() {
    m_mapRequest.Remove(acd_skill::ProcessInvalidRequest);
    m_strSkill.clear();
}

bool acd_skill::InsertAgent(const string& agentId) {
    return m_setAgent.Insert(agentId);
}

bool acd_skill::EraseAgent(const string& agentId) {
    return m_setAgent.Erase(agentId);
}

int32_t acd_skill::GetAgentNumber() {
    return m_setAgent.Size();
}

int32_t acd_skill::GetRequestNumber() {
    return m_mapRequest.Size();
}

void acd_skill::GetWaitingNumber(int32_t& queueNum, int32_t& freeNum) {
    queueNum = m_mapRequest.Size();
    freeNum = 0;
    m_setAgent.DoSomething(acd_skill::GetFreeAgent, freeNum);
}

void acd_skill::GetAgentDetails(int32_t& agentNum, acd::AgentInfoListT& agentInfoList) {
    agentNum = m_setAgent.Size();
    m_setAgent.DoSomething(acd_skill::GerAgentDetail, agentInfoList);
}

void acd_skill::GetWaitingCallInfos(int32_t& queueNum, acd::QueueInfoListT& queueInfoList) {
    queueNum = m_mapRequest.Size();
    m_mapRequest.DoSomething(acd_skill::GetWaitingCallInfo, queueInfoList);
}

void acd_skill::RouteRequest(const ims::RouteEventT& event) {
    m_mapRequest.Insert(event.requstid, request_ptr(new requestinfo(event)));
    m_queueRequest.BlockPush(event.requstid);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "flag:%d skill:%s requestId:%"SHOW_LONG"d in queue", m_skill_flag, m_strSkill.c_str(),
                                event.requstid);
}

void acd_skill::RouteRequestCancel(const ims::RouteEventT& event) {
    if (m_mapRequest.Erase(event.requstid)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "flag:%d skill:%s requestId:%"SHOW_LONG"d cancel success", m_skill_flag, m_strSkill.c_str(),
                                    event.requstid);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "flag:%d skill:%s requestId %"SHOW_LONG"d cancel fail", m_skill_flag, m_strSkill.c_str(),
                                    event.requstid);
        m_setAgent.Find(event, acd_skill::UnlockByRequestId);
    }
}
