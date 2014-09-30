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


#include "acd_agent_manager.h"
#include "acd_tool.h"

void acd_agent_manager::Method() {
    while (this->mIsLoop) {
        bgcc::TimeUtil::safe_sleep_s(m_agent_timeout / 2);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "remove timeout agent");
        m_agentHandle_map.Remove(acd_agent_manager::ProcessCheckAgent);
    }
}

bool acd_agent_manager::ProcessCheckAgent(const acd_agent_ptr& p_agent) {
    return acd_tool::m_agent_manager.CheckAgent(p_agent);
}

void acd_agent_manager::ProcessIMSConnect(int64_t handle, const acd_agent_ptr& p_agent) {
    if (p_agent->AssignDn()) {
        p_agent->ProcessIMSEvent(acd::OtherEventTypeT::IMSMasterChange);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s assign success", p_agent->GetAgentId().c_str(),
                                    p_agent->GetAgentDn().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s assign fail", p_agent->GetAgentId().c_str(),  p_agent->GetAgentDn().c_str());
    }
}

void acd_agent_manager::ProcessIMSDisconnect(int64_t handle, const acd_agent_ptr& p_agent) {
    p_agent->ProcessIMSEvent(acd::OtherEventTypeT::IMSDisconnect);
}

void acd_agent_manager::ProcessGetAgentCalls(int64_t handle, acd_agent_ptr p_agent, int32_t& num) {
    if (p_agent->isCalling()) {
        num++;
    }
}

int32_t acd_agent_manager::GetAgentCalls() {
    int32_t num = 0;
    m_agentHandle_map.DoSomething(acd_agent_manager::ProcessGetAgentCalls, num);
    return num;
}

bool acd_agent_manager::CheckAgent(const acd_agent_ptr& p_agent) {
    if (time(NULL) - p_agent->GetHeartbeatTime() <  m_agent_timeout) {
        return false;
    }

    acd::AcdResultT ret = p_agent->SignOut(true);

    if (acd::AcdResultT::ArSuccess == ret) {
        m_agentID_map.Erase(p_agent->GetAgentId());
        m_agentDN_map.Erase(p_agent->GetAgentDn());
        acd_tool::m_skill_manager.erase_agent(p_agent->GetAgentId(), p_agent->GetAgentSkill());
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d timeout signout success", p_agent->GetAgentId().c_str(),
                                    p_agent->GetHandle());
        return true;
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d timeout signout fail:%s", p_agent->GetAgentId().c_str(),
                                    p_agent->GetHandle(), ret.get_desc().c_str());
        return false;
    }
}

void acd_agent_manager::RouteRequest(const ims::RouteEventT& event) {
    if (event.requestType == ims::RouteRequestTypeT::RR_TypePrivate) {
        acd_agent_ptr p_agent;

        if (m_agentID_map.Find(event.requestArgs, p_agent)) {
            if (acd::AgentStatusT::AsReadyState == p_agent->GetAgentStatus()) {
                RouteRequestSuccess(event, p_agent);
            } else {
                RouteRequestFail(event, ims::RouteEventReasonT::RouteReasonBusy);
            }
        } else {
            RouteRequestFail(event, ims::RouteEventReasonT::RouteReasonNotAssigned);
        }
    } else if (event.requestType == ims::RouteRequestTypeT::RR_TypePrivateList) {
        vector<string> vecAgent;
        bgcc::StringUtil::split_string(string(event.requestArgs), ",", vecAgent, true);

        free_agent agent;
        acd_agent_ptr p_agent;
        bool isAgentExisted = false;

        for (vector<string>::iterator it = vecAgent.begin(); it != vecAgent.end(); it++) {
            if (m_agentID_map.Find(*it, p_agent)) {
                isAgentExisted = true;

                if (acd::AgentStatusT::AsReadyState == p_agent->GetAgentStatus()
                        && agent.getTime() > p_agent->GetCurrStatusTime()) {
                    agent.setFree();
                    agent.setTime(p_agent->GetCurrStatusTime());
                    agent.setAgentPtr(p_agent);
                }
            }
        }

        if (agent.isFree() && acd::AgentStatusT::AsReadyState == agent.GetAgentPtr()->GetAgentStatus()) {
            RouteRequestSuccess(event, agent.GetAgentPtr());
        } else if (isAgentExisted) {
            RouteRequestFail(event, ims::RouteEventReasonT::RouteReasonBusy);
        } else {
            RouteRequestFail(event, ims::RouteEventReasonT::RouteReasonNotAssigned);
        }
    }
}

void acd_agent_manager::RouteRequestCancel(const ims::RouteEventT& event) {
    if (event.requestType == ims::RouteRequestTypeT::RR_TypePrivate) {
        acd_agent_ptr p_agent;

        if (m_agentID_map.Find(event.requestArgs, p_agent)) {
            p_agent->unlock(event);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "requestId:%"SHOW_LONG"d agentId:%s cancel success", event.requstid, event.requestArgs.c_str());
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "requestId:%"SHOW_LONG"d agentId:%s cancel fail:agent not existed", event.requstid,
                                        event.requestArgs.c_str());
        }
    } else if (event.requestType == ims::RouteRequestTypeT::RR_TypePrivateList) {
        vector<string> vecAgent;
        bgcc::StringUtil::split_string(string(event.requestArgs), ",", vecAgent, true);

        acd_agent_ptr p_agent;

        for (vector<string>::iterator it = vecAgent.begin(); it != vecAgent.end(); it++) {
            if (m_agentID_map.Find(*it, p_agent)) {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                            "requestId:%"SHOW_LONG"d check agentId:%s", event.requstid, it->c_str());

                if (p_agent->unlock(event)) {
                    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                                "requestId:%"SHOW_LONG"d agentId:%s cancel success", event.requstid, it->c_str());
                    break;
                }
            } else {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                            "requestId:%"SHOW_LONG"d agentId:%s cancel fail:agent not existed", event.requstid, it->c_str());
            }
        }
    }
}

void acd_agent_manager::RouteRequestSuccess(const ims::RouteEventT& event,
        const acd_agent_ptr& p_agent) {
    p_agent->lock(event);

    if (acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid,
            ims::RouteEventReasonT::RouteReasonSuccess, p_agent->GetAgentDn())) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d request agentId:%s agentDn:%s success", event.requstid,
                                    event.requestArgs.c_str(), p_agent->GetAgentDn().c_str());
    } else {
        p_agent->unlock(event);
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d request agentId:%s agentDn:%s fail", event.requstid,
                                    event.requestArgs.c_str(), p_agent->GetAgentDn().c_str());
    }
}

void acd_agent_manager::RouteRequestFail(const ims::RouteEventT& event,
        const ims::RouteEventReasonT& result) {
    acd_tool::p_m_acd_ims->RouteRequestRespond(event.sessionid, event.requstid, result, "");
    time_t t = time(NULL);
    callinfo info;
    info.Initial(event.sessionid, event.callid, "", "", "", event.callerDn, event.calleeDn, t, t);
    info.WriteCallLog();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                "requestId:%"SHOW_LONG"d request agentId:%s fail:%s", event.requstid, event.requestArgs.c_str(),
                                result.get_desc().c_str());
}

acd_agent_manager::acd_agent_manager() : m_agent_timeout(60), m_default_anishow(""),
    m_default_destshow(""), m_password("") {
}

acd_agent_manager::~acd_agent_manager() {
}

void acd_agent_manager::Initialize(uint32_t agent_timeout, const string& default_anishow,
                                   const string& default_destshow, const string& password) {
    m_agent_timeout = agent_timeout;
    m_default_anishow = default_anishow;
    m_default_destshow = default_destshow;
    m_password = password;
    Start();
}

void acd_agent_manager::Uninitialize() {
    Stop();
}

void acd_agent_manager::ProcessIMSEvent(const ims::CallEventT& event) {
    acd_agent_ptr p_agent;

    if (m_agentDN_map.Find(event.device, p_agent)) {
        p_agent->ProcessIMSEvent(event);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentDn:%s not find", event.device.c_str());
    }
}

void acd_agent_manager::ProcessIMSEvent(const ims::MediaEventT& event) {
    acd_agent_ptr p_agent;

    if (m_agentDN_map.Find(event.device, p_agent)) {
        p_agent->ProcessIMSEvent(event);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentDn:%s not find", event.device.c_str());
    }
}

void acd_agent_manager::ProcessIMSEvent(const ims::RouteEventT& event) {
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

void acd_agent_manager::ProcessIMSEvent(const ims::OtherEventT& event) {
    acd_agent_ptr p_agent;

    if (m_agentDN_map.Find(event.device, p_agent)) {
        p_agent->ProcessIMSEvent(event);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentDn:%s not find", event.device.c_str());
    }
}

void acd_agent_manager::IMSConnect() {
    m_agentHandle_map.DoSomething(acd_agent_manager::ProcessIMSConnect);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "connect to ims");
}

void acd_agent_manager::IMSDisconnect() {
    m_agentHandle_map.DoSomething(acd_agent_manager::ProcessIMSDisconnect);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "disconnect to ims");
}

bool acd_agent_manager::GetAgent(const string& agentId, acd_agent_ptr& p_agent) {
    return m_agentID_map.Find(agentId, p_agent);
}

SafeMap<string, acd_agent_ptr>& acd_agent_manager::GetAgents() {
    return m_agentID_map;
}

acd::AcdResultT acd_agent_manager::SignIn(const string& agentId, const string& agentDn,
        const string& agentPwd, const acd::StatusChangeT& statusChangetype,
        bool autoAnswer, bool fcSignin, const string& skill, int64_t& handle,
        const std::map<std::string, std::string>& ctx) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    // 参数验证
    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (agentDn.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s empty agentDn", agentId.c_str());
        ret = acd::AcdResultT::ArAgentDnIsEmpty;
        return ret;
    }

    if (skill.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s empty skill", agentId.c_str());
        ret = acd::AcdResultT::ArSkillIsEmpty;
        return ret;
    }

    // 主备验证
    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s not master", agentId.c_str());
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    // 坐席验证
    ret = acd_tool::validate_agent(agentId, agentPwd, skill);

    if (ret != acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentPwd:%s skill:%s validate error:%s", agentId.c_str(), agentPwd.c_str(),
                                    skill.c_str(), ret.get_desc().c_str());
        return ret;
    }

    // 分机是否被占用
    acd_agent_ptr p_agent;

    if (m_agentDN_map.Find(agentDn, p_agent) && p_agent->GetAgentId() != agentId) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s occupied by agentId %s", agentId.c_str(), agentDn.c_str(),
                                    p_agent->GetAgentId().c_str());
        ret = acd::AcdResultT::ArAgentDnBeOccupied;
        return ret;
    }

    // 登录
    if (m_agentID_map.Find(agentId, p_agent)) { // 坐席已登录
        if (fcSignin) {
            int64_t handle_temp = p_agent->GetHandle();
            string agentDn_temp = p_agent->GetAgentDn();
            string skill_temp = p_agent->GetAgentSkill();
            ret = p_agent->SignIn(agentId, agentDn, statusChangetype, autoAnswer, true, skill, handle, ctx);

            if (ret == acd::AcdResultT::ArSuccess) {
                m_agentHandle_map.Erase(handle_temp);
                m_agentHandle_map.Insert(handle, p_agent);
                m_agentDN_map.Erase(agentDn_temp);
                m_agentDN_map.Insert(agentDn, p_agent);
                acd_tool::m_skill_manager.erase_agent(agentId, skill_temp);
                acd_tool::m_skill_manager.insert_agent(agentId, skill);
                acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                            "agentId:%s handle:%"SHOW_LONG"d SignIn success", agentId.c_str(), handle);
            } else {
                acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                            "agentId:%s SignIn fail:%s", agentId.c_str(), ret.get_desc().c_str());
            }
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s has signed in", agentId.c_str());
            ret = acd::AcdResultT::ArHasSigned;
        }
    } else {
        p_agent = acd_agent_ptr(new acd_agent());
        ret = p_agent->SignIn(agentId, agentDn, statusChangetype, autoAnswer, false, skill, handle, ctx);

        if (ret == acd::AcdResultT::ArSuccess) {
            m_agentHandle_map.Insert(handle, p_agent);
            m_agentID_map.Insert(agentId, p_agent);
            m_agentDN_map.Insert(agentDn, p_agent);
            acd_tool::m_skill_manager.insert_agent(agentId, skill);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d SignIn success", agentId.c_str(), handle);
        } else {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s SignIn fail:%s", agentId.c_str(), ret.get_desc().c_str());
        }
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SignOut(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->SignOut(false);

    if (ret == acd::AcdResultT::ArSuccess) {
        m_agentHandle_map.Erase(handle);
        m_agentID_map.Erase(p_agent->GetAgentId());
        m_agentDN_map.Erase(p_agent->GetAgentDn());
        acd_tool::m_skill_manager.erase_agent(p_agent->GetAgentId(), p_agent->GetAgentSkill());
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SignOut success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SignOut fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SetAgentStatus(int64_t handle, const string& agentId,
        const acd::AgentStatusT& agentStatus, const string& restReason) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    p_agent->SetAgentStatus(agentStatus, restReason);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d set status:%s success", agentId.c_str(), handle,
                                agentStatus.get_desc().c_str());
    return ret;
}

acd::AcdResultT acd_agent_manager::GetAgentStatus(int64_t handle, const string& agentId,
        acd::AgentStatusT& agentStatus) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    agentStatus = p_agent->GetAgentStatus();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d get status:%s success", agentId.c_str(), handle,
                                agentStatus.get_desc().c_str());
    return ret;
}

acd::AcdResultT acd_agent_manager::ResetStatuschangetype(int64_t handle, const string& agentId,
        const acd::StatusChangeT& statusChangetype) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    p_agent->ResetStatuschangetype(statusChangetype);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d set Statuschangetype:%s success", agentId.c_str(), handle,
                                statusChangetype.get_desc().c_str());
    return ret;
}

acd::AcdResultT acd_agent_manager::ResetAutoAnswer(int64_t handle, const string& agentId,
        bool autoAnswer) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    p_agent->ResetAutoAnswer(autoAnswer);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d set autoAnswer:%d success", agentId.c_str(), handle, autoAnswer);
    return ret;
}

acd::AcdResultT acd_agent_manager::ResetSkill(int64_t handle, const string& agentId,
        const string& skill) {
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
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    ret = acd_tool::validate_agent(agentId, skill);

    if (ret != acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d skill:%s validate error:%s", agentId.c_str(), handle,
                                    skill.c_str(), ret.get_desc().c_str());
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_tool::m_skill_manager.erase_agent(p_agent->GetAgentId(), p_agent->GetAgentSkill());
    acd_tool::m_skill_manager.insert_agent(p_agent->GetAgentId(), skill);
    p_agent->ResetSkill(skill);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d ResetSkill:%s success", agentId.c_str(), handle, skill.c_str());
    return ret;
}

acd::AcdResultT acd_agent_manager::Reset(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    p_agent->ReleaseCall();
    p_agent->SignOut(false);
    m_agentHandle_map.Erase(p_agent->GetHandle());
    m_agentID_map.Erase(p_agent->GetAgentId());
    m_agentDN_map.Erase(p_agent->GetAgentDn());
    acd_tool::m_skill_manager.erase_agent(p_agent->GetAgentId(), p_agent->GetAgentSkill());
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d Reset success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::OutboundCall(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, int32_t timeout, const acd::CallModeT& callMode,
        const acd::CallTypeT& callType) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    string dstDevicenumber(destId);

    if (callType == acd::CallTypeT::CtAgent) {
        acd_agent_ptr p_agentDest;

        if (!m_agentID_map.Find(destId, p_agentDest)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d destId %s is not existed", agentId.c_str(), handle,
                                        destId.c_str());
            ret = acd::AcdResultT::ArDestAgentIdNotExist;
            return ret;
        }

        dstDevicenumber = p_agentDest->GetAgentDn();
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->OutboundCall(callerId, dstDevicenumber, forCallerDispNumPara, forCalleeDispNumPara,
                                timeout, callMode);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d OutboundCall success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d OutboundCall fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::AnswerCall(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->AnswerCall();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d AnswerCall success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d AnswerCall fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ReleaseCall(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ReleaseCall();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ReleaseCall success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ReleaseCall fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::Hold(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->Hold();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Hold success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Hold fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::Retrieve(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->Retrieve();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d RetrieveHeld success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d RetrieveHeld fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::Consult(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, const acd::CallTypeT& callType) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    string dstDevicenumber(destId);

    if (callType == acd::CallTypeT::CtAgent) {
        acd_agent_ptr p_agentDest;

        if (!m_agentID_map.Find(destId, p_agentDest)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d destId %s is not existed", agentId.c_str(), handle,
                                        destId.c_str());
            ret = acd::AcdResultT::ArDestAgentIdNotExist;
            return ret;
        }

        dstDevicenumber = p_agentDest->GetAgentDn();
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->Consult(callerId, dstDevicenumber, forCallerDispNumPara, forCalleeDispNumPara);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Consult success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Consult fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ConsultReconnect(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ConsultReconnect();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultReconnect success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultReconnect fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ConsultTransfer(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ConsultTransfer();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultTransfer success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultTransfer fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SingleStepTransfer(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, bool isPassthrough, const acd::CallTypeT& transferType) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    string dstDevicenumber(destId);

    if (transferType == acd::CallTypeT::CtAgent) {
        acd_agent_ptr p_agentDest;

        if (!m_agentID_map.Find(destId, p_agentDest)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d destId %s is not existed", agentId.c_str(), handle,
                                        destId.c_str());
            ret = acd::AcdResultT::ArDestAgentIdNotExist;
            return ret;
        }

        dstDevicenumber = p_agentDest->GetAgentDn();
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->SingleStepTransfer(callerId, dstDevicenumber, forCallerDispNumPara,
                                      forCalleeDispNumPara, isPassthrough);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SingleStepTransfer success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SingleStepTransfer fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ConsultConference(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ConsultConference();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultConference success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConsultConference fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ConferenceJoin(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, const acd::ConferenceT& conferenceType) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_agent_ptr p_destAgent;

    if (!m_agentID_map.Find(destId, p_destAgent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destId %s is not existed", agentId.c_str(), handle,
                                    destId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->ConferenceJoin(p_agent->GetSessionId(), p_destAgent->GetAgentDn(),
                                  p_agent->GetAgentDn(), forCallerDispNumPara, forCalleeDispNumPara, conferenceType);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConferenceJoin success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ConferenceJoin fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SetAssociateData(int64_t handle, const string& agentId,
        const string& key, const string& value) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (key.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty key", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArKeyIsEmpty;
        return ret;
    }

    if (value.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty value", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArValueIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->SetAssociateData(key, value);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SetAssociateData success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SetAssociateData fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::GetAssociateData(int64_t handle, const string& agentId,
        const string& key, string& value) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (key.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty key", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArKeyIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->GetAssociateData(key, value);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d GetAssociateData success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d GetAssociateData fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ForceSignOut(int64_t handle, const string& agentId,
        const string& destAgentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentID_map.Find(destAgentId, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    p_agent->ReleaseCall();
    ret = p_agent->SignOut(true);

    if (ret == acd::AcdResultT::ArSuccess) {
        m_agentHandle_map.Erase(p_agent->GetHandle());
        m_agentID_map.Erase(p_agent->GetAgentId());
        m_agentDN_map.Erase(p_agent->GetAgentDn());
        acd_tool::m_skill_manager.erase_agent(p_agent->GetAgentId(), p_agent->GetAgentSkill());
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d ForceSignOut success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SignOut fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ForceSetAgentStatus(int64_t handle, const string& agentId,
        const string& destAgentId, const acd::AgentStatusT& agentStatus, const string& restReason) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentID_map.Find(destAgentId, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    p_agent->SetAgentStatus(agentStatus, restReason);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d ForceSetAgentStatus success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::Listen(int64_t handle, const string& agentId,
        const string& callerId, const string& destAgentId, const string& forCallerDispNum,
        const string& forCalleeDispNum) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_agent_ptr p_destAgent;

    if (!m_agentID_map.Find(destAgentId, p_destAgent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->Listen(p_destAgent->GetSessionId(), callerId, p_destAgent->GetAgentDn(),
                          forCallerDispNumPara, forCalleeDispNumPara);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Listen success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Listen fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::StopListen(int64_t handle, const string& agentId,
        const string& destAgentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ReleaseCall();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d StopListen success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d StopListen fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::Insert(int64_t handle, const string& agentId,
        const string& callerId, const string& destAgentId, const string& forCallerDispNum,
        const string& forCalleeDispNum) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_agent_ptr p_destAgent;

    if (!m_agentID_map.Find(destAgentId, p_destAgent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    string forCallerDispNumPara(forCallerDispNum);
    string forCalleeDispNumPara(forCalleeDispNum);

    if (forCallerDispNum.empty()) {
        forCallerDispNumPara = m_default_anishow;
    }

    if (forCalleeDispNum.empty()) {
        forCalleeDispNumPara = m_default_destshow;
    }

    ret = p_agent->Insert(p_destAgent->GetSessionId(), callerId, p_destAgent->GetAgentDn(),
                          forCallerDispNumPara, forCalleeDispNumPara);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Insert success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Insert fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::StopInsert(int64_t handle, const string& agentId,
        const string& destAgentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->ReleaseCall();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d StopInsert success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d StopInsert fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SwitchInsertorListen(int64_t handle, const string& agentId,
        const string& callerId, const string& destAgentId, const string& forCallerDispNum,
        const string& forCalleeDispNum) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (callerId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty callerId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArCallerIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->SwitchInsertorListen(callerId, destAgentId, forCallerDispNum, forCalleeDispNum);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SwitchInsertorListen success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SwitchInsertorListen fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::Break(int64_t handle, const string& agentId,
        const string& destAgentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentID_map.Find(destAgentId, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    ret = p_agent->ReleaseCall();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Break success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Break fail:%s", agentId.c_str(), handle, ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::SendDTMF(int64_t handle, const string& agentId,
        const string& digitals) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (digitals.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty digitals", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDigitalsIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->SendDTMF(digitals);

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SendDTMF success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d SendDTMF fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::GetAgentDetailByAgentID(int64_t handle, const string& agentId,
        const string& destAgentId, acd::AgentInfoT& agentInfo) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    // get agent detail
    acd_agent_ptr p_agent;

    if (!m_agentID_map.Find(destAgentId, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                    destAgentId.c_str());
        ret = acd::AcdResultT::ArDestAgentIdNotExist;
        return ret;
    }

    p_agent->GetAgentDetail(agentInfo);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetAgentDetailByAgentID success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetAgentDetailByAgentDN(int64_t handle, const string& agentId,
        const string& destAgentDn, acd::AgentInfoT& agentInfo) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (destAgentDn.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d empty destAgentDn", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArDestDnIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    // get agent detail
    acd_agent_ptr p_agent;

    if (!m_agentDN_map.Find(destAgentDn, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d destAgentDn %s is not existed", agentId.c_str(), handle,
                                    destAgentDn.c_str());
        ret = acd::AcdResultT::ArDestAgentDnNotExist;
        return ret;
    }

    p_agent->GetAgentDetail(agentInfo);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetAgentDetailByAgentDN success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetAgentDetailsByAgentIDs(int64_t handle, const string& agentId,
        const acd::StringListT& destAgentIdList, acd::AgentInfoListT& agentInfoList) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    // get agent details
    for (acd::StringListT::const_iterator it = destAgentIdList.begin(); it != destAgentIdList.end();
            it++) {
        if (it->empty()) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d empty destAgentId", agentId.c_str(), handle);
            continue;
        }

        acd_agent_ptr p_agent;

        if (!m_agentID_map.Find(*it, p_agent)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d destAgentId %s is not existed", agentId.c_str(), handle,
                                        it->c_str());
            continue;
        }

        acd::AgentInfoT agentInfo;
        p_agent->GetAgentDetail(agentInfo);
        agentInfoList.push_back(agentInfo);
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetAgentDetailsByAgentIDs success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetAgentDetailsByAgentDNs(int64_t handle, const string& agentId,
        const acd::StringListT& destAgentDnList, acd::AgentInfoListT& agentInfoList) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    // get agent details
    for (acd::StringListT::const_iterator it = destAgentDnList.begin(); it != destAgentDnList.end();
            it++) {
        if (it->empty()) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d empty destAgentDn", agentId.c_str(), handle);
            continue;
        }

        acd_agent_ptr p_agent;

        if (!m_agentDN_map.Find(*it, p_agent)) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s handle:%"SHOW_LONG"d destAgentDn %s is not existed", agentId.c_str(), handle,
                                        it->c_str());
            continue;
        }

        acd::AgentInfoT agentInfo;
        p_agent->GetAgentDetail(agentInfo);
        agentInfoList.push_back(agentInfo);
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetAgentDetailsByAgentDNs success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetRecordFileName(int64_t handle, const string& agentId,
        string& filename) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    filename = p_agent->GetRecordFileName();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetRecordFileName success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetSkill(int64_t handle, const string& agentId,
        acd::StringListT& skill) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    if (!m_agentHandle_map.Find(handle)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_tool::GetSkill(skill);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetSkill success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetRestReason(int64_t handle, const string& agentId,
        acd::StringListT& restReason) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    if (!m_agentHandle_map.Find(handle)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    acd_tool::GetRestReason(restReason);
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d GetRestReason success", agentId.c_str(), handle);
    return ret;
}

acd::AcdResultT acd_agent_manager::GetSysInfo(int64_t handle, const string& agentId,
        acd::SysInfoT& sysInfo) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    if (!m_agentHandle_map.Find(handle)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    sysInfo.totalAgents    = m_agentHandle_map.Size();
    sysInfo.ivrCalls       = 0;
    sysInfo.agentCalls     = GetAgentCalls();
    sysInfo.totalCalls     = sysInfo.ivrCalls + sysInfo.agentCalls;
    sysInfo.queueCalls     = acd_tool::m_skill_manager.GetRouteRequestNumber();
    sysInfo.privQueueCalls = 0;
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d, totalAgents:%d, totalCalls:%d, ivrCalls:%d, agentCalls:%d, queueCalls:%d, privQueueCalls:%d",
                                agentId.c_str(), handle, sysInfo.totalAgents, sysInfo.totalCalls, sysInfo.ivrCalls,
                                sysInfo.agentCalls, sysInfo.queueCalls, sysInfo.privQueueCalls);
    return ret;
}

acd::AcdResultT acd_agent_manager::SynchronizeCTITime(int64_t handle, const string& agentId,
        int64_t& timestamp) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    if (!m_agentHandle_map.Find(handle)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    timestamp = bgcc::TimeUtil::get_timestamp_us();
    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "agentId:%s handle:%"SHOW_LONG"d, timestamp:%"SHOW_LONG"d", agentId.c_str(), handle, timestamp);
    return ret;
}

acd::AcdResultT acd_agent_manager::Heartbeat(int64_t handle, const string& agentId) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (agentId.empty()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "empty agentId");
        ret = acd::AcdResultT::ArAgentIdIsEmpty;
        return ret;
    }

    if (!acd_tool::p_m_acd_backup->GetIsMaster()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d not master", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNotMaster;
        return ret;
    }

    acd_agent_ptr p_agent;

    if (!m_agentHandle_map.Find(handle, p_agent)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d has not signed in", agentId.c_str(), handle);
        ret = acd::AcdResultT::ArNoSignin;
        return ret;
    }

    ret = p_agent->Heartbeat();

    if (ret == acd::AcdResultT::ArSuccess) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Heartbeat success", agentId.c_str(), handle);
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s handle:%"SHOW_LONG"d Heartbeat fail:%s", agentId.c_str(), handle,
                                    ret.get_desc().c_str());
    }

    return ret;
}

acd::AcdResultT acd_agent_manager::ResetConfig(const string& password) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (0 != password.compare(m_password)) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "wrong password");
        ret = acd::AcdResultT::ArPasswordError;
        return ret;
    }

    if (!acd_tool::ResetConfig()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                    "something error happen");
        ret = acd::AcdResultT::ArFailed;
        return ret;
    }

    acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                "ResetConfig success");
    return ret;
}
