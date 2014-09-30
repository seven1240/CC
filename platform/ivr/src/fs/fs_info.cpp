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

#include <fs_info.h>
#include "event_receiver.h"


int32_t fs_info_t::init() {
    IVR_DEBUG("connect to fs[%d] start ", _no);
    locker_t lock(&_opr_mutex);

    if (!lock.is_locked()) {
        IVR_DEBUG("connecting to fs[%d] failed, ims_fail_lock", _no);
        return IVR_FAIL_LOCK;
    }

    IVR_DEBUG("fs[%d] create fs_opr start ", _no);

    for (uint32_t i = 0; i < _max_conn; ++i) {
        fs_opr_t* opr = NULL;
        opr = opl.construct(_no);

        if (opr && opr->connect(_address, _port, _pswd) != IVR_SUCCESS) {
            IVR_WARN("add opr [%d] failed, cannot connect to fs [%u : %u]", _no, _address, _port);
#if NOT_DEPENDENCE_FW
            _oprs_idle.push_back(opr);
#else
            return IVR_FAIL_CONNECT;
#endif
        } else {
            IVR_DEBUG("add opr [%d][%d] ok, add opr", _no, i);
            _oprs_idle.push_back(opr);
        }
    }

    IVR_DEBUG("starting heartbeat receiver for fs[%d]", _no);
    fs_opr_t* hbopr = NULL;
    hbopr = opl.construct(_no);

    if (hbopr && hbopr->connect(_address, _port, _pswd) != IVR_SUCCESS) {
        IVR_DEBUG("heartbeat receiver connecting to fs[%d] failed, cannot connect to fs [%u : %u]", _no,
                  _address, _port);
#if NOT_DEPENDENCE_FW
#else
        return IVR_FAIL_CONNECT;
#endif
    }

    heartbeat_recv_ptr hbrun(new heartbeat_recv_t(this, hbopr, 10));
    _thrd_heartbeat = bgcc::SharedPointer<bgcc::Thread>(new bgcc::Thread(hbrun));
    _thrd_heartbeat->start();

    IVR_DEBUG("starting callevent receiver for fs[%d]", _no);
    fs_opr_t* callopr = NULL;
    callopr = opl.construct(_no);

    if (callopr && callopr->connect(_address, _port, _pswd) != IVR_SUCCESS) {
        IVR_DEBUG("event  reciever connecting to fs[%d] failed, cannot connect to fs [%u : %u]", _no,
                  _address, _port);
#if NOT_DEPENDENCE_FW
#else
        return IVR_FAIL_CONNECT;
#endif
    }

    callevent_recv_ptr callrun(new callevent_recv_t(this, callopr, 10));
    _thrd_event = bgcc::SharedPointer<bgcc::Thread>(new bgcc::Thread(callrun));
    _thrd_event->start();

    //启动线程
    IVR_DEBUG("connecting to fs[%d] ok", _no);
    return IVR_SUCCESS;
}

int32_t fs_info_t::uninit() {
    locker_t lock(&_opr_mutex);

    if (!lock.is_locked()) {
        return IVR_FAIL_LOCK;
    }

    //析构的时候会自动断开链接
    while (!_oprs_idle.empty()) {
        _oprs_idle.pop_front();
    }

    _oprs_busy.clear();


    return IVR_SUCCESS;
}

int32_t fs_info_t::fetch(fs_opr_t** opr) {
    if (!opr) {
        IVR_WARN("fs_in[%u] fetch failed, IVR_FAIL_MEM", _no);
        return IVR_FAIL_MEM;
    }

    locker_t lock(&_opr_mutex);

    if (!lock.is_locked()) {
        IVR_WARN("fs_in[%u] fetch failed, IVR_FAIL_LOCK", _no);
        return IVR_FAIL_LOCK;
    }

    if (!_oprs_idle.empty()) {
        *opr = _oprs_idle.front();
        _oprs_idle.pop_front();
        // _oprs_busy.set(*opr);
        _oprs_busy.insert(*opr);
        return IVR_SUCCESS;
    }

    IVR_WARN("fs_in[%u] fetch failed, IVR_FAIL_ALL_BUSY", _no);
    return IVR_FAIL_ALL_BUSY;

}

int32_t fs_info_t::free(fs_opr_t** opr) {
    if (!opr || !(*opr)) {
        return IVR_FAIL_MEM;
    }

    locker_t lock(&_opr_mutex);

    if (!lock.is_locked()) {
        return IVR_FAIL_LOCK;
    }

    _oprs_idle.push_back(*opr);
    _oprs_busy.erase(*opr);

    *opr = NULL;

    return IVR_SUCCESS;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
