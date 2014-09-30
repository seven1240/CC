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

#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include "const_define.h"

using namespace std;

class ConfigUnit {
private:
    string m_strItem;

public:
    ConfigUnit(const string& item);
    ~ConfigUnit();
    const string& to_cstr();
    int to_int32();
};

class ConfigGroup {
private:
    map<string, ConfigUnit*> m_mapConfigUnit;

public:
    ConfigGroup();
    ~ConfigGroup();
    void Insert(const string& key, const string& value);
    ConfigUnit& operator[](const char* key) const;
};

class Configure {
private:
    map<string, ConfigGroup*> m_mapConfig;

private:
    bool GetSection(const string& line, string& section);
    bool GetKeyValue(const string& line, string& key, string& value);
    void Insert(const string& section, const string& key, const string& value);

public:
    Configure();
    ~Configure();
    ConfigGroup& operator[](const char*) const;
    bool Load(const char* dirName, const char* fileName);
};
