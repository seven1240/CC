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
#include "ccagentbarctrl1.h"
#include "AgentFrameView.h"
#include "resource.h"

// CMainFormView 窗体视图

class CMainFormView : public CFormView
{
	DECLARE_DYNCREATE(CMainFormView)

protected:
	CMainFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMainFormView();

public:
	enum { IDD = IDD_MAINFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CAgentFrameView* m_pFrameView;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnGetAgentsData(WPARAM wParam, LPARAM lParam);	
	DECLARE_MESSAGE_MAP()
public:
	CCcagentbarctrl1 m_agentCtrl;
	virtual void OnInitialUpdate();
	CString m_strMainIP;
	CString m_strSlaveIP;
	int m_nPort;
	CString m_strSIPIP;
	CString m_strSIPNum;
	CString m_strAgentId;
	CString m_strAgentPass;
	CString m_strAgentNum;
	CString m_strSkill;
	int m_strSIPPort;
	CString m_strSIPPass;
	int m_nTimeout;
	CString m_strCTag;
	CString m_strATag;
	BOOL m_bSIPIntegrate;
	CString m_strSkillList;
	CString m_strEnabledColumn;

	// BOOL m_bIsLoginIn;
	BOOL m_bIsInited;
	BOOL m_bStartGettingData;
protected:
 	virtual void OnDraw(CDC* /*pDC*/);
public:
	DECLARE_EVENTSINK_MAP()
	void OnReadyCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnBusyCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	afx_msg void OnTimer(UINT nIDEvent);
	void OnUnLoginCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	afx_msg void On32771();
	afx_msg void OnMenuUninit();
	afx_msg void OnMenuOptions();
	void getAgentData(void);
public:
	void getAgentListBySkill(CString skill);
	CString getQueueByAgent(CString agent);
	void getQueueBySkill(CString skill);
	void getSysInfo();
	afx_msg void OnClose();
	afx_msg void OnUpdate32771(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuUninit(CCmdUI *pCmdUI);
};

