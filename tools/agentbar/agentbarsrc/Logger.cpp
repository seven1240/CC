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

#include "Logger.h"

// **********************************私有函数**********************************
bool Logger::CreatDirectory(const string &strPath)
{
	if(access(strPath.c_str(), 0) == 0)//目录存在
	{
		return true;
	}
	vector<string> dirVector;
	string temp;
	for(string::const_iterator it = strPath.begin(); it != strPath.end(); it++)
	{
		temp.push_back(*it);
		if((*it) == '\\')
		{
			dirVector.push_back(temp);
		}
	}
	for(vector<string>::iterator it = dirVector.begin(); it != dirVector.end(); it++)
	{
		if(access((*it).c_str(), 0) != 0)
		{
			if(!CreateDirectory((*it).c_str(), NULL))
			{
				return false;
			}
		}
	}
	return true;
}

void Logger::GetTimeFileName(LongString strTime)
{
	assert(strTime != NULL);

	SYSTEMTIME now;
	GetLocalTime(&now);
	snprintf(strTime, LONG_STRING_LENGHT, "_%04d%02d%02d%02d%02d%02d%03d", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
		now.wSecond, now.wMilliseconds);
}

void Logger::GetCurrentTimeString(LongString strTime)
{
	assert(strTime != NULL);

	SYSTEMTIME now;
	GetLocalTime(&now);
	snprintf(strTime, LONG_STRING_LENGHT, "%04d-%02d-%02d %02d:%02d:%02d.%03d", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
		now.wSecond, now.wMilliseconds);
}

void Logger::InitLogger()
{
	LongString strFileTime;
	this->GetTimeFileName(strFileTime);
	this->mFuleFileName = this->mDirName + this->mFileName + strFileTime + ".log";
	this->mOutStream.open(this->mFuleFileName.c_str(), ios::out|ios::trunc);
	if(this->mOutStream.is_open() && this->mShowVersion)
	{
		LongString strTime;
		this->GetCurrentTimeString(strTime);
		this->mOutStream<<"["<<strTime<<"] "<<mVersion<<endl;
	}
}

void Logger::DeleteLog()
{
	string temp = this->mDirName + this->mFileName + "_*.log";
	WIN32_FIND_DATA fileData;
	HANDLE handle = FindFirstFile(temp.c_str(), &fileData);
	if(handle != INVALID_HANDLE_VALUE)
	{
		list<WIN32_FIND_DATA> fileList;
		fileList.push_back(fileData);
		while(FindNextFile(handle, &fileData))
		{
			fileList.push_back(fileData);
		}
		while(fileList.size() >= this->mFileCount)
		{
			list<WIN32_FIND_DATA>::iterator min_it = fileList.begin();
			for(list<WIN32_FIND_DATA>::iterator it = fileList.begin(); it != fileList.end(); it++)
			{
				if(strcmp((*it).cFileName, (*min_it).cFileName) < 0)
				{
					min_it = it;
				}
			}
			temp = this->mDirName + (*min_it).cFileName;
			remove(temp.c_str());
			fileList.erase(min_it);
		}
		FindClose(handle);
	}
}

void Logger::UnInitLogger()
{
	if(this->mOutStream.is_open())
	{
		this->mOutStream.close();
	}
}

void Logger::ProcessLog()
{
	if(this->mCurLogCount >= this->mLogCount)
	{
		this->UnInitLogger();
		this->DeleteLog();
		this->InitLogger();
		this->mCurLogCount = 0;
	}
	this->mCurLogCount++;
}

// **********************************共有函数**********************************
Logger::Logger() : mLogCount(100), mFileCount(1), mShowVersion(true), mLevel(Level_High), mCurLogCount(0)
{
}

Logger::~Logger()
{
	this->UnInitLogger();
}

void Logger::Initialize(unsigned long logCount, unsigned long fileCount, const char *dirName, const char *fileName, const char *version, bool showVersion, Level level)
{
	assert(logCount > 0);
	assert(fileCount > 0);
	assert(dirName != NULL);
	assert(*dirName != '\0');
	assert(fileName != NULL);
	assert(*fileName != '\0');
	assert(version != NULL);
	assert(*version != '\0');

	SingleLocker s(&mLocker);
	mLogCount = logCount;
	mFileCount = fileCount;
	mDirName.assign(dirName);
	if(mDirName[mDirName.size() - 1] != '\\')
		mDirName.push_back('\\');
	mFileName.assign(fileName);
	mVersion.assign(version);
	mShowVersion = showVersion;
	mLevel = level;

	this->CreatDirectory(this->mDirName);
	this->UnInitLogger();
	this->DeleteLog();
	this->InitLogger();
	mCurLogCount = 0;
}

void Logger::UnInitialize()
{
	SingleLocker s(&mLocker);
	this->UnInitLogger();
}

void Logger::WriteLog(Level level, const char *pFormat, ...)
{
	assert(pFormat != NULL);

	SingleLocker s(&mLocker);
	Text content;
	va_list list;
	va_start(list, pFormat);
	vsnprintf(content, TEXT_LENGHT, pFormat, list);
	va_end(list);

	if(this->mLevel < level)
		return;
	this->ProcessLog();
	if(this->mOutStream.is_open())
	{
		LongString strTime;
		this->GetCurrentTimeString(strTime);
		this->mOutStream<<"["<<strTime<<"] "<<content<<endl;
	}
}

void Logger::WriteLog(const char *content, Level level)
{
	assert(content != NULL);

	SingleLocker s(&mLocker);
	if(this->mLevel < level)
		return;
	this->ProcessLog();
	if(this->mOutStream.is_open())
	{
		LongString strTime;
		this->GetCurrentTimeString(strTime);
		this->mOutStream<<"["<<strTime<<"] "<<content<<endl;
	}
}

void Logger::WriteLog(const char *owner, const char *method, const char *content, int result, Level level)
{
	assert(owner != NULL);
	assert(method != NULL);
	assert(content != NULL);

	SingleLocker s(&mLocker);
	if(this->mLevel < level)
		return;
	this->ProcessLog();
	if(this->mOutStream.is_open())
	{
		LongString strTime;
		this->GetCurrentTimeString(strTime);
		this->mOutStream<<"["<<strTime<<"] [owner]"<<owner<<" [method]"<<method<<" [content]"<<content<<" [result]"<<result<<endl;
	}
}

void Logger::WriteLog(const char *owner, const char *method, int content, int result, Level level)
{
	assert(owner != NULL);
	assert(method != NULL);

	SingleLocker s(&mLocker);
	if(this->mLevel < level)
		return;
	this->ProcessLog();
	if(this->mOutStream.is_open())
	{
		LongString strTime;
		this->GetCurrentTimeString(strTime);
		this->mOutStream<<"["<<strTime<<"] [owner]"<<owner<<" [method]"<<method<<" [content]"<<content<<" [result]"<<result<<endl;
	}
}

void Logger::SetLogLevel(Level level)
{
	SingleLocker s(&mLocker);
	mLevel = level;
}

const string &Logger::GetFullFileName()
{
	SingleLocker s(&mLocker);
	return this->mFuleFileName;
}
