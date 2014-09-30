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

#ifndef APSERVICE_H
#define APSERVICE_H

#include <bgcc.h>
#include "ap.h"
#include "AgentProxy.h"

using namespace ap;

class ApService: public apapi {
public:
    /**
     * @brief InitApService    初始化AP自身服务，用于响应ReLoadConfig与GetAgents接口
     * @param ApListenIp       IP地址
     * @param ApListenPort     监听端口
     * @param threadPoolNum    服务处理连接数
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool InitApService(std::string ApListenIp, int32_t ApListenPort, int32_t threadPoolNum);

    /**
     * @brief ReLoadConfig     配置重加载接口
     * @param ctx              proxy携带的连接信息
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    virtual bool ReLoadConfig(const std::map<std::string, std::string>& ctx);

    /**
     * @brief GetAgents        获取AP服务中的坐席信息
     * @param agentInfoList    坐席信息，输出参数
     * @param ctx              proxy携带的连接信息
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    virtual bool GetAgents(ApAgentInfoListT& agentInfoList,
                           const std::map<std::string, std::string>& ctx);
private:

    int32_t     _threadPoolNum;
    int32_t     _ApListenPort;
    std::string _ApListenIp;
    Server*     _server;

public:
    ApService() {}
    virtual ~ApService();
};

#endif

