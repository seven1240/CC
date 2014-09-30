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

#ifndef _IVR_LOCK_H_
#define _IVR_LOCK_H_

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

/**
* @brief 普通锁封装
*   detail description
*
*/
class lock_t {
public:
    /**
     * @brief 构造并加锁
     *
     * @param [in/out] mutex   : pthread_mutex_t&
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/28 16:00:51
    **/
    lock_t(pthread_mutex_t& mutex): _mutex(mutex) {
        _locked = (pthread_mutex_lock(&_mutex) == 0);
    }
    /**
     * @brief 释放并解锁
     *
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/28 16:00:55
    **/
    ~lock_t() {
        pthread_mutex_unlock(&_mutex);
    }
    /**
     * @brief 返回是否加锁
     *
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/28 16:00:58
    **/
    bool locked() const {
        return _locked;
    }
private:
    pthread_mutex_t& _mutex;          ///<  锁对象
    bool _locked;         ///<是否加锁
};

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
     * @date 2011/08/28 14:54:44
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
     * @date 2011/08/28 14:54:49
    **/
    ~rw_lock_t() {
        pthread_rwlock_unlock(&_mutex);
        _locked = false;
    }

    /**
     * @brief 判断是否加锁成功
     *
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/28 14:57:36
    **/
    bool locked() const {
        return _locked;
    }

private:
    pthread_rwlock_t& _mutex;    ///<锁
    bool _locked;          ///<是否加锁
};

class sem_lock_t {
public:
    sem_lock_t(sem_t& sem): _sem(sem) {
    }

    bool wait()const {
        int32_t ret = 0;

        do {
            ret = sem_wait(&_sem);
        } while (-1 == ret && EINTR == errno);

        return 0 == ret;
    }
    bool post()const {
        int32_t ret = 0;

        do {
            ret = sem_post(&_sem);
        } while (-1 == ret && EINTR == errno);

        return 0 == ret;
    }
private:
    mutable sem_t& _sem;
};

#endif
