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

#include <list>
#include "const_define.h"

using namespace std;

const uint32_t MAX_LIST_COUNT = 1000000;

template<class T>
class SafeList {
private:
    list<T> mList;
    bgcc::Mutex mLocker;
public:
    SafeList();
    ~SafeList();

    bool Empty();
    typename list<T>::size_type Size();
    void Clear();
    bool Back(T& value);
    bool Front(T& value);
    bool Pop_back();
    bool Pop_front();
    bool Push_back(const T& value);
    bool Push_front(const T& value);

    template<class K, class F>
    bool Find(const K& key, F function);
    template<class K, class F>
    bool Find(const K& key, F function, T& value);

    template<class K, class F>
    bool Erase(const K& key, F function);

    template<class F>
    void DoSomething(F function);
};

template<class T>
SafeList<T>::SafeList() {
}

template<class T>
SafeList<T>::~SafeList() {
}

template<class T>
bool SafeList<T>::Empty() {
    SingleLocker s(&mLocker);
    return mList.empty();
}

template<class T>
typename list<T>::size_type SafeList<T>::Size() {
    SingleLocker s(&mLocker);
    return mList.size();
}

template<class T>
void SafeList<T>::Clear() {
    SingleLocker s(&mLocker);
    mList.clear();
}

template<class T>
bool SafeList<T>::Back(T& value) {
    SingleLocker s(&mLocker);

    if (mList.empty()) {
        return false;
    }

    value = mList.back();
    return true;
}

template<class T>
bool SafeList<T>::Front(T& value) {
    SingleLocker s(&mLocker);

    if (mList.empty()) {
        return false;
    }

    value = mList.front();
    return true;
}

template<class T>
bool SafeList<T>::Pop_back() {
    SingleLocker s(&mLocker);

    if (mList.empty()) {
        return false;
    }

    mList.pop_back();
    return true;
}

template<class T>
bool SafeList<T>::Pop_front() {
    SingleLocker s(&mLocker);

    if (mList.empty()) {
        return false;
    }

    mList.pop_front();
    return true;
}

template<class T>
bool SafeList<T>::Push_back(const T& value) {
    SingleLocker s(&mLocker);

    if (mList.size() >= MAX_LIST_COUNT) { //maybe overflow, need log out
        return false;
    } else {
        mList.push_back(value);
        return true;
    }
}

template<class T>
bool SafeList<T>::Push_front(const T& value) {
    SingleLocker s(&mLocker);

    if (mList.size() >= MAX_LIST_COUNT) { //maybe overflow, need log out
        return false;
    } else {
        mList.push_front(value);
        return true;
    }
}

template<class T>
template<class K, class F>
bool SafeList<T>::Find(const K& key, F function) {
    SingleLocker s(&mLocker);

    for (typename list<T>::iterator it = mList.begin(); it != mList.end(); it++) {
        if (function(*it, key)) {
            return true;
        }
    }

    return false;
}

template<class T>
template<class K, class F>
bool SafeList<T>::Find(const K& key, F function, T& value) {
    SingleLocker s(&mLocker);

    for (typename list<T>::iterator it = mList.begin(); it != mList.end(); it++) {
        if (function(*it, key)) {
            value = *it;
            return true;
        }
    }

    return false;
}

template<class T>
template<class K, class F>
bool SafeList<T>::Erase(const K& key, F function) {
    SingleLocker s(&mLocker);

    for (typename list<T>::iterator it = mList.begin(); it != mList.end(); it++) {
        if (function(*it, key)) {
            mList.erase(it);
            return true;
        }
    }

    return false;
}

template<class T>
template<class F>
void SafeList<T>::DoSomething(F function) {
    SingleLocker s(&mLocker);
    for_each(mList.begin(), mList.end(), function);
}
