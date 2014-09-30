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
#include "const_define.h"

using namespace std;

template<class K, class T>
class SafeMultimap {
private:
    multimap<K, T> mMultimap;
    bgcc::Mutex mLocker;
public:
    SafeMultimap();
    ~SafeMultimap();
    bool Empty();
    typename multimap<K, T>::size_type Size();
    void Clear();
    bool Find(const K& key);
    bool Find(const K& key, T& value);
    void Insert(const K& key, const T& value);
    typename multimap<K, T>::size_type Erase(const K& key);
    bool EraseSingle(const K& key);

    template<class F>
    void Remove(F function);
};

template<class K, class T>
SafeMultimap<K, T>::SafeMultimap() {
}

template<class K, class T>
SafeMultimap<K, T>::~SafeMultimap() {
}

template<class K, class T>
bool SafeMultimap<K, T>::Empty() {
    SingleLocker s(&mLocker);
    return mMultimap.empty();
}

template<class K, class T>
typename multimap<K, T>::size_type SafeMultimap<K, T>::Size() {
    SingleLocker s(&mLocker);
    return mMultimap.size();
}

template<class K, class T>
void SafeMultimap<K, T>::Clear() {
    SingleLocker s(&mLocker);
    mMultimap.clear();
}

template<class K, class T>
bool SafeMultimap<K, T>::Find(const K& key) {
    SingleLocker s(&mLocker);
    typename multimap<K, T>::iterator it = mMultimap.find(key);
    return it != mMultimap.end();
}

template<class K, class T>
bool SafeMultimap<K, T>::Find(const K& key, T& value) {
    SingleLocker s(&mLocker);
    typename multimap<K, T>::iterator it = mMultimap.find(key);

    if (it != mMultimap.end()) {
        value = it->second;
        return true;
    }

    return false;
}

template<class K, class T>
void SafeMultimap<K, T>::Insert(const K& key, const T& value) {
    SingleLocker s(&mLocker);
    typename multimap<K, T>::iterator it = mMultimap.insert(typename multimap<K, T>::value_type(key,
                                           value));
}

template<class K, class T>
typename multimap<K, T>::size_type SafeMultimap<K, T>::Erase(const K& key) {
    SingleLocker s(&mLocker);
    return mMultimap.erase(key);
}

template<class K, class T>
bool SafeMultimap<K, T>::EraseSingle(const K& key) {
    SingleLocker s(&mLocker);
    typename multimap<K, T>::iterator it = mMultimap.find(key);

    if (it != mMultimap.end()) {
        mMultimap.erase(it);
        return true;
    }

    return false;
}

template<class K, class T>
template<class F>
void SafeMultimap<K, T>::Remove(F function) {
    SingleLocker s(&mLocker);

    for (typename multimap<K, T>::iterator it = mMultimap.begin(); it != mMultimap.end();) {
        if (function(it->second)) {
            mMultimap.erase(it++);
        } else {
            it++;
        }
    }
}
