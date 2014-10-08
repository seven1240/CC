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


// CPrivQueueDialog 对话框

class CPrivQueueDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrivQueueDialog)

public:
	CPrivQueueDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivQueueDialog();

// 对话框数据
	enum { IDD = IDD_PRIVQUEUEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_queueList;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDataChanged(WPARAM wParam, LPARAM lParam);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static UINT ThreadGetPrivQueueData(LPVOID param);

	void displayQueue();
 
	BOOL m_bInited;
	CString m_currAgentID;
	CRITICAL_SECTION m_csForQueue;
	CString m_strQueue;
	CWinThread* m_pThread;
	BOOL m_bShouldExitThread;

	afx_msg void OnClose();
	CStatic m_staticQueueStatus;
	afx_msg void OnDestroy();
};
