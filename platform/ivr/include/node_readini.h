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

#ifndef _NODE_READINI_H_
#define _NODE_READINI_H_

#include "node_base.h"

class NodeReadIni : public NodeBase {
public:
    NodeReadIni(const uint32_t id, const string& name,
                const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeReadIni(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:
    string _file_name;          //配置文件路径名
    string _session_name;       //session名
    string _map_var_name;       //key-value 变量名

    const static char* PARAM_FILE;
    const static char* PARAM_SECTION;
    const static char* PARAM_VAR;

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
     * @date 2011/09/02 17:42:03
    **/
    std::string leave(const map<string, variable_t>& vars)const;
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
     * @date 2011/09/02 17:42:07
    **/
    std::string enter(const map<string, variable_t>& vars)const;
};

#endif
