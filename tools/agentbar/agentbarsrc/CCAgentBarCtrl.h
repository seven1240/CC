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

#include "CCBar.h"

class CCCAgentBarCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCCAgentBarCtrl)

// 构造函数，自动生成
public:
	CCCAgentBarCtrl();

// 重写，自动生成
protected:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip);

// 实现，自动生成
protected:
	~CCCAgentBarCtrl();

	DECLARE_OLECREATE_EX(CCCAgentBarCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CCCAgentBarCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCCAgentBarCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CCCAgentBarCtrl)		// 类型名称和杂项状态

// 消息映射，自动生成
	DECLARE_MESSAGE_MAP()

// 调度映射，自动生成
	DECLARE_DISPATCH_MAP()

// 事件映射，自动生成
	DECLARE_EVENT_MAP()

// 调度和事件 ID，自动生成
public:
	enum
	{
        eventidOnBtnStatus = 29L,
        eventidOnHeartbeat = 28L,
        eventidOnBeforeOutCall = 27L,
		eventidOnOperationFailed = 26L,
		eventidOnCTIMasterChanged = 25L,
		eventidOnCTIDisconnect = 24L,
		eventidOnOutprivatequeue = 23L,
		eventidOnInprivatequeue = 22L,
		eventidOnEndRecord = 21L,
		eventidOnBeginRecord = 20L,
		eventidOnInserted = 19L,
		eventidOnMonitored = 18L,
		eventidOnInsert = 17L,
		eventidOnMonitor = 16L,
		eventidOnConference = 15L,
		eventidOnConsultConnected = 14L,
		eventidOnConsultConnecting = 13L,
		eventidOnSuspended = 12L,
		eventidOnInternalConnected = 11L,
		eventidOnHarfConnected = 10L,
		eventidOnConnected = 9L,
		eventidOnConnecting = 8L,
		eventidOnHarfAlerting = 7L,
		eventidOnAlerting = 6L,
		eventidOnLock = 5L,
		eventidOnRest = 4L,
		eventidOnBusy = 3L,
		eventidOnReady = 2L,
		eventidOnUnLogin = 1L,
		dispidTransIVR = 81L,
		dispidTransIVREx = 82L,
		dispidJumptheQueue = 80L,
		dispidGetPromptByErrorCode = 79L,
		dispidSynchronizeCTITime = 78L,
		dispidGetOrgCalledNo = 77L,
		dispidGetCalledNo = 76L,
		dispidGetOrgCallingNo = 75L,
		dispidGetCallingNo = 74L,
		dispidGetSysInfo = 73L,
		dispidGetPrivateQueue = 72L,
		dispidGetSkillWaitingCallInfo = 71L,
		dispidGetSkillWaitingNumber = 70L,
		dispidGetAgentDetailsBySkill = 69L,
		dispidGetAgentNumberBySkill = 68L,
		dispidGetRestReason = 67L,
		dispidGetRecordFileName = 66L,
		dispidGetAgentDetailsByAgentDNs = 65L,
		dispidGetAgentDetailsByAgentIDs = 64L,
		dispidGetAgentDetailByAgentDN = 63L,
		dispidGetAgentDetailByAgentID = 62L,
		dispidMuteOff = 61L,
		dispidMuteOn = 60L,
		dispidSendDTMF = 59L,
		dispidBreak = 58L,
		dispidSwitchInsertorListen = 57L,
		dispidStopInsert = 56L,
		dispidInsert = 55L,
		dispidStopListen = 54L,
		dispidListen = 53L,
		dispidForceBusy = 52L,
		dispidForceIdle = 51L,
		dispidForceOut = 50L,
		dispidGetCallData = 49L,
		dispidSetCallData = 48L,
		dispidConference = 47L,
		dispidSingleStepTransfer = 46L,
		dispidTransfer = 45L,
		dispidReconnect = 44L,
		dispidConsult = 43L,
		dispidRetrieve = 42L,
		dispidHold = 41L,
		dispidReleaseCall = 40L,
		dispidAnswer = 39L,
		dispidMakeCall = 38L,
		dispidReset = 37L,
		dispidResetSkill = 36L,
		dispidGetAgentStatus = 35L,
		dispidSetAgentStatus = 34L,
		dispidSetRest = 33L,
		dispidSetBusy = 32L,
		dispidSetIdle = 31L,
		dispidSignOut = 30L,
		dispidSignIn = 29L,
		dispidUnInitial = 28L,
		dispidInitial = 27L,
		dispidAnyProperty = 26,
		dispidEnableSeniorCall = 25,
		dispidLogLevel = 24,
		dispidIsCallOut = 23,
		dispidIsShowCallOut = 22,
		dispidANIChangeType = 21,
		dispidCustomerTag = 20,
		dispidAgentTag = 19,
		dispidPhonePwd = 18,
		dispidPhoneNum = 17,
		dispidSIPServerPort = 16,
		dispidSIPServerIP = 15,
		dispidIsSIPPhone = 14,
		dispidIsSignIn = 13,
		dispidIsInitial = 12,
		dispidTimeOut = 11,
		dispidCTIPort = 10,
		dispidBackCTIIP = 9,
		dispidMainCTIIP = 8,
		dispidServiceList = 7,
		dispidForceSignIn = 6,
		dispidAutoAnswer = 5,
		dispidStatusChangeType = 4,
		dispidDN = 3,
		dispidPassWord = 2,
		dispidAgentID = 1
	};

// 变量，后来添加
private:
	CCCBar *p_m_Bar;

private:
	void GetClippingCoordinates(LPCRECT pPosRect, LPCRECT pClipRect, LPRECT pIntersectRect, LPPOINT pOffsetPoint);

// 函数重载和消息响应，后来添加
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// 属性
protected:
	BSTR GetAgentID(void);
	void SetAgentID(LPCTSTR newVal);
	BSTR GetPassWord(void);
	void SetPassWord(LPCTSTR newVal);
	BSTR GetDN(void);
	void SetDN(LPCTSTR newVal);
	LONG GetStatusChangeType(void);
	void SetStatusChangeType(LONG newVal);
	LONG GetAutoAnswer(void);
	void SetAutoAnswer(LONG newVal);
	LONG GetForceSignIn(void);
	void SetForceSignIn(LONG newVal);
	BSTR GetServiceList(void);
	void SetServiceList(LPCTSTR newVal);
	BSTR GetMainCTIIP(void);
	void SetMainCTIIP(LPCTSTR newVal);
	BSTR GetBackCTIIP(void);
	void SetBackCTIIP(LPCTSTR newVal);
	LONG GetCTIPort(void);
	void SetCTIPort(LONG newVal);
	LONG GetTimeOut(void);
	void SetTimeOut(LONG newVal);
	LONG GetIsInitial(void);
	void SetIsInitial(LONG newVal);
	LONG GetIsSignIn(void);
	void SetIsSignIn(LONG newVal);
	LONG GetIsSIPPhone(void);
	void SetIsSIPPhone(LONG newVal);
	BSTR GetSIPServerIP(void);
	void SetSIPServerIP(LPCTSTR newVal);
	LONG GetSIPServerPort(void);
	void SetSIPServerPort(LONG newVal);
	BSTR GetPhoneNum(void);
	void SetPhoneNum(LPCTSTR newVal);
	BSTR GetPhonePwd(void);
	void SetPhonePwd(LPCTSTR newVal);
	BSTR GetAgentTag(void);
	void SetAgentTag(LPCTSTR newVal);
	BSTR GetCustomerTag(void);
	void SetCustomerTag(LPCTSTR newVal);
	LONG GetANIChangeType(void);
	void SetANIChangeType(LONG newVal);
	LONG GetIsShowCallOut(void);
	void SetIsShowCallOut(LONG newVal);
	LONG GetIsCallOut(void);
	void SetIsCallOut(LONG newVal);
	LONG GetLogLevel(void);
	void SetLogLevel(LONG newVal);
	LONG GetEnableSeniorCall(void);
	void SetEnableSeniorCall(LONG newVal);
	BSTR GetAnyProperty(void);
	void SetAnyProperty(LPCTSTR newVal);

// 方法
protected:
	LONG Initial(void);
	LONG UnInitial(void);
	LONG SignIn(void);
	LONG SignOut(void);
	LONG SetIdle(void);
	LONG SetBusy(void);
	LONG SetRest(LPCTSTR reason);
	LONG SetAgentStatus(LONG agentState, LPCTSTR reason);
	LONG GetAgentStatus(void);
	LONG ResetSkill(LPCTSTR skillList);
	LONG Reset(void);
	LONG MakeCall(LPCTSTR dest, LPCTSTR showANI, LPCTSTR showDest, LONG isOffhook, LONG type);
	LONG Answer(void);
	LONG ReleaseCall(void);
	LONG Hold(void);
	LONG Retrieve(void);
	LONG Consult(LPCTSTR consultNum, LPCTSTR showANI, LPCTSTR showDest, LONG consultType);
	LONG Reconnect(void);
	LONG Transfer(void);
	LONG SingleStepTransfer(LPCTSTR transferNum, LPCTSTR showANI, LPCTSTR showDest, LONG transferStyle, LONG transferType);
	LONG Conference(void);
	LONG SetCallData(LPCTSTR key, LPCTSTR callData);
	BSTR GetCallData(LPCTSTR key);
	LONG ForceOut(LPCTSTR agentID);
	LONG ForceIdle(LPCTSTR agentID);
	LONG ForceBusy(LPCTSTR agentID);
	LONG Listen(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest);
	LONG StopListen(LPCTSTR agentID);
	LONG Insert(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest);
	LONG StopInsert(LPCTSTR agentID);
	LONG SwitchInsertorListen(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest);
	LONG Break(LPCTSTR agentID);
	LONG SendDTMF(LPCTSTR dtmf);
	LONG MuteOn(void);
	LONG MuteOff(void);
	BSTR GetAgentDetailByAgentID(LPCTSTR agentID);
	BSTR GetAgentDetailByAgentDN(LPCTSTR agentDN);
	BSTR GetAgentDetailsByAgentIDs(LPCTSTR agentIDs);
	BSTR GetAgentDetailsByAgentDNs(LPCTSTR agentDNs);
	BSTR GetRecordFileName(void);
	BSTR GetRestReason(void);
	LONG GetAgentNumberBySkill(LPCTSTR skill);
	BSTR GetAgentDetailsBySkill(LPCTSTR skill);
	BSTR GetSkillWaitingNumber(LPCTSTR skill);
	BSTR GetSkillWaitingCallInfo(LPCTSTR skill);
	BSTR GetPrivateQueue(LPCTSTR agentID);
	BSTR GetSysInfo(void);
	BSTR GetCallingNo(void);
	BSTR GetOrgCallingNo(void);
	BSTR GetCalledNo(void);
	BSTR GetOrgCalledNo(void);
	LONG SynchronizeCTITime(void);
	BSTR GetPromptByErrorCode(LONG errCode);
	LONG JumptheQueue(LONGLONG requestId);
	LONG TransIVR(LPCTSTR transferNum);
	LONG TransIVREx(LPCTSTR callerNum, LPCTSTR transferNum);

// 事件
public:
	void OnUnLogin(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnUnLogin, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnReady(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnReady, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnBusy(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnBusy, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnRest(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnRest, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnLock(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnLock, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnAlerting(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnAlerting, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnHarfAlerting(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnHarfAlerting, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnConnecting(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnConnecting, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnConnected(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnConnected, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnHarfConnected(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnHarfConnected, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnInternalConnected(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnInternalConnected, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnSuspended(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnSuspended, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnConsultConnecting(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnConsultConnecting, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnConsultConnected(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnConsultConnected, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnConference(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnConference, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnMonitor(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnMonitor, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnInsert(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnInsert, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnMonitored(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnMonitored, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnInserted(LONG eventID, LPCTSTR callID, LONGLONG contactID, LONG partyNum, LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnInserted, EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	}

	void OnBeginRecord(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnBeginRecord, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8), callID, contactID, filename, reason, timestamp);
	}

	void OnEndRecord(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnEndRecord, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8), callID, contactID, filename, reason, timestamp);
	}
	
	void OnInprivatequeue(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnInprivatequeue, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), callID, contactID, requestID, originalANI, originalDNIS, reason, timestamp);
	}

	void OnOutprivatequeue(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnOutprivatequeue, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), callID, contactID, requestID, originalANI, originalDNIS, reason, timestamp);
	}

	void OnCTIDisconnect(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnCTIDisconnect, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), callID, contactID, originalANI, originalDNIS, reason, timestamp);
	}

	void OnCTIMasterChanged(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnCTIMasterChanged, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), callID, contactID, originalANI, originalDNIS, reason, timestamp);
	}

	void OnOperationFailed(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnOperationFailed, EVENT_PARAM(VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), callID, contactID, originalANI, originalDNIS, reason, timestamp);
	}

	void OnBeforeOutCall(LPCTSTR otherParty, LONG otherPartyAttribute, LPCTSTR originalANI, LPCTSTR originalDNIS, LONG reason, LONGLONG timestamp)
	{
		FireEvent(eventidOnBeforeOutCall, EVENT_PARAM(VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8), otherParty, otherPartyAttribute, originalANI, originalDNIS, reason, timestamp);
	}

    void OnHeartbeat(LONGLONG timestamp)
    {
        FireEvent(eventidOnHeartbeat, EVENT_PARAM(VTS_I8), timestamp);
    }

    void OnBtnStatus(LONGLONG btnStatus, LPCTSTR info)
    {
        FireEvent(eventidOnBtnStatus, EVENT_PARAM(VTS_I8 VTS_BSTR), btnStatus, info);
    }

// 补充的属性、方法和时间
protected:

};
