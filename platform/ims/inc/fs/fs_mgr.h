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

#ifndef  __FS_MGR_H_
#define  __FS_MGR_H_

#include <boost/pool/object_pool.hpp>
#include <bgcc.h>

#include "fs_struct.h"
#include "fs_info.h"

/**
* @brief FreeSWITCH对象管理器
*   detail description
*
*/
class fs_mgr_t {
private:
    const static uint32_t MAX_FW = 256;       ///<  可管理的最多FreeSWITCH对象
    fs_mgr_t() {
    }
    ~fs_mgr_t() {
    }
public:

    static fs_mgr_t* instance() {
        static fs_mgr_t mgr;
        return &mgr;
    }

    /**
     * @brief 增加 删除 freeswitch
     *
     * @param [in/out] info   : fs_info_t&
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 23:37:35
     **/
    int32_t add_fs(fs_info_t& info);
    int32_t del_fs(uint32_t fs_no);
    int32_t clear_fs();

    /**
     * @brief从编号为fs_no的fs中取一个操作对象
     *
     * @param [in/out] fs_no   : uint32_t
     * @param [in/out] opr   : fs_opr_ti**
     * @param [in/out] timeout   : int32_t
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 23:38:24
     **/
    int32_t fetch_opr(uint32_t fs_no, fs_opr_t** opr);
    int32_t free_opr(fs_opr_t** opr);

    /**
     * @brief 决策一个FW提供服务
     *
     * @param [in/out] fs_no   : uint32_t&
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 23:41:12
     **/
    int32_t decision_fs(uint32_t& fs_no);

    /**
     * @brief 更新编号为fs_no的FreeSWITCH的状态
     *
     * @param [in/out] fs_no   : uint32_t
     * @param [in/out] run   : event_data_heartbeat_t&
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/09 15:41:21
     **/
    int32_t update_runinfo(uint32_t fs_no, event_data_heartbeat_t& run);

    /**
     * @brief 重定向FreeSWITCH的日志输出
     *
     * @param [in/out] open   : bool
     * @return  void
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/09 15:41:19
     **/
    void update_log(bool open);
    /**
     * @brief 有没有连接到地址为ip的freeswitch上
     *
     * @param [in]  ip    : ip address
     * @param [out] fs_no : fs_no
     * @return  int32_t
     * @author dangdawei
     * @date 2012/7/5 17:22:30
    **/
    int32_t fetch_fs_no(uint32_t ip, uint32_t& fs_no);
private:

    bgcc::Mutex _info_mutex;
    std::map<uint32_t, fs_info_t* > _fsinfo;

    pthread_rwlock_t _runinfo_rwlock;
    std::map<uint32_t, event_data_heartbeat_t*> _runinfo;    ///<  每个FreeSWITCH的实时状态

    boost::object_pool<fs_info_t> _fsinfo_pool;
    boost::object_pool<event_data_heartbeat_t> _evt_hb_pool;
};

/**
 * @brief FW operator 包装器
 *   利用构造函数、析构函数对fw进行链接申请与释放
 *
 */
class fs_tool_t {
public:
    fs_tool_t(uint32_t fsno):
        _fsno(fsno), _opr(NULL), _result(false) {
        _result = (fs_mgr_t::instance()->fetch_opr(_fsno, &_opr) == IMS_SUCCESS);
    }

    ~fs_tool_t() {
        if (_result && _opr) {
            fs_mgr_t::instance()->free_opr(&_opr);
        }
    }

    inline bool valid() {
        return _result && _opr;
    }

    inline fs_opr_t& opr() {
        return *_opr;
    }

private:
    uint32_t _fsno;       ///<  FW 编号
    fs_opr_t* _opr;       ///<  FW 操作符
    bool _result;         ///<  FW 操作符申请结果
};

#endif  //__FS_MGR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
