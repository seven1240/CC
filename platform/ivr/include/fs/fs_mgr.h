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
#include <boost/unordered_map.hpp>
#include "fs_struct.h"
#include "fs_info.h"
#include "common.h"

class fs_mgr_t {
private:
    fs_mgr_t() {
    }
    ~fs_mgr_t() {
        IVR_DEBUG("runinfo had clean done.");
    }
public:

    static fs_mgr_t* instance() {
        static fs_mgr_t mgr;
        return &mgr;
    }

    /**
     * @brief 增加freeswitch
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
    int32_t decision_fs(uint32_t& fs_no);

    int32_t update_runinfo(uint32_t fs_no, event_data_heartbeat_t& run);

    void update_log(bool open);
public:
    int32_t get_callsource(uint32_t fs_no, std::string& callsource);
private:

    bgcc::Mutex _info_mutex;
    boost::unordered_map<uint32_t, fs_info_t*> _fsinfo;

    pthread_rwlock_t _runinfo_rwlock;
    boost::unordered_map<uint32_t, event_data_heartbeat_t*> _runinfo;

    boost::object_pool<fs_info_t> _fsopl;
    boost::object_pool<event_data_heartbeat_t> _edhopl;
};
class fs_tool_t {
public:
    fs_tool_t(uint32_t fsno):
        _fsno(fsno), _opr(NULL), _result(false) {
        _result = (fs_mgr_t::instance()->fetch_opr(_fsno, &_opr) == IVR_SUCCESS);
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
    uint32_t _fsno;
    fs_opr_t* _opr;
    bool _result;
};

#endif  //__FS_MGR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
