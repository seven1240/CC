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

#include "ImgMgr.h"
#include "Resource.h"

const char RESDLL[] = "ccl_imgex.dll";

CImgMgr::CImgMgr(void) : m_hModule_Res(NULL)
{
}

CImgMgr::~CImgMgr(void)
{
	UnLoadImg();
}

CImgMgr &CImgMgr::Instance()
{
	static CImgMgr obj;
	return obj;
}

bool CImgMgr::LoadImg()
{
	m_hModule_Res = LoadLibrary(RESDLL);
	if(m_hModule_Res)
	{
		for(int i = IDB_BMP_SIGNIN; i <= IDB_BMP_FENGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			HBITMAP hBit = NULL;
			if(((hBit = LoadBitmap(m_hModule_Res, MAKEINTRESOURCE(i))) && pTmp->Attach(hBit)) || pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		for(int i = IDB_BMP_MS_SIGNIN; i <= IDB_BMP_MS_SKILLCHANGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			HBITMAP hBit = NULL;
			if(((hBit = LoadBitmap(m_hModule_Res, MAKEINTRESOURCE(i))) && pTmp->Attach(hBit)) || pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		for(int i = IDB_BMP_IN_SIGNIN; i <= IDB_BMP_IN_SKILLCHANGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			HBITMAP hBit = NULL;
			if(((hBit = LoadBitmap(m_hModule_Res, MAKEINTRESOURCE(i))) && pTmp->Attach(hBit)) || pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		CBitmap *pTmp = new CBitmap();
		HBITMAP hBit = NULL;
		if((hBit = LoadBitmap(m_hModule_Res, MAKEINTRESOURCE(IDB_BMP_BACKGROUND))) && pTmp->Attach(hBit))
			m_imgs.insert(std::map<int, CBitmap*>::value_type(IDB_BMP_BACKGROUND, pTmp));
		else
			delete pTmp;
		return true;
	}
	else
	{
		for(int i = IDB_BMP_SIGNIN; i <= IDB_BMP_FENGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			if(pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		for(int i = IDB_BMP_MS_SIGNIN; i <= IDB_BMP_MS_SKILLCHANGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			if(pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		for(int i = IDB_BMP_IN_SIGNIN; i <= IDB_BMP_IN_SKILLCHANGE; i++)
		{
			CBitmap *pTmp = new CBitmap();
			if(pTmp->LoadBitmap(i))
				m_imgs.insert(std::map<int, CBitmap*>::value_type(i, pTmp));
			else
				delete pTmp;
		}
		return false;
	}
}

void CImgMgr::UnLoadImg()
{
	for(std::map<int, CBitmap*>::iterator it = m_imgs.begin(); it != m_imgs.end(); it++)
	{
		if(it->second)
		{
			it->second->DeleteObject();
			delete it->second;
			it->second = NULL;
		}
	}
	m_imgs.clear();
	if(m_hModule_Res)
	{
		FreeLibrary(m_hModule_Res);
		m_hModule_Res = NULL;
	}
}

CBitmap *CImgMgr::Get(int id)
{
	if(m_imgs.find(id) == m_imgs.end())
	{
		return NULL;
	}
	else
	{
		return m_imgs[id];
	}
}
