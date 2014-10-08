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

typedef unsigned int UNIT;

class CButtonEx : public CButton
{
private:
	CBrush m_BrushBk;
	// 按钮的状态
	BOOL m_bOver;			// 鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;		// 在鼠标按下没有释放时该值为true
	BOOL m_bSelected;		// 按钮被按下是该值为true
	BOOL m_bIsDefault;
	BOOL m_nTypeStyle;
	int  m_btPX;			// 按钮的横坐标
	int  m_btPY;			// 按钮的纵坐标
	int  m_nIDBmpDefault;
	int  m_nIDBmpHover;

public:
	CButtonEx();
	virtual ~CButtonEx();

private:
	void TransparentBlt(HDC hdcDest,		// 目标DC
					 int nXOriginDest,		// 目标X偏移
					 int nYOriginDest,		// 目标Y偏移
					 int nWidthDest,		// 目标宽度
					 int nHeightDest,		// 目标高度
					 HDC hdcSrc,			// 源DC
					 int nXOriginSrc,		// 源X起点
					 int nYOriginSrc,		// 源Y起点
					 int nWidthSrc,			// 源宽度
					 int nHeightSrc,		// 源高度
					 UINT crTransparent );

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawButton(CDC *pDC, CBitmap &bitmap, CRect *rect);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnClicked();
	afx_msg UINT OnGetDlgCode();
	LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);

public:
	void SetBitMap(int nIDBmpDefault, int nIDBmpHover);
	void SetButtonPos(int bx, int by);

};
