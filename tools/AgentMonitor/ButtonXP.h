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

#define MY_BS_TYPEMASK SS_TYPEMASK

class CButtonXP : public CButton
{
private:
	// 按钮的外边框
	CPen m_BoundryPen;

	// 鼠标指针置于按钮之上时按钮的内边框
	CPen m_InsideBoundryPenLeft;
	CPen m_InsideBoundryPenRight;
	CPen m_InsideBoundryPenTop;
	CPen m_InsideBoundryPenBottom;

	// 按钮获得焦点时按钮的内边框
	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;

	// 按钮的画刷
	CBrush m_FillActive;
	CBrush m_FillInactive;

	// 按钮的状态
	BOOL m_bOver;		// 鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;	// 在鼠标按下没覩释放时该值为true
	BOOL m_bSelected;	// 按钮被按下是该值为true
	BOOL m_bFocus;		// 按钮为当前焦点所在时该值为true
	BOOL m_bIsDefault;
	BOOL m_nTypeStyle;

public:
	CButtonXP();
	virtual ~CButtonXP();

protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DoGradientFill(CDC *pDC, CRect* rect);
	virtual void DrawInsideBorder(CDC *pDC, CRect* rect);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnClicked();
    afx_msg UINT OnGetDlgCode();
	LRESULT OnSetStyle(WPARAM wParam, LPARAM lParam);
};
