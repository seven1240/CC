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

#include "EditEx.h"

CEditEx::CEditEx()
{
}

CEditEx::~CEditEx()
{
}

void CEditEx::CheckNumber(const string &intput, string &output)
{
	if(intput.empty())
		return;

	unsigned char chCurrent = 0;
	unsigned char chNext = 0;
	for(unsigned int i = 0; i < intput.length(); i++)
	{
		chCurrent = intput[i];
		chNext = intput[i + 1];
		if(chCurrent >= 48 && chCurrent <= 57)// 当前字符是半角数字
		{
			output += chCurrent;
		}
		else if(chCurrent < 163)// 当前字符为其他单字节编码字符
		{
		}
		else if(chCurrent == 163 && chNext >= 176 && chNext <= 185)// 当前字符为全角数字
		{
			unsigned char temp = chNext - 128;
			output += temp;
			i++;// 跳过双字节编码字符的第二字节
		}
		else// 中文及其他全角字符
		{
			i++;// 跳过双字节编码字符的第二字节
		}
	}
}

LRESULT CEditEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == WM_PASTE)
	{
		if(IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard())
		{
			HGLOBAL hGlobalClip = GetClipboardData(CF_TEXT);
			char *pDataBuf = static_cast<char *>(GlobalLock(hGlobalClip));
			string strInput(pDataBuf);
			GlobalUnlock(hGlobalClip);

			string strOutput;
			CheckNumber(strInput, strOutput);

			if(EmptyClipboard())
			{
				hGlobalClip = GlobalAlloc(GHND, strOutput.length() + 1);
				pDataBuf = static_cast<char *>(GlobalLock(hGlobalClip));
				strcpy(pDataBuf, strOutput.c_str());
				GlobalUnlock(hGlobalClip);
				SetClipboardData(CF_TEXT, hGlobalClip);
			}

			CloseClipboard();
		}
	}
	else if(message == WM_CHAR)
	{
		BYTE ch = LOBYTE(LOWORD(wParam));
		if(!isdigit(ch) && ch != 8 && ch != 'c' - 'a' + 1 && ch != 'v' - 'a' + 1 && ch != 'x' - 'a' + 1)
			return 0;
	}

	return CEdit::WindowProc(message, wParam, lParam);
}
