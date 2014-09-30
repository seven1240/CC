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


#pragma once

#include "acd_agent.h"
#include "thread.h"

class acd_agent_manager : public Thread {
private:
    uint32_t m_agent_timeout;
    string m_default_anishow;
    string m_default_destshow;
    string m_password;
    SafeMap<int64_t, acd_agent_ptr> m_agentHandle_map;
    SafeMap<string, acd_agent_ptr> m_agentID_map;
    SafeMap<string, acd_agent_ptr> m_agentDN_map;

protected:
    virtual void Method();

private:
    static bool ProcessCheckAgent(const acd_agent_ptr& p_agent);
    static void ProcessIMSConnect(int64_t handle, const acd_agent_ptr& p_agent);
    static void ProcessIMSDisconnect(int64_t handle, const acd_agent_ptr& p_agent);
    static void ProcessGetAgentCalls(int64_t handle, acd_agent_ptr p_agent, int32_t& num);
    int32_t GetAgentCalls();
    bool CheckAgent(const acd_agent_ptr& p_agent);
    void RouteRequest(const ims::RouteEventT& event);
    void RouteRequestCancel(const ims::RouteEventT& event);
    void RouteRequestSuccess(const ims::RouteEventT& event, const acd_agent_ptr& p_agent);
    void RouteRequestFail(const ims::RouteEventT& event, const ims::RouteEventReasonT& result);

public:
    acd_agent_manager();
    ~acd_agent_manager();
    void Initialize(uint32_t agent_timeout, const string& default_anishow,
                    const string& default_destshow, const string& password);
    void Uninitialize();
    void ProcessIMSEvent(const ims::CallEventT& event);
    void ProcessIMSEvent(const ims::MediaEventT& event);
    void ProcessIMSEvent(const ims::RouteEventT& event);
    void ProcessIMSEvent(const ims::OtherEventT& event);
    void IMSConnect();
    void IMSDisconnect();
    bool GetAgent(const string& agentId, acd_agent_ptr& p_agent);
    SafeMap<string, acd_agent_ptr>& GetAgents();

public:
    acd::AcdResultT SignIn(const string& agentId, const string& agentDn, const string& agentPwd,
                           const acd::StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const string& skill,
                           int64_t& handle, const std::map<std::string, std::string>& ctx);
    acd::AcdResultT SignOut(int64_t handle, const string& agentId);
    acd::AcdResultT SetAgentStatus(int64_t handle, const string& agentId,
                                   const acd::AgentStatusT& agentStatus, const string& restReason);
    acd::AcdResultT GetAgentStatus(int64_t handle, const string& agentId,
                                   acd::AgentStatusT& agentStatus);
    acd::AcdResultT ResetStatuschangetype(int64_t handle, const string& agentId,
                                          const acd::StatusChangeT& statusChangetype);
    acd::AcdResultT ResetAutoAnswer(int64_t handle, const string& agentId, bool autoAnswer);
    acd::AcdResultT ResetSkill(int64_t handle, const string& agentId, const string& skill);
    acd::AcdResultT Reset(int64_t handle, const string& agentId);
    acd::AcdResultT OutboundCall(int64_t handle, const string& agentId, const string& callerId,
                                 const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                 int32_t timeout, const acd::CallModeT& callMode, const acd::CallTypeT& callType);
    acd::AcdResultT AnswerCall(int64_t handle, const string& agentId);
    acd::AcdResultT ReleaseCall(int64_t handle, const string& agentId);
    acd::AcdResultT Hold(int64_t handle, const string& agentId);
    acd::AcdResultT Retrieve(int64_t handle, const string& agentId);
    acd::AcdResultT Consult(int64_t handle, const string& agentId, const string& callerId,
                            const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                            const acd::CallTypeT& callType);
    acd::AcdResultT ConsultReconnect(int64_t handle, const string& agentId);
    acd::AcdResultT ConsultTransfer(int64_t handle, const string& agentId);
    acd::AcdResultT SingleStepTransfer(int64_t handle, const string& agentId, const string& callerId,
                                       const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                       bool isPassthrough, const acd::CallTypeT& transferType);
    acd::AcdResultT ConsultConference(int64_t handle, const string& agentId);
    acd::AcdResultT ConferenceJoin(int64_t handle, const string& agentId, const string& callerId,
                                   const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const acd::ConferenceT& conferenceType);
    acd::AcdResultT SetAssociateData(int64_t handle, const string& agentId, const string& key,
                                     const string& value);
    acd::AcdResultT GetAssociateData(int64_t handle, const string& agentId, const string& key,
                                     string& value);
    acd::AcdResultT ForceSignOut(int64_t handle, const string& agentId, const string& destAgentId);
    acd::AcdResultT ForceSetAgentStatus(int64_t handle, const string& agentId,
                                        const string& destAgentId, const acd::AgentStatusT& agentStatus, const string& restReason);
    acd::AcdResultT Listen(int64_t handle, const string& agentId, const string& callerId,
                           const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT StopListen(int64_t handle, const string& agentId, const string& destAgentId);
    acd::AcdResultT Insert(int64_t handle, const string& agentId, const string& callerId,
                           const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT StopInsert(int64_t handle, const string& agentId, const string& destAgentId);
    acd::AcdResultT SwitchInsertorListen(int64_t handle, const string& agentId, const string& callerId,
                                         const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT Break(int64_t handle, const string& agentId, const string& destAgentId);
    acd::AcdResultT SendDTMF(int64_t handle, const string& agentId, const string& digitals);
    acd::AcdResultT GetAgentDetailByAgentID(int64_t handle, const string& agentId,
                                            const string& destAgentId, acd::AgentInfoT& agentInfo);
    acd::AcdResultT GetAgentDetailByAgentDN(int64_t handle, const string& agentId,
                                            const string& destAgentDn, acd::AgentInfoT& agentInfo);
    acd::AcdResultT GetAgentDetailsByAgentIDs(int64_t handle, const string& agentId,
            const acd::StringListT& destAgentIdList, acd::AgentInfoListT& agentInfoList);
    acd::AcdResultT GetAgentDetailsByAgentDNs(int64_t handle, const string& agentId,
            const acd::StringListT& destAgentDnList, acd::AgentInfoListT& agentInfoList);
    acd::AcdResultT GetRecordFileName(int64_t handle, const string& agentId, string& filename);
    acd::AcdResultT GetSkill(int64_t handle, const string& agentId, acd::StringListT& skill);
    acd::AcdResultT GetRestReason(int64_t handle, const string& agentId, acd::StringListT& restReason);
    acd::AcdResultT GetSysInfo(int64_t handle, const string& agentId, acd::SysInfoT& sysInfo);
    acd::AcdResultT SynchronizeCTITime(int64_t handle, const string& agentId, int64_t& timestamp);
    acd::AcdResultT Heartbeat(int64_t handle, const string& agentId);
    acd::AcdResultT ResetConfig(const string& password);
};
