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

#include "calldata_manager.h"
#include "lock.h"
#include "tools.h"

extern call_data_conf_t g_calldata_conf;

CallDataManager::CallDataManager() {
    pthread_mutex_init(&_mutex, NULL);
}

CallDataManager::~CallDataManager() {
    pthread_mutex_destroy(&_mutex);
}

CallDataManager* CallDataManager::get_instance() {
    ///<gcc默认的threadsafe-statics保证线程安全
    static CallDataManager mgr;
    return &mgr;
}

//将话单数据 push到队列中
void CallDataManager::push_calldata(const char* calldata) {
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        _calldata_deque.push_back(calldata);
    } else {
        IVR_TRACE("加锁失败,话单入队失败[%s]", calldata);
    }
}

//将临时文件 移动到 sendto 目录
bool CallDataManager::move_generate_sendto(const char* generate_filename) {
    time_t rawtime;
    time(&rawtime);

    char buffer[25];
    bzero(buffer, 25);
    struct tm* timeinfo = localtime(&rawtime);

    strftime(buffer, 25, "%Y-%m-%d-%H.%M.%S", timeinfo);

    string sendto_filename = g_calldata_conf.sendto_path + buffer + g_calldata_conf.file_name;

    if (ivr_tools_t::check_and_create_dir(g_calldata_conf.sendto_path.c_str())) {
        ostringstream ostm;
        ostm << "mv " << generate_filename << " " << sendto_filename;

        if (system(ostm.str().c_str()) == 0) {
            return true;
        }
    } else {
        IVR_WARN("mkdir %s failed", g_calldata_conf.sendto_path.c_str());
    }

    return false;
}

//将话单数据 生成到文件
void CallDataManager::calldata_to_file_block_func() {
    string calldata;
    string generate_filename = g_calldata_conf.generate_path + g_calldata_conf.file_name;

    ofstream fout;
    struct stat st;

    time_t begin_tm;
    time(&begin_tm);

    while (!g_stopped) {
        if (stat(generate_filename.c_str(), &st) == 0) {
            time_t now_tm;
            time(&now_tm);

            //当前时间-文件起始时间 大于配置阈值 则移动文件
            if ((now_tm - begin_tm) > g_calldata_conf.generate_interval) {
                IVR_TRACE("当前时间-文件起始时间 大于配置阈值 则移动文件");

                if (move_generate_sendto(generate_filename.c_str())) {
                    begin_tm = now_tm;
                }
            } else if (st.st_size > (g_calldata_conf.generate_file_size * 1024)) {
                //文件大小 大于配置阈值 则移动文件
                IVR_TRACE("文件大小 大于配置阈值 则移动文件");

                if (move_generate_sendto(generate_filename.c_str())) {
                    begin_tm = now_tm;
                }
            }
        }

        if (!ivr_tools_t::check_and_create_dir(g_calldata_conf.generate_path.c_str())) {
            IVR_WARN("mkdir %s failed", g_calldata_conf.generate_path.c_str());
            ivr_tools_t::safe_sleeps(2);
            continue;
        }

        fout.open(generate_filename.c_str(), ofstream::app | ofstream::out);

        if (fout.good()) {
            deque<string> to_write_queue;

            {
                ::lock_t lock(_mutex);

                if (lock.locked()) {
                    to_write_queue.assign(_calldata_deque.begin(), _calldata_deque.end());
                    _calldata_deque.clear();
                }
            }

            if (to_write_queue.size()) {
                for (deque<string>::iterator it = to_write_queue.begin();
                        it != to_write_queue.end(); ++it) {

                    fout << *it << "\n";
                }

            }
        } else {
            IVR_WARN("打开话单文件%s失败", generate_filename.c_str());
        }

        if (fout.is_open()) {
            fout << flush;
            fout.close();
        }

        ivr_tools_t::safe_sleeps(2);
    }

    return;
}
