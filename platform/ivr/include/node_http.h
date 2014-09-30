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

#ifndef _NODE_HTTP_H_
#define _NODE_HTTP_H_

#include "node_base.h"
#include "curl/curl.h"

class NodeHttp : public NodeBase {
public:
    NodeHttp(const uint32_t id, const string& name,
             const string& type, const string& desc, const key_map_t& keymap);
    virtual ~NodeHttp(void);

    virtual NodeBase* run(base_script_t* param);

    virtual bool load_other();
private:
    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/05 19:30:18
    **/
    virtual std::string enter(const map<string, variable_t>& vars)const ;
    /**
     * @brief
     *
     * @param [in/out] map<string   : const
     * @param [in/out] vars   : variable_t>&
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/05 19:30:23
    **/
    virtual std::string leave(const map<string, variable_t>& vars)const ;

private:
    string _url;   //url
    string _sendtype;    //发送方式，GET或POST
    std::string _timeout; // response timeout
    string _resp;  //url 请求的 response
    const static char* PARAM_URL;
    const static char* PARAM_SENDTYPE;
    const static char* PARAM_RESP;
    const static char* PARAM_TIMEOUT;

    const static char* PARAMITEM_POST;
    const static char* PARAMITEM_GET;
};

#endif
