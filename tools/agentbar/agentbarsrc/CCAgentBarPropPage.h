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

// CCAgentBarPropPage.h : CCCAgentBarPropPage 属性页类的声明。
// CCCAgentBarPropPage : 有关实现的信息，请参阅 CCAgentBarPropPage.cpp。
class CCCAgentBarPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCCAgentBarPropPage)
	DECLARE_OLECREATE_EX(CCCAgentBarPropPage)

// 构造函数
public:
	CCCAgentBarPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CCAGENTBAR };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};
