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

#include "acd_heartbeat.h"
#include "thread.h"

class beat_listen : public Thread {
private:
    bgcc::Server* p_m_server;
protected:
    virtual void Method();
public:
    beat_listen(bgcc::Server* pserver);
    ~beat_listen();
};

class acd_backup : public Thread {
private:
    bgcc::SharedPointer<acd_heartbeat> m_acdheartbeat_ptr;
    bgcc::ServiceManager m_servicemanager;
    bgcc::ThreadPool m_threadpool;
    bgcc::Server m_server;
    beat_listen* p_m_listen;

    uint32_t m_times_max;
    uint32_t m_timespan;
    bgcc::ServerInfo m_serverinfo;

protected:
    virtual void Method();
public:
    acd_backup(const char* server_ip, uint32_t server_port, uint32_t local_port, uint32_t timesmax,
               uint32_t timespan);
    ~acd_backup();
    bool GetIsMaster();
};
