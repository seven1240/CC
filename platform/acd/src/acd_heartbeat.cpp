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


#include "acd_heartbeat.h"
#include "acd_tool.h"

acd_heartbeat::acd_heartbeat() : m_is_master(false), m_is_aggressive(false) {
}

acd_heartbeat::~acd_heartbeat() {
}

bool acd_heartbeat::Heartbeat(bool currentType, bool& newType,
                              const std::map<std::string, std::string>& ctx) {
    if (m_is_master && currentType) {   // both master
        if (m_is_aggressive) {
            m_is_master = true;
            newType = false;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "both master, aggressive:%d", m_is_master);
        } else {
            m_is_master = false;
            newType = true;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "both master, not aggressive:%d", m_is_master);
        }

        return false;
    } else if (m_is_master && !currentType) {
        newType = currentType;
        //acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "normal:%d", m_is_master);
        return true;
    } else if (!m_is_master && currentType) {
        newType = currentType;
        //acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "normal:%d", m_is_master);
        return true;
    } else {                // both slaver
        if (m_is_aggressive) {
            m_is_master = true;
            newType = false;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "both slaver, aggressive:%d", m_is_master);
        } else {
            m_is_master = false;
            newType = true;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                        "both slaver, not aggressive:%d", m_is_master);
        }

        return false;
    }
}

bool acd_heartbeat::GetIsMaster() {
    return m_is_master;
}

void acd_heartbeat::SetIsMaster(bool is_master) {
    m_is_master = is_master;
}

void acd_heartbeat::SetAggressive(bool is_aggressive) {
    m_is_aggressive = is_aggressive;
}
