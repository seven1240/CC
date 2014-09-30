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

#include "common.h"
#include "tools.h"
#include "flow_manager.h"
#include "conf_manager.h"

int32_t g_stopped = 0;
sem_t g_stop_sem;

//system configuration
string g_server_ip;
uint32_t g_server_port = 0;
uint32_t g_reload_port = 0;
call_data_conf_t g_calldata_conf;

//inbound configuration
inbound_conf_t  g_inbound_conf;

//autorun configuration
autorun_conf_t  g_autorun_conf;

std::auto_ptr<ConfManager> g_conf_manager;

// mutex
pthread_rwlock_t g_inbound_conf_rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t g_autorun_conf_rwlock = PTHREAD_RWLOCK_INITIALIZER;

//autorun configuration
DBPool* g_dbpool;

bool g_output_esllog = true;
time_t g_autorun_script_stamp = 0;

uint32_t g_inbound_chan_num = 0;
uint32_t g_autorun_chan_num = 0;
uint32_t g_autodial_chan_num = 0;
pthread_rwlock_t g_inbound_chan_rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t g_autorun_chan_rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t g_autodial_chan_rwlock = PTHREAD_RWLOCK_INITIALIZER;

FlowManager g_flowmanager_inbound;
FlowManager g_flowmanager_autorun;
//map<string, flow_t*> g_flow_name_info_map;  //
//vector<flow_t*> g_clear_flow_vec;           //

/*
const char* SYS_VAR[]={
    "_ani",
    "_dnis",
    "_callid",
    "_record_file_name",
    "_hangup_cause",
    "_call_begin_time",
    "_call_answer_time"
};
*/

const char* SYS_VAR[] = {
    "_ANI",
    "_DNIS",
    "_CALLID",
    "_RECORD_FILE_NAME",
    "_HANGUP_CAUSE",
    "_CALL_BEGIN_TIME",
    "_CALL_ANSWER_TIME"
};
std::string base_script_t::bill_info() {
    ostringstream ostm;

    string call_begin_second = *(string*)name_var_map[SYS_VAR[sys_var_t::CALL_BEGIN_TIME]].pvalue;
    string call_answer_second = *(string*)name_var_map[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue;
    string call_end_second = ivr_tools_t::get_current_second();
    int32_t duration = atoi(call_end_second.c_str()) - atoi(call_begin_second.c_str());
    int32_t billsec = atoi(call_end_second.c_str()) - atoi(call_answer_second.c_str());

    ostm << '"' << *(string*)name_var_map[SYS_VAR[sys_var_t::ANI]].pvalue << '"' << ',';
    ostm << '"' << *(string*)name_var_map[SYS_VAR[sys_var_t::DNIS]].pvalue << '"' << ',';
    ostm << '"' << ivr_tools_t::format_datatime_str(call_begin_second) << '"' << ',';
    ostm << '"' << ivr_tools_t::format_datatime_str(call_answer_second) << '"' << ',';
    ostm << '"' << ivr_tools_t::format_datatime_str(call_end_second) << '"' << ',';
    ostm << '"' << duration << '"' << ',';
    ostm << '"' << billsec << '"' << ',';
    ostm << '"' << *(string*)name_var_map[SYS_VAR[sys_var_t::HANGUP_CAUSE]].pvalue << '"' << ',';

    std::string callid = *(string*)name_var_map["BK_CALLID"].pvalue;

    if (callid.length() > 0) {
        ostm << '"' << callid << '"' << ',';
    } else {
        ostm << '"' << *(string*)name_var_map[SYS_VAR[sys_var_t::CALLID]].pvalue << '"' << ',';
    }

    ostm << '"' << *(string*)name_var_map[SYS_VAR[sys_var_t::RECORD_FILE]].pvalue << '"';

    return ostm.str();

}

const std::map<int32_t, string>& errorcode_string::errormap() {
    static std::map<int32_t, string> _map;

    if (_map.empty()) {
        typedef std::pair<int32_t, string> mpair;
        _map.insert(mpair(IVR_SUCCESS, "IVR_SUCCESS"));
        _map.insert(mpair(IVR_FAIL_GENERAL, "IVR_FAIL_GENERAL"));
        _map.insert(mpair(IVR_FAIL_LOCK, "IVR_FAIL_LOCK"));
        _map.insert(mpair(IVR_FAIL_EXISTS, "IVR_FAIL_EXISTS"));
        _map.insert(mpair(IVR_FAIL_NOTEXISTS, "IVR_FAIL_NOTEXISTS"));
        _map.insert(mpair(IVR_FAIL_MEM, "IVR_FAIL_MEM"));
        _map.insert(mpair(IVR_FAIL_INVALID_FSNO, "IVR_FAIL_INVALID_FSNO"));
        _map.insert(mpair(IVR_FAIL_ALL_BUSY, "IVR_FAIL_ALL_BUSY"));
        _map.insert(mpair(IVR_FAIL_CONNECT, "IVR_FAIL_CONNECT"));
        _map.insert(mpair(IVR_FAIL_TIMEOUT, "IVR_FAIL_TIMEOUT"));
        _map.insert(mpair(IVR_FAIL_NOIMS, "IVR_FAIL_NOIMS"));
        _map.insert(mpair(IVR_FAIL_IMS_REGIST, "IVR_FAIL_IMS_REGIST"));
        _map.insert(mpair(IVR_FAIL_IMS_NOTEXIST, "IVR_FAIL_IMS_NOTEXIST"));
        _map.insert(mpair(IVR_FAIL_IMS_ROUTEREQUEST, "IVR_FAIL_IMS_ROUTEREQUEST"));
        _map.insert(mpair(IVR_FAIL_IMS_CANCELROUTEREQUEST, "IVR_FAIL_IMS_CANCELROUTEREQUEST"));
        _map.insert(mpair(IVR_FAIL_IMS_TRANSAGENT, "IVR_FAIL_IMS_TRANSAGENT"));
        _map.insert(mpair(IVR_FAIL_IMS_SETASSOCIATEDATA, "IVR_FAIL_IMS_SETASSOCIATEDATA"));
        _map.insert(mpair(IVR_FAIL_IMS_GETASSOCIATEDATA, "IVR_FAIL_IMS_GETASSOCIATEDATA"));
        _map.insert(mpair(IVR_FAIL_IMS_NOMAIN, "IVR_FAIL_IMS_NOMAIN"));
        _map.insert(mpair(IVR_FAIL_IMS_CREATESESSION, "IVR_FAIL_IMS_CREATESESSION"));
        _map.insert(mpair(IVR_FAIL_IMS_SESSIONINVALIDATE, "IVR_FAIL_IMS_SESSIONINVALIDATE"));
        _map.insert(mpair(IVR_FAIL_IMS_INFOINVALIDATE, "IVR_FAIL_IMS_INFOINVALIDATE"));
        _map.insert(mpair(IVR_FAIL_IMS_AGENTNOTASSIGNED, "IVR_FAIL_IMS_AGENTNOTASSIGNED"));
        _map.insert(mpair(IVR_FAIL_IMS_ROUTEREQUEST_REPEATED, "IVR_FAIL_IMS_ROUTEREQUEST_REPEATED"));
        //_map.insert(mpair(, ""));
    }

    return _map;
}

string errorcode_string::tostring(int32_t errorcode) {
    std::map<int32_t, string>::const_iterator iterfind = errormap().find(errorcode);

    if (iterfind != errormap().end()) {
        return iterfind->second;
    } else {
        return "UnknownErrorCode";
    }
}
