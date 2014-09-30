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

#include <ims/ims_info.h>
#include <ims/ims_mgr.h>
#include <ims/eventimp.h>
#include <tools.h>
#include <common.h>

extern std::string g_server_ip;

ims_info_t::ims_info_t(uint32_t imsno, const std::string& ip, uint32_t port)
    : _no(imsno)
    , _ip(ip)
    , _port(port)
    , _reqid(0) {
}

ims_info_t::ims_info_t(const ims_info_t& other)
//    : Shareable(other)
    : _no(other._no)
    , _ip(other._ip)
    , _port(other._port)
    , _reqid(other._reqid) {
}

ims_info_t::~ims_info_t() {
}

int32_t ims_info_t::get_info(imsapi_proxy_pointer& proxy, ims_reqid_t& reqid) {
    locker_t guard(&_ctx_mutex);

    if (!guard.is_locked()) {
        IVR_WARN("lock failed");
        return IVR_FAIL_LOCK;
    }

    IVR_DEBUG("locked");

    if (_proxy.get() == NULL) {
        bgcc::ServerInfo imsServer(_ip, (uint16_t)_port);
        bgcc::SharedPointer<bgcc::IProcessor> xp(new ims::event_callbackProcessor(
                    bgcc::SharedPointer<ims::event_callback>(new ImsEventImp)));
        ims_mgr_t::get_instance()->getCallbackService()->add_service(xp);
        imsapi_proxy_pointer opr(new(std::nothrow)imsapi_proxy(imsServer, 10,
                                 ims_mgr_t::get_instance()->getCallbackService()));

        if (opr.get() == NULL) {
            IVR_WARN("ims[%u] new proxy failed!", _no);
            return -1;
        } else {
            // create callback service manager
            IVR_TRACE("add ims[%u] call back service done.", _no);

            _proxy = opr;
            IVR_TRACE("ims[%u] create new proxy success, ip(%s), port(%d)!", _no, _ip.c_str(), _port);
        }
    }

    if (_reqid == 0) {
        IVR_NOTICE("ims[%u] need regist", _no);

        if (IVR_SUCCESS != _regist_ims()) {
            return IVR_FAIL_IMS_REGIST;
        }
    }

    IVR_DEBUG("get ims_info success, set reqid and proxy");
    proxy = _proxy;
    reqid = _reqid;

    return IVR_SUCCESS;
}

int32_t ims_info_t::update(ims_reqid_t reqid) {
    IVR_TRACE("ims[%d] ip(%s) port(%d) update", _no, _ip.c_str(), _port);
    locker_t guard(&_ctx_mutex);

    if (!guard.is_locked()) {
        IVR_WARN("lock failed");
        return IVR_FAIL_LOCK;
    }

    IVR_DEBUG("locked");

    if (reqid != _reqid) {
        return IVR_FAIL_IMS_REINIT; // don't need update
    }

    if (_proxy.get() == NULL) {
        // ims has not init
        return -1;
    }

    return _regist_ims();
}

int32_t ims_info_t::_regist_ims() {
    // regist on ims
    ims_reqid_t tmp_reqid;
    ims::ServiceTypeT stype(ims::ServiceTypeT::ServiceIVR);
    IVR_TRACE("ims[%d] try to regist", _no);
    int32_t res = _proxy->Register(stype, tmp_reqid).get_value();
    int32_t proxy_err = _proxy->get_errno();

    if (proxy_err == 0 && ims::CcResultT::ResSuccess == res) {
        IVR_TRACE("ims[%d] regist success, reqid %ld!", _no, tmp_reqid);
        _reqid = tmp_reqid;
    } else if (proxy_err != 0) {
        // connection failed
        IVR_WARN("ims[%d] regist failed, connection failed, proxy err %d", _no, proxy_err);
        // make reqid invalidate
        _reqid = 0;
        return IVR_FAIL_IMS_REGIST;
    } else {
        _reqid = 0;
        ims::CcResultT tmpS(res);
        IVR_WARN("ims[%d] regist failed! recode %s", _no, tmpS.get_desc().c_str());
        // todo: log failed resaon here
        return IVR_FAIL_IMS_REGIST;
    }

    return IVR_SUCCESS;
}

uint32_t ims_info_t::get_imsno() const {
    return _no;
}

