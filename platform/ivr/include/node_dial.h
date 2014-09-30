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

#ifndef _NODE_DIAL_H_
#define _NODE_DIAL_H_

#include "node_resource.h"

class NodeDial : public NodeResource {
public:
    NodeDial(const uint32_t id, const string& name,
             const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeDial(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

private:
    string _called_number;//被叫号码
    string _caller_number;//显示的主叫
    string _calltype;
    const static char* PARAM_CALLED;
    const static char* PARAM_CALLER;
    const static char* PARAM_CALLTYPE;

    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/06 14:55:16
    **/
    std::string enter(const map<string, variable_t>& vars)const;

};

#endif
