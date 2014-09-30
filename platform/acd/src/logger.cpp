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


#include "logger.h"

// **********************************私有函数**********************************
bool Logger::CreatDirectory(const string& strPath) {
    if (access(strPath.c_str(), 0) == 0) { //目录存在
        return true;
    }

    vector<string> dirVector;
    string temp;

    for (string::const_iterator it = strPath.begin(); it != strPath.end(); it++) {
        temp.push_back(*it);

        if ((*it) == PATH_FLAG) {
            dirVector.push_back(temp);
        }
    }

    for (vector<string>::iterator it = dirVector.begin(); it != dirVector.end(); it++) {
        if (access((*it).c_str(), 0) != 0) {
#ifdef WIN32

            if (!CreateDirectory((*it).c_str(), NULL))
#else
            if (mkdir((*it).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
#endif
            {
                return false;
            }
        }
    }

    return true;
}

void Logger::GetTimeFileName(LongString strTime) {
    assert(strTime != NULL);

#ifdef WIN32
    SYSTEMTIME now;
    GetLocalTime(&now);
    snprintf(strTime, LONG_STRING_LENGHT, "_%04d%02d%02d%02d%02d%02d%03d", now.wYear, now.wMonth,
             now.wDay, now.wHour, now.wMinute,
             now.wSecond, now.wMilliseconds);
#else
    struct timeb tTime;
    struct tm tmTemp;
    ftime(&tTime);
    localtime_r(&tTime.time, &tmTemp);
    snprintf(strTime, LONG_STRING_LENGHT, "_%04d%02d%02d%02d%02d%02d%03d", tmTemp.tm_year + 1900,
             tmTemp.tm_mon + 1,
             tmTemp.tm_mday, tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec, tTime.millitm);
#endif
}

void Logger::GetCurrentTimeString(LongString strTime) {
    assert(strTime != NULL);

#ifdef WIN32
    SYSTEMTIME now;
    GetLocalTime(&now);
    snprintf(strTime, LONG_STRING_LENGHT, "%04d-%02d-%02d %02d:%02d:%02d.%03d", now.wYear, now.wMonth,
             now.wDay, now.wHour, now.wMinute,
             now.wSecond, now.wMilliseconds);
#else
    struct timeb tTime;
    struct tm tmTemp;
    ftime(&tTime);
    localtime_r(&tTime.time, &tmTemp);
    snprintf(strTime, LONG_STRING_LENGHT, "%04d-%02d-%02d %02d:%02d:%02d.%03d", tmTemp.tm_year + 1900,
             tmTemp.tm_mon + 1,
             tmTemp.tm_mday, tmTemp.tm_hour, tmTemp.tm_min, tmTemp.tm_sec, tTime.millitm);
#endif
}

void Logger::InitLogger() {
    this->mFuleFileName = this->mDirName + this->mFileName + ".log";
    this->mOutStream.open(this->mFuleFileName.c_str(), ios::out | ios::app);

    if (this->mOutStream.is_open() && this->mShowVersion) {
        LongString strTime;
        this->GetCurrentTimeString(strTime);
        LongText logText;
        snprintf(logText, LONG_TEXT_LENGHT, "[%s] %s", strTime, mVersion.c_str());
        this->mOutStream << logText << endl;
    }
}

void Logger::DeleteLog() {
#ifdef WIN32
    string temp = this->mDirName + this->mFileName + "_*.log";
    WIN32_FIND_DATA fileData;
    HANDLE handle = FindFirstFile(temp.c_str(), &fileData);

    if (handle != INVALID_HANDLE_VALUE) {
        list<WIN32_FIND_DATA> fileList;
        fileList.push_back(fileData);

        while (FindNextFile(handle, &fileData)) {
            fileList.push_back(fileData);
        }

        while (fileList.size() >= this->mFileCount) {
            list<WIN32_FIND_DATA>::iterator min_it = fileList.begin();

            for (list<WIN32_FIND_DATA>::iterator it = fileList.begin(); it != fileList.end(); it++) {
                if (strcmp((*it).cFileName, (*min_it).cFileName) < 0) {
                    min_it = it;
                }
            }

            temp = this->mDirName + (*min_it).cFileName;
            remove(temp.c_str());
            fileList.erase(min_it);
        }

        FindClose(handle);
    }

#else
    DIR* p_dir;
    dirent* direntp;

    if (NULL == (p_dir = opendir(this->mDirName.c_str()))) {
        return;
    }

    list<string> fileList;

    while ((direntp = readdir(p_dir)) != NULL) {
        string temp = mFileName + "_";

        if (strstr(direntp->d_name, ".log") != NULL && strstr(direntp->d_name, temp.c_str()) != NULL) {
            fileList.push_back(direntp->d_name);
        }
    }

    closedir(p_dir);

    while (fileList.size() >= this->mFileCount) {
        list<string>::iterator min_it = fileList.begin();

        for (list<string>::iterator it = fileList.begin(); it != fileList.end(); it++) {
            if ((*it).compare(*min_it) < 0) {
                min_it = it;
            }
        }

        string temp = this->mDirName + *min_it;
        remove(temp.c_str());
        fileList.erase(min_it);
    }

#endif
}

void Logger::UnInitLogger() {
    if (this->mOutStream.is_open()) {
        this->mOutStream.close();

        LongString strFileTime;
        this->GetTimeFileName(strFileTime);
        string oldLogFileName = this->mDirName + this->mFileName + strFileTime + ".log";
        rename(this->mFuleFileName.c_str(), oldLogFileName.c_str());
    }
}

void Logger::ProcessLog() {
    if (this->mCurLogCount >= this->mLogCount || this->LogFileNotExisted()) {
        this->UnInitLogger();
        this->DeleteLog();
        this->InitLogger();
        this->mCurLogCount = 0;
    }

    this->mCurLogCount++;
}

bool Logger::LogFileNotExisted() {
#ifdef WIN32
    return false;
#else
    struct stat st;
    return -1 == stat(this->mFuleFileName.c_str(), &st) && ENOENT == errno;
#endif
}

void Logger::GetLevelString(Level level, string& levelString) {
    switch (level) {
    case LOG_LEVEL_CRITICAL:
        levelString = "CRITICAL";
        break;

    case LOG_LEVEL_WARNING:
        levelString = "WARNING";
        break;

    case LOG_LEVEL_NOTICE:
        levelString = "NOTICE";
        break;

    case LOG_LEVEL_DEBUG:
        levelString = "DEBUG";
        break;

    default:
        levelString = "OVERFLOW";
        break;
    }
}

// **********************************共有函数**********************************
Logger::Logger() : mLogCount(50000), mFileCount(10), mDirName(LOG_DIR), mFileName(LOG_FILE),
    mVersion(ACD_VERSION), mShowVersion(true), mLevel(LOG_LEVEL_NOTICE), mCurLogCount(0) {
}

Logger::~Logger() {
    this->UnInitLogger();
}

void Logger::Initialize(uint32_t logCount, uint32_t fileCount, const char* dirName,
                        const char* fileName, const char* version, bool showVersion, Level level) {
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

    if (mDirName[mDirName.size() - 1] != PATH_FLAG) {
        mDirName.push_back(PATH_FLAG);
    }

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

void Logger::UnInitialize() {
    SingleLocker s(&mLocker);
    this->UnInitLogger();
}

void Logger::WriteLog(const char* pFormat, ...) {
    assert(pFormat != NULL);

    SingleLocker s(&mLocker);
    Text content;
    va_list list;
    va_start(list, pFormat);
    vsnprintf(content, TEXT_LENGHT, pFormat, list);
    va_end(list);

    this->ProcessLog();

    if (this->mOutStream.is_open()) {
        LongString strTime;
        this->GetCurrentTimeString(strTime);
        LongText logText;
        snprintf(logText, LONG_TEXT_LENGHT, "[%s] %s", strTime, content);
        this->mOutStream << logText << endl;
    }
}

void Logger::WriteLog(Level level, const char* pFormat, ...) {
    assert(pFormat != NULL);

    SingleLocker s(&mLocker);
    Text content;
    va_list list;
    va_start(list, pFormat);
    vsnprintf(content, TEXT_LENGHT, pFormat, list);
    va_end(list);

    if (this->mLevel < level) {
        return;
    }

    this->ProcessLog();

    if (this->mOutStream.is_open()) {
        LongString strTime;
        this->GetCurrentTimeString(strTime);
        string levelString;
        GetLevelString(level, levelString);
        LongText logText;
        snprintf(logText, LONG_TEXT_LENGHT, "[%s] [%s] %s", strTime, levelString.c_str(), content);
        this->mOutStream << logText << endl;
    }
}

void Logger::WriteLog(Level level, const char* file, uint32_t line, const char* fun,
                      const char* pFormat, ...) {
    assert(file != NULL);
    assert(pFormat != NULL);

    SingleLocker s(&mLocker);
    Text content;
    va_list list;
    va_start(list, pFormat);
    vsnprintf(content, TEXT_LENGHT, pFormat, list);
    va_end(list);

    if (this->mLevel < level) {
        return;
    }

    this->ProcessLog();

    if (this->mOutStream.is_open()) {
        LongString strTime;
        this->GetCurrentTimeString(strTime);
        string levelString;
        GetLevelString(level, levelString);
        LongText logText;
        snprintf(logText, LONG_TEXT_LENGHT, "[%s] [%s] [%s:%d] [%s] %s", strTime, levelString.c_str(), file,
                 line, fun, content);
        this->mOutStream << logText << endl;
    }
}

void Logger::SetTimeout() {
    SingleLocker s(&mLocker);
    this->UnInitLogger();
    this->DeleteLog();
    this->InitLogger();
    mCurLogCount = 0;
}

void Logger::SetLogLevel(Level level) {
    SingleLocker s(&mLocker);
    mLevel = level;
}
