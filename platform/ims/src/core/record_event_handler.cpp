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
void event_handler_t::handle_record_event(const fs_event_t& evt) {
    const event_data_normal_t& edata = evt.event_data.normal;
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();
    callid_t callid = 0;

    if (!session_mgr->locate_call(edata.uuid, callid)) {
        WARNING_LOG("handle_record_event failed(locate_call failed), sessionid=%lu,chid:%s",  evt.sessionid,
                    edata.uuid);
        return;
    }

    bool start_event = (strcasecmp(evt.name, "RECORD_START") == 0);

    if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)) {
        {
            MediaEventT event;
            event.timestamp = evt.timestamp;
            event.sessionid = evt.sessionid;
            event.callid = ims_tool_t::num2str(callid);
            event.device = edata.deviceno;
            event.eventType = (start_event ?
                               MediaEventTypeT::MG_TP_Record_Started :
                               MediaEventTypeT::MG_TP_Record_Done);
            event.state = (start_event ?
                           MediaStateT::MG_RecordingState :
                           MediaStateT::MG_IdleState);
            event.reason = (start_event ?
                            MediaEventReasonT::ReasonMediaUnknown :
                            MediaEventReasonT::ReasonMediaEnd);
            event.otherDevice = edata.other_deviceno;
            event.mediaBuffer = (start_event ?
                                 edata.ims_data :
                                 "");

            session_mgr->update_channel_mediastate(edata.uuid, event.state);
            session_mgr->add_imsevent_media(evt.sessionid, event);
        }

        if (session_mgr->rt_query_dn(edata.other_channel_name, DnTypeT::AgentDn)) {
            MediaEventT event;
            event.timestamp = evt.timestamp;
            event.sessionid = evt.sessionid;
            event.callid = ims_tool_t::num2str(callid);
            event.device = edata.other_deviceno;
            event.eventType = (start_event ?
                               MediaEventTypeT::MG_OP_Record_Started :
                               MediaEventTypeT::MG_OP_Record_Done);
            session_mgr->get_channel_mediastate(edata.other_uuid, event.state);
            event.reason = (start_event ?
                            MediaEventReasonT::ReasonMediaUnknown :
                            MediaEventReasonT::ReasonMediaEnd);
            event.otherDevice = edata.deviceno;
            event.mediaBuffer = "";

            session_mgr->add_imsevent_media(evt.sessionid, event);
        }
    } else {
        session_mgr->update_channel_mediastate(edata.uuid,
                                               MediaStateT::MG_RecordingState);

        if (session_mgr->rt_query_dn(edata.other_channel_name, DnTypeT::AgentDn)) {
            MediaEventT event;
            event.timestamp = evt.timestamp;
            event.sessionid = evt.sessionid;
            event.callid = ims_tool_t::num2str(callid);
            event.device = edata.other_deviceno;
            event.eventType = (start_event ?
                               MediaEventTypeT::MG_OP_Record_Started :
                               MediaEventTypeT::MG_OP_Record_Done);
            session_mgr->get_channel_mediastate(edata.other_uuid, event.state);
            event.reason = (start_event ?
                            MediaEventReasonT::ReasonMediaUnknown :
                            MediaEventReasonT::ReasonMediaEnd);
            event.otherDevice = edata.deviceno;
            event.mediaBuffer = "";

            session_mgr->add_imsevent_media(evt.sessionid, event);
        }
    }
}
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
