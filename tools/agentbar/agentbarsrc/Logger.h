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

#include <string>			//标准C++库，string类
#include <fstream>			//标准C++库，IO流类
#include <vector>			//标准C++库，vector
#include <list>				//标准C++库，list
#include <cstdio>			//标准C++库，remove
#include <cstring>			//标准C++库，strcmp
#include <io.h>				//C库，access函数
#include <cassert>
#include "ConstDef.h"

using namespace std;

class Logger
{
private:
	unsigned long mLogCount;					//日志文件大小
	unsigned long mFileCount;					//日志文件数量
	string mDirName;							//日志文件路径
	string mFileName;							//日志文件名
	string mVersion;							//程序版本
	bool mShowVersion;							//是否显示版本
	Level mLevel;								//日志级别

	unsigned long mCurLogCount;					//当前日志条数
	string mFuleFileName;						//日志文件全名
	ofstream mOutStream;						//IO流
	bgcc::Mutex mLocker;								//同步锁
private:
	bool CreatDirectory(const string &strPath);
	void GetTimeFileName(LongString strTime);
	void GetCurrentTimeString(LongString strTime);
	void InitLogger();
	void DeleteLog();
	void UnInitLogger();
	void ProcessLog();
public:
	Logger();
	~Logger();
	void Initialize(unsigned long logCount, unsigned long fileCount, const char *dirName, const char *fileName, const char *version, bool showVersion = true, Level level = Level_High);
	void UnInitialize();
	void WriteLog(Level level, const char *pFormat, ...);
	void WriteLog(const char *content, Level level = Level_Low);
	void WriteLog(const char *owner, const char *method, const char *content, int result, Level level = Level_Low);
	void WriteLog(const char *owner, const char *method, int content, int result, Level level = Level_Low);
	void SetLogLevel(Level level = Level_High);
	const string &GetFullFileName();
};
