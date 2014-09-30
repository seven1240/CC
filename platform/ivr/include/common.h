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

#ifndef _IVR_COMMON_H_
#define _IVR_COMMON_H_

#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <stdint.h>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <exception>
#include <stdexcept>

//#include <com_log.h>
#include <bgcc.h>

#include "esl.h"
#include "esl_threadmutex.h"

#include "ims/ims_struct.h"

//global macro
#define  SUCCESS  (0)
#define  FAILURE  (1)
#define  MAX_THREAD_NUM  (950)
#define  LOG_PATH  "./conf/"
#define  FLOW_PATH  "./flow/"

#define IMS_SESSION_TAG "IMSDATA"
#define CREATE_SESSION_EMPTY_CALLID "create empty session by ivr"

#define LEN_8  8
#define LEN_16 16
#define LEN_32 32
#define LEN_64 64
#define LEN_128 128
#define LEN_256 256
#define LEN_512 512

#define IVR_IMS_REINIT_TIME                 3

#define IVR_FAIL_GENERAL                   -1
#define IVR_SUCCESS                         0
#define IVR_FAIL_LOCK                       1
#define IVR_FAIL_EXISTS                     2
#define IVR_FAIL_NOTEXISTS                  3
#define IVR_FAIL_MEM                        4
#define IVR_FAIL_INVALID_FSNO               5
#define IVR_FAIL_ALL_BUSY                   6
#define IVR_FAIL_CONNECT                    7
#define IVR_FAIL_TIMEOUT                    8
#define IVR_FAIL_NOIMS                      9
#define IVR_FAIL_IMS_REGIST                10
#define IVR_FAIL_IMS_NOTEXIST              11
#define IVR_FAIL_IMS_ROUTEREQUEST          12
#define IVR_FAIL_IMS_CANCELROUTEREQUEST    13
#define IVR_FAIL_IMS_TRANSAGENT            14
#define IVR_FAIL_IMS_SETASSOCIATEDATA      15
#define IVR_FAIL_IMS_GETASSOCIATEDATA      16
#define IVR_FAIL_IMS_NOMAIN                17
#define IVR_FAIL_IMS_CREATESESSION         18
#define IVR_FAIL_IMS_SESSIONINVALIDATE     19
#define IVR_FAIL_IMS_INFOINVALIDATE        20
#define IVR_FAIL_IMS_AGENTNOTASSIGNED      21
#define IVR_FAIL_IMS_ROUTEREQUEST_REPEATED 22
#define IVR_FAIL_IMS_REQIDINVALIDATE       23
#define IVR_FAIL_IMS_PROXY_FAILED          24
#define IVR_FAIL_IMS_REINIT                25
#define IVR_FAIL_IMS_MAKECALL              26
#define IVR_TRACE(fmt, arg...) do { BGCC_TRACE("ivr", fmt, ##arg); }  while(0)
#define IVR_NOTICE(fmt, arg...) do { BGCC_NOTICE("ivr", fmt, ##arg); }  while(0)
#define IVR_DEBUG(fmt, arg...) do { BGCC_DEBUG("ivr", fmt, ##arg); }  while(0)
#define IVR_WARN(fmt, arg...) do { BGCC_WARN("ivr", fmt, ##arg); }  while(0)
#define IVR_FATAL(fmt, arg...) do { BGCC_FATAL("ivr", fmt, ##arg); }  while(0)

using namespace std;

typedef map<string, string> key_map_t;
typedef map<string, key_map_t> section_map_t;
typedef std::map<std::string, std::string> str2str_map;

typedef uint32_t fw_id_t;     //Freeswitch唯一标志
typedef uint64_t ivr_session_id_t;    //ivr的sessionid

typedef ivr::ReloadFlagT conf_reload_flag_t;
typedef ims::RouteEventT ims_route_eventdata_t;

typedef bgcc::Guard<bgcc::Mutex> locker_t;

/**
 * @brief 数据库连接池
 *   detail description
 *
 */
class DBPool;

/**
 * @brief 流程节点基类
 *   detail description
 *
 */
class NodeBase;

class ThreadPool;

class IvrTimer;

/**
 * @brief 变量类型
 *   detail description
 *
 */
enum var_type_t {
    INT32 = 0,      ///<  整数
    STRING,         ///<  STRING
    RESULTSET,      ///<  结果集
    MAP             ///<  映射
};

/**
 * @brief 变量类型定义
 *   detail description
 *
 */
struct variable_t {
    string name;     ///< 名称
    var_type_t type; ///< 类型
    void* pvalue;    ///< 根据变量的类型 创建不同类型的 对象指针
    string initial;  ///< 初始化值
};

/**
 * @brief流程承载节点
 *   detail description
 *
 */
struct flow_t {
    uint32_t begin_id;                      ///< 流程开始节点编号
    map<uint32_t, NodeBase*>  id_node_map;  ///< 节点映射
    map<string, variable_t> name_var_map;   ///< 脚本中变量的模版
    uint32_t ref_count;                     ///< 脚本引用计数 用于延时释放内存
    time_t last_modify_time;                ///< 最近一次修改时间
    bgcc::Mutex refcmutex;                  ///< mutex for ref_count
};

typedef std::map<std::string, flow_t*> flow_name_map;

struct channel_info_t {
    std::string channel_name;
    std::string channel_id;
    std::string callsource;
};

/**
 * @brief IVR事件基类
 *   detail description
 *
 */
struct ivr_base_event_t {
    // virtual destruct, delete drived class's member objects
    virtual ~ivr_base_event_t() {}

    enum ivr_event_type {
        CALL_EVENT = 0,
        MEDIA_EVENT,
        IMS_EVENT,
        OTHER_EVENT
    };
    ivr_event_type evt_type;
    ivr_session_id_t sessionId;
    uint64_t timestamp;
};

/**
 * @brief IVR呼叫事件
 *   detail description
 *
 */
struct ivr_call_event_t : public ivr_base_event_t {
    enum call_event_name {
        IVR_EVT_ANSWER = 0,     //应答
        IVR_EVT_ALERT,          //振铃
        IVR_EVT_HANGUP,         //挂断
        IVR_EVT_BRIDGE,         //搭接成功
        IVR_EVT_UNBRIDGE,       //取消搭接成功
        IVR_EVT_CHANLE_DESTORY, //Freeswitch拆线
        IVR_EVT_CALLFAIL        //外呼失败
    };

    enum call_event_reason {
        CALL_NORMAL,        //正常外呼/
        CALL_DEST_BUSY,     //对端忙
        CALL_DEST_NOANSWER, //对端无应答
        CALL_REJECTED,      //对端拒绝
        CALL_USER_NOT_REGISTERED,
        CALL_SUBSCRIBER_ABSENT,
        CALL_UNKNOW         //其它原因
    };

    call_event_name evt_name;
    call_event_reason evt_reason;

    string callid;              //事件对应的callid
    string ani;                 //主叫号码
    string dnis;                //被叫号码

    //搭接时使用下面变量，否则为空
    string other_callid;        //另一方通话的callid
    string other_ani;           //另一方通话的主叫号码
    string other_dnis;          //另一方通话的被叫号码
};

/**
 * @brief IVR媒体事件
 *   detail description
 *
 */
struct ivr_media_event_t : public ivr_base_event_t {
    enum media_event_name {
        IVR_EVT_PLAY_END = 100, //播放语音完毕
        IVR_EVT_FILENOTEXIST,   //语音文件不存在
        IVR_EVT_GETDIGIT_SUCC,  //收号成功
        IVR_EVT_GETDIGIT_FAIL,  //收号失败
        IVR_EVT_DTMF,           //用户按键
        IVR_EVT_RECORD_START,   //录音开始
        IVR_EVT_RECORD_END      //录音结束
    };
    enum media_event_reason {
        MEDIA_END,              //正常结束
        MEDIA_GETDIGIT,         //收号
        MEDIA_INVALID_FILE,     //文件异常
        MEDIA_DISCONNECT,       //话路断开
        MEDIA_UNKNOW            //其它原因
    };

    media_event_name evt_name;
    media_event_reason evt_reason;

    string callid;              //媒体话路的callid
    string media_data;          //媒体文件名称
    string digits;              //收号结果
};

/**
 * @brief IVR其它事件
 *   detail description
 *
 */
struct ivr_other_event_t : public ivr_base_event_t {
    enum other_event_name {
        IVR_EVT_TIMEOUT = 200,  //超时事件
        IVR_EVT_UNKNOW          //其它事件
    };
    other_event_name evt_name;
    string data;                //事件数据(超时事件为timerId)
};

struct ivr_ims_event_t : public ivr_base_event_t {
    enum ims_event_name {
        IVR_EVT_IMS_ROUTE_RESPONSE = 300,
        IVR_EVT_IMS_NOT_RESPONSE,
        IVR_EVT_IMS_UNKNOW
    };

    ims_event_name evt_name;
    ims_route_eventdata_t data;
};

typedef queue< ivr_base_event_t* > ivr_event_queue_t;

struct ivr_thread_param_t {
    ThreadPool* pool;               //需要其中的_worker_queue
    ivr_event_queue_t* event_queue;   //该线程分配到的IVR事件队列
    //    sem_t * evt_sem;            //队列信号量
    IvrTimer* timer;                //该线程分配到的计时器
};
/*
struct ivr_task_param_t{
    ivr_event_queue_t * event_queue;  //该线程分配到的IVR事件队列
    sem_t * evt_sem;              //事件队列的信号量
    IvrTimer * timer;               //该线程分配到的计时器
};
*/
struct session_dynamic_resource_t {
    session_dynamic_resource_t() : event_queue(NULL), timer(NULL) { /*, sem(NULL)*/  }
    ivr_event_queue_t* event_queue;   ///<IVR事件队列，session创建后确定
    IvrTimer* timer;                ///<IVR计时器，session创建后确定
    //    sem_t *sem;
};

// timer type: usr timer or system defined timer
enum timer_type_t {
    user_define, // user defined timer
    ims_transagent, // ims trans agent timer
    unknown // other timer
};

/**
 * @brief 流程描述
 *   detail description
 *
 */
struct base_script_t {
    // virtual destruct
    virtual ~base_script_t() {}
    enum script_type_t {
        AUTOBOUND = 0,       ///<外呼类型
        INBOUND = 1,         ///<呼入类型
    };
    string name;          ///<流程名称
    string desc;          ///<流程描述
    string flow_name;     ///<流程文件名称
    string vox_base;      ///<语音文件根路径
    flow_t* flow;         ///<流程节点
    uint32_t type;        ///<流程类型
    map<string, variable_t> name_var_map;   ///<通道中的变量的 副本

    //esl_handle_t*  handle;                  ///<通道中 使用的socket handle
    /** 动态信息，随话路改变 **/
    fw_id_t fid;          ///<Freeswitch编号
    string ani;           ///<主叫号
    string dnis;          ///<被叫号
    string callid;        ///<该呼叫的callid
    ivr_session_id_t session_id;    ///<session id，session创建后确定

    string channel_name;
    string channel_id;
    string callsource; // Freeswitch IP

    IvrTimer* timer;                ///<IVR计时器，session创建后确定

    // ims infomation
    uint32_t imsno; // ims index
    ims_session_id_t imssid; // ims session id
    ims_routerequest_id_t requestId;


    std::string bill_info();
};

/**
 * @brief inbound流程
 *   detail description
 *
 */
struct inbound_script_t: public base_script_t {
    esl_socket_t socket;        ///< 和freeswitch的连接
    struct sockaddr_in* addr;   ///<  sockaddr

    std::string dialdata;

    inbound_script_t(): addr(NULL) {}
    ~inbound_script_t() {
        if (addr) {
            delete addr;
            addr = NULL;
        }
    }
};


/**
 * @brief 自动外呼流程
 *   detail description
 *
 */
struct autorun_script_t: public base_script_t {
    //    vector<freeswitch_info_t> freeswitch_info_vec;      ///<用到的fs信息
    uint32_t autorun_chan_num;                          ///<执行流程的通道数
    uint32_t autorun_interval;                          ///<自启动间隔
    time_t last_startup_time;                           ///<最后一次启动时间
    bool is_write_bill;                                 ///<是否写话单
};

/**
 * @brief 呼入相关的配置
 *   detail description
 *
 */
struct inbound_conf_t {
    map<string, inbound_script_t> dnis_script_map;  ///<所有呼入流程
    inbound_script_t default_script;                ///<默认流程
    uint32_t max_inbound_chan_num;                  ///<呼入最大通道数
    uint32_t max_autodial_chan_num;                 ///<max autodial chan number
    time_t last_modify_time;                        ///<最后一次修改时间
    bool has_default;                               ///<是否配置了默认流程
};

/**
 * @brief 自启动流程相关配置
 *   detail description
 *
 */
struct autorun_conf_t {
    vector<autorun_script_t> autorun_script_vec;///<自启动流程列表
    uint32_t max_autorun_chan_num;              ///<自启动通道最大数量
    time_t last_modify_time;                    ///最后修改日期
};

struct call_data_conf_t {
    string file_name;
    uint32_t generate_interval;
    uint32_t generate_file_size;
    string generate_path;
    string sendto_path;
};

typedef struct _sys_var_t {
    enum {//注意和SYS_VAR的对应关系
        BEGIN = 0,
        ANI = 0,
        DNIS = 1,
        CALLID = 2,
        RECORD_FILE = 3,
        HANGUP_CAUSE = 4,
        CALL_BEGIN_TIME = 5, ///< 呼叫到达平台的时间
        CALL_ANSWER_TIME = 6, ///< 呼叫被接起的时间
        END = 7
    };
} sys_var_t;

struct errorcode_string {
    // get description of error code
    static string tostring(int32_t errorcode);
    //    static int32_t tocode(const string& errorstring);

private:
    static const std::map<int32_t, string>& errormap();
};


extern int32_t g_stopped;
extern sem_t g_stop_sem;

extern string g_server_ip;
extern uint32_t g_server_port;
extern uint32_t g_reload_port;
extern call_data_conf_t g_calldata_conf;

extern inbound_conf_t  g_inbound_conf;
extern autorun_conf_t  g_autorun_conf;

extern pthread_rwlock_t g_inbound_conf_rwlock; // used for lock g_inbound_conf
extern pthread_rwlock_t g_autorun_conf_rwlock; // used for lock g_autorun_conf

extern DBPool* g_dbpool;///< 数据库连接池

extern uint32_t g_inbound_chan_num;
extern uint32_t g_autorun_chan_num;
extern uint32_t g_autodial_chan_num;

extern pthread_rwlock_t g_inbound_chan_rwlock;
extern pthread_rwlock_t g_autorun_chan_rwlock;
extern pthread_rwlock_t g_autodial_chan_rwlock;

extern const char* SYS_VAR[];

extern bool
g_output_esllog; // enable/disable esl log, true: output log information, false: not print
extern time_t g_autorun_script_stamp;   // mark last autorun script loaded time
// every autorun chan thread save the time(st) when it started
//  if st < g_autorun_script_stamp, the thread need stop,
//      because autorun script ust reloaded

#endif
