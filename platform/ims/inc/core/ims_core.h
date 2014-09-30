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

#ifndef  __IMS_CORE_H_
#define  __IMS_CORE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <list>
#include <map>
#include <set>
#include <boost/functional/hash.hpp>

#define LEN_8  8
#define LEN_16 16
#define LEN_32 32
#define LEN_64 64
#define LEN_128 128
#define LEN_256 256
#define LEN_512 512

#define IMS_FAIL_GENERAL        -1
#define IMS_SUCCESS             0
#define IMS_FAIL_LOCK           1
#define IMS_FAIL_EXISTS         2
#define IMS_FAIL_NOTEXISTS      3
#define IMS_FAIL_MEM            4
#define IMS_FAIL_INVALID_FSNO   5
#define IMS_FAIL_ALL_BUSY       6
#define IMS_FAIL_CONNECT        7
#define IMS_FAIL_TIMEOUT        8

#define IMS_CONF_FILE ./conf/ims.conf.xml
#define DEFAULT_HOLDON_MUSIC "${sound_prefix}/hold_music.wav"

#define IMS_WAIT_RING_TIMEOUT   30000
#define IMS_WAIT_ANSWER_TIMEOUT 60000

#define SPECIAL_CHANNELID "create empty session by ivr"

typedef uint64_t callid_t;

/**
* @brief session 当前操作
*
*/
enum ims_session_operation_t {
    SOPR_UNKNOWN,
    SOPR_MAKECALL,
    SOPR_HOLD,
    SOPR_RETRIEVE,
    SOPR_CONSULT,
    SOPR_RECONNECT,
    SOPR_TRANSFER,
    SOPR_CONFERENCE,
    SOPR_SINGLESTEPTRANSFER,
    SOPR_LISTEN,
    SOPR_INSERT,
    SOPR_IVRTRANSFER            /* transferAgent被调用时*/
};

/**
* @brief sessiong 创建原因
*
*/
enum ims_session_create_reason_t {
    SCRT_UNKNOWN,
    SCRT_INBOUND_IVR,         ///<  IVR 呼入
    SCRT_INBOUND_NORMAL,      ///<  直接呼入
    SCRT_OUTBOUND_IVR,        ///<  IVR外乎
    SCRT_OUTBOUND_NORMAL      ///<  座席呼出
};

/**
 * @brief state of channel when signaled
 */
enum ims_state_signal_t {
    STATE_UNKNOWN,
    STATE_RING,
    STATE_ANSWER,
};

typedef struct ims_global_data {
    const static uint32_t MAX_SESSION = 2048;         ///<  单台IMS支持的session
    const static uint32_t MAX_REQUEST = 1024;         ///<  最多客户端对象个数
    const static uint32_t DN_SIZE = 64;               ///<  座席分机最大长度
    const static uint32_t MAX_OBJ_PER_SESSION = 16;   ///<  session中各种对象的最多个数
    ///<  任意session最大持续时间24小时, 单位微秒
    const static uint64_t MAX_SESSION_LIFETIME = 24ll * 60 * 60 * 1000000;
    ///<  空session最大持续时间1小时, 单位微秒
    const static uint64_t MAX_EMPTY_SESSION_LIFETIME = 1ll * 60 * 60 * 1000000;
} global_data_t;


struct hashfunctor {
    size_t operator()(const char* pstr) const {
        std::string str(pstr);
        boost::hash<std::string> hash_string;
        return hash_string(str);
    }
};

struct ims_equal {
    /**
     * @brief char * 在stl中的比较函数
     *
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/15 14:01:28
    **/
    inline bool operator()(const char* _1, const char* _2) const {
        if (!_1 && !_2) {
            return true;
        }

        if (!_1 || !_2) {
            return false;
        }

        return strcmp(_1, _2) == 0;
    }
};

#endif  //__IMS_CORE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
