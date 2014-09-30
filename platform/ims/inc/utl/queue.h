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

#ifndef  __IMS_QUEUE_H_
#define  __IMS_QUEUE_H_

#include <deque>
#include <pthread.h>
#include <ims_log.h>
#include <time.h>
#include <ims_log.h>

namespace ims {

template<class T>
class queue_t {
public:
    queue_t(): _waitings(0) {
        int32_t ret = pthread_mutex_init(&this->_mutex, NULL);

        if (0 != ret) {
            WARNING_LOG("pthread_mutex_init error!");
        }

        ret = pthread_cond_init(&this->_cond, NULL);

        if (0 != ret) {
            WARNING_LOG("pthread_cond_init error!");
        }
    }

    ~queue_t() {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

    /**
     * @brief put the element to the end of the queue
     *
     * @param [in] item   : const T&
     * @return  void
     * @retval
     * @see
     * @note
     **/
    void put(const T& item) {
        pthread_mutex_lock(&_mutex);
        _q.push_back(item);
        pthread_mutex_unlock(&_mutex);

        if (_waitings > 0) {
            pthread_cond_signal(&_cond);
        }
    }

    void insert(const T& item) {
        pthread_mutex_lock(&_mutex);
        _q.push_front(item);
        pthread_mutex_unlock(&_mutex);

        if (_waitings > 0) {
            pthread_cond_signal(&_cond);
        }
    }

    /**
     * @brief get an element from the front of the quue
     *
     * @param [out] ret : T&
     * @param [in] timeout : millisecond
     * @return  bool
     * @retval
     * @see
     * @note
     **/
    bool get(T& ret, int32_t timeout = 0) {
        pthread_mutex_lock(&_mutex);
        ++_waitings;

        if (_q.empty()) {
            if (timeout > 0) {
                struct timespec abstime;
                clock_gettime(CLOCK_REALTIME, &abstime);
                abstime.tv_sec += timeout / 1000;
                abstime.tv_nsec += (timeout % 1000) * 1000000;
                pthread_cond_timedwait(&_cond, &_mutex, &abstime);
            }
        }

        if (_q.empty()) {
            --_waitings;
            pthread_mutex_unlock(&_mutex);
            return false;
        }

        ret = _q.front();
        _q.pop_front();
        --_waitings;
        pthread_mutex_unlock(&_mutex);
        return true;
    }


    /**
     * @brief
     *
     * @return  size_t
     * @retval
     * @see
     * @note
     **/
    size_t size() const {
        return _q.size();
    }

    void clear() {
        _q.clear();
    }
private:

    pthread_mutex_t     _mutex;

    pthread_cond_t      _cond;

    uint32_t            _waitings;

    std::deque<T>       _q;
};


}







#endif  //__QUEUE_H_


/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
