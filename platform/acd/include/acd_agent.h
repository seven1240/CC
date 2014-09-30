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

#include "safe_map.h"
#include "acd_info.h"

using namespace std;

class acd_agent {
private:
    string m_agentId;
    string m_agentDn;
    acd::StatusChangeT m_statusChangetype;
    bool m_autoAnswer;
    string m_skill;
    int64_t m_handle;
    acd_callback_proxy_ptr m_callback_ptr;

    ims::SessionIdT m_sessionId;
    ims::CallIdT m_callId;
    ims::RouteRequestIDT m_requestId;
    time_t m_validTime;
    time_t m_heartbeatTime;                        // 心跳时间
    string m_recordFilename;                         // 录音生成的语音文件名

    time_t m_loginTime;                              // 登陆时间
    acd::AgentStatusT m_agentStatus;
    time_t m_currStatusTime;
    time_t m_callTime;
    time_t m_answerTime;
    string m_origCaller;                             // 原始主叫
    string m_origCallee;                             // 原始被叫
    uint32_t m_callTimes;                            // 此次登录呼叫次数
    uint32_t m_answerTimes;                          // 此次登录应答次数
    time_t m_freeTotalTime;                          // 此次登录空闲总时长
    time_t m_busyTotalTime;                          // 此次登录忙总时长
    time_t m_restTotalTime;                          // 此次登录休息总时长
    time_t m_callTotalTime;                          // 此次登录后呼叫总时长
    time_t m_answerTotalTime;                        // 此次登录后通话总时长
    string m_agentIP;
    callinfo m_callinfo;

    bgcc::RWLock m_RWLock;

private:
    void WriteTraceLog(const string& restReason = "");
    void SetStatus(const acd::AgentStatusT& agentStatus, const acd::CallEventReasonT& reason,
                   const string& restReason = "");
    void Record();
    void Reset();

public:
    acd_agent(void);
    ~acd_agent(void);
    string GetAgentId();
    string GetAgentDn();
    string GetAgentSkill();
    int64_t GetHandle();
    ims::SessionIdT GetSessionId();
    string GetRecordFileName();
    void GetAgentDetail(acd::AgentInfoT& agentInfo);
    void lock(const ims::RouteEventT& event, time_t waitbegin = time(NULL));
    bool unlock(const ims::RouteEventT& event);
    bool unlockTimeout();
    bool isCalling();
    time_t GetCurrStatusTime();
    uint64_t GetHeartbeatTime();
    bool AssignDn();
    void ProcessIMSEvent(const ims::CallEventT& event);
    void ProcessIMSEvent(const ims::MediaEventT& event);
    void ProcessIMSEvent(const ims::OtherEventT& event);
    void ProcessIMSEvent(const acd::OtherEventTypeT& type);

public:
    void SetAgentStatus(const acd::AgentStatusT& agentStatus, const string& restReason);
    acd::AgentStatusT GetAgentStatus();
    void ResetStatuschangetype(const acd::StatusChangeT& statusChangetype);
    void ResetAutoAnswer(bool autoAnswer);
    void ResetSkill(const string& skill);

public:
    acd::AcdResultT SignIn(const string& agentId, const string& agentDn,
                           const acd::StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const string& skill,
                           int64_t& handle, const std::map<std::string, std::string>& ctx);
    acd::AcdResultT SignOut(bool fcSignout);
    acd::AcdResultT OutboundCall(const string& callerId, const string& destId,
                                 const string& forCallerDispNum, const string& forCalleeDispNum, int32_t timeout,
                                 const acd::CallModeT& callMode);
    acd::AcdResultT AnswerCall();
    acd::AcdResultT ReleaseCall();
    acd::AcdResultT Hold();
    acd::AcdResultT Retrieve();
    acd::AcdResultT Consult(const string& callerId, const string& destId,
                            const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT ConsultReconnect();
    acd::AcdResultT ConsultTransfer();
    acd::AcdResultT SingleStepTransfer(const string& callerId, const string& destId,
                                       const string& forCallerDispNum, const string& forCalleeDispNum, bool isPassthrough);
    acd::AcdResultT ConsultConference();
    acd::AcdResultT ConferenceJoin(ims::SessionIdT sessionId, const string& callerId,
                                   const string& destAgentId, const string& forCallerDispNum, const string& forCalleeDispNum,
                                   const acd::ConferenceT& conferenceType);
    acd::AcdResultT SetAssociateData(const string& key, const string& value);
    acd::AcdResultT GetAssociateData(const string& key, string& value);
    acd::AcdResultT Listen(ims::SessionIdT sessionId, const string& callerId, const string& destAgentId,
                           const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT Insert(ims::SessionIdT sessionId, const string& callerId, const string& destAgentId,
                           const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT SwitchInsertorListen(const string& callerId, const string& destAgentId,
                                         const string& forCallerDispNum, const string& forCalleeDispNum);
    acd::AcdResultT SendDTMF(const string& digitals);
    acd::AcdResultT Heartbeat();
};

typedef bgcc::SharedPtr<acd_agent> acd_agent_ptr;
