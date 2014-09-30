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

#include "tools.h"
#include "node_base.h"
#include "arithmetic_operate.h"
#include "common.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "statement.h"
#include "lock.h"


using namespace sql;

NodeBase::NodeBase(const uint32_t id, const string& name,
                   const string& type, const string& desc, const key_map_t& keymap):
    _id(id), _name(name), _type(type), _desc(desc), _key_map(keymap) {
    _system_invoke_vec.push_back(SYS_DATE);
    _system_invoke_vec.push_back(SYS_TIME);
    _system_invoke_vec.push_back(SYS_SEC);
    _system_invoke_vec.push_back(SYS_INBOUND_NUM);
    _system_invoke_vec.push_back(SYS_OUTBOUND_NUM);

    _function_vec.push_back(FUNC_STR_LEN);
    _function_vec.push_back(FUNC_STR_LEFT);
    _function_vec.push_back(FUNC_STR_RIGHT);
    _function_vec.push_back(FUNC_STR_FIND);
    _function_vec.push_back(FUNC_STR_SUB);
    _function_vec.push_back(FUNC_STR_REPLACE);
    _function_vec.push_back(FUNC_INT_RAND);
}

NodeBase::~NodeBase(void) {
    _key_map.clear();
    _exit_id_map.clear();
    _exit_node_map.clear();

    _system_invoke_vec.clear();
}

std::string NodeBase::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    std::string out;

    ostm << "\nENTER NODE:" << _id << ",TYPE:" << _type << ",DESC:" << _desc << " ";

    if (get_sys_var(vars, sys_var_t::ANI, out)) {
        ostm << "ANI:"  << out;
    }

    if (get_sys_var(vars, sys_var_t::DNIS, out)) {
        ostm << ",DNIS:"  << out;
    }

    if (get_sys_var(vars, sys_var_t::CALLID, out)) {
        ostm << ",CALLID:" << out << " ";
    }

    return ostm.str();
}

std::string NodeBase::leave(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    std::string out;

    ostm << "\nLEAVE NODE:" << _id << ",TYPE:" << _type << ",DESC:" << _desc << " ";

    if (get_sys_var(vars, sys_var_t::ANI, out)) {
        ostm << "ANI:"  << out;
    }

    if (get_sys_var(vars, sys_var_t::DNIS, out)) {
        ostm << ",DNIS:"  << out;
    }

    if (get_sys_var(vars, sys_var_t::CALLID, out)) {
        ostm << ",CALLID:" << out << " ";
    }

    return ostm.str();
}

bool NodeBase::key_map_find(string& key) {
    return (_key_map.find(key) != _key_map.end());
}

bool NodeBase::check_exit(string exit) {
    if (!key_map_find(exit)) {
        IVR_WARN("%s %s 事件出口未配置", exit.c_str(), _name.c_str());
        return false;
    }

    string exit_id = _key_map[exit.c_str()];

    if (!ivr_tools_t::is_nonnegative_integer(exit_id)) {
        IVR_WARN("%s %s 事件出口配置错误", exit.c_str(), _name.c_str());
        return false;
    }

    uint32_t id = atoi(exit_id.c_str());
    _exit_id_map[exit.c_str()] = id;
    return true;
}

bool NodeBase::load_other() {
    return (check_exit(EXIT_SUCC) && check_exit(EXIT_FAIL));
}


//系统调用
bool NodeBase::system_invoke(const string& system, std::string& out) {
    time_t rawtime;
    struct tm timeinfo;
    char buffer [20];
    bool result = false;

    time(&rawtime);
    localtime_r(&rawtime, &timeinfo);

    if (ivr_tools_t::str_eq(system, SYS_DATE)) {
        strftime(buffer, 20, "%Y%m%d", &timeinfo);
        out = buffer;
        result = true;
    } else if (ivr_tools_t::str_eq(system, SYS_TIME)) {
        strftime(buffer, 20, "%H:%M:%S", &timeinfo);
        out = buffer;
        result = true;
    } else if (ivr_tools_t::str_eq(system, SYS_SEC)) {
        snprintf(buffer, 20, "%ld", rawtime);
        out = buffer;
        result = true;
    } else if (ivr_tools_t::str_eq(system, SYS_INBOUND_NUM)) {
        ostringstream ostm;
        {
            rw_lock_t lock(g_inbound_chan_rwlock);

            if (lock.locked()) {
                ostm << g_inbound_chan_num;
                result = true;
            } else {
                ostm << 0;
            }
        }
        out = ostm.str();
    } else if (ivr_tools_t::str_eq(system, SYS_OUTBOUND_NUM)) {
        ostringstream ostm;
        {
            rw_lock_t lock(g_autorun_chan_rwlock);

            if (lock.locked()) {
                ostm << g_autorun_chan_num;
                result = true;
            } else {
                ostm << 0;
            }
        }

        out = ostm.str();
    } else {
        IVR_WARN("%s  不存在的系统调用", system.c_str());
        out = system;
    }

    return result;
}


//数据库函数调用
bool NodeBase::db_func_invoke(const string& func, const string& name, uint32_t param,
                              const map<string, variable_t>& name_var_map, std::string& out) {
    bool result = true;

    map<string, variable_t>::const_iterator it = name_var_map.find(name);

    if (it != name_var_map.end()) {
        const variable_t& var = it->second;
        ResultSet* rs = (ResultSet*)var.pvalue;

        if (rs) {
            if (ivr_tools_t::str_eq(func, FUNC_DB_NEXT)) {
                if (rs->next()) {
                    out = "1";
                } else {
                    out = "0";
                }
            } else if (ivr_tools_t::str_eq(func, FUNC_DB_VAL)) {
                try {
                    out = rs->getString(param);
                } catch (...) {
                    IVR_WARN("%s  %s(%u) 数据库调用 错误",
                             name.c_str(), func.c_str(), param);
                    result = false;
                }
            }
        }
    } else {
        result = false;
    }

    return result;
}


//MAP函数调用
bool NodeBase::map_func_invoke(const string& func, const string& name, const string& param,
                               const map<string, variable_t>& name_var_map, std::string& out) {
    bool result = true;
    map<string, variable_t>::const_iterator it = name_var_map.find(name);

    if (it != name_var_map.end()) {
        const variable_t& var = it->second;
        key_map_t* keymap = (key_map_t*)var.pvalue;

        if (keymap) {
            if (ivr_tools_t::str_eq(func, FUNC_MAP_VAL)) {
                if (keymap->find(param) != keymap->end()) {
                    out = (*keymap)[param];
                } else {
                    result = false;
                }
            }
        }
    } else {
        result = false;
    }

    return result;
}

//字符串函数调用
bool NodeBase::str_func_invoke(const string& func, const string& param, string& out) {
    bool result = true;

    if (ivr_tools_t::str_eq(func, FUNC_STR_LEN)) {
        ostringstream ostm;
        ostm << param.length();
        out = ostm.str();
    } else if (ivr_tools_t::str_eq(func, FUNC_STR_LEFT)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);

        if (vec.size() == 2 && atoi(vec[1].c_str()) > 0) {
            out = vec[0].substr(0, atoi(vec[1].c_str()));
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    } else if (ivr_tools_t::str_eq(func, FUNC_STR_RIGHT)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);

        if (vec.size() == 2) {
            uint32_t len = vec[0].length();

            if (atoi(vec[1].c_str()) < 0 || len < (uint32_t)atoi(vec[1].c_str())) {
                IVR_WARN("%s %s,字符串函数 长度越界", func.c_str(), param.c_str());
                return false;
            } else {
                out = vec[0].substr(len - atoi(vec[1].c_str()), atoi(vec[1].c_str()));
            }
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    } else if (ivr_tools_t::str_eq(func, FUNC_STR_FIND)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);

        if (2 == vec.size()) {
            IVR_WARN("STARS: %s,%s", vec[0].c_str(), vec[1].c_str());
            string::size_type first = vec[0].find(vec[1]);
            ostringstream ostm;

            if (first == string::npos) {
                ostm << -1;
            } else {
                ostm << first;
            }

            out = ostm.str();
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    } else if (ivr_tools_t::str_eq(func, FUNC_STR_SUB)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);

        if (3 == vec.size()) {
            int32_t para1 = atoi(vec[1].c_str());
            int32_t para2 = atoi(vec[2].c_str());
            uint32_t len = vec[0].length();

            if (para1 < 0 || len < (uint32_t)para1) {
                IVR_WARN("%s %s,字符串函数 长度越界", func.c_str(), param.c_str());
                result = false;
            } else if (para1 >= 0 && para2 > 0) {
                out = vec[0].substr(para1, para2);
            } else {
                IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
                result = false;
            }
        } else if (2 == vec.size()) {
            int32_t para1 = atoi(vec[1].c_str());
            uint32_t len = vec[0].length();

            if (para1 < 0 || len < (uint32_t)para1) {
                IVR_WARN("%s %s,字符串函数 长度越界", func.c_str(), param.c_str());
                result = false;
            } else if (para1 >= 0) {
                out = vec[0].substr(para1);
            } else {
                IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
                result = false;
            }
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    } else if (ivr_tools_t::str_eq(func, FUNC_STR_REPLACE)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);

        if (3 == vec.size()) {
            string para0 = vec[0];
            string src = vec[1];
            string dest = vec[2];
            uint32_t len = src.length();

            if (0 == len) {
                IVR_WARN("%s %s,字符串函数 长度为0", func.c_str(), param.c_str());
                result = false;
            }

            std::string::size_type pos_begin = 0;
            std::string::size_type pos = para0.find(src);

            while (pos != std::string::npos) {
                out.append(para0.data() + pos_begin, pos - pos_begin);
                out += dest;
                pos_begin = pos + len;
                pos = para0.find(src, pos_begin);
            }

            if (pos_begin < para0.length()) {
                out.append(para0.begin() + pos_begin, para0.end());
            }
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    } else if (ivr_tools_t::str_eq(func, FUNC_INT_RAND)) {
        vector<string> vec;
        ivr_tools_t::split_string(param, ",", vec);
        srand(time(0));

        if (2 == vec.size()) {
            int32_t para1 = atoi(vec[0].c_str());
            int32_t para2 = atoi(vec[1].c_str());

            if (para1 >= 0 && para2 >= 0 && para1 < para2) {
                int ir = rand() % (para2 - para1 + 1) + para1;
                std::ostringstream oss;
                oss << ir;
                out = oss.str();
            } else {
                IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
                result = false;
            }
        } else {
            IVR_WARN("%s %s 字符串函数 参数错误", func.c_str(), param.c_str());
            result = false;
        }
    }

    return result;
}


//解析变量
bool NodeBase::parse_variable(const string& exp_, const map<string, variable_t>& name_var_map,
                              string& out) {
    out = exp_;

    for (map<string, variable_t>::const_iterator it = name_var_map.begin();
            it != name_var_map.end(); ++ it) {
        size_t pos = string::npos;

        do {
            pos = string::npos;
            string tmp = "${" + it->first + "}";

            pos = out.find(tmp);

            if (pos != string::npos) {
                if (it->second.type == INT32 || it->second.type == STRING) {
                    string* pval = (string*)it->second.pvalue;

                    if (pval) {
                        out.replace(pos, tmp.size(), *pval);
                    }
                } else {
                    break;
                }
            }
        } while (pos != string::npos);
    }

    return true;
}


//解析系统调用
bool NodeBase::parse_sys_invoke(const string& exp_, const map<string, variable_t>& name_var_map,
                                string& out) {
    out = exp_;

    for (uint32_t i = 0; i < _system_invoke_vec.size(); i ++) {
        size_t pos = string::npos;

        do {
            pos = string::npos;
            string tmp = "${" + _system_invoke_vec[i] + "}";

            pos = out.find(tmp);
            std::string tmp_out;

            if (pos != string::npos) {
                if (!system_invoke(_system_invoke_vec[i], tmp_out)) {
                    return false;
                } else {
                    out.replace(pos, tmp.size(), tmp_out);
                }
            }
        } while (pos != string::npos);
    }

    return true;
}


//解析函数调用
bool NodeBase::parse_function(const string& exp_, const map<string, variable_t>& name_var_map,
                              string& out) {
    out = exp_;

    //解析字符串函数
    for (uint32_t i = 0; i < _function_vec.size(); i++) {
        size_t head = string::npos;
        size_t tail = string::npos;

        do {
            string tmp = _function_vec[i] + "(";
            head = string::npos;
            tail = string::npos;

            head = out.find(tmp);

            if (head != string::npos) {

                tail = out.find(")", head + 1);

                if (tail != string::npos) {

                    //找到了正确格式的函数 和 参数
                    uint32_t len = _function_vec[i].length();
                    string param = out.substr(head + len + 1, tail - head - len - 1);
                    string func_result;

                    if (str_func_invoke(_function_vec[i], param, func_result)) {
                        out.replace(head, tail - head + 1, func_result);
                    } else {
                        return false;
                    }
                }
            }
        } while (head != string::npos);
    }

    //解析数据库函数
    for (map<string, variable_t>::const_iterator it = name_var_map.begin();
            it != name_var_map.end(); it++) {

        if (it->second.type == RESULTSET) {

            // NEXT函数
            size_t pos = string::npos;

            do {
                pos = string::npos;
                string tmp = "${" + it->second.name + "}.next()";

                pos = out.find(tmp);

                if (pos != string::npos) {
                    string func = FUNC_DB_NEXT;
                    std::string db_result;

                    if (db_func_invoke(func, it->second.name, 0, name_var_map, db_result)) {
                        out.replace(pos, tmp.size(), db_result);
                        return true;
                    } else {
                        return false;
                    }
                }
            } while (pos != string::npos);

            // VALUE函数
            size_t head = string::npos;

            do {
                head = string::npos;
                string tmp = "${" + it->second.name + "}.value(";

                head = out.find(tmp);

                if (head != string::npos) {

                    size_t tail = string::npos;
                    tail = out.find(")", head);
                    uint32_t param = 0;

                    if (tail != string::npos) {
                        string str = out.substr(head + tmp.length(), tail - head - tmp.length());
                        param = atoi(str.c_str());

                        if (param == 0) {
                            IVR_WARN("数据库调用 参数不正确 %s", out.c_str());
                            return false;
                        }
                    } else {
                        IVR_WARN("数据库函数格式错误 %s", out.c_str());
                        return false;
                    }

                    string func = FUNC_DB_VAL;
                    std::string db_result;

                    if (db_func_invoke(func, it->second.name, param, name_var_map, db_result)) {
                        out.replace(head, tail - head + 1, db_result);
                    } else {
                        return false;
                    }
                }
            } while (head != string::npos);
        }
    }

    //解析MAP类型的函数
    for (map<string, variable_t>::const_iterator it = name_var_map.begin();
            it != name_var_map.end(); it++) {

        if (it->second.type == MAP) {

            // VALUE函数
            size_t head = string::npos;

            do {
                head = string::npos;
                string tmp = "${" + it->second.name + "}.value(";

                head = out.find(tmp);

                if (head != string::npos) {

                    size_t tail = string::npos;
                    tail = out.find(")", head);
                    string param;

                    if (tail != string::npos) {
                        param = out.substr(head + tmp.length(), tail - head - tmp.length());

                        if (param == "") {
                            IVR_WARN("MAP类型函数调用 参数不正确 %s", out.c_str());
                            return false;
                        }
                    } else {
                        IVR_WARN("MAP类型函数格式错误 %s", out.c_str());
                        return false;
                    }

                    string func = FUNC_MAP_VAL;
                    string map_result;

                    if (map_func_invoke(func, it->second.name, param, name_var_map, map_result)) {
                        out.replace(head, tail - head + 1, map_result);
                    } else {
                        return false;
                    }
                }
            } while (head != string::npos);

        }
    }

    return true;
}


//解析表达式
bool NodeBase::parse_expression(const string exp_, const map<string, variable_t>& name_var_map,
                                string& out) {
    std::string out2 = exp_;

    if (parse_variable(out2, name_var_map, out)
            && parse_sys_invoke(out, name_var_map, out2)
            && parse_function(out2, name_var_map, out)) {
        int32_t result = 0;
        ArithmeticOperate arithmetic;

        //如果是算术表达式 就进行计算
        if (arithmetic.calculate(out2.c_str(), result)) {
            ostringstream ostm;
            ostm << result;
            out = ostm.str();
        }

        return true;
    }

    return false;
}

bool NodeBase::valid_str(key_map_t& vars, const char* key, std::string& out, bool trim) {
    key_map_t::iterator it = vars.find(key);

    if (it == vars.end() || (out = (trim ? ivr_tools_t::delete_blank(it->second) : it->second)) == "") {
        IVR_WARN("parameter %s is invalid", key);
        return false;
    }

    return true;

}

bool NodeBase::valid_str(key_map_t& vars, const char* key, uint32_t& out) {
    std::string str;

    if (valid_str(vars, key, str) && ivr_tools_t::is_positive_integer(str)) {
        out = atoi(str.c_str());
        return true;
    } else {
        IVR_WARN("parameter %s is invalid(%s)", key, str.c_str());
    }

    return false;
}

bool NodeBase::parse_all(const std::string exp, const map<string, variable_t>& name_var_map,
                         string& out) {
    std::string out_tmp = exp;
    return parse_variable(out_tmp, name_var_map, out)
           && parse_sys_invoke(out, name_var_map, out_tmp)
           && parse_function(out_tmp, name_var_map, out);
}


const char* NodeBase::EXIT_SUCC = "_success";
const char* NodeBase::EXIT_FAIL = "_failure";

const char* NodeBase::SYS_DATE = "_date";
const char* NodeBase::SYS_TIME = "_time";
const char* NodeBase::SYS_SEC = "_second";
const char* NodeBase::SYS_INBOUND_NUM = "_inbound_num";
const char* NodeBase::SYS_OUTBOUND_NUM = "_autorun_num";

const char* NodeBase::SYS_ANSWER_TIME = "_call_answer_time";
const char* NodeBase::SYS_HANGUP_CAUSE = "_hangup_cause";


const char* NodeBase::FUNC_STR_LEN = "length";
const char* NodeBase::FUNC_STR_LEFT = "left";
const char* NodeBase::FUNC_STR_RIGHT = "right";
const char* NodeBase::FUNC_STR_FIND = "find";
const char* NodeBase::FUNC_STR_SUB = "sub";
const char* NodeBase::FUNC_STR_REPLACE = "replace";
const char* NodeBase::FUNC_INT_RAND = "rand";
const char* NodeBase::FUNC_DB_NEXT = "next";
const char* NodeBase::FUNC_DB_VAL = "value";
const char* NodeBase::FUNC_MAP_VAL = "value";

const char* NodeBase::HANGUP_CAUSE_SYS = "system_hangup";
const char* NodeBase::HANGUP_CAUSE_USER = "user_hangup";
const char* NodeBase::HANGUP_CAUSE_THIRD = "third_hangup";
