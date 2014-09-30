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

#include "event_receiver.h"
#include "ims_core.h"
#include "fs_mgr.h"
#include "ims_log.h"
#include "common.h"
#include "threadpool.h"
#include "ims_core_session_mgr.h"

namespace ims {


int32_t heartbeat_recv_t::operator()(const bool* isstoped, void* param) {
    //_shutdown = false;
    if (_info == NULL || _opr == NULL) {
        FATAL_LOG("heartbeat_recv_t fs_info or fs_opr is null.");
        return -1;
    }

    int32_t ret = IMS_SUCCESS;

    do {
        ret = _opr->subscribe_event_heartbeat();

        if (ret != IMS_SUCCESS) {
            WARNING_LOG("heartbeat_recv_t[%d] subscribe_event failed.", _info->get_no());
            ims_tool_t::safe_sleeps(3);
            continue;
        }

        TRACE_LOG("heartbeat_recv_t[%d] subscribe_event ok.", _info->get_no());

        while (!_shutdown) {
            fs_event_t evt;
            ret = _opr->get_event(evt, _timeout);

            if (ret == IMS_SUCCESS) {
                if (EDT_HEARTBEAT == evt.datatype && strncasecmp(evt.name, "HEARTBEAT", 9) == 0) {
                    fs_mgr_t::instance()->update_runinfo(_info->get_no(), evt.event_data.heartbeat);
                } else {
                    TRACE_LOG("heartbeat_recv_t[%d] recv type:%u,name:%s",
                              _info   ->get_no(), evt.datatype, evt.name);
                }
            } else if (ret == IMS_FAIL_CONNECT) {
                TRACE_LOG("heartbeat_recv_t[%d] get_event lostconnection.", _info->get_no());
                evt.datatype = EDT_HEARTBEAT;
                evt.event_data.heartbeat.cur_session = 0xaaaa; //don't use 0xffff to avoid overflow when added.
                evt.event_data.heartbeat.all_session = 0xaaaa;
                evt.event_data.heartbeat.cpu_idle = 0;
                fs_mgr_t::instance()->update_runinfo(_info->get_no(), evt.event_data.heartbeat);
                break;
            } else if (ret == IMS_FAIL_TIMEOUT) {
                //TRACE_LOG("heartbeat_recv_t[%d] get_event timeout.", _info->get_no());
            } else {
                TRACE_LOG("heartbeat_recv_t[%d] get_event failed ret:%d.", _info->get_no(), ret);
            }
        }

    } while (ret != IMS_SUCCESS && !_shutdown);

    return 0;

}

int32_t callevent_recv_t::operator()(const bool* isstoped, void* param) {
    //_shutdown = false;
    while (!_shutdown) {
        if (_opr->subscribe_event_normal() != IMS_SUCCESS) {
            WARNING_LOG("callevent_recv_t[%d] subscribe_event failed.", _info->get_no());
            ims_tool_t::safe_sleeps(3);
            continue;
        }

        TRACE_LOG("callevent_recv_t[%d] subscribe_event ok.", _info->get_no());
        fs_event_t evt;
        ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

        while (!_shutdown) {
            int32_t ret = _opr->get_event(evt, _timeout);

            if (ret == IMS_SUCCESS) {
                event_data_normal_t& edata = evt.event_data.normal;

                if (strcmp(evt.name , "CHANNEL_ORIGINATE") == 0) {
                    TRACE_LOG("===== uuid:[%s] otheruuid:[%s] sid:%lu",
                              edata.uuid, edata.other_uuid, evt.sessionid);
                    //first side alerting
                    ims_session_operation_t operation;

                    if (session_mgr->get_session_operation(evt.sessionid, operation)
                            && (SOPR_INSERT == operation || SOPR_LISTEN == operation || SOPR_IVRTRANSFER == operation)) {

                        std::list<callid_t> calls;

                        if (session_mgr->locate_call(evt.sessionid, calls) && calls.size() != 0) {
                            evt.callid = calls.front();

                            session_mgr->create_channel(evt.sessionid,
                                                        edata.uuid,
                                                        edata.channel_name,
                                                        CallStateT::SG_UnknownState,
                                                        MediaStateT::MG_UnknownState);

                            session_mgr->update_channel_call(edata.uuid, evt.callid);
                        }
                    } else if (edata.other_uuid[0] == '\0') {
                        TRACE_LOG("Receive Agent ChannelCreate CHANNEL_ORIGINATE EVENT[%ld]"
                                  , evt.sessionid);

                        if (!session_mgr->create_channel(evt.sessionid, edata.uuid, edata.channel_name,
                                                         CallStateT::SG_IdleState, MediaStateT::MG_IdleState)
                                || !session_mgr->create_call(evt.sessionid, edata.uuid, NULL, evt.callid)) {

                            WARNING_LOG("create channel or call failed ignore event");
                            continue;
                        }
                    } else {
                        //other side alerting
                        TRACE_LOG("Receive Customer ChannelCreate CHANNEL_ORIGINATE EVENT[%ld]", evt.sessionid);

                        if (session_mgr->locate_session(edata.other_uuid, (ims::SessionIdT&)evt.sessionid)) {
                            session_mgr->create_channel(evt.sessionid,
                                                        edata.uuid,
                                                        edata.channel_name,
                                                        CallStateT::SG_UnknownState,
                                                        MediaStateT::MG_UnknownState);

                            ims_session_operation_t operation;

                            if (session_mgr->get_session_operation(evt.sessionid, operation) && SOPR_CONSULT == operation) {
                                session_mgr->create_call(evt.sessionid, edata.uuid, NULL, evt.callid);

                                session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.other_deviceno);
                                session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.deviceno);

                                //when dest not exist ,no channel_progress event,
                                callid_t src_callid;

                                if (!session_mgr->locate_call(edata.other_uuid, src_callid)) {
                                    WARNING_LOG("sid=%ld locate_call failed, chid:[%s]", evt.sessionid, edata.uuid);
                                    continue;
                                }

                                session_mgr->remove_channelfromcall(evt.sessionid, src_callid, edata.other_uuid);
                                session_mgr->update_channel_call(edata.other_uuid, evt.callid);
                            } else {
                                if (!session_mgr->locate_call(edata.other_uuid, evt.callid)) {
                                    WARNING_LOG("[%ld] locate_call failed, chid:[%s]", evt.sessionid, edata.uuid);
                                }

                                session_mgr->update_channel_call(edata.uuid, evt.callid);

                                if (session_mgr->get_session_operation(evt.sessionid, operation) && SOPR_MAKECALL == operation) {
                                    if (session_mgr->rt_query_dn(edata.channel_name, DnTypeT::AgentDn)
                                            && session_mgr->rt_query_dn(edata.other_channel_name, DnTypeT::AgentDn)) {
                                        session_mgr->update_call_internal(evt.sessionid, evt.callid, true);
                                    }
                                }
                            }
                        }//if(session_mgr->locate_session
                    }//other_uuid != 0

                    continue;
                } else if (strcasecmp(evt.name, "OPERATION_FAILED") == 0) {
                    session_mgr->add_event(evt.sessionid, evt);
                } else {
                    if (session_mgr->locate_session(edata.uuid, (ims::SessionIdT&)evt.sessionid)
                            && session_mgr->locate_call(edata.uuid, evt.callid)) {
                        session_mgr->add_event(evt.sessionid, evt);
                    } else {
                        WARNING_LOG("[%ld] locate session failed,ignore event:%s", evt.sessionid, evt.name);
                    }
                }
            } else if (IMS_FAIL_CONNECT == ret) {
                break;
            }
        }
    }

    return 0;
}

void callevent_recv_t::fs_inboud_handler(fs_event_t& evt) {
    event_data_normal_t& edata = evt.event_data.normal;
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();
    ReqIdT reqid = 0;

    if (strcasecmp(evt.name, "CHANNEL_EXECUTE") == 0
            && strcasecmp(edata.application, "set") == 0
            && strcasecmp(edata.application_data, "outside_call=true") == 0) {
        TRACE_LOG("New inbound call(%s->%s)", edata.deviceno, edata.called_no);

        if (!session_mgr->rt_query_dn(edata.called_no, DnTypeT::IvrANI, &reqid)) {
            WARNING_LOG("inbound call(%s(%s)->%s)(unknown accessno),omiting",
                        edata.deviceno, edata.channel_name, edata.called_no);
            return;
        }

        session_thread_ptr thrd = session_thrd_mgr::instance()->get_prefer_thread();

        if (!thrd.is_valid()) {
            WARNING_LOG("inbound call(%s(%s)->%s)(get_prefer_thread error),omiting",
                        edata.deviceno, edata.channel_name, edata.called_no);
            return ;
        }

        if (!session_mgr->create_session(_opr->get_fs_no(), reqid, SCRT_INBOUND_IVR, thrd,
                                         edata.caller_no, edata.called_no, (ims::SessionIdT&)evt.sessionid)) {
            WARNING_LOG("inbound call(%s(%s)->%s)(get_prefer_thread error),omiting",
                        edata.deviceno, edata.channel_name, edata.called_no);
            return ;
        }

        if (!session_mgr->create_channel(evt.sessionid, edata.uuid, edata.channel_name,
                                         CallStateT::SG_AlertingState)) {
            WARNING_LOG("inbound call(%s(%s)->%s)(create channel error),omiting",
                        edata.deviceno, edata.channel_name, edata.called_no);
            session_mgr->remove_session(evt.sessionid);
            return ;
        }

        if (!session_mgr->create_call(evt.sessionid, edata.uuid, NULL, evt.callid)) {
            WARNING_LOG("inbound call(%s(%s)->%s)(create call error),omiting",
                        edata.deviceno, edata.channel_name, edata.called_no);
            session_mgr->destroy_channel(edata.uuid);
            return ;
        }

        NOTICE_LOG("New inbound call(%s->%s),create session(%lu) success",
                   edata.deviceno, edata.called_no, evt.sessionid);

        session_mgr->update_call_ani(evt.sessionid, evt.callid, edata.deviceno);
        session_mgr->update_call_dnis(evt.sessionid, evt.callid, edata.called_no);

        OtherEventT ims_event;
        ims_event.sessionid = evt.sessionid;
        ims_event.timestamp = evt.timestamp;
        ims_event.device = edata.called_no;
        ims_event.eventType = OtherEventTypeT::OG_SessionCreate;
        ims_event.callid = ims_tool_t::num2str(evt.callid);
        ims_event.data.insert(std::pair<std::string, std::string>("IMS_CUST_NO", edata.deviceno));
        session_mgr->add_imsevent_other(evt.sessionid, ims_event);
    } else {
        if (session_mgr->locate_session(edata.uuid, (ims::SessionIdT&)evt.sessionid)
                && session_mgr->locate_call(edata.uuid, evt.callid)) {
            session_mgr->add_event(evt.sessionid, evt);
        } else {
            WARNING_LOG("inbound call event(%s)(%s(%s)->%s)(locate_session failed),omiting",
                        evt.name, edata.deviceno, edata.channel_name, edata.called_no);
        }
    }

}
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
