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
//安全控件
#include <objsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCCAgentBarApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xC996584, 0x8882, 0x4D08, { 0x9D, 0x29, 0x24, 0xF1, 0x8B, 0x99, 0x28, 0xBA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

//与控件的guid一致
const GUID CDECL CLSID_SafeItem =
		{ 0x6d4733b4, 0x8e49, 0x495c, { 0x9f, 0x2b, 0x27, 0x60, 0x6c, 0xeb, 0x20, 0xe3 } };

// CCCAgentBarApp::InitInstance - DLL 初始化
BOOL CCCAgentBarApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}

// CCCAgentBarApp::ExitInstance - DLL 终止
int CCCAgentBarApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}

// 创建组件种类 
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription) 
{ 
    ICatRegister *pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER,
		IID_ICatRegister, (void**)&pcr);
    if(FAILED(hr))
		return hr;

    // Make sure the HKCR\Component Categories\{..catid...} 
    // key is registered. 
    CATEGORYINFO catinfo; 
    catinfo.catid = catid; 
    catinfo.lcid = 0x0409 ; // english

    // Make sure the provided description is not too long. 
    // Only copy the first 127 characters if it is. 
    size_t len = wcslen(catDescription);
    if(len > 127)
		len = 127;
    wcsncpy(catinfo.szDescription, catDescription, len);
    // Make sure the description is null terminated. 
    catinfo.szDescription[len] = '\0';

    hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

    return hr; 
}

// 注册组件种类 
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid) 
{ 
    // Register your component categories information. 
    ICatRegister *pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER,
		IID_ICatRegister, (void**)&pcr);
    if(SUCCEEDED(hr))
    { 
		// Register this category as being "implemented" by the class. 
		CATID rgcatid[1];
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
    } 
    if(pcr != NULL)
		pcr->Release();
	return hr;
}

// 卸载组件种类 
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid) 
{ 
    ICatRegister *pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER,
		IID_ICatRegister, (void**)&pcr);
    if(SUCCEEDED(hr))
    { 
		// Unregister this category as being "implemented" by the class.
		CATID rgcatid[1];
		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if(pcr != NULL)
		pcr->Release();

    return hr;
}

// DllRegisterServer - 将项添加到系统注册表
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	// 标记控件初始化安全. 
	// 创建初始化安全组件种类 
	HRESULT hr = S_OK;
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if(FAILED(hr))
		return hr;

	// 注册初始化安全 
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if(FAILED(hr))
		return hr;

	// 标记控件脚本安全 
	// 创建脚本安全组件种类 
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if(FAILED(hr))
		return hr;

	// 注册脚本安全组件种类 
	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if(FAILED(hr))
		return hr;

	return NOERROR;
}

// DllUnregisterServer - 将项从系统注册表中移除
STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	// 删除控件初始化安全入口
	HRESULT hr = S_OK;
	hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if(FAILED(hr))
		return hr;

	// 删除控件脚本安全入口
	hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if(FAILED(hr))
		return hr;

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
