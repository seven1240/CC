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

#include "node_hangup.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodeHangup::NodeHangup(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeHangup::~NodeHangup(void) {
}

NodeBase* NodeHangup::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    string callid;
    fw_id_t fs_no = param->fid;

    if (true == parse_expression(_callid, param->name_var_map, callid)) {
        IVR_TRACE("callid=%s", callid.c_str());

        fs_opr_t* opr = NULL;

        if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
            if (NULL != opr) {
                if (opr->hangup(callid.c_str()) == IVR_SUCCESS) {
                    *(string*)param->name_var_map[SYS_VAR[sys_var_t::HANGUP_CAUSE]].pvalue = HANGUP_CAUSE_SYS;
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr hangup failed(callid %s)", _callid.c_str());
                }

                fs_mgr_t::instance()->free_opr(&opr);
            } else {
                IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
            }
        }
    } else {
        IVR_WARN("parse callid failed(%s)", _callid.c_str());
    }

    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s()",
                  leave(param->name_var_map).c_str(), exit);
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeHangup::load_other() {
    return NodeResource::load_other();
}
