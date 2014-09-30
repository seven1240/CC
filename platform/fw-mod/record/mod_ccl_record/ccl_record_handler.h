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

#ifndef  __CCL_RECORD_HANDLER_H_
#define  __CCL_RECORD_HANDLER_H_

#include <string>
#include "safemap.h"
#include "safequeue.h"

class ccl_record_handler_t {
public:
    static ccl_record_handler_t* instance() {
        static ccl_record_handler_t handler;
        return &handler;
    }

    /**
     * @brief 开始录音任务处理
     *
     * @param [in/out] uuid   : const char*
     * @param [in/out] filename   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/06 17:25:04
    **/
    bool on_record_start(const char* uuid, const char* filename);


    /**
     * @brief 结束录音任务处理
     *
     * @param [in/out] uuid   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/06 17:25:27
    **/
    bool on_record_stop(const char* uuid);

    /**
     * @brief 获取可处理的任务
     *
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/06 17:24:51
    **/
    std::string get_task();

    /**
     * @brief 添加失败的任务
     *
     * @return  void
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/08 16:13:38
    **/
    void add_failtask(const char* s);

    /**
     * @brief 获取需要重试的任务
     *
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/08 16:54:20
    **/
    std::string get_failtask();

    bool clear_failtask();

    bool execute_task(const char* task);

private:
    ccl_record_handler_t() {}

    safemap_t<std::string, std::string> _tmp_tasks;
    safequeue_t<std::string> _tasks;
    safequeue_t<std::string> _failtasks;
};

#endif  //__CCL_RECORD_HANDLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
