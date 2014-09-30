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

#ifndef _IVR_IMS_INFO_H_
#define _IVR_IMS_INFO_H_

#include "common.h"
#include "ims_struct.h"

class ims_event_receiver;
// ims information
class ims_info_t : public bgcc::Shareable {
public:
    ims_info_t(uint32_t imsno, const std::string& ip, uint32_t port);
    ims_info_t(const ims_info_t& other);
    virtual ~ims_info_t();
public:
    // get current proxy and reqid
    // if proxy had not created, create it
    // if ims has not regist, rigist at ims
    // will update _reqid
    int32_t get_info(imsapi_proxy_pointer& proxy, ims_reqid_t& reqid);

    // re-regist at this ims
    // if reqid != _reqid, just return failed
    int32_t update(ims_reqid_t reqid);

    // get ims number: return _no
    uint32_t get_imsno() const;
protected:
    // if regist at ims
    int32_t _regist_ims();
protected:
    struct imsproxy_opr;
protected:
    // ims number(index)
    uint32_t _no;

    // ims ip, used to listen ims event or get heartbeat
    std::string _ip;

    // ims port, used to listen ims event or get heartbeat
    uint32_t _port;

    // the identity of the service unit @ims, return after registed at ims
    ims_reqid_t _reqid;

    // last call register time
    time_t _lastinit_time;
protected:
    // proxy of this ims
    imsapi_proxy_pointer _proxy;
    // locker of _proxy
    bgcc::Mutex _ctx_mutex;
};

typedef bgcc::SharedPointer<ims_info_t> ims_info;

#endif
