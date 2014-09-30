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

#include "ims/eventimp.h"
#include <tools.h>
#include <ims/ims_mgr.h>
#include <ivr_instance_manager.h>
#include <common.h>

ims::CcResultT ImsEventImp::SendCallEvent(const ims::CallEventT& event,
        const std::map<std::string, std::string>& ctx) {
    //IVR_DEBUG("ims call event");
    return ims::CcResultT::ResSuccess;
}

ims::CcResultT ImsEventImp::SendMediaEvent(const ims::MediaEventT& event,
        const std::map<std::string, std::string>& ctx) {
    //IVR_DEBUG("ims media event");
    return ims::CcResultT::ResSuccess;
}

ims::CcResultT ImsEventImp::SendRouteEvent(const ims::RouteEventT& event,
        const std::map<std::string, std::string>& ctx) {
    {
        std::ostringstream ss;
        ss << "callid(" << event.callid
           << ") sessionid(" << event.sessionid
           << ") reason" << event.reason.get_desc()
           << ") agent(" << event.targetDevice << ")";
        IVR_TRACE("ims route event: %s", ss.str().c_str());
    }
    ivr_session_id_t ivrsid = 0;

    if (ims_mgr_t::get_instance()->get_map_session_id(event.sessionid, ivrsid)) {
        std::auto_ptr<ivr_ims_event_t> ivrevent(new(std::nothrow) ivr_ims_event_t);

        if (ivrevent.get() != NULL) {
            ivrevent->data = event;
            ivrevent->sessionId = ivrsid;
            ivrevent->evt_type = ivr_base_event_t::IMS_EVENT;
            ivrevent->evt_name = ivr_ims_event_t::IVR_EVT_IMS_ROUTE_RESPONSE;
            IvrInstanceManager::get_instance()->put_ivr_event(ivrevent.release());
            IVR_TRACE("route event success!");
        } else {
            IVR_WARN("failed to new ivr_ims_event_t");
            return ims::CcResultT::ResNoEnoughResource;
        }
    } else {
        IVR_WARN("no found matched ivr session id of ims session id(%ld)", event.sessionid);
        return ims::CcResultT::ResFailed;
    }

    return ims::CcResultT::ResSuccess;
}

ims::CcResultT ImsEventImp::SendOtherEvent(const ims::OtherEventT& event,
        const std::map<std::string, std::string>& ctx) {
    //IVR_DEBUG("ims other event");
    return ims::CcResultT::ResSuccess;
}
