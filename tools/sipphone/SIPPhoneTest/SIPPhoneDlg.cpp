// SIPPhoneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SIPPhone.h"
#include "SIPPhoneDlg.h"
#include ".\sipphonedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CSIPPhoneDlg * CSIPPhoneDlg::mySelf=NULL;

void GetModulePath(char *pszPathName)
{
	int nPos = 0;
	char szTmpPath[MAX_PATH] = {0};

	//获取Dll文件全路径名
	GetModuleFileName(NULL, szTmpPath, sizeof(szTmpPath));
	for(int i = strlen(szTmpPath); i > 0; i--)     //去除全路径名中最后的文件名
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
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSIPPhoneDlg 对话框



CSIPPhoneDlg::CSIPPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSIPPhoneDlg::IDD, pParent)
	, m_sipIP(_T(""))
	, m_account(_T(""))
	, m_pass(_T(""))
	, m_sipPort(0)
	, m_timeout(0)
	, m_dest(_T(""))
	, m_codecs(_T(""))
	, m_devNum(0)
	 
	, m_localPort(0)
	, m_selMicDev(_T(""))
	, m_selSpkrDev(_T(""))
	, m_logFile(_T(""))
 
	, m_logLevel(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSIPPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_SIP_IP, m_sipIP);
	DDX_Text(pDX, IDC_EDIT_SIP_ACCOUNT, m_account);
	DDX_Text(pDX, IDC_EDIT_SIP_PASS, m_pass);
	DDX_Text(pDX, IDC_EDIT_SIP_PORT, m_sipPort);
	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_timeout);
	DDX_Text(pDX, IDC_EDIT_DEST, m_dest);
	DDX_Text(pDX, IDC_EDIT_CODECS, m_codecs);

	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_localPort);
	DDX_Control(pDX, IDC_COMBO_MIC, m_micList);
	DDX_Control(pDX, IDC_COMBO_SPKR, m_spkrList);
	DDX_CBString(pDX, IDC_COMBO_MIC, m_selMicDev);
	DDX_CBString(pDX, IDC_COMBO_SPKR, m_selSpkrDev);
	DDX_Control(pDX, IDC_SLIDER_MIC, m_volMic);
	DDX_Control(pDX, IDC_SLIDER_SPKR, m_volSpkr);
	DDX_Text(pDX, IDC_EDIT_LOG_FILE, m_logFile);

	DDX_Text(pDX, IDC_EDIT_LOG_LEVEL, m_logLevel);
}

BEGIN_MESSAGE_MAP(CSIPPhoneDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
 
 
 
	ON_MESSAGE(WM_CALL_STATE_CHANGED,OnCallStateChanged)
	ON_MESSAGE(WM_REG_STATE_CHANGED,OnRegStateChanged)


 
 
	ON_BN_CLICKED(IDC_BUTTON_B1, OnBnClickedButtonB1)
	ON_BN_CLICKED(IDC_BUTTON_B2, OnBnClickedButtonB2)
	ON_BN_CLICKED(IDC_BUTTON_B3, OnBnClickedButtonB3)
	ON_BN_CLICKED(IDC_BUTTON_B4, OnBnClickedButtonB4)
	ON_BN_CLICKED(IDC_BUTTON_B5, OnBnClickedButtonB5)
	ON_BN_CLICKED(IDC_BUTTON_B6, OnBnClickedButtonB6)
	ON_BN_CLICKED(IDC_BUTTON_B7, OnBnClickedButtonB7)
	ON_BN_CLICKED(IDC_BUTTON_B8, OnBnClickedButtonB8)
	ON_BN_CLICKED(IDC_BUTTON_B9, OnBnClickedButtonB9)
	ON_BN_CLICKED(IDC_BUTTON_BS, OnBnClickedButtonBs)
	ON_BN_CLICKED(IDC_BUTTON_B0, OnBnClickedButtonB0)
	ON_BN_CLICKED(IDC_BUTTON_BP, OnBnClickedButtonBp)
 
	ON_BN_CLICKED(IDC_BUTTON_SET_ACCOUNT, OnBnClickedButtonSetAccount)
	ON_BN_CLICKED(IDC_BUTTON_MAKE_CALL_TO, OnBnClickedButtonMakeCallTo)
	ON_BN_CLICKED(IDC_BUTTON_ANSWER, OnBnClickedButtonAnswer)
	ON_BN_CLICKED(IDC_BUTTON_HANGUP, OnBnClickedButtonHangup)
	ON_BN_CLICKED(IDC_BUTTON_SET_CODECS, OnBnClickedButtonSetCodecs)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GET_VER, OnBnClickedButtonGetVer)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnBnClickedButtonInit)
 
	ON_CBN_SELCHANGE(IDC_COMBO_MIC, OnCbnSelchangeComboMic)
	ON_CBN_SELCHANGE(IDC_COMBO_SPKR, OnCbnSelchangeComboSpkr)
	ON_BN_CLICKED(IDC_BUTTON_SET_AUDIO_DEVICES, OnBnClickedButtonSetAudioDevices)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MIC, OnNMCustomdrawSliderMic)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPKR, OnNMCustomdrawSliderSpkr)
	ON_BN_CLICKED(IDC_CHECK_MUTE_MIC, OnBnClickedCheckMuteMic)
 
	ON_BN_CLICKED(IDC_CHECK_MUTE_SPKR, OnBnClickedCheckMuteSpkr)
	ON_BN_CLICKED(IDC_BUTTON_HOLD, OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_UNHOLD, OnBnClickedButtonUnhold)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
END_MESSAGE_MAP()

/*
typedef void (*func_reg_state_callback)(int,PHONELIB_REG_STATE,int,char*);//注册事件回调函数指针
typedef void (*func_call_state_callback)(int,int,char*,char*,PHONELIB_CALL_STATE,int,char*);//呼叫事件回调函数指针

typedef void (*func_media_state_callback)(PHONELIB_MEDIA_STATE,char*);

//typedef void (*func_ media_state_callback)(PHONELIB_MEDIA_STATE ,char* );//媒体事件回调函数指针
typedef void (*func_network_state_callback)(PHONELIB_NETWORK_STATE,char* );//网络事件回调函数指针
*/


void call_state_callback (int account_id, int call_id,const char* srcnum,const char* dstnum ,
PHONELIB_CALL_STATE cstate, int sip_response_code, const char* sip_response_desc)

{


	if(CSIPPhoneDlg::mySelf)
	{
		CallStateMsg* csm=new CallStateMsg;
		csm->account_id=account_id;
		csm->call_id=call_id;
		strcpy(csm->src,srcnum);
		strcpy(csm->dst,dstnum);
		strcpy(csm->response,sip_response_desc);
		csm->state=cstate;
		csm->sipcode=sip_response_code;
		::PostMessage(CSIPPhoneDlg::mySelf->GetSafeHwnd(),WM_CALL_STATE_CHANGED,(WPARAM)csm,0);
	}
 
}

void reg_state_callback (int account_id, PHONELIB_REG_STATE state,int status,const char* statusText )

{


	if(CSIPPhoneDlg::mySelf)
	{
		RegStateMsg* csm=new RegStateMsg;
		csm->account_id=account_id;
		 
		csm->state=state;
		csm->sipcode=status;
		strcpy(csm->response,statusText);
		 
		::PostMessage(CSIPPhoneDlg::mySelf->GetSafeHwnd(),WM_REG_STATE_CHANGED,(WPARAM)csm,0);
	}
 
}

// CSIPPhoneDlg 消息处理程序



BOOL CSIPPhoneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	char path[MAX_PATH];
	GetModulePath(path);
 
	strcat(path,"\\settings.ini");

	char sipip[256];
	char account[256];
	char pass[256];
	char codecs[512];
	char dest[256];
	char logfile[512];


	::GetPrivateProfileString("settings","sipip","10.36.159.60",sipip,256,path);
	::GetPrivateProfileString("settings","account","1105",account,256,path);
	::GetPrivateProfileString("settings","pass","1234",pass,256,path);

	::GetPrivateProfileString("settings","dest","1205",dest,256,path);

	::GetPrivateProfileString("settings","logfile","./phoneliblog.txt",logfile,512,path);
	::GetPrivateProfileString("settings","codecs",
		"iLBC/8000/1 GSM/8000/1 PCMU/8000/1 PCMA/8000/1 speex/8000/1 speex/32000/1 G722/16000/1 L16/44100/1 L16/44100/2 ",
		codecs,512,path);

	m_sipPort=::GetPrivateProfileInt("settings","sipport",8060,path);
	m_localPort=::GetPrivateProfileInt("settings","localport",8888,path);
	m_timeout=::GetPrivateProfileInt("settings","timeout",60,path);
	int	spkrlevel=::GetPrivateProfileInt("settings","spkrlevel",100,path);
	int miclevel=::GetPrivateProfileInt("settings","miclevel",100,path);
	int loglevel=::GetPrivateProfileInt("settings","loglevel",6,path);
	int logappend=::GetPrivateProfileInt("settings","logappend",1,path);
	m_sipIP=sipip;
	m_account=account;
	m_pass=pass;
	m_codecs=codecs;
	m_dest=dest;
	m_muteMic=m_muteSpkr=false;
	m_lastMicLevel=miclevel;
	m_lastSpkrLevel=spkrlevel;
	m_logLevel=loglevel;
	m_logFile=logfile;
 

	mySelf=this;
	m_volMic.SetRange(0,200);
	m_volSpkr.SetRange(0,200);
	m_volMic.SetPos(miclevel);
	m_volSpkr.SetPos(spkrlevel);


	( (CButton*) (this->GetDlgItem(IDC_BUTTON_ANSWER)) )->EnableWindow(0);
	( (CButton*) (this->GetDlgItem(IDC_CHECK_LOG_APPEND)) )->SetCheck(logappend);
	UpdateData(false);


	this->InitializePhoneLib();
	
	if(this->m_sipIP !="" && this->m_account!="")
	{
		phonelib_add_account(m_sipIP,m_sipPort,m_account,m_pass,m_timeout,&m_currentAcct);

	}
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CSIPPhoneDlg::InitializePhoneLib(void)
{
		///////////////////初始化/////////////

	m_currentAcct=-1;
	m_currentCall=-1;

	AddMessage("Initalize...");
	int x=(( (CButton*) (this->GetDlgItem(IDC_CHECK_LOG_APPEND)) )->GetCheck());
	bool append=x==1?true:false;
 

	phonelib_init(m_localPort,(char*)(LPCTSTR)m_logFile,m_logLevel,append);

	phonelib_set_call_state_callback(call_state_callback);
	phonelib_set_reg_state_callback(reg_state_callback);


	unsigned int max=AUDIO_DEVICE_MAX;

	phonelib_get_audio_device_list(m_devList,&max);
	m_devNum=max;
	CString desc;

	int mic=0;
	int spkr=0;


	phonelib_aud_dev_info mic_info,spkr_info;
	memset(&mic_info,0,sizeof(phonelib_aud_dev_info));
	memset(&spkr_info,0,sizeof(phonelib_aud_dev_info));
	phonelib_get_active_audio_device(&mic_info,&spkr_info);


	for(int x=0; x<max; x++)
	{
			
		desc.Format("[detect audio device] name:%s, %s,%s",m_devList[x].name,m_devList[x].input_count>0?"mic":"-",m_devList[x].output_count>0?"spkr":"-");
	 
		if(m_devList[x].input_count>0)
		{
			m_micList.InsertString(mic,m_devList[x].name);
			if(!strcmp(m_devList[x].name,mic_info.name))
			{
				//m_selMicDev=m_devList[x].name;
				m_micList.SetCurSel(mic);
			}
			mic++;
		}
		if(m_devList[x].output_count>0)
		{
			m_spkrList.InsertString(spkr,m_devList[x].name);
			if(!strcmp(m_devList[x].name,spkr_info.name))
			{
				//m_selSpkrDev=m_devList[x].name;
				m_spkrList.SetCurSel(spkr);
			}
			spkr++;
		}

		this->AddMessage(desc);
	}
	


	
	phonelib_set_codecs((char*)(LPCTSTR)m_codecs);
	
	AddMessage("Initalized");
	//UpdateData(true);
	/////////////////初始化结束///////
}

void CSIPPhoneDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSIPPhoneDlg::OnPaint() 
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CSIPPhoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
 

LRESULT CSIPPhoneDlg::OnRegStateChanged(WPARAM wParam,LPARAM lParam)
{

	RegStateMsg *csm=(RegStateMsg *)wParam;
	//	this->multiParametersCallback(param);
	 
	CString msg;
	CString state;
	switch(csm->state)
	{
	case PHONELIB_REG_STATE_REGISTERING:
		state="Registering";
		break;
	case PHONELIB_REG_STATE_REGISTERED:
		state="Registered";
		break;
	case PHONELIB_REG_STATE_REJECTED:
		state="Rejected";
		break;
	case PHONELIB_REG_STATE_NOTFOUND:
		state="Not Found";
		break;
	case PHONELIB_REG_STATE_SERVERERROR:
		state="Server Error";
		break;
 
	default:
		state="Unknown";
		break;

	}
	msg.Format("%d: %s [%d/%s]",csm->account_id,state,csm->sipcode,csm->response);
	AddMessage(msg);
	delete csm;//////sukerry: must delete this buffer!!!
	return 1;
}

LRESULT CSIPPhoneDlg::OnCallStateChanged(WPARAM wParam,LPARAM lParam)
{

	CallStateMsg *csm=(CallStateMsg *)wParam;
	//	this->multiParametersCallback(param);
	 
	CString msg;
	CString state;
 
	if(m_currentCall!=-1 && csm->call_id!=m_currentCall)// we are in single call mode, just ignore second call and drop another incoming call
	{
		//nodisplay=true;
		if(csm->state==PHONELIB_CALL_STATE_INCOMING)
		{
 
		 
			msg.Format("%d,%d: %s--%s",csm->account_id,csm->call_id,"Denied Incoming",csm->dst);
			AddMessage(msg);
			phonelib_drop_call(csm->call_id);
	  
		}
		delete csm; //must delete
		return 1;
	}

	switch(csm->state)
	{
	case PHONELIB_CALL_STATE_CALLING:
		state="Calling";
		break;
	case PHONELIB_CALL_STATE_PROGRESSING:
		state="Ringing with Tone";
		break;
	case PHONELIB_CALL_STATE_RINGING:
		state="Ringing";
		break;
	case PHONELIB_CALL_STATE_TERMINATED:
		state="Terminated";
		m_currentCall=-1;
		( (CButton*) (this->GetDlgItem(IDC_BUTTON_ANSWER)) )->EnableWindow(0);
		break;
	case PHONELIB_CALL_STATE_CONNECTED:
		state="Connected";
		break;
	case PHONELIB_CALL_STATE_INCOMING:

		state="Incoming";
		m_currentCall=csm->call_id;
		( (CButton*) (this->GetDlgItem(IDC_BUTTON_ANSWER)) )->EnableWindow(1);

		break;

	}
 
	msg.Format("%d,%d: %s--%s  [%d/%s]",csm->account_id,csm->call_id,state, csm->dst,csm->sipcode,csm->response);
	AddMessage(msg);
 
	delete csm;//////sukerry: must delete this buffer!!!
	return 1;
}

void CSIPPhoneDlg::AddMessage(CString message)
{
	CString s=message;

	s.Replace("\r\n","\n");
	s.Replace("\r","\n");

	int start=0;

	while(start>=0)
	{

		CString ss=s.Tokenize("\n",start);
		if(start>=0)
		
		int i=m_list.InsertString(m_list.GetCount(),ss);

		m_list.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);

	}


}


void CSIPPhoneDlg::OnBnClickedButtonB1()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'1');
}

void CSIPPhoneDlg::OnBnClickedButtonB2()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'2');
}

void CSIPPhoneDlg::OnBnClickedButtonB3()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'3');
}

void CSIPPhoneDlg::OnBnClickedButtonB4()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'4');
}

void CSIPPhoneDlg::OnBnClickedButtonB5()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'5');
}

void CSIPPhoneDlg::OnBnClickedButtonB6()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'6');
}

void CSIPPhoneDlg::OnBnClickedButtonB7()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'7');
}

void CSIPPhoneDlg::OnBnClickedButtonB8()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'8');
}

void CSIPPhoneDlg::OnBnClickedButtonB9()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'9');
}

void CSIPPhoneDlg::OnBnClickedButtonBs()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'*');
}

void CSIPPhoneDlg::OnBnClickedButtonB0()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'0');
}

void CSIPPhoneDlg::OnBnClickedButtonBp()
{
	// TODO: 在此添加控件通知处理程序代码
	phonelib_send_dtmf(m_currentCall,'#');
	/*
	unsigned mic,spkr;
	phonelib_get_last_rx_tx_level(&mic,&spkr);
	CString tmp;
	tmp.Format("mic: %d, spkr: %d",mic,spkr);
	AddMessage(tmp);
	*/
}


void CSIPPhoneDlg::OnBnClickedButtonSetAccount()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	
	if(m_currentAcct!=-1)
		phonelib_remove_account(m_currentAcct);

	 phonelib_add_account(m_sipIP,m_sipPort,m_account,m_pass,m_timeout,&m_currentAcct);

}

void CSIPPhoneDlg::OnBnClickedButtonMakeCallTo()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	if(m_currentCall>=0)
		return;//do not make call if there is already a call ongoing, since we are in single call mode 
	if(m_currentAcct>0)
	{


		int call_id;

		//phonelib_make_call_to(m_currentAcct,"sip:1199900011861095555@199.119.200.176:9677",&call_id,"");
		CString strDestURI;
		strDestURI.Format("sip:%s@%s:%d",m_dest,m_sipIP,m_sipPort);

		phonelib_make_call_to(m_currentAcct,(char*)(LPCTSTR)strDestURI,&call_id,"");

		m_currentCall=call_id;
	}
}

void CSIPPhoneDlg::OnBnClickedButtonAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
 

	if(m_currentCall>=0)
	{
		phonelib_answer_call(m_currentCall);
		( (CButton*) (this->GetDlgItem(IDC_BUTTON_ANSWER)) )->EnableWindow(0);
	}

 
}

void CSIPPhoneDlg::OnBnClickedButtonHangup()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_currentCall>=0)
	{
		phonelib_drop_call(m_currentCall);
		 
	}
 
 
}
/*
speex/8000/1 
speex/32000/1 
iLBC/8000/1 
GSM/8000/1 
PCMU/8000/1 
PCMA/8000/1 
G722/16000/1 
L16/44100/1 
L16/44100/2 
*/
 
void CSIPPhoneDlg::OnBnClickedButtonSetCodecs()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	if(!phonelib_set_codecs((char*)(LPCTSTR)m_codecs))
		AddMessage("Set codecs ok!");
	else
		AddMessage("Set codecs failed!");
}

void CSIPPhoneDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	AddMessage("UnRegister SIP Account...");
//	if(m_currentAcct>=0)
//		phonelib_remove_account(m_currentAcct);
	AddMessage("phonelib destroy...");
	phonelib_destroy();
	AddMessage("phonelib destroyed...");


	char path[MAX_PATH];
	GetModulePath(path);
	 
	strcat(path,"\\settings.ini");
	

	UpdateData(true); 

 
	char tmp[256];
	
	::WritePrivateProfileString("settings","sipip",(LPCTSTR)m_sipIP,path);

	::WritePrivateProfileString("settings","sipport",_itoa(m_sipPort,tmp,10),path);
	::WritePrivateProfileString("settings","account",(LPCTSTR)m_account,path);
	::WritePrivateProfileString("settings","pass",(LPCTSTR)m_pass,path);
	::WritePrivateProfileString("settings","dest",(LPCTSTR)m_dest,path);
	::WritePrivateProfileString("settings","timeout",_itoa(m_timeout,tmp,10),path);
	::WritePrivateProfileString("settings","localport",_itoa(m_localPort,tmp,10),path);
	::WritePrivateProfileString("settings","codecs",(LPCTSTR)m_codecs,path);
	::WritePrivateProfileString("settings","miclevel",_itoa(this->m_volMic.GetPos(),tmp,10),path);
	::WritePrivateProfileString("settings","spkrlevel",_itoa(this->m_volSpkr.GetPos(),tmp,10),path);
	::WritePrivateProfileString("settings","logfile",(LPCTSTR)m_logFile,path);
 
	::WritePrivateProfileString("settings","loglevel",_itoa(this->m_logLevel,tmp,10),path);
	int x=(( (CButton*) (this->GetDlgItem(IDC_CHECK_LOG_APPEND)) )->GetCheck());
	::WritePrivateProfileString("settings","logappend",_itoa(x,tmp,10),path);
	CDialog::OnClose();
}

void CSIPPhoneDlg::OnBnClickedButtonGetVer()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(phonelib_get_version_string(),IDOK,0);

	AddMessage(phonelib_get_version_string());
}

void CSIPPhoneDlg::OnBnClickedButtonInit()
{
	// TODO: 在此添加控件通知处理程序代码
	this->InitializePhoneLib();

}

 

void CSIPPhoneDlg::OnCbnSelchangeComboMic()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	UpdateData(true);
	CString str;
	str.Format("select Mic dev: %s",m_selMicDev);
	AddMessage(str);
	*/
}

void CSIPPhoneDlg::OnCbnSelchangeComboSpkr()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	UpdateData(true);
	CString str;
	str.Format("select Spkr dev: %s",m_selSpkrDev);
	AddMessage(str);
	*/
}

void CSIPPhoneDlg::OnBnClickedButtonSetAudioDevices()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	int micInd=-1;
	int spkrInd=-1;

	for(int i=0; i<m_devNum; i++)
	{

		if(!strcmp(m_devList[i].name,(char*)(LPCTSTR)m_selMicDev))
			micInd=i;

		if(!strcmp(m_devList[i].name,(char*)(LPCTSTR)m_selSpkrDev))
			spkrInd=i;

	}

	if(micInd>=0)
	{
		CString tmp;
		tmp.Format("select Mic device: %s, driver: %s",m_devList[micInd].name,m_devList[micInd].driver);
		AddMessage(tmp);
	}
	else
	{
		AddMessage("Mic device not valid!");
	}
	if(spkrInd>=0)
	{

		CString tmp;
		tmp.Format("select Spkr device: %s, driver: %s",m_devList[spkrInd].name,m_devList[spkrInd].driver);
		AddMessage(tmp);
	}
	else
	{
		AddMessage("Spkr device not valid!");
	}

	if(micInd>=0 && spkrInd>=0)
	{
		int ret=phonelib_set_audio_device((char*)(LPCTSTR)m_devList[micInd].driver,(char*)(LPCTSTR)m_devList[micInd].name,
		(char*)(LPCTSTR)m_devList[spkrInd].driver,(char*)(LPCTSTR)m_devList[spkrInd].name);

		if(!ret)
			AddMessage("Set audio device successfully!");
		else
			AddMessage("Set audio device failed!");


	}


}

void CSIPPhoneDlg::OnNMCustomdrawSliderMic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	// TODO: 在此添加控件通知处理程序代码
	
	int x=m_volMic.GetPos();
	this->m_lastMicLevel=x;
	float level=(float)x/100;
	CString strV;
	strV.Format("vMic:%4.2f",level);
//	AddMessage(strV);
	if(!this->m_muteMic)
		phonelib_adjust_rx_level(level);
	
 
	*pResult = 0;
}

void CSIPPhoneDlg::OnNMCustomdrawSliderSpkr(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	
	int x=m_volSpkr.GetPos();
	this->m_lastSpkrLevel=x;
	float level=(float)x/100;
	CString strV;
	strV.Format("vSpkr:%4.2f",level);
//	AddMessage(strV);
	if(!this->m_muteSpkr)
		phonelib_adjust_tx_level(level);
	
	
	*pResult = 0;
}


void CSIPPhoneDlg::OnBnClickedCheckMuteMic()
{
	// TODO: 在此添加控件通知处理程序代码
	int x=(( (CButton*) (this->GetDlgItem(IDC_CHECK_MUTE_MIC)) )->GetCheck());
	if(x==1)
	{
		 phonelib_mute_mic();
		 this->m_muteMic=true;
	}
	else
	{
		phonelib_adjust_rx_level((float)this->m_lastMicLevel/100);
		this->m_muteMic=false;
	}
}

 

void CSIPPhoneDlg::OnBnClickedCheckMuteSpkr()
{
	// TODO: 在此添加控件通知处理程序代码
	int x=(( (CButton*) (this->GetDlgItem(IDC_CHECK_MUTE_SPKR)) )->GetCheck());
	if(x==1)
	{
		 phonelib_mute_spkr();
		 this->m_muteSpkr=true;
	}
	else
	{
		phonelib_adjust_tx_level((float)this->m_lastSpkrLevel/100);
		this->m_muteSpkr=false;
	}
}

void CSIPPhoneDlg::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_currentCall>=0)
		phonelib_hold_call(m_currentCall);
}

void CSIPPhoneDlg::OnBnClickedButtonUnhold()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_currentCall>=0)	
		phonelib_unhold_call(m_currentCall);
}

void CSIPPhoneDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_list.ResetContent();
}
