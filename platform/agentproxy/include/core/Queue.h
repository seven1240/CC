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

#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include <bgcc.h>

#ifndef _WIN32
#include <errno.h>
#endif
using namespace bgcc;
template <typename ElementType>

class Queue {
public:

    typedef Guard<Mutex> ScopeGuard;

    Queue() {}

    bool put(const ElementType& item) {
        ScopeGuard guard(&_mutex);

        try {
            _q.push_back(item);
        } catch (std::bad_alloc&) {
            /*记录日志*/
            BGCC_NOTICE("ap", "Queue Put item fail.");
            return false;
        }

        _sema.signal();
        return true;
    }

    bool get(ElementType& ret, int32_t timeout = 0) {
        int32_t rv = _sema.wait(timeout);

        if (0 != rv) {
            return false;
        }

        {
            ScopeGuard guard(&_mutex);
            ret = _q.front();
            _q.pop_front();

        }

        return true;

    }

    int32_t size() {
        ScopeGuard guard(&_mutex);
        return _q.size();
    }

    void clear() {
        ScopeGuard guard(&_mutex);
        _q.clear();
        return;
    }
private:

    Mutex                        _mutex;       /** 互斥量*/
    Semaphore                    _sema;        /** 条件变量*/
    std::deque<ElementType>      _q;           /** 队列*/
};


#endif // QUEUE_H

