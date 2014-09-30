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

#include <acd.h>

using namespace std;

class acd_main_server {
public:
    acd_main_server();
    ~acd_main_server();
    void start_server(uint32_t port, uint32_t thread_num);
    void stop_server();
};

class acd_server : public acd::acdapi {
public:
    acd_server();
    ~acd_server();
    virtual acd::AcdResultT SignIn(const string& agentId, const string& agentDn, const string& agentPwd,
                                   const acd::StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const string& skill,
                                   int64_t& handle, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SignOut(int64_t handle, const string& agentId,
                                    const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SetAgentStatus(int64_t handle, const string& agentId,
                                           const acd::AgentStatusT& agentStatus, const string& restReason,
                                           const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentStatus(int64_t handle, const string& agentId,
                                           acd::AgentStatusT& agentStatus, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ResetStatuschangetype(int64_t handle, const string& agentId,
            const acd::StatusChangeT& statusChangetype, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ResetAutoAnswer(int64_t handle, const string& agentId, bool autoAnswer,
                                            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ResetSkill(int64_t handle, const string& agentId, const string& skill,
                                       const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Reset(int64_t handle, const string& agentId,
                                  const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT OutboundCall(int64_t handle, const string& agentId, const string& callerId,
                                         const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                         int32_t timeout, const acd::CallModeT& callMode, const acd::CallTypeT& callType,
                                         const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT AnswerCall(int64_t handle, const string& agentId,
                                       const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ReleaseCall(int64_t handle, const string& agentId,
                                        const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Hold(int64_t handle, const string& agentId,
                                 const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Retrieve(int64_t handle, const string& agentId,
                                     const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Consult(int64_t handle, const string& agentId, const string& callerId,
                                    const string& destId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                    const acd::CallTypeT& callType, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ConsultReconnect(int64_t handle, const string& agentId,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ConsultTransfer(int64_t handle, const string& agentId,
                                            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SingleStepTransfer(int64_t handle, const string& agentId,
            const string& callerId, const string& destId, const string& forCallerDispNum,
            const string& forCalleeDispNum, bool isPassthrough, const acd::CallTypeT& transferType,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ConsultConference(int64_t handle, const string& agentId,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ConferenceJoin(int64_t handle, const string& agentId,
                                           const string& callerId, const string& destId, const string& forCallerDispNum,
                                           const string& forCalleeDispNum, const acd::ConferenceT& conferenceType,
                                           const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SetAssociateData(int64_t handle, const string& agentId, const string& key,
            const string& value, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAssociateData(int64_t handle, const string& agentId, const string& key,
            string& value, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT JumptheQueue(int64_t handle, const string& agentId, int64_t requestId,
                                         const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ForceSignIn(int64_t handle, const string& agentId,
                                        const string& destAgentId, const string& agentDn, const string& agentPwd,
                                        const acd::StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const string& skill,
                                        const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ForceSignOut(int64_t handle, const string& agentId,
                                         const string& destAgentId, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ForceSetAgentStatus(int64_t handle, const string& agentId,
            const string& destAgentId, const acd::AgentStatusT& agentStatus,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Listen(int64_t handle, const string& agentId, const string& callerId,
                                   const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT StopListen(int64_t handle, const string& agentId, const string& destAgentId,
                                       const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Insert(int64_t handle, const string& agentId, const string& callerId,
                                   const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT StopInsert(int64_t handle, const string& agentId, const string& destAgentId,
                                       const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SwitchInsertorListen(int64_t handle, const string& agentId,
            const string& callerId, const string& destAgentId, const string& forCallerDispNum,
            const string& forCalleeDispNum, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Break(int64_t handle, const string& agentId, const string& destAgentId,
                                  const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SendDTMF(int64_t handle, const string& agentId, const string& digitals,
                                     const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT StartPlay(int64_t handle, const string& agentId, const string& filename,
                                      const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT StopPlay(int64_t handle, const string& agentId,
                                     const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT MuteOn(int64_t handle, const string& agentId,
                                   const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT MuteOff(int64_t handle, const string& agentId,
                                    const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentDetailByAgentID(int64_t handle, const string& agentId,
            const string& destAgentId, acd::AgentInfoT& agentInfo,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentDetailByAgentDN(int64_t handle, const string& agentId,
            const string& destAgentDn, acd::AgentInfoT& agentInfo,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentDetailsByAgentIDs(int64_t handle, const string& agentId,
            const acd::StringListT& destAgentIdList, acd::AgentInfoListT& agentInfoList,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentDetailsByAgentDNs(int64_t handle, const string& agentId,
            const acd::StringListT& destAgentDnList, acd::AgentInfoListT& agentInfoList,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetRecordFileName(int64_t handle, const string& agentId, string& filename,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetSkill(int64_t handle, const string& agentId, acd::StringListT& skill,
                                     const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetRestReason(int64_t handle, const string& agentId,
                                          acd::StringListT& restReason, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentNumberBySkill(int64_t handle, const string& agentId,
            const string& skill, int32_t& agentNum, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetAgentDetailsBySkill(int64_t handle, const string& agentId,
            const string& skill, int32_t& agentNum, acd::AgentInfoListT& agentInfoList,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetSkillWaitingNumber(int64_t handle, const string& agentId,
            const string& skill, int32_t& queueNum, int32_t& freeNum,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetSkillWaitingCallInfo(int64_t handle, const string& agentId,
            const string& skill, int32_t& queueNum, acd::QueueInfoListT& queueInfoList,
            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetPrivateQueue(int64_t handle, const string& agentId,
                                            const string& destAgentId, int32_t& queueNum, acd::QueueInfoListT& queueInfoList,
                                            const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT GetSysInfo(int64_t handle, const string& agentId, acd::SysInfoT& sysInfo,
                                       const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT SynchronizeCTITime(int64_t handle, const string& agentId,
            int64_t& timestamp, const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT Heartbeat(int64_t handle, const string& agentId,
                                      const std::map<std::string, std::string>& ctx);
    virtual acd::AcdResultT ResetConfig(const string& password,
                                        const std::map<std::string, std::string>& ctx);
};
