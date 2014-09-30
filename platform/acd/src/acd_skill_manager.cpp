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


#include "acd_skill_manager.h"
#include "acd_tool.h"

void acd_skill_manager::Method() {
    while (this->mIsLoop) {
        bgcc::TimeUtil::safe_sleep_s(m_request_timespan);
        acd_tool::m_agent_manager.GetAgents().DoSomething(acd_skill_manager::ProcessUnlock);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "unlock timeout agent");
    }
}

void acd_skill_manager::ProcessUnlock(const string& agentId, const acd_agent_ptr& p_agent) {
    if (p_agent->unlockTimeout()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s unlock success", p_agent->GetAgentId().c_str());
    }
}

void acd_skill_manager::GetRequestNumber(const string& strSkill, const acd_skill_ptr& p_skill,
        int32_t& num) {
    num += p_skill->GetRequestNumber();
}

void acd_skill_manager::InsertSkill(const string& strSkill, acd_skill_ptr& p_skill) {
    bool isAllocated = false;

    for (vector<acd_skill_ptr>::iterator it = m_skill_array.begin(); it != m_skill_array.end(); it++) {
        if ((*it)->isNotUseSkill()) {
            p_skill = *it;
            p_skill->UseSkill(strSkill);
            m_mapSkill.Insert(strSkill, p_skill);
            isAllocated = true;
            break;
        }
    }

    if (!isAllocated) {
        for (uint32_t i = 0; i < m_skill_count; i++) {
            p_skill = acd_skill_ptr(new acd_skill(acd_tool::CreatSkillId(), m_queue_timespan));
            p_skill->Start();
            m_skill_array.push_back(p_skill);
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "restart skill count:%d", m_skill_array.size());
        p_skill->UseSkill(strSkill);
        m_mapSkill.Insert(strSkill, p_skill);
    }
}

void acd_skill_manager::EraseSkill(const string& strSkill, const acd_skill_ptr& p_skill) {
    p_skill->UnuseSkill();
    m_mapSkill.Erase(strSkill);
}

void acd_skill_manager::RouteRequest(const ims::RouteEventT& event) {
    SingleRWLocker s(&m_RWLock, false);
    acd_skill_ptr p_skill;

    if (m_mapSkill.Find(event.requestArgs, p_skill)) {
        p_skill->RouteRequest(event);
    } else {
        acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid,
                ims::RouteEventReasonT::RouteReasonWrongSkill, "");
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d request skill:%s not existed", event.requstid, event.requestArgs.c_str());
    }
}

void acd_skill_manager::RouteRequestCancel(const ims::RouteEventT& event) {
    SingleRWLocker s(&m_RWLock, false);
    acd_skill_ptr p_skill;

    if (m_mapSkill.Find(event.requestArgs, p_skill)) {
        p_skill->RouteRequestCancel(event);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d cancel skill:%s not existed", event.requstid, event.requestArgs.c_str());
    }
}

acd_skill_manager::acd_skill_manager() : m_request_timespan(30), m_queue_timespan(1),
    m_skill_count(10) {
}

acd_skill_manager::~acd_skill_manager() {
}

void acd_skill_manager::Initialize(uint32_t request_timespan, uint32_t queue_timespan,
                                   uint32_t skill_count) {
    m_request_timespan = request_timespan;
    m_queue_timespan = queue_timespan;
    m_skill_count = skill_count;

    for (uint32_t i = 0; i < m_skill_count; i++) {
        acd_skill_ptr p_skill(new acd_skill(acd_tool::CreatSkillId(), m_queue_timespan));
        p_skill->Start();
        m_skill_array.push_back(p_skill);
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "start skill count:%d", m_skill_count);

    Start();
}

void acd_skill_manager::Uninitialize() {
    Stop();

    for (vector<acd_skill_ptr>::iterator it = m_skill_array.begin(); it != m_skill_array.end(); it++) {
        (*it)->Stop();
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "stop skill count:%d", m_skill_array.size());
}

void acd_skill_manager::insert_agent(const string& agentId, const string& skill) {
    vector<string> vecSkill;
    bgcc::StringUtil::split_string(skill, ",", vecSkill, true);

    SingleRWLocker s(&m_RWLock, true);
    acd_skill_ptr p_skill;

    for (vector<string>::iterator it = vecSkill.begin(); it != vecSkill.end(); it++) {
        if (!m_mapSkill.Find(*it, p_skill)) {
            InsertSkill(*it, p_skill);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s create skill:%s", agentId.c_str(), it->c_str());
        }

        if (p_skill->InsertAgent(agentId)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s insert skill:%s success", agentId.c_str(), it->c_str());
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s insert skill:%s fail", agentId.c_str(), it->c_str());
        }
    }
}

void acd_skill_manager::erase_agent(const string& agentId, const string& skill) {
    vector<string> vecSkill;
    bgcc::StringUtil::split_string(skill, ",", vecSkill, true);

    SingleRWLocker s(&m_RWLock, true);
    acd_skill_ptr p_skill;

    for (vector<string>::iterator it = vecSkill.begin(); it != vecSkill.end(); it++) {
        if (m_mapSkill.Find(*it, p_skill)) {
            if (p_skill->EraseAgent(agentId)) {
                if (0 == p_skill->GetAgentNumber()) {
                    EraseSkill(*it, p_skill);
                    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                                "agentId:%s delete skill:%s", agentId.c_str(), it->c_str());
                }

                acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                            "agentId:%s erase skill:%s success", agentId.c_str(), it->c_str());
            } else {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                            "agentId:%s erase skill:%s fail", agentId.c_str(), it->c_str());
            }
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s erase skill:%s not existed", agentId.c_str(), it->c_str());
        }
    }
}

void acd_skill_manager::ProcessIMSEvent(const ims::RouteEventT& event) {
    switch (event.eventType.get_value()) {
    case ims::RouteEventTypeT::RT_RouteUnknown:
        acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid,
                ims::RouteEventReasonT::RouteReasonError, "");
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "event type error");
        break;

    case ims::RouteEventTypeT::RT_RouteRequest:
        RouteRequest(event);
        break;

    case ims::RouteEventTypeT::RT_RouteRespond:
        acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid,
                ims::RouteEventReasonT::RouteReasonError, "");
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "event type error");
        break;

    case ims::RouteEventTypeT::RT_RouteRequestCancel:
        RouteRequestCancel(event);
        break;

    default:
        acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid,
                ims::RouteEventReasonT::RouteReasonError, "");
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "event type error");
        break;
    }
}

int32_t acd_skill_manager::GetRouteRequestNumber() {
    int32_t num = 0;
    m_mapSkill.DoSomething(acd_skill_manager::GetRequestNumber, num);
    return num;
}

acd::AcdResultT acd_skill_manager::GetAgentNumberBySkill(int64_t handle, const string& agentId,
        const string& skill, int32_t& agentNum) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (skill.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty skill", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArSkillIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not master", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_skill_ptr p_skill;

    if (!m_mapSkill.Find(skill, p_skill)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not existed", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArSkillNotExist;
        return ret;
    }

    agentNum = p_skill->GetAgentNumber();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d skill:%s has agentNum:%d", agentId.c_str(), handle, skill.c_str(),
                                agentNum);
    return ret;
}

acd::AcdResultT acd_skill_manager::GetAgentDetailsBySkill(int64_t handle, const string& agentId,
        const string& skill, int32_t& agentNum, acd::AgentInfoListT& agentInfoList) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (skill.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty skill", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArSkillIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not master", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_skill_ptr p_skill;

    if (!m_mapSkill.Find(skill, p_skill)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not existed", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArSkillNotExist;
        return ret;
    }

    agentNum = 0;
    p_skill->GetAgentDetails(agentNum, agentInfoList);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d skill:%s get agent details success", agentId.c_str(), handle,
                                skill.c_str());
    return ret;
}

acd::AcdResultT acd_skill_manager::GetSkillWaitingNumber(int64_t handle, const string& agentId,
        const string& skill, int32_t& queueNum, int32_t& freeNum) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (skill.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty skill", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArSkillIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not master", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_skill_ptr p_skill;

    if (!m_mapSkill.Find(skill, p_skill)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not existed", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArSkillNotExist;
        return ret;
    }

    queueNum = freeNum = 0;
    p_skill->GetWaitingNumber(queueNum, freeNum);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d skill:%s has queueNum:%d freeNum:%d", agentId.c_str(), handle,
                                skill.c_str(), queueNum, freeNum);
    return ret;
}

acd::AcdResultT acd_skill_manager::GetSkillWaitingCallInfo(int64_t handle, const string& agentId,
        const string& skill, int32_t& queueNum, acd::QueueInfoListT& queueInfoList) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (skill.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty skill", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArSkillIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not master", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_skill_ptr p_skill;

    if (!m_mapSkill.Find(skill, p_skill)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s not existed", agentId.c_str(), handle, skill.c_str());
        ret = acd::AcdResultT::ArSkillNotExist;
        return ret;
    }

    queueNum = 0;
    p_skill->GetWaitingCallInfos(queueNum, queueInfoList);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d skill:%s has queueNum:%d", agentId.c_str(), handle, skill.c_str(),
                                queueNum);
    return ret;
}
