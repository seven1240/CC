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

event_handler_t::event_handler_t(int32_t timeout) :
    _timeout(timeout),
    _shutdown(true),
    _stopping(false) {
}

int32_t event_handler_t::operator()(const bool* isstoped, void* param) {
    _shutdown = false;
    fs_event_t evt;
    //while(!_shutdown){
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

    while (session_mgr->isrunning()) {
        memset(&evt, 0 , sizeof(evt));

        if (!_q.get(evt, _timeout)) {
            //it's timeout
            if (_stopping) {
                _shutdown = true;
            }

            continue;
        }

        if (strcasecmp(evt.name, "RECORD_START") == 0
                || strcasecmp(evt.name, "RECORD_STOP") == 0) {
            handle_record_event(evt);
        } else if (strcasecmp(evt.name, "CHANNEL_DESTROY") == 0) {
            const event_data_normal_t& edata = evt.event_data.normal;
            session_mgr->remove_channelfromcall(evt.sessionid, evt.callid, edata.uuid);
            session_mgr->destroy_channel(edata.uuid);
        } else {
            do_real_handle_event(evt);
        }
    }


    _shutdown = true;
    return 0;
}

void event_handler_t::do_real_handle_event(const fs_event_t& evt) {
    /*{{{*/

    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();
    ims_session_operation_t operation;

    if (!session_mgr->get_session_operation(evt.sessionid, operation)) {
        WARNING_LOG("get_session_operation failed [%ld]", evt.sessionid);
        return;
    }

    switch (operation) {
    case SOPR_MAKECALL:
        handle_makecall_event(evt);
        break;

    case SOPR_HOLD:
        handle_hold_event(evt);
        break;

    case SOPR_RETRIEVE:
        handle_retrieve_event(evt);
        break;

    case SOPR_CONSULT:
        handle_consult_event(evt);
        break;

    case SOPR_RECONNECT:
        handle_reconnect_event(evt);
        break;

    case SOPR_TRANSFER:
        handle_transfer_event(evt);
        break;

    case SOPR_CONFERENCE:
        handle_conference_event(evt);
        break;

    case SOPR_SINGLESTEPTRANSFER:
        handle_singlesteptransfer_event(evt);
        break;

    case SOPR_LISTEN:
        handle_singlestepconference_event(evt, false);
        break;

    case SOPR_INSERT:
        handle_singlestepconference_event(evt);
        break;

    case SOPR_IVRTRANSFER:
        handle_ivrtransfer_event(evt);
        break;

    default:
        if (session_mgr->is_inbound_session(evt.sessionid)) {
            handle_inbound_agent(evt);
            return;
        }

        WARNING_LOG("unknown operation:%d", operation);
        break;
    }
}/*}}}*/

void event_handler_t::handle_hangup(const ims_session_operation_t operation,
                                    const fs_event_t& evt) {

    const event_data_normal_t& edata = evt.event_data.normal;
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

    switch (operation) {
    case SOPR_CONSULT:
    case SOPR_RECONNECT: {
        std::list<const char*> chls;
        session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, chls);

        if (chls.size() == 0) {
            //first side hangup

            {
                callid_t ocallid = 0;

                if (!session_mgr->locate_othercall(evt.sessionid, evt.callid, ocallid)
                        || session_mgr->is_dead_call(evt.sessionid, ocallid)) {
                    //consult party hangup,cause be consulted party hangup auto
                    //manually hangup customer,push event to
                    TRACE_LOG("have no calls");
                    return;
                }

                TRACE_LOG("already have??");
            }

            std::string last_name;

            if (!session_mgr->locate_lastchannel(evt.sessionid, last_name)) {
                WARNING_LOG("sid=%ld locat last channel failed", evt.sessionid);
                return;
            }

            std::list<callid_t> other_calls;
            char last_id[LEN_64] = {0};

            if (!session_mgr->locate_callbyname(evt.sessionid, last_name.c_str(), other_calls,
                                                last_id, LEN_64) || other_calls.size() < 1) {
                WARNING_LOG("sid=%lu,name=%s locate call failed", evt.sessionid, last_name.c_str());
                return;
            }

            callid_t other_callid = other_calls.front();
            std::list<const char*> other_otherids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, other_callid, last_id, other_otherids)
                    || other_otherids.size() < 1) {
                WARNING_LOG("sid=%lu,othercallid=%lu,last_id=%s locate other channel failed",
                            evt.sessionid, other_callid, last_id);
                return;
            }

            const char* consult_partyid = other_otherids.front();
            std::string consult_partyname;

            if (!session_mgr->get_channelnamebyid(evt.sessionid, consult_partyid, consult_partyname)) {
                WARNING_LOG("sid=%lu,consultparyid=%s get partyname failed",
                            evt.sessionid, consult_partyid);
                return;
            }

            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           ims_tool_t::chlname2no(consult_partyname),
                                           CallStateT::SG_ConnectedState);
            session_mgr->get_channel_callstate(consult_partyid, callevent.state);

            callevent.eventType  = CallEventTypeT::SG_OtherPartyDisconnected_ConsultCall;
            callevent.partyNum = 2;
            callevent.originatingParty = edata.deviceno;
            callevent.otherDevice = ims_tool_t::chlname2no(last_name);

            if (session_mgr->rt_query_dn(last_name.c_str(), DnTypeT::AgentDn)) { //consult internal
                session_mgr->update_call_internal(evt.sessionid, other_callid, true);
                callevent.otherAttr = ims::PartyAttributeT::P_Internal;
            } else {
                callevent.otherAttr = ims::PartyAttributeT::P_Normal;
            }

            session_mgr->update_channel_callstate(edata.other_uuid, CallStateT::SG_IdleState);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
            session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL);
        } else {
            std::string cur_opr;
            session_mgr->get_session_operator(evt.sessionid, cur_opr);

            if (strcasecmp(cur_opr.c_str(), edata.channel_name) == 0) {
                //consut party hangup,equal transfer(but after bridge party hangup,be
                //consult party also hangup ,so ,hangup all )
                callid_t other_callid = 0;

                if (!session_mgr->locate_othercall(evt.sessionid, evt.callid, other_callid)) {
                    WARNING_LOG("sid=%lu,srccall=%lu can't locate other call", evt.sessionid, evt.callid);
                    return;
                }

                std::list<const char*> chls;

                if (!session_mgr->get_channelsbycall(evt.sessionid, other_callid, chls)
                        || chls.size() < 1) {

                    WARNING_LOG("sid=%lu,callid=%lu can't locate channels", evt.sessionid, other_callid);
                    return;
                }

                {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);

                    callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_ConsultCall;
                    callevent.partyNum = 0;

                    //session_mgr->remove_channelfromcall(evt.sessionid,evt.callid,edata.uuid);
                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }


                {
                    //push to be consult party
                    std::list<const char*> other_ids;
                    session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids);

                    if (other_ids.size()) {
                        std::string name;
                        session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);

                        if (session_mgr->rt_query_dn(name.c_str(), DnTypeT::AgentDn)) {
                            CallEventT callevent;
                            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                           ims_tool_t::num2str(evt.callid), ims_tool_t::chlname2no(name), CallStateT::SG_IdleState);

                            callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnected_InternalCall;
                            callevent.partyNum = 0;
                            callevent.originatingParty = edata.deviceno;

                            session_mgr->add_imsevent_call(evt.sessionid, callevent);
                        }
                    }
                }

                if (SOPR_CONSULT == operation) {
                    //moni customer manually hangup event
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(other_callid), edata.deviceno, CallStateT::SG_IdleState);
                    callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
                    callevent.partyNum = 0;
                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);

                    session_mgr->find_other_hangup(evt.sessionid, other_callid, "");
                }


                //only update callid,not update operation, in order to deal hangup
                //freeswith's hangup event
                //notice: party who is consult operator hangup sip phone,be consulted party will
                //be hanguped auto.
                if (SOPR_RECONNECT == operation) {
                    session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL);
                }

                return ;
            } else {
                //be consulted party hangup,equal reconnect
                std::string consult_partyname;
                bool internal_consult = (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn));
                session_mgr->get_session_operator(evt.sessionid, consult_partyname);
                {
                    ims::CallStateT state;
                    session_mgr->get_channel_callstate(edata.other_uuid, state);

                    if (consult_partyname == edata.other_channel_name
                            && SOPR_CONSULT == operation
                            && (state == ims::CallStateT::SG_IdleState || state == ims::CallStateT::SG_UnknownState)) {
                        //because consult party hangup sip phone,be consulted party auto
                        //be hanguped by freeswith
                        session_mgr->update_channel_callstate(edata.uuid, CallStateT::SG_IdleState);

                        if (internal_consult) {
                            CallEventT callevent;
                            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                           ims_tool_t::num2str(evt.callid),
                                                           edata.deviceno , CallStateT::SG_IdleState);
                            callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_InternalCall;

                            callevent.partyNum = 0;
                            session_mgr->update_channel_callstate(edata.uuid , callevent.state);
                            session_mgr->add_imsevent_call(evt.sessionid, callevent);
                        }

                        return;
                    } else { //be consulted party hangup sip phone manually
                        //push to consult party
                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                       ims_tool_t::num2str(evt.callid),
                                                       ims_tool_t::chlname2no(consult_partyname), CallStateT::SG_SuspendedState);
                        callevent.eventType = (SOPR_CONSULT == operation
                                               ? CallEventTypeT::SG_OtherPartyDisconnected_ConsultCall
                                               : CallEventTypeT::SG_ThisPartyDisconnected_ConsultCall
                                              );
                        callevent.partyNum = 0;
                        callevent.originatingParty = (SOPR_CONSULT == operation
                                                      ? edata.deviceno
                                                      : ims_tool_t::chlname2no(consult_partyname)
                                                     );
                        session_mgr->update_channel_callstate(chls.front(), callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    }
                }

                if (internal_consult) {
                    //push to be consulted party
                    {
                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                       ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);
                        callevent.eventType = (SOPR_CONSULT == operation
                                               ? CallEventTypeT::SG_ThisPartyDisconnected_InternalCall
                                               : CallEventTypeT::SG_OtherPartyDisconnected_InternalCall
                                              );
                        callevent.partyNum = 0;
                        callevent.originatingParty = (SOPR_CONSULT == operation
                                                      ? edata.deviceno
                                                      : ims_tool_t::chlname2no(consult_partyname)
                                                     );

                        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    }
                    {
                        //moni tp¡¢op hangup event
                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                       ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);
                        callevent.eventType = (SOPR_CONSULT == operation
                                               ? CallEventTypeT::SG_OtherPartyDisconnected_InternalCall
                                               : CallEventTypeT::SG_ThisPartyDisconnected_InternalCall
                                              );
                        callevent.partyNum = 0;
                        callevent.originatingParty = (SOPR_CONSULT == operation
                                                      ? ims_tool_t::chlname2no(consult_partyname)
                                                      : edata.deviceno
                                                     );

                        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    }
                }

                callid_t other_callid = 0;

                if (!session_mgr->locate_othercall(evt.sessionid, evt.callid, other_callid)) {
                    WARNING_LOG("sid=%lu,srccall=%lu can't locate other call", evt.sessionid, evt.callid);
                    return;
                }

                session_mgr->remove_channelfromcall(evt.sessionid, evt.callid, chls.front());
                session_mgr->update_channel_call(chls.front(), other_callid);
                TRACE_LOG("sid=%lu update channel %s to suspend call %lu",
                          evt.sessionid, consult_partyname.c_str(), other_callid);

                session_mgr->update_session_operation(evt.sessionid, SOPR_RECONNECT);
            }

            //other channels in session uuid_bridge
            std::list<const char*> chls2;

            if (!session_mgr->get_channelsbysession(evt.sessionid, chls2) || chls2.size() < 3) {
                WARNING_LOG("sid=%lu get chanels faild", evt.sessionid);
                return ;
            }

            const char* first_leg = chls.front(); //È«¾ÖµÄchls
            const char* second_leg = NULL;

            for (std::list<const char*>::iterator it = chls2.begin(); it != chls2.end(); ++it) {
                if (!strcasecmp(*it, edata.uuid) || !strcasecmp(*it, first_leg)) {
                    continue;
                }

                second_leg = *it;
                break;
            }

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                WARNING_LOG("process consult event faile,get fs_opr");
                return;
            }

            opr.opr().stop_media(second_leg);
            opr.opr().uuid_bridge(first_leg, second_leg);
        }
    }
    break;

    default:
        break;
    }
}

void event_handler_t::handle_transfer_event(const fs_event_t& evt) {

    debug_func("transfer", evt);

    if (strcasecmp(evt.name, "CHANNEL_UNBRIDGE") == 0) { //party who start transfer will receive
        std::string transfer_self;

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)
                && session_mgr->get_session_operator(evt.sessionid, transfer_self)
                && transfer_self == edata.channel_name) {

            callid_t other_callid = 0;

            if (!session_mgr->locate_othercall(evt.sessionid, evt.callid, other_callid)) {
                WARNING_LOG("sid=%lu,srccall=%lu can't locate other call"
                            , evt.sessionid, evt.callid);
                return;
            }

            std::list<const char*> chls;

            if (!session_mgr->get_channelsbycall(evt.sessionid, other_callid, chls)
                    || chls.size() < 1) {

                WARNING_LOG("sid=%lu,callid=%lu can't locate channels"
                            , evt.sessionid, other_callid);
                return;
            }

            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           /*ims_tool_t::num2str(evt.callid)*/
                                           ims_tool_t::num2str(other_callid), edata.deviceno, CallStateT::SG_IdleState);
            callevent.eventType = CallEventTypeT::SG_ThisPartyTransferred_ConsultCall;
            callevent.partyNum = 0;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);

            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)
                    || other_ids.size() < 1) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
                return;
            }

            opr.opr().stop_media(chls.front());
            opr.opr().uuid_bridge(other_ids.front(), chls.front());

            session_mgr->remove_channelfromcall(evt.sessionid, other_callid, chls.front());
            session_mgr->update_channel_call(chls.front(), evt.callid);
            TRACE_LOG("sid=%lu update suspend channel %s to active call %lu",
                      evt.sessionid , chls.front(), evt.callid);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_ConnectedState);

            callevent.eventType = CallEventTypeT::SG_OtherPartyTransferred_ConsultCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;
            session_mgr->get_session_operator(evt.sessionid, callevent.originatingParty);
            callevent.originatingParty = ims_tool_t::chlname2no(callevent.originatingParty);

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, edata.channel_name);
        session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.other_deviceno);
    }
}
void event_handler_t::handle_reconnect_event(const fs_event_t& evt) {

    debug_func("reconnect", evt);

    if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        CallEventT callevent;
        ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                       ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_ConnectedState);

        callevent.eventType = CallEventTypeT::SG_ThisPartyRetrieved_NormalCall;
        callevent.partyNum = 2;
        callevent.otherDevice = edata.other_deviceno;
        callevent.otherAttr = PartyAttributeT::P_Normal;

        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, edata.channel_name);

        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        handle_hangup(SOPR_RECONNECT, evt);
    }
}
void event_handler_t::handle_hold_event(const fs_event_t& evt) {
    /*{{{*/
    debug_func("hold", evt);

    if (strcasecmp(evt.name, "CHANNEL_UNBRIDGE") == 0) {
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) { //callout
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_SuspendedState);

            callevent.eventType  = CallEventTypeT::SG_ThisPartySuspended_NormalCall;
            callevent.partyNum = 2;

            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            std::string name;
            session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);
            callevent.otherDevice = ims_tool_t::chlname2no(name);
            callevent.otherAttr = PartyAttributeT::P_Normal;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else { //callin
            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids) ||
                    other_ids.size() < 1) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            std::string name;
            session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);

            if (session_mgr->rt_query_dn(name.c_str(), DnTypeT::AgentDn)
                    && session_mgr->is_inbound_session(evt.sessionid)) {

                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid), ims_tool_t::chlname2no(name), CallStateT::SG_SuspendedState);

                callevent.eventType  = CallEventTypeT::SG_ThisPartySuspended_NormalCall;
                callevent.partyNum = 2;
                callevent.otherDevice = edata.deviceno;
                callevent.otherAttr = PartyAttributeT::P_Normal;

                session_mgr->update_channel_callstate(other_ids.front(), callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        }
    } else if (strcasecmp(evt.name, "CHANNEL_EXECUTE_COMPLETE") == 0) {
        if (strcasecmp(edata.application, "playback") == 0
                && (strncasecmp(edata.application_resp, "FILE PLAYED", 11) == 0
                    || strncasecmp(edata.application_resp, "PLAYBACK ERROR", 14) == 0
                   )) {

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                return;
            }

            opr.opr().play(edata.uuid, DEFAULT_HOLDON_MUSIC);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        //hold hangup,other is null
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);

            callevent.eventType  = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
            callevent.partyNum = 0;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else {
            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            for (std::list<const char*>::iterator it = other_ids.begin();
                    it != other_ids.end(); ++it) {
                std::string name = "";

                if (session_mgr->get_channelnamebyid(evt.sessionid, *it, name)) {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid), ims_tool_t::chlname2no(name),
                                                   CallStateT::SG_IdleState);
                    callevent.device = ims_tool_t::chlname2no(name);
                    callevent.eventType  = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
                    callevent.partyNum = 0;
                    callevent.originatingParty = edata.deviceno;

                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
            }
        }

        session_mgr->find_other_hangup(evt.sessionid, evt.callid, edata.uuid);
    }

}/*}}}*/
void event_handler_t::handle_retrieve_event(const fs_event_t& evt) {
    /*{{{*/
    debug_func("retrieve", evt);

    if (strcasecmp(evt.name, "CHANNEL_BRIDGE") == 0) {
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_ConnectedState);
            callevent.eventType  = CallEventTypeT::SG_ThisPartyRetrieved_NormalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;

            session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, edata.channel_name);
            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_IdleState);
            callevent.eventType  = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
            callevent.partyNum = 0;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else {
            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)
                    || other_ids.size() < 1) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            std::string name = "";
            session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), ims_tool_t::chlname2no(name), CallStateT::SG_IdleState);
            callevent.eventType  = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
            callevent.partyNum = 0;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(other_ids.front(), callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        session_mgr->find_other_hangup(evt.sessionid, evt.callid, edata.uuid);
    }
}/*}}}*/
void event_handler_t::handle_consult_event(const fs_event_t& evt) {
    /*{{{*/
    debug_func("consult", evt);

    if (strcasecmp(evt.name, "CHANNEL_UNBRIDGE") == 0) {
        std::string consult_opr;

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)
                && session_mgr->get_session_operator(evt.sessionid, consult_opr)
                && consult_opr == edata.channel_name) {
            ims::CallStateT state;
            session_mgr->get_channel_callstate(edata.uuid, state);

            if (state == CallStateT::SG_IdleState || state == CallStateT::SG_UnknownState) {
                return;
            }

            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_SuspendedState);
            callevent.eventType  = CallEventTypeT::SG_ThisPartySuspended_NormalCall;
            callevent.partyNum = 2;

            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)) {
                WARNING_LOG("[sid=%ld] locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            std::string name;
            session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);
            callevent.otherDevice = ims_tool_t::chlname2no(name);

            callevent.otherAttr =
                (session_mgr->rt_query_dn(name.c_str(), DnTypeT::AgentDn) ?
                 PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else {
            std::list<const char*> other_ids;

            if (!session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids) ||
                    other_ids.size() < 1) {
                WARNING_LOG("sid=%ld locate_otherchannel failed, chid:[%s]",
                            evt.sessionid, edata.uuid);
                return;
            }

            std::string name;
            session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), name);

            if (session_mgr->rt_query_dn(name.c_str(), DnTypeT::AgentDn)
                    && session_mgr->is_inbound_session(evt.sessionid)
                    && session_mgr->get_session_operator(evt.sessionid, consult_opr)
                    && consult_opr == name) {
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               ims_tool_t::chlname2no(name), CallStateT::SG_SuspendedState);

                callevent.eventType  = CallEventTypeT::SG_ThisPartySuspended_NormalCall;
                callevent.partyNum = 2;
                callevent.otherDevice = edata.deviceno;
                callevent.otherAttr = PartyAttributeT::P_Normal;

                session_mgr->update_channel_callstate(other_ids.front(), callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            } else {
                WARNING_LOG("sid=%ld not operator %s unbridged",
                            evt.sessionid, ims_tool_t::chlname2no(name).c_str());
            }
        }
    } else if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
               || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) {
        bool internal_consult = false;

        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            TRACE_LOG("sid=%ld is internal consult ", evt.sessionid);
            internal_consult = true;
        }


        {
            //consult party
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.other_deviceno, CallStateT::SG_ConnectingState);
            callevent.eventType  = CallEventTypeT::SG_DestSeized_ConsultCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.deviceno;
            callevent.originatingParty = edata.deviceno;
            callevent.otherAttr = (internal_consult ? PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);

            session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        if (internal_consult) {
            //be consultd party
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_AlertingState);
            callevent.eventType  = CallEventTypeT::SG_InboundCall_InternalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_ANSWER") == 0) {
        bool internal_consult = session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn);
        {
            //consult party
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.other_deviceno, CallStateT::SG_ConnectedState);
            callevent.eventType = CallEventTypeT::SG_OtherPartyAnswered_ConsultCall;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = (internal_consult ? PartyAttributeT::P_Internal : PartyAttributeT::P_Normal);
            callevent.originatingParty = edata.deviceno;
            callevent.partyNum = 2;

            session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        if (internal_consult) {
            //be consulted party
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid), edata.deviceno, CallStateT::SG_ConnectedState);
            callevent.eventType  = CallEventTypeT::SG_ThisPartyAnswered_InternalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Internal;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        handle_hangup(SOPR_CONSULT, evt);
    } else if (strcasecmp(evt.name, "CHANNEL_EXECUTE_COMPLETE") == 0) {
        if (strcasecmp(edata.application, "playback") == 0
                && strncasecmp(edata.application_resp, "FILE PLAYED", 11) == 0) {

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                return;
            }

            opr.opr().play(edata.uuid, DEFAULT_HOLDON_MUSIC);
        }
    }
}/*}}}*/


void event_handler_t::handle_makecall_event(const fs_event_t& evt) {
    /*{{{*/
    debug_func("makecall", evt);

    if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
            || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) {
        /*{{{*/
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            if ('\0' == edata.other_uuid[0]) { //first agent alerting
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                               ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_HalfAlertingState);

                callevent.eventType  = CallEventTypeT::SG_InboundCall_InternalCall;

                session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.deviceno);
                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            } else { //second agent alerting
                session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);
                {
                    //push to first agent
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid),
                                                   edata.other_deviceno, CallStateT::SG_ConnectingState);

                    callevent.eventType  = CallEventTypeT::SG_DestSeized_InternalCall;
                    callevent.partyNum = 2;
                    callevent.otherDevice = edata.deviceno;
                    callevent.otherAttr = PartyAttributeT::P_Internal;
                    callevent.originatingParty = edata.deviceno;

                    session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
                {
                    //push to second agent
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                                   ims_tool_t::num2str(evt.callid),
                                                   edata.deviceno, CallStateT::SG_AlertingState);

                    callevent.eventType = CallEventTypeT::SG_InboundCall_InternalCall;
                    callevent.partyNum = 2;
                    callevent.otherDevice = edata.other_deviceno;
                    callevent.otherAttr = PartyAttributeT::P_Internal;
                    callevent.originatingParty = edata.deviceno;

                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
            }
        } else {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.other_deviceno, CallStateT::SG_ConnectingState);

            callevent.eventType  = CallEventTypeT::SG_DestSeized_NormalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);
            session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }

        // add after callcloud 3.0 by david
        session_mgr->rt_del_session_route(evt.sessionid);
    }/*}}}*/
    else if (strcasecmp(evt.name, "CHANNEL_ANSWER") == 0) {
        /*{{{*/
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            if ('\0' == edata.other_uuid[0]) { //makecall first agent answerd
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                               evt.sessionid, ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_HalfConnectedState);

                callevent.eventType  = CallEventTypeT::SG_ThisPartyAnswered_InternalCall;

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            } else { //second agent answerd
                if (session_mgr->rt_query_dn(edata.other_channel_name, DnTypeT::AgentDn)) {
                    //singletrans internal
                    {
                        //push to frist agent
                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                                       edata.other_deviceno, CallStateT::SG_ConnectedState);

                        callevent.eventType  = CallEventTypeT::SG_OtherPartyAnswered_InternalCall;
                        callevent.partyNum = 2;
                        callevent.otherDevice = edata.deviceno;
                        callevent.otherAttr = PartyAttributeT::P_Internal;
                        callevent.originatingParty = edata.deviceno;

                        session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    }
                    {
                        //push to second agent
                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                                       edata.deviceno, CallStateT::SG_ConnectedState);

                        callevent.eventType = CallEventTypeT::SG_ThisPartyAnswered_InternalCall;
                        callevent.partyNum = 2;
                        callevent.otherDevice = edata.other_deviceno;
                        callevent.otherAttr = PartyAttributeT::P_Internal;
                        callevent.originatingParty = edata.deviceno;

                        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    }
                } else {
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                                   evt.sessionid, ims_tool_t::num2str(evt.callid),
                                                   edata.deviceno, CallStateT::SG_ConnectedState);

                    callevent.eventType = CallEventTypeT::SG_ThisPartyAnswered_NormalCall;
                    callevent.partyNum = 2;
                    callevent.otherDevice = edata.other_deviceno;
                    callevent.otherAttr = PartyAttributeT::P_Normal;
                    callevent.originatingParty = edata.deviceno;

                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
            }
        } else if (session_mgr->rt_query_dn(edata.other_channel_name , DnTypeT::AgentDn)) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           edata.other_deviceno, CallStateT::SG_ConnectedState);

            callevent.eventType  = CallEventTypeT::SG_OtherPartyAnswered_NormalCall;
            callevent.partyNum = 2;

            callevent.otherDevice = edata.deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    }/*}}}*/
    else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
        if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
            if (session_mgr->is_internal_call(evt.sessionid, evt.callid)) {
                //ob internal
                {
                    //push to self
                    CallEventT callevent;
                    ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                                   evt.sessionid, ims_tool_t::num2str(evt.callid),
                                                   edata.deviceno, CallStateT::SG_IdleState);

                    callevent.partyNum = 0;
                    callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_InternalCall;

                    session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                    session_mgr->add_imsevent_call(evt.sessionid, callevent);
                }
                {
                    //push to other
                    std::list<const char*> other_ids;
                    std::string other_name;

                    if (session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)
                            && other_ids.size() > 0
                            && session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), other_name)) {

                        CallEventT callevent;
                        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                                       ims_tool_t::chlname2no(other_name) , CallStateT::SG_IdleState);

                        callevent.partyNum = 0;
                        callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnected_InternalCall;
                        callevent.originatingParty = edata.deviceno;

                        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                        session_mgr->add_imsevent_call(evt.sessionid, callevent);
                    } else {
                        WARNING_LOG("hangup locate other object fail");
                    }
                }
            } else {
                //ob external,agent hangup
                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                               evt.sessionid, ims_tool_t::num2str(evt.callid),
                                               edata.deviceno, CallStateT::SG_IdleState);
                callevent.partyNum = 0;
                ims::CallStateT state;
                session_mgr->get_channel_callstate(edata.uuid, state);

                if (state == ims::CallStateT::SG_HalfAlertingState) {
                    //self phone ring hangup
                    callevent.eventType = CallEventTypeT::SG_ThisPartyDisconnected_InternalCall;
                } else {
                    callevent.eventType  = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
                }

                session_mgr->update_channel_callstate(edata.uuid, callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        } else if (session_mgr->rt_query_dn(edata.other_channel_name,
                                            DnTypeT::AgentDn)) { //ob external,customer hangup
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           edata.other_deviceno, CallStateT::SG_IdleState);

            callevent.eventType  = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
            callevent.partyNum = 0;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(edata.other_uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else {
            std::list<const char*> other_ids;
            std::string other_name;

            if (session_mgr->locate_otherchannel(evt.sessionid, evt.callid, edata.uuid, other_ids)
                    && other_ids.size() > 0
                    && session_mgr->get_channelnamebyid(evt.sessionid, other_ids.front(), other_name)) {

                CallEventT callevent;
                ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                               evt.sessionid, ims_tool_t::num2str(evt.callid),
                                               ims_tool_t::chlname2no(other_name) , CallStateT::SG_IdleState);

                callevent.partyNum = 0;
                callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
                callevent.originatingParty = edata.deviceno;

                session_mgr->update_channel_callstate(other_ids.front(), callevent.state);
                session_mgr->add_imsevent_call(evt.sessionid, callevent);
            }
        }

        session_mgr->find_other_hangup(evt.sessionid, evt.callid, edata.uuid);
    } else if (strcasecmp(evt.name, "OPERATION_FAILED") == 0) {
        OtherEventT otherevent;
        otherevent.sessionid = evt.sessionid;
        otherevent.callid = "";
        //session_mgr->get_session_operator(evt.sessionid,otherevent.device);
        otherevent.device = ims_tool_t::chlname2no(edata.channel_name);
        otherevent.eventType = OtherEventTypeT::OG_OperationFailed;
        otherevent.timestamp = evt.timestamp;
        otherevent.data.insert(std::pair<std::string, std::string>("REASON", edata.reason));

        if (strcasecmp(edata.reason, "DESTINATION_OUT_OF_ORDER") == 0
                || strcasecmp(edata.reason, "USER_NOT_REGISTERED") == 0
                || strcasecmp(edata.reason, "SUBSCRIBER_ABSENT") == 0
                || strcasecmp(edata.reason, "INVALID_NUMBER_FORMAT") == 0
                || strcasecmp(edata.reason, "NETWORK_OUT_OF_ORDER") == 0) { //no channel_* event

            // push CancelRouteRequest event to ACD
            // add after callcloud 3.0 by david
            ims_tool_t::push_cancel_route_event(evt.sessionid);
            session_mgr->remove_session(evt.sessionid);
        } else {
            TRACE_LOG("sid=%lu,REASON NO EQUAL,%s != %s",
                      evt.sessionid, edata.reason, "DESTINATION_OUT_OF_ORDER");
        }

        session_mgr->add_imsevent_other(evt.sessionid, otherevent);
    }
}/*}}}*/

}/*}}}*/












/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
