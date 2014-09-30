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

#include "thread.h"
#include "safe_queue.h"
#include "safe_set.h"
#include "acd_agent.h"

class requestinfo {
private:
    bool m_transferAgent;
    time_t m_waitbegin;
    ims::RouteEventT m_event;

public:
    requestinfo(const ims::RouteEventT& event);
    ~requestinfo();
    time_t GetWaitbeginTime();
    ims::RouteEventT& GetEvent();
};

typedef bgcc::SharedPtr<requestinfo> request_ptr;

class free_agent {
private:
    uint64_t m_t;
    bool m_isfree;
    acd_agent_ptr m_agent_ptr;
public:
    free_agent();
    ~free_agent();
    void setTime(uint64_t t);
    uint64_t getTime();
    void setFree();
    bool isFree();
    void setAgentPtr(const acd_agent_ptr& p_agent);
    acd_agent_ptr GetAgentPtr();
};

class acd_skill : public Thread {
private:
    int64_t m_skill_flag;
    uint32_t m_queue_timespan;
    string m_strSkill;
    SafeSet<string> m_setAgent;
    SafeQueue<ims::RouteRequestIDT> m_queueRequest;
    SafeMap<ims::RouteRequestIDT, request_ptr> m_mapRequest;

protected:
    virtual void Method();

private:
    static void ProcessIdleAgent(const string& agentId, free_agent& agent);
    static bool isTimeoutRequest(const request_ptr& pRequest);
    static bool ProcessInvalidRequest(const request_ptr& pRequest);
    static void GetFreeAgent(const string& agentId, int32_t& freeNum);
    static void GerAgentDetail(const string& agentId, acd::AgentInfoListT& agentInfoList);
    static void GetWaitingCallInfo(ims::RouteRequestIDT requestId, const request_ptr& pRequest,
                                   acd::QueueInfoListT& queueInfoList);
    static bool UnlockByRequestId(const string& agentId, const ims::RouteEventT& event);
    bool GetIdleAgent(acd_agent_ptr& p_agent);

public:
    acd_skill(int64_t skill_flag, uint32_t queue_timespan);
    ~acd_skill();
    bool isNotUseSkill();
    void UseSkill(const string& strSkill);
    void UnuseSkill();
    bool InsertAgent(const string& agentId);
    bool EraseAgent(const string& agentId);
    int32_t GetAgentNumber();
    int32_t GetRequestNumber();
    void GetWaitingNumber(int32_t& queueNum, int32_t& freeNum);
    void GetAgentDetails(int32_t& agentNum, acd::AgentInfoListT& agentInfoList);
    void GetWaitingCallInfos(int32_t& queueNum, acd::QueueInfoListT& queueInfoList);
    void RouteRequest(const ims::RouteEventT& event);
    void RouteRequestCancel(const ims::RouteEventT& event);
};

typedef bgcc::SharedPtr<acd_skill> acd_skill_ptr;
