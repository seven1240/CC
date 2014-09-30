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

#ifndef APCLIENT_H
#define APCLIENT_H

#include <bgcc.h>
#include "ApCommon.h"
#include "acd.h"
#include "acdcallback.h"
#include "AgentProxy.h"
using namespace acd;

class AcdCallbackReceiver: public acdcallback {

private:
    virtual ~AcdCallbackReceiver() {}
    virtual void SendAgentEvent(const AgentEventT& event,
                                const std::map<std::string, std::string>& ctx);
    virtual void SendMediaEvent(const MediaEventT& event,
                                const std::map<std::string, std::string>& ctx);
    virtual void SendQueueEvent(const RouteEventT& event,
                                const std::map<std::string, std::string>& ctx);
    virtual void SendOtherEvent(const OtherEventT& event,
                                const std::map<std::string, std::string>& ctx);
};


class ApClient {

private:
    int32_t        _WarnSendmsgTimeout;
    int32_t        _acdMainPort;
    int32_t        _connectionNum;
    std::string    _acdMainIp;
    acdapiProxy*   _acdClientProxy;
    ServiceManager sm;
public:
    ApClient(std::string AcdMainIp, int32_t AcdMainPort, int32_t WarnSendMsgTime,
             int32_t connectionNum) {
        _acdMainIp = AcdMainIp;
        _acdMainPort = AcdMainPort;
        _WarnSendmsgTimeout = WarnSendMsgTime * 1000 * 1000;
        _connectionNum = connectionNum;
    }

    ~ApClient() {
        delete _acdClientProxy;
    }
    bool InitClient();
    AcdResultT SignIn(const std::string& agentId,
                      const std::string& agentDn,
                      const std::string& agentPwd,
                      const StatusChangeT statusChangetype,
                      bool autoAnswer,
                      bool fcSignin,
                      const std::string& skills,
                      int64_t& handle,
                      uint64_t time_rcv);


    AcdResultT SignOut(int64_t handle,
                       const std::string& agentId,
                       uint64_t time_rcv);


    AcdResultT SetAgentStatus(int64_t handle,
                              const std::string& agentId,
                              const AgentStatusT& agentStatus,
                              const std::string& restReason,
                              uint64_t time_rcv);


    AcdResultT GetAgentStatus(int64_t handle,
                              const std::string& agentId,
                              AgentStatusT& agentStatus,
                              uint64_t time_rcv);


    AcdResultT ResetStatuschangetype(int64_t handle,
                                     const std::string& agentId,
                                     const StatusChangeT& statusChangetype,
                                     uint64_t time_rcv);


    AcdResultT ResetAutoAnswer(int64_t handle,
                               const std::string& agentId,
                               bool autoAnswer,
                               uint64_t time_rcv);


    AcdResultT ResetSkill(int64_t handle,
                          const std::string& agentId,
                          const std::string& skills,
                          uint64_t time_rcv);


    AcdResultT Reset(int64_t handle,
                     const std::string& agentId,
                     uint64_t time_rcv);

    AcdResultT OutboundCall(int64_t handle,
                            const std::string& agentId,
                            const std::string& callerId,
                            const std::string& destId,
                            const std::string& forCallerDispNum,
                            const std::string& forCalleeDispNum,
                            int32_t timeout,
                            const CallModeT& callMode,
                            const CallTypeT& callType,
                            uint64_t time_rcv);

    AcdResultT AnswerCall(int64_t handle,
                          const std::string& agentId,
                          uint64_t time_rcv);

    AcdResultT ReleaseCall(int64_t handle,
                           const std::string& agentId,
                           uint64_t time_rcv);

    AcdResultT Hold(int64_t handle,
                    const std::string& agentId,
                    uint64_t time_rcv);

    AcdResultT RetrieveHeld(int64_t handle,
                            const std::string& agentId,
                            uint64_t time_rcv);

    AcdResultT Consult(int64_t handle,
                       const std::string& agentId,
                       const std::string& callerId,
                       const std::string& destId,
                       const std::string& forCallerDispNum,
                       const std::string& forCalleeDispNum,
                       const CallTypeT& callType,
                       uint64_t time_rcv);


    AcdResultT ConsultReconnect(int64_t handle,
                                const std::string& agentId,
                                uint64_t time_rcv);

    AcdResultT ConsultTransfer(int64_t handle,
                               const std::string& agentId,
                               uint64_t time_rcv);

    AcdResultT SingleStepTransfer(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& callerId,
                                  const std::string& destId,
                                  const std::string& forCallerDispNum,
                                  const std::string& forCalleeDispNum,
                                  bool isPassthrough,
                                  const CallTypeT& transferType,
                                  uint64_t time_rcv);

    AcdResultT ConsultConference(int64_t handle,
                                 const std::string& agentId,
                                 uint64_t time_rcv);

    AcdResultT ConferenceJoin(int64_t handle,
                              const std::string& agentId,
                              const std::string& callerId,
                              const std::string& destAgentId,
                              const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum,
                              const ConferenceT& conferenceType,
                              uint64_t time_rcv);

    AcdResultT SetAssociateData(int64_t handle,
                                const std::string& agentId,
                                const std::string& key,
                                const std::string& value,
                                uint64_t time_rcv);

    AcdResultT GetAssociateData(int64_t handle,
                                const std::string& agentId,
                                const std::string& key,
                                std::string& value,
                                uint64_t time_rcv);

    AcdResultT ForceSignIn(int64_t handle,
                           const std::string& agentId,
                           const std::string& destAgentId,
                           const std::string& agentDn,
                           const std::string& agentPwd,
                           const StatusChangeT& statusChangetype,
                           bool autoAnswer,
                           bool fcSignin,
                           const std::string& skills,
                           uint64_t time_rcv);

    AcdResultT ForceSignOut(int64_t handle,
                            const std::string& agentId,
                            const std::string& destAgentId,
                            uint64_t time_rcv);

    AcdResultT ForceSetAgentStatus(int64_t handle,
                                   const std::string& agentId,
                                   const std::string& destAgentId,
                                   const AgentStatusT& agentStatus,
                                   uint64_t time_rcv);

    AcdResultT Listen(int64_t handle,
                      const std::string& agentId,
                      const std::string& callerId,
                      const std::string& destAgentId,
                      const std::string& forCallerDispNum,
                      const std::string& forCalleeDispNum,
                      uint64_t time_rcv);

    AcdResultT StopListen(int64_t handle,
                          const std::string& agentId,
                          const std::string& destAgentId,
                          uint64_t time_rcv);

    AcdResultT Insert(int64_t handle,
                      const std::string& agentId,
                      const std::string& callerId,
                      const std::string& destAgentId,
                      const std::string& forCallerDispNum,
                      const std::string& forCalleeDispNum,
                      uint64_t time_rcv);

    AcdResultT StopInsert(int64_t handle,
                          const std::string& agentId,
                          const std::string& destAgentId,
                          uint64_t time_rcv);

    AcdResultT SwitchInsertorListen(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& callerId,
                                    const std::string& destAgentId,
                                    const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum,
                                    uint64_t time_rcv);

    AcdResultT Break(int64_t handle,
                     const std::string& agentId,
                     const std::string& destAgentId,
                     uint64_t time_rcv);

    AcdResultT SendDTMF(int64_t handle,
                        const std::string& agentId,
                        const std::string& digitals,
                        uint64_t time_rcv);

    AcdResultT StartPlay(int64_t handle,
                         const std::string& agentId,
                         const std::string& filename,
                         uint64_t time_rcv);

    AcdResultT StopPlay(int64_t handle,
                        const std::string& agentId,
                        uint64_t time_rcv);

    AcdResultT MuteOn(int64_t handle,
                      const std::string& agentId,
                      uint64_t time_rcv);

    AcdResultT MuteOff(int64_t handle,
                       const std::string& agentId,
                       uint64_t time_rcv);


    AcdResultT GetAgentDetailByAgentID(int64_t handle,
                                       const std::string& agentId,
                                       const std::string& destAgentId,
                                       AgentInfoT& agentInfo,
                                       uint64_t time_rcv);

    AcdResultT GetAgentDetailByAgentDN(int64_t handle,
                                       const std::string& agentId,
                                       const std::string& destAgentDn,
                                       AgentInfoT& agentInfo,
                                       uint64_t time_rcv);

    AcdResultT GetAgentDetailsByAgentIDs(int64_t handle,
                                         const std::string& agentId,
                                         const StringListT& destAgentIdList,
                                         AgentInfoListT& agentInfoList,
                                         uint64_t time_rcv);

    AcdResultT GetAgentDetailsByAgentDNs(int64_t handle,
                                         const std::string& agentId,
                                         const StringListT& destAgentDnList,
                                         AgentInfoListT& agentInfoList,
                                         uint64_t time_rcv);

    AcdResultT GetRecordFileName(int64_t handle,
                                 const std::string& agentId,
                                 std::string& filename,
                                 uint64_t time_rcv);

    AcdResultT GetRestReason(int64_t handle,
                             const std::string& agentId,
                             StringListT& restReason,
                             uint64_t time_rcv);

    AcdResultT GetSkill(int64_t handle,
                        const std::string& agentId,
                        StringListT& skill,
                        uint64_t time_rcv);

    AcdResultT GetAgentNumberBySkill(int64_t handle,
                                     const std::string& agentId,
                                     const std::string& skill,
                                     int32_t& agentNum,
                                     uint64_t time_rcv);

    AcdResultT GetAgentDetailsBySkill(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& skill,
                                      int32_t& agentNum,
                                      AgentInfoListT& agentInfoList,
                                      uint64_t time_rcv);

    AcdResultT GetSkillWaitingNumber(int64_t handle,
                                     const std::string& agentId,
                                     const std::string& skill,
                                     int32_t& queueNum,
                                     int32_t& freeNum,
                                     uint64_t time_rcv);

    AcdResultT GetSkillWaitingCallInfo(int64_t handle,
                                       const std::string& agentId,
                                       const std::string& skill,
                                       int32_t& queueNum,
                                       QueueInfoListT& queueInfoList,
                                       uint64_t time_rcv);

    AcdResultT GetPrivateQueue(int64_t handle,
                               const std::string& agentId,
                               const std::string& destAgentId,
                               int32_t& queueNum,
                               QueueInfoListT& queueInfoList,
                               uint64_t time_rcv);

    AcdResultT GetSysInfo(int64_t handle,
                          const std::string& agentId,
                          SysInfoT& sysInfo,
                          uint64_t time_rcv);

    AcdResultT SynchronizeCTITime(int64_t handle,
                                  const std::string& agentId,
                                  int64_t& timestamp,
                                  uint64_t time_rcv);

    AcdResultT Heartbeat(int64_t handle,
                         const std::string& agentId,
                         uint64_t time_rcv);
    AcdResultT ResetConfig(const std::string& password,
                           uint64_t time_rcv);

    AcdResultT JumptheQueue(int64_t handle,
                            const std::string& agentId,
                            int64_t requestId,
                            uint64_t time_rcv);

}; // end of class ApClient


#endif

