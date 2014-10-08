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

#include "ButtonIcon.h"

CButtonIcon::CButtonIcon() : m_iconIndex(0)
{
}

CButtonIcon::~CButtonIcon()
{
}

void CButtonIcon::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// 获取图标， 此处如果图标的index不存在，在有些机器上除了返回空的HICON外，还会报错
	HICON h = AfxGetApp()->LoadIcon(m_iconIndex);
	// IDI_ASTERISK-信息，IDI_EXCLAMATION-警告，IDI_QUESTION-问号，IDI_HAND-错误，IDI_APPLICATION-应用程序图标
	if(!h)
		h = AfxGetApp()->LoadStandardIcon(IDI_HAND);
	// 获得DC资源
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	// 保存DC
	int oldDC = pDC->SaveDC();
	// 绘制图标按钮
	pDC->DrawIcon(0, 0, h);
	// 还原DC
	pDC->RestoreDC(oldDC);
}

void CButtonIcon::PreSubclassWindow() 
{
	// 修改风格为自绘
	ModifyStyle(0, BS_OWNERDRAW);
    
	CButton::PreSubclassWindow();
}

void CButtonIcon::SetIcon(int index)
{
    m_iconIndex = index;
}
