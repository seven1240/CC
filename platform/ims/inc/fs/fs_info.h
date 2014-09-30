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

#ifndef  __FS_INFO_H_
#define  __FS_INFO_H_

#include <list>
#include <set>
#include <boost/pool/object_pool.hpp>
#include <bgcc.h>
#include "ims_core.h"
#include "ims_thread.h"
#include "fs_opr.h"

class fs_info_t {
private:
    uint32_t _no;
    uint32_t _address;
    uint32_t _port;
    uint32_t _max_conn;        /**< 最大连接数       */
    char _user[LEN_16 + 1];
    char _pswd[LEN_16 + 1];

    ims::ims_thread_ptr _thrd_heartbeat;
    ims::ims_thread_ptr _thrd_event;

    bgcc::Mutex _opr_mutex;
    std::list<fs_opr_t*> _oprs_idle;
    std::set<fs_opr_t*> _oprs_busy;
    boost::object_pool<fs_opr_t> _fsopr_pool;
public:

    /**
     * @brief 标准构造函数
     *
     * @param [in/out] no   : uint32_t
     * @param [in/out] address   : uint32_t
     * @param [in/out] port   : uint32_t
     * @param [in/out] max_conn   : uint32_t
     * @param [in/out] user   : const char*
     * @param [in/out] pswd   : const char*
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/16 15:07:29
    **/
    fs_info_t(uint32_t no, uint32_t address, uint32_t port, uint32_t max_conn,
              const char* user, const char* pswd):
        _no(no), _address(address), _port(port), _max_conn(max_conn) {
        _user[LEN_16] = '\0';
        _pswd[LEN_16] = '\0';

        if (NULL != user) {
            strncpy(_user, user, LEN_16);
        } else {
            _user[0] = '\0';
        }

        if (NULL != pswd) {
            strncpy(_pswd, pswd, LEN_16);
        } else {
            _pswd[0] = '\0';
        }

    }

    fs_info_t(const fs_info_t& info) {
        _no = info._no;
        _address = info._address;
        _port = info._port;
        _max_conn = info._max_conn;
        strncpy(_user, info._user, LEN_16);
        strncpy(_pswd, info._pswd, LEN_16);
    }
    ~fs_info_t() {
    }
    inline uint32_t get_no() {
        return _no;
    }
    /**
     * @brief 初始化连接池
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/16 15:14:23
     **/
    int32_t init();

    /**
     * @brief 销毁连接池
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/16 15:14:27
     **/
    int32_t uninit();

    /**
     * @brief 获取一个空闲连接
     *
     * @param [in/out] opr   : fs_opr_t**
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/16 15:14:31
     **/
    int32_t fetch(fs_opr_t** opr);

    /**
     * @brief 释放空闲链接
     *
     * @param [in/out] opr   : fs_opr_t**
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/11/16 15:14:34
     **/
    int32_t free(fs_opr_t** opr);

    inline uint32_t get_address() {
        return _address;
    }
};

#endif  //__FS_INFO_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
