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

#include "CCBar.h"
#include "CCAgentBarCtrl.h"
#include "Info.h"
#include "ImgMgr.h"
// CCCBar 对话框

IMPLEMENT_DYNAMIC(CCCBar, CDialog)
CCCBar::CCCBar(CWnd* pParent) : CDialog(CCCBar::IDD, pParent), m_AgentStatus(acd::AgentStatusT::AsUnknownState), m_totalTime(0), m_heartbeatCount(0), m_lDetaTime(0), 
	m_intStatusChangeType(acd::StatusChangeT::ScReady), m_intAutoAnswer(TRUE), m_intForceSignIn(TRUE), m_intCTIPort(10000), m_intTimeOut(3000), 
	m_intIsInitial(FALSE), m_intIsSignIn(FALSE), m_intIsSIPPhone(FALSE), m_intSIPServerPort(5060), m_intANIChangeType(ANICHANGE_SYSTEM), 
	m_intIsShowCallOut(TRUE), m_intIsCallOut(TRUE), m_intLogLevel(Level_High), m_intEnableSeniorCall(FALSE)
{
	p_m_BarCtrl = dynamic_cast<CCCAgentBarCtrl *>(pParent);

	// 初始化工具组件（日志等）
	Tool::Init(AfxGetInstanceHandle());
}

CCCBar::~CCCBar()
{
	if(m_thrd_heartbeat.is_valid()){
		m_thrd_heartbeat->stop();
		m_thrd_heartbeat->join();
		m_thrd_heartbeat = bgcc::SharedPointer<bgcc::Thread>(NULL);
	}
	Tool::UnInit();
}

void CCCBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SIGNINOUT, m_btnSignInOut);
	DDX_Control(pDX, IDC_BUTTON_ANSWER, m_btnAnswer);
	DDX_Control(pDX, IDC_BUTTON_CALLOUT, m_btnCallOut);
	DDX_Control(pDX, IDC_BUTTON_HUNGUP, m_btnHangup);
	DDX_Control(pDX, IDC_BUTTON_HOLD, m_btnHold);
	DDX_Control(pDX, IDC_BUTTON_CONSULT, m_btnConsult);
	DDX_Control(pDX, IDC_BUTTON_TRANSFER, m_btnTransfer);
	DDX_Control(pDX, IDC_BUTTON_CONFERENCE, m_btnConference);
	DDX_Control(pDX, IDC_BUTTON_SINGLESTEPTRANSFER, m_btnSingleStepTransfer);
	DDX_Control(pDX, IDC_BUTTON_REST, m_btnRest);
	DDX_Control(pDX, IDC_BUTTON_READY, m_btnReady);
	DDX_Control(pDX, IDC_BUTTON_BUSY, m_btnBusy);
	DDX_Control(pDX, IDC_BUTTON_SKILLCHANGE, m_btnSkillChange);
	DDX_Control(pDX, IDC_BUTTON_FENGEONE, m_btnFengeOne);
	DDX_Control(pDX, IDC_BUTTON_FENGETWO, m_btnFengeTwo);
	DDX_Control(pDX, IDC_BUTTON_FENGETHREE, m_btnFengeThree);
	DDX_Control(pDX, IDC_BUTTON_FENGEFOUR, m_btnFengeFour);
	DDX_Control(pDX, IDC_STATIC_AGENTSTATE, m_stcAgentState);
	DDX_Control(pDX, IDC_STATIC_AGENTSTATE_TIME, m_stcStateTime);
	DDX_Control(pDX, IDC_STATIC_TALK, m_stcTalk);
	DDX_Control(pDX, IDC_STATIC_TALK_TIME, m_stcTalkTime);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_stcTotalTalk);
	DDX_Control(pDX, IDC_STATIC_TOTAL_TIME, m_stcTotalTalkTime);
	DDX_Control(pDX, IDC_COMBO_REST, m_cmbRest);
	DDX_Control(pDX, IDC_COMBO_SKILL, m_cmbSkill);
}

BOOL CCCBar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(CImgMgr::Instance().LoadImg())
	{
		CBitmap *pBit = CImgMgr::Instance().Get(IDB_BMP_BACKGROUND);
		if(pBit == NULL)
			return FALSE;

		m_BrushTop.CreatePatternBrush(pBit);
		m_BrushBottom.CreateSolidBrush(RGB(170,211,253));

		m_stcAgentState.SetColor(RGB(170,211,253), RGB(5, 75, 144));
		m_stcStateTime.SetColor(RGB(233,191,145), RGB(5, 75, 144));

		m_stcTalk.SetColor(RGB(170,211,253), RGB(5, 75, 144));
		m_stcTalkTime.SetColor(RGB(233,191,145), RGB(5, 75, 144));

		m_stcTotalTalk.SetColor(RGB(170,211,253), RGB(5, 75, 144));
		m_stcTotalTalkTime.SetColor(RGB(233,191,145),RGB(5, 75, 144));
	}
	else
	{
		m_BrushTop.CreateSolidBrush(RGB(240,240,240));
		m_BrushBottom.CreateSolidBrush(RGB(225,225,225));
		
		m_stcAgentState.SetColor(RGB(128,255,255), RGB(250, 0, 0));
		m_stcStateTime.SetColor(RGB(92,80,35), RGB(255, 255, 255));

		m_stcTalk.SetColor(RGB(128,255,255), RGB(255, 0, 0));
		m_stcTalkTime.SetColor(RGB(92,80,35), RGB(255, 255, 255));

		m_stcTotalTalk.SetColor(RGB(128,255,255), RGB(255, 0, 0));
		m_stcTotalTalkTime.SetColor(RGB(92,80,35), RGB(255, 255, 255));
	}

	CRect rect;
	GetClientRect(&rect);
	rect.right = rect.left + BAR_WIDTH;											//宽1440
	rect.bottom = rect.top + BAR_HEIGHT;										//高84

	m_RectTop.left = rect.left;
	m_RectTop.top = rect.top;
	m_RectTop.right = rect.right;
	m_RectTop.bottom = rect.top + TOP_HEIGHT;

	m_RectBottom.left = rect.left;
	m_RectBottom.top = rect.top + TOP_HEIGHT;
	m_RectBottom.right = rect.right;
	m_RectBottom.bottom = rect.bottom;

	//宽150
	m_stcAgentState.SetWidth(150);
	m_stcAgentState.SetStaticexText("未签入");
	m_stcAgentState.SetFont(110, "宋体");
	m_stcAgentState.SetWindowpos(m_RectBottom.left, m_RectBottom.top);
	

	//宽100
	m_stcStateTime.SetWidth(100);
	m_stcStateTime.SetStaticexText("00:00:00");
	m_stcStateTime.SetFont(110, "宋体");
	m_stcStateTime.SetWindowpos(m_RectBottom.left + 150, m_RectBottom.top);

	//宽150
	m_stcTalk.SetWidth(150);
	m_stcTalk.SetStaticexText("当前通话时长");
	m_stcTalk.SetFont(110, "宋体");
	m_stcTalk.SetWindowpos(m_RectBottom.left + 250, m_RectBottom.top);

	//宽100
	m_stcTalkTime.SetWidth(100);
	m_stcTalkTime.SetStaticexText("00:00:00");
	m_stcTalkTime.SetFont(110, "宋体");
	m_stcTalkTime.SetWindowpos(m_RectBottom.left + 400, m_RectBottom.top);

	//宽150
	m_stcTotalTalk .SetWidth(150);
	m_stcTotalTalk.SetStaticexText("总通话时长");
	m_stcTotalTalk.SetFont(110, "宋体");
	m_stcTotalTalk.SetWindowpos(m_RectBottom.left + 500, m_RectBottom.top);

	//宽100
	m_stcTotalTalkTime.SetWidth(100);
	m_stcTotalTalkTime.SetStaticexText("00:00:00");
	m_stcTotalTalkTime.SetFont(110, "宋体");
	m_stcTotalTalkTime.SetWindowpos(m_RectBottom.left + 650, m_RectBottom.top);

	m_btnSignInOut.SetButtonPos(m_RectTop.left + 10, m_RectTop.top + BAR_TOP_POSITION);
	m_btnSignInOut.SetBitMap(IDB_BMP_IN_SIGNIN, IDB_BMP_IN_SIGNIN);
	m_btnSignInOut.EnableWindow(FALSE);

	m_btnFengeOne.SetButtonPos(m_RectTop.left + 62,  m_RectTop.top + BAR_TOP_POSITION);
	m_btnFengeOne.SetBitMap(IDB_BMP_FENGE, IDB_BMP_FENGE);
	m_btnFengeOne.EnableWindow(FALSE);

	m_btnAnswer.SetButtonPos(m_RectTop.left + 74, m_RectTop.top + BAR_TOP_POSITION);
	m_btnAnswer.SetBitMap(IDB_BMP_IN_ANSWER, IDB_BMP_IN_ANSWER);
	m_btnAnswer.EnableWindow(FALSE);

	m_btnCallOut.SetButtonPos(m_RectTop.left + 126,  m_RectTop.top + BAR_TOP_POSITION);
	m_btnCallOut.SetBitMap(IDB_BMP_IN_CALLOUT, IDB_BMP_IN_CALLOUT);
	m_btnCallOut.EnableWindow(FALSE);

	m_btnHangup.SetButtonPos(m_RectTop.left + 178,  m_RectTop.top + BAR_TOP_POSITION);
	m_btnHangup.SetBitMap(IDB_BMP_IN_HANGUP, IDB_BMP_IN_HANGUP);
	m_btnHangup.EnableWindow(FALSE);

	m_btnFengeTwo.SetButtonPos(m_RectTop.left + 230, m_RectTop.top + BAR_TOP_POSITION);
	m_btnFengeTwo.SetBitMap(IDB_BMP_FENGE, IDB_BMP_FENGE);
	m_btnFengeTwo.EnableWindow(FALSE);

	m_btnHold.SetButtonPos(m_RectTop.left + 242, m_RectTop.top + BAR_TOP_POSITION);
	m_btnHold.SetBitMap(IDB_BMP_IN_HOLD, IDB_BMP_IN_HOLD);
	m_btnHold.EnableWindow(FALSE);

	m_btnFengeThree.SetButtonPos(m_RectTop.left + 294, m_RectTop.top + BAR_TOP_POSITION);
	m_btnFengeThree.SetBitMap(IDB_BMP_FENGE, IDB_BMP_FENGE);
	m_btnFengeThree.EnableWindow(FALSE);

	m_btnConsult.SetButtonPos(m_RectTop.left + 306, m_RectTop.top + BAR_TOP_POSITION);
	m_btnConsult.SetBitMap(IDB_BMP_IN_CONSULT, IDB_BMP_IN_CONSULT);
	m_btnConsult.EnableWindow(FALSE);

	m_btnTransfer.SetButtonPos(m_RectTop.left + 358, m_RectTop.top + BAR_TOP_POSITION);
	m_btnTransfer.SetBitMap(IDB_BMP_IN_TRANSFER, IDB_BMP_IN_TRANSFER);
	m_btnTransfer.EnableWindow(FALSE);

	m_btnConference.SetButtonPos(m_RectTop.left + 410, m_RectTop.top + BAR_TOP_POSITION);
	m_btnConference.SetBitMap(IDB_BMP_IN_CONFERENCE, IDB_BMP_IN_CONFERENCE);
	m_btnConference.EnableWindow(FALSE);

	m_btnSingleStepTransfer.SetButtonPos(m_RectTop.left + 462, m_RectTop.top + BAR_TOP_POSITION);
	m_btnSingleStepTransfer.SetBitMap(IDB_BMP_IN_SSTRANSFER, IDB_BMP_IN_SSTRANSFER);
	m_btnSingleStepTransfer.EnableWindow(FALSE);

	m_btnFengeFour.SetButtonPos(m_RectTop.left + 514, m_RectTop.top + BAR_TOP_POSITION);
	m_btnFengeFour.SetBitMap(IDB_BMP_FENGE, IDB_BMP_FENGE);
	m_btnFengeFour.EnableWindow(FALSE);

	m_btnRest.SetButtonPos(m_RectTop.left + 526, m_RectTop.top + BAR_TOP_POSITION);
	m_btnRest.SetBitMap(IDB_BMP_IN_REST, IDB_BMP_IN_REST);
	m_btnRest.EnableWindow(FALSE);

	m_cmbRest.MoveWindow(m_RectTop.left + 578, m_RectTop.top + BAR_TOP_POSITION, 76, 80);
	m_cmbRest.EnableWindow(FALSE);

	m_btnReady.SetButtonPos(m_RectTop.left + 658, m_RectTop.top + BAR_TOP_POSITION); 
	m_btnReady.SetBitMap(IDB_BMP_IN_READY, IDB_BMP_IN_READY);
	m_btnReady.EnableWindow(FALSE);

	m_btnBusy.SetButtonPos(m_RectTop.left + 710, m_RectTop.top + BAR_TOP_POSITION);
	m_btnBusy.SetBitMap(IDB_BMP_IN_BUSY, IDB_BMP_IN_BUSY);
	m_btnBusy.EnableWindow(FALSE);

	m_btnSkillChange.SetButtonPos(m_RectTop.left + 762 ,m_RectTop.top + BAR_TOP_POSITION);
	m_btnSkillChange.SetBitMap(IDB_BMP_IN_SKILLCHANGE, IDB_BMP_IN_SKILLCHANGE);
	m_btnSkillChange.EnableWindow(FALSE);

	m_cmbSkill.MoveWindow(m_RectTop.left + 814, m_RectTop.top + BAR_TOP_POSITION, 152, 80);
	m_cmbSkill.EnableWindow(FALSE);

	m_btnSkillChange.ShowWindow(SW_HIDE);
	m_cmbSkill.ShowWindow(SW_HIDE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCCBar, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SIGNINOUT, OnBnClickedButtonSigninout)
	ON_BN_CLICKED(IDC_BUTTON_ANSWER, OnBnClickedButtonAnswer)
	ON_BN_CLICKED(IDC_BUTTON_CALLOUT, OnBnClickedButtonCallout)
	ON_BN_CLICKED(IDC_BUTTON_HUNGUP, OnBnClickedButtonHungup)
	ON_BN_CLICKED(IDC_BUTTON_HOLD, OnBnClickedButtonHold)
	ON_BN_CLICKED(IDC_BUTTON_CONSULT, OnBnClickedButtonConsult)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER, OnBnClickedButtonTransfer)
	ON_BN_CLICKED(IDC_BUTTON_CONFERENCE, OnBnClickedButtonConference)
	ON_BN_CLICKED(IDC_BUTTON_SINGLESTEPTRANSFER, OnBnClickedButtonSinglesteptransfer)
	ON_BN_CLICKED(IDC_BUTTON_REST, OnBnClickedButtonRest)
	ON_BN_CLICKED(IDC_BUTTON_READY, OnBnClickedButtonReady)
	ON_BN_CLICKED(IDC_BUTTON_BUSY, OnBnClickedButtonBusy)
	ON_BN_CLICKED(IDC_BUTTON_SKILLCHANGE, OnBnClickedButtonSkillchange)
	ON_MESSAGE(WM_AGENTEVENT, OnAgentEvent)
	ON_MESSAGE(WM_MEDIAEVENT, OnMediaEvent)
	ON_MESSAGE(WM_QUEUEEVENT, OnRouteEvent)
	ON_MESSAGE(WM_OTHEREVENT, OnOtherEvent)
END_MESSAGE_MAP()

void CCCBar::SetButton()
{
	if(m_btnStatus.btnLogin ^ m_lastBtnStatus.btnLogin || m_btnStatus.btnLogout ^ m_lastBtnStatus.btnLogout)
	{
		if(m_btnStatus.btnLogin)
		{
			m_btnSignInOut.SetBitMap(IDB_BMP_SIGNIN, IDB_BMP_MS_SIGNIN);
			m_btnSignInOut.EnableWindow(TRUE);
		}
		else if(m_btnStatus.btnLogout)
		{
			m_btnSignInOut.SetBitMap(IDB_BMP_SIGNOUT, IDB_BMP_MS_SIGNOUT);
			m_btnSignInOut.EnableWindow(TRUE);
		}
		else if(m_lastBtnStatus.btnLogin)
		{
			m_btnSignInOut.SetBitMap(IDB_BMP_IN_SIGNIN, IDB_BMP_IN_SIGNIN);
			m_btnSignInOut.EnableWindow(FALSE);
		}
		else
		{
			m_btnSignInOut.SetBitMap(IDB_BMP_IN_SIGNOUT, IDB_BMP_IN_SIGNOUT);
			m_btnSignInOut.EnableWindow(FALSE);
		}
		m_btnSignInOut.Invalidate();
	}
	if(m_btnStatus.btnAnswer ^ m_lastBtnStatus.btnAnswer)
	{
		if(m_btnStatus.btnAnswer)
		{
			m_btnAnswer.SetBitMap(IDB_BMP_ANSWER, IDB_BMP_MS_ANSWER);
			m_btnAnswer.EnableWindow(TRUE);
		}
		else
		{
			m_btnAnswer.SetBitMap(IDB_BMP_IN_ANSWER, IDB_BMP_IN_ANSWER);
			m_btnAnswer.EnableWindow(FALSE);
		}
		m_btnAnswer.Invalidate();
	}
	if((m_btnStatus.btnCallout ^ m_lastBtnStatus.btnCallout || m_btnStatus.btnSenddtmf ^ m_lastBtnStatus.btnSenddtmf) && m_intIsShowCallOut)
	{
		if(m_btnStatus.btnCallout)
		{
			m_btnCallOut.SetBitMap(IDB_BMP_CALLOUT, IDB_BMP_MS_CALLOUT);
			m_btnCallOut.EnableWindow(TRUE);
		}
		else if(m_btnStatus.btnSenddtmf)
		{
			m_btnCallOut.SetBitMap(IDB_BMP_SENDDTMF, IDB_BMP_MS_SENDDTMF);
			m_btnCallOut.EnableWindow(TRUE);
		}
		else
		{
			m_btnCallOut.SetBitMap(IDB_BMP_IN_CALLOUT, IDB_BMP_IN_CALLOUT);
			m_btnCallOut.EnableWindow(FALSE);
		}
		m_btnCallOut.Invalidate();
	}
	if(m_btnStatus.btnHangup ^ m_lastBtnStatus.btnHangup)
	{
		if(m_btnStatus.btnHangup)
		{
			m_btnHangup.SetBitMap(IDB_BMP_HANGUP, IDB_BMP_MS_HANGUP);
			m_btnHangup.EnableWindow(TRUE);
		}
		else
		{
			m_btnHangup.SetBitMap(IDB_BMP_IN_HANGUP, IDB_BMP_IN_HANGUP);
			m_btnHangup.EnableWindow(FALSE);
		}
		m_btnHangup.Invalidate();
	}
	if(m_btnStatus.btnHold ^ m_lastBtnStatus.btnHold || m_btnStatus.btnRetrieve ^ m_lastBtnStatus.btnRetrieve)
	{
		if(m_btnStatus.btnHold)
		{
			m_btnHold.SetBitMap(IDB_BMP_HOLD, IDB_BMP_MS_HOLD);
			m_btnHold.EnableWindow(TRUE);
		}
		else if(m_btnStatus.btnRetrieve)
		{
			m_btnHold.SetBitMap(IDB_BMP_RETRIEVE, IDB_BMP_MS_RETRIEVE);
			m_btnHold.EnableWindow(TRUE);
		}
		else
		{
			m_btnHold.SetBitMap(IDB_BMP_IN_HOLD, IDB_BMP_IN_HOLD);
			m_btnHold.EnableWindow(FALSE);
		}
		m_btnHold.Invalidate();
	}
	if((m_btnStatus.btnConsult ^ m_lastBtnStatus.btnConsult || m_btnStatus.btnReconnect ^ m_lastBtnStatus.btnReconnect) && m_intEnableSeniorCall)
	{
		if(m_btnStatus.btnConsult)
		{
			m_btnConsult.SetBitMap(IDB_BMP_CONSULT, IDB_BMP_MS_CONSULT);
			m_btnConsult.EnableWindow(TRUE);
		}
		else if(m_btnStatus.btnReconnect)
		{
			m_btnConsult.SetBitMap(IDB_BMP_RECONNECT, IDB_BMP_MS_RECONNECT);
			m_btnConsult.EnableWindow(TRUE);
		}
		else
		{
			m_btnConsult.SetBitMap(IDB_BMP_IN_CONSULT, IDB_BMP_IN_CONSULT);
			m_btnConsult.EnableWindow(FALSE);
		}
		m_btnConsult.Invalidate();
	}
	if((m_btnStatus.btnTransfer ^ m_lastBtnStatus.btnTransfer) && m_intEnableSeniorCall)
	{
		if(m_btnStatus.btnTransfer)
		{
			m_btnTransfer.SetBitMap(IDB_BMP_TRANSFER, IDB_BMP_MS_TRANSFER);
			m_btnTransfer.EnableWindow(TRUE);
		}
		else
		{
			m_btnTransfer.SetBitMap(IDB_BMP_IN_TRANSFER, IDB_BMP_IN_TRANSFER);
			m_btnTransfer.EnableWindow(FALSE);
		}
		m_btnTransfer.Invalidate();
	}
	if((m_btnStatus.btnConference ^ m_lastBtnStatus.btnConference) && m_intEnableSeniorCall)
	{
		if(m_btnStatus.btnConference)
		{
			m_btnConference.SetBitMap(IDB_BMP_CONFERENCE, IDB_BMP_MS_CONFERENCE);
			m_btnConference.EnableWindow(TRUE);
		}
		else
		{
			m_btnConference.SetBitMap(IDB_BMP_IN_CONFERENCE, IDB_BMP_IN_CONFERENCE);
			m_btnConference.EnableWindow(FALSE);
		}
		m_btnConference.Invalidate();
	}
	if((m_btnStatus.btnSSTransfer ^ m_lastBtnStatus.btnSSTransfer) && m_intEnableSeniorCall)
	{
		if(m_btnStatus.btnSSTransfer)
		{
			m_btnSingleStepTransfer.SetBitMap(IDB_BMP_SSTRANSFER, IDB_BMP_MS_SSTRANSFER);
			m_btnSingleStepTransfer.EnableWindow(TRUE);
		}
		else
		{
			m_btnSingleStepTransfer.SetBitMap(IDB_BMP_IN_SSTRANSFER, IDB_BMP_IN_SSTRANSFER);
			m_btnSingleStepTransfer.EnableWindow(FALSE);
		}
		m_btnSingleStepTransfer.Invalidate();
	}
	if(m_btnStatus.btnRest ^ m_lastBtnStatus.btnRest)
	{
		if(m_btnStatus.btnRest)
		{
			m_btnRest.SetBitMap(IDB_BMP_REST, IDB_BMP_MS_REST);
			m_btnRest.EnableWindow(TRUE);
			m_cmbRest.EnableWindow(TRUE);
		}
		else
		{
			m_btnRest.SetBitMap(IDB_BMP_IN_REST, IDB_BMP_IN_REST);
			m_btnRest.EnableWindow(FALSE);
			m_cmbRest.EnableWindow(FALSE);
		}
		m_btnRest.Invalidate();
	}
	if(m_btnStatus.btnReady ^ m_lastBtnStatus.btnReady)
	{
		if(m_btnStatus.btnReady)
		{
			m_btnReady.SetBitMap(IDB_BMP_READY, IDB_BMP_MS_READY);
			m_btnReady.EnableWindow(TRUE);
		}
		else
		{
			m_btnReady.SetBitMap(IDB_BMP_IN_READY, IDB_BMP_IN_READY);
			m_btnReady.EnableWindow(FALSE);
		}
		m_btnReady.Invalidate();
	}
	if(m_btnStatus.btnBusy ^ m_lastBtnStatus.btnBusy)
	{
		if(m_btnStatus.btnBusy)
		{
			m_btnBusy.SetBitMap(IDB_BMP_BUSY, IDB_BMP_MS_BUSY);
			m_btnBusy.EnableWindow(TRUE);
		}
		else
		{
			m_btnBusy.SetBitMap(IDB_BMP_IN_BUSY, IDB_BMP_IN_BUSY);
			m_btnBusy.EnableWindow(FALSE);
		}
		m_btnBusy.Invalidate();
	}
	if(m_btnStatus.btnSkill ^ m_lastBtnStatus.btnSkill)
	{
		if(m_btnStatus.btnSkill)
		{
			m_btnSkillChange.SetBitMap(IDB_BMP_SKILLCHANGE, IDB_BMP_MS_SKILLCHANGE);
			m_btnSkillChange.EnableWindow(TRUE);
			m_cmbSkill.EnableWindow(TRUE);
		}
		else
		{
			m_btnSkillChange.SetBitMap(IDB_BMP_IN_SKILLCHANGE, IDB_BMP_IN_SKILLCHANGE);
			m_btnSkillChange.EnableWindow(FALSE);
			m_cmbSkill.EnableWindow(FALSE);
		}
		m_btnSkillChange.Invalidate();
	}
}

void CCCBar::PostMessageEx(const acd::AgentStatusT &agentStatus, const acd::CallEventReasonT &reason)
{
	acd::AgentEventT *pAE = new acd::AgentEventT;
	pAE->agentId = m_strAgentID;
	pAE->eventId = acd::CallEventTypeT::CeUnKnownEvent;
	pAE->agentDn = m_strDN;
	pAE->callId = "";
	pAE->sessionId = 0;
	pAE->agentStatus = agentStatus;
	pAE->originalCallid = "";
	pAE->partyNum = 0;
	pAE->otherParty = "";
	pAE->otherAttr = acd::PartyAttributeT::PaUnknown;
	pAE->originatingParty = "";
	pAE->originalAni = m_orgCallingNo;
	pAE->originalDnis = m_orgCalledNo;
	pAE->reason = reason;
	if(!m_lDetaTime)
	{
		pAE->timestamp = CTime::GetCurrentTime().GetTime() * 1000000;
	}
	else
	{
		pAE->timestamp = static_cast<int64_t>(GetTickCount()) * 1000 + static_cast<int64_t>(m_lDetaTime);
	}

	LONGLONG address = reinterpret_cast<LONGLONG>(pAE);
	int ladr = LOLONG(address);
	int hadr = HILONG(address);
	PostMessage(WM_AGENTEVENT, ladr, hadr);
}

void CCCBar::PostMessageEx(const acd::OtherEventTypeT &otherEventType)
{
	acd::OtherEventT *pOE = new acd::OtherEventT;
	pOE->agentId = m_strAgentID;
	pOE->eventType = otherEventType;
	pOE->agentDn = m_strDN;
	pOE->callId = "";
	pOE->sessionId = 0;
	pOE->originalAni = m_orgCallingNo;
	pOE->originalDnis = m_orgCalledNo;
	if(!m_lDetaTime)
	{
		pOE->timestamp = CTime::GetCurrentTime().GetTime() * 1000000;
	}
	else
	{
		pOE->timestamp = static_cast<int64_t>(GetTickCount()) * 1000 + static_cast<int64_t>(m_lDetaTime);
	}

	LONGLONG address = reinterpret_cast<LONGLONG>(pOE);
	int ladr = LOLONG(address);
	int hadr = HILONG(address);
	PostMessage(WM_OTHEREVENT, ladr, hadr);
}

void CCCBar::Backup()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	// 签出坐席
	PostMessageEx(acd::AgentStatusT::AsUnLoginState, acd::CallEventReasonT::CerUnloginBackup);
	// 发送断连消息
	PostMessageEx(acd::OtherEventTypeT::ACDDisconnect);
	// 服务倒换
	m_acd.AcdBackup();
	// 尝试重连
	int tryTime = TIMES_HEARTBEAT_EXCEPTION;
	while(tryTime--)
	{
		ret = m_acd.AcdSignIn(m_strAgentID, m_strDN, m_strPassWord, m_intStatusChangeType, !!m_intAutoAnswer, !!m_intForceSignIn, m_strServiceList);
		if(ret == acd::AcdResultT::ArNotMaster)// 非主
		{
			bgcc::TimeUtil::safe_sleep_ms(TIMESPAN_HEARTBEAT);
		}
		else
		{
			break;
		}
	}
	if(ret == AGENTBARERROR_SUCCESS)
	{
		// 倒换成功
		PostMessageEx(acd::OtherEventTypeT::ACDMasterChange);
	}
	else
	{
		// 倒换失败
		PostMessageEx(acd::OtherEventTypeT::ACDOperationFailed);
	}
}

void CCCBar::ReSignIn()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	// 签出坐席
	PostMessageEx(acd::AgentStatusT::AsUnLoginState, acd::CallEventReasonT::CerUnloginResignin);
	// 尝试重签
	ret = m_acd.AcdSignIn(m_strAgentID, m_strDN, m_strPassWord, m_intStatusChangeType, !!m_intAutoAnswer, !!m_intForceSignIn, m_strServiceList);
	if(ret == AGENTBARERROR_SUCCESS)
	{
		// 重签成功
		PostMessageEx(acd::OtherEventTypeT::ACDReLoginSuccess);
	}
	else
	{
		// 重签失败
		PostMessageEx(acd::OtherEventTypeT::ACDReLoginFailed);
	}
}

BOOL CCCBar::OnEraseBkgnd(CDC* pDC)
{
	CBrush * p_OldBrush = pDC->SelectObject(&m_BrushTop);
	pDC->FillRect(&m_RectTop, &m_BrushTop);
	pDC->SelectObject(p_OldBrush);

	p_OldBrush = pDC->SelectObject(&m_BrushBottom);
	pDC->FillRect(&m_RectBottom, &m_BrushBottom);
	pDC->SelectObject(p_OldBrush);

	p_OldBrush = NULL;

	return TRUE;
}

BOOL CCCBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_BUTTON_SIGNINOUT:
		case IDC_BUTTON_ANSWER:
		case IDC_BUTTON_CALLOUT:
		case IDC_BUTTON_HUNGUP:
		case IDC_BUTTON_HOLD:
		case IDC_BUTTON_CONSULT:
		case IDC_BUTTON_TRANSFER:
		case IDC_BUTTON_CONFERENCE:
		case IDC_BUTTON_SINGLESTEPTRANSFER:
		case IDC_BUTTON_REST:
		case IDC_BUTTON_READY:
		case IDC_BUTTON_BUSY:
		case IDC_BUTTON_SKILLCHANGE:
		case IDC_BUTTON_FENGEONE:
		case IDC_BUTTON_FENGETWO:
		case IDC_BUTTON_FENGETHREE:
		case IDC_BUTTON_FENGEFOUR:
			if(pWnd->IsWindowEnabled())
			{
				if(GetCursor() != AfxGetApp()->LoadStandardCursor(IDC_HAND))
				{
					SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
				}
			}
			break;
		default :
			if(GetCursor() != AfxGetApp()->LoadStandardCursor(IDC_ARROW))
			{
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			}	
			break;
	}
	return TRUE;
}

void CCCBar::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case TIMER_STATUS://状态定时器
		{
			CTime curentTime = CTime::GetCurrentTime();
			CTimeSpan timeSpan = curentTime - m_lastStatusTime;
			if(timeSpan.GetTotalSeconds() > 60 || timeSpan.GetTotalSeconds() < 0)
			{
				m_beginStatusTime += timeSpan;
			}
			timeSpan = curentTime - m_beginStatusTime;
			m_lastStatusTime = curentTime;

			m_stcStateTime.SetStaticexText(timeSpan.Format("%H:%M:%S"));
			m_stcStateTime.Invalidate();
			break;
		}
	case TIMER_TALK:
		{
			CTime curentTime = CTime::GetCurrentTime();
			CTimeSpan timeSpan = curentTime - m_lastTalkTime;
			m_totalTime += timeSpan;
			if(timeSpan.GetTotalSeconds() > 60 || timeSpan.GetTotalSeconds() < 0)
			{
				m_beginTalkTime += timeSpan;
			}
			timeSpan = curentTime - m_beginTalkTime;
			m_lastTalkTime = curentTime;

			m_stcTalkTime.SetStaticexText(timeSpan.Format("%H:%M:%S"));
			m_stcTalkTime.Invalidate();

			m_stcTotalTalkTime.SetStaticexText(m_totalTime.Format("%H:%M:%S"));
			m_stcTotalTalkTime.Invalidate();

			break;
		}
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CCCBar::OnDestroy()
{
	// TODO: 在此处添加消息处理程序代码
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState)
	{
		// 不处理
	}
	else if(m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		// 未登录则反初始化
		m_acd.AcdUnInitial();
		if(m_intIsSIPPhone)
		{
			m_sip.SipUnInitial();
		}
	}
	else
	{
		// 先挂断，后签出，最后反初始化BGCC和SIP
		m_acd.AcdReset(m_strAgentID);
		m_acd.AcdUnInitial();
		if(m_intIsSIPPhone)
		{
			m_sip.SipUnInitial();
		}
	}
	m_BrushTop.DeleteObject();
	m_BrushBottom.DeleteObject();
	CImgMgr::Instance().UnLoadImg();
	CDialog::OnDestroy();
}

void CCCBar::OnBnClickedButtonSigninout()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	if(m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		LONG ret =  BSignIn();
		if(AGENTBARERROR_SUCCESS != ret)
		{
			string mes;
			Tool::GetAcdResult_Str(ret, mes);
			CInfo info;
			info.SetInfo(IDI_ICON_ERROR, "签入失败：%s", mes.c_str());
			info.DoModal();
		}
	}
	else
	{
		LONG ret = BSignOut();
		if(AGENTBARERROR_SUCCESS != ret)
		{
			string mes;
			Tool::GetAcdResult_Str(ret, mes);
			CInfo info;
			info.SetInfo(IDI_ICON_ERROR, "签出失败：%s", mes.c_str());
			info.DoModal();
		}
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BAnswer();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "接听失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonCallout()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	CRect rect;
	m_btnCallOut.GetWindowRect(&rect);
	m_dlgCallOut.SetPosition(rect.right, rect.bottom);
	if(m_dlgCallOut.DoModal() == IDOK)
	{
		if(m_AgentStatus == acd::AgentStatusT::AsBusyState)// 外呼
		{
			if(m_dlgCallOut.GetAgentOrOut() == 0)//外线
			{
				// 是否发起外呼
				m_intIsCallOut = TRUE;
				p_m_BarCtrl->OnBeforeOutCall(m_dlgCallOut.GetNumber(), acd::PartyAttributeT::PaNormal, m_strDN, m_dlgCallOut.GetNumber(), 1, CTime::GetCurrentTime().GetTime() * 1000000);
				if(!m_intIsCallOut)
				{
					Tool::m_Logger.WriteLog("CCCBar", "OnBnClickedButtonCallout", "IsCallOut Error", m_intIsCallOut);
					return;
				}
				// 发起外呼
				CString showANI, showDNIS;
				switch(m_intANIChangeType)
				{
				case ANICHANGE_SYSTEM:
					break;
				case ANICHANGE_TRANSFER:
					showDNIS = m_strDN;
					break;
				case ANICHANGE_SPECIAL:
					break;
				default:
					break;
				}
				LONG ret = BMakeCall(m_dlgCallOut.GetNumber(), showANI, showDNIS, acd::CallModeT::CmNormal, acd::CallTypeT::CtOut);
				if(AGENTBARERROR_SUCCESS != ret)
				{
					string mes;
					Tool::GetAcdResult_Str(ret, mes);
					CInfo info;
					info.SetInfo(IDI_ICON_ERROR, "呼出失败：%s", mes.c_str());
					info.DoModal();
				}
			}
			else//坐席
			{
				CString showANI, showDNIS;
				switch(m_intANIChangeType)
				{
				case ANICHANGE_SYSTEM:
					break;
				case ANICHANGE_TRANSFER:
					showDNIS = m_strDN;
					break;
				case ANICHANGE_SPECIAL:
					break;
				default:
					break;
				}
				LONG ret = BMakeCall(m_dlgCallOut.GetNumber(), showANI, showDNIS, acd::CallModeT::CmNormal, acd::CallTypeT::CtAgent);
				if(AGENTBARERROR_SUCCESS != ret)
				{
					string mes;
					Tool::GetAcdResult_Str(ret, mes);
					CInfo info;
					info.SetInfo(IDI_ICON_ERROR, "呼出失败：%s", mes.c_str());
					info.DoModal();
				}
			}
		}
		else// 二次拨号
		{
			LONG ret = BSendDTMF(m_dlgCallOut.GetNumber());
			if(AGENTBARERROR_SUCCESS != ret)
			{
				string mes;
				Tool::GetAcdResult_Str(ret, mes);
				CInfo info;
				info.SetInfo(IDI_ICON_ERROR, "拨打分机失败：%s", mes.c_str());
				info.DoModal();
			}
		}
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonHungup()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BReleaseCall();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "挂断失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonHold()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	if(m_AgentStatus == acd::AgentStatusT::AsConnectedState)
	{
		LONG ret = BHold();
		if(AGENTBARERROR_SUCCESS != ret)
		{
			string mes;
			Tool::GetAcdResult_Str(ret, mes);
			CInfo info;
			info.SetInfo(IDI_ICON_ERROR, "保持失败：%s", mes.c_str());
			info.DoModal();
		}
	}
	else
	{
		LONG ret = BRetrieve();
		if(AGENTBARERROR_SUCCESS != ret)
		{
			string mes;
			Tool::GetAcdResult_Str(ret, mes);
			CInfo info;
			info.SetInfo(IDI_ICON_ERROR, "保持接回失败：%s", mes.c_str());
			info.DoModal();
		}
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonConsult()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	if(m_AgentStatus == acd::AgentStatusT::AsConnectedState)
	{
		CRect rect;
		m_btnConsult.GetWindowRect(&rect);
		m_dlgCallOut.SetPosition(rect.right, rect.bottom);
		if(m_dlgCallOut.DoModal() == IDOK)
		{
			if(m_dlgCallOut.GetAgentOrOut() == 0)// 外线
			{
				// 是否发起外呼
				m_intIsCallOut = TRUE;
				p_m_BarCtrl->OnBeforeOutCall(m_dlgCallOut.GetNumber(), acd::PartyAttributeT::PaNormal, m_strDN, m_dlgCallOut.GetNumber(), 2, CTime::GetCurrentTime().GetTime() * 1000000);
				if(!m_intIsCallOut)
				{
					Tool::m_Logger.WriteLog("CCCBar", "OnBnClickedButtonConsult", "IsCallOut Error", m_intIsCallOut);
					return;
				}
				// 发起咨询
				CString showANI, showDNIS;
				switch(m_intANIChangeType)
				{
				case ANICHANGE_SYSTEM:
					break;
				case ANICHANGE_TRANSFER:
					showDNIS = m_strDN;
					break;
				case ANICHANGE_SPECIAL:
					break;
				default:
					break;
				}
				LONG ret = BConsult(m_dlgCallOut.GetNumber(), showANI, showDNIS, acd::CallTypeT::CtOut);
				if(AGENTBARERROR_SUCCESS != ret)
				{
					string mes;
					Tool::GetAcdResult_Str(ret, mes);
					CInfo info;
					info.SetInfo(IDI_ICON_ERROR, "咨询失败：%s", mes.c_str());
					info.DoModal();
				}
			}
			else// 坐席
			{
				CString showANI, showDNIS;
				switch(m_intANIChangeType)
				{
				case ANICHANGE_SYSTEM:
					break;
				case ANICHANGE_TRANSFER:
					showDNIS = m_strDN;
					break;
				case ANICHANGE_SPECIAL:
					break;
				default:
					break;
				}
				LONG ret = BConsult(m_dlgCallOut.GetNumber(), showANI, showDNIS, acd::CallTypeT::CtAgent);
				if(AGENTBARERROR_SUCCESS != ret)
				{
					string mes;
					Tool::GetAcdResult_Str(ret, mes);
					CInfo info;
					info.SetInfo(IDI_ICON_ERROR, "咨询失败：%s", mes.c_str());
					info.DoModal();
				}
			}
		}
	}
	else
	{
		LONG ret = BReconnect();
		if(AGENTBARERROR_SUCCESS != ret)
		{
			string mes;
			Tool::GetAcdResult_Str(ret, mes);
			CInfo info;
			info.SetInfo(IDI_ICON_ERROR, "咨询接回失败：%s", mes.c_str());
			info.DoModal();
		}
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonTransfer()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BTransfer();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "咨询转移失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonConference()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BConference();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "咨询会议失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonSinglesteptransfer()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	CRect rect;
	m_btnSingleStepTransfer.GetWindowRect(&rect);
	m_dlgCallOut.SetPosition(rect.right, rect.bottom);
	if(m_dlgCallOut.DoModal() == IDOK)
	{
		if(m_dlgCallOut.GetAgentOrOut() == 0)// 外线
		{
			// 是否发起外呼
			m_intIsCallOut = TRUE;
			p_m_BarCtrl->OnBeforeOutCall(m_dlgCallOut.GetNumber(), acd::PartyAttributeT::PaNormal, m_strDN, m_dlgCallOut.GetNumber(), 3, CTime::GetCurrentTime().GetTime() * 1000000);
			if(!m_intIsCallOut)
			{
				Tool::m_Logger.WriteLog("CCCBar", "OnBnClickedButtonSinglesteptransfer", "IsCallOut Error", m_intIsCallOut);
				return;
			}
			// 发起转移
			CString showANI, showDNIS;
			switch(m_intANIChangeType)
			{
			case ANICHANGE_SYSTEM:
				break;
			case ANICHANGE_TRANSFER:
				showDNIS = m_strDN;
				break;
			case ANICHANGE_SPECIAL:
				break;
			default:
				break;
			}
			LONG ret = BSingleStepTransfer(m_dlgCallOut.GetNumber(), showANI, showDNIS, FALSE, acd::CallTypeT::CtOut);
			if(AGENTBARERROR_SUCCESS != ret)
			{
				string mes;
				Tool::GetAcdResult_Str(ret, mes);
				CInfo info;
				info.SetInfo(IDI_ICON_ERROR, "通话转移失败：%s", mes.c_str());
				info.DoModal();
			}
		}
		else// 坐席
		{
			CString showANI, showDNIS;
			switch(m_intANIChangeType)
			{
			case ANICHANGE_SYSTEM:
				break;
			case ANICHANGE_TRANSFER:
				showDNIS = m_strDN;
				break;
			case ANICHANGE_SPECIAL:
				break;
			default:
				break;
			}
			LONG ret = BSingleStepTransfer(m_dlgCallOut.GetNumber(), showANI, showDNIS, FALSE, acd::CallTypeT::CtAgent);
			if(AGENTBARERROR_SUCCESS != ret)
			{
				string mes;
				Tool::GetAcdResult_Str(ret, mes);
				CInfo info;
				info.SetInfo(IDI_ICON_ERROR, "通话转移失败：%s", mes.c_str());
				info.DoModal();
			}
		}
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonRest()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	// 取休息原因
	int index = m_cmbRest.GetCurSel();
	CString reason;
	if(index != -1)
		m_cmbRest.GetLBText(index, reason);
	LONG ret = BSetRest(reason);
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "休息失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonReady()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BSetIdle();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "应答就绪失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonBusy()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BSetBusy();
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "接听就绪失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

void CCCBar::OnBnClickedButtonSkillchange()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	LONG ret = BResetSkill("");
	if(AGENTBARERROR_SUCCESS != ret)
	{
		string mes;
		Tool::GetAcdResult_Str(ret, mes);
		CInfo info;
		info.SetInfo(IDI_ICON_ERROR, "技能切换失败：%s", mes.c_str());
		info.DoModal();
	}
	EndWaitCursor();
}

LRESULT CCCBar::OnAgentEvent(WPARAM wParam, LPARAM lParam)
{
	LONGLONG address = MAKELONGLONG(wParam, lParam);
	acd::AgentEventT *pAE = reinterpret_cast<acd::AgentEventT *>(address);
	Tool::WriteAgentEventLog(pAE, "out");

	m_AgentStatus = pAE->agentStatus;
	m_btnStatus.Reset();
	m_beginStatusTime = CTime::GetCurrentTime();

	m_strActiveCallID = pAE->callId;

	try
	{
		switch(m_AgentStatus.get_value())
		{
		case acd::AgentStatusT::AsUnknownState:
			{
				m_stcAgentState.SetStaticexText("未知状态");
				break;
			}
		case acd::AgentStatusT::AsUnLoginState:
			{
				m_btnStatus.btnLogin = true;
				m_stcAgentState.SetStaticexText("未签入");
				// 终止状态定时器，所有时间归零
				if(m_intIsSignIn)
				{
					KillTimer(TIMER_STATUS);
					m_stcStateTime.SetStaticexText("00:00:00");
					m_stcStateTime.Invalidate();
					KillTimer(TIMER_TALK);
					m_stcTalkTime.SetStaticexText("00:00:00");
					m_stcTalkTime.Invalidate();
					if(m_thrd_heartbeat.is_valid()){
						m_thrd_heartbeat->stop();
						m_thrd_heartbeat->join();
						m_thrd_heartbeat=bgcc::SharedPointer<bgcc::Thread>(NULL);
					}

					m_totalTime = 0;
					m_stcTotalTalkTime.SetStaticexText("00:00:00");
					m_stcTotalTalkTime.Invalidate();
				}
				m_intIsSignIn = FALSE;
				// 事件回调
				p_m_BarCtrl->OnUnLogin(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsReadyState:
			{
				m_btnStatus.btnLogout = true;
				m_btnStatus.btnRest = true;
				m_btnStatus.btnBusy = true;
				m_btnStatus.btnSkill = true;
				m_stcAgentState.SetStaticexText("接听就绪");
				// 启动状态定时器、终止通话定时器
				if(pAE->reason == acd::CallEventReasonT::CerIdleSelfLogin || pAE->reason == acd::CallEventReasonT::CerIdleOtherLogin)
				{
					SetTimer(TIMER_STATUS, TIMESPAN_STATUS, NULL);
					m_thrd_heartbeat=bgcc::SharedPointer<bgcc::Thread>(new bgcc::Thread(bgcc::SharedPointer<HeartBeatTask>(new HeartBeatTask(this))));
					if(m_thrd_heartbeat.is_valid()){
						m_thrd_heartbeat->start();
					}
					m_lastStatusTime = CTime::GetCurrentTime();
					// 初始化休息原因
					m_cmbRest.ResetContent();
					acd::StringListT reasons;
					if(BGetRestReason(reasons) == AGENTBARERROR_SUCCESS)
					{
						for(acd::StringListT::iterator it = reasons.begin(); it != reasons.end(); it++)
						{
							m_cmbRest.AddString((*it).c_str());
						}
						if(m_cmbRest.GetCount() > 0)
							m_cmbRest.SetCurSel(0);
					}
				}
				else if(pAE->reason == acd::CallEventReasonT::CerIdleNormalSelfHangup 
					|| pAE->reason == acd::CallEventReasonT::CerIdleNormalOtherHangup
					|| pAE->reason == acd::CallEventReasonT::CerIdleErrorOtherHangup
					|| pAE->reason == acd::CallEventReasonT::CerIdleErrorSelfHangup )
				{
					KillTimer(TIMER_TALK);
				}
				m_intIsSignIn = TRUE;
				// 事件回调
				p_m_BarCtrl->OnReady(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsBusyState:
			{
				m_btnStatus.btnLogout = true;
				m_btnStatus.btnCallout = true;
				m_btnStatus.btnRest = true;
				m_btnStatus.btnReady = true;
				m_btnStatus.btnSkill = true;
				m_stcAgentState.SetStaticexText("呼出就绪");
				// 启动状态定时器、终止通话定时器
				if(pAE->reason == acd::CallEventReasonT::CerIdleSelfLogin || pAE->reason == acd::CallEventReasonT::CerIdleOtherLogin)
				{
					SetTimer(TIMER_STATUS, TIMESPAN_STATUS, NULL);
					m_thrd_heartbeat=bgcc::SharedPointer<bgcc::Thread>(new bgcc::Thread(bgcc::SharedPointer<HeartBeatTask>(new HeartBeatTask(this))));
					if(m_thrd_heartbeat.is_valid()){
						m_thrd_heartbeat->start();
					}
					m_lastStatusTime = CTime::GetCurrentTime();
					// 初始化休息原因
					m_cmbRest.ResetContent();
					acd::StringListT reasons;
					if(BGetRestReason(reasons) == AGENTBARERROR_SUCCESS)
					{
						for(acd::StringListT::iterator it = reasons.begin(); it != reasons.end(); it++)
						{
							m_cmbRest.AddString((*it).c_str());
						}
						if(m_cmbRest.GetCount() > 0)
							m_cmbRest.SetCurSel(0);
					}
				}
				else if(pAE->reason == acd::CallEventReasonT::CerIdleNormalSelfHangup 
					|| pAE->reason == acd::CallEventReasonT::CerIdleNormalOtherHangup
					|| pAE->reason == acd::CallEventReasonT::CerIdleErrorOtherHangup
					|| pAE->reason == acd::CallEventReasonT::CerIdleErrorSelfHangup )
				{
					KillTimer(TIMER_TALK);
				}
				m_intIsSignIn = TRUE;
				// 事件回调
				p_m_BarCtrl->OnBusy(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsRestState:
			{
				m_btnStatus.btnReady = true;
				m_btnStatus.btnBusy = true;
				m_stcAgentState.SetStaticexText("休息");
				// 事件回调
				p_m_BarCtrl->OnRest(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsLockState:
			{
				m_stcAgentState.SetStaticexText("预占");
				// 事件回调
				p_m_BarCtrl->OnLock(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsAlertingState:
			{
				// 原始主被叫
				m_callingNo = pAE->otherParty.c_str();
				m_orgCallingNo = pAE->originalAni.c_str();
				m_calledNo = pAE->agentDn.c_str();
				m_orgCalledNo = pAE->originalDnis.c_str();
				//
				if(m_intIsSIPPhone)		// xiangmao
				{
					m_btnStatus.btnAnswer = true;
					if(m_intAutoAnswer)
						BAnswer();
				}
				m_stcAgentState.SetStaticexText("振铃");
				// 事件回调
				p_m_BarCtrl->OnAlerting(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsHalfAlertingState:
			{
				if(m_intIsSIPPhone)		// xiangmao
				{
					m_btnStatus.btnAnswer = true;
					if(m_intAutoAnswer)
						BAnswer();
				}
				m_stcAgentState.SetStaticexText("半振铃");
				// 事件回调
				p_m_BarCtrl->OnHarfAlerting(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsConnectingState:
			{
				// 原始主被叫
				m_callingNo = pAE->agentDn.c_str();
				m_orgCallingNo = pAE->originalAni.c_str();
				m_calledNo = pAE->otherParty.c_str();
				m_orgCalledNo = pAE->originalDnis.c_str();
				//
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("呼出中");
				// 事件回调
				p_m_BarCtrl->OnConnecting(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsConnectedState:
			{
				// 原始主被叫
				m_btnStatus.btnSenddtmf = true;
				m_btnStatus.btnHangup = true;
				m_btnStatus.btnHold = true;
				m_btnStatus.btnConsult = true;
				m_btnStatus.btnSSTransfer = true;
				m_stcAgentState.SetStaticexText("通话");
				// 开始通话定时器
				if(pAE->reason == acd::CallEventReasonT::CerTalkSelfCreat || pAE->reason == acd::CallEventReasonT::CerTalkOtherCreat)
				{
					SetTimer(TIMER_TALK, TIMESPAN_TALK, NULL);
					m_beginTalkTime = CTime::GetCurrentTime();
					m_lastTalkTime = m_beginTalkTime;
				}
				// 事件回调
				p_m_BarCtrl->OnConnected(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsHalfConnectedState:
			{
				m_stcAgentState.SetStaticexText("半通话");
				// 事件回调
				p_m_BarCtrl->OnHarfConnected(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsInternalConnectedState:
			{
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("内部通话");
				// 开始通话定时器
				if(pAE->reason == acd::CallEventReasonT::CerTalkSelfCreat || pAE->reason == acd::CallEventReasonT::CerTalkOtherCreat)
				{
					SetTimer(TIMER_TALK, TIMESPAN_TALK, NULL);
					m_beginTalkTime = CTime::GetCurrentTime();
					m_lastTalkTime = m_beginTalkTime;
				}
				// 事件回调
				p_m_BarCtrl->OnInternalConnected(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsSuspendedState:
			{
				m_btnStatus.btnRetrieve = true;
				m_stcAgentState.SetStaticexText("保持");
				// 事件回调
				p_m_BarCtrl->OnSuspended(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsConsultConnectingState:
			{
				m_btnStatus.btnReconnect = true;
				m_stcAgentState.SetStaticexText("咨询");
				// 事件回调
				p_m_BarCtrl->OnConsultConnecting(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsConsultConnectedState:
			{
				m_btnStatus.btnReconnect = true;
				m_btnStatus.btnTransfer = true;
				m_btnStatus.btnConference = true;
				m_stcAgentState.SetStaticexText("咨询通话");
				// 事件回调
				p_m_BarCtrl->OnConsultConnected(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsConferenceState:
			{
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("会议");
				// 事件回调
				p_m_BarCtrl->OnConference(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsMonitorState:
			{
				// 原始主被叫
				m_callingNo = pAE->agentDn.c_str();
				m_orgCallingNo = pAE->originalAni.c_str();
				m_calledNo = pAE->otherParty.c_str();
				m_orgCalledNo = pAE->originalDnis.c_str();
				//
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("监听");
				// 启动通话定时器
				SetTimer(TIMER_TALK, TIMESPAN_TALK, NULL);
				m_beginTalkTime = CTime::GetCurrentTime();
				m_lastTalkTime = m_beginTalkTime;
				// 事件回调
				p_m_BarCtrl->OnMonitor(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsInsertState:
			{
				// 原始主被叫
				m_callingNo = pAE->agentDn.c_str();
				m_orgCallingNo = pAE->originalAni.c_str();
				m_calledNo = pAE->otherParty.c_str();
				m_orgCalledNo = pAE->originalDnis.c_str();
				//
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("强插");
				// 启动通话定时器
				SetTimer(TIMER_TALK, TIMESPAN_TALK, NULL);
				m_beginTalkTime = CTime::GetCurrentTime();
				m_lastTalkTime = m_beginTalkTime;
				// 事件回调
				p_m_BarCtrl->OnInsert(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsMonitoredState:
			{
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("被监听");
				// 事件回调
				p_m_BarCtrl->OnMonitored(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		case acd::AgentStatusT::AsInsertedState:
			{
				m_btnStatus.btnHangup = true;
				m_stcAgentState.SetStaticexText("被强插");
				// 事件回调
				p_m_BarCtrl->OnInserted(pAE->eventId.get_value(), pAE->callId.c_str(), pAE->sessionId, pAE->partyNum, pAE->otherParty.c_str(), pAE->otherAttr.get_value(), 
					pAE->originatingParty.c_str(), pAE->originalAni.c_str(), pAE->originalDnis.c_str(), pAE->reason.get_value(), pAE->timestamp);
				break;
			}
		default:
			{
				m_stcAgentState.SetStaticexText("错误状态");
				break;
			}
		}
	}
	catch(...)
	{
		Tool::m_Logger.WriteLog("CCCBar", "OnAgentEvent", "catch Error", AGENTBARERROR_BAR_OUTEVENTERROR);
	}

	SetButton();
	m_stcAgentState.Invalidate();
    p_m_BarCtrl->OnBtnStatus(m_btnStatus.StatusAsLonglong(), m_stcAgentState.GetStaticexText());  // 通知状态改变

	m_lastBtnStatus = m_btnStatus;

	delete pAE;
	return 0;
}

LRESULT CCCBar::OnMediaEvent(WPARAM wParam, LPARAM lParam)
{
	LONGLONG address = MAKELONGLONG(wParam, lParam);
	acd::MediaEventT *pME = reinterpret_cast<acd::MediaEventT *>(address);
	Tool::WriteMediaEventLog(pME, "out");

	try
	{
		switch(pME->eventType.get_value())
		{
		case acd::MediaEventTypeT::MeUnKownEvent:
			break;
		case acd::MediaEventTypeT::MeTpRecordStarted:
			p_m_BarCtrl->OnBeginRecord(pME->callId.c_str(), pME->sessionId, pME->buffer.c_str(), pME->reason.get_value(), pME->timestamp);
			break;
		case acd::MediaEventTypeT::MeTpRecordDone:
			p_m_BarCtrl->OnEndRecord(pME->callId.c_str(), pME->sessionId, pME->buffer.c_str(), pME->reason.get_value(), pME->timestamp);
			break;
		default:
			break;
		}
	}
	catch(...)
	{
		Tool::m_Logger.WriteLog("CCCBar", "OnMediaEvent", "catch Error", AGENTBARERROR_BAR_OUTEVENTERROR);
	}

	delete pME;
	return 0;
}

LRESULT CCCBar::OnRouteEvent(WPARAM wParam, LPARAM lParam)
{
	LONGLONG address = MAKELONGLONG(wParam, lParam);
	acd::RouteEventT *pQE = reinterpret_cast<acd::RouteEventT *>(address);
	Tool::WriteRouteEventLog(pQE, "out");

	try
	{
		switch(pQE->eventType.get_value())
		{
		case acd::RouteEventTypeT::ReInQueue:
			p_m_BarCtrl->OnInprivatequeue(pQE->callId.c_str(), pQE->sessionId, pQE->requestId, pQE->originalAni.c_str(), pQE->originalDnis.c_str(), 0, pQE->timestamp);
			break;
		case acd::RouteEventTypeT::ReOutQueue:
			p_m_BarCtrl->OnOutprivatequeue(pQE->callId.c_str(), pQE->sessionId, pQE->requestId, pQE->originalAni.c_str(), pQE->originalDnis.c_str(), 0, pQE->timestamp);
			break;
		default:
			break;
		}
	}
	catch(...)
	{
		Tool::m_Logger.WriteLog("CCCBar", "OnRouteEvent", "catch Error", AGENTBARERROR_BAR_OUTEVENTERROR);
	}

	delete pQE;
	return 0;
}

LRESULT CCCBar::OnOtherEvent(WPARAM wParam, LPARAM lParam)
{
	LONGLONG address = MAKELONGLONG(wParam, lParam);
	acd::OtherEventT *pOE = reinterpret_cast<acd::OtherEventT *>(address);
	Tool::WriteOtherEventLog(pOE, "out");

	try
	{
		switch(pOE->eventType.get_value())
		{
		case acd::OtherEventTypeT::IMSDisconnect:
			{
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "IMS Disconnect", EVENTREASON_IMS_DISCONNECT);
				p_m_BarCtrl->OnCTIDisconnect(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_IMS_DISCONNECT, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::IMSMasterChange:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "IMS主备倒换完成！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "IMS MasterChange", EVENTREASON_IMS_MASTERCHANGE);
				p_m_BarCtrl->OnCTIMasterChanged(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_IMS_MASTERCHANGE, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::IMSOperationFailed:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "本方未应答！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "IMS OperationFailed", EVENTREASON_IMS_OPERATIONFAILED);
				p_m_BarCtrl->OnOperationFailed(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_IMS_OPERATIONFAILED, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::ACDDisconnect:
			{
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "ACD Disconnect", EVENTREASON_ACD_DISCONNECT);
				p_m_BarCtrl->OnCTIDisconnect(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_ACD_DISCONNECT, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::ACDMasterChange:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "ACD主备倒换完成！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "ACD MasterChange", EVENTREASON_ACD_MASTERCHANGE);
				p_m_BarCtrl->OnCTIMasterChanged(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_ACD_MASTERCHANGE, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::ACDOperationFailed:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "网络或者ACD服务异常！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "ACD OperationFailed", EVENTREASON_ACD_OPERATIONFAILED);
				p_m_BarCtrl->OnOperationFailed(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_ACD_OPERATIONFAILED, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::ACDReLoginSuccess:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "ACD重签成功！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "ACD ReLoginSuccess", EVENTREASON_ACD_RELOGINSUCCESS);
				p_m_BarCtrl->OnCTIMasterChanged(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_ACD_RELOGINSUCCESS, pOE->timestamp);
				break;
			}
		case acd::OtherEventTypeT::ACDReLoginFailed:
			{
				CInfo info;
				info.SetInfo(IDI_ICON_INFOMATION, "ACD重签失败！");
				info.DoModal();
				Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "ACD ReLoginFailed", EVENTREASON_ACD_RELOGINFAILED);
				p_m_BarCtrl->OnOperationFailed(pOE->callId.c_str(), pOE->sessionId, pOE->originalAni.c_str(), pOE->originalDnis.c_str(), EVENTREASON_ACD_RELOGINFAILED, pOE->timestamp);
				break;
			}
		default:
			break;
		}
	}
	catch(...)
	{
		Tool::m_Logger.WriteLog("CCCBar", "OnOtherEvent", "catch Error", AGENTBARERROR_BAR_OUTEVENTERROR);
	}

	delete pOE;
	return 0;
}

LONG CCCBar::BInitial()
{
	Tool::m_Logger.SetLogLevel(m_intLogLevel);

	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsUnknownState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BInitial", "Status Error", ret);
	}
	else
	{
		if(m_intIsSIPPhone)
		{
			ret = m_sip.SipInitial();
			if(ret != AGENTBARERROR_SUCCESS)
				return ret;
		}

		ret = m_acd.AcdInitial(m_strMainCTIIP, m_strBackCTIIP, m_intCTIPort);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_btnStatus.btnLogin = true;
			SetButton();

			m_AgentStatus = acd::AgentStatusT::AsUnLoginState;
			m_intIsInitial = TRUE;

			m_lastBtnStatus = m_btnStatus;
		}
	}
	return ret;
}

LONG CCCBar::BUnInitial()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BUnInitial", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdUnInitial();
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_btnStatus.Reset();
			SetButton();

			m_AgentStatus = acd::AgentStatusT::AsUnknownState;
			m_intIsInitial = FALSE;

			m_lastBtnStatus.Reset();
		}
		else
		{
			return ret;
		}

		if(m_intIsSIPPhone)
		{
			ret = m_sip.SipUnInitial();
		}
	}
	return ret;
}

LONG CCCBar::BSignIn()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSignIn", "Status Error", ret);
	}
	else
	{
		m_lDetaTime = 0;
		if(m_intIsSIPPhone)
		{
			ret = m_sip.SipRegister(m_strSIPServerIP, m_intSIPServerPort, m_strPhoneNum, m_strPhonePwd, m_intTimeOut);
			if(ret != AGENTBARERROR_SUCCESS)
				return ret;
		}

		// 尝试主
		ret = m_acd.AcdSignIn(m_strAgentID, m_strDN, m_strPassWord, m_intStatusChangeType, !!m_intAutoAnswer, !!m_intForceSignIn, m_strServiceList);
		if(ret == AGENTBARERROR_BGCC_EXCEPTION || ret == acd::AcdResultT::ArNotMaster)// 主故障
		{
			// 尝试备
			m_acd.AcdBackup();
			ret = m_acd.AcdSignIn(m_strAgentID, m_strDN, m_strPassWord, m_intStatusChangeType, !!m_intAutoAnswer, !!m_intForceSignIn, m_strServiceList);
		}
		
		if(AGENTBARERROR_SUCCESS == ret)
		{
			LONGLONG timestamp = 0;
			DWORD start_call = GetTickCount();
			ret = m_acd.AcdSynchronizeCTITime(m_strAgentID, timestamp);
			DWORD end_call = GetTickCount();
			if(AGENTBARERROR_SUCCESS == ret)
			{
				m_lDetaTime = timestamp - static_cast<LONGLONG>(start_call) * 1000 - (static_cast<LONGLONG>(end_call) - static_cast<LONGLONG>(start_call)) * 1000 / 2;
			}
			Tool::m_Logger.WriteLog(Level_High, "[CCCBar-BSignIn] [out] datetime:%I64d", m_lDetaTime);
		}
	}
	return ret;
}

LONG CCCBar::BSignOut()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSignOut", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSignOut(m_strAgentID);
		if(ret != AGENTBARERROR_SUCCESS)
		{
			return ret;
		}

		if(m_intIsSIPPhone)
		{
			ret = m_sip.SipUnRegister();
		}
	}
	return ret;
}

LONG CCCBar::BSetIdle()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsBusyState && m_AgentStatus != acd::AgentStatusT::AsRestState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSetIdle", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSetAgentStatus(m_strAgentID, acd::AgentStatusT::AsReadyState);
	}
	return ret;
}

LONG CCCBar::BSetBusy()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsRestState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSetBusy", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSetAgentStatus(m_strAgentID, acd::AgentStatusT::AsBusyState);
	}
	return ret;
}

LONG CCCBar::BSetRest(const char *reason)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSetRest", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSetAgentStatus(m_strAgentID, acd::AgentStatusT::AsRestState, reason);
	}
	return ret;
}

LONG CCCBar::BGetAgentStatus(acd::AgentStatusT &agentStatus)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BGetAgentStatus", "Status Error", ret);
	}
	else
	{
		agentStatus = m_AgentStatus;
	}
	return ret;
}

LONG CCCBar::BResetSkill(const char *skillList)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BResetSkill", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdResetSkill(m_strAgentID, skillList);
	}
	return ret;
}

LONG CCCBar::BReset()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BReset", "Status Error", ret);
	}
	else
	{
		// 挂断、签出
		ret = m_acd.AcdReset(m_strAgentID);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			// 签出坐席
			PostMessageEx(acd::AgentStatusT::AsUnLoginState, acd::CallEventReasonT::CerUnloginSelfForceout);
		}
		else
		{
			return ret;
		}

		if(m_intIsSIPPhone)
		{
			ret = m_sip.SipUnRegister();
		}
	}
	return ret;
}

LONG CCCBar::BMakeCall(const char *dest, const char *showANI, const char *showDest, acd::CallModeT callMode, acd::CallTypeT callType)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BMakeCall", "Status Error", ret);
	}
	else
	{
		CString callerId;
		switch(callType.get_value())
		{
		case acd::CallTypeT::CtAgent:
			callerId = m_strAgentTag + m_strDN;
			break;
		case acd::CallTypeT::CtOut:
			callerId = m_strDN;
			break;
		default:
			callerId = m_strDN;
			break;
		}
		ret = m_acd.AcdOutboundCall(m_strAgentID, callerId, dest, showANI, showDest, m_intTimeOut, callMode, callType);
	}
	return ret;
}

LONG CCCBar::BAnswer()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsAlertingState && m_AgentStatus != acd::AgentStatusT::AsHalfAlertingState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BAnswer", "Status Error", ret);
	}
	else
	{
		if(m_intIsSIPPhone)		// suxiangmao
		{
			ret = m_sip.SipAnswercall();
		}
		else
		{
			ret = AGENTBARERROR_BAR_ANSWERERROR;
		}
	}
	return ret;
}

LONG CCCBar::BReleaseCall()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BReleaseCall", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdReleaseCall(m_strAgentID);
	}
	return ret;
}

LONG CCCBar::BHold()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BHold", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdHold(m_strAgentID);
	}
	return ret;
}

LONG CCCBar::BRetrieve()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsSuspendedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BRetrieve", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdRetrieve(m_strAgentID);
	}	
	return ret;
}

LONG CCCBar::BConsult(const char *consultNum, const char *showANI, const char *showDest, acd::CallTypeT callType)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BConsult", "Status Error", ret);
	}
	else
	{
		CString callerId;
		switch(callType.get_value())
		{
		case acd::CallTypeT::CtAgent:
			callerId = m_strAgentTag + m_strDN;
			break;
		case acd::CallTypeT::CtOut:
			callerId = m_strDN;
			break;
		default:
			callerId = m_strDN;
			break;
		}
		ret = m_acd.AcdConsult(m_strAgentID, callerId, consultNum, showANI, showDest, callType);
	}
	return ret;
}

LONG CCCBar::BReconnect()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConsultConnectingState && m_AgentStatus != acd::AgentStatusT::AsConsultConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BReconnect", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdConsultReconnect(m_strAgentID);
	}
	return ret;
}

LONG CCCBar::BTransfer()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConsultConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BTransfer", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdConsultTransfer(m_strAgentID);
	}
	return ret;
}

LONG CCCBar::BSingleStepTransfer(const char *transferNum, const char *showANI, const char *showDest, BOOL transferStyle, acd::CallTypeT callType)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSingleStepTransfer", "Status Error", ret);
	}
	else
	{
		CString callerId;
		switch(callType.get_value())
		{
		case acd::CallTypeT::CtAgent:
			callerId = m_strAgentTag + m_strDN;
			break;
		case acd::CallTypeT::CtOut:
			callerId = m_strDN;
			break;
		default:
			callerId = m_strDN;
			break;
		}
		ret = m_acd.AcdSingleStepTransfer(m_strAgentID, callerId, transferNum, showANI, showDest, !!transferStyle, callType);
	}
	return ret;
}

LONG CCCBar::BConference()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConsultConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BConference", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdConsultConference(m_strAgentID);
	}
	return ret;
}

LONG CCCBar::BListen(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BListen", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdListen(m_strAgentID, m_strAgentTag + m_strDN, destAgentId, forCallerDispNum, forCalleeDispNum);
	}
	return ret;
}

LONG CCCBar::BStopListen(const char *destAgentId)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsMonitorState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BStopListen", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdStopListen(m_strAgentID, destAgentId);
	}
	return ret;
}

LONG CCCBar::BInsert(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsReadyState && m_AgentStatus != acd::AgentStatusT::AsBusyState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BInsert", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdInsert(m_strAgentID, m_strAgentTag + m_strDN, destAgentId, forCallerDispNum, forCalleeDispNum);
	}
	return ret;
}

LONG CCCBar::BStopInsert(const char *destAgentId)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsInsertState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BStopInsert", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdStopInsert(m_strAgentID, destAgentId);
	}
	return ret;
}

LONG CCCBar::BSwitchInsertorListen(const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsMonitorState && m_AgentStatus != acd::AgentStatusT::AsInsertState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSwitchInsertorListen", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSwitchInsertorListen(m_strAgentID, m_strAgentTag + m_strDN, destAgentId, forCallerDispNum, forCalleeDispNum);
	}
	return ret;
}

LONG CCCBar::BSendDTMF(const char *digitals)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConnectedState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSendDTMF", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdSendDTMF(m_strAgentID, digitals);
	}
	return ret;
}

LONG CCCBar::BGetRestReason(acd::StringListT &restReason)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BGetRestReason", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdGetRestReason(m_strAgentID, restReason);
	}
	return ret;
}

LONG CCCBar::BSynchronizeCTITime()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BSynchronizeCTITime", "Status Error", ret);
	}
	else
	{
		LONGLONG timestamp = 0;
		ret = m_acd.AcdSynchronizeCTITime(m_strAgentID, timestamp);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			// 获取当前时间
			CTime serverTime(timestamp / 1000000);
			CTimeSpan timeSpan = serverTime - CTime::GetCurrentTime();
			// 设置本地时间
			SYSTEMTIME systemTime;
			serverTime.GetAsSystemTime(systemTime);
			SetLocalTime(&systemTime);
			// 重置时间
			if(m_beginStatusTime.GetTime() != 0)
				m_beginStatusTime += timeSpan;
			if(m_beginTalkTime.GetTime() != 0)
				m_beginTalkTime += timeSpan;
			if(m_lastStatusTime.GetTime() != 0)
				m_lastStatusTime += timeSpan;
			if(m_lastTalkTime.GetTime() != 0)
				m_lastTalkTime += timeSpan;
		}
	}
	return ret;
}

LONG CCCBar::BHeartbeat()
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus == acd::AgentStatusT::AsUnknownState || m_AgentStatus == acd::AgentStatusT::AsUnLoginState)
	{
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BHeartbeat", "Status Error", ret);
	}
	else
	{
		ret = m_acd.AcdHeartbeat(m_strAgentID);
		if(ret == AGENTBARERROR_SUCCESS)
		{
			m_heartbeatCount = 0;
            // 通知心跳成功
            LONGLONG timestamp = 0;
            if(!m_lDetaTime)
            {
                timestamp = CTime::GetCurrentTime().GetTime() * 1000000;
            }
            else
            {
                timestamp = static_cast<LONGLONG>(GetTickCount()) * 1000 + m_lDetaTime;
            }
            p_m_BarCtrl->OnHeartbeat(timestamp);
		}
		else if(ret == acd::AcdResultT::ArNotMaster)
		{
			m_heartbeatCount = 0;
			// 倒换
			Backup();
		}
		else if(ret == acd::AcdResultT::ArNoSignin)
		{
			m_heartbeatCount = 0;
			// 重签
			ReSignIn();
		}
		else
		{
			m_heartbeatCount++;
		}
		if(m_heartbeatCount == TIMES_HEARTBEAT_EXCEPTION)
		{
			m_heartbeatCount = 0;
			// 倒换
			Backup();
		}
	}
	return ret;
}

AcdClient &CCCBar::GetAcdClient()
{
	return m_acd;
}

// suxiangmao
SipphoneClient &CCCBar::GetSipphoneClient()
{
	return m_sip;
}

LONG CCCBar::BTransferIVR(const char *transferNum, const char *callerNum)
{
	LONG ret = AGENTBARERROR_SUCCESS;
	if(m_AgentStatus != acd::AgentStatusT::AsConnectedState){
		ret = AGENTBARERROR_BAR_WRONGSTATE;
		Tool::m_Logger.WriteLog("CCCBar", "BTransferIVR", "Status Error", ret);
	}
	else{
		ret = m_acd.AcdSingleStepTransfer(m_strAgentID, m_strCustomerTag + m_strDN, transferNum, 
			(callerNum?callerNum:m_strActiveCallID.c_str()), (callerNum?callerNum:m_strActiveCallID.c_str()), false, acd::CallTypeT::CtOut);
	}
	return ret;	
}

int32_t HeartBeatTask::operator()(const bool *isstopped, void *param)
{
	int32_t time_count=100;

	if(!m_bar){
		return -1;
	}

	while(!(*isstopped)){
		m_bar->BHeartbeat();

		time_count=100;
		while(!(*isstopped)&&(time_count--)){
			bgcc::TimeUtil::safe_sleep_ms(100);
		}
	}

	return 0;
}
