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

#include <acdheartbeat.h>

class acd_heartbeat : public acd::acdheartbeat {
private:
    bool m_is_master;
    bool m_is_aggressive;
public:
    acd_heartbeat();
    ~acd_heartbeat();
    virtual bool Heartbeat(bool currentType, bool& newType,
                           const std::map<std::string, std::string>& ctx);
    bool GetIsMaster();
    void SetIsMaster(bool is_master);
    void SetAggressive(bool is_aggressive);
};
