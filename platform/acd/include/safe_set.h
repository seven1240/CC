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

#include <set>
#include <algorithm>
#include "locker.h"

using namespace std;

template<class T>
class SafeSet {
private:
    set<T> mSet;
    bgcc::RWLock m_RWLock;
public:
    SafeSet();
    ~SafeSet();
    bool Empty();
    typename set<T>::size_type Size();
    void Clear();
    bool Find(const T& key);

    template<class K, class F>
    bool Find(const K& key, F function);
    template<class K, class F>
    bool Find(const K& key, F function, T& value);

    bool Insert(const T& key);
    bool Erase(const T& key);

    template<class F>
    void DoSomething(F function);
    template<class F, class V>
    void DoSomething(F function, V& value);
};

template<class T>
SafeSet<T>::SafeSet() {
}

template<class T>
SafeSet<T>::~SafeSet() {
}

template<class T>
bool SafeSet<T>::Empty() {
    SingleRWLocker s(&m_RWLock, false);
    return mSet.empty();
}

template<class T>
typename set<T>::size_type SafeSet<T>::Size() {
    SingleRWLocker s(&m_RWLock, false);
    return mSet.size();
}

template<class T>
void SafeSet<T>::Clear() {
    SingleRWLocker s(&m_RWLock, true);
    mSet.clear();
}

template<class T>
bool SafeSet<T>::Find(const T& key) {
    SingleRWLocker s(&m_RWLock, false);
    typename set<T>::iterator it = mSet.find(key);
    return it != mSet.end();
}

template<class T>
template<class K, class F>
bool SafeSet<T>::Find(const K& key, F function) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename set<T>::const_iterator it = mSet.begin(); it != mSet.end(); it++) {
        if (function(*it, key)) {
            return true;
        }
    }

    return false;
}

template<class T>
template<class K, class F>
bool SafeSet<T>::Find(const K& key, F function, T& value) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename set<T>::const_iterator it = mSet.begin(); it != mSet.end(); it++) {
        if (function(*it, key)) {
            value = *it;
            return true;
        }
    }

    return false;
}

template<class T>
bool SafeSet<T>::Insert(const T& key) {
    SingleRWLocker s(&m_RWLock, true);
    pair<typename set<T>::iterator, bool> p = mSet.insert(key);
    return p.second;
}

template<class T>
bool SafeSet<T>::Erase(const T& key) {
    SingleRWLocker s(&m_RWLock, true);
    typename set<T>::size_type size = mSet.erase(key);
    return size != 0;
}

template<class T>
template<class F>
void SafeSet<T>::DoSomething(F function) {
    SingleRWLocker s(&m_RWLock, true);
    for_each(mSet.begin(), mSet.end(), function);
}

template<class T>
template<class F, class V>
void SafeSet<T>::DoSomething(F function, V& value) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename set<T>::const_iterator it = mSet.begin(); it != mSet.end(); it++) {
        function(*it, value);
    }
}
