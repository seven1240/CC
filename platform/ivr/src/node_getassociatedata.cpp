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

#include <node_getassociatedata.h>


NodeGetAssociateData::NodeGetAssociateData(const uint32_t id, const string& name,
        const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeGetAssociateData::~NodeGetAssociateData() {
}

NodeBase* NodeGetAssociateData::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    string data_key, data_value;
    const map<string, variable_t>& vars = param->name_var_map;

    if (vars.find(_value_data) == vars.end()) {
        IVR_WARN("未找到需要赋值的变量 %s", _value_data.c_str());
        return _find_exit_node(param, exit);
    }

    if (parse_all(_key_data, vars, data_key) && !data_key.empty()) {
        int32_t recode = ims_mgr_t::get_instance()->get_associatedata(param->imsno, param->imssid, data_key,
                         data_value);

        if (IVR_SUCCESS == recode) {
            variable_t& var = param->name_var_map[_value_data];

            if (var.type == STRING && NULL != var.pvalue) {
                *((string*)(var.pvalue)) = data_value;
                exit = EXIT_SUCC;
            } else {
                IVR_WARN("get associate data set result failed");
            }
        } else {
            IVR_WARN("get associate data failed");
        }
    } else {
        IVR_WARN("解析key字符串失败 %s", _key_data.c_str());
    }

    return _find_exit_node(param, exit);
}

string NodeGetAssociateData::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::enter(vars) +
    "key: " + _key_data + ", " +
    "value: " + _value_data;
    return strb.str();
}

NodeBase* NodeGetAssociateData::_find_exit_node(base_script_t* param, const char* exit) {
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

bool NodeGetAssociateData::load_other() {
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_KEY, _key_data) &&
           valid_str(_key_map, PARAM_VALUE, _value_data);
}

const char* NodeGetAssociateData::PARAM_KEY = "key";
const char* NodeGetAssociateData::PARAM_VALUE = "value";
