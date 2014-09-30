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

#include <boost/pool/object_pool.hpp>
#include <boost/unordered_set.hpp>
#include <bgcc.h>
#include <iostream>
#include <list>
#include <set>
#include "common.h"
#include "fs_opr.h"


class fs_info_t {
private:
    uint32_t _no;
    uint32_t _address;
    uint32_t _port;
    uint32_t _max_conn;        /**< 最大连接数       */
    char _user[LEN_16 + 1];
    char _pswd[LEN_16 + 1];

    bgcc::SharedPointer<bgcc::Thread> _thrd_heartbeat;
    bgcc::SharedPointer<bgcc::Thread> _thrd_event;

    bgcc::Mutex _opr_mutex;
    std::list<fs_opr_t*> _oprs_idle;//wangting add
    boost::unordered_set<fs_opr_t*> _oprs_busy;//wangting add
    boost::object_pool<fs_opr_t> opl;
public:

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

        //_oprs_busy.create(200); wangting del
    }

    fs_info_t(const fs_info_t& info) {
        _no = info._no;
        _address = info._address;
        _port = info._port;
        _max_conn = info._max_conn;
        strncpy(_user, info._user, LEN_16);
        strncpy(_pswd, info._pswd, LEN_16);
        // wangitngdel _oprs_busy.create(200);
    }

    ~fs_info_t() {
        // _oprs_busy.destroy(); wangtingdel
    }

    inline uint32_t get_no() {
        return _no;
    }

    int32_t init();

    int32_t uninit();

    int32_t fetch(fs_opr_t** opr);

    int32_t free(fs_opr_t** opr);
public:
    uint32_t get_address() {
        return _address;
    }

    uint32_t get_port() {
        return _port;
    }
};

#endif  //__FS_INFO_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
