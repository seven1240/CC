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

#include "acd_config.h"
#include "logger.h"
#include "acd_log_timer.h"
#include "acd_receive_event_manager.h"
#include "acd_send_event_manager.h"
#include "acd_agent_manager.h"
#include "acd_skill_manager.h"
#include "acd_backup.h"
#include "acd_ims.h"
#include "acd_server.h"

class IDCreater {
private:
    int64_t m_ID;
    bgcc::Mutex mLocker;
public:
    IDCreater();
    ~IDCreater();
    int64_t GetID();
};

class acd_tool {
private:
    static acd_config m_config;
    static IDCreater m_handle;
    static IDCreater m_eventId;
    static IDCreater m_skillId;
public:
    static Logger m_logger;
private:
    static Logger m_eventlogger;
public:
    static Logger m_calllogger;
    static acd_log_timer m_calllog_timer;
    static acd_receive_event_manager m_receive_event_manager;
    static acd_send_event_manager m_send_event_manager;
    static acd_agent_manager m_agent_manager;
    static acd_skill_manager m_skill_manager;
    static acd_backup* p_m_acd_backup;
    static acd_ims* p_m_acd_ims;
    static acd_main_server m_main_server;

private:
    static void init_log();
    static void un_init_log();
    static void init_manager();
    static void un_init_manager();
    static void init_connect();
    static void un_init_connect();

public:
    static void init();
    static void un_init();

    static acd::AcdResultT validate_agent(const string& agentId, const string& skill);
    static acd::AcdResultT validate_agent(const string& agentId, const string& agentPwd,
                                          const string& skill);
    static void GetSkill(acd::StringListT& skill);
    static void GetRestReason(acd::StringListT& restReason);

    static int64_t CreatHandle();
    static int64_t CreatEventId();
    static int64_t CreatSkillId();

    static uint32_t LocalPort();
    static bool ResetConfig();

    static void write_ims_event_log(const ims::CallEventT& event);
    static void write_ims_event_log(const ims::MediaEventT& event);
    static void write_ims_event_log(const ims::RouteEventT& event);
    static void write_ims_event_log(const ims::OtherEventT& event);
    static void write_acd_event_log(const SendEventT& event);

    static acd::CallEventTypeT TranslateCallEvent(const ims::CallEventTypeT& type);
    static acd::PartyAttributeT TranslatePartyAtt(const ims::PartyAttributeT& type);
    static acd::CallEventReasonT TranslateCallReason(const ims::CallEventReasonT& type);
    static acd::MediaEventTypeT TranslateMediaEvent(const ims::MediaEventTypeT& type);
    static acd::MediaStateT TranslateMediaState(const ims::MediaStateT& type);
    static acd::MediaEventReasonT TranslateMediaReason(const ims::MediaEventReasonT& type);
};
