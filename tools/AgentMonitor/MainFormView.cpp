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
#include "MainFormView.h"
#include ".\mainformview.h"
#include "json.h"
#include "DataMgr.h"
#include "acdcommon.h"
#include "OptionsDlg.h"
#include <string>
using namespace std;

// CMainFormView
extern void GetModulePath(char *pszPathName);

void ConvertSecondsToDurx(int seconds,char* durx)
{
	int hour = seconds/3600; 
	int minute = (seconds-hour*3600)/60; 
	int second = seconds-hour*3600-minute*60; 
	sprintf(durx,"%2d:%2d:%2d",hour,minute,second);
}

IMPLEMENT_DYNCREATE(CMainFormView, CFormView)

CMainFormView::CMainFormView()
: CFormView(CMainFormView::IDD)
{
	this->m_bStartGettingData = FALSE;
	// this->m_bIsLoginIn = FALSE;
	this->m_bIsInited = FALSE;
}

CMainFormView::~CMainFormView()
{
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CCAGENTBARCTRL1, m_agentCtrl);
}

BEGIN_MESSAGE_MAP(CMainFormView, CFormView)
	ON_WM_TIMER()
	ON_MESSAGE(WM_GETAGENTSDATA, OnGetAgentsData) // deprecated
	ON_COMMAND(ID_32771, On32771)
	ON_COMMAND(ID_MENU_UNINIT, OnMenuUninit)
	ON_COMMAND(ID_MENU_OPTIONS, OnMenuOptions)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_32771, OnUpdate32771)
	ON_UPDATE_COMMAND_UI(ID_MENU_UNINIT, OnUpdateMenuUninit)
END_MESSAGE_MAP()


// CMainFormView 诊断

#ifdef _DEBUG
void CMainFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CMainFormView 消息处理程序

void CMainFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CDataMgr::getInstance()->m_pMainFormView=this;
	this->getAgentData();

	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	this->GetWindowRect(&rect);

	m_agentCtrl.MoveWindow(0,0,rect.Width(),93,1);

	m_pFrameView = ( CAgentFrameView * )RUNTIME_CLASS( CAgentFrameView )->CreateObject();
	m_pFrameView->Create( NULL, NULL, WS_CHILD|WS_VISIBLE, rect, this );

	this->m_pFrameView->MoveWindow(0,93,rect.Width(),rect.Height()-93,1);
	CDataMgr::getInstance()->startGetAgentsDataThread();

}

void CMainFormView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	this->GetWindowRect(&rect); 
	m_agentCtrl.MoveWindow(0,0,rect.Width(),93,1);
	this->m_pFrameView->MoveWindow(0,93,rect.Width(),rect.Height()-93,1);

}
BEGIN_EVENTSINK_MAP(CMainFormView, CFormView)
	ON_EVENT(CMainFormView, IDC_CCAGENTBARCTRL1, 2, OnReadyCcagentbarctrl1, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CMainFormView, IDC_CCAGENTBARCTRL1, 3, OnBusyCcagentbarctrl1, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CMainFormView, IDC_CCAGENTBARCTRL1, 1, OnUnLoginCcagentbarctrl1, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
END_EVENTSINK_MAP()

void CMainFormView::OnReadyCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
										   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	// this->SetTimer(0,1000,NULL);
	this->m_bStartGettingData = TRUE;
}

void CMainFormView::OnBusyCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
										  LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	// this->SetTimer(0,1000,NULL);
	this->m_bStartGettingData = TRUE;
}

void CMainFormView::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(0 == nIDEvent)
	{


		this->PostMessage(WM_GETAGENTSDATA,NULL,NULL); // deprecated
		/*
		CString oriStr = m_strSkillList;
		std::vector<CString> strVec;
		while (true)
		{
		CString n = oriStr.SpanExcluding(",");
		strVec.push_back(n);
		oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
		if (oriStr.IsEmpty())
		{
		break;
		}
		}

		for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
		{
		this->getAgentListBySkill(*it);
		}

		::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_DATACHANGED,NULL,NULL);
		*/
	}

	CFormView::OnTimer(nIDEvent);
}

void CMainFormView::OnUnLoginCcagentbarctrl1(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
											 LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	// this->KillTimer(0);
	this->m_bStartGettingData = FALSE;
	::SendMessage(CDataMgr::getInstance()->m_hSysInfoWnd,WM_DATACHANGED,NULL,NULL);
	::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_DATACHANGED,NULL,NULL);
	::SendMessage(CDataMgr::getInstance()->m_hQueueDetailWnd,WM_DATACHANGED,NULL,NULL);
}

void CMainFormView::getQueueBySkill(CString skill)
{
	string s = this->m_agentCtrl.GetSkillWaitingCallInfo(skill);
	CString str = s.c_str();

	::EnterCriticalSection(&CDataMgr::getInstance()->m_csForQueue);
	CDataMgr::getInstance()->setQueueStringForSkill(skill,str);
	::LeaveCriticalSection(&CDataMgr::getInstance()->m_csForQueue);
}

CString CMainFormView::getQueueByAgent(CString agent)
{
	string s = this->m_agentCtrl.GetPrivateQueue(agent);
	CString str = s.c_str();
	return str;
}

void CMainFormView::getAgentListBySkill(CString skill)
{
	string s = this->m_agentCtrl.GetAgentDetailsBySkill(skill);
	CString str = s.c_str();
	// TRACE(str);
	Json::Value readRoot;

	Json::Reader r;
	r.parse(s,readRoot);

	if(!readRoot.isArray())
		return;

	::EnterCriticalSection(&CDataMgr::getInstance()->m_csForAgents);
	Agents* agentList = CDataMgr::getInstance()->getAgentsBySkill(skill);
	agentList->RemoveAll();

	for(Json::Value::iterator it = readRoot.begin(); it != readRoot.end(); it++)
	{

		Json::Value v = (*it)["agentId"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		const char* cs = v.asCString();
		CString agid = cs;
		/*
		string s2 = this->m_agentCtrl.GetAgentDetailByAgentID(agid);
		CString str2 = s2.c_str();
		*/
		// AfxMessageBox(str2);
		AgentInfo* ai=CDataMgr::getInstance()->getAgentInfoOrCreate(agid);
		strcpy(ai->agentId,cs);

		v = (*it)["agentDn"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		cs = v.asCString();
		strcpy(ai->agentDn,cs);

		v = (*it)["origCaller"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		cs = v.asCString();
		strcpy(ai->origCaller,cs);

		v = (*it)["origCallee"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		cs = v.asCString();
		strcpy(ai->origCallee,cs);

		v = (*it)["agentIP"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		cs = v.asCString();
		strcpy(ai->clientIpAddr,cs);

		v = (*it)["privQueueNum"];
		if(!v)
			continue;
		if(!v.isInt())
			continue; 
		ai->privQueueNum = v.asInt();

		v = (*it)["currStatus"];
		if(!v)
			continue;
		if(!v.isInt())
			continue; 
		int st=v.asInt();
		ai->currStatus=st;

		v = (*it)["loginTime"];
		if(!v)
			continue;
		if(!v.isInt())
			continue; 
		long loginTime = v.asInt();
		CTime c((time_t)loginTime);
		CString lt = c.Format(_T("%Y/%m/%d %H:%M:%S"));
		strcpy(ai->loginTime,lt.GetBuffer());

		v = (*it)["currTime"];
		if(!v)
			continue;
		if(!v.isInt())
			continue; 
		long currTime = v.asInt();

		v = (*it)["currStatusTime"];
		if(!v)
			continue;
		if(!v.isInt())
			continue;
		long currStatusTime = v.asInt();
		CTime c1((time_t)currStatusTime);
		CString ct = c1.Format(_T("%Y/%m/%d %H:%M:%S"));
		strcpy(ai->currStatusTime,ct.GetBuffer());

		int loginDurxSec = currTime - loginTime;
		int currStatusSec = currTime - currStatusTime;
		CTimeSpan lTs(loginDurxSec);
		CTimeSpan cTs(currStatusSec);
		CString loginDurx = lTs.Format("%H:%M:%S");
		CString currStatusDurx = cTs.Format("%H:%M:%S");
		/*
		char loginDurx[128];
		::ConvertSecondsToDurx(loginDurxSec,loginDurx);
		char currStatusDurx[128];
		::ConvertSecondsToDurx(currStatusSec,currStatusDurx);


		strcpy(ai->currStatusDurx,currStatusDurx);
		strcpy(ai->loginDurx,loginDurx);
		*/

		strcpy(ai->currStatusDurx,currStatusDurx.GetBuffer());
		strcpy(ai->loginDurx,loginDurx.GetBuffer());

		agentList->SetAt(agid,1);

		// below codes is for unit test
		// #define UNIT_TEST_MULTIPLE_AGENTS
#ifdef UNIT_TEST_MULTIPLE_AGENTS
		for(int x = 0; x<800; x++)
		{

			CString s2;
			s2.Format("%s%d",agid,x);
			AgentInfo* ai=CDataMgr::getInstance()->getAgentInfoOrCreate(s2);
			srand(time(0));
			ai->currStatus = (acd::AgentStatusT)((rand()+x)%4) ;
			strcpy(ai->agentId,s2.GetBuffer());
			strcpy(ai->agentDn,"01013520935916");
			strcpy(ai->loginDurx,"00:02:23");
			agentList->SetAt(s2,1);

		}
#endif
		// test end
	}	
	::LeaveCriticalSection(&CDataMgr::getInstance()->m_csForAgents);
}

void CMainFormView::getSysInfo()
{
	string s = this->m_agentCtrl.GetSysInfo();
	CString str = s.c_str();
	// AfxMessageBox(str);
	Json::Value readRoot;

	Json::Reader r;
	r.parse(s,readRoot);

	Json::Value v = readRoot["totalAgents"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.totalAgents=v.asInt();

	v = readRoot["totalCalls"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.totalCalls=v.asInt();

	v = readRoot["ivrCalls"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.ivrCalls=v.asInt();

	v = readRoot["agentCalls"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.agentCalls=v.asInt();

	v = readRoot["queueCalls"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.queueCalls=v.asInt();

	v = readRoot["privQueueCalls"];
	if(!v)
		return;
	if(!v.isInt())
		return;
	CDataMgr::getInstance()->m_sysInfo.privQueueCalls=v.asInt();

}

void CMainFormView::On32771()
{
	// TODO: 在此添加命令处理程序代码
	/*
	this->m_agentCtrl.SetMainCTIIP("10.36.159.19");
	this->m_agentCtrl.SetBackCTIIP("10.36.159.19");
	this->m_agentCtrl.SetCTIPort(10000);
	this->m_agentCtrl.SetAgentID("2011");
	this->m_agentCtrl.SetPassWord("2011123");
	this->m_agentCtrl.SetDN("1205");
	this->m_agentCtrl.SetServiceList("咨询");
	this->m_agentCtrl.SetTimeOut(3000);
	this->m_agentCtrl.SetAgentTag("");
	this->m_agentCtrl.SetCustomerTag("agt");


	this->m_agentCtrl.SetStatusChangeType(0);
	this->m_agentCtrl.SetANIChangeType(0);
	this->m_agentCtrl.SetLogLevel(2);
	this->m_agentCtrl.SetAutoAnswer(1);
	this->m_agentCtrl.SetForceSignIn(1);
	this->m_agentCtrl.SetIsInitial(0);
	this->m_agentCtrl.SetIsSignIn(0);
	this->m_agentCtrl.SetIsShowCallOut(1);
	this->m_agentCtrl.SetIsCallOut(1);
	this->m_agentCtrl.SetEnableSeniorCall(0);

	this->m_agentCtrl.SetSIPServerIP("10.36.159.60");
	this->m_agentCtrl.SetSIPServerPort(8060);
	this->m_agentCtrl.SetPhoneNum("1205");
	this->m_agentCtrl.SetPhonePwd("1234");
	this->m_agentCtrl.SetIsSIPPhone(0);
	*/

	this->getAgentData();
	this->m_agentCtrl.SetMainCTIIP(this->m_strMainIP);
	this->m_agentCtrl.SetBackCTIIP(this->m_strSlaveIP);
	this->m_agentCtrl.SetCTIPort(this->m_nPort);
	this->m_agentCtrl.SetAgentID(this->m_strAgentId);
	this->m_agentCtrl.SetPassWord(this->m_strAgentPass);
	this->m_agentCtrl.SetDN(this->m_strAgentNum);
	this->m_agentCtrl.SetServiceList(this->m_strSkill);
	this->m_agentCtrl.SetTimeOut(this->m_nTimeout);
	this->m_agentCtrl.SetAgentTag(this->m_strATag);
	this->m_agentCtrl.SetCustomerTag(this->m_strCTag);
	this->m_agentCtrl.SetStatusChangeType(1);
	 
	// this->m_agentCtrl.SetANIChangeType(0);
	// this->m_agentCtrl.SetLogLevel(2);
	// this->m_agentCtrl.SetAutoAnswer(1);
	// this->m_agentCtrl.SetForceSignIn(1);
	// this->m_agentCtrl.SetIsInitial(0);
	// this->m_agentCtrl.SetIsSignIn(0);
	// this->m_agentCtrl.SetIsShowCallOut(1);
	// this->m_agentCtrl.SetIsCallOut(1);
	// this->m_agentCtrl.SetEnableSeniorCall(0);

	this->m_agentCtrl.SetSIPServerIP(this->m_strSIPIP);
	this->m_agentCtrl.SetSIPServerPort(this->m_strSIPPort);
	this->m_agentCtrl.SetPhoneNum(this->m_strSIPNum);
	this->m_agentCtrl.SetPhonePwd(this->m_strSIPPass);
	this->m_agentCtrl.SetIsSIPPhone(this->m_bSIPIntegrate);

	int ret = m_agentCtrl.Initial();

	CString oriStr = this->m_strSkillList;
	std::vector<CString> strVec;
	while (true)
	{
		CString n = oriStr.SpanExcluding(",");
		strVec.push_back(n);
		oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
		if (oriStr.IsEmpty())
			break;
	}

	for (std::vector<CString>::const_iterator it=strVec.begin();it!=strVec.end();it++)
	{
		CDataMgr::getInstance()->createSkillAgentsMap(*it,new Agents);
		CDataMgr::getInstance()->createSkillQueueMap(*it,"");
	}
	this->m_bIsInited = TRUE;

}

void CMainFormView::OnMenuUninit()
{
	// TODO: 在此添加命令处理程序代码
	this->m_agentCtrl.UnInitial();
	this->m_bIsInited = FALSE;
}

void CMainFormView::OnMenuOptions()
{
	// TODO: 在此添加命令处理程序代码
	COptionsDlg od;
	od.DoModal();
}

void CMainFormView::getAgentData(void)
{

	char path[MAX_PATH];
	GetModulePath(path);

	strcat(path,"\\settings.ini");

	char mainip[MAX_PATH];
	::GetPrivateProfileString("settings","mainip",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetMainCTIIP(),mainip,MAX_PATH,path);
	this->m_strMainIP = mainip;

	char slaveip[MAX_PATH];
	::GetPrivateProfileString("settings","slaveip",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetBackCTIIP(),slaveip,MAX_PATH,path);
	this->m_strSlaveIP = slaveip;

	char agentid[MAX_PATH];
	::GetPrivateProfileString("settings","agentid",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetAgentID(),agentid,MAX_PATH,path);
	this->m_strAgentId = agentid;

	char agentpass[MAX_PATH];
	::GetPrivateProfileString("settings","agentpass",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetPassWord(),agentpass,MAX_PATH,path);
	this->m_strAgentPass = agentpass;

	char agentnum[MAX_PATH];
	::GetPrivateProfileString("settings","agentnum",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetDN(),agentnum,MAX_PATH,path);
	this->m_strAgentNum = agentnum;

	char skill[MAX_PATH];
	::GetPrivateProfileString("settings","skill",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetServiceList(),skill,MAX_PATH,path);
	this->m_strSkill = skill;

	char sipip[MAX_PATH];
	::GetPrivateProfileString("settings","sipip",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetSIPServerIP(),sipip,MAX_PATH,path);
	this->m_strSIPIP = sipip;

	char atag[MAX_PATH];
	::GetPrivateProfileString("settings","atag",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetAgentTag(),atag,MAX_PATH,path);
	this->m_strATag = atag;

	char ctag[MAX_PATH];
	::GetPrivateProfileString("settings","ctag",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetCustomerTag(),ctag,MAX_PATH,path);
	this->m_strCTag = ctag;

	char sipnum[MAX_PATH];
	::GetPrivateProfileString("settings","sipnum",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetPhoneNum(),sipnum,MAX_PATH,path);
	this->m_strSIPNum = sipnum;

	char sippass[MAX_PATH];
	::GetPrivateProfileString("settings","sippass",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetPhonePwd(),sippass,MAX_PATH,path);
	this->m_strSIPPass = sippass;

	m_strSIPPort = ::GetPrivateProfileInt("settings","sipport",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetSIPServerPort(),path);
	m_nPort = ::GetPrivateProfileInt("settings","port",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetCTIPort(),path);
	m_nTimeout = ::GetPrivateProfileInt("settings","timeout",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetTimeOut(),path);
	m_bSIPIntegrate = ::GetPrivateProfileInt("settings","sipintegrate",CDataMgr::getInstance()->m_pMainFormView->m_agentCtrl.GetIsSIPPhone(),path);

	char skilllist[MAX_PATH];
	::GetPrivateProfileString("settings","skilllist","咨询,示例",skilllist,MAX_PATH,path);
	this->m_strSkillList = skilllist;

	char enabledColumn[2560];
	::GetPrivateProfileString("settings","enabledColumn","工号,号码,登录时间,登录时长,当前状态,当前状态时间,当前状态时长,主叫,被叫,私有队列,客户端IP地址",enabledColumn,2560,path);
	this->m_strEnabledColumn = enabledColumn;
}

LRESULT CMainFormView::OnGetAgentsData(WPARAM wParam, LPARAM lParam)
{
	static bool isRun=false;

	if(!isRun)
	{
		isRun=true;
		CString oriStr = m_strSkillList;
		std::vector<CString> strVec;
		while (true)
		{
			CString n = oriStr.SpanExcluding(",");
			strVec.push_back(n);
			oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
			if (oriStr.IsEmpty())
			{
				break;
			}
		}

		for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
		{
			this->getAgentListBySkill(*it);
		}

		::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_DATACHANGED,NULL,NULL);
	}
	else
		return 0;
	isRun=false;
	return 0;
}

void CMainFormView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->m_bStartGettingData = FALSE;
	this->m_agentCtrl.SignOut();
	if(CDataMgr::getInstance()->m_pThread)
		CDataMgr::getInstance()->m_pThread->ExitInstance();
		//::TerminateThread(CDataMgr::getInstance()->m_pThread->m_hThread,0);
		//delete CDataMgr::getInstance()->m_pThread;
		//CDataMgr::getInstance()->m_pThread = NULL;
	CFormView::OnClose();
}

void CMainFormView::OnUpdate32771(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!this->m_bIsInited&&!this->m_bStartGettingData);
}

void CMainFormView::OnUpdateMenuUninit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(this->m_bIsInited&&!this->m_bStartGettingData);
}
