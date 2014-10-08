#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被改写。

/////////////////////////////////////////////////////////////////////////////
// CCcagentbarctrl 包装类

class CCcagentbarctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCcagentbarctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x6D4733B4, 0x8E49, 0x495C, { 0x9F, 0x2B, 0x27, 0x60, 0x6C, 0xEB, 0x20, 0xE3 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 属性
public:


// 操作
public:

// _DCCAgentBar

// Functions
//

	long Initial()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long UnInitial()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SignIn()
	{
		long result;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SignOut()
	{
		long result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetIdle()
	{
		long result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetBusy()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetRest(LPCTSTR reason)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms, reason);
		return result;
	}
	long SetAgentStatus(long agentState, LPCTSTR reason)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, agentState, reason);
		return result;
	}
	long GetAgentStatus()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ResetSkill(LPCTSTR skillList)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, skillList);
		return result;
	}
	long Reset()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long MakeCall(LPCTSTR dest, LPCTSTR showANI, LPCTSTR showDest, long isOffhook, long type)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dest, showANI, showDest, isOffhook, type);
		return result;
	}
	long Answer()
	{
		long result;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ReleaseCall()
	{
		long result;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Hold()
	{
		long result;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Retrieve()
	{
		long result;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Consult(LPCTSTR consultNum, LPCTSTR showANI, LPCTSTR showDest, long consultType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, consultNum, showANI, showDest, consultType);
		return result;
	}
	long Reconnect()
	{
		long result;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Transfer()
	{
		long result;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SingleStepTransfer(LPCTSTR transferNum, LPCTSTR showANI, LPCTSTR showDest, long transferStyle, long transferType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, transferNum, showANI, showDest, transferStyle, transferType);
		return result;
	}
	long Conference()
	{
		long result;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCallData(LPCTSTR key, LPCTSTR callData)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms, key, callData);
		return result;
	}
	CString GetCallData(LPCTSTR key)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, key);
		return result;
	}
	long ForceOut(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long ForceIdle(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long ForceBusy(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long Listen(LPCTSTR AgentID, LPCTSTR showANI, LPCTSTR showDest)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID, showANI, showDest);
		return result;
	}
	long StopListen(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long Insert(LPCTSTR AgentID, LPCTSTR showANI, LPCTSTR showDest)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID, showANI, showDest);
		return result;
	}
	long StopInsert(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long SwitchInsertorListen(LPCTSTR AgentID, LPCTSTR showANI, LPCTSTR showDest)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID, showANI, showDest);
		return result;
	}
	long Break(LPCTSTR AgentID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AgentID);
		return result;
	}
	long SendDTMF(LPCTSTR dtmf)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dtmf);
		return result;
	}
	long MuteOn()
	{
		long result;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long MuteOff()
	{
		long result;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetAgentDetailByAgentID(LPCTSTR AgentID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, AgentID);
		return result;
	}
	CString GetAgentDetailByAgentDN(LPCTSTR agentDN)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, agentDN);
		return result;
	}
	CString GetAgentDetailsByAgentIDs(LPCTSTR agentIDs)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, agentIDs);
		return result;
	}
	CString GetAgentDetailsByAgentDNs(LPCTSTR agentDNs)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, agentDNs);
		return result;
	}
	CString GetRecordFileName()
	{
		CString result;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetRestReason()
	{
		CString result;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetAgentNumberBySkill(LPCTSTR skill)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, parms, skill);
		return result;
	}
	CString GetAgentDetailsBySkill(LPCTSTR skill)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, skill);
		return result;
	}
	CString GetSkillWaitingNumber(LPCTSTR skill)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, skill);
		return result;
	}
	CString GetSkillWaitingCallInfo(LPCTSTR skill)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, skill);
		return result;
	}
	CString GetPrivateQueue(LPCTSTR AgentID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, AgentID);
		return result;
	}
	CString GetSysInfo()
	{
		CString result;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCallingNo()
	{
		CString result;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetOrgCallingNo()
	{
		CString result;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCalledNo()
	{
		CString result;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetOrgCalledNo()
	{
		CString result;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long SynchronizeCTITime()
	{
		long result;
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetPromptByErrorCode(long errCode)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, errCode);
		return result;
	}
	long JumptheQueue(__int64 requestId)
	{
		long result;
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, parms, requestId);
		return result;
	}
	long TransIVR(LPCTSTR transferNum)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, parms, transferNum);
		return result;
	}
	long TransIVREx(LPCTSTR callerNum, LPCTSTR transferNum)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, parms, callerNum, transferNum);
		return result;
	}

// Properties
//

CString GetAgentID()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}
void SetAgentID(CString propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}
CString GetPassWord()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}
void SetPassWord(CString propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}
CString GetDN()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}
void SetDN(CString propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}
long GetStatusChangeType()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetStatusChangeType(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
long GetAutoAnswer()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}
void SetAutoAnswer(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}
long GetForceSignIn()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}
void SetForceSignIn(long propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}
CString GetServiceList()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}
void SetServiceList(CString propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}
CString GetMainCTIIP()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}
void SetMainCTIIP(CString propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}
CString GetBackCTIIP()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}
void SetBackCTIIP(CString propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}
long GetCTIPort()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetCTIPort(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
long GetTimeOut()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetTimeOut(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
long GetIsInitial()
{
	long result;
	GetProperty(0xc, VT_I4, (void*)&result);
	return result;
}
void SetIsInitial(long propVal)
{
	SetProperty(0xc, VT_I4, propVal);
}
long GetIsSignIn()
{
	long result;
	GetProperty(0xd, VT_I4, (void*)&result);
	return result;
}
void SetIsSignIn(long propVal)
{
	SetProperty(0xd, VT_I4, propVal);
}
long GetIsSIPPhone()
{
	long result;
	GetProperty(0xe, VT_I4, (void*)&result);
	return result;
}
void SetIsSIPPhone(long propVal)
{
	SetProperty(0xe, VT_I4, propVal);
}
CString GetSIPServerIP()
{
	CString result;
	GetProperty(0xf, VT_BSTR, (void*)&result);
	return result;
}
void SetSIPServerIP(CString propVal)
{
	SetProperty(0xf, VT_BSTR, propVal);
}
long GetSIPServerPort()
{
	long result;
	GetProperty(0x10, VT_I4, (void*)&result);
	return result;
}
void SetSIPServerPort(long propVal)
{
	SetProperty(0x10, VT_I4, propVal);
}
CString GetPhoneNum()
{
	CString result;
	GetProperty(0x11, VT_BSTR, (void*)&result);
	return result;
}
void SetPhoneNum(CString propVal)
{
	SetProperty(0x11, VT_BSTR, propVal);
}
CString GetPhonePwd()
{
	CString result;
	GetProperty(0x12, VT_BSTR, (void*)&result);
	return result;
}
void SetPhonePwd(CString propVal)
{
	SetProperty(0x12, VT_BSTR, propVal);
}
CString GetAgentTag()
{
	CString result;
	GetProperty(0x13, VT_BSTR, (void*)&result);
	return result;
}
void SetAgentTag(CString propVal)
{
	SetProperty(0x13, VT_BSTR, propVal);
}
CString GetCustomerTag()
{
	CString result;
	GetProperty(0x14, VT_BSTR, (void*)&result);
	return result;
}
void SetCustomerTag(CString propVal)
{
	SetProperty(0x14, VT_BSTR, propVal);
}
long GetANIChangeType()
{
	long result;
	GetProperty(0x15, VT_I4, (void*)&result);
	return result;
}
void SetANIChangeType(long propVal)
{
	SetProperty(0x15, VT_I4, propVal);
}
long GetIsShowCallOut()
{
	long result;
	GetProperty(0x16, VT_I4, (void*)&result);
	return result;
}
void SetIsShowCallOut(long propVal)
{
	SetProperty(0x16, VT_I4, propVal);
}
long GetIsCallOut()
{
	long result;
	GetProperty(0x17, VT_I4, (void*)&result);
	return result;
}
void SetIsCallOut(long propVal)
{
	SetProperty(0x17, VT_I4, propVal);
}
long GetLogLevel()
{
	long result;
	GetProperty(0x18, VT_I4, (void*)&result);
	return result;
}
void SetLogLevel(long propVal)
{
	SetProperty(0x18, VT_I4, propVal);
}
long GetEnableSeniorCall()
{
	long result;
	GetProperty(0x19, VT_I4, (void*)&result);
	return result;
}
void SetEnableSeniorCall(long propVal)
{
	SetProperty(0x19, VT_I4, propVal);
}
CString GetAnyProperty()
{
	CString result;
	GetProperty(0x1a, VT_BSTR, (void*)&result);
	return result;
}
void SetAnyProperty(CString propVal)
{
	SetProperty(0x1a, VT_BSTR, propVal);
}


};
