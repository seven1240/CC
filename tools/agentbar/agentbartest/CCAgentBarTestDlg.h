// CCAgentBarTestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ccagentbarctrl.h"
#include "afxcmn.h"

// CCCAgentBarTestDlg 对话框
class CCCAgentBarTestDlg : public CDialog
{
// 构造
public:
	CCCAgentBarTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CCAGENTBARTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CCcagentbarctrl m_ocxAgentBar;
	CEdit m_edtCTIMainIP;
	CEdit m_edtCTIBackIP;
	CEdit m_edtCTIPort;
	CEdit m_edtAgentID;
	CEdit m_edtAgentPWD;
	CEdit m_edtAgentDN;
	CEdit m_edtSkill;
	CEdit m_edtTimeout;
	CEdit m_edtATag;
	CEdit m_edtCTag;
	CComboBox m_cbbSCType;
	CComboBox m_cbbACType;
	CComboBox m_cbbLogLevel;
	CButton m_btnAutoAns;
	CButton m_btnForceIn;
	CButton m_btnIsInital;
	CButton m_btnIsIn;
	CButton m_btnShowOut;
	CButton m_btnCanOut;
	CButton m_btnSeniorCall;
	CEdit m_edtSIPIP;
	CEdit m_edtSIPPort;
	CEdit m_edtSIPNo;
	CEdit m_edtSIPPWD;
	CButton m_btnIsSIP;
	CButton m_btnInitail;
	CButton m_btnUninitial;
	CEdit m_edtNo;
	CEdit m_edtShowANI;
	CEdit m_edtShowDNIS;
	CComboBox m_cbbPhoneType;
	CComboBox m_cbbCallType;
	CEdit m_edtInput;
	CEdit m_edtOutput;
	CButton m_btnSignIn;
	CButton m_btnSignOut;
	CButton m_btnAnswer;
	CButton m_btnCallout;
	CButton m_btnSendDTMF;
	CButton m_btnHangup;
	CButton m_btnHold;
	CButton m_btnRetrive;
	CButton m_btnConsult;
	CButton m_btnReconnect;
	CButton m_btnTransfer;
	CButton m_btnConf;
	CButton m_btnSSTrans;
	CButton m_btnRest;
	CButton m_btnReady;
	CButton m_btnBusy;
	CComboBox m_cbbOper;
	CButton m_BtnRun;
	CButton m_btn_TransIVR;

private:
	void ResetControl();
	void ShowMessage(CString str);
	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedButtonUninitial();
	afx_msg void OnBnClickedButtonIn();
	afx_msg void OnBnClickedButtonOut();
	afx_msg void OnBnClickedButtonAns();
	afx_msg void OnBnClickedButtonCallout();
	afx_msg void OnBnClickedButtonDtmf();
	afx_msg void OnBnClickedButtonHungup();
	afx_msg void OnBnClickedButtonHold();
	afx_msg void OnBnClickedButtonRetrive();
	afx_msg void OnBnClickedButtonConsult();
	afx_msg void OnBnClickedButtonReconnect();
	afx_msg void OnBnClickedButtonCTrans();
	afx_msg void OnBnClickedButtonConf();
	afx_msg void OnBnClickedButtonTrans();
	afx_msg void OnBnClickedButtonRest();
	afx_msg void OnBnClickedButtonReady();
	afx_msg void OnBnClickedButtonBusy();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonTransivr();

private:

	DECLARE_EVENTSINK_MAP()
	void OnUnLoginCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnReadyCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnBusyCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnRestCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnLockCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnAlertingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnHarfAlertingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnConnectingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnHarfConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnInternalConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnSuspendedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnConsultConnectingCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnConsultConnectedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnConferenceCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnMonitorCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnInsertCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnMonitoredCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnInsertedCcagentbarctrl(long eventID, LPCTSTR callID, LONGLONG contactID, long partyNum, LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originatingParty, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, 
		LONGLONG timestamp);
	void OnBeginRecordCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, long reason, LONGLONG timestamp);
	void OnEndRecordCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR filename, long reason, LONGLONG timestamp);
	void OnInprivatequeueCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnOutprivatequeueCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LONGLONG requestID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnCTIDisconnectCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnCTIMasterChangedCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnOperationFailedCcagentbarctrl(LPCTSTR callID, LONGLONG contactID, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
	void OnBeforeOutCallCcagentbarctrl(LPCTSTR otherParty, long otherPartyAttribute, LPCTSTR originalANI, LPCTSTR originalDNIS, long reason, LONGLONG timestamp);
    void OnHeartbeatCcagentbarctrl(LONGLONG timestamp);
    void OnBtnStatusCcagentbarctrl(LONGLONG btnStatus, LPCTSTR info);
public:
	
};
