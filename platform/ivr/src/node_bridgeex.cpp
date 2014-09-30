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

#include "node_bridgeex.h"
#include "fs_opr.h"
#include "fs_mgr.h"

node_bridgeex_t::node_bridgeex_t(const uint32_t id, const string& name,
                                 const string& type, const string& desc, const key_map_t& keymap)
    : NodeResource(id, name, type, desc, keymap) {
}

NodeBase* node_bridgeex_t::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    string caller;
    string called;
    string calltype;
    string bgmfile;
    bool usebgm = true;
    std::string callid;
    fw_id_t fs_no = param->fid;

    void* ptmp = param->name_var_map[SYS_VAR[sys_var_t::CALLID]].pvalue;

    if (ptmp) {
        callid = *(std::string*)ptmp;
    }

    if (strcasecmp(_bgtype.c_str(), PARAMITEM_RING) != 0
            && strcasecmp(_bgtype.c_str(), PARAMITEM_BGM) != 0) {
        IVR_WARN("bgtype error, USE ring");
        usebgm = false;
    } else if (strcasecmp(_bgtype.c_str(), PARAMITEM_RING) == 0) {
        usebgm = false;
    } else if (strcasecmp(_bgtype.c_str(), PARAMITEM_BGM) == 0 && _bgmfile.length() == 0) {
        IVR_WARN("BGM file is null, use ring");
        usebgm = false;
    }

    parse_expression(_bgmfile, param->name_var_map, bgmfile);

    if (true == parse_expression(_caller, param->name_var_map, caller)
            && true == parse_expression(_called, param->name_var_map, called)
            && true == parse_expression(_calltype, param->name_var_map, calltype)) {
        IVR_TRACE("caller=%s,called=%s,bgtype=%s(usebgm:%d),bgmfile=%s", caller.c_str(), called.c_str(),
                  _bgtype.c_str(), usebgm, bgmfile.c_str());

        fs_opr_t* opr = NULL;

        if (fs_mgr_t::instance()->fetch_opr(fs_no, &opr) == IVR_SUCCESS) {
            if (NULL != opr) {
                if (IVR_SUCCESS == opr->bridgeex(callid.c_str(), caller.c_str(), called.c_str(), calltype != "0",
                                                 usebgm, bgmfile.c_str())) {
                    exit = EXIT_SUCC;
                } else {
                    IVR_WARN("bridgeex failed(caller: %s, called: %s)", _caller.c_str(), _called.c_str());
                }

                fs_mgr_t::instance()->free_opr(&opr);
            } else {
                IVR_WARN("fs_opr_t pointer should not be null");
            }
        } else {
            IVR_WARN("fetch opr failed. freeswitch no is %d", fs_no);
        }
    } else {
        IVR_WARN("caller or called parse failed(%s,%s)", _caller.c_str(), _called.c_str());
    }

    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s(bridgeex to %s)",
                  leave(param->name_var_map).c_str(), exit, called.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool node_bridgeex_t::load_other() {
    valid_str(_key_map, PARAM_BGTYPE, _bgtype);
    valid_str(_key_map, PARAM_BGMFILE, _bgmfile);
    return NodeResource::load_other()
           && valid_str(_key_map, PARAM_CALLER, _caller)
           && valid_str(_key_map, PARAM_CALLED, _called)
           && valid_str(_key_map, PARAM_CALLTYPE, _calltype);
}

std::string node_bridgeex_t::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "caller:" << _caller << ",called:" << _called;
    return ostm.str();
}

const char* node_bridgeex_t::PARAM_CALLER = "callernumber";
const char* node_bridgeex_t::PARAM_CALLED = "callednumber";
const char* node_bridgeex_t::PARAM_CALLTYPE = "calltype";
const char* node_bridgeex_t::PARAM_BGTYPE = "bgtype";
const char* node_bridgeex_t::PARAM_BGMFILE = "bgmfile";

const char* node_bridgeex_t::PARAMITEM_BGM = "bgm";
const char* node_bridgeex_t::PARAMITEM_RING = "ring";

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
