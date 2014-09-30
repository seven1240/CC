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

#ifndef _ARITHMETIC_OPERATE_H_
#define _ARITHMETIC_OPERATE_H_

#include <vector>
#include <map>
#include <string>

#include "common.h"

/**
* @brief 表达式计算
*
*/
class ArithmeticOperate {
private:
    typedef std::vector<std::pair<int32_t, double> > token_seq_t;
public:
    /**
     * @brief 构造函数
     *
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/24 17:34:22
    **/
    ArithmeticOperate();
    /**
     * @brief 析构函数
     *
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/24 17:34:25
    **/
    ~ArithmeticOperate();

    /**
     * @brief 表达式计算
     *
     * @param [in/out] str   : const char*
     * @param [in/out] num   : int32_t&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/24 17:34:29
    **/
    bool calculate(const char* str, int32_t& num);//表达式计算

private:
    /**
     * @brief 将表达式转化为token列表
     *
     * @param [in/out] input   : const std::string&
     * @param [in/out] tokens   : token_seq_t&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/24 17:33:32
    **/
    bool tokenize(const std::string& input, token_seq_t& tokens);
    /**
     * @brief 按照token进行计算
     *
     * @param [in/out] tokens   : token_seq_t&
     * @param [in/out] val   : double&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/24 17:33:44
    **/
    bool calculate_tokens(token_seq_t& tokens, double& val);
private:
    std::map<std::string, int32_t> _operator_map;                 ///<计算符号列表

};

#endif
