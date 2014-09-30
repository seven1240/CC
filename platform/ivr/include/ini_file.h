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

#ifndef _INI_FILE_H_
#define _INI_FILE_H_

#include "common.h"

class INIFile {
public:
    virtual ~INIFile();

public:
    static  INIFile* get_instance();

    bool load_file(const char* file_name, bool casesensive = false);
    void unload_file(const char* file_name, bool casesensive = false);

    int32_t get_int(
        const char* section_name,       // section name
        const char* key_name,           // key name
        int32_t default_value,          // return value if key name not found
        const char* file_name,           // initialization file name
        bool casesensive = false
    );

    int32_t get_string(
        const char* section_name,        // section name
        const char* key_name,            // key name
        const char* default_value,       // default string
        char* dest_buff,                 // destination buffer
        uint32_t buff_size,              // size of destination buffer
        const char* file_name,            // initialization file name
        bool casesensive = false
    );

    section_map_t get_section_map(const char* file_name, bool casesensive = false);
    /**
     * @brief 线程安全，对成员变量无影响
     *
     * @param [in/out] section_name   : const char*
     * @param [in/out] key_name   : const char*
     * @param [in/out] default_value   : const char*
     * @param [in/out] dest_buff   : char*
     * @param [in/out] buff_size   : uint32_t
     * @param [in/out] sections   : const section_map_t&
     * @param [in/out] casesensive   : bool
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/27 13:38:21
     **/
    int32_t get_string(
        const char* section_name, const char* key_name, const char* default_value,
        char* dest_buff, uint32_t buff_size, const section_map_t& sections,
        bool casesensive = false)const;

    /**
     * @brief 线程安全，对成员变量无影响
     *
     * @param [in/out] section_name   : const char*
     * @param [in/out] key_name   : const char*
     * @param [in/out] default_value   : int
     * @param [in/out] sections   : const section_map_t&
     * @param [in/out] casesensive   : bool
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/27 13:41:50
    **/
    int32_t get_int(
        const char* section_name, const char* key_name, int default_value,
        const section_map_t& sections, bool casesensive = false)const;

    /**
     * @brief 线程安全，对成员变量无影响
     *
     * @param [in/out] file_name   : const char*
     * @param [in/out] sections   : section_map_t&
     * @param [in/out] casesensive   : bool
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/27 13:42:03
    **/
    bool load_file(const char* file_name, section_map_t& sections, bool casesensive = false) const;
private:
    /**
     * @brief 判断字符串是否为数字
     *
     * @param [in/out] str   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/25 11:46:30
     **/
    bool is_number(const char* str)const;

    map<string, section_map_t> _file_map;
};

#endif
