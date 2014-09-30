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

#ifndef _NODE_BASE_H_
#define _NODE_BASE_H_

#include "common.h"
#include "fs_operator.h"
#include "tools.h"
struct base_script_t;

class NodeBase {
public:
    NodeBase(const uint32_t id, const string& name,
             const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeBase(void);

    virtual NodeBase* run(base_script_t* param) = 0;

    virtual bool load_other();

public:

    /**
     * @brief 判断map中是否有需要的变量,如果有，则赋值给out
     *
     * @param [in/out] vars   : key_map_t&
     * @param [in/out] key   : const char*
     * @param [in/out] out   : std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/06 14:17:04
     **/
    bool valid_str(key_map_t& vars, const char* key, std::string& out, bool trim = true);

    /**
     * @brief
     *
     * @param [in/out] vars   : key_map_t&
     * @param [in/out] key   : const char*
     * @param [in/out] out   : int32_t&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/06 15:55:47
     **/
    bool NodeBase::valid_str(key_map_t& vars, const char* key, uint32_t& out);

    static bool get_sys_var(const map<string, variable_t>& vars, uint32_t type,
                            std::string& out) {
        bool result = false;

        if (type >= _sys_var_t::END) {
            return false;
        }

        map<string, variable_t>::const_iterator it = vars.find(SYS_VAR[type]);

        if (it != vars.end() && NULL != it->second.pvalue) {
            out = *(string*)(it->second.pvalue);
            result = true;
        }

        return result;
    }
    /**
     * @brief 进入节点
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  const char*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/01 14:31:23
     **/
    virtual std::string enter(const map<string, variable_t>& vars)const ;
    /**
     * @brief 离开节点
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  const char*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/01 14:31:34
     **/
    virtual std::string leave(const map<string, variable_t>& vars)const ;

    /**
     * @brief 封装了key_map的查找函数
     *
     * @param [in/out] key   : string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:54:36
     **/
    bool key_map_find(string& key);

    /**
     * @brief  封装了节点事件出口的检测
     *
     * @param [in/out] exit   : string
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:54:52
     **/
    bool check_exit(string exit);

    /**
     * @brief 系统调用
     *
     * @param [in/out] system   : string&
     * @return  string
     * @retval
     * @see
     * @note 目前支持的系统调用：
     *          _DATE：当前日期
     *          _TIME：当前时间
     *          _SECOND：1970-1-1 08:00:00 之后经过的秒数
     *          _INBOUND_NUM：呼入占用的通道数
     *          _AUTORUN_NUM：外呼占用的通道数
     * @author chenyuzhen
     * @date 2011/09/02 10:38:09
     **/
    bool system_invoke(const std::string& system, std::string& out);

    /**
     * @brief 字符串函数
     *
     * @param [in/out] func   : string&
     * @param [in/out] param   : string&
     * @return  bool 仅仅在找到了函数，且函数执行失败的时候发挥false
     *               其他情况下返回true
     * @retval
     * @see
     * @note 目前支持的字符串函数有：
     *          LENGTH：获取字符串的长度 LENGTH(str)
     *          LEFT：获取字符串左边n个字符LEFT(str,n)
     *          RIGHT：获取字符串右边n个字符RIGHT(str,n)
     * @author chenyuzhen
     * @date 2011/09/02 10:48:04
     **/
    bool str_func_invoke(const string& func, const string& param, std::string& out);


    bool db_func_invoke(const string& func, const string& name, uint32_t param,
                        const map<string, variable_t>& name_var_map, std::string& out);

    bool map_func_invoke(const string& func, const string& name, const string& param,
                         const map<string, variable_t>& name_var_map, std::string& out);
    /**
     * @brief 解析表达式，转换为系统函数的调用
     *
     * @param [in] exp   : string&
     * @param [in] name_var_map   : map<string,variable_t>&
     * @return  string&
     * @retval
     * @see system_invoke
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:48:04
     **/
    bool parse_sys_invoke(const string& exp, const map<string, variable_t>& name_var_map,
                          string& out);

    /**
     * @brief 解析流程级别的表达式，替换为流程级别的变量值
     *
     * @param [in] exp   : string&
     * @param [in] name_var_map   : map<string,variable_t>&
     * @return  string&
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:48:04
     **/
    bool parse_variable(const string& exp_, const map<string, variable_t>& name_var_map,
                        string& out);

    /**
     * @brief 解析函数调用，然后调用相关函数完成相关功能
     *
     * @param [in] exp   : string&
     * @param [in] name_var_map   : map<string,variable_t>&
     * @return  string&
     * @retval
     * @see str_func_invoke,db_func_invoke,map_func_invoke
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:48:04
     **/
    bool parse_function(const string& exp_, const map<string, variable_t>& name_var_map,
                        string& out);

    /**
     * @brief 解析表达式的统一入口
     *
     * @param [in] exp   : string&
     * @param [in] name_var_map   : map<string,variable_t>&
     * @return  string&
     * @retval
     * @see parse_function,parse_variable,parse_sys_invoke
     * @note
     * @author chenyuzhen
     * @date 2011/09/02 10:48:04
     **/
    bool parse_expression(const string exp, const map<string, variable_t>& name_var_map,
                          string& out);

    /**
     * @brief 所有表达式进行转换
     *
     * @param [in/out] exp   : const std::string
     * @param [in/out] map<string   : const
     * @param [in/out] name_var_map   : variable_t>&
     * @param [in/out] out   : string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/21 12:35:35
    **/
    bool parse_all(const std::string exp, const map<string, variable_t>& name_var_map,
                   string& out);

public:
    uint32_t      _id;
    string        _name;
    string        _desc;
    string        _type;
    key_map_t     _key_map;

    map<string, uint32_t>  _exit_id_map;     //事件出口到节点ID的映射
    map<string, NodeBase*> _exit_node_map;   //事件出口到节点对象的映射

    vector<string> _system_invoke_vec;
    vector<string> _function_vec;

protected:
    const static char* EXIT_SUCC;         ///<
    const static char* EXIT_FAIL;         ///<
    const static char* SYS_DATE;          ///<
    const static char* SYS_TIME;          ///<
    const static char* SYS_SEC;           ///<
    const static char* SYS_INBOUND_NUM;           ///<
    const static char* SYS_OUTBOUND_NUM;          ///<
    const static char* SYS_ANSWER_TIME;           ///<
    const static char* SYS_HANGUP_CAUSE;          ///<

    const static char* FUNC_STR_LEN;          ///<
    const static char* FUNC_STR_LEFT;         ///<
    const static char* FUNC_STR_RIGHT;        ///<
    const static char* FUNC_STR_FIND;         ///<
    const static char* FUNC_STR_SUB;          ///<
    const static char* FUNC_STR_REPLACE;      ///<
    const static char* FUNC_INT_RAND;         ///<

    const static char* FUNC_DB_NEXT;          ///<
    const static char* FUNC_DB_VAL;           ///<

    const static char* FUNC_MAP_VAL;          ///<

    const static char* HANGUP_CAUSE_SYS;
    const static char* HANGUP_CAUSE_USER;
    const static char* HANGUP_CAUSE_THIRD;
};

#endif
