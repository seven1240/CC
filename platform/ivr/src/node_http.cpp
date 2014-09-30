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

#include "node_http.h"
#include "http.h"

NodeHttp::NodeHttp(const uint32_t id, const string& name,
                   const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeHttp::~NodeHttp(void) {
}

NodeBase* NodeHttp::run(base_script_t* param) {
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    string url;
    const char* exit = EXIT_FAIL;
    std::string resp;
    int32_t timeout = 0;

    if (_timeout.empty()) {
        timeout = 5;
        IVR_DEBUG("use default timeout 5s");
    } else {
        std::string str_timeout;

        if (!parse_all(_timeout, param->name_var_map, str_timeout)
                || !ivr_tools_t::is_positive_integer(str_timeout)) {
            IVR_WARN("timeout is invalid, input(%s), string(%s), use defalt timeout 5s",
                     _timeout.c_str(), str_timeout.c_str());
            timeout = 5;
        } else {
            timeout = atoi(str_timeout.c_str());
        }
    }

    if (param->name_var_map.find(_resp) == param->name_var_map.end()) {
        IVR_WARN("output param(%s) is not in name_var_map.", _resp.c_str());
    } else if (timeout > 0 && parse_all(_url, param->name_var_map, url)) {
        IVR_TRACE("Send url = %s, timeout = %d", url.c_str(), timeout);

        if (strcasecmp(_sendtype.c_str(), PARAMITEM_POST) == 0) {
            if (http_t::post(url.c_str(), resp, timeout)) {
                IVR_TRACE("Send: POST, resp = %s", resp.c_str());
                variable_t var = param->name_var_map[_resp];

                if ((var.type == INT32 || var.type == STRING) && NULL != var.pvalue) {
                    *(string*)var.pvalue = resp;
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("变量%s 的类型不能被赋值", var.name.c_str());
                }
            }
        } else if (strcasecmp(_sendtype.c_str(), PARAMITEM_GET) == 0) {
            if (http_t::get(url.c_str(), resp, timeout)) {
                IVR_TRACE("Send: GET, resp = %s", resp.c_str());
                variable_t var = param->name_var_map[_resp];

                if ((var.type == INT32 || var.type == STRING) && NULL != var.pvalue) {
                    *(string*)var.pvalue = resp;
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("变量%s 的类型不能被赋值", var.name.c_str());
                }
            }
        } else {
            IVR_TRACE("Param outtype is invalid: %s", _sendtype.c_str());
        }
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, resp.c_str());

    return _exit_node_map[exit];
}

bool NodeHttp::load_other() {
    valid_str(_key_map, PARAM_TIMEOUT, _timeout);  // can empty
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_URL, _url)
           && valid_str(_key_map, PARAM_SENDTYPE, _sendtype)
           && valid_str(_key_map, PARAM_RESP, _resp);
}

const char* NodeHttp::PARAM_URL = "url";
const char* NodeHttp::PARAM_RESP = "resp";
const char* NodeHttp::PARAM_SENDTYPE = "outtype";
const char* NodeHttp::PARAM_TIMEOUT = "timeout";

const char* NodeHttp::PARAMITEM_POST = "post";
const char* NodeHttp::PARAMITEM_GET = "get";

std::string NodeHttp::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "url:" << _url << ", resp:" << _resp;
    return ostm.str();
}

std::string NodeHttp::leave(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "url:" << _url;
    return ostm.str();
}

