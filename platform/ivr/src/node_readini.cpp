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

#include "node_readini.h"
#include "ini_file.h"

NodeReadIni::NodeReadIni(const uint32_t id, const string& name,
                         const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeReadIni::~NodeReadIni(void) {
}

NodeBase* NodeReadIni::run(base_script_t* param) {
    const char* _exit = EXIT_FAIL;

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    INIFile* conf = INIFile::get_instance();
    std::string filename;
    std::string sectionname;

    section_map_t sections;

    key_map_t* presult = NULL;

    if (parse_all(_file_name, param->name_var_map, filename)
            && parse_all(_session_name, param->name_var_map, sectionname)
            && conf->load_file(filename.c_str(), sections, true)) {

        section_map_t::iterator it = sections.find(sectionname);

        if (it == sections.end()) {
            IVR_WARN("Section(%s) not exists!", sectionname.c_str());
        } else {
            map<string, variable_t>::iterator itr = param->name_var_map.find(_map_var_name);

            if (itr == param->name_var_map.end()) {
                IVR_WARN("MapVarName(%s) not exists!", _map_var_name.c_str());
            } else if (itr->second.type != MAP) {
                IVR_WARN("variable[%s] is not map type!", _map_var_name.c_str());
            } else {
                presult = (key_map_t*)(itr->second.pvalue);
                *presult = sections[sectionname];
                _exit = EXIT_SUCC;
            }
        }
    } else {
        IVR_WARN("配置文件不存在");
    }

    IVR_TRACE("%s exit from %s(%s)",
              leave(param->name_var_map).c_str(), _exit,
              presult == NULL ? "<null>" : ivr_tools_t::map2str(*presult).c_str());
    return _exit_node_map[_exit];

}

bool NodeReadIni::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_FILE, _file_name)
           && valid_str(_key_map, PARAM_SECTION, _session_name)
           && valid_str(_key_map, PARAM_VAR, _map_var_name);
}

const char* NodeReadIni::PARAM_FILE = "filename";
const char* NodeReadIni::PARAM_SECTION = "sectionname";
const char* NodeReadIni::PARAM_VAR = "mapvarname";

std::string NodeReadIni::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "file:" << _file_name << ",section:" << _session_name << ",mapvar:" << _map_var_name;
    return ostm.str();
}

std::string NodeReadIni::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "file:" << _file_name << ",section:" << _session_name << ",mapvar:" << _map_var_name;
    return ostm.str();
}


