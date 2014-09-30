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

#ifndef _NODE_DB_H_
#define _NODE_DB_H_

#include "node_base.h"

class NodeDB : public NodeBase {
public:
    NodeDB(const uint32_t id, const string& name,
           const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeDB(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

private:
    uint32_t _connectid;
    string _sql;
    string _rs_var_name;
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
     * @date 2011/09/06 11:59:17
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
     * @date 2011/09/06 11:59:20
    **/
    virtual std::string leave(const map<string, variable_t>& vars)const ;

    const static char* PARAM_CONNID;
    const static char* PARAM_SQL;
    const static char* PARAM_RSNAME;
};

#endif
