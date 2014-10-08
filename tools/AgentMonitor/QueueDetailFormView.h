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
#include "afxcmn.h"


// CQueueDetailFormView 窗体视图

class CQueueDetailFormView : public CFormView
{
	DECLARE_DYNCREATE(CQueueDetailFormView)

protected:
	CQueueDetailFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CQueueDetailFormView();

public:
	enum { IDD = IDD_QUEUEDETAILFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnSkillChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDataChanged(WPARAM wParam, LPARAM lParam);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staticQueueStatus;
	CListCtrl m_queueList;
	virtual void OnInitialUpdate();
	BOOL m_bInited;
	CString m_currSkill;

	void displayQueueForSkill(CString skill);
protected:
	virtual void OnDraw(CDC* /*pDC*/);
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};


