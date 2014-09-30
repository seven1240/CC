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

#include <stdint.h>
#include <uuid/uuid.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <pcre.h>

#include "ims_tool.h"
#include "ims_log.h"
#include "ims_lock.h"
#include "ims_core_session_mgr.h"

#define OVERCOUNT 100
/**
 * 生成session_id
 * @param   freeswitch_id   [in] : freeswitch编号
 *
 * @return 生成的session_id
 *
 */

uint64_t ims_tool_t::get_sessionid(uint32_t fs_id) {
    unsigned int seed = (unsigned int) ims_tool_t::get_timestamp_ms();
    uint64_t rand_num = rand_r(&seed) & 0xffff;
    uint64_t current_time = get_timestamp_ms() & 0xffffffffff;
    uint64_t session_id = ((uint64_t)fs_id << 56) | (current_time << 16) | rand_num;
    return session_id;
}


/**
 * 生成req_id
 * @param   req_type    [in] : 请求服务类型
 *          req_ip      [in] : 请求ip地址
 *          req_port    [in] : 请求端口
 *
 * @return 生成的req_id
 *
 */
uint64_t ims_tool_t::get_reqid(const ims::ServiceTypeT& req_type, uint32_t req_ip,
                               uint32_t req_port) {
    unsigned int seed = (unsigned int) ims_tool_t::get_timestamp_ms();
    uint64_t rand_num = rand_r(&seed) & 0xff;
    uint64_t port = (uint64_t)req_port;
    port = (port << 8) & 0xffff00;
    uint64_t ip = (uint64_t)req_ip;
    ip = (ip << 24) & 0xffffffff000000;
    uint64_t type = (((uint64_t) req_type.get_value()) << 56) & 0xff00000000000000;
    uint64_t req_id = type | ip | port | rand_num;
    return req_id;
}

ims::RouteRequestIDT ims_tool_t::get_requestid(const ims::SessionIdT& sessionid,
        const ims::RouteRequestTypeT& requestType) {
    uint64_t tmstamp = ims_tool_t::get_timestamp_ms() & 0xffffffffff;
    uint64_t sessionid_random = sessionid & 0xffff;
    uint64_t type = (((uint64_t) requestType.get_value()) << 56) & 0xff00000000000000;
    ims::RouteRequestIDT requestId = type | (tmstamp << 16) | sessionid_random;
    return requestId;
}

/**
 * 时间处理函数，得到毫秒级时间戳
 * @param
 *
 * @return 返回当前时间的毫秒级时间戳
 *
 */
uint64_t ims_tool_t::get_timestamp_ms() {
    timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

/**
 * 时间处理函数，得到秒级时间戳
 * @param
 *
 * @return 返回当前时间的秒级时间戳
 *
 */
uint64_t ims_tool_t::get_timestamp_s() {
    timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec;
}


/**
 * 将64位无符号数转换为二进制，用字符串形式表示
 * @param   num [in] : 一个无符号64位十进制数
 *
 * @return 转换为二进制后的字符串
 *
 */
std::string ims_tool_t::decimal_to_binary(uint64_t num) {
    std::string binary;

    if (num == 0) {
        return "0";
    }

    while (num != 0) {
        int tmp = num & 1;

        if (tmp == 0) {
            binary.append("0");
        } else {
            binary.append("1");
        }

        num = num >> 1;
    }

    /* 字符串翻转 */
    int len = binary.length();
    int size = len / 2;

    for (int i = 0; i < size; ++i) {
        char tmp = binary[i];
        binary[i] = binary[len - i - 1];
        binary[len - i - 1] = tmp;
    }

    return binary;
}

const char* ims_tool_t::strdup(const char* src, boost::object_pool<std::string>* pool) {
    std::string* str = NULL;
    str = pool->construct(src);
    return str->c_str();
}

const char* ims_tool_t::inet_ntop(uint32_t src, char* dest, uint32_t dest_len) {
    if (dest == NULL) {
        return NULL;
    }

    uint32_t idx = 0;

    for (int i = 3; i >= 0 && idx < dest_len; --i) {
        uint32_t tmp = (src >> (i * 8)) & 0xff;
        char subip[5];
        int j = -1;

        while (j < 5) {
            ++j;
            subip[j] = tmp % 10 + '0';
            tmp = tmp / 10;

            if (tmp == 0) {
                break;
            }
        }

        while (j >= 0 && idx < dest_len) {
            dest[idx] = subip[j];
            --j;
            ++idx;
        }

        if (idx >= dest_len) {
            dest[0] = '\0';
            break;
        } else if (i > 0) {
            dest[idx] = '.';
            ++idx;
        } else {
            dest[idx] = '\0';
            ++idx;
        }
    }

    return dest;
}

uint32_t ims_tool_t::inet_pton(const char* src) {
    if (src == NULL) {
        return 0;
    }

    uint32_t result = 0;

    if (ims_tool_t::pa_chkip(src, result) == false) {
        result = 0;
    }

    return result;
}

bool ims_tool_t::is_local_ipv4(uint32_t naddr) {
    struct ifaddrs* ifAddrStruct = NULL;
    struct ifaddrs* ifa = NULL;
    void* tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);
    uint32_t local_naddr = 0;

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa ->ifa_addr->sa_family == AF_INET) { // check it is IP4
            tmpAddrPtr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            ::inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            local_naddr = ims_tool_t::inet_pton(addressBuffer);

            if (local_naddr == naddr) {
                freeifaddrs(ifAddrStruct);
                return true;
            }
        }
    }

    if (ifAddrStruct) {
        freeifaddrs(ifAddrStruct);
    }

    return false;
}

bool ims_tool_t::parse_proxy_info(const std::string& src, std::string& ipstr, uint32_t& port) {
    if (src.length() <= 3) {
        return false;
    }

    int getip = -1, getport = -1;
    ipstr = "";
    port = 0;

    for (int i = 2; ; ++i) {

        if (getip == -1 && src[i - 2] == '-' && src[i - 1] == 'h' && src[i] == ' ') {
            getip = 0;
        } else if (getip == 0 && src[i] != ' ') {
            getip = 1;
        } else if (getport == -1 && src[i - 2] == '-' && src[i - 1] == 'p' && src[i] == ' ') {
            getport = 0;
        } else if (getport == 0 && src[i] != ' ') {
            getport = 1;
        }

        if (getip == 1) {
            if (src[i] != ' ' && src[i] != '\0') {
                ipstr += src[i];
            } else {
                getip = 2;
            }
        } else if (getport == 1) {
            if (src[i] >= '0' && src[i] <= '9') {
                port = port * 10 + (src[i] - '0');

                //port合法性判断
                if (port > 0xffff) {
                    port = 0;
                    return false;
                }
            } else if (src[i] == ' ' || src[i] == '\0') {
                getport = 2;
            } else {
                port = 0;
                return false;
            }
        }

        if (getip == 2 && getport == 2) {
            if (ims_tool_t::pa_chkip(ipstr.c_str()) == false) {
                return false;
            }

            return true;
        }

        if (src[i] == '\0') {
            return false;
        }
    }
}


bool ims_tool_t::pa_chkip(const char* src, uint32_t& result) {
    result = 0;

    if (src == NULL) {
        return false;
    }

    if (strcmp(src, "localhost") == 0) {
        result = (127 << 24) | 0x1;
        return true;
    }

    const char* s = src;
    uint32_t count = 0;
    char subip[5];
    uint32_t idx = 0;

    while (*s == ' ') {
        ++s;
    }

    while (1) {
        if (*s == '.' || *s == '\0' || *s == ' ') {
            ++count;
            uint32_t tmp = 0;

            for (uint32_t i = 0; i < idx; ++i) {
                tmp = (subip[i] - '0') + tmp * 10;
            }

            idx = 0;

            if (tmp > 255) {
                return false;
            }

            result = ((result << 8) & 0xffffff00) | (tmp & 0xff);
        } else if (*s >= '0' && *s <= '9') {
            subip[idx] = *s;
            idx++;
        } else {
            return false;
        }

        if (*s == '\0' || *s == ' ' || count > 4) {
            break;
        }

        ++s;
    }

    while (*s == ' ') {
        ++s;
    }

    if (count == 4 && *s == '\0') {
        return true;
    } else {
        result = 0;
        return false;
    }
}


bool ims_tool_t::pa_chkip(const char* src) {
    uint32_t result = 0;
    return ims_tool_t::pa_chkip(src, result);
}
void ims_tool_t::safe_sleeps(uint32_t s) {
    struct timespec interval, remainder;
    interval.tv_sec = s;
    interval.tv_nsec = 0;
    int32_t rr = -1;

    if ((rr = nanosleep(&interval, &remainder)) == -1) {
        while (EINTR == errno && -1 == rr) {
            rr = nanosleep(&remainder, &remainder);
        }
    }
}

void ims_tool_t::safe_sleepms(uint32_t ms) {
    struct timespec interval, remainder;
    interval.tv_sec = ms / 1000;
    interval.tv_nsec = (ms % 1000) * 1000 * 1000;
    int32_t rr = -1;

    if ((rr = nanosleep(&interval, &remainder)) == -1) {
        while (EINTR == errno && -1 == rr) {
            rr = nanosleep(&remainder, &remainder);
        }
    }
}



bool ims_tool_t::set_callno(const std::string& caller_no, const std::string& called_no,
                            const std::string& dn, const ims_conf_t& conf,
                            std::string& disp_caller, std::string& caller, std::string& called) {

    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    rw_lock_t  lock(pmgr->config_lock());

    if (!lock.locked()) {
        DEBUG_LOG("lock config failed!");
        return false;
    }

    pcre* re = NULL;
    const char* error;
    const char* subject = caller_no.c_str();
    int erroffset;
    int ovector[OVERCOUNT];
    int subject_length = caller_no.length();
    int rc;

    std::list<ims_conf_route_node_t*> routes = conf.route;

    for (std::list<ims_conf_route_node_t*>::iterator iter = routes.begin(); iter != routes.end();
            ++iter) {
        ims_conf_route_node_t* cur_route = (*iter);
        const char* pattern = cur_route->expression;
        re = pcre_compile(pattern, 0, &error, &erroffset, NULL);

        if (re) {
            rc = pcre_exec(re, NULL, subject, subject_length, 0, 0, ovector, OVERCOUNT);

            if (rc < 0) {
                free(re);
                re = NULL;
                continue;
            }

            if (rc == 0) {
                WARNING_LOG("find the conf, but the size of the vector is too small! Please change OVERCOUNT in ims_tool.cpp");
            }

            std::vector <std::string> res;

            for (int i = 0; i < rc; i++) {
                const char* substring_start = subject + ovector[2 * i];
                int substring_length = ovector[2 * i + 1] - ovector[2 * i];
                char* tmp = (char*)malloc((substring_length + 5) * sizeof(char));
                snprintf(tmp, substring_length + 4, "%.*s", substring_length, substring_start);
                std::string s = tmp;
                res.push_back(s);
                free(tmp);
            }

            disp_caller = cur_route->rule_disp_caller;
            caller = cur_route->rule_call_caller;
            called = cur_route->rule_call_called;
            ims_tool_t::replace_substring(caller, "${DN}", dn);
            ims_tool_t::replace_substring(called, "${CALLED}", called_no);
            ims_tool_t::replace_callno(caller, res);
            ims_tool_t::replace_callno(called, res);
            ims_tool_t::replace_callno(disp_caller, res);

            free(re);
            re = NULL;

            return true;
        }
    }

    disp_caller = "";
    caller = dn;
    called = called_no;
    return false;
}

bool ims_tool_t::replace_callno(std::string& callno, const std::vector<std::string>& res) {
    bool result = false;
    uint32_t size = res.size();
    std::string::size_type s = callno.find('$');

    while (s != std::string::npos) {
        uint32_t e = s + 1;
        uint32_t pos = 0;

        if (callno[e] != '0') {
            while (callno[e] >= '0' && callno[e] < '9') {
                uint32_t tmp = pos * 10 + callno[e] - '0';

                if (tmp >= size) {
                    break;
                }

                pos = tmp;
                ++e;
            }
        }

        if (pos != 0) {
            result = true;
            callno.replace(s, e - s, res[pos]);
        }

        s = callno.find('$', s + 1);
    }

    return result;
}



bool ims_tool_t::replace_substring(std::string& dest, const std::string& substr_replaced,
                                   const std::string& src) {
    bool result = false;
    uint32_t len = substr_replaced.length();

    std::string::size_type s = dest.find(substr_replaced);

    while (s != std::string::npos) {
        result = true;
        dest.replace(s, len, src);
        s = dest.find(substr_replaced, s + len);
    }

    return result;
}


std::string ims_tool_t::chlname2no(const std::string& src) {
    std::string ret;

    if (chlname2no(src, ret)) {
        return ret;
    } else {
        return src;
    }
}
bool ims_tool_t::chlname2no(const std::string& src, std::string& dest) {

    int len = src.length();
    dest = "";

    for (int i = 0; i < len; ++i) {
        if (src[i] == '/') {
            dest = "";
        } else if (src[i] == '@') {
            return true;
        } else {
            dest += src[i];
        }
    }

    dest = "";
    return false;

}


bool ims_tool_t::pa_chkport(const char* src, uint32_t& result) {
    result = 0;

    if (src == NULL) {
        return false;
    }

    const char* s = src;

    while (*s == ' ') {
        ++s;
    }

    while (*s >= '0' && *s <= '9') {
        result = result * 10 + ((*s) - '0');

        if (result > 0xffff) {
            result = 0;
            return false;
        }

        ++s;
    }

    while (*s == ' ') {
        ++s;
    }

    if (*s != '\0') {
        return false;
    }

    return true;

}


uint32_t ims_tool_t::get_fsno(uint64_t sessionid) {
    uint32_t fsno = (uint32_t)((sessionid >> 56) & 0xff);
    return fsno;
}

std::string ims_tool_t::num2str(uint64_t num) {
    std::ostringstream ostm;
    ostm << num;
    return ostm.str();
}


uint32_t ims_tool_t::str_to_uint32(const char* src) {
    if (src == NULL) {
        return 0;
    }

    const char* s = src;
    uint32_t result = 0;

    while (*s == ' ') {
        ++s;
    }

    while (*s >= '0' && *s <= '9') {
        result = result * 10 + ((*s) - '0');
        ++s;
    }

    while (*s == ' ') {
        ++s;
    }

    if (*s == '\0') {
        return result;
    }

    return 0;


}

bool ims_tool_t::ip_mask_parse(const char* src , uint32_t& ip, uint32_t& mask, uint32_t& bit) {
    ip = 0;
    mask = 0;
    bit = 0;

    if (src == NULL) {
        return false;
    }

    std::string cip = "";
    std::string cbit = "";
    const char* s = src;

    while (*s != '\0' && *s != '/') {
        cip += *s;
        ++s;
    }

    if (*s != '/') {
        if (*s == '\0' && pa_chkip(cip.c_str(), ip)) {
            return true;
        }

        return false;
    }

    ++s;

    while (*s != '\0') {
        cbit += *s;
        ++s;
    }

    mask = 0xffffffff;
    bit = ims_tool_t::str_to_uint32(cbit.c_str());

    if (pa_chkip(cip.c_str(), ip) && bit <= 32) {
        mask = mask << (32 - bit);
        return true;
    }

    return false;
}



void ims_tool_t::print_conf_DEBUGLOG(const ims_conf_t& conf) {

    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    rw_lock_t  lock(pmgr->config_lock());

    if (!lock.locked()) {
        DEBUG_LOG("lock config failed!");
        return;
    }

    DEBUG_LOG("********************* read  conf  begin ******************************");
    DEBUG_LOG("============ service =================");
    std::map<ims_conf_service_type_t, ims_conf_server_t* > service = conf.service;
    DEBUG_LOG("service size : %ld ", service.size());

    for (std::map<ims_conf_service_type_t, ims_conf_server_t* >::iterator iter = service.begin();
            iter != service.end(); ++iter) {
        ims_conf_service_type_t type = iter->first;
        ims_conf_server_t* cur = iter->second;
        char dest[100];
        ims_tool_t::inet_ntop(cur->ip, dest, 100);


        DEBUG_LOG("type : %u", type);
        DEBUG_LOG("ip : %u  ||  %s", cur->ip , dest);
        DEBUG_LOG("port : %u", cur->port);
    }

    DEBUG_LOG("=========   param ==================");
    std::map<ims_conf_param_type_t, const char*> param = conf.param;
    DEBUG_LOG("param size : %ld", param.size());

    for (std::map<ims_conf_param_type_t, const char*>::iterator iter = param.begin();
            iter != param.end(); ++iter) {

        DEBUG_LOG("type : %u", iter->first);
        DEBUG_LOG("data  : %s", iter->second);

    }

    DEBUG_LOG("=========   client ==================");
    std::map<ims_conf_client_type_t, std::list<ims_conf_acl_node_t*> > clients = conf.clients;
    DEBUG_LOG("clients size : %ld", clients.size());

    for (std::map<ims_conf_client_type_t, std::list<ims_conf_acl_node_t*> >::iterator iter =
                clients.begin(); iter != clients.end(); ++iter) {
        DEBUG_LOG("type : %u", iter->first);
        std::list<ims_conf_acl_node_t*> tmp = iter->second;

        for (std::list<ims_conf_acl_node_t*>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            ims_conf_acl_node_t* cur = (*it);
            char dest[100];
            ims_tool_t::inet_ntop(cur->ip, dest, 100);
            char dest1[100];
            ims_tool_t::inet_ntop(cur->mask, dest1, 100);

            DEBUG_LOG("ip : %u  ||  %s", cur->ip, dest);
            DEBUG_LOG("mask : %u  ||  %s", cur->mask, dest1);
            DEBUG_LOG("bit : %u", cur->bit);
        }
    }

    DEBUG_LOG("=========   gateway  ==================");
    std::list<ims_conf_gw_node_t*> gateway = conf.gateway;
    DEBUG_LOG("gateway size : %ld", gateway.size());

    for (std::list<ims_conf_gw_node_t*>::iterator iter = gateway.begin(); iter != gateway.end();
            ++iter) {
        ims_conf_gw_node_t* gw = (*iter);

        char dest[100];
        ims_tool_t::inet_ntop(gw->ip, dest, 100);
        DEBUG_LOG("id  %u", gw->id);
        DEBUG_LOG("ip : %u  ||  %s", gw->ip, dest);
        DEBUG_LOG("port : %u", gw->port);
        DEBUG_LOG("max_conn : %u", gw->max_conn);
        DEBUG_LOG("user : %s", gw->user);
        DEBUG_LOG("pswd : %s", gw->pswd);

    }

    DEBUG_LOG("======== route ============");
    std::list<ims_conf_route_node_t*> route = conf.route;
    DEBUG_LOG("route size : %ld", route.size());

    for (std::list<ims_conf_route_node_t*>::iterator iter = route.begin(); iter != route.end();
            ++iter) {
        ims_conf_route_node_t* route = (*iter);
        DEBUG_LOG("name : %s", route->name);
        DEBUG_LOG("type : %u", route->type);
        DEBUG_LOG("field : %s", route->field);
        DEBUG_LOG("expression : %s", route->expression);
        DEBUG_LOG("rule_disp_caller : %s", route->rule_disp_caller);
        DEBUG_LOG("rule_call_caller : %s", route->rule_call_caller);
        DEBUG_LOG("rule_call_called : %s", route->rule_call_called);
    }

    DEBUG_LOG("***************** read conf end ************************************");
    return;
}


std::string ims_tool_t::get_assigned_caller(const std::string& dn, const std::string& ani) {
    std::string caller;
    std::string called;
    std::string disp;
    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    ims_conf_t& conf = pmgr->config();

    if (ims_tool_t::set_callno(ani, "", dn, conf, disp, caller, called)) {
        return caller;
    }

    return dn;
}

std::string ims_tool_t::get_assigned_called(const std::string& dnis, const std::string& ani) {
    std::string caller;
    std::string called;
    std::string disp;
    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    ims_conf_t& conf = pmgr->config();

    if (ims_tool_t::set_callno(ani, dnis, "", conf, disp, caller, called)) {
        return called;
    }

    return dnis;
}


std::string ims_tool_t::generate_uuid() {
    char uuid[40] = {0};
    uuid_t uucid;
    uuid_clear(uucid);
    uuid_generate(uucid);
    uuid_unparse(uucid, uuid);
    return uuid;
}

void ims_tool_t::prepare_call_event(ims::CallEventT& call_event,
                                    const uint64_t time,
                                    const ims::SessionIdT sid,
                                    const ims::CallIdT callid,
                                    const std::string& device,
                                    ims::CallStateT state) {
    call_event.timestamp = time;
    call_event.sessionid = sid;
    call_event.callid = callid;
    call_event.device = device;
    call_event.state = state;
    call_event.originatingParty = device;

    call_event.eventType = ims::CallEventTypeT::SG_UnKnownEvent;
    call_event.originalCallid = callid;
    call_event.partyNum = 1;
    call_event.otherDevice = "";
    call_event.otherAttr = ims::PartyAttributeT::P_Unknown;
    call_event.reason = ims::CallEventReasonT::ReasonSuccess;
    ims_session_manager_t::instance()->get_callercalled(
        sid, call_event.originalAni, call_event.originalDnis);
}

void  ims_tool_t::prepare_route_event(ims::RouteEventT& ims_event,
                                      ims::SessionIdT sessionid, const ims_route_info_t& info) {
    ims_event.timestamp   = get_timestamp_ms();
    ims_event.eventType   = ims::RouteEventTypeT::RT_RouteUnknown;
    ims_event.sessionid   = sessionid;
    ims_event.requestType = ims::RouteRequestTypeT::RR_TypeUnknown;
    ims_event.reason      = ims::RouteEventReasonT::RouteReasonOther;
    ims_event.requstid    = info.requestId;
    ims_event.callid      = info.callid;
    ims_event.targetDevice = info.targetUri;
    ims_event.destService = info.destService;
    ims_event.requestType = info.requestType;
    ims_event.requestArgs = info.requestArgs;
    ims_event.level       = info.level;
    ims_event.callerDn    = info.callerDn;
    ims_event.calleeDn    = info.calleeDn;
    ims_event.validtime   = info.validtime;
    ims_event.timeout     = info.timeout;
    ims_event.buffer      = info.buffer;
}

bool ims_tool_t::push_cancel_route_event(ims::SessionIdT sessionid) {
    ims_session_manager_t* session_mgr = ims_session_manager_t::instance();

    if (session_mgr->is_IVRoutbound_session(sessionid) ||
            session_mgr->is_IVRinbound_session(sessionid)) {
        TRACE_LOG("[%ld]current session is originated by IVR, cancel RouteRequest", sessionid);
        ims_route_info_t info;

        if (!session_mgr->rt_query_session_route(sessionid, info)) {
            WARNING_LOG("[%ld]rt_query_session_route failed.", sessionid);
            return false;
        }

        ims::RouteEventT ims_event;
        ims_tool_t::prepare_route_event(ims_event, sessionid, info);
        ims_event.eventType = ims::RouteEventTypeT::RT_RouteRequestCancel;
        ims_event.reason = ims::RouteEventReasonT::RouteReasonIVRCancel;

        return session_mgr->rt_add_imsevent_route(info.dest_reqid, ims_event);
    }

    return false;
}

bool ims_tool_t::is_accessible_ip(const std::string& addr, ims::ServiceTypeT type) {
    std::list<ims_conf_acl_node_t*> acl_nodes;
    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    uint32_t naddr = ims_tool_t::inet_pton(addr.c_str());

    // allow 127.0.0.1 and local ipv4 by default.
    if (is_local_ipv4(naddr)) {
        TRACE_LOG("is_accessible_ip(ip=%s is allowed by default.", addr.c_str());
        return true;
    }

    rw_lock_t lock(pmgr->config_lock());

    if (!lock.locked()) {
        WARNING_LOG("is_accessible_ip(ip=%s,type=%s)failed(lockerror)", addr.c_str(),
                    type.get_desc().c_str());
        return false;
    }

    switch (type.get_value()) {
    case ims::ServiceTypeT::ServiceIVR:
        if (pmgr->config().clients.count(ICCT_IVR) == 0) {
            WARNING_LOG("is_accessible_ip(ip=%s,type=%s)failed(IVR acl not exist)", addr.c_str(),
                        type.get_desc().c_str());
            return false;
        }

        acl_nodes = pmgr->config().clients[ICCT_IVR];
        break;

    case ims::ServiceTypeT::ServiceACD:
        if (pmgr->config().clients.count(ICCT_ACD) == 0) {
            WARNING_LOG("is_accessible_ip(ip=%s,type=%s)failed(ACD acl not exist)", addr.c_str(),
                        type.get_desc().c_str());
            return false;
        }

        acl_nodes = pmgr->config().clients[ICCT_ACD];
        break;

    case ims::ServiceTypeT::ServiceDS:
        break;

    default:
        WARNING_LOG("Unkonwn ServiceType:%s", type.get_desc().c_str());
        return false;
    }

    for (std::list<ims_conf_acl_node_t*>::iterator it = acl_nodes.begin(); it != acl_nodes.end();
            ++it) {
        //TRACE_LOG("acd_node:  (ip=%x,mask=%x)",(*it)->ip, (*it)->mask );
        //TRACE_LOG("loopback&mask=%x)",INADDR_LOOPBACK & (*it)->mask );
        if ((naddr & (*it)->mask) == (*it)->ip) {
            TRACE_LOG("ip=%s is allowed by (ip=%x,mask=%x)", addr.c_str(), (*it)->ip, (*it)->mask);
            return true;
        }
    }

    WARNING_LOG("is_accessible_ip(ip=%s,type=%s) denied by default", addr.c_str(),
                type.get_desc().c_str());
    return false;
}
