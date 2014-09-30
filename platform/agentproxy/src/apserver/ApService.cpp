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


#include "ApService.h"
#include "AgentProxy.h"

bool ApService::InitApService(std::string ApListenIp, int ApListenPort, int threadPoolNum) {
    bool status = true;

    _ApListenIp = ApListenIp;
    _ApListenPort = ApListenPort;
    _threadPoolNum = threadPoolNum;

    SharedPointer<IProcessor> xp(
        new apapiProcessor(
            SharedPointer<apapi>(
                new ApService)));

    ServiceManager sm;
    sm.add_service(xp);

    ThreadPool tp;
    tp.init(_threadPoolNum);
    Server* server = new Server(&sm, &tp, _ApListenPort);

    if (0 != server->serve()) {
        status =  false;
    }

    return status;
}
bool ApService::ReLoadConfig(const std::map<std::string, std::string>& ctx) {
    AgentProxy* agentProxy = AgentProxy::Instance();
    return agentProxy->ReLoadConfig();
}


bool ApService::GetAgents(ApAgentInfoListT& agentInfoList,
                          const std::map<std::string, std::string>& ctx) {
    AgentProxy* agentProxy = AgentProxy::Instance();
    return agentProxy->GetAgents(agentInfoList);
}

ApService::~ApService() {
}
