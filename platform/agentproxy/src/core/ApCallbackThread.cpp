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



#include "ApCallbackThread.h"
#include "AgentProxy.h"
#include "ApCommon.h"

int32_t ApCallbackThread::operator()(const bool* isstopped, void* param) {
    AgentProxy* agentPrx = AgentProxy::Instance();

    while (!(*isstopped)) {
        if (agentPrx->IsNeedApThreadShutdown()) {
            break;
        }

        AgentEventT acdCallEvent;
        MediaEventT acdMediaEvent;
        RouteEventT acdRouteEvent;
        OtherEventT acdOtherEvent;

        AgentData agentInfo;

        if (agentPrx->GetAcdCallEvent(acdCallEvent, _threadNo)) {
            BGCC_TRACE("ap", "Thread[%d]:Success Get Agentbar[%s] CallEvent,TimeStamp = %"int64ld".",
                       _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp);

            agentPrx->SendCallEvent(acdCallEvent, _threadNo);
        }


        if (agentPrx->GetAcdMediaEvent(acdMediaEvent, _threadNo)) {
            BGCC_TRACE("ap", "Thread[%d]:Success Get Agentbar[%s] MediaEvent.",
                       _threadNo, acdMediaEvent.agentId.c_str());

            agentPrx->SendMediaEvent(acdMediaEvent, _threadNo);
            //if(!agentPrx->GetAgentData(acdMediaEvent.agentId,agentInfo))
            //{
            //    BGCC_FATAL("ap","Thread[%d]:CallbackThreadRun:Can not find AgentId[%s].AgentInfo.",
            //                 _threadNo,acdMediaEvent.agentId.c_str());
            //}
            //else
            //{
            //    try
            //    {
            //        if(agentInfo.proxy)
            //        {
            //            agentInfo.proxy->SendMediaEvent(acdMediaEvent);
            //        }
            //        else
            //        {

            //            BGCC_FATAL("ap","SendMediaEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
            //                          acdMediaEvent.agentId.c_str(),acdMediaEvent.timestamp);
            //        }
            //    }
            //    catch (const Ice::Exception &ex)
            //    {
            //        BGCC_FATAL("ap","SendMediaEvent Exception.ex = %s,AgentId = %s,TimeStamp = %"int64ld".",
            //                      ex.ice_name().c_str(),acdMediaEvent.agentId.c_str(),acdMediaEvent.timestamp);
            //    }
            //    catch(...)
            //    {
            //        BGCC_FATAL("ap","SendMediaEvent Exception.ex = catch Error,AgentId = %s,TimeStamp = %"int64ld".",
            //                      acdMediaEvent.agentId.c_str(),acdMediaEvent.timestamp);
            //    }
            //}
        }

        if (agentPrx->GetAcdRouteEvent(acdRouteEvent, _threadNo)) {
            BGCC_TRACE("ap", "Thread[%d]:Success Get Agentbar[%s] RouteEvent.",
                       _threadNo, acdRouteEvent.agentId.c_str());

            agentPrx->SendRouteEvent(acdRouteEvent, _threadNo);
            //if(!agentPrx->GetAgentData(acdRouteEvent.agentId,agentInfo))
            //{
            //    BGCC_TRACE("ap","Thread[%d]:CallbackThreadRun:Can not find AgentId[%s].AgentInfo.",
            //                _threadNo,acdRouteEvent.agentId.c_str());
            //}
            //else
            //{
            //    try
            //    {
            //        if(agentInfo.proxy)
            //        {
            //            agentInfo.proxy->SendQueueEvent(acdRouteEvent);
            //        }
            //        else
            //        {
            //            BGCC_FATAL("ap","SendQueueEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
            //                          acdRouteEvent.agentId.c_str(),acdRouteEvent.timestamp);
            //        }
            //    }
            //    catch (const Ice::Exception &ex)
            //    {
            //        BGCC_FATAL("ap","SendQueueEvent Exception.ex = %s,AgentId = %s,TimeStamp = %"int64ld".",
            //                      ex.ice_name().c_str(),acdRouteEvent.agentId.c_str(),acdRouteEvent.timestamp);
            //    }
            //    catch(...)
            //    {
            //        BGCC_FATAL("ap","SendQueueEvent Exception.ex = catch Error,AgentId = %s,TimeStamp = %"int64ld".",
            //                      acdRouteEvent.agentId.c_str(),acdRouteEvent.timestamp);
            //    }
            //}

        }

        if (agentPrx->GetAcdOtherEvent(acdOtherEvent, _threadNo)) {
            BGCC_TRACE("ap", "Thread[%d]:Success Get Agentbar[%s] OtherEvent.",
                       _threadNo, acdOtherEvent.agentId.c_str());

            agentPrx->SendOtherEvent(acdOtherEvent, _threadNo);
            //if(!agentPrx->GetAgentData(acdOtherEvent.agentId,agentInfo))
            //{
            //    BGCC_TRACE("ap","Thread[%d]:CallbackThreadRun:Can not find AgentId[%s].AgentInfo.",
            //                _threadNo,acdOtherEvent.agentId.c_str());
            //}
            //else
            //{
            //    try
            //    {
            //        if(agentInfo.proxy)
            //        {
            //            agentInfo.proxy->SendOtherEvent(acdOtherEvent);
            //        }
            //        else
            //        {
            //            BGCC_FATAL("ap","SendOtherEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
            //                          acdOtherEvent.agentId.c_str(),acdOtherEvent.timestamp);
            //        }
            //    }
            //    catch (const Ice::Exception &ex)
            //    {
            //        BGCC_FATAL("ap","SendOtherEvent Exception.ex = %s,AgentId = %s,TimeStamp = %"int64ld".",
            //                      ex.ice_name().c_str(),acdOtherEvent.agentId.c_str(),acdOtherEvent.timestamp);
            //    }
            //    catch(...)
            //    {
            //        BGCC_FATAL("ap","SendOtherEvent Exception.ex = catch Error,AgentId = %s,TimeStamp = %"int64ld".",
            //                      acdOtherEvent.agentId.c_str(),acdOtherEvent.timestamp);
            //    }
            //}


        }

        if (agentPrx->IsQueueEmpty(_threadNo)) {
            TimeUtil::safe_sleep_ms(100);
        }
    }

    return 0;
}

