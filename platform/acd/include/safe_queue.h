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

#include <queue>
#include "const_define.h"

using namespace std;

const uint32_t MAX_QUEUE_COUNT = 1000000;

template<typename T>
class SafeQueue {
private:
    queue<T> mQueue;
    bgcc::Mutex mLocker;

    bgcc::Semaphore mFullSemaphore;
    bgcc::Semaphore mEmptySemaphore;
public:
    SafeQueue();
    ~SafeQueue();
    bool Empty();
    typename queue<T>::size_type Size();
    void BlockFront(T& value);
    bool Pop(T& value);
    void BlockPop();
    void BlockPop(T& value);
    void HarfBlockPop(T& value);
    void Push(const T& value);
    void BlockPush(const T& value);
    void HarfBlockPush(const T& value);
};

template<class T>
SafeQueue<T>::SafeQueue() : mFullSemaphore(0), mEmptySemaphore(MAX_QUEUE_COUNT) {
}

template<class T>
SafeQueue<T>::~SafeQueue() {
}

template<class T>
bool SafeQueue<T>::Empty() {
    SingleLocker s(&mLocker);
    return mQueue.empty();
}

template<class T>
typename queue<T>::size_type SafeQueue<T>::Size() {
    SingleLocker s(&mLocker);
    return mQueue.size();
}

template<class T>
void SafeQueue<T>::BlockFront(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mLocker.unlock();
    mFullSemaphore.signal();
}

template<class T>
bool SafeQueue<T>::Pop(T& value) {
    SingleLocker s(&mLocker);

    if (mQueue.empty()) {
        return false;
    }

    value = mQueue.front();
    mQueue.pop();
    return true;
}

template<class T>
void SafeQueue<T>::BlockPop() {
    mFullSemaphore.wait();
    mLocker.lock();
    mQueue.pop();
    mLocker.unlock();
    mEmptySemaphore.signal();
}

template<class T>
void SafeQueue<T>::BlockPop(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mQueue.pop();
    mLocker.unlock();
    mEmptySemaphore.signal();
}

template<class T>
void SafeQueue<T>::HarfBlockPop(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mQueue.pop();
    mLocker.unlock();
}

template<class T>
void SafeQueue<T>::Push(const T& value) {
    SingleLocker s(&mLocker);

    if (mQueue.size() >= MAX_QUEUE_COUNT) { //maybe overflow, need log out
        mQueue.pop();
    }

    mQueue.push(value);
}

template<class T>
void SafeQueue<T>::BlockPush(const T& value) {
    mEmptySemaphore.wait();
    mLocker.lock();
    mQueue.push(value);
    mLocker.unlock();
    mFullSemaphore.signal();
}

template<class T>
void SafeQueue<T>::HarfBlockPush(const T& value) {
    bool isFull = false;
    mLocker.lock();

    if (mQueue.size() >= MAX_QUEUE_COUNT) { //maybe overflow, need log out
        isFull = true;
        mQueue.pop();
    }

    mQueue.push(value);
    mLocker.unlock();

    if (!isFull) {
        mFullSemaphore.signal();
    }
}
