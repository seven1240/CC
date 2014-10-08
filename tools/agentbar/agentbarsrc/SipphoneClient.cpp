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
#include "SipphoneClient.h"

const int LOCAL_SIP_PORT = 6060;
const int LOG_LEVEL = 3;
const bool LOG_APPEND = true;

void call_state_callback(int account_id, int call_id, const char *srcnum, const char *dstnum, PHONELIB_CALL_STATE cstate, int sip_response_code, const char *sip_response_desc)
{
	assert(Tool::p_Bar != NULL);

	CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
	p_Bar->GetSipphoneClient().process_call_state(account_id, call_id, srcnum, dstnum, cstate, sip_response_code, sip_response_desc);
}

void reg_state_callback(int account_id, PHONELIB_REG_STATE state, int code, const char *statusText)
{
	assert(Tool::p_Bar != NULL);

	CCCBar *p_Bar = static_cast<CCCBar *>(Tool::p_Bar);
	p_Bar->GetSipphoneClient().process_reg_state(account_id, state, code, statusText);
}

SipphoneClient::SipphoneClient(void) : m_account_id(-1), m_call_id(-1), m_is_initial(false), m_is_register(false), m_is_talking(false)
{
	m_Logger.Initialize(50000, 50, "C:\\Log\\CCAgentBar\\", "SIP", phonelib_get_version_string());
	m_Logger.UnInitialize();
}

SipphoneClient::~SipphoneClient(void)
{
}

void SipphoneClient::process_reg_state(int account_id, PHONELIB_REG_STATE state, int sip_response_code, const char *sip_response_desc)
{
	assert(Tool::p_Bar != NULL);

	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-process_reg_state] account_id:%d state:%d sip_response_code:%d sip_response_desc:%s", 
		account_id, state, sip_response_code, sip_response_desc);
}

void SipphoneClient::process_call_state(int account_id, int call_id, const char *srcnum, const char *dstnum, PHONELIB_CALL_STATE state, int sip_response_code, const char *sip_response_desc)
{
	assert(Tool::p_Bar != NULL);

	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-process_call_state] account_id:%d call_id:%d srcnum:%s dstnum:%s state:%d sip_response_code:%d sip_response_desc:%s", 
		account_id, call_id, srcnum, dstnum, state, sip_response_code, sip_response_desc);

	switch(state)
	{
	case PHONELIB_CALL_STATE_TERMINATED:
		{
			m_is_talking = false;
			break;
		}
	case PHONELIB_CALL_STATE_INCOMING:
		{
			if(m_is_talking)
			{
				phonelib_drop_call(call_id);
			}
			else
			{
				m_is_talking = true;
				m_call_id = call_id;
			}
			break;
		}
	default:
		break;
	}
}

int SipphoneClient::SipInitial()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipInitial] void");
	if(!m_is_initial)
	{
		ret = phonelib_init(LOCAL_SIP_PORT, m_Logger.GetFullFileName().c_str(), LOG_LEVEL, LOG_APPEND);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_is_initial = true;
			phonelib_set_call_state_callback(call_state_callback);
			phonelib_set_reg_state_callback(reg_state_callback);
		}
		else
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipInitial", "phonelib_init", ret);
	}
	return ret;
}

int SipphoneClient::SipUnInitial()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipUnInitial] void");
	if(m_is_initial)
	{
		ret = phonelib_destroy();
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_is_register = false;	// 在phonelib_destroy()里，会自动将sip账号给remove掉，因此将此变量设置成false, 则不会再继续调用addaccount
			m_is_initial = false;
		}
		else
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipUnInitial", "phonelib_destroy", ret);
	}
	return ret;
}

int SipphoneClient::SipRegister(const char *server, int server_port, const char *sip_account, const char *sip_password, int timeout)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipRegister] server:%s server_port:%d sip_account:%s sip_password:%s timeout:%d", server, server_port, sip_account, sip_password, timeout);
	if(m_is_register)
	{
		ret = phonelib_remove_account(m_account_id);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_is_register = false;
		}
		else
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipRegister", "phonelib_remove_account", ret);
	}
	if(!m_is_register)
	{
		ret = phonelib_add_account(server, server_port, sip_account, sip_password, timeout, &m_account_id);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_is_register = true;
		}
		else
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipRegister", "phonelib_add_account", ret);
		Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipRegister] [out] m_account_id:%d", m_account_id);
	}
	return ret;
}

int SipphoneClient::SipUnRegister()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipUnRegister] void");
	if(m_is_register)
	{
		ret = phonelib_remove_account(m_account_id);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_is_register = false;
		}
		else
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipUnRegister", "phonelib_remove_account", ret);
	}
	return ret;
}

int SipphoneClient::SipMakecall(const char *dest)
{
	return AGENTBARERROR_SUCCESS;
}

int SipphoneClient::SipAnswercall()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipAnswercall] void");
	if(m_is_talking)
	{
		ret = phonelib_answer_call(m_call_id);
		if(ret != AGENTBARERROR_SUCCESS)
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipAnswercall", "phonelib_answer_call", ret);
	}
	return ret;
}

int SipphoneClient::SipHangupcall()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	Tool::m_Logger.WriteLog(Level_High, "[SipphoneClient-SipHangupcall] void");
	if(m_is_talking)
	{
		ret = phonelib_drop_call(m_call_id);
		if(ret != AGENTBARERROR_SUCCESS)
		{
			ret = AGENTBARERROR_SOFTPHONE_ERROR;
		}
		Tool::m_Logger.WriteLog("SipphoneClient", "SipHangupcall", "phonelib_drop_call", ret);
	}
	return ret;
}

int SipphoneClient::SipHoldcall()
{
	return AGENTBARERROR_SUCCESS;
}

int SipphoneClient::SipUnholdcall()
{
	return AGENTBARERROR_SUCCESS;
}

int SipphoneClient::SipSenddtmf(const char *dtmf)
{
	return AGENTBARERROR_SUCCESS;
}
