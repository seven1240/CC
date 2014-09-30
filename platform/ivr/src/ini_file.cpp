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

#include "tools.h"
#include "ini_file.h"
#include <fstream>

INIFile::~INIFile() {
    _file_map.clear();
}

INIFile* INIFile::get_instance() {
    static INIFile mgr;
    return &mgr;
}

bool INIFile::load_file(const char* file_name, section_map_t& sections, bool casesensive)const {
    IVR_DEBUG("load ini file(%s)", file_name == NULL ? "" : file_name);
    std::auto_ptr<std::ifstream> tmpfs(new std::ifstream(file_name));
    std::ifstream& fp = *tmpfs;

    if (!fp) {
        return false;
    }

    key_map_t keys;
    string filename = file_name;

    if (!casesensive) {
        transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
    }

    char szbuf[1024];
    string line;
    bool has_read = false;

    while (!fp.eof() && !fp.fail()) {//用来搞定section
        if (!has_read) {
            fp.getline(szbuf, 1024);

            if (szbuf[0] == '#' || szbuf[0] == ';' || szbuf[0] == '\0') {
                continue;
            }

            line = szbuf;
            ivr_tools_t::trim(line);
            //            if(!casesensive){
            //                transform(line.begin(), line.end(), line.begin(), ::tolower);
            //            }
        } else {
            has_read = false;
        }

        if (line.size() == 0) {
            continue;
        }

        uint32_t first_pos = line.find_first_not_of(' ');

        if (line[first_pos] != '[') {
            continue;
        }

        uint32_t last_pos = line.find_last_not_of(' ');

        if (line[last_pos] != ']') {
            continue;
        }

        if (last_pos - first_pos <= 1) {
            continue;
        }

        string section = line.substr(first_pos + 1, last_pos - first_pos - 1);
        ivr_tools_t::trim(section);

        if (!casesensive) {
            transform(section.begin(), section.end(), section.begin(), ::tolower);
        }

        keys.clear();

        while (!fp.eof() && !fp.fail()) {//用来搞定section内部的key:value
            fp.getline(szbuf, 1024);

            if (szbuf[0] == '#' || szbuf[0] == ';' || szbuf[0] == '\0') {
                continue;
            }

            line = szbuf;
            ivr_tools_t::trim(line);

            //            if(!casesensive){
            //                transform(line.begin(), line.end(), line.begin(), ::tolower);
            //            }
            if (line.size() == 0) {
                continue;
            }

            first_pos = line.find_first_not_of(' ');

            if (line[first_pos] == '=') {
                continue;
            }

            if (line[first_pos] == '[') {
                has_read = true;
                break;
            }

            last_pos = line.find_last_not_of(' ');

            if (last_pos - first_pos <= 1) {
                continue;
            }

            int32_t pos0 = line.find_first_of('=');

            if (pos0 == -1) {
                continue;
            }

            int32_t pos = line.find_last_not_of(' ', pos0 - 1);

            string key = line.substr(first_pos, pos - first_pos + 1);

            if (!casesensive) {
                transform(key.begin(), key.end(), key.begin(), ::tolower);
            }

            pos = line.find_first_not_of(' ', pos0 + 1);
            string value;

            if (pos == -1) {
                value = "";
            } else {
                value = line.substr(pos);
            }

            ivr_tools_t::trim(key);
            ivr_tools_t::trim(value);
            keys[key] = value;
        }

        sections[section] = keys;
    }

    fp.close();

    return true;

    /*
    if(sections.size()){
       _file_map[filename]=sections;
    }
    */

}

bool INIFile::load_file(const char* file_name, bool casesensive) {
    unload_file(file_name, casesensive);

    section_map_t sections;

    if (load_file(file_name, sections, casesensive)) {
        if (sections.size()) {
            _file_map[file_name] = sections;
        }
    }

    return _file_map.size();
}

void INIFile::unload_file(const char* file_name, bool casesensive) {
    string filename = file_name;

    if (!casesensive) {
        transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
    }

    if (_file_map.find(filename) == _file_map.end()) {
        return;
    }

    section_map_t& sections = _file_map[filename];

    section_map_t::iterator it = sections.begin();

    for (; it != sections.end(); it++) {
        it->second.clear();
    }

    sections.clear();

    _file_map.erase(filename);

}

int32_t INIFile::get_int(
    const char* section_name,
    const char* key_name,
    int default_value,
    const section_map_t& sections,
    bool casesensive)const {

    int rt = default_value;
    std::string tmp = section_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    section_map_t::const_iterator it = sections.find(tmp);

    if (it == sections.end()) {
        return rt;
    }

    const key_map_t& keys = it->second;

    tmp = key_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    key_map_t::const_iterator it2 = keys.find(tmp);

    if (it2 == keys.end()) {
        return rt;
    }

    if (is_number(it2->second.c_str())) {
        rt = atoi(it2->second.c_str());
    }

    return rt;

}


int32_t INIFile::get_int(
    const char* section_name,
    const char* key_name,
    int default_value,
    const char* file_name,
    bool casesensive) {
    int rt = default_value;

    string tmp = file_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    if (_file_map.find(tmp) == _file_map.end()) {
        return rt;
    }

    section_map_t& sections = _file_map[tmp];

    return get_int(section_name, key_name, default_value, sections, casesensive);

}
int32_t INIFile::get_string(
    const char* section_name,
    const char* key_name,
    const char* default_value,
    char* dest_buff,
    uint32_t buff_size,
    const section_map_t& sections,
    bool casesensive) const {
    std::string tmp = section_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    section_map_t::const_iterator it = sections.find(tmp);

    if (it == sections.end()) {
        strcpy(dest_buff, default_value);
        return 0;
    }

    const key_map_t& keys = it->second;

    tmp = key_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    key_map_t::const_iterator it2 = keys.find(tmp);

    if (it2 == keys.end()) {
        strcpy(dest_buff, default_value);
        return 0;
    }

    const string& value = it2->second;
    uint32_t len = value.length();

    if (buff_size <= len) {
        strcpy(dest_buff, value.substr(0, buff_size - 1).c_str());
        len = buff_size - 1;
    } else {
        strcpy(dest_buff, value.c_str());
    }

    return len;

}
int32_t INIFile::get_string(
    const char* section_name,
    const char* key_name,
    const char* default_value,
    char* dest_buff,
    uint32_t buff_size,
    const char* file_name,
    bool casesensive
) {
    string tmp = file_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    if (_file_map.find(tmp) == _file_map.end()) {
        strcpy(dest_buff, default_value);
        return 0;
    }

    section_map_t& sections = _file_map[tmp];

    return get_string(section_name, key_name, default_value, dest_buff, buff_size, sections,
                      casesensive);
}

section_map_t INIFile::get_section_map(const char* file_name, bool casesensive) {
    string tmp = file_name;

    if (!casesensive) {
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    }

    if (_file_map.find(tmp) != _file_map.end()) {
        return _file_map[tmp];
    }

    return section_map_t();
}


bool INIFile::is_number(const char* str) const {
    const char* pstr = str;

    while (pstr && (*pstr)) {
        if ((*pstr) >= '0' && (*pstr) <= '9') {
            ++pstr;
            continue;
        } else {
            break;
        }
    }

    return (pstr && 0 == (*pstr));
}

