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

#include "ims_lock.h"
#include "ims_log.h"
#include "ims_tool.h"
#include "fs_mgr.h"

static const char* cut_path(const char* in) {
    const char* p, *ret = in;
    char delims[] = "/\\";
    char* i;

    for (i = delims; *i; i++) {
        p = in;

        while ((p = strchr(p, *i)) != 0) {
            ret = ++p;
        }
    }

    return ret;
}
void esl_log_ims(const char* file, const char* func, int line, int level, const char* fmt, ...) {
    const char* fp;
    char* data;
    va_list ap;
    int ret;

    fp = cut_path(file);

    va_start(ap, fmt);

    ret = vasprintf(&data, fmt, ap);

    if (ret != -1) {
        BGCC_TRACE("esl", "%s:%d %s() %s", fp, line, func, data);
        /*
        if(level<=3){//ERROR
            FATAL_LOG("%s:%d %s() %s", fp, line, func, data);
        }
        else if(4==level){//WARING
            WARNING_LOG("%s:%d %s() %s", fp, line, func, data);
        }
        else if(5==level){//NOTICE
            NOTICE_LOG("%s:%d %s() %s", fp, line, func, data);
        }
        else if(6==level){//trace
            TRACE_LOG("%s:%d %s() %s", fp, line, func, data);
        }
        else{//DEBUG
            DEBUG_LOG("%s:%d %s() %s", fp, line, func, data);
        }
        */
        free(data);
    }

    va_end(ap);
}


int32_t fs_mgr_t::fetch_fs_no(uint32_t ip, uint32_t& fs_no) {
    bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

    if (!lock.is_locked()) {
        WARNING_LOG("fetch fs_no failed(lock falied).");
        return IMS_FAIL_LOCK;
    }

    for (std::map<uint32_t, fs_info_t*>::iterator it = _fsinfo.begin();
            it != _fsinfo.end(); ++it) {
        if (it->second && ip == it->second->get_address()) {
            fs_no = it->first;
            TRACE_LOG("fetch fs_no=%u success.", fs_no);
            return IMS_SUCCESS;
        } else if (it->second && 0x7f000001 == it->second->get_address()) {
            if (ims_tool_t::is_local_ipv4(ip)) {
                fs_no = it->first;
                TRACE_LOG("fetch fs_no=%u success.", fs_no);
                return IMS_SUCCESS;
            }
        }
    }

    return IMS_FAIL_GENERAL;
}

int32_t fs_mgr_t::clear_fs() {
    {
        bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

        if (!lock.is_locked()) {
            return IMS_FAIL_LOCK;
        }

        for (std::map<uint32_t, fs_info_t*>::iterator it = _fsinfo.begin();
                it != _fsinfo.end(); ++it) {
            if (it->second) {
                it->second->uninit();
            }
        }

        _fsinfo.clear();
    }
    {
        //删除运行信息
        rw_lock_t lock(_runinfo_rwlock, true);

        if (!lock.locked()) {
            return IMS_FAIL_LOCK;
        }

        _runinfo.clear();
    }

    return IMS_SUCCESS;
}

void fs_mgr_t::update_log(bool open) {
    esl_global_set_logger(open ? esl_log_ims : NULL);
}

int32_t fs_mgr_t::update_runinfo(uint32_t fs_no, event_data_heartbeat_t& run) {
    rw_lock_t lock(_runinfo_rwlock, true);

    if (!lock.locked()) {
        return IMS_FAIL_LOCK;
    }

    //DEBUG_LOG("fs_no(=%u)", fs_no);
    //DEBUG_LOG("cur_session(=%u)", run.cur_session);
    //DEBUG_LOG("all_session(=%u)", run.all_session);
    //DEBUG_LOG("cpu_idle(=%u)", run.cpu_idle);

    run.used_times = 0;

    event_data_heartbeat_t* pinfo = NULL;

    if (_runinfo.count(fs_no) == 0 || NULL == _runinfo[fs_no]) {
        //pinfo=_rp.createp<event_data_heartbeat_t>();
        pinfo = _evt_hb_pool.construct();
    }

    if (NULL != pinfo) {
        _runinfo[fs_no] = pinfo;
        memcpy(pinfo, &run, sizeof(run));

        return IMS_SUCCESS;
    }

    return IMS_FAIL_MEM;
}

int32_t fs_mgr_t::del_fs(uint32_t fs_no) {
    {
        //删除链接信息
        bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

        if (!lock.is_locked()) {
            return IMS_FAIL_LOCK;
        }

        fs_info_t* fsinfo = NULL;

        if (_fsinfo.count(fs_no) == 0) {
            return IMS_FAIL_NOTEXISTS;
        }

        fsinfo = _fsinfo[fs_no];

        if (fsinfo) {
            fsinfo->uninit();
        }

        _fsinfo.erase(fs_no);
    }
    {
        //删除运行信息
        rw_lock_t lock(_runinfo_rwlock, true);

        if (!lock.locked()) {
            return IMS_FAIL_LOCK;
        }

        _runinfo.erase(fs_no);
    }

    return IMS_SUCCESS;
}

int32_t fs_mgr_t::add_fs(fs_info_t& info) {
    bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

    if (!lock.is_locked()) {
        return IMS_FAIL_LOCK;
    }

    if (_fsinfo.count(info.get_no()) != 0) {
        return IMS_FAIL_EXISTS;
    }

    //fs_info_t *pinfo=_rp.createp<fs_info_t>(info);
    fs_info_t* pinfo = _fsinfo_pool.construct(info);

    if (NULL == pinfo) {
        return IMS_FAIL_MEM;
    }

    int32_t ret = pinfo->init();

    if (IMS_SUCCESS != ret) {
        return ret;
    }

    _fsinfo[info.get_no()] = pinfo;

    if (_fsinfo.count(info.get_no()) == 0) {
        return IMS_FAIL_GENERAL;
    }

    event_data_heartbeat_t data;
    data.cur_session = 0;
    data.all_session = 0;
    data.cpu_idle = 100;
    data.used_times = 0;
    update_runinfo(pinfo->get_no(), data);

    return IMS_SUCCESS;
}

int32_t fs_mgr_t::fetch_opr(uint32_t fs_no, fs_opr_t** opr) {

    bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

    if (!lock.is_locked()) {
        WARNING_LOG("fs[%u] fetch_opr failed, IMS_FAIL_LOCK", fs_no);
        return IMS_FAIL_LOCK;
    }

    fs_info_t* fs_info;

    if (_fsinfo.count(fs_no) == 0) {
        WARNING_LOG("fs[%u] fetch_opr failed, IMS_FAIL_INVALID_FSNO", fs_no);
        return IMS_FAIL_INVALID_FSNO;
    }

    fs_info = _fsinfo[fs_no];

    if (fs_info) {
        return fs_info->fetch(opr);
    } else {
        WARNING_LOG("fs[%u] fetch_opr failed, IMS_FAIL_MEM", fs_no);
        return IMS_FAIL_MEM;
    }
}

int32_t fs_mgr_t::free_opr(fs_opr_t** opr) {

    if (!opr || !(*opr)) {
        return IMS_FAIL_MEM;
    }

    bgcc::Guard<bgcc::Mutex> lock(&_info_mutex);

    if (!lock.is_locked()) {
        return IMS_FAIL_LOCK;
    }

    fs_info_t* fs_info;

    if (_fsinfo.count((*opr)->get_fs_no()) == 0) {
        return IMS_FAIL_INVALID_FSNO;
    }

    fs_info = _fsinfo[(*opr)->get_fs_no()];

    if (fs_info) {
        return fs_info->free(opr);
    } else {
        return IMS_FAIL_MEM;
    }

}

int32_t fs_mgr_t::decision_fs(uint32_t& fs_no) {
    rw_lock_t lock(_runinfo_rwlock, true);

    if (!lock.locked()) {
        WARNING_LOG("decision_fs failed. IMS_FAIL_LOCK ");
        return IMS_FAIL_LOCK;
    }

    if (_runinfo.begin() == _runinfo.end()) {
        WARNING_LOG("decision_fs failed. IMS_FAIL_NOTEXISTS");
        return IMS_FAIL_NOTEXISTS;
    }

    fs_no = 0xffff;

    event_data_heartbeat_t fs_data;
    fs_data.cpu_idle = 0;
    fs_data.cur_session = 0xaaaa; //don't use 0xffff to avoid overflow when added.
    fs_data.used_times =  0xaaaa;

    //int heavyload_node_count = 0; //num of freeswitch node reached the utmost-heavy load
    std::map<uint32_t, event_data_heartbeat_t*>::iterator iter = _runinfo.begin();
    event_data_heartbeat_t* final = NULL;

    while (iter != _runinfo.end()) {
        uint32_t key = iter->first;
        event_data_heartbeat_t* curr = iter->second;
        bool change = false;

        if (curr->cpu_idle > fs_data.cpu_idle + 20) {
            change = true;
        } else if (curr->cpu_idle >= (fs_data.cpu_idle > 20 ? fs_data.cpu_idle - 20 : 0)) {
            if (curr->cur_session + curr->used_times * 2 < fs_data.cur_session + fs_data.used_times * 2) {
                change = true;
            } else if (curr->cur_session + curr->used_times * 2 == fs_data.cur_session + fs_data.used_times *
                       2) {
                if (key < fs_no) {
                    change = true;
                }
            }
        }

        DEBUG_LOG("fs_no(=%u), cpu_idle(=%u), cur_session(=%u), 2*used_times(=%u), all_session(=%u)",
                  key, curr->cpu_idle, curr->cur_session, curr->used_times * 2, curr->all_session);

        if (change) {
            fs_no = key;
            fs_data.cpu_idle = curr->cpu_idle;
            fs_data.cur_session = curr->cur_session;
            fs_data.used_times = curr->used_times;
            final = curr;
        }

        //if(curr->cpu_idle == 99 && curr->cur_session + curr->used_times*2 > 1000) {
        //    ++heavyload_node_count;
        //}

        ++iter;
    }

    // return IMS_FAIL_GENERAL when all freeswitch reached the utmost-heavy load
    // reject the next call to ensure the service quality of current calls.
    //if(heavyload_node_count == _runinfo.size()) {
    //    return IMS_FAIL_ALL_BUSY;
    //}

    if ((~0) == fs_no) {
        return IMS_FAIL_GENERAL;
    } else {
        if (final) {
            ++ final->used_times;
        }

        return IMS_SUCCESS;
    }
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
