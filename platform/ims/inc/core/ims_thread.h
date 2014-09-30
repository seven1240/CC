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

#ifndef  _IMS_THREAD_H_
#define  _IMS_THREAD_H_

#include <bgcc.h>

namespace ims {

class ims_thread_t: public bgcc::Thread {
public:
    ims_thread_t(bgcc::RunnableSP runner)
        : bgcc::Thread(runner, true), _runner(runner) {} //detached mode

    bgcc::RunnableSP get_runner() {
        return _runner;
    }

private:

    bgcc::RunnableSP _runner;
};

typedef bgcc::SharedPointer<ims_thread_t>  ims_thread_ptr;

};





#endif  //_IMS_THREAD_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
