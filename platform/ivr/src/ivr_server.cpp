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

#include "lock.h"
#include "common.h"
#include "ini_file.h"
#include "node_base.h"
#include "thread_pool.h"
#include "conf_manager.h"
#include "inbound_chan_thread.h"
#include "autorun_chan_thread.h"
#include "arithmetic_operate.h"
#include "calldata_manager.h"
#include "cpu_manager.h"
#include "autorun_manager.h"

#include "ivr_timer.h"
#include "ivrapi.h"

#include <getopt.h>

#ifndef SCMPF_MODULE_VERSION
#define SCMPF_MODULE_VERSION "undefined"
#endif

static const char* cut_path(const char* in) {
    const char* p, *ret = in;
    char delims[] = "/\\";
    char* i;

    for (i = delims; *i; i++) {
        p = in;

        while ((p = strchr(p, *i)) != 0) {
            ret = ++p;
        }
    }

    return ret;
}

void esl_log_ivr(const char* file, const char* func, int line, int level, const char* fmt, ...) {
    if (0 == g_output_esllog) {
        // disable esl log file
        return;
    }

    const char* fp;
    char* data;
    va_list ap;
    int ret;

    fp = cut_path(file);

    va_start(ap, fmt);

    ret = vasprintf(&data, fmt, ap);

    if (ret != -1) {
        //wangtingdel com_writelog("esl", "%s:%d %s() %s",fp,line,func,data);
        BGCC_WARN("esl", "%s:%d %s() %s", fp, line, func, data);
        /*
        if(level<=3){//ERROR
            IVR_FATAL("%s:%d %s() %s", fp, line, func, data);
        }
        else if(4==level){//WARING
            IVR_WARN("%s:%d %s() %s", fp, line, func, data);
        }
        else if(5==level){//NOTICE
            IVR_NOTICE("%s:%d %s() %s", fp, line, func, data);
        }
        else if(6==level){//trace
            IVR_TRACE("%s:%d %s() %s", fp, line, func, data);
        }
        else{//DEBUG
            IVR_DEBUG("%s:%d %s() %s", fp, line, func, data);
        }
        */
        free(data);
    }

    va_end(ap);
}

//IVR呼入请求处理 回调函数
void inbound_callback(esl_socket_t server_sock,
                      esl_socket_t client_sock, struct sockaddr_in* addr) {
    esl_handle_t handle;
    string callid;

    bzero(&handle, sizeof(esl_handle_t));

    if (ESL_SUCCESS != esl_attach_handle(&handle, client_sock, addr)) {
        IVR_WARN("attach handle failed");
        esl_disconnect(&handle);
        return;
    }

    if (!handle.connected) {
        IVR_WARN("get callid failed");
        esl_disconnect(&handle);
        return;
    }

    callid = esl_event_get_header(handle.info_event, "caller-unique-id");
    IVR_DEBUG("CALLID = %s", callid.c_str());
    // load_balance_mod 的请求、caller-unique-id == "xyz" 返回cpu占用率和通道数量
    // ivr_monitor_mod 的请求、caller-unique-id == "opq" 返回cpu占用率和通道数量
    int32_t idtype = 0;

    if (strcasecmp(callid.c_str(), "xyz") == 0) {
        idtype = 1;
    } else if (strcasecmp(callid.c_str(), "opq") == 0) {
        idtype = 2;
    }

    //
    if (idtype != 0) {
        uint32_t inbound_chan_num_cp = 0;
        uint32_t cpu = CpuManager::get_instance()->get_cpu_occupy();
        std::string err;
        char resp[20] = {0};
        bzero(resp, 20);

        {
            rw_lock_t lock(g_inbound_chan_rwlock);

            if (lock.locked()) {
                inbound_chan_num_cp = g_inbound_chan_num;
            } else {
                err = "lock inbound num failed";
            }
        }

        if (err.length()) {
            IVR_WARN("%s", err.c_str());
        }

        // cann't change format of this string, because monitor and ivrloadbanlance use this string
        snprintf(resp, 20, "cpu=%02u,chan=%05u", cpu, inbound_chan_num_cp);
        esl_send(&handle, resp);

        IVR_DEBUG("ivr-%s-resp = %s", (idtype == 1 ? "loadbalance" : "monitor"), resp);
    }

    esl_disconnect(&handle);
    return;
}

// Event Socket 线程函数
void* esl_listen_thread_func(void* arg) {
    if (ESL_SUCCESS != esl_listen(g_server_ip.c_str(), g_server_port, inbound_callback)) {
        IVR_FATAL("esl_listen return fail");
        //raise(SIGKILL);
        _exit(0);
        //exit (0); //直接结束进程
    }

    return NULL;
}

//将话单生成到文件 线程函数
void* calldata_to_file_thread_func(void* arg) {
    CallDataManager* calldata_manager = CallDataManager::get_instance();
    calldata_manager->calldata_to_file_block_func();
    return NULL;
}

//计算CPU占用率 线程函数
void* calc_cpu_occupy_thread_func(void* arg) {
    CpuManager* cpu_manager = CpuManager::get_instance();
    cpu_manager->calculate_cpu_occupy_block_func();
    return NULL;
}

//输出运行时信息 线程函数
void* disp_runinfo_thread_func(void* arg) {
    CpuManager* cpu_manager = CpuManager::get_instance();
    uint32_t cpu = 0;
    uint32_t inbound_chan = 0;
    uint32_t autorun_chan = 0;
    uint32_t autodial_chan = 0;

    while (!g_stopped) {
        cpu = cpu_manager->get_cpu_occupy();

        {
            rw_lock_t lock1(g_inbound_chan_rwlock);

            if (lock1.locked()) {
                inbound_chan = g_inbound_chan_num;
            }
        }

        {
            rw_lock_t lock2(g_autorun_chan_rwlock);

            if (lock2.locked()) {
                autorun_chan = g_autorun_chan_num;
            }
        }

        {
            rw_lock_t lock3(g_autodial_chan_rwlock);

            if (lock3.locked()) {
                autodial_chan = g_autodial_chan_num;
            }
        }

        IVR_TRACE("cpu:%u\tinbound-channel:%u\tautorun-channel:%u\tautodial-channel:%u",
                  cpu, inbound_chan, autorun_chan, autodial_chan);
        ivr_tools_t::safe_sleeps(6);
    }

    return NULL;
}

//自启动流程控制 线程函数
void* autorun_script_manager_thread_func(void* arg) {
    AutoRunManager* autorun_manager = AutoRunManager::get_instance();
    uint32_t autorun_script_num = g_autorun_conf.autorun_script_vec.size();

    for (uint32_t i = 0; i < autorun_script_num; i++) {
        autorun_manager->begin(i);
    }

    return NULL;
}

//信号处理
void sig_handler(int32_t signum) {
    if (signum == SIGINT) {
        IVR_TRACE("发送停止线程信号");
        g_stopped = 1;

        //为了停止所有的线程，给每个线程一个虚拟的work触发线程函数的执行
        ThreadPool* threadpool = ThreadPool::get_instance();
        uint32_t max_chan_num = threadpool->get_max_thread_num();

        for (uint32_t i = 0; i < max_chan_num; i++) {
            inbound_script_t* basescript = new inbound_script_t;

            InboundChanThread* inbound_thread = new InboundChanThread(basescript);
            ThreadPool* threadpool = ThreadPool::get_instance();
            threadpool->assign_work(inbound_thread);
        }

        ivr_tools_t::safe_sleeps(1);
        sem_lock_t sem_lock(g_stop_sem);
        //        sem_post(&g_stop_sem);
        sem_lock.post();
    }
}

bool init_log() {
    std::string bgcclogpath = LOG_PATH;
    bgcclogpath += "bgcc.cfg";
    bgcc::log_open(bgcclogpath.c_str());
    IVR_TRACE("bgcc::log_open success!");

    /* int32_t ret = com_loadlog(LOG_PATH, "log.conf");
     if (ret != 0) {
         IVR_FATAL("com_openlog() = %d \n", ret);
         return false;
     }
     else {
         IVR_TRACE("com_openlog() success");
     }*/

    return true;
}


extern std::auto_ptr<ConfManager> g_conf_manager;

int32_t main(int32_t argc, char* argv[]) {
    char const* const short_options = "vh";
    struct option long_options[] = {
        { "version", 0, NULL, 'v'},
        { "help", 0, NULL, 'h'},
    };

    // is version command
    char ch = 0;

    while ((ch = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (ch) {
        case 'v':
            std::cout << "version: " << SCMPF_MODULE_VERSION << std::endl;
            return 0;

        case 'h':
            std::cout << "version " << SCMPF_MODULE_VERSION << "\n./{IVRSERVER}& run ivrserver" << std::endl;
            return 0;

        default:
            std::cerr << "ivrserver --version";
            return 0;
        }
    }

    sem_init(&g_stop_sem, 0, 0);

    signal(SIGPIPE, SIG_IGN);
    //signal(SIGINT, sig_handler);

    //esl_global_set_default_logger(0);

    if (!init_log()) {
        return FAILURE;
    }

    esl_global_set_logger(esl_log_ivr);

    g_conf_manager.reset(new ConfManager("conf/system.conf", "conf/inbound.conf", "conf/autorun.conf"));

    if (g_conf_manager->load_max_chan_num() != SUCCESS) {
        return FAILURE;
    }

    //获取最大通道数量
    uint32_t max_chan_num = g_inbound_conf.max_inbound_chan_num
                            + g_autorun_conf.max_autorun_chan_num;

    if (max_chan_num > MAX_THREAD_NUM) {
        IVR_FATAL("max_inbound_chan_num + max_autorun_chan_num > MAX_USER_THREAD");
        return FAILURE;
    }

    //初始化线程池
    ThreadPool* threadpool = ThreadPool::get_instance();
    threadpool->initialize_threads(max_chan_num);

    ivr_tools_t::safe_sleeps(1);//让线程池先初始化 等待一秒 否则线程输出日志太多

    IVR_TRACE("create thread_pool(%u) success", max_chan_num);

    //加载配置文件
    if (g_conf_manager->load_conf() != SUCCESS) {
        return FAILURE;
    }

    pthread_t thread_h = 0;

    //启动event socket监听线程
    if (pthread_create(&thread_h, NULL, esl_listen_thread_func, NULL) != 0) {
        IVR_FATAL("create esl listen thread failure");
        return FAILURE;
    }


    //启动话单文件生成线程
    if (pthread_create(&thread_h, NULL, calldata_to_file_thread_func, NULL) != 0) {
        IVR_FATAL("create generate calldata thread failure");
        return FAILURE;
    }

    //启动计算CPU占用率线程
    if (pthread_create(&thread_h, NULL, calc_cpu_occupy_thread_func, NULL) != 0) {
        IVR_FATAL("create calculate cpu occupy thread failure");
        return FAILURE;
    }

    //启动运行时信息输出线程
    if (pthread_create(&thread_h, NULL, disp_runinfo_thread_func, NULL) != 0) {
        IVR_FATAL("create display runinfo thread failure");
        return FAILURE;
    }

    //外呼通道的控制策略
    uint32_t num = g_autorun_conf.autorun_script_vec.size();

    for (uint32_t i = 0; i < num; i++) {
        AutoRunManager::get_instance()->begin(i);
    }

    // wait for reload
    ivr_reload_server svr(g_reload_port);

    if (g_reload_port != 0) {
        svr.start();
    }

#if IVR_ENABLE_DEBUGER
    extern void start_debug_server(int32_t);
    start_debug_server(g_server_port - 1);
#endif

    sem_lock_t stop_sem(g_stop_sem);
    stop_sem.wait();
    //    threadpool->destroy_pool(1);

    return SUCCESS;
}

