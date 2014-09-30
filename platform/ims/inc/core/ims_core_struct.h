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

#ifndef  __IMS_CORE_STRUCT_H_
#define  __IMS_CORE_STRUCT_H_

#include <boost/pool/object_pool.hpp>
#include <boost/unordered_map.hpp>
#include <bgcc.h>
#include "session_thread.h"
#include "ims_conf.h"
#include "ims_tool.h"
#include "ims_core_request.h"
#include "ims_thread.h"
#include "ims_obj_pool.h"
#include "common.h"
/**
* @brief IMS 通道对象
*
*/
typedef struct ims_channel {
    char name[LEN_64 + 1];       /**< channel name(dn or custnumber)*/
    char id[LEN_64 + 1];         /**< unique-id      */

    ims::CallStateT callstate;        /**<        */
    ims::MediaStateT mediastate;
    uint64_t create_time;
    ims_channel(const char* name_, const char* id_,
                ims::CallStateT callstate_) {
        name[0] = '\0';
        id[0] = '\0';
        name[LEN_64] = '\0';
        id[LEN_64] = '\0';
        create_time = ims_tool_t::get_timestamp_ms();

        if (name_) {
            strncpy(name, name_, LEN_64);
        }

        if (id_) {
            strncpy(id, id_, LEN_64);
        }

        callstate = callstate_;
        //mediastate=mediastate_;
    }
} ims_channel_t;


struct ims_runtime;
struct ims_session;
typedef struct ims_runtime ims_runtime_t;
typedef struct ims_session ims_session_t;

/**
* @brief IMS 呼叫对象
*   IMS会叫对象，每个call包含 1+ 个通道
*
*/
typedef struct ims_call {
    char ani[LEN_32 + 1];
    char dnis[LEN_32 + 1];
    std::list<const char*> chls;
    bool internal;

    ims_call() {
        ani[0] = '\0';
        dnis[0] = '\0';
        ani[LEN_32] = '\0';
        dnis[LEN_32] = '\0';
        internal = false;
    }
} ims_call_t;

/**
* @brief IMS session 对象
*   IMS session,一个session包含 0+ call，1+ channel
*   IMS 的核心对象
*/
struct ims_session {
    friend class ims_obj_pool<ims_session_t>;
    friend class ims_session_manager_t;
private:
    ims::SessionIdT id;
    uint64_t create_time;         /**< 创建时间       */
    uint32_t fs_no;               /**< 所属Freeswitch编号      */
    boost::object_pool<ims_channel_t>*
    pims_channel_pool;         /**<用于创建session内自己都对象,字符串、通道etc. */
    boost::object_pool<ims_call_t>* pims_call_pool;
    boost::object_pool<std::string>* pstring_pool;
    ims::ReqIdT reqid;            /**< 所属客户端       */
    char oricaller[LEN_64 + 1];
    char oricalled[LEN_64 + 1];

    ims_session_create_reason_t create_reason;        /**< 创建原因         */
    ims_session_operation_t cur_operation;            /**<  当前执行的操作  */
    char cur_opr[LEN_64 + 1];
    ims::session_thread_ptr thrd;                     /**<  处理事件的线程  */

    bgcc::Mutex mutex;


    /**< 运行过程需要保存的业务数据，目前用来保存会议相关的信息       */
    boost::unordered_map<const char* , const char*, hashfunctor, ims_equal> self_rundata;
    boost::unordered_map<const char* , const char*, hashfunctor, ims_equal>
    calldata;         /**< 随路数据 */

    std::map<callid_t, ims_call_t*> calls;         /**<   所有的call     */
    typedef boost::unordered_map<const char*, ims_channel_t*, hashfunctor, ims_equal> map_str2chl_t;
    map_str2chl_t channels;       /**< 所有都通道      */

    ims_session() {
        //channels.create(global_data_t::MAX_OBJ_PER_SESSION);
        //calldata.create(global_data_t::MAX_OBJ_PER_SESSION);
        //calls.create(global_data_t::MAX_OBJ_PER_SESSION);
        //self_rundata.create(global_data_t::MAX_OBJ_PER_SESSION);
    }

    ~ims_session() {
        //channels.destroy();
        //calldata.destroy();
        //calls.destroy();
        //self_rundata.destroy();
    }

    void init(uint32_t fs_no_, ims::ReqIdT reqid_, ims_session_create_reason_t reason,
              ims::session_thread_ptr thrd_) {
        fs_no = fs_no_;
        reqid = reqid_;
        create_reason = reason;
        thrd = thrd_;
        create_time = ims_tool_t::get_timestamp_ms();
        id = ims_tool_t::get_sessionid(fs_no);

        thrd->attach_session(id);

        pims_channel_pool = new boost::object_pool<ims_channel_t>();
        pims_call_pool = new boost::object_pool<ims_call_t>();
        pstring_pool = new boost::object_pool<std::string>();

        oricalled[0] = '\0';
        oricaller[0] = '\0';
        cur_opr[0] = '\0';

        oricalled[LEN_64] = '\0';
        oricaller[LEN_64] = '\0';
        cur_opr[LEN_64] = '\0';
    }

    void uninit() {
        thrd->detach_session(id);
        channels.clear();
        calldata.clear();
        calls.clear();
        self_rundata.clear();

        // boost release memory of bject_pool
        delete pims_channel_pool;
        delete pims_call_pool;
    }
};

/**
* @brief 路由相关信息
*   路由对象
*
*/
typedef struct ims_route_info {
    ims::SessionIdT         sessionid;
    ims::RouteRequestIDT    requestId;
    ims::CallIdT            callid;
    ims::ReqIdT             reqid;
    ims::ReqIdT             dest_reqid;
    std::string             targetUri;
    ims::ServiceTypeT       destService;
    ims::RouteRequestTypeT  requestType;
    std::string             requestArgs;
    std::string             callerDn;
    std::string             calleeDn;
    int32_t                 validtime;
    int32_t                 timeout;
    int32_t                 level;
    uint64_t                timestamp;
    std::string             buffer;

    bgcc::Semaphore*        psema;   //semphore for CHANNEL_PROGRESS
    volatile ims_state_signal_t      state_signal;
    ims_route_info() {
        psema = NULL;
        state_signal = STATE_UNKNOWN;
    }
} ims_route_info_t;

typedef boost::unordered_map<const char* , char(*) [global_data_t::DN_SIZE], hashfunctor, ims_equal>
string_map;

/**
* @brief 客户端对象
*   客户端对象,每个客户端创建一个对象
*
*/
typedef struct req_info {
    std::string conn_info;
    ims::ims_thread_t* thread;
    string_map agent_dn;
    string_map accessno;
    bool is_master;
    req_info() {
        //agent_dn.create(global_data_t::MAX_SESSION);
        //accessno.create(global_data_t::MAX_SESSION);
        is_master = false;
    }

    ~req_info() {
        //agent_dn.destroy();
        //accessno.destroy();
    }
} req_info_t;

struct runtime_pool_t {
    boost::object_pool<ims_conf_server_t> conf_server_pool;
    boost::object_pool<ims_conf_acl_node_t> conf_acl_pool;
    boost::object_pool<ims_conf_gw_node_t> conf_gw_pool;
    boost::object_pool<ims_conf_route_node_t> conf_route_pool;
    boost::object_pool<std::string> string_pool;

    boost::object_pool<req_info_t> req_info_pool;
    boost::object_pool<ims::ims_thread_t> ims_thread_obj_pool;
};
/**
 * @brief 整个进程唯一一个该对象
 *   进程运行过程中所有配置都信息、锁信息
 *
 */
struct ims_runtime {
    friend class ims_session_manager_t;
private:
    bool isrunning;

    mutable bgcc::Mutex mutex;
    uint64_t max_session;         /**< 配置都最大允许同时支持session*/
    uint64_t session_count;       /**< 当前活动的session       */
    uint64_t session_accu;        /**< 启动之后的所有session   */
    uint64_t starttime;           /**< 系统启动时间      */


    runtime_pool_t pool;          /**< 用于创建自己内部都所有数据*/

    typedef boost::unordered_map<const char*, ims::ReqIdT, hashfunctor, ims_equal> map_monitord_t;
    pthread_rwlock_t monitord_dn_lock;
    map_monitord_t monitord_dn;                                         ///<  监控的所有座席分机

    pthread_rwlock_t monitord_accessno_lock;
    map_monitord_t monitord_accessno;                                   ///<  监控的所有IVR介入吗

    pthread_rwlock_t req_mgr_lock;
    std::map<ims::ReqIdT, req_info_t*> req_mgr;                    ///<  客户端对象容器

    pthread_rwlock_t route_mgr_lock;
    std::map<ims::RouteRequestIDT, ims_route_info_t> route_mgr;     ///<  路由请求容器
    std::map<ims::SessionIdT, ims::RouteRequestIDT> sessionId2requestId; /*ssionid  requestId */

    pthread_rwlock_t config_lock;
    ims_conf_t config;

    ims_runtime() {
        session_count = 0;
        session_accu = 0;
        max_session = global_data_t::MAX_SESSION;
        isrunning = true;

        starttime = ims_tool_t::get_timestamp_ms();
    }
    ~ims_runtime() {
    }

    bool inc_session() {
        bgcc::Guard<bgcc::Mutex> lock(&mutex);

        if (lock.is_locked()) {
            ++session_count;
            ++session_accu;
            return true;
        }

        return false;
    }
    bool dec_session() {
        bgcc::Guard<bgcc::Mutex> lock(&mutex);

        if (lock.is_locked()) {
            --session_count;
            return true;
        }

        return false;
    }
};

#endif  //__IMS_CORE_STRUCT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
