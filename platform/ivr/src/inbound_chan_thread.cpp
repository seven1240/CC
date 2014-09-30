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

#include "lock.h"
#include "tools.h"
#include "inbound_chan_thread.h"
#include "cpu_manager.h"
#include "calldata_manager.h"
#include "node_base.h"
#include "ivr_timer.h"
#include "ivr_instance_manager.h"
#include "flow_manager.h"
#include "fs_mgr.h"
#include "fs_opr.h"
#include "lock.h"
#include <ims/ims_mgr.h>

#if IVR_ENABLE_DEBUGER
#include "ivrdebuger.h"
#endif

extern inbound_conf_t  g_inbound_conf;
//extern map<string, flow_t*> g_flow_name_info_map;
extern FlowManager g_flowmanager;

InboundChanThread::~InboundChanThread(void) {
}

bool InboundChanThread::check_capability() {
    bool result = false;
    ostringstream ostm;
    {
        rw_lock_t lock(g_inbound_chan_rwlock, true);

        if (lock.locked()) {
            if (g_inbound_chan_num < g_inbound_conf.max_inbound_chan_num) {
                ++g_inbound_chan_num;
                result = true;
            } else {
                ostm << "[IB]achieve max capability,reject service(" << g_inbound_chan_num << ")";
            }
        } else {
            ostm << "lock inbound rwlock failed";
        }
    }

    if (!result) {
        IVR_WARN("%s", ostm.str().c_str());
    }

    return result;
}

void InboundChanThread::heartbeat(esl_handle_t& handle) {
    uint32_t inbound_chan_num_cp = 0;
    uint32_t cpu = CpuManager::get_instance()->get_cpu_occupy();
    std::string err;
    char resp[20] = {0};
    bzero(resp, 20);

    {
        rw_lock_t lock(g_inbound_chan_rwlock);

        if (lock.locked()) {
            inbound_chan_num_cp = g_inbound_chan_num;
        } else {
            err = "lock inbound num failed";
        }
    }

    if (err.length()) {
        IVR_WARN("%s", err.c_str());
    }

    snprintf(resp, 20, "cpu=%02u,chan=%05u", cpu, inbound_chan_num_cp);
    esl_send(&handle, resp);
    IVR_TRACE("ivr-loadbalance-resp = %s", resp);
}

uint32_t InboundChanThread::execute(void* taskparam) {
    string callid, ani, dnis;
    NodeBase* node = NULL;
    inbound_script_t script;
    std::string err;
    channel_info_t cinfo;

    // clear flow ptr
    script.flow = NULL;

    uint32_t ret = 0;
    std::string curr;
    dnis = ((inbound_script_t*)_param)->dnis;
    ostringstream ost;
    fs_opr_t* opr = NULL;
    IVR_DEBUG("inbound_execute event queue pointer %lu, queue size: %lu",
              (uint64_t)(((session_dynamic_resource_t*)taskparam)->event_queue),
              ((session_dynamic_resource_t*)taskparam)->event_queue->size());

    if (!check_capability()) {
        ret = 1;
        goto END;
    }

    //inbound_script 对象 作为流程执行run函数的参数param
    {
        rw_lock_t lock(g_inbound_conf_rwlock, false);

        if (!lock.locked()) {
            IVR_WARN("failed lock!");
            goto CHAN_END;
        }

        if (g_inbound_conf.dnis_script_map.find(dnis) == g_inbound_conf.dnis_script_map.end()) {
            if (!g_inbound_conf.has_default) {
                IVR_WARN("没有找到可以匹配的流程(dnis=%s),且默认流程未配置或未正确加载", dnis.c_str());
                ret = 1;
                goto CHAN_END;
            } else {
                IVR_TRACE("没有找到可以匹配的流程(dnis=%s),启动默认流程", dnis.c_str());
                script = g_inbound_conf.default_script;

                if (SUCCESS != FlowManager::attach_flow(g_inbound_conf.default_script.flow, &script.flow)) {
                    ret = 1;
                    goto CHAN_END;
                }
            }
        } else {
            IVR_TRACE("找到匹配的流程(dnis=%s)", dnis.c_str());
            script = g_inbound_conf.dnis_script_map[dnis];

            if (SUCCESS != FlowManager::attach_flow(g_inbound_conf.dnis_script_map[dnis].flow, &script.flow)) {
                ret = 1;
                goto CHAN_END;
            }
        }
    }
    // init ims information
    script.imsno = (uint32_t) - 1;
    script.imssid = 0;
    script.requestId = 0;
    script.type = ((inbound_script_t*)_param)->type;
    script.fid = ((inbound_script_t*)_param)->fid;
    script.ani = ((inbound_script_t*)_param)->ani;
    script.dnis = ((inbound_script_t*)_param)->dnis;
    script.callid = ((inbound_script_t*)_param)->callid;
    script.callsource = ((inbound_script_t*)_param)->callsource;
    script.channel_name = ((inbound_script_t*)_param)->channel_name;
    script.channel_id = ((inbound_script_t*)_param)->channel_id;
    ivr_tools_t::build_vars(script.flow->name_var_map, script.name_var_map);

    // don't add channel information here
    //  if answer the call, will add information

    //创建实例
    ivr_session_id_t ivr_s_id;
    session_dynamic_resource_t* resource = (session_dynamic_resource_t*)taskparam;
    IvrInstanceManager* mgr = IvrInstanceManager::get_instance();

    if (IVR_SUCCESS != mgr->create_ivr_instance(script.type, script.fid, &ivr_s_id, *resource,
            script.callid.c_str())) {
        IVR_WARN("创建实例失败(dnis=%s)", script.dnis.c_str());
        goto CHAN_END;
    }

    //添加uuid
    if (IVR_SUCCESS != mgr->add_uuid(ivr_s_id, script.callid)) {
        IVR_WARN("创建实例失败(dnis=%s)", script.dnis.c_str());
        mgr->destroy_ivr_instance(ivr_s_id);
        goto CHAN_END;
    }

    //注册uuid
    if (fs_mgr_t::instance()->fetch_opr(script.fid, &opr) == IVR_SUCCESS) {
        if (NULL == opr || IVR_SUCCESS != opr->register_session(script.callid.c_str(), ivr_s_id)) {
            IVR_WARN("添加uuid失败(dnis=%s)", script.dnis.c_str());
            mgr->destroy_ivr_instance(ivr_s_id);
            fs_mgr_t::instance()->free_opr(&opr);
            goto CHAN_END;
        }

        fs_mgr_t::instance()->free_opr(&opr);
    } else {
        IVR_WARN("注册实例失败(dnis=%s)", script.dnis.c_str());
        mgr->destroy_ivr_instance(ivr_s_id);
        goto CHAN_END;
    }

    // update channel info
    cinfo.callsource = _param->callsource;
    cinfo.channel_id = _param->channel_id;
    cinfo.channel_name = _param->channel_name;
    IvrInstanceManager::get_instance()->add_channel_info(script.callid, cinfo);

    //设置script内容
    script.session_id = ivr_s_id;
    script.timer = resource->timer;
    curr = ivr_tools_t::get_current_second();
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::ANI]].pvalue = script.ani;
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::DNIS]].pvalue = script.dnis;
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::CALLID]].pvalue = script.callid;
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::RECORD_FILE]].pvalue = "";
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::HANGUP_CAUSE]].pvalue = "user_hangup";

    *(string*)script.name_var_map[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue = curr;
    *(string*)script.name_var_map[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue = curr;

    //运行流程
    node = script.flow->id_node_map[script.flow->begin_id];
    ost << "\n================";
    ost << "ANI:\t" << script.ani << endl;
    ost << "DNIS:\t" << script.dnis << endl;
    ost << "CALLID:\t" << script.callid << endl;
    ost << "FID:\t" << script.fid << endl;
    ost << "SESSIONID:\t" << script.session_id << endl;
    ost << "================";
    IVR_DEBUG("%s", ost.str().c_str());

#if IVR_ENABLE_DEBUGER
    IvrDebuger::get_instance()->report(this, "startup", script, node);
#endif

    do {
#if IVR_ENABLE_DEBUGER

        if (IvrDebuger::get_instance()->wait(this) == 1) {
            break;
        }

#endif
        node = node->run(&script);
#if IVR_ENABLE_DEBUGER
        IvrDebuger::get_instance()->report(this, "runnode", script, node);
#endif
    } while (node && !g_stopped);


    if (!node) {
        CallDataManager* calldata_manager = CallDataManager::get_instance();
        calldata_manager->push_calldata(script.bill_info().c_str());
    }

    ivr_tools_t::destroy_vars(script.name_var_map);
    mgr->destroy_ivr_instance(ivr_s_id);
    ims_mgr_t::get_instance()->unbind_session_id(ivr_s_id);

    if (resource->timer != NULL) {
        // clear all timer
        resource->timer->clear_all_timer();
    }

CHAN_END:
    FlowManager::detach_flow(&script.flow);
    {
        rw_lock_t lock(g_inbound_chan_rwlock, true);

        if (lock.locked()) {
            --g_inbound_chan_num;
        } else {
            err = "lock inbound rwlock failed";
        }
    }

    if (err.length()) {
        IVR_WARN("%s", err.c_str());
    }

END:
    return ret;
}
