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

#include "fs_info.h"
#include "event_receiver.h"
#include "ims_log.h"
using namespace ims;
using namespace bgcc;

int32_t fs_info_t::init() {
    DEBUG_LOG("connect to fs[%d] start ", _no);
    Guard<Mutex> lock(&_opr_mutex);

    if (!lock.is_locked()) {
        DEBUG_LOG("connecting to fs[%d] failed, ims_fail_lock", _no);
        return IMS_FAIL_LOCK;
    }

    DEBUG_LOG("fs[%d] create fs_opr start ", _no);

    for (uint32_t i = 0; i < _max_conn; ++i) {
        //fs_opr_t *opr=_rp.createp<fs_opr_t,uint32_t>(_no);
        fs_opr_t* opr = _fsopr_pool.construct(_no);

        if (opr && opr->connect(_address, _port, _pswd) != IMS_SUCCESS) {
            WARNING_LOG("add opr [%d] failed, cannot connect to fs [%u : %u]", _no, _address, _port);
            return IMS_FAIL_CONNECT;
        } else {
            DEBUG_LOG("add opr [%d][%d] ok, add opr", _no, i);
            _oprs_idle.push_back(opr);
        }
    }

    DEBUG_LOG("starting heartbeat receiver for fs[%d]", _no);
    //fs_opr_t *hbopr =_rp.createp<fs_opr_t,uint32_t>(_no);
    fs_opr_t* hbopr = _fsopr_pool.construct(_no);

    if (hbopr && hbopr->connect(_address, _port, _pswd) != IMS_SUCCESS) {
        DEBUG_LOG("heartbeat receiver connecting to fs[%d] failed, cannot connect to fs [%u : %u]", _no,
                  _address, _port);
        return IMS_FAIL_CONNECT;
    }

    heartbeat_recv_ptr hbrun(new heartbeat_recv_t(this, hbopr, 500));
    _thrd_heartbeat = ims_thread_ptr(new ims_thread_t(hbrun));
    _thrd_heartbeat->start();

    DEBUG_LOG("starting callevent receiver for fs[%d]", _no);
    //fs_opr_t *callopr =_rp.createp<fs_opr_t,uint32_t>(_no);
    fs_opr_t* callopr = _fsopr_pool.construct(_no);

    if (callopr && callopr->connect(_address, _port, _pswd) != IMS_SUCCESS) {
        DEBUG_LOG("event  reciever connecting to fs[%d] failed, cannot connect to fs [%u : %u]", _no,
                  _address, _port);
        return IMS_FAIL_CONNECT;
    }

    callevent_recv_ptr callrun(new callevent_recv_t(this, callopr, 500));
    _thrd_event = ims_thread_ptr(new ims_thread_t(callrun));
    _thrd_event->start();

    //Æô¶¯Ïß³Ì
    DEBUG_LOG("connecting to fs[%d] ok", _no);
    return IMS_SUCCESS;
}

int32_t fs_info_t::uninit() {
    Guard<Mutex> lock(&_opr_mutex);

    if (!lock.is_locked()) {
        return IMS_FAIL_LOCK;
    }

    _oprs_idle.clear();
    _oprs_busy.clear();

    //stop callevent and heartbeat event thread
    //thread is detached mode, so don't need join
    dynamic_cast<base_recv_t*>(_thrd_heartbeat->get_runner().get())->shutdown();
    dynamic_cast<base_recv_t*>(_thrd_event->get_runner().get())->shutdown();

    //_rp.reset();

    return IMS_SUCCESS;
}

int32_t fs_info_t::fetch(fs_opr_t** opr) {
    if (!opr) {
        WARNING_LOG("fs_in[%u] fetch failed, IMS_FAIL_MEM", _no);
        return IMS_FAIL_MEM;
    }

    Guard<Mutex> lock(&_opr_mutex);

    if (!lock.is_locked()) {
        WARNING_LOG("fs_in[%u] fetch failed, IMS_FAIL_LOCK", _no);
        return IMS_FAIL_LOCK;
    }

    if (!_oprs_idle.empty()) {
        *opr = _oprs_idle.front();
        _oprs_idle.pop_front();
        _oprs_busy.insert(*opr);
        return IMS_SUCCESS;
    }

    WARNING_LOG("fs_in[%u] fetch failed, IMS_FAIL_ALL_BUSY", _no);
    return IMS_FAIL_ALL_BUSY;

}
int32_t fs_info_t::free(fs_opr_t** opr) {
    if (!opr || !(*opr)) {
        return IMS_FAIL_MEM;
    }

    Guard<Mutex> lock(&_opr_mutex);

    if (!lock.is_locked()) {
        return IMS_FAIL_LOCK;
    }

    _oprs_idle.push_back(*opr);
    _oprs_busy.erase(*opr);

    *opr = NULL;

    return IMS_SUCCESS;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
