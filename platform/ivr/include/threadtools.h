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

#ifndef _THREAD_TOOLS_H_
#define _THREAD_TOOLS_H_

#include <bgcc.h>

template<typename _Func>
class anyrunnable : public bgcc::Runnable {
public:
    anyrunnable(_Func func)
        : _func(func) {
    }
public:
    int32_t operator()(const bool*, void*) {
        return _func();
    }
private:
    _Func _func;
};

template<typename _Func>
class smart_thread_t : public bgcc::Thread {
public:
    smart_thread_t(_Func _func)
        : bgcc::Thread(bgcc::SharedPointer<bgcc::Runnable>(new anyrunnable<_Func>(_func))) {
    }
};

template<typename _Func> bgcc::SharedPointer<bgcc::Thread> smart_thread(_Func func) {
    bgcc::SharedPointer<bgcc::Thread> _tp(new smart_thread_t<_Func>(func));
    return _tp;
}

template<typename _Func, typename _Argument>
struct bind_unary_func_ref_t {
    typedef typename _Func::result_type result_type;

    bind_unary_func_ref_t(_Func func, _Argument& arg)
        : _func(func), _arg(arg) {
    }

    result_type operator()() {
        return _func(_arg);
    }

    _Func _func;
    _Argument&  _arg;
};

template<typename _Func, typename _Argument> bind_unary_func_ref_t<_Func, _Argument> bindarg_ref(
    _Func func, _Argument& arg) {
    bind_unary_func_ref_t<_Func, _Argument> _f(func, arg);
    return _f;
}

template<typename _Class, typename _Return>
bind_unary_func_ref_t<std::mem_fun_ref_t<_Return, _Class>, _Class>
mem_fun_call(_Return(_Class::*f)(), _Class& obj) {
    return bindarg_ref(std::mem_fun_ref(f), obj);
}

template<typename _Class, typename _Argument, typename _Return>
bind_unary_func_ref_t<std::binder2nd<std::mem_fun1_ref_t<_Return, _Class, _Argument> >, _Class>
mem_fun_call(_Return(_Class::*f)(_Argument), _Class& obj, _Argument arg) {
    return bindarg_ref(std::bind2nd(std::mem_fun_ref(f), arg), obj);
}

#endif
