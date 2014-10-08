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

#pragma once

#include "Logger.h"

class Tool
{
public:
	static Logger m_Logger;
	static void *p_Bar;
private:
	static void GetVersion(HINSTANCE handle, LongString version);
public:
	static void Init(HINSTANCE handle);
	static void UnInit();

	static void GetAcdResult_Str(LONG input, string &output);

	static void WriteAgentEventLog(const acd::AgentEventT *agentEvent, const char *type);
	static void WriteMediaEventLog(const acd::MediaEventT *mediaEvent, const char *type);
	static void WriteRouteEventLog(const acd::RouteEventT *routeEvent, const char *type);
	static void WriteOtherEventLog(const acd::OtherEventT *otherEvent, const char *type);
	static void WriteAgentIdListLog(const char *agentId, const acd::StringListT &destAgentIdList);
	static void WriteAgenDntListLog(const char *agentId, const acd::StringListT &destAgentDnList);
	static void WriteRestReasonLog(const acd::StringListT &restReason);
};
