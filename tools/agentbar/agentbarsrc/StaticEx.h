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

#pragma once

#include "stdafx.h"

class CStaticEx : public CStatic
{
private:
	CBrush m_brush;
	COLORREF m_bkColor;
	COLORREF m_textColor;
    int m_nptx;
	int m_npty;
	CFont m_font;
	int m_Fontsize;
	CString m_FontFacename;
	CString m_WindowText;
	int m_nLen;

public:
	CStaticEx();
	virtual ~CStaticEx();

protected:
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnPaint();

public:
	void SetFont(int nSize, const char *strFaceName);
	void SetColor(COLORREF bkColor, COLORREF textColor);
	void SetWindowpos(int nx, int ny);
	void SetStaticexText(const char *strtext);
    CString &GetStaticexText();
	void SetWidth(int len);
};
