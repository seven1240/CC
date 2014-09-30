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

#ifndef _IVR_NODE_REQUESTAGENT_H_
#define _IVR_NODE_REQUESTAGENT_H_

#include "node_resource.h"
#include "ims/ims_mgr.h"

// request agent
//  find an ims to create a new ims session(if sessionid existed, use it)
//  use the ims to call routerequest, ims will use an ims route event to feedback
//  normally, there is a waitevent node after this node(_Success exit) to receive response from ims
class NodeRequestAgent : public NodeResource {
public:
    NodeRequestAgent(const uint32_t id, const string& name,
                     const string& type, const string& desc, const key_map_t& keymap);

    virtual ~NodeRequestAgent();

public:
    // run this node
    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:
    void _new_request_timer(base_script_t* param, int32_t timeout, ims_routerequest_id_t orgid,
                            ims_routerequest_id_t curid);

    // find exit, and return next node
    NodeBase* _find_exit_node(base_script_t* param, const char* exit);

    // get request type
    bool _get_reqType(const std::string& strtype, ims_routerequest_type_t& reqType) const;
private:
    // get information when enter node
    std::string enter(const map<string, variable_t>& vars) const;
private:
    // if after _timeout sec, no free agent was found, ims will send a timeout message
    string _timeout;

    // if got an agent, but don't use it in _valid_time, the agent will be free(flow can't use it)
    string _valid_time;

    string _reqType;
    string _reqArgs;

    std::string _callee;
    std::string _caller;

    // reverse
    string _buffer;

    // before send request message, ivr will play a music
    string _filename;
private:
    static const char* PARAM_FILENAME;
    static const char* PARAM_TIMEOUT;
    static const char* PARAM_VALIDTIME;
    static const char* PARAM_REQTYPE;
    static const char* PARAM_REQARGS;
    static const char* PARAM_BUFFER;
    static const char* PARAM_CALLER;
    static const char* PARAM_CALLEE;
};

#endif
