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

void event_handler_t::handle_singlesteptransfer_event(const fs_event_t& evt) {
    debug_func("stringlesteptransfer", evt);

    if (strcasecmp(evt.name, "CHANNEL_PROGRESS") == 0
            || strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") == 0) {
        //be transferd party ringring

        session_mgr->update_session_operation(evt.sessionid, SOPR_MAKECALL, edata.channel_name);
        session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.other_deviceno);
        session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);

        if (!session_mgr->rt_query_dn(edata.channel_name , DnTypeT::AgentDn)) { //transfer out
            return;
        }

        //transfer agent,agent ring
        CallEventT callevent;
        ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                       evt.sessionid, ims_tool_t::num2str(evt.callid),
                                       edata.deviceno, CallStateT::SG_AlertingState);

        callevent.eventType = CallEventTypeT::SG_InboundCall_NormalCall;
        callevent.partyNum = 2;
        callevent.otherAttr = PartyAttributeT::P_Normal;
        callevent.otherDevice = edata.other_deviceno;

        session_mgr->update_create_reason(evt.sessionid, SCRT_INBOUND_NORMAL);
        session_mgr->update_channel_callstate(edata.uuid, callevent.state);
        session_mgr->add_imsevent_call(evt.sessionid, callevent);
    } else if (strcasecmp(evt.name, "CHANNEL_HANGUP") == 0) { //anyone may hangup
        std::string opr;
        session_mgr->get_session_operator(evt.sessionid, opr);

        if (opr == edata.channel_name) {
            //start transfer party hangup
            CallEventT callevent;
            ims_tool_t::prepare_call_event(callevent, evt.timestamp,
                                           evt.sessionid, ims_tool_t::num2str(evt.callid),
                                           edata.deviceno, CallStateT::SG_IdleState);

            callevent.eventType = CallEventTypeT::SG_ThisPartyTransferred_NormalCall;
            callevent.partyNum = 0;

            session_mgr->update_channel_callstate(edata.uuid, callevent.state);
            session_mgr->add_imsevent_call(evt.sessionid, callevent);
        }
    }
}

}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
