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

#include "acd_skill.h"

class acd_skill_manager : public Thread {
private:
    uint32_t m_request_timespan;
    uint32_t m_queue_timespan;
    uint32_t m_skill_count;
    vector<acd_skill_ptr> m_skill_array;
    SafeMap<string, acd_skill_ptr> m_mapSkill;
    bgcc::RWLock m_RWLock;

protected:
    virtual void Method();

private:
    static void ProcessUnlock(const string& agentId, const acd_agent_ptr& p_agent);
    static void GetRequestNumber(const string& strSkill, const acd_skill_ptr& p_skill, int32_t& num);
    void InsertSkill(const string& strSkill, acd_skill_ptr& p_skill);
    void EraseSkill(const string& strSkill, const acd_skill_ptr& p_skill);
    void RouteRequest(const ims::RouteEventT& event);
    void RouteRequestCancel(const ims::RouteEventT& event);

public:
    acd_skill_manager();
    ~acd_skill_manager();
    void Initialize(uint32_t request_timespan, uint32_t queue_timespan, uint32_t skill_count);
    void Uninitialize();
    void insert_agent(const string& agentId, const string& skill);
    void erase_agent(const string& agentId, const string& skill);
    void ProcessIMSEvent(const ims::RouteEventT& event);
    int32_t GetRouteRequestNumber();

public:
    acd::AcdResultT GetAgentNumberBySkill(int64_t handle, const std::string& agentId,
                                          const std::string& skill, int32_t& agentNum);
    acd::AcdResultT GetAgentDetailsBySkill(int64_t handle, const std::string& agentId,
                                           const std::string& skill, int32_t& agentNum, acd::AgentInfoListT& agentInfoList);
    acd::AcdResultT GetSkillWaitingNumber(int64_t handle, const std::string& agentId,
                                          const std::string& skill, int32_t& queueNum, int32_t& freeNum);
    acd::AcdResultT GetSkillWaitingCallInfo(int64_t handle, const std::string& agentId,
                                            const std::string& skill, int32_t& queueNum, acd::QueueInfoListT& queueInfoList);
};
