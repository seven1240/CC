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


#include "config_reader.h"

ConfigUnit::ConfigUnit(const string& item) : m_strItem(item) {
}

ConfigUnit::~ConfigUnit() {
}

const string& ConfigUnit::to_cstr() {
    return m_strItem;
}

int ConfigUnit::to_int32() {
    return atoi(m_strItem.c_str());
}

ConfigGroup::ConfigGroup() {
}

ConfigGroup::~ConfigGroup() {
    for (map<string, ConfigUnit*>::iterator it = m_mapConfigUnit.begin(); it != m_mapConfigUnit.end();
            it++) {
        delete it->second;
        it->second = NULL;
    }
}

void ConfigGroup::Insert(const string& key, const string& value) {
    m_mapConfigUnit.insert(map<string, ConfigUnit*>::value_type(key, new ConfigUnit(value)));
}

ConfigUnit& ConfigGroup::operator[](const char* key) const {
    map<string, ConfigUnit*>::const_iterator it = m_mapConfigUnit.find(key);

    if (it == m_mapConfigUnit.end()) {
        Text errorinfo;
        snprintf(errorinfo, TEXT_LENGHT, "invalid key : %s", key);
        throw runtime_error(errorinfo);
    }

    return *(it->second);
}

bool Configure::GetSection(const string& line, string& section) {
    string::size_type index1 = line.find('[');
    string::size_type index2 = line.rfind(']');

    if (index1 == string::npos || index2 == string::npos || index1 + 1 >= index2) {
        return false;
    }

    section = line.substr(index1 + 1, index2 - index1 - 1);
    section = bgcc::StringUtil::trim(section);
    return !section.empty();
}

bool Configure::GetKeyValue(const string& line, string& key, string& value) {
    string::size_type index = line.find(':');

    if (index == string::npos || index == 0 || index + 1 == line.size()) {
        return false;
    }

    key = line.substr(0, index);
    value = line.substr(index + 1);
    key = bgcc::StringUtil::trim(key);
    value = bgcc::StringUtil::trim(value);
    return !(key.empty() || value.empty());
}

void Configure::Insert(const string& section, const string& key, const string& value) {
    map<string, ConfigGroup*>::iterator it = m_mapConfig.find(section);

    if (it == m_mapConfig.end()) {
        ConfigGroup* p = new ConfigGroup();
        p->Insert(key, value);
        m_mapConfig.insert(map<string, ConfigGroup*>::value_type(section, p));
    } else {
        it->second->Insert(key, value);
    }
}

Configure::Configure() {
}

Configure::~Configure() {
    for (map<string, ConfigGroup*>::iterator it = m_mapConfig.begin(); it != m_mapConfig.end(); it++) {
        delete it->second;
        it->second = NULL;
    }
}

ConfigGroup& Configure::operator[](const char* section) const {
    map<string, ConfigGroup*>::const_iterator it = m_mapConfig.find(section);

    if (it == m_mapConfig.end()) {
        Text errorinfo;
        snprintf(errorinfo, TEXT_LENGHT, "invalid section : %s", section);
        throw runtime_error(errorinfo);
    }

    return *(it->second);
}

bool Configure::Load(const char* dirName, const char* fileName) {
    assert(dirName != NULL);
    assert(*dirName != '\0');
    assert(fileName != NULL);
    assert(*fileName != '\0');

    string strDirName(dirName), strFileName(fileName);

    if (strDirName[strDirName.size() - 1] != PATH_FLAG) {
        strDirName.push_back(PATH_FLAG);
    }

    string strPathName = strDirName + strFileName;

    ifstream fin;
    fin.open(strPathName.c_str());

    if (!fin) {
        return false;
    }

    Text lineSS;
    string section;

    while (fin.getline(lineSS, TEXT_LENGHT)) {
        string line(lineSS);
        line = bgcc::StringUtil::trim(line);

        if (line.empty() || '#' == line[0]) {
            continue;
        }

        if (GetSection(line, section)) {
            continue;
        }

        string key, value;

        if (GetKeyValue(line, key, value) && !section.empty()) {
            Insert(section, key, value);
        }
    }

    fin.close();
    return true;
}
