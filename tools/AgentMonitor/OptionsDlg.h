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
#include "afxwin.h"
#include "AgentMonitorConfirm.h"

// COptionsDlg 对话框

class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionsDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
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

	virtual BOOL OnInitDialog();
	void getAgentData(void);
	CListBox mListDisable;
	CListBox mListEnable;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();


	CString m_strMainIP_tmp;
	CString m_strSlaveIP_tmp;
	int m_nPort_tmp;
	CString m_strSIPIP_tmp;
	CString m_strSIPNum_tmp;
	CString m_strAgentId_tmp;
	CString m_strAgentPass_tmp;
	CString m_strAgentNum_tmp;
	CString m_strSkill_tmp;
	int m_strSIPPort_tmp;
	CString m_strSIPPass_tmp;
	int m_nTimeout_tmp;
	CString m_strCTag_tmp;
	CString m_strATag_tmp;
	BOOL m_bSIPIntegrate_tmp;
	CString m_strSkillList_tmp;
	CString m_strEnabledColumn_tmp;
};
