// SIPPhoneDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSIPPhoneDlg 对话框
#define AUDIO_DEVICE_MAX 10
#define WM_CALL_STATE_CHANGED (WM_USER+9996)
#define WM_REG_STATE_CHANGED (WM_USER+9995)
typedef struct CallStateMsg
{

		int account_id;
		int call_id;
		char src[256];
		char dst[256];
		PHONELIB_CALL_STATE state;
		int sipcode;
		char response[256];
} CallStateMsg;

typedef struct RegStateMsg
{

		int account_id;
	 
		PHONELIB_REG_STATE state;
		int sipcode;
		char response[256];
} RegStateMsg;
class CSIPPhoneDlg : public CDialog
{
// 构造
public:
	CSIPPhoneDlg(CWnd* pParent = NULL);	// 标准构造函数

	static CSIPPhoneDlg* mySelf;

// 对话框数据
	enum { IDD = IDD_SIPPHONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	int m_currentAcct;
	int m_currentCall;
 
	phonelib_aud_dev_info m_devList[AUDIO_DEVICE_MAX];
	int m_devNum;
	
 


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
 

	afx_msg LRESULT OnCallStateChanged(WPARAM wParam,LPARAM lParam);
	
	afx_msg LRESULT OnRegStateChanged(WPARAM wParam,LPARAM lParam);
	CListBox m_list;
	
	void AddMessage(CString message);
 
	afx_msg void OnBnClickedButtonB1();
	afx_msg void OnBnClickedButtonB2();
	afx_msg void OnBnClickedButtonB3();
	afx_msg void OnBnClickedButtonB4();
	afx_msg void OnBnClickedButtonB5();
	afx_msg void OnBnClickedButtonB6();
	afx_msg void OnBnClickedButtonB7();
	afx_msg void OnBnClickedButtonB8();
	afx_msg void OnBnClickedButtonB9();
	afx_msg void OnBnClickedButtonBs();
	afx_msg void OnBnClickedButtonB0();
	afx_msg void OnBnClickedButtonBp();
 ;
	afx_msg void OnBnClickedButtonSetAccount();
	afx_msg void OnBnClickedButtonMakeCallTo();
	afx_msg void OnBnClickedButtonAnswer();
	afx_msg void OnBnClickedButtonHangup();
	afx_msg void OnBnClickedButtonSetCodecs();
	bool m_muteMic;
	bool m_muteSpkr;
	int m_lastMicLevel;
	int m_lastSpkrLevel;
	CString m_sipIP;
 
	CString m_account;
	CString m_pass;
	int m_sipPort;
	int m_timeout;
	CString m_dest;
	CString m_codecs;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonGetVer();
	 
	int m_localPort;
	afx_msg void OnBnClickedButtonInit();
 
	CComboBox m_micList;
	CComboBox m_spkrList;
	afx_msg void OnCbnSelchangeComboMic();
	afx_msg void OnCbnSelchangeComboSpkr();
	CString m_selMicDev;
	CString m_selSpkrDev;
	afx_msg void OnBnClickedButtonSetAudioDevices();
	afx_msg void OnNMCustomdrawSliderMic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderSpkr(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_volMic;
	CSliderCtrl m_volSpkr;
	void InitializePhoneLib(void);
	afx_msg void OnBnClickedCheckMuteMic();
	afx_msg void OnBnClickedCheck2MuteSpkr();
	afx_msg void OnBnClickedCheckMuteSpkr();
	afx_msg void OnBnClickedButtonHold();
	afx_msg void OnBnClickedButtonUnhold();
	CString m_logFile;
 
	int m_logLevel;
	afx_msg void OnBnClickedButtonClear();
};
