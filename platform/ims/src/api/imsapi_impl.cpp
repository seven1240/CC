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

#include <sstream>
#include "imsapi_impl.h"
#include "ims_core.h"
#include "ims_core_request.h"
#include "ims_conf_loader.h"
#include "ims_core_session_mgr.h"
#include "threadpool.h"
#include "fs_mgr.h"
#include "ims_tool.h"
#include "ims_log.h"

namespace ims {

CcResultT imsapi_impl_t::Register(const ServiceTypeT& type,
                                  ReqIdT& reqid,
                                  const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("Register start. type:%s ", type.get_desc().c_str());

    std::string peerIP, peerPort, peerProxyInfo;
    std::map<std::string, std::string>::const_iterator cit;
    cit = ctx.find("PeerIP");

    if (cit != ctx.end()) {
        peerIP = cit->second;
    }

    cit = ctx.find("PeerPort");

    if (cit != ctx.end()) {
        peerPort = cit->second;
    }

    cit = ctx.find("ProxyName");

    if (cit != ctx.end()) {
        peerProxyInfo = cit->second;
    }

    is_empty("Register", "PeerIP", peerIP);
    is_empty("Register", "ProxyName", peerProxyInfo);
    TRACE_LOG("Peer ip=%s, Peer port=%s", peerIP.c_str(), peerPort.c_str());

    uint32_t naddr = ims_tool_t::inet_pton(peerIP.c_str());

    if (0 == naddr) {
        WARNING_LOG("Register type:%s peerProxyInfo:%s failed, InvalidParam",
                    type.get_desc().c_str(), peerProxyInfo.c_str());
        return CcResultT::ResInvalidParam;
    }

    if (!ims_tool_t::is_accessible_ip(peerIP, type)) {
        WARNING_LOG("Register type:%s peerProxyInfo:%s failed, AccessDenied",
                    type.get_desc().c_str(), peerProxyInfo.c_str());
        return CcResultT::ResAccessDenied;
    }

    uint64_t ireqid;
    ireqid = ims_tool_t::get_reqid(type, naddr, ims_tool_t::str_to_uint32(peerPort.c_str()));

    if (ims_session_manager_t::instance()->rt_add_req(ireqid, peerProxyInfo.c_str())) {
        TRACE_LOG("Register OK, type:%s peerProxyInfo:%s reqid:%ld",
                  type.get_desc().c_str(), peerProxyInfo.c_str(), ireqid);

        reqid = (ReqIdT)ireqid;
        return CcResultT::ResSuccess;
    } else {
        WARNING_LOG("Register failed, type:%s peerProxyInfo:%s failed, add request failed.",
                    type.get_desc().c_str(), peerProxyInfo.c_str());
        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::UnRegister(ReqIdT reqid, const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld] UnRegister start.", reqid);

    judge_req("UnRegister", reqid);

    if (!session_mgr->rt_del_req(reqid)) {
        WARNING_LOG("[%ld] UnRegister failed.", reqid);
        return CcResultT::ResFailed;
    }

    TRACE_LOG("[%ld] UnRegister ok.", reqid);
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Assign(ReqIdT reqid,
                                const std::string& devicenumber,
                                const DnTypeT& type,
                                const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld] Assign, dn:%s, type:%s",
               reqid, devicenumber.c_str(), type.get_desc().c_str());

    is_empty("Assign", "devicenumber", devicenumber);
    judge_req("Assign", reqid);

    std::string assign_num;

    if (type == DnTypeT::IvrANI) {
        assign_num = devicenumber;
    } else {
        assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    }

    if (!session_mgr->rt_add_dn(assign_num.c_str(), type, reqid)) {
        WARNING_LOG("[%ld] Assign failed, dn:%s, type:%s", reqid, assign_num.c_str(),
                    type.get_desc().c_str());
        return CcResultT::ResFailed;
    }

    NOTICE_LOG("[%ld] Assign ok, dn:%s, type:%s", reqid, assign_num.c_str(), type.get_desc().c_str());
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::DeAssign(ReqIdT reqid,
                                  const std::string& devicenumber,
                                  const DnTypeT& type,
                                  const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld] DeAssign, dn:%s, type:%s",
               reqid, devicenumber.c_str(), type.get_desc().c_str());

    is_empty("DeAssign", "devicenumber", devicenumber);
    judge_req("DeAssign", reqid);

    std::string assign_num;

    if (type == DnTypeT::IvrANI) {
        assign_num = devicenumber;
    } else {
        assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    }

    if (!ims_session_manager_t::instance()->rt_del_dn(assign_num.c_str(), type)) {
        WARNING_LOG("[%lu] DeAssign failed, dn:%s, type:%s", reqid, assign_num.c_str(),
                    type.get_desc().c_str());
        return CcResultT::ResFailed;
    }

    NOTICE_LOG("[%ld] DeAssign ok, dn:%s, type:%s", reqid, assign_num.c_str(), type.get_desc().c_str());
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::OutboundCall(ReqIdT reqid,
                                      const std::string& srcUri,
                                      const std::string& destUri,
                                      const std::string& setSrcUri,
                                      const std::string& setDestUri,
                                      int32_t timeout,
                                      const CallModeT& callmode,
                                      SessionIdT& sessionid,
                                      const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld] OutboundCall start. src:%s, dest:%s, setsrc:%s, setdest:%s, timeout:%d, mode:%s, sid=%ld",
               reqid, srcUri.c_str(),
               destUri.c_str(), setSrcUri.c_str(), setDestUri.c_str(),
               timeout, callmode.get_desc().c_str(), sessionid);

    is_empty("OutboundCall", "srcUri", srcUri);
    is_empty("OutboundCall", "destUri", destUri);
    judge_req("OutboundCall", reqid);

    if (timeout < 10) {
        timeout = 10;
    } else if (timeout > 60) {
        timeout = 60;
    }

    std::string caller = ims_tool_t::get_assigned_caller(srcUri, srcUri);
    std::string called = ims_tool_t::get_assigned_called(destUri, srcUri);
    judge_agent("OutboundCall", caller.c_str(), reqid);

    if (caller == called) {
        WARNING_LOG("[%ld] OutboundCall failed, agent==dest(%s,%s)"
                    , reqid, caller.c_str(), called.c_str());
        return CcResultT::ResInvalidParam;
    }

    if (!is_idle("OutboundCall", ims_tool_t::chlname2no(caller), caller)) {
        WARNING_LOG("[%ld] OutboundCall failed, agent %s is busy"
                    , reqid, caller.c_str());
        return CcResultT::ResInvalidState;
    }

    if (!is_idle("OutboundCall", ims_tool_t::chlname2no(called), called)) {
        WARNING_LOG("[%ld] OutboundCall failed, agent %s is busy"
                    , reqid, called.c_str());
        return CcResultT::ResInvalidState;
    }

    uint32_t fsno = (~0);

    // ivr makecall
    if (session_mgr->is_IVRoutbound_session(sessionid)) {
        TRACE_LOG("[%ld]OutboundCall4IVR start. sessionid:%ld", reqid, sessionid);
        ims_route_info_t info;

        if (!session_mgr->rt_query_session_route(sessionid, info)) {
            WARNING_LOG("[%ld]OutboundCall4IVR failed(sid=%ld), sessiond not exist",
                        reqid, sessionid);
            return CcResultT::ResInvalidParam;
        }

        if (0 == info.targetUri.size()) {
            WARNING_LOG("[%ld]OutboundCall4IVR failed(sid=%ld), targetUri is null",
                        reqid, sessionid);
            return CcResultT::ResInvalidState;
        }

        // if route request success, ivr should makecall within $validtime second
        if (ims_tool_t::get_timestamp_s() - info.timestamp / 1000000 > info.validtime) {
            WARNING_LOG("[%ld]OutboundCall4IVR failed(sid=%ld), ivr should makecall \
						within $validtime seconds after routerequest.", reqid, sessionid);
            return CcResultT::ResInvalidState;
        }

        fsno = ims_tool_t::get_fsno(sessionid);
    }
    // acd makecall, ivr is not allowed to make normal call
    else if ((reqid >> 56) == ServiceTypeT::ServiceACD) {
        sessionid = 0;

        if (fs_mgr_t::instance()->decision_fs(fsno) != IMS_SUCCESS) {
            WARNING_LOG("[%ld] OutboundCall failed, decision_fs error.", reqid);
            return CcResultT::ResNoEnoughResource;
        }

        session_thread_ptr thrd = session_thrd_mgr::instance()->get_prefer_thread();

        if (!thrd.is_valid()) {
            WARNING_LOG("[%ld] OutboundCall failed, get_prefer_thread error.", reqid);
            return CcResultT::ResFailed;
        }

        if (!session_mgr->create_session(fsno,
                                         reqid,
                                         SCRT_OUTBOUND_NORMAL,
                                         thrd,
                                         ims_tool_t::chlname2no(caller).c_str(),
                                         ims_tool_t::chlname2no(called).c_str(),
                                         sessionid)) {
            WARNING_LOG("[%ld] OutboundCall failed, create_session error.", reqid);
            return CcResultT::ResFailed;
        }
    } else {
        WARNING_LOG("[%ld] OutboundCall failed, invalid param.", reqid);
        return CcResultT::ResInvalidParam;
    }

    session_mgr->update_session_operation(sessionid, SOPR_MAKECALL, caller.c_str());

    fs_tool_t opr(fsno);

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] OutboundCall failed, fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    if (opr.opr().originate(caller.c_str(), called.c_str(), setSrcUri.c_str(),
                            setDestUri.c_str(), sessionid, timeout) != IMS_SUCCESS) {
        WARNING_LOG("[%ld] OutboundCall failed, originate error.", reqid);

        // add when callcloud 3.0 for ivr outboundcall
        if (session_mgr->is_IVRoutbound_session(sessionid)) {
            ims_tool_t::push_cancel_route_event(sessionid);
        }

        session_mgr->remove_session(sessionid);
        return CcResultT::ResFailed;
    }

    NOTICE_LOG("[%ld] OutboundCall OK. src:%s, dest:%s, setsrc:%s, setdest:%s, timeout:%d,mode:%s, sessionid:%ld",
               reqid, srcUri.c_str(), destUri.c_str(), setSrcUri.c_str(), setDestUri.c_str(), timeout,
               callmode.get_desc().c_str(), sessionid);
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Answer(ReqIdT reqid,
                                SessionIdT sessionid,
                                const std::string& devicenumber,
                                const std::map<std::string, std::string>& ctx) {
    //IVR answer
    TRACE_LOG("[%ld][%ld] Answer dn:%s", reqid, sessionid, devicenumber.c_str());
    is_empty("Answer", "devicenumber", devicenumber);
    judge_req("Answer", reqid);

    std::string called = ims_tool_t::get_assigned_called(devicenumber, devicenumber);
    char channelid[LEN_64 + 1] = {0};

    if (!session_mgr->locate_channel(sessionid, called.c_str(), channelid, LEN_64)) {
        TRACE_LOG("[%ld][%ld] Answer failed, cannot locate channel by devicenumber. ", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    uint32_t fsno = ims_tool_t::get_fsno(sessionid);
    fs_tool_t opr(fsno);

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] Answer fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    if (opr.opr().answer(channelid) != IMS_SUCCESS) {
        WARNING_LOG("[%ld][%ld] Answer error.", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Release(ReqIdT reqid,
                                 SessionIdT sessionid,
                                 const std::string& devicenumber,
                                 const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Release dn:%s", reqid, sessionid, devicenumber.c_str());

    is_empty("Release", "devicenumber", devicenumber);
    judge_req("Release", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Release", assign_num.c_str(), reqid);

    char channelid[LEN_64 + 1] = {0};

    if (!session_mgr->locate_channel(sessionid, assign_num.c_str(), channelid, LEN_64)) {
        TRACE_LOG("[%ld][%ld] Release failed, cannot locate channel by dn. ", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] Release fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    if (opr.opr().hangup(channelid) != IMS_SUCCESS) {
        WARNING_LOG("[%ld][%ld] Release hangup error.", reqid, sessionid);
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Hold(ReqIdT reqid,
                              SessionIdT sessionid,
                              const std::string& devicenumber,
                              const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Hold agent dn:%s", reqid, sessionid, devicenumber.c_str());

    is_empty("Hold", "devicenumber", devicenumber);
    judge_req("Hold", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Hold", assign_num.c_str(), reqid);

    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (!is_state("hold",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_MAKECALL, callid, chlid, otherids)
            && !is_inbound("hold", sessionid, ims_tool_t::chlname2no(assign_num), assign_num, callid, chlid,
                           otherids)) {

        return CcResultT::ResInvalidState;
    }

    if (session_mgr->is_internal_call(sessionid, callid)) {
        WARNING_LOG("[%ld][%ld] Hold failed, internal call", reqid, sessionid);
        return CcResultT::ResInvalidState;
    }

    session_mgr->update_session_operation(sessionid, SOPR_HOLD, assign_num.c_str());

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        session_mgr->update_session_operation(sessionid, SOPR_MAKECALL, assign_num.c_str());
        WARNING_LOG("[%ld][%ld] Hold fetch_opr error.", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    return
        (opr.opr().unbridge(chlid.c_str()) == IMS_SUCCESS
         && opr.opr().play(otherids.front(), DEFAULT_HOLDON_MUSIC) == IMS_SUCCESS
        ) ? CcResultT::ResSuccess : CcResultT::ResFailed;
}

CcResultT imsapi_impl_t::Retrieve(ReqIdT reqid,
                                  SessionIdT sessionid,
                                  const std::string& devicenumber,
                                  const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Retrieve agent dn:%s", reqid, sessionid, devicenumber.c_str());

    judge_req("Retrieve", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Retrieve", assign_num.c_str(), reqid);

    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (!is_state("retrieve",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_HOLD, callid, chlid, otherids)) {

        return CcResultT::ResInvalidState;
    }

    session_mgr->update_session_operation(sessionid, SOPR_RETRIEVE);

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] Retrieve fetch_opr error.", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    return
        (opr.opr().stop_media(otherids.front()) == IMS_SUCCESS
         && opr.opr().uuid_bridge(chlid.c_str(), otherids.front()) == IMS_SUCCESS
        ) ? CcResultT::ResSuccess : CcResultT::ResFailed;

}/*}}}*/

CcResultT imsapi_impl_t::Consult(ReqIdT reqid,
                                 SessionIdT sessionid,
                                 const std::string& devicenumber,
                                 const std::string& destUri,
                                 const std::string& setDestUri,
                                 const std::map<std::string, std::string>& ctx) {
    /*{{{*/
    NOTICE_LOG("[%ld][%ld] Consult agentdn:%s,destno:%s,setDestUri:%s",
               reqid, sessionid, devicenumber.c_str(), destUri.c_str(), setDestUri.c_str());

    is_empty("Consult", "devicenumber", devicenumber);
    is_empty("Consult", "destUri", destUri);
    judge_req("Consult", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    std::string assign_dest_num = ims_tool_t::get_assigned_called(destUri, devicenumber);
    judge_agent("Consult", assign_num.c_str(), reqid);

    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (assign_num == assign_dest_num) {
        WARNING_LOG("[%ld] Consult return failed, agent==dest(%s,%s)"
                    , reqid, assign_num.c_str(), assign_dest_num.c_str());
        return CcResultT::ResInvalidParam;
    }

    if (!is_state("consult",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_MAKECALL, callid, chlid, otherids)
            && !is_inbound("consult", sessionid, ims_tool_t::chlname2no(assign_num), assign_num, callid, chlid,
                           otherids)) {
        return CcResultT::ResInvalidState;
    }

    if (session_mgr->is_internal_call(sessionid, callid)) {
        WARNING_LOG("[%ld][%ld] Consult failed, internal call", reqid, sessionid);
        return CcResultT::ResInvalidState;
    }

    if (!is_idle("consult", ims_tool_t::chlname2no(assign_dest_num), assign_dest_num)) {
        WARNING_LOG("[%ld] Consult failed, agent %s is busy"
                    , reqid, assign_dest_num.c_str());
        return CcResultT::ResInvalidState;
    }

    session_mgr->update_session_operation(sessionid, SOPR_CONSULT, assign_num.c_str());

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] Consult fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    std::list<const char*>::iterator chit = otherids.begin();

    for (; chit != otherids.end(); ++chit) {
        if (opr.opr().unbridge(*chit) != IMS_SUCCESS) {
            WARNING_LOG("[%ld][%ld] Consult unbridge error. [%s]", reqid, sessionid, *chit);
            session_mgr->update_session_operation(sessionid, SOPR_MAKECALL, assign_num.c_str());
            return CcResultT::ResFailed;
        }

        if (opr.opr().play(*chit, DEFAULT_HOLDON_MUSIC) != IMS_SUCCESS) {
            WARNING_LOG("[%ld][%ld] Consult play hold music error.", reqid, sessionid);
        } else {
            TRACE_LOG("[%ld][%ld] Consult playing default hold music on chl[%s].", reqid, sessionid, *chit);
        }
    }

    if (opr.opr().bridge(chlid.c_str(), setDestUri.c_str(), assign_dest_num.c_str()) != IMS_SUCCESS) {
        WARNING_LOG("[%ld][%ld] Consult invoke fs brideg failed.", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Reconnect(ReqIdT reqid,
                                   SessionIdT sessionid,
                                   const std::string& devicenumber,
                                   const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Reconnect agent dn:%s", reqid, sessionid, devicenumber.c_str());

    is_empty("Reconnect", "devicenumber", devicenumber);
    judge_req("Reconnect", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Reconnect", assign_num.c_str(), reqid);

    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (!is_state("reconnect",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_CONSULT, callid, chlid, otherids)) {
        return CcResultT::ResInvalidState;
    }

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld] Reconnect fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    session_mgr->update_session_operation(sessionid, SOPR_RECONNECT);

    std::list<const char*>::iterator chit = otherids.begin();

    for (; chit != otherids.end(); ++chit) {
        if (opr.opr().unbridge(chlid.c_str()) != IMS_SUCCESS
                || opr.opr().hangup(*chit) != IMS_SUCCESS) {
            WARNING_LOG("[%ld][%ld] Reconnect unbridge error. [%s]", reqid, sessionid, *chit);
        }

        break;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Transfer(ReqIdT reqid,
                                  SessionIdT sessionid,
                                  const std::string& devicenumber,
                                  const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Transfer agent dn:%s", reqid, sessionid, devicenumber.c_str());

    is_empty("Transfer", "devicenumber", devicenumber);
    judge_req("Transfer", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Transfer", assign_num.c_str(), reqid);


    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (!is_state("transfer",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_CONSULT, callid, chlid, otherids)) {
        return CcResultT::ResInvalidState;
    }

    session_mgr->update_session_operation(sessionid, SOPR_TRANSFER);

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld]Transfer fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    if (opr.opr().unbridge(chlid.c_str()) != IMS_SUCCESS) {
        WARNING_LOG("[%ld][%ld] Transfer unbridge error. [%s]", reqid, sessionid, chlid.c_str());
    }

    if (opr.opr().hangup(chlid.c_str()) != IMS_SUCCESS) {
        WARNING_LOG("[%ld][%ld] Transfer hangup error. [%s]", reqid, sessionid, chlid.c_str());
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::Conference(ReqIdT reqid,
                                    SessionIdT sessionid,
                                    const std::string& devicenumber,
                                    const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] Conference agent dn:%s", reqid, sessionid, devicenumber.c_str());

    is_empty("Conference", "devicenumber", devicenumber);
    judge_req("Conference", reqid);
    std::string assign_num = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Conference", assign_num.c_str(), reqid);

    std::string chlid;
    callid_t callid = 0;
    std::list<const char*> otherids;

    if (!is_state("conference",
                  sessionid, ims_tool_t::chlname2no(assign_num), assign_num, SOPR_CONSULT, callid, chlid, otherids)) {
        return CcResultT::ResInvalidState;
    }

    std::list<const char*> chls_held;
    callid_t callid_held;

    if (!session_mgr->locate_othercall(sessionid, callid, callid_held)
            || !session_mgr->get_channelsbycall(sessionid, callid_held, chls_held)
            || chls_held.size() < 1) {

        TRACE_LOG("[%ld][%ld] Conference failed, cannot locate held channels by call(%lu) "
                  , reqid, sessionid, callid_held);
        return CcResultT::ResFailed;
    }

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("[%ld][%ld]Conference fetch_opr error.", reqid, sessionid);
        return CcResultT::ResNoEnoughResource;
    }

    session_mgr->update_session_operation(sessionid, SOPR_CONFERENCE);

    session_mgr->remove_channelfromcall(sessionid, callid_held, chls_held.front());
    session_mgr->update_channel_call(chls_held.front(), callid);

    std::string conf_name = ims_tool_t::generate_uuid();
    //session_mgr->add_rundata(sessionid,"conf_name",conf_name.c_str());

    opr.opr().unbridge(chlid.c_str());
    opr.opr().stop_media(chls_held.front());
    ims_tool_t::safe_sleepms(50);
    opr.opr().conference(chlid.c_str(), conf_name.c_str());
    ims_tool_t::safe_sleepms(50);
    opr.opr().conference(otherids.front(), conf_name.c_str());
    ims_tool_t::safe_sleepms(50);
    opr.opr().conference(chls_held.front(), conf_name.c_str());

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::SingleStepTransfer(ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& dispForCalled,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] SingleStepTransfer agent dn:%s,destdn:%s,disp:%s",
               reqid, sessionid, devicenumber.c_str(), destUri.c_str(), dispForCalled.c_str());

    is_empty("SingleStepTransfer", "devicenumber", devicenumber);
    judge_req("SingleStepTransfer", reqid);
    std::string chlid;
    callid_t callid;
    std::string name = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    std::string dest_channel = ims_tool_t::get_assigned_called(destUri, devicenumber);

    if (name == dest_channel) {
        WARNING_LOG("[%ld] SingleStepTransfer return failed, agent==dest(%s,%s)"
                    , reqid, name.c_str(), dest_channel.c_str());
        return CcResultT::ResInvalidParam;
    }

    std::list<const char*> otherids;
    judge_agent("SingleStepTransfer", name.c_str(), reqid);

    if (!is_state("singlesteptransfer",
                  sessionid, ims_tool_t::chlname2no(name), name, SOPR_MAKECALL, callid, chlid, otherids)
            && !is_inbound("singlesteptransfer", sessionid, ims_tool_t::chlname2no(name), name, callid, chlid,
                           otherids)) {
        return CcResultT::ResInvalidState;
    }

    if (session_mgr->is_internal_call(sessionid, callid)) {
        WARNING_LOG("singlesteptransfer(sid=%lu,reqid=%lu,dn=%s,dest=%s)failed internal call",
                    sessionid, reqid, devicenumber.c_str(), destUri.c_str());
        return CcResultT::ResInvalidState;
    }

    if (!is_idle("singlesteptransfer", ims_tool_t::chlname2no(dest_channel), dest_channel)) {
        WARNING_LOG("[%ld] singlesteptransfer failed, agent %s is busy"
                    , reqid, dest_channel.c_str());
        return CcResultT::ResInvalidState;
    }

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("singlesteptransfer(sid=%ld,reqid=%ld)failed fetch_opr error."
                    , sessionid, reqid);
        return CcResultT::ResNoEnoughResource;
    }

    session_mgr->update_session_operation(sessionid, SOPR_SINGLESTEPTRANSFER, name.c_str());

    opr.opr().unbridge(chlid.c_str());
    opr.opr().hangup(chlid.c_str());
    opr.opr().bridge(otherids.front(), dispForCalled.c_str(), dest_channel.c_str());

    return CcResultT::ResSuccess;
}


CcResultT imsapi_impl_t::SingleStepConference(ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::string& destUri,
        const std::string& dispForCalled,
        const SsConferenceTypeT& type,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] SingleStepConference agent dn:%s,destdn:%s,mode:%s",
               reqid, sessionid, devicenumber.c_str(), destUri.c_str(), type.get_desc().c_str());

    is_empty("SingleStepConference", "devicenumber", devicenumber);
    is_empty("SingleStepConference", "destUri", destUri);
    judge_req("SingleStepConference", reqid);
    std::string chlid;
    callid_t callid;
    std::string name = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    std::string dest_channel = ims_tool_t::get_assigned_called(destUri, devicenumber);

    if (name == dest_channel) {
        WARNING_LOG("[%ld] SingleStepConference return failed, agent==dest(%s,%s)"
                    , reqid, name.c_str(), dest_channel.c_str());
        return CcResultT::ResInvalidParam;
    }

    std::list<const char*> otherids;
    judge_agent("SingleStepConference", name.c_str(), reqid);

    if (!is_state("singlestepconference",
                  sessionid, destUri, dest_channel, SOPR_MAKECALL, callid, chlid, otherids)
            && !is_inbound("singlestepconference", sessionid, destUri, dest_channel, callid, chlid, otherids)) {

        return CcResultT::ResInvalidState;
    }

    if (session_mgr->is_internal_call(sessionid, callid)) {
        WARNING_LOG("singlestepconference(sid=%lu,reqid=%lu,dn=%s,dest=%s)failed internal call",
                    sessionid, reqid, devicenumber.c_str(), destUri.c_str());

        return CcResultT::ResInvalidState;
    }

    if (!is_idle("singlestepconference", ims_tool_t::chlname2no(name), name)) {
        WARNING_LOG("[%ld] singlestepconference return failed, agent %s is busy"
                    , reqid, dest_channel.c_str());

        return CcResultT::ResInvalidState;
    }

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("singlestepconference(sid=%ld,reqid=%ld)failed fetch_opr error."
                    , sessionid, reqid);
        return CcResultT::ResNoEnoughResource;
    }

    fs_opr_t::CONF_MODE conf_mod = fs_opr_t::CONF_INSERT;
    session_mgr->update_session_operation(sessionid, SOPR_INSERT, name.c_str());

    if (type == ims::SsConferenceTypeT::Monitor) {
        conf_mod = fs_opr_t::CONF_LISTEN;
        session_mgr->update_session_operation(sessionid, SOPR_LISTEN, name.c_str());
    }

    std::string conf_name = ims_tool_t::generate_uuid();

    if (!session_mgr->add_rundata(sessionid, "conf_name", conf_name.c_str())) {
        WARNING_LOG("singlestepconference(sid=%lu,reqid=%lu,dn=%s,dest=%s)fail add_runndata(%s))"
                    , sessionid, reqid, devicenumber.c_str(), destUri.c_str(), conf_name.c_str());
        return CcResultT::ResFailed;
    }

    if (opr.opr().join_conference(conf_name.c_str(), dispForCalled.c_str(),
                                  name.c_str(), conf_mod, sessionid) != IMS_SUCCESS) {
        WARNING_LOG("singlestepconference(sid=%lu,reqid=%lu,dn=%s,dest=%s)fail join conference(%s))"
                    , sessionid, reqid, devicenumber.c_str(), destUri.c_str(), conf_name.c_str());
        session_mgr->update_session_operation(sessionid, SOPR_MAKECALL, dest_channel.c_str());
        return CcResultT::ResNoEnoughResource;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::SwitchListenAndIntrude(ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& devicenumber,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] SwitchListenAndIntrude agent dn:%s",
               reqid, sessionid, devicenumber.c_str());

    judge_req("SwitchListenAndIntrude", reqid);
    std::string chlid;
    callid_t callid;
    std::string name = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    std::list<const char*> otherids;
    judge_agent("SwitchListenAndIntrude", name.c_str(), reqid);

    char conf_name[LEN_64 + 1] = {0};
    char conf_memid[LEN_64 + 1] = {0};

    fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

    if (!opr.valid()) {
        WARNING_LOG("switchlistentointrude(sid=%ld,reqid=%ld)failed fetch_opr error."
                    , sessionid, reqid);
        return CcResultT::ResNoEnoughResource;
    }

    if (is_state("switchlistentointrude",
                 sessionid, devicenumber, name, SOPR_LISTEN, callid, chlid, otherids)) {
        //change to insert

        if (!session_mgr->get_rundata(sessionid, "conf_name", conf_name, LEN_64)
                || !session_mgr->get_rundata(sessionid, chlid.c_str(), conf_memid, LEN_64)) {
            WARNING_LOG("switchlistentointrude(sid=%ld,reqid=%ld)failed get rundata"
                        , sessionid, reqid);
            return CcResultT::ResFailed;
        }

        if (opr.opr().conference_unmute(conf_name, conf_memid) != IMS_SUCCESS) {
            return CcResultT::ResFailed;
        }
    } else if (is_state("switchlistentointrude",
                        sessionid, devicenumber, name, SOPR_INSERT, callid, chlid, otherids)) {
        //change to listen

        if (!session_mgr->get_rundata(sessionid, "conf_name", conf_name, LEN_64)
                || !session_mgr->get_rundata(sessionid, chlid.c_str(), conf_memid, LEN_64)) {
            WARNING_LOG("switchlistentointrude(sid=%ld,reqid=%ld)failed get rundata"
                        , sessionid, reqid);
            return CcResultT::ResFailed;
        }

        if (opr.opr().conference_mute(conf_name, conf_memid) != IMS_SUCCESS) {
            return CcResultT::ResFailed;
        }
    } else {
        return CcResultT::ResInvalidState;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::SetAssociateData(ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& key,
        const std::string& val,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("SetAssociateData reqid=%lu,sid=%lu,key=%s,val=%s",
               reqid, sessionid, key.c_str(), val.c_str());
    judge_req("SetAssociateData", reqid);

    if (session_mgr->save_session_data(sessionid, key.c_str(), val.c_str())) {
        return CcResultT::ResSuccess;
    } else {
        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::GetAssociateData(ReqIdT reqid,
        SessionIdT sessionid,
        const std::string& key,
        std::string& val,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("GetAssociateData reqid=%lu,sid=%lu,key=%s",
               reqid, sessionid, key.c_str());
    judge_req("GetAssociateData", reqid);

    char tmp[LEN_256 + 1] = {0};

    if (session_mgr->get_session_data(sessionid, key.c_str(), tmp, LEN_256)) {
        val = tmp;
        return CcResultT::ResSuccess;
    } else {
        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::RouteRequest(ReqIdT reqid,
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
                                      const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("RouteRequest start.  reqid=%ld,sid=%ld,destService=%s,timeout=%d,"
               "valid_time=%d,reqtype=%s,reqargs=%s,level=%d,caller=%s,callee=%s,buffer=%s",
               reqid, sessionid, destService.get_desc().c_str(), timeout, valid_time,
               reqType.get_desc().c_str(), reqArgs.c_str(), level,
               caller_uri.c_str(), callee_uri.c_str(), buffer.c_str());

    judge_req("RouteRequest", reqid);

    if (timeout < 0 || valid_time < 0) {
        WARNING_LOG("RouteRequest failed(sid=%ld timeout and valid_time < 0)", sessionid);
        return CcResultT::ResInvalidParam;
    }

    if (!session_mgr->is_valid_request(sessionid)) {
        WARNING_LOG("RouteRequest failed(sid=%ld already has a route request, waiting for reponse)"
                    , sessionid);
        return CcResultT::ResRouteRequestRepeated;
    }

    ReqIdT reqid_dest = 0;

    if (!session_mgr->rt_query_register_service(destService, reqid_dest)) {
        WARNING_LOG("RouteRequest failed(sid=%ld,destservice=%s no dest service)"
                    , sessionid, destService.get_desc().c_str());
        return CcResultT::ResInvalidParam;
    }

    //找到callid
    std::list<callid_t> calls;

    if (session_mgr->is_IVRinbound_session(sessionid)) {
        ims_session_operation_t operation = SOPR_UNKNOWN;

        if (!session_mgr->get_session_operation(sessionid, operation)
                || (SOPR_IVRTRANSFER != operation)) {
            WARNING_LOG("RouteRequest failed(sid=%ld session operation type error.)", sessionid);
            return CcResultT::ResInvalidParam;
        }

        std::list<const char*> chls;

        if (!session_mgr->get_channelsbysession(sessionid, chls) || chls.size() == 0) {
            WARNING_LOG("RouteRequest failed(sid=%ld not contain channels)", sessionid);
            return CcResultT::ResInvalidParam;
        }

        if (!session_mgr->locate_call(sessionid, calls) || calls.size() == 0) {
            WARNING_LOG("RouteRequest failed(sid=%ld) locate call by session error.", sessionid);
            return CcResultT::ResFailed;
        }
    } else if (session_mgr->is_IVRoutbound_session(sessionid)) {
        ims_session_operation_t operation = SOPR_UNKNOWN;

        if (!session_mgr->get_session_operation(sessionid, operation)
                || (SOPR_MAKECALL != operation)) {
            WARNING_LOG("RouteRequest failed(sid=%ld session operation type error.)", sessionid);
            return CcResultT::ResInvalidParam;
        }

        // avoid ivr recall RouteRequest after agent ring
        std::list<const char*> chls;

        if (!session_mgr->get_channelsbysession(sessionid, chls) || chls.size() != 0) {
            WARNING_LOG("RouteRequest failed(sid=%ld session should be empty now.)", sessionid);
            return CcResultT::ResInvalidState;
        }
    } else {
        WARNING_LOG("RouteRequest failed(sid=%ld create reason error)", sessionid);
        return CcResultT::ResInvalidParam;
    }

    requestId = ims_tool_t::get_requestid(sessionid, reqType);

    ims_route_info_t info;
    info.timestamp   = ims_tool_t::get_timestamp_ms();
    info.reqid       = reqid;
    info.dest_reqid  = reqid_dest;
    info.sessionid   = sessionid;
    info.requestId   = requestId;
    info.callid      = calls.size() > 0 ? ims_tool_t::num2str(calls.front()) : "";
    info.destService = destService;
    info.requestType = reqType;
    info.requestArgs = reqArgs;
    info.level       = level;
    info.callerDn    = caller_uri;
    info.calleeDn    = callee_uri;
    info.validtime   = valid_time;
    info.timeout     = timeout;
    info.buffer      = buffer;
    //组织request事件，e籺Id = tmstamp << 16 | sessionid_random;笸扑偷讲檎业降膔equest
    RouteEventT ims_event;
    ims_tool_t::prepare_route_event(ims_event, sessionid, info);
    ims_event.eventType = RouteEventTypeT::RT_RouteRequest;
    ims_event.reason = RouteEventReasonT::RouteReasonSuccess;

    if (!session_mgr->rt_add_imsevent_route(reqid_dest, ims_event)) {
        WARNING_LOG("RouteRequest failed(sid=%ld,requestId=%ld,add ims route event error, ommiting)",
                    sessionid, requestId);
        return CcResultT::ResFailed;
    }

    if (!session_mgr->rt_add_route(requestId, info)) {
        WARNING_LOG("RouteRequest failed(sid=%ld,requestId=%ld,add route_info error)",
                    sessionid, requestId);
        return CcResultT::ResFailed;
    }

    NOTICE_LOG("RouteRequest OK.  reqid=%ld,sid=%ld,destService=%s,timeout=%d,"
               "valid_time=%d,reqtype=%s,reqargs=%s,level=%d,caller=%s,callee=%s,buffer=%s",
               reqid, sessionid, destService.get_desc().c_str(), timeout, valid_time,
               reqType.get_desc().c_str(), reqArgs.c_str(), level,
               caller_uri.c_str(), callee_uri.c_str(), buffer.c_str());
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::CancelRouteRequest(ims::ReqIdT reqid,
        SessionIdT sessionid,
        RouteRequestIDT requestId,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("CancelRouteRequest start. reqid=%ld,sid=%ld,requestId=%ld", reqid, sessionid,
               requestId);
    judge_req("CancelRouteRequest", reqid);
    ims_route_info_t info;

    if (!session_mgr->rt_query_route(requestId, info)) {
        WARNING_LOG("CancelRouteRequest failed(sid=%ld,requestId=%ld,requestId not exist)",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    if (sessionid != info.sessionid) {
        WARNING_LOG("CancelRouteRequest failed(sid=%ld,requestId=%ld),sessionid!=info.sessionid.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    RouteEventT ims_event;
    ims_tool_t::prepare_route_event(ims_event, sessionid, info);
    ims_event.eventType = RouteEventTypeT::RT_RouteRequestCancel;
    ims_event.reason = RouteEventReasonT::RouteReasonIVRCancel;

    if (session_mgr->rt_add_imsevent_route(info.dest_reqid , ims_event)) {
        session_mgr->rt_del_route(requestId);

        // add when callcloud 3.0 ivr outboundcall
        if (session_mgr->is_IVRoutbound_session(sessionid)) {
            session_mgr->remove_session(sessionid);
        }

        NOTICE_LOG("CancelRouteRequest OK. reqid=%ld,sid=%ld,requestId=%ld", reqid, sessionid, requestId);
        return CcResultT::ResSuccess;
    } else {
        WARNING_LOG("CancelRouteRequest failed(routeid=%ld,add route error)", requestId);
        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::RouteRequestRespond(ReqIdT reqid,
        SessionIdT sessionid,
        RouteRequestIDT requestId,
        const RouteEventReasonT& result,
        const std::string& targetUri,
        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("RouteRequestRespond start, reqid=%ld,sid=%ld,requestId=%ld,result=%s,target=%s",
               reqid, sessionid, requestId, result.get_desc().c_str(), targetUri.c_str());
    judge_req("RouteRequestRespond", reqid);

    ims_route_info_t info;

    if (!session_mgr->rt_query_route(requestId, info)) {
        WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld,requestId not exist)",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    if (sessionid != info.sessionid) {
        WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld),sessionid!=info.sessionid.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    if (info.targetUri.size() != 0) {
        WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld),repeat response.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    RouteEventT ims_event;
    ims_tool_t::prepare_route_event(ims_event, sessionid, info);
    ims_event.reason = result;
    ims_event.eventType = ims::RouteEventTypeT::RT_RouteRespond;
    ims_event.targetDevice = targetUri;

    /*        //先删除记录再推送事件，因为事件推送是不可逆的。
            //但是这样更容易因为线程之间的竞争导致不一致的结果。
            if(result != RouteEventReasonT::RouteReasonSuccess){
                if(!session_mgr->rt_del_route(requestId)){
                    WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld) del route error.",
                        sessionid,requestId);
                    return CcResultT::ResFailed;
                }
            }
            else {
                ims_event.eventType=ims::RouteEventTypeT::RT_RouteRespond;
                ims_event.targetDevice=targetUri;
            }

            if(!session_mgr->rt_add_imsevent_route(info.reqid, ims_event)){
                WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld) add event error.",
                        sessionid,requestId);
                session_mgr->rt_add_route(requestId, info);//如果没add成功，怎么办？
                return CcResultT::ResFailed;
            }
    */

    if (result == RouteEventReasonT::RouteReasonSuccess) {
        std::string assign_num = ims_tool_t::get_assigned_caller(targetUri, targetUri);
        judge_agent("RouteRequestRespond", assign_num.c_str(), reqid);
    }

    //先推事件
    if (!session_mgr->rt_add_imsevent_route(info.reqid, ims_event)) {
        WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld) add event error.",
                    sessionid, requestId);
        return CcResultT::ResFailed;
    }

    if (result == RouteEventReasonT::RouteReasonSuccess) {
        is_empty("RouteRequestRespond", "targetUri", targetUri);
        info.targetUri = targetUri;

        //把targetUri放到route_info中去
        if (!session_mgr->rt_update_route(requestId, info)) {
            WARNING_LOG("RouteRequestRespond failed, update route error.");
            return CcResultT::ResFailed;
        }
    } else {
        if (!session_mgr->rt_del_route(requestId)) {
            WARNING_LOG("RouteRequestRespond failed(sid=%ld,requestId=%ld) del route error.",
                        sessionid, requestId);
            return CcResultT::ResFailed;
        }

        // add when callcloud 3.0 ivr outboundcall
        if (session_mgr->is_IVRoutbound_session(sessionid)) {
            session_mgr->remove_session(sessionid);
        }
    }

    NOTICE_LOG("RouteRequestRespond OK. reqid=%ld,sid=%ld,requestId=%ld,result=%s,target=%s",
               reqid, sessionid, requestId, result.get_desc().c_str(), targetUri.c_str());
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::CreateSession(ReqIdT reqid,
                                       const std::string& callsource,
                                       const std::string& channel_id,
                                       const std::string& oricalled,
                                       SessionIdT& sid,
                                       const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld] CreateSession start. callsource:%s, channel_id:%s, oricalled=%s",
               reqid, callsource.c_str(), channel_id.c_str(), oricalled.c_str());

    judge_req("CreateSession", reqid);
    is_empty("CreateSession", "callsource", callsource);

    ReqIdT reqid_dest = 0;

    if (!session_mgr->rt_query_register_service(ServiceTypeT::ServiceACD, reqid_dest)) {
        WARNING_LOG("[%lu]CreateSession failed, no master acd connected.", reqid);
        return CcResultT::ResNoAgentAssigned;
    }

    TRACE_LOG("callsource = %s", callsource.c_str());
    uint32_t naddr = ims_tool_t::inet_pton(callsource.c_str());

    if (0 == naddr) {
        WARNING_LOG("[%ld]CreateSession failed, InvalidParam callsource.", reqid);
        return CcResultT::ResInvalidParam;
    }

    uint32_t fs_no = 0;

    if (IMS_SUCCESS != fs_mgr_t::instance()->fetch_fs_no(naddr, fs_no)) {
        WARNING_LOG("[%ld]CreateSession failed, callsource is not connected to ims.", reqid);
        return CcResultT::ResCallSourceNotFound;
    }

    if (SPECIAL_CHANNELID == channel_id) {
        return create_ivr_outbound_session(reqid, sid, fs_no);
    }

    is_empty("CreateSession", "channel_id", channel_id);
    is_empty("CreateSession", "oricalled", oricalled);

    //取得fs_opr，用来检查uuid_exists
    fs_tool_t opr(fs_no);

    if (!opr.valid()) {
        WARNING_LOG("[%ld]CreateSession failed, fetch opr error.", reqid);
        return CcResultT::ResFailed;
    }

    if (IMS_SUCCESS != opr.opr().uuid_exists(channel_id.c_str())) {
        WARNING_LOG("[%ld]CreateSession failed(uuid=%s), uuid doesn't exist.", reqid, channel_id.c_str());
        return CcResultT::ResInvalidParam;
    }

    if (session_mgr->locate_session(channel_id.c_str(), sid)) {
        WARNING_LOG("[%ld]CreateSession failed(uuid=%s), channel id already exist.", reqid,
                    channel_id.c_str());
        return CcResultT::ResInvalidParam;
    }

    //get channel name from channel id
    char szcmd[LEN_128 + 1] = {0};
    snprintf(szcmd, LEN_128, "uuid:%s ${channel-name}", channel_id.c_str());
    char chlname[LEN_256 + 1] = {0};

    if (IMS_SUCCESS != opr.opr().eval(szcmd, chlname, LEN_256)) {
        WARNING_LOG("[%ld]CreateSession failed(uuid=%s),get channel name error", reqid, channel_id.c_str());
        return CcResultT::ResFailed;
    }

    TRACE_LOG("channel name get by uuid = %s.", chlname);

    {
        session_thread_ptr thrd = session_thrd_mgr::instance()->get_prefer_thread();

        if (!thrd.is_valid()) {
            WARNING_LOG("[%ld]CreateSession failed, get prefer thread error", reqid);
            return CcResultT::ResFailed;
        }

        if (!session_mgr->create_session(fs_no,
                                         reqid,
                                         SCRT_INBOUND_IVR,
                                         thrd,
                                         ims_tool_t::chlname2no(chlname).c_str(),
                                         oricalled.c_str(),
                                         sid)) {
            WARNING_LOG("[%ld]CreateSession failed, create session error", reqid);
            return CcResultT::ResFailed;
        }
    }

    session_mgr->update_session_operation(sid, SOPR_IVRTRANSFER, chlname);

    if (!session_mgr->create_channel(sid, channel_id.c_str(), chlname)) {
        WARNING_LOG("[%ld]CreateSession failed, create channel error, ommiting session", reqid);
        session_mgr->remove_session(sid);
        return CcResultT::ResFailed;
    }

    callid_t callid = 0;

    if (!session_mgr->create_call(sid, channel_id.c_str(), NULL, callid)) {
        WARNING_LOG("[%ld]CreateSession failed, create call error, ommiting...", reqid);
        session_mgr->destroy_channel(channel_id.c_str());
        return CcResultT::ResFailed;
    }

    session_mgr->update_call_ani(sid, callid, ims_tool_t::chlname2no(chlname).c_str());

    //mark channel with sessionid
    if (IMS_SUCCESS != opr.opr().mark_sessionid(channel_id.c_str(), sid)) {
        WARNING_LOG("[%ld]CreateSession failed, mark sessionid error, ommiting...", reqid);
        session_mgr->destroy_channel(channel_id.c_str());
        return CcResultT::ResFailed;
    }

    NOTICE_LOG("[%ld] CreateSession OK. callsource:%s, channel_id:%s, sessionid:%ld",
               reqid, callsource.c_str(), channel_id.c_str(), sid);

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::TransferAgent(ReqIdT reqid,
                                       SessionIdT sessionid,
                                       RouteRequestIDT requestId,
                                       const TransferTypeT& transType,
                                       const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("TransferAgent start. reqid=%ld,sid=%ld,requestId=%ld,transType=%s",
               reqid, sessionid, requestId, transType.get_desc().c_str());
    judge_req("TransferAgent", reqid);

    ims_route_info_t info;

    if (!session_mgr->rt_query_route(requestId, info)) {
        WARNING_LOG("TransferAgent failed(sid=%ld,requestId=%ld,requestId not exist)",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    if (sessionid != info.sessionid) {
        WARNING_LOG("TransferAgent failed(sid=%ld,requestId=%ld),sessionid!=info.sessionid.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    if (0 == info.targetUri.size()) {
        WARNING_LOG("TransferAgent failed(sid=%ld,requestId=%ld), info.targetUri is null.",
                    sessionid, requestId);
        return CcResultT::ResInvalidState;
    }

    std::list<const char*> chls;

    if (!session_mgr->get_channelsbysession(sessionid, chls) || 0 == chls.size()) {
        WARNING_LOG("TransferAgent failed(sid=%ld,requestId=%ld), session no channel.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    std::string client_chlname;

    if (!session_mgr->get_channelnamebyid(sessionid, chls.front(), client_chlname)
            || client_chlname.size() == 0) {
        WARNING_LOG("TransferAgent failed(sid=%ld,requestId=%ld), get channel name error.",
                    sessionid, requestId);
        return CcResultT::ResInvalidParam;
    }

    callid_t callid;
    session_mgr->locate_call(chls.front(), callid);

    //把transType 放到 selfrun data，在ivrtransfer event handler中判断来确定要不要挂断客户
    if (!session_mgr->add_rundata(sessionid, "TransferTypeT", transType.get_desc().c_str())) {
        WARNING_LOG("[%ld][%ld]TransferAgent faied, add rundata failed.", reqid, sessionid);
        //return;
    }

    std::string assign_num = ims_tool_t::get_assigned_caller(info.targetUri, info.targetUri);

    switch (transType.get_value()) {
    case ims::TransferTypeT::TT_INSTANT: {
        char result[LEN_128 + 1] = {0};
        int ret = IMS_FAIL_GENERAL;
        {
            fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

            if (!opr.valid()) {
                WARNING_LOG("TransferAgent failed(sid=%ld,reqid=%ld, opr error)", reqid, sessionid);
                return CcResultT::ResNoEnoughResource;
            }

            ret = opr.opr().bridge_ex(chls.front(), info.callerDn.c_str(), assign_num.c_str(), true, true);
        }

        if (IMS_SUCCESS != ret) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, esl_execute_async bridge failed.", reqid, sessionid);
            OtherEventT otherevent;
            otherevent.sessionid = sessionid;
            otherevent.device = info.targetUri;
            otherevent.callid = ims_tool_t::num2str(callid);
            otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
            otherevent.data.insert(std::pair<std::string, std::string>("REASON", std::string(result)));
            otherevent.timestamp = ims_tool_t::get_timestamp_ms();
            session_mgr->add_imsevent_other(sessionid, otherevent);

            goto fail;
        }

        break;
    }

    case ims::TransferTypeT::TT_RING: {
        bgcc::Semaphore ring_sema;
        info.psema = &ring_sema;

        if (!session_mgr->rt_update_route(requestId, info)) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, update route error.", reqid, sessionid);
            goto fail;
        }

        char result[LEN_128 + 1] = {0};
        int ret = IMS_FAIL_GENERAL;
        {
            fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

            if (!opr.valid()) {
                WARNING_LOG("TransferAgent failed(sid=%ld,reqid=%ld, opr error)", reqid, sessionid);
                return CcResultT::ResNoEnoughResource;
            }

            ret = opr.opr().bridge_ex(chls.front(), info.callerDn.c_str(), assign_num.c_str(), false, true);
        }

        if (IMS_SUCCESS != ret) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, esl_execute bridge failed.", reqid, sessionid);
            OtherEventT otherevent;
            otherevent.sessionid = sessionid;
            otherevent.device = info.targetUri;
            otherevent.callid = ims_tool_t::num2str(callid);
            otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
            otherevent.data.insert(std::pair<std::string, std::string>("REASON", std::string(result)));
            otherevent.timestamp = ims_tool_t::get_timestamp_ms();
            session_mgr->add_imsevent_other(sessionid, otherevent);

            goto fail;
        }

        TRACE_LOG("[%ld][%ld]before wait until agent ring : event CHANNEL_PROGRESS", reqid, sessionid);
        //any valid call is surposed to be ringed with 10 seconds
        int32_t retw = ring_sema.wait(IMS_WAIT_RING_TIMEOUT);
        TRACE_LOG("[%ld][%ld]after wait until agent ring : event CHANNEL_PROGRESS", reqid, sessionid);

        if (0 != retw) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, wait for ring failed.ret=(%d)", reqid, sessionid,
                        retw);
            goto fail;
        } else {
            ims_route_info_t info_temp;

            if (!session_mgr->rt_query_route(requestId, info_temp)) {
                WARNING_LOG("[%ld][%ld]TransferAgent failed, query route failed. requestId=(%ld)",
                            reqid, sessionid, requestId);
                goto fail;
            }

            DEBUG_LOG("[%ld][%ld] state_signal (%d)", reqid, sessionid, info_temp.state_signal);

            if (info_temp.state_signal != STATE_RING) {
                WARNING_LOG("[%ld][%ld]TransferAgent failed, state_signal is not STATE_RING. state=(%d)",
                            reqid, sessionid, info_temp.state_signal);
                goto fail;
            }
        }

        break;
    }

    case ims::TransferTypeT::TT_ANSWER: {
        bgcc::Semaphore answer_sema;
        info.psema = &answer_sema;

        if (!session_mgr->rt_update_route(requestId, info)) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, update route error.", reqid, sessionid);
            goto fail;
        }

        char result[LEN_128 + 1] = {0};
        int retl = IMS_FAIL_GENERAL;
        {
            fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

            if (!opr.valid()) {
                WARNING_LOG("TransferAgent failed(sid=%ld,reqid=%ld, opr error)", reqid, sessionid);
                return CcResultT::ResNoEnoughResource;
            }

            retl = opr.opr().single_originate(assign_num.c_str(),
                                              info.callerDn.c_str(),
                                              sessionid,
                                              false, false,
                                              NULL, 0,
                                              result, LEN_128);
        }

        if (IMS_SUCCESS != retl) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, invoke fs single_originate failed.", reqid, sessionid);
            OtherEventT otherevent;
            otherevent.sessionid = sessionid;
            otherevent.device = info.targetUri;
            otherevent.callid = ims_tool_t::num2str(callid);
            otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
            otherevent.data.insert(std::pair<std::string, std::string>("REASON", std::string(result)));
            otherevent.timestamp = ims_tool_t::get_timestamp_ms();
            session_mgr->add_imsevent_other(sessionid, otherevent);

            goto fail;
        }

        TRACE_LOG("[%ld][%ld]before wait until agent answer : event CHANNEL_ANSWER", reqid, sessionid);
        //any valid call is surposed to be answered with 60 seconds
        int32_t retw = answer_sema.wait(IMS_WAIT_ANSWER_TIMEOUT);
        TRACE_LOG("[%ld][%ld]after wait until agent answer : event CHANNEL_ANSWER", reqid, sessionid);

        if (0 != retw) {
            WARNING_LOG("[%ld][%ld]TransferAgent failed, wait for answer failed.ret=(%d)", reqid, sessionid,
                        retw);
            goto fail;
        } else {
            ims_route_info_t info_temp;

            if (!session_mgr->rt_query_route(requestId, info_temp)) {
                WARNING_LOG("[%ld][%ld]TransferAgent failed, query route failed. requestId=(%ld)",
                            reqid, sessionid, requestId);
                goto fail;
            }

            DEBUG_LOG("[%ld][%ld] state_signal (%d)", reqid, sessionid, info_temp.state_signal);

            if (info_temp.state_signal != STATE_ANSWER) {
                WARNING_LOG("[%ld][%ld]TransferAgent failed, state_signal is not STATE_ANSWER. state=(%d)",
                            reqid, sessionid, info_temp.state_signal);
                goto fail;
            }
        }

        break;
    }

    default:
        WARNING_LOG("[%ld][%ld]TransferAgent failed, Unkonwn transfertype:%s", reqid, sessionid,
                    transType.get_desc().c_str());
        return CcResultT::ResInvalidParam;
    }

    NOTICE_LOG("TransferAgent OK. reqid=%ld,sid=%ld,requestId=%ld,transType=%s",
               reqid, sessionid, requestId, transType.get_desc().c_str());
    return CcResultT::ResSuccess;

fail:

    if (!session_mgr->rt_del_session_route(sessionid)) {
        WARNING_LOG("[%ld][%ld]TransferAgent failed, delete session route info failed.", reqid, sessionid);
    }

    return CcResultT::ResFailed;
}
CcResultT imsapi_impl_t::Record(ReqIdT reqid,
                                SessionIdT sessionid,
                                const std::string& devicenumber,
                                const std::string& filename,
                                int32_t maxTime,
                                const std::string& interruptKeys,
                                const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("Record start.reqid=%lu,sid=%lu,devicenumber=%s,filename=%s",
               reqid, sessionid, devicenumber.c_str(), filename.c_str());
    judge_req("Record", reqid);
    char tmp[LEN_64 + 1] = {0};
    std::string chlname = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("Record", chlname.c_str(), reqid);

    if (session_mgr->locate_channel(sessionid, chlname.c_str(), tmp, LEN_64)) {
        fs_tool_t opr(ims_tool_t::get_fsno(sessionid));

        if (opr.valid()
                && opr.opr().record(tmp, filename.c_str(), maxTime) == IMS_SUCCESS) {

            NOTICE_LOG("Record OK. reqid=%lu,sid=%lu,devicenumber=%s,filename=%s.",
                       reqid, sessionid, devicenumber.c_str(), filename.c_str());
            return CcResultT::ResSuccess;
        } else {
            WARNING_LOG("Record failed(sid=%lu,reqid=%ld,deviceno=%s fs error)",
                        reqid, sessionid, devicenumber.c_str());
            return CcResultT::ResNoEnoughResource;
        }
    } else {
        WARNING_LOG("Record failed(sid=%lu,reqid=%ld,deviceno=%s locate channel err)",
                    reqid, sessionid, devicenumber.c_str());

        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::SendDTMF(ReqIdT reqid,
                                  SessionIdT sessionid,
                                  const std::string& devicenumber,
                                  const std::string& dtmf,
                                  const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("SendDTMF reqid=%lu,sid=%lu,devicenumber=%s,dtmf=%s",
               reqid, sessionid, devicenumber.c_str(), dtmf.c_str());
    judge_req("SendDTMF", reqid);
    char tmp[LEN_64 + 1] = {0};
    std::string chlname = ims_tool_t::get_assigned_caller(devicenumber, devicenumber);
    judge_agent("SendDTMF", chlname.c_str(), reqid);

    if (dtmf.size() == 0 || dtmf.size() > 20) {
        return CcResultT::ResInvalidParam;
    }

    if (session_mgr->locate_channel(sessionid, chlname.c_str(), tmp, LEN_64)) {
        uint32_t fs_no = ims_tool_t::get_fsno(sessionid);
        fs_tool_t opr(fs_no);

        if (!opr.valid()) {
            WARNING_LOG("SendDTMF failed(sid=%lu,reqid=%ld,deviceno=%s fs error)",
                        reqid, sessionid, devicenumber.c_str());
            return CcResultT::ResNoEnoughResource;
        }

        dtmf_type_t dtmf_type;
        session_mgr->config().get_gwdtmftype(fs_no, dtmf_type);
        std::list<const char*> chls;
        char sz_digit[LEN_32 + 1] = {0};

        if (!session_mgr->get_channelsbysession(sessionid, chls)
                || chls.size() < 1) {
            WARNING_LOG("SendDTMF failed(sid=%lu,reqid=%ld,deviceno=%s locate other err)",
                        reqid, sessionid, devicenumber.c_str());
            return CcResultT::ResFailed;
        }

        int ret = -1;

        if (DTMF_INBAND == dtmf_type) {
            std::string::const_iterator it = dtmf.begin();

            while (it != dtmf.end()) {
                if (isdigit(*it) || '*' == (*it) || '#' == (*it)) {
                    for (std::list<const char*>::iterator chl_it = chls.begin();
                            chl_it != chls.end(); ++chl_it) {
                        snprintf(sz_digit, LEN_32, "${sound_prefix}/dtmf/%c.wav", *it);
                        ret = opr.opr().play(*chl_it, sz_digit);

                        if (ret == IMS_SUCCESS) {
                            TRACE_LOG("send_dtmf %c success", *it);
                        } else {
                            TRACE_LOG("send_dtmf %c failed", *it);
                        }
                    }

                    if ((++it) != dtmf.end()) {
                        ims_tool_t::safe_sleepms(200);
                    }

                } else {
                    ++it;
                }
            }
        } else {
            snprintf(sz_digit, LEN_32, "%s", dtmf.c_str());

            for (std::list<const char*>::iterator chl_it = chls.begin();
                    chl_it != chls.end(); ++chl_it) {
                ret = opr.opr().send_dtmf(*chl_it, sz_digit);

                if (ret == IMS_SUCCESS) {
                    NOTICE_LOG("send_dtmf %s success", dtmf.c_str());
                } else {
                    TRACE_LOG("send_dtmf %s failed", dtmf.c_str());
                }
            }
        }

        return CcResultT::ResSuccess;
    } else {
        WARNING_LOG("SendDTMF failed(sid=%lu,reqid=%ld,deviceno=%s locate channel err)",
                    reqid, sessionid, devicenumber.c_str());

        return CcResultT::ResFailed;
    }
}

CcResultT imsapi_impl_t::DestroySession(ReqIdT reqid,
                                        SessionIdT sessionid,
                                        const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("[%ld][%ld] DestroySession start.", reqid, sessionid);
    judge_req("DestroySession", reqid);

    if (!session_mgr->destroy_session(sessionid)) {
        WARNING_LOG("[%ld][%ld]DestroySession failed.", reqid, sessionid);
        return CcResultT::ResFailed;
    }

    TRACE_LOG("in DestroySession clear dead session before return");
    session_mgr->clear_dead_session();

    NOTICE_LOG("[%ld][%ld] DestroySession OK.", reqid, sessionid);
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::QuerySession(ReqIdT reqid,
                                      SessionIdT sessionid,
                                      std::string& originalAni,
                                      std::string& originalDnis,
                                      CallIdListT& callidList,
                                      std::vector<std::string>& deviceList,
                                      const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("enter querysession(%lu,%lu)", reqid, sessionid);
    judge_req("QuerySession", reqid);
    callidList.clear();
    deviceList.clear();

    std::list<const char*> chls;
    std::list<callid_t> calls;

    if (!session_mgr->get_channelsbysession(sessionid, chls) || chls.size() == 0
            || !session_mgr->locate_call(sessionid, calls)
            || calls.size() == 0
            || !session_mgr->get_callercalled(sessionid, originalAni, originalDnis)) {
        return CcResultT::ResInvalidParam;
    }

    std::string chlname;

    for (std::list<const char*>::iterator it = chls.begin(); it != chls.end(); ++it) {
        if (session_mgr->get_channelnamebyid(sessionid, *it, chlname)) {
            std::string chlno = ims_tool_t::chlname2no(chlname);
            deviceList.push_back(chlno);
        }
    }

    for (std::list<callid_t>::iterator it = calls.begin(); it != calls.end(); ++it) {
        callidList.push_back(ims_tool_t::num2str(*it));
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::QueryCall(ReqIdT reqid,
                                   SessionIdT sessionid,
                                   const CallIdT& callId,
                                   std::string& deviceAni,
                                   std::string& deviceDnis,
                                   std::string& originalAni,
                                   std::string& originalDnis,
                                   std::vector<std::string>& devicelist,
                                   int32_t& fsid,
                                   const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("enter querycall(%lu,%lu,%s)", reqid, sessionid, callId.c_str());
    judge_req("QueryCall", reqid);
    devicelist.clear();
    deviceAni = "";
    deviceDnis = "";

    std::list<const char*> chls;

    if (!session_mgr->get_channelsbycall(sessionid, atoll(callId.c_str()), chls)
            || chls.size() == 0
            || !session_mgr->get_callercalled(sessionid, originalAni, originalDnis)) {
        return CcResultT::ResInvalidParam;
    }

    session_mgr->get_call_info(sessionid, atoll(callId.c_str()), deviceAni, deviceDnis);

    std::string chlname, chlno;

    for (std::list<const char*>::iterator it = chls.begin(); it != chls.end(); ++it) {
        if (session_mgr->get_channelnamebyid(sessionid, *it, chlname)) {
            chlno = ims_tool_t::chlname2no(chlname);
            devicelist.push_back(chlno);
        }
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::QueryDevice(ReqIdT reqid,
                                     const std::string& device,
                                     SessionIdT& sessionid,
                                     CallIdT& callId,
                                     CallStateT& callstate,
                                     MediaStateT& mediastate,
                                     const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("enter querydevice(%lu,%s)", reqid, device.c_str());
    judge_req("QueryDevice", reqid);
    std::string caller = ims_tool_t::get_assigned_caller(device, device);
    judge_agent("QueryDevice", caller.c_str(), reqid);

    callId = "";
    callstate = ims::CallStateT::SG_UnknownState;
    mediastate = ims::MediaStateT::MG_UnknownState;

    char chlno[LEN_64 + 1] = {0};
    SessionIdT sid = 0;

    if (!session_mgr->locate_sessionbyname(caller.c_str(), sid)
            || !session_mgr->locate_channel(sid, caller.c_str(), chlno, LEN_64)) {
        callstate = ims::CallStateT::SG_IdleState;
        mediastate = ims::MediaStateT::MG_IdleState;
        return CcResultT::ResSuccess;
    }

    sessionid = sid;
    callid_t callid;

    if (session_mgr->locate_call(chlno, callid)) {
        callId = ims_tool_t::num2str(callid);
    }

    session_mgr->get_channel_callstate(chlno, callstate);
    session_mgr->get_channel_mediastate(chlno, mediastate);

    NOTICE_LOG("leave querydevice(%lu,%s)", reqid, device.c_str());

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::QuerySysInfo(ReqIdT reqid,
                                      SysInfoT& sysinfo,
                                      const std::map<std::string, std::string>& ctx) {

    NOTICE_LOG("enter querysysinfo(%lu)", reqid);
    judge_req("QuerySysInfo", reqid);
    sysinfo.sessionCount = session_mgr->get_sessioncount();
    sysinfo.sessionSinceStartup = session_mgr->get_sessionaccu();

    uint64_t duration = (ims_tool_t::get_timestamp_ms() - session_mgr->get_starttime()) / 1000 / 1000;
    TRACE_LOG("now:%ld,start:%ld,duration:%ld", ims_tool_t::get_timestamp_ms(),
              session_mgr->get_starttime(), duration);

    if (duration) {
        sysinfo.sessionPerSec = session_mgr->get_sessionaccu() * 1.0 / duration;
    } else {
        sysinfo.sessionPerSec = 0.0;
    }

    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::ReloadConfig(const ims::ConfigTypeT& type,
                                      const std::map<std::string, std::string>& ctx) {
    NOTICE_LOG("enter reloadconfig");
    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    ims_conf_t& conf = pmgr->config();
    return (ims_conf_loader_t::instance()->load_conf(pmgr->pool(), conf, true) ?
            CcResultT::ResSuccess : CcResultT::ResFailed);
}

bool imsapi_impl_t::is_inbound(
    const std::string& func,
    const SessionIdT sessionid,
    const std::string& device,
    const std::string& name,
    callid_t& callid,
    std::string& chlid_self,
    std::list<const char*>& otherids) {

    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();
    char chlid[LEN_64 + 1] = {0};

    if (!session_mgr->is_inbound_session(sessionid)) {
        TRACE_LOG("%s(sid=%ld) failed, not inbound sessionid"
                  , func.c_str(), sessionid);
        return false;
    }

    if (!session_mgr->locate_callbyname(sessionid, name.c_str(), callid, chlid, LEN_64)) {
        TRACE_LOG("%s(sid=%ld) failed, cannot locate channel by dn(%s)"
                  , func.c_str(), sessionid, name.c_str());
        return false;
    }

    if (!session_mgr->locate_otherchannel(sessionid, callid, chlid, otherids)
            || otherids.size() == 0) {
        WARNING_LOG("%s(sid=%lu,callid=%lu,self=%s)locate_otherchannel failed"
                    , func.c_str(), sessionid, callid, chlid);
        return false;
    }

    if (otherids.size() > 1) {
        WARNING_LOG("%s,inbound call && callparty>3", func.c_str());
        return false;
    }

    chlid_self = chlid;

    return true;
}

bool imsapi_impl_t::is_state(
    const std::string& func,
    const SessionIdT sessionid,
    const std::string& device,
    const std::string& name,
    const ims_session_operation_t param_operation,
    callid_t& callid,
    std::string& chlid_self,
    std::list<const char*>& otherids) {

    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();
    char chlid[LEN_64 + 1] = {0};

    ims_session_operation_t operation;
    {
        char opr[LEN_64 + 1] = {0};

        if (!session_mgr->get_session_operation(sessionid, operation, opr, LEN_64)
                || param_operation != operation
                || strcasecmp(opr, name.c_str())) {
            TRACE_LOG("%s(sid=%ld) failed, %s(active operation:%u require %u, active opr is %s)"
                      , func.c_str(), sessionid,
                      name.c_str(), operation, param_operation, opr);

            return false;
        }
    }

    if (!session_mgr->locate_callbyname(sessionid, name.c_str(), callid, chlid, LEN_64)) {
        TRACE_LOG("%s(sid=%ld) failed, cannot locate channel by dn(%s)"
                  , func.c_str(), sessionid, name.c_str());
        return false;
    }

    if (!session_mgr->locate_otherchannel(sessionid, callid, chlid, otherids)
            || otherids.size() == 0) {
        WARNING_LOG("%s(sid=%lu,callid=%lu,self=%s)locate_otherchannel failed"
                    , func.c_str(), sessionid, callid, chlid);
        return false;
    }

    chlid_self = chlid;

    return true;
}

bool imsapi_impl_t::is_idle(
    const std::string& func,
    const std::string& device,
    const std::string& name) {
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

    if (!session_mgr->rt_query_dn(name.c_str(), DnTypeT::AgentDn)) {
        return true;
    }

    SessionIdT sid = 0;

    if (!session_mgr->locate_sessionbyname(name.c_str(), sid)) {
        return true;
    } else {
        TRACE_LOG("%s channelname(%s) exist in session(%lu), check if it's dead session. "
                  , func.c_str(), name.c_str(), sid);
        // check if the channelid exist in freeswitch.
        // if func"channel exist in ims session must exist in freeswitch"
        fs_tool_t opr(ims_tool_t::get_fsno(sid));
        std::list<const char*> chls;

        if (opr.valid() && session_mgr->get_channelsbysession(sid, chls)) {
            bool is_dead_session = true;

            for (std::list<const char*>::iterator it = chls.begin();
                    it != chls.end(); ++it) {
                if (IMS_SUCCESS == opr.opr().uuid_exists(*it)) {
                    is_dead_session = false;
                }
            }

            if (is_dead_session && session_mgr->destroy_session(sid)) {
                TRACE_LOG("%s all channels in session(%lu) don't exist in freeswitch."
                          , func.c_str(), sid);
                return true;
            }
        }

        TRACE_LOG("%s %s is busy", func.c_str(), name.c_str());
        return false;
    }
}

CcResultT imsapi_impl_t::create_ivr_outbound_session(
    ReqIdT reqid,
    SessionIdT& sid,
    uint32_t fsno) {
    judge_req("create_ivr_outbound_session", reqid);

    session_thread_ptr thrd = session_thrd_mgr::instance()->get_prefer_thread();

    if (!thrd.is_valid()) {
        WARNING_LOG("[%ld] CreateSessionOut failed, get_prefer_thread error.", reqid);
        return CcResultT::ResFailed;
    }

    if (!session_mgr->create_session(fsno,
                                     reqid,
                                     SCRT_OUTBOUND_IVR,
                                     thrd,
                                     NULL,
                                     NULL,
                                     sid)) {
        WARNING_LOG("[%ld] CreateSessionOut failed, create_session error.", reqid);
        return CcResultT::ResFailed;
    }

    session_mgr->update_session_operation(sid, SOPR_MAKECALL, NULL);

    NOTICE_LOG("[%ld] CreateSessionOut OK. channelid:%s, sessionid:%ld", reqid, SPECIAL_CHANNELID, sid);
    return CcResultT::ResSuccess;
}

CcResultT imsapi_impl_t::HeartBeat(ims::ReqIdT reqid,
                                   const std::string& info,
                                   const std::map<std::string, std::string>& ctx) {
    //NOTICE_LOG("HeartBeat.(%lu,%s)",reqid,info.c_str());
    judge_req("HeartBeat", reqid);
    ims::ReqIdT id = reqid;

    if ((id >> 56) == ims::ServiceTypeT::ServiceACD) {
        //TRACE_LOG("update acd as master or slave.");
        is_empty("HeartBear", "info", info);
        ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

        if (!session_mgr->rt_update_reqstate(reqid, info)) {
            WARNING_LOG("update acd as master or slave failed!");
        } else {
            //TRACE_LOG("update acd as master or slave done!");
        }
    } else {
        //do nothing if it's IVR's reqid
    }

    return CcResultT::ResSuccess;
}
}




/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
