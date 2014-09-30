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

#include <switch.h>
#include "ccl_record_handler.h"

bool ccl_record_handler_t::on_record_start(const char* uuid, const char* filename) {

    return _tmp_tasks.put(uuid, filename);
}


bool ccl_record_handler_t::on_record_stop(const char* uuid) {

    std::string filename;

    if (_tmp_tasks.get(uuid, filename)) {
        return _tasks.put(filename);
    }

    return true;
}

std::string ccl_record_handler_t::get_task() {
    if (_tasks.size() == 0) {
        return "";
    }

    std::string filename;

    if (_tasks.get(filename)) {
        return filename;
    }

    return "";
}

void ccl_record_handler_t::add_failtask(const char* s) {
    if (s && strlen(s)) {
        _failtasks.put(s);
    }
}

std::string ccl_record_handler_t::get_failtask() {
    if (_failtasks.size() == 0) {
        return "";
    }

    std::string filename;

    if (_failtasks.get(filename)) {
        return filename;
    }

    return "";
}

bool ccl_record_handler_t::clear_failtask() {
    return _failtasks.clear();
}

bool ccl_record_handler_t::execute_task(const char* task) {
    int32_t ret = system(task);

    if (ret < 0) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "fail %s, system return:%s\n", task, strerror(errno));
    } else if (ret == 0) {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG,
                          "succ %s\n", task);
        return true;
    } else {
        switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_WARNING,
                          "fail %s, command return:%d\n", task, ret);
    }

    return false;

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
