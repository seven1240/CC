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
#ifndef  __RW_LOCK_H_
#define  __RW_LOCK_H_

#include <errno.h>
#include <pthread.h>
/**
* @brief 读写锁封装
*   detail description
*
*/
class rw_lock_t {
public:
    /**
     * @brief 构造并加锁
     *
     * @param [in/out] mutex   : pthread_mutex_t&
     * @param [in/out] write   : bool
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 22:47:18
    **/
    rw_lock_t(pthread_rwlock_t& mutex, bool write = false): _mutex(mutex), _locked(false) {
        if (write) {
            _locked = (pthread_rwlock_wrlock(&_mutex) == 0);
        } else {
            _locked = (pthread_rwlock_rdlock(&_mutex) == 0);
        }
    }
    /**
     * @brief 析构并解锁
     *
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 22:48:10
    **/
    ~rw_lock_t() {
        unlock();
    }

    void unlock() {
        if (_locked) {
            pthread_rwlock_unlock(&_mutex);
            _locked = false;
        }
    }

    /**
     * @brief 判断是否加锁成功
     *
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/11/16 22:57:36
    **/
    bool locked() const {
        return _locked;
    }

private:
    pthread_rwlock_t& _mutex;    ///<锁
    bool _locked;          ///<是否加锁
};


#endif  //__RW_LOCK_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
