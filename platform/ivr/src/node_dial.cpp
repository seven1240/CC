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

#include "node_dial.h"
#include "tools.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodeDial::NodeDial(const uint32_t id, const string& name,
                   const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeDial::~NodeDial(void) {
}

NodeBase* NodeDial::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    const char* exit = EXIT_FAIL;
    std::string ret = "";
    //bool result = false;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    std::string callid, called_number, caller_number, calltype; ///<calltype==0标示内呼叫，其他为外呼

    /*map<string, variable_t>::iterator it = param->name_var_map.find(_new_callid);
    if (it == param->name_var_map.end()) {
        IVR_WARN("输出的变量 %s 未定义", _new_callid.c_str());
        goto END;
    }*/

    if (true == parse_expression(_called_number, param->name_var_map, called_number)
            && true == parse_expression(_caller_number, param->name_var_map, caller_number)
            && true == parse_expression(_calltype, param->name_var_map, calltype)) {
        IVR_TRACE("callid=%s,caller_number=%s,called_number=%s,ivrsid=%lu",
                  callid.c_str(), caller_number.c_str(), called_number.c_str(), param->session_id);
    } else {
        IVR_WARN("parse callid or callerno or calledno failed");
        goto END;
    }


    *(string*)param->name_var_map[SYS_VAR[sys_var_t::ANI]].pvalue = caller_number;
    *(string*)param->name_var_map[SYS_VAR[sys_var_t::DNIS]].pvalue = called_number;
    *(string*)param->name_var_map[SYS_VAR[sys_var_t::RECORD_FILE]].pvalue = "";

    *(string*)param->name_var_map[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue =
        ivr_tools_t::get_current_second();

    *(string*)param->name_var_map[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue =
        *(string*)param->name_var_map[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue;

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (opr->dial(param->session_id, called_number.c_str(), caller_number.c_str(), 30,
                          calltype != "0") == IVR_SUCCESS) {
                exit = EXIT_SUCC;
            } else {
                IVR_WARN("opr dial failed(callid: %s)", _callid.c_str());
            }

            fs_mgr_t::instance()->free_opr(&opr);
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }
    }

END:
    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, callid.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeDial::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_CALLED, _called_number)
           && valid_str(_key_map, PARAM_CALLER, _caller_number)
           && valid_str(_key_map, PARAM_CALLTYPE, _calltype);
}

const char* NodeDial::PARAM_CALLED = "callednumber";
const char* NodeDial::PARAM_CALLER = "callernumber";
const char* NodeDial::PARAM_CALLTYPE = "calltype";

std::string NodeDial::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "caller:" << _caller_number << ",called:" << _called_number;
    return ostm.str();
}

