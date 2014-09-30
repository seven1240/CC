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

#include "tools.h"
#include "lock.h"
#include "autorun_chan_thread.h"
#include "calldata_manager.h"
#include "node_base.h"
#include "ivr_instance_manager.h"
#include "fs_mgr.h"
#include "flow_manager.h"

extern autorun_conf_t  g_autorun_conf;
extern map<string, flow_t*> g_flow_name_info_map;

AutoRunChanThread::AutoRunChanThread(base_script_t* param) : WorkerThread(param), _script(NULL) {
    bzero(&_handle, sizeof(esl_handle_t));
    _script = (autorun_script_t*)_param;
    //    if(_script&&!_script->flow){
    //        _script->flow=g_flow_name_info_map[_script->flow_name];
    //    }
}

AutoRunChanThread::~AutoRunChanThread(void) {
}

bool AutoRunChanThread::init_handle(std::string& err) {
    /*    for(std::vector<freeswitch_info_t>::iterator it= _script->freeswitch_info_vec.begin();
                it!=_script->freeswitch_info_vec.end();++it){
            if(fs_operator_t::connect(_handle,it->ip.c_str(),it->port,NULL,it->pwd.c_str())){
                break;
            }
        }
    */    err = _handle.err;

    if (_handle.connected) {
        //外呼第一个节点也进行了过滤，可以去掉下面的过滤。。。
        //至于我为什么没有去掉，我也不知道。。。。
        if (fs_operator_t::events(_handle, ESL_EVENT_TYPE_PLAIN,
                                  "CHANNEL_EXECUTE_COMPLETE CHANNEL_ANSWER CHANNEL_HANGUP CHANNEL_BRIDGE CHANNEL_UUID")) {
            return true;
        } else {
            fs_operator_t::disconnect(_handle);
        }
    } else {
        //必须的，否则handle中分配的一些变量无法进行内存回收
        fs_operator_t::disconnect(_handle);
    }

    return false;
}

uint32_t AutoRunChanThread::execute(void* taskparam) {

    //if(!_script||!_script->flow||!_script->freeswitch_info_vec.size()){
    if (!_script || !_script->flow) {
        IVR_WARN("脚本文件或FS配置异常，自启动流程启动失败");
        return 1;
    }

    if (!occupy_channel()) {
        return 1;
    }

    ivr_session_id_t ivr_s_id;
    session_dynamic_resource_t* resource = (session_dynamic_resource_t*)taskparam;

    time_t ct = time(NULL);

    while (!g_stopped && ct >= g_autorun_script_stamp) {
        std::string err;
        /*
        if(!init_handle(err)){
            IVR_WARN("连接FS失败，自启动流程执行失败[%s]",err.c_str());
            ivr_tools_t::safe_sleeps(_script->autorun_interval);
            continue;
        }

        _script->handle = &_handle;
        */
        //获取当前最优的freeswitch
        fs_mgr_t::instance()->decision_fs(_script->fid);
        //创建实例
        IvrInstanceManager* mgr = IvrInstanceManager::get_instance();

        if (IVR_SUCCESS != mgr->create_ivr_instance(_script->type, _script->fid, &ivr_s_id, *resource,
                "0")) {
            IVR_WARN("创建实例失败");
            continue;
        }

        _script->session_id = ivr_s_id;
        _script->timer = resource->timer;

        std::string curr = ivr_tools_t::get_current_second();
        ivr_tools_t::build_vars(_script->flow->name_var_map, _script->name_var_map);

        *(string*)_script->name_var_map[SYS_VAR[sys_var_t::HANGUP_CAUSE]].pvalue = "user_hangup";
        *(string*)_script->name_var_map[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue = curr;
        *(string*)_script->name_var_map[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue = curr;

        NodeBase* node = _script->flow->id_node_map[_script->flow->begin_id];

        do {
            node = node->run(_script);
        } while (node && !g_stopped);

        if (!node && _script->is_write_bill) {
            IVR_TRACE("流程结束生成话单数据");
            CallDataManager::get_instance()->push_calldata(_script->bill_info().c_str());
        }

        ivr_tools_t::destroy_vars(_script->name_var_map);
        mgr->destroy_ivr_instance(ivr_s_id);

        //fs_operator_t::disconnect(_handle);
        if (!g_stopped) {
            ivr_tools_t::safe_sleeps(_script->autorun_interval);
        }
    }

    free_channel();

    IVR_TRACE("auto chan %s stoped", _script->name.c_str());
    FlowManager::detach_flow(&_script->flow);

    return 0;
}

bool AutoRunChanThread::free_channel() {
    std::string err;
    {
        rw_lock_t lock(g_autorun_chan_rwlock, true);

        if (lock.locked()) {
            --g_autorun_chan_num;
            return true;
        } else {
            err = "free_channel lock autorun rwlock failed";
        }
    }

    IVR_WARN("%s", err.c_str());

    return false;
}

bool AutoRunChanThread::occupy_channel() {
    ostringstream ostm;
    bool result = false;
    {
        rw_lock_t lock(g_autorun_chan_rwlock, true);

        if (lock.locked()) {
            if (g_autorun_chan_num < g_autorun_conf.max_autorun_chan_num) {
                ++g_autorun_chan_num;
                result = true;
            } else {
                ostm << "[OB]achieve max capability,reject service(" << g_autorun_chan_num << ")";
            }
        } else {
            ostm << "occupy_channel lock autorun rwlock failed";
        }
    }

    if (!result) {
        IVR_WARN("%s", ostm.str().c_str());
    }

    return result;
}

