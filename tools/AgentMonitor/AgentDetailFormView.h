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
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
enum AGENT_SORT_TYPE
{
	AGENT_SORT_TYPE_AGENT_ID,
	AGENT_SORT_TYPE_AGEND_DN,
	AGENT_SORT_TYPE_LOGIN_TIME,
	AGENT_SORT_TYPE_LOGIN_DURX,
	AGENT_SORT_TYPE_CURR_STATUS,
	AGENT_SORT_TYPE_CURR_STATUS_TIME,
	AGENT_SORT_TYPE_CURR_STATUS_DURX,
	AGENT_SORT_TYPE_ORIG_CALLER,
	AGENT_SORT_TYPE_ORIG_CALLEE,
	AGENT_SORT_TYPE_ORIG_PRIVATE_QUEUE_NUM,
	AGENT_SORT_TYPE_ORIG_CLIENT_IPADDR,
	AGENT_SORT_TYPE_NONE
};

enum AGENT_SORT_ORDER
{
	AGENT_SORT_ORDER_UP,
	AGENT_SORT_ORDER_DOWN
};
// CAgentDetailFormView 窗体视图

class CAgentDetailFormView : public CFormView
{
	DECLARE_DYNCREATE(CAgentDetailFormView)

protected:
	CAgentDetailFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAgentDetailFormView();

public:
	enum { IDD = IDD_AGENTDETAILFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
 
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnSkillChanged(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT OnDataChanged(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT OnResetDetail(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CListCtrl m_agentList;
	BOOL m_bInited;
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	void displayAgentsForSkill(CString skill);
	CButton m_chkIdle;
	CButton m_chkBusy;
	CButton m_chkRest;
	CButton m_chkTalking;
	CButton m_chkTalkingProgress;
	CString m_currSkill;
	AGENT_SORT_TYPE m_sortType;
	AGENT_SORT_ORDER m_sortOrder;
	afx_msg void OnBnClickedCheckTalking();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	afx_msg void OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckIdle();
	afx_msg void OnBnClickedCheckBusy();
	afx_msg void OnBnClickedCheckRest();
	afx_msg void OnBnClickedCheckTalkingProgress();
	afx_msg void On32774();
	afx_msg void OnUpdate32774(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentSetBusy();
	afx_msg void OnUpdateMenuAgentSetBusy(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentSignout();
	afx_msg void OnUpdateMenuAgentSignout(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentMonitor();
	afx_msg void OnUpdateMenuAgentMonitor(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentStopMonitor();
	afx_msg void OnUpdateMenuAgentStopMonitor(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentInsert();
	afx_msg void OnUpdateMenuAgentInsert(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentStopInsert();
	afx_msg void OnUpdateMenuAgentStopInsert(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentInsertMonitorConvert();
	afx_msg void OnUpdateMenuAgentInsertMonitorConvert(CCmdUI *pCmdUI);
	afx_msg void OnMenuAgentBreak();
	afx_msg void OnUpdateMenuAgentBreak(CCmdUI *pCmdUI);
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CButton m_chkMonitor;
	CButton m_chkOther;
	afx_msg void OnBnClickedCheckMonitor();
	afx_msg void OnBnClickedCheckOther();

	CStatic m_txtAll;
	std::vector<CString> m_strVec;
	afx_msg void OnBnClickedButtonForceSignoutAll();
	CStatic m_staticAgentsStatus;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};

