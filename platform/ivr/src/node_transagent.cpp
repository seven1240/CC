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

#include <node_transagent.h>
#include <ivr_instance_manager.h>


NodeTransAgent::NodeTransAgent(const uint32_t id, const string& name,
                               const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeTransAgent::~NodeTransAgent() {
}

NodeBase* NodeTransAgent::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    std::string noevent;
    parse_all(_disable_event, param->name_var_map, noevent);

    ims_transtype_t ttype;

    if (_get_type(_transtype, ttype)) {
        if (IVR_SUCCESS == ims_mgr_t::get_instance()->trans_agent(param->imsno, param->imssid,
                param->requestId, ttype)) {
            IVR_TRACE("trans agent success!");
            exit = EXIT_SUCC;
            // mark stop to receive fs event and send fs cmd
            IvrInstanceManager::get_instance()->mark_transagent(param->session_id,
                    strcasecmp(noevent.c_str(), "false") != 0);
        } else {
            IVR_WARN("trans agent failed!");
        }
    } else {
        IVR_WARN("failed to convert %s to trans type!", _transtype.c_str());
    }

    return _find_exit_node(param, exit);
}

bool NodeTransAgent::_get_type(const string& v, ims_transtype_t& ttype) {
    if (0 == strcasecmp(v.c_str(), "TT_INSTANT")) {
        ttype = ims::TransferTypeT::TT_INSTANT;
    } else if (0 == strcasecmp(v.c_str(), "TT_RING")) {
        ttype = ims::TransferTypeT::TT_RING;
    } else if (0 == strcasecmp(v.c_str(), "TT_ANSWER")) {
        ttype = ims::TransferTypeT::TT_ANSWER;
    } else {
        return false;
    }

    return true;
}

string NodeTransAgent::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::enter(vars) +
    "transtype: " + _transtype +
    "noevent: " + _disable_event;
    return strb.str();
}

bool NodeTransAgent::load_other() {
    valid_str(_key_map, PARAM_NOEVENT, _disable_event);
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_TRANSTYPE, _transtype);
}

NodeBase* NodeTransAgent::_find_exit_node(base_script_t* param, const char* exit) {
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

const char* NodeTransAgent::PARAM_TRANSTYPE = "transtype";
const char* NodeTransAgent::PARAM_NOEVENT = "noevent";
