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

#include "Tool.h"
#include "phonelib.h"

struct CallStateMsg
{
	int account_id;
	int call_id;
	string src;
	string dst;
	PHONELIB_CALL_STATE state;
	int sipcode;
	string response;
};

struct RegStateMsg
{
	int account_id;
	PHONELIB_REG_STATE state;
	int sipcode;
	string response;
};

class SipphoneClient
{
private:
	int m_account_id;
	int m_call_id;
	bool m_is_initial;
	bool m_is_register;
	bool m_is_talking;
	Logger m_Logger;

public:
	void process_reg_state(int account_id, PHONELIB_REG_STATE state, int sip_response_code, const char *sip_response_desc);
	void process_call_state(int account_id, int call_id, const char *srcnum, const char *dstnum, PHONELIB_CALL_STATE state, int sip_response_code, const char *sip_response_desc);

public:
	SipphoneClient(void);
	~SipphoneClient(void);
	int SipInitial();
	int SipUnInitial();
	int SipRegister(const char *server, int server_port, const char *sip_account, const char *sip_password, int timeout);
	int SipUnRegister();
	int SipMakecall(const char *dest);
	int SipAnswercall();
	int SipHangupcall();
	int SipHoldcall();
	int SipUnholdcall();
	int SipSenddtmf(const char *dtmf);
};
