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
#include "AgentMonitorConfirm.h"
#include ".\agentmonitorconfirm.h"


// AgentMonitorConfirm 对话框

IMPLEMENT_DYNAMIC(AgentMonitorConfirm, CDialog)
AgentMonitorConfirm::AgentMonitorConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(AgentMonitorConfirm::IDD, pParent)
{
}

AgentMonitorConfirm::~AgentMonitorConfirm()
{
}
BOOL AgentMonitorConfirm::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_brush.CreateSolidBrush(RGB(250,250,250)); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void AgentMonitorConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(AgentMonitorConfirm, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// AgentMonitorConfirm 消息处理程序

void AgentMonitorConfirm::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
	::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_RESETAGENTDETAIL,NULL,NULL);
}

HBRUSH AgentMonitorConfirm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return 0;
}
