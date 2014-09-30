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

#include "node_record.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodeRecord::NodeRecord(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeRecord::~NodeRecord(void) {
}

NodeBase* NodeRecord::run(base_script_t* param) {
    fs_opr_t* opr = NULL;
    string path;

    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    string callid;
    string record_file;
    fw_id_t fs_no = param->fid;


    if (!parse_expression(_callid, param->name_var_map, callid)
            || !parse_expression(_record_file, param->name_var_map, record_file)) {
        IVR_WARN("parse callid or recordfile failed");
        goto END;
    } else {
        IVR_TRACE("callid=%s,recordfile=%s", callid.c_str(), record_file.c_str());
    }

    //    *(string*)param->name_var_map[SYS_VAR[sys_var_t::RECORD_FILE]].pvalue=record_file;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            path = record_file;

            if (opr->record(callid.c_str(), path.c_str(), true) == IVR_SUCCESS) {
                exit = EXIT_SUCC;
            } else {
                IVR_WARN("opr record failed(callid: %s)", _callid.c_str());
            }

            fs_mgr_t::instance()->free_opr(&opr);
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }
    } else {
        IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
    }

END:
    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, record_file.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

const char* NodeRecord::PARAM_RECORDFILE = "recordfile";

bool NodeRecord::load_other() {
    return NodeResource::load_other()
           && valid_str(_key_map, PARAM_RECORDFILE, _record_file);
}
