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

#ifndef APCOMMON_H
#define APCOMMON_H

#ifdef _WIN32
#include <hash_set>
#include <hash_map>
using namespace stdext;
#else
#include <ext/hash_map>
#endif

#include <bgcc.h>
#include <acd.h>


#ifdef _WIN32
const char APCONFIG[]    = "conf\\Ap.cfg";
const char APLOGCONFIG[] = "conf\\Aplog.cfg";
#else
const char APCONFIG[]    = "conf/Ap.cfg";
const char APLOGCONFIG[] = "conf/Aplog.cfg";

using namespace __gnu_cxx;  //for hash_map
namespace __gnu_cxx {
template<> struct hash< std::string > {
    size_t operator()(const std::string& x) const {
        return hash< const char* >()(x.c_str());
    }
};
}
#endif

#ifdef _WIN32
#define int64ld "I64d"
#define uint64ld "U64d"
#else
#define int64ld "ld"
#define uint64ld "lu"
#endif

#include "Queue.h"
using namespace acd;

#define CALLBACKTHREADNUM    4
#define CHECKHBTHREADNUM     2

/**
 * @brief   AP与ACD的连接状态
 * @see
 * @note
 * @author  caozhenxing(caozhenxing@baidu.com)
 * @date    2012年06月28日 12时59分21秒
 */
enum APCONNACDSTATE {
    AP_CONNACD_MASTER,
    AP_CONNACD_SLAVE,
    AP_CONNACD_BACKING,
    AP_CONNACD_UNKNOW,
};


/**
 * @brief   AP保存的agentbar信息，用于回调事件推送
 * @see
 * @note
 * @author  caozhenxing(caozhenxing@baidu.com)
 * @date    2012年06月28日 13时03分12秒
 */
struct AgentData {
    std::string agentId;            /*坐席工号，并唯一标示一个agentbar连接*/
    std::string agentDn;            /*座席使用的电话号码*/
    std::string agentPwd;           /*座席签入的密码*/
    StatusChangeT statusChangetype; /*挂断后状态（自动示闲、自动示忙）*/
    bool autoAnswer;                /*挂断后，从示闲或示忙状态到后处理的时间间隔，默认5秒*/
    bool fcSignin;                  /*坐席已签入，是否强制签出后迁入 */
    std::string skill;              /*技能和技能级别描述*/
    int64_t handle;
    int32_t flag;                   /*表示坐席是否signout*/
    int64_t timestamp;              /*标示至flag的时间*/
    std::string agentIP;
    std::string proxyname;
    std::string proxyname_old;
};

typedef hash_map<std::string, AgentData*> MapAgentIdDataType; /*坐席工号、连接代理数据*/

/**
 * @brief   事件队列结构体，用于发送回调事件
 * @see
 * @note
 * @author  caozhenxing(caozhenxing@baidu.com)
 * @date    2012年06月28日 14时05分06秒
 */
struct ApEventQ {
    Queue<AgentEventT > _qEventCall;
    Queue<MediaEventT> _qEventMedia;
    Queue<RouteEventT> _qEventRoute;
    Queue<OtherEventT > _qEventOther;
};

typedef struct ApEventQ ApEventQT;

#endif // APCOMMON_H

