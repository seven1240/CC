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


#pragma once

#include "callback.h"

class acd_ims_callback : public ims::event_callback {
public:
    virtual ims::CcResultT SendCallEvent(const ims::CallEventT& event,
                                         const std::map<std::string, std::string>& ctx);

    virtual ims::CcResultT SendMediaEvent(const ims::MediaEventT& event,
                                          const std::map<std::string, std::string>& ctx);

    virtual ims::CcResultT SendRouteEvent(const ims::RouteEventT& event,
                                          const std::map<std::string, std::string>& ctx);

    virtual ims::CcResultT SendOtherEvent(const ims::OtherEventT& event,
                                          const std::map<std::string, std::string>& ctx);
};
