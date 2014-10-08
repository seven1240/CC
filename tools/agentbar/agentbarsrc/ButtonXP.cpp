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

#include "ButtonXP.h"

CButtonXP::CButtonXP()
{
	m_BoundryPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(0, 0, 0));
	m_InsideBoundryPenLeft.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(250, 196, 88)); 
	m_InsideBoundryPenRight.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(251, 202, 106));
	m_InsideBoundryPenTop.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(252, 210, 121));
	m_InsideBoundryPenBottom.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(229, 151, 0));

	m_FillActive.CreateSolidBrush(RGB(223, 222, 236));
	m_FillInactive.CreateSolidBrush(RGB(222, 223, 236));

	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(153, 198, 252)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 3, RGB(162, 189, 252));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 2, RGB(162, 201, 255));
	m_bIsDefault = FALSE;
	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
}

CButtonXP::~CButtonXP()
{
	m_BoundryPen.DeleteObject();
	m_InsideBoundryPenLeft.DeleteObject();
	m_InsideBoundryPenRight.DeleteObject();
	m_InsideBoundryPenTop.DeleteObject();
	m_InsideBoundryPenBottom.DeleteObject();

	m_FillActive.DeleteObject();
	m_FillInactive.DeleteObject();

	m_InsideBoundryPenLeftSel.DeleteObject();
	m_InsideBoundryPenTopSel.DeleteObject();
	m_InsideBoundryPenRightSel.DeleteObject();
	m_InsideBoundryPenBottomSel.DeleteObject();
}

//添加Owner Draw属性
void CButtonXP::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();

	// Set initial default state flag
	if(m_nTypeStyle == BS_DEFPUSHBUTTON)
	{
		m_nTypeStyle = BS_PUSHBUTTON;
	} 

	//设置按钮的有效区域
	CRgn rgn;
	CRect rc;
	GetClientRect(&rc);

	//有效区域为一个角半径为5的圆角矩形
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5);

	SetWindowRgn(rgn, TRUE);

	rgn.DeleteObject();
}

void CButtonXP::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//从lpDrawItemStruct获取控件的相关信息
	CRect rect =  lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC = pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	TCHAR strText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strText, MAX_PATH);

	//画按钮的外边框，它是一个半径为5的圆角矩形
	pt.x = 5;
	pt.y = 5;
	CPen* hOldPen = pDC->SelectObject(&m_BoundryPen);
	pDC->RoundRect(&rect, pt);

	//获取按钮的状态
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}

	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}

	pDC->SelectObject(hOldPen);

	rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));

	//根据按钮的状态填充按钮的底色
	CBrush* pOldBrush;
	if (m_bOver)
	{
		pOldBrush = pDC->SelectObject(&m_FillActive);
		DoGradientFill(pDC, &rect);
	}
	else
	{
		pOldBrush = pDC->SelectObject(&m_FillInactive);
		DoGradientFill(pDC, &rect);
	}

	//根据按钮的状态绘制内边框
	if (m_bOver || m_bSelected)
		DrawInsideBorder(pDC, &rect);

	pDC->SelectObject(pOldBrush);

	//显示按钮的文本
	if (strText!=NULL)
	{
		CFont* hFont = GetFont();
		CFont* hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(strText, lstrlen(strText));
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = pDC->SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			pDC->DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
			pDC->DrawState(pt, szExtent, strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
	}

	pDC->RestoreDC(nSaveDC);
}

//绘制按钮的底色
void CButtonXP::DoGradientFill(CDC *pDC, CRect* rect)
{
	CBrush brBk[64];
	int nWidth = rect->Width();	
	int nHeight = rect->Height();
	CRect rct;

	int i = 0;
	for ( i = 0; i < 64; i ++)
	{
		if (m_bOver)
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}

	for (i = rect->top; i <= nHeight + 2; i ++) 
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		pDC->FillRect(&rct, &brBk[((i * 63) / nHeight)]);
	}

	for (i = 0; i < 64; i ++)
		brBk[i].DeleteObject();
}

//绘制按钮的内边框
void CButtonXP::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	CPen *pLeft, *pRight, *pTop, *pBottom;

	if (m_bSelected && !m_bOver)
	{
		pLeft = & m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		pLeft = &m_InsideBoundryPenLeft;
		pRight = &m_InsideBoundryPenRight;
		pTop = &m_InsideBoundryPenTop;
		pBottom = &m_InsideBoundryPenBottom;
	}

	CPoint oldPoint = pDC->MoveTo(rect->left, rect->bottom - 1);
	CPen* pOldPen = pDC->SelectObject(pLeft);
	pDC->LineTo(rect->left, rect->top + 1);
	pDC->SelectObject(pRight);
	pDC->MoveTo(rect->right - 1, rect->bottom - 1);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pTop);
	pDC->MoveTo(rect->left - 1, rect->top);
	pDC->LineTo(rect->right - 1, rect->top);
	pDC->SelectObject(pBottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right - 1, rect->bottom);
	pDC->SelectObject(pOldPen);
	pDC->MoveTo(oldPoint);

	if (m_bSelected && !m_bOver)
		DrawFocusRect(pDC->m_hDC,rect);
}

BEGIN_MESSAGE_MAP(CButtonXP, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_GETDLGCODE()
	ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
END_MESSAGE_MAP()

void CButtonXP::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if(!m_bTracking)//是否要监视鼠标
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = m_hWnd;
        tme.dwFlags = TME_LEAVE | TME_HOVER; //设置要监听的事件
        tme.dwHoverTime = 1; //设置监视的间隔时间
        m_bTracking = _TrackMouseEvent(&tme);
    }

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CButtonXP::OnMouseLeave(WPARAM wParam, LPARAM lParam) //鼠标离开消息处理函数
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CButtonXP::OnMouseHover(WPARAM wParam, LPARAM lParam)//鼠标在按钮上的消息处理函数
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}

BOOL CButtonXP::OnEraseBkgnd(CDC* pDC) 
{
	// 禁止自动绘制底色
	return TRUE;
}

BOOL CButtonXP::OnClicked() 
{
	SetFocus();
	return FALSE;
}

UINT CButtonXP::OnGetDlgCode() 
{
	UINT nCode = CButton::OnGetDlgCode();
	nCode |= (1 ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);

	return nCode;
}

LRESULT CButtonXP::OnSetStyle(WPARAM wParam, LPARAM lParam)
{
	UINT nNewType = (UINT)(wParam & MY_BS_TYPEMASK);

	if(nNewType == BS_DEFPUSHBUTTON)
	{
		m_bIsDefault = TRUE;
	}
	else if(nNewType == BS_PUSHBUTTON)
	{
		m_bIsDefault = FALSE;
	}

	return DefWindowProc(BM_SETSTYLE, (wParam & ~MY_BS_TYPEMASK) | BS_OWNERDRAW, lParam);
}
