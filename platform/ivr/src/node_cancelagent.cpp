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

#include <node_cancelagent.h>
#include <ivr_timer.h>

NodeCancelAgent::NodeCancelAgent(const uint32_t id, const string& name,
                                 const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeCancelAgent::~NodeCancelAgent() {
}

NodeBase* NodeCancelAgent::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    if (IVR_SUCCESS == ims_mgr_t::get_instance()->cancel_route_request(
                param->imsno, param->imssid, param->requestId)) {
        IVR_TRACE("cancel request agent success!");
        exit = EXIT_SUCC;

        // stop request timer
        if (param->requestId != 0 && param->timer != NULL) {
            param->timer->delete_timer(param->requestId, ims_transagent);
        }

        // reset requestid
        param->requestId = 0;
    } else {
        IVR_WARN("cancel request agent failed!");
    }

    return _find_exit_node(param, exit);
}

string NodeCancelAgent::enter(const map<string, variable_t>& vars) const {
    return NodeBase::enter(vars);
}

bool NodeCancelAgent::load_other() {
    return NodeBase::load_other();
}

NodeBase* NodeCancelAgent::_find_exit_node(base_script_t* param, const char* exit) {
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
