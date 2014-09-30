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

#ifndef  __QUEUE_H_
#define  __QUEUE_H_

#include <deque>

#include "lock.h"

template<class T>
class safequeue_t {
public:
    bool put(const T& item) {
        rw_lock_t lock(_rwlock, true);

        if (!lock.locked()) {
            return false;
        }

        _q.push_back(item);

        return true;
    }

    bool get(T& ret) {
        rw_lock_t lock(_rwlock, true);

        if (!lock.locked()) {
            return false;
        }

        if (_q.empty()) {
            return false;
        }

        ret = _q.front();
        _q.pop_front();
        return true;
    }

    size_t size() const {
        rw_lock_t lock(_rwlock);

        if (!lock.locked()) {
            return 0;
        }

        return _q.size();
    }

    bool clear() {
        rw_lock_t lock(_rwlock, true);

        if (!lock.locked()) {
            return false;
        }

        _q.clear();

        return true;
    }

private:
    mutable pthread_rwlock_t    _rwlock;

    std::deque<T>       _q;
};


#endif  //__QUEUE_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
