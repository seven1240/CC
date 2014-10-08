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

#include "AgentMonitorDoc.h"
#include "AgentMonitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAgentMonitorView

IMPLEMENT_DYNCREATE(CAgentMonitorView, CView)

BEGIN_MESSAGE_MAP(CAgentMonitorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAgentMonitorView 构造/析构

CAgentMonitorView::CAgentMonitorView()
{
	// TODO: 在此处添加构造代码

}

CAgentMonitorView::~CAgentMonitorView()
{
}

BOOL CAgentMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CAgentMonitorView 绘制

void CAgentMonitorView::OnDraw(CDC* /*pDC*/)
{
	CAgentMonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CAgentMonitorView 打印

BOOL CAgentMonitorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAgentMonitorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CAgentMonitorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CAgentMonitorView 诊断

#ifdef _DEBUG
void CAgentMonitorView::AssertValid() const
{
	CView::AssertValid();
}

void CAgentMonitorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAgentMonitorDoc* CAgentMonitorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAgentMonitorDoc)));
	return (CAgentMonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CAgentMonitorView 消息处理程序
