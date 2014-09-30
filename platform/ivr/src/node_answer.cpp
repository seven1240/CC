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

#include "common.h"
#include "tools.h"
#include "node_answer.h"
#include "fs_mgr.h"
#include "fs_opr.h"

NodeAnswer::NodeAnswer(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeAnswer::~NodeAnswer(void) {
}

NodeBase* NodeAnswer::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    string callid;
    const char* exit;
    fw_id_t fs_no;

    exit = EXIT_FAIL;
    fs_no = param->fid;

    if (true == parse_expression(_callid, param->name_var_map, callid)) {
        IVR_TRACE("callid = %s", callid.c_str());

        fs_opr_t* opr = NULL;

        if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
            if (NULL != opr) {
                if (opr->answer(callid.c_str()) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr answer failed(callid: %s)", _callid.c_str());
                }
            } else {
                IVR_WARN("fs_opr_t pointer should not be null");
            }

            fs_mgr_t::instance()->free_opr(&opr);
        } else {
            IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
        }
    } else {
        IVR_WARN("callid parse failed(%s)", _callid.c_str());
    }

    NodeBase* pnode = NULL;
    bool bfind = get_exit_node(exit, &pnode);

    if (true == bfind) {
        IVR_TRACE("%s exit from %s", leave(param->name_var_map).c_str(), exit);
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return pnode;
}

bool NodeAnswer::get_exit_node(const char* exit_name, NodeBase** ppnode) {
    if (NULL == ppnode) {
        IVR_WARN("pointer to pointer of NodeBase should not be null");
        return false;
    }

    std::map<std::string, NodeBase*>::iterator citr;

    citr = _exit_node_map.find(exit_name);

    if (citr != _exit_node_map.end()) {
        *ppnode = citr->second;
        return true;
    } else {
        *ppnode = NULL;
        return false;
    }
}

bool NodeAnswer::load_other() {
    return NodeResource::load_other();
}

