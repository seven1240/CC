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

#include "tools.h"
#include "node_getdigits.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodeGetDigits::NodeGetDigits(const uint32_t id, const string& name,
                             const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
    _min_len = "0";
    _max_len = "0";
    _repeat = "1";
    _input_timeout = "0";
}

NodeGetDigits::~NodeGetDigits(void) {
}

NodeBase* NodeGetDigits::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    string str_min_len;
    string str_max_len;
    string str_repeat;
    string str_input_timeout;
    uint32_t min_len;
    uint32_t max_len;
    uint32_t repeat;
    uint32_t input_timeout;
    const char* exit = EXIT_FAIL;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;
    std::string ret = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    std::string callid, playfile, invalidfile;

    //    map<string, variable_t>::iterator it = param->name_var_map.find(_var);

    if (parse_expression(_min_len, param->name_var_map, str_min_len) &&
            parse_expression(_max_len, param->name_var_map, str_max_len) &&
            parse_expression(_repeat, param->name_var_map, str_repeat) &&
            parse_expression(_input_timeout, param->name_var_map, str_input_timeout)) {
        if (!ivr_tools_t::is_positive_integer(str_min_len) ||
                !ivr_tools_t::is_positive_integer(str_max_len) ||
                !ivr_tools_t::is_positive_integer(str_repeat) ||
                !ivr_tools_t::is_positive_integer(str_input_timeout)) {
            IVR_WARN("Parameter Error: min_len:%s, max_len:%s, repeat:%s, timeout:%s",
                     str_min_len.c_str(), str_max_len.c_str(),
                     str_repeat.c_str(), str_input_timeout.c_str());
            goto END;
        }

        min_len = atoi(str_min_len.c_str());
        max_len = atoi(str_max_len.c_str());
        repeat =  atoi(str_repeat.c_str());
        input_timeout = atoi(str_input_timeout.c_str());
        IVR_TRACE("min_len:%u, max_len:%u, repeat:%u, timeout:%u", min_len, max_len, repeat, input_timeout);
    } else {
        IVR_WARN("Parameter Parse Error: min_len:%s, max_len:%s, repeat:%s, timeout:%s",
                 _min_len.c_str(), _max_len.c_str(),
                 _repeat.c_str(), _input_timeout.c_str());
        goto END;
    }

    if (parse_expression(_callid, param->name_var_map, callid)
            && parse_expression(_play_file, param->name_var_map, playfile)
            && parse_expression(_invalid_file, param->name_var_map, invalidfile)) {
        IVR_TRACE("callid=%s,playfile=%s,invalidfile=%s",
                  callid.c_str(),
                  (param->vox_base + playfile).c_str(),
                  (param->vox_base + invalidfile).c_str());
    } else {
        IVR_WARN("parse playfile or invalidfile or callid failed");
        goto END;
    }

    playfile = param->vox_base + playfile;
    invalidfile = param->vox_base + invalidfile;

    //    if (it == param->name_var_map.end()) {
    //        IVR_WARN("输出的变量 %s 未定义", _var.c_str());
    //        goto END;
    //    }

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (opr->play_and_get_digits(callid.c_str(), playfile.c_str(),
                                         min_len, max_len, repeat, input_timeout, _end.c_str(), invalidfile.c_str()) == IVR_SUCCESS) {
                exit = EXIT_SUCC;
            } else {
                IVR_TRACE("收号调用失败");
            }
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }

        fs_mgr_t::instance()->free_opr(&opr);
    } else {
        IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
    }

END:
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

const char* NodeGetDigits::PARAM_MIN = "minlen";
const char* NodeGetDigits::PARAM_MAX = "maxlen";
const char* NodeGetDigits::PARAM_REPEAT = "repeat";
const char* NodeGetDigits::PARAM_TIMEOUT = "inputtimeout";
const char* NodeGetDigits::PARAM_FILE = "playfile";
const char* NodeGetDigits::PARAM_INVALIDFILE = "invalidfile";
const char* NodeGetDigits::PARAM_ENDKEY = "end";

bool NodeGetDigits::load_other() {

    if (valid_str(_key_map, PARAM_FILE, _play_file)) {
        if (!valid_str(_key_map, PARAM_REPEAT, _repeat)) {
            _repeat = "1";
        }

        if (!valid_str(_key_map, PARAM_INVALIDFILE, _invalid_file)) {
            _invalid_file = "undef";
        }
    } else {
        return false;
    }

    return NodeResource::load_other()
           && valid_str(_key_map, PARAM_MIN, _min_len)
           && valid_str(_key_map, PARAM_MAX, _max_len)
           && valid_str(_key_map, PARAM_TIMEOUT, _input_timeout)
           && valid_str(_key_map, PARAM_ENDKEY, _end)
           && ("*" == _end || "#" == _end || "#*" == _end || "*#" == _end);
}

std::string NodeGetDigits::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "PlayFile:" << _play_file << ",";
    ostm << "MinLen:" << _min_len << ",";
    ostm << "MaxLen:" << _max_len << ",";
    ostm << "Repeat:" << _repeat << ",";
    ostm << "End:" << _end << ",";
    ostm << "InvalidFile:" << _invalid_file << ",";

    return ostm.str();
}

