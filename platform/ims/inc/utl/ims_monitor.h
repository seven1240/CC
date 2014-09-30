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

#ifndef _IMS_MONITOR_H_
#define _IMS_MONUTOR_H_

#include <stdint.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include "ims_core_session_mgr.h"

class ims_monitor_t {

    /*
     * @bried 监控当前活动session
     * @param
     * @return 当前活动的session数量
     *
    **/
    static uint32_t monitor_sessioncount();
};

#endif
