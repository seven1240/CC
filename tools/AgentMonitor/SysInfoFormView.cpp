// SysInfoFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "AgentMonitor.h"
#include "SysInfoFormView.h"
#include ".\sysinfoformview.h"
#include "DataMgr.h"


// CSysInfoFormView

IMPLEMENT_DYNCREATE(CSysInfoFormView, CFormView)

CSysInfoFormView::CSysInfoFormView()
	: CFormView(CSysInfoFormView::IDD)
	, m_strTotalAgents(_T(""))
	, m_strTotalCalls(_T(""))
	, m_strIVRCalls(_T(""))
	, m_strAgentCalls(_T(""))
	, m_strQueueCalls(_T(""))
	, m_strPrivQueueCalls(_T(""))
{
}

CSysInfoFormView::~CSysInfoFormView()
{
}

void CSysInfoFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TOTAL_AGENTS, m_strTotalAgents);
	DDX_Text(pDX, IDC_STATIC_TOTAL_CALLS, m_strTotalCalls);
	DDX_Text(pDX, IDC_STATIC_IVR_CALLS, m_strIVRCalls);
	DDX_Text(pDX, IDC_STATIC_AGENT_CALLS, m_strAgentCalls);
	DDX_Text(pDX, IDC_STATIC_QUEUE_CALLS, m_strQueueCalls);
	DDX_Text(pDX, IDC_STATIC_PRIV_QUEUE_CALLS, m_strPrivQueueCalls);
}

BEGIN_MESSAGE_MAP(CSysInfoFormView, CFormView)
	ON_MESSAGE(WM_DATACHANGED, OnDataChanged)
END_MESSAGE_MAP()


// CSysInfoFormView 诊断

#ifdef _DEBUG
void CSysInfoFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSysInfoFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CSysInfoFormView 消息处理程序

void CSysInfoFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	if (!CDataMgr::getInstance()->m_pMainFormView->m_bStartGettingData)
	{

		CDataMgr::getInstance()->m_sysInfo.totalAgents=0;
		CDataMgr::getInstance()->m_sysInfo.totalCalls=0;
		CDataMgr::getInstance()->m_sysInfo.ivrCalls=0;
		CDataMgr::getInstance()->m_sysInfo.agentCalls=0;
		CDataMgr::getInstance()->m_sysInfo.queueCalls=0;
		CDataMgr::getInstance()->m_sysInfo.privQueueCalls=0;
	}
 
	CDataMgr::getInstance()->m_hSysInfoWnd = this->GetSafeHwnd();
	this->m_strTotalAgents.Format("%d",CDataMgr::getInstance()->m_sysInfo.totalAgents);
	this->m_strTotalCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.totalCalls);
	this->m_strIVRCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.ivrCalls);
	this->m_strAgentCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.agentCalls);
	this->m_strQueueCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.queueCalls);
	this->m_strPrivQueueCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.privQueueCalls);
 

	this->UpdateData(false);

	// TODO: 在此添加专用代码和/或调用基类
}

LRESULT CSysInfoFormView::OnDataChanged(WPARAM wParam, LPARAM lParam)
{
 
	if (!CDataMgr::getInstance()->m_pMainFormView->m_bStartGettingData)
	{

		CDataMgr::getInstance()->m_sysInfo.totalAgents=0;
		CDataMgr::getInstance()->m_sysInfo.totalCalls=0;
		CDataMgr::getInstance()->m_sysInfo.ivrCalls=0;
		CDataMgr::getInstance()->m_sysInfo.agentCalls=0;
		CDataMgr::getInstance()->m_sysInfo.queueCalls=0;
		CDataMgr::getInstance()->m_sysInfo.privQueueCalls=0;
	}
	this->m_strTotalAgents.Format("%d",CDataMgr::getInstance()->m_sysInfo.totalAgents);
	this->m_strTotalCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.totalCalls);
	this->m_strIVRCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.ivrCalls);
	this->m_strAgentCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.agentCalls);
	this->m_strQueueCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.queueCalls);
	this->m_strPrivQueueCalls.Format("%d",CDataMgr::getInstance()->m_sysInfo.privQueueCalls);
	UpdateData(false);
	return 0;
}
