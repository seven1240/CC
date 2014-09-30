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

#ifndef  __IMS_SINGLETON_H_
#define  __IMS_SINGLETON_H_

#include <pthread.h>
#include <stdlib.h>

namespace ims {

template<class T>
class singleton_t {
public:
    static T* instance() {
        pthread_once(&_once, &singleton_t::initialize);
        return _instance;
    }
private:
    static void initialize() {
        _instance = new T();
        ::atexit(destroy);
    }

    static void destroy() {
        delete _instance;
    }

private:
    singleton_t(const singleton_t&);
    const singleton_t& operator=(const singleton_t&);

    static pthread_once_t       _once;
    static T*                   _instance;
};

template<class T>
pthread_once_t  singleton_t<T>::_once  = PTHREAD_ONCE_INIT;
template<class T>
T* singleton_t<T>::_instance = NULL;
}
















#endif  //__SINGLETON_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
