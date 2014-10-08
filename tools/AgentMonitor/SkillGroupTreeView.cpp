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
 

#include "stdafx.h"
#include "AgentMonitor.h"
#include "SkillGroupTreeView.h"
#include ".\skillgrouptreeview.h"
#include "DataMgr.h"


// CSkillGroupTreeView

IMPLEMENT_DYNCREATE(CSkillGroupTreeView, CTreeView)

CSkillGroupTreeView::CSkillGroupTreeView()
{
	this->m_bTreeInited=FALSE;
}

CSkillGroupTreeView::~CSkillGroupTreeView()
{
}

BEGIN_MESSAGE_MAP(CSkillGroupTreeView, CTreeView)
	ON_MESSAGE(WM_SKILLGROUPCHANGED, OnSkillGroupChanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
END_MESSAGE_MAP()


// CSkillGroupTreeView 诊断

#ifdef _DEBUG
void CSkillGroupTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSkillGroupTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG


// CSkillGroupTreeView 消息处理程序

void CSkillGroupTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CDataMgr::getInstance()->m_hSkillGroupTreeView = this->GetSafeHwnd();

	if(!this->m_bTreeInited)
	{
		CTreeCtrl& theTree = GetTreeCtrl();

		TVINSERTSTRUCT insert;
		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );

		TVITEM item;
		::ZeroMemory( &item, sizeof(TVITEM) );

		insert.hParent =TVI_ROOT;
		insert.hInsertAfter = TVI_LAST;
		item.mask =  TVIF_TEXT|TVIF_PARAM;
		item.pszText = "监控";	// (char*)(LPCTSTR)file;
		item.lParam = 0;
		//item.iImage  = 1; //是文件夹图标
		//tem.iSelectedImage= 1;

		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		HTREEITEM hParent= theTree.InsertItem( &insert );	// 在hParent下插入信息文件项


		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
		::ZeroMemory( &item, sizeof(TVITEM) );
		insert.hParent = hParent;
		insert.hInsertAfter = TVI_LAST;
		item.mask =  TVIF_TEXT|TVIF_PARAM;
		item.lParam = 1;
		CString sz = "系统";
		item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		theTree.InsertItem( &insert );

		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
		::ZeroMemory( &item, sizeof(TVITEM) );
		insert.hParent = hParent;
		insert.hInsertAfter = TVI_LAST;
		item.mask =  TVIF_TEXT|TVIF_PARAM;
		item.lParam = 0;
		sz = "技能";
		item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		HTREEITEM hSkills = theTree.InsertItem( &insert );

		CString oriStr = CDataMgr::getInstance()->m_pMainFormView->m_strSkillList;
		std::vector<CString> strVec;
		while (true)
		{
			CString n = oriStr.SpanExcluding(",");
			strVec.push_back(n);
			oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
			if (oriStr.IsEmpty())
				break;
		}

		for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
		{
			::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
			::ZeroMemory( &item, sizeof(TVITEM) );
			insert.hParent = hSkills;
			insert.hInsertAfter = TVI_LAST;
			item.mask = TVIF_TEXT|TVIF_PARAM;
			item.lParam = 2;
			CString sz = (*it);
			item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
			::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
			theTree.InsertItem( &insert );
		}

		/*
		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
		::ZeroMemory( &item, sizeof(TVITEM) );
		insert.hParent = hParent;
		insert.hInsertAfter = TVI_LAST;
		item.mask = TVIF_TEXT;
		item.pszText = "示例";//(char*)(LPCTSTR)file;
		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		theTree.InsertItem( &insert );

		*/

		theTree.Expand(hParent,TVE_EXPAND );
		theTree.Expand(hSkills,TVE_EXPAND );

		this->m_bTreeInited = TRUE;
	}


}

BOOL CSkillGroupTreeView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	return CTreeView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CSkillGroupTreeView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	HTREEITEM ht = this->GetTreeCtrl().GetSelectedItem();
	CString strSelected = this->GetTreeCtrl().GetItemText(ht);

	LPARAM lp = this->GetTreeCtrl().GetItemData(ht);

	if(2 == lp)
	{
		char* skill = new char[512];
		strcpy(skill,strSelected.GetBuffer());
	
		LONGLONG address = reinterpret_cast<LONGLONG>(skill);
		int ladr = LOLONG(address);
		int hadr = HILONG(address);

		char* skill2 = new char[512];
		strcpy(skill2,strSelected.GetBuffer());
	
		LONGLONG address2 = reinterpret_cast<LONGLONG>(skill2);
		int ladr2 = LOLONG(address2);
		int hadr2 = HILONG(address2);

		
		CString showskill = strSelected.GetBuffer();
		CDataMgr::getInstance()->beginGetBySkill(showskill);

		::SendMessage(CDataMgr::getInstance()->m_hAgentFrameView,WM_DISPLAYAGENTINFO,0,0);
		::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_SKILLCHANGED,ladr,hadr);
		::SendMessage(CDataMgr::getInstance()->m_hQueueDetailWnd,WM_SKILLCHANGED,ladr2,hadr2);
	}
	else if(1 == lp)
	{
		CDataMgr::getInstance()->beginGetSysInfo();
		::SendMessage(CDataMgr::getInstance()->m_hAgentFrameView,WM_DISPLAYSYSINFO,0,0);

	}

	*pResult = 0;
}

BOOL CSkillGroupTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}

LRESULT CSkillGroupTreeView::OnSkillGroupChanged(WPARAM wParam, LPARAM lParam)
{
 	CTreeCtrl& theTree = GetTreeCtrl();

	theTree.DeleteAllItems();

	TVINSERTSTRUCT insert;
	::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );

	TVITEM item;
	::ZeroMemory( &item, sizeof(TVITEM) );

	insert.hParent =TVI_ROOT;
	insert.hInsertAfter = TVI_LAST;
	item.mask =  TVIF_TEXT|TVIF_PARAM;
	item.pszText = "监控";	// (char*)(LPCTSTR)file;
	item.lParam = 0;
	


	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	HTREEITEM hParent= theTree.InsertItem( &insert );	// 在hParent下插入信息文件项


	::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
	::ZeroMemory( &item, sizeof(TVITEM) );
	insert.hParent = hParent;
	insert.hInsertAfter = TVI_LAST;
	item.mask =  TVIF_TEXT|TVIF_PARAM;
	item.lParam = 1;
	CString sz = "系统";
	item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	theTree.InsertItem( &insert );

	::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
	::ZeroMemory( &item, sizeof(TVITEM) );
	insert.hParent = hParent;
	insert.hInsertAfter = TVI_LAST;
	item.mask =  TVIF_TEXT|TVIF_PARAM;
	item.lParam = 0;
	sz = "技能";
	item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
	::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
	HTREEITEM hSkills = theTree.InsertItem( &insert );

	CString oriStr = CDataMgr::getInstance()->m_pMainFormView->m_strSkillList;
	std::vector<CString> strVec;
	while (true)
	{
		CString n = oriStr.SpanExcluding(",");
		strVec.push_back(n);
		oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
		if (oriStr.IsEmpty())
			break;
	}

	for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
	{
		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
		::ZeroMemory( &item, sizeof(TVITEM) );
		insert.hParent = hSkills;
		insert.hInsertAfter = TVI_LAST;
		item.mask = TVIF_TEXT|TVIF_PARAM;
		item.lParam = 2;
		CString sz = (*it);
		item.pszText = sz.GetBuffer();	// (char*)(LPCTSTR)file;
		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		theTree.InsertItem( &insert );
	}

		/*
		::ZeroMemory( &insert, sizeof(TVINSERTSTRUCT) );
		::ZeroMemory( &item, sizeof(TVITEM) );
		insert.hParent = hParent;
		insert.hInsertAfter = TVI_LAST;
		item.mask = TVIF_TEXT;
		item.pszText = "示例";//(char*)(LPCTSTR)file;
		::CopyMemory( &(insert.item), &item, sizeof(TVITEM) );
		theTree.InsertItem( &insert );

		*/

	theTree.Expand(hParent,TVE_EXPAND );
	theTree.Expand(hSkills,TVE_EXPAND );


	return 0;
}