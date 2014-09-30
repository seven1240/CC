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


#include "acd_backup.h"
#include "acd_tool.h"

const uint32_t HEARTBEAT_THREADPOOL_SIZE = 1;

void beat_listen::Method() {
    assert(p_m_server != NULL);

    if (0 != p_m_server->serve()) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "heartbeat listen exit");
        cout << "heartbeat listen fail, acd exit!" << endl;
        exit(0);
    }
}

beat_listen::beat_listen(bgcc::Server* pserver) : p_m_server(pserver) {
}

beat_listen::~beat_listen() {
}

void acd_backup::Method() {
    bool is_first = true;
    uint32_t times = 0;
    acd::acdheartbeatProxy proxy(m_serverinfo, 1, NULL, 0);

    while (this->mIsLoop) {
        bool newType = false;
        proxy.Heartbeat(m_acdheartbeat_ptr->GetIsMaster(), newType);

        if (proxy.get_errno() == 0) {
            if (is_first) {
                m_acdheartbeat_ptr->SetAggressive(false);
                acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                            "first heartbeat success, not aggressive");
            }

            times = 0;
            m_acdheartbeat_ptr->SetIsMaster(newType);
            //acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "Heartbeat success:%d", m_acdheartbeat_ptr->GetIsMaster());
        } else {
            if (is_first) {
                m_acdheartbeat_ptr->SetAggressive(true);
                acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                            "first heartbeat error, aggressive");
            }

            times++;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "Heartbeat error:%d", m_acdheartbeat_ptr->GetIsMaster());
        }

        if (times == m_times_max) {
            times = 0;
            m_acdheartbeat_ptr->SetIsMaster(true);
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "set master:%d",
                                        m_acdheartbeat_ptr->GetIsMaster());
        }

        is_first = false;
        bgcc::TimeUtil::safe_sleep_s(m_timespan);
    }
}

acd_backup::acd_backup(const char* server_ip, uint32_t server_port, uint32_t local_port,
                       uint32_t timesmax, uint32_t timespan) :
    m_acdheartbeat_ptr(new acd_heartbeat()), m_server(&m_servicemanager, &m_threadpool, local_port),
    p_m_listen(NULL),
    m_times_max(timesmax), m_timespan(timespan), m_serverinfo(server_ip, (uint16_t)server_port) {
    m_servicemanager.add_service(bgcc::SharedPointer<bgcc::IProcessor>(new acd::acdheartbeatProcessor(
                                     m_acdheartbeat_ptr)));
    m_threadpool.init(HEARTBEAT_THREADPOOL_SIZE);
    p_m_listen = new beat_listen(&m_server);
    p_m_listen->Start();
}

acd_backup::~acd_backup() {
    if (p_m_listen) {
        p_m_listen->Stop();
        delete p_m_listen;
        p_m_listen = NULL;
    }
}

bool acd_backup::GetIsMaster() {
    return m_acdheartbeat_ptr->GetIsMaster();
}
