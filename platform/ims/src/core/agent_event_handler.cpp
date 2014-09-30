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
void event_handler_t::handle_inbound_agent(const fs_event_t& evt) {
    TRACE_LOG("[Inbound Call]recv %s,sessionid=%lu", evt.name, evt.sessionid);
    debug_func("inboundagent", evt);

    if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
        //monitored
        if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
                || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) {
            session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.other_deviceno);
            session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);

            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid
                                           , ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_AlertingState);

            callevent.eventType  = CallEventTypeT::SG_InboundCall_NormalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else if (strcasecmp(evt.name, "CHANNEL_ANSWER") == 0) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_ConnectedState);

            callevent.eventType  = CallEventTypeT::SG_ThisPartyAnswered_NormalCall;
            callevent.partyNum = 2;
            callevent.otherDevice = edata.other_deviceno;
            callevent.otherAttr = PartyAttributeT::P_Normal;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_IdleState);

            callevent.eventType  = CallEventTypeT::SG_ThisPartyDisconnected_NormalCall;
            callevent.partyNum = 0;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
                return;
            }

            opr.opr().hangup(edata.other_uuid);
        }
    } else {
        //customer msg
        if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) {
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp, evt.sessionid,
                                           ims_tool_t::num2str(evt.callid),
                                           edata.other_deviceno, CallStateT::SG_IdleState);
            callevent.eventType = CallEventTypeT::SG_OtherPartyDisconnected_NormalCall;
            callevent.partyNum = 0;
            callevent.originatingParty = edata.deviceno;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);

            fs_tool_t opr(ims_tool_t::get_fsno(evt.sessionid));

            if (!opr.valid()) {
                WARNING_LOG("sid=%lu,get fs error", evt.sessionid);
                return;
            }

            opr.opr().hangup(edata.other_uuid);

        }
    }
}
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
