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

#include "node_assign.h"

NodeAssign::NodeAssign(const uint32_t id, const string& name,
                       const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeAssign::~NodeAssign(void) {
}

NodeBase* NodeAssign::run(base_script_t* param) {
    const char* exit = EXIT_FAIL;
    std::string ret = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    map<string, variable_t>::iterator it = param->name_var_map.find(_result);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到需要赋值的变量");
    } else {
        if (parse_expression(_exp, param->name_var_map, ret)) {

            if (INT32 != it->second.type && STRING != it->second.type) {
                IVR_WARN("变量%s 的类型不能被赋值", _result.c_str());
            } else {
                *(string*)it->second.pvalue = ret;
                exit = EXIT_SUCC;
            }
        } else {
            IVR_WARN("parse assign expression failed(%s)", _exp.c_str());
        }
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, ret.c_str());
    return _exit_node_map[exit];
}

bool NodeAssign::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_EXP, _exp, false)
           && valid_str(_key_map, PARAM_RESULT, _result);
}

const char* NodeAssign::PARAM_EXP = "exp";
const char* NodeAssign::PARAM_RESULT = "result";

std::string NodeAssign::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Exp:" << _exp << ",result:" << _result;
    return ostm.str();
}

std::string NodeAssign::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "Exp:" << _exp;
    return ostm.str();
}


