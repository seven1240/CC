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

#ifndef  __IMS_CORE_SESSION_MGR_H_
#define  __IMS_CORE_SESSION_MGR_H_

#include <boost/unordered_map.hpp>
#include <vector>
#include "fs_struct.h"
#include "ims_obj_pool.h"
#include "ims_core_struct.h"
#include "ims_thread.h"
/**
 * @brief 整个进程唯一一个该对象
 *   detail description
 *
 */
class ims_session_manager_t {
private:
    pthread_rwlock_t session_table_lock;
    std::map<ims::SessionIdT, ims_session_t*>
    session_table;      /**< 这个session启动直接new出来，用的时候获取       */
    pthread_rwlock_t channel_table_lock;
    /**< all channel,session增加、删除channel直接修改       */
    typedef boost::unordered_map<const char*, ims::SessionIdT, hashfunctor, ims_equal> map_str2int_t;
    map_str2int_t channel_table;
    map_str2int_t channelname_table;
    ims_runtime_t runtime;

    ims_obj_pool<char[global_data_t::DN_SIZE]> dn_pool; ///< 座席分机 对象池
    ims_obj_pool<ims_session_t> session_pool;           ///< session 对象池

private:
    /**
     * @brief 根据sessionid获取当前链接
     *
     * @param [in/out] id   : ims::SessionIdT
     * @return  ims_request_t*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/22 14:07:30
    **/
    ims_request_t* get_request(ims::SessionIdT id);

    ims_session_manager_t() {
        runtime.isrunning = true;
        //session_table.create(global_data_t::MAX_SESSION );
        //channel_table.create(global_data_t::MAX_SESSION);
        //channelname_table.create(global_data_t::MAX_SESSION);
        dn_pool.init(global_data_t::MAX_SESSION);
        session_pool.init(global_data_t::MAX_SESSION);
    }
    ~ims_session_manager_t() {
        session_pool.uninit();
        dn_pool.uninit();
    }

public:
    static ims_session_manager_t* instance() {
        static ims_session_manager_t mgr;
        return &mgr;
    }
    //////////////////////session ////////////////////////
    bool create_session(uint32_t fs_no,
                        ims::ReqIdT reqid,
                        ims_session_create_reason_t reason,
                        ims::session_thread_ptr thrd,
                        const char* oricaller,
                        const char* oricalled,
                        ims::SessionIdT& id);

    /// remove a empty session
    bool remove_session(ims::SessionIdT id);

    /**
     * @brief
     *    destroy_session can remove non-empty session. Firstly destroying the call and channel
     *    inside, and then call this->remove_session()
     *
     * @return  ture if the session successfully removed or not existed at all
     * @author  dangdawei(dangdawei@baidu.com)
     * @date    2014-2-14
     */
    bool destroy_session(ims::SessionIdT id);
    bool locate_session(const char* channelid, ims::SessionIdT& id);
    bool locate_sessionbyname(const char* channenname, ims::SessionIdT& id);
    bool update_session_operation(ims::SessionIdT id, ims_session_operation_t operation,
                                  const char* opr = NULL);
    bool get_session_operation(ims::SessionIdT id, ims_session_operation_t& operation, char* opr = NULL,
                               uint32_t len = 0);
    bool get_session_operator(ims::SessionIdT id, std::string& opr);
    bool save_session_data(ims::SessionIdT id, const char* key, const char* val);
    bool get_session_data(ims::SessionIdT id, const char* key, char* val, uint32_t val_len);

    /**
     * @brief clear dead session
     *        definition of dead session:
     *        1. empty session lasts for more than one hour
     *        2. any session lasts for more than 24 hours
     *
     * @author  dangdawei(dangdawei@baidu.com)
     * @date    2013年09月23日 17时14分42秒
     */
    void clear_dead_session();
    /**
     * @brief s是否是由IVR呼入创建的session
     *
     * @param [in/out] id   : ims::SessionIdT
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/12/09 12:11:54
    **/
    bool is_inbound_session(ims::SessionIdT id);

    /**
     * @brief 是否是由IVR呼入 或呼出创建的session
     *
     * @param [in/out] id   : ims::SessionIdT
     * @return  bool
     * @author  dangdawei
     * @date 2012/7/06 10:06:24
    **/
    bool is_IVRinbound_session(ims::SessionIdT id);
    bool is_IVRoutbound_session(ims::SessionIdT id);

    /**
     * @brief 是否已经在处理一个 routerequest
     *
     * @param [in/out] id   : ims::SessionIdT
     * @return  bool
     * @author  dangdawei
     * @date 2012/7/06 10:36:24
    **/
    bool is_valid_request(ims::SessionIdT id);

    bool update_create_reason(ims::SessionIdT id, ims_session_create_reason_t reason);

    //////////////////////channel ////////////////////////
    bool create_channel(ims::SessionIdT id,
                        const char* id, const char* name,
                        ims::CallStateT callstate = ims::CallStateT::SG_UnknownState,
                        ims::MediaStateT mediastate = ims::MediaStateT::MG_UnknownState);
    bool destroy_channel(const char* channelid);
    bool locate_channel(ims::SessionIdT id, const char* channel_name, char* channelid,
                        uint32_t channelid_len);
    bool get_channelnamebyid(ims::SessionIdT id, const char* chlid, std::string& name);
    bool remove_channelfromcall(ims::SessionIdT id, callid_t callid, const char* chlid);

    bool find_other_hangup(ims::SessionIdT id, callid_t callid, const char* self_chlid);

    /**
     * @brief 获取最后一个加入session都通道
     *
     * @param [in/out] id   : ims::SessionIdT
     * @param [in/out] chl_name   : std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/30 20:32:53
    **/
    bool locate_lastchannel(ims::SessionIdT id, std::string& chl_name);
    /**
     * @brief 根据channel name 找到和该channel关联call的所有channel
     *
     * @param [in] id   : ims::SessionIdT
     * @param [in] my_name   : const char*
     * @param [out] my_id  : char *
     * @param [in] myid_len   : uint32_t
     * @param [out] other_ids   : std::list<const char* >
     * @param [in] callid : callid_t
     * @return  bool
     * @retval
     * @see
     * @note 如果发起方存在于多个call，需要指定callid，否则返回失败
     * @author chenyuzhen
     * @date 2011/11/30 13:37:31
    **/
    bool locate_otherchannel(ims::SessionIdT id, const char* my_name,
                             std::list<const char*>& other_ids,
                             callid_t callid,
                             char* my_id = NULL,
                             uint32_t myid_len = 0);

    bool locate_otherchannel(ims::SessionIdT id, callid_t callid, const char* my_id,
                             std::list<const char*>& other_ids);

    bool update_channel_call(const char* channelid, callid_t callid);
    bool update_channel_callstate(const char* channelid, ims::CallStateT state);
    bool get_channel_callstate(const char* channelid, ims::CallStateT& state);
    bool get_channel_mediastate(const char* channelid, ims::MediaStateT& state);
    bool update_channel_mediastate(const char* channelid, ims::MediaStateT state);
    bool get_channelsbysession(ims::SessionIdT id, std::list<const char*>& chls);
    bool get_channelsbycall(ims::SessionIdT id, callid_t callid, std::list<const char*>& chls);
    int32_t get_channels_size(ims::SessionIdT id);

    //////////////////////call ///////////////////////////
    bool create_call(ims::SessionIdT id, const char* channelid1, const char* channelid2,
                     callid_t& callid);
    bool destroy_call(ims::SessionIdT id, callid_t callid);

    bool update_call_ani(ims::SessionIdT id, callid_t callid, const char* ani);
    bool update_call_dnis(ims::SessionIdT id, callid_t callid, const char* dnis);
    bool get_call_info(ims::SessionIdT id, callid_t callid, std::string& ani, std::string& dnis);

    bool locate_call(const char* channelid, std::list<callid_t>& calls);
    bool locate_call(const char* channelid, callid_t& callid);
    bool locate_call(ims::SessionIdT id, std::list<callid_t>& calls);
    bool locate_othercall(ims::SessionIdT id, callid_t callid, callid_t& other_callid);
    bool update_call_internal(ims::SessionIdT id, callid_t callid, bool internal);
    bool is_internal_call(ims::SessionIdT id, callid_t callid);
    bool is_dead_call(ims::SessionIdT id, callid_t callid);
    uint32_t get_call_size(ims::SessionIdT id, callid_t callid);

    bool get_callercalled(ims::SessionIdT id, std::string& fist_dn, std::string& second_dn);
    bool set_callercalled(ims::SessionIdT id, const std::string& fist_dn, const std::string& second_dn);
    /**
     * @brief 根据通道名称，获取相关的call
     *
     * @param [in/out] channelname   : const char*
     * @param [in/out] calls   : std::list<callid_t>&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/30 14:21:45
    **/
    bool locate_callbyname(ims::SessionIdT id, const char* channelname, std::list<callid_t>& calls,
                           char* self_id = NULL, uint32_t len = 0);
    bool locate_callbyname(ims::SessionIdT id, const char* channelname, callid_t& callid,
                           char* self_id = NULL, uint32_t len = 0) {
        std::list<callid_t> calls;

        if (locate_callbyname(id, channelname, calls, self_id, len) && calls.size() > 0) {
            callid = calls.front();
            return true;
        }

        return false;
    }

    ////////////////////////////sef run data ////////////////////////////
    bool add_rundata(ims::SessionIdT id, const char* key, const char* val);
    bool get_rundata(ims::SessionIdT id, const char* key, char* val = NULL, uint32_t val_len = 0);
    bool del_rundata(ims::SessionIdT id, const char* key);

    ////////////////////////add event to event processer/////////////////
    bool add_event(ims::SessionIdT id, fs_event_t& event);
    /**
      * @brief 手动添加事件
      *
      * @param [in/out] id   : ims::SessionIdT
      * @param [in/out] event   : const char* CHANNEL_HANGUP/CHANNEL_DESTROY
      * @return  bool
      * @retval
      * @see
      * @note
      * @author chenyuzhen
      * @date 2012/11/06 11:09:03
     **/
    bool add_event(ims::SessionIdT id, const char* event);
    bool add_imsevent_media(ims::SessionIdT id, ims::MediaEventT& event);
    bool add_imsevent_call(ims::SessionIdT id, ims::CallEventT& event);
    bool add_imsevent_other(ims::SessionIdT id, ims::OtherEventT& event);

    ////////////////////////add event to /////////////////

    ////////////////////////manual session ////////////////
    /**
     * @brief FW断连之后,需要手动模拟生成相关挂机事件
     *
     * @param [in] fw_no   : uint32_t 发生断连的FW 编号
     * @param [out] ids    : std::vector 该FW上的所有session
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/05 17:05:49
    **/
    bool on_fw_disconn(uint32_t fw_no, std::vector<ims::SessionIdT>& ids);

    ////////////////////////runtime ////////////////

    bool rt_add_dn(const char* dn, ims::DnTypeT type, ims::ReqIdT reqid);
    bool rt_del_dn(const char* dn, ims::DnTypeT type);
    bool rt_query_dn(const char* dn, ims::DnTypeT, ims::ReqIdT* reqid = NULL);

    bool rt_add_req(ims::ReqIdT reqid, const std::string& conninfo);
    bool rt_del_req(ims::ReqIdT reqid);
    bool rt_query_req(ims::ReqIdT reqid);
    /**
     * @brief update reqinfo->is_master
     *
     * @param reqid   : ims::ReqIdT
     * @param info    : std::string only can be("master" or "slave") case sensitive
     * @ return       : bool
     * @ author       : dangdawei
     * @ date         : 2013/1/21
    **/
    bool rt_update_reqstate(ims::ReqIdT reqid, const std::string& info);
    /**
     * @brief  return true if the master acd connect to ims
     *
     * @param reqid   : ims::ReqIdT&   if find one return it's reqid
     * @param type    : ims::ServiceTypeT  currently only ServiceACD
     * @ return       : bool
     * @ author       : dangdawei
     * @ date         : 2013/1/21
    **/
    bool rt_query_register_service(ims::ServiceTypeT, ims::ReqIdT& reqid);
    bool rt_add_imsevent_route(ims::ReqIdT reqid, ims::RouteEventT& event);

    bool rt_add_route(ims::RouteRequestIDT, const ims_route_info_t&);
    bool rt_update_route(ims::RouteRequestIDT, const ims_route_info_t&);

    bool rt_query_route(ims::RouteRequestIDT, ims_route_info_t&, bool del = false);
    bool rt_query_session_route(ims::SessionIdT, ims_route_info_t&, bool del = false);

    bool rt_del_route(ims::RouteRequestIDT);
    bool rt_del_session_route(ims::SessionIdT);

    //bool rt_route_wait_ring(ims::RouteRequestIDT);
    //bool rt_route_signal_ring(ims::RouteRequestIDT);
    uint32_t get_monitord_dn_size();

    ////////////////////////general////////////////
    inline bool isrunning() const {
        return runtime.isrunning;
    }

    inline void stop() {
        runtime.isrunning = false;
    }

    inline uint64_t get_sessioncount()const {
        bgcc::Guard<bgcc::Mutex> lock(&runtime.mutex);

        if (lock.is_locked()) {
            return runtime.session_count;
        }

        return 0;
    }

    inline uint64_t get_sessionaccu()const {
        bgcc::Guard<bgcc::Mutex> lock(&runtime.mutex);

        if (lock.is_locked()) {
            return runtime.session_accu;
        }

        return 0;
    }

    inline uint64_t get_starttime()const {
        return runtime.starttime;
    }

    inline void maxsession(uint32_t count) {
        bgcc::Guard<bgcc::Mutex> lock(&runtime.mutex);

        if (lock.is_locked()) {
            runtime.max_session = count;
        }
    }
    inline uint32_t maxsession() const {
        bgcc::Guard<bgcc::Mutex> lock(&runtime.mutex);

        if (lock.is_locked()) {
            return runtime.max_session;
        }

        return 0;
    }
    ///////////////////////general not threadsafe/////////////////

    inline pthread_rwlock_t& config_lock() {
        return runtime.config_lock;
    }
    inline runtime_pool_t& pool() {
        return runtime.pool;
    }
    inline ims_conf_t& config() {
        return runtime.config;
    }

#define lock_session(opr) \
        ims_session_t *session=NULL;\
        rw_lock_t lock_table(session_table_lock);\
        if(!lock_table.locked()){\
            WARNING_LOG("get session (id=%lu) failed(session table lock error)",id);\
            return false;\
        }\
        if(session_table.find(id)==session_table.end()){\
            WARNING_LOG("get session (id=%lu) failed(sessionid error)",id);\
            return false;\
        }\
        session = session_table[id];\
        if(!session){\
            WARNING_LOG("get session (id=%lu) failed(null)",id);\
            return false;\
        }\
        bgcc::Guard<bgcc::Mutex> lock(&session->mutex);\
        if(!lock.is_locked()){\
            WARNING_LOG(opr"(id=%lu) failed(session lock error)",session->id);\
            return false;   \
        }\
        lock_table.unlock();

#define lock_channel_table(opr,iswrite)\
        rw_lock_t lock_chl(channel_table_lock,iswrite); \
        if(!lock_chl.locked()){ \
            WARNING_LOG(opr" channel table lock error)"); \
            return false; \
        }

#define get_channel(opr,cid,iswrite) \
    ims::SessionIdT id=0;\
    if(NULL==channelid||'\0'==channelid[0]){\
        WARNING_LOG(opr"(cid=%s,sid=%lu)failed(invalid channelid)",channelid,id);\
        return false;\
    }\
    {\
        lock_channel_table(opr,iswrite);\
        map_str2int_t::iterator it = channel_table.find(channelid); \
        if(it==channel_table.end()||0==it->second){\
            WARNING_LOG(opr"(cid=%s)failed(invalid channelid)",cid);\
            return false;\
        }\
        id = it->second;\
    }\
    lock_session(opr);\
    ims_channel_t* channel=session->channels.find(cid)->second;\
    if(NULL==channel){\
        WARNING_LOG(opr"(cid=%s,sid=%lu)failed(invalid channelid)",channelid,id);\
        return false;\
    }

};

#endif  //__IMS_CORE_SESSION_MGR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
