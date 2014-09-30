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

#ifndef  __IMS_SERVICE_IMPL_H_
#define  __IMS_SERVICE_IMPL_H_

#include "ims.h"

#include <ims_core.h>
#include <list>

namespace ims {

class imsapi_impl_t : public imsapi {
private:
    bool is_inbound(
        const std::string& func,
        const SessionIdT sessionid,
        const std::string& device,
        const std::string& name,
        callid_t& callid,
        std::string& chlid_self,
        std::list<const char*>& otherids
    );

    bool is_state(
        const std::string& func,
        const SessionIdT sessionid,
        const std::string& device,
        const std::string& name,
        const ims_session_operation_t operation,
        callid_t& callid,
        std::string& chlid,
        std::list<const char*>& otherids
    );
    bool is_idle(
        const std::string& func,
        const std::string& device,
        const std::string& name);
    /**
     * @brief create a empty session for ivr outboundCall
     *          for callcloud 3.0
     *
     * @param reqid
     * @param sid
     * @param fsno
     *
     * @return CcResultT
     * @author  dangdawei(dangdawei@baidu.com)
     * @date    2013年09月18日 16时47分12秒
     */
    CcResultT create_ivr_outbound_session(
        ReqIdT reqid,
        SessionIdT& sid,
        uint32_t fsno
    );
public:
    virtual CcResultT Register(
        const ServiceTypeT& type,
        ReqIdT& reqid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT UnRegister(
        ReqIdT reqid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Assign(
        ReqIdT reqid,
        const std::string& devicenumber,
        const DnTypeT& type,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT DeAssign(
        ReqIdT reqid,
        const std::string& devicenumber,
        const DnTypeT& type,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT OutboundCall(
        ReqIdT reqid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& setSrcUri,
        const std::string& setDestUri,
        int32_t timeout,
        const CallModeT& callmode,
        SessionIdT& sessionid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Answer(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Release(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Hold(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Retrieve(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Consult(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& setDestUri,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Reconnect(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Transfer(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Conference(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT SingleStepTransfer(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& dispForCalled,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT SingleStepConference(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& dispForCalled,
        const SsConferenceTypeT& type,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT SwitchListenAndIntrude(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT SetAssociateData(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& key,
        const std::string& val,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT GetAssociateData(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& key,
        std::string& val,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT RouteRequest(
        ReqIdT reqid,
        SessionIdT sessionid,
        const ServiceTypeT& destService,
        int32_t timeout,
        int32_t valid_time,
        const RouteRequestTypeT& reqType,
        const std::string& reqArgs,
        int32_t level,
        const std::string& caller_uri,
        const std::string& callee_uri,
        const std::string& buffer,
        RouteRequestIDT& requestId,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT CancelRouteRequest(
        ReqIdT reqid,
        SessionIdT sessionid,
        RouteRequestIDT requestId,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT RouteRequestRespond(
        ReqIdT reqid,
        SessionIdT sessionid,
        RouteRequestIDT requestId,
        const RouteEventReasonT& result,
        const std::string& targetUri,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT CreateSession(
        ReqIdT reqid,
        const std::string& callsource,
        const std::string& channel_id,
        const std::string& oricalled,
        SessionIdT& sessionid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT TransferAgent(
        ReqIdT reqid,
        SessionIdT sessionid,
        RouteRequestIDT requestId,
        const TransferTypeT& transType,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT Record(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& filename,
        int32_t maxTime,
        const std::string& interruptKeys,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT SendDTMF(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& dtmf,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT DestroySession(
        ReqIdT reqid,
        SessionIdT sessionid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT QuerySession(
        ReqIdT reqid,
        SessionIdT sessionid,
        std::string& originalAni,
        std::string& originalDnis,
        CallIdListT& callidList,
        std::vector<std::string>&   deviceList,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT QueryCall(
        ReqIdT reqid,
        SessionIdT sessionid,
        const CallIdT& callId,
        std::string& deviceAni,
        std::string& deviceDnis,
        std::string& originalAni,
        std::string& originalDnis,
        std::vector<std::string>&   deviceList,
        int32_t& fsid,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT QueryDevice(
        ReqIdT reqid,
        const std::string& device,
        SessionIdT& sessionid,
        CallIdT& callId,
        CallStateT& callstate,
        MediaStateT& mediastate,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT QuerySysInfo(
        ReqIdT reqid,
        SysInfoT& sysinfo,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT ReloadConfig(
        const ConfigTypeT& type,
        const std::map<std::string, std::string>& ctx);

    virtual CcResultT HeartBeat(
        ReqIdT reqid,
        const std::string& info,
        const std::map<std::string, std::string>& ctx);

#define is_empty(func,str,val)\
            if(val.size()==0){\
                WARNING_LOG(func" failed, "str" is empty");\
                return CcResultT::ResInvalidParam;\
            }

#define judge_req(func,reqid) \
            ims_session_manager_t *session_mgr=ims_session_manager_t::instance();\
            if(!session_mgr->rt_query_req(reqid)){\
                WARNING_LOG(func" failed, Invalid ReqID %lu",reqid);\
                return CcResultT::ResInvalidReqId;\
            }

#define judge_agent(func,dn,reqid)\
            if(!session_mgr->rt_query_dn(dn,DnTypeT::AgentDn)){\
                WARNING_LOG(func" failed,  reqid=%lu,invalid agentdn %s",reqid,dn);\
                return CcResultT::ResInvalidDn;\
            }
};
}

#endif  //__IMS_SERVICE_IMPL_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
