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
#include <afxtempl.h>
#include "acdcommon.h"
#include "MainFormView.h"

typedef struct //座席信息
{
	char agentId[64];
	char agentDn[64];
	int currStatus;
	char loginTime[64];
	char loginDurx[64];
	char currStatusTime[64];
	char currStatusDurx[64];
	char origCaller[128];
	char origCallee[128];
	char statusStr[256];
	int	privQueueNum;
	char clientIpAddr[128];
} AgentInfo;

typedef struct //技能队列信息
{
	char callid[128];
	char startTime[64];
	char waitDurx[64];
	char origCaller[128];
	char origCallee[128];

} SkillQueueInfo;


typedef struct //私有队列信息
{
	char callid[128];
	char startTime[64];
	char waitDurx[64];
	char origCaller[128];
	char origCallee[128];

} PrivQueueInfo;

struct SysInfoT //系统统计数据
{
    int totalAgents;
    int totalCalls;
    int ivrCalls;
    int agentCalls;
    int queueCalls;
    int privQueueCalls;
};

typedef CMap<CString,LPCTSTR,int,int> Agents; //座席Map（座席号，某个整数）
typedef CMap<CString,LPCTSTR,AgentInfo*,AgentInfo*> AgentMap; //座席信息Map（座席号，座席信息）
typedef CMap<CString,LPCTSTR,Agents*,Agents*>	SkillAgentsMap; //技能座席Map （技能，座席Map）,保存每个技能的座席
typedef CMap<CString,LPCTSTR,CString,LPCTSTR>	SkillQueueMap; //技能队列Map （技能，队列String），保存每个技能的队列字串
#define MAKELONGLONG(a, b) ((__int64)(((unsigned __int64)(a) & 0xffffffff) | ((unsigned __int64)(b) & 0xffffffff) << 32))
#define LOLONG(a) ((__int32)((unsigned __int64)(a) & 0xffffffff))
#define HILONG(a) ((__int32)((unsigned __int64)(a) >> 32))

#define WM_SKILLCHANGED WM_USER+9900 //用户选择了某个技能
#define WM_DATACHANGED WM_USER+9901 //后台线程获取了数据，需要界面更新
#define WM_GETAGENTSDATA WM_USER+9902 // deprecated
#define WM_DISPLAYSYSINFO WM_USER+9903 //需要显示系统统计信息
#define WM_DISPLAYAGENTINFO WM_USER+9904 //需要显示技能信息
#define WM_SKILLGROUPCHANGED WM_USER+9905
#define WM_RESETAGENTDETAIL WM_USER+9906 //需要显示技能信息

#define WM_SKILLNODE WM_USER+9907 //需要查询的技能节点
#define WM_SYSINFONODE WM_USER+9908 //需要显示sysinfo节点

class CDataMgr
{
public:
	CDataMgr(void);
	~CDataMgr(void);

	static CDataMgr* getInstance();
	void startGetAgentsDataThread();
	static UINT ThreadGetAgentsAndQueueData(LPVOID param);
	void createSkillAgentsMap(CString skill, Agents* pAgents);
	void createSkillQueueMap(CString skill, CString strQueue);
	void setQueueStringForSkill(CString skill, CString queueStr);
	Agents* getAgentsBySkill(CString skill);
	void setAgentInfo(CString agentId,AgentInfo* pAgentInfo);
	AgentInfo* getAgentInfo(CString agentId);
	AgentInfo* getAgentInfoOrCreate(CString agentId);
	CString CDataMgr::getQueueStringBySkill(CString skill);
	
	void beginGetSysInfo();
	void beginGetBySkill(CString skill);


	SkillAgentsMap m_skillAgentsMap;
	AgentMap m_agentMap;
	SkillQueueMap m_skillQueueMap;
	HWND m_hAgentDetailWnd;
	HWND m_hQueueDetailWnd;
	HWND m_hSysInfoWnd;
	HWND m_hAgentFrameView;
	HWND m_hSkillGroupTreeView;
	CMainFormView* m_pMainFormView;
	CWinThread* m_pThread;
	SysInfoT m_sysInfo;
	CRITICAL_SECTION m_csForAgents; //保护座席相关数据的临界区
	CRITICAL_SECTION m_csForQueue; //保护技能队列相关数据的临界区
	int m_privQueueColumn;



private:
	static CDataMgr* m_dataMgr;
};
