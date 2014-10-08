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

#include <cassert>
#include "Info.h"
#include "ConstDef.h"		//常量定义

// CInfo 对话框

IMPLEMENT_DYNAMIC(CInfo, CDialog)
CInfo::CInfo(CWnd* pParent /*=NULL*/) : CDialog(CInfo::IDD, pParent), m_index(IDI_ICON_ERROR)
{
	m_BrushBK.CreateSolidBrush(RGB(250,250,250));
}

CInfo::~CInfo()
{
	m_BrushBK.DeleteObject();
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_ICON, m_btnInfo);
	DDX_Control(pDX, IDC_EDIT_INFO, m_edtInfo);
}

BOOL CInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_index)
	{
	case IDI_ICON_ALARM:
		SetWindowText("警告");
		break;
	case IDI_ICON_ERROR:
		SetWindowText("错误");
		break;
	case IDI_ICON_INFOMATION:
		SetWindowText("提示");
		break;
	default:
		// 系统默认为IDI_ICON_ERROR，如果设置一个不存在的index，则为IDI_ICON_ERROR
		SetWindowText("错误");
		m_index = IDI_ICON_ERROR;
		break;
	}

	m_edtInfo.SetWindowText(m_info);
	m_btnInfo.SetIcon(m_index);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CInfo, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CInfo 消息处理程序

HBRUSH CInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_BUTTON_ICON:
	case IDC_EDIT_INFO:
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(250,250,250));
		return m_BrushBK;
		break;
	default:
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CInfo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	CBrush *p_OldBrush = NULL;

	p_OldBrush = pDC->SelectObject(&m_BrushBK);
	pDC->GetClipBox(&rect);
	pDC->FillRect(&rect, &m_BrushBK);
	pDC->SelectObject(p_OldBrush);

	p_OldBrush = NULL;

	return TRUE;

	//return CDialog::OnEraseBkgnd(pDC);
}

void CInfo::SetInfo(int index, const char *pFormat, ...)
{
	assert(pFormat != NULL);

	Text content;
	va_list list;
	va_start(list, pFormat);
	vsnprintf(content, TEXT_LENGHT, pFormat, list);
	va_end(list);

	m_index = index;
	m_info = content;
}
