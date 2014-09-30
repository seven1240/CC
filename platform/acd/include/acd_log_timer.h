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

#include "logger.h"
#include "thread.h"

class acd_log_timer : public Thread {
private:
    uint32_t m_log_timeout;
    Logger* p_m_logger;

protected:
    virtual void Method();

public:
    acd_log_timer(void);
    ~acd_log_timer(void);
    void Initialize(uint32_t log_timeout, Logger* plogger);
    void Uninitialize();

};
