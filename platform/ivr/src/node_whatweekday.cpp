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

#include <node_whatweekday.h>
#include <ctime>

NodeWhatWeekday::NodeWhatWeekday(const uint32_t id, const string& name,
                                 const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeWhatWeekday::~NodeWhatWeekday() {
}

NodeBase* NodeWhatWeekday::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    map<string, variable_t>& vars = param->name_var_map;

    if (_weekday.empty()) {
        IVR_WARN("check output param failed, (weekday) is empty!");
        return _find_exit_node(param, exit);
    }

    map<string, variable_t>::iterator it = vars.find(_weekday);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到需要赋值的变量 %s", _weekday.c_str());
    } else {
        // try to set output variable
        if ((it->second.type == STRING || it->second.type == INT32) && it->second.pvalue != NULL) {
            // set output param
            int day = bgcc::TimeUtil::get_day();
            //time_t ctm = time(NULL);
            //int day = gmtime(&ctm)->tm_wday;
            *(string*)it->second.pvalue = std::string(1, '0' + day);
            exit = EXIT_SUCC;
        } else {
            IVR_WARN("output param is not STRING or INT32 type!");
        }
    }

    return _find_exit_node(param, exit);
}

string NodeWhatWeekday::enter(const map<string, variable_t>& vars) const {
    return NodeBase::enter(vars) + "weekday: " + _weekday;
}

NodeBase* NodeWhatWeekday::_find_exit_node(base_script_t* param, const char* exit) {
    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, param->callid.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeWhatWeekday::load_other() {
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_WEEKDAY, _weekday);
}

const char* NodeWhatWeekday::PARAM_WEEKDAY = "weekday";
