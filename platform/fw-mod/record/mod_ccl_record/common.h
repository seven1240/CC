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

#ifndef  __STRUCT_H_
#define  __STRUCT_H_

#include <switch.h>

#define LEN_255 (255)

typedef struct _tasklist_t {
    char task[LEN_255 + LEN_255 + 1];
    struct _tasklist_t* next;
} tasklist_t;

typedef struct _global_info {
    switch_memory_pool_t* pool;
    switch_thread_rwlock_t* rwlock;
    switch_event_node_t* reload_node;
    switch_event_node_t* start_node;
    switch_event_node_t* end_node;
    switch_thread_t** threads;
    switch_thread_t** failthreads;
    uint32_t failthreads_count;

    int32_t running;

    char rec_basedir[LEN_255 + 1];
    uint32_t max_thread;
    char dest_basedir[LEN_255 + 1];

    tasklist_t* task;

} global_info_t;













#endif  //__STRUCT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
