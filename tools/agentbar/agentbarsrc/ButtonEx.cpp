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

#include "ButtonEx.h"
#include "ImgMgr.h"

CButtonEx::CButtonEx()
{
	m_bIsDefault = FALSE;
	m_bOver = m_bSelected = m_bTracking = FALSE;
	m_BrushBk.CreateSolidBrush(RGB(240,240,240));
}

CButtonEx::~CButtonEx()
{
}

void CButtonEx::TransparentBlt(HDC hdcDest,		// 目标DC
					 int nXOriginDest,			// 目标X偏移
					 int nYOriginDest,			// 目标Y偏移
					 int nWidthDest,			// 目标宽度
					 int nHeightDest,			// 目标高度
					 HDC hdcSrc,				// 源DC
					 int nXOriginSrc,			// 源X起点
					 int nYOriginSrc,			// 源Y起点
					 int nWidthSrc,				// 源宽度
					 int nHeightSrc,			// 源高度
					 UINT crTransparent)
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	// 还原DC的默认状态
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}

// 添加Owner Draw属性
void CButtonEx::PreSubclassWindow()
{
	// 修改按钮自绘属性
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();

	if (m_nTypeStyle == BS_DEFPUSHBUTTON)
	{
		m_nTypeStyle = BS_PUSHBUTTON;
	}
}

void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 从lpDrawItemStruct获取控件的相关信息
	CBitmap *pBit = CImgMgr::Instance().Get(m_bOver ? m_nIDBmpHover : m_nIDBmpDefault);
	if(pBit == NULL)
		return;

	CRect rect = lpDrawItemStruct->rcItem;
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);			// 获得按钮的DC
	int nSaveDC = pDC->SaveDC();

	BITMAP bit;
	pBit->GetBitmap(&bit);
	rect.left = 0;
	rect.right = bit.bmWidth;
	rect.top = 0;
	rect.bottom = bit.bmHeight;
	MoveWindow(m_btPX, m_btPY, rect.Width(), rect.Height());	// 设置按钮的大小为位图的大小
	DrawButton(pDC, *pBit, &rect);
	pDC->RestoreDC(nSaveDC);									// 恢复按钮DC为初始状态
}

// 在按钮上绘制透明的位图
void CButtonEx::DrawButton(CDC *pDC, CBitmap &bitmap, CRect *rect)
{
	COLORREF crMask = RGB(255,255,255);
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	int nWidth = bm.bmWidth;
	int nHeight = bm.bmHeight;
	CDC ImageDC;
	ImageDC.CreateCompatibleDC(pDC);																						// 创建一个与按钮DC相兼容位图DC
	CBitmap *pOldImageBMP = ImageDC.SelectObject(&bitmap);																	// 将位图选入位图DC
	TransparentBlt(pDC->m_hDC,0, 0, rect->Width(), rect->Height(),ImageDC.m_hDC,0,0,rect->Width(), rect->Height(),crMask);	// 绘制透明位图
	ImageDC.SelectObject(pOldImageBMP);																						// 恢复位图DC的初始状态
}

BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_ERASEBKGND()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_GETDLGCODE()
	ON_MESSAGE(BM_SETSTYLE, OnSetStyle)
END_MESSAGE_MAP()

void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		// 鼠标第一次移入窗口时， 请求一个WM_MOUSELEAVE 消息
		TRACKMOUSEEVENT tme;

		tme.cbSize = sizeof(tme);

		tme.hwndTrack = m_hWnd;

		tme.dwFlags = TME_LEAVE;

		_TrackMouseEvent(&tme);
		m_bTracking = TRUE;
		if (!m_bOver)
		{
			m_bOver = TRUE;
			Invalidate(FALSE);
		}
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnMouseMove(nFlags, point);
}

// 鼠标离开消息处理函数
LRESULT CButtonEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking = false;
	m_bOver = FALSE;

	Invalidate(false);

	return TRUE;
}

// 自绘按钮底色
BOOL CButtonEx::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush * pOldBrush = pDC->SelectObject(&m_BrushBk);
	pDC->FillRect(&rect,&m_BrushBk);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}

BOOL CButtonEx::OnClicked() 
{
	m_bSelected = true;
	return FALSE;
}

// 设置默认状态风格
UINT CButtonEx::OnGetDlgCode()
{
	UINT nCode = CButton::OnGetDlgCode();
	nCode |= (1 ? DLGC_DEFPUSHBUTTON : DLGC_UNDEFPUSHBUTTON);

	return nCode;
}

LRESULT CButtonEx::OnSetStyle(WPARAM wParam, LPARAM lParam)
{
	UINT nNewType = (UNIT)(wParam & BS_TYPEMASK);

	// 更新默认状态风格
	if(nNewType == BS_DEFPUSHBUTTON)
	{
		m_bIsDefault = TRUE;
	}
	else if(nNewType == BS_PUSHBUTTON)
	{
		m_bIsDefault = FALSE;
	}

	return DefWindowProc(BM_SETSTYLE, (wParam & ~BS_TYPEMASK) | BS_OWNERDRAW, lParam);
}

// 设置按钮的默认位图和鼠标移到按钮上的位图
void CButtonEx::SetBitMap(int nIDBmpDefault, int nIDBmpHover)
{
	m_nIDBmpDefault = nIDBmpDefault;
	m_nIDBmpHover = nIDBmpHover;
}

// 设置按钮在父窗口的坐标位置
void CButtonEx::SetButtonPos(int bx, int by)
{
	m_btPX = bx;
	m_btPY = by;
}
