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

#ifndef _IMS_LOG_H_
#define _IMS_LOG_H_

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <bgcc.h>

#define LOGNAME "ims"

#define FATAL_LOG(fmt, arg...) do{BGCC_FATAL(LOGNAME, fmt, ##arg);}while(0)
#define WARNING_LOG(fmt, arg...) do{BGCC_WARN(LOGNAME, fmt,##arg);}while(0)
#define NOTICE_LOG(fmt, arg...) do{BGCC_NOTICE(LOGNAME, fmt,##arg);}while(0)
#define TRACE_LOG(fmt, arg...) do{BGCC_TRACE(LOGNAME, fmt,##arg);}while(0)
#define DEBUG_LOG(fmt, arg...) do{BGCC_DEBUG(LOGNAME, fmt,##arg);}while(0)

#endif //_IMS_LOG_H_
