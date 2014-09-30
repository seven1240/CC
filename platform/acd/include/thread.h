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

#include <cassert>          //±ê×¼C++¿â£¬assert
#include "const_define.h"

class Thread {
private:
#ifdef WIN32
    HANDLE mHandle;
#else
    pthread_t mHandle;
#endif
protected:
    bool mIsLoop;
private:
#ifdef WIN32
    static DWORD WINAPI ThreadMethod(LPVOID lpParams);
#else
    static void* ThreadMethod(void* lpParams);
#endif
protected:
    virtual void Method() = 0;
public:
    Thread();
    virtual ~Thread();
    virtual void Start();
    virtual void Stop();
};
