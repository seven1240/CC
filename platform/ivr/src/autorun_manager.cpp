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

#include "autorun_manager.h"
#include "autorun_chan_thread.h"
#include "thread_pool.h"

#include "tools.h"
#include "flow_manager.h"

AutoRunManager::AutoRunManager() {
}

AutoRunManager::~AutoRunManager() {
}

AutoRunManager* AutoRunManager::get_instance() {
    static AutoRunManager mgr;
    return &mgr;
}

void AutoRunManager::begin(uint32_t idx) {
    uint32_t chnl_num = g_autorun_conf.autorun_script_vec[idx].autorun_chan_num;

    for (uint32_t ii = 0; ii < chnl_num; ii++) {
        autorun_script_t* script = new(std::nothrow) autorun_script_t(); //worker线程负责删除

        if (script == NULL) {
            IVR_TRACE("create new autorun script[%d] failed", ii);
            continue;
        }

        *script = g_autorun_conf.autorun_script_vec[idx];

        if (SUCCESS != FlowManager::attach_flow(g_autorun_conf.autorun_script_vec[idx].flow,
                                                &(script->flow))) {
            IVR_TRACE("attach flow autorun script[%d] failed", ii);
        }

        AutoRunChanThread* autorun_thread = new(std::nothrow)AutoRunChanThread(script); //pool负责删除
        ThreadPool* threadpool = ThreadPool::get_instance();
        threadpool->assign_work(autorun_thread);
        ivr_tools_t::safe_sleepms(50);
    }
}
