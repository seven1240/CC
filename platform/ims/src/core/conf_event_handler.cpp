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

#include "event_handler.h"
#include "ims_log.h"
#include "fs_struct.h"
#include "fs_opr.h"
#include "fs_mgr.h"
#include "ims_core_session_mgr.h"

namespace ims {

void event_handler_t::handle_singlestepconference_event(const fs_event_t& evt, bool binsert) {

    debug_func("singlesetpconference", evt);

    if (strcasecmp(evt.name, "OPERATION_FAILED") == 0) {
        OtherEventT otherevent;
        otherevent.sessionid = evt.sessionid;
        otherevent.callid = "";
        //session_mgr->get_session_operator(evt.sessionid,otherevent.device);
        otherevent.device = ims_tool_t::chlname2no(edata.channel_name);
        otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
        otherevent.timestamp = evt.timestamp;
        otherevent.data.insert(std::pair<std::string, std::string>("REASON", edata.reason));
        /*
        if(strcasecmp(edata.reason,"DESTINATION_OUT_OF_ORDER")==0
                ||strcasecmp(edata.reason,"USER_NOT_REGISTERED")==0
                ||strcasecmp(edata.reason,"INVALID_NUMBER_FORMAT")==0
                ||strcasecmp(edata.reason,"NETWORK_OUT_OF_ORDER")==0){//no channel_* event
            session_mgr->remove_session(evt.sessionid);
        */
        return;
    }

    std::string opr_deviceno;
    session_mgr->get_session_operator(evt.sessionid, opr_deviceno);
    char opr_channelid[LEN_64] = {0};

    std::list<const char*> otherids;
    char other_agtid[LEN_64] = {0}, other_custid[LEN_64] = {0};
    std::string other_agtname, other_custname;

    session_mgr->locate_channel(evt.sessionid, opr_deviceno.c_str(), opr_channelid, LEN_64);
    session_mgr->locate_otherchannel(evt.sessionid, evt.callid, opr_channelid, otherids);

    std::string tmp;

    for (std::list<const char*>::iterator it = otherids.begin();
            it != otherids.end(); ++it) {
        if (session_mgr->get_channelnamebyid(evt.sessionid, *it, tmp)) {
            if (session_mgr->rt_query_dn(tmp.c_str(), DnTypeT::AgentDn)) {
                strncpy(other_agtid, *it, LEN_64);
                other_agtname = tmp;
            } else {
                strncpy(other_custid, *it, LEN_64);
                other_custname = tmp;
            }
        }
    }

    if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
            || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) { //monitor ringing
        if (!session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            return;
        }

        CallEventT callevent;
        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                       edata.deviceno, CallStateT::SG_HalfAlertingState);
        callevent.eventType = CallEventTypeT::SG_InboundCall_InternalCall;
        callevent.partyNum = 1;

        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);
    } else if (strcasecmp(evt.name, "CHANNEL_ANSWER") == 0) { //monitor ringing
        if (!session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            return;
        }

        CallEventT callevent;
        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                       edata.deviceno, CallStateT::SG_HalfConnectedState);
        callevent.eventType = CallEventTypeT::SG_ThisPartyAnswered_InternalCall;
        callevent.partyNum = 1;

        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);

        fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

        if (!opr.valid()) {
            WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
            return;
        }

        std::list<const char*> chls;

        if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, chls)
                || chls.size() != 2) {
            WARNING_LOG("sid=%lu,callid=%lu,size=%ld locate otherchannel failed"
                        , evt.sessionid, evt.callid, chls.size());

            opr.opr().hangup(edata.uuid);
            return;
        }

        char conf_name[LEN_64 + 1] = {0};

        if (!session_mgr->get_rundata(evt.sessionid, "conf_name", conf_name, LEN_64)) {
            opr.opr().hangup(edata.uuid);
            WARNING_LOG("sid=%lu,callid=%lu,get rundata failed"
                        , evt.sessionid, evt.callid);
        }

        opr.opr().conference(chls.front(), conf_name);
        opr.opr().conference(chls.back(), conf_name);
    } else if (strcasecmp(evt.name, "CONFERENCE_MUTE") == 0) {
        session_mgr->update_session_operation(evt.sessionid, SOPR_LISTEN, edata.channel_name);

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_ConferenceState);
            callevent.eventType = CallEventTypeT::SG_ThisPartyConferenced_MonitorCall;
            callevent.partyNum = 3;
            callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        if (session_mgr->rt_query_dn(other_agtname.c_str(), DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           ims_tool_t::chlname2no(other_agtname), CallStateT::SG_ConferenceState);

            callevent.eventType = CallEventTypeT::SG_OtherPartyConferenced_MonitorCall;
            callevent.otherDevice = edata.deviceno;
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(other_agtid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CONFERENCE_UNMUTE") == 0) {
        session_mgr->update_session_operation(evt.sessionid, SOPR_INSERT, edata.channel_name);

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_ConferenceState);
            callevent.eventType = CallEventTypeT::SG_ThisPartyConferenced_IntrudeCall;
            callevent.partyNum = 3;
            callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        if (session_mgr->rt_query_dn(other_agtname.c_str(), DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           ims_tool_t::chlname2no(other_agtname), CallStateT::SG_ConferenceState);

            callevent.eventType = CallEventTypeT::SG_OtherPartyConferenced_IntrudeCall;
            callevent.otherDevice = edata.deviceno;
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(other_agtid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CONFERENCE_JOIN") == 0) {

        session_mgr->add_rundata(evt.sessionid, edata.uuid, edata.ims_data);

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_ConferenceState);

            callevent.partyNum = 3;

            if (opr_deviceno == edata.channel_name) {
                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_ThisPartyConferenced_IntrudeCall
                     : CallEventTypeT::SG_ThisPartyConferenced_MonitorCall
                    ) ;
                callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
                callevent.otherAttr = PartyAttributeT::P_Internal;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            } else if (edata.deviceno == ims_tool_t::chlname2no(other_agtname)) {
                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_OtherPartyConferenced_IntrudeCall
                     : CallEventTypeT::SG_OtherPartyConferenced_MonitorCall
                    ) ;
                callevent.originatingParty = ims_tool_t::chlname2no(opr_deviceno);
                callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                callevent.otherAttr = PartyAttributeT::P_Internal;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        }
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        TRACE_LOG("opr=%s,otheragt=%s,edata.deviceno=%s"
                  , opr_deviceno.c_str(), other_agtname.c_str(), edata.deviceno);
        TRACE_LOG("oprid=%s,otheragtid=%s,edata.uuid=%s"
                  , opr_channelid, other_agtid, edata.uuid);

        //need to update ani dnis;
        if (strcasecmp(edata.channel_name , opr_deviceno.c_str()) != 0) {
            std::string src_ani, src_dnis;
            session_mgr->get_call_info(evt.sessionid, evt.callid, src_ani, src_dnis);

            if (src_ani == edata.deviceno) {
                session_mgr->update_call_ani(evt.sessionid, evt.callid,
                                             ims_tool_t::chlname2no(opr_deviceno).c_str());
            } else if (src_dnis == edata.deviceno) {
                session_mgr->update_call_dnis(evt.sessionid, evt.callid,
                                              ims_tool_t::chlname2no(opr_deviceno).c_str());
            }
        } else {
            ims::CallStateT state;

            if (session_mgr->get_channel_callstate(edata.uuid, state)
                    && state != CallStateT::SG_ConferenceState) {
                //发起质检之后，发起质检方未接通
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_IdleState);
                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_ThisPartyDisconnect_IntrudeCall
                     : CallEventTypeT::SG_ThisPartyDisconnect_MonitorCall
                    ) ;
                callevent.partyNum = 0;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);

                session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                                      session_mgr->rt_query_dn(other_agtname.c_str() ,
                                                              DnTypeT::AgentDn) ? other_agtname.c_str() : other_custname.c_str());

                //delete rundata<"conf_name", name_uuid>
                session_mgr->del_rundata(evt.sessionid, "conf_name");
                return;
            }
        }

        if (strcasecmp(edata.channel_name, opr_deviceno.c_str()) == 0
                || strcasecmp(edata.channel_name, other_agtname.c_str()) == 0) {
            //confer pary hangup
            {

                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_IdleState);
                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_ThisPartyDisconnect_IntrudeCall
                     : CallEventTypeT::SG_ThisPartyDisconnect_MonitorCall
                    ) ;
                callevent.partyNum = 0;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                TRACE_LOG("update %s to state:%s", edata.deviceno, callevent.state.get_desc().c_str());
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
            ims::CallStateT state;

            if (0 == strcasecmp(edata.channel_name, other_agtname.c_str())
                    && session_mgr->get_channel_callstate(opr_channelid, state)
                    && state == CallStateT::SG_HalfAlertingState) {
                TRACE_LOG("other agent(%s) hangup when cur_opr(%s) is alerting."
                          , other_agtname.c_str(), opr_deviceno.c_str());

                //tell opr agent that other agent has hangup, so he know why insert is failed.
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid
                                               , ims_tool_t::num2str(evt.callid)
                                               , ims_tool_t::chlname2no(opr_deviceno)
                                               , CallStateT::SG_IdleState);

                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                     : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                    ) ;
                callevent.originatingParty = edata.deviceno;
                callevent.partyNum = 2;
                callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
                callevent.otherAttr = PartyAttributeT::P_Internal;

                session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                TRACE_LOG("update %s to state:%s", opr_deviceno.c_str(), callevent.state.get_desc().c_str());
                session_mgr->add_imsevent_call(evt.sessionid, callevent);

            } else if ('\0' != other_agtname[0] || opr_deviceno.size()) { //must be monitored
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               (strcasecmp(edata.channel_name , opr_deviceno.c_str()) == 0
                                                ? ims_tool_t::chlname2no(other_agtname)
                                                : ims_tool_t::chlname2no(opr_deviceno))
                                               , CallStateT::SG_ConnectedState);

                callevent.eventType  =
                    (binsert
                     ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                     : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                    );
                callevent.originatingParty = edata.deviceno;
                callevent.partyNum = 2;
                callevent.otherDevice = ims_tool_t::chlname2no(other_custname);
                callevent.otherAttr = PartyAttributeT::P_Normal;

                if (strcasecmp(edata.channel_name , opr_deviceno.c_str()) == 0) {
                    session_mgr->update_channel_callstate(other_agtid, callevent.state);
                    TRACE_LOG("update %s to state:%s", other_agtname.c_str(), callevent.state.get_desc().c_str());
                } else {
                    session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                    TRACE_LOG("update %s to state:%s", opr_deviceno.c_str(), callevent.state.get_desc().c_str());
                }

                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        } else {
            //cust hangup
            ims::CallStateT state;

            if (session_mgr->get_channel_callstate(opr_channelid, state)
                    && state == CallStateT::SG_HalfAlertingState) {
                TRACE_LOG("customer(%s) hangup when cur_opr(%s) is alerting."
                          , edata.deviceno, opr_deviceno.c_str());
                //tell the other two agt than cust hangup, and change both's state to idle
                {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid
                                                   , ims_tool_t::num2str(evt.callid)
                                                   , ims_tool_t::chlname2no(other_agtname)
                                                   , CallStateT::SG_IdleState);

                    callevent.eventType =
                        (binsert
                         ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                         : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                        ) ;
                    callevent.partyNum = 2;
                    callevent.originatingParty = edata.deviceno;
                    callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                    callevent.otherAttr = PartyAttributeT::P_Internal;

                    TRACE_LOG("update %s to state:%s", other_agtid, callevent.state.get_desc().c_str());
                    session_mgr->update_channel_callstate(other_agtid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
                {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid),
                                                   ims_tool_t::chlname2no(opr_deviceno),
                                                   CallStateT::SG_IdleState);

                    callevent.eventType  =
                        (binsert
                         ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                         : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                        ) ;
                    callevent.partyNum = 2;
                    callevent.originatingParty = edata.deviceno;
                    callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
                    callevent.otherAttr = PartyAttributeT::P_Internal;

                    TRACE_LOG("update %s to state:%s", opr_channelid, callevent.state.get_desc().c_str());
                    session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
            } else {
                {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid
                                                   , ims_tool_t::num2str(evt.callid)
                                                   , ims_tool_t::chlname2no(other_agtname)
                                                   , CallStateT::SG_ConnectedState);

                    callevent.eventType =
                        (binsert
                         ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                         : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                        ) ;
                    callevent.partyNum = 2;
                    callevent.originatingParty = edata.deviceno;
                    callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                    callevent.otherAttr = PartyAttributeT::P_Internal;

                    TRACE_LOG("update %s to state:%s", other_agtid, callevent.state.get_desc().c_str());
                    session_mgr->update_channel_callstate(other_agtid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
                {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid),
                                                   ims_tool_t::chlname2no(opr_deviceno),
                                                   CallStateT::SG_ConnectedState);

                    callevent.eventType  =
                        (binsert
                         ? CallEventTypeT::SG_OtherPartyDisconnect_IntrudeCall
                         : CallEventTypeT::SG_OtherPartyDisconnect_MonitorCall
                        ) ;
                    callevent.partyNum = 2;
                    callevent.originatingParty = edata.deviceno;
                    callevent.otherDevice = ims_tool_t::chlname2no(other_agtname);
                    callevent.otherAttr = PartyAttributeT::P_Internal;

                    TRACE_LOG("update %s to state:%s", opr_channelid, callevent.state.get_desc().c_str());
                    session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }

                session_mgr->update_call_internal(evt.sessionid, evt.callid, true);
            }
        }

        std::list<const char*> chls;

        if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, chls)
                || chls.size() != 2) {
            WARNING_LOG("sid=%lu,callid=%lu,size=%ld locate otherchannel failed"
                        , evt.sessionid, evt.callid, chls.size());
            return;
        }

        fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

        if (!opr.valid()) {
            WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
            return;
        }

        ims::CallStateT state;

        if ((session_mgr->get_channel_callstate(chls.front(), state) &&
                (state == CallStateT::SG_HalfAlertingState || state == CallStateT::SG_IdleState
                 || state == CallStateT::SG_UnknownState))
                || (session_mgr->get_channel_callstate(chls.back(), state) &&
                    (state == CallStateT::SG_HalfAlertingState || state == CallStateT::SG_IdleState
                     || state == CallStateT::SG_UnknownState))) {
            TRACE_LOG("one of the left two channels' state is alerting or idle, hangup the left two.");
            session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, other_agtname.c_str());
            opr.opr().hangup(chls.front());
            opr.opr().hangup(chls.back());
        } else if (!binsert && opr_deviceno != edata.channel_name) {
            //be listened party hangup,all hangup
            session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, other_agtname.c_str());
            opr.opr().hangup(chls.front());
            opr.opr().hangup(chls.back());
        } else {
            opr.opr().unjoin_conference(NULL, chls.front());
            opr.opr().unjoin_conference(NULL, chls.back());

            if (IMS_SUCCESS != opr.opr().uuid_bridge(chls.front(), chls.back())) {
                std::string frontchname, backchname;
                session_mgr->get_channelnamebyid(evt.sessionid, chls.front(), frontchname);
                session_mgr->get_channelnamebyid(evt.sessionid, chls.back(), backchname);
                session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                                      session_mgr->rt_query_dn(frontchname.c_str(),
                                                              DnTypeT::AgentDn) ? frontchname.c_str() : backchname.c_str());
            }
        }

        //delete rundata<"conf_name", name_uuid>
        session_mgr->del_rundata(evt.sessionid, "conf_name");
    } else if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                              session_mgr->rt_query_dn(edata.channel_name,
                                                      DnTypeT::AgentDn) ? edata.channel_name : edata.other_channel_name);
    }
}

void event_handler_t::handle_conference_event(const fs_event_t& evt) {
    /*{{{*/
    debug_func("conference", evt);

    std::string opr_deviceno;
    session_mgr->get_session_operator(evt.sessionid, opr_deviceno);
    char opr_channelid[LEN_64] = {0};
    session_mgr->locate_channel(evt.sessionid, opr_deviceno.c_str(), opr_channelid, LEN_64);


    std::string last_channelname, last_deviceno;
    session_mgr->locate_lastchannel(evt.sessionid, last_channelname);
    last_deviceno = ims_tool_t::chlname2no(last_channelname);
    char last_channelid[LEN_64] = {0};
    session_mgr->locate_channel(evt.sessionid, last_channelname.c_str(), last_channelid, LEN_64);

    std::list<const char*> all_chls;
    std::string first_name;
    session_mgr->get_channelsbycall(evt.sessionid, evt.callid, all_chls);

    for (std::list<const char*>::iterator it = all_chls.begin(); it != all_chls.end(); ++it) {
        if (strcasecmp(*it, last_channelid) && strcasecmp(*it, opr_channelid)) {
            session_mgr->get_channelnamebyid(evt.sessionid, *it, first_name);
            break;
        }
    }

    bool islastinternal = session_mgr->rt_query_dn(last_channelname.c_str(), DnTypeT::AgentDn);

    if (strcasecmp(evt.name, "CONFERENCE_JOIN") == 0) {
        session_mgr->add_rundata(evt.sessionid, edata.uuid, edata.ims_data);

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_ConferenceState);

            callevent.partyNum = 3;

            if (opr_deviceno == edata.channel_name) {
                callevent.eventType  = CallEventTypeT::SG_ThisPartyConferenced_ConferenceCall;
                callevent.otherDevice = last_deviceno;
                callevent.otherAttr =
                    (islastinternal ? PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);
            } else {
                callevent.eventType = CallEventTypeT::SG_OtherPartyConferenced_ConferenceCall;
                callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                callevent.otherAttr = PartyAttributeT::P_Internal;
            }

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        if (opr_deviceno == edata.channel_name) {
            //opr hangup
            session_mgr->update_call_ani(evt.sessionid, evt.callid, ims_tool_t::chlname2no(first_name).c_str());
            {
                //push self
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_IdleState);
                callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnect_ConferenceCall;
                callevent.otherDevice = last_deviceno;
                callevent.partyNum = 2;
                callevent.otherAttr =
                    (islastinternal ? PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }

            if (islastinternal) { //push other
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               last_deviceno , CallStateT::SG_ConnectedState);

                callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnect_ConferenceCall;
                callevent.otherDevice = ims_tool_t::chlname2no(first_name);
                callevent.partyNum = 2;
                callevent.originatingParty = edata.deviceno;
                callevent.otherAttr = PartyAttributeT::P_Normal;

                session_mgr->update_channel_callstate(last_channelid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        } else if (last_deviceno == edata.deviceno) {
            //be consulted party hangup
            session_mgr->update_call_dnis(evt.sessionid, evt.callid,
                                          ims_tool_t::chlname2no(first_name).c_str());

            {
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               ims_tool_t::chlname2no(opr_deviceno), CallStateT::SG_ConnectedState);
                callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnect_ConferenceCall;
                callevent.otherDevice = ims_tool_t::chlname2no(first_name);
                callevent.partyNum = 2;
                callevent.otherAttr = PartyAttributeT::P_Normal;

                session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }

            if (islastinternal) {
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               edata.deviceno , CallStateT::SG_IdleState);

                callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnect_ConferenceCall;
                callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                callevent.partyNum = 2;
                callevent.originatingParty = edata.deviceno;
                callevent.otherAttr = PartyAttributeT::P_Internal;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        } else {
            //first party hangup
            {
                //push to opr
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               ims_tool_t::chlname2no(opr_deviceno) , CallStateT::SG_ConnectedState);
                callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnect_ConferenceCall;
                callevent.otherDevice = last_deviceno;
                callevent.partyNum = 2;
                callevent.originatingParty = edata.deviceno;
                callevent.otherAttr =
                    (islastinternal ? PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);

                session_mgr->update_channel_callstate(opr_channelid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }

            if (islastinternal) {
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               last_deviceno, CallStateT::SG_ConnectedState);
                callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnect_ConferenceCall;
                callevent.otherDevice = ims_tool_t::chlname2no(opr_deviceno);
                callevent.partyNum = 2;
                callevent.originatingParty = edata.deviceno;
                callevent.otherAttr = PartyAttributeT::P_Internal;

                session_mgr->update_call_internal(evt.sessionid, evt.callid, true);
                session_mgr->update_channel_callstate(last_channelid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        }

        std::list<const char*> chls;

        if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, chls)
                || chls.size() != 2) {
            WARNING_LOG("sid=%lu,callid=%lu,size=%ld locate otherchannel failed"
                        , evt.sessionid, evt.callid, chls.size());
            return;
        }

        fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

        if (!opr.valid()) {
            WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
            return;
        }

        opr.opr().unjoin_conference(NULL, chls.front());
        opr.opr().unjoin_conference(NULL, chls.back());
        std::string frontchname, backchname;
        bool isfrontAgent = false;
        int32_t ret = IMS_FAIL_GENERAL;
        session_mgr->get_channelnamebyid(evt.sessionid, chls.front(), frontchname);
        session_mgr->get_channelnamebyid(evt.sessionid, chls.back(), backchname);

        if (session_mgr->rt_query_dn(frontchname.c_str(), DnTypeT::AgentDn)) {
            isfrontAgent = true;
        }

        if (isfrontAgent) {
            ret = opr.opr().uuid_bridge(chls.front(), chls.back());
        } else {
            ret = opr.opr().uuid_bridge(chls.back(), chls.front());
        }

        if (IMS_SUCCESS != ret) {
            WARNING_LOG("sid=%lu, uuid_bridge error.", evt.sessionid);
            session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                                  isfrontAgent ? frontchname.c_str() : backchname.c_str());
        }

    } else if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL,
                                              session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn) ? edata.channel_name
                                              : (session_mgr->rt_query_dn(edata.other_channel_name,
                                                      DnTypeT::AgentDn) ? edata.other_channel_name : ""));
    }
}/*}}}*/

}






















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
