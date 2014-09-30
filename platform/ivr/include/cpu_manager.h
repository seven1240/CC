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

#ifndef _CPU_MANAGER_H_
#define _CPU_MANAGER_H_

#include "common.h"

class CpuManager {
public:
    CpuManager();
    virtual ~CpuManager();

    struct CPU_INFO {
        char name[20];
        uint32_t user;
        uint32_t nice;
        uint32_t system;
        uint32_t idle;
    };

public:
    static CpuManager* get_instance();

    //获取cpu占用率
    uint32_t get_cpu_occupy();

    //计算CPU占用率线程 阻塞函数
    void calculate_cpu_occupy_block_func();

private:
    //获取cpu信息
    void get_cpu_info(CPU_INFO* cpust);
    //通过cpu信息进行计算
    uint32_t calc_cpu_info(CPU_INFO* first, CPU_INFO* second);

private:
    uint32_t _cpu_occupy;
    pthread_rwlock_t _rwlock;  //_cpu_occupy 变量的读写锁
};

#endif
