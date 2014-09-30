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


#include <bgcc.h>
#include "AgentProxy.h"

using namespace std;
#define Exit()\
{\
    agentPrx->Destroy();\
    return 0;\
}


int main(int argc, char** argv) {
#ifdef _WIN32
    HWND hwnd;
    hwnd = FindWindow("ConsoleWindowClass", NULL); //找到当前窗口句柄

    if (hwnd) {
        ShowWindow(hwnd, SW_HIDE);    //控制窗口不可见
    }

#endif

    AgentProxy* agentPrx = AgentProxy::Instance();

    if (!agentPrx->Init()) {
        BGCC_FATAL("ap", "AgentPrx Init Failed.");
    }

    Exit();
}

