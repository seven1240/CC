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
#include "OptionsDlg.h"
#include ".\optionsdlg.h"
#include "DataMgr.h"

#define AGENT_COLUMN_TOTAL 11
// COptionsDlg 对话框
void GetModulePath(char *pszPathName)
{
	size_t nPos = 0;
	char szTmpPath[MAX_PATH] = {0};

	//获取Dll文件全路径名
	GetModuleFileName(NULL, szTmpPath, sizeof(szTmpPath));
	for(size_t i = strlen(szTmpPath); i > 0; i--)     //去除全路径名中最后的文件名
	{											   //即最后一个'\'后的名字
		if(szTmpPath[i] == '\\')                  
		{
			nPos = i;
			break;
		}
	}

	strncpy(pszPathName, szTmpPath, nPos + 1);   
	pszPathName[nPos + 1] = '\0';
	return;
}

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)
COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
	, m_strMainIP(_T(""))
	, m_strSlaveIP(_T(""))
	, m_nPort(0)
	, m_strSIPIP(_T(""))
	, m_strSIPNum(_T(""))
	, m_strAgentId(_T(""))
	, m_strAgentPass(_T(""))
	, m_strAgentNum(_T(""))
	, m_strSkill(_T(""))
	, m_strSIPPort(0)
	, m_strSIPPass(_T(""))
	, m_nTimeout(0)
	, m_strCTag(_T(""))
	, m_strATag(_T(""))
	, m_bSIPIntegrate(FALSE)
	, m_strSkillList(_T(""))
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MAINIP, m_strMainIP);
	DDX_Text(pDX, IDC_EDIT_SLAVEIP, m_strSlaveIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_SIPIP, m_strSIPIP);
	DDX_Text(pDX, IDC_EDIT_SIPNUM, m_strSIPNum);
	DDX_Text(pDX, IDC_EDIT_AGENTID, m_strAgentId);
	DDX_Text(pDX, IDC_EDIT_AGENTPASS, m_strAgentPass);
	DDX_Text(pDX, IDC_EDIT_AGENTNUM, m_strAgentNum);
	DDX_Text(pDX, IDC_EDIT_SKILL, m_strSkill);
	DDX_Text(pDX, IDC_EDIT_SIPPORT, m_strSIPPort);
	DDX_Text(pDX, IDC_EDIT_SIPPASS, m_strSIPPass);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_nTimeout);
	DDX_Text(pDX, IDC_EDIT_CTAG, m_strCTag);
	DDX_Text(pDX, IDC_EDIT_ATAG, m_strATag);
	DDX_Check(pDX, IDC_CHECK_SIP_INTERGRATE, m_bSIPIntegrate);
	DDX_Text(pDX, IDC_EDIT_MAINIP_SKILL_LIST, m_strSkillList);
	DDX_Control(pDX, IDC_LIST3, mListDisable);
	DDX_Control(pDX, IDC_LIST1, mListEnable);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnBnClickedButtonDown)
END_MESSAGE_MAP()


// COptionsDlg 消息处理程序

void COptionsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	char path[MAX_PATH];
	GetModulePath(path);
 
	strcat(path,"\\settings.ini");
	UpdateData(true);

	::WritePrivateProfileString("settings","mainip",(LPCTSTR)this->m_strMainIP,path);
	::WritePrivateProfileString("settings","slaveip",(LPCTSTR)this->m_strSlaveIP,path);
	::WritePrivateProfileString("settings","agentid",(LPCTSTR)this->m_strAgentId,path);
	::WritePrivateProfileString("settings","agentpass",(LPCTSTR)this->m_strAgentPass,path);
	::WritePrivateProfileString("settings","agentnum",(LPCTSTR)this->m_strAgentNum,path);
	::WritePrivateProfileString("settings","skill",(LPCTSTR)this->m_strSkill,path);
	::WritePrivateProfileString("settings","sipip",(LPCTSTR)this->m_strSIPIP,path);
	::WritePrivateProfileString("settings","atag",(LPCTSTR)this->m_strATag,path);
	::WritePrivateProfileString("settings","ctag",(LPCTSTR)this->m_strCTag,path);
	::WritePrivateProfileString("settings","sipnum",(LPCTSTR)this->m_strSIPNum,path);
	::WritePrivateProfileString("settings","sippass",(LPCTSTR)this->m_strSIPPass,path);

	char tmp[16];
	::WritePrivateProfileString("settings","sipport",_itoa(m_strSIPPort,tmp,10),path);
	::WritePrivateProfileString("settings","port",_itoa(m_nPort,tmp,10),path);
	::WritePrivateProfileString("settings","timeout",_itoa(m_nTimeout,tmp,10),path);
	::WritePrivateProfileString("settings","sipintegrate",_itoa(m_bSIPIntegrate,tmp,10),path);

	::WritePrivateProfileString("settings","skilllist",(LPCTSTR)this->m_strSkillList,path);


	this->m_strEnabledColumn = "";
	int c = mListEnable.GetCount();
	for(int x=0 ; x<c; x++)
	{
		CString co; 
		mListEnable.GetText(x,co);
		m_strEnabledColumn += co;
		if(x!=c-1)
			m_strEnabledColumn += ",";

	}

	CDataMgr::getInstance()->m_pMainFormView->m_strEnabledColumn=m_strEnabledColumn;
	::WritePrivateProfileString("settings","enabledColumn",(LPCTSTR)this->m_strEnabledColumn,path);
	CDataMgr::getInstance()->m_pMainFormView->m_strSkillList = this->m_strSkillList;
	::SendMessage(CDataMgr::getInstance()->m_hSkillGroupTreeView,WM_SKILLGROUPCHANGED,NULL,NULL);
	OnOK();

	if(	m_strMainIP_tmp!=   this->m_strMainIP||                      
		m_strSlaveIP_tmp!=  this->m_strSlaveIP||         
		m_nPort_tmp!=       this->m_nPort||    
		m_strSIPIP_tmp!=    this->m_strSIPIP||       
		m_strSIPNum_tmp!=   this->m_strSIPNum||        
		m_strAgentId_tmp!=  this->m_strAgentId||         
		m_strAgentPass_tmp!=this->m_strAgentPass||           
		m_strAgentNum_tmp!= this->m_strAgentNum||          
		m_strSkill_tmp!=    this->m_strSkill||       
		m_strSIPPort_tmp!=  this->m_strSIPPort||         
		m_strSIPPass_tmp!=  this->m_strSIPPass||         
		m_nTimeout_tmp!=    this->m_nTimeout||       
		m_strCTag_tmp!=     this->m_strCTag||      
		m_strATag_tmp!=     this->m_strATag||      
		m_bSIPIntegrate_tmp!= this->m_bSIPIntegrate ||              
		m_strSkillList_tmp!= this->m_strSkillList )
	{
		AgentMonitorConfirm confirm_msg;
		confirm_msg.DoModal();
	}
	else
	{
		//通知刷新界面
		::SendMessage(CDataMgr::getInstance()->m_hAgentDetailWnd,WM_RESETAGENTDETAIL,NULL,NULL);
	}

	
}

void COptionsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	this->getAgentData();
	UpdateData(false);

	m_strMainIP_tmp=   m_strMainIP;           
	m_strSlaveIP_tmp=  m_strSlaveIP;
	m_nPort_tmp=       m_nPort;
	m_strSIPIP_tmp=    m_strSIPIP;
	m_strSIPNum_tmp=   m_strSIPNum;
	m_strAgentId_tmp=  m_strAgentId;
	m_strAgentPass_tmp=m_strAgentPass;
	m_strAgentNum_tmp= m_strAgentNum;
	m_strSkill_tmp=    m_strSkill;
	m_strSIPPort_tmp=  m_strSIPPort;
	m_strSIPPass_tmp=  m_strSIPPass;
	m_nTimeout_tmp=    m_nTimeout;
	m_strCTag_tmp=     m_strCTag;
	m_strATag_tmp=     m_strATag;
	m_bSIPIntegrate_tmp= m_bSIPIntegrate;
	m_strSkillList_tmp= m_strSkillList;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COptionsDlg::getAgentData(void)
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

	char allcolumns[AGENT_COLUMN_TOTAL][256] = {"工号","号码","登录时间","登录时长","当前状态","当前状态时间","当前状态时长","主叫","被叫","私有队列","客户端IP地址"};
	bool columnInEnableList[AGENT_COLUMN_TOTAL] = {false,false,false,false,false,false,false,false,false,false,false};
	//char disable[2560];
 
 
	//GetPrivateProfileString("settings","enabledColumn","",enable,2560,path);
 
	this->m_strEnabledColumn = CDataMgr::getInstance()->m_pMainFormView->m_strEnabledColumn;
	CString oriStr = m_strEnabledColumn;
	std::vector<CString> strVec;
	while (true)
	{
		CString n = oriStr.SpanExcluding(",");
		strVec.push_back(n);
		oriStr = oriStr.Right(oriStr.GetLength()-n.GetLength()-1);
		if (oriStr.IsEmpty())
			break;
	}

	for (std::vector<CString>::const_iterator it = strVec.begin();it != strVec.end();it++)
	{
 
		CString sz = (*it);
		for(int x=0; x<AGENT_COLUMN_TOTAL; x++) 
		{
			if(!sz.Compare(allcolumns[x]))
			{
					columnInEnableList[x]=true;
			
					int c=mListEnable.GetCount();
					this->mListEnable.InsertString(c,sz);
			}
		}
		
	}


	for(int j=0; j<AGENT_COLUMN_TOTAL; j++)
			if(columnInEnableList[j]==false)
				this->mListDisable.InsertString(mListDisable.GetCount(),allcolumns[j]);


}

void COptionsDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	UINT sel=this->mListDisable.GetCurSel();
	if(sel>=0 && sel < UINT_MAX)
	{
		this->mListDisable.GetText(sel,str);
		this->mListDisable.DeleteString(sel);
		this->mListEnable.InsertString(this->mListEnable.GetCount(),str);
	}
}

void COptionsDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if(this->mListEnable.GetCount()<=1) return;
	UINT sel=this->mListEnable.GetCurSel();
	if(sel>=0 && sel < UINT_MAX)
	{
		this->mListEnable.GetText(sel,str);
		this->mListEnable.DeleteString(sel);
		this->mListDisable.InsertString(this->mListDisable.GetCount(),str);
	}
}

void COptionsDlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT sel=this->mListEnable.GetCurSel();
	if(sel>0 && sel < UINT_MAX)
	{
		CString str;
	
		this->mListEnable.GetText(sel,str);
		this->mListEnable.DeleteString(sel);
		this->mListEnable.InsertString(sel-1,str);
		this->mListEnable.SetCurSel(sel-1);
	//	mListEnable.UpdateWindow();
    
	
	}
}

void COptionsDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel=this->mListEnable.GetCurSel();
	if(sel>=0 && sel < this->mListEnable.GetCount()-1)
	{
		CString str;
	
		this->mListEnable.GetText(sel,str);
		this->mListEnable.DeleteString(sel);
		this->mListEnable.InsertString(sel+1,str);
		this->mListEnable.SetCurSel(sel+1);
	
	}
}
