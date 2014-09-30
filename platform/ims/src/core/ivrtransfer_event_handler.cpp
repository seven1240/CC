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

#include <bgcc.h>
#include "event_handler.h"
#include "ims_log.h"
#include "fs_struct.h"
#include "fs_opr.h"
#include "fs_mgr.h"
#include "ims_core_session_mgr.h"

using namespace bgcc;
namespace ims {

void event_handler_t::handle_ivrtransfer_event(const fs_event_t& evt) {
    debug_func("ivrtransfer", evt);

    std::string oricaller, oricalled;
    session_mgr->get_callercalled(evt.sessionid, oricaller, oricalled);

    if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
            || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) { //agent alerting

        if (!session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            //client ring
            DEBUG_LOG("ims got client's CHANNEL_PROGRESS event, do nothing.");
            return;
        }

        //if TT_RING, signal get event CHANNEL_PROGRESS
        char transType[26] = {0};//magic number:26 是最长的类型的字符串长度。

        if (session_mgr->get_rundata(evt.sessionid, "TransferTypeT", transType, 25)) {
            if (strncmp("TransferTypeT::TT_RING", transType, 22) == 0) {
                TRACE_LOG("transferType is TT_RING, signal get event CHANNEL_PROGRESS");
                ims_route_info_t info;

                if (!session_mgr->rt_query_session_route(evt.sessionid, info)) {
                    WARNING_LOG("query session route info failed(sid=%ld)", evt.sessionid);
                }

                info.state_signal = STATE_RING;

                if (info.psema) {
                    TRACE_LOG("after agent ring, signal get event %s", evt.name);
                    bgcc::Semaphore* psema = info.psema;
                    info.psema = NULL;

                    if (!session_mgr->rt_update_route(info.requestId, info)) {
                        WARNING_LOG("update session route info failed(requestId=%ld)", info.requestId);
                    }

                    ims_route_info_t temp;
                    session_mgr->rt_query_route(info.requestId, temp);
                    DEBUG_LOG("temp: requestId=%ld, psema=%p, state_signal = %u", temp.requestId, temp.psema,
                              temp.state_signal);
                    psema->signal();
                }
            }//if transType == TT_RING
            else {
                TRACE_LOG("transferType is not TT_RING, do nothing.");
            }
        }//if(session_mgr->get_rundata()
        else {
            WARNING_LOG("get transferType from rundata error.");
        }

        CallEventT callevent;
        session_mgr->get_channel_callstate(edata.uuid, callevent.state);

        if (callevent.state == CallStateT::SG_AlertingState) {
            return;
        }

        //agent ringring
        session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);
        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                       edata.deviceno, CallStateT::SG_AlertingState);

        callevent.eventType = CallEventTypeT::SG_InboundCall_NormalCall;
        callevent.partyNum = 2;
        callevent.otherAttr = PartyAttributeT::P_Normal;
        callevent.otherDevice = oricaller;

        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);
        //session_mgr->set_callercalled(evt.sessionid, oricaller, edata.deviceno);
    } else if (strcasecmp(evt.name, "CHANNEL_ANSWER") == 0) {
        if (!session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            //client answer
            DEBUG_LOG("ims got client's CHANNEL_ANSWER event, do nothing.");
            return;
        }

        //agent answer, only if transferType is TT_ANSWER, call uuid_bridge()
        char transType[26] = {0};//magic number:26 是最长的类型的字符串长度。

        if (session_mgr->get_rundata(evt.sessionid, "TransferTypeT", transType, 25)) {
            if (strncmp("TransferTypeT::TT_ANSWER", transType, 24) == 0) {
                TRACE_LOG("transferType is TT_ANSWER, signal get event CHANNEL_ANSWER`");
                ims_route_info_t info;

                if (!session_mgr->rt_query_session_route(evt.sessionid, info)) {
                    WARNING_LOG("query session route info failed(sid=%ld, sessionid not exist)",
                                evt.sessionid);
                }

                info.state_signal = STATE_ANSWER;

                if (info.psema) { //only when TT_RING, info.ring_sema != NULL
                    TRACE_LOG("after agent answer, signal get event %s", evt.name);
                    bgcc::Semaphore* psema = info.psema;
                    info.psema = NULL;

                    if (!session_mgr->rt_update_route(info.requestId, info)) {
                        WARNING_LOG("update session route info failed(requestId=%ld)", info.requestId);
                    }

                    psema->signal();
                }

                TRACE_LOG("transferType is TT_ANSWER, uuid_bridge agent and custom.");
                std::list<const char*> other_ids;

                if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)
                        || other_ids.size() == 0) {
                    WARNING_LOG("sid=%ld locate_otherchannel failed,chid:[%s]", evt.sessionid, edata.uuid);
                    return;
                }

                fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

                if (!opr.valid()) {
                    WARNING_LOG("get opr by session=%ld failed.", evt.sessionid);
                    return;
                }

                //opr.opr().hangup(edata.uuid);//for test when uuid_bridge failed
                if (opr.opr().uuid_bridge(edata.uuid, other_ids.front()) != IMS_SUCCESS) {
                    WARNING_LOG("uuid_bridge failed, hangup both. session=%ld", evt.sessionid);
                    opr.opr().hangup(edata.uuid);
                    opr.opr().hangup(other_ids.front());
                    return;
                }
            }//if transType == TT_ANSWER
            else {
                TRACE_LOG("transferType is not TT_ANSWER, do nothing.");
            }
        }//if(session_mgr->get_rundata()
        else {
            WARNING_LOG("get transferType from rundata error.");
        }

    } else if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        //if(edata.deviceno == oricaller){//client bridge
        TRACE_LOG("oricaller=%s, oricalled=%s", oricaller.c_str(), oricalled.c_str());
        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                              (edata.deviceno == oricaller) ? edata.other_channel_name : edata.channel_name);
        session_mgr->update_create_reason(evt.sessionid, SCRT_INBOUND_IVR);

        CallEventT callevent;
        ims_tool_t::prepare_call_event(callevent,
                                       evt.timestamp,
                                       evt.sessionid,
                                       ims_tool_t::num2str(evt.callid),
                                       (edata.deviceno == oricaller) ? edata.other_deviceno : edata.deviceno,
                                       CallStateT::SG_ConnectedState);

        callevent.eventType = CallEventTypeT::SG_ThisPartyAnswered_NormalCall;
        callevent.partyNum = 2;
        callevent.otherAttr = PartyAttributeT::P_Normal;
        callevent.otherDevice = (edata.deviceno == oricaller) ? edata.deviceno : edata.other_deviceno;

        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);
        //}
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        std::list<const char*> other_ids;
        session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids);

        fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

        if (!opr.valid()) {
            WARNING_LOG("[%ld]ivrtransfer_handler fetch_opr error.", evt.sessionid);
            return;
        }

        ims_route_info_t info;

        if (!session_mgr->rt_query_session_route(evt.sessionid, info)) {
            WARNING_LOG("query session route info failed(sid=%ld, sessionid not exist)",
                        evt.sessionid);
        }

        if (info.psema) {
            TRACE_LOG("if info.psema != NULL, signal get event %s", evt.name);
            info.psema->signal();
            info.psema = NULL;

            if (!session_mgr->rt_update_route(info.requestId, info)) {
                WARNING_LOG("update session route info failed(requestId=%ld)", info.requestId);
            }
        }

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) { //agent hangup
            TRACE_LOG("agent hangup. edata.channelname=%s, edata.other_channel_name=%s",
                      edata.channel_name, edata.other_channel_name);
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);
            callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
            callevent.partyNum = 1;
            callevent.otherAttr = PartyAttributeT::P_Unknown;
            //callevent.otherDevice=oricaller;

            ims::CallStateT state;
            session_mgr->get_channel_callstate(edata.uuid, state);

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);

            //如果转移类型不是TT_ANSWER, 挂断客户
            char transType[26] = {0};//magic number:26 是最长的类型的字符串长度。

            if (session_mgr->get_rundata(evt.sessionid, "TransferTypeT", transType, 25)) {
                if (state != CallStateT::SG_AlertingState && //处理没有channel_progress就直接挂断的情况。
                        strncmp("TransferTypeT::TT_INSTANT", transType, 25) != 0) { //假如是INSTANT，肯定要挂断客户
                    TRACE_LOG("channel state is not alerting and transferType is not TT_INSTANT");
                    return;
                }

                TRACE_LOG("Transfer type is %s, other_ids.size()=%ld", transType, other_ids.size());

                if (strncmp("TransferTypeT::TT_ANSWER", transType, 24) != 0  && other_ids.size() != 0) {
                    TRACE_LOG("hangup client uuid=%s", other_ids.front());
                    opr.opr().hangup(other_ids.front());
                }

                session_mgr->del_rundata(evt.sessionid, "TransferTypeT");
            } else {
                WARNING_LOG("get transferType from rundata error.");
            }
        } else { //client hangup
            TRACE_LOG("client hangup. edata.channelname=%s, edata.other_channel_name=%s"
                      "other_uuid=%s.", edata.channel_name, edata.other_channel_name, edata.other_uuid);

            if (other_ids.size() != 0) { // 如果已经调用了transferAgent
                std::string name;
                session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               ims_tool_t::chlname2no(name),//agent deviceno
                                               CallStateT::SG_IdleState);
                callevent.eventType  = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
                callevent.partyNum = 1;
                callevent.otherAttr = PartyAttributeT::P_Unknown;
                //callevent.otherDevice=edata.deviceno;//client device no

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
                //挂断坐席
                opr.opr().hangup(other_ids.front());
            }

            //取消路由请求
            ims_route_info_t info;

            if (!session_mgr->rt_query_session_route(evt.sessionid, info)) {
                WARNING_LOG("query session route info failed(sid=%ld, sessionid not exist)",
                            evt.sessionid);
                return;
            }

            session_mgr->rt_del_session_route(evt.sessionid);

            RouteEventT ims_event;
            ims_tool_t::prepare_route_event(ims_event, evt.sessionid, info);
            ims_event.eventType = RouteEventTypeT::RT_RouteRequestCancel;
            ims_event.reason = RouteEventReasonT::RouteReasonClientHangup;

            if (session_mgr->rt_add_imsevent_route(info.dest_reqid, ims_event)) {
                session_mgr->rt_del_route(info.requestId);
            } else {
                WARNING_LOG("add ims route event failed");
            }
        }//client hangup

        //删除路由信息
        session_mgr->rt_del_session_route(evt.sessionid);
    } else if (strcasecmp(evt.name, "OPERATION_FAILED") == 0) {
        ims_route_info_t info;

        if (!session_mgr->rt_query_session_route(evt.sessionid, info)) {
            WARNING_LOG("query session route info failed(sid=%ld, sessionid not exist)",
                        evt.sessionid);
            return;
        }

        if (info.psema) {
            TRACE_LOG("if info.psema != NULL, signal get event %s", evt.name);
            info.psema->signal();
            info.psema = NULL;

            if (!session_mgr->rt_update_route(info.requestId, info)) {
                WARNING_LOG("update session route info failed(requestId=%ld)", info.requestId);
            }
        }

        std::list<callid_t> calls;
        session_mgr->locate_call(evt.sessionid, calls);

        OtherEventT otherevent;
        otherevent.sessionid = evt.sessionid;
        otherevent.device = info.targetUri;
        otherevent.callid = ims_tool_t::num2str(calls.front());
        otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
        otherevent.timestamp = ims_tool_t::get_timestamp_ms();
        session_mgr->add_imsevent_other(evt.sessionid, otherevent);

        //hangup client
        std::list<const char*> chls;
        session_mgr->get_channelsbysession(evt.sessionid, chls);
        fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

        if (!opr.valid()) {
            WARNING_LOG("[%ld]ivrtransfer_handler fetch_opr error.", evt.sessionid);
            return;
        }

        opr.opr().hangup(chls.front());//front is client's channel id.

        //删除路由信息
        session_mgr->rt_del_session_route(evt.sessionid);
    }//if(strcasecmp(evt.name,"OPERATION_FAILED")
}
}//namespace ims



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
