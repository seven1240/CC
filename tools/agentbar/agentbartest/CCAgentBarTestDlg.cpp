// CCAgentBarTestDlg.cpp : 实现文件

#include "stdafx.h"
#include "CCAgentBarTest.h"
#include "CCAgentBarTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCCAgentBarTestDlg 对话框
CCCAgentBarTestDlg::CCCAgentBarTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCAgentBarTestDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCAgentBarTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CCAGENTBARCTRL, m_ocxAgentBar);
	DDX_Control(pDX, IDC_EDIT_MAINCTI, m_edtCTIMainIP);
	DDX_Control(pDX, IDC_EDIT_BACKCTI, m_edtCTIBackIP);
	DDX_Control(pDX, IDC_EDIT_CTIPORT, m_edtCTIPort);
	DDX_Control(pDX, IDC_EDIT_AGENTID, m_edtAgentID);
	DDX_Control(pDX, IDC_EDIT_AGENTPWD, m_edtAgentPWD);
	DDX_Control(pDX, IDC_EDIT_AGENTDN, m_edtAgentDN);
	DDX_Control(pDX, IDC_EDIT_AGENTSKILL, m_edtSkill);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT, m_edtTimeout);
	DDX_Control(pDX, IDC_EDIT_ATAG, m_edtATag);
	DDX_Control(pDX, IDC_EDIT_CTAG, m_edtCTag);
	DDX_Control(pDX, IDC_COMBO_SCTYPE, m_cbbSCType);
	DDX_Control(pDX, IDC_COMBO_ACTYPE, m_cbbACType);
	DDX_Control(pDX, IDC_COMBO_LOGLEVEL, m_cbbLogLevel);
	DDX_Control(pDX, IDC_CHECK_AUTOANSWER, m_btnAutoAns);
	DDX_Control(pDX, IDC_CHECK_FORCEIN, m_btnForceIn);
	DDX_Control(pDX, IDC_CHECK_ISINITAIL, m_btnIsInital);
	DDX_Control(pDX, IDC_CHECK_ISIN, m_btnIsIn);
	DDX_Control(pDX, IDC_CHECK_SHOWCALLOUT, m_btnShowOut);
	DDX_Control(pDX, IDC_CHECK_CANCALLOUT, m_btnCanOut);
	DDX_Control(pDX, IDC_CHECK_SENIORCALL, m_btnSeniorCall);
	DDX_Control(pDX, IDC_EDIT_SIP, m_edtSIPIP);
	DDX_Control(pDX, IDC_EDIT_SIPPORT, m_edtSIPPort);
	DDX_Control(pDX, IDC_EDIT_SIPDN, m_edtSIPNo);
	DDX_Control(pDX, IDC_EDIT_SIPPWD, m_edtSIPPWD);
	DDX_Control(pDX, IDC_CHECK_ISSIP, m_btnIsSIP);
	DDX_Control(pDX, IDC_BUTTON_INITIAL, m_btnInitail);
	DDX_Control(pDX, IDC_BUTTON_UNINITIAL, m_btnUninitial);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_edtNo);
	DDX_Control(pDX, IDC_EDIT_SHOWANI, m_edtShowANI);
	DDX_Control(pDX, IDC_EDIT_SHOWDNIS, m_edtShowDNIS);
	DDX_Control(pDX, IDC_COMBO_AGENTTYPE, m_cbbPhoneType);
	DDX_Control(pDX, IDC_COMBO_CALLTYPE, m_cbbCallType);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_edtInput);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_edtOutput);
	DDX_Control(pDX, IDC_BUTTON_IN, m_btnSignIn);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_btnSignOut);
	DDX_Control(pDX, IDC_BUTTON_ANS, m_btnAnswer);
	DDX_Control(pDX, IDC_BUTTON_CALLOUT, m_btnCallout);
	DDX_Control(pDX, IDC_BUTTON_DTMF, m_btnSendDTMF);
	DDX_Control(pDX, IDC_BUTTON_HUNGUP, m_btnHangup);
	DDX_Control(pDX, IDC_BUTTON_HOLD, m_btnHold);
	DDX_Control(pDX, IDC_BUTTON_RETRIVE, m_btnRetrive);
	DDX_Control(pDX, IDC_BUTTON_CONSULT, m_btnConsult);
	DDX_Control(pDX, IDC_BUTTON_RECONNECT, m_btnReconnect);
	DDX_Control(pDX, IDC_BUTTON_CTRANS, m_btnTransfer);
	DDX_Control(pDX, IDC_BUTTON_CONF, m_btnConf);
	DDX_Control(pDX, IDC_BUTTON_TRANS, m_btnSSTrans);
	DDX_Control(pDX, IDC_BUTTON_REST, m_btnRest);
	DDX_Control(pDX, IDC_BUTTON_READY, m_btnReady);
	DDX_Control(pDX, IDC_BUTTON_BUSY, m_btnBusy);
	DDX_Control(pDX, IDC_COMBO_OPERATION, m_cbbOper);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_BtnRun);
	DDX_Control(pDX, IDC_BUTTON_TRANSIVR, m_btn_TransIVR);
}

BEGIN_MESSAGE_MAP(CCCAgentBarTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_INITIAL, OnBnClickedButtonInitial)
	ON_BN_CLICKED(IDC_BUTTON_UNINITIAL, OnBnClickedButtonUninitial)
	ON_BN_CLICKED(IDC_BUTTON_IN, OnBnClickedButtonIn)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_ANS, OnBnClickedButtonAns)
	ON_BN_CLICKED(IDC_BUTTON_CALLOUT, OnBnClickedButtonCallout)
	ON_BN_CLICKED(IDC_BUTTON_DTMF, OnBnClickedButtonDtmf)
	ON_BN_CLICKED(IDC_BUTTON_HUNGUP, OnBnClickedButtonHungup)
	ON_BN_CLICKED(IDC_BUTTON_HOLD, OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_RETRIVE, OnBnClickedButtonRetrive)
	ON_BN_CLICKED(IDC_BUTTON_CONSULT, OnBnClickedButtonConsult)
	ON_BN_CLICKED(IDC_BUTTON_RECONNECT, OnBnClickedButtonReconnect)
	ON_BN_CLICKED(IDC_BUTTON_CTRANS, OnBnClickedButtonCTrans)
	ON_BN_CLICKED(IDC_BUTTON_CONF, OnBnClickedButtonConf)
	ON_BN_CLICKED(IDC_BUTTON_TRANS, OnBnClickedButtonTrans)
	ON_BN_CLICKED(IDC_BUTTON_REST, OnBnClickedButtonRest)
	ON_BN_CLICKED(IDC_BUTTON_READY, OnBnClickedButtonReady)
	ON_BN_CLICKED(IDC_BUTTON_BUSY, OnBnClickedButtonBusy)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_TRANSIVR, OnBnClickedButtonTransivr)
END_MESSAGE_MAP()


// CCCAgentBarTestDlg 消息处理程序
BOOL CCCAgentBarTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	// 执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_edtCTIMainIP.SetWindowText(m_ocxAgentBar.GetMainCTIIP());
	m_edtCTIBackIP.SetWindowText(m_ocxAgentBar.GetBackCTIIP());
	CString port;
	port.Format("%d", m_ocxAgentBar.GetCTIPort());
	m_edtCTIPort.SetWindowText(port);
	m_edtAgentID.SetWindowText(m_ocxAgentBar.GetAgentID());
	m_edtAgentPWD.SetWindowText(m_ocxAgentBar.GetPassWord());
	m_edtAgentDN.SetWindowText(m_ocxAgentBar.GetDN());
	m_edtSkill.SetWindowText(m_ocxAgentBar.GetServiceList());
	port.Format("%d", m_ocxAgentBar.GetTimeOut());
	m_edtTimeout.SetWindowText(port);
	m_edtATag.SetWindowText(m_ocxAgentBar.GetAgentTag());
	m_edtCTag.SetWindowText(m_ocxAgentBar.GetCustomerTag());
	m_cbbSCType.SetCurSel(m_ocxAgentBar.GetStatusChangeType());
	m_cbbACType.SetCurSel(m_ocxAgentBar.GetANIChangeType());
	m_cbbLogLevel.SetCurSel(m_ocxAgentBar.GetLogLevel());
	m_btnAutoAns.SetCheck(m_ocxAgentBar.GetAutoAnswer());
	m_btnForceIn.SetCheck(m_ocxAgentBar.GetForceSignIn());
	m_btnIsInital.SetCheck(m_ocxAgentBar.GetIsInitial());
	m_btnIsIn.SetCheck(m_ocxAgentBar.GetIsSignIn());
	m_btnShowOut.SetCheck(m_ocxAgentBar.GetIsShowCallOut());
	m_btnCanOut.SetCheck(m_ocxAgentBar.GetIsCallOut());
	m_btnSeniorCall.SetCheck(m_ocxAgentBar.GetEnableSeniorCall());
	m_edtSIPIP.SetWindowText(m_ocxAgentBar.GetSIPServerIP());
	port.Format("%d", m_ocxAgentBar.GetSIPServerPort());
	m_edtSIPPort.SetWindowText(port);
	m_edtSIPNo.SetWindowText(m_ocxAgentBar.GetPhoneNum());
	m_edtSIPPWD.SetWindowText(m_ocxAgentBar.GetPhonePwd());
	m_btnIsSIP.SetCheck(m_ocxAgentBar.GetIsSIPPhone());

	m_cbbOper.AddString("SetAgentStatus");
	m_cbbOper.AddString("GetAgentStatus");
	m_cbbOper.AddString("ResetSkill");
	m_cbbOper.AddString("Reset");
	m_cbbOper.AddString("SetCallData");
	m_cbbOper.AddString("GetCallData");
	m_cbbOper.AddString("ForceOut");
	m_cbbOper.AddString("ForceIdle");
	m_cbbOper.AddString("ForceBusy");
	m_cbbOper.AddString("Listen");
	m_cbbOper.AddString("StopListen");
	m_cbbOper.AddString("Insert");
	m_cbbOper.AddString("StopInsert");
	m_cbbOper.AddString("SwitchInsertorListen");
	m_cbbOper.AddString("Break");
	m_cbbOper.AddString("SendDTMF");
	m_cbbOper.AddString("MuteOn");
	m_cbbOper.AddString("MuteOff");
	m_cbbOper.AddString("GetAgentDetailByAgentID");
	m_cbbOper.AddString("GetAgentDetailByAgentDN");
	m_cbbOper.AddString("GetAgentDetailsByAgentIDs");
	m_cbbOper.AddString("GetAgentDetailsByAgentDNs");
	m_cbbOper.AddString("GetRecordFileName");
	m_cbbOper.AddString("GetRestReason");
	m_cbbOper.AddString("GetAgentNumberBySkill");
	m_cbbOper.AddString("GetAgentDetailsBySkill");
	m_cbbOper.AddString("GetSkillWaitingNumber");
	m_cbbOper.AddString("GetSkillWaitingCallInfo");
	m_cbbOper.AddString("GetPrivateQueue");
	m_cbbOper.AddString("GetSysInfo");
	m_cbbOper.AddString("GetCallingNo");
	m_cbbOper.AddString("GetOrgCallingNo");
	m_cbbOper.AddString("GetCalledNo");
	m_cbbOper.AddString("GetOrgCalledNo");
	m_cbbOper.AddString("SynchronizeCTITime");
	m_cbbOper.AddString("GetPromptByErrorCode");
	m_cbbOper.AddString("JumptheQueue");

	m_cbbPhoneType.SetCurSel(0);
	m_cbbCallType.SetCurSel(1);
	m_cbbOper.SetCurSel(0);

	ResetControl();
	m_btnInitail.EnableWindow(TRUE);
	m_cbbOper.EnableWindow(FALSE);
	m_BtnRun.EnableWindow(FALSE);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

BOOL CCCAgentBarTestDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
// 来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
// 这将由框架自动完成。
void CCCAgentBarTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CCCAgentBarTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCCAgentBarTestDlg::ResetControl()
{
	m_btnInitail.EnableWindow(FALSE);
	m_btnUninitial.EnableWindow(FALSE);
	m_btnSignIn.EnableWindow(FALSE);
	m_btnSignOut.EnableWindow(FALSE);
	m_btnAnswer.EnableWindow(FALSE);
	m_btnCallout.EnableWindow(FALSE);
	m_btnSendDTMF.EnableWindow(FALSE);
	m_btnHangup.EnableWindow(FALSE);
	m_btnHold.EnableWindow(FALSE);
	m_btnRetrive.EnableWindow(FALSE);
	m_btnConsult.EnableWindow(FALSE);
	m_btnReconnect.EnableWindow(FALSE);
	m_btnTransfer.EnableWindow(FALSE);
	m_btnConf.EnableWindow(FALSE);
	m_btnSSTrans.EnableWindow(FALSE);
	m_btnRest.EnableWindow(FALSE);
	m_btnReady.EnableWindow(FALSE);
	m_btnBusy.EnableWindow(FALSE);
	m_btn_TransIVR.EnableWindow(FALSE);
}

void CCCAgentBarTestDlg::ShowMessage(CString str)
{
    int length = static_cast<int>(m_edtOutput.SendMessage(WM_GETTEXTLENGTH));
    m_edtOutput.SetSel(length, length);
	m_edtOutput.ReplaceSel(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonInitial()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edtCTIMainIP.GetWindowText(str);
	m_ocxAgentBar.SetMainCTIIP(str);
	m_edtCTIBackIP.GetWindowText(str);
	m_ocxAgentBar.SetBackCTIIP(str);
	m_edtCTIPort.GetWindowText(str);
	m_ocxAgentBar.SetCTIPort(atoi(str));
	m_edtAgentID.GetWindowText(str);
	m_ocxAgentBar.SetAgentID(str);
	m_edtAgentPWD.GetWindowText(str);
	m_ocxAgentBar.SetPassWord(str);
	m_edtAgentDN.GetWindowText(str);
	m_ocxAgentBar.SetDN(str);
	m_edtSkill.GetWindowText(str);
	m_ocxAgentBar.SetServiceList(str);
	m_edtTimeout.GetWindowText(str);
	m_ocxAgentBar.SetTimeOut(atoi(str));
	m_edtATag.GetWindowText(str);
	m_ocxAgentBar.SetAgentTag(str);
	m_edtCTag.GetWindowText(str);
	m_ocxAgentBar.SetCustomerTag(str);
	m_ocxAgentBar.SetStatusChangeType(m_cbbSCType.GetCurSel());
	m_ocxAgentBar.SetANIChangeType(m_cbbACType.GetCurSel());
	m_ocxAgentBar.SetLogLevel(m_cbbLogLevel.GetCurSel());
	m_ocxAgentBar.SetAutoAnswer(m_btnAutoAns.GetCheck());
	m_ocxAgentBar.SetForceSignIn(m_btnForceIn.GetCheck());
	m_ocxAgentBar.SetIsInitial(m_btnIsInital.GetCheck());
	m_ocxAgentBar.SetIsSignIn(m_btnIsIn.GetCheck());
	m_ocxAgentBar.SetIsShowCallOut(m_btnShowOut.GetCheck());
	m_ocxAgentBar.SetIsCallOut(m_btnCanOut.GetCheck());
	m_ocxAgentBar.SetEnableSeniorCall(m_btnSeniorCall.GetCheck());
	m_edtSIPIP.GetWindowText(str);
	m_ocxAgentBar.SetSIPServerIP(str);
	m_edtSIPPort.GetWindowText(str);
	m_ocxAgentBar.SetSIPServerPort(atoi(str));
	m_edtSIPNo.GetWindowText(str);
	m_ocxAgentBar.SetPhoneNum(str);
	m_edtSIPPWD.GetWindowText(str);
	m_ocxAgentBar.SetPhonePwd(str);
	m_ocxAgentBar.SetIsSIPPhone(m_btnIsSIP.GetCheck());

	int ret = m_ocxAgentBar.Initial();
	if(0 == ret)
	{
		ResetControl();
		m_btnUninitial.EnableWindow(TRUE);
		m_btnSignIn.EnableWindow(TRUE);
	}
	str.Format("Initial retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonUninitial()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.UnInitial();
	if(0 == ret)
	{
		ResetControl();
		m_btnInitail.EnableWindow(TRUE);
	}
	CString str;
	str.Format("UnInitial retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonIn()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.SignIn();
	CString str;
	str.Format("SignIn retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonOut()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.SignOut();
	CString str;
	str.Format("SignOut retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonAns()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Answer();
	CString str;
	str.Format("Answer retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonCallout()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strNo, strShowANI, strShowDNIS;
	m_edtNo.GetWindowText(strNo);
	m_edtShowANI.GetWindowText(strShowANI);
	m_edtShowDNIS.GetWindowText(strShowDNIS);
	int ret = m_ocxAgentBar.MakeCall(strNo, strShowANI, strShowDNIS, m_cbbPhoneType.GetCurSel(), m_cbbCallType.GetCurSel());
	CString str;
	str.Format("MakeCall retrun: %d\r\n", ret);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonDtmf()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edtInput.GetWindowText(str);
	int ret = m_ocxAgentBar.SendDTMF(str);
	str.Format("SendDTMF retrun: %d\r\n", ret);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonHungup()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.ReleaseCall();
	CString str;
	str.Format("ReleaseCall retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Hold();
	CString str;
	str.Format("Hold retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonRetrive()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Retrieve();
	CString str;
	str.Format("Retrieve retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonConsult()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strNo, strShowANI, strShowDNIS;
	m_edtNo.GetWindowText(strNo);
	m_edtShowANI.GetWindowText(strShowANI);
	m_edtShowDNIS.GetWindowText(strShowDNIS);
	int ret = m_ocxAgentBar.Consult(strNo, strShowANI, strShowDNIS, m_cbbCallType.GetCurSel());
	CString str;
	str.Format("Consult retrun: %d\r\n", ret);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonReconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Reconnect();
	CString str;
	str.Format("Reconnect retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonCTrans()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Transfer();
	CString str;
	str.Format("Transfer retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonConf()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.Conference();
	CString str;
	str.Format("Conference retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonTrans()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strNo, strShowANI, strShowDNIS;
	m_edtNo.GetWindowText(strNo);
	m_edtShowANI.GetWindowText(strShowANI);
	m_edtShowDNIS.GetWindowText(strShowDNIS);
	int ret = m_ocxAgentBar.SingleStepTransfer(strNo, strShowANI, strShowDNIS, m_cbbPhoneType.GetCurSel(), m_cbbCallType.GetCurSel());
	CString str;
	str.Format("SingleStepTransfer retrun: %d\r\n", ret);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonRest()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edtInput.GetWindowText(str);
	int ret = m_ocxAgentBar.SetRest(str);
	str.Format("SetRest retrun: %d\r\n", ret);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonReady()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.SetIdle();
	CString str;
	str.Format("SetIdle retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonBusy()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = m_ocxAgentBar.SetBusy();
	CString str;
	str.Format("SetBusy retrun: %d\r\n", ret);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_cbbOper.GetCurSel())
	{
	case 0:// SetAgentStatus
		{
			CString status, strout;
			m_edtInput.GetWindowText(status);
			int ret = m_ocxAgentBar.SetAgentStatus(atoi(status), "隆科多");
			strout.Format("SetAgentStatus retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	case 1:// GetAgentStatus
		{
			CString str;
			int ret = m_ocxAgentBar.GetAgentStatus();
			str.Format("GetAgentStatus retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 2:// ResetSkill
		{
			CString str;
			m_edtInput.GetWindowText(str);
			int ret = m_ocxAgentBar.ResetSkill(str);
			str.Format("ResetSkill retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 3:// Reset
		{
			CString str;
			int ret = m_ocxAgentBar.Reset();
			str.Format("Reset retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 4:// SetCallData
		{
			CString key, data, strout;
			m_edtNo.GetWindowText(key);
			m_edtInput.GetWindowText(data);
			int ret = m_ocxAgentBar.SetCallData(key, data);
			strout.Format("SetCallData retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	case 5:// GetCallData
		{
			CString strin, strout;
			m_edtNo.GetWindowText(strin);
			strin = m_ocxAgentBar.GetCallData(strin);
			strout.Format("GetCallData retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 6:// ForceOut
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.ForceOut(str);
			str.Format("ForceOut retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 7:// ForceIdle
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.ForceIdle(str);
			str.Format("ForceIdle retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 8:// ForceBusy
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.ForceBusy(str);
			str.Format("ForceBusy retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 9:// Listen
		{
			CString agentid, showani, showdnis, strout;
			m_edtNo.GetWindowText(agentid);
			m_edtShowANI.GetWindowText(showani);
			m_edtShowDNIS.GetWindowText(showdnis);
			int ret = m_ocxAgentBar.Listen(agentid, showani, showdnis);
			strout.Format("Listen retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	case 10:// StopListen
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.StopListen(str);
			str.Format("StopListen retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 11:// Insert
		{
			CString agentid, showani, showdnis, strout;
			m_edtNo.GetWindowText(agentid);
			m_edtShowANI.GetWindowText(showani);
			m_edtShowDNIS.GetWindowText(showdnis);
			int ret = m_ocxAgentBar.Insert(agentid, showani, showdnis);
			strout.Format("Insert retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	case 12:// StopInsert
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.StopInsert(str);
			str.Format("StopInsert retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 13:// SwitchInsertorListen
		{
			CString agentid, showani, showdnis, strout;
			m_edtNo.GetWindowText(agentid);
			m_edtShowANI.GetWindowText(showani);
			m_edtShowDNIS.GetWindowText(showdnis);
			int ret = m_ocxAgentBar.SwitchInsertorListen(agentid, showani, showdnis);
			strout.Format("SwitchInsertorListen retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	case 14:// Break
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.Break(str);
			str.Format("Break retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 15:// SendDTMF
		{
			CString str;
			m_edtNo.GetWindowText(str);
			int ret = m_ocxAgentBar.SendDTMF(str);
			str.Format("SendDTMF retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 16:// MuteOn
		{
			CString str;
			int ret = m_ocxAgentBar.MuteOn();
			str.Format("MuteOn retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 17:// MuteOff
		{
			CString str;
			int ret = m_ocxAgentBar.MuteOff();
			str.Format("MuteOff retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 18:// GetAgentDetailByAgentID
		{
			CString strin, strout;
			m_edtNo.GetWindowText(strin);
			strin = m_ocxAgentBar.GetAgentDetailByAgentID(strin);
			strout.Format("GetAgentDetailByAgentID retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 19:// GetAgentDetailByAgentDN
		{
			CString strin, strout;
			m_edtNo.GetWindowText(strin);
			strin = m_ocxAgentBar.GetAgentDetailByAgentDN(strin);
			strout.Format("GetAgentDetailByAgentDN retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 20:// GetAgentDetailsByAgentIDs
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetAgentDetailsByAgentIDs(strin);
			strout.Format("GetAgentDetailsByAgentIDs retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 21:// GetAgentDetailsByAgentDNs
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetAgentDetailsByAgentDNs(strin);
			strout.Format("GetAgentDetailsByAgentDNs retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 22:// GetRecordFileName
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetRecordFileName();
			strout.Format("GetRecordFileName retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 23:// GetRestReason
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetRestReason();
			strout.Format("GetRestReason retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 24:// GetAgentNumberBySkill
		{
			CString str;
			m_edtInput.GetWindowText(str);
			int ret = m_ocxAgentBar.GetAgentNumberBySkill(str);
			str.Format("GetAgentNumberBySkill retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 25:// GetAgentDetailsBySkill
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetAgentDetailsBySkill(strin);
			strout.Format("GetAgentDetailsBySkill retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 26:// GetSkillWaitingNumber
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetSkillWaitingNumber(strin);
			strout.Format("GetSkillWaitingNumber retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 27:// GetSkillWaitingCallInfo
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetSkillWaitingCallInfo(strin);
			strout.Format("GetSkillWaitingCallInfo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 28:// GetPrivateQueue
		{
			CString strin, strout;
			m_edtNo.GetWindowText(strin);
			strin = m_ocxAgentBar.GetPrivateQueue(strin);
			strout.Format("GetPrivateQueue retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 29:// GetSysInfo
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetSysInfo();
			strout.Format("GetSysInfo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 30:// GetCallingNo
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetCallingNo();
			strout.Format("GetCallingNo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 31:// GetOrgCallingNo
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetOrgCallingNo();
			strout.Format("GetOrgCallingNo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 32:// GetCalledNo
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetCalledNo();
			strout.Format("GetCalledNo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 33:// GetOrgCalledNo
		{
			CString strin, strout;
			strin = m_ocxAgentBar.GetOrgCalledNo();
			strout.Format("GetOrgCalledNo retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 34:// SynchronizeCTITime
		{
			CString str;
			int ret = m_ocxAgentBar.SynchronizeCTITime();
			str.Format("SynchronizeCTITime retrun: %d\r\n", ret);
			ShowMessage(str);
			break;
		}
	case 35:// GetPromptByErrorCode
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			strin = m_ocxAgentBar.GetPromptByErrorCode(atoi(strin));
			strout.Format("GetPromptByErrorCode retrun: %s\r\n", strin);
			ShowMessage(strout);
			break;
		}
	case 36:// JumptheQueue
		{
			CString strin, strout;
			m_edtInput.GetWindowText(strin);
			int ret = m_ocxAgentBar.JumptheQueue(_atoi64(strin));
			strout.Format("JumptheQueue retrun: %d\r\n", ret);
			ShowMessage(strout);
			break;
		}
	default:
		break;
	}
}

void CCCAgentBarTestDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
//	m_edtInput.SetWindowText("");
	m_edtOutput.SetWindowText("");
}

void CCCAgentBarTestDlg::OnBnClickedButtonTransivr()
{
	CString strNo;
	m_edtNo.GetWindowText(strNo);

	CString strShowToDest;
	m_edtShowDNIS.GetWindowText( strShowToDest );

	int ret = 0;
	CString str;

	if(strShowToDest.IsEmpty()){
		ret=m_ocxAgentBar.TransIVR(strNo);
		str.Format("TransIVR(%s) retrun: %d\r\n", strNo, ret);
	}
	else{
		ret=m_ocxAgentBar.TransIVREx( strShowToDest, strNo );
		str.Format("TransIVREx(%s, %s) retrun: %d\r\n", strShowToDest, strNo, ret);
	}
	
	ShowMessage(str);
}

BEGIN_EVENTSINK_MAP(CCCAgentBarTestDlg, CDialog)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 1, OnUnLoginCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 2, OnReadyCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 3, OnBusyCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 4, OnRestCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 5, OnLockCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 6, OnAlertingCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 7, OnHarfAlertingCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 8, OnConnectingCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 9, OnConnectedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 10, OnHarfConnectedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 11, OnInternalConnectedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 12, OnSuspendedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 13, OnConsultConnectingCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 14, OnConsultConnectedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 15, OnConferenceCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 16, OnMonitorCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 17, OnInsertCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 18, OnMonitoredCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 19, OnInsertedCcagentbarctrl, VTS_I4 VTS_BSTR VTS_I8 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 20, OnBeginRecordCcagentbarctrl, VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 21, OnEndRecordCcagentbarctrl, VTS_BSTR VTS_I8 VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 22, OnInprivatequeueCcagentbarctrl, VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 23, OnOutprivatequeueCcagentbarctrl, VTS_BSTR VTS_I8 VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 24, OnCTIDisconnectCcagentbarctrl, VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 25, OnCTIMasterChangedCcagentbarctrl, VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 26, OnOperationFailedCcagentbarctrl, VTS_BSTR VTS_I8 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
	ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 27, OnBeforeOutCallCcagentbarctrl, VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I8)
    ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 28, OnHeartbeatCcagentbarctrl, VTS_I8)
    ON_EVENT(CCCAgentBarTestDlg, IDC_CCAGENTBARCTRL, 29, OnBtnStatusCcagentbarctrl, VTS_I8 VTS_BSTR)
END_EVENTSINK_MAP()

void CCCAgentBarTestDlg::OnUnLoginCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												 LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnUninitial.EnableWindow(TRUE);
	m_btnSignIn.EnableWindow(TRUE);
	m_cbbOper.EnableWindow(FALSE);
	m_BtnRun.EnableWindow(FALSE);
	switch(reason)
	{
	case 7:// CerUnloginInitial
		{
			CString str = "initial\r\n";
			ShowMessage(str);
			break;
		}
	case 8:// CerUnloginLogout
		{
			CString str = "logout\r\n";
			ShowMessage(str);
			break;
		}
	case 9:// CerUnloginSelfForceout
		{
			CString str = "self forceout\r\n";
			ShowMessage(str);
			break;
		}
	case 10:// CerUnloginOtherForceout
		{
			CString str = "other forceout\r\n";
			ShowMessage(str);
			break;
		}
	case 11:// CerUnloginBackup
		{
			CString str = "backup out\r\n";
			ShowMessage(str);
			break;
		}
	case 12:// CerUnloginResignin
		{
			CString str = "resign out\r\n";
			ShowMessage(str);
			break;
		}
	case 13:// CerUnloginElse
		{
			CString str = "else out\r\n";
			ShowMessage(str);
			break;
		}
	default:
		{
			CString str = "overflow!\r\n";
			ShowMessage(str);
			break;
		}
	}
	CString str;
	str.Format("[OnUnLogin]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnReadyCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
											   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnSignOut.EnableWindow(TRUE);
	m_btnRest.EnableWindow(TRUE);
	m_btnBusy.EnableWindow(TRUE);
	switch(reason)
	{
	case 14:// CerIdleSelfLogin
		{
			m_cbbOper.EnableWindow(TRUE);
			m_BtnRun.EnableWindow(TRUE);
			CString str = "self login\r\n";
			ShowMessage(str);
			break;
		}
	case 15:// CerIdleOtherLogin
		{
			m_cbbOper.EnableWindow(TRUE);
			m_BtnRun.EnableWindow(TRUE);
			CString str = "other login\r\n";
			ShowMessage(str);
			break;
		}
	case 16:// CerIdleNormalSelfHangup
		{
			CString str = "normal self end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 17:// CerIdleNormalOtherHangup
		{
			CString str = "normal other end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 18:// CerIdleErrorSelfHangup
		{
			CString str = "error self end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 19:// CerIdleErrorOtherHangup
		{
			CString str = "error other end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 20:// CerIdleUnlock
		{
			CString str = "unlock idle\r\n";
			ShowMessage(str);
			break;
		}
	case 21:// CerIdleIdle
		{
			CString str = "idle idle\r\n";
			ShowMessage(str);
			break;
		}
	case 22:// CerIdleSelfSet
		{
			CString str = "self set idle\r\n";
			ShowMessage(str);
			break;
		}
	case 23:// CerIdleOtherSet
		{
			CString str = "other set idle\r\n";
			ShowMessage(str);
			break;
		}
	case 24:// CerIdleElse
		{
			CString str = "else idle\r\n";
			ShowMessage(str);
			break;
		}
	default:
		{
			CString str = "overflow!\r\n";
			ShowMessage(str);
			break;
		}
	}
	CString str;
	str.Format("[OnReady]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBusyCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnSignOut.EnableWindow(TRUE);
	m_btnCallout.EnableWindow(TRUE);
	m_btnRest.EnableWindow(TRUE);
	m_btnReady.EnableWindow(TRUE);
	switch(reason)
	{
	case 14:// CerIdleSelfLogin
		{
			m_cbbOper.EnableWindow(TRUE);
			m_BtnRun.EnableWindow(TRUE);
			CString str = "self login\r\n";
			ShowMessage(str);
			break;
		}
	case 15:// CerIdleOtherLogin
		{
			m_cbbOper.EnableWindow(TRUE);
			m_BtnRun.EnableWindow(TRUE);
			CString str = "other login\r\n";
			ShowMessage(str);
			break;
		}
	case 16:// CerIdleNormalSelfHangup
		{
			CString str = "normal self end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 17:// CerIdleNormalOtherHangup
		{
			CString str = "normal other end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 18:// CerIdleErrorSelfHangup
		{
			CString str = "error self end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 19:// CerIdleErrorOtherHangup
		{
			CString str = "error other end talk\r\n";
			ShowMessage(str);
			break;
		}
	case 20:// CerIdleUnlock
		{
			CString str = "unlock idle\r\n";
			ShowMessage(str);
			break;
		}
	case 21:// CerIdleIdle
		{
			CString str = "idle idle\r\n";
			ShowMessage(str);
			break;
		}
	case 22:// CerIdleSelfSet
		{
			CString str = "self set idle\r\n";
			ShowMessage(str);
			break;
		}
	case 23:// CerIdleOtherSet
		{
			CString str = "other set idle\r\n";
			ShowMessage(str);
			break;
		}
	case 24:// CerIdleElse
		{
			CString str = "else idle\r\n";
			ShowMessage(str);
			break;
		}
	default:
		{
			CString str = "overflow!\r\n";
			ShowMessage(str);
			break;
		}
	}
	CString str;
	str.Format("[OnBusy]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnRestCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnReady.EnableWindow(TRUE);
	m_btnBusy.EnableWindow(TRUE);
	CString str;
	str.Format("[OnRest]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnLockCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	CString str;
	str.Format("[OnLock]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnAlertingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												  LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	if(m_ocxAgentBar.GetIsSIPPhone())
	{
		m_btnAnswer.EnableWindow(TRUE);
	}
	CString str;
	str.Format("[OnAlerting]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnHarfAlertingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
													  LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	if(m_ocxAgentBar.GetIsSIPPhone())
	{
		m_btnAnswer.EnableWindow(TRUE);
	}
	CString str;
	str.Format("[OnHarfAlerting]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnConnectingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
													LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnConnecting]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnSendDTMF.EnableWindow(TRUE);
	m_btnHangup.EnableWindow(TRUE);
	m_btnHold.EnableWindow(TRUE);
	m_btnConsult.EnableWindow(m_ocxAgentBar.GetEnableSeniorCall());
	m_btnSSTrans.EnableWindow(m_ocxAgentBar.GetEnableSeniorCall());
	m_btn_TransIVR.EnableWindow(m_ocxAgentBar.GetEnableSeniorCall() );
	switch(reason)
	{
	case 25:// CerTalkSelfCreat
		{
			CString str = "self begin talk\r\n";
			ShowMessage(str);
			break;
		}
	case 26:// CerTalkOtherCreat
		{
			CString str = "other begin talk\r\n";
			ShowMessage(str);
			break;
		}
	case 27:// CerTalkSelfRetrieve
		{
			CString str = "self retrive talk\r\n";
			ShowMessage(str);
			break;
		}
	case 28:// CerTalkOtherRetrieve
		{
			CString str = "other retrive talk\r\n";
			ShowMessage(str);
			break;
		}
	case 29:// CerTalkElse
		{
			CString str = "else talk\r\n";
			ShowMessage(str);
			break;
		}
	default:
		{
			CString str = "overflow!\r\n";
			ShowMessage(str);
			break;
		}
	}
	CString str;
	str.Format("[OnConnected]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnHarfConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
													   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	CString str;
	str.Format("[OnHarfConnected]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnInternalConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
														   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	switch(reason)
	{
	case 25:// CerTalkSelfCreat
		{
			CString str = "self begin talk\r\n";
			ShowMessage(str);
			break;
		}
	case 26:// CerTalkOtherCreat
		{
			CString str = "other begin talk\r\n";
			ShowMessage(str);
			break;
		}
	case 27:// CerTalkSelfRetrieve
		{
			CString str = "self retrive talk\r\n";
			ShowMessage(str);
			break;
		}
	case 28:// CerTalkOtherRetrieve
		{
			CString str = "other retrive talk\r\n";
			ShowMessage(str);
			break;
		}
	case 29:// CerTalkElse
		{
			CString str = "else talk\r\n";
			ShowMessage(str);
			break;
		}
	default:
		{
			CString str = "overflow!\r\n";
			ShowMessage(str);
			break;
		}
	}
	CString str;
	str.Format("[OnInternalConnected]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnSuspendedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnRetrive.EnableWindow(TRUE);
	CString str;
	str.Format("[OnSuspended]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnConsultConnectingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
														   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnReconnect.EnableWindow(TRUE);
	CString str;
	str.Format("[OnConsultConnecting]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnConsultConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
														  LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnReconnect.EnableWindow(TRUE);
	m_btnTransfer.EnableWindow(TRUE);
	m_btnConf.EnableWindow(TRUE);
	CString str;
	str.Format("[OnConsultConnected]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnConferenceCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
													LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnConference]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnMonitorCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												 LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnMonitor]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnInsertCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnInsert]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnMonitoredCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												   LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnMonitored]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnInsertedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
												  LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	ResetControl();
	m_btnHangup.EnableWindow(TRUE);
	CString str;
	str.Format("[OnInserted]-eventID:%d callID:%s contactID:%I64d partyNum:%d otherParty:%s otherPartyAttribute:%d originatingParty:%s originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		eventID, callID, contactID, partyNum, otherParty, otherPartyAttribute, originatingParty, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBeginRecordCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnBeginRecord]-callID:%s contactID:%I64d filename:%s reason:%d timestamp:%I64d\r\n", callID, contactID, filename, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnEndRecordCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnEndRecord]-callID:%s contactID:%I64d filename:%s reason:%d timestamp:%I64d\r\n", callID, contactID, filename, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnInprivatequeueCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("%I64d", requestID);
	m_edtInput.SetWindowText(str);
	str.Format("[OnInprivatequeue]-callID:%s contactID:%I64d requestID:%I64d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		callID, contactID, requestID, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnOutprivatequeueCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnOutprivatequeue]-callID:%s contactID:%I64d requestID:%I64d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		callID, contactID, requestID, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnCTIDisconnectCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnCTIDisconnect]-callID:%s contactID:%I64d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		callID, contactID, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnCTIMasterChangedCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnCTIMasterChanged]-callID:%s contactID:%I64d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		callID, contactID, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnOperationFailedCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnOperationFailed]-callID:%s contactID:%I64d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		callID, contactID, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBeforeOutCallCcagentbarctrl(LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp)
{
	// TODO: 在此处添加消息处理程序代码
	CString str;
	str.Format("[OnBeforeOutCall]-otherParty:%s otherPartyAttribute:%d originalANI:%s originalDNIS:%s reason:%d timestamp:%I64d\r\n", 
		otherParty, otherPartyAttribute, originalANI, originalDNIS, reason, timestamp);
	ShowMessage(str);
}

void CCCAgentBarTestDlg::OnHeartbeatCcagentbarctrl(LONGLONG timestamp)
{
    // TODO: 在此处添加消息处理程序代码
    CString str;
    str.Format("[OnHeartbeat]-timestamp:%I64d\r\n", 
        timestamp);
    ShowMessage(str);
}

void CCCAgentBarTestDlg::OnBtnStatusCcagentbarctrl(LONGLONG btnStatus, LPCTSTR info)
{
    // TODO: 在此处添加消息处理程序代码
    CString str;
    str.Format("[OnBtnStatus]-btnStatus:%I64d info:%s\r\n", 
        btnStatus, info);
    ShowMessage(str);
}