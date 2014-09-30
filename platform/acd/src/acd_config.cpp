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


#include "acd_config.h"
#include "config_reader.h"
#include <mysql.h>
#include "acd_tool.h"

void acd_config::copy_unit(const string& unit, acd::StringListT& lst) {
    lst.push_back(unit);
}

void acd_config::Clear() {
    m_setSkills.Clear();
    m_setRestReason.Clear();
    m_mapAgent.Clear();
    cout << "reset config, clear success!" << endl;
}

bool acd_config::LoadConf() {
    Configure conf;

    if (!conf.Load(CONFIG_DIR, CONFIG_FILE)) {
        return false;
    }

    try {
        // mysql configuration para
        m_dbhost = conf["mysql"]["dbhost"].to_cstr();
        m_dbport = conf["mysql"]["dbport"].to_int32();
        m_dbusername = conf["mysql"]["dbusername"].to_cstr();
        m_dbpasswd = conf["mysql"]["dbpasswd"].to_cstr();
        m_dbname = conf["mysql"]["dbname"].to_cstr();

        // log para
        m_log_count = conf["log"]["log_count"].to_int32();
        m_log_filecount = conf["log"]["log_filecount"].to_int32();
        m_log_level = static_cast<Level>(conf["log"]["log_level"].to_int32());

        // eventlog para
        m_eventlog_count = conf["eventlog"]["eventlog_count"].to_int32();
        m_eventlog_filecount = conf["eventlog"]["eventlog_filecount"].to_int32();
        m_eventlog_level = static_cast<Level>(conf["eventlog"]["eventlog_level"].to_int32());

        // calllog para
        m_calllog_count = conf["calllog"]["calllog_count"].to_int32();
        m_calllog_filecount = conf["calllog"]["calllog_filecount"].to_int32();
        m_calllog_level = static_cast<Level>(conf["calllog"]["calllog_level"].to_int32());
        m_calllog_timeout = conf["calllog"]["calllog_timeout"].to_int32();

        // acd manager
        m_sendevent_threadcount = conf["acd"]["sendevent_threadcount"].to_int32();
        m_agent_timeout = conf["acd"]["agent_timeout"].to_int32();
        m_default_anishow = conf["acd"]["default_anishow"].to_cstr();
        m_default_destshow = conf["acd"]["default_destshow"].to_cstr();
        m_password = conf["acd"]["password"].to_cstr();
        m_request_timespan = conf["acd"]["request_timespan"].to_int32();
        m_queue_timespan = conf["acd"]["queue_timespan"].to_int32();
        m_skill_count = conf["acd"]["skill_count"].to_int32();

        // acd heartbeat
        m_other_acdhost = conf["acd_backup"]["other_host"].to_cstr();
        m_other_acdport = conf["acd_backup"]["other_port"].to_int32();
        m_this_acdport = conf["acd_backup"]["this_port"].to_int32();
        m_acdheartbeat_timesmax = conf["acd_backup"]["acdheartbeat_timesmax"].to_int32();
        m_acdheartbeat_timespan = conf["acd_backup"]["acdheartbeat_timespan"].to_int32();

        // ims configuration para
        m_main_server_ip = conf["ims"]["main_server_ip"].to_cstr();
        m_main_server_port = conf["ims"]["main_server_port"].to_int32();
        m_back_server_ip = conf["ims"]["back_server_ip"].to_cstr();
        m_back_server_port = conf["ims"]["back_server_port"].to_int32();
        m_imsheartbeat_timesmax = conf["ims"]["imsheartbeat_timesmax"].to_int32();
        m_imsheartbeat_timespan = conf["ims"]["imsheartbeat_timespan"].to_int32();
        m_ims_proxy_num = conf["ims"]["ims_proxy_num"].to_int32();

        // agent server
        m_this_agentport = conf["agent"]["port"].to_int32();
        m_thread_num = conf["agent"]["thread_num"].to_int32();
    } catch (runtime_error e) {
        cout << "read config, load config error: " << e.what() << endl;
        return false;
    } catch (...) {
        cout << "read config, load config error!" << endl;
        return false;
    }

    cout << "read config, load config success!" << endl;
    return true;
}

bool acd_config::LoadSkills() {
    MYSQL* conn;
    MYSQL_RES* result;
    MYSQL_ROW row;
    bool ret = false;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, m_dbhost.c_str(), m_dbusername.c_str(), m_dbpasswd.c_str(),
                           m_dbname.c_str(), m_dbport, NULL, 0)) {
        mysql_query(conn, "set names gbk");

        if (!mysql_query(conn, "SELECT * FROM SkillIdTbl")) {
            result = mysql_store_result(conn);

            while (row = mysql_fetch_row(result)) {
                m_setSkills.Insert(row[1]);
            }

            mysql_free_result(result);
            cout << "read config, load skill success!" << endl;
            ret = true;
        } else {
            cout << "read config, load skills, query mysql error!" << endl;
            ret = false;
        }
    } else {
        cout << "read config, load skills, open mysql error!" << endl;
        ret = false;
    }

    mysql_close(conn);
    mysql_library_end();
    return ret;
}

bool acd_config::LoadRestReason() {
    MYSQL* conn;
    MYSQL_RES* result;
    MYSQL_ROW row;
    bool ret = false;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, m_dbhost.c_str(), m_dbusername.c_str(), m_dbpasswd.c_str(),
                           m_dbname.c_str(), m_dbport, NULL, 0)) {
        mysql_query(conn, "set names gbk");

        if (!mysql_query(conn, "SELECT * FROM RestReasonTbl")) {
            result = mysql_store_result(conn);

            while (row = mysql_fetch_row(result)) {
                m_setRestReason.Insert(row[1]);
            }

            mysql_free_result(result);
            cout << "read config, load restreason success!" << endl;
            ret = true;
        } else {
            cout << "read config, load restreasons, query mysql error!" << endl;
            ret = false;
        }
    } else {
        cout << "read config, load restreasons, open mysql error!" << endl;
        ret = false;
    }

    mysql_close(conn);
    mysql_library_end();
    return ret;
}

bool acd_config::LoadAgent() {
    MYSQL* conn;
    MYSQL_RES* result;
    MYSQL_ROW row;
    bool ret = false;
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, m_dbhost.c_str(), m_dbusername.c_str(), m_dbpasswd.c_str(),
                           m_dbname.c_str(), m_dbport, NULL, 0)) {
        mysql_query(conn, "set names gbk");

        if (!mysql_query(conn, "SELECT * FROM AgentTbl")) {
            result = mysql_store_result(conn);

            while ((row = mysql_fetch_row(result))) {
                m_mapAgent.Insert(row[1], NULL == row[2] ? "" : row[2]);
            }

            mysql_free_result(result);
            cout << "read config, load agent success!" << endl;
            ret = true;
        } else {
            cout << "read config, load agents, query mysql error!" << endl;
            ret = false;
        }
    } else {
        cout << "read config, load agents, open mysql error!" << endl;
        ret = false;
    }

    mysql_close(conn);
    mysql_library_end();
    return ret;
}

bool acd_config::ValidateSkill(const string& skill) {
    vector<string> ins;
    bgcc::StringUtil::split_string(skill, ",", ins, true);

    for (vector<string>::iterator it = ins.begin(); it != ins.end(); it++) {
        if (!m_setSkills.Find(*it)) {
            return false;
        }
    }

    return true;
}

acd_config::acd_config(void) :
    m_dbhost("127.0.0.1"), m_dbport(3306), m_dbusername("acd"), m_dbpasswd("acd"), m_dbname("acddb"),
    m_log_count(50000), m_log_filecount(10), m_log_level(LOG_LEVEL_DEBUG),
    m_eventlog_count(50000), m_eventlog_filecount(10), m_eventlog_level(LOG_LEVEL_DEBUG),
    m_calllog_count(50000), m_calllog_filecount(10), m_calllog_level(LOG_LEVEL_DEBUG),
    m_calllog_timeout(60),
    m_sendevent_threadcount(10), m_agent_timeout(60), m_default_anishow("1111"),
    m_default_destshow("2222"), m_password("123456"), m_request_timespan(30), m_queue_timespan(1),
    m_skill_count(10),
    m_other_acdhost("127.0.0.1"), m_other_acdport(9999), m_this_acdport(9988),
    m_acdheartbeat_timesmax(3), m_acdheartbeat_timespan(3),
    m_main_server_ip("127.0.0.1"), m_main_server_port(9527), m_back_server_ip("127.0.0.1"),
    m_back_server_port(9527), m_imsheartbeat_timesmax(3), m_imsheartbeat_timespan(3),
    m_ims_proxy_num(10),
    m_this_agentport(10000), m_thread_num(10) {
}

acd_config::~acd_config(void) {
}

bool acd_config::read_config() {
    SingleLocker s(&m_Locker);
    return LoadConf() && LoadSkills() && LoadRestReason() && LoadAgent();
}

bool acd_config::reset_config() {
    Clear();
    return read_config();
}

acd::AcdResultT acd_config::validate_agent(const string& agentId, const string& skill) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;

    if (!m_mapAgent.Find(agentId)) {
        ret = acd::AcdResultT::ArAgentIdNotExist;
    } else if (!ValidateSkill(skill)) {
        ret = acd::AcdResultT::ArAgentSkillError;
    }

    return ret;
}

acd::AcdResultT acd_config::validate_agent(const string& agentId, const string& agentPwd,
        const string& skill) {
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
    string password;

    if (!m_mapAgent.Find(agentId, password)) {
        ret = acd::AcdResultT::ArAgentIdNotExist;
    } else if (password != agentPwd) {
        ret = acd::AcdResultT::ArAgentPasswordError;
    } else if (!ValidateSkill(skill)) {
        ret = acd::AcdResultT::ArAgentSkillError;
    }

    return ret;
}

void acd_config::GetSkill(acd::StringListT& skill) {
    m_setSkills.DoSomething(acd_config::copy_unit, skill);
}

void acd_config::GetRestReason(acd::StringListT& restReason) {
    m_setRestReason.DoSomething(acd_config::copy_unit, restReason);
}
