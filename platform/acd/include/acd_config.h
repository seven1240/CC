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

#include "const_define.h"
#include "safe_set.h"
#include "safe_map.h"

class acd_config {
private:
    // mysql configuration para
    string m_dbhost;
    uint32_t m_dbport;
    string m_dbusername;
    string m_dbpasswd;
    string m_dbname;

    bgcc::Mutex m_Locker;

public:
    // log para
    uint32_t m_log_count;
    uint32_t m_log_filecount;
    Level m_log_level;

    // eventlog para
    uint32_t m_eventlog_count;
    uint32_t m_eventlog_filecount;
    Level m_eventlog_level;

    // calllog para
    uint32_t m_calllog_count;
    uint32_t m_calllog_filecount;
    Level m_calllog_level;
    uint32_t m_calllog_timeout;

    // acd manager
    uint32_t m_sendevent_threadcount;
    uint32_t m_agent_timeout;
    string m_default_anishow;
    string m_default_destshow;
    string m_password;
    uint32_t m_request_timespan;
    uint32_t m_queue_timespan;
    uint32_t m_skill_count;

    // acd heartbeat
    string m_other_acdhost;
    uint32_t m_other_acdport;
    uint32_t m_this_acdport;
    uint32_t m_acdheartbeat_timesmax;
    uint32_t m_acdheartbeat_timespan;

    // ims configuration para
    string m_main_server_ip;
    uint32_t m_main_server_port;
    string m_back_server_ip;
    uint32_t m_back_server_port;
    uint32_t m_imsheartbeat_timesmax;
    uint32_t m_imsheartbeat_timespan;
    uint32_t m_ims_proxy_num;

    // agent server
    uint32_t m_this_agentport;
    uint32_t m_thread_num;

    // agent info
    SafeSet<string> m_setSkills;
    SafeSet<string> m_setRestReason;
    SafeMap<string, string> m_mapAgent;

private:
    static void copy_unit(const string& unit, acd::StringListT& lst);
    void Clear();
    bool LoadConf();        // 读取配置文件
    bool LoadSkills();      // 读取技能
    bool LoadRestReason();      // 读取休息原因
    bool LoadAgent();       // 读取坐席信息
    bool ValidateSkill(const string& skill);

public:
    acd_config(void);
    ~acd_config(void);
    bool read_config();
    bool reset_config();
    acd::AcdResultT validate_agent(const string& agentId, const string& skill);
    acd::AcdResultT validate_agent(const string& agentId, const string& agentPwd, const string& skill);
    void GetSkill(acd::StringListT& skill);
    void GetRestReason(acd::StringListT& restReason);
};
