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


#include <iomanip>
#include "acd_tool.h"

void ShowVersion() {
    cout << "Auto Call Distribution Server " << ACD_VERSION << endl;
}

void ShowHelp() {
    ShowVersion();
    cout << left << setw(20) << "--help, -h" << "Show this help page." << endl;
    cout << left << setw(20) << "--version, -v" << "Show version." << endl;
    cout << left << setw(20) << "--config, -c" << "Reload config file." << endl;
}

void ResetConfig() {
    string password;
    cout << "input password: ";
    cin >> password;

    acd::acdapiProxy proxy(bgcc::ServerInfo("127.0.0.1", (uint16_t)acd_tool::LocalPort()));
    acd::AcdResultT ret = acd::AcdResultT::ArSuccess;
    ret = proxy.ResetConfig(password);

    if (proxy.get_errno() != 0) {
        cout << "communication error, reset config fail!" << endl;
        exit(0);
    }

    if (acd::AcdResultT::ArSuccess == ret) {
        cout << "reset config success!" << endl;
    } else if (acd::AcdResultT::ArPasswordError == ret) {
        cout << "wrong password, reset config fail!" << endl;
    } else {
        cout << "error, reset config fail!" << endl;
    }
}

#if WIN32
char getopt(int argc, char* argv[], const string& opt) {
    if (2 != argc) {
        return 0;
    }

    string optinput(argv[1]);

    if (2 != optinput.size() || '-' != optinput[0]) {
        return 0;
    }

    if (string::npos == opt.find(optinput[1])) {
        return 0;
    } else {
        return optinput[1];
    }
}
#else
struct option long_options[] = {
    // name,      has_arg,  flag,      val
    {"config",    0,        NULL,      'c'},
    {"help",      0,        NULL,      'h'},
    {"version",   0,        NULL,      'v'},
    {NULL,        0,        NULL,      0}
};
#endif

int main(int argc, char* argv[]) {
    if (1 == argc) {
        acd_tool::init();
        acd_tool::un_init();
    } else {
#if WIN32
        char c = getopt(argc, argv, "hvc");
#else
        char c = getopt_long(argc, argv, "hvc", long_options, NULL);
#endif

        if (c == -1) {
            return 0;
        }

        switch (c) {
        case 'h':
            ShowHelp();
            break;

        case 'v':
            ShowVersion();
            break;

        case 'c':
            ResetConfig();
            break;

        default:
            ShowHelp();
            break;
        }
    }

    return 0;
}
