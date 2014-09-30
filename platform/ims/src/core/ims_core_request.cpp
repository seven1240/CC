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
#include <callback.h>
#include "ims_log.h"
#include "ims_tool.h"
#include "ims_core.h"
#include "ims_core_session_mgr.h"
#include "ims_core_request.h"

using namespace bgcc;

int32_t ims_request_t::operator()(const bool* isstoped, void* param) {
    uint64_t disconn_time = 0;
    uint64_t last_heartbeat = ims_tool_t::get_timestamp_s();
    ims::event_callbackProxy proxy(_conn_info, 0, 0);

    //ims::event_callbackProxy proxy(_conn_info);
    while (_isconnect) {
        ims::OtherEventT heartbeat;
        heartbeat.timestamp = ims_tool_t::get_timestamp_ms();
        heartbeat.sessionid = 0;
        heartbeat.callid = "";
        heartbeat.device = "";
        heartbeat.eventType = ims::OtherEventTypeT::OG_HeartBeat;
        proxy.SendOtherEvent(heartbeat);

        if (proxy.get_errno() != 0) {
            if (0 == disconn_time) {
                disconn_time = ims_tool_t::get_timestamp_s();
            } else if ((ims_tool_t::get_timestamp_s() - disconn_time) >= 6) { //fail for 6 seconds
                WARNING_LOG("event push to client(%s) max reconn failed,reqid=%lu,remove request"
                            , _conn_info.c_str(), _reqid);
                ims_session_manager_t::instance()->rt_del_req(_reqid);
                break;
            }

            WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
            ims_tool_t::safe_sleepms(500);
            continue;
        } else {
            disconn_time = 0;
        }

        TRACE_LOG("ims event pusher(%lu/%s) start", _reqid, _conn_info.c_str());
        ims::CallEventT callevent;
        ims::MediaEventT mediaevent;
        ims::RouteEventT routeevent;
        ims::OtherEventT otherevent;

        while (_isconnect) {
            if ((ims_tool_t::get_timestamp_s() - last_heartbeat) >= 3) {
                last_heartbeat = ims_tool_t::get_timestamp_s();
                heartbeat.timestamp = ims_tool_t::get_timestamp_ms();
                ims::CcResultT result = proxy.SendOtherEvent(heartbeat);

                if (proxy.get_errno() != 0) {
                    WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
                    break;
                }
            }

            if (_qevent_call.get(callevent)) {
                TRACE_LOG("before push _qevent_call.size()=%ld", _qevent_call.size());
                ims::CcResultT result = proxy.SendCallEvent(callevent);
                TRACE_LOG("after push _qevent_call.size()=%ld", _qevent_call.size());

                if (proxy.get_errno() != 0) {
                    WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
                    _qevent_call.insert(callevent);
                    break;
                }

                if (result != ims::CcResultT::ResSuccess) {
                    WARNING_LOG("***Push_Evt:(%s:%s) to %lu(%s) failed(%s)"
                                , callevent.device.c_str(), callevent.eventType.get_desc().c_str()
                                , _reqid, _conn_info.c_str(),
                                result.get_desc().c_str());
                } else {
                    std::ostringstream ostm;
                    ostm << std::endl;
                    ostm << "================IMS EVENT (CALL)================" << std::endl;
                    ostm << "Time           : " << (uint64_t)callevent.timestamp << std::endl;
                    ostm << "Type           : " << callevent.eventType.get_desc() << std::endl;
                    ostm << "SessionID      : " << (uint64_t)callevent.sessionid << std::endl;
                    ostm << "CallID         : " << callevent.callid << std::endl;
                    ostm << "CallState      : " << callevent.state.get_desc() << std::endl;
                    ostm << "Device         : " << callevent.device << std::endl;
                    ostm << "PartyNum       : " << callevent.partyNum << std::endl;
                    ostm << "OrignatingParty: " << callevent.originatingParty << std::endl;
                    ostm << "OtherDevice    : " << callevent.otherDevice << std::endl;
                    ostm << "OtherPartyAttr : " << callevent.otherAttr.get_desc() << std::endl;
                    ostm << "OriginateCallid: " << callevent.originalCallid << std::endl;
                    ostm << "OriginateANI   : " << callevent.originalAni << std::endl;
                    ostm << "OriginateDNIS  : " << callevent.originalDnis << std::endl;
                    ostm << "Reason         : " << callevent.reason.get_desc() << std::endl;
                    ostm << "ReqID          : " << _reqid << std::endl;
                    ostm << "ConnInfo       : " << _conn_info.c_str() << std::endl;
                    ostm << "================IMS EVENT ====================" << std::endl;

                    BGCC_TRACE("imsevent", "%s", ostm.str().c_str());
                }

                TRACE_LOG("after print _qevent.size()=%ld", _qevent_call.size());
            }

            if (_qevent_media.get(mediaevent)) {
                TRACE_LOG("before push _qevent_media.size()=%ld", _qevent_call.size());
                ims::CcResultT result = proxy.SendMediaEvent(mediaevent);
                TRACE_LOG("after push _qevent_media.size()=%ld", _qevent_call.size());

                if (proxy.get_errno() != 0) {
                    WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
                    _qevent_media.insert(mediaevent);
                    break;
                }

                if (result != ims::CcResultT::ResSuccess) {
                    WARNING_LOG("***Push_Evt:(%s:%s) to %lu(%s) failed(%s)"
                                , mediaevent.device.c_str(), mediaevent.eventType.get_desc().c_str()
                                , _reqid, _conn_info.c_str(),
                                result.get_desc().c_str());
                } else {
                    std::ostringstream ostm;
                    ostm << std::endl;
                    ostm << "================IMS EVENT (MEDIA)================" << std::endl;
                    ostm << "Time           : " << (uint64_t)mediaevent.timestamp << std::endl;
                    ostm << "Type           : " << mediaevent.eventType.get_desc() << std::endl;
                    ostm << "SessionID      : " << (uint64_t)mediaevent.sessionid << std::endl;
                    ostm << "CallID         : " << mediaevent.callid << std::endl;
                    ostm << "Device         : " << mediaevent.device << std::endl;
                    ostm << "MediaState     : " << mediaevent.state.get_desc() << std::endl;
                    ostm << "OtherDevice    : " << mediaevent.otherDevice << std::endl;
                    ostm << "MediaBuffer    : " << mediaevent.mediaBuffer << std::endl;
                    ostm << "Reason         : " << mediaevent.reason.get_desc() << std::endl;
                    ostm << "ReqID          : " << _reqid << std::endl;
                    ostm << "ConnInfo       : " << _conn_info.c_str() << std::endl;
                    ostm << "================IMS EVENT ======================" << std::endl;

                    BGCC_TRACE("imsevent", "%s", ostm.str().c_str());
                }
            }

            if (_qevent_route.get(routeevent)) {
                TRACE_LOG("before push _qevent_route.size()=%ld", _qevent_call.size());
                ims::CcResultT result = proxy.SendRouteEvent(routeevent);
                TRACE_LOG("after push _qevent_route.size()=%ld", _qevent_call.size());

                if (proxy.get_errno() != 0) {
                    WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
                    _qevent_route.insert(routeevent);
                    break;
                }

                if (result != ims::CcResultT::ResSuccess) {
                    WARNING_LOG("***Push_Evt:(%s:%s) to %lu(%s) failed(%s)"
                                , routeevent.device.c_str(), routeevent.eventType.get_desc().c_str()
                                , _reqid, _conn_info.c_str(),
                                result.get_desc().c_str());
                } else {
                    std::ostringstream ostm;
                    ostm << std::endl;
                    ostm << "================IMS EVENT (ROUTE)================" << std::endl;
                    ostm << "Time           : " << (uint64_t)routeevent.timestamp << std::endl;
                    ostm << "Type           : " << routeevent.eventType.get_desc() << std::endl;
                    ostm << "SessionID      : " << (uint64_t)routeevent.sessionid << std::endl;
                    ostm << "CallID         : " << routeevent.callid << std::endl;
                    ostm << "Device         : " << routeevent.device << std::endl;

                    ostm << "RequestID      : " << routeevent.requstid << std::endl;
                    ostm << "TargetDevice   : " << routeevent.targetDevice << std::endl;
                    ostm << "TargetService  : " << routeevent.destService.get_desc() << std::endl;
                    ostm << "RequestType    : " << routeevent.requestType.get_desc() << std::endl;
                    ostm << "RequestArgs    : " << routeevent.requestArgs << std::endl;
                    ostm << "Level          : " << routeevent.level << std::endl;
                    ostm << "CallerNo       : " << routeevent.callerDn << std::endl;
                    ostm << "CalleeNo       : " << routeevent.calleeDn << std::endl;
                    ostm << "ValidTime      : " << routeevent.validtime << std::endl;
                    ostm << "TimeOut        : " << routeevent.timeout << std::endl;
                    ostm << "Buffer         : " << routeevent.buffer << std::endl;
                    ostm << "Reason         : " << routeevent.reason.get_desc() << std::endl;

                    ostm << "ReqID          : " << _reqid << std::endl;
                    ostm << "ConnInfo       : " << _conn_info.c_str() << std::endl;
                    ostm << "================IMS EVENT ======================" << std::endl;
                    BGCC_TRACE("imsevent", "%s", ostm.str().c_str());
                }
            }

            if (_qevent_other.get(otherevent)) {
                TRACE_LOG("before push _qevent_other.size()=%ld", _qevent_call.size());
                ims::CcResultT result = proxy.SendOtherEvent(otherevent);
                TRACE_LOG("after push _qevent_other.size()=%ld", _qevent_call.size());

                if (proxy.get_errno() != 0) {
                    WARNING_LOG("event push to client(%s) failed,reqid=%lu", _conn_info.c_str(), _reqid);
                    _qevent_other.insert(otherevent);
                    break;
                }

                if (result != ims::CcResultT::ResSuccess) {
                    WARNING_LOG("***Push_Evt:(%s:%s) to %lu(%s) failed(%s)"
                                , otherevent.device.c_str(), otherevent.eventType.get_desc().c_str()
                                , _reqid, _conn_info.c_str(),
                                result.get_desc().c_str());
                } else {
                    std::ostringstream ostm;
                    ostm << std::endl;
                    ostm << "================IMS EVENT (OTHER)================" << std::endl;
                    ostm << "Time           : " << (uint64_t)otherevent.timestamp << std::endl;
                    ostm << "Type           : " << otherevent.eventType.get_desc() << std::endl;
                    ostm << "SessionID      : " << (uint64_t)otherevent.sessionid << std::endl;
                    ostm << "CallID         : " << otherevent.callid << std::endl;
                    ostm << "Device         : " << otherevent.device << std::endl;

                    for (ims::OtherEventDataT::const_iterator data = otherevent.data.begin();
                            data != otherevent.data.end(); ++data) {
                        ostm << "Data           : " << "key:" << data->first << ",val:" << data->second << std::endl;
                    }

                    ostm << "ReqID          : " << _reqid << std::endl;
                    ostm << "ConnInfo       : " << _conn_info.c_str() << std::endl;
                    ostm << "================IMS EVENT ======================" << std::endl;

                    BGCC_TRACE("imsevent", "%s", ostm.str().c_str());
                }
            }

            ims_tool_t::safe_sleepms(1);
        }

        //the earyliest disconnected timestamp, to makesure that ims knows acd-dead within 6 seconds.
        //execute this sentence only if inner-loop breaked.
        disconn_time = last_heartbeat - 3;
    }

    TRACE_LOG("ims event pusher(%lu/%s) stopped", _reqid, _conn_info.c_str());
    return 0;
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
