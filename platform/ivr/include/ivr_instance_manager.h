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

#ifndef _IVR_INSTANCE_MANAGER_H_
#define _IVR_INSTANCE_MANAGER_H_

#include <queue>
#include <map>
#include <pthread.h>
#include <stdint.h>

//#include "ivr_event.h" //ivr_base_event_t
#include "ivr_type.h"  //some macros
#include "common.h"

class IvrInstanceManager {
public:
    /**
     * @brief   构造函数
     * @param
     * @return
     */
    IvrInstanceManager();

    /**
     * @brief   构造函数
     * @param
     * @return
     */
    ~IvrInstanceManager();

    /**
     * @brief   获取IvrInstanceManager单例
     * @param
     * @return  IvrInstanceManager单例指针
     */
    static IvrInstanceManager* get_instance();

    /**
     * @brief   初始化IvrInstanceManager
     * @param
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t init();

    /**
     * @brief   销毁IvrInstanceManager
     * @param
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t destroy();

    /**
     * @brief   创建ivr实例
     * @param   type 流程实例类型，分为auto和inbound两类
     * @param   freeswitch_no freeswitch编号
     * @param   id [out] 创建成功的IVR实例ID
     * @param   dynmic_resoure 动态资源（包括queue, sem_t, IvrTimer三者的指针）
     * @param   uuid 通话标识
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     * @note 参数id需由调用者申请空间。当创建成功后，成功创建的IVR实例ID会被写入id
     */
    int32_t create_ivr_instance(int32_t type, fw_id_t freeswith_no, ivr_session_id_t* id,
                                session_dynamic_resource_t dynmic_resoure, const string& uuid);

    /**
     * @brief   销毁ivr实例
     * @param   id 将被销毁的IVR实例id
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t destroy_ivr_instance(ivr_session_id_t id);

    /**
     * @brief   查找IVR实例是否存在
     * @param   id 待查找的IVR实例ID
     * @return  存在返回true;否则返回false
     */
    bool  search_ivr_instance(ivr_session_id_t id);

    /**
     * @brief   将IVR事件放入对应的IVR ID事件队列中
     * @param   event Ivr事件 event中已经有ivr_session_id_t，故在接口中不再添加ivr_session_id_t一项
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t put_ivr_event(ivr_base_event_t* event);

    /**
     * @brief   获取指针ID的IVR事件队列的队首事件，并将队首移除
     * @param   sid IVR事件ID
     * @param   event 事件
     * @return
     */
    int32_t get_ivr_event(ivr_session_id_t sid, ivr_base_event_t** event);

    /**
     * @brief   清空指定IVR实例的事件队列
     * @param   id IVR实例ID
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t clear_event_queue(ivr_session_id_t id);


    /**
     * @brief   检查uuid是否存在
     * @param   uuid 待检查的uuid
     * @param   sid 若uuid存在，则将uuid对应的session id写入sid
     * @return  若uuid存在，返回true；否则返回false
     */
    bool check_uuid(const std::string& uuid, ivr_session_id_t& sid);

    /**
     * @brief   加入uuid与sessionid的关系
     * @param   sid session id
     * @param   uuid 待添加的uuid
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t add_uuid(ivr_session_id_t sid, const std::string& uuid);

    int32_t add_channel_info(const std::string& uuid, const channel_info_t& info);

    int32_t get_channel_info(const std::string& uuid, channel_info_t& info);

public:

    // set flag to mark flow had(or not) transagent
    //  _trans_valid[sid] = valid;
    void mark_transagent(ivr_session_id_t sid, bool valid);

    // test wether flow had transagent
    //  return _trans_valid[sid]
    bool is_transagent(ivr_session_id_t sid);
private:
    /**
     * @brief   删除uuid与sessionid的关系
     * @param   uuid
     * @return  成功返回IVR_SUCCESS;否则返回错误码
     */
    int32_t remove_uuid(const std::string& uuid);

    int32_t remove_uuid(ivr_session_id_t sid);

    int32_t remove_tav(ivr_session_id_t sid);

private:

    /** sessionid与动态资源(queue,sem,timer)的对应关系 */
    std::map<ivr_session_id_t, session_dynamic_resource_t> _sid_dynres_map;
    typedef std::map<ivr_session_id_t, session_dynamic_resource_t>::iterator iterator;

    /** _sid_dynres_map互斥锁 */
    //static pthread_mutex_t _mutex;
    static pthread_mutex_t _mutex;

    std::map<std::string, ivr_session_id_t> _uuid_sid_map;
    typedef std::map<std::string, ivr_session_id_t>::iterator uuid_sid_iterator;
    //static pthread_mutex_t _uuid_map_mutex;
    static pthread_mutex_t _uuid_map_mutex;

    // mark ivr flow had(or not) trans agent
    //  if true, flow can't send fs cmd and receive fs event
    std::map<ivr_session_id_t, bool> _transagent_valid;
    typedef std::map<ivr_session_id_t, bool>::iterator tav_iterator;

    std::map<std::string, channel_info_t> _uuid_info_map;
    typedef std::map<std::string, channel_info_t>::iterator cinfo_iterator;

    /**
     * @brief   创建ivr session id
     * @param
     * @return  ivr session id
     */
    static ivr_session_id_t create_ivr_session_id(int32_t type, int32_t freeswith_no);
};


#endif // _IVR_INSTANCE_MANAGER_H_

