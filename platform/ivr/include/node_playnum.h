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

#ifndef _NODE_PLAYNUM_H_
#define _NODE_PLAYNUM_H_

#include "node_resource.h"

class NodePlayNum : public NodeResource {
public:
    NodePlayNum(const uint32_t id, const string& name,
                const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodePlayNum(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:

    string _play_str;
    uint32_t _delay;          ///< 开始放音的延时
    string _playtype;         ///<播放类型：NUMBER或INT32
    typedef enum {
        RES_SUCC = 0,
        RES_FAIL,
        RES_FILENOTFOUND,
        RES_INTERRUPT,
        RES_USER_HANGUP
    } PLAY_RESULT;

    const static char* PARAM_DELAY;       ///<
    const static char* PARAM_INTERRUPT;   ///<
    const static char* PARAM_STR;         ///<
    const static char* PARAM_PLAYTYPE;    ///<
    const static char* PARAMITEM_NUMBER;
    const static char* PARAMITEM_INT32;

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
     * @date 2011/09/06 15:24:52
    **/
    std::string enter(const map<string, variable_t>& vars)const;
};

#endif
