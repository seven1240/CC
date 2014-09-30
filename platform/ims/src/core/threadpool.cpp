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

#include "threadpool.h"
#include "event_handler.h"
#include "ims_log.h"

using namespace bgcc;
namespace ims {

threadpool_t::threadpool_t(int32_t size, int32_t timeout):
    _size(size),
    _timeout(timeout) {
}

threadpool_t::~threadpool_t() {
    this->stop();
    _threads.clear();
}

void threadpool_t::start() {
    if (_isstart) {
        WARNING_LOG("threadpool_t already started, do nothing.");
        return;
    }

    TRACE_LOG("threadpool_t start size:%d, tasktimeout:%d", _size, _timeout);

    for (int32_t i = 0; i < _size; ++i) {
        TRACE_LOG("threadpool_t starting session thread [%d]", i);
        event_handler_ptr handler(new event_handler_t(_timeout));
        session_thread_ptr thrd(new session_thread_t(handler));
        thrd->start();
        _threads.push_back(thrd);
    }

    TRACE_LOG("threadpool_t start ok");
    _isstart = true;
}

void threadpool_t::stop() {
    std::vector<session_thread_ptr>::iterator it;

    for (it = _threads.begin(); it != _threads.end(); ++it) {
        dynamic_cast<event_handler_t*>((*it)->get_runner().get())->shutdown();
        (*it)->join();
    }
}

session_thread_ptr threadpool_t::get_prefer_thread() {
    Guard<Mutex>  lock(&_mutex);
    std::vector<session_thread_ptr>::const_iterator it;
    session_thread_ptr target;
    int32_t min = -1;
    int32_t cur = 0;

    for (it = _threads.begin(); it != _threads.end(); ++it) {
        cur = (*it)->get_session_count();

        if (cur < min || min < 0) {
            min = cur;
            target = *it;
        }
    }

    return target;
}


}














/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
