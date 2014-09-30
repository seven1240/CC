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

#include "node_jsonget_arraylen.h"
#include <json/json.h>
#include <sstream>

NodeJsonGetArrayLen::NodeJsonGetArrayLen(const uint32_t id, const string& name,
        const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeJsonGetArrayLen::~NodeJsonGetArrayLen(void) {
}

NodeBase* NodeJsonGetArrayLen::run(base_script_t* param) {
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    std::string len = "";
    std::string input = "";
    std::string key = "";
    variable_t var_len;
    variable_t var_reason;
    std::string reason_type_error = "reason type error";
    var_len.pvalue = &reason_type_error;
    var_reason.pvalue = &reason_type_error;

    if (param->name_var_map.find(_len) == param->name_var_map.end()) {
        IVR_WARN("not found variable %s", _len.c_str());
        goto LEAVE;
    }

    if (param->name_var_map.find(_reason) == param->name_var_map.end()) {
        IVR_WARN("not found variable %s", _reason.c_str());
        goto LEAVE;
    }

    var_len = param->name_var_map[_len];
    var_reason = param->name_var_map[_reason];

    if (var_reason.type != INT32) {
        IVR_WARN("变量%s 的类型错误", _reason.c_str());
        //(*(std::string*)var_reason.pvalue).assign("5");
        goto LEAVE;
    }

    if (var_len.type != INT32) {
        IVR_WARN("变量%s 的类型错误", _len.c_str());
        (*(std::string*)var_reason.pvalue).assign("21");
        goto LEAVE;
    }

    (*(std::string*)var_reason.pvalue).assign("0");
    (*(std::string*)var_len.pvalue).assign("");


    if (parse_all(_input, param->name_var_map, input)
            && parse_all(_key, param->name_var_map, key)) {
        //获取json串
        json_object* obj = json_tokener_parse(input.c_str());

        if (is_error(obj) || NULL == obj) {
            IVR_TRACE("未找到需要赋值的变量");
            (*(std::string*)var_reason.pvalue).assign("1");
            goto LEAVE;
        }

        const char* tmp = json_object_get_string(obj);

        if (tmp[0] >= '0' && tmp[0] <= '9') { // used to fix json-c bug, '0{abc}' will true
            IVR_TRACE("未找到需要赋值的变量");
            (*(std::string*)var_reason.pvalue).assign("1");
            json_object_put(obj);
            goto LEAVE;
        }

        //查找key
        json_object* obj_value = json_object_object_get(obj, key.c_str());

        if (is_error(obj_value) || NULL == obj_value) {
            IVR_TRACE("未找到key值");
            (*(std::string*)var_reason.pvalue).assign("2");
            json_object_put(obj);
            goto LEAVE;
        }

        //检查是否为array
        if (! json_object_is_type(obj_value, json_type_array)) {
            IVR_WARN("非array");
            (*(std::string*)var_reason.pvalue).assign("10");
            json_object_put(obj);
            //json_object_put(obj_value);
            goto LEAVE;
        }

        int32_t array_len = json_object_array_length(obj_value);
        char buffer[BUFSIZ];
        snprintf(buffer, BUFSIZ, "%d", array_len);
        (*(std::string*)var_len.pvalue).assign(buffer);
        exit = EXIT_SUCC;
        json_object_put(obj);
        //json_object_put(obj_value);
    }

LEAVE:
    IVR_TRACE("%s: Input:%s,Key:%s,Len:%s,Reason:%s exit from %s",
              leave(param->name_var_map).c_str(),
              input.c_str(), key.c_str(), (*(std::string*)var_len.pvalue).c_str(),
              (*(std::string*)var_reason.pvalue).c_str(), exit);
    return _exit_node_map[exit];
}

bool NodeJsonGetArrayLen::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_INPUT, _input)
           && valid_str(_key_map, PARAM_KEY, _key)
           && valid_str(_key_map, PARAM_LEN, _len)
           && valid_str(_key_map, PARAM_REASON, _reason);
}

std::string NodeJsonGetArrayLen::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Input:" << _input << ",Key:" << _key << ",len:" << _len << ",Reason:" << _reason;
    return ostm.str();
}

std::string NodeJsonGetArrayLen::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    return ostm.str();
}

const char* NodeJsonGetArrayLen::PARAM_INPUT = "input";
const char* NodeJsonGetArrayLen::PARAM_KEY = "key";
const char* NodeJsonGetArrayLen::PARAM_LEN = "len";
const char* NodeJsonGetArrayLen::PARAM_REASON = "reason";

const char* NodeJsonGetArrayLen::PARAMITEM_TYPE_STRING = "string";
const char* NodeJsonGetArrayLen::PARAMITEM_TYPE_INT32 = "int32";
const char* NodeJsonGetArrayLen::PARAMITEM_TYPE_BOOL = "bool";
