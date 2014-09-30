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


#pragma once

#include "acd_ims_callback.h"
#include "thread.h"
#include "ims.h"

using namespace std;

class acd_ims : public Thread {
private:
    bgcc::ServiceManager m_servicemanager;
    uint32_t m_times_max;
    uint32_t m_timespan;
    ims::imsapiProxy m_imsapi_main;
    ims::imsapiProxy m_imsapi_back;
    ims::imsapiProxy* p_m_imsapi_prx;
    ims::ReqIdT m_reqid;

private:
    bool ConnectIMS(bool is_main);
    void DestroyIMS();
protected:
    virtual void Method();
public:
    acd_ims(const char* main_server_ip, uint32_t main_server_port, const char* back_server_ip,
            uint32_t back_server_port, uint32_t ims_proxy_num, uint32_t times_max, uint32_t timespan);
    ~acd_ims();

    bool Register();
    bool UnRegister();
    bool Assign(const string& agentId, const string& agentDn, const ims::DnTypeT& type);
    bool DeAssign(const string& agentId, const string& agentDn, const ims::DnTypeT& type);
    bool OutboundCall(const string& agentId, const string& agentDn, const string& destUri,
                      const string& setSrcUri, const string& setDestUri, int32_t timeout, const ims::CallModeT& callmode,
                      ims::SessionIdT& sessionid);
    bool Answer(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Release(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Hold(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Retrieve(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Consult(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                 const string& destUri, const string& setDestUri);
    bool Reconnect(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Transfer(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool Conference(ims::SessionIdT sessionid, const string& agentId, const string& agentDn);
    bool SingleStepTransfer(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                            const string& destUri, const string& dispForCalled);
    bool SingleStepConference(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                              const string& destUri, const string& dispForCalled, const ims::SsConferenceTypeT& type);
    bool SwitchListenAndIntrude(ims::SessionIdT sessionid, const string& agentId,
                                const string& agentDn);
    bool SetAssociateData(ims::SessionIdT sessionid, const string& agentId, const string& key,
                          const string& val);
    bool GetAssociateData(ims::SessionIdT sessionid, const string& agentId, const string& key,
                          string& val);
    //RouteRequest, CancelRouteRequest
    bool RouteRequestRespond(ims::SessionIdT sessionid, ims::RouteRequestIDT requestId,
                             const ims::RouteEventReasonT& result, const string& targetUri);
    //CreateSession, TransferAgent
    bool Record(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                const string& filename, int32_t maxTime, const string& interruptKeys);
    bool SendDTMF(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                  const string& dtmf);
    //DestroySession, QuerySession, QueryCall, QueryDevice
    bool QuerySysInfo(const string& agentId, ims::SysInfoT& sysinfo);
    //ReloadConfig
    bool HeartBeat(const string& info);
};
