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
#include "node_compare.h"

NodeCompare::NodeCompare(const uint32_t id, const string& name,
                         const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeCompare::~NodeCompare(void) {
}

NodeBase* NodeCompare::run(base_script_t* param) {
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    bool ret = parse_logic(_exp, param->name_var_map);
    const char* _exit = (ret ? EXIT_SUCC : EXIT_FAIL);

    IVR_TRACE("%sexit from %s(%s)",
              leave(param->name_var_map).c_str(), _exit, ret ? "true" : "false");

    return _exit_node_map[_exit];
}

bool NodeCompare::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_EXP, _exp);
}

const char* NodeCompare::PARAM_EXP = "exp";

//解析 逻辑表达式
bool NodeCompare::parse_logic(string exp_, map<string, variable_t>& name_var_map) {
    std::string exp;
    vector<string> vec;

    if (!parse_all(exp_, name_var_map, exp)) {
        IVR_WARN("parse failed(%s,%s)", exp.c_str(), exp_.c_str());
        return false;

    }

    //字符串 相等
    if (exp.find(STR_E, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_E, vec);
        return vec.size() >= 2 && vec[0] == vec[1];
    }

    //字符串 不相等
    if (exp.find(STR_NE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_NE, vec);
        return vec.size() >= 2 && vec[0] != vec[1];
    }

    //字符串 大于
    if (exp.find(STR_G, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_G, vec);
        return vec.size() >= 2 && vec[0] > vec[1];
    }

    //字符串 小于
    if (exp.find(STR_L, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_L, vec);
        return vec.size() >= 2 && vec[0] < vec[1];
    }

    //字符串 大于等于
    if (exp.find(STR_GE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_GE, vec);
        return vec.size() >= 2 && vec[0] >= vec[1];
    }

    //字符串 小于等于
    if (exp.find(STR_LE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, STR_LE, vec);
        return vec.size() >= 2 && vec[0] <= vec[1];
    }

    //数值 大于等于
    if (exp.find(GE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, GE, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) >= atoi(vec[1].c_str());
    }

    //数值 小于等于
    if (exp.find(LE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, LE, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) <= atoi(vec[1].c_str());
    }

    //数值 相等
    if (exp.find(E, 0) != string::npos) {
        ivr_tools_t::split_string(exp, E, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) == atoi(vec[1].c_str());
    }

    //数值 不相等
    if (exp.find(NE, 0) != string::npos) {
        ivr_tools_t::split_string(exp, NE, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) != atoi(vec[1].c_str());
    }

    //数值 大于
    if (exp.find(G, 0) != string::npos) {
        ivr_tools_t::split_string(exp, G, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) > atoi(vec[1].c_str());
    }

    //数值 小于
    if (exp.find(L, 0) != string::npos) {
        ivr_tools_t::split_string(exp, L, vec);
        return vec.size() >= 2 && atoi(vec[0].c_str()) < atoi(vec[1].c_str());
    }

    IVR_WARN("比较表达式%s格式错误", exp.c_str());
    return false;
}

std::string NodeCompare::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Exp:" << _exp;
    return ostm.str();
}

std::string NodeCompare::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "Exp:" << _exp;
    return ostm.str();
}


const char* NodeCompare::STR_E = "===";
const char* NodeCompare::STR_NE = "=!=";
const char* NodeCompare::STR_L = "=<<";
const char* NodeCompare::STR_LE = "=<=";
const char* NodeCompare::STR_G = "=>>";
const char* NodeCompare::STR_GE = "=>=";

const char* NodeCompare::E = "==";
const char* NodeCompare::GE = ">=";
const char* NodeCompare::LE = "<=";
const char* NodeCompare::NE = "!=";

const char* NodeCompare::L = "<";
const char* NodeCompare::G = ">";

