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
#include "node_play.h"
#include "fs_opr.h"
#include "fs_mgr.h"

NodePlay::NodePlay(const uint32_t id, const string& name,
                   const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
    _delay = 0;
}

NodePlay::~NodePlay(void) {
}

NodeBase* NodePlay::run(base_script_t* param) {
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

    std::string playfile, callid;
    fs_opr_t* opr = NULL;
    fw_id_t fs_no;

    if (parse_expression(_callid, param->name_var_map, callid)
            && parse_expression(_play_file, param->name_var_map, playfile)) {
        IVR_TRACE("%s,delay=%u,playfile=%s",
                  callid.c_str(), _delay, (param->vox_base + playfile).c_str());

        playfile = param->vox_base + playfile;
    } else {
        IVR_WARN("parse callid or playfile failed");
        goto END;
    }

    fs_no = param->fid;

    if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
        if (NULL != opr) {
            if (_is_allow_interrupt) {
                if (opr->collect(callid.c_str(), playfile.c_str(), 1, 1, 1, "#") == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr collect failed(callid: %s)", _callid.c_str());
                }
            } else {
                if (opr->play(callid.c_str(), playfile.c_str()) == IVR_SUCCESS) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("opr play failed(callid: %s)", _callid.c_str());
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

bool NodePlay::load_other() {
    std::string tmp;
    valid_str(_key_map, PARAM_FILE, _play_file); //允许为空

    _delay = 0;

    if (valid_str(_key_map, PARAM_DELAY, tmp)) { //允许为空
        if (ivr_tools_t::is_positive_integer(tmp)) {
            _delay = atoi(tmp.c_str());
        }
    }

    _is_allow_interrupt = true;

    if (valid_str(_key_map, PARAM_INTERRUPT, tmp)) { //允许为空
        _is_allow_interrupt = ("0" == tmp ? false : true);
    }

    check_exit(EXIT_INTERRUPT);
    check_exit(EXIT_FILENOTFOUND);
    return NodeResource::load_other();
}

const char* NodePlay::PARAM_DELAY = "delay";
const char* NodePlay::PARAM_INTERRUPT = "allowinterrupt";
const char* NodePlay::PARAM_FILE = "playfile";

std::string NodePlay::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "file:" << _play_file << ",delay:" << _delay << ",allowinterrupt:" << _is_allow_interrupt;
    return ostm.str();
}
