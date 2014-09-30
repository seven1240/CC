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

#ifndef _IVR_NODE_TRANSAGENT_H_
#define _IVR_NODE_TRANSAGENT_H_

#include "node_resource.h"
#include "ims/ims_mgr.h"

// send cmd to ims: trans agent
//  if success, ivr will lost the control of the channel(will not receive event from fs and can't send cmd to fs)
class NodeTransAgent : public NodeResource {
public:
    NodeTransAgent(const uint32_t id, const string& name,
                   const string& type, const string& desc, const key_map_t& keymap);

    virtual ~NodeTransAgent();

public:
    // run this node
    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:
    // convert string value to ims_transtype_t
    bool _get_type(const string& v, ims_transtype_t& ttype);

    // find exit, and return next node
    NodeBase* _find_exit_node(base_script_t* param, const char* exit);
private:
    // get information when enter node
    string enter(const map<string, variable_t>& vars) const;
private:
    // trans type: TT_INSTANT, TT_RING, TT_ANSWER
    string _transtype;
    std::string _disable_event;
private:
    static const char* PARAM_TRANSTYPE;
    static const char* PARAM_NOEVENT;
};

#endif
