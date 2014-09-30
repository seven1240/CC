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


#include "acd_log_timer.h"

void acd_log_timer::Method() {
    assert(p_m_logger != NULL);

    while (this->mIsLoop) {
        bgcc::TimeUtil::safe_sleep_s(m_log_timeout);
        p_m_logger->SetTimeout();
    }
}

acd_log_timer::acd_log_timer() : m_log_timeout(60), p_m_logger(NULL) {
}

acd_log_timer::~acd_log_timer() {
}

void acd_log_timer::Initialize(uint32_t log_timeout, Logger* plogger) {
    assert(plogger != NULL);
    m_log_timeout = log_timeout;
    p_m_logger = plogger;
    Start();
}

void acd_log_timer::Uninitialize() {
    Stop();
}
