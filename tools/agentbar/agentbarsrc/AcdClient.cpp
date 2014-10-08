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

#include "CCBar.h"
#include "AcdClient.h"

// AcdCallbackReceiver
void AcdCallbackReceiver::SendAgentEvent(const acd::AgentEventT &agentEvent, const std::map<std::string, std::string>& ctx)
{
	assert(Tool::p_Bar != NULL);

	acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
	try
	{
		Tool::WriteAgentEventLog(&agentEvent, "callback");
		acd::AgentEventT *pAE = new acd::AgentEventT(agentEvent);
		LONGLONG address = reinterpret_cast<LONGLONG>(pAE);
		int ladr = LOLONG(address);
		int hadr = HILONG(address);
		CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
		BOOL re = p_Bar->PostMessage(WM_AGENTEVENT, ladr, hadr);
		if(!re)
		{
			ret = acd::AcdResultT::ArFailed;
			Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendAgentEvent", "PostMessage Error", re);
		}
	}
	catch(...)
	{
		ret = acd::AcdResultT::ArFailed;
		Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendAgentEvent", "catch Error", ret.get_value());
	}
}

void AcdCallbackReceiver::SendMediaEvent(const acd::MediaEventT &mediaEvent, const std::map<std::string, std::string>& ctx)
{
	assert(Tool::p_Bar != NULL);

	acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
	try
	{
		Tool::WriteMediaEventLog(&mediaEvent, "callback");
		acd::MediaEventT *pME = new acd::MediaEventT(mediaEvent);
		LONGLONG address = reinterpret_cast<LONGLONG>(pME);
		int ladr = LOLONG(address);
		int hadr = HILONG(address);
		CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
		BOOL re = p_Bar->PostMessage(WM_MEDIAEVENT, ladr, hadr);
		if(!re)
		{
			ret = acd::AcdResultT::ArFailed;
			Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendMediaEvent", "PostMessage Error", re);
		}
	}
	catch(...)
	{
		ret = acd::AcdResultT::ArFailed;
		Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendMediaEvent", "catch Error", ret.get_value());
	}
}

void AcdCallbackReceiver::SendQueueEvent(const acd::RouteEventT &routeEvent, const std::map<std::string, std::string>& ctx)
{
	assert(Tool::p_Bar != NULL);

	acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
	try
	{
		Tool::WriteRouteEventLog(&routeEvent, "callback");
		acd::RouteEventT *pQE = new acd::RouteEventT(routeEvent);
		LONGLONG address = reinterpret_cast<LONGLONG>(pQE);
		int ladr = LOLONG(address);
		int hadr = HILONG(address);
		CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
		BOOL re = p_Bar->PostMessage(WM_QUEUEEVENT, ladr, hadr);
		if(!re)
		{
			ret = acd::AcdResultT::ArFailed;
			Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendQueueEvent", "PostMessage Error", re);
		}
	}
	catch(...)
	{
		ret = acd::AcdResultT::ArFailed;
		Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendQueueEvent", "catch Error", ret.get_value());
	}
}

void AcdCallbackReceiver::SendOtherEvent(const acd::OtherEventT &otherEvent, const std::map<std::string, std::string>& ctx)
{
	assert(Tool::p_Bar != NULL);

	acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
	try
	{
		Tool::WriteOtherEventLog(&otherEvent, "callback");
		acd::OtherEventT *pOE = new acd::OtherEventT(otherEvent);
		LONGLONG address = reinterpret_cast<LONGLONG>(pOE);
		int ladr = LOLONG(address);
		int hadr = HILONG(address);
		CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
		BOOL re = p_Bar->PostMessage(WM_OTHEREVENT, ladr, hadr);
		if(!re)
		{
			ret = acd::AcdResultT::ArFailed;
			Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendOtherEvent", "PostMessage Error", re);
		}
	}
	catch(...)
	{
		ret = acd::AcdResultT::ArFailed;
		Tool::m_Logger.WriteLog("AcdCallbackReceiver", "SendOtherEvent", "catch Error", ret.get_value());
	}
}

// AcdClient
AcdClient::AcdClient(void) : p_m_mainProxy(NULL), p_m_backProxy(NULL), m_MainHost(""), m_BackHost(""), m_isMainHost(true), p_m_acdClientProxy(NULL), m_Handle(0)
{
	m_servicemanager.add_service(bgcc::SharedPointer<bgcc::IProcessor>(new acd::acdcallbackProcessor(bgcc::SharedPointer<acd::acdcallback>(new AcdCallbackReceiver()))));
	//bgcc::log_open("bgcc.conf");  // 打开bgcc日志
}

AcdClient::~AcdClient(void)
{
}

int AcdClient::AcdInitial(const char *mianHost, const char *backHost, int port)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdInitial] mianHost:%s backHost:%s port:%d", mianHost, backHost, port);
		if(p_m_mainProxy)
		{
			delete p_m_mainProxy;
			p_m_mainProxy = NULL;
		}
		if(p_m_backProxy)
		{
			delete p_m_backProxy;
			p_m_backProxy = NULL;
		}
		if(p_m_acdClientProxy)
		{
			p_m_acdClientProxy = NULL;
		}
		m_Handle = 0;
		p_m_mainProxy = new acd::acdapiProxy(bgcc::ServerInfo(mianHost, port), 0, &m_servicemanager, 1);
		p_m_backProxy = new acd::acdapiProxy(bgcc::ServerInfo(backHost, port), 0, &m_servicemanager, 1);
		m_MainHost = mianHost;
		m_BackHost = backHost;
		m_isMainHost = true;
		p_m_acdClientProxy = p_m_mainProxy;

		if(p_m_mainProxy){
			p_m_mainProxy->set_property(bgcc::BaseProxy::PROXY_SEND_TIMEOUT, 2000);
			p_m_mainProxy->set_property(bgcc::BaseProxy::PROXY_RECV_TIMEOUT, 2000);
		}

		if(p_m_backProxy){
			p_m_backProxy->set_property(bgcc::BaseProxy::PROXY_SEND_TIMEOUT, 2000);
			p_m_backProxy->set_property(bgcc::BaseProxy::PROXY_RECV_TIMEOUT, 2000);
		}

		Tool::m_Logger.WriteLog("AcdClient", "AcdInitial", "new proxy", ret, Level_High);
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdInitial", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdUnInitial()
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdUnInitial] void");
		if(p_m_mainProxy)
		{
			delete p_m_mainProxy;
			p_m_mainProxy = NULL;
		}
		if(p_m_backProxy)
		{
			delete p_m_backProxy;
			p_m_backProxy = NULL;
		}
		if(p_m_acdClientProxy)
		{
			p_m_acdClientProxy = NULL;
		}
		m_Handle = 0;
		Tool::m_Logger.WriteLog("AcdClient", "AcdUnInitial", "delete proxy", ret, Level_High);
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdUnInitial", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSignIn(const char *agentId, const char *agentDn, const char *agentPwd, const acd::StatusChangeT &statusChangetype, bool autoAnswer, bool fcSignin, const char *skill)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		string host = m_isMainHost ? m_MainHost : m_BackHost;
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSignIn] host:%s agentId:%s agentDn:%s agentPwd:%s statusChangetype:%s autoAnswer:%d fcSignin:%d skill:%s", 
			host.c_str(), agentId, agentDn, agentPwd, statusChangetype.get_desc().c_str(), autoAnswer, fcSignin, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SignIn(agentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill, m_Handle).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSignIn", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSignIn", "SignIn", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSignIn] [out] handle:%I64d", m_Handle);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSignIn", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSignIn", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSignOut(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSignOut] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SignOut(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSignOut", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSignOut", "SignOut", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSignOut", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSignOut", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSetAgentStatus(const char *agentId, const acd::AgentStatusT &agentStatus, const char *restReason)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSetAgentStatus] agentId:%s agentStatus:%s restReason:%s", agentId, agentStatus.get_desc().c_str(), restReason);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SetAgentStatus(m_Handle, agentId, agentStatus, restReason).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSetAgentStatus", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSetAgentStatus", "SetAgentStatus", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSetAgentStatus", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSetAgentStatus", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentStatus(const char *agentId, acd::AgentStatusT &agentStatus)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetAgentStatus] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentStatus(m_Handle, agentId, agentStatus).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentStatus", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentStatus", "GetAgentStatus", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetAgentStatus] [out] agentStatus:%s", agentStatus.get_desc().c_str());
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentStatus", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentStatus", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdResetStatuschangetype(const char *agentId, const acd::StatusChangeT &statusChangetype)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdResetStatuschangetype] agentId:%s statusChangetype:%s", agentId, statusChangetype.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ResetStatuschangetype(m_Handle, agentId, statusChangetype).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetStatuschangetype", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetStatuschangetype", "ResetStatuschangetype", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdResetStatuschangetype", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdResetStatuschangetype", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdResetAutoAnswer(const char *agentId, bool autoAnswer)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdResetAutoAnswer] agentId:%s autoAnswer:%d", agentId, autoAnswer);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ResetAutoAnswer(m_Handle, agentId, autoAnswer).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetAutoAnswer", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetAutoAnswer", "ResetAutoAnswer", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdResetAutoAnswer", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdResetAutoAnswer", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdResetSkill(const char *agentId, const char *skill)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdResetSkill] agentId:%s skill:%s", agentId, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ResetSkill(m_Handle, agentId, skill).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetSkill", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetSkill", "ResetSkill", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdResetSkill", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdResetSkill", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdReset(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdReset] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Reset(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetSkill", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdReset", "Reset", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdReset", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdReset", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdOutboundCall(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, int timeout, const acd::CallModeT &callMode, const acd::CallTypeT &callType)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdOutboundCall] agentId:%s callerId:%s destId:%s forCallerDispNum:%s forCalleeDispNum:%s timeout:%d callMode:%s callType:%s", 
			agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, timeout, callMode.get_desc().c_str(), callType.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->OutboundCall(m_Handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, timeout, callMode, callType).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdOutboundCall", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdOutboundCall", "OutboundCall", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdOutboundCall", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdOutboundCall", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdAnswerCall(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdAnswerCall] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->AnswerCall(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdAnswerCall", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdAnswerCall", "AnswerCall", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdAnswerCall", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdAnswerCall", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdReleaseCall(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdReleaseCall] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ReleaseCall(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdReleaseCall", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdReleaseCall", "ReleaseCall", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdReleaseCall", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdReleaseCall", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdHold(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdHold] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Hold(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdHold", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdHold", "Hold", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdHold", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdHold", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdRetrieve(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdRetrieve] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Retrieve(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdRetrieve", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdRetrieve", "Retrieve", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdRetrieve", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdRetrieve", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdConsult(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, const acd::CallTypeT &callType)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdConsult] agentId:%s callerId:%s destId:%s forCallerDispNum:%s forCalleeDispNum:%s callType:%s", 
			agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, callType.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Consult(m_Handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, callType).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsult", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsult", "Consult", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdConsult", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdConsult", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdConsultReconnect(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdConsultReconnect] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ConsultReconnect(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultReconnect", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultReconnect", "ConsultReconnect", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdConsultReconnect", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdConsultReconnect", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdConsultTransfer(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdConsultTransfer] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ConsultTransfer(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultTransfer", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultTransfer", "ConsultTransfer", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdConsultTransfer", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdConsultTransfer", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSingleStepTransfer(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, bool isPassthrough, const acd::CallTypeT &callType)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSingleStepTransfer] agentId:%s callerId:%s destId:%s forCallerDispNum:%s forCalleeDispNum:%s isPassthrough:%d callType:%s", 
			agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, isPassthrough, callType.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SingleStepTransfer(m_Handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, isPassthrough, callType).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSingleStepTransfer", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSingleStepTransfer", "SingleStepTransfer", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSingleStepTransfer", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSingleStepTransfer", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdConsultConference(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdConsultConference] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ConsultConference(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultConference", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdConsultConference", "ConsultConference", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdConsultConference", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdConsultConference", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdConferenceJoin(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum, const acd::ConferenceT &conferenceType)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdConferenceJoin] agentId:%s callerId:%s destAgentId:%s forCallerDispNum:%s forCalleeDispNum:%s conferenceType:%s", 
			agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, conferenceType.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ConferenceJoin(m_Handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, conferenceType).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdConferenceJoin", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdConferenceJoin", "ConferenceJoin", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdConferenceJoin", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdConferenceJoin", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSetAssociateData(const char *agentId, const char *key, const char *value)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSetAssociateData] agentId:%s key:%s value:%s", agentId, key, value);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SetAssociateData(m_Handle, agentId, key, value).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSetAssociateData", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSetAssociateData", "SetAssociateData", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSetAssociateData", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSetAssociateData", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAssociateData(const char *agentId, const char *key, string &value)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetAssociateData] agentId:%s key:%s", agentId, key);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAssociateData(m_Handle, agentId, key, value).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAssociateData", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAssociateData", "GetAssociateData", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetAssociateData] [out] value:%s", value.c_str());
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAssociateData", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAssociateData", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdJumptheQueue(const char *agentId, LONGLONG requestId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdJumptheQueue] agentId:%s requestId:%I64d", agentId, requestId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->JumptheQueue(m_Handle, agentId, requestId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdJumptheQueue", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdJumptheQueue", "JumptheQueue", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdJumptheQueue", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdJumptheQueue", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdForceSignIn(const char *agentId, const char *destAgentId, const char *agentDn, const char *agentPwd, const acd::StatusChangeT &statusChangetype, bool autoAnswer, bool fcSignin, const char *skill)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdForceSignIn] agentId:%s destAgentId:%s agentDn:%s agentPwd:%s statusChangetype:%s autoAnswer:%d fcSignin:%d skill:%s", 
			agentId, destAgentId, agentDn, agentPwd, statusChangetype.get_desc().c_str(), autoAnswer, fcSignin, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ForceSignIn(m_Handle, agentId, destAgentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignIn", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignIn", "ForceSignIn", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignIn", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignIn", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdForceSignOut(const char *agentId, const char *destAgentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdForceSignOut] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ForceSignOut(m_Handle, agentId, destAgentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignOut", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignOut", "ForceSignOut", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignOut", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdForceSignOut", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdForceSetAgentStatus(const char *agentId, const char *destAgentId, const acd::AgentStatusT &agentStatus)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdForceSetAgentStatus] agentId:%s destAgentId:%s agentStatus:%s", agentId, destAgentId, agentStatus.get_desc().c_str());
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ForceSetAgentStatus(m_Handle, agentId, destAgentId, agentStatus).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSetAgentStatus", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdForceSetAgentStatus", "ForceSetAgentStatus", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdForceSetAgentStatus", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdForceSetAgentStatus", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdListen(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdListen] agentId:%s callerId:%s destAgentId:%s forCallerDispNum:%s forCalleeDispNum:%s", 
			agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Listen(m_Handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdListen", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdListen", "Listen", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdListen", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdListen", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdStopListen(const char *agentId, const char *destAgentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdStopListen] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->StopListen(m_Handle, agentId, destAgentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopListen", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopListen", "StopListen", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdStopListen", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdStopListen", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdInsert(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdInsert] agentId:%s callerId:%s destAgentId:%s forCallerDispNum:%s forCalleeDispNum:%s", 
			agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Insert(m_Handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdInsert", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdInsert", "Insert", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdInsert", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdInsert", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdStopInsert(const char *agentId, const char *destAgentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdStopInsert] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->StopInsert(m_Handle, agentId, destAgentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopInsert", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopInsert", "StopInsert", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdStopInsert", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdStopInsert", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSwitchInsertorListen(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSwitchInsertorListen] agentId:%s callerId:%s destAgentId:%s forCallerDispNum:%s forCalleeDispNum:%s", 
			agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SwitchInsertorListen(m_Handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSwitchInsertorListen", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSwitchInsertorListen", "SwitchInsertorListen", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSwitchInsertorListen", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSwitchInsertorListen", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdBreak(const char *agentId, const char *destAgentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdBreak] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Break(m_Handle, agentId, destAgentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdBreak", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdBreak", "Break", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdBreak", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdBreak", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSendDTMF(const char *agentId, const char *digitals)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdSendDTMF] agentId:%s digitals:%s", agentId, digitals);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SendDTMF(m_Handle, agentId, digitals).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSendDTMF", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSendDTMF", "SendDTMF", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSendDTMF", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSendDTMF", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdStartPlay(const char *agentId, const char *filename)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdStartPlay] agentId:%s filename:%s", agentId, filename);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->StartPlay(m_Handle, agentId, filename).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdStartPlay", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdStartPlay", "StartPlay", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdStartPlay", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdStartPlay", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdStopPlay(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdStopPlay] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->StopPlay(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopPlay", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdStopPlay", "StopPlay", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdStopPlay", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdStopPlay", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdMuteOn(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdMuteOn] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->MuteOn(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOn", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOn", "MuteOn", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOn", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOn", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdMuteOff(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdMuteOff] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->MuteOff(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOff", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOff", "MuteOff", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOff", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdMuteOff", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentDetailByAgentID(const char *agentId, const char *destAgentId, acd::AgentInfoT &agentInfo)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentDetailByAgentID] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentDetailByAgentID(m_Handle, agentId, destAgentId, agentInfo).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentID", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentID", "GetAgentDetailByAgentID", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentDetailByAgentID] [out] agentStatus:%s", agentInfo.currStatus.get_desc().c_str());
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentID", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentID", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentDetailByAgentDN(const char *agentId, const char *destAgentDn, acd::AgentInfoT &agentInfo)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentDetailByAgentDN] agentId:%s destAgentDn:%s", agentId, destAgentDn);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentDetailByAgentDN(m_Handle, agentId, destAgentDn, agentInfo).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentDN", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentDN", "GetAgentDetailByAgentDN", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentDetailByAgentDN] [out] agentStatus:%s", agentInfo.currStatus.get_desc().c_str());
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentDN", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailByAgentDN", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentDetailsByAgentIDs(const char *agentId, const acd::StringListT &destAgentIdList, acd::AgentInfoListT &agentInfoList)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::WriteAgentIdListLog(agentId, destAgentIdList);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentDetailsByAgentIDs(m_Handle, agentId, destAgentIdList, agentInfoList).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentIDs", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentIDs", "GetAgentDetailsByAgentIDs", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentIDs", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentIDs", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentDetailsByAgentDNs(const char *agentId, const acd::StringListT &destAgentDnList, acd::AgentInfoListT &agentInfoList)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::WriteAgenDntListLog(agentId, destAgentDnList);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentDetailsByAgentDNs(m_Handle, agentId, destAgentDnList, agentInfoList).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentDNs", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentDNs", "GetAgentDetailsByAgentDNs", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentDNs", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsByAgentDNs", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetRecordFileName(const char *agentId, string &filename)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetRecordFileName] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetRecordFileName(m_Handle, agentId, filename).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetRecordFileName", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetRecordFileName", "GetRecordFileName", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetRecordFileName] [out] filename:%s", filename.c_str());
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetRecordFileName", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetRecordFileName", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetRestReason(const char *agentId, acd::StringListT &restReason)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_High, "[AcdClient-AcdGetRestReason] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetRestReason(m_Handle, agentId, restReason).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetRestReason", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetRestReason", "GetRestReason", ret, Level_High);
				Tool::WriteRestReasonLog(restReason);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetRestReason", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetRestReason", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentNumberBySkill(const char *agentId, const char *skill, int &agentNum)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentNumberBySkill] agentId:%s skill:%s", agentId, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentNumberBySkill(m_Handle, agentId, skill, agentNum).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentNumberBySkill", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentNumberBySkill", "GetAgentNumberBySkill", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentNumberBySkill] [out] agentNum:%d", agentNum);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentNumberBySkill", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentNumberBySkill", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetAgentDetailsBySkill(const char *agentId, const char *skill, int &agentNum, acd::AgentInfoListT &agentInfoList)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetAgentDetailsBySkill] agentId:%s skill:%s", agentId, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetAgentDetailsBySkill(m_Handle, agentId, skill, agentNum, agentInfoList).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsBySkill", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsBySkill", "GetAgentDetailsBySkill", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsBySkill", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetAgentDetailsBySkill", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetSkillWaitingNumber(const char *agentId, const char *skill, int &queueNum, int &freeNum)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetSkillWaitingNumber] agentId:%s skill:%s", agentId, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetSkillWaitingNumber(m_Handle, agentId, skill, queueNum, freeNum).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingNumber", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingNumber", "GetSkillWaitingNumber", ret, Level_High);
				Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetSkillWaitingNumber] [out] queueNum:%d freeNum:%d", queueNum, freeNum);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingNumber", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingNumber", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetSkillWaitingCallInfo(const char *agentId, const char *skill, int &queueNum, acd::QueueInfoListT &queueInfoList)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetSkillWaitingCallInfo] agentId:%s skill:%s", agentId, skill);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetSkillWaitingCallInfo(m_Handle, agentId, skill, queueNum, queueInfoList).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingCallInfo", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingCallInfo", "GetSkillWaitingCallInfo", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingCallInfo", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetSkillWaitingCallInfo", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetPrivateQueue(const char *agentId, const char *destAgentId, int &queueNum, acd::QueueInfoListT &queueInfoList)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetPrivateQueue] agentId:%s destAgentId:%s", agentId, destAgentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetPrivateQueue(m_Handle, agentId, destAgentId, queueNum, queueInfoList).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetPrivateQueue", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetPrivateQueue", "GetPrivateQueue", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetPrivateQueue", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetPrivateQueue", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdGetSysInfo(const char *agentId, acd::SysInfoT &sysInfo)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdGetSysInfo] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->GetSysInfo(m_Handle, agentId, sysInfo).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSysInfo", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdGetSysInfo", "GetSysInfo", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdGetSysInfo", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdGetSysInfo", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdSynchronizeCTITime(const char *agentId, LONGLONG &timestamp)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdSynchronizeCTITime] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->SynchronizeCTITime(m_Handle, agentId, timestamp).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdSynchronizeCTITime", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdSynchronizeCTITime", "SynchronizeCTITime", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdSynchronizeCTITime", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdSynchronizeCTITime", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdHeartbeat(const char *agentId)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdHeartbeat] agentId:%s", agentId);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->Heartbeat(m_Handle, agentId).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdHeartbeat", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdHeartbeat", "Heartbeat", ret, Level_Super);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdHeartbeat", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdHeartbeat", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdResetConfig(const char *password)
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		Tool::m_Logger.WriteLog(Level_Super, "[AcdClient-AcdResetConfig] password:%s", password);
		if(p_m_acdClientProxy)
		{
			ret = p_m_acdClientProxy->ResetConfig(password).get_value();
			if(p_m_acdClientProxy->get_errno() != 0)
			{
				ret = AGENTBARERROR_BGCC_EXCEPTION;
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetConfig", p_m_acdClientProxy->get_errno(), ret);
			}
			else
			{
				Tool::m_Logger.WriteLog("AcdClient", "AcdResetConfig", "ResetConfig", ret, Level_High);
			}
		}
		else
		{
			ret = AGENTBARERROR_BGCC_CLIENTPROXYFAIL;
			Tool::m_Logger.WriteLog("AcdClient", "AcdResetConfig", "BGCC Proxy Error", ret);
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdResetConfig", "catch Error", ret);
	}
	return ret;
}

int AcdClient::AcdBackup()
{
	int ret = AGENTBARERROR_SUCCESS;
	try
	{
		if(m_isMainHost)
		{
			//p_m_mainProxy.close();
			p_m_acdClientProxy = p_m_backProxy;
			m_isMainHost = false;
		}
		else
		{
			//p_m_backProxy.close();
			p_m_acdClientProxy = p_m_mainProxy;
			m_isMainHost = true;
		}
	}
	catch(...)
	{
		ret = AGENTBARERROR_BGCC_EXCEPTION;
		Tool::m_Logger.WriteLog("AcdClient", "AcdBackup", "catch Error", ret);
	}
	return ret;
}
