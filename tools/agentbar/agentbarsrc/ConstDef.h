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

#include "acdcommon.h"

// Post消息类型，AcdClient和CCBar中使用
#define WM_AGENTEVENT WM_USER + 1001
#define WM_MEDIAEVENT WM_USER + 1002
#define WM_QUEUEEVENT WM_USER + 1003
#define WM_OTHEREVENT WM_USER + 1004

// 将void *转换成长整型，AcdClient和CCBar中使用
#define MAKELONGLONG(a, b) ((__int64)(((unsigned __int64)(a) & 0xffffffff) | ((unsigned __int64)(b) & 0xffffffff) << 32))
#define LOLONG(a) ((__int32)((unsigned __int64)(a) & 0xffffffff))
#define HILONG(a) ((__int32)((unsigned __int64)(a) >> 32))

//日志组件、info对话框使用
#define vsnprintf _vsnprintf
#define snprintf _snprintf
#define access _access

// 控件的参数，CCBar中使用
const int BAR_WIDTH = 1440;					//控件宽度，1440*900显示器的最大宽度
const int BAR_HEIGHT = 84;					//控件高度
const int TOP_HEIGHT = 70;					//按钮高度
const int BAR_TOP_POSITION = 10;			//按钮离控件高度

// 定时器类型，CCBar中使用
const int TIMER_STATUS = 1;					//状态定时器
const int TIMER_TALK = 2;					//通话定时器
const int TIMESPAN_STATUS = 300;			//状态定时器间隔时间
const int TIMESPAN_TALK = 300;				//通话定时器间隔时间
const int TIMESPAN_HEARTBEAT = 10000;		//心跳定时器间隔时间
const int TIMES_HEARTBEAT_EXCEPTION = 3;	//心跳异常次数

// ACD回调线程数
//const int ACD_PROXY_NUM = 1;

// 日志等中广泛使用
const unsigned long LONG_STRING_LENGHT = 128;
const unsigned long TEXT_LENGHT = 1024;

typedef char LongString[LONG_STRING_LENGHT];
typedef char Text[TEXT_LENGHT];

typedef bgcc::Guard<bgcc::Mutex> SingleLocker;

// 事件原因，区分不同原因导致的事件
enum EVENTREASON
{
	EVENTREASON_SUCCESS,
	EVENTREASON_IMS_DISCONNECT = 1000,
	EVENTREASON_IMS_MASTERCHANGE,
	EVENTREASON_IMS_OPERATIONFAILED,
	EVENTREASON_ACD_DISCONNECT,
	EVENTREASON_ACD_MASTERCHANGE,
	EVENTREASON_ACD_OPERATIONFAILED,
	EVENTREASON_ACD_RELOGINSUCCESS,
	EVENTREASON_ACD_RELOGINFAILED
};

// 错误类型，AcdClient和CCBar中使用
enum AGENTBARERROR
{
	AGENTBARERROR_SUCCESS,
	AGENTBARERROR_BGCC_CLIENTPROXYFAIL = 1000,
	AGENTBARERROR_BGCC_EXCEPTION,
	AGENTBARERROR_BAR_INITIAL,
	AGENTBARERROR_BAR_UNINITIAL,
	AGENTBARERROR_BAR_UNSIGNIN,
	AGENTBARERROR_BAR_WRONGSTATE,
	AGENTBARERROR_BAR_OUTEVENTERROR,
	AGENTBARERROR_BAR_ANSWERERROR,
	AGENTBARERROR_JSON_READERROR,
	AGENTBARERROR_SOFTPHONE_ERROR					//suxiangmao
};

// 主叫变换类型
enum ANICHANGE
{
	ANICHANGE_SYSTEM,
	ANICHANGE_TRANSFER,
	ANICHANGE_SPECIAL
};

// 日志级别
enum Level
{
	Level_Low,
	Level_Middle,
	Level_High,
	Level_Super
};

// 按钮状态，CCBar中使用
struct ButtonStatus
{
private:
    static const LONGLONG LOGIN = 1;
    static const LONGLONG LOGOUT = 1<<1;
    static const LONGLONG ANSWER = 1 << 2;
    static const LONGLONG CALLOUT = 1 << 3;
    static const LONGLONG SENDDTMF = 1 << 4;
    static const LONGLONG HANGUP = 1 << 5;
    static const LONGLONG HOLD = 1 << 6;
    static const LONGLONG RETRIEVE = 1 << 7;
    static const LONGLONG CONSULT = 1 << 8;
    static const LONGLONG RECONNECT = 1 << 9;
    static const LONGLONG TRANSFER = 1 << 10;
    static const LONGLONG CONFERENCE = 1 << 11;
    static const LONGLONG SSTRANSFER = 1 << 12;
    static const LONGLONG REST = 1 << 13;
    static const LONGLONG READY = 1 << 14;
    static const LONGLONG BUSY = 1 << 15;
    static const LONGLONG SKILL = 1 << 16;

public:
	bool btnLogin;
	bool btnLogout;
	bool btnAnswer;
	bool btnCallout;
	bool btnSenddtmf;
	bool btnHangup;
	bool btnHold;
	bool btnRetrieve;
	bool btnConsult;
	bool btnReconnect;
	bool btnTransfer;
	bool btnConference;					//没有SKILLCHANGE，有CONFERENCE
	bool btnSSTransfer;
	bool btnRest;
	bool btnReady;
	bool btnBusy;
	bool btnSkill;

public:
	ButtonStatus()
	{
		Reset();
	}

	void Reset()
	{
		btnLogin = false;
		btnLogout = false;
		btnAnswer = false;
		btnCallout = false;
		btnSenddtmf = false;
		btnHangup = false;
		btnHold = false;
		btnRetrieve = false;
		btnConsult = false;
		btnReconnect = false;
		btnTransfer = false;
		btnConference = false;					//没有SKILLCHANGE，有CONFERENCE
		btnSSTransfer = false;
		btnRest = false;
		btnReady = false;
		btnBusy = false;
		btnSkill = false;
	}

    LONGLONG StatusAsLonglong()
    {
        LONGLONG res = 0;
        if(btnLogin)
            res |= LOGIN;
        if(btnLogout)
            res |= LOGOUT;
        if(btnAnswer)
            res |= ANSWER;
        if(btnCallout)
            res |= CALLOUT;
        if(btnSenddtmf)
            res |= SENDDTMF;
        if(btnHangup)
            res |= HANGUP;
        if(btnHold)
            res |= HOLD;
        if(btnRetrieve)
            res |= RETRIEVE;
        if(btnConsult)
            res |= CONSULT;
        if(btnReconnect)
            res |= RECONNECT;
        if(btnTransfer)
            res |= TRANSFER;
        if(btnConference)
            res |= CONFERENCE;
        if(btnSSTransfer)
            res |= SSTRANSFER;
        if(btnRest)
            res |= REST;
        if(btnReady)
            res |= READY;
        if(btnBusy)
            res |= BUSY;
        if(btnSkill)
            res |= SKILL;
        return res;
    }
};
