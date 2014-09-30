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

#include <lock.h>
#include <fs_mgr.h>
#include <bgcc.h>


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
        //com_writelog("esl", "%s:%d %s() %s",fp,line,func,data);
        BGCC_WARN("esl", "%s:%d %s() %s", fp, line, func, data);
        /*
        if(level<=3){//ERROR
            IVR_FATAL("%s:%d %s() %s", fp, line, func, data);
        }
        else if(4==level){//WARING
            IVR_WARN("%s:%d %s() %s", fp, line, func, data);
        }
        else if(5==level){//NOTICE
            IVR_NOTICE("%s:%d %s() %s", fp, line, func, data);
        }
        else if(6==level){//trace
            IVR_TRACE("%s:%d %s() %s", fp, line, func, data);
        }
        else{//DEBUG
            IVR_DEBUG("%s:%d %s() %s", fp, line, func, data);
        }
        */
        free(data);
    }

    va_end(ap);
}


int32_t fs_mgr_t::clear_fs() {
    locker_t lock(&_info_mutex);

    if (!lock.is_locked()) {
        return IVR_FAIL_LOCK;
    }

    for (boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.begin();
            it != _fsinfo.end(); ++it) {
        if (it->second) {
            it->second->uninit();
        }
    }

    _fsinfo.clear();

    return IVR_SUCCESS;
}

void fs_mgr_t::update_log(bool open) {
    esl_global_set_logger(open ? esl_log_ims : NULL);
}

int32_t fs_mgr_t::update_runinfo(uint32_t fs_no, event_data_heartbeat_t& run) {
    rw_lock_t lock(_runinfo_rwlock, true);

    if (!lock.locked()) {
        return IVR_FAIL_LOCK;
    }

    event_data_heartbeat_t* pinfo = NULL;
    boost::unordered_map<uint32_t, event_data_heartbeat_t*>::iterator it = _runinfo.find(fs_no);

    if (it == _runinfo.end() || NULL == (pinfo = it->second)) {
        pinfo = _edhopl.construct();
    }

    if (NULL != pinfo) {
        _runinfo[fs_no] = pinfo;
        memcpy(pinfo, &run, sizeof(run));

        return IVR_SUCCESS;
    }

    return IVR_FAIL_MEM;
}

int32_t fs_mgr_t::del_fs(uint32_t fs_no) {
    {
        //删除链接信息
        locker_t lock(&_info_mutex);

        if (!lock.is_locked()) {
            return IVR_FAIL_LOCK;
        }

        fs_info_t* fsinfo = NULL;
        boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.find(fs_no);

        if (it == _fsinfo.end()) {
            return IVR_FAIL_NOTEXISTS;
        } else {
            fsinfo = it->second;
        }


        if (fsinfo) {
            fsinfo->uninit();
        }

        _fsinfo.erase(fs_no);
    }
    {
        //删除运行信息
        rw_lock_t lock(_runinfo_rwlock, true);

        if (!lock.locked()) {
            return IVR_FAIL_LOCK;
        }

        _runinfo.erase(fs_no);
    }

    return IVR_SUCCESS;
}

int32_t fs_mgr_t::add_fs(fs_info_t& info) {
    locker_t lock(&_info_mutex);

    if (!lock.is_locked()) {
        return IVR_FAIL_LOCK;
    }

    boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.find(info.get_no());

    if (it != _fsinfo.end()) {
        return IVR_FAIL_EXISTS;
    }

    fs_info_t* pinfo = NULL;
    pinfo = _fsopl.construct(info);

    if (NULL == pinfo) {
        return IVR_FAIL_MEM;
    }

    int32_t ret = pinfo->init();

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    std::pair< boost::unordered_map<uint32_t, fs_info_t*>::iterator, bool > pr =
        _fsinfo.insert(std::make_pair(info.get_no(), pinfo));

    if (!pr.second) {
        return IVR_FAIL_GENERAL;
    }

    event_data_heartbeat_t data;
    data.cur_session = 0;
    data.all_session = 0;
    data.cpu_idle = 100;
    update_runinfo(pinfo->get_no(), data);

    return IVR_SUCCESS;
}

int32_t fs_mgr_t::fetch_opr(uint32_t fs_no, fs_opr_t** opr) {
    locker_t lock(&_info_mutex);

    if (!lock.is_locked()) {
        IVR_WARN("fs[%u] fetch_opr failed, IVR_FAIL_LOCK", fs_no);
        return IVR_FAIL_LOCK;
    }

    fs_info_t* fs_info;
    boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.find(fs_no);

    if (it == _fsinfo.end()) {
        IVR_WARN("fs[%u] fetch_opr failed, IVR_FAIL_INVALID_FSNO", fs_no);
        return IVR_FAIL_INVALID_FSNO;
    } else {
        fs_info = it->second;
    }

    if (fs_info) {
        return fs_info->fetch(opr);
    } else {
        IVR_WARN("fs[%u] fetch_opr failed, IVR_FAIL_MEM", fs_no);
        return IVR_FAIL_MEM;
    }
}

int32_t fs_mgr_t::free_opr(fs_opr_t** opr) {
    if (!opr || !(*opr)) {
        return IVR_FAIL_MEM;
    }

    locker_t lock(&_info_mutex);

    if (!lock.is_locked()) {
        return IVR_FAIL_LOCK;
    }

    fs_info_t* fs_info;
    boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.find((*opr)->get_fs_no());

    if (it == _fsinfo.end()) {
        return IVR_FAIL_INVALID_FSNO;
    } else {
        fs_info = it->second;
    }

    if (fs_info) {
        return fs_info->free(opr);
    } else {
        return IVR_FAIL_MEM;
    }

}

int32_t fs_mgr_t::decision_fs(uint32_t& fs_no) {
    rw_lock_t lock(_runinfo_rwlock);

    if (!lock.locked()) {
        IVR_WARN("decision_fs failed. IVR_FAIL_LOCK ");
        return IVR_FAIL_LOCK;
    }

    if (_runinfo.begin() == _runinfo.end()) {
        IVR_WARN("decision_fs failed. IVR_FAIL_NOTEXISTS");
        return IVR_FAIL_NOTEXISTS;
    }

    fs_no = 0xffff;

    event_data_heartbeat_t fs_data;
    fs_data.cpu_idle = 0;
    fs_data.cur_session = 0xffff;
    fs_data.all_session = 0xffff;

    boost::unordered_map<uint32_t, event_data_heartbeat_t*>::iterator iter = _runinfo.begin();

    while (iter != _runinfo.end()) {
        uint32_t key = iter->first;
        event_data_heartbeat_t* curr = iter->second;
        bool change = false;

        if (curr->cpu_idle > fs_data.cpu_idle) {
            change = true;
        } else if (curr->cpu_idle == fs_data.cpu_idle) {
            if (curr->cur_session + curr->all_session < fs_data.cur_session) {
                change = true;
            } else if (curr->cur_session + curr->all_session == fs_data.cur_session) {
                if ((curr->all_session < fs_data.all_session) ||
                        (curr->all_session == fs_data.all_session && key < fs_no)) {
                    change = true;
                }
            }
        }

        if (change) {
            fs_no = key;
            fs_data.cpu_idle = curr->cpu_idle;
            fs_data.all_session = fs_data.cur_session =
                                      curr->all_session + curr->cur_session;
        }

        ++ iter;
    }

    event_data_heartbeat_t* hdata = NULL;
    boost::unordered_map<uint32_t,  event_data_heartbeat_t*>::iterator it = _runinfo.find(fs_no);

    if (it != _runinfo.end() && NULL != (hdata = it->second)) {
        ++ hdata->use_session;
    }

    return IVR_SUCCESS;
}

int32_t fs_mgr_t::get_callsource(uint32_t fs_no, std::string& callsource) {
    locker_t lock(&_info_mutex);

    if (!lock.is_locked()) {
        IVR_WARN("fs[%u] get_fs_ipport failed, IVR_FAIL_LOCK", fs_no);
        return IVR_FAIL_LOCK;
    }

    fs_info_t* fs_info;
    boost::unordered_map<uint32_t, fs_info_t*>::iterator it = _fsinfo.find(fs_no);

    if (it == _fsinfo.end()) {
        IVR_WARN("fs[%u] get_fs_ipport failed, IVR_FAIL_INVALID_FSNO", fs_no);
        return IVR_FAIL_INVALID_FSNO;
    } else {
        fs_info = it->second;
    }

    if (fs_info) {
        char buff[32] = {0};
        uint32_t ip = fs_info->get_address();
        sprintf(buff, "%d.%d.%d.%d",
                (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
        callsource = buff;
    } else {
        IVR_WARN("fs[%u] get_fs_ipport failed, IVR_FAIL_MEM", fs_no);
        return IVR_FAIL_MEM;
    }

    return IVR_SUCCESS;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
