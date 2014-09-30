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

#include <map>
#include "locker.h"

using namespace std;

template<class K, class T>
class SafeMap {
private:
    map<K, T> mMap;
    bgcc::RWLock m_RWLock;
public:
    SafeMap();
    ~SafeMap();
    bool Empty();
    typename map<K, T>::size_type Size();
    void Clear();
    bool Find(const K& key);
    bool Find(const K& key, T& value);

    template<class F>
    bool FindKey(K& key, F function, const T& value);

    template<class OUTK, class F>
    bool Search(const OUTK& key, F function);
    template<class OUTK, class F>
    bool Search(const OUTK& key, F function, T& value);

    bool Insert(const K& key, const T& value);
    bool Erase(const K& key);

    template<class F>
    void Remove(F function);

    void SetValue(const K& key, const T& value);

    template<class F>
    void DoSomething(F function);
    template<class F, class V>
    void DoSomething(F function, V& value);
};

template<class K, class T>
SafeMap<K, T>::SafeMap() {
}

template<class K, class T>
SafeMap<K, T>::~SafeMap() {
}

template<class K, class T>
bool SafeMap<K, T>::Empty() {
    SingleRWLocker s(&m_RWLock, false);
    return mMap.empty();
}

template<class K, class T>
typename map<K, T>::size_type SafeMap<K, T>::Size() {
    SingleRWLocker s(&m_RWLock, false);
    return mMap.size();
}

template<class K, class T>
void SafeMap<K, T>::Clear() {
    SingleRWLocker s(&m_RWLock, true);
    mMap.clear();
}

template<class K, class T>
bool SafeMap<K, T>::Find(const K& key) {
    SingleRWLocker s(&m_RWLock, false);
    typename map<K, T>::iterator it = mMap.find(key);
    return it != mMap.end();
}

template<class K, class T>
bool SafeMap<K, T>::Find(const K& key, T& value) {
    SingleRWLocker s(&m_RWLock, false);
    typename map<K, T>::iterator it = mMap.find(key);

    if (it != mMap.end()) {
        value = it->second;
        return true;
    }

    return false;
}

template<class K, class T>
template<class F>
bool SafeMap<K, T>::FindKey(K& key, F function, const T& value) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename map<K, T>::const_iterator it = mMap.begin(); it != mMap.end(); it++) {
        if (function(it->second, value)) {
            key = it->first;
            return true;
        }
    }

    return false;
}

template<class K, class T>
template<class OUTK, class F>
bool SafeMap<K, T>::Search(const OUTK& key, F function) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename map<K, T>::const_iterator it = mMap.begin(); it != mMap.end(); it++) {
        if (function(it->second, key)) {
            return true;
        }
    }

    return false;
}

template<class K, class T>
template<class OUTK, class F>
bool SafeMap<K, T>::Search(const OUTK& key, F function, T& value) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename map<K, T>::const_iterator it = mMap.begin(); it != mMap.end(); it++) {
        if (function(it->second, key)) {
            value = it->second;
            return true;
        }
    }

    return false;
}

template<class K, class T>
bool SafeMap<K, T>::Insert(const K& key, const T& value) {
    SingleRWLocker s(&m_RWLock, true);
    pair<typename map<K, T>::iterator, bool> pair = mMap.insert(typename map<K, T>::value_type(key,
            value));
    return pair.second;
}

template<class K, class T>
bool SafeMap<K, T>::Erase(const K& key) {
    SingleRWLocker s(&m_RWLock, true);
    typename map<K, T>::size_type size = mMap.erase(key);
    return size != 0;
}

template<class K, class T>
template<class F>
void SafeMap<K, T>::Remove(F function) {
    SingleRWLocker s(&m_RWLock, true);

    for (typename map<K, T>::iterator it = mMap.begin(); it != mMap.end();) {
        if (function(it->second)) {
            mMap.erase(it++);
        } else {
            it++;
        }
    }
}

template<class K, class T>
void SafeMap<K, T>::SetValue(const K& key, const T& value) {
    SingleRWLocker s(&m_RWLock, true);
    mMap[key] = value;
}

template<class K, class T>
template<class F>
void SafeMap<K, T>::DoSomething(F function) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename map<K, T>::const_iterator it = mMap.begin(); it != mMap.end(); it++) {
        function(it->first, it->second);
    }
}

template<class K, class T>
template<class F, class V>
void SafeMap<K, T>::DoSomething(F function, V& value) {
    SingleRWLocker s(&m_RWLock, false);

    for (typename map<K, T>::const_iterator it = mMap.begin(); it != mMap.end(); it++) {
        function(it->first, it->second, value);
    }
}
