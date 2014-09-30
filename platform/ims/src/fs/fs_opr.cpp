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
#include "ims_log.h"
#include "ims_tool.h"

int32_t fs_opr_t::connect(uint32_t address, int32_t port, const char* pswd, bool reconnect) {
    int32_t ret = IMS_FAIL_CONNECT;
    char ip[sizeof "255.255.255.255"];

    if (reconnect) {
        disconnect();
        ims_tool_t::inet_ntop(address, ip, sizeof "255.255.255.255");

        if (esl_connect(&_handle, ip, _port, NULL, _pswd) == ESL_SUCCESS) {
            TRACE_LOG("reconnect to FreeSWITCH [%s:%d] success", ip, _port);
            eval(RECORD_BASEDIR, _recordbase, LEN_256);
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("reconnect to FreeSWITCH [%s:%d] failed(%s)", ip, _port, _handle.err);
        }
    } else {
        if (is_handle_valid()) {
            return IMS_SUCCESS;
        }

        strncpy(_pswd, pswd, LEN_16);
        _address = address;
        _port = port;

        ims_tool_t::inet_ntop(address, ip, sizeof "255.255.255.255");

        if (esl_connect(&_handle, ip, _port, NULL, _pswd) == ESL_SUCCESS) {
            TRACE_LOG("connect to FreeSWITCH [%s:%d] success", ip, _port);
            eval(RECORD_BASEDIR, _recordbase, LEN_256);
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("connect to FreeSWITCH [%s:%d] failed(%s)", ip, _port, _handle.err);
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

int32_t fs_opr_t::mark_sessionid(const char* uuid, uint64_t sid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, "IMSDATA=%lu", sid);

    if (set_channel_attribute(uuid, szcmd)
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs_opr:mark_sessionid(%s,%lu);ret(%s)", uuid, sid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::uuid_exists(const char* uuid) {
    FUNC_BEGIN();
    const char* uuid_exists = "api uuid_exists %s";
    snprintf(szcmd, LEN_512, uuid_exists, uuid);
    TRACE_LOG("uuid_exists(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        fs_resp = esl_event_get_body(_handle.last_sr_event);

        if (fs_resp && strncasecmp(fs_resp, "true", 4) == 0) {
            TRACE_LOG("uuid=%s exists.", uuid);
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:uuid=%s not exists;ret(%s)", uuid, fs_resp);
        }
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
        TRACE_LOG("subscribe_event %s success", event);
        ret = IMS_SUCCESS;
        break;
    } else {
        WARNING_LOG("subscribe_event %s failed(connect err)", event);
        ims_tool_t::safe_sleepms(20);
    }

    /*
    if(is_handle_valid()){
        ret=IMS_FAIL_TIMEOUT;
        break;
    }
    else if(IMS_SUCCESS!=connect(_address,_port,_pswd,true)){
        WARNING_LOG("subscribe_event %s failed(connect err)",event);
        ret=IMS_FAIL_CONNECT;
        break;
    }
    */

    FUNC_END();
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
    //if(esl_recv_event_timed(&_handle, timeout, 1, NULL)==ESL_SUCCESS){
    //使用带超时的接口会导致获取的fsevent事件内容为空，具体原因未知
    if (esl_recv_event_timed(&_handle, 0, 1, NULL) == ESL_SUCCESS) {
        event.timestamp = 0;
        //拷贝事件到event中
        get_head_val("Event-Name", event.name, LEN_64);

        if (IMS_SUCCESS == get_head_val("Event-Date-Timestamp", szcmd, LEN_512)) {
            event.timestamp = atoll(szcmd);
        } else {
            WARNING_LOG("get head_val Event-Date-Timestamp failed.!");
        }

        if (strcasecmp(event.name, "HEARTBEAT") == 0) {
            event.datatype = EDT_HEARTBEAT;

            if (IMS_SUCCESS == get_head_val("Session-Since-Startup", szcmd, LEN_512)) {
                event.event_data.heartbeat.all_session = (uint32_t)atoi(szcmd);
            }

            if (IMS_SUCCESS == get_head_val("Session-Count", szcmd, LEN_512)) {
                event.event_data.heartbeat.cur_session = (uint32_t)atoi(szcmd);
            }

            if (IMS_SUCCESS == get_head_val("Idle-CPU", szcmd, LEN_512)) {
                event.event_data.heartbeat.cpu_idle = (uint32_t)atoi(szcmd);
            }
        } else {
            event.datatype = EDT_NORMAL;
            event.event_data.normal.call_direction = FCD_UNKNOWN;
            event.event_data.normal.call_state = FCS_UNKNOWN;

            if (strcasecmp(event.name, "BACKGROUND_JOB") == 0) {
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

                        fs_tmp++;
                    }

                    char tmp[LEN_512 + 1] = {0};
                    get_head_val("Job-Command-Arg", tmp, LEN_512);

                    {
                        //uuid_record error
                        char cmd[LEN_512 + 1] = {0};
                        get_head_val("Job-Command", cmd, LEN_512);
                        DEBUG_LOG("BACKGROUND_JOB: Job-Command(=%s)", cmd);

                        if (0 == strncasecmp(cmd, "uuid_record", 11)) {
                            WARNING_LOG("uuid_record failed, command-arg(=%s)", tmp);
                            continue;
                        }
                    }

                    {
                        char* tmp_start = strstr(tmp, "}");

                        if (tmp_start) {
                            char* tmp_end = strstr(tmp_start, " ");

                            if (tmp_end && tmp_end > tmp_start) {
                                strncpy(event.event_data.normal.channel_name, tmp_start + 1, tmp_end - tmp_start - 1);
                            }
                        }

                    }

                    {
                        char* tmp_sz = strstr(tmp, "IMSDATA=");

                        if (tmp_sz) {
                            tmp_sz += 8;
                            char* id_end = tmp_sz;

                            while (id_end && isdigit(*id_end)) {
                                id_end++;
                            }

                            if (id_end) {
                                *id_end = '\0';
                                event.sessionid = atoll(tmp_sz);
                                strncpy(event.name, "OPERATION_FAILED", LEN_64);
                            }
                        }
                    }
                } else {
                    ret = IMS_FAIL_TIMEOUT;
                    break;
                }
            } else {
                get_head_val("Unique-ID", event.event_data.normal.uuid, LEN_64);
                get_head_val("Caller-Caller-ID-Number", event.event_data.normal.caller_no, LEN_64);
                get_head_val("Caller-Destination-Number", event.event_data.normal.called_no, LEN_64);
                get_head_val("Channel-Name", event.event_data.normal.channel_name, LEN_64);
                std::string deviceno;

                if (ims_tool_t::chlname2no(event.event_data.normal.channel_name, deviceno)) {
                    strncpy(event.event_data.normal.deviceno, deviceno.c_str(), LEN_64);
                } else {
                    event.event_data.normal.deviceno[0] = '\0';
                }

                get_head_val("Other-Leg-Unique-ID", event.event_data.normal.other_uuid, LEN_64);
                get_head_val("Other-Leg-Caller-ID-Number", event.event_data.normal.other_caller_no, LEN_64);
                get_head_val("Other-Leg-Destination-Number", event.event_data.normal.other_called_no, LEN_64);
                get_head_val("Other-Leg-Channel-Name", event.event_data.normal.other_channel_name, LEN_64);
                deviceno = "";

                if ('\0' != event.event_data.normal.other_channel_name[0]
                        && ims_tool_t::chlname2no(event.event_data.normal.other_channel_name, deviceno)) {
                    strncpy(event.event_data.normal.other_deviceno, deviceno.c_str(), LEN_64);
                } else {
                    event.event_data.normal.other_deviceno[0] = '\0';
                }

                get_head_val("Application", event.event_data.normal.application, LEN_32);
                get_head_val("Application-Data", event.event_data.normal.application_data, LEN_64);
                get_head_val("Application-Response", event.event_data.normal.application_resp, LEN_128);
                get_head_val("Hangup-Cause", event.event_data.normal.reason, LEN_128);

                if (IMS_SUCCESS == get_var("IMSDATA", szcmd, LEN_512)) {
                    event.sessionid = atoll(szcmd);
                } else {
                    event.sessionid = 0;
                }

                if (IMS_SUCCESS == get_head_val("Call-Direction", szcmd, LEN_512)) {
                    if (strcasecmp(szcmd, "outbound") == 0) {
                        event.event_data.normal.call_direction = FCD_OUTBOUND;
                    } else if (strcasecmp(szcmd, "inbound") == 0) {
                        event.event_data.normal.call_direction = FCD_INBOUND;
                    }
                }

                if (IMS_SUCCESS == get_head_val("Answer-State", szcmd, LEN_512)) {
                    if (strcasecmp(szcmd, "answered") == 0) {
                        event.event_data.normal.call_state = FCS_ANSWERED;
                    } else if (strcasecmp(szcmd, "early") == 0) {
                        event.event_data.normal.call_state = FCS_EARLY;
                    } else if (strcasecmp(szcmd, "ringing") == 0) {
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
                            get_head_val("Member-ID", event.event_data.normal.ims_data, LEN_128);
                        } else if (strcasecmp(tmp, "mute-member") == 0) {
                            strncpy(event.name, "CONFERENCE_MUTE", LEN_64);
                        } else if (strcasecmp(tmp, "unmute-member") == 0) {
                            strncpy(event.name, "CONFERENCE_UNMUTE", LEN_64);
                        } else {
                            ret = IMS_FAIL_TIMEOUT;
                            break;
                        }
                    } else {
                        ret = IMS_FAIL_TIMEOUT;
                        break;
                    }
                } else if (strcasecmp(event.name, "RECORD_START") == 0) {
                    get_head_val("Record-File-Path", event.event_data.normal.ims_data, LEN_128);

                    if (strlen(event.event_data.normal.ims_data) > strlen(_recordbase)) {
                        char* ptmp = (char*)(event.event_data.normal.ims_data) + strlen(_recordbase);

                        while (ptmp && *ptmp == '/') {
                            ++ptmp;
                        }

                        std::string new_file = ptmp;
                        strncpy(event.event_data.normal.ims_data, new_file.c_str(), LEN_128);
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
            ostm << "IMSDATA       : " << event.event_data.normal.ims_data << std::endl;
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

            BGCC_TRACE("fsevent", "%s", ostm.str().c_str());
        }

        ret = IMS_SUCCESS;
        break;
    }

    //链接是好都么
    if (is_handle_valid()) {
        ret = IMS_FAIL_TIMEOUT;
        break;
    } else { // if(IMS_SUCCESS!=connect(_address,_port,_pswd,true)){
        WARNING_LOG("recv event failed(connect err)");
        ret = IMS_FAIL_CONNECT;
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
    TRACE_LOG("originate(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
        break;
    } else {
        WARNING_LOG("fs:originate(%s,%s,%s,%s,%u,%lu);ret(%s)", ani, dnis, caller_disp, called_disp,
                    timeout, sessionid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::single_originate(const char* ani, const char* caller_disp,
                                   uint64_t sessionid, bool return_ring_ready, bool bgapi,
                                   char* uuid_output, uint32_t output_len,
                                   char* result, uint32_t result_len) {
    FUNC_BEGIN();
    const char* originate = "%s originate {return_ring_ready=%s,origination_caller_id_number=%s,"
                            "origination_caller_id_name=%s,IMSDATA=%lu}%s &park()";
    const char* ring_ready = return_ring_ready ? "true" : "false";
    const char* api_type = bgapi ? "bgapi" : "api";
    snprintf(szcmd, LEN_512, originate, api_type, ring_ready, caller_disp, caller_disp, sessionid, ani);
    TRACE_LOG("originate(%s)", szcmd);

    if (bgapi && esl_send_recv(&_handle, szcmd) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
        break;
    }

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            TRACE_LOG("fs_resp=(%s)", fs_resp);
            fs_resp += 3;

            while (*fs_resp && ' ' == *fs_resp) {
                fs_resp++;
            }

            if (*fs_resp && uuid_output && output_len > 0) {
                strncpy(uuid_output, fs_resp, output_len);
                uint32_t idx = 0;

                do {
                    if ('\n' == uuid_output[idx]) {
                        uuid_output[idx] = '\0';
                        break;
                    }

                    ++idx;
                } while (uuid_output[idx]);
            }

            //TRACE_LOG("new create uuid = %s",uuid_output);
            ret = IMS_SUCCESS;
        } else {
            TRACE_LOG("fs_resp=(%s)", fs_resp);

            if (fs_resp && *fs_resp && result && result_len > 0) {
                strncpy(result, fs_resp + 5, result_len);
                uint32_t idx = 0;

                do {
                    if ('\n' == result[idx]) {
                        result[idx] = '\0';
                        break;
                    }

                    ++idx;
                } while (result[idx]);
            }

            WARNING_LOG("fs:single_originate(%s) failed;ret(%s)", ani, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::bridge(const char* uuid, const char* called_disp, const char* dnis) {
    FUNC_BEGIN();

    if (set_channel_attribute(uuid, "bridge_early_media=true")
            && set_channel_attribute(uuid, "hangup_after_bridge=false")
            && set_channel_attribute(uuid, "bypass_media=false")
            && set_channel_attribute(uuid, "playback_terminators=none")
            && set_channel_attribute(uuid, "continue_on_fail=true")) {
        set_channel_attribute(uuid, "export_vars=IMSDATA");
        snprintf(szcmd, LEN_512, "effective_caller_id_name=%s", called_disp);
        set_channel_attribute(uuid, szcmd);
        snprintf(szcmd, LEN_512, "effective_caller_id_number=%s", called_disp);
        set_channel_attribute(uuid, szcmd);

        if (esl_execute(&_handle, "bridge", dnis, uuid) == ESL_SUCCESS &&
                is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IMS_SUCCESS;
            break;
        } else {
            WARNING_LOG("fs:bridge(%s,%s,%s);ret(%s)", uuid, called_disp, dnis, fs_resp);
        }

    }

    FUNC_END();
}

int32_t fs_opr_t::bridge_ex(const char* uuid, const char* called_disp, const char* dnis,
                            bool isAsync, bool return_ring_ready) {
    FUNC_BEGIN();

    if (set_channel_attribute(uuid, "bridge_early_media=true")
            && set_channel_attribute(uuid, "hangup_after_bridge=false")
            && set_channel_attribute(uuid, "bypass_media=false")
            && set_channel_attribute(uuid, "playback_terminators=none")
            && set_channel_attribute(uuid, "continue_on_fail=true")) {
        set_channel_attribute(uuid, "export_vars=IMSDATA");
        snprintf(szcmd, LEN_512, "effective_caller_id_name=%s", called_disp);
        set_channel_attribute(uuid, szcmd);
        snprintf(szcmd, LEN_512, "effective_caller_id_number=%s", called_disp);
        set_channel_attribute(uuid, szcmd);

        //char param[LEN_512+1]={0};
        //snprintf(param, LEN_512, "[return_ring_ready=%s]%s", return_ring_ready ? "true" : "false", dnis);

        esl_status_t esl_ret = ESL_GENERR;

        TRACE_LOG("before bridge %s", isAsync ? "async" : "sync");

        if (isAsync) {
            int async = _handle.async_execute;
            _handle.async_execute = 1;
            esl_ret = esl_execute(&_handle, "bridge", dnis, uuid);
            _handle.async_execute = async;
        } else {
            esl_ret = esl_execute(&_handle, "bridge", dnis, uuid);
        }

        TRACE_LOG("after bridge %s", isAsync ? "async" : "sync");

        if (esl_ret == ESL_SUCCESS &&
                is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IMS_SUCCESS;
            break;
        } else {
            WARNING_LOG("fs:bridge(%s,%s,%s,%s);ret(%s)", uuid, called_disp, dnis, fs_resp,
                        isAsync ? "async" : "sync");
        }

    }

    FUNC_END();
}

int32_t fs_opr_t::uuid_bridge(const char* uuid1, const char* uuid2, char* uuid_output,
                              uint32_t output_len) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, CMD_UUIDBRIDGE_FMT, uuid1, uuid2);
    TRACE_LOG("uuid_bridge(%s)", szcmd);

    if (set_channel_attribute(uuid1, "bypass_media=false") &&
            set_channel_attribute(uuid2, "bypass_media=false")) {
        if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
            if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
                fs_resp += 3;

                while (*fs_resp && ' ' == *fs_resp) {
                    fs_resp++;
                }

                if (*fs_resp && uuid_output && output_len > 0) {
                    strncpy(uuid_output, fs_resp, output_len);
                    uint32_t idx = 0;

                    do {
                        if ('\n' == uuid_output[idx]) {
                            uuid_output[idx] = '\0';
                            break;
                        }

                        ++idx;
                    } while (uuid_output[idx]);
                }

                ret = IMS_SUCCESS;
            } else {
                WARNING_LOG("fs:uuid_bridge(%s,%s,%s);ret(%s)", uuid1, uuid2, uuid_output, fs_resp);
            }
        }
    } else {
        WARNING_LOG("fs:uuid_bridge(%s,%s) failed(set channel attribute err)", uuid1, uuid2);
    }

    FUNC_END();
}

int32_t fs_opr_t::unbridge(const char* uuid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, CMD_UNBRIDGE_FMT, uuid);
    TRACE_LOG("unbridge(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:unbridge(%s);ret(%s)", uuid, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::answer(const char* uuid) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "answer", NULL, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:answer(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::hangup(const char* uuid, const char* cause) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "hangup", cause, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:hangup(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}
int32_t fs_opr_t::conference(const char* uuid, const char* name) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "conference", name, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:conference(%s,%s);ret(%s)", uuid, name, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::join_conference(const char* name, const char* dest_disp, const char* destno,
                                  CONF_MODE mode, uint64_t sessionid) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, CMD_JOINCONFERENCE_FMT, dest_disp, dest_disp, sessionid, destno, name,
             ((CONF_LISTEN == mode) ? "+flags{mute}" : ""));
    TRACE_LOG("join_conference(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:join_conference(%s,%s,%s,%u,%lu);ret(%s)", name, dest_disp, destno, mode, sessionid,
                        fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::unjoin_conference(const char* name, const char* uuid) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512,
             "api uuid_transfer %s -aleg 'set:hangup_after_bridge=false,set:park_after_bridge=true,park:' inline \n\n",
             uuid);
    TRACE_LOG("unjoin_conference(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:unjoin_conference(%s,%s);ret(%s)", name, uuid, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::conference_mute(const char* name, const char* member) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, "api conference %s mute %s\n\n", name, member);
    TRACE_LOG("conference_mute(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:conference_mute (%s,%s);ret(%s)", name, member, fs_resp);
        }
    }

    FUNC_END();
}

int32_t fs_opr_t::conference_unmute(const char* name, const char* member) {
    FUNC_BEGIN();

    snprintf(szcmd, LEN_512, "api conference %s unmute %s\n\n", name, member);
    TRACE_LOG("conference_unmute(%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS) {
        if (is_result_ok(fs_resp = esl_event_get_body(_handle.last_sr_event))) {
            ret = IMS_SUCCESS;
        } else {
            WARNING_LOG("fs:conference_unmute (%s,%s);ret(%s)", name, member, fs_resp);
        }
    }

    FUNC_END();

}

///////////////////////////////////// 呼叫 END /////////////////////////////////////////////////


/////////////////////////////////////媒体START/////////////////////////////////////////////////
int32_t fs_opr_t::stop_media(const char* uuid) {
    FUNC_BEGIN();
    (void)szcmd;

    if (esl_execute(&_handle, "break", NULL, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:stop_media(%s);ret(%s)", uuid, fs_resp);
    }

    FUNC_END();
}
int32_t fs_opr_t::play(const char* uuid, const char* file, uint32_t count) {
    FUNC_BEGIN();
    (void)szcmd;

    if (set_channel_attribute(uuid, "playback_terminators=none")
            && esl_execute(&_handle, "playback", file, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
        TRACE_LOG("fs:play(%s,%s,%u) success.", uuid, file, count);
    } else {
        WARNING_LOG("fs:play(%s,%s,%u);ret(%s)", uuid, file, count, fs_resp);
    }

    FUNC_END();
}
int32_t fs_opr_t::send_dtmf(const char* uuid, const char* keys) {
    FUNC_BEGIN();
    (void)szcmd;

    //snprintf(szcmd,LEN_512,CMD_UUIDSENDDTMF_FMT,uuid,keys);
    //TRACE_LOG("send_dtmf(%s)",szcmd);
    //if(esl_send_recv(&_handle,szcmd)==ESL_SUCCESS){
    if (esl_execute(&_handle, "send_dtmf", keys, uuid) == ESL_SUCCESS
            && is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {

        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:send_dtmf(%s,%s);ret(%s)", uuid, keys, fs_resp);
    }

    FUNC_END();
}

int32_t fs_opr_t::record(const char* uuid, const char* file, uint32_t time_s) {
    FUNC_BEGIN();

    std::string full_file = _recordbase;
    full_file += "/";
    full_file += file;

    TRACE_LOG("fs::record(%s) start.", full_file.c_str());
    //set_channel_attribute(uuid,"playback_terminators=none");
    //set_channel_attribute(uuid,"RECORD_HANGUP_ON_ERROR=false");//1.0.7的fs才有
    //set_channel_attribute(uuid,"RECORD_MIN_SEC=0");

    //TRACE_LOG("fs::record(%s) middle.",full_file.c_str());
    snprintf(szcmd, LEN_512, CMD_RECORD_FMT, uuid, full_file.c_str(), time_s);

    //if(esl_send_recv(&_handle,szcmd)==ESL_SUCCESS){
    //    if(is_result_ok(fs_resp=esl_event_get_body(_handle.last_sr_event))){
    //        ret=IMS_SUCCESS;
    //    }
    //    else{
    //        WARNING_LOG("fs:record(%s,%s,%u);ret(%s)",uuid,full_file.c_str(),time_s,fs_resp);
    //    }
    //}
    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS &&
            is_result_ok(fs_resp = esl_event_get_header(_handle.last_sr_event, "Reply-Text"))) {
        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs:record(%s,%s,%u) esl_send_recv != ESL_SUCCESS", uuid, full_file.c_str(), time_s);
    }

    //TRACE_LOG("fs::record(%s) done.",full_file.c_str());

    FUNC_END();
}

int32_t fs_opr_t::eval(const char* key, char* val, uint32_t val_len) {
    FUNC_BEGIN();
    snprintf(szcmd, LEN_512, "api eval %s\n\n", key);
    TRACE_LOG("eval, (%s)", szcmd);

    if (esl_send_recv(&_handle, szcmd) == ESL_SUCCESS
            && (fs_resp = esl_event_get_body(_handle.last_sr_event))) {
        strncpy(val, fs_resp, val_len);

        fs_resp = val;

        while (fs_resp && *fs_resp && (fs_resp - val) < val_len) {
            if ('\n' == *fs_resp || '\r' == *fs_resp) {
                val[fs_resp - val] = '\0';
                break;
            }

            ++fs_resp;
        }

        ret = IMS_SUCCESS;
    } else {
        WARNING_LOG("fs_eval(%s) failed", key);
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
    int32_t ret = IMS_FAIL_NOTEXISTS;

    if (key && _handle.last_ievent) {
        const char* fs_resp = esl_event_get_header(_handle.last_ievent, key);

        if (val && fs_resp) {
            strncpy(val, fs_resp, val_len);
            //esl_url_decode(val);
            ret = IMS_SUCCESS;
        } else {
            //WARNING_LOG("get esl_event_get_header failed, fs_resp = %d", fs_resp);
        }
    }

    return ret;
}

/////////////////////////////////////其他 END  /////////////////////////////////////////////////

const char* fs_opr_t::CMD_JOINCONFERENCE_FMT =
    "bgapi originate {return_ring_ready=false,bridge_early_media=true,bypass_media=false,"
    "playback_terminators=none,origination_caller_id_number=%s,origination_caller_id_name=%s,IMSDATA=%lu}%s "
    "&conference(%s%s)\n\n";
//"effective_caller_id_number=%s,effective_caller_id_name=%s,IMSDATA=%lu}%s "
const char* fs_opr_t::CMD_UUIDBRIDGE_FMT = "api uuid_bridge %s %s\n\n";
const char* fs_opr_t::CMD_UNBRIDGE_FMT =
    "api uuid_transfer  %s -both 'set:hangup_after_bridge=false,set:park_after_bridge=true,park:' inline\n\n";
const char* fs_opr_t::CMD_UUIDSENDDTMF_FMT = "api uuid_send_dtmf %s %s\n\n";
const char* fs_opr_t::CMD_ORIGINATE_FMT =
    "bgapi originate {return_ring_ready=false,bridge_early_media=true,bypass_media=false,"
    "playback_terminators=none,origination_caller_id_number=%s,origination_caller_id_name=%s,IMSDATA=%lu}%s "
    "&bridge([origination_caller_id_number=%s,origination_caller_id_name=%s,call_timeout=%u,IMSDATA=%lu]%s)\n\n";

const char* fs_opr_t::CMD_RECORD_FMT = "bgapi uuid_record %s start %s %u\n\n";

const char* fs_opr_t::EVENT_NORMAL = "CHANNEL_ANSWER CHANNEL_HANGUP CHANNEL_DESTROY "
                                     "CHANNEL_EXECUTE CHANNEL_EXECUTE_COMPLETE CHANNEL_BRIDGE CHANNEL_UNBRIDGE CHANNEL_PROGRESS CHANNEL_PROGRESS_MEDIA "
                                     "BACKGROUND_JOB CHANNEL_ORIGINATE RECORD_START RECORD_STOP CUSTOM conference::maintenance";
const char* fs_opr_t::EVENT_HEARTBEAT = "HEARTBEAT";
const char* fs_opr_t::RECORD_BASEDIR = "${sounds_dir}";

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
