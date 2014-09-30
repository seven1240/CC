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
#include "common.h"
#include "fs_mgr.h"
#include "tools.h"
#include "inbound_chan_thread.h"
#include "thread_pool.h"
#include "ivr_instance_manager.h"


int32_t heartbeat_recv_t::operator()(const bool*, void* param) {
    _shutdown = false;

    if (_info == NULL || _opr == NULL) {
        IVR_FATAL("heartbeat_recv_t fs_info or fs_opr is null.");
        return -1;
    }

    int32_t ret = IVR_SUCCESS;

    do {
        ret = _opr->subscribe_event_heartbeat();

        if (ret != IVR_SUCCESS) {
            IVR_WARN("heartbeat_recv_t[%d] subscribe_event failed.", _info->get_no());
            ivr_tools_t::safe_sleeps(3);
            continue;
        }

        IVR_TRACE("heartbeat_recv_t[%d] subscribe_event ok.", _info->get_no());

        while (!_shutdown) {
            fs_event_t evt;
            ret = _opr->get_event(evt, _timeout);

            if (ret == IVR_SUCCESS) {
                if (EDT_HEARTBEAT == evt.datatype && strncasecmp(evt.name, "HEARTBEAT", 9) == 0) {
                    fs_mgr_t::instance()->update_runinfo(_info->get_no(), evt.event_data.heartbeat);
                } else {
                    IVR_TRACE("heartbeat_recv_t[%d] recv type:%u,name:%s",
                              _info->get_no(), evt.datatype, evt.name);
                }
            } else if (ret == IVR_FAIL_CONNECT) {
                IVR_TRACE("heartbeat_recv_t[%d] get_event lostconnection.", _info->get_no());
                evt.datatype = EDT_HEARTBEAT;
                evt.event_data.heartbeat.cur_session = (~0);
                evt.event_data.heartbeat.all_session = (~0);
                evt.event_data.heartbeat.use_session = 0;
                evt.event_data.heartbeat.cpu_idle = 0;
                fs_mgr_t::instance()->update_runinfo(_info->get_no(), evt.event_data.heartbeat);
                break;
            } else if (ret == IVR_FAIL_TIMEOUT) {
                //IVR_TRACE("heartbeat_recv_t[%d] get_event timeout.", _info->get_no());
            } else {
                IVR_TRACE("heartbeat_recv_t[%d] get_event failed ret:%d.", _info->get_no(), ret);
            }
        }

    } while (ret != IVR_SUCCESS && !_shutdown);

    return 0;

}

int32_t callevent_recv_t::operator()(const bool*, void* param) {
    _shutdown = false;

    while (!_shutdown) {
        if (_opr->subscribe_event_normal() != IVR_SUCCESS) {
            IVR_WARN("callevent_recv_t[%d] subscribe_event failed.", _info->get_no());
            ivr_tools_t::safe_sleeps(3);
            continue;
        }

        IVR_TRACE("callevent_recv_t[%d] subscribe_event ok.", _info->get_no());
        fs_event_t evt;
        //ims_session_manager_t *session_mgr=ims_session_manager_t::instance();

        while (!_shutdown) {
            int32_t ret = _opr->get_event(evt, _timeout);

            if (ret == IVR_SUCCESS) {
                if (0 == evt.sessionid) {
                    if (0 == strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") ||
                            0 == strcasecmp(evt.name, "CHANNEL_PROGRESS")) {
                        IVR_DEBUG("Incall Work");
                        IVR_TRACE("inbound call, , fid(%d), ani(%s), dnis(%s), callid(%s)",
                                  _info->get_no(), evt.event_data.normal.caller_no,
                                  evt.event_data.normal.called_no, evt.event_data.normal.uuid);
                        //New incall, start one flow
                        ///*
                        inbound_script_t* param = new inbound_script_t; // 析构时delete
                        param->type = base_script_t::INBOUND;
                        param->fid = _info->get_no();
                        param->ani = string(evt.event_data.normal.caller_no);
                        param->dnis = string(evt.event_data.normal.called_no);
                        param->callid = string(evt.event_data.normal.uuid);
                        param->channel_name = string(evt.event_data.normal.channel_name);
                        param->channel_id = string(evt.event_data.normal.uuid);
                        param->callsource = ivr_tools_t::get_address(_info->get_address());
                        param->imsno = (uint32_t) - 1;
                        param->imssid = 0;
                        param->requestId = 0;
                        InboundChanThread* inbound_thread = new InboundChanThread(param); // thread pool will delete it
                        ThreadPool* threadpool = ThreadPool::get_instance();
                        threadpool->assign_work(inbound_thread);
                        //*/
                    }
                } else if (IvrInstanceManager::get_instance()->search_ivr_instance(evt.sessionid))
                    //else if(evt.sessionid == 123)
                {
                    ivr_base_event_t* ivr_evt = NULL;
                    bool has_new_evt = false;

                    //Compact IVR Event
                    if (0 == strcasecmp(evt.name, "DTMF")) {
                        if (IVR_SUCCESS != compact_ivr_dtmf_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact DTMF Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_ANSWER")) {
                        if (IVR_SUCCESS != compact_ivr_answer_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Answer Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_PROGRESS_MEDIA") ||
                               0 == strcasecmp(evt.name, "CHANNEL_PROGRESS")) {
                        if (IVR_SUCCESS != compact_ivr_alert_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Alert Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_HANGUP")) {
                        if (IVR_SUCCESS != compact_ivr_hangup_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Hangup Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_BRIDGE")) {
                        if (IVR_SUCCESS != compact_ivr_bridge_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Bridge Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_UNBRIDGE")) {
                        if (IVR_SUCCESS != compact_ivr_unbridge_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Unbridge Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_DESTROY")) {
                        if (IVR_SUCCESS != compact_ivr_destroy_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Destroy Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "OPERATION_FAILED")) {
                        if (IVR_SUCCESS != compact_ivr_callfail_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact CallFail Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "RECORD_START")) {
                        if (IVR_SUCCESS != compact_ivr_recordstart_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Record Start Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "RECORD_STOP")) {
                        if (IVR_SUCCESS != compact_ivr_recordstop_evt(&ivr_evt, evt)) {
                            IVR_WARN("Compact Record Stop Event Fail");
                            continue;
                        }

                        has_new_evt = true;
                    } else if (0 == strcasecmp(evt.name, "CHANNEL_EXECUTE_COMPLETE")) {
                        IVR_DEBUG("app: %s,  resp: %s", evt.event_data.normal.application,
                                  evt.event_data.normal.application_resp);

                        if (0 == strcasecmp(evt.event_data.normal.application, "playback") &&
                                0 == strcasecmp(evt.event_data.normal.application_resp, "FILE PLAYED")) {
                            if (IVR_SUCCESS != compact_ivr_playend_evt(&ivr_evt, evt)) {
                                IVR_WARN("Compact PlayEnd Event Fail");
                                continue;
                            }

                            has_new_evt = true;
                        } else if (0 == strcasecmp(evt.event_data.normal.application, "playback") &&
                                   0 == strcasecmp(evt.event_data.normal.application_resp, "FILE NOT FOUND")) {
                            if (IVR_SUCCESS != compact_ivr_notfound_evt(&ivr_evt, evt)) {
                                IVR_WARN("Compact FileNotExist Event Fail");
                                continue;
                            }

                            has_new_evt = true;
                        } else if (0 == strcasecmp(evt.event_data.normal.application, "playback") &&
                                   0 == strcasecmp(evt.event_data.normal.application_resp, "PLAYBACK ERROR")) {
                            if (IVR_SUCCESS != compact_ivr_notfound_evt(&ivr_evt, evt)) {
                                IVR_WARN("Compact FileNotExist Event Fail");
                                continue;
                            }

                            has_new_evt = true;
                        } else if (0 == strcasecmp(evt.event_data.normal.application, "read")) {
                            if (IVR_SUCCESS != compact_ivr_playend_evt(&ivr_evt, evt)) {
                                IVR_WARN("Compact PlayEnd Event Fail");
                                continue;
                            }

                            has_new_evt = true;
                        } else if (0 == strcasecmp(evt.event_data.normal.application, "play_and_get_digits")) {
                            if (IVR_SUCCESS != compact_ivr_getdigits_evt(&ivr_evt, evt)) {
                                IVR_WARN("Compact GetDigits Event Fail");
                                continue;
                            }

                            has_new_evt = true;
                        }
                    }

                    if (has_new_evt) {
                        log_ivrevent(ivr_evt);

                        if (ivr_evt != NULL && IvrInstanceManager::get_instance()->is_transagent(ivr_evt->sessionId)) {
                            IVR_TRACE("ivr instance(%lu) don't need fs event", ivr_evt->sessionId);
                        } else if (IVR_SUCCESS != IvrInstanceManager::get_instance()->put_ivr_event(ivr_evt)
                                   && ivr_evt != NULL) {
                            IVR_TRACE("push freeswitch event failed!");
                            delete ivr_evt;
                            ivr_evt = NULL;
                        }
                    }

                }
            } else if (IVR_FAIL_CONNECT == ret) {
                ivr_tools_t::safe_sleeps(3);
                break;
            }
        }
    }

    return 0;
}

int32_t callevent_recv_t::log_ivrevent(const ivr_base_event_t* ivr_evt) {
    ostringstream ost;
    //ost("");
    ost << endl << "====================================================" << endl;

    if (ivr_evt->evt_type == ivr_base_event_t::CALL_EVENT) {
        ost << "TYPE\t\t:CALL_EVENT" << endl;

        switch (((ivr_call_event_t*)ivr_evt)->evt_name) {
        case ivr_call_event_t::IVR_EVT_ANSWER:
            ost << "NAME\t\t:ANSWER" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_ALERT:
            ost << "NAME\t\t:ALERT" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_HANGUP:
            ost << "NAME\t\t:HANGUP" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_BRIDGE:
            ost << "NAME\t\t:BRIDGE" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_UNBRIDGE:
            ost << "NAME\t\t:UNBRIDGE" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_CHANLE_DESTORY:
            ost << "NAME\t\t:CHANLE_DESTROY" << endl;
            break;

        case ivr_call_event_t::IVR_EVT_CALLFAIL:
            ost << "NAME\t\t:CALLFAIL" << endl;
            break;
        }

        switch (((ivr_call_event_t*)ivr_evt)->evt_reason) {
        case ivr_call_event_t::CALL_NORMAL:
            ost << "REASON\t\t:CALL_NORMAL" << endl;
            break;

        case ivr_call_event_t::CALL_DEST_BUSY:
            ost << "REASON\t\t:CALL_DEST_BUSY" << endl;
            break;

        case ivr_call_event_t::CALL_DEST_NOANSWER:
            ost << "REASON\t\t:CALL_DEST_NOANSWER" << endl;
            break;

        case ivr_call_event_t::CALL_REJECTED:
            ost << "REASON\t\t:CALL_REJECTED" << endl;
            break;

        case ivr_call_event_t::CALL_UNKNOW:
            ost << "REASON\t\t:CALL_UNKNOW" << endl;
            break;

        case ivr_call_event_t::CALL_USER_NOT_REGISTERED:
            ost << "REASON\t\t:CALL_USER_NOT_REGISTERED" << endl;
            break;

        case ivr_call_event_t::CALL_SUBSCRIBER_ABSENT:
            ost << "REASON\t\t:CALL_SUBSCRIBER_ABSENT" << endl;
            break;
        }

        ost << "SESSIONID\t:" << ((ivr_call_event_t*)ivr_evt)->sessionId << endl;
        ost << "TIMESTAMP\t:" << ((ivr_call_event_t*)ivr_evt)->timestamp << endl;
        ost << "CALLID\t\t:" << ((ivr_call_event_t*)ivr_evt)->callid << endl;
        ost << "ANI\t\t:" << ((ivr_call_event_t*)ivr_evt)->ani << endl;
        ost << "DNIS\t\t:" << ((ivr_call_event_t*)ivr_evt)->dnis << endl;
        ost << "OTHER_CALLID\t:" << ((ivr_call_event_t*)ivr_evt)->other_callid << endl;
        ost << "OTHER_ANI\t:" << ((ivr_call_event_t*)ivr_evt)->other_ani << endl;
        ost << "OTHER_DNIS\t:" << ((ivr_call_event_t*)ivr_evt)->other_dnis << endl;
    } else if (ivr_evt->evt_type == ivr_base_event_t::MEDIA_EVENT) {
        ost << "TYPE\t\t:MEDIA_EVENT" << endl;

        switch (((ivr_media_event_t*)ivr_evt)->evt_name) {
        case ivr_media_event_t::IVR_EVT_PLAY_END:
            ost << "NAME\t\t:PLAY_END" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_FILENOTEXIST:
            ost << "NAME\t\t:FILENOTEXIST" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_GETDIGIT_SUCC:
            ost << "NAME\t\t:GETDIGIT_SUCC" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_GETDIGIT_FAIL:
            ost << "NAME\t\t:GETDIGIT_FAIL" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_DTMF:
            ost << "NAME\t\t:DTMF" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_RECORD_START:
            ost << "NAME\t\t:RECORD_START" << endl;
            break;

        case ivr_media_event_t::IVR_EVT_RECORD_END:
            ost << "NAME\t\t:RECORD_END" << endl;
            break;
        }

        switch (((ivr_media_event_t*)ivr_evt)->evt_reason) {
        case ivr_media_event_t::MEDIA_END:
            ost << "REASON\t\t:MEDIA_END" << endl;
            break;

        case ivr_media_event_t::MEDIA_GETDIGIT:
            ost << "REASON\t\t:MEDIA_GETDIGIT" << endl;
            break;

        case ivr_media_event_t::MEDIA_INVALID_FILE:
            ost << "REASON\t\t:MEDIA_INVALID_FILE" << endl;
            break;

        case ivr_media_event_t::MEDIA_DISCONNECT:
            ost << "REASON\t\t:MEDIA_DISCONNECT" << endl;
            break;

        case ivr_media_event_t::MEDIA_UNKNOW:
            ost << "REASON\t\t:MEDIA_UNKNOW" << endl;
            break;
        }

        ost << "SESSIONID\t:" << ((ivr_media_event_t*)ivr_evt)->sessionId << endl;
        ost << "TIMESTAMP\t:" << ((ivr_media_event_t*)ivr_evt)->timestamp << endl;
        ost << "CALLID\t\t:" << ((ivr_media_event_t*)ivr_evt)->callid << endl;
        ost << "MEDIA_DATA\t:" << ((ivr_media_event_t*)ivr_evt)->media_data << endl;
        ost << "DIGITS\t\t:" << ((ivr_media_event_t*)ivr_evt)->digits << endl;
    } else if (ivr_evt->evt_type == ivr_base_event_t::OTHER_EVENT) {
        ost << "OTHER_EVENT" << endl;

        switch (((ivr_other_event_t*)ivr_evt)->evt_name) {
        case ivr_other_event_t::IVR_EVT_TIMEOUT:
            ost << "NAME\t\t:TIMEOUT" << endl;
            break;

        case ivr_other_event_t::IVR_EVT_UNKNOW:
            ost << "NAME\t\t:UNKNOW" << endl;
            break;
        }
    }

    ost << "====================================================" << endl;
    //wangtingdel com_writelog("ivrevent", ost.str().c_str());
    BGCC_TRACE("ivrevent", ost.str().c_str());
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_callevt_base(ivr_base_event_t const* ivr_evt,
        const fs_event_t& fs_evt) {
    ((ivr_call_event_t*)ivr_evt)->timestamp = fs_evt.timestamp;

    ((ivr_call_event_t*)ivr_evt)->callid = fs_evt.event_data.normal.uuid;
    ((ivr_call_event_t*)ivr_evt)->ani    = fs_evt.event_data.normal.caller_no;
    ((ivr_call_event_t*)ivr_evt)->dnis   = fs_evt.event_data.normal.called_no;

    ((ivr_call_event_t*)ivr_evt)->other_callid = fs_evt.event_data.normal.other_uuid;
    ((ivr_call_event_t*)ivr_evt)->other_ani    = fs_evt.event_data.normal.other_caller_no;
    ((ivr_call_event_t*)ivr_evt)->other_dnis   = fs_evt.event_data.normal.other_called_no;
    string reason = fs_evt.event_data.normal.reason;

    if (reason == "NORMAL_CLEARING") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_NORMAL;
    } else if (reason == "USER_BUSY") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_DEST_BUSY;
    } else if (reason == "NO_ANSWER") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_DEST_NOANSWER;
    } else if (reason == "CALL_REJECTED") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_REJECTED;
    } else if (reason == "USER_NOT_REGISTERED") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_USER_NOT_REGISTERED;
    } else if (reason == "SUBSCRIBER_ABSENT") {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_SUBSCRIBER_ABSENT;
    } else {
        ((ivr_call_event_t*)ivr_evt)->evt_reason = ivr_call_event_t::CALL_UNKNOW;
    }

    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_answer_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_ANSWER;
    compact_callevt_base(*ivr_evt, fs_evt);

    // add channel information
    channel_info_t cinfo;
    cinfo.callsource = ivr_tools_t::get_address(_info->get_address());
    cinfo.channel_id = string(fs_evt.event_data.normal.uuid);
    cinfo.channel_name = string(fs_evt.event_data.normal.channel_name);
    IvrInstanceManager::get_instance()->add_channel_info(((ivr_call_event_t*)(*ivr_evt))->callid,
            cinfo);

    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_hangup_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_HANGUP;
    compact_callevt_base(*ivr_evt, fs_evt);

    // remove channel information
    // when ivr instance finish running, will remove info automatic
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_destroy_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_CHANLE_DESTORY;
    compact_callevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_alert_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_ALERT;
    compact_callevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_bridge_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_BRIDGE;
    compact_callevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_unbridge_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_UNBRIDGE;
    compact_callevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_callfail_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_call_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::CALL_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_call_event_t*)(*ivr_evt))->evt_name = ivr_call_event_t::IVR_EVT_CALLFAIL;
    compact_callevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

/**媒体事件*/
int32_t callevent_recv_t::compact_mediaevt_base(ivr_base_event_t const* ivr_evt,
        const fs_event_t& fs_evt) {
    ((ivr_call_event_t*)ivr_evt)->callid = fs_evt.event_data.normal.uuid;
    ((ivr_call_event_t*)ivr_evt)->timestamp = fs_evt.timestamp;
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_playend_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_PLAY_END;
    ((ivr_media_event_t*)(*ivr_evt))->media_data = fs_evt.event_data.normal.application_data;
    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_END;
    compact_mediaevt_base(*ivr_evt, fs_evt);

    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_notfound_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_FILENOTEXIST;
    ((ivr_media_event_t*)(*ivr_evt))->media_data = fs_evt.event_data.normal.application_data;
    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_INVALID_FILE;
    compact_mediaevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_getdigits_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    if (strlen(fs_evt.event_data.normal.ivr_data) > 0) {
        ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_GETDIGIT_SUCC;
        ((ivr_media_event_t*)(*ivr_evt))->digits = fs_evt.event_data.normal.ivr_data;
    } else {
        ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_GETDIGIT_FAIL;
    }

    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_GETDIGIT;
    compact_mediaevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_dtmf_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_DTMF;
    ((ivr_media_event_t*)(*ivr_evt))->digits = fs_evt.event_data.normal.ivr_data;
    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_GETDIGIT;
    compact_mediaevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_recordstart_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_RECORD_START;
    ((ivr_media_event_t*)(*ivr_evt))->media_data = fs_evt.event_data.normal.ivr_data;
    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_UNKNOW;
    compact_mediaevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

int32_t callevent_recv_t::compact_ivr_recordstop_evt(ivr_base_event_t** ivr_evt,
        const fs_event_t& fs_evt) {
    (*ivr_evt) = new ivr_media_event_t;
    (*ivr_evt)->evt_type = ivr_base_event_t::MEDIA_EVENT;
    (*ivr_evt)->sessionId = fs_evt.sessionid;

    ((ivr_media_event_t*)(*ivr_evt))->evt_name = ivr_media_event_t::IVR_EVT_RECORD_END;
    ((ivr_media_event_t*)(*ivr_evt))->media_data = fs_evt.event_data.normal.ivr_data;
    ((ivr_media_event_t*)(*ivr_evt))->evt_reason = ivr_media_event_t::MEDIA_END;
    compact_mediaevt_base(*ivr_evt, fs_evt);
    return IVR_SUCCESS;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
