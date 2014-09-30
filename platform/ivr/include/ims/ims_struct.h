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

#ifndef _IVR_IMS_STRUCT_H_
#define _IVR_IMS_STRUCT_H_

#include <ivr.h>
#include <ims.h>
#include <bgcc.h>

typedef ims::ReqIdT ims_reqid_t;
typedef ims::SessionIdT ims_session_id_t;
typedef ims::RouteRequestIDT ims_routerequest_id_t;
typedef ims::ServiceTypeT ims_servicetype_t;
typedef ims::RouteRequestTypeT ims_routerequest_type_t;
typedef ims::TransferTypeT ims_transtype_t;
typedef ims::CcResultT ims_ccresult_t;
typedef ims::RouteEventReasonT ims_routeevent_reason_t;

class imsapi_proxy : public bgcc::Shareable, public ims::imsapiProxy {
public:
    imsapi_proxy(bgcc::ServerInfo serverinfo, int32_t nprotocols, bgcc::ServiceManager* mgr)
        : ims::imsapiProxy(serverinfo, nprotocols, mgr, 1, 300) {
    }
};

// make imsapi_proxy_t shareable
typedef bgcc::SharedPointer<imsapi_proxy> imsapi_proxy_pointer;


#endif
