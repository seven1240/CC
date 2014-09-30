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

#include <errno.h>

#include "thread_pool.h"
#include "lock.h"
#include "tools.h"
#include "ivr_timer.h"


using namespace std;

pthread_mutex_t ThreadPool::_mutex_sync = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ThreadPool::_mutex_work_completion = PTHREAD_MUTEX_INITIALIZER;

ThreadPool::ThreadPool() {
    _max_thread_num = 0;
    _cur_thread_num = 0;
    _queue_size = 0;
    _unfinished_work = 0;

    sem_init(&_available_work, 0, 0);
    sem_init(&_available_threads, 0, _queue_size);
}

ThreadPool::~ThreadPool() {
}

ThreadPool* ThreadPool::get_instance() {
    ///<gcc默认的threadsafe-statics保证线程安全
    static ThreadPool pool;
    return &pool;
}

uint32_t ThreadPool::get_max_thread_num() {
    return this->_max_thread_num;
}

void ThreadPool::initialize_threads(uint32_t max_thread_num) {
    if (max_thread_num < 0) {
        max_thread_num = 0;
    }

    int32_t empty_works = 0;
    {
        IVR_TRACE("set thread pool size(%u)!", max_thread_num);
        ::lock_t lock(_mutex_sync);

        if (lock.locked()) {
            //空余20%的资源，20%以内的呼叫直接挂机，超过20%则不予响应
            uint32_t tmp = (uint32_t)((double)max_thread_num * 1.2) + 1;

            sem_lock_t lock_threads(_available_threads);

            for (uint32_t i = _max_thread_num; i < tmp; ++i) {
                pthread_t tempThread;
                ivr_thread_param_t* thr_param = new(std::nothrow) ivr_thread_param_t;

                if (thr_param == NULL) {
                    IVR_WARN("failed to new ivr_thread_param_t! exit at once!");
                    _exit(0);
                }

                thr_param->pool = this;
                thr_param->event_queue = new(std::nothrow) ivr_event_queue_t;
                //            thr_param->evt_sem = new(std::nothrow) sem_t;
                //            sem_init(thr_param->evt_sem, 0, 0);
                thr_param->timer = new(std::nothrow) IvrTimer;

                // fix bug: tcb not free after thread stoped
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

                if (pthread_create(&tempThread, &attr, &ThreadPool::thread_execute, (void*) thr_param) == 0) {
                    IVR_TRACE("create thread %u  %lu  success", i, tempThread);
                } else {
                    IVR_WARN("create thread %u  failure", i);
                }

                pthread_attr_destroy(&attr);

                // queue size update
                lock_threads.post();
                ++ _cur_thread_num;
            }

            // if now < max, add some empty works
            if (tmp < _max_thread_num && _worker_queue.empty()) {
                empty_works = (int32_t)(_max_thread_num - tmp);
                empty_works -= std::max(0, (int32_t)(tmp - _cur_thread_num));
            }

            _max_thread_num = tmp;
            //_queue_size = tmp;
        } else {
            IVR_WARN("locked failure");
        }
    }

    IVR_TRACE("add empty works(%d)", empty_works);

    for (int32_t i = 0; i < empty_works; ++ i) {
        assign_work(NULL);
    }
}

void ThreadPool::destroy_pool(int max_poll_second = 2) {
    while (_unfinished_work > 0) {
        ivr_tools_t::safe_sleeps(max_poll_second);
    }

    sem_destroy(&_available_work);
    sem_destroy(&_available_threads);
    pthread_mutex_destroy(&_mutex_sync);
    pthread_mutex_destroy(&_mutex_work_completion);
}


bool ThreadPool::assign_work(WorkerThread* worker_thread) {
    sem_lock_t lock_sem(_available_threads);

    if (!lock_sem.wait()) {
        return false;
    }

    ::lock_t lock2(_mutex_sync);

    if (!lock2.locked()) {
        return false;
    }

    ::lock_t lock(_mutex_work_completion);

    if (!lock.locked()) {
        return false;
    }

    _worker_queue.push(worker_thread);
    _unfinished_work++;
    IVR_TRACE("unfinished_work = %u", _unfinished_work);
    IVR_TRACE("push worker address:[%p]", worker_thread);

    sem_lock_t lock_work(_available_work);
    return lock_work.post();
}

bool ThreadPool::fetch_work(WorkerThread** worker) {
    sem_lock_t lock_work(_available_work);

    if (!lock_work.wait()) {
        return false;
    }

    ::lock_t lock(_mutex_sync);

    if (!lock.locked()) {
        return false;
    }

    IVR_TRACE("QUEUE SIZE:%lu", _worker_queue.size());
    *worker = _worker_queue.front();
    _worker_queue.pop();
    IVR_TRACE("fetch work (%p)", *worker);

    sem_lock_t lock_thread(_available_threads);
    return lock_thread.post();
}

void* ThreadPool::thread_execute(void* param) {
    //   com_openlog_r();
    WorkerThread* worker = NULL;
    ivr_thread_param_t* thr_param = (ivr_thread_param_t*)param;
    session_dynamic_resource_t task_param;

    while (thr_param->pool->fetch_work(&worker)) {

        if (g_stopped) {
            IVR_TRACE("thread [%lu] terminated!", pthread_self());
            break;
        }

        if (worker) {
            task_param.event_queue = thr_param->event_queue;

            IVR_DEBUG("thread_execute event queue pointer %lu, queue size: %lu",
                      (uint64_t)task_param.event_queue, task_param.event_queue->size());

            // task_param.sem = thr_param->evt_sem;
            task_param.timer = thr_param->timer;

            if (task_param.timer != NULL) {
                task_param.timer->clear_all_timer();
            }

            IVR_TRACE("pop worker address:[%lu]", (uint64_t)worker);
            worker->execute(&task_param);
            delete worker;
            worker = NULL;
        }

        {
            ::lock_t lock(thr_param->pool->_mutex_work_completion);

            if (lock.locked()) {
                IVR_TRACE("thread [%lu] has finished a work!", pthread_self());
                thr_param->pool->_unfinished_work--;
            } else {
                IVR_WARN("locked failed");
            }
        }

        if (ThreadPool::get_instance()->is_too_many()) {
            IVR_TRACE("thread [%lu] don't need to run, terminated", pthread_self());
            break;
        }
    }

    // delete params
    IVR_DEBUG("free thread [%lu]'s resource(event queue, timer, param)!", pthread_self());

    if (param != NULL) {
        if (thr_param->event_queue != NULL) {
            delete thr_param->event_queue;
            thr_param->event_queue = NULL;
        }

        if (thr_param->timer != NULL) {
            delete thr_param->timer;
            thr_param->timer = NULL;
        }

        delete thr_param;
        param = NULL;
    }

    IVR_TRACE("thread [%lu] Terminated!", pthread_self());
    ThreadPool::get_instance()->thread_end();
    return 0;
}

bool ThreadPool::is_too_many() const {
    ::lock_t lock(_mutex_sync);

    if (lock.locked()) {
        IVR_DEBUG("too many? current(%u), max(%u)", _cur_thread_num, _max_thread_num);
        return _max_thread_num < _cur_thread_num;
    } else {
        IVR_TRACE("locked failed!");
    }

    return false;
}

void ThreadPool::thread_end() {
    IVR_TRACE("thread [%lu] end", pthread_self());
    ::lock_t lock(_mutex_sync);

    if (lock.locked()) {
        -- _cur_thread_num;
    } else {
        IVR_TRACE("locked failed!");
    }
}
