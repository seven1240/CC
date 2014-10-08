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
#include "AgentFrameView.h"
#include ".\agentframeview.h"
#include "SkillGroupTreeView.h"
#include "DataMgr.h"
#include "SysInfoFormView.h"
#include "AgentDetailFormView.h"
#include "QueueDetailFormView.h"


// CAgentFrameView

IMPLEMENT_DYNCREATE(CAgentFrameView, CFrameWnd)

CAgentFrameView::CAgentFrameView()
{
	this->m_pContext = NULL;
}

CAgentFrameView::~CAgentFrameView()
{
	if(this->m_pWndSplitterV)
		delete m_pWndSplitterV;
}


BEGIN_MESSAGE_MAP(CAgentFrameView, CFrameWnd)
	ON_MESSAGE(WM_DISPLAYSYSINFO, OnGetSysInfo)
	ON_MESSAGE(WM_DISPLAYAGENTINFO, OnAgentInfo)
END_MESSAGE_MAP()


// CAgentFrameView 消息处理程序

BOOL CAgentFrameView::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	this->m_pContext = pContext;
	CDataMgr::getInstance()->m_hAgentFrameView=this->GetSafeHwnd();
	m_wndSplitterH.CreateStatic(this,1,2);	// 对整个窗口进行分割，共一行，二列
	m_wndSplitterH.CreateView(0,0,RUNTIME_CLASS(CSkillGroupTreeView),CSize(200,0),pContext);	// 第0行第0列的视图是CSkillGroupTreeView,列宽为360

	m_pWndSplitterV = new CSplitterWnd();
	if( !m_pWndSplitterV->CreateStatic(&m_wndSplitterH,2,1,WS_CHILD|WS_VISIBLE,m_wndSplitterH.IdFromRowCol(0,1)))
		return FALSE;
	m_pWndSplitterV->CreateView(0,0,RUNTIME_CLASS(CAgentDetailFormView),CSize(0,400),pContext);
	m_pWndSplitterV->CreateView(1,0,RUNTIME_CLASS(CQueueDetailFormView),CSize(0,100),pContext);
	return TRUE;
}

LRESULT CAgentFrameView::OnGetSysInfo(WPARAM wParam, LPARAM lParam)
{
	// LONGLONG address = MAKELONGLONG(wParam, lParam);
	// char* skill = reinterpret_cast<char *>(address);

	/*
	CCreateContext context;
	BOOL bSetActive;

   // ((CSplitter *)GetParent())->ReplaceView(0,1,RUNTIME_CLASS(CView1), size);
   CRuntimeClass* pViewClass = RUNTIME_CLASS(CSysInfoFormView);
   if ((this->m_wndSplitterH.GetPane(0,1)->IsKindOf(pViewClass))==TRUE)
		return FALSE;

 
	// Get pointer to CDocument object so that it can be used in the creation 
	// process of the new view
	CDocument * pDoc= ((CView *)this->m_wndSplitterH.GetPane(0,1))->GetDocument();
	CView * pActiveView=this->m_wndSplitterH.GetParentFrame()->GetActiveView();
	if (pActiveView==NULL || pActiveView==this->m_wndSplitterH.GetPane(0,1))
		bSetActive=TRUE;
	else
		bSetActive=FALSE;

	// set flag so that document will not be deleted when view is destroyed
	//pDoc->m_bAutoDelete=FALSE;    
	// Delete existing view 
	((CView *) this->m_wndSplitterH.GetPane(0,1))->DestroyWindow();
	// set flag back to default 
	//pDoc->m_bAutoDelete=TRUE;

	// Create new view                      

	context.m_pNewViewClass=pViewClass;
	context.m_pCurrentDoc=pDoc;
	context.m_pNewDocTemplate=NULL;
	context.m_pLastView=NULL;
	context.m_pCurrentFrame=NULL;

	this->m_wndSplitterH.CreateView(0,1,pViewClass,CSize(0,100), &context);

	CView * pNewView= (CView *)this->m_wndSplitterH.GetPane(0,1);

	if (bSetActive==TRUE)
		GetParentFrame()->SetActiveView(pNewView);

	RecalcLayout(); 
	this->m_wndSplitterH.GetPane(0,1)->SendMessage(WM_PAINT);
	//this->Invalidate();
	pNewView->ShowWindow(SW_SHOW);
 */

	CRuntimeClass* pViewClass = RUNTIME_CLASS(CSysInfoFormView);
    if ((this->m_wndSplitterH.GetPane(0,1)->IsKindOf(pViewClass)))
		return FALSE;

	
	((CView *) this->m_wndSplitterH.GetPane(0,1))->DestroyWindow(); 
	delete this->m_pWndSplitterV;
	this->m_pWndSplitterV = NULL;
	this->m_wndSplitterH.CreateView(0,1,pViewClass,CSize(0,100),  m_pContext);
	
	CView * pNewView= (CView *)this->m_wndSplitterH.GetPane(0,1);
	this->m_wndSplitterH.RecalcLayout();
	this->m_wndSplitterH.GetPane(0,1)->SendMessage(WM_PAINT);

	return 0;
} 

LRESULT CAgentFrameView::OnAgentInfo(WPARAM wParam, LPARAM lParam)
{
	// LONGLONG address = MAKELONGLONG(wParam, lParam);
	// char* skill = reinterpret_cast<char *>(address);

	/*
	CCreateContext context;
	BOOL bSetActive;

   // ((CSplitter *)GetParent())->ReplaceView(0,1,RUNTIME_CLASS(CView1), size);
   CRuntimeClass* pViewClass = RUNTIME_CLASS(CSysInfoFormView);
   if ((this->m_wndSplitterH.GetPane(0,1)->IsKindOf(pViewClass))==TRUE)
		return FALSE;

 
	// Get pointer to CDocument object so that it can be used in the creation 
	// process of the new view
	CDocument * pDoc= ((CView *)this->m_wndSplitterH.GetPane(0,1))->GetDocument();
	CView * pActiveView=this->m_wndSplitterH.GetParentFrame()->GetActiveView();
	if (pActiveView==NULL || pActiveView==this->m_wndSplitterH.GetPane(0,1))
		bSetActive=TRUE;
	else
		bSetActive=FALSE;

	// set flag so that document will not be deleted when view is destroyed
	//pDoc->m_bAutoDelete=FALSE;    
	// Delete existing view 
	((CView *) this->m_wndSplitterH.GetPane(0,1))->DestroyWindow();
	// set flag back to default 
	//pDoc->m_bAutoDelete=TRUE;

	// Create new view                      

	context.m_pNewViewClass=pViewClass;
	context.m_pCurrentDoc=pDoc;
	context.m_pNewDocTemplate=NULL;
	context.m_pLastView=NULL;
	context.m_pCurrentFrame=NULL;

	this->m_wndSplitterH.CreateView(0,1,pViewClass,CSize(0,100), &context);

	CView * pNewView= (CView *)this->m_wndSplitterH.GetPane(0,1);

	if (bSetActive==TRUE)
		GetParentFrame()->SetActiveView(pNewView);

	RecalcLayout(); 
	this->m_wndSplitterH.GetPane(0,1)->SendMessage(WM_PAINT);
	//this->Invalidate();
	pNewView->ShowWindow(SW_SHOW);
 */

	/*
	CRuntimeClass* pViewClass = RUNTIME_CLASS(CAgentDetailFormView);
    if ((this->m_wndSplitterH.GetPane(0,1)->IsKindOf(pViewClass))==TRUE)
		return FALSE;

	((CView *) this->m_wndSplitterH.GetPane(0,1))->DestroyWindow();                
	this->m_wndSplitterH.CreateView(0,1,pViewClass,CSize(0,100),  m_pContext);

	CView * pNewView= (CView *)this->m_wndSplitterH.GetPane(0,1);
	this->m_wndSplitterH.RecalcLayout();
	this->m_wndSplitterH.GetPane(0,1)->SendMessage(WM_PAINT);
	*/



	/*
	if(! m_wndSplitterV.CreateStatic(&m_wndSplitterH,2,1,WS_CHILD|WS_VISIBLE,m_wndSplitterH.IdFromRowCol(0,1)))
		return FALSE;

	m_wndSplitterV.CreateView(0,0,pViewClass,CSize(0,400),m_pContext);
	m_wndSplitterV.CreateView(1,0,RUNTIME_CLASS(CQueueDetailFormView),CSize(0,100),m_pContext);
	this->m_wndSplitterV.GetPane(0,0)->SendMessage(WM_PAINT);
	*/

	// CRuntimeClass* pViewClass = m_pWndSplitterV->GetRuntimeClass();
	if (this->m_pWndSplitterV)
	 	return FALSE;

	this->m_pWndSplitterV = new CSplitterWnd();
	((CView *) this->m_wndSplitterH.GetPane(0,1))->DestroyWindow();  


	 if(! m_pWndSplitterV->CreateStatic(&m_wndSplitterH,2,1,WS_CHILD|WS_VISIBLE,m_wndSplitterH.IdFromRowCol(0,1)))
	 	return FALSE;

	m_pWndSplitterV->CreateView(0,0,RUNTIME_CLASS(CAgentDetailFormView),CSize(0,400),m_pContext);
	m_pWndSplitterV->CreateView(1,0,RUNTIME_CLASS(CQueueDetailFormView),CSize(0,100),m_pContext);

	         
	//this->m_wndSplitterH.CreateView(0,1,pViewClass,CSize(0,100),  m_pContext);

	CView * pNewView= (CView *)this->m_pWndSplitterV->GetPane(0,0);
	this->m_wndSplitterH.RecalcLayout();
	pNewView->SendMessage(WM_PAINT);

	return TRUE;
 
 
}
