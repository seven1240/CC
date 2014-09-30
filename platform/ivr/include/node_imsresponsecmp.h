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

#include "node_resource.h"
#include "ims/ims_mgr.h"

#ifndef _IVR_NODE_IMS_RESPONSE_CMP_
#define _IVR_NODE_IMS_RESPONSE_CMP_

// test wait event node's data is ok
//  if ok exit from success, and agent is the agent_no from acd
//  else exit from failure
class NodeRequestResponseCompare : public NodeResource {
public:
    NodeRequestResponseCompare(const uint32_t id, const string& name,
                               const string& type, const string& desc, const key_map_t& keymap);

    virtual ~NodeRequestResponseCompare();

public:
    // run this node
    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:
    // find exit, and return next node
    NodeBase* _find_exit_node(base_script_t* param, const char* exit);
private:
    // get information when enter node
    std::string enter(const map<string, variable_t>& vars) const;
    std::string leave(const map<string, variable_t>& vars) const;
private:
    bool _get_values(const string& input, ims_routerequest_id_t& requestid, int32_t& reason,
                     string& agent);
private:
    // response of ims, get from waitevent node's data property
    string _response;
    string _agent;
private:
    static const char* PARAM_RESPONSE;
    static const char* PARAM_AGENT;
};

#endif
