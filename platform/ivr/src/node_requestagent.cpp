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

#include <node_requestagent.h>
#include <ivr_timer.h>
#include "fs_opr.h"
#include "fs_mgr.h"
#include <ivr_instance_manager.h>

NodeRequestAgent::NodeRequestAgent(const uint32_t id, const string& name,
                                   const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeRequestAgent::~NodeRequestAgent() {
}

NodeBase* NodeRequestAgent::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;

    string filename;
    int32_t timeout = 0;
    int32_t valid_time = 0;

    ims_routerequest_type_t reqType;
    string reqargs;
    string buffer;
    string str_timeout;
    string str_valid_time;
    string callid;

    const map<string, variable_t>& vars = param->name_var_map;

    // check params
    if (!parse_all(_filename, vars, filename) ||
            !parse_all(_timeout, vars, str_timeout) ||
            !parse_all(_valid_time, vars, str_valid_time) ||
            !parse_all(_reqArgs, vars, reqargs) ||
            !parse_all(_buffer, vars, buffer) ||
            !ivr_tools_t::is_positive_integer(str_timeout) ||
            !ivr_tools_t::is_positive_integer(str_valid_time) ||
            !_get_reqType(_reqType, reqType)) {
        IVR_WARN("some params parsed failed!");
        return _find_exit_node(param, exit);
    }

    // get callid
    parse_all(_callid, vars, callid);

    timeout = atoi(str_timeout.c_str());
    valid_time = atoi(str_valid_time.c_str());

    // set caller_uri and callee_uri
    std::string caller_uri;
    std::string callee_uri;
    std::string original_dest;

    if (!_caller.empty()) {
        parse_all(_caller, vars, caller_uri);
    } else {
        caller_uri = *((const string*)(param->name_var_map["_ANI"].pvalue));
    }

    if (!_callee.empty()) {
        parse_all(_callee, vars, callee_uri);
    } else {
        callee_uri = *((const string*)(param->name_var_map["_DNIS"].pvalue));
    }

    original_dest = *((const string*)(param->name_var_map["_DNIS"].pvalue));
    //    IVR_DEBUG("original_dest=(%s)", original_dest.c_str());

    // if filename is empty, use default file
    if (filename.empty()) {
        filename = "hold_music.wav";
    }

    channel_info_t cinfo;

    if (!callid.empty()) {
        if (IvrInstanceManager::get_instance()->get_channel_info(callid, cinfo) != IVR_SUCCESS) {
            IVR_WARN("not found callid(%s)'s channel information!", callid.c_str());
            return _find_exit_node(param, exit);
        }

        fs_opr_t* opr = NULL;
        fw_id_t fs_no = param->fid;

        if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS && opr != NULL) {
            if (opr->play(callid.c_str(), filename.c_str()) == IVR_SUCCESS) {
                IVR_TRACE("opr play success(callid: %s)", callid.c_str());
            } else {
                IVR_WARN("opr play failed(callid: %s)", callid.c_str());
            }

            fs_mgr_t::instance()->free_opr(&opr);
        } else {
            IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
            return _find_exit_node(param, exit);
        }
    } else { // callid is empty try create empty session
        if (fs_mgr_t::instance()->get_callsource(param->fid, cinfo.callsource) != IVR_SUCCESS) {
            IVR_WARN("not found fs(%d)'s ip!", param->fid);
            return _find_exit_node(param, exit);
        }

        cinfo.channel_id = CREATE_SESSION_EMPTY_CALLID;
        cinfo.channel_name = CREATE_SESSION_EMPTY_CALLID;
    }

    // if session id is invalidate, retry again(and just try one time)
    int retryTimes = 1;

    do {
        if (0 == param->imssid) {
            if (IVR_SUCCESS == ims_mgr_t::get_instance()->create_session(cinfo.callsource, cinfo.channel_id,
                    cinfo.channel_name, original_dest, param->imssid, param->imsno)) {
                //IVR_TRACE("(%s) create session successful!", );
                ims_mgr_t::get_instance()->bind_session_id(param->imssid, param->session_id);
                param->requestId = 0; // because imssid has changed, so request id must change
                ims_routerequest_id_t requestid = 0;

                if (IVR_SUCCESS == ims_mgr_t::get_instance()->route_request(param->imsno, param->imssid, requestid,
                        ims::ServiceTypeT::ServiceACD, timeout, valid_time, reqType,
                        reqargs, 0, caller_uri, callee_uri, buffer)) {
                    // add timer here, +2 make sure ims response had came
                    _new_request_timer(param, timeout + 2, param->requestId, requestid);
                    param->requestId = requestid;
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("route request 2 failed");
                }
            } else {
                IVR_WARN("create session failed");
            }

            // don't need retry again
            break;
        } else {
            ims_routerequest_id_t requestid = 0;
            int32_t ret = ims_mgr_t::get_instance()->route_request(param->imsno, param->imssid, requestid,
                          ims::ServiceTypeT::ServiceACD, timeout, valid_time, reqType,
                          reqargs, 0, caller_uri, callee_uri, buffer);

            switch (ret) {
            case IVR_SUCCESS:
                // add timer here, +2 make sure ims response had came
                _new_request_timer(param, timeout + 2, param->requestId, requestid);
                param->requestId = requestid;
                exit = EXIT_SUCC;
                break;

            case IVR_FAIL_IMS_ROUTEREQUEST_REPEATED:
                // don't try again
                -- retryTimes;
                break;

            case IVR_FAIL_IMS_REQIDINVALIDATE:
            case IVR_FAIL_IMS_SESSIONINVALIDATE:
                // ims may restarted, so must retry again
                param->imssid = 0;
                param->imsno = (uint32_t) - 1;
                param->requestId = 0;

            default:
                // don't try again
                -- retryTimes;
                break;
            }
        }
    } while (retryTimes-- > 0 && exit != EXIT_SUCC);

    return _find_exit_node(param, exit);
}

bool NodeRequestAgent::load_other() {
    valid_str(_key_map, PARAM_CALLER, _caller);  // can empty
    valid_str(_key_map, PARAM_CALLEE, _callee);  // can empty
    valid_str(_key_map, PARAM_FILENAME, _filename); // can empty
    valid_str(_key_map, PARAM_BUFFER, _buffer); // can empty
    valid_str(_key_map, PARAM_CALLID, _callid); // can empty
    return NodeBase::load_other() &&
           valid_str(_key_map, PARAM_TIMEOUT, _timeout) &&
           valid_str(_key_map, PARAM_VALIDTIME, _valid_time) &&
           valid_str(_key_map, PARAM_REQTYPE, _reqType) &&
           valid_str(_key_map, PARAM_REQARGS, _reqArgs);
}

void NodeRequestAgent::_new_request_timer(base_script_t* param, int32_t timeout,
        ims_routerequest_id_t orgid, ims_routerequest_id_t curid) {
    // clear timer first
    if (orgid != 0 && param != NULL && param->timer != NULL) {
        param->timer->delete_timer(orgid, ims_transagent);
    }

    // regist new timer
    if (param != NULL && param->timer != NULL && curid != 0) {
        // get current time
        time_t ct = time(NULL);
        // add timeout
        ct += timeout;
        param->timer->add_timer(curid, ct, ims_transagent);
    }
}

bool NodeRequestAgent::_get_reqType(const std::string& strtype,
                                    ims_routerequest_type_t& reqType) const {
    if (0 == strcasecmp(strtype.c_str(), "RR_TypeSkill")) {
        reqType = ims_routerequest_type_t::RR_TypeSkill;
    } else if (0 == strcasecmp(strtype.c_str(), "RR_TypePrivate")) {
        reqType = ims_routerequest_type_t::RR_TypePrivate;
    } else if (0 == strcasecmp(strtype.c_str(), "RR_TypePrivateList")) {
        reqType = ims_routerequest_type_t::RR_TypePrivateList;
    } else {
        IVR_WARN("unknown route request type: %s", strtype.c_str());
        return false;
    }

    return true;
}

string NodeRequestAgent::enter(const map<string, variable_t>& vars) const {
    string_build strb;
    strb + NodeResource::enter(vars) +
    "callid: " + _callid + ", " +
    "playfile: " + _filename + ", " +
    "timeout: " + _timeout + ", " +
    "valid_time: " + _valid_time + ", " +
    "reqType: " + _reqType + ", " +
    "reqArgs: " + _reqArgs + ", " +
    "showani: " + _caller + ", " +
    "showdest: " + _callee + ", " +
    "buffer: " + _buffer;
    return strb.str();
}

NodeBase* NodeRequestAgent::_find_exit_node(base_script_t* param, const char* exit) {
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

const char* NodeRequestAgent::PARAM_FILENAME = "filename";
const char* NodeRequestAgent::PARAM_TIMEOUT = "timeout";
const char* NodeRequestAgent::PARAM_VALIDTIME = "validtime";
const char* NodeRequestAgent::PARAM_REQTYPE = "reqtype";
const char* NodeRequestAgent::PARAM_REQARGS = "reqargs";
const char* NodeRequestAgent::PARAM_BUFFER = "buffer";
const char* NodeRequestAgent::PARAM_CALLEE = "showdest";
const char* NodeRequestAgent::PARAM_CALLER = "showani";
