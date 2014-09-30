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

#ifndef _FLOW_MANAGER_H_
#define _FLOW_MANAGER_H_

#include "common.h"

/**
* @brief 流程加载类
*   detail description
*
*/
class FlowManager {
public:
public:
    const static char* VAR;       ///<  var变量
    const static char* NODE;      ///<  node变量
public:
    FlowManager();
    virtual ~FlowManager();
public:
    /**
     * @brief 根据流程文件名加载流程
     *
     * @param [in/out] flowname   : const string&
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 17:11:25
    **/
    int32_t load_flow(const string& flowname, flow_t** flow);

    // swap content
    void swap(FlowManager& other) throw();
public:
    // inc flow's refcount
    static int32_t attach_flow(flow_t* flow_in, flow_t** out);

    // dec flow's refcount,
    // if refcount become 0, delete it
    static int32_t detach_flow(flow_t** flow);
private:
    // p = new flow_t
    // p->refcount = 1;
    static int32_t new_flow(flow_t** flow);

    // delete flow's node and variables
    static int32_t free_flow(flow_t** flow);
private:
    map<string, flow_t*> _flow_name_info_map;  //
};

#endif

