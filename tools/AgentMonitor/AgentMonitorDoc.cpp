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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAgentMonitorDoc

IMPLEMENT_DYNCREATE(CAgentMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CAgentMonitorDoc, CDocument)
END_MESSAGE_MAP()


// CAgentMonitorDoc 构造/析构

CAgentMonitorDoc::CAgentMonitorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CAgentMonitorDoc::~CAgentMonitorDoc()
{
}

BOOL CAgentMonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CAgentMonitorDoc 序列化

void CAgentMonitorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CAgentMonitorDoc 诊断

#ifdef _DEBUG
void CAgentMonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAgentMonitorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAgentMonitorDoc 命令
