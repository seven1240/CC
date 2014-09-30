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

#include <node_imsresponsecmp.h>
#include <json/json.h>

NodeRequestResponseCompare::NodeRequestResponseCompare(const uint32_t id, const string& name,
        const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeRequestResponseCompare::~NodeRequestResponseCompare() {
}

NodeBase* NodeRequestResponseCompare::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    string response;
    const map<string, variable_t>& vars = param->name_var_map;

    if (!parse_expression(_response, vars, response)) {
        IVR_WARN("check ims reponse failed, parse json error!");
        return _find_exit_node(param, exit);
    }

    if (_agent.empty()) {
        IVR_WARN("check output param failed, (agent) is empty!");
        return _find_exit_node(param, exit);
    }

    ims_routerequest_id_t requestid = 0;
    int32_t reason = 0;
    string agent;

    map<string, variable_t>::iterator it = param->name_var_map.find(_agent);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到需要赋值的变量 %s", _agent.c_str());
    } else {
        // try to parse json string
        if (_get_values(response, requestid, reason, agent)) {
            if (ims_routeevent_reason_t::RouteReasonSuccess == reason) {
                // acd got agent
                IVR_TRACE("get agent success, agent %s!", agent.c_str());

                if (it->second.type == STRING && it->second.pvalue != NULL) {
                    // set output param
                    *(string*)it->second.pvalue = agent;
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("output param is not STRING type!");
                }
            } else {
                IVR_WARN("get agent failed!");
            }
        } else {
            IVR_WARN("failed parse json string!");
        }
    }

    return _find_exit_node(param, exit);
}

bool NodeRequestResponseCompare::_get_values(const string& response,
        ims_routerequest_id_t& requestid, int32_t& reason, string& agent) {
    IVR_TRACE("parse json string(%s)", response.c_str());
    json_object* obj = json_tokener_parse(response.c_str());

    if (NULL == obj || is_error(obj)) {
        IVR_WARN("check ims reponse failed, parse json error!");
        return false;
    }

    {
        // get request id
        json_object* obj_requestid = json_object_object_get(obj, "requestID");

        if (NULL == obj_requestid || is_error(obj_requestid)) {
            IVR_WARN("check ims reponse failed, get requestid error!");
            json_object_put(obj);
            return false;
        }

        const char* requestid_result = json_object_get_string(obj_requestid);

        if (NULL == requestid_result) {
            IVR_WARN("check ims reponse failed, get requestid string error!");
            //json_object_put(obj_requestid);
            json_object_put(obj);
            return false;
        }

        requestid = atoll(requestid_result);

        //json_object_put(obj_requestid);
    }

    {
        // get response result
        json_object* obj_resresult = json_object_object_get(obj, "RequestResult");

        if (NULL == obj_resresult || is_error(obj_resresult)) {
            IVR_WARN("check ims reponse failed, get response result error!");
            json_object_put(obj);
            return false;
        }

        const char* response_result = json_object_get_string(obj_resresult);

        if (NULL == response_result) {
            IVR_WARN("check ims reponse failed, get response result string error!");
            //json_object_put(obj_resresult);
            json_object_put(obj);
            return false;
        } else if (0 == strcasecmp(response_result, "RouteReasonSuccess")) {
            IVR_TRACE("route reason success!");
            reason = ims_routeevent_reason_t::RouteReasonSuccess;
        } else if (0 == strcasecmp(response_result, "RouteReasonBusy")) {
            IVR_TRACE("route reason busy!");
            reason = ims_routeevent_reason_t::RouteReasonBusy;
        } else if (0 == strcasecmp(response_result, "RouteReasonPrivateBusy")) {
            IVR_TRACE("route reason private busy!");
            reason = ims_routeevent_reason_t::RouteReasonPrivateBusy;
        } else if (0 == strcasecmp(response_result, "RouteReasonError")) {
            IVR_TRACE("route reason error!");
            reason = ims_routeevent_reason_t::RouteReasonError;
        } else if (0 == strcasecmp(response_result, "RouteReasonOther")) {
            IVR_TRACE("route reason other!");
            reason = ims_routeevent_reason_t::RouteReasonOther;
        } else {
            IVR_WARN("unknown reason %s!", response_result);
            //json_object_put(obj_resresult);
            json_object_put(obj);
            return false;
        }

        //json_object_put(obj_resresult);
    }

    {
        // get agent
        json_object* obj_agent = json_object_object_get(obj, "Agent");

        if (NULL == obj_agent || is_error(obj_agent)) {
            IVR_WARN("check ims reponse failed, get agent error!");
            json_object_put(obj);
            return false;
        }

        const char* agent_result = json_object_get_string(obj_agent);

        if (NULL == agent_result) {
            IVR_WARN("check ims reponse failed, get requestid string error!");
            //json_object_put(obj_agent);
            json_object_put(obj);
            return false;
        }

        agent = agent_result;

        //json_object_put(obj_agent);
    }

    json_object_put(obj);
    return true;
}

string NodeRequestResponseCompare::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::enter(vars) +
    "response: " + _response;
    return strb.str();
}

string NodeRequestResponseCompare::leave(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeBase::leave(vars) +
    "agent: " + _agent;
    return strb.str();
}

NodeBase* NodeRequestResponseCompare::_find_exit_node(base_script_t* param, const char* exit) {
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

bool NodeRequestResponseCompare::load_other() {
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_AGENT, _agent) &&
           valid_str(_key_map, PARAM_RESPONSE, _response);
}

const char* NodeRequestResponseCompare::PARAM_RESPONSE = "response";
const char* NodeRequestResponseCompare::PARAM_AGENT = "agent";
