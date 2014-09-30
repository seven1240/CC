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

#include "node_regtimer.h"
#include "ivr_timer.h"

NodeRegTimer::NodeRegTimer(const uint32_t id, const string& name,
                           const string& type, const string& desc, const key_map_t& keymap) :
    NodeBase(id, name, type, desc, keymap) {
}

NodeRegTimer::~NodeRegTimer(void) {
}

NodeBase* NodeRegTimer::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    const char* exit = EXIT_FAIL;
    std::string ret;
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    IvrTimer* timer;
    time_t now;
    time_t expired;

    timer = (IvrTimer*)param->timer;

    if (NULL != timer) {
        parse_expression(_waittime, param->name_var_map, ret);

        if (ivr_tools_t::is_positive_integer(ret)) {
            time(&now);
            expired = now + atoi(ret.c_str());

            IVR_DEBUG("add timer. Add a timer %ld = now %ld + waittimer %d", expired, now,
                      atoi(_waittime.c_str()));

            if (IVR_SUCCESS == timer->add_timer(atoi(_timerid.c_str()), expired)) {
                exit = EXIT_SUCC;
            } else {
                IVR_WARN("Add timer failed. Timer id is %s", _timerid.c_str());
            }
        }
    } else {
        IVR_WARN("Add timer failed. Timer is null. Timer id is %s", _timerid.c_str());
    }

    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s(%s)",
                  leave(param->name_var_map).c_str(), exit, ret.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeRegTimer::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_TIMERID, _timerid)
           && valid_str(_key_map, PARAM_WAITTIME, _waittime);
}

std::string NodeRegTimer::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Timer id: " << _timerid << ", wait time: " << _waittime;
    return ostm.str();
}

std::string NodeRegTimer::leave(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "Timer id: " << _timerid << ", wait time: " << _waittime;
    return ostm.str();
}

const char* NodeRegTimer::PARAM_TIMERID = "timerid";
const char* NodeRegTimer::PARAM_WAITTIME = "waittime";
