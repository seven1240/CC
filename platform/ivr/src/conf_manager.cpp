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
#include "conf_manager.h"
#include "flow_manager.h"
#include "db_pool.h"
#include "common.h"
#include "fs_info.h"
#include "fs_mgr.h"
#include "ims/ims_mgr.h"
#include "thread_pool.h"
#include "lock.h"
#include <autorun_manager.h>

extern string g_server_ip;
extern uint32_t g_server_port;
extern call_data_conf_t g_calldata_conf;
extern FlowManager g_flowmanager_autorun;
extern FlowManager g_flowmanager_inbound;

extern inbound_conf_t  g_inbound_conf;
extern autorun_conf_t  g_autorun_conf;
extern DBPool* g_dbpool;

const char* ConfManager::SCRIPT = "script";
const char* ConfManager::FREESWITCH = "freeswitch";
const char* ConfManager::CONN = "conn";
const char* ConfManager::IMS = "ims";

ConfManager::ConfManager(const std::string sys_file,
                         const std::string in_file,
                         const std::string auto_file):
    _sys_file(sys_file), _in_file(in_file), _auto_file(auto_file) {
}

ConfManager::~ConfManager() {
    unload_conf();
}

int32_t ConfManager::load_max_chan_num() {
    return load_max_chan_num(g_inbound_conf.max_inbound_chan_num, g_autorun_conf.max_autorun_chan_num,
                             g_inbound_conf.max_autodial_chan_num);
}

int32_t ConfManager::load_max_chan_num(uint32_t& max_inbound, uint32_t& max_autorun,
                                       uint32_t& max_autodial) {

    INIFile* conf = INIFile::get_instance();

    //inbound.conf
    if (!conf->load_file(_in_file.c_str(), true)) {
        IVR_FATAL("load_conf_file inbound_conf fail");
        return FAILURE;
    }

    max_inbound = conf->get_int("general", "maxinboundchannum", 0, _in_file.c_str(), true);

    if (0 == max_inbound) {
        IVR_FATAL("[General] MaxInboundChanNum not find in inbound.conf");
        return FAILURE;
    }

    max_autodial = conf->get_int("general", "maxautodialchannum", 0, _in_file.c_str(), true);

    if (0 > max_autodial) {
        IVR_FATAL("[General] MaxAutoDialChanNum not find in inbound.conf");
        return FAILURE;
    }

    //autorun.conf
    if (!conf->load_file(_auto_file.c_str(), true)) {
        IVR_FATAL("load_conf_file autorun_conf fail");
        return FAILURE;
    }

    max_autorun = conf->get_int("general", "maxautorunchannum", 0, _auto_file.c_str(), true);

    //外呼通道允许数量为0
    return SUCCESS;
}


int32_t ConfManager::load_esllog_conf(int32_t& enable) {
    INIFile* conf = INIFile::get_instance();

    //system.conf
    if (!conf->load_file(_sys_file.c_str(), true)) {
        IVR_TRACE("load_conf_file system.conf fail");
        return FAILURE;
    }

    enable = conf->get_int("general", "esllog", enable, _sys_file.c_str(), true);

    if (0 == enable) {
        IVR_TRACE("[General] disalble esl log file!");
    } else {
        IVR_TRACE("[General] enable esl log file!");
    }

    return SUCCESS;
}

int32_t ConfManager::load_system_conf() {
    INIFile* conf = INIFile::get_instance();

    //system.conf
    if (!conf->load_file(_sys_file.c_str(), true)) {
        IVR_TRACE("load_conf_file system.conf fail");
        return FAILURE;
    }

    IVR_TRACE("---------------[System]-[General]---------------------------------");

    char ip[16] = {0};           //load ip
    conf->get_string("general", "ip", "127.0.0.1", ip, 16, _sys_file.c_str(), true);
    g_server_ip = ip;
    IVR_TRACE("Ip = %s", g_server_ip.c_str());

    g_server_port = conf->get_int("general", "port", 0, _sys_file.c_str(), true);

    if (0 == g_server_port) {  //load port
        IVR_FATAL("[General] Port not find in system.conf");
        return FAILURE;
    }

    if (g_server_port > 0 && g_server_port <= 65535) {
        IVR_TRACE("Port = %d", g_server_port);
    } else {
        IVR_FATAL("[General] Port not in [1-65535] system.conf");
        return FAILURE;
    }

    g_output_esllog = conf->get_int("general", "esllog", 1, _sys_file.c_str(), true);

    if (0 == g_output_esllog) {
        IVR_TRACE("[General] disalble esl log file!");
    } else {
        IVR_TRACE("[General] enable esl log file!");
    }

    g_reload_port = conf->get_int("general", "reloadport", 0, _sys_file.c_str(), true);

    if (0 == g_reload_port) {
        IVR_TRACE("[General] reload port not find in system.conf!");
    } else {
        IVR_TRACE("[General] reload port(%u)!", g_reload_port);
    }

    IVR_TRACE("---------------[System]-[Connect]---------------------------------");

    g_dbpool = new DBPool();
    //load [conn***]
    vector<uint32_t> conn_idx_vec;
    section_map_t section_map = conf->get_section_map(_sys_file.c_str(), true);
    ivr_tools_t::idx2vec(CONN, section_map, conn_idx_vec);
    ostringstream conn_name;

    for (uint32_t ii = 0; ii < conn_idx_vec.size(); ++ii) {
        conn_name.str("");
        conn_name << CONN << conn_idx_vec[ii];
        key_map_t key_map = section_map[conn_name.str()];

        string connstr = key_map["connstr"];
        vector<string> vec;
        ivr_tools_t::split_string(connstr, ";", vec);

        if (vec.size() != 3) {
            IVR_WARN("conn str not match(**;**;**) [%s] !!!",
                     conn_name.str().c_str());
            continue;
        }

        string host = "tcp://" + vec[0];
        string user = vec[1];
        string passwd = vec[2];
        uint32_t conn_num = 0;
        string conn_num_str = key_map["connnum"];

        if (ivr_tools_t::is_positive_integer(conn_num_str)) {
            conn_num = atoi(conn_num_str.c_str());
        } else {
            IVR_WARN("conn num not number [%s] !!!",
                     conn_name.str().c_str());
            continue;
        }

        uint32_t timeout = 3;

        if (g_dbpool->create_container_to_pool
                (conn_idx_vec[ii], host, user, passwd, conn_num, timeout) != SUCCESS) {
            IVR_WARN("Load db conn failure host=%s user=%s pwd=%s conn_num=%u [%s] !!!",
                     host.c_str(), user.c_str(), passwd.c_str(), conn_num,
                     conn_name.str().c_str());
            return FAILURE;
        }

        IVR_TRACE("Load db [%s] success host=%s user=%s conn_num=%u",
                  conn_name.str().c_str(), host.c_str(),
                  user.c_str(), conn_num);
    }

    IVR_TRACE("---------------[System]-[Freeswitch]---------------------------------");
    vector<uint32_t> fs_idx_vec;
    ivr_tools_t::idx2vec(FREESWITCH, section_map, fs_idx_vec);
    ostringstream fs_name;

    for (uint32_t ii = 0; ii < fs_idx_vec.size(); ++ii) {
        fs_name.str("");
        fs_name << FREESWITCH << fs_idx_vec[ii];
        key_map_t key_map = section_map[fs_name.str()];
        //Get ip
        uint32_t ip = 0;
        string str_ip = key_map["ip"];

        if (!ivr_tools_t::check_ip(str_ip.c_str(), ip)) {
            IVR_WARN("Freeswitch [%u] ip invalid [%s] !!!",
                     fs_idx_vec[ii], str_ip.c_str());
            continue;
        }

        //Get port
        uint32_t port = 0;
        string str_port = key_map["port"];

        if (!ivr_tools_t::check_port(str_port.c_str(), port)) {
            IVR_WARN("Freeswitch [%u] port invalid [%s] !!!",
                     fs_idx_vec[ii], str_port.c_str());
            continue;
        }

        //Get user
        string user = key_map["user"];

        //Get password
        string passwd = key_map["password"];

        //Get Max handle
        uint32_t max_handles = 0;
        string str_handle = key_map["maxsendhandle"];

        if (ivr_tools_t::is_positive_integer(str_handle)) {
            max_handles = atoi(str_handle.c_str());
        } else {
            IVR_WARN("Freeswitch [%u] maxhandlenum number invalid [%s] !!!",
                     fs_idx_vec[ii], str_handle.c_str());
            continue;
        }

        fs_info_t info(fs_idx_vec[ii], ip, port, max_handles, user.c_str(), passwd.c_str());

        if (IVR_SUCCESS != fs_mgr_t::instance()->add_fs(info)) {
            IVR_FATAL("Load Freeswitch Fail: No=%u, ip=%u, port=%u, user=%s, pswd=%s",
                      fs_idx_vec[ii], ip, port, user.c_str(), passwd.c_str());
            raise(SIGKILL);
        }

        IVR_TRACE("Read Freeswitch Succ: No=%u, ip=%u, port=%u, user=%s, pass=%s, max=%d",
                  fs_idx_vec[ii], ip, port, user.c_str(), passwd.c_str(), max_handles);

    }

    IVR_TRACE("---------------[System]-[CallData]---------------------------------");

    char filename[512] = {0};    //load calldata conf
    conf->get_string("calldata", "filename", "", filename, 512, _sys_file.c_str(), true);
    g_calldata_conf.file_name = filename;

    if ("" == g_calldata_conf.file_name) {
        IVR_FATAL("[CallData] FileName not find in system.conf");
        return FAILURE;
    }

    IVR_TRACE("FileName = %s", g_calldata_conf.file_name.c_str());

    g_calldata_conf.generate_interval =
        conf->get_int("calldata", "generateinterval", 0, _sys_file.c_str(), true);

    if (g_calldata_conf.generate_interval <= 0) {
        IVR_FATAL("[CallData] GenerateInterval not find in system.conf");
        return FAILURE;
    }

    IVR_TRACE("GenerateInterval = %u", g_calldata_conf.generate_interval);

    g_calldata_conf.generate_file_size =
        conf->get_int("calldata", "generatefilesize", 0, _sys_file.c_str(), true);

    if (g_calldata_conf.generate_file_size <= 0) {
        IVR_FATAL("[CallData] GenerateFileSize not find in system.conf");
        return FAILURE;
    }

    IVR_TRACE("GenerateFileSize = %u", g_calldata_conf.generate_file_size);

    char generatepath[512] = {0};
    conf->get_string(
        "calldata", "generatepath", "", generatepath, 512, _sys_file.c_str(), true);
    g_calldata_conf.generate_path = generatepath;

    if ("" == g_calldata_conf.generate_path) {
        IVR_WARN("[CallData] GeneratePath not find in system.conf,adjust to ./generate/");
        g_calldata_conf.generate_path = "./generate/";
    } else {
        g_calldata_conf.generate_path += "/";
    }

    IVR_TRACE("GeneratePath = %s", g_calldata_conf.generate_path.c_str());

    char sendtopath[512] = {0};
    conf->get_string(
        "calldata", "sendtopath", "", sendtopath, 512, _sys_file.c_str(), true);
    g_calldata_conf.sendto_path = sendtopath;

    if ("" == g_calldata_conf.sendto_path) {
        IVR_WARN("[CallData] SendToPath not find in system.conf,adjust to ./sendto/");
        g_calldata_conf.sendto_path = "./sendto/";
    } else {
        g_calldata_conf.sendto_path += "/";
    }

    IVR_TRACE("SendToPath = %s", g_calldata_conf.sendto_path.c_str());

    IVR_TRACE("---------------[System]-[IMS]---------------------------------");
    vector<uint32_t> ims_idx_vec;
    ivr_tools_t::idx2vec(IMS, section_map, ims_idx_vec);
    ostringstream ims_name;
    uint32_t first_suc = (uint32_t) - 1;
    bool is_seted_default = false;
    bool is_reseted_first = false;

    for (uint32_t ii = 0; ii < ims_idx_vec.size(); ++ii) {
        ims_name.str("");
        ims_name << IMS << ims_idx_vec[ii];
        key_map_t key_map = section_map[ims_name.str()];
        //Get ip
        uint32_t ip;
        string str_ip = key_map["ip"];

        if (!ivr_tools_t::check_ip(str_ip.c_str(), ip)) {
            IVR_WARN("IMS [%d] ip invalid [%s] !!!",
                     ims_idx_vec[ii], str_ip.c_str());
            continue;
        }

        //Get port
        uint32_t port = 0;
        string str_port = key_map["port"];

        if (!ivr_tools_t::check_port(str_port.c_str(), port)) {
            IVR_WARN("IMS [%d] port invalid [%s] !!!",
                     ims_idx_vec[ii], str_port.c_str());
            continue;
        }

        int32_t ismain = 0;
        string str_main = key_map["is_main"];

        if (str_main == "1") {
            ismain = 1;
        }

        ims_info_t ims(ims_idx_vec[ii], str_ip, port);
        IVR_TRACE("add new ims[%d] ip(%s), port(%d), ismain(%d)",
                  ims_idx_vec[ii], str_ip.c_str(), port, ismain);
        ims_mgr_t::get_instance()->add_ims(ims);

        if (!is_reseted_first) {
            first_suc = ims_idx_vec[ii];
            is_reseted_first = true;
        }

        if (ismain) {
            ims_mgr_t::get_instance()->set_default_ims(ims_idx_vec[ii]);
            is_seted_default = true;
        }
    }

    if (!is_seted_default && is_reseted_first) {
        ims_mgr_t::get_instance()->set_default_ims(first_suc);
        is_seted_default = true;
    } else if (!is_seted_default && !is_reseted_first) {
        IVR_WARN("no successful ims found!");
    }

    IVR_TRACE("load system.conf done!");

    return SUCCESS;
}

int32_t ConfManager::load_inbound_conf(FlowManager& fm, inbound_conf_t& inconf) {
    INIFile* inifile = INIFile::get_instance();

    //inbound.conf
    if (!inifile->load_file(_in_file.c_str(), true)) {
        IVR_FATAL("load_conf_file inbound_conf fail");
        return FAILURE;
    }

    //inbound.inifile
    IVR_TRACE("---------------[Inbound]-[General]---------------------------------");

    inconf.max_inbound_chan_num =
        inifile->get_int("general", "maxinboundchannum", 0, _in_file.c_str(), true);

    if (inconf.max_inbound_chan_num <= 0) {
        IVR_FATAL("[General] Correct MaxInboundChanNum not find in %s",
                  _in_file.c_str());
        return FAILURE;
    }

    IVR_TRACE("MaxInboundChanNum = %u", inconf.max_inbound_chan_num);

    inconf.max_autodial_chan_num =
        inifile->get_int("general", "maxautodialchannum", 0, _in_file.c_str(), true);

    if (inconf.max_autodial_chan_num < 0) { // zero is ok here
        IVR_FATAL("[General] Correct MaxAutodialChanNum not find in %s",
                  _in_file.c_str());
        return FAILURE;
    }

    IVR_TRACE("MaxAutoDialChanNum = %u", inconf.max_autodial_chan_num);

    section_map_t section_map = inifile->get_section_map(_in_file.c_str());

    //load [script***]
    vector<uint32_t> script_idx_vec;
    ivr_tools_t::idx2vec(SCRIPT, section_map, script_idx_vec);

    for (uint32_t i = 0; i < script_idx_vec.size(); ++i) {

        inbound_script_t script;
        script.type = base_script_t::INBOUND;
        script.imsno = (uint32_t) - 1;
        script.imssid = 0;
        script.requestId = 0;
        script.session_id = 0;
        script.flow = NULL;

        ostringstream script_name;
        script_name << "script" << script_idx_vec[i];
        key_map_t key_map = section_map[script_name.str()];

        script.dnis = key_map["dnis"];

        if ("" == script.dnis) {
            IVR_WARN("[%s] Dnis not find in inbound.inifile Ignore [%s] !!!",
                     script_name.str().c_str(), script_name.str().c_str());
            continue;
        }

        script.desc = key_map["desc"];//desc允许为空字符串

        script.vox_base = key_map["voxbase"];//允许为空，使用fs的默认路径
        script.flow_name = key_map["flowfile"];

        if ("" == script.flow_name) {
            IVR_WARN("[%s] FlowFile not find in inbound.inifile Ignore [%s] !!!",
                     script_name.str().c_str(), script_name.str().c_str());
            continue;
        }

        //load flow
        if (fm.load_flow(script.flow_name, &script.flow) != SUCCESS) {
            IVR_WARN("[%s] FlowFile=%s not load Ignore [Inbound]-[%s] !!!",
                     script_name.str().c_str(), script.flow_name.c_str(),
                     script_name.str().c_str());
            continue;
        } else {
            IVR_TRACE("[%s] FlowFile=%s load success [Inbound]-[%s] !!!",
                      script_name.str().c_str(), script.flow_name.c_str(),
                      script_name.str().c_str());
        }

        IVR_TRACE("####################[Inbound]-[%s]###########################",
                  script_name.str().c_str());
        IVR_TRACE("Dnis = %s", script.dnis.c_str());
        IVR_TRACE("Desc = %s", script.desc.c_str());
        IVR_TRACE("FlowFile = %s", script.flow_name.c_str());
        IVR_TRACE("VoxBase = %s", script.vox_base.c_str());

        IVR_TRACE("-----------------[Inbound]-[%s]-加载成功---------------------",
                  script_name.str().c_str());

        // check if existing same dnis script, dec ref count of before flow
        if (inconf.dnis_script_map.find(script.dnis) != inconf.dnis_script_map.end()) {
            // dec refcount first
            IVR_WARN("find one more inbound scirpt using dnis %s", script.dnis.c_str());
            FlowManager::detach_flow(&inconf.dnis_script_map[script.dnis].flow);
        }

        inconf.dnis_script_map[script.dnis] = script;
    }

    //load [Default]

    inconf.has_default = false;

    char tmp[512] = {0};
    inifile->get_string("-", "flowfile", "", tmp, 512, _in_file.c_str(), true);
    inconf.default_script.flow_name = tmp;

    inifile->get_string("-", "desc", "", tmp, 512, _in_file.c_str(), true);
    inconf.default_script.desc = tmp;

    inifile->get_string("-", "voxbase", "", tmp, 512, _in_file.c_str(), true);
    inconf.default_script.vox_base = tmp;

    //load flow
    if (fm.load_flow(inconf.default_script.flow_name, &inconf.default_script.flow) != SUCCESS) {
        IVR_WARN("[Default] FlowFile=%s not load Ignore [Inbound]-[Default] !!!",
                 inconf.default_script.flow_name.c_str());
    } else {
        inconf.has_default = true;
        IVR_TRACE("[Default] FlowFile=%s load success [Inbound]-[Default] !!!",
                  inconf.default_script.flow_name.c_str());

        IVR_TRACE("##################[Inbound]-[Default]########################");
        IVR_TRACE("Desc = %s", inconf.default_script.desc.c_str());
        IVR_TRACE("FlowFile = %s", inconf.default_script.flow_name.c_str());
        IVR_TRACE("VoxBase = %s", inconf.default_script.vox_base.c_str());
        IVR_TRACE("---------------[Inbound]-[Default]-[-]-加载成功--------------");
    }


    return SUCCESS;
}

int32_t ConfManager::load_autorun_conf(FlowManager& fm, autorun_conf_t& autoconf) {
    INIFile* inifile = INIFile::get_instance();

    //autorun.conf
    if (!inifile->load_file(_auto_file.c_str(), true)) {
        IVR_FATAL("load_conf_file autorun_conf(%s) fail", _auto_file.c_str());
        return FAILURE;
    }

    //autorun.conf
    IVR_TRACE("---------------[AutoRun]-[General]---------------------------------");

    autoconf.max_autorun_chan_num =
        inifile->get_int("general", "maxautorunchannum", 0, _auto_file.c_str(), true);

    IVR_TRACE("maxautorunchannum = %u", autoconf.max_autorun_chan_num);

    if (autoconf.max_autorun_chan_num <= 0) {//允许最大外呼通道数为0
        IVR_WARN("[General] Correct MaxAutoRunChanNum not find in autorun.inifile");
        return SUCCESS;
    }

    section_map_t section_map = inifile->get_section_map(_auto_file.c_str());

    //load [script***]
    vector<uint32_t> script_idx_vec;
    ivr_tools_t::idx2vec(SCRIPT, section_map, script_idx_vec);

    for (uint32_t i = 0; i < script_idx_vec.size(); ++i) {
        autorun_script_t script;
        script.type = base_script_t::AUTOBOUND;

        ostringstream script_name;
        script_name << "script" << script_idx_vec[i];
        key_map_t key_map = section_map[script_name.str()];

        script.desc = key_map["desc"];//desc允许为空字符串

        script.flow_name = key_map["flowfile"];

        if ("" == script.flow_name) {
            IVR_WARN("[%s] FlowFile not find in autorun.inifile Ignore [%s] !!!",
                     script_name.str().c_str(), script_name.str().c_str());
            continue;
        }

        script.vox_base = key_map["voxbase"];//允许为空，默认使用fs的配置路径
        script.is_write_bill = (key_map["bill"] != "0");

        string tmp = key_map["runchannum"];

        if (ivr_tools_t::is_positive_integer(tmp)) {
            script.autorun_chan_num = atoi(tmp.c_str());
        } else {
            script.autorun_chan_num = 1;
            IVR_WARN("[%s] RunChanNum not valid,adjust to 1 [%s] !!!",
                     script_name.str().c_str(), script_name.str().c_str());
        }

        tmp = key_map["runinterval"];

        if (ivr_tools_t::is_positive_integer(tmp)) {
            script.autorun_interval = atoi(tmp.c_str());
        } else {
            script.autorun_interval = 10;
            IVR_WARN("[%s] RunInterval not valid,adjust to 10s [%s] !!!",
                     script_name.str().c_str(), script_name.str().c_str());
        }

        //load flow
        if (fm.load_flow(script.flow_name, &script.flow) != SUCCESS) {
            IVR_WARN("[%s] FlowFile=%s not load Ignore [AutoRun]-[%s] !!!",
                     script_name.str().c_str(), script.flow_name.c_str(),
                     script_name.str().c_str());
            continue;
        } else {
            IVR_TRACE("[%s] FlowFile=%s load success [AutoRun]-[%s] !!!",
                      script_name.str().c_str(), script.flow_name.c_str(),
                      script_name.str().c_str());
        }

        IVR_TRACE("#######################[AutoRun]-[%s]#######################",
                  script_name.str().c_str());
        IVR_TRACE("Desc = %s", script.desc.c_str());
        IVR_TRACE("FlowFile = %s", script.flow_name.c_str());
        IVR_TRACE("VoxBase = %s", script.vox_base.c_str());
        IVR_TRACE("RunChanNum = %u", script.autorun_chan_num);
        IVR_TRACE("RunInterval = %u", script.autorun_interval);
        IVR_TRACE("-----------------[AutoRun]-[%s]-加载成功---------------------",
                  script_name.str().c_str());

        script.flow->ref_count = 1;
        autoconf.autorun_script_vec.push_back(script);
    }

    return SUCCESS;
}

int32_t ConfManager::load_conf() {
    if (load_system_conf() != SUCCESS) {
        return FAILURE;
    }

    if (load_inbound_conf(g_flowmanager_inbound, g_inbound_conf) != SUCCESS) {
        return FAILURE;
    }

    if (load_autorun_conf(g_flowmanager_autorun, g_autorun_conf) != SUCCESS) {
        return FAILURE;
    }

    return SUCCESS;
}

int32_t ConfManager::reload_conf(conf_reload_flag_t flag) {
    IVR_TRACE("try reload config type(%s)", flag.get_desc().c_str());
    unload_conf();
    // add a lock here, make sure only one to reload
    static bgcc::Mutex _reload_mutex;
    locker_t _reload_lock(&_reload_mutex);

    if (!_reload_lock.is_locked()) {
        IVR_WARN("reload lock failed!");
        IVR_TRACE("reload finished with error!");
        return FAILURE;
    }

    IVR_DEBUG("reload(%s) starting", flag.get_desc().c_str());
    FlowManager tmpfm;
    bool is_need_reload_inbound = false;
    bool is_need_reload_autorun = false;
    uint32_t max_inbound = g_inbound_conf.max_inbound_chan_num;
    uint32_t max_autodial = g_inbound_conf.max_autodial_chan_num;
    uint32_t max_autorun = g_autorun_conf.max_autorun_chan_num;
    inbound_conf_t in_conf;
    autorun_conf_t au_conf;

    FlowManager tmpfm_in;
    FlowManager tmpfm_au;

    if (flag == conf_reload_flag_t::ReloadInBound || flag == conf_reload_flag_t::ReloadAll) {
        // load inbound information in tmp datastruct
        if (load_inbound_conf(tmpfm_in, in_conf) == SUCCESS) {
            is_need_reload_inbound = true;
            max_inbound = in_conf.max_inbound_chan_num;
        } else {
            IVR_TRACE("reload inbound conf failed!");
            IVR_TRACE("reload finished with error!");
            return FAILURE;
        }
    }

    if (flag == conf_reload_flag_t::ReloadAutorun || flag == conf_reload_flag_t::ReloadAll) {
        // load autorun information in tmp datastruct
        if (load_autorun_conf(tmpfm_au, au_conf) == SUCCESS) {
            is_need_reload_autorun = true;
            max_autorun = au_conf.max_autorun_chan_num;
        } else {
            IVR_TRACE("reload autorun conf failed!");
            IVR_TRACE("reload finished with error!");
            return FAILURE;
        }
    }

    int32_t enable_esllog = g_output_esllog;

    if (flag == conf_reload_flag_t::ReloadEslLog || flag == conf_reload_flag_t::ReloadAll) {
        // get esllog flag, update when reload success
        if (load_esllog_conf(enable_esllog) == 0) {
            IVR_TRACE("reload esllog conf, result(%d)", enable_esllog);
        }
    }

    if (flag == conf_reload_flag_t::ReloadThreadCount || flag == conf_reload_flag_t::ReloadAll) {
        // get thread count here
        if (SUCCESS != load_max_chan_num(max_inbound, max_autorun, max_autodial)) {
            IVR_TRACE("reload max chan num failed!");
            return FAILURE;
        }
    }

    // update thread count first
    if (max_inbound >= 0 && max_autorun >= 0 && max_autodial >= 0 &&
            max_inbound + max_autorun + max_autodial < MAX_THREAD_NUM) {
        IVR_TRACE("try to reset thread pool threads, max_inbound(%d), max_autorun(%d), max_autodial(%d)",
                  max_inbound, max_autorun, max_autodial);
        int32_t max_chan_num = max_inbound + max_autorun + max_autodial;
        ThreadPool* threadpool = ThreadPool::get_instance();
        threadpool->initialize_threads(max_chan_num);
    } else {
        in_conf.max_inbound_chan_num = g_inbound_conf.max_inbound_chan_num;
        in_conf.max_autodial_chan_num = g_inbound_conf.max_autodial_chan_num;
        au_conf.max_autorun_chan_num = g_autorun_conf.max_autorun_chan_num;
        IVR_WARN("failed to reset thread pool threads, max_inbound(%d), max_autorun(%d), max_autodial(%d)",
                 max_inbound, max_autorun, max_autodial);
    }

    if (is_need_reload_inbound) {
        IVR_TRACE("reload inbound conf!");
        rw_lock_t lock(g_inbound_conf_rwlock, true);

        if (lock.locked()) {
            IVR_DEBUG("locked!");
            // dec current flows' reference count
            g_flowmanager_inbound.swap(tmpfm_in);
            g_inbound_conf = in_conf;
        } else {
            IVR_WARN("lock failed!");
            IVR_TRACE("reload finished with error!");
            return FAILURE;
        }
    }

    if (is_need_reload_autorun) {
        IVR_TRACE("reload autorun conf!");
        rw_lock_t lock(g_autorun_conf_rwlock, true);

        if (lock.locked()) {
            IVR_DEBUG("locked!");
            // dec current flows' reference count
            g_flowmanager_autorun.swap(tmpfm_au);
            // update time stamp to stop all running autorun script
            g_autorun_script_stamp = time(NULL);
            g_autorun_conf = au_conf;

            // start new scripts
            for (size_t i = 0; i < g_autorun_conf.autorun_script_vec.size(); ++ i) {
                AutoRunManager::get_instance()->begin((uint32_t)i);
            }
        } else {
            IVR_WARN("lock failed!");
            IVR_TRACE("reload finished with error!");
            return FAILURE;
        }

        // sleep 1s to make sure next autorun success, because g_autorun_script_stamp is time_t
        sleep(1);
    }

    IVR_TRACE("set esllog flag %d", enable_esllog);
    g_output_esllog = enable_esllog != 0;
    IVR_TRACE("reload done!");
    return SUCCESS;
}

void ConfManager::unload_conf() {
    INIFile* conf = INIFile::get_instance();

    conf->unload_file(_sys_file.c_str(), true);
    conf->unload_file(_in_file.c_str(), true);
    conf->unload_file(_auto_file.c_str(), true);
}
