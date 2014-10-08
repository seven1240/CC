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
 

#include "StdAfx.h"
#include ".\datamgr.h"

CDataMgr* CDataMgr::m_dataMgr = NULL;


CString m_showSkill = "";//需要显示的技能
bool m_ifShowSysInfo = false;//是否显示sysinfo信息标志位

CDataMgr::CDataMgr(void)
{
	this->m_pMainFormView = NULL;
	::InitializeCriticalSection(&m_csForAgents);
	::InitializeCriticalSection(&m_csForQueue);

	memset(&this->m_sysInfo,0,sizeof(SysInfoT));
	this->m_pThread = NULL;
	this->m_hAgentDetailWnd  = NULL;
	this->m_hQueueDetailWnd = NULL;
	this->m_hSysInfoWnd = NULL;
	this->m_hSkillGroupTreeView = NULL;
	this->m_privQueueColumn = -1;

	//this->m_ifShowSysInfo = false;
	//this->m_showSkill = "";
}

CDataMgr::~CDataMgr(void)
{
	this->m_hAgentDetailWnd = NULL;
	this->m_hQueueDetailWnd = NULL;
}

void CDataMgr::createSkillAgentsMap(CString skill,  Agents* pAgentList)
{
	m_skillAgentsMap[skill] = pAgentList;
}

void CDataMgr::createSkillQueueMap(CString skill, CString strQueue)
{
	m_skillQueueMap[skill] = strQueue;
}

CDataMgr* CDataMgr::getInstance()
{
	if(!m_dataMgr)
		m_dataMgr = new CDataMgr();

	return m_dataMgr;
}


Agents* CDataMgr::getAgentsBySkill(CString skill)
{
	Agents* pList = m_skillAgentsMap[skill];
	return pList;
}

CString CDataMgr::getQueueStringBySkill(CString skill)
{
	CString strQueue = m_skillQueueMap[skill];
	return strQueue;
}

void CDataMgr::setQueueStringForSkill(CString skill, CString queueStr)
{
	m_skillQueueMap[skill]=queueStr;
}

void CDataMgr::setAgentInfo(CString agentId, AgentInfo* pAgentInfo)
{
	m_agentMap[agentId] = pAgentInfo;
}

AgentInfo* CDataMgr::getAgentInfo(CString agentId)
{
	AgentInfo* ai = m_agentMap[agentId];
	return ai;
}

AgentInfo* CDataMgr::getAgentInfoOrCreate(CString agentId)
{

	AgentInfo* ai = m_agentMap[agentId];
	if(ai==NULL)
	{
		ai = new AgentInfo;
		memset(ai,0,sizeof(AgentInfo));
		m_agentMap[agentId] = ai;
	}
	return ai;
}

void CDataMgr::startGetAgentsDataThread()
{

	this->m_pThread = ::AfxBeginThread(this->ThreadGetAgentsAndQueueData,NULL);
}

UINT  CDataMgr::ThreadGetAgentsAndQueueData(LPVOID param) // 线程函数，此后台线程通过AgentBar控件从ACD SERVER获取监控数据
{


	while(1)
	{

		if(CDataMgr::getInstance()->m_pMainFormView->m_bStartGettingData)
		{
			//CString oriStr = CDataMgr::getInstance()->m_pMainFormView->m_strSkillList;
			//std::vector<CString> strVec;
			//while (true)
			//{
			//	CString n = oriStr.SpanExcluding(",");
			//	strVec.push_back(n);
			//	oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
			//	if (oriStr.IsEmpty())
			//	{
			//		break;
			//	}
			//}

			//for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
			//{
			//	CDataMgr::getInstance()->m_pMainFormView->getAgentListBySkill(*it); //得到技能组的座席列表
			//	CDataMgr::getInstance()->m_pMainFormView->getQueueBySkill(*it); //得到技能组的排队队列
			//}
			if(m_showSkill!="")
			{
				CDataMgr::getInstance()->m_pMainFormView->getAgentListBySkill(m_showSkill); //得到技能组的座席列表
				CDataMgr::getInstance()->m_pMainFormView->getQueueBySkill(m_showSkill); //得到技能组的排队队列

				::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_DATACHANGED,NULL,NULL); //通知CAgentDetailFormView
				::SendMessage(CDataMgr::getInstance()->m_hQueueDetailWnd,WM_DATACHANGED,NULL,NULL); //通知CQueueInfoFormView
			}
			if(m_ifShowSysInfo)
			{
				CDataMgr::getInstance()->m_pMainFormView->getSysInfo();
				::SendMessage(CDataMgr::getInstance()->m_hSysInfoWnd,WM_DATACHANGED,NULL,NULL); // 通知CSysInfoFormView
			}
		}

		Sleep(1000);
	}

	return 0;

}

void CDataMgr::beginGetSysInfo()
{
	m_ifShowSysInfo = true;
	m_showSkill = "";
}
void CDataMgr::beginGetBySkill(CString skill)
{
	m_ifShowSysInfo = false;
	m_showSkill = skill;
}
