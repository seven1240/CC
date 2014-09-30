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

#ifndef _IVR_IMS_EVENT_IMP_H_
#define _IVR_IMS_EVENT_IMP_H_

#include <callback.h>

class ImsEventImp : public ims::event_callback {
public:
    ims::CcResultT SendCallEvent(const ims::CallEventT& event,
                                 const std::map<std::string, std::string>& ctx);

    ims::CcResultT SendMediaEvent(const ims::MediaEventT& event,
                                  const std::map<std::string, std::string>& ctx);

    // route event: ims call the funcion
    ims::CcResultT SendRouteEvent(const ims::RouteEventT& event,
                                  const std::map<std::string, std::string>& ctx);

    ims::CcResultT SendOtherEvent(const ims::OtherEventT& event,
                                  const std::map<std::string, std::string>& ctx);
};

#endif
