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

#ifndef _BIDL2SL_AP_H_
#define _BIDL2SL_AP_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <bgcc.h>

#include "acdcommon.h"
namespace ap {
class ApAgentInfo {
public:
    ApAgentInfo();
    ~ApAgentInfo();

    std::string agentId;
    std::string agentDn;
    std::string agentPwd;
    acd::StatusChangeT statusChangetype;
    bool autoAnswer;
    bool fcSignin;
    std::string skills;
    std::string proxyname;
    std::string proxyname_old;
    int64_t handle;
    int32_t flag;

    bool operator==(const ApAgentInfo& rhs) const;
    bool operator!=(const ApAgentInfo& rhs) const;
    bool operator< (const ApAgentInfo& rhs) const;
    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto);
    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request, int32_t request_len);
    int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

typedef std::vector<ApAgentInfo>  ApAgentInfoListT;
class apapi : public bgcc::Shareable {
public:
    virtual ~apapi() { }

    virtual bool ReLoadConfig(
        const std::map<std::string, std::string>& ctx) = 0;

    virtual bool GetAgents(
        ApAgentInfoListT& agentInfoList,
        const std::map<std::string, std::string>& ctx) = 0;

};

class apapi_ReLoadConfig_args {
public:
    apapi_ReLoadConfig_args();
    virtual ~apapi_ReLoadConfig_args();

    bool operator==(const apapi_ReLoadConfig_args& rhs) const;
    bool operator!=(const apapi_ReLoadConfig_args& rhs) const;
    bool operator< (const apapi_ReLoadConfig_args& rhs) const;
    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request, int32_t request_len);
};

class apapi_GetAgents_args {
public:
    apapi_GetAgents_args();
    virtual ~apapi_GetAgents_args();


    bool operator==(const apapi_GetAgents_args& rhs) const;
    bool operator!=(const apapi_GetAgents_args& rhs) const;
    bool operator< (const apapi_GetAgents_args& rhs) const;
    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request, int32_t request_len);
};

class apapi_ReLoadConfig_pargs {
public:
    virtual ~apapi_ReLoadConfig_pargs();

    int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapi_GetAgents_pargs {
public:
    virtual ~apapi_GetAgents_pargs();


    int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapi_ReLoadConfig_result {
public:
    apapi_ReLoadConfig_result();
    virtual ~apapi_ReLoadConfig_result();

    bool return_value;
    bool operator==(const apapi_ReLoadConfig_result& rhs) const;
    bool operator!=(const apapi_ReLoadConfig_result& rhs) const;
    bool operator< (const apapi_ReLoadConfig_result& rhs) const;
    int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapi_GetAgents_result {
public:
    apapi_GetAgents_result();
    virtual ~apapi_GetAgents_result();

    bool return_value;
    ApAgentInfoListT agentInfoList;

    bool operator==(const apapi_GetAgents_result& rhs) const;
    bool operator!=(const apapi_GetAgents_result& rhs) const;
    bool operator< (const apapi_GetAgents_result& rhs) const;
    int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapi_ReLoadConfig_presult {
public:
    virtual ~apapi_ReLoadConfig_presult();

    bool* return_value;
    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapi_GetAgents_presult {
public:
    virtual ~apapi_GetAgents_presult();

    bool* return_value;
    ApAgentInfoListT* agentInfoList;

    int32_t read(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
};

class apapiProxy : public bgcc::BaseProxy {
public:
    apapiProxy(
        bgcc::ServerInfo serverinfo,
        int32_t nprotocols,
        bgcc::ServiceManager* mgr = NULL,
        int32_t tryCount = 5,
        int32_t tryInterval = 500);

    apapiProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr = NULL,
        int32_t tryCount = 5,
        int32_t tryInterval = 500);

    apapiProxy(
        const std::string& proxy_name,
        int32_t tryCount = 5,
        int32_t tryInterval = 500);

    bool ReLoadConfig(
        bool last = false);

    bool GetAgents(
        ApAgentInfoListT& agentInfoList,
        bool last = false);

private:
    void send_ReLoadConfig(
        int32_t seqid,
        bgcc::SharedPointer<bgcc::IProtocol> proto);

    bool recv_ReLoadConfig(
        bgcc::SharedPointer<bgcc::IProtocol> proto);

    void send_GetAgents(
        int32_t seqid,
        bgcc::SharedPointer<bgcc::IProtocol> proto);

    bool recv_GetAgents(
        ApAgentInfoListT& agentInfoList,
        bgcc::SharedPointer<bgcc::IProtocol> proto);

private:
    std::string _proxy_name;
    bool _use_existing_socket;
};

class apapiProcessor : public bgcc::BaseProcessor {
public:
    apapiProcessor(bgcc::SharedPointer<apapi> intf);

    virtual ~apapiProcessor() { }

    virtual int32_t process(
        char* request,
        int32_t request_len,
        bgcc::SharedPointer<bgcc::IProtocol> proto);

    virtual std::string get_name() const;

protected:
    virtual int32_t do_function__(
        char* request,
        int32_t request_len,
        bgcc::SharedPointer<bgcc::IProtocol> proto,
        const std::string& fname, int32_t seqid);

    bgcc::SharedPointer<apapi> __intf;

private:
    int32_t do_ReLoadConfig(
        char* request,
        int32_t request_len,
        bgcc::SharedPointer<bgcc::IProtocol> proto,
        int32_t seqid);

    int32_t do_GetAgents(
        char* request,
        int32_t request_len,
        bgcc::SharedPointer<bgcc::IProtocol> proto,
        int32_t seqid);

    typedef int32_t (apapiProcessor::* do_function_ptr)(
        char* request,
        int32_t request_len,
        bgcc::SharedPointer<bgcc::IProtocol> proto,
        int32_t seqid);

    std::map<std::string, do_function_ptr> __fun_map;
};
}


#endif
