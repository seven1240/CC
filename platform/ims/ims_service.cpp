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

#include <stdio.h>
#include <unistd.h>
#include <bgcc.h>

#include "ims_log.h"
#include "ims_core_session_mgr.h"
#include "ims_conf_loader.h"

#include "fs_mgr.h"
#include "fs_info.h"

#include "threadpool.h"
#include "ims.h"
#include "imsapi_impl.h"

#include <getopt.h>

using namespace ims;
using namespace bgcc;

void sig_handler(int signum) {
    if (SIGINT == signum) {
        ims_session_manager_t::instance()->stop();
    }
}
#if defined(__DATE__) && defined(__TIME__)
#define BUILD_DATE  (__DATE__ " " __TIME__)
#else
#define BUILD_DATE  "unknown"
#endif


int main(int argc, char** argv) {

    signal(SIGPIPE, SIG_IGN);

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
            std::cout << VERSION << std::endl;
            return 0;

        case 'h':
            std::cout << "./{ims_server}& run ims_server" << std::endl;
            return 0;

        default:
            std::cerr << "ims_server --version";
            return 0;
        }
    }

    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    //读取配置
    ims_conf_t& conf = pmgr->config();

    if (!ims_conf_loader_t::instance()->load_conf(pmgr->pool(), conf)) {
        FATAL_LOG("load config file failed");
        return -1;
    }

    NOTICE_LOG("ims server starting(version : %s , build time : %s" , VERSION , BUILD_DATE);

    //open bgcc log
    std::string bgcclog = "bgcc.cfg";
    bgcc::log_open(bgcclog.c_str());
    TRACE_LOG("bgcc::log_open success!");

    fs_mgr_t::instance()->update_log(conf.gw_log);
    TRACE_LOG("load configure file ok");

    const char* tmp = NULL;

    if (conf.param.count(ICPT_MAXSESSION) != 0 && conf.param[ICPT_MAXSESSION] != NULL) {
        tmp = conf.param[ICPT_MAXSESSION];
        pmgr->maxsession((uint32_t)atoi(tmp));
    } else {
        pmgr->maxsession(2000);
    }

    TRACE_LOG("starting freeswitch manager...");
    //fs_mgr启动
    std::list<ims_conf_gw_node_t*>& gws = conf.gateway;
    ims_conf_gw_node_t* gw_node;

    for (std::list<ims_conf_gw_node_t*>::iterator it = gws.begin(); it != gws.end(); ++it) {
        if (gw_node = *it) {
            fs_info_t info(gw_node->id, gw_node->ip, gw_node->port, gw_node->max_conn,
                           gw_node->user, gw_node->pswd);

            if (IMS_SUCCESS != fs_mgr_t::instance()->add_fs(info)) {
                FATAL_LOG("load freeswitch(id=%u,ip=%u,port=%u,user=%s,pswd=%s) failed",
                          gw_node->id, gw_node->ip, gw_node->port, gw_node->user, gw_node->pswd);
                raise(SIGKILL);
            }

            TRACE_LOG("load freeswitch(%u,%u:%u) success", gw_node->id,  gw_node->ip, gw_node->port);
        }
    }

    //session thread_mgr start
    //
    TRACE_LOG("starting ims session thread pool...");
    session_thrd_mgr::instance()->start();

    TRACE_LOG("starting ims api service...");

    //启动主服务bgcc的端口监听
    std::map<ims_conf_service_type_t, ims_conf_server_t*>& service
        = conf.service;

    ims_conf_server_t* pserver = NULL;

    if (service.count(ICST_MONITOR) != 0) {
        //TODO 启动监控
    } else {
        WARNING_LOG("monitor service not started");
    }

    if (service.count(ICST_CONFIG) != 0) {
        //TODO 启动配置接口
    } else {
        WARNING_LOG("config service not started(dynamic config will disabled)");
    }


    if (service.count(ICST_MAIN) != 0 && service[ICST_MAIN] != NULL) {
        pserver = service[ICST_MAIN];
        //TODO 启动主服务程序
        TRACE_LOG("starting ims api service on port :%d", pserver->port);
        SharedPointer<IProcessor> ims_proc(new imsapiProcessor(SharedPointer<imsapi>(new imsapi_impl_t)));

        ServiceManager sm;
        sm.add_service(ims_proc);

        ThreadPool tp;
        int pool_size = 500; //set default to 500
        const char* tmp_poolsize = NULL;

        if (conf.param.count(ICPT_BGCCPOOLSIZE) != 0 && conf.param[ICPT_BGCCPOOLSIZE] != NULL) {
            tmp_poolsize = conf.param[ICPT_BGCCPOOLSIZE];
            pool_size = atoi(tmp_poolsize);
        }

        //if(argc == 2){
        //    pool_size = std::max(pool_size, atoi(argv[1]));
        //    TRACE_LOG("main service thread pool size: %d", pool_size);
        //}
        if (pool_size <= 0) {
            WARNING_LOG("main service thread pool size: %d <= 0, exiting...", pool_size);
            raise(SIGKILL);
        }

        TRACE_LOG("main service thread pool size: %d", pool_size);
        tp.init(pool_size);
        Server* server = new Server(&sm, &tp, pserver->port);

        if (NULL == server || 0 != server->serve()) {
            WARNING_LOG("ims api service exiting...");
            delete server;
            raise(SIGKILL);
        }

        delete server;
    } else {
        FATAL_LOG("ims api service config error");
        return -1;
    }

    ///////////////////servcie run////////////////////

    //////////////////////////////////////////////////

    //////////////////service stop////////////////////
    fs_mgr_t::instance()->clear_fs();
    WARNING_LOG("after clear fs...");

    return 0;
}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
