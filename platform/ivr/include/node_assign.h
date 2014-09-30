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

#ifndef _NODE_ASSIGN_H_
#define _NODE_ASSIGN_H_

#include "node_base.h"

class NodeAssign : public NodeBase {
public:
    NodeAssign(const uint32_t id, const string& name,
               const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeAssign(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  const char*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 11:14:15
    **/
    virtual std::string enter(const map<string, variable_t>& vars)const ;
    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  const char*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 11:14:19
    **/
    virtual std::string leave(const map<string, variable_t>& vars)const ;
private:
    string _exp;          ///< node中的计算表达式
    string _result;       ///< node中存放计算结果的变量名称
    const static char* PARAM_EXP;
    const static char* PARAM_RESULT;

};

#endif
