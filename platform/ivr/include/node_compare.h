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

#ifndef _NODE_COMPARE_H_
#define _NODE_COMPARE_H_

#include "node_base.h"

class NodeCompare : public NodeBase {
public:
    NodeCompare(const uint32_t id, const string& name,
                const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeCompare(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

private:
    bool parse_logic(string exp, map<string, variable_t>& name_var_map);
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
     * @date 2011/09/02 16:25:47
    **/
    virtual std::string enter(const map<string, variable_t>& vars)const ;
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
     * @date 2011/09/02 16:25:49
    **/
    virtual std::string leave(const map<string, variable_t>& vars)const ;

private:
    string _exp;
    const static char* STR_E;
    const static char* STR_NE;
    const static char* STR_L;
    const static char* STR_LE;
    const static char* STR_G;
    const static char* STR_GE;

    const static char* GE;
    const static char* LE;
    const static char* NE;

    const static char* L;
    const static char* G;
    const static char* E;

    const static char* PARAM_EXP;

};

#endif
