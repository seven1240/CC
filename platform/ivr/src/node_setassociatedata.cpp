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

#include <node_setassociatedata.h>

NodeSetAssociateData::NodeSetAssociateData(const uint32_t id, const string& name,
        const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeSetAssociateData::~NodeSetAssociateData() {
}

NodeBase* NodeSetAssociateData::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    string key_data;
    string value_data;
    const map<string, variable_t>& vars = param->name_var_map;

    if (!parse_all(_key_data, vars, key_data) || key_data.empty() ||
            !parse_all(_value_data, vars, value_data)) {
        IVR_WARN("get key or key failed!, key %s, value %s", _key_data.c_str(), _value_data.c_str());
        return _find_exit_node(param, exit);
    }

    if (IVR_SUCCESS == ims_mgr_t::get_instance()->set_associatedata(
                param->imsno, param->imssid, key_data, value_data)) {
        IVR_TRACE("set associate data success!");
        exit = EXIT_SUCC;
    } else {
        IVR_WARN("set associate data failed!");
    }

    return _find_exit_node(param, exit);
}

string NodeSetAssociateData::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::enter(vars) +
    "key: " + _key_data + ", " +
    "value: " + _value_data;
    return strb.str();
}

NodeBase* NodeSetAssociateData::_find_exit_node(base_script_t* param, const char* exit) {
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

bool NodeSetAssociateData::load_other() {
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_KEY, _key_data) &&
           valid_str(_key_map, PARAM_VALUE, _value_data);
}

const char* NodeSetAssociateData::PARAM_KEY = "key";
const char* NodeSetAssociateData::PARAM_VALUE = "value";
