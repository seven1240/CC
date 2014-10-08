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
#include "QueueDetailFormView.h"
#include ".\queuedetailformview.h"
#include "DataMgr.h"
#include "json.h"

// CQueueDetailFormView

IMPLEMENT_DYNCREATE(CQueueDetailFormView, CFormView)

int CALLBACK CQueueDetailFormView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CQueueDetailFormView* pView = reinterpret_cast<CQueueDetailFormView*>( lParamSort);
	ASSERT( pView->IsKindOf( RUNTIME_CLASS( CQueueDetailFormView ) ) );

	SkillQueueInfo* pid1 = reinterpret_cast<SkillQueueInfo*>( lParam1 );
	SkillQueueInfo* pid2 = reinterpret_cast<SkillQueueInfo*>( lParam2 );

	int res = 0;
 
	res = strcmp(pid2->waitDurx,pid1->waitDurx);
	return res;
}

CQueueDetailFormView::CQueueDetailFormView()
	: CFormView(CQueueDetailFormView::IDD)
{
		this->m_bInited=FALSE;
}

CQueueDetailFormView::~CQueueDetailFormView()
{
}

void CQueueDetailFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_QUEUE_STATUS, m_staticQueueStatus);
	DDX_Control(pDX, IDC_LIST2, m_queueList);
}

BEGIN_MESSAGE_MAP(CQueueDetailFormView, CFormView)
	ON_MESSAGE(WM_SKILLCHANGED, OnSkillChanged)
	ON_MESSAGE(WM_DATACHANGED, OnDataChanged)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CQueueDetailFormView 诊断

#ifdef _DEBUG
void CQueueDetailFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQueueDetailFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CQueueDetailFormView 消息处理程序

void CQueueDetailFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	CDataMgr::getInstance()->m_hQueueDetailWnd=this->GetSafeHwnd();

	CFont ft;
	ft.CreateFont(-24, 0, 0, 0, 400, FALSE, FALSE,
	                0,GB2312_CHARSET , OUT_DEFAULT_PRECIS,//ANSI_CHARSET
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                 VARIABLE_PITCH | FF_SCRIPT, "楷体_GB2312");//DEFAULT_PITCH FF_MODERN
	this->m_staticQueueStatus.SetFont(&ft,TRUE);

	if(!m_bInited)
	{

		CRect rect;
		this->GetWindowRect(&rect);
		int width=rect.Width();

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
		

		/*
		int sub = 0;
		CDataMgr::getInstance()->m_privQueueColumn = -1;
		for (std::vector<CString>::const_iterator it = m_strVec.begin();it != m_strVec.end();it++)
		{
 
			CString sz = (*it);
			LV_COLUMN lvcol;	////////插入四个列
			lvcol.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvcol.iSubItem = sub;
			lvcol.pszText = (char*)(LPCTSTR)sz;
			if(!sz.Compare("工号"))
				lvcol.cx = 50;
			else if(!sz.Compare("号码"))
				lvcol.cx = 100;

			else if(!sz.Compare("登录时间"))
			{
				lvcol.cx = 140;
				lvcol.pszText = "登录时间▲";
			}
			else if(!sz.Compare("登录时长"))
				lvcol.cx = 90;
			else if(!sz.Compare("当前状态"))
				lvcol.cx = 80;
			else if(!sz.Compare("当前状态时间"))
				lvcol.cx = 140;
			else if(!sz.Compare("私有队列"))
			{
				lvcol.cx = 80;
				CDataMgr::getInstance()->m_privQueueColumn = sub;
			}
			else if(!sz.Compare("当前状态时长"))
				lvcol.cx = 100;
			else if(!sz.Compare("主叫"))
				lvcol.cx = 100;
			else if(!sz.Compare("被叫"))
				lvcol.cx = 100;	

			this->m_agentList.InsertColumn(sub, &lvcol);
			sub ++;
		}

		*/
		//this->m_sortType=::AGENT_SORT_TYPE_LOGIN_TIME;
		//this->m_sortOrder=AGENT_SORT_ORDER_UP;
		m_queueList.MoveWindow(0,40,rect.Width(),rect.Height()-40,1);
		this->m_bInited=TRUE;
	}

	// TODO: 在此添加专用代码和/或调用基类
}

void CQueueDetailFormView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	this->GetWindowRect(&rect);
	int width=rect.Width();

	m_queueList.MoveWindow(0,40,rect.Width(),rect.Height()-40,1);
}


LRESULT CQueueDetailFormView::OnSkillChanged(WPARAM wParam, LPARAM lParam)
{
	LONGLONG address = MAKELONGLONG(wParam, lParam);
	char* skill = reinterpret_cast<char *>(address);

	this->m_currSkill=skill;
	this->displayQueueForSkill(m_currSkill);

	delete skill;
	return 0;
}

LRESULT CQueueDetailFormView::OnDataChanged(WPARAM wParam, LPARAM lParam)
{
	this->displayQueueForSkill(this->m_currSkill);
	return 0;
}
//#define TEST_SKILL_QUEUE
void CQueueDetailFormView::displayQueueForSkill(CString skill)
{
	::EnterCriticalSection(&CDataMgr::getInstance()->m_csForQueue);
	CString strQueue = CDataMgr::getInstance()->getQueueStringBySkill(skill);
	::LeaveCriticalSection(&CDataMgr::getInstance()->m_csForQueue);

	//strQueue = 
//"[{\"callId\":\"1355301219150683\",\"changeTime\":0,\"contactId\":73412895257078587,\"currTime\":1355301257070543,\"origCallee\":\"\",\"origCaller\":\"1001\",\"requestId\":1355301219151352,\"startTime\":1355301219151358}]";

	// TRACE(strQueue);
 
#ifdef TEST_SKILL_QUEUE

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

	CMap<CString,LPCTSTR,SkillQueueInfo*,SkillQueueInfo*> dataMap;
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
				SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(j)); //队列信息是不断创建的，所以必须删除，否则内存泄漏
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
		//int currTime = (int)(currTimeL/1000000);
		int currTime = (int)(currTimeL);

		int waitDurxSec = currTime - startTime;
		CTimeSpan wTs(waitDurxSec);
		CString waitDurx = wTs.Format("%H:%M:%S");

		SkillQueueInfo* ski = new SkillQueueInfo;
		strcpy(ski->callid,szCallId.GetBuffer());
		strcpy(ski->origCallee,szCallee.GetBuffer());
		strcpy(ski->origCaller,szCaller.GetBuffer());
		strcpy(ski->startTime,stTime.GetBuffer());
		strcpy(ski->waitDurx,waitDurx.GetBuffer());
		dataMap.SetAt(szCallId,ski);
		total ++;

	}	


	CString strStatic;
	strStatic.Format("队列状态（共%d个）",total);
	this->m_staticQueueStatus.SetWindowText(strStatic);

	CMap<CString,LPCTSTR,int,int> uiMap;
	CList<int> deletel;
	int listC = m_queueList.GetItemCount();
	for(int j = 0; j < listC; j++)
	{
		SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(j));
	
		CString callid = sqi->callid;
		SkillQueueInfo* tmpI;
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
		SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(item));
		delete sqi;
		m_queueList.DeleteItem(item);
	}

	listC = m_queueList.GetItemCount();
	for( j = 0; j < listC; j++)
	{
		SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(j));
		CString callid = sqi->callid;
		uiMap.SetAt(callid,j);
	}

	POSITION pos = dataMap.GetStartPosition();

	while(pos)
	{
		CString callid;
		SkillQueueInfo* ski;
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
			 
			SkillQueueInfo* sk = new SkillQueueInfo;
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
			
			SkillQueueInfo* sk = (SkillQueueInfo*)(m_queueList.GetItemData(tmpI));
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
 
	this->m_queueList.SortItems(CQueueDetailFormView::CompareFunc,(DWORD_PTR)this);

///////////


	pos = dataMap.GetStartPosition();
	while(pos)
	{
		CString strKey;
		SkillQueueInfo* ski;
		dataMap.GetNextAssoc(pos, strKey, ski);
		delete ski;

	}
	dataMap.RemoveAll();
	
	 

}

void CQueueDetailFormView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int listC = m_queueList.GetItemCount();
	for(int j = 0; j < listC; j++)
	{
		SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(j));
		delete sqi;
	}
	this->m_queueList.DeleteAllItems();	
	CFormView::OnClose();
}

void CQueueDetailFormView::OnDestroy()
{
	CFormView::OnDestroy();
	int listC = m_queueList.GetItemCount();
	for(int j = 0; j < listC; j++)
	{
		SkillQueueInfo* sqi = (SkillQueueInfo*)(m_queueList.GetItemData(j));
		delete sqi;
	}
	this->m_queueList.DeleteAllItems();	

	// TODO: 在此处添加消息处理程序代码
}
