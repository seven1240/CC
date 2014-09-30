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


#include "ApServer.h"
#include "AgentProxy.h"

bool ApServer::InitApServer(std::string ApListenIp, int32_t ApListenPort, int32_t threadPoolNum) {

    bool status = true;

    _ApListenIp = ApListenIp;
    _ApListenPort = ApListenPort;
    _threadPoolNum = threadPoolNum;

    SharedPointer<IProcessor> xp(
        new acdapiProcessor(
            SharedPointer<acdapi>(
                new ApServer)));

    ServiceManager sm;
    sm.add_service(xp);

    ThreadPool tp;
    tp.init(_threadPoolNum);
    Server* server = new Server(&sm, &tp, _ApListenPort);

    if (0 != server->serve()) {
        status =  false;
    }

    return status;
}


AcdResultT ApServer::SignIn(
    const std::string& agentId,
    const std::string& agentDn,
    const std::string& agentPwd,
    const StatusChangeT& statusChangetype,
    bool autoAnswer,
    bool fcSignin,
    const std::string& skills,
    int64_t& handle, const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "SignIn AgentId = %s,AgentDn = %s,AgentPwd = %s,statusChangetype = %d,autoAnswer = %d,fcSignin = %d,skill = %s.",
               agentId.c_str(), agentDn.c_str(), agentPwd.c_str(), statusChangetype.get_value(), autoAnswer,
               fcSignin, skills.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SignIn(agentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skills,
                             handle, ctx, time_rcv);
    return ret;
}


AcdResultT ApServer::SignOut(int64_t handle,
                             const std::string& agentId, const std::map<std::string, std::string>& ctx) {

    BGCC_TRACE("ap", "SignOut AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SignOut(handle, agentId, ctx, time_rcv);


    return ret;
}

AcdResultT ApServer::SetAgentStatus(int64_t handle,
                                    const std::string& agentId,
                                    const AgentStatusT& agentStatus,
                                    const std::string& restReason,
                                    const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "SetAgentStatus AgentId = %s,handle = %"int64ld",agentStatus = %d,restReason = %s.",
               agentId.c_str(), handle, agentStatus.get_value(), restReason.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    AgentData agentinfo;

    ret = agentProxy->SetAgentStatus(handle, agentId, agentStatus, restReason, ctx, time_rcv);


    return ret;
}

AcdResultT ApServer::GetAgentStatus(int64_t handle,
                                    const std::string& agentId,
                                    AgentStatusT& agentStatus,
                                    const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "GetAgentStatus AgentId = %s,handle = %"int64ld",agentStatus = %d.",
               agentId.c_str(), handle, agentStatus.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->GetAgentStatus(handle, agentId, agentStatus, ctx, time_rcv);


    return ret;
}
AcdResultT ApServer::ResetStatuschangetype(int64_t handle,
        const std::string& agentId,
        const StatusChangeT& statusChangetype,
        const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ResetStatuschangetype AgentId = %s,handle = %"int64ld",statusChangetype = %d.",
               agentId.c_str(), handle, statusChangetype.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ResetStatuschangetype(handle, agentId, statusChangetype, ctx, time_rcv);
    return ret;
}
AcdResultT ApServer::ResetAutoAnswer(int64_t handle,
                                     const std::string& agentId,
                                     bool autoAnswer,
                                     const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ResetAutoAnswer AgentId = %s,handle = %"int64ld",autoAnswer = %d.",
               agentId.c_str(), handle, autoAnswer);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->ResetAutoAnswer(handle, agentId, autoAnswer, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::ResetSkill(int64_t handle,
                                const std::string& agentId,
                                const std::string& skill,
                                const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ResetSkill AgentId = %s,handle = %"int64ld",skill = %s.",
               agentId.c_str(), handle, skill.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->ResetSkill(handle, agentId, skill, ctx, time_rcv);

    return ret;
}


AcdResultT ApServer::Reset(int64_t handle, const std::string& agentId,
                           const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "Reset AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Reset(handle, agentId, ctx, time_rcv);


    return ret;
}
AcdResultT ApServer::OutboundCall(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& callerId,
                                  const std::string& destId,
                                  const std::string& forCallerDispNum,
                                  const std::string& forCalleeDispNum,
                                  int32_t timeout,
                                  const CallModeT& callMode,
                                  const CallTypeT& callType,
                                  const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "OutboundCall AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s,timeout = %d,callMode = %d,callType = %d.",
               agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str(),
               timeout, callMode.get_value(), callType.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->OutboundCall(handle, agentId, callerId, destId, forCallerDispNum,
                                   forCalleeDispNum, timeout, callMode, callType, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::AnswerCall(int64_t handle,
                                const std::string& agentId,
                                const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "AnswerCall AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->AnswerCall(handle, agentId, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::ReleaseCall(int64_t handle,
                                 const std::string& agentId,
                                 const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ReleaseCall AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ReleaseCall(handle, agentId, ctx, time_rcv);
    return ret;
}

AcdResultT ApServer::Hold(int64_t handle,
                          const std::string& agentId,
                          const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "Hold AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Hold(handle, agentId, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::Retrieve(int64_t handle,
                              const std::string& agentId,
                              const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "Retrieve AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->RetrieveHeld(handle, agentId, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::Consult(int64_t handle,
                             const std::string& agentId,
                             const std::string& callerId,
                             const std::string& destId,
                             const std::string& forCallerDispNum,
                             const std::string& forCalleeDispNum,
                             const CallTypeT& callType,
                             const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "Consult AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s,callType = %d.",
               agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str(), callType.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    AgentData agentinfo;

    ret = agentProxy->Consult(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum,
                              callType, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::ConsultReconnect(int64_t handle,
                                      const std::string& agentId,
                                      const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ConsultReconnect AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ConsultReconnect(handle, agentId, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::ConsultTransfer(int64_t handle, const std::string& agentId,
                                     const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ConsultTransfer AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->ConsultTransfer(handle, agentId, ctx, time_rcv);

    return ret;

}
AcdResultT ApServer::SingleStepTransfer(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& callerId,
                                        const std::string& destId,
                                        const std::string& forCallerDispNum,
                                        const std::string& forCalleeDispNum,
                                        bool isPassthrough,
                                        const CallTypeT& transferType,
                                        const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "SingleStepTransfer AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s,isPassthrough = %d,transferType = %d.",
               agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str(), isPassthrough, transferType.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SingleStepTransfer(handle, agentId, callerId, destId, forCallerDispNum,
                                         forCalleeDispNum, isPassthrough, transferType, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::ConsultConference(int64_t handle,
                                       const std::string& agentId,
                                       const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ConsultConference AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ConsultConference(handle, agentId, ctx, time_rcv);

    return ret;

}
AcdResultT ApServer::ConferenceJoin(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& callerId,
                                    const std::string& destAgentId,
                                    const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum,
                                    const ConferenceT& conferenceType,
                                    const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "ConferenceJoin AgentId = %s,handle = %"int64ld",callerId = %s,destAgentId = %s,forCallerDispNum = %s,forCalleeDispNum = %s,conferenceType = %d.",
               agentId.c_str(), handle, callerId.c_str(), destAgentId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str(), conferenceType.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->ConferenceJoin(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                     forCalleeDispNum, conferenceType, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::SetAssociateData(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& key,
                                      const std::string& value,
                                      const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "SetAssociateData AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SetAssociateData(handle, agentId, key, value, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::GetAssociateData(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& key,
                                      std::string& value,
                                      const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "GetAssociateData AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->GetAssociateData(handle, agentId, key, value, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::ForceSignIn(int64_t handle,
                                 const std::string& agentId, const std::string& destAgentId,
                                 const std::string& agentDn, const std::string& agentPwd,
                                 const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin,
                                 const std::string& skills, const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "ForceSignIn AgentId = %s,handle = %"int64ld",destAgentId = %s,AgentDn = %s,AgentPwd = %s,statusChangetype = %d,autoAnswer = %d,fcSignin = %d,skill = %s.",
               agentId.c_str(), handle, destAgentId.c_str(), agentDn.c_str(), agentPwd.c_str(),
               statusChangetype.get_value(), autoAnswer, fcSignin, skills.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ForceSignIn(handle, agentId, destAgentId, agentDn, agentPwd, statusChangetype,
                                  autoAnswer, fcSignin, skills, ctx, time_rcv);
    return ret;
}
AcdResultT ApServer::ForceSignOut(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId,
                                  const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "ForceSignOut AgentId = %s,handle = %"int64ld",destAgentId = %s.", agentId.c_str(),
               handle, destAgentId.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ForceSignOut(handle, agentId, destAgentId, ctx, time_rcv);
    return ret;

}
AcdResultT ApServer::ForceSetAgentStatus(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        const AgentStatusT& agentStatus,
        const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "ForceSetAgentStatus AgentId = %s,handle = %"int64ld",destAgentId = %s,agentStatus = %d.",
               agentId.c_str(), handle, destAgentId.c_str(), agentStatus.get_value());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ForceSetAgentStatus(handle, agentId, destAgentId, agentStatus, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::Listen(int64_t handle,
                            const std::string& agentId,
                            const std::string& callerId,
                            const std::string& destAgentId,
                            const std::string& forCallerDispNum,
                            const std::string& forCalleeDispNum,
                            const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "Listen AgentId = %s,handle = %"int64ld",callerId = %s,destAgentId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
               agentId.c_str(), handle, callerId.c_str(), destAgentId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Listen(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum,
                             ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::StopListen(int64_t handle,
                                const std::string& agentId,
                                const std::string& destAgentId,
                                const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "StopListen AgentId = %s,handle = %"int64ld",destAgentId = %s.", agentId.c_str(),
               handle, destAgentId.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->StopListen(handle, agentId, destAgentId, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::Insert(int64_t handle,
                            const std::string& agentId,
                            const std::string& callerId,
                            const std::string& destAgentId,
                            const std::string& forCallerDispNum,
                            const std::string& forCalleeDispNum,
                            const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "Insert AgentId = %s,handle = %"int64ld",callerId = %s,destAgentId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
               agentId.c_str(), handle, callerId.c_str(), destAgentId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Insert(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum,
                             ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::StopInsert(int64_t handle,
                                const std::string& agentId,
                                const std::string& destAgentId,
                                const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "StopInsert AgentId = %s,handle = %"int64ld",destAgentId = %s.", agentId.c_str(),
               handle, destAgentId.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->StopInsert(handle, agentId, destAgentId, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::SwitchInsertorListen(int64_t handle,
        const std::string& agentId,
        const std::string& callerId,
        const std::string& destAgentId,
        const std::string& forCallerDispNum,
        const std::string& forCalleeDispNum,
        const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap",
               "SwitchInsertorListen AgentId = %s,handle = %"int64ld",callerId = %s,destAgentId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
               agentId.c_str(), handle, callerId.c_str(), destAgentId.c_str(), forCallerDispNum.c_str(),
               forCalleeDispNum.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SwitchInsertorListen(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                           forCalleeDispNum, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::Break(int64_t handle,
                           const std::string& agentId,
                           const std::string& destAgentId,
                           const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "Break AgentId = %s,handle = %"int64ld",destAgentId = %s.", agentId.c_str(),
               handle, destAgentId.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Break(handle, agentId, destAgentId, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::SendDTMF(int64_t handle,
                              const std::string& agentId,
                              const std::string& digitals,
                              const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "SendDTMF AgentId = %s,handle = %"int64ld",digitals = %s.", agentId.c_str(),
               handle, digitals.c_str());
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SendDTMF(handle, agentId, digitals, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::StartPlay(int64_t handle,
                               const std::string& agentId,
                               const std::string& filename,
                               const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "StartPlay AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->StartPlay(handle, agentId, filename, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::StopPlay(int64_t handle, const std::string& agentId,
                              const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "StopPlay AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->StopPlay(handle, agentId, ctx, time_rcv);
    return ret;
}


AcdResultT ApServer::MuteOn(int64_t handle, const std::string& agentId,
                            const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "MuteOn AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->MuteOn(handle, agentId, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::MuteOff(int64_t handle, const std::string& agentId,
                             const std::map<std::string, std::string>& ctx) {
    BGCC_TRACE("ap", "MuteOff AgentId = %s,handle = %"int64ld".", agentId.c_str(), handle);
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->MuteOff(handle, agentId, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::GetAgentDetailByAgentID(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        AgentInfoT& agentInfo,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetAgentDetailByAgentID(handle, agentId, destAgentId, agentInfo, ctx, time_rcv);
    return ret;
}

AcdResultT ApServer::GetAgentDetailByAgentDN(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentDn,
        AgentInfoT& agentInfo,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->GetAgentDetailByAgentDN(handle, agentId, destAgentDn, agentInfo, ctx, time_rcv);

    return ret;
}


AcdResultT ApServer::GetAgentDetailsByAgentIDs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentIdList,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetAgentDetailsByAgentIDs(handle, agentId, destAgentIdList, agentInfoList, ctx,
            time_rcv);

    return ret;
}

AcdResultT ApServer::GetAgentDetailsByAgentDNs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentDnList,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetAgentDetailsByAgentDNs(handle, agentId, destAgentDnList, agentInfoList, ctx,
            time_rcv);

    return ret;
}

AcdResultT ApServer::GetRecordFileName(int64_t handle,
                                       const std::string& agentId,
                                       std::string& filename,
                                       const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetRecordFileName(handle, agentId, filename, ctx, time_rcv);

    return ret;
}
AcdResultT ApServer::GetRestReason(int64_t handle,
                                   const std::string& agentId,
                                   StringListT& restReason,
                                   const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetRestReason(handle, agentId, restReason, ctx, time_rcv);

    return ret;
}


AcdResultT ApServer::GetSkill(
    int64_t handle,
    const std::string& agentId,
    StringListT& skill,
    const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->GetSkill(handle, agentId, skill, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::GetAgentNumberBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetAgentNumberBySkill(handle, agentId, skill, agentNum, ctx, time_rcv);
    return ret;
}

AcdResultT ApServer::GetAgentDetailsBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;
    ret = agentProxy->GetAgentDetailsBySkill(handle, agentId, skill, agentNum, agentInfoList, ctx,
            time_rcv);

    return ret;
}


AcdResultT ApServer::GetSkillWaitingNumber(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        int32_t& freeNum,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetSkillWaitingNumber(handle, agentId, skill, queueNum, freeNum, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::GetSkillWaitingCallInfo(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        QueueInfoListT& queueInfoList,
        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetSkillWaitingCallInfo(handle, agentId, skill, queueNum, queueInfoList, ctx,
            time_rcv);

    return ret;
}

AcdResultT ApServer::GetPrivateQueue(int64_t handle,
                                     const std::string& agentId,
                                     const std::string& destAgentId,
                                     int32_t& queueNum,
                                     QueueInfoListT& queueInfoList,
                                     const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetPrivateQueue(handle, agentId, destAgentId, queueNum, queueInfoList, ctx,
                                      time_rcv);

    return ret;
}

AcdResultT ApServer::GetSysInfo(int64_t handle,
                                const std::string& agentId,
                                SysInfoT& sysInfo,
                                const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->GetSysInfo(handle, agentId, sysInfo, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::SynchronizeCTITime(int64_t handle,
                                        const std::string& agentId,
                                        int64_t& timestamp,
                                        const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->SynchronizeCTITime(handle, agentId, timestamp, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::Heartbeat(int64_t handle, const std::string& agentId,
                               const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->Heartbeat(handle, agentId, ctx, time_rcv);

    return ret;
}

AcdResultT ApServer::JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId,
                                  const std::map<std::string, std::string>& ctx) {

    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->JumptheQueue(handle, agentId, requestId, ctx, time_rcv);
    return ret;
}
AcdResultT ApServer::ResetConfig(const std::string& password,
                                 const std::map<std::string, std::string>& ctx) {
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AgentProxy* agentProxy = AgentProxy::Instance();
    AcdResultT ret;

    ret = agentProxy->ResetConfig(password, ctx, time_rcv);
    return ret;
}
ApServer::~ApServer() {}

