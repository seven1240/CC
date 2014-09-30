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
#include "node_playnum.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodePlayNum::NodePlayNum(const uint32_t id, const string& name,
                         const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
    _delay = 0;
}

NodePlayNum::~NodePlayNum(void) {
}

NodeBase* NodePlayNum::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    const char* exit = EXIT_FAIL;
    std::string ret = "";
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    if (_delay != 0) {
        ivr_tools_t::safe_sleeps(_delay);
    }

    std::string playstr;
    std::string callid;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;

    if (parse_expression(_callid, param->name_var_map, callid)
            && parse_expression(_play_str, param->name_var_map, playstr)) {
        IVR_TRACE("%s,delay=%u,playstr=%s",
                  callid.c_str(), _delay, playstr.c_str());
    } else {
        IVR_WARN("parse callid or playstr failed");
        goto END;
    }

    if (!ivr_tools_t::is_all_digit(playstr)) {
        IVR_TRACE("放音字符串不均为数字[%s]", playstr.c_str());
        goto END;
    }

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (0 == strcasecmp(_playtype.c_str(), PARAMITEM_NUMBER)) {
                if (opr->playnum(callid.c_str(), playstr.c_str(), param->vox_base.c_str(), true) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr playnum err(callid: %s,number: %s)", _callid.c_str(), playstr.c_str());
                }
            } else if (0 == strcasecmp(_playtype.c_str(), PARAMITEM_INT32)) {
                if (opr->playnum(callid.c_str(), playstr.c_str(), param->vox_base.c_str(), false) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr playnum err(callid: %s,number: %s)", _callid.c_str(), playstr.c_str());
                }
            }
        } else {
            IVR_WARN("fs_opr_t pointer should not be null");
        }

        fs_mgr_t::instance()->free_opr(&opr);
    } else {
        IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
    }

END:
    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), exit, ret.c_str());

    return _exit_node_map[exit];
}

bool NodePlayNum::load_other() {
    std::string tmp;
    valid_str(_key_map, PARAM_STR, _play_str); //允许为空

    //延时时间设置
    _delay = 0;

    if (valid_str(_key_map, PARAM_DELAY, tmp)) { //允许为空
        if (ivr_tools_t::is_positive_integer(tmp)) {
            _delay = atoi(tmp.c_str());
        }
    }

    //playtype初始化
    _playtype = PARAMITEM_NUMBER;

    if (valid_str(_key_map, PARAM_PLAYTYPE, tmp)) {
        if (0 == strcasecmp(_playtype.c_str(), PARAMITEM_NUMBER)
                || 0 == strcasecmp(_playtype.c_str(), PARAMITEM_INT32)) {
            _playtype = tmp;
        }
    }

    return NodeResource::load_other();
}

const char* NodePlayNum::PARAM_DELAY = "delay";
const char* NodePlayNum::PARAM_INTERRUPT = "allowinterrupt";
const char* NodePlayNum::PARAM_STR = "playstr";
const char* NodePlayNum::PARAM_PLAYTYPE = "playtype";
const char* NodePlayNum::PARAMITEM_NUMBER = "number";
const char* NodePlayNum::PARAMITEM_INT32 = "int32";

std::string NodePlayNum::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "file:" << _play_str << ",delay:" << _delay;
    return ostm.str();
}
