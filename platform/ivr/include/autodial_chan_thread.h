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

#ifndef _AUTODIAL_CHAN_THREAD_H_
#define _AUTODIAL_CHAN_THREAD_H_

#include "common.h"
#include "worker_thread.h"

// autodial thread
class AutoDialChanThread  : public WorkerThread {
public:
    AutoDialChanThread(base_script_t* param);
    virtual~ AutoDialChanThread();
    virtual uint32_t execute(void* taskparam);
protected:
    bool check_capability();
    bool init_ivrvars(const std::string& dialdata, inbound_script_t& script) const;
    bool before_start_flow(const std::string& dnis, inbound_script_t& script);
    bool clean_chan_context(inbound_script_t& script);
};

#endif
