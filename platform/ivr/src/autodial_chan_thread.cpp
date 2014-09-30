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
#include "autodial_chan_thread.h"
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
#include <json/json.h>
#include "common.h"

#if IVR_ENABLE_DEBUGER
#include "ivrdebuger.h"
#endif

extern inbound_conf_t  g_inbound_conf;
//extern map<string, flow_t*> g_flow_name_info_map;
extern FlowManager g_flowmanager;

AutoDialChanThread::AutoDialChanThread(base_script_t* param)
    : WorkerThread(param) {
}

AutoDialChanThread::~AutoDialChanThread() {
}

bool AutoDialChanThread::check_capability() {
    bool result = false;
    rw_lock_t lock(g_autodial_chan_rwlock, true);

    if (lock.locked()) {
        if (g_autodial_chan_num < g_inbound_conf.max_autodial_chan_num) {
            ++ g_autodial_chan_num;
            result = true;
        } else {
            IVR_WARN("[AD]achieve max capability,reject service(%u)", g_autodial_chan_num);
        }
    } else {
        IVR_WARN("lock inbound rwlock failed");
    }

    return result;
}

bool AutoDialChanThread::init_ivrvars(const std::string& dialdata, inbound_script_t& script) const {
    typedef std::map<std::string, variable_t> str2var_map;
    str2var_map& kvpair = script.name_var_map;
    ivr_tools_t::build_vars(script.flow->name_var_map, kvpair);
    std::string curr = ivr_tools_t::get_current_second();
    *(string*)kvpair[SYS_VAR[sys_var_t::HANGUP_CAUSE]].pvalue = "user_hangup";
    *(string*)kvpair[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue = curr;
    *(string*)kvpair[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue = curr;

    if (kvpair.find("_AUTODIALDATA") == kvpair.end()) {
        variable_t variable;
        variable.name = "_AUTODIALDATA";
        variable.type = STRING;
        variable.pvalue = new std::string(dialdata);
        kvpair["_AUTODIALDATA"] = variable;
    } else {
        IVR_DEBUG("flow existing _AUTODIALDATA");
        variable_t& variable = kvpair["_AUTODIALDATA"];

        if (variable.type == STRING) {
            *(std::string*)variable.pvalue = dialdata;
        } else {
            IVR_WARN("_AUTODIALDATA is not a string variable");
            return false;
        }
    }

    IVR_TRACE("parse json string(%s)", dialdata.c_str());
    json_object* obj = json_tokener_parse(dialdata.c_str());

    if (NULL == obj || is_error(obj)) {
        IVR_WARN("check calldata failed, parse json error!");
        return false;
    }

    if (json_object_get_type(obj) != json_type_object) {
        IVR_WARN("input calldata is not json-object, its type is %d", json_object_get_type(obj));
        return false;
    }

    json_object_object_foreach(obj, key, val) {
        if (key == NULL) {
            continue;
        }

        str2var_map::iterator iter = kvpair.find(key);

        if (iter == kvpair.end()) {
            IVR_WARN("not found variable(%s)", key);
            json_object_put(obj);
            return false;
        } else if (iter->second.type != STRING) {
            IVR_WARN("variable(%s) type is not string", key);
            json_object_put(obj);
            return false;
        }

        const char* tmp = json_object_get_string(val);
        IVR_DEBUG("json object(%s)=%s", key, tmp);

        if (tmp != NULL) {
            if (iter->second.pvalue != NULL) {
                *((std::string*)iter->second.pvalue) = tmp;
            } else {
                iter->second.pvalue = new std::string(tmp);
            }
        } else {
            IVR_WARN("get string of key(%s) failed", key);
        }
    }
    json_object_put(obj);
    return true;
}

bool AutoDialChanThread::before_start_flow(const std::string& dnis, inbound_script_t& script) {
    // init ims information
    script.imsno = (uint32_t) - 1;
    script.imssid = 0;
    script.requestId = 0;
    script.session_id = 0;
    script.type = base_script_t::INBOUND;
    script.flow = NULL; // clean flow
    {
        // find dest flow
        rw_lock_t lock(g_inbound_conf_rwlock, false);

        if (!lock.locked()) {
            IVR_WARN("failed lock!");
            return false;
        }

        if (g_inbound_conf.dnis_script_map.find(dnis) == g_inbound_conf.dnis_script_map.end()) {
            // don't use default flow
            IVR_TRACE("not found matched auto dial flow(%s)", dnis.c_str());
            return false;
        } else {
            IVR_TRACE("find matched autodial flow(%s), ptr(%p)", dnis.c_str(),
                      g_inbound_conf.dnis_script_map[dnis].flow);
            script = g_inbound_conf.dnis_script_map[dnis];

            if (SUCCESS != FlowManager::attach_flow(g_inbound_conf.dnis_script_map[dnis].flow, &script.flow)) {
                return false;
            }
        }
    }
    return true;
}

uint32_t AutoDialChanThread::execute(void* taskparam) {
    IVR_DEBUG("autorun_execute event queue pointer %lu, queue size: %lu",
              (uint64_t)((session_dynamic_resource_t*)taskparam)->event_queue,
              ((session_dynamic_resource_t*)taskparam)->event_queue->size());

    // check can run
    if (!check_capability()) {
        return (uint32_t) - 1;
    }

    inbound_script_t script;
    script.flow = NULL;

    // get flow
    session_dynamic_resource_t* resource = (session_dynamic_resource_t*)taskparam;

    if (!before_start_flow(((inbound_script_t*)_param)->dnis, script)) {
        IVR_DEBUG("get flow failed!");
        clean_chan_context(script);
        return (uint32_t) - 1;
    }

    IVR_DEBUG("get flow (0x%p)", script.flow);

    // find a freeswitch to use
    if (IVR_SUCCESS != fs_mgr_t::instance()->decision_fs(script.fid)) {
        clean_chan_context(script);
        return (uint32_t) - 1;
    }

    IVR_TRACE("decision freeswitch result: %d", script.fid);

    // initial script vars
    if (!init_ivrvars(((inbound_script_t*)_param)->dialdata, script)) {
        IVR_WARN("build vars failed");
        clean_chan_context(script);
        return (uint32_t) - 1;
    }

    // set timer
    script.timer = resource->timer;
    // create an ivr session id
    IvrInstanceManager* mgr = IvrInstanceManager::get_instance();

    if (IVR_SUCCESS != mgr->create_ivr_instance(script.type, script.fid, &script.session_id, *resource,
            "1")) {
        clean_chan_context(script);
        IVR_WARN("create_ivr_instance failed!");
        return 1;
    }

    // run flow
    NodeBase* node = script.flow->id_node_map[script.flow->begin_id];
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
    } while (node != NULL && !g_stopped);

    IVR_TRACE("generate calldata");
    CallDataManager::get_instance()->push_calldata(script.bill_info().c_str());

    if (resource->timer != NULL) {
        // clear all timer
        resource->timer->clear_all_timer();
    }

    clean_chan_context(script);

    IVR_TRACE("finish run flow(%s)", script.dnis.c_str());
#if IVR_ENABLE_DEBUGER
    IvrDebuger::get_instance()->report(this, "finish", script, node);
#endif

    return 0;
}

bool AutoDialChanThread::clean_chan_context(inbound_script_t& script) {
    IvrInstanceManager* mgr = IvrInstanceManager::get_instance();
    ivr_tools_t::destroy_vars(script.name_var_map);

    if (script.session_id != 0) {
        mgr->destroy_ivr_instance(script.session_id);

        ims_mgr_t::get_instance()->unbind_session_id(script.session_id);
    }

    // release flow
    if (script.flow != NULL) {
        IVR_DEBUG("detach flow");
        FlowManager::detach_flow(&script.flow);
        IVR_DEBUG("detach flow");
    }

    {
        // dec count
        rw_lock_t lock(g_autodial_chan_rwlock, true);

        if (lock.locked()) {
            -- g_autodial_chan_num;
        } else {
            IVR_WARN("lock autodial rwlock failed");
        }
    }

    return 0;
}
