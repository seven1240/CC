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

#include <libgen.h>

#include "fs_opr.h"
#include "tools.h"
#include "ivr_instance_manager.h"
#include "ims/ims_mgr.h"

#define IMSDATA_EQUAL IMS_SESSION_TAG"="

int32_t fs_opr_t::connect(uint32_t address, int32_t port, const char* pswd, bool reconnect) {
    int32_t ret = IVR_FAIL_CONNECT;
    char ip[sizeof "255.255.255.255"];

    if (reconnect) {
        disconnect();
        ivr_tools_t::inet_ntop(address, ip, sizeof "255.255.255.255");

        if (esl_connect(&_handle, ip, _port, NULL, _pswd) == ESL_SUCCESS) {
            eval(RECORD_BASEDIR, _recordbase, LEN_256);
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("reconnect to fs [%s][%d] failed", ip, _port);
            //disconnect();
        }
    } else {
        if (is_handle_valid()) {
            return IVR_SUCCESS;
        }

        strncpy(_pswd, pswd, LEN_16);
        _address = address;
        _port = port;

        ivr_tools_t::inet_ntop(address, ip, sizeof "255.255.255.255");

        if (esl_connect(&_handle, ip, _port, NULL, _pswd) == ESL_SUCCESS) {
            eval(RECORD_BASEDIR, _recordbase, LEN_256);
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("connect to fs [%s][%d] failed", ip, _port);
            //disconnect();
        }
    }

    return ret;
}

int32_t fs_opr_t::reset(uint32_t address, int32_t port, const char* pswd) {

    strncpy(_pswd, pswd, LEN_16);
    _address = address;
    _port = port;

    return connect(address, port, pswd, true);
}

int32_t fs_opr_t::register_session(const char* uuid, ivr_session_id_t sid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, "IVR_SESSION_ID=%lu", sid);
    IVR_DEBUG("STARS BEFORE TAG[%s][%lu][%s]", uuid, sid, szcmd);

    if (set_channel_attribute(uuid, szcmd)
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:register;ret(%s)", fs_resp);
    }

    FUNC_END();
}

///////////////////////////////////// EVENT START /////////////////////////////////////////////////

int32_t fs_opr_t::subscribe_event_normal() {
    return subscribe_event(EVENT_NORMAL);
}

int32_t fs_opr_t::subscribe_event_heartbeat() {
    return subscribe_event(EVENT_HEARTBEAT);
}

int32_t fs_opr_t::subscribe_event(const char* event) {
    FUNC_BEGIN();

    (void)szcmd;
    (void)fs_resp;

    if (esl_events(&_handle, ESL_EVENT_TYPE_PLAIN, event) == ESL_SUCCESS) {
        IVR_TRACE("subscribe_event %s success", event);
        ret = IVR_SUCCESS;
        break;
    }

    if (is_handle_valid()) {
        ret = IVR_FAIL_TIMEOUT;
        break;
    } else if (IVR_SUCCESS != connect(_address, _port, _pswd, true)) {
        IVR_WARN("subscribe_event %s failed(connect err)", event);
        ret = IVR_FAIL_CONNECT;
        break;
    }

    FUNC_END();
}

bool fs_opr_t::check_ivr_ip(const char* get_ip) {
    ostringstream oss;
    oss << g_server_ip << ":" << g_server_port;
    string oldIP = oss.str();
    IVR_DEBUG("RECV FS DATA: IVR_GET[%s] IVR_OLD[%s]", get_ip, oldIP.c_str());
    return 0 == strcasecmp(get_ip, oldIP.c_str());

}

int32_t fs_opr_t::get_event(fs_event_t& event, uint32_t timeout) {
    FUNC_BEGIN();
    bzero(&event, sizeof(event));
    (void)fs_resp;

    //if(esl_recv_timed(&_handle,timeout*1000)==ESL_SUCCESS){
    //check_q If set to 1, will check the handle queue (handle->race_event) and return the last
    //event from it
    //
    //没太看明白 稍微看了下源码，好像是set为1则取队列中的。不设置为1则可能丢事件，需要再次确定
    if (esl_recv_event_timed(&_handle, timeout * 1000, 1, NULL) == ESL_SUCCESS) {
        event.timestamp = 0;
        //拷贝事件到event中
        get_head_val("Event-Name", event.name, LEN_64);

        if (IVR_SUCCESS == get_head_val("Event-Date-Timestamp", szcmd, LEN_512)) {
            event.timestamp = atoll(szcmd);
        }

        if (strcasecmp(event.name, "HEARTBEAT") == 0) {
            event.datatype = EDT_HEARTBEAT;
            event.event_data.heartbeat.use_session = 0;

            if (IVR_SUCCESS == get_head_val("Session-Since-Startup", szcmd, LEN_512)) {
                event.event_data.heartbeat.all_session = (uint32_t)atoi(szcmd);
            }

            if (IVR_SUCCESS == get_head_val("Session-Count", szcmd, LEN_512)) {
                event.event_data.heartbeat.cur_session = (uint32_t)atoi(szcmd);
            }

            if (IVR_SUCCESS == get_head_val("Idle-CPU", szcmd, LEN_512)) {
                event.event_data.heartbeat.cpu_idle = (uint32_t)atoi(szcmd);
            }
        } else {
            event.datatype = EDT_NORMAL;
            event.sessionid = 0;
            event.event_data.normal.call_direction = FCD_UNKNOWN;
            event.event_data.normal.call_state = FCS_UNKNOWN;

            char tmp_uuid[LEN_64 + 1];
            get_head_val("Unique-ID", tmp_uuid, LEN_64);

            if (IVR_SUCCESS == get_var("IVR_SESSION_ID", szcmd, LEN_512)) {
                event.sessionid = atoll(szcmd);
            } else if (IVR_SUCCESS == get_var(IMS_SESSION_TAG, szcmd, LEN_512)) {
                int64_t ims_sid = atoll(szcmd);

                if (ims_sid != 0) {
                    ims_mgr_t::get_instance()->get_map_session_id(ims_sid, event.sessionid);
                }
            }

            string getIP = "";

            if (IVR_SUCCESS == get_var("IVR_GET", szcmd, LEN_512)) {
                getIP = szcmd;
            }

            if (strcasecmp(event.name, "BACKGROUND_JOB") == 0) {
                get_head_val("Job-Command", szcmd, LEN_512);

                if (0 != strcasecmp(szcmd, "originate")) {
                    continue;
                }

                event.event_data.normal.call_direction = FCD_OUTBOUND;
                char* fs_resp = esl_event_get_body(_handle.last_ievent);

                if (fs_resp && !is_result_ok(fs_resp)) {
                    strncpy(event.event_data.normal.reason, fs_resp + 5, LEN_128);
                    char* fs_tmp = event.event_data.normal.reason;

                    while (fs_tmp && *fs_tmp) {
                        if (*fs_tmp == '\n') {
                            *fs_tmp = '\0';
                            break;
                        }

                        fs_tmp ++;
                    }

                    char tmp[LEN_512 + 1] = {0};
                    //Channel name
                    get_head_val("Job-Command-Arg", tmp, LEN_512);

                    {
                        char* tmp_start = strstr(tmp, "}");

                        if (tmp_start) {
                            char* tmp_end = strstr(tmp_start, " ");

                            if (tmp_end && tmp_end > tmp_start) {
                                strncpy(event.event_data.normal.channel_name, tmp_start + 1, tmp_end - tmp_start - 1);
                            }
                        }

                    }
                    //other_caller_no
                    {
                        char* tmp_start = strstr(tmp, "}");

                        if (tmp_start) {
                            char* tmp_end = strstr(tmp_start, " ");

                            if (tmp_end) {
                                char* tmp_mid = tmp_start;

                                while (tmp_mid && tmp_mid < tmp_end) {
                                    if (*(tmp_mid + 1) >= '0' && *(tmp_mid + 1) <= '9') {
                                        break;
                                    }

                                    tmp_mid = strstr(tmp_mid + 1, "/");
                                }

                                //IVR_DEBUG("%x,%x:%s,%s", tmp_mid, tmp_end, tmp_mid, tmp_end);
                                IVR_DEBUG("tmp_mid,tmp_end:%s,%s", tmp_mid, tmp_end);

                                if (tmp_mid && tmp_mid < tmp_end) {
                                    strncpy(event.event_data.normal.other_called_no, tmp_mid + 1, tmp_end - tmp_mid - 1);
                                }
                            }
                        }
                    }
                    //other_called_no
                    {
                        char* tmp_start = strstr(tmp, "park()");

                        if (tmp_start && *(tmp_start + 1) >= '0' && *(tmp_start + 1) <= '9') {
                            tmp_start = strstr(tmp_start + 1, " ");

                            if (tmp_start) {
                                tmp_start = strstr(tmp_start + 1, " ");

                                if (tmp_start) {
                                    tmp_start = strstr(tmp_start + 1, " ");

                                    if (tmp_start) {
                                        if (*(tmp_start + 1) >= '0' && *(tmp_start + 1) <= '9') {
                                            char* tmp_end = strstr(tmp_start + 1, " ");

                                            if (tmp_end && tmp_end > tmp_start) {
                                                strncpy(event.event_data.normal.other_caller_no,
                                                        tmp_start + 1, tmp_end - tmp_start - 1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //Seesion id
                    {
                        char* tmp_sz = strstr(tmp, "IVR_SESSION_ID=");

                        if (tmp_sz) {
                            tmp_sz += 15;
                            char* id_end = tmp_sz;

                            while (id_end && isdigit(*id_end)) {
                                id_end++;
                            }

                            if (id_end) {
                                *id_end = '\0';
                                event.sessionid = atoll(tmp_sz);
                                strncpy(event.name, "OPERATION_FAILED", LEN_64);
                            }
                        } else if ((tmp_sz = strstr(tmp, IMSDATA_EQUAL)) != NULL) {
                            // not found IVR_SESSION_ID, try use IMSDATA
                            char* id_end = tmp_sz + (sizeof IMSDATA_EQUAL);

                            while (id_end && isdigit(*id_end)) {
                                id_end ++;
                            }

                            if (id_end != NULL) {
                                char bkdata = *id_end;
                                *id_end = '\0';
                                int64_t ims_sid = atoll(tmp_sz + (sizeof IMSDATA_EQUAL));
                                *id_end = bkdata;

                                if (ims_sid != 0) {
                                    if (ims_mgr_t::get_instance()->get_map_session_id(ims_sid, event.sessionid)) {
                                        strncpy(event.name, "OPERATION_FAILED", LEN_64);
                                    }
                                }
                            }
                        }
                    }
                    //uuid
                    {
                        char* tmp_start = strstr(tmp, "origination_uuid=");

                        if (tmp_start) {
                            char* tmp_end = strstr(tmp_start, ",");

                            if (tmp_end) {
                                tmp_start += 17;

                                if (tmp_start && tmp_start < tmp_end) {
                                    strncpy(event.event_data.normal.other_uuid, tmp_start, tmp_end - tmp_start);
                                }
                            }
                        }
                    }
                } else {
                    ret = IVR_FAIL_TIMEOUT;
                    break;
                }
            }
            //过滤消息逻辑，以振铃事件为判断依据，
            //1）没有sessionid的振铃视为呼入，同时标记
            //2）有sessionid的振铃视为外呼后的振铃
            //3）其它事件根据uuid查询
            else if (0 == strcasecmp(event.name, "CHANNEL_PROGRESS_MEDIA") ||
                     0 == strcasecmp(event.name, "CHANNEL_PROGRESS")) {
                if (0 != event.sessionid &&
                        IvrInstanceManager::get_instance()->search_ivr_instance(event.sessionid)) {
                    IvrInstanceManager::get_instance()->add_uuid(event.sessionid, tmp_uuid);
                    IVR_DEBUG("ADD UUID SUCC: UUID= %s", tmp_uuid);
                } else {
                    if (!check_ivr_ip(getIP.c_str())) {
                        continue;
                    }
                }
            } else if (!IvrInstanceManager::get_instance()->check_uuid(tmp_uuid, event.sessionid)) {
                IVR_DEBUG("CHECK UUID FAIL: UUID= %s", tmp_uuid);
                continue;
            }

            //封装事件
            if (strcasecmp(event.name, "BACKGROUND_JOB") != 0) {
                get_head_val("Unique-ID", event.event_data.normal.uuid, LEN_64);
                get_head_val("Caller-Caller-ID-Number", event.event_data.normal.caller_no, LEN_64);
                get_head_val("Caller-Destination-Number", event.event_data.normal.called_no, LEN_64);
                get_head_val("Channel-Name", event.event_data.normal.channel_name, LEN_64);
                std::string deviceno;

                if (ivr_tools_t::chlname2no(event.event_data.normal.channel_name, deviceno)) {
                    strncpy(event.event_data.normal.deviceno, deviceno.c_str(), LEN_64);
                } else {
                    event.event_data.normal.deviceno[0] = '\0';
                }

                get_head_val("Other-Leg-Unique-ID", event.event_data.normal.other_uuid, LEN_64);
                get_head_val("Other-Leg-Caller-ID-Number", event.event_data.normal.other_caller_no, LEN_64);
                get_head_val("Other-Leg-Destination-Number", event.event_data.normal.other_called_no, LEN_64);
                get_head_val("Other-Leg-Channel-Name", event.event_data.normal.other_channel_name, LEN_64);
                deviceno = "";

                if ('\0' != event.event_data.normal.other_channel_name[0] &&
                        ivr_tools_t::chlname2no(event.event_data.normal.other_channel_name, deviceno)) {
                    strncpy(event.event_data.normal.other_deviceno, deviceno.c_str(), LEN_64);
                } else {
                    event.event_data.normal.other_deviceno[0] = '\0';
                }

                get_head_val("Application", event.event_data.normal.application, LEN_32);
                get_head_val("Application-Data", event.event_data.normal.application_data, LEN_64);
                get_head_val("Application-Response", event.event_data.normal.application_resp, LEN_128);
                get_head_val("Hangup-Cause", event.event_data.normal.reason, LEN_128);

                /*
                                if(IVR_SUCCESS == get_var("IVR_SESSION_ID",szcmd,LEN_512))
                                {
                                    event.sessionid=atoll(szcmd);
                                }
                */
                if (IVR_SUCCESS == get_head_val("Call-Direction", szcmd, LEN_512)) {
                    if (strcasecmp(szcmd, "outbound") == 0) {
                        event.event_data.normal.call_direction = FCD_OUTBOUND;
                    } else if (strcasecmp(szcmd, "inbound") == 0) {
                        event.event_data.normal.call_direction = FCD_INBOUND;
                    }
                }

                if (IVR_SUCCESS == get_head_val("Answer-State", szcmd, LEN_512)) {
                    if (strcasecmp(szcmd, "answered") == 0) {
                        event.event_data.normal.call_state = FCS_ANSWERED;
                    }

                    if (strcasecmp(szcmd, "early") == 0) {
                        event.event_data.normal.call_state = FCS_EARLY;
                    }

                    if (strcasecmp(szcmd, "ringing") == 0) {
                        event.event_data.normal.call_state = FCS_RING;
                    }
                }

                if (strcasecmp(event.name, "CUSTOM") == 0) {
                    char tmp[LEN_128 + 1] = {0};
                    get_head_val("Event-Subclass", tmp, LEN_128);

                    if (strcasecmp(tmp, "conference::maintenance") == 0) {
                        get_head_val("Action", tmp, LEN_128);

                        if (strcasecmp(tmp, "add-member") == 0) {
                            strncpy(event.name, "CONFERENCE_JOIN", LEN_64);
                            get_head_val("Member-ID", event.event_data.normal.ivr_data, LEN_128);
                        } else if (strcasecmp(tmp, "mute-member") == 0) {
                            strncpy(event.name, "CONFERENCE_MUTE", LEN_64);
                        } else if (strcasecmp(tmp, "unmute-member") == 0) {
                            strncpy(event.name, "CONFERENCE_UNMUTE", LEN_64);
                        } else {
                            ret = IVR_FAIL_TIMEOUT;
                            break;
                        }
                    } else {
                        ret = IVR_FAIL_TIMEOUT;
                        break;
                    }
                } else if (strcasecmp(event.name, "DTMF") == 0) {
                    get_head_val("DTMF-Digit", event.event_data.normal.ivr_data, LEN_128);
                } else if (strcasecmp(event.name, "RECORD_START") == 0
                           || strcasecmp(event.name, "RECORD_STOP") == 0) {
                    get_head_val("Record-File-Path", event.event_data.normal.ivr_data, LEN_128);

                    if (strlen(event.event_data.normal.ivr_data) > strlen(_recordbase)) {
                        char* ptmp = (char*)(event.event_data.normal.ivr_data) + strlen(_recordbase);

                        while (ptmp && *ptmp == '/') {
                            ++ ptmp;
                        }

                        std::string new_file = ptmp;
                        strncpy(event.event_data.normal.ivr_data, new_file.c_str(), LEN_128);
                    }
                } else if (0 == strcasecmp(event.name, "CHANNEL_EXECUTE_COMPLETE") &&
                           0 == strcasecmp(event.event_data.normal.application, "play_and_get_digits")) {
                    if (IVR_SUCCESS == get_var("BAIDU_CC_DATA", szcmd, LEN_512)) {
                        strncpy(event.event_data.normal.ivr_data, szcmd, LEN_128);
                    }

                }
            }


            std::ostringstream ostm;
            ostm << std::endl;
            ostm << "===========================FS EVENT============================" << std::endl;
            ostm << "ID            : " << _fs_no << std::endl;
            ostm << "Address       : " << _address << ":" << _port << std::endl;
            ostm << "Time          : " << event.timestamp << std::endl;
            ostm << "SessionID     : " << event.sessionid << std::endl;
            ostm << "IVRDATA       : " << event.event_data.normal.ivr_data << std::endl;
            ostm << "Name          : " << event.name << std::endl;
            ostm << "Type          : Normal" << std::endl;
            ostm << "Uuid          : " << event.event_data.normal.uuid << std::endl;;
            ostm << "CallerNo      : " << event.event_data.normal.caller_no << std::endl;;
            ostm << "CalledNo      : " << event.event_data.normal.called_no << std::endl;
            ostm << "ChannelName   : " << event.event_data.normal.channel_name << std::endl;
            ostm << "Direction     : " << event.event_data.normal.call_direction << std::endl;
            ostm << "CallState     : " << event.event_data.normal.call_state << std::endl;
            ostm << "App:          : " << event.event_data.normal.application << std::endl;
            ostm << "App_Data      : " << event.event_data.normal.application_data << std::endl;
            ostm << "App_Resp      : " << event.event_data.normal.application_resp << std::endl;
            ostm << "Other_Uuid    : " << event.event_data.normal.other_uuid << std::endl;
            ostm << "Other_Caller  : " << event.event_data.normal.other_caller_no << std::endl;
            ostm << "Other_Called  : " << event.event_data.normal.other_called_no << std::endl;
            ostm << "Other_Channel : " << event.event_data.normal.other_channel_name << std::endl;
            ostm << "Reason        : " << event.event_data.normal.reason << std::endl;
            ostm << "============================End Event============================" << std::endl;

            // com_writelog("fsevent","%s", ostm.str().c_str());
            BGCC_TRACE("fsevent", "%s", ostm.str().c_str());
        }

        ret = IVR_SUCCESS;
        break;
    }

    //链接是好都么
    if (is_handle_valid()) {
        ret = IVR_FAIL_TIMEOUT;
        break;
    } else {
        ret = IVR_FAIL_CONNECT;
        break;
    }

    FUNC_END();
}

///////////////////////////////////// EVENT END /////////////////////////////////////////////////



///////////////////////////////////// 呼叫 START /////////////////////////////////////////////////
int32_t fs_opr_t::originate(const char* ani, const char* dnis,
                            const char* caller_disp, const char* called_disp,
                            uint64_t sessionid, uint32_t timeout) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, CMD_ORIGINATE_FMT,
             caller_disp, caller_disp, sessionid, ani, called_disp, called_disp, timeout, sessionid, dnis);
    IVR_TRACE("originate(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
        break;
    } else {
        IVR_WARN("fs:originate(%s,%s,%s,%s,%u,%lu);ret(%s)",
                 ani, dnis, caller_disp, called_disp, timeout, sessionid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::bridge(const char* uuid, const char* called_disp, const char* dnis) {
    FUNC_BEGIN();

    if (set_channel_attribute(uuid, "bridge_early_media=true")
            && set_channel_attribute(uuid, "hangup_after_bridge=false")
            && set_channel_attribute(uuid, "bypass_media=false")
            && set_channel_attribute(uuid, "continue_on_fail=true")) {
        set_channel_attribute(uuid, "export_vars=IVR_SESSION_ID");
        snprintf(szcmd, LEN_512, "effective_caller_id_name=%s", called_disp);
        set_channel_attribute(uuid, szcmd);

        snprintf(szcmd, LEN_512, "effective_caller_id_number=%s", called_disp);
        set_channel_attribute(uuid, szcmd);

        if (esl_execute(&_handle, "bridge", dnis, uuid) == ESL_SUCCESS &&
                is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IVR_SUCCESS;
            break;
        } else {
            IVR_WARN("fs:bridge(%s,%s,%s);ret(%s)", uuid, called_disp, dnis, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::uuid_bridge(const char* uuid1, const char* uuid2, char* uuid_output,
                              uint32_t output_len) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, CMD_UUIDBRIDGE_FMT, uuid1, uuid2);
    IVR_TRACE("uuid_bridge(%s)", szcmd);

    if (set_channel_attribute(uuid1, "bypass_media=false") &&
            set_channel_attribute(uuid2, "bypass_media=false")) {
        if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
            if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
                fs_resp += 3;

                while (*fs_resp && ' ' == *fs_resp) {
                    fs_resp ++;
                }

                if (*fs_resp && uuid_output && output_len > 0) {
                    strncpy(uuid_output, fs_resp, output_len);
                    uint32_t idx = 0;

                    do {
                        if ('\n' == uuid_output[idx]) {
                            uuid_output[idx] = '\0';
                            break;
                        }

                        ++ idx;
                    } while (uuid_output[idx]);
                }

                ret = IVR_SUCCESS;
            } else {
                IVR_WARN("fs:uuid_bridge(%s,%s,%s);ret(%s)", uuid1, uuid2, uuid_output, fs_resp);
            }
        }
    } else {
        IVR_WARN("fs:uuid_bridge(%s,%s) failed(set channel attribute err)", uuid1, uuid2);
    }

    FUNC_END();
}

int32_t fs_opr_t::unbridge(const char* uuid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, CMD_UNBRIDGE_FMT, uuid);
    IVR_TRACE("uubridge(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:unbridge(%s);ret(%s)", uuid, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::answer(const char* uuid) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "answer", NULL, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:answer(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::hangup(const char* uuid, const char* cause) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "hangup", cause, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:hangup(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}
int32_t fs_opr_t::conference(const char* uuid, const char* name) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "conference", name, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:conference(%s,%s);ret(%s)", uuid, name, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::join_conference(const char* name, const char* dest_disp, const char* destno,
                                  CONF_MODE mode, uint64_t sessionid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, CMD_JOINCONFERENCE_FMT, dest_disp, dest_disp, sessionid, destno,
             name, ((CONF_LISTEN == mode) ? "+flags{mute}" : ""));
    IVR_TRACE("join_conference(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:join_conference(%s,%s,%s,%u,%lu);ret(%s)",
                     name, dest_disp, destno, mode, sessionid, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::unjoin_conference(const char* name, const char* uuid) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512,
             "api uuid_transfer %s -aleg 'set:hangup_after_bridge=false,set:park_after_bridge=true,park:' inline \n\n",
             uuid);
    IVR_TRACE("unjoin_conference(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:unjoin_conference(%s,%s);ret(%s)", name, uuid, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::conference_mute(const char* name, const char* member) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, "api conference %s mute %s\n\n", name, member);
    IVR_TRACE("conference_mute(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:conference_mute (%s,%s);ret(%s)", name, member, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::conference_unmute(const char* name, const char* member) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, "api conference %s unmute %s\n\n", name, member);
    IVR_TRACE("conference_unmute(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:conference_unmute (%s,%s);ret(%s)", name, member, fs_resp);
        }
    }

    FUNC_END();

}

int32_t fs_opr_t::bridgeonly(const char* uuid1, const char* uuid2) {
    FUNC_BEGIN();
    (void)fs_resp;
    snprintf(szcmd, LEN_512, "%s %s %s%s", CMD_BRIDGE, uuid1, uuid2, CMD_END);

    if (esl_execute(&_handle, CMD_SET, "bypass_media=false", uuid1) == ESL_SUCCESS
            && check_result(esl_event_get_header(_handle.last_sr_event, REPLY_TEXT))
            && esl_execute(&_handle, CMD_SET, "bypass_media=false", uuid2) == ESL_SUCCESS
            && check_result(esl_event_get_header(_handle.last_sr_event, REPLY_TEXT))
            && esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        const char* resp = esl_event_get_body(_handle.last_sr_event);

        if (check_result(resp)) {
            std::string callid = resp + 4;
            callid.erase(callid.find_last_not_of("\n") + 1);

            if (strcasecmp(callid.c_str(), uuid2) == 0) {
                ret = IVR_SUCCESS;
            }
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::bridgeex(const char* uuid, const char* caller, const char* called,
                           bool external, bool usbgm, const char* bgmfile) {
    FUNC_BEGIN();
    (void)fs_resp;
    ostringstream ostm;

    if (external) {
        ostm << "sofia/external/" << called;
    } else {
        ostm << "user/" << called;
    }

    if (usbgm) {
        snprintf(szcmd, LEN_512, "ringback=${sounds_dir}/%s", bgmfile);

        if (!set_channel_attribute(uuid, szcmd)) {
            break;
        }
    } else {
        if (!set_channel_attribute(uuid, "bridge_early_media=true")) {
            break;
        }
    }

    if (set_channel_attribute(uuid, "hangup_after_bridge=false") &&
            set_channel_attribute(uuid, "bypass_media=false") &&
            set_channel_attribute(uuid, "continue_on_fail=true")) {
        set_channel_attribute(uuid, "export_vars=IVR_SESSION_ID");
        //set_channel_attribute(uuid,"export_vars=IVRDATA");

        snprintf(szcmd, LEN_512, "effective_caller_id_name=%s", caller);
        set_channel_attribute(uuid, szcmd);

        snprintf(szcmd, LEN_512, "effective_caller_id_number=%s", caller);
        set_channel_attribute(uuid, szcmd);

        //snprintf(szcmd,LEN_512,"effective_caller_id_number=%s",caller);
        //if(esl_send_recv(&_handle,szcmd)==ESL_SUCCESS  &&
        //        is_result_ok(fs_resp=esl_event_get_header(_handle.last_sr_event,"Reply-Text")))
        //{
        if (esl_execute(&_handle, "bridge", ostm.str().c_str(), uuid) == ESL_SUCCESS &&
                is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IVR_SUCCESS;
            break;
        } else {
            IVR_WARN("fs:bridge(%s,%s);ret(%s)", uuid, ostm.str().c_str(), fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::dial(ivr_session_id_t sessionid, const char* called_number,
                       const char* caller_number, uint32_t timeout, bool external) {
    FUNC_BEGIN();
    (void)fs_resp;
    //if (handle) {
    snprintf(szcmd, LEN_512, "%s %s", CMD_CREATE_UUID, CMD_END);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        const char* resp = esl_event_get_body(_handle.last_sr_event);
        std::string callid = resp;
        callid.erase(callid.find_last_not_of("\n") + 1);
        IVR_TRACE("CREATE_UUID:%s", callid.c_str());

        snprintf(szcmd, LEN_512,
                 "%s {return_ring_ready=true,originate_timeout=%u,origination_uuid=%s,IVR_SESSION_ID=%lu}%s%s &park() %s %s %s %s %u %s",
                 CMD_DIAL, timeout, callid.c_str(), sessionid, external ? "sofia/external/" : "user/",
                 called_number, CMD_UNDEF, CMD_UNDEF,
                 caller_number, caller_number, timeout,
                 CMD_END);

        if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS &&
                is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IVR_SUCCESS;
            break;
        } else {
            IVR_WARN("fs:originate(%s, %s, %u, %i);ret(%s)",
                     called_number, caller_number, timeout, external, fs_resp);
        }
    } else {
        IVR_WARN("fs:originate(%s, %s, %u, %i);ret(%s)",
                 called_number, caller_number, timeout, external, fs_resp);
    }

    //}
    FUNC_END();
}

///////////////////////////////////// 呼叫 END /////////////////////////////////////////////////


/////////////////////////////////////媒体START/////////////////////////////////////////////////
int32_t fs_opr_t::collect(const char* callid, const char* playfile, uint32_t min, uint32_t max,
                          uint32_t timeout, const char* end) {
    FUNC_BEGIN();
    (void)fs_resp;
    (void)szcmd;
    ostringstream ostm;
    ostm << min << " " << max << " " << playfile << " " << FS_VAR_TMP << " " << timeout * 1000 << " " <<
         end;

    // stop media first
    if (esl_execute(&_handle, "break", NULL, callid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text")) &&
            esl_execute(&_handle, CMD_COLLECT, ostm.str().c_str(), callid) == ESL_SUCCESS &&
            check_result(esl_event_get_header(_handle.last_sr_event, REPLY_TEXT))) {
        ret = IVR_SUCCESS;
    }

    FUNC_END();
}

int32_t fs_opr_t::play_and_get_digits(const char* callid, const char* playfile, uint32_t min,
                                      uint32_t max,
                                      uint32_t repeat, uint32_t timeout, const char* end, const char* invalidfile) {
    FUNC_BEGIN();
    ostringstream ostm;

    (void)fs_resp;
    (void)szcmd;
    ostm << min << " " << max << " " << repeat << " " << timeout * 1000 << " " << end << " ";
    ostm << playfile << " " << invalidfile << " " << FS_VAR_TMP << "\nevent-lock: true\n" ;

    if (esl_execute(&_handle, CMD_FLUSH_DTMF, NULL, callid) == ESL_SUCCESS &&
            check_result(esl_event_get_header(_handle.last_sr_event, REPLY_TEXT)) &&
            esl_execute(&_handle, "break", NULL, callid) == ESL_SUCCESS  &&//stop before play
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text")) &&
            esl_execute(&_handle, CMD_PLAY_WITH_COLLECT, ostm.str().c_str(), callid) == ESL_SUCCESS &&
            check_result(esl_event_get_header(_handle.last_sr_event, REPLY_TEXT))) {
        ret = IVR_SUCCESS;
    }

    FUNC_END();
}

int32_t fs_opr_t::stop_media(const char* uuid) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "break", NULL, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:stop_media(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::play(const char* uuid, const char* file, uint32_t count) {
    FUNC_BEGIN();
    (void)szcmd;

    if (set_channel_attribute(uuid, "playback_terminators=none") &&
            set_channel_attribute(uuid, "playback_delimiter=&") &&
            esl_execute(&_handle, "break", NULL, uuid) == ESL_SUCCESS && //stop before play
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text")) &&
            esl_execute(&_handle, "playback", file, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:play(%s,%s,%u);ret(%s)", uuid, file, count, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::send_dtmf(const char* uuid, const char* keys) {
    FUNC_BEGIN();
    (void)szcmd;

    //snprintf(szcmd,LEN_512,CMD_UUIDSENDDTMF_FMT,uuid,keys);
    //IVR_TRACE("send_dtmf(%s)",szcmd);
    //if(esl_send_recv(&_handle,szcmd)==ESL_SUCCESS){
    if (esl_execute(&_handle, "send_dtmf", keys, uuid) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {

        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs:send_dtmf(%s,%s);ret(%s)", uuid, keys, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::record(const char* uuid, const char* file, bool isstart) {
    FUNC_BEGIN();

    std::string full_file = _recordbase;
    full_file += "/";
    full_file += file;

    IVR_TRACE("fs::record %s(%s)", isstart ? "start" : "stop", full_file.c_str());
    set_channel_attribute(uuid, "playback_terminators=none");
    set_channel_attribute(uuid, "RECORD_HANGUP_ON_ERROR=false");//1.0.7的fs才有
    set_channel_attribute(uuid, "RECORD_MIN_SEC=0");

    if (isstart) {
        snprintf(szcmd, LEN_512, CMD_RECORD_FMT, uuid, full_file.c_str());
    } else {
        snprintf(szcmd, LEN_512, CMD_STOPRECORD_FMT, uuid);
    }

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IVR_SUCCESS;
        } else {
            IVR_WARN("fs:record %s(%s,%s);ret(%s)", uuid,
                     isstart ? "start" : "stop", full_file.c_str(), fs_resp);
        }
    } else {
        IVR_WARN("fs:record %s(%s,%s) esl_send_recv != ESL_SUCCESS",
                 uuid, isstart ? "start" : "stop", full_file.c_str());
    }

    FUNC_END();
}

int32_t fs_opr_t::eval(const char* key, char* val, uint32_t val_len) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, "api eval %s\n\n", key);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        fs_resp = esl_event_get_body(_handle.last_sr_event);
        strncpy(val, fs_resp, val_len);
        ret = IVR_SUCCESS;
    } else {
        IVR_WARN("fs_eval(%s) failed", "test");
    }

    FUNC_END();
}

int32_t fs_opr_t::playnum(const char* uuid, const char* data, const char* basepath, bool isStr) {
    FUNC_BEGIN();
    (void)szcmd;
    (void)fs_resp;

    if (isStr) {
        string playstr = string(data);
        IVR_DEBUG("playstr:[%s]", data);
        string playlist = "";
        uint32_t i = 0;

        for (i = 0; i < playstr.size(); i ++) {
            playlist = playlist + basepath + "system/num" + data[i] + ".wav&";
        }

        if (play(uuid, playlist.c_str()) != IVR_SUCCESS) {
            IVR_TRACE("%s,放音失败[%s]", uuid, playlist.c_str());
        }

        ret = IVR_SUCCESS;
    } else {
        uint32_t tmp = atoi(data);
        string strNumber;
        //Get the int without 0 at the head
        std::ostringstream ostm;
        ostm.str("");
        ostm << tmp;
        strNumber = ostm.str();

        uint32_t numLength = strNumber.size();
        IVR_TRACE("STARS tmp:%u; str:%s; len:%u", tmp, strNumber.c_str(), numLength);
        string playlist = "";

        for (uint32_t i = 0; i < numLength; i++) {
            uint32_t small = (numLength - i - 1) % 4;
            uint32_t big   = (numLength - i - 1) / 4;
            bool zerotag = false;

            if (small == 0) {
                if (strNumber.at(i) != '0') {
                    if (zerotag) {
                        playlist = playlist + basepath + "system/num0.wav&";
                    }

                    playlist = playlist + basepath + "system/num" + strNumber.at(i) + ".wav&";
                }

                zerotag = false;

                if (big > 0) {
                    char tmp = '4' + big;
                    playlist = playlist + basepath + "system/dimension" + tmp + ".wav&";
                }
            } else {
                if (strNumber.at(i) == '0') {
                    zerotag = true;
                } else {
                    if (zerotag) {
                        playlist = playlist + basepath + "system/num0.wav&";
                    }

                    playlist = playlist + basepath + "system/num" + strNumber.at(i) + ".wav&";
                    char tmp = '0' + small;
                    playlist = playlist + basepath + "system/dimension" + tmp + ".wav&";
                }
            }
        }

        //Play the number
        if (play(uuid, playlist.c_str()) != IVR_SUCCESS) {
            IVR_TRACE("%s,放音失败[%s]", uuid, playlist.c_str());
        }

        ret = IVR_SUCCESS;
    }

    FUNC_END();
}

/////////////////////////////////////媒体 END /////////////////////////////////////////////////

/////////////////////////////////////其他 START/////////////////////////////////////////////////

int32_t fs_opr_t::get_var(const char* key, char* val, uint32_t val_len) {
    FUNC_BEGIN();
    (void)fs_resp;
    snprintf(szcmd, LEN_512, "variable_%s", key);
    ret = get_head_val(szcmd, val, val_len);
    FUNC_END();
}

int32_t fs_opr_t::get_head_val(const char* key, char* val, uint32_t val_len) {
    int32_t ret = IVR_FAIL_NOTEXISTS;

    if (key && _handle.last_ievent) {
        const char* fs_resp = esl_event_get_header(_handle.last_ievent, key);

        if (val && fs_resp) {
            strncpy(val, fs_resp, val_len);
            //esl_url_decode(val);
            ret = IVR_SUCCESS;
        }
    }

    return ret;
}

/////////////////////////////////////其他 END  /////////////////////////////////////////////////


bool fs_opr_t::check_result(const char* result) {
    if (result) {
        return (strlen(result) >= 3 && strncasecmp(RESULT_OK, result, 3) == 0);
    }

    return false;
}

const char* fs_opr_t::CMD_JOINCONFERENCE_FMT =
    "bgapi originate {return_ring_ready=false,bridge_early_media=true,bypass_media=false"
    "origination_caller_id_number=%s,origination_caller_id_name=%s,IVRDATA=%llu}%s "
    "&conference(%s%s)\n\n";
//"effective_caller_id_number=%s,effective_caller_id_name=%s,IVRDATA=%llu}%s "
const char* fs_opr_t::CMD_UUIDBRIDGE_FMT = "api uuid_bridge %s %s\n\n";
const char* fs_opr_t::CMD_UNBRIDGE_FMT =
    "api uuid_transfer  %s -both 'set:hangup_after_bridge=false,set:park_after_bridge=true,park:' inline\n\n";
const char* fs_opr_t::CMD_UUIDSENDDTMF_FMT = "api uuid_send_dtmf %s %s\n\n";
const char* fs_opr_t::CMD_ORIGINATE_FMT =
    "bgapi originate {return_ring_ready=false,bridge_early_media=true,bypass_media=false,"
    "origination_caller_id_number=%s,origination_caller_id_name=%s,IVRDATA=%llu}%s "
    "&bridge([origination_caller_id_number=%s,origination_caller_id_name=%s,call_timeout=%u,IVRDATA=%llu]%s)\n\n";

const char* fs_opr_t::CMD_RECORD_FMT = "api uuid_record %s start %s\n\n";
const char* fs_opr_t::CMD_STOPRECORD_FMT = "api uuid_record %s stop all\n\n";

const char* fs_opr_t::EVENT_NORMAL = "DTMF CHANNEL_ANSWER CHANNEL_HANGUP CHANNEL_DESTROY "
                                     "CHANNEL_EXECUTE CHANNEL_EXECUTE_COMPLETE CHANNEL_BRIDGE CHANNEL_UNBRIDGE CHANNEL_PROGRESS CHANNEL_PROGRESS_MEDIA "
                                     "BACKGROUND_JOB CHANNEL_ORIGINATE RECORD_START RECORD_STOP CUSTOM conference::maintenance";
const char* fs_opr_t::EVENT_HEARTBEAT = "HEARTBEAT";
const char* fs_opr_t::RECORD_BASEDIR = "${sounds_dir}";


const char* fs_opr_t::CMD_BRIDGE = "api uuid_bridge";
const char* fs_opr_t::CMD_END = "\n\n";
const char* fs_opr_t::CMD_BRIDGEEX = "bridge";
const char* fs_opr_t::CMD_SET = "set";
const char* fs_opr_t::CMD_CREATE_UUID = "api create_uuid";
const char* fs_opr_t::RESULT_OK = "+ok";
const char* fs_opr_t::REPLY_TEXT = "Reply-Text";
const char* fs_opr_t::CMD_DIAL = "bgapi originate ";
const char* fs_opr_t::CMD_UNDEF = "undef";
const char* fs_opr_t::FS_VAR_TMP = "BAIDU_CC_DATA";
const char* fs_opr_t::CMD_COLLECT = "read";
const char* fs_opr_t::CMD_FLUSH_DTMF = "flush_dtmf";
const char* fs_opr_t::CMD_PLAY_WITH_COLLECT = "play_and_get_digits";

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
