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

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "common.h"
#include "worker_thread.h"

/*
ThreadPool class manages all the ThreadPool related activities. This includes keeping track of idle threads and ynchronizations between all threads.
*/
class ThreadPool {
public:
    ThreadPool();
    virtual ~ThreadPool();

    static  ThreadPool* get_instance();

    void destroy_pool(int32_t max_poll_second);

    bool assign_work(WorkerThread* worker);
    bool fetch_work(WorkerThread** worker);

    void initialize_threads(uint32_t max_thread_num);
    uint32_t get_max_thread_num();

    bool is_too_many() const;
    void thread_end();

    static void* thread_execute(void* param);
private:
    uint32_t _max_thread_num;
    uint32_t _cur_thread_num;
    pthread_cond_t  _cond_crit;

private:
    static pthread_mutex_t _mutex_sync;
    queue<WorkerThread*> _worker_queue;

    static pthread_mutex_t _mutex_work_completion;
    uint32_t _unfinished_work;

    sem_t _available_work;

    sem_t _available_threads;
    uint32_t _queue_size;

};

#endif



