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
#include "safe_queue.h"
#include "thread.h"

class acd_send_event : public Thread {
private:
    uint32_t m_thread_flag;
    SafeQueue<SendEventT*> m_event_queue;
protected:
    virtual void Method();
public:
    acd_send_event(uint32_t flag);
    ~acd_send_event(void);
    void in_queue(SendEventT* p_event);
};

class acd_send_event_manager {
private:
    uint32_t m_max_thread;
    vector<acd_send_event*> m_event_arrey;
public:
    acd_send_event_manager(void);
    ~acd_send_event_manager(void);
    void Initialize(uint32_t max_thread);
    void Uninitialize();
    void send_event(SendEventT* p_event, int64_t handle);
};
