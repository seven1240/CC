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

#ifndef _INBOUND_CHAN_THREAD_H_
#define _INBOUND_CHAN_THREAD_H_

#include "worker_thread.h"

//呼入启动流程处理线程
class InboundChanThread  : public WorkerThread {
public:
    InboundChanThread(base_script_t* param) : WorkerThread(param) {
    };
    virtual ~InboundChanThread();
    virtual uint32_t execute(void* taskparam);
private:
    void heartbeat(esl_handle_t& handle);
    bool check_capability();
};

#endif
