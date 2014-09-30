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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tools.h"

#include "arithmetic_operate.h"
#include "parser.c"

ArithmeticOperate::ArithmeticOperate() {
    _operator_map["+"] = PLUS;
    _operator_map["-"] = MINUS;
    _operator_map["*"] = TIMES;
    _operator_map["/"] = DIVIDE;
    _operator_map["%"] = MOD;
    _operator_map["^"] = POW;
    _operator_map["("] = LP;
    _operator_map[")"] = RP;
}

ArithmeticOperate::~ArithmeticOperate() {
}

bool ArithmeticOperate::calculate(const char* str, int32_t& num) {
    std::string expr;
    token_seq_t tokens;
    double result = 0.0;

    num = 0;

    if (NULL == str) {
        return false;
    }

    expr = str;

    uint32_t i = 0;

    for (i = 0; i < expr.size(); ++i) {
        if (!isdigit(expr.at(i))) {
            break;
        }
    }

    if (expr.size() == i) { //全部都是数字
        return false;
    }

    if (tokenize(expr, tokens) && calculate_tokens(tokens, result)) {
        num = (int32_t)result;

        return true;
    }

    return false;
}

bool ArithmeticOperate::tokenize(const std::string& input, token_seq_t& tokens) {
    std::string s = input;
    ivr_tools_t::trim(s);
    const char* current = s.data();
    const char* end = s.data() + s.size();

    int32_t num_val = 0;

    tokens.clear();

    while (current < end) {
        while ((' ' == *current) || ('\t' == *current)) {
            ++current;
        }

        const char* token_beg = current;

        while (((*current >= '0') && (*current <= '9')) || '.' == *current) {
            ++current;
        }

        if (token_beg < current) {
            std::string num_tok(token_beg, current - token_beg);
            double val = 0.0;

            if (!ivr_tools_t::str2double(num_tok, val)) {
                return false;
            }

            tokens.push_back(std::make_pair(INTEGER, val));
            ++num_val;
            continue;
        }

        for (size_t len = 1; len <= 3; ++len) {
            if (current + len > end) {
                return false;
            }

            std::string window(current, len);
            std::map<std::string, int>::const_iterator op_it = _operator_map.find(window);

            if (op_it == _operator_map.end()) {
                continue;
            }

            tokens.push_back(std::make_pair(op_it->second, 0.0));
            current += len;
            break;
        }

        if (token_beg < current) {
            continue;
        }

        return false;
    }

    return (num_val);
}

bool ArithmeticOperate::calculate_tokens(token_seq_t& tokens, double& val) {
    void* parser = ParseAlloc(malloc);
    result_t result;

    for (size_t i = 0; i < tokens.size(); ++i) {
        Parse(parser, tokens[i].first, tokens[i].second, &result);
    }

    Parse(parser, 0, 0.0, &result);
    ParseFree(parser, free);

    if (result.error_type != result_t::ACCEPTED) {
        return false;
    }

    val = result.value;
    return true;
}
