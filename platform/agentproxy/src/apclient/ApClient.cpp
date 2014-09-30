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



#include "ApClient.h"
using namespace std;

void AcdCallbackReceiver::SendAgentEvent(const AgentEventT& event,
        const std::map<std::string, std::string>& ctx) {
    BGCC_NOTICE("ap", "AcdCallbackReceiver::SendAgentEvent In.");
    std::ostringstream stream;
    AgentEventT& Event = const_cast<AgentEventT&>(event);
    stream << std::endl;
    stream << "================CALL EVENT BEGIN================" << std::endl;
    stream << "AgentId        : " << Event.agentId << std::endl;
    stream << "Time           : " << (uint64_t)Event.timestamp << std::endl;
    stream << "EventId        : " << Event.eventId.get_desc() << std::endl;
    stream << "AgentDn        : " << Event.agentDn << std::endl;
    stream << "CallId         : " << Event.callId << std::endl;
    stream << "SessionID      : " << (uint64_t)Event.sessionId << std::endl;
    stream << "AgentStatus    : " << Event.agentStatus.get_desc() << std::endl;
    stream << "OriginateCallid: " << Event.originalCallid << std::endl;
    stream << "PartyNum       : " << Event.partyNum << std::endl;
    stream << "OtherParty     : " << Event.otherParty << std::endl;
    stream << "OtherAttr      : " << Event.otherAttr.get_desc() << std::endl;
    stream << "OrignatingParty: " << Event.originatingParty << std::endl;
    stream << "OriginateANI   : " << Event.originalAni << std::endl;
    stream << "OriginateDNIS  : " << Event.originalDnis << std::endl;
    stream << "Reason         : " << Event.reason.get_desc() << std::endl;
    stream << "================CALL EVENT END==================" << std::endl;

    BGCC_NOTICE("ap", "SendAgentEvent:Receive Event %s", stream.str().c_str());

    AgentProxy* agentPrx = AgentProxy::Instance();
    (void)agentPrx->AddAcdCallEvent(Event);

    return;
}
void AcdCallbackReceiver::SendMediaEvent(const MediaEventT& event,
        const std::map<std::string, std::string>& ctx) {
    BGCC_NOTICE("ap", "AcdCallbackReceiver::SendMediaEvent In.");
    std::ostringstream stream;
    MediaEventT& Event = const_cast<MediaEventT&>(event);
    stream << std::endl;
    stream << "================MEDIA EVENT BEGIN================" << std::endl;
    stream << "AgentId        : " << Event.agentId << std::endl;
    stream << "Time           : " << (uint64_t)Event.timestamp << std::endl;
    stream << "Type           : " << Event.eventType.get_desc() << std::endl;
    stream << "AgentDn        : " << Event.agentDn << std::endl;
    stream << "CallID         : " << Event.callId << std::endl;
    stream << "SessionID      : " << (uint64_t)Event.sessionId << std::endl;
    stream << "MediaState     : " << Event.state.get_desc() << std::endl;
    stream << "Reason         : " << Event.reason.get_desc() << std::endl;
    stream << "OtherParty     : " << Event.otherParty << std::endl;
    stream << "MediaBuffer    : " << Event.buffer << std::endl;
    stream << "================MEDIA EVENT END==================" << std::endl;

    BGCC_NOTICE("ap", "SendMediaEvent:Receive MediaEvent %s", stream.str().c_str());

    AgentProxy* agentPrx = AgentProxy::Instance();
    (void)agentPrx->AddAcdMediaEvent(Event);
    return;
}
void AcdCallbackReceiver::SendQueueEvent(const RouteEventT& event,
        const std::map<std::string, std::string>& ctx) {
    BGCC_NOTICE("ap", "AcdCallbackReceiver::SendQueueEvent In.");
    std::stringstream stream;
    RouteEventT& Event = const_cast<RouteEventT&>(event);
    stream << std::endl;
    stream << "================ROUTE EVENT BEGIN================" << std::endl;
    stream << "AgentId        : " << Event.agentId << std::endl;
    stream << "Time           : " << (uint64_t)Event.timestamp << std::endl;
    stream << "Type           : " << Event.eventType.get_desc() << std::endl;
    stream << "AgentDn        : " << Event.agentDn << std::endl;
    stream << "CallID         : " << Event.callId << std::endl;
    stream << "SessionID      : " << (uint64_t)Event.sessionId << std::endl;
    stream << "OriginateANI   : " << Event.originalAni << std::endl;
    stream << "OriginateDNIS  : " << Event.originalDnis << std::endl;
    stream << "================ROUTE EVENT END==================" << std::endl;
    BGCC_NOTICE("ap", "SendRouteEvent:Receive RouteEvent %s", stream.str().c_str());

    AgentProxy* agentPrx = AgentProxy::Instance();
    (void)agentPrx->AddAcdRouteEvent(Event);
    return;
}

void AcdCallbackReceiver::SendOtherEvent(const OtherEventT& event,
        const std::map<std::string, std::string>& ctx) {
    BGCC_NOTICE("ap", "AcdCallbackReceiver::SendOtherEvent In.");
    std::stringstream stream;
    OtherEventT& Event = const_cast<OtherEventT&>(event);
    stream << std::endl;
    stream << "================OTHER EVENT BEGIN================" << std::endl;
    stream << "AgentId        : " << Event.agentId << std::endl;
    stream << "Time           : " << (uint64_t)Event.timestamp << std::endl;
    stream << "Type           : " << Event.eventType.get_desc() << std::endl;
    stream << "AgentDn        : " << Event.agentDn << std::endl;
    stream << "CallID         : " << Event.callId << std::endl;
    stream << "SessionID      : " << (uint64_t)Event.sessionId << std::endl;
    stream << "OriginateANI   : " << Event.originalAni << std::endl;
    stream << "OriginateDNIS  : " << Event.originalDnis << std::endl;
    stream << "================OTHER EVENT END==================" << std::endl;
    BGCC_NOTICE("ap", "SendOtherEvent:Receive OtherEvent %s", stream.str().c_str());

    AgentProxy* agentPrx = AgentProxy::Instance();
    (void)agentPrx->AddAcdOtherEvent(Event);
    return;
}


bool ApClient::InitClient() {
    SharedPointer<IProcessor> xp(
        new acdcallbackProcessor(
            SharedPointer<acdcallback>(
                new AcdCallbackReceiver)));

    sm.add_service(xp);
    _acdClientProxy = new acdapiProxy(ServerInfo(_acdMainIp, _acdMainPort), &sm, 1);
    return true;
}

AcdResultT ApClient::SignIn(const std::string& agentId,
                            const std::string& agentDn,
                            const std::string& agentPwd,
                            const StatusChangeT statusChangetype,
                            bool autoAnswer, bool fcSignin,
                            const std::string& skill,
                            int64_t& handle,
                            uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "SignIn:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld".",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SignIn(agentId, agentDn, agentPwd, statusChangetype,
                                      autoAnswer, fcSignin, skill, handle);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SignIn:Fail to SignIn to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SignIn:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::SignOut(int64_t handle,
                             const std::string& agentId,
                             uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "SignOut:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SignOut(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SignOut:Fail to SignOut to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SignOut:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::SetAgentStatus(int64_t handle,
                                    const std::string& agentId,
                                    const AgentStatusT& agentStatus,
                                    const std::string& restReason,
                                    uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "SetAgentStatus:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SetAgentStatus(handle, agentId, agentStatus, restReason);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "SetAgentStatus:Fail to SetAgentStatus to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SetAgentStatus:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentStatus(int64_t handle,
                                    const std::string& agentId,
                                    AgentStatusT& agentStatus,
                                    uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentStatus:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentStatus(handle, agentId, agentStatus);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentStatus:Fail to GetAgentStatus to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SetAgentStatus:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ResetStatuschangetype(int64_t handle,
        const std::string& agentId,
        const StatusChangeT& statusChangetype,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ResetStatuschangetype:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ResetStatuschangetype(handle, agentId, statusChangetype);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ResetStatuschangetype:Fail to ResetStatuschangetype to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ResetStatuschangetype:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ResetAutoAnswer(int64_t handle,
                                     const std::string& agentId,
                                     bool autoAnswer,
                                     uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ResetAutoAnswer:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ResetAutoAnswer(handle, agentId, autoAnswer);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ResetAutoAnswer:Fail to ResetAutoAnswer to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ResetAutoAnswer:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ResetSkill(int64_t handle,
                                const std::string& agentId,
                                const std::string& skill,
                                uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ResetSkill:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ResetSkill(handle, agentId, skill);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "ResetSkill:Fail to ResetSkill to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ResetSkill:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::Reset(int64_t handle, const std::string& agentId, uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Reset:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Reset(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Reset:Fail to Reset to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Reset:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::OutboundCall(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& callerId,
                                  const std::string& destId,
                                  const std::string& forCallerDispNum,
                                  const std::string& forCalleeDispNum,
                                  int32_t timeout,
                                  const CallModeT& callMode,
                                  const CallTypeT& callType,
                                  uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "OutboundCall:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }


    if (_acdClientProxy) {
        ret = _acdClientProxy->OutboundCall(handle, agentId, callerId, destId, forCallerDispNum,
                                            forCalleeDispNum, timeout, callMode, callType);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "OutboundCall:Fail to OutboundCall to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "OutboundCall:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::AnswerCall(int64_t handle,
                                const std::string& agentId,
                                uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "AnswerCall:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->AnswerCall(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "AnswerCall:Fail to AnswerCall to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "AnswerCall:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::ReleaseCall(int64_t handle,
                                 const std::string& agentId,
                                 uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ReleaseCall:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ReleaseCall(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ReleaseCall:Fail to ReleaseCall to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ReleaseCall:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::Hold(int64_t handle,
                          const std::string& agentId,
                          uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Hold:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Hold(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Hold:Fail to Hold to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Hold:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }


    return ret;
}
AcdResultT ApClient::RetrieveHeld(int64_t handle,
                                  const std::string& agentId,
                                  uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "RetrieveHeld:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Retrieve(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "RetrieveHeld:Fail to RetrieveHeld to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "RetrieveHeld:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::Consult(int64_t handle,
                             const std::string& agentId,
                             const std::string& callerId,
                             const std::string& destId,
                             const std::string& forCallerDispNum,
                             const std::string& forCalleeDispNum,
                             const CallTypeT& callType,
                             uint64_t time_rcv) {

    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Consult:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Consult(handle, agentId, callerId, destId, forCallerDispNum,
                                       forCalleeDispNum, callType);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Consult:Fail to Consult to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Consult:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ConsultReconnect(int64_t handle,
                                      const std::string& agentId,
                                      uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ConsultReconnect:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }


    if (_acdClientProxy) {
        ret = _acdClientProxy->ConsultReconnect(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ConsultReconnect:Fail to ConsultReconnect to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ConsultReconnect:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ConsultTransfer(int64_t handle, const std::string& agentId,
                                     uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ConsultTransfer:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ConsultTransfer(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ConsultTransfer:Fail to ConsultTransfer to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ConsultTransfer:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::SingleStepTransfer(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& callerId,
                                        const std::string& destId,
                                        const std::string& forCallerDispNum,
                                        const std::string& forCalleeDispNum,
                                        bool isPassthrough,
                                        const CallTypeT& transferType,
                                        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "SingleStepTransfer:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }


    if (_acdClientProxy) {
        ret = _acdClientProxy->SingleStepTransfer(handle, agentId, callerId, destId, forCallerDispNum,
                forCalleeDispNum, isPassthrough, transferType);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "SingleStepTransfer:Fail to SingleStepTransfer to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SingleStepTransfer:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ConsultConference(int64_t handle,
                                       const std::string& agentId,
                                       uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ConsultConference:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }


    if (_acdClientProxy) {
        ret = _acdClientProxy->ConsultConference(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ConsultConference:Fail to ConsultConference to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ConsultConference:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;

}
AcdResultT ApClient::ConferenceJoin(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& callerId,
                                    const std::string& destAgentId,
                                    const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum,
                                    const ConferenceT& conferenceType,
                                    uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ConferenceJoin:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ConferenceJoin(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                              forCalleeDispNum, conferenceType);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ConferenceJoin:Fail to ConferenceJoin to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ConferenceJoin:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::SetAssociateData(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& key,
                                      const std::string& value,
                                      uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "SetAssociateData:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SetAssociateData(handle, agentId, key, value);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "SetAssociateData:Fail to SetAssociateData to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SetAssociateData:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::GetAssociateData(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& key,
                                      std::string& value,
                                      uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAssociateData:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAssociateData(handle, agentId, key, value);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAssociateData:Fail to GetAssociateData to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAssociateData:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ForceSignIn(int64_t handle,
                                 const std::string& agentId,
                                 const std::string& destAgentId,
                                 const std::string& agentDn,
                                 const std::string& agentPwd,
                                 const StatusChangeT& statusChangetype,
                                 bool autoAnswer,
                                 bool fcSignin,
                                 const std::string& skill,
                                 uint64_t time_rcv) {

    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ForceSignIn:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ForceSignIn(handle, agentId, destAgentId, agentDn, agentPwd,
                                           statusChangetype, autoAnswer, fcSignin, skill);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ForceSignIn:Fail to ForceSignIn to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ForceSignIn:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::ForceSignOut(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId,
                                  uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ForceSignOut:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ForceSignOut(handle, agentId, destAgentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ForceSignOut:Fail to ForceSignOut to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ForceSignOut:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;

}
AcdResultT ApClient::ForceSetAgentStatus(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        const AgentStatusT& agentStatus,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "ForceSetAgentStatus:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ForceSetAgentStatus(handle, agentId, destAgentId, agentStatus);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "ForceSetAgentStatus:Fail to ForceSetAgentStatus to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ForceSetAgentStatus:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::Listen(int64_t handle,
                            const std::string& agentId,
                            const std::string& callerId,
                            const std::string& destAgentId,
                            const std::string& forCallerDispNum,
                            const std::string& forCalleeDispNum,
                            uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Listen:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Listen(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                      forCalleeDispNum);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Listen:Fail to Listen to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Listen:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::StopListen(int64_t handle,
                                const std::string& agentId,
                                const std::string& destAgentId,
                                uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "StopListen:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->StopListen(handle, agentId, destAgentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "StopListen:Fail to StopListen to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "StopListen:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::Insert(int64_t handle,
                            const std::string& agentId,
                            const std::string& callerId,
                            const std::string& destAgentId,
                            const std::string& forCallerDispNum,
                            const std::string& forCalleeDispNum,
                            uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Insert:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Insert(handle, agentId, callerId, destAgentId, forCallerDispNum,
                                      forCalleeDispNum);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Insert:Fail to Insert to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Insert:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::StopInsert(int64_t handle,
                                const std::string& agentId,
                                const std::string& destAgentId,
                                uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "StopInsert:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->StopInsert(handle, agentId, destAgentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "StopInsert:Fail to StopInsert to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "StopInsert:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::SwitchInsertorListen(int64_t handle,
        const std::string& agentId,
        const std::string& callerId,
        const std::string& destAgentId,
        const std::string& forCallerDispNum,
        const std::string& forCalleeDispNum,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "SwitchInsertorListen:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SwitchInsertorListen(handle, agentId, callerId, destAgentId,
                forCallerDispNum, forCalleeDispNum);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "SwitchInsertorListen:Fail to SwitchInsertorListen to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SwitchInsertorListen:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::Break(int64_t handle,
                           const std::string& agentId,
                           const std::string& destAgentId,
                           uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Break:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Break(handle, agentId, destAgentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Break:Fail to Break to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Break:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::SendDTMF(int64_t handle,
                              const std::string& agentId,
                              const std::string& digitals,
                              uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "SendDTMF:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SendDTMF(handle, agentId, digitals);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SendDTMF:Fail to SendDTMF to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SendDTMF:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::StartPlay(int64_t handle,
                               const std::string& agentId,
                               const std::string& filename,
                               uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "StartPlay:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->StartPlay(handle, agentId, filename);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "StartPlay:Fail to StartPlay to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "StartPlay:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::StopPlay(int64_t handle, const std::string& agentId, uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "StopPlay:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->StopPlay(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "StopPlay:Fail to StopPlay to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "StopPlay:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::MuteOn(int64_t handle, const std::string& agentId, uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "MuteOn:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->MuteOn(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "MuteOn:Fail to MuteOn to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "MuteOn:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}
AcdResultT ApClient::MuteOff(int64_t handle, const std::string& agentId, uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "MuteOff:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->MuteOff(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "MuteOff:Fail to MuteOff to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "MuteOff:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentDetailByAgentID(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        AgentInfoT& agentInfo,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentDetailByAgentID:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentDetailByAgentID(handle, agentId, destAgentId, agentInfo);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentDetailByAgentID:Fail to GetAgentDetailByAgentID to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentDetailByAgentID:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentDetailByAgentDN(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentDn,
        AgentInfoT& agentInfo,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentDetailByAgentDN:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentDetailByAgentDN(handle, agentId, destAgentDn, agentInfo);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentDetailByAgentDN:Fail to GetAgentDetailByAgentDN to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentDetailByAgentDN:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::GetAgentDetailsByAgentIDs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentIdList,
        AgentInfoListT& agentInfoList,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentDetailsByAgentIDs:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentDetailsByAgentIDs(handle, agentId, destAgentIdList, agentInfoList);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentDetailsByAgentIDs:Fail to GetAgentDetailsByAgentIDs to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentDetailsByAgentIDs:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentDetailsByAgentDNs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentDnList,
        AgentInfoListT& agentInfoList,
        uint64_t time_rcv) {
    AcdResultT ret;

    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentDetailsByAgentDNs:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentDetailsByAgentDNs(handle, agentId, destAgentDnList, agentInfoList);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentDetailsByAgentDNs:Fail to GetAgentDetailsByAgentDNs to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentDetailsByAgentDNs:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetRecordFileName(int64_t handle,
                                       const std::string& agentId,
                                       std::string& filename,
                                       uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetRecordFileName:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetRecordFileName(handle, agentId, filename);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetRecordFileName:Fail to GetRecordFileName to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetRecordFileName:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetSkill(int64_t handle,
                              const std::string& agentId,
                              StringListT& skill,
                              uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "GetSkill:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetSkill(handle, agentId, skill);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "GetSkill:Fail to GetSkill to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetSkill:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetRestReason(int64_t handle,
                                   const std::string& agentId,
                                   StringListT& restReason,
                                   uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetRestReason:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetRestReason(handle, agentId, restReason);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetRestReason:Fail to GetRestReason to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetRestReason:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentNumberBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentNumberBySkill:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentNumberBySkill(handle, agentId, skill, agentNum);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentNumberBySkill:Fail to GetAgentNumberBySkill to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentNumberBySkill:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetAgentDetailsBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        AgentInfoListT& agentInfoList,
        uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetAgentDetailsBySkill:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetAgentDetailsBySkill(handle, agentId, skill, agentNum, agentInfoList);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetAgentDetailsBySkill:Fail to GetAgentDetailsBySkill to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetAgentDetailsBySkill:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::GetSkillWaitingNumber(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        int32_t& freeNum,
        uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetSkillWaitingNumber:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetSkillWaitingNumber(handle, agentId, skill, queueNum, freeNum);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetSkillWaitingNumber:Fail to GetSkillWaitingNumber to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetSkillWaitingNumber:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetSkillWaitingCallInfo(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        QueueInfoListT& queueInfoList,
        uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetSkillWaitingCallInfo:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetSkillWaitingCallInfo(handle, agentId, skill, queueNum, queueInfoList);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetSkillWaitingCallInfo:Fail to GetSkillWaitingCallInfo to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetSkillWaitingCallInfo:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetPrivateQueue(int64_t handle,
                                     const std::string& agentId,
                                     const std::string& destAgentId,
                                     int32_t& queueNum,
                                     QueueInfoListT& queueInfoList,
                                     uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetPrivateQueue:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetPrivateQueue(handle, agentId, destAgentId, queueNum, queueInfoList);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "GetPrivateQueue:Fail to GetPrivateQueue to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetPrivateQueue:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::GetSysInfo(int64_t handle,
                                const std::string& agentId,
                                SysInfoT& sysInfo,
                                uint64_t time_rcv) {

    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "GetSysInfo:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->GetSysInfo(handle, agentId, sysInfo);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "GetSysInfo:Fail to GetSysInfo to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "GetSysInfo:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::SynchronizeCTITime(int64_t handle,
                                        const std::string& agentId,
                                        int64_t& timestamp,
                                        uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "SynchronizeCTITime:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->SynchronizeCTITime(handle, agentId, timestamp);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "SynchronizeCTITime:Fail to SynchronizeCTITime to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "SynchronizeCTITime:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}



AcdResultT ApClient::Heartbeat(int64_t handle, const std::string& agentId, uint64_t time_rcv) {

    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "Heartbeat:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->Heartbeat(handle, agentId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "Heartbeat:Fail to Heartbeat to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "Heartbeat:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}


AcdResultT ApClient::ResetConfig(const std::string& password,
                                 uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap", "ResetConfig:SendMsg Timeout.sendtime = %"uint64ld"", time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->ResetConfig(password);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "ResetConfig:Fail to ResetConfig to ACD.errno = %d.", err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "ResetConfig:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

AcdResultT ApClient::JumptheQueue(int64_t handle,
                                  const std::string& agentId,
                                  int64_t requestId,
                                  uint64_t time_rcv) {
    AcdResultT ret;
    uint64_t time = TimeUtil::get_timestamp_ms() - time_rcv;

    if (time > (uint64_t)_WarnSendmsgTimeout) {
        BGCC_WARN("ap",
                  "JumptheQueue:SendMsg Timeout.AgentId = %s,handle = %"int64ld",sendtime = %"uint64ld"",
                  agentId.c_str(), handle, time);
    }

    if (_acdClientProxy) {
        ret = _acdClientProxy->JumptheQueue(handle, agentId, requestId);

        int32_t err = _acdClientProxy->get_errno();

        if (err != 0) {
            BGCC_WARN("ap",
                      "JumptheQueue:Fail to Heartbeat to ACD.AgentId = %s,handle = %"int64ld",errno = %d.",
                      agentId.c_str(), handle, err);
            ret = AcdResultT::ArConnAcdFail;
        }
    } else {
        BGCC_WARN("ap", "JumptheQueue:Proxy is NULL");
        ret = AcdResultT::ArApFailed;
    }

    return ret;
}

