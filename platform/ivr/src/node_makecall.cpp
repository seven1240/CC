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

#include "node_makecall.h"
#include <ivr_timer.h>
#include "fs_opr.h"
#include "fs_mgr.h"
#include <ivr_instance_manager.h>

NodeMakeCall::NodeMakeCall(const uint32_t id, const string& name,
                           const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeMakeCall::~NodeMakeCall() {
}

NodeBase* NodeMakeCall::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    int32_t timeout = 0;
    int32_t callmode = 0;
    std::string agentdn;
    std::string clientdn;
    std::string showani;
    std::string showdest;
    std::string str_callmode;
    std::string noevent;

    std::string str_timeout;
    const map<string, variable_t>& vars = param->name_var_map;

    // check params
    if (!parse_all(_timeout, vars, str_timeout) ||
            !parse_all(_agentdn, vars, agentdn) ||
            !parse_all(_clientdn, vars, clientdn) ||
            !parse_all(_showani, vars, showani) ||
            !parse_all(_showdest, vars, showdest) ||
            !parse_all(_callmode, vars, str_callmode) ||
            !ivr_tools_t::is_integer(str_callmode) ||
            !(str_timeout.empty() || ivr_tools_t::is_nonnegative_integer(str_timeout))) {
        IVR_WARN("some params parsed failed!");
        return _find_exit_node(param, exit);
    }

    // timeout
    if (str_timeout.empty()) {
        timeout = 60;
        IVR_DEBUG("use default timeout 60s");
    } else {
        timeout = atoi(str_timeout.c_str());
        IVR_DEBUG("get timeout %ds", timeout);
    }

    // callmode
    callmode = atoi(str_callmode.c_str());
    IVR_DEBUG("get callmode %d", callmode);

    if (!_showani.empty()) {
        parse_all(_showani, vars, showani);
        IVR_DEBUG("get showani (%s)", showani.c_str());
    } else {
        showani = agentdn;
        IVR_DEBUG("use agentdn as showani (%s)", showani.c_str());
    }

    if (!_showdest.empty()) {
        parse_all(_showdest, vars, showdest);
        IVR_DEBUG("get showdest (%s)", showdest.c_str());
    } else {
        showdest = clientdn;
        IVR_DEBUG("use clientdn as showdest (%s)", showdest.c_str());
    }

    parse_all(_disable_event, vars, noevent);
    IVR_DEBUG("disable event ? %s", noevent.c_str());

    if (IVR_SUCCESS == ims_mgr_t::get_instance()->makecall(param->imsno, agentdn, clientdn,
            showani, showdest, timeout, callmode, param->imssid)) {
        IVR_TRACE("makecall success!");
        IVR_DEBUG("ims session id (%ld)", param->imssid);
        ims_mgr_t::get_instance()->bind_session_id(param->imssid, param->session_id);
        exit = EXIT_SUCC;
        // mark stop to receive fs event and send fs cmd
        IvrInstanceManager::get_instance()->mark_transagent(param->session_id,
                strcasecmp(noevent.c_str(), "false") != 0);
    } else {
        IVR_WARN("makecall failed!");
    }

    return _find_exit_node(param, exit);
}

bool NodeMakeCall::load_other() {
    valid_str(_key_map, PARAM_SHOWANI, _showani);  // can empty
    valid_str(_key_map, PARAM_SHOWDEST, _showdest);  // can empty
    valid_str(_key_map, PARAM_TIMEOUT, _timeout); // can empty
    valid_str(_key_map, PARAM_NOEVENT, _disable_event); // can empty
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_AGENTDN, _agentdn) &&
           valid_str(_key_map, PARAM_CLIENTDN, _clientdn) &&
           valid_str(_key_map, PARAM_CALLMODE, _callmode);
}

string NodeMakeCall::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::enter(vars) +
    "agentdn: " + _agentdn + ", " +
    "clientdn: " + _clientdn + ", " +
    "showani: " + _showani + ", " +
    "showdest: " + _showdest + ", " +
    "callmode: " + _callmode + ", " +
    "timeout: " + _timeout + ", " +
    "noevent: " + _disable_event;
    return strb.str();
}

NodeBase* NodeMakeCall::_find_exit_node(base_script_t* param, const char* exit) {
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

const char* NodeMakeCall::PARAM_AGENTDN = "agentdn";
const char* NodeMakeCall::PARAM_CLIENTDN = "clientdn";
const char* NodeMakeCall::PARAM_SHOWANI = "showani";
const char* NodeMakeCall::PARAM_SHOWDEST = "showdest";
const char* NodeMakeCall::PARAM_CALLMODE = "callmode";
const char* NodeMakeCall::PARAM_TIMEOUT = "timeout";
const char* NodeMakeCall::PARAM_NOEVENT = "noevent";
