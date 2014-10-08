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

#include "Resource.h"
#include "ButtonXP.h"
#include "EditEx.h"

class CCallOut : public CDialog
{
	DECLARE_DYNAMIC(CCallOut)

public:
	CCallOut(CWnd* pParent = NULL);						// 标准构造函数
	virtual ~CCallOut();

	// 对话框数据
	enum { IDD = IDD_DIALOG_CALLOUT };

// 自动生成
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

// 控件变量
private:
	CButton m_rdoAgent;
	CButton m_rdoOut;
	CButtonXP m_btnOK;
	CButtonXP m_btnCancel;
	CEditEx m_editNumber;
	CString m_strNumber;

// 函数重载和消息响应
protected:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// 私有变量
private:
	CBrush m_BrushBK;
	LONG m_posX;
	LONG m_posY;
	int m_intAgentOrOut;

// 公共函数
public:
	void SetPosition(LONG x, LONG y);
	int GetAgentOrOut();
	CString &GetNumber();

};
