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


#include "thread.h"

#ifdef WIN32

DWORD Thread::ThreadMethod(LPVOID lpParams) {
    assert(lpParams != NULL);

    Thread* pThread = static_cast<Thread*>(lpParams);
    pThread->Method();
    return 0;
}

Thread::Thread() : mHandle(NULL), mIsLoop(false) {
}

Thread::~Thread() {
    if (mHandle) {
        CloseHandle(mHandle);
    }
}

void Thread::Start() {
    mIsLoop = true;
    mHandle = CreateThread(NULL, 0, ThreadMethod, this, 0, NULL);
}

void Thread::Stop() {
    mIsLoop = false;
    TerminateThread(mHandle, 0);
    WaitForSingleObject(mHandle, INFINITE);
    CloseHandle(mHandle);
    mHandle = NULL;
}

#else

void* Thread::ThreadMethod(void* lpParams) {
    assert(lpParams != NULL);

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);   // linux(PTHREAD_CANCEL_ASYNCHRONOUS)

    Thread* pThread = static_cast<Thread*>(lpParams);
    pThread->Method();
    pthread_exit(NULL);
}

Thread::Thread() : mHandle(0), mIsLoop(false) {
}

Thread::~Thread() {
}

void Thread::Start() {
    mIsLoop = true;
    pthread_create(&mHandle, NULL, ThreadMethod, this);
    //pthread_detach(mHandle);
}

void Thread::Stop() {
    mIsLoop = false;
    pthread_cancel(mHandle);
    pthread_join(mHandle, NULL);
    mHandle = 0;
}

#endif
