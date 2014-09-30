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

#ifndef  __IMS_CORE_REQUEST_H_
#define  __IMS_CORE_REQUEST_H_

#include <bgcc.h>
#include "queue.h"
/**
* @brief req 处理单元
*   detail description
*
*/
class ims_request_t: public bgcc::Runnable {
private:
    uint64_t _reqid;
    std::string _conn_info;
    bool _isconnect;

    ims::queue_t<ims::CallEventT>  _qevent_call;
    ims::queue_t<ims::MediaEventT> _qevent_media;
    ims::queue_t<ims::RouteEventT> _qevent_route;
    ims::queue_t<ims::OtherEventT> _qevent_other;
public:
    ims_request_t(uint64_t reqid, const std::string& conninfo)
        : _reqid(reqid), _conn_info(conninfo), _isconnect(true) {
    }

    void stop() {
        _isconnect = false;
    }

    bool add_callevent(ims::CallEventT& event) {
        _qevent_call.put(event);
        return true;
    }
    bool add_mediaevent(ims::MediaEventT& event) {
        _qevent_media.put(event);
        return true;
    }
    bool add_routeevent(ims::RouteEventT& event) {
        _qevent_route.put(event);
        return true;
    }
    bool add_otherevent(ims::OtherEventT& event) {
        _qevent_other.put(event);
        return true;
    }

    int32_t operator()(const bool* isstoped, void* param = NULL);
};

typedef bgcc::SharedPointer<ims_request_t> ims_request_ptr;

#endif  //__IMS_CORE_REQUEST_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
