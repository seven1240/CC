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


// CSkillGroupTreeView 视图

class CSkillGroupTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CSkillGroupTreeView)

protected:
	CSkillGroupTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSkillGroupTreeView();
	BOOL m_bTreeInited;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnSkillGroupChanged(WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


