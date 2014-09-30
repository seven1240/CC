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

#ifndef _IVR_IVRAPI_H_
#define _IVR_IVRAPI_H_

#include <ivr.h>
#include <common.h>
#include <ims/ims_struct.h>

// reloadconfig call back
class IvrApi_Imp : public ivr::ivrapi {
public:
    // reload config
    ivr::IvrResultT ReloadConfig(const ivr::ReloadFlagT& type, const str2str_map& ctx);
    ivr::IvrResultT StartFlow(const std::string& flowname, const std::string& flowvars,
                              const str2str_map& ctx);
    ivr::IvrResultT Heartbeat(std::string& ivrinfo, const str2str_map& ctx);
};

// reload config server, create a bgcc server to wait reload command
class ivr_reload_server {
    typedef bgcc::SharedPointer<bgcc::Thread> thread_ptr;
public:
    ivr_reload_server(uint32_t port)
        : _port(port)
        , _svr(NULL)
        , _shutdown(true) {
    }

    virtual ~ivr_reload_server() {
    }
public:
    // start a server in new thread
    virtual uint32_t start();

    // stop the sever
    virtual void shutdown();
private:
    int32_t _thread_fun();
protected:
    uint32_t _port;
    bgcc::EpollServer* _svr;
    bool _shutdown;
protected:
    thread_ptr _server_thread;
};

#endif
