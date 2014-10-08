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
#include "PrivQueueDialog.h"
#include ".\privqueuedialog.h"
#include "DataMgr.h"
#include "json.h"
#include "acdcommon.h"
// CPrivQueueDialog 对话框

IMPLEMENT_DYNAMIC(CPrivQueueDialog, CDialog)

int CALLBACK CPrivQueueDialog::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CPrivQueueDialog* pView = reinterpret_cast<CPrivQueueDialog*>( lParamSort);
	ASSERT( pView->IsKindOf( RUNTIME_CLASS( CPrivQueueDialog ) ) );

	PrivQueueInfo* pid1 = reinterpret_cast<PrivQueueInfo*>( lParam1 );
	PrivQueueInfo* pid2 = reinterpret_cast<PrivQueueInfo*>( lParam2 );

	int res = 0;
 
	res = strcmp(pid2->waitDurx,pid1->waitDurx);
	return res;
}

CPrivQueueDialog::CPrivQueueDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivQueueDialog::IDD, pParent)
{
	::InitializeCriticalSection(&m_csForQueue);
	this->m_bInited = FALSE;
	this->m_strQueue = "";
	this->m_currAgentID = "";
	this->m_bShouldExitThread = FALSE;

}

CPrivQueueDialog::~CPrivQueueDialog()
{
}

void CPrivQueueDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_queueList);
	DDX_Control(pDX, IDC_STATIC_PRIV_QUEUE, m_staticQueueStatus);

}


BEGIN_MESSAGE_MAP(CPrivQueueDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_DATACHANGED, OnDataChanged)
END_MESSAGE_MAP()


// CPrivQueueDialog 消息处理程序

void CPrivQueueDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

BOOL CPrivQueueDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->m_pThread = ::AfxBeginThread(this->ThreadGetPrivQueueData,this);
	// TODO:  在此添加额外的初始化
	CFont ft;
	ft.CreateFont(-24, 0, 0, 0, 400, FALSE, FALSE,
	                0,GB2312_CHARSET , OUT_DEFAULT_PRECIS,//ANSI_CHARSET
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                 VARIABLE_PITCH | FF_SCRIPT, "楷体_GB2312");//DEFAULT_PITCH FF_MODERN
	this->m_staticQueueStatus.SetFont(&ft,TRUE);

	if(!m_bInited)
	{

		 

		m_queueList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_queueList.ModifyStyle(0,LVS_REPORT);

 

		LV_COLUMN lvcol;
		lvcol.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcol.pszText = "开始时间";
		lvcol.iSubItem = 0;
		lvcol.cx = 140;
		this->m_queueList.InsertColumn(0, &lvcol);

		lvcol.pszText = "等待时长";
		lvcol.iSubItem = 1;
		lvcol.cx = 100;
		this->m_queueList.InsertColumn(1, &lvcol);
 
		lvcol.pszText = "主叫";
		lvcol.iSubItem = 2;
		lvcol.cx = 150;
		this->m_queueList.InsertColumn(2, &lvcol);

 
		lvcol.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcol.pszText = "被叫";
		lvcol.iSubItem = 3;
		lvcol.cx = 150;
		this->m_queueList.InsertColumn(3, &lvcol);
		
		this->m_bInited=TRUE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CPrivQueueDialog::OnDataChanged(WPARAM wParam, LPARAM lParam)
{
	this->displayQueue();
	return 0;
}

//#define TEST_PRIV_QUEUE
void CPrivQueueDialog::displayQueue()
{
	::EnterCriticalSection(&m_csForQueue);
	CString strQueue = m_strQueue;
	::LeaveCriticalSection(&m_csForQueue);
 
#ifdef TEST_PRIV_QUEUE

	static int xxx = 0;
	xxx ++;
	int yyy = xxx % 100;
	CString testStr;
	CString innerStr;
	for(int ccc = 0; ccc < yyy; ccc++)
	{
	 
		innerStr.AppendFormat("{\"startTime\":%d,\"currTime\":%d,\"origCallee\":\"%d\",\"origCaller\":\"%d\",\"callId\":\"ffdsfdsfds%d\"}",1355210634-ccc,1355218510,ccc,ccc,ccc);
		if(ccc!=yyy-1)
			innerStr.Append(",");
	}

	if(yyy>0)
		strQueue.Format("[%s]",innerStr);
#endif

	CMap<CString,LPCTSTR,PrivQueueInfo*,PrivQueueInfo*> dataMap;
	Json::Value readRoot;

	std::string s = strQueue.GetBuffer();
	Json::Reader r;
	r.parse(s,readRoot);

	if(!readRoot.isArray())
	{
			int listC = m_queueList.GetItemCount();
			for(int j = 0; j < listC; j++)
			{
				//CString* callid = (CString*)(m_queueList.GetItemData(j));
				//delete callid;
				PrivQueueInfo* sqi = (PrivQueueInfo*)(m_queueList.GetItemData(j));
				delete sqi;
			}
			this->m_queueList.DeleteAllItems();	
			return;
	}

	int total = 0;
	for(Json::Value::iterator it = readRoot.begin(); it != readRoot.end(); it++)
	{

		Json::Value v = (*it)["callId"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		const char* callid = v.asCString();
		CString szCallId = callid;
 
		v = (*it)["origCaller"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		const char* origcaller = v.asCString();
		CString szCaller = origcaller;


		v = (*it)["origCallee"];
		if(!v)
			continue;
		if(!v.isString())
			continue; 
		const char* origcallee = v.asCString();
		CString szCallee = origcallee;

		v = (*it)["startTime"];
		if(!v)
			continue;
		if(!v.isNumeric())
			continue; 
		Json::Value::Int64 startTimeL = v.asInt64();
		int startTime = (int)(startTimeL/1000000);
		CTime c((time_t)startTime);
		CString stTime = c.Format(_T("%Y/%m/%d %H:%M:%S"));

		v = (*it)["currTime"];
		if(!v)
			continue;
		if(!v.isNumeric())
			continue; 
		Json::Value::Int64 currTimeL = v.asInt64();
		int currTime = (int)(currTimeL/1000000);



		int waitDurxSec = currTime - startTime;
		CTimeSpan wTs(waitDurxSec);
		CString waitDurx = wTs.Format("%H:%M:%S");

		PrivQueueInfo* ski = new PrivQueueInfo;
		strcpy(ski->callid,szCallId.GetBuffer());
		strcpy(ski->origCaller,szCaller.GetBuffer());
		strcpy(ski->origCallee,szCallee.GetBuffer());
		strcpy(ski->startTime,stTime.GetBuffer());
		strcpy(ski->waitDurx,waitDurx.GetBuffer());
		dataMap.SetAt(szCallId,ski);
		total ++;

	}	


	CString strStatic;
	strStatic.Format("坐席%s的私有队列（共%d个）",this->m_currAgentID,total);
	this->m_staticQueueStatus.SetWindowText(strStatic);

	CMap<CString,LPCTSTR,int,int> uiMap;
	CList<int> deletel;
	int listC = m_queueList.GetItemCount();
	for(int j = 0; j < listC; j++)
	{
		PrivQueueInfo* sqi = (PrivQueueInfo*)(m_queueList.GetItemData(j));
	
		CString callid = sqi->callid;
		PrivQueueInfo* tmpI;
		if(!dataMap.Lookup(callid,tmpI))
		{
			deletel.AddHead(j);
		}

	}

/////////////
	POSITION posList = deletel.GetHeadPosition();
	while(posList != NULL)   
	{   

		int item = deletel.GetNext(posList);
		PrivQueueInfo* sqi = (PrivQueueInfo*)(m_queueList.GetItemData(item));
		delete sqi;
		m_queueList.DeleteItem(item);
	}

	listC = m_queueList.GetItemCount();
	for( j = 0; j < listC; j++)
	{
		PrivQueueInfo* sqi = (PrivQueueInfo*)(m_queueList.GetItemData(j));
		CString callid = sqi->callid;
		uiMap.SetAt(callid,j);
	}

	POSITION pos = dataMap.GetStartPosition();

	while(pos)
	{
		CString callid;
		PrivQueueInfo* ski;
		dataMap.GetNextAssoc(pos, callid, ski);
	 
		LV_ITEM lvi;
		lvi.mask = LVIF_TEXT ;

		int tmpI;
		if(!uiMap.Lookup(callid,tmpI))	// List has no this callid, should create and add
		{
			int cItem = m_queueList.GetItemCount();
			lvi.iItem = cItem;	 
			lvi.mask = LVIF_TEXT | LVIF_PARAM;
			lvi.iSubItem = 0; 
			 
			PrivQueueInfo* sk = new PrivQueueInfo;
			strcpy(sk->callid,ski->callid);
			strcpy(sk->origCaller,ski->origCaller);
			strcpy(sk->startTime,ski->origCallee);
			strcpy(sk->waitDurx,ski->waitDurx);
			lvi.lParam = (LPARAM)sk;

			lvi.pszText = ski->startTime;
			int iItem = this->m_queueList.InsertItem(&lvi);	 
			 
			this->m_queueList.SetItemText(iItem,1,ski->waitDurx);
			this->m_queueList.SetItemText(iItem,2,ski->origCaller);
			this->m_queueList.SetItemText(iItem,3,ski->origCallee);
 

		}
		else //just update
		{
			
			PrivQueueInfo* sk = (PrivQueueInfo*)(m_queueList.GetItemData(tmpI));
			strcpy(sk->callid,ski->callid);
			strcpy(sk->origCaller,ski->origCaller);
			strcpy(sk->startTime,ski->origCallee);
			strcpy(sk->waitDurx,ski->waitDurx);

			this->m_queueList.SetItemText(tmpI,0,ski->startTime);
			this->m_queueList.SetItemText(tmpI,1,ski->waitDurx);
			this->m_queueList.SetItemText(tmpI,2,ski->origCaller);
			this->m_queueList.SetItemText(tmpI,3,ski->origCallee);

		}

	}
 
	this->m_queueList.SortItems(CPrivQueueDialog::CompareFunc,(DWORD_PTR)this);

///////////


	pos = dataMap.GetStartPosition();
	while(pos)
	{
		CString strKey;
		PrivQueueInfo* ski;
		dataMap.GetNextAssoc(pos, strKey, ski);
		delete ski;

	}
	dataMap.RemoveAll();
	
	 
}

// BOOL g_privQueueThreadCanQuit = TRUE;
// BOOL g_privQueueShouldQuit = FALSE;
UINT  CPrivQueueDialog::ThreadGetPrivQueueData(LPVOID param) // 线程函数 
{

	while(1)
	{
		// g_privQueueThreadCanQuit = FALSE;
		// if(g_privQueueShouldQuit) return 0;
		CPrivQueueDialog* dlg = (CPrivQueueDialog*) param;
		if(dlg->m_bShouldExitThread) return 0;
		::EnterCriticalSection(&(dlg->m_csForQueue));
		dlg->m_strQueue = CDataMgr::getInstance()->m_pMainFormView->getQueueByAgent(dlg->m_currAgentID);
		 ::LeaveCriticalSection(&(dlg->m_csForQueue));
		::SendMessage(dlg->GetSafeHwnd(),WM_DATACHANGED,NULL,NULL);
		// g_privQueueThreadCanQuit = TRUE;
		Sleep(1000);

	}

	return 0;

}
void CPrivQueueDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//while(!g_privQueueThreadCanQuit)
	//	Sleep(10);
	//g_privQueueShouldQuit = TRUE;
	this->m_bShouldExitThread = TRUE;
	if(m_pThread)
	{

		::TerminateThread(m_pThread->m_hThread,0);
		//m_pThread->ExitInstance();
		delete this->m_pThread;
		m_pThread = NULL;
	}
	int listC = m_queueList.GetItemCount();
	for(int j = 0; j < listC; j++)
	{
		PrivQueueInfo* sqi = (PrivQueueInfo*)(m_queueList.GetItemData(j));
		delete sqi;
	}
	this->m_queueList.DeleteAllItems();	

	CDialog::OnClose();
}

void CPrivQueueDialog::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
