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


#include "AgentMonitorDoc.h"
// CSysInfoFormView 窗体视图

class CSysInfoFormView : public CFormView
{
	DECLARE_DYNCREATE(CSysInfoFormView)

protected:
	CSysInfoFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSysInfoFormView();

public:
	enum { IDD = IDD_SYSINFOFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnDataChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	CString m_strTotalAgents;
	CString m_strTotalCalls;
	CString m_strIVRCalls;
	CString m_strAgentCalls;
	CString m_strQueueCalls;
	CString m_strPrivQueueCalls;
	virtual void OnInitialUpdate();
};


