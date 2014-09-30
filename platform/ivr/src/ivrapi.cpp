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

#include <ivrapi.h>
#include <conf_manager.h>
#include <threadtools.h>
#include "thread_pool.h"
#include "autodial_chan_thread.h"
#include "cpu_manager.h"
#include "lock.h"
#include "common.h"

extern std::auto_ptr<ConfManager> g_conf_manager;
ivr::IvrResultT IvrApi_Imp::ReloadConfig(const ivr::ReloadFlagT& type,
        const std::map<std::string, std::string>& ctx) {
    IVR_DEBUG("server receive reload event(%s)", type.get_desc().c_str());

    if (g_conf_manager.get() != NULL) {
        return ivr::IvrResultT(g_conf_manager->reload_conf(type));
    }

    return ivr::IvrResultT::ResFailed;
}

ivr::IvrResultT IvrApi_Imp::StartFlow(const std::string& flowname, const std::string& flowvars,
                                      const str2str_map& ctx) {
    // create new thread
    IVR_TRACE("[startflow] flowname(%s), vars(%s)", flowname.c_str(), flowvars.c_str());
    {
        // check can create new flow
        rw_lock_t lock(g_autodial_chan_rwlock, false);

        if (lock.locked()) {
            if (g_autodial_chan_num >= g_inbound_conf.max_autodial_chan_num) {
                IVR_WARN("can't start flow: chan num(%d) >= max(%d)",
                         g_autodial_chan_num, g_inbound_conf.max_autodial_chan_num);
                return ivr::IvrResultT::ResNoEnoughResource;
            }
        } else {
            IVR_WARN("lock failed!~");
            return ivr::IvrResultT::ResFailed;
        }
    }

    {
        // find dest flow
        rw_lock_t lock(g_inbound_conf_rwlock, false);

        if (!lock.locked()) {
            IVR_WARN("failed lock!");
            return ivr::IvrResultT::ResFailed;
        }

        if (g_inbound_conf.dnis_script_map.find(flowname) == g_inbound_conf.dnis_script_map.end()) {
            IVR_TRACE("not found matched auto dial flow(%s)", flowname.c_str());
            return ivr::IvrResultT::ResInvalidParam;
        }
    }

    // check flow is exists
    inbound_script_t* param = new(std::nothrow)inbound_script_t;

    if (param == NULL) {
        IVR_WARN("alloc script object failed!");
        return ivr::IvrResultT::ResNoEnoughResource;
    }

    param->type = base_script_t::INBOUND;
    param->fid = (uint32_t) - 1;
    param->ani = "";
    param->dnis = flowname;
    param->callid = CREATE_SESSION_EMPTY_CALLID;
    param->channel_id = CREATE_SESSION_EMPTY_CALLID;
    param->imsno = (uint32_t) - 1;
    param->imssid = 0;
    param->requestId = 0;
    param->dialdata = flowvars;
    AutoDialChanThread* autodial_thread = new AutoDialChanThread(param); // thread pool will delete it
    ThreadPool* threadpool = ThreadPool::get_instance();
    IVR_DEBUG("assign worker");

    if (threadpool->assign_work(autodial_thread)) {
        IVR_TRACE("input a new autodial worker(%p)", param);
    } else {
        IVR_WARN("assign new autodial worker(%p) failed!", autodial_thread);
        delete autodial_thread;
        autodial_thread = NULL;
        return ivr::IvrResultT::ResNoEnoughResource;
    }

    return ivr::IvrResultT::ResSuccess;
}

ivr::IvrResultT IvrApi_Imp::Heartbeat(std::string& ivrinfo, const str2str_map& ctx) {
    // get ivr information
    std::ostringstream oss;
    oss << "{"
        << "\"cpu\":" << CpuManager::get_instance()->get_cpu_occupy() << ","
        << "\"inbound-chan\":" << g_inbound_chan_num << ","
        << "\"autorun-chan\":" << g_autorun_chan_num << ","
        << "\"autodial-chan\":" << g_autodial_chan_num << ","
        << "\"flowdetail\":[";
    bool is_first = true;
    {
        // get inbound information
        rw_lock_t lock(g_inbound_conf_rwlock, false);

        if (lock.locked()) {
            for (std::map<std::string, inbound_script_t>::const_iterator iter =
                        g_inbound_conf.dnis_script_map.begin();
                    iter != g_inbound_conf.dnis_script_map.end(); ++ iter) {
                if (iter->second.flow != NULL) {
                    if (!is_first) {
                        oss << ",";
                    } else {
                        is_first = false;
                    }

                    oss << "{\"" << iter->first << "\":" << iter->second.flow->ref_count - 1 << "}";
                }
            }
        } else {
            IVR_WARN("lock failed!");
        }
    }
    oss << "]}";

    ivrinfo = oss.str();
    return 0;
}

uint32_t ivr_reload_server::start() {
    if (!_shutdown) {
        IVR_WARN("ivr reload thread is running!");
        return 1;
    }

    _shutdown = false;
    _svr = NULL;

    _server_thread = smart_thread(mem_fun_call(&ivr_reload_server::_thread_fun, *this));

    _server_thread->start();
    // wait server started
    int32_t retry_times = 100;

    while (NULL == _svr && --retry_times > 0) {
        usleep(1000);
    }

    usleep(100 * 1000);

    if (NULL != _svr) {
        IVR_TRACE("ivr reload server may be ok now!");
    } else {
        IVR_WARN("ivr reload server not ok now!");
    }

    return IVR_SUCCESS;
}

int32_t ivr_reload_server::_thread_fun() {
    bgcc::SharedPointer<IvrApi_Imp> cimp(new(std::nothrow)IvrApi_Imp());
    bgcc::SharedPointer<bgcc::IProcessor> xp(new ivr::ivrapiProcessor(cimp));
    bgcc::ServiceManager sm;
    sm.add_service(xp);

    bgcc::ThreadPool tp;
    tp.init(2);
    bgcc::EpollServer svr(&sm, &tp, _port);

    // start event receive serve
    _svr = &svr;
    IVR_TRACE("ivr reload server start to server!");

    if (0 != svr.serve()) {
        tp.terminate();
        IVR_TRACE("ivr reload server failed with unknown reason!");
    } else {
        IVR_TRACE("ivr reload server stoped!");
    }

    _svr = NULL;
    return 0;
}

void ivr_reload_server::shutdown() {
    if (NULL != _svr) {
        IVR_TRACE("try to shutdown ivr reload server !");
        _svr->stop();
        // wait server stop
        int32_t retry_times = 1000;

        do {
            usleep(1000);
        } while (_svr != NULL && -- retry_times > 0);

        if (_svr != NULL) {
            _svr = NULL;
            IVR_WARN("ivr reload server server has not stoped!");
        } else {
            IVR_TRACE("ivr reload server has stoped!");
        }
    }

    if (_server_thread.get() != NULL) {
        // wait thread stop
        //_server_thread->join();
        IVR_TRACE("must reset thread when using bgcc1.0");
        // _server_thread = thread_ptr(NULL);
        //if(retry_times > 0) _server_thread = thread_ptr(NULL);
        //else memset(&_server_thread, 0, sizeof(_server_thread));
        IVR_TRACE("ivr reload server had shutdown!");
    }

    _shutdown = true;
}
