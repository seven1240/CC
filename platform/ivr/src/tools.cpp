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

#include <errno.h>
#include "tools.h"
#include "db_pool.h"

int32_t ivr_tools_t::get_abs_timespec(struct timespec* ts, int32_t milliSeconds) {
    struct timeval tp;
    int32_t rv;

    if (NULL == ts) {
        return -1;
    }

    rv = gettimeofday(&tp, NULL);

    if (0 != rv) {
        return -1;
    }

    ts->tv_sec = tp.tv_sec;
    ts->tv_nsec = tp.tv_usec * 1000UL;

    ts->tv_sec += milliSeconds / 1000UL;
    ts->tv_nsec += milliSeconds % 1000UL * 1000000UL;

    ts->tv_sec += ts->tv_nsec / (1000UL * 1000UL * 1000UL);
    ts->tv_nsec %= (1000UL * 1000UL * 1000UL);

    return 0;
}

uint64_t ivr_tools_t::get_timestamp_ms() {
    timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

bool ivr_tools_t:: check_port(const char* src, uint32_t& result) {
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

bool ivr_tools_t::check_ip(const char* src, uint32_t& result) {
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

bool ivr_tools_t::is_positive_integer(std::string& str) {
    if (str.size() == 0 || str.at(0) == '0') {
        return false;
    }

    for (uint32_t i = 0; i < str.size(); i++) {
        if (!isdigit(str.at(i))) {
            return false;
        }
    }

    uint32_t len = str.length();

    if (len > 10) {
        return false;
    } else if (10 == len && str > "2147483647") {
        return false;
    }

    return true;

}

bool ivr_tools_t::is_nonnegative_integer(std::string& str) {
    return ("0" == str) || is_positive_integer(str);
}

bool ivr_tools_t::is_integer(std::string& str) {
    if ("0" == str) {
        return true;
    } else if (str.empty()) {
        return false;
    } else if ('-' == str.at(0)) {
        std::string str2 = str.substr(1);
        return is_positive_integer(str2);
    }

    return is_positive_integer(str);
}

bool ivr_tools_t::is_all_digit(std::string& str) {
    if (str.size() == 0) {
        return false;
    }

    for (uint32_t i = 0; i < str.size(); i++) {
        if (!isdigit(str.at(i))) {
            return false;
        }
    }

    return true;
}

bool ivr_tools_t::split_string(const std::string& src,
                               const std::string& separator, std::vector<std::string>& dest) {

    if (src.size() == 0) {
        return false;
    }

    size_t old_pos = 0;
    size_t new_pos = 0;
    std::string tmp_data;

    while (true) {
        new_pos = src.find(separator, old_pos);

        if (new_pos != std::string::npos) {
            tmp_data = src.substr(old_pos, new_pos - old_pos);
            dest.push_back(tmp_data);
            old_pos = new_pos + separator.size();
        } else if (old_pos <= src.size()) {
            tmp_data = src.substr(old_pos);
            dest.push_back(tmp_data);
            break;
        } else {
            break;
        }
    }

    return true;

}

std::string ivr_tools_t::get_current_second() {
    time_t tm = time(NULL);

    char ret[15] = {0};

    sprintf(ret, "%ld", tm);

    return ret;

}

std::string ivr_tools_t::format_datatime_str(std::string& second) {
    time_t rawtime = atol(second.c_str());
    struct tm timeinfo;
    char buffer[25] = {0};

    if (localtime_r(&rawtime, &timeinfo)) {
        strftime(buffer, 25, "%Y-%m-%d %H:%M:%S", &timeinfo);
    }

    return buffer;

}

bool ivr_tools_t::str2double(const std::string& str, double& value) {
    std::string str_tmp = str;
    trim(str_tmp);

    const char* s = str_tmp.c_str();
    char* endptr = NULL;

    value = strtod(s, &endptr);

    if ((value ==  std::numeric_limits<double>::infinity()) ||
            (value == -std::numeric_limits<double>::infinity())) {
        return false;
    }

    if (endptr == s) {
        return false;
    }

    while (isspace(*endptr)) {
        ++endptr;
    }

    return (*endptr == '\0');// && (errno == 0);
}

void ivr_tools_t::trim(std::string& str) {
    str.erase(str.find_last_not_of("\t ") + 1);
    str.erase(0, str.find_first_not_of("\t "));
}

void ivr_tools_t::idx2vec(const char* prefix,
                          const section_map_t& sec, std::vector<uint32_t>& vec) {
    if (sec.size() == 0) {
        return;
    }

    std::vector<std::string> key_vec;

    for (section_map_t::const_iterator it = sec.begin(); it != sec.end(); ++it) {
        key_vec.push_back(it->first);
    }

    idx2vec_imp(prefix, key_vec, vec);

}

void ivr_tools_t::idx2vec(const char* prefix,
                          const key_map_t& sec, std::vector<uint32_t>& vec) {
    if (sec.size() == 0) {
        return;
    }

    std::vector<std::string> key_vec;

    for (key_map_t::const_iterator it = sec.begin(); it != sec.end(); ++it) {
        key_vec.push_back(it->first);
    }

    idx2vec_imp(prefix, key_vec, vec);


}
void ivr_tools_t::idx2vec_imp(const char* prefix,
                              const std::vector<std::string>& sec, std::vector<uint32_t>& vec) {
    size_t len_prefix = 0;

    if (NULL == prefix || (len_prefix = strlen(prefix)) == 0) {
        return;
    }

    vec.clear();

    size_t len_str = 0;
    std::string idx_str;

    for (std::vector<std::string>::const_iterator it = sec.begin(); it != sec.end(); ++it) {
        len_str = it->size();

        if (len_prefix >= len_str) {
            continue;
        }

        if (strcasecmp(it->substr(0, len_prefix).c_str(), prefix) == 0) {
            idx_str = it->substr(len_prefix, len_str - len_prefix);

            if (is_positive_integer(idx_str)) {
                vec.push_back(atoi(idx_str.c_str()));
            }
        }
    }

    sort(vec.begin(), vec.end());
}

bool ivr_tools_t::str_eq(const std::string& str, const char* sz) {
    if (NULL == sz) {
        return false;
    }

    std::string clean_str = str;
    trim(clean_str);

    return (strcasecmp(str.c_str(), sz) == 0);

}

bool ivr_tools_t::check_and_create_dir(const char* dirname) {
    struct stat _stat;

    if (stat(dirname, &_stat) != 0 || !S_ISDIR(_stat.st_mode)) { //目录不存在
        ostringstream ostm;
        ostm << "mkdir -p " << dirname;
        return (system(ostm.str().c_str()) == 0);
    }

    return true;
}

std::string ivr_tools_t::delete_blank(const std::string& exp) {
    vector<string> vec;
    split_string(exp, " ", vec);

    ostringstream ostm;

    for (uint32_t i = 0; i < vec.size(); i++) {
        ostm << vec[i];
    }

    return ostm.str();
}

std::string ivr_tools_t::map2str(const std::map<std::string, std::string>& val) {
    ostringstream ostm;

    for (std::map<std::string, std::string>::const_iterator it = val.begin();
            it != val.end(); ++it) {
        ostm << it->first << ":" << it->second << ",";
    }

    return ostm.str();
}

void ivr_tools_t::build_vars(const std::map<std::string, variable_t>& temp,
                             std::map<std::string, variable_t>& out) {
    for (std::map<std::string, variable_t>::const_iterator it = temp.begin();
            it != temp.end(); ++it) {
        variable_t var = it->second;
        var.pvalue = NULL;

        if (INT32 == var.type || STRING == var.type) {
            var.pvalue = new std::string;

            *(std::string*)(var.pvalue) = var.initial;
        } else if (MAP == var.type) {
            var.pvalue = new key_map_t;
        }

        //resultset部分由node_db来设置

        out[var.name] = var;
    }
}

void ivr_tools_t::destroy_vars(std::map<std::string, variable_t>& vars) {
    for (std::map<std::string, variable_t>::iterator it = vars.begin();
            it != vars.end(); ++it) {

        if (INT32 == it->second.type || STRING == it->second.type) {
            delete(std::string*)(it->second.pvalue);
        } else if (MAP == it->second.type) {
            delete(key_map_t*)(it->second.pvalue);
        } else if (RESULTSET == it->second.type) {
            sql::ResultSet* result = (sql::ResultSet*)(it->second.pvalue);

            /*
            if(result&&!result->isClosed()){
                result->close();
            }*/
            //delete result->getStatement();
            if (result) {
                delete result->getStatement();
                delete result;
            }
        }

        it->second.pvalue = NULL;
    }

    vars.clear();
}

const char* ivr_tools_t::inet_ntop(uint32_t src, char* dest, uint32_t dest_len) {
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

std::string ivr_tools_t::chlname2no(const std::string& src) {
    std::string ret;

    if (chlname2no(src, ret)) {
        return ret;
    } else {
        return src;
    }
}

bool ivr_tools_t::chlname2no(const std::string& src, std::string& dest) {

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

void ivr_tools_t::safe_sleeps(uint32_t s) {
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

void ivr_tools_t::safe_sleepms(uint32_t ms) {
    struct timespec interval, remainder;
    interval.tv_sec = ms / 1000;
    interval.tv_nsec = (ms % 1000) * 1000000;
    int32_t rr = -1;

    if ((rr = nanosleep(&interval, &remainder)) == -1) {
        while (EINTR == errno && -1 == rr) {
            rr = nanosleep(&remainder, &remainder);
        }
    }
}

std::string ivr_tools_t::get_address(uint32_t ip) {
    std::ostringstream ss;
    ss << ((ip >> 24) & 0xff) << "." << ((ip >> 16) & 0xff) << "." << ((ip >> 8) & 0xff) << "." <<
       (ip & 0xff);
    return ss.str();
}

std::string ivr_tools_t::get_callsource(uint32_t ip, uint32_t port) {
    std::ostringstream ss;
    ss << "-h " << get_address(ip)
       << " -p " << port;
    return ss.str();
}

std::string ivr_tools_t::get_callsource(const std::string& ip, uint32_t port) {
    uint32_t uip = 0;

    if (!ivr_tools_t::check_ip(ip.c_str(), uip)) {
        return "";
    }

    return get_callsource(uip, port);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
