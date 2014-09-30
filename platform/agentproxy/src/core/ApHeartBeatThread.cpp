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



#include "ApHeartBeatThread.h"

int32_t ApHeartBeatThread::operator()(const bool* isstopped, void* param) {
    AgentProxy* agentPrx = AgentProxy::Instance();
    int32_t timeout = agentPrx->GetHeartBeatTimeOut();

    while (!(*isstopped)) {
        if (agentPrx->IsNeedApThreadShutdown()) {
            break;
        }

        agentPrx->HeartBeat();

        TimeUtil::safe_sleep_s(timeout);
    }

    return 0;
}

