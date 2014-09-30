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

#include "session_thread.h"

using namespace bgcc;
namespace ims {

session_thread_t::session_thread_t(RunnableSP runner)
    : Thread(runner), _runner(runner) {
}

bool session_thread_t::attach_session(const SessionIdT& sid) {
    Guard<Mutex> lock(&_mutex);

    if (_sessions.find(sid) != _sessions.end()) {
        return false;
    }

    _sessions.insert(sid);
    return true;
}

bool session_thread_t::detach_session(const SessionIdT& sid) {
    Guard<Mutex> lock(&_mutex);

    if (_sessions.find(sid) == _sessions.end()) {
        return false;
    }

    _sessions.erase(sid);
    return true;
}

int32_t session_thread_t::get_session_count() {
    Guard<Mutex> lock(&_mutex);
    return _sessions.size();
}


};






/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
