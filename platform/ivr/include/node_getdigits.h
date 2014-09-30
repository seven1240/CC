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

#ifndef _NODE_GETDIGITS_H_
#define _NODE_GETDIGITS_H_

#include "node_resource.h"

class NodeGetDigits : public NodeResource {
public:
    NodeGetDigits(const uint32_t id, const string& name,
                  const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeGetDigits(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();

private:
    /*
    uint32_t _min_len;
    uint32_t _max_len;
    uint32_t _repeat;
    uint32_t _input_timeout;
    */
    string _min_len;
    string _max_len;
    string _repeat;
    string _input_timeout;
    string _end;

    string _play_file;
    string _invalid_file;
    const static char* PARAM_MIN;
    const static char* PARAM_MAX;
    const static char* PARAM_REPEAT;
    const static char* PARAM_TIMEOUT;
    const static char* PARAM_FILE;
    const static char* PARAM_INVALIDFILE;
    const static char* PARAM_ENDKEY;

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
     * @date 2011/09/06 15:48:23
    **/
    std::string NodeGetDigits::enter(const map<string, variable_t>& vars)const;

};

#endif
