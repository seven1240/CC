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

#include "stdafx.h"
#include "CCAgentBar.h"
#include "CCAgentBarPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCCAgentBarPropPage, COlePropertyPage)

// 消息映射
BEGIN_MESSAGE_MAP(CCCAgentBarPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid
IMPLEMENT_OLECREATE_EX(CCCAgentBarPropPage, "CCAGENTBAR.CCAgentBarPropPage.1",
	0x35261f88, 0xccd6, 0x4c86, 0x89, 0xc1, 0xe6, 0x74, 0x7e, 0xf0, 0xb3, 0x36)

// CCCAgentBarPropPage::CCCAgentBarPropPageFactory::UpdateRegistry -
// 添加或移除 CCCAgentBarPropPage 的系统注册表项
BOOL CCCAgentBarPropPage::CCCAgentBarPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CCAGENTBAR_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CCCAgentBarPropPage::CCCAgentBarPropPage - 构造函数
CCCAgentBarPropPage::CCCAgentBarPropPage() :
	COlePropertyPage(IDD, IDS_CCAGENTBAR_PPG_CAPTION)
{
}

// CCCAgentBarPropPage::DoDataExchange - 在页和属性间移动数据
void CCCAgentBarPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CCCAgentBarPropPage 消息处理程序
