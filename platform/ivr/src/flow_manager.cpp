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
#include "flow_manager.h"
#include "ini_file.h"
#include "db_pool.h"

#include "node_factory.h"

FlowManager::FlowManager() {
}

FlowManager::~FlowManager() {
    map<string, flow_t*>::iterator iter = _flow_name_info_map.begin();

    while (iter != _flow_name_info_map.end()) {
        if (iter->second != NULL) {
            detach_flow(&iter->second);
        }

        ++ iter;
    }
}

int32_t FlowManager::load_flow(const string& flowname, flow_t** flow_ret) {
    if (NULL == flow_ret) {
        IVR_WARN("flow_ret == NULL");
        return FAILURE;
    }

    INIFile* conf = INIFile::get_instance();

    string flow_path_name = flowname;

    if (!conf->load_file(flow_path_name.c_str())) {
        IVR_TRACE("load flow %s fail", flow_path_name.c_str());
        return FAILURE;
    }

    // check whethe has same flow file
    std::map<string, flow_t*>::iterator iterfind = _flow_name_info_map.find(flowname);

    if (iterfind != _flow_name_info_map.end()) {
        // juest return old one
        IVR_TRACE("flow with same file_path has loaded before, just use it!");
        return attach_flow(iterfind->second, flow_ret);
    }

    flow_t* tmpf = NULL;

    if (new_flow(&tmpf) != SUCCESS) {
        IVR_WARN("malloc new flow object failed.");
        return FAILURE;
    }

    std::auto_ptr<flow_t> flow(tmpf);

    IVR_TRACE("---------------load-flow-[%s] BEGIN---------------------------", flowname.c_str());

    //load [var***]
    //每个变量不需要new出实际对象，仅仅是模板，在流程实例中创建实例
    vector<uint32_t> var_idx_vec;
    section_map_t section_map = conf->get_section_map(flow_path_name.c_str(), true);
    ivr_tools_t::idx2vec(VAR, section_map, var_idx_vec);

    for (uint32_t ii = 0; ii < var_idx_vec.size(); ++ii) {
        ostringstream var_name;
        var_name << VAR << var_idx_vec[ii];
        key_map_t key_map = section_map[var_name.str()];

        variable_t variable;
        variable.pvalue = NULL;
        variable.name = key_map["name"];

        string type = key_map["type"];

        if (type == "int32") {
            variable.type = INT32;
        } else if (type == "string") {
            variable.type = STRING;
        } else if (type == "resultset") {
            variable.type = RESULTSET;
        } else if (type == "map") {
            variable.type = MAP;
        } else {
            IVR_WARN("var type error [%s]-[%s] !!!",
                     var_name.str().c_str(), flowname.c_str());
            continue;
        }

        if (flow->name_var_map.count(variable.name)) { //该名称变量已经存在
            IVR_WARN("参数重名,加载流程失败[%s] name = %s  type = %s  [%s]", var_name.str().c_str(),
                     variable.name.c_str(), type.c_str(), flowname.c_str());
            return FAILURE;
        }

        //initial
        if (type == "int32") {
            key_map_t::iterator it = key_map.find("initial");

            if (it != key_map.end()) {
                if (it->second == "") {
                    IVR_TRACE("var initial error [%s]-[%s] !!!",
                              var_name.str().c_str(), flowname.c_str());
                    variable.initial = "0";
                } else if (!ivr_tools_t::is_integer(it->second)) {
                    IVR_TRACE("var initial error [%s]-[%s] !!!",
                              var_name.str().c_str(), flowname.c_str());
                    variable.initial = "0";
                } else {
                    variable.initial = it->second;
                }
            } else {
                variable.initial = "0";
            }
        }

        if (type == "string") {
            key_map_t::iterator it = key_map.find("initial");

            if (it != key_map.end()) {
                if (it->second == "") {
                    IVR_TRACE("var initial error [%s]-[%s] !!!",
                              var_name.str().c_str(), flowname.c_str());
                    variable.initial = "";
                } else {
                    variable.initial = it->second;
                }
            } else {
                variable.initial = "";
            }
        }

        if ("int32" == type || "string" == type) {
            IVR_TRACE("Load [%s] name = %s  type = %s  initialValue = %s [%s]", var_name.str().c_str(),
                      variable.name.c_str(), type.c_str(), variable.initial.c_str(), flowname.c_str());
        } else {
            IVR_TRACE("Load [%s] name = %s  type = %s [%s]", var_name.str().c_str(),
                      variable.name.c_str(), type.c_str(), flowname.c_str());
        }

        flow->name_var_map[variable.name] = variable;

    }

    //load system var
    //每个变量不需要new出实际对象，仅仅是模板，在流程实例中创建实例
    for (uint32_t ii = sys_var_t::BEGIN; ii < sys_var_t::END; ii++) {
        variable_t variable;
        variable.name = SYS_VAR[ii];
        variable.type = STRING;

        if (flow->name_var_map.count(variable.name)) { //该名称变量已经存在
            IVR_WARN("参数与系统变量重名,加载流程失败 name = %s [%s]",
                     variable.name.c_str(), flowname.c_str());
            return FAILURE;
        }

        flow->name_var_map[variable.name] = variable;
    }

    {
        variable_t variable;
        variable.name = "BK_CALLID";
        variable.type = STRING;
        flow->name_var_map[variable.name] = variable;
    }

    //load [node***]
    vector<uint32_t> node_idx_vec;
    ivr_tools_t::idx2vec(NODE, section_map, node_idx_vec);

    if (node_idx_vec.size() == 0) { //没有node 加载流程失败
        IVR_WARN("%s流程中没有node,加载流程失败", flowname.c_str());
        return FAILURE;
    }

    flow->begin_id = node_idx_vec[0];

    // 遍历每个节点 并创建节点对象
    for (uint32_t i = 0; i < node_idx_vec.size(); i++) {

        ostringstream node_name;
        node_name << NODE << node_idx_vec[i];
        key_map_t key_map = section_map[node_name.str()];

        uint32_t id = node_idx_vec[i];
        string name = node_name.str();
        string type = key_map["type"];
        string desc = key_map["descript"];

        NodeBase* node = node_factory::create_node(id, name, type, desc, key_map);

        if (!node) {
            IVR_WARN("%s流程中有节点%s参数错误", flowname.c_str(), name.c_str());
            return FAILURE;
        }

        IVR_TRACE("%s流程 加载节点成功 %s", flowname.c_str(), name.c_str());


        flow->id_node_map[id] = node;//将节点插入到流程id_node_map中
    }

    //从最小的node开始，采用递归的方式建立有向图
    for (uint32_t ii = 0; ii < node_idx_vec.size(); ii++) {

        map<uint32_t, NodeBase*>::iterator it = flow->id_node_map.find(node_idx_vec[ii]);

        if (it == flow->id_node_map.end()) {
            //根据ID 没有找到这个node对象 忽略这个对象
            continue;
        }

        NodeBase* node = it->second;//节点对象

        map<string, uint32_t> exit_id_map = node->_exit_id_map;//事件出口

        for (map<string, uint32_t>::iterator iit = exit_id_map.begin();//遍历事件出口
                iit != exit_id_map.end(); ++ iit) {

            if (iit->second == 0) { //id=0 表明是流程终止节点
                node->_exit_node_map[iit->first] = NULL;
                continue;
            }

            map<uint32_t, NodeBase*>::iterator itr = flow->id_node_map.find(iit->second);

            if (itr == flow->id_node_map.end()) {
                IVR_WARN("%s流程中有节点%s的事件出口指向节点不存在",
                         flowname.c_str(), node->_name.c_str());
                return FAILURE;//这个node对象 配置的事件出口ID 没有找到匹配的对象
            }

            node->_exit_node_map[iit->first] = flow->id_node_map[iit->second];//建立节点网状连接
        }
    }

    _flow_name_info_map[flowname] = flow.get();
    *flow_ret = flow.release();

    return SUCCESS;
}

int32_t FlowManager::new_flow(flow_t** flow) {
    if (flow == NULL) {
        IVR_WARN("dest is null!");
        return FAILURE;
    }

    std::auto_ptr<flow_t> tmp(new(std::nothrow)flow_t);

    if (tmp.get() != NULL) {
        tmp->ref_count = 1;
        *flow = tmp.release();
    } else {
        IVR_WARN("memory failed!");
        return FAILURE;
    }

    return SUCCESS;
}

int32_t FlowManager::free_flow(flow_t** flow) {
    if (flow == NULL || *flow == NULL) {
        return FAILURE;
    }

    // free nodes
    IVR_DEBUG("delete flow(%p)'s nodes!", *flow);

    for (std::map<uint32_t, NodeBase*>::iterator iter = (*flow)->id_node_map.begin();
            iter != (*flow)->id_node_map.end(); ++ iter) {
        if (iter->second != NULL) {
            delete iter->second;
            iter->second = NULL;
        }
    }

    delete *flow;
    *flow = NULL;
    return SUCCESS;
}

int32_t FlowManager::detach_flow(flow_t** flow) {
    if (flow == NULL || *flow == NULL) {
        return SUCCESS;
    }

    locker_t lock(&((*flow)->refcmutex));

    if (lock.is_locked()) {
        IVR_DEBUG("acquired!");
        IVR_TRACE("flow(%p)'s refcount dec to (%u)", *flow, (*flow)->ref_count - 1);

        if (-- ((*flow)->ref_count) == 0) {
            // need free all node's memory
            flow_t* backp = *flow;
            free_flow(flow);
            IVR_TRACE("flow(%p) deleted!", backp);
        }
    } else {
        IVR_WARN("lock failed!");
        return FAILURE;
    }

    return SUCCESS;
}

int32_t FlowManager::attach_flow(flow_t* flow_in, flow_t** out) {
    if (out == NULL) {
        IVR_WARN("dest is null!");
        return FAILURE;
    }

    if (flow_in == NULL) {
        *out = flow_in;
        return SUCCESS;
    }

    locker_t lock(&flow_in->refcmutex);

    if (lock.is_locked()) {
        IVR_DEBUG("acquired");
        ++ flow_in->ref_count;
        IVR_TRACE("flow(%p)'s refcount inc to (%u)", flow_in, flow_in->ref_count);
        *out = flow_in;
    } else {
        IVR_WARN("lock failed");
        return FAILURE;
    }

    return SUCCESS;
}

void FlowManager::swap(FlowManager& other) throw () {
    // don't need a lock here, because g_inbound_rwlock(or g_autorun_rwlock) lock this when modify
    std::swap(_flow_name_info_map, other._flow_name_info_map);
}

const char* FlowManager::VAR = "var";
const char* FlowManager::NODE = "node";

