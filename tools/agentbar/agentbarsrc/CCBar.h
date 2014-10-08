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

#include "ButtonEx.h"
#include "StaticEx.h"
#include "CallOut.h"
#include "AcdClient.h"
#include "SipphoneClient.h"

class CCCAgentBarCtrl;

class CCCBar : public CDialog
{
	DECLARE_DYNAMIC(CCCBar)

public:
	CCCBar(CWnd* pParent = NULL);						// 标准构造函数
	virtual ~CCCBar();

	// 对话框数据
	enum { IDD = IDD_DIALOG_CCBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

// 自定义变量
private:
	CCCAgentBarCtrl *p_m_BarCtrl;
	AcdClient m_acd;
	SipphoneClient m_sip;
	CRect m_RectTop;
	CRect m_RectBottom;
	CBrush m_BrushTop;
	CBrush m_BrushBottom;
	acd::AgentStatusT m_AgentStatus;
	ButtonStatus m_lastBtnStatus;
	ButtonStatus m_btnStatus;
	CTime m_beginStatusTime;
	CTime m_lastStatusTime;			// 处理坐席自己改时间
	CTime m_beginTalkTime;
	CTime m_lastTalkTime;			// 处理坐席自己改时间
	CTimeSpan m_totalTime;			// 本次signin之后的开始通话时长
	CCallOut m_dlgCallOut;
	int m_heartbeatCount;
	string m_strActiveCallID;		//当前活动呼叫的callid
	LONGLONG m_lDetaTime;

	bgcc::SharedPointer<bgcc::Thread> m_thrd_heartbeat;	//心跳线程
// 私有函数
private:
	void SetButton();
	// 事件补充器
	void PostMessageEx(const acd::AgentStatusT &agentStatus, const acd::CallEventReasonT &reason);
	void PostMessageEx(const acd::OtherEventTypeT &otherEventType);
	void Backup();
	void ReSignIn();

// 控件
private:
	CButtonEx m_btnSignInOut;
	CButtonEx m_btnAnswer;
	CButtonEx m_btnCallOut;
	CButtonEx m_btnHangup;
	CButtonEx m_btnHold;
	CButtonEx m_btnConsult;
	CButtonEx m_btnTransfer;
	CButtonEx m_btnConference;
	CButtonEx m_btnSingleStepTransfer;
	CButtonEx m_btnRest;
	CButtonEx m_btnReady;
	CButtonEx m_btnBusy;
	CButtonEx m_btnSkillChange;
	CButtonEx m_btnFengeOne;
	CButtonEx m_btnFengeTwo;
	CButtonEx m_btnFengeThree;
	CButtonEx m_btnFengeFour;
	CStaticEx m_stcAgentState;
	CStaticEx m_stcStateTime;
	CStaticEx m_stcTalk;
	CStaticEx m_stcTalkTime;
	CStaticEx m_stcTotalTalk;
	CStaticEx m_stcTotalTalkTime;
	CComboBox m_cmbRest;
	CComboBox m_cmbSkill;

// 函数重载和消息响应
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSigninout();
	afx_msg void OnBnClickedButtonAnswer();
	afx_msg void OnBnClickedButtonCallout();
	afx_msg void OnBnClickedButtonHungup();
	afx_msg void OnBnClickedButtonHold();
	afx_msg void OnBnClickedButtonConsult();
	afx_msg void OnBnClickedButtonTransfer();
	afx_msg void OnBnClickedButtonConference();
	afx_msg void OnBnClickedButtonSinglesteptransfer();
	afx_msg void OnBnClickedButtonRest();
	afx_msg void OnBnClickedButtonReady();
	afx_msg void OnBnClickedButtonBusy();
	afx_msg void OnBnClickedButtonSkillchange();
	afx_msg LRESULT OnAgentEvent(WPARAM wParam, LPARAM lParam);				// 主线程事件
	afx_msg LRESULT OnMediaEvent(WPARAM wParam, LPARAM lParam);				// 主线程事件
	afx_msg LRESULT OnRouteEvent(WPARAM wParam, LPARAM lParam);				// 主线程事件
	afx_msg LRESULT OnOtherEvent(WPARAM wParam, LPARAM lParam);				// 主线程事件

// 公共变量
public:
	CString m_strAgentID;
	CString m_strPassWord;
	CString m_strDN;
	acd::StatusChangeT m_intStatusChangeType;
	BOOL m_intAutoAnswer;
	BOOL m_intForceSignIn;
	CString m_strServiceList;
	CString m_strMainCTIIP;
	CString m_strBackCTIIP;
	LONG m_intCTIPort;
	LONG m_intTimeOut;
	BOOL m_intIsInitial;
	BOOL m_intIsSignIn;
	BOOL m_intIsSIPPhone;
	CString m_strSIPServerIP;
	LONG m_intSIPServerPort;
	CString m_strPhoneNum;
	CString m_strPhonePwd;
	CString m_strAgentTag;
	CString m_strCustomerTag;
	ANICHANGE m_intANIChangeType;
	BOOL m_intIsShowCallOut;
	BOOL m_intIsCallOut;
	Level m_intLogLevel;
	BOOL m_intEnableSeniorCall;

	CString m_callingNo;
	CString m_orgCallingNo;
	CString m_calledNo;
	CString m_orgCalledNo;
	
// 公共函数
public:
	// 回调函数
	LONG BInitial();
	LONG BUnInitial();
	LONG BSignIn();
	LONG BSignOut();
	LONG BSetIdle();
	LONG BSetBusy();
	LONG BSetRest(const char *reason);
	LONG BGetAgentStatus(acd::AgentStatusT &agentStatus);
	// BSetAgentStatus和BGetAgentStatus此处不实现
	LONG BResetSkill(const char *skillList);
	LONG BReset();
	LONG BMakeCall(const char *dest, const char *showANI, const char *showDest, acd::CallModeT callMode, acd::CallTypeT callType);
	LONG BAnswer();
	LONG BReleaseCall();
	LONG BHold();
	LONG BRetrieve();
	LONG BConsult(const char *consultNum, const char *showANI, const char *showDest, acd::CallTypeT callType);
	LONG BReconnect();
	LONG BTransfer();
	LONG BSingleStepTransfer(const char *transferNum, const char *showANI, const char *showDest, BOOL transferStyle, acd::CallTypeT callType);
	LONG BTransferIVR(const char *transferNum, const char *callerNum=NULL); //chenyz add 20130220
	LONG BConference();
	// BSetAssociateData和BGetAssociateData此处不实现
	LONG BListen(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	LONG BStopListen(const char *destAgentId);
	LONG BInsert(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	LONG BStopInsert(const char *destAgentId);
	LONG BSwitchInsertorListen(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	LONG BSendDTMF(const char *digitals);
	LONG BGetRestReason(acd::StringListT &restReason);
	LONG BSynchronizeCTITime();
	LONG BHeartbeat();
	AcdClient &GetAcdClient();
	SipphoneClient &GetSipphoneClient();		// suxiangmao
	// 其他函数此处不实现

};


class HeartBeatTask : public bgcc::Runnable{
private:
	CCCBar *m_bar;
public:
	HeartBeatTask(CCCBar *_bar):m_bar(_bar){}
	int32_t operator()(const bool *isstopped, void *param=NULL);	//心跳线程实现
};
