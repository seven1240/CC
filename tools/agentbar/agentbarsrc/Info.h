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
#include "ButtonIcon.h"
#include "ButtonXP.h"

// CInfo 对话框

class CInfo : public CDialog
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_index;
	CString m_info;
	CBrush  m_BrushBK;

private:
	CButtonXP m_btnOK;
	CButtonXP m_btnCancel;
	CButtonIcon m_btnInfo;
	CEdit m_edtInfo;

protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	void SetInfo(int index, const char *pFormat, ...);

};
