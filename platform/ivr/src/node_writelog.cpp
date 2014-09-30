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

#include "node_writelog.h"

NodeWriteLog::NodeWriteLog(const uint32_t id, const string& name,
                           const string& type, const string& desc, const key_map_t& keymap) :
    NodeBase(id, name, type, desc, keymap) {
}

NodeWriteLog::~NodeWriteLog(void) {
}

NodeBase* NodeWriteLog::run(base_script_t* param) {
    const char* exit = EXIT_FAIL;
    std::string ret;
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    if (parse_expression(_exp, param->name_var_map, ret)) {
        BGCC_TRACE(_businame.c_str(), ret.c_str());
        exit = EXIT_SUCC;
    } else {
        IVR_WARN("parse assign expression failed(%s)", _exp.c_str());
    }

    IVR_TRACE("%s exit from %s",
              leave(param->name_var_map).c_str(), exit);
    return _exit_node_map[exit];
}

bool NodeWriteLog::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_EXP, _exp, false)
           && valid_str(_key_map, PARAM_BUSINAME, _businame);
}

std::string NodeWriteLog::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Exp: " << _exp << ", businame: " << _businame;
    return ostm.str();
}

std::string NodeWriteLog::leave(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "Exp: " << _exp << ", businame: " << _businame;
    return ostm.str();
}

const char* NodeWriteLog::PARAM_EXP = "exp";
const char* NodeWriteLog::PARAM_BUSINAME = "businame";
