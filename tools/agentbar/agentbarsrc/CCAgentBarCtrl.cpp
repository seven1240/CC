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

#include "CCAgentBarCtrl.h"
#include "CCAgentBar.h"
#include "CCAgentBarPropPage.h"
#include "json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCCAgentBarCtrl, COleControl)

// 消息映射
BEGIN_MESSAGE_MAP(CCCAgentBarCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// 调度映射
BEGIN_DISPATCH_MAP(CCCAgentBarCtrl, COleControl)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "AgentID", dispidAgentID, GetAgentID, SetAgentID, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "PassWord", dispidPassWord, GetPassWord, SetPassWord, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "DN", dispidDN, GetDN, SetDN, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "StatusChangeType", dispidStatusChangeType, GetStatusChangeType, SetStatusChangeType, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "AutoAnswer", dispidAutoAnswer, GetAutoAnswer, SetAutoAnswer, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "ForceSignIn", dispidForceSignIn, GetForceSignIn, SetForceSignIn, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "ServiceList", dispidServiceList, GetServiceList, SetServiceList, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "MainCTIIP", dispidMainCTIIP, GetMainCTIIP, SetMainCTIIP, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "BackCTIIP", dispidBackCTIIP, GetBackCTIIP, SetBackCTIIP, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "CTIPort", dispidCTIPort, GetCTIPort, SetCTIPort, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "TimeOut", dispidTimeOut, GetTimeOut, SetTimeOut, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "IsInitial", dispidIsInitial, GetIsInitial, SetIsInitial, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "IsSignIn", dispidIsSignIn, GetIsSignIn, SetIsSignIn, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "IsSIPPhone", dispidIsSIPPhone, GetIsSIPPhone, SetIsSIPPhone, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "SIPServerIP", dispidSIPServerIP, GetSIPServerIP, SetSIPServerIP, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "SIPServerPort", dispidSIPServerPort, GetSIPServerPort, SetSIPServerPort, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "PhoneNum", dispidPhoneNum, GetPhoneNum, SetPhoneNum, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "PhonePwd", dispidPhonePwd, GetPhonePwd, SetPhonePwd, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "AgentTag", dispidAgentTag, GetAgentTag, SetAgentTag, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "CustomerTag", dispidCustomerTag, GetCustomerTag, SetCustomerTag, VT_BSTR)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "ANIChangeType", dispidANIChangeType, GetANIChangeType, SetANIChangeType, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "IsShowCallOut", dispidIsShowCallOut, GetIsShowCallOut, SetIsShowCallOut, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "IsCallOut", dispidIsCallOut, GetIsCallOut, SetIsCallOut, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "LogLevel", dispidLogLevel, GetLogLevel, SetLogLevel, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "EnableSeniorCall", dispidEnableSeniorCall, GetEnableSeniorCall, SetEnableSeniorCall, VT_I4)
	DISP_PROPERTY_EX_ID(CCCAgentBarCtrl, "AnyProperty", dispidAnyProperty, GetAnyProperty, SetAnyProperty, VT_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Initial", dispidInitial, Initial, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "UnInitial", dispidUnInitial, UnInitial, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SignIn", dispidSignIn, SignIn, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SignOut", dispidSignOut, SignOut, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SetIdle", dispidSetIdle, SetIdle, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SetBusy", dispidSetBusy, SetBusy, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SetRest", dispidSetRest, SetRest, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SetAgentStatus", dispidSetAgentStatus, SetAgentStatus, VT_I4, VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentStatus", dispidGetAgentStatus, GetAgentStatus, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "ResetSkill", dispidResetSkill, ResetSkill, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Reset", dispidReset, Reset, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "MakeCall", dispidMakeCall, MakeCall, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Answer", dispidAnswer, Answer, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "ReleaseCall", dispidReleaseCall, ReleaseCall, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Hold", dispidHold, Hold, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Retrieve", dispidRetrieve, Retrieve, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Consult", dispidConsult, Consult, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Reconnect", dispidReconnect, Reconnect, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Transfer", dispidTransfer, Transfer, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SingleStepTransfer", dispidSingleStepTransfer, SingleStepTransfer, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Conference", dispidConference, Conference, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SetCallData", dispidSetCallData, SetCallData, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetCallData", dispidGetCallData, GetCallData, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "ForceOut", dispidForceOut, ForceOut, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "ForceIdle", dispidForceIdle, ForceIdle, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "ForceBusy", dispidForceBusy, ForceBusy, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Listen", dispidListen, Listen, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "StopListen", dispidStopListen, StopListen, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Insert", dispidInsert, Insert, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "StopInsert", dispidStopInsert, StopInsert, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SwitchInsertorListen", dispidSwitchInsertorListen, SwitchInsertorListen, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "Break", dispidBreak, Break, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SendDTMF", dispidSendDTMF, SendDTMF, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "MuteOn", dispidMuteOn, MuteOn, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "MuteOff", dispidMuteOff, MuteOff, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentDetailByAgentID", dispidGetAgentDetailByAgentID, GetAgentDetailByAgentID, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentDetailByAgentDN", dispidGetAgentDetailByAgentDN, GetAgentDetailByAgentDN, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentDetailsByAgentIDs", dispidGetAgentDetailsByAgentIDs, GetAgentDetailsByAgentIDs, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentDetailsByAgentDNs", dispidGetAgentDetailsByAgentDNs, GetAgentDetailsByAgentDNs, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetRecordFileName", dispidGetRecordFileName, GetRecordFileName, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetRestReason", dispidGetRestReason, GetRestReason, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentNumberBySkill", dispidGetAgentNumberBySkill, GetAgentNumberBySkill, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetAgentDetailsBySkill", dispidGetAgentDetailsBySkill, GetAgentDetailsBySkill, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetSkillWaitingNumber", dispidGetSkillWaitingNumber, GetSkillWaitingNumber, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetSkillWaitingCallInfo", dispidGetSkillWaitingCallInfo, GetSkillWaitingCallInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetPrivateQueue", dispidGetPrivateQueue, GetPrivateQueue, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetSysInfo", dispidGetSysInfo, GetSysInfo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetCallingNo", dispidGetCallingNo, GetCallingNo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetOrgCallingNo", dispidGetOrgCallingNo, GetOrgCallingNo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetCalledNo", dispidGetCalledNo, GetCalledNo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetOrgCalledNo", dispidGetOrgCalledNo, GetOrgCalledNo, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "SynchronizeCTITime", dispidSynchronizeCTITime, SynchronizeCTITime, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "GetPromptByErrorCode", dispidGetPromptByErrorCode, GetPromptByErrorCode, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "JumptheQueue", dispidJumptheQueue, JumptheQueue, VT_I4, VTS_I8)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "TransIVR", dispidTransIVR, TransIVR, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CCCAgentBarCtrl, "TransIVREx", dispidTransIVREx, TransIVREx, VT_I4, VTS_BSTR VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射
BEGIN_EVENT_MAP(CCCAgentBarCtrl, COleControl)
	EVENT_CUSTOM_ID("OnUnLogin",           eventidOnUnLogin,           OnUnLogin,           VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnReady",             eventidOnReady,             OnReady,             VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnBusy",              eventidOnBusy,              OnBusy,              VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnRest",              eventidOnRest,              OnRest,              VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnLock",              eventidOnLock,              OnLock,              VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnAlerting",          eventidOnAlerting,          OnAlerting,          VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnHarfAlerting",      eventidOnHarfAlerting,      OnHarfAlerting,      VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnConnecting",        eventidOnConnecting,        OnConnecting,        VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnConnected",         eventidOnConnected,         OnConnected,         VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnHarfConnected",     eventidOnHarfConnected,     OnHarfConnected,     VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnInternalConnected", eventidOnInternalConnected, OnInternalConnected, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnSuspended",         eventidOnSuspended,         OnSuspended,         VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnConsultConnecting", eventidOnConsultConnecting, OnConsultConnecting, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnConsultConnected",  eventidOnConsultConnected,  OnConsultConnected,  VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnConference",        eventidOnConference,        OnConference,        VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnMonitor",           eventidOnMonitor,           OnMonitor,           VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnInsert",            eventidOnInsert,            OnInsert,            VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnMonitored",         eventidOnMonitored,         OnMonitored,         VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnInserted",          eventidOnInserted,          OnInserted,          VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnBeginRecord",       eventidOnBeginRecord,       OnBeginRecord,       VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnEndRecord",         eventidOnEndRecord,         OnEndRecord,         VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnInprivatequeue",    eventidOnInprivatequeue,    OnInprivatequeue,    VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnOutprivatequeue",   eventidOnOutprivatequeue,   OnOutprivatequeue,   VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnCTIDisconnect",     eventidOnCTIDisconnect,     OnCTIDisconnect,     VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnCTIMasterChanged",  eventidOnCTIMasterChanged,  OnCTIMasterChanged,  VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnOperationFailed",   eventidOnOperationFailed,   OnOperationFailed,   VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	EVENT_CUSTOM_ID("OnBeforeOutCall",     eventidOnBeforeOutCall,     OnBeforeOutCall,     VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
    EVENT_CUSTOM_ID("OnHeartbeat", eventidOnHeartbeat, OnHeartbeat, VTS_I8)
    EVENT_CUSTOM_ID("OnBtnStatus", eventidOnBtnStatus, OnBtnStatus, VTS_I8 VTS_BSTR)
END_EVENT_MAP()

// 属性页
// TODO: 按需要添加更多属性页。请记住增加计数！
BEGIN_PROPPAGEIDS(CCCAgentBarCtrl, 1)
	PROPPAGEID(CCCAgentBarPropPage::guid)
END_PROPPAGEIDS(CCCAgentBarCtrl)

// 初始化类工厂和 guid
IMPLEMENT_OLECREATE_EX(CCCAgentBarCtrl, "CCAGENTBAR.CCAgentBarCtrl.1",
	0x6d4733b4, 0x8e49, 0x495c, 0x9f, 0x2b, 0x27, 0x60, 0x6c, 0xeb, 0x20, 0xe3)

// 键入库 ID 和版本
IMPLEMENT_OLETYPELIB(CCCAgentBarCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID
const IID BASED_CODE IID_DCCAgentBar =
		{ 0x72EA8ED1, 0xD4EE, 0x4FE9, { 0x93, 0x13, 0xBB, 0x72, 0x57, 0xEC, 0x19, 0xB8 } };
const IID BASED_CODE IID_DCCAgentBarEvents =
		{ 0x7AE6BDA7, 0x9F41, 0x4C75, { 0x9F, 0x71, 0xFF, 0x5, 0x5A, 0x16, 0x7D, 0xC2 } };

// 控件类型信息
static const DWORD BASED_CODE _dwCCAgentBarOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCCAgentBarCtrl, IDS_CCAGENTBAR, _dwCCAgentBarOleMisc)

// CCCAgentBarCtrl::CCCAgentBarCtrlFactory::UpdateRegistry -
// 添加或移除 CCCAgentBarCtrl 的系统注册表项
BOOL CCCAgentBarCtrl::CCCAgentBarCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CCAGENTBAR,
			IDB_CCAGENTBAR,
			afxRegInsertable | afxRegApartmentThreading,
			_dwCCAgentBarOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

// CCCAgentBarCtrl::CCCAgentBarCtrl - 构造函数
CCCAgentBarCtrl::CCCAgentBarCtrl()
{
	InitializeIIDs(&IID_DCCAgentBar, &IID_DCCAgentBarEvents);
	// TODO: 在此初始化控件的实例数据。

	this->SetInitialSize(BAR_WIDTH, BAR_HEIGHT);
	this->SetBorderStyle(0);

	p_m_Bar = new CCCBar(this);
	Tool::p_Bar = p_m_Bar;
}

// CCCAgentBarCtrl::~CCCAgentBarCtrl - 析构函数
CCCAgentBarCtrl::~CCCAgentBarCtrl()
{
	// TODO: 在此清理控件的实例数据。
	delete p_m_Bar;
	p_m_Bar = NULL;
}

// CCCAgentBarCtrl::OnDraw - 绘图函数
void CCCAgentBarCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
}

// CCCAgentBarCtrl::DoPropExchange - 持久性支持
void CCCAgentBarCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	if(pPX->GetVersion() == static_cast<DWORD>(MAKELONG(_wVerMinor, _wVerMajor)))
	{
		PX_String(pPX, "AgentID", p_m_Bar->m_strAgentID);
		PX_String(pPX, "PassWord", p_m_Bar->m_strPassWord);
		PX_String(pPX, "DN", p_m_Bar->m_strDN);

		long temp = -1;
		PX_Long(pPX, "StatusChangeType", temp);
		if(temp != -1)
		{
			if(temp < 0 || temp > 1)// 注意！
				temp = 0;
			p_m_Bar->m_intStatusChangeType = temp;
		}

		PX_Bool(pPX, "AutoAnswer", p_m_Bar->m_intAutoAnswer);
		PX_Bool(pPX, "ForceSignIn", p_m_Bar->m_intForceSignIn);
		PX_String(pPX, "ServiceList", p_m_Bar->m_strServiceList);
		PX_String(pPX, "MainCTIIP", p_m_Bar->m_strMainCTIIP);
		PX_String(pPX, "BackCTIIP", p_m_Bar->m_strBackCTIIP);
		PX_Long(pPX, "CTIPort", p_m_Bar->m_intCTIPort);
		PX_Long(pPX, "TimeOut", p_m_Bar->m_intTimeOut);
		//IsInitial和IsSignIn是只读属性，此处不处理
		PX_Bool(pPX, "IsSIPPhone", p_m_Bar->m_intIsSIPPhone);
		PX_String(pPX, "SIPServerIP", p_m_Bar->m_strSIPServerIP);
		PX_Long(pPX, "SIPServerPort", p_m_Bar->m_intSIPServerPort);
		PX_String(pPX, "PhoneNum", p_m_Bar->m_strPhoneNum);
		PX_String(pPX, "PhonePwd", p_m_Bar->m_strPhonePwd);
		PX_String(pPX, "AgentTag", p_m_Bar->m_strAgentTag);
		PX_String(pPX, "CustomerTag", p_m_Bar->m_strCustomerTag);

		temp = -1;
		PX_Long(pPX, "ANIChangeType", temp);
		if(temp != -1)
		{
			if(temp < 0 || temp > 2)// 注意！
				temp = 0;
			p_m_Bar->m_intANIChangeType = static_cast<ANICHANGE>(temp);
		}

		PX_Bool(pPX, "IsShowCallOut", p_m_Bar->m_intIsShowCallOut);
		PX_Bool(pPX, "IsCallOut", p_m_Bar->m_intIsCallOut);

		temp = -1;
		PX_Long(pPX, "LogLevel", temp);
		if(temp != -1)
		{
			if(temp < 0 || temp > 3)// 注意！
				temp = 2;
			p_m_Bar->m_intLogLevel = static_cast<Level>(temp);
		}

		PX_Bool(pPX, "EnableSeniorCall", p_m_Bar->m_intEnableSeniorCall);
	}
}

// CCCAgentBarCtrl::OnResetState - 将控件重置为默认状态
void CCCAgentBarCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}

BOOL CCCAgentBarCtrl::OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip)
{
	// TODO: 在此添加专用代码和/或调用基类

	ASSERT(lpRectPos != NULL);

	// Remember the position rectangle for later
	m_rcPos = *lpRectPos;

	// Calculate complete rectangle including the tracker (if present)
	CRect rectPos = m_rcPos;
	if(m_bUIActive && m_pRectTracker != NULL)
	{
		// Save new clipping rectangle (for DestroyTracker)
		if(lpRectClip != NULL)
			m_pRectTracker->m_rectClip = *lpRectClip;

		// Adjust tracker rectangle to new dimensions
		CRect rectTmp = rectPos;
		rectTmp.OffsetRect(-rectTmp.left, -rectTmp.top);
		m_pRectTracker->m_rect = rectTmp;

		// Adjust the "true" rectangle to include handles/hatching
		UINT nHandleSize = m_pRectTracker->m_nHandleSize - 1;
		rectPos.InflateRect(nHandleSize, nHandleSize);
	}

	// Now clip that rectangle as appropriate
	CRect rectClip;

	// CHANGE - call your own copy of _GetClippingCoordinates
	GetClippingCoordinates(rectPos, lpRectClip, rectClip, &m_ptOffset);

	// Move outer window first. then inner window
	if(!m_bInPlaceSiteWndless)
	{
		CWnd* pWndOuter = GetOuterWindow();

		//BEGIN CHANGE
		if(pWndOuter != NULL)
			::MoveWindow(pWndOuter->m_hWnd, rectPos.left, rectPos.top, rectPos.Width(), rectPos.Height(), TRUE);

		//END CHANGE								
		if(pWndOuter != this)
			MoveWindow(m_ptOffset.x, m_ptOffset.y, rectPos.Width(), rectPos.Height());
	}

	return TRUE;

	//return COleControl::OnSetObjectRects(lpRectPos, lpRectClip);
}

void CCCAgentBarCtrl::GetClippingCoordinates(LPCRECT pPosRect, LPCRECT pClipRect, LPRECT pIntersectRect, LPPOINT pOffsetPoint)
{
	int clipLeft = 0;
	int clipTop = 0;

	if(pClipRect == NULL || IsRectEmpty(pClipRect))
	{
		CopyRect(pIntersectRect, pPosRect);
	}
	else
	{
		IntersectRect(pIntersectRect, pPosRect, pClipRect);
		clipLeft = pClipRect->left;
		clipTop = pClipRect->top;
	}

	pOffsetPoint->x = 0;
	pOffsetPoint->y = 0;
}

// CCCAgentBarCtrl 消息处理程序
int CCCAgentBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	p_m_Bar->Create(IDD_DIALOG_CCBAR, this);

	//p_m_Bar->MoveWindow(0, 0, BAR_WIDTH, BAR_HEIGHT); //根据控件的大小调整界面的大小
	//p_m_Bar->ShowWindow(SW_SHOW);

	return 0;
}

void CCCAgentBarCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	p_m_Bar->MoveWindow(0, 0, BAR_WIDTH, BAR_HEIGHT); //根据控件的大小调整界面的大小
	p_m_Bar->ShowWindow(SW_SHOW);
}

// 属性--------------------------------------------------------------------------------------------------------------
BSTR CCCAgentBarCtrl::GetAgentID(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strAgentID.AllocSysString();
}

void CCCAgentBarCtrl::SetAgentID(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strAgentID = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetPassWord(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strPassWord.AllocSysString();
}

void CCCAgentBarCtrl::SetPassWord(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strPassWord = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetDN(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strDN.AllocSysString();
}

void CCCAgentBarCtrl::SetDN(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strDN = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetStatusChangeType(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intStatusChangeType.get_value();
}

void CCCAgentBarCtrl::SetStatusChangeType(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		if(newVal < 0 || newVal > 1)// 注意！
			newVal = 0;
		p_m_Bar->m_intStatusChangeType = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetAutoAnswer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intAutoAnswer;
}

void CCCAgentBarCtrl::SetAutoAnswer(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intAutoAnswer = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetForceSignIn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intForceSignIn;
}

void CCCAgentBarCtrl::SetForceSignIn(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intForceSignIn = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetServiceList(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strServiceList.AllocSysString();
}

void CCCAgentBarCtrl::SetServiceList(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strServiceList = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetMainCTIIP(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strMainCTIIP.AllocSysString();
}

void CCCAgentBarCtrl::SetMainCTIIP(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strMainCTIIP = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetBackCTIIP(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strBackCTIIP.AllocSysString();
}

void CCCAgentBarCtrl::SetBackCTIIP(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strBackCTIIP = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetCTIPort(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intCTIPort;
}

void CCCAgentBarCtrl::SetCTIPort(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intCTIPort = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetTimeOut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intTimeOut;
}

void CCCAgentBarCtrl::SetTimeOut(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intTimeOut = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetIsInitial(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intIsInitial;
}

void CCCAgentBarCtrl::SetIsInitial(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	// 只读属性，此处不处理
	//p_m_Bar->m_intIsInitial = newVal;

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetIsSignIn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intIsSignIn;
}

void CCCAgentBarCtrl::SetIsSignIn(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	// 只读属性，此处不处理
	//p_m_Bar->m_intIsSignIn = newVal;

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetIsSIPPhone(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intIsSIPPhone;
}

void CCCAgentBarCtrl::SetIsSIPPhone(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsInitial)
	{
		p_m_Bar->m_intIsSIPPhone = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetSIPServerIP(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strSIPServerIP.AllocSysString();
}

void CCCAgentBarCtrl::SetSIPServerIP(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strSIPServerIP = newVal;
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetSIPServerPort(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intSIPServerPort;
}

void CCCAgentBarCtrl::SetSIPServerPort(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intSIPServerPort = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetPhoneNum(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strPhoneNum.AllocSysString();
}

void CCCAgentBarCtrl::SetPhoneNum(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strPhoneNum = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetPhonePwd(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strPhonePwd.AllocSysString();
}

void CCCAgentBarCtrl::SetPhonePwd(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_strPhonePwd = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetAgentTag(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strAgentTag.AllocSysString();
}

void CCCAgentBarCtrl::SetAgentTag(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	p_m_Bar->m_strAgentTag = newVal;

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetCustomerTag(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_strCustomerTag.AllocSysString();
}

void CCCAgentBarCtrl::SetCustomerTag(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	p_m_Bar->m_strCustomerTag = newVal;

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetANIChangeType(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intANIChangeType;
}

void CCCAgentBarCtrl::SetANIChangeType(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(newVal < 0 || newVal > 2)// 注意！
		newVal = 0;
	p_m_Bar->m_intANIChangeType = static_cast<ANICHANGE>(newVal);

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetIsShowCallOut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intIsShowCallOut;
}

void CCCAgentBarCtrl::SetIsShowCallOut(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	p_m_Bar->m_intIsShowCallOut = newVal;

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetIsCallOut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intIsCallOut;
}

void CCCAgentBarCtrl::SetIsCallOut(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	p_m_Bar->m_intIsCallOut = newVal;

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetLogLevel(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intLogLevel;
}

void CCCAgentBarCtrl::SetLogLevel(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsInitial)
	{
		if(newVal < 0 || newVal > 3)// 注意！
			newVal = 2;
		p_m_Bar->m_intLogLevel = static_cast<Level>(newVal);
	}

	SetModifiedFlag();
}

LONG CCCAgentBarCtrl::GetEnableSeniorCall(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return p_m_Bar->m_intEnableSeniorCall;
}

void CCCAgentBarCtrl::SetEnableSeniorCall(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if(!p_m_Bar->m_intIsSignIn)
	{
		p_m_Bar->m_intEnableSeniorCall = newVal;
	}

	SetModifiedFlag();
}

BSTR CCCAgentBarCtrl::GetAnyProperty(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();
}

void CCCAgentBarCtrl::SetAnyProperty(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码

	SetModifiedFlag();
}

// 方法-------------------------------------------------------------------------------------------------------------
LONG CCCAgentBarCtrl::Initial(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(p_m_Bar->m_intIsInitial)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Initial", "IsInitial Error", AGENTBARERROR_BAR_INITIAL);
		return AGENTBARERROR_BAR_INITIAL;
	}

	return p_m_Bar->BInitial();
}

LONG CCCAgentBarCtrl::UnInitial(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsInitial)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "UnInitial", "IsInitial Error", AGENTBARERROR_BAR_UNINITIAL);
		return AGENTBARERROR_BAR_UNINITIAL;
	}

	return p_m_Bar->BUnInitial();
}

LONG CCCAgentBarCtrl::SignIn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsInitial)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SignIn", "IsInitial Error", AGENTBARERROR_BAR_UNINITIAL);
		return AGENTBARERROR_BAR_UNINITIAL;
	}

	return p_m_Bar->BSignIn();
}

LONG CCCAgentBarCtrl::SignOut(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SignOut", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSignOut();
}

LONG CCCAgentBarCtrl::SetIdle(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SetIdle", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSetIdle();
}

LONG CCCAgentBarCtrl::SetBusy(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SetBusy", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSetBusy();
}

LONG CCCAgentBarCtrl::SetRest(LPCTSTR reason)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SetRest", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSetRest(reason);
}

LONG CCCAgentBarCtrl::SetAgentStatus(LONG agentState, LPCTSTR reason)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SetAgentStatus", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	if(agentState < 0 || agentState > 19)// 注意！
		agentState = 0;

	return p_m_Bar->GetAcdClient().AcdSetAgentStatus(p_m_Bar->m_strAgentID, agentState, reason);
}

LONG CCCAgentBarCtrl::GetAgentStatus(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentStatus", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	acd::AgentStatusT status = acd::AgentStatusT::AsUnknownState;
	int ret = p_m_Bar->BGetAgentStatus(status);

	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentStatus", "Return Error", ret);
		return ret;
	}

	return status.get_value();
}

LONG CCCAgentBarCtrl::ResetSkill(LPCTSTR skillList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "ResetSkill", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BResetSkill(skillList);
}

LONG CCCAgentBarCtrl::Reset(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Reset", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BReset();
}

LONG CCCAgentBarCtrl::MakeCall(LPCTSTR dest, LPCTSTR showANI, LPCTSTR showDest, LONG isOffhook, LONG type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "MakeCall", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	if(isOffhook < 0 || isOffhook > 1)// 注意！
		isOffhook = 0;
	if(type < 0 || type > 1)// 注意！
		type = 0;

	CString ani, dnis;
	switch(p_m_Bar->m_intANIChangeType)
	{
	case ANICHANGE_SYSTEM:
		break;
	case ANICHANGE_TRANSFER:
		//ani = dest; 政策问题
		dnis = p_m_Bar->m_strDN;
		break;
	case ANICHANGE_SPECIAL:
		ani = showANI;
		dnis = showDest;
		break;
	default:
		break;
	}

	return p_m_Bar->BMakeCall(dest, ani, dnis, isOffhook, type);
}

LONG CCCAgentBarCtrl::Answer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Answer", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BAnswer();
}

LONG CCCAgentBarCtrl::ReleaseCall(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "ReleaseCall", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BReleaseCall();
}

LONG CCCAgentBarCtrl::Hold(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Hold", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BHold();
}

LONG CCCAgentBarCtrl::Retrieve(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Retrieve", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BRetrieve();
}

LONG CCCAgentBarCtrl::Consult(LPCTSTR consultNum, LPCTSTR showANI, LPCTSTR showDest, LONG consultType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Consult", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	if(consultType < 0 || consultType > 1)// 注意！
		consultType = 0;

	CString ani, dnis;
	switch(p_m_Bar->m_intANIChangeType)
	{
	case ANICHANGE_SYSTEM:
		break;
	case ANICHANGE_TRANSFER:
		//ani = consultNum; 政策问题
		dnis = p_m_Bar->m_strDN;
		break;
	case ANICHANGE_SPECIAL:
		ani = showANI;
		dnis = showDest;
		break;
	default:
		break;
	}

	return p_m_Bar->BConsult(consultNum, ani, dnis, consultType);
}

LONG CCCAgentBarCtrl::Reconnect(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Reconnect", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BReconnect();
}

LONG CCCAgentBarCtrl::Transfer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Transfer", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BTransfer();
}

LONG CCCAgentBarCtrl::SingleStepTransfer(LPCTSTR transferNum, LPCTSTR showANI, LPCTSTR showDest, LONG transferStyle, LONG transferType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SingleStepTransfer", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	if(transferType < 0 || transferType > 2)// 注意！
		transferType = 0;

	// 0：内线
	// 1：外线
	// 2：IVR 只对agentbar有效，acd没有此类型，到acd之后，转换为外线
	if(2 == transferType)
	{
		return p_m_Bar->BTransferIVR(transferNum);
	}

	CString ani, dnis;
	switch(p_m_Bar->m_intANIChangeType)
	{
	case ANICHANGE_SYSTEM:
		break;
	case ANICHANGE_TRANSFER:
		//ani = transferNum; 政策问题
		dnis = p_m_Bar->m_strDN;
		break;
	case ANICHANGE_SPECIAL:
		ani = showANI;
		dnis = showDest;
		break;
	default:
		break;
	}

	return p_m_Bar->BSingleStepTransfer(transferNum, ani, dnis, transferStyle, transferType);
}

LONG CCCAgentBarCtrl::Conference(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Conference", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BConference();
}

LONG CCCAgentBarCtrl::SetCallData(LPCTSTR key, LPCTSTR callData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SetCallData", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdSetAssociateData(p_m_Bar->m_strAgentID, key, callData);
}

BSTR CCCAgentBarCtrl::GetCallData(LPCTSTR key)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetCallData", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	string data;
	int ret = p_m_Bar->GetAcdClient().AcdGetAssociateData(p_m_Bar->m_strAgentID, key, data);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetCallData", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}

	CString strResult(data.c_str());
	return strResult.AllocSysString();
}

LONG CCCAgentBarCtrl::ForceOut(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "ForceOut", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdForceSignOut(p_m_Bar->m_strAgentID, agentID);
}

LONG CCCAgentBarCtrl::ForceIdle(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "ForceIdle", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdForceSetAgentStatus(p_m_Bar->m_strAgentID, agentID, acd::AgentStatusT::AsReadyState);
}

LONG CCCAgentBarCtrl::ForceBusy(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "ForceBusy", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdForceSetAgentStatus(p_m_Bar->m_strAgentID, agentID, acd::AgentStatusT::AsBusyState);
}

LONG CCCAgentBarCtrl::Listen(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Listen", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BListen(agentID, showANI, showDest);
}

LONG CCCAgentBarCtrl::StopListen(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "StopListen", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BStopListen(agentID);
}

LONG CCCAgentBarCtrl::Insert(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Insert", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BInsert(agentID, showANI, showDest);
}

LONG CCCAgentBarCtrl::StopInsert(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "StopInsert", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BStopInsert(agentID);
}

LONG CCCAgentBarCtrl::SwitchInsertorListen(LPCTSTR agentID, LPCTSTR showANI, LPCTSTR showDest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SwitchInsertorListen", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSwitchInsertorListen(agentID, showANI, showDest);
}

LONG CCCAgentBarCtrl::Break(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "Break", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdBreak(p_m_Bar->m_strAgentID, agentID);
}

LONG CCCAgentBarCtrl::SendDTMF(LPCTSTR dtmf)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SendDTMF", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSendDTMF(dtmf);
}

LONG CCCAgentBarCtrl::MuteOn(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "MuteOn", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdMuteOn(p_m_Bar->m_strAgentID);
}

LONG CCCAgentBarCtrl::MuteOff(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "MuteOff", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdMuteOff(p_m_Bar->m_strAgentID);
}

BSTR CCCAgentBarCtrl::GetAgentDetailByAgentID(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailByAgentID", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	acd::AgentInfoT agentInfo;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentDetailByAgentID(p_m_Bar->m_strAgentID, agentID, agentInfo);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailByAgentID", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}

	Json::Value root;
	root["agentId"]         = Json::Value(agentInfo.agentId);
	root["agentDn"]         = Json::Value(agentInfo.agentDn);
	root["loginTime"]       = Json::Value(agentInfo.loginTime);
	root["currStatus"]      = Json::Value(agentInfo.currStatus.get_value());
	root["currStatusTime"]  = Json::Value(agentInfo.currStatusTime);
	root["answerTime"]      = Json::Value(agentInfo.answerTime);
	root["currTime"]        = Json::Value(agentInfo.currTime);
	root["origCaller"]      = Json::Value(agentInfo.origCaller);
	root["origCallee"]      = Json::Value(agentInfo.origCallee);
	root["privQueueNum"]    = Json::Value(agentInfo.privQueueNum);
	root["callTimes"]       = Json::Value(agentInfo.callTimes);
	root["answerTimes"]     = Json::Value(agentInfo.answerTimes);
	root["freeTotalTime"]   = Json::Value(agentInfo.freeTotalTime);
	root["busyTotalTime"]   = Json::Value(agentInfo.busyTotalTime);
	root["resetTotalTime"]  = Json::Value(agentInfo.resetTotalTime);
	root["callTotalTime"]   = Json::Value(agentInfo.callTotalTime);
	root["answerTotalTime"] = Json::Value(agentInfo.answerTotalTime);
	root["agentIP"]         = Json::Value(agentInfo.agentIP);
	Json::FastWriter w;
	string s = w.write(root);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetAgentDetailByAgentDN(LPCTSTR agentDN)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailByAgentDN", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	acd::AgentInfoT agentInfo;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentDetailByAgentDN(p_m_Bar->m_strAgentID, agentDN, agentInfo);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailByAgentDN", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}

	Json::Value root;
	root["agentId"]         = Json::Value(agentInfo.agentId);
	root["agentDn"]         = Json::Value(agentInfo.agentDn);
	root["loginTime"]       = Json::Value(agentInfo.loginTime);
	root["currStatus"]      = Json::Value(agentInfo.currStatus.get_value());
	root["currStatusTime"]  = Json::Value(agentInfo.currStatusTime);
	root["answerTime"]      = Json::Value(agentInfo.answerTime);
	root["currTime"]        = Json::Value(agentInfo.currTime);
	root["origCaller"]      = Json::Value(agentInfo.origCaller);
	root["origCallee"]      = Json::Value(agentInfo.origCallee);
	root["privQueueNum"]    = Json::Value(agentInfo.privQueueNum);
	root["callTimes"]       = Json::Value(agentInfo.callTimes);
	root["answerTimes"]     = Json::Value(agentInfo.answerTimes);
	root["freeTotalTime"]   = Json::Value(agentInfo.freeTotalTime);
	root["busyTotalTime"]   = Json::Value(agentInfo.busyTotalTime);
	root["resetTotalTime"]  = Json::Value(agentInfo.resetTotalTime);
	root["callTotalTime"]   = Json::Value(agentInfo.callTotalTime);
	root["answerTotalTime"] = Json::Value(agentInfo.answerTotalTime);
	root["agentIP"]         = Json::Value(agentInfo.agentIP);
	Json::FastWriter w;
	string s = w.write(root);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetAgentDetailsByAgentIDs(LPCTSTR agentIDs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentIDs", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	Json::Reader reader;
	Json::Value readRoot;
	if(!reader.parse(agentIDs, readRoot))
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentIDs", "json Error", AGENTBARERROR_JSON_READERROR);
		CString strResult;
		return strResult.AllocSysString();
	}
	if(!readRoot.isArray())
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentIDs", "json not array Error", AGENTBARERROR_JSON_READERROR);
		CString strResult;
		return strResult.AllocSysString();
	}
	acd::StringListT agents;
	for(Json::Value::iterator it = readRoot.begin(); it != readRoot.end(); it++)
	{
		Json::Value v = (*it)["AgentID"];
		if(!v)
			continue;
		if(!v.isString())
			continue;
		agents.push_back(v.asCString());
	}
	if(agents.size() == 0)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentIDs", "AgentList size", 0);
		CString strResult;
		return strResult.AllocSysString();
	}
	acd::AgentInfoListT agentInfos;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentDetailsByAgentIDs(p_m_Bar->m_strAgentID, agents, agentInfos);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentIDs", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::AgentInfoListT::iterator it = agentInfos.begin(); it != agentInfos.end(); it++)
	{
		Json::Value temp;
		temp["agentId"]         = Json::Value((*it).agentId);
		temp["agentDn"]         = Json::Value((*it).agentDn);
		temp["loginTime"]       = Json::Value((*it).loginTime);
		temp["currStatus"]      = Json::Value((*it).currStatus.get_value());
		temp["currStatusTime"]  = Json::Value((*it).currStatusTime);
		temp["answerTime"]      = Json::Value((*it).answerTime);
		temp["currTime"]        = Json::Value((*it).currTime);
		temp["origCaller"]      = Json::Value((*it).origCaller);
		temp["origCallee"]      = Json::Value((*it).origCallee);
		temp["privQueueNum"]    = Json::Value((*it).privQueueNum);
		temp["callTimes"]       = Json::Value((*it).callTimes);
		temp["answerTimes"]     = Json::Value((*it).answerTimes);
		temp["freeTotalTime"]   = Json::Value((*it).freeTotalTime);
		temp["busyTotalTime"]   = Json::Value((*it).busyTotalTime);
		temp["resetTotalTime"]  = Json::Value((*it).resetTotalTime);
		temp["callTotalTime"]   = Json::Value((*it).callTotalTime);
		temp["answerTotalTime"] = Json::Value((*it).answerTotalTime);
		temp["agentIP"]         = Json::Value((*it).agentIP);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetAgentDetailsByAgentDNs(LPCTSTR agentDNs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentDNs", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	Json::Reader reader;
	Json::Value readRoot;
	if(!reader.parse(agentDNs, readRoot))
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentDNs", "json Error", AGENTBARERROR_JSON_READERROR);
		CString strResult;
		return strResult.AllocSysString();
	}
	if(!readRoot.isArray())
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentDNs", "json not array Error", AGENTBARERROR_JSON_READERROR);
		CString strResult;
		return strResult.AllocSysString();
	}
	acd::StringListT agents;
	for(Json::Value::iterator it = readRoot.begin(); it != readRoot.end(); it++)
	{
		Json::Value v = (*it)["AgentDN"];
		if(!v)
			continue;
		if(!v.isString())
			continue;
		agents.push_back(v.asCString());
	}
	if(agents.size() == 0)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentDNs", "AgentList size", 0);
		CString strResult;
		return strResult.AllocSysString();
	}
	acd::AgentInfoListT agentInfos;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentDetailsByAgentDNs(p_m_Bar->m_strAgentID, agents, agentInfos);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsByAgentDNs", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::AgentInfoListT::iterator it = agentInfos.begin(); it != agentInfos.end(); it++)
	{
		Json::Value temp;
		temp["agentId"]         = Json::Value((*it).agentId);
		temp["agentDn"]         = Json::Value((*it).agentDn);
		temp["loginTime"]       = Json::Value((*it).loginTime);
		temp["currStatus"]      = Json::Value((*it).currStatus.get_value());
		temp["currStatusTime"]  = Json::Value((*it).currStatusTime);
		temp["answerTime"]      = Json::Value((*it).answerTime);
		temp["currTime"]        = Json::Value((*it).currTime);
		temp["origCaller"]      = Json::Value((*it).origCaller);
		temp["origCallee"]      = Json::Value((*it).origCallee);
		temp["privQueueNum"]    = Json::Value((*it).privQueueNum);
		temp["callTimes"]       = Json::Value((*it).callTimes);
		temp["answerTimes"]     = Json::Value((*it).answerTimes);
		temp["freeTotalTime"]   = Json::Value((*it).freeTotalTime);
		temp["busyTotalTime"]   = Json::Value((*it).busyTotalTime);
		temp["resetTotalTime"]  = Json::Value((*it).resetTotalTime);
		temp["callTotalTime"]   = Json::Value((*it).callTotalTime);
		temp["answerTotalTime"] = Json::Value((*it).answerTotalTime);
		temp["agentIP"]         = Json::Value((*it).agentIP);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetRecordFileName(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetRecordFileName", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	string fileName;
	int ret = p_m_Bar->GetAcdClient().AcdGetRecordFileName(p_m_Bar->m_strAgentID, fileName);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetRecordFileName", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}

	CString strResult(fileName.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetRestReason(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetRestReason", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	acd::StringListT reasons;
	int ret = p_m_Bar->BGetRestReason(reasons);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetRestReason", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::StringListT::iterator it = reasons.begin(); it != reasons.end(); it++)
	{
		Json::Value temp;
		temp["reason"] = Json::Value(*it);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

LONG CCCAgentBarCtrl::GetAgentNumberBySkill(LPCTSTR skill)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentNumberBySkill", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	int agentNumber = 0;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentNumberBySkill(p_m_Bar->m_strAgentID, skill, agentNumber);

	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentNumberBySkill", "Return Error", ret);
		return ret;
	}

	return agentNumber;
}

BSTR CCCAgentBarCtrl::GetAgentDetailsBySkill(LPCTSTR skill)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsBySkill", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	int agentNumber = 0;
	acd::AgentInfoListT agentInfos;
	int ret = p_m_Bar->GetAcdClient().AcdGetAgentDetailsBySkill(p_m_Bar->m_strAgentID, skill, agentNumber, agentInfos);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetAgentDetailsBySkill", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::AgentInfoListT::iterator it = agentInfos.begin(); it != agentInfos.end(); it++)
	{
		Json::Value temp;
		temp["agentId"]         = Json::Value((*it).agentId);
		temp["agentDn"]         = Json::Value((*it).agentDn);
		temp["loginTime"]       = Json::Value((*it).loginTime);
		temp["currStatus"]      = Json::Value((*it).currStatus.get_value());
		temp["currStatusTime"]  = Json::Value((*it).currStatusTime);
		temp["answerTime"]      = Json::Value((*it).answerTime);
		temp["currTime"]        = Json::Value((*it).currTime);
		temp["origCaller"]      = Json::Value((*it).origCaller);
		temp["origCallee"]      = Json::Value((*it).origCallee);
		temp["privQueueNum"]    = Json::Value((*it).privQueueNum);
		temp["callTimes"]       = Json::Value((*it).callTimes);
		temp["answerTimes"]     = Json::Value((*it).answerTimes);
		temp["freeTotalTime"]   = Json::Value((*it).freeTotalTime);
		temp["busyTotalTime"]   = Json::Value((*it).busyTotalTime);
		temp["resetTotalTime"]  = Json::Value((*it).resetTotalTime);
		temp["callTotalTime"]   = Json::Value((*it).callTotalTime);
		temp["answerTotalTime"] = Json::Value((*it).answerTotalTime);
		temp["agentIP"]         = Json::Value((*it).agentIP);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetSkillWaitingNumber(LPCTSTR skill)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSkillWaitingNumber", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	int queueNum = 0;
	int freeNum = 0;
	int ret = p_m_Bar->GetAcdClient().AcdGetSkillWaitingNumber(p_m_Bar->m_strAgentID, skill, queueNum, freeNum);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSkillWaitingNumber", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	writeRoot["queueNum"] = Json::Value(queueNum);
	writeRoot["freeNum"]  = Json::Value(freeNum);
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetSkillWaitingCallInfo(LPCTSTR skill)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSkillWaitingCallInfo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	int queueNum = 0;
	acd::QueueInfoListT queueInfos;
	int ret = p_m_Bar->GetAcdClient().AcdGetSkillWaitingCallInfo(p_m_Bar->m_strAgentID, skill, queueNum, queueInfos);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSkillWaitingCallInfo", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::QueueInfoListT::iterator it = queueInfos.begin(); it != queueInfos.end(); it++)
	{
		Json::Value temp;
		temp["callId"]     = Json::Value((*it).callId);
		temp["contactId"]  = Json::Value((*it).contactId);
		temp["requestId"]  = Json::Value((*it).requestId);
		temp["origCaller"] = Json::Value((*it).origCaller);
		temp["origCallee"] = Json::Value((*it).origCallee);
		temp["startTime"]  = Json::Value((*it).startTime);
		temp["currTime"]   = Json::Value((*it).currTime);
		temp["changeTime"] = Json::Value((*it).changeTime);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetPrivateQueue(LPCTSTR agentID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetPrivateQueue", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	int queueNum = 0;
	acd::QueueInfoListT queueInfos;
	int ret = p_m_Bar->GetAcdClient().AcdGetPrivateQueue(p_m_Bar->m_strAgentID, agentID, queueNum, queueInfos);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetPrivateQueue", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value writeRoot;
	for(acd::QueueInfoListT::iterator it = queueInfos.begin(); it != queueInfos.end(); it++)
	{
		Json::Value temp;
		temp["callId"]     = Json::Value((*it).callId);
		temp["contactId"]  = Json::Value((*it).contactId);
		temp["requestId"]  = Json::Value((*it).requestId);
		temp["origCaller"] = Json::Value((*it).origCaller);
		temp["origCallee"] = Json::Value((*it).origCallee);
		temp["startTime"]  = Json::Value((*it).startTime);
		temp["currTime"]   = Json::Value((*it).currTime);
		temp["changeTime"] = Json::Value((*it).changeTime);
		writeRoot.append(temp);
	}
	Json::FastWriter w;
	string s = w.write(writeRoot);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetSysInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSysInfo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	acd::SysInfoT sysInfo;
	int ret = p_m_Bar->GetAcdClient().AcdGetSysInfo(p_m_Bar->m_strAgentID, sysInfo);
	if(ret != AGENTBARERROR_SUCCESS)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetSysInfo", "Return Error", ret);
		CString strResult;
		return strResult.AllocSysString();
	}
	Json::Value root;
	root["totalAgents"]    = Json::Value(sysInfo.totalAgents);
	root["totalCalls"]     = Json::Value(sysInfo.totalCalls);
	root["ivrCalls"]       = Json::Value(sysInfo.ivrCalls);
	root["agentCalls"]     = Json::Value(sysInfo.agentCalls);
	root["queueCalls"]     = Json::Value(sysInfo.queueCalls);
	root["privQueueCalls"] = Json::Value(sysInfo.privQueueCalls);
	Json::FastWriter w;
	string s = w.write(root);
	CString strResult(s.c_str());
	return strResult.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetCallingNo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetCallingNo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	return p_m_Bar->m_callingNo.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetOrgCallingNo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetOrgCallingNo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	return p_m_Bar->m_orgCallingNo.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetCalledNo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetCalledNo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	return p_m_Bar->m_calledNo.AllocSysString();
}

BSTR CCCAgentBarCtrl::GetOrgCalledNo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetOrgCalledNo", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	return p_m_Bar->m_orgCalledNo.AllocSysString();
}

LONG CCCAgentBarCtrl::SynchronizeCTITime(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "SynchronizeCTITime", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BSynchronizeCTITime();
}

BSTR CCCAgentBarCtrl::GetPromptByErrorCode(LONG errCode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "GetPromptByErrorCode", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		CString strResult;
		return strResult.AllocSysString();
	}

	string errDescript;
	Tool::GetAcdResult_Str(errCode, errDescript);

	CString strResult(errDescript.c_str());
	return strResult.AllocSysString();
}

LONG CCCAgentBarCtrl::JumptheQueue(LONGLONG requestId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "JumptheQueue", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->GetAcdClient().AcdJumptheQueue(p_m_Bar->m_strAgentID, requestId);
}


LONG CCCAgentBarCtrl::TransIVR(LPCTSTR transferNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "TransIVR", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BTransferIVR(transferNum);
}

LONG CCCAgentBarCtrl::TransIVREx(LPCTSTR callerNum, LPCTSTR transferNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	if(!p_m_Bar->m_intIsSignIn)
	{
		Tool::m_Logger.WriteLog("CCCAgentBarCtrl", "TransIVREx", "IsSignIn Error", AGENTBARERROR_BAR_UNSIGNIN);
		return AGENTBARERROR_BAR_UNSIGNIN;
	}

	return p_m_Bar->BTransferIVR(transferNum, callerNum);
}