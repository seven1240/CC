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

#ifndef  __NODE_FACTORY_H_
#define  __NODE_FACTORY_H_

#include "common.h"
#include "node_base.h"

/**
 * @brief 节点创建工厂
 *   detail description
 *
 */
class node_factory {
public:
    /**
     * @brief 创建特定类型的节点
     *
     * @param [in/out] id   : const uint32_t
     * @param [in/out] name   : const string&
     * @param [in/out] type   : const string&
     * @param [in/out] desc   : const string&
     * @param [in/out] keymap   : const key_map_t&
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 18:30:21
     **/
    static NodeBase* create_node(const uint32_t id,
                                 const string& name, const string& type,
                                 const string& desc, const key_map_t& keymap);

private:
    const static char* NODE_ANSWER;
    const static char* NODE_HANGUP;
    const static char* NODE_PLAY;
    const static char* NODE_RECORD;
    const static char* NODE_DIGIT;
    const static char* NODE_DIAL;
    const static char* NODE_BRIDGE;
    const static char* NODE_ASSIGN;
    const static char* NODE_COMP;
    const static char* NODE_DB;
    const static char* NODE_HTTP;
    const static char* NODE_INI;
    const static char* NODE_BRIDGEEX;
    const static char* NODE_JSONGET;
    const static char* NODE_PLAYNUM;

    const static char* NODE_WAITEVENT;
    const static char* NODE_REGTIMER;
    const static char* NODE_STOPTIMER;
    const static char* NODE_WRITELOG;
    const static char* NODE_STOPMEDIA;
    const static char* NODE_STOPRECORD;
    const static char* NODE_JSONGET_ARRAY;
    const static char* NODE_JSONGET_ARRAYLEN;

    const static char* NODE_REQUEST_AGENT;
    const static char* NODE_TRANS_AGENT;
    const static char* NODE_CANCEL_AGENT;
    const static char* NODE_SET_ASSOCIATEDATA;
    const static char* NODE_GET_ASSOCIATEDATA;
    const static char* NODE_REQUEST_RESULT;

    const static char* NODE_WHATWEEKDAY;
    const static char* NODE_MAKECALL;
};

#endif  //__NODE_FACTORY_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
