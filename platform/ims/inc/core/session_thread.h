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

#ifndef  __WORK_THREAD_H_
#define  __WORK_THREAD_H_

#include <set>
#include <bgcc.h>

#include "common.h"

namespace ims {

class session_thread_t : public bgcc::Thread {
public:
    session_thread_t(bgcc::RunnableSP runner);

    bool attach_session(const SessionIdT& sid);

    bool detach_session(const SessionIdT& sid);

    int32_t get_session_count();

    bgcc::RunnableSP get_runner() {
        return _runner;
    }

private:

    bgcc::Mutex                 _mutex;
    std::set<SessionIdT>        _sessions;
    bgcc::RunnableSP            _runner;
};

typedef bgcc::SharedPointer<session_thread_t>  session_thread_ptr;

};





#endif  //__WORK_THREAD_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
