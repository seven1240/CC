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

#include "StaticEx.h"

CStaticEx::CStaticEx()
{
}

CStaticEx::~CStaticEx()
{
}

void CStaticEx::PreSubclassWindow() 
{
	// 修改风格为自绘
	ModifyStyle(0, BS_OWNERDRAW);
	CStatic::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
ON_WM_ERASEBKGND()
ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CStaticEx::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

void CStaticEx::OnPaint() 
{
    CPaintDC dc(this); 
        
	m_font.CreatePointFont(m_Fontsize, m_FontFacename);	// 创建自定义的文字
	CFont *pOldFont = dc.SelectObject(&m_font);
	CSize sz = dc.GetTextExtent(m_WindowText);			// 获得文字的长度以便改变Static控件的大小
	m_brush.CreateSolidBrush(m_bkColor);				// 创建背景画刷
	CRect rect;
	rect.left = m_nptx;
	rect.top  = m_npty;
	rect.right = rect.left + m_nLen;
	rect.bottom = rect.top + sz.cy;
	MoveWindow(&rect);
	GetClientRect(&rect);
	CBrush * pOldBrush = dc.SelectObject(&m_brush);
	dc.FillRect(&rect,&m_brush);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_textColor);

	int n = m_nLen - sz.cx;
	n >>= 1;
	dc.TextOut(rect.left + n, rect.top, m_WindowText);	// 文字显示

	dc.SelectObject(pOldFont);							// 还原DC为默认状态
	dc.SelectObject(pOldBrush);
	m_brush.DeleteObject();								// 删除资源对象
	m_font.DeleteObject();
}

void CStaticEx::SetFont(int nSize, const char *strFaceName)
{
	// 设置字体
    m_Fontsize = nSize;
	m_FontFacename = strFaceName;
}

void CStaticEx::SetColor(COLORREF bkColor, COLORREF textColor)
{
	// 设置文字的背景色和前景色
    m_bkColor = bkColor; 
	m_textColor = textColor;
}

void CStaticEx::SetWindowpos(int nx, int ny)
{
    m_nptx = nx;
	m_npty = ny;
}

void CStaticEx::SetStaticexText(const char *strtext)
{
	m_WindowText = strtext;
}

CString &CStaticEx::GetStaticexText()
{
    return m_WindowText;
}

void CStaticEx::SetWidth(int len)
{
	m_nLen = len;
}
