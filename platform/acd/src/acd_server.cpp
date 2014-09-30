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


#include "acd_server.h"
#include "acd_tool.h"

acd_main_server::acd_main_server() {
}

acd_main_server::~acd_main_server() {
}

void acd_main_server::start_server(uint32_t port, uint32_t thread_num) {
    bgcc::ServiceManager servicemanager;
    bgcc::ThreadPool threadpool;
    servicemanager.add_service(bgcc::SharedPointer<bgcc::IProcessor>(new acd::acdapiProcessor(
                                   bgcc::SharedPointer<acd::acdapi>(new acd_server()))));
    threadpool.init(thread_num);
    bgcc::Server server(&servicemanager, &threadpool, port);

    if (0 != server.serve()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "acd main server listen exit");
        cout << "acd main server listen fail, acd exit!" << endl;
        exit(0);
    }
}

void acd_main_server::stop_server() {
}

acd_server::acd_server() {
}

acd_server::~acd_server() {
}

acd::AcdResultT acd_server::SignIn(const string& agentId, const string& agentDn,
                                   const string& agentPwd, const acd::StatusChangeT& statusChangetype,
                                   bool autoAnswer, bool fcSignin, const string& skill, int64_t& handle,
                                   const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SignIn(agentId, agentDn, agentPwd, statusChangetype, autoAnswer,
                                            fcSignin, skill, handle, ctx);
}

acd::AcdResultT acd_server::SignOut(int64_t handle, const string& agentId,
                                    const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SignOut(handle, agentId);
}

acd::AcdResultT acd_server::SetAgentStatus(int64_t handle, const string& agentId,
        const acd::AgentStatusT& agentStatus, const string& restReason,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SetAgentStatus(handle, agentId, agentStatus, restReason);
}

acd::AcdResultT acd_server::GetAgentStatus(int64_t handle, const string& agentId,
        acd::AgentStatusT& agentStatus, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAgentStatus(handle, agentId, agentStatus);
}

acd::AcdResultT acd_server::ResetStatuschangetype(int64_t handle, const string& agentId,
        const acd::StatusChangeT& statusChangetype, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ResetStatuschangetype(handle, agentId, statusChangetype);
}

acd::AcdResultT acd_server::ResetAutoAnswer(int64_t handle, const string& agentId, bool autoAnswer,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ResetAutoAnswer(handle, agentId, autoAnswer);
}

acd::AcdResultT acd_server::ResetSkill(int64_t handle, const string& agentId, const string& skill,
                                       const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ResetSkill(handle, agentId, skill);
}

acd::AcdResultT acd_server::Reset(int64_t handle, const string& agentId,
                                  const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Reset(handle, agentId);
}

acd::AcdResultT acd_server::OutboundCall(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, int32_t timeout, const acd::CallModeT& callMode,
        const acd::CallTypeT& callType, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.OutboundCall(handle, agentId, callerId, destId, forCallerDispNum,
            forCalleeDispNum, timeout, callMode, callType);
}

acd::AcdResultT acd_server::AnswerCall(int64_t handle, const string& agentId,
                                       const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.AnswerCall(handle, agentId);
}

acd::AcdResultT acd_server::ReleaseCall(int64_t handle, const string& agentId,
                                        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ReleaseCall(handle, agentId);
}

acd::AcdResultT acd_server::Hold(int64_t handle, const string& agentId,
                                 const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Hold(handle, agentId);
}

acd::AcdResultT acd_server::Retrieve(int64_t handle, const string& agentId,
                                     const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Retrieve(handle, agentId);
}

acd::AcdResultT acd_server::Consult(int64_t handle, const string& agentId, const string& callerId,
                                    const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                    const acd::CallTypeT& callType, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Consult(handle, agentId, callerId, destId, forCallerDispNum,
            forCalleeDispNum, callType);
}

acd::AcdResultT acd_server::ConsultReconnect(int64_t handle, const string& agentId,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ConsultReconnect(handle, agentId);
}

acd::AcdResultT acd_server::ConsultTransfer(int64_t handle, const string& agentId,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ConsultTransfer(handle, agentId);
}

acd::AcdResultT acd_server::SingleStepTransfer(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, bool isPassthrough, const acd::CallTypeT& transferType,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SingleStepTransfer(handle, agentId, callerId, destId,
            forCallerDispNum, forCalleeDispNum, isPassthrough, transferType);
}

acd::AcdResultT acd_server::ConsultConference(int64_t handle, const string& agentId,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ConsultConference(handle, agentId);
}

acd::AcdResultT acd_server::ConferenceJoin(int64_t handle, const string& agentId,
        const string& callerId, const string& destId, const string& forCallerDispNum,
        const string& forCalleeDispNum, const acd::ConferenceT& conferenceType,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ConferenceJoin(handle, agentId, callerId, destId, forCallerDispNum,
            forCalleeDispNum, conferenceType);
}

acd::AcdResultT acd_server::SetAssociateData(int64_t handle, const string& agentId,
        const string& key, const string& value, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SetAssociateData(handle, agentId, key, value);
}

acd::AcdResultT acd_server::GetAssociateData(int64_t handle, const string& agentId,
        const string& key, string& value, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAssociateData(handle, agentId, key, value);
}

acd::AcdResultT acd_server::JumptheQueue(int64_t handle, const string& agentId, int64_t requestId,
        const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::ForceSignIn(int64_t handle, const string& agentId,
                                        const string& destAgentId, const string& agentDn, const string& agentPwd,
                                        const acd::StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const string& skill,
                                        const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::ForceSignOut(int64_t handle, const string& agentId,
        const string& destAgentId, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ForceSignOut(handle, agentId, destAgentId);
}

acd::AcdResultT acd_server::ForceSetAgentStatus(int64_t handle, const string& agentId,
        const string& destAgentId, const acd::AgentStatusT& agentStatus,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ForceSetAgentStatus(handle, agentId, destAgentId, agentStatus, "");
}

acd::AcdResultT acd_server::Listen(int64_t handle, const string& agentId, const string& callerId,
                                   const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Listen(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                            forCalleeDispNum);
}

acd::AcdResultT acd_server::StopListen(int64_t handle, const string& agentId,
                                       const string& destAgentId, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.StopListen(handle, agentId, destAgentId);
}

acd::AcdResultT acd_server::Insert(int64_t handle, const string& agentId, const string& callerId,
                                   const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Insert(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                            forCalleeDispNum);
}

acd::AcdResultT acd_server::StopInsert(int64_t handle, const string& agentId,
                                       const string& destAgentId, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.StopInsert(handle, agentId, destAgentId);
}

acd::AcdResultT acd_server::SwitchInsertorListen(int64_t handle, const string& agentId,
        const string& callerId, const string& destAgentId, const string& forCallerDispNum,
        const string& forCalleeDispNum, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SwitchInsertorListen(handle, agentId, callerId, destAgentId,
            forCallerDispNum, forCalleeDispNum);
}

acd::AcdResultT acd_server::Break(int64_t handle, const string& agentId, const string& destAgentId,
                                  const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Break(handle, agentId, destAgentId);
}

acd::AcdResultT acd_server::SendDTMF(int64_t handle, const string& agentId, const string& digitals,
                                     const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SendDTMF(handle, agentId, digitals);
}

acd::AcdResultT acd_server::StartPlay(int64_t handle, const string& agentId, const string& filename,
                                      const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::StopPlay(int64_t handle, const string& agentId,
                                     const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::MuteOn(int64_t handle, const string& agentId,
                                   const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::MuteOff(int64_t handle, const string& agentId,
                                    const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::GetAgentDetailByAgentID(int64_t handle, const string& agentId,
        const string& destAgentId, acd::AgentInfoT& agentInfo,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAgentDetailByAgentID(handle, agentId, destAgentId, agentInfo);
}

acd::AcdResultT acd_server::GetAgentDetailByAgentDN(int64_t handle, const string& agentId,
        const string& destAgentDn, acd::AgentInfoT& agentInfo,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAgentDetailByAgentDN(handle, agentId, destAgentDn, agentInfo);
}

acd::AcdResultT acd_server::GetAgentDetailsByAgentIDs(int64_t handle, const string& agentId,
        const acd::StringListT& destAgentIdList, acd::AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAgentDetailsByAgentIDs(handle, agentId, destAgentIdList,
            agentInfoList);
}

acd::AcdResultT acd_server::GetAgentDetailsByAgentDNs(int64_t handle, const string& agentId,
        const acd::StringListT& destAgentDnList, acd::AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetAgentDetailsByAgentDNs(handle, agentId, destAgentDnList,
            agentInfoList);
}

acd::AcdResultT acd_server::GetRecordFileName(int64_t handle, const string& agentId,
        string& filename, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetRecordFileName(handle, agentId, filename);
}

acd::AcdResultT acd_server::GetSkill(int64_t handle, const string& agentId, acd::StringListT& skill,
                                     const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetSkill(handle, agentId, skill);
}

acd::AcdResultT acd_server::GetRestReason(int64_t handle, const string& agentId,
        acd::StringListT& restReason, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetRestReason(handle, agentId, restReason);
}

acd::AcdResultT acd_server::GetAgentNumberBySkill(int64_t handle, const string& agentId,
        const string& skill, int32_t& agentNum, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_skill_manager.GetAgentNumberBySkill(handle, agentId, skill, agentNum);
}

acd::AcdResultT acd_server::GetAgentDetailsBySkill(int64_t handle, const string& agentId,
        const string& skill, int32_t& agentNum, acd::AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_skill_manager.GetAgentDetailsBySkill(handle, agentId, skill, agentNum,
            agentInfoList);
}

acd::AcdResultT acd_server::GetSkillWaitingNumber(int64_t handle, const string& agentId,
        const string& skill, int32_t& queueNum, int32_t& freeNum,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_skill_manager.GetSkillWaitingNumber(handle, agentId, skill, queueNum, freeNum);
}

acd::AcdResultT acd_server::GetSkillWaitingCallInfo(int64_t handle, const string& agentId,
        const string& skill, int32_t& queueNum, acd::QueueInfoListT& queueInfoList,
        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_skill_manager.GetSkillWaitingCallInfo(handle, agentId, skill, queueNum,
            queueInfoList);
}

acd::AcdResultT acd_server::GetPrivateQueue(int64_t handle, const string& agentId,
        const string& destAgentId, int32_t& queueNum, acd::QueueInfoListT& queueInfoList,
        const std::map<std::string, std::string>& ctx) {
    return acd::AcdResultT::ArSuccess;
}

acd::AcdResultT acd_server::GetSysInfo(int64_t handle, const string& agentId,
                                       acd::SysInfoT& sysInfo, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.GetSysInfo(handle, agentId, sysInfo);
}

acd::AcdResultT acd_server::SynchronizeCTITime(int64_t handle, const string& agentId,
        int64_t& timestamp, const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.SynchronizeCTITime(handle, agentId, timestamp);
}

acd::AcdResultT acd_server::Heartbeat(int64_t handle, const string& agentId,
                                      const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.Heartbeat(handle, agentId);
}

acd::AcdResultT acd_server::ResetConfig(const string& password,
                                        const std::map<std::string, std::string>& ctx) {
    return acd_tool::m_agent_manager.ResetConfig(password);
}
