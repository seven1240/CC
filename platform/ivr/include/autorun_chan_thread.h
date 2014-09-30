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

#ifndef _AUTORUN_CHAN_THREAD_H_
#define _AUTORUN_CHAN_THREAD_H_

#include "common.h"
#include "worker_thread.h"

//自启动流程处理线程
class AutoRunChanThread  : public WorkerThread {
public:
    AutoRunChanThread(base_script_t* param);
    virtual~ AutoRunChanThread();
    virtual uint32_t execute(void* taskparam);
private:
    bool occupy_channel();
    bool free_channel();
    bool init_handle(std::string& err);

    esl_handle_t _handle;
    autorun_script_t* _script;
};

#endif
