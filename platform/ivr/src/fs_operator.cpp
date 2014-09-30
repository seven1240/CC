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

#include "fs_operator.h"
#include "tools.h"

bool fs_operator_t::connect(esl_handle_t& handle,
                            const char* ip, uint32_t port,
                            const char* user, const char* pswd) {

    return esl_connect(&handle, ip, port, user, pswd) == ESL_SUCCESS;
}

bool fs_operator_t::startdtmf(esl_handle_t* handle, const std::string& callid) {
    return handle
           && esl_execute(handle, CMD_STARTDTMF, NULL, callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::stopdtmf(esl_handle_t* handle, const std::string& callid) {
    return handle
           && esl_execute(handle, CMD_STOPDTMF, NULL, callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::answer(esl_handle_t* handle, const std::string& callid) {
    return handle
           && esl_execute(handle, CMD_ANSWER, NULL, callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::hangup(esl_handle_t* handle, const string& callid) {
    return handle
           && esl_execute(handle, CMD_HANGUP, NULL, callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::playback(esl_handle_t* handle,
                             const string& callid, const string& playfile) {
    //首先将terminators设置为none，否则系统使用默认的*
    return handle
           && esl_execute(handle, CMD_SET, "playback_terminators=none", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           && esl_execute(handle, CMD_PLAY, playfile.c_str(), callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::dial(esl_handle_t* handle,
                         std::string& callid,
                         const std::string& called, const std::string& caller,
                         uint32_t timeout, bool external) {
    if (handle) {
        char szcmd[256] = {0};
        snprintf(szcmd, 256,
                 "%s {originate_timeout=%u,origination_uuid=%s}%s%s &park() %s %s %s %s %u %s",
                 CMD_DIAL, timeout, callid.c_str(), external ? "sofia/external/" : "user/",
                 called.c_str(), CMD_UNDEF, CMD_UNDEF,
                 caller.c_str(), caller.c_str(), timeout,
                 CMD_END);

        if (esl_send_recv(handle, szcmd) == ESL_SUCCESS) {
            const char* resp = esl_event_get_body(handle->last_sr_event);

            if (check_result(resp)) {
                //callid=resp+4;
                //callid.erase(callid.find_last_not_of("\n")+1);
                return true;
            }

        }
    }

    return false;
}

bool fs_operator_t::play_and_get_digits(esl_handle_t* handle,
                                        const std::string& callid, const std::string& playfile,
                                        uint32_t min, uint32_t max,
                                        uint32_t tries, uint32_t timeout,
                                        const std::string& term,
                                        const std::string& invalidfile) {
    //    <min> <max> <tries> <timeout> <terminators> <file> <invalid_file> <var_name> <regexp>"
    ostringstream ostm;


    ostm << min << " " << max << " " << tries << " " << timeout * 1000 << " " << term << " ";
    ostm << playfile << " " << invalidfile << " " << FS_VAR_TMP << "\nevent-lock: true\n" ;

    /*
    ostm << min << " " << max << " " << playfile << " " << FS_VAR_TMP << " ";
    ostm << timeout*1000 << term << "\nevent-lock: true\n";
    */
    //usleep(200000);
    return handle &&
           esl_execute(handle, CMD_FLUSH_DTMF, NULL, callid.c_str()) == ESL_SUCCESS &&
           check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT)) &&
           esl_execute(handle, CMD_PLAY_WITH_COLLECT, ostm.str().c_str(), callid.c_str()) == ESL_SUCCESS &&
           check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::bridge(esl_handle_t* handle,
                           const std::string& callid1, const std::string& callid2) {
    if (handle) {
        char szcmd[256] = {0};
        snprintf(szcmd, 256, "%s %s %s%s", CMD_BRIDGE,
                 callid1.c_str(), callid2.c_str(),
                 CMD_END);


        //ivr_tools_t::safe_sleeps(1);
        if (esl_execute(handle, CMD_SET, "bypass_media=false", callid1.c_str()) == ESL_SUCCESS
                && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
                && esl_execute(handle, CMD_SET, "bypass_media=false", callid2.c_str()) == ESL_SUCCESS
                && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
                && esl_send_recv(handle, szcmd) == ESL_SUCCESS) {
            const char* resp = esl_event_get_body(handle->last_sr_event);

            if (check_result(resp)) {
                std::string callid = resp + 4;
                callid.erase(callid.find_last_not_of("\n") + 1);
                return strcasecmp(callid.c_str(), callid2.c_str()) == 0;
            }

            //return check_result(resp);
        }
    }

    return false;
}

bool fs_operator_t::record(esl_handle_t* handle,
                           const std::string& callid, const std::string& recordpath, const std::string& recordfile) {

    std::string dir = recordpath;
    std::string base = "${sound_prefix}";
    std::string file = dir + "/" + recordfile;

    if (handle) {
        esl_execute(handle, CMD_SET, "RECORD_STEREO=false", callid.c_str());
        check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));

        esl_execute(handle, CMD_SET, "RECORD_COPYRIGHT=(c) 2011 Baidu.com", callid.c_str());
        check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));

        esl_execute(handle, CMD_SET, "RECORD_TITLE=callcloud@baidu.com", callid.c_str());
        check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));

        esl_execute(handle, CMD_SET, "RECORD_MIN_SEC=0", callid.c_str());
        check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));

        if (dir.size() == 0 || dir.substr(0, 1) != "/") {
            dir = base + "/" + file;
        } else {
            dir = file;
        }

        dir.erase(dir.find_last_of("/") + 1);

        esl_execute(handle, CMD_MKDIR, dir.c_str(), callid.c_str());
        check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
    }

    char szcmd[256] = {0};

    //设置话单数据，用来供ds提取录音文件使用
    snprintf(szcmd, 256, "userfield=%s", file.c_str());
    esl_execute(handle, CMD_SET, szcmd, callid.c_str());
    check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));

    ivr_tools_t::safe_sleeps(1);

    snprintf(szcmd, 256, "%s %s start %s%s", CMD_RECORD, callid.c_str(), file.c_str(), CMD_END);


    return handle
           && esl_execute(handle, CMD_SET, "playback_terminators=none", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           && esl_send_recv(handle, szcmd) == ESL_SUCCESS;
}

bool fs_operator_t::get_callercalled(esl_handle_t& hdl,
                                     std::string& caller, std::string& called) {
    if (!hdl.connected) {
        return false;
    }

    caller = esl_event_get_header(hdl.info_event, "Caller-ANI");
    called = esl_event_get_header(hdl.info_event, "Caller-Destination-Number");

    return true;
}

bool fs_operator_t::get_callid(esl_handle_t& hdl, std::string& callid) {
    if (!hdl.connected) {
        return false;
    }

    callid = esl_event_get_header(hdl.info_event, "caller-unique-id");
    return true;
}


bool fs_operator_t::collect(esl_handle_t* handle,
                            const std::string& callid, const std::string& playfile,
                            uint32_t min, uint32_t max, uint32_t timeout,
                            const std::string term) {
    //src\mod\applications\mod_dptools\mod_dptools.c
    //"<min> <max> <file> <var_name> <timeout> <terminators>"
    ostringstream ostm;
    ostm << min << " " << max << " " << playfile << " " << FS_VAR_TMP << " " << timeout * 1000 << " " <<
         term;
    return handle
           && esl_execute(handle, CMD_COLLECT, ostm.str().c_str(), callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}

bool fs_operator_t::check_event(esl_handle_t* handle, int32_t timeout, fs_event_t& event) {
    esl_status_t status = ESL_SUCCESS;
    event.event = fs_event_t::EV_UNKNOWN;

    if (0 == timeout) {
        return true;//不需要收事件
    }

    const char* type = NULL;
LOOP:

    if (timeout < 0) {
        status = esl_recv(handle);
    } else {
        status = esl_recv_timed(handle, timeout * 1000);
    }

    if (ESL_SUCCESS != status) {
        if (ESL_FAIL == status && 0 == handle->connected) {
            //连接断开
            //一种场景就是呼入的时候，客户挂断，socket断开
            event.event = fs_event_t::EV_DISCONNECT_OTHER;
            return true;
        } else if (ESL_BREAK == status) {
            event.event = fs_event_t::EV_TIMEOUT;
        }

        return false;
    }

    type = esl_event_get_header(handle->last_event, CONTENT_TYPE);

    if (type) {
        if (strcasecmp(type, PLAIN) == 0) {
            const char* eventname = esl_event_get_header(handle->last_ievent, "Event-Name");

            if (eventname && strcasecmp(eventname, "RECORD_START") == 0) {
                event.event = fs_event_t::EV_RECORD_BEGIN_SUCC;
                event.media_resp = fs_event_t::MEDIA_SUCC;
                const char* filename = esl_event_get_header(handle->last_ievent, "Record-File-Path");

                if (filename) {
                    strncpy(event.data, filename, MAX_DATA_SIZE);
                }

                return true;
            } else if (eventname && strcasecmp(eventname, "CHANNEL_UUID") == 0) {
                //origination_uuid模式外呼
                const char* old_uuid = esl_event_get_header(handle->last_ievent, "Old-Unique-ID");

                if (old_uuid) {
                    strncpy(event.data, old_uuid, MAX_DATA_SIZE);
                }

                goto LOOP;
            } else if (eventname && strcasecmp(eventname, "RECORD_STOP") == 0) {
            } else if (eventname && strcasecmp(eventname, "CHANNEL_ANSWER") == 0) {
                //外呼，外部应答
                event.event = fs_event_t::EV_ANSWER_SUCC;
                return true;
            } else if (eventname && strcasecmp(eventname, "CHANNEL_HANGUP") == 0) {
                event.event = fs_event_t::EV_DISCONNECT_OTHER;
                return true;
            } else if (eventname && strcasecmp(eventname, "CHANNEL_BRIDGE") == 0) {
                //桥接成功，被桥接方应答成功
                event.event = fs_event_t::EV_ANSWER_SUCC;
                /**stars 1124-0552**/
                /*const char * new_uuid=esl_event_get_header(handle->last_ievent,"Other-Leg-Unique-ID");
                IVR_TRACE("NEW UUID suc: new_callid=%s", new_uuid);
                if(new_uuid)
                {
                    strncpy(event.data, new_uuid, MAX_DATA_SIZE);
                }*/
                /** stars end**/
                return true;
            } else if (eventname && strcasecmp(eventname, "CHANNEL_EXECUTE_COMPLETE") == 0) {
                const char* app = esl_event_get_header(handle->last_ievent, APPLICATION);

                if (app) {
                    if (strcasecmp(app, CMD_ANSWER) == 0) {
                        event.event = fs_event_t::EV_ANSWER_SUCC;
                    } else if (strcasecmp(app, CMD_HANGUP) == 0) {
                        event.event = fs_event_t::EV_HANGUP_SUCC;
                    } else if (strcasecmp(app, CMD_BRIDGE) == 0) {
                        event.event = fs_event_t::EV_BRIDGE_SUCC;
                    } else if (strcasecmp(app, CMD_RECORD) == 0) {
                        event.event = fs_event_t::EV_RECORD_BEGIN_SUCC;
                    } else if (strcasecmp(app, CMD_PLAY) == 0) {
                        event.event = fs_event_t::EV_PLAY_SUCC;
                        event.media_resp = fs_event_t::MEDIA_SUCC;
                        const char* media = esl_event_get_header(handle->last_ievent, APP_RESP);

                        if (media) {
                            if (strcasecmp(media, MEDIA_FILE_PLAYED) == 0) {
                                event.media_resp = fs_event_t::MEDIA_SUCC;
                            } else if (strcasecmp(media, MEDIA_FILE_NOEXIST) == 0) {
                                event.media_resp = fs_event_t::MEDIA_FILE_NOEXIST;
                            }
                        }
                    } else if (strcasecmp(app, CMD_COLLECT) == 0
                               || strcasecmp(app, CMD_PLAY_WITH_COLLECT) == 0) {
                        event.event = fs_event_t::EV_PLAY_SUCC;
                        event.media_resp = fs_event_t::MEDIA_SUCC;
                        const char* media = esl_event_get_header(handle->last_ievent, APP_RESP);

                        if (media) {
                            if (strcasecmp(media, MEDIA_FILE_PLAYED) == 0) {
                                event.media_resp = fs_event_t::MEDIA_SUCC;
                            } else if (strcasecmp(media, MEDIA_FILE_NOEXIST) == 0) {
                                event.media_resp = fs_event_t::MEDIA_FILE_NOEXIST;
                            }
                        }

                        std::string input = get_variable(handle, FS_VAR_DIGIT_READ);

                        if (strcasecmp(input.c_str(), FS_DIGIT_RESULT_FAIL) != 0) {
                            input = get_variable(handle, FS_VAR_TMP);

                            if (input.size()) {
                                event.event = fs_event_t::EV_COLLECT_SUCC;
                                strncpy(event.data, input.c_str(), MAX_DATA_SIZE);
                            }
                        }
                    } else {
                        return false;
                    }

                    if (event.event != fs_event_t::EV_HANGUP_SUCC) { //系统主动挂断就不处理了
                        const char* ch_status = esl_event_get_header(handle->last_ievent, CH_ST);

                        if (ch_status && strcasecmp(ch_status, CH_ST_HANGUP) == 0) {
                            event.event = fs_event_t::EV_DISCONNECT_OTHER;
                            std::string var = get_variable(handle, "bridge_uuid");

                            if (var.size() != 0) {
                                //以消息中有没有该变量来确认挂断场景是否为bridge
                                //有点土，但是没有找到更好的办法
                                event.event = fs_event_t::EV_DISCONNECT_THIRD;
                            }
                        }
                    }
                }
            } else {
                return false;
            }
        } else if (strcasecmp(type, DISCONNECT) == 0) {
            event.event = fs_event_t::EV_DISCONNECT_OTHER;
        }
    }

    return true;
}

std::string fs_operator_t::get_variable(esl_handle_t* handle, const char* var) {
    if (var) {
        std::string s = FS_VAR_PREFIX;
        s += var;
        const char* sztmp = esl_event_get_header(handle->last_ievent, s.c_str());

        if (sztmp) {
            return sztmp;
        }
    }

    return "";
}

std::string fs_operator_t::create_uuid(esl_handle_t& handle) {
    std::string uuid;

    if (handle.connected && esl_send_recv(&handle, CMD_CREATEUUID) == ESL_SUCCESS) {
        const char* resp = esl_event_get_body(handle.last_sr_event);

        if (resp) {
            uuid = resp;
            uuid.erase(uuid.find_last_not_of("\n") + 1);
        }
    }

    return uuid;
}

bool fs_operator_t::check_result(const char* result) {
    if (result) {
        return (strlen(result) >= 3 && strncasecmp(RESULT_OK, result, 3) == 0);
    }

    return false;
}

bool fs_operator_t::bridgeex(esl_handle_t* handle,
                             const std::string& callid,
                             const std::string& caller, const std::string& called,
                             bool external, bool usbgm, const std::string& bgmfile) {
    ostringstream ostm;
    /*
    ostm<<"{";
    ostm<<"originate_timeout=30,";
    ostm<<"originate_caller_id_number="<<caller<<",";
    ostm<<"originate_caller_id_name="<<caller;
    ostm<<"}";
    */

    if (external) {
        ostm << "sofia/external/" << called;
    } else {
        ostm << "user/" << called;
    }

    if (usbgm) {
        return handle
               //语音透传
               && esl_execute(handle, CMD_SET, ("ringback=${sounds_dir}/" + bgmfile).c_str(),
                              callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               //被bridge不通，返回第一个呼叫不挂
               && esl_execute(handle, CMD_SET, "continue_on_fail=true", callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               //被bridge方挂断，发起方也挂断
               && esl_execute(handle, CMD_SET, "hangup_after_bridge=true", callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               && esl_execute(handle, CMD_SET, "bypass_media=false", callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               //&& esl_execute(handle,CMD_SET,"call_timeout=30",callid.c_str())==ESL_SUCCESS
               //&& check_result(esl_event_get_header(handle->last_sr_event,REPLY_TEXT))
               && esl_execute(handle, CMD_SET, ("effective_caller_id_name=" + caller).c_str(),
                              callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               && esl_execute(handle, CMD_SET, ("effective_caller_id_number=" + caller).c_str(),
                              callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
               && esl_execute(handle, CMD_BRIDGEEX, ostm.str().c_str(), callid.c_str()) == ESL_SUCCESS
               && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
    }

    return handle
           //语音透传
           && esl_execute(handle, CMD_SET, "bridge_early_media=true", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           //被bridge不通，返回第一个呼叫不挂
           && esl_execute(handle, CMD_SET, "continue_on_fail=true", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           //被bridge方挂断，发起方也挂断
           && esl_execute(handle, CMD_SET, "hangup_after_bridge=true", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           && esl_execute(handle, CMD_SET, "bypass_media=false", callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           //&& esl_execute(handle,CMD_SET,"call_timeout=30",callid.c_str())==ESL_SUCCESS
           //&& check_result(esl_event_get_header(handle->last_sr_event,REPLY_TEXT))
           && esl_execute(handle, CMD_SET, ("effective_caller_id_name=" + caller).c_str(),
                          callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           && esl_execute(handle, CMD_SET, ("effective_caller_id_number=" + caller).c_str(),
                          callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT))
           && esl_execute(handle, CMD_BRIDGEEX, ostm.str().c_str(), callid.c_str()) == ESL_SUCCESS
           && check_result(esl_event_get_header(handle->last_sr_event, REPLY_TEXT));
}


const char* fs_operator_t::CMD_SET = "set";
const char* fs_operator_t::CMD_ANSWER = "answer";
const char* fs_operator_t::CMD_STARTDTMF = "start_dtmf";
const char* fs_operator_t::CMD_STOPDTMF = "stop_dtmf";
const char* fs_operator_t::CMD_FLUSH_DTMF = "flush_dtmf";
const char* fs_operator_t::CMD_HANGUP = "hangup";
const char* fs_operator_t::CMD_PLAY = "playback";
const char* fs_operator_t::CMD_COLLECT = "read";
const char* fs_operator_t::CMD_BRIDGEEX = "bridge";
const char* fs_operator_t::CMD_PLAY_WITH_COLLECT = "play_and_get_digits";
//    const char * fs_operator_t::CMD_PLAY_WITH_COLLECT="read";
const char* fs_operator_t::CMD_DIAL = "api originate ";
const char* fs_operator_t::CMD_UNDEF = "undef";
const char* fs_operator_t::CMD_RECORD = "api uuid_record";
const char* fs_operator_t::CMD_BRIDGE = "api uuid_bridge";
const char* fs_operator_t::CMD_GETVAR = "api uuid_getvar";
const char* fs_operator_t::CMD_MKDIR = "mkdir";
const char* fs_operator_t::CMD_END = "\n\n";
const char* fs_operator_t::CMD_CREATEUUID = "api create_uuid";

const char* fs_operator_t::RESULT_OK = "+ok";
const char* fs_operator_t::REPLY_TEXT = "Reply-Text";
const char* fs_operator_t::CH_ST = "Channel-State";
const char* fs_operator_t::CONTENT_TYPE = "content-type";
const char* fs_operator_t::PLAIN = "text/event-plain";
const char* fs_operator_t::APPLICATION = "Application";
const char* fs_operator_t::APP_RESP = "Application-Response";
const char* fs_operator_t::DISCONNECT = "text/disconnect-notice";

const char* fs_operator_t::CH_ST_HANGUP = "CS_HANGUP";

const char* fs_operator_t::MEDIA_FILE_PLAYED = "FILE PLAYED";
const char* fs_operator_t::MEDIA_FILE_NOEXIST = "FILE NOT FOUND";

//const uint32_t fs_operator_t::MAX_DATA_SIZE=255;
const char* fs_operator_t::FS_VAR_TMP = "BAIDU_CC_DATA";
const char* fs_operator_t::FS_DIGIT_RESULT_SUCC = "success";
const char* fs_operator_t::FS_DIGIT_RESULT_FAIL = "failure";
const char* fs_operator_t::FS_DIGIT_RESULT_TO = "timeout";
const char* fs_operator_t::FS_VAR_DIGIT_READ = "read_result";
const char* fs_operator_t::FS_VAR_PREFIX = "variable_";







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
