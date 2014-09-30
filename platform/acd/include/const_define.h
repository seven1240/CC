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

#ifdef WIN32
// mysql依赖sock头文件
#include <Winsock2.h>
// Logger(C库，access函数)
#include <io.h>
// windows API
// Locker(InitializeCriticalSection, DeleteCriticalSection, EnterCriticalSection, LeaveCriticalSection)
// Logger(FindFirstFile, FindNextFile, CreateDirectory, SYSTEMTIME, GetLocalTime)
#include <windows.h>
// 文件版本
// Logger(GetFileVersionInfoSize, GetFileVersionInfo, VerQueryValue)
#include <winver.h>
#else
#include <sys/stat.h>       // mkdir, access
#include <dirent.h>         // DIR, dirent, opendir, readdir, closedir
#include <time.h>
#include <sys/timeb.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <getopt.h>         // getopt_long
#endif

#include <acdcommon.h>
#include <acdcallback.h>
#include <common.h>

#include <libs/shared_ptr.h>
#include <libs/rwlock.h>

#ifdef WIN32
//日志组件、info对话框使用
#define vsnprintf _vsnprintf
#define snprintf _snprintf
#define access _access
#else
#endif

#ifdef WIN32
#define SHOW_LONG "I64"
#define PATH_FLAG '\\'
#else
#define SHOW_LONG "ll"
#define PATH_FLAG '/'
#endif

// 日志等中广泛使用
//const uint32_t STRING_LENGHT = 64;
const uint32_t LONG_STRING_LENGHT = 128;
const uint32_t TEXT_LENGHT = 1024;
const uint32_t LONG_TEXT_LENGHT = 2048;

//typedef char String[STRING_LENGHT];
typedef char LongString[LONG_STRING_LENGHT];
typedef char Text[TEXT_LENGHT];
typedef char LongText[LONG_TEXT_LENGHT];

typedef bgcc::Guard<bgcc::Mutex> SingleLocker;
typedef bgcc::SharedPtr<acd::acdcallbackProxy> acd_callback_proxy_ptr;

#ifdef WIN32
const char ACD_VERSION[] = "version: 1.1.2.9";
const char CONFIG_DIR[] = "conf\\";
const char LOG_DIR[] = "log\\";
const char EVNET_LOG_DIR[] = "log\\eventlog\\";
const char CALL_LOG_DIR[] = "log\\calllog\\";
const char BGCC_LOG_CONFIG_FILE[] = "conf\\bgcc.conf";
#else
const char CONFIG_DIR[] = "conf/";
const char LOG_DIR[] = "log/";
const char EVNET_LOG_DIR[] = "log/eventlog/";
const char CALL_LOG_DIR[] = "log/calllog/";
const char BGCC_LOG_CONFIG_FILE[] = "conf/bgcc.conf";
#endif
const char CONFIG_FILE[] = "acd.conf";
const char LOG_FILE[] = "acdlog";
const char EVNET_LOG_FILE[] = "acdeventlog";
const char CALL_LOG_FILE[] = "acdcalllog";

// 日志级别
enum Level {
    LOG_LEVEL_CRITICAL,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_DEBUG
};

enum EventTypeT {
    AGENT_EVENT,
    MEDIA_EVENT,
    ROUTE_EVENT,
    OTHER_EVENT
};

struct SendEventT {
    int64_t m_event_id;
    acd_callback_proxy_ptr m_callback_proxy;
    EventTypeT m_event_type;
    acd::AgentEventT m_agent_event;
    acd::MediaEventT m_media_event;
    acd::RouteEventT m_route_event;
    acd::OtherEventT m_other_event;
};
