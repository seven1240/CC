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


#include "AgentProxy.h"
using namespace acd;

bool AgentProxy::Init_log() {
    bgcc::log_open(APLOGCONFIG);
    return true;
}

bool AgentProxy::getApCommonConf(const char* conf_filepath) {
    ConfUnit* root = ConfLoader::load_conf(conf_filepath);

    if (NULL == root) {
        std::cerr << "ConfLoader::load_conf return a NULL ConfUnit pointer" << std::endl;
        delete root;
        return false;
    }

    ConfUnit* confdevs = (*root)["ap"];

    if (NULL == confdevs) {
        std::cerr << "Not find conf_devices section" << std::endl;
        delete root;
        return false;
    }

    if (ConfUnit::UT_ARRAY != confdevs->get_type()) {
        std::cerr << "conf_devices is not an array" << std::endl;
        delete root;
        return false;
    }

    ConfUnit::const_iterator citr;
    int32_t i;

    for (citr = confdevs->begin(), i = 1; citr != confdevs->end(); ++citr, ++i) {
        ConfUnit* dev = *citr;

        if (NULL == dev || ConfUnit::UT_GROUP != dev->get_type()) {
            std::cerr << "counter a non device group in citr" << std::endl;
            delete root;
            exit(0);
        }

        ConfUnit* host = (*dev)["host"];

        if (NULL == host || ConfUnit::UT_STRING != host->get_type()) {
            std::cerr << "no host variable in ApConf" << std::endl;
            delete root;
            exit(0);
        }

        _apHost = host->to_string();

        ConfUnit* listen_port = (*dev)["listen_port"];

        if (NULL == listen_port || ConfUnit::UT_STRING != listen_port->get_type()) {
            std::cerr << "no listen_port variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(listen_port->to_string().c_str(), _apListenPort)) {
            delete root;
            return false;
        }

        ConfUnit* listen_port_own = (*dev)["listen_port_own"];

        if (NULL == listen_port_own || ConfUnit::UT_STRING != listen_port_own->get_type()) {
            std::cerr << "no listen_port_own variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(listen_port_own->to_string().c_str(), _apListenPortOwn)) {
            delete root;
            return false;
        }

        ConfUnit* ap_callback_threadnum = (*dev)["ap_callback_threadnum"];

        if (NULL == ap_callback_threadnum || ConfUnit::UT_STRING != ap_callback_threadnum->get_type()) {
            std::cerr << "no ap_callback_threadnum variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_callback_threadnum->to_string().c_str(),
                                           _CallbackThreadNum)) {
            delete root;
            return false;
        }

        ConfUnit* ap_heartbeat_timeout = (*dev)["ap_heartbeat_timeout"];

        if (NULL == ap_heartbeat_timeout || ConfUnit::UT_STRING != ap_heartbeat_timeout->get_type()) {
            std::cerr << "no ap_heartbeat_timeout variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_heartbeat_timeout->to_string().c_str(),
                                           _apHeartBeatTimeout)) {
            delete root;
            return false;
        }

        ConfUnit* ap_heartbeat_max_trytimes = (*dev)["ap_heartbeat_max_trytimes"];

        if (NULL == ap_heartbeat_max_trytimes
                || ConfUnit::UT_STRING != ap_heartbeat_max_trytimes->get_type()) {
            std::cerr << "no ap_heartbeat_max_trytimes variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_heartbeat_max_trytimes->to_string().c_str(),
                                           _apHeartBeatMaxTrytimes)) {
            delete root;
            return false;
        }

        ConfUnit* ap_warn_sendmsg_timeout = (*dev)["ap_warn_sendmsg_timeout"];

        if (NULL == ap_warn_sendmsg_timeout || ConfUnit::UT_STRING != ap_warn_sendmsg_timeout->get_type()) {
            std::cerr << "no ap_warn_sendmsg_timeout variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_warn_sendmsg_timeout->to_string().c_str(),
                                           _apWarnSendmsgTimeout)) {
            delete root;
            return false;
        }

        ConfUnit* ap_timeout = (*dev)["timeout"];

        if (NULL == ap_timeout || ConfUnit::UT_STRING != ap_timeout->get_type()) {
            std::cerr << "no timeout variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_timeout->to_string().c_str(), _AgentTimeOut)) {
            delete root;
            return false;
        }
    }

    delete root;
    return true;
}

bool AgentProxy::getAcdConf(const char* conf_filepath) {
    ConfUnit* root = ConfLoader::load_conf(conf_filepath);

    if (NULL == root) {
        std::cerr << "ConfLoader::load_conf return a NULL ConfUnit pointer" << std::endl;
        delete root;
        return false;
    }

    ConfUnit* confdevs0 = (*root)["acd0"];
    ConfUnit* confdevs1 = (*root)["acd1"];

    if (NULL == confdevs0 || NULL == confdevs1) {
        std::cerr << "Not find conf_devices section" << std::endl;
        delete root;
        return false;
    }

    if (ConfUnit::UT_ARRAY != confdevs0->get_type() || ConfUnit::UT_ARRAY != confdevs1->get_type()) {
        std::cerr << "conf_devices is not an array" << std::endl;
        delete root;
        return false;
    }

    ConfUnit::const_iterator citr;
    int32_t i;

    for (citr = confdevs0->begin(), i = 1; citr != confdevs0->end(); ++citr, ++i) {
        ConfUnit* dev = *citr;

        if (NULL == dev || ConfUnit::UT_GROUP != dev->get_type()) {
            std::cerr << "counter a non device group in citr" << std::endl;
            delete root;
            exit(0);
        }

        ConfUnit* host = (*dev)["host"];

        if (NULL == host || ConfUnit::UT_STRING != host->get_type()) {
            std::cerr << "no acd host variable in ApConf" << std::endl;
            delete root;
            exit(0);
        }

        _strMainACDIP = host->to_string();

        ConfUnit* port = (*dev)["port"];

        if (NULL == port || ConfUnit::UT_STRING != port->get_type()) {
            std::cerr << "no port variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(port->to_string().c_str(), _AcdMainPort)) {
            delete root;
            return false;
        }
    }

    for (citr = confdevs1->begin(), i = 1; citr != confdevs1->end(); ++citr, ++i) {
        ConfUnit* dev = *citr;

        if (NULL == dev || ConfUnit::UT_GROUP != dev->get_type()) {
            std::cerr << "counter a non device group in citr" << std::endl;
            delete root;
            exit(0);
        }

        ConfUnit* host = (*dev)["host"];

        if (NULL == host || ConfUnit::UT_STRING != host->get_type()) {
            std::cerr << "no acd host variable in ApConf" << std::endl;
            delete root;
            exit(0);
        }

        _strBackACDIP = host->to_string();

        ConfUnit* port = (*dev)["port"];

        if (NULL == port || ConfUnit::UT_STRING != port->get_type()) {
            std::cerr << "no port variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(port->to_string().c_str(), _AcdBackupPort)) {
            delete root;
            return false;
        }
    }

    delete root;
    return true;
}

bool AgentProxy::getBgccConf(const char* conf_filepath) {
    ConfUnit* root = ConfLoader::load_conf(conf_filepath);

    if (NULL == root) {
        std::cerr << "ConfLoader::load_conf return a NULL ConfUnit pointer" << std::endl;
        delete root;
        return false;
    }

    ConfUnit* confdevs = (*root)["bgcc"];

    if (NULL == confdevs) {
        std::cerr << "Not find conf_devices section" << std::endl;
        delete root;
        return false;
    }

    if (ConfUnit::UT_ARRAY != confdevs->get_type()) {
        std::cerr << "conf_devices is not an array" << std::endl;
        delete root;
        return false;
    }

    ConfUnit::const_iterator citr;
    int32_t i;

    for (citr = confdevs->begin(), i = 1; citr != confdevs->end(); ++citr, ++i) {
        ConfUnit* dev = *citr;

        if (NULL == dev || ConfUnit::UT_GROUP != dev->get_type()) {
            std::cerr << "counter a non device group in citr" << std::endl;
            delete root;
            exit(0);
        }

        ConfUnit* connNum = (*dev)["connNum"];

        if (NULL == connNum || ConfUnit::UT_STRING != connNum->get_type()) {
            std::cerr << "no bgcc connNum variable in ApConf" << std::endl;
            delete root;
            exit(0);
        }

        if (false == StringUtil::str2int32(connNum->to_string().c_str(), _apClientConnNum)) {
            delete root;
            return false;
        }

        ConfUnit* threadPoolNum = (*dev)["threadPoolNum"];

        if (NULL == threadPoolNum || ConfUnit::UT_STRING != threadPoolNum->get_type()) {
            std::cerr << "no threadPoolNum variable in ApConf" << std::endl;
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(threadPoolNum->to_string().c_str(), _apServerThreadPoolNum)) {
            delete root;
            return false;
        }
    }

    delete root;
    return true;
}


bool AgentProxy::readConf(const char* conf_filepath) {
    bool ret = getApCommonConf(conf_filepath);

    if (!ret) {
        return false;
    }

    ret = getAcdConf(conf_filepath);

    if (!ret) {
        return false;
    }

    ret = getBgccConf(conf_filepath);

    if (!ret) {
        return false;
    }

    return true;
}

bool AgentProxy::Init() {
    _pApServer = NULL;
    _pApClient = NULL;
    _heartBeatCount = 0;
    _apClientHandle = 0;
    _ACDPort = 0;
    _ctiService = AP_CONNACD_MASTER;
#ifndef _WIN32
    _mapAgentIdData.resize(8000);
#endif
    _CallbackThreadNum = 0;
    _ApEventQ = NULL;

    _apHeartBeatTimeout = 0;
    _apHeartBeatMaxTrytimes = 0;
    _apWarnSendmsgTimeout = 0;


    /*初始化日志模块*/
    if (!Init_log()) {
        return false;
    }

    /*初始化配置文件*/
    if (!readConf(APCONFIG)) {
        return false;
    }

    /** 创建回调队列*/
    _ApEventQ = new(std::nothrow)ApEventQT[_CallbackThreadNum];

    if (!_ApEventQ) {
        BGCC_WARN("ap", "Fail to new ApEventQT!");
        return false;
    }

    int32_t i = 0;

    while (i < _CallbackThreadNum) {
        _ApEventQ[i]._qEventCall.clear();
        _ApEventQ[i]._qEventMedia.clear();
        _ApEventQ[i]._qEventOther.clear();
        _ApEventQ[i]._qEventRoute.clear();
        i++;
    }

    //创建连接acd的客户端对象，如果主acd连不上，则创建连接备acd的客户端对象
    if (!CreateClient(_strMainACDIP, _AcdMainPort, _apClientConnNum)) {
        if (!CreateClient(_strBackACDIP, _AcdBackupPort, _apClientConnNum)) {
            BGCC_WARN("ap", "Both ACD[0] and ACD[1] is invalid.");
            return false;
        } else { //_ctiService默认值为连接主acd
            _ctiService = AP_CONNACD_SLAVE;
        }
    }

    //创建AP自己监听的线程
    if (!CreateApListenThread()) {

        BGCC_WARN("ap", "Fail to Create ApListen Thread!");
        return false;
    }

    //创建处理回调事件的线程
    if (!CreateAcdCBThread()) {

        BGCC_WARN("ap", "Fail to Create ACD Callback Thread!");
        return false;
    }

    //创建发送心跳给acd的线程
    if (!CreateCheckHBThread()) {

        BGCC_WARN("ap", "Fail to Create Check HeartBeat Thread!");
        return false;
    }

    //创建监听客户端的Server
    _pApServer = new ApServer();

    if (!_pApServer->InitApServer(_apHost, _apListenPort, _apServerThreadPoolNum)) {
        BGCC_WARN("ap", "Fail to Init ApServer!");
        return false;
    }

    return true;
}

bool AgentProxy::StartApListen() {
    //创建监听客户端的Server
    _pApService = new ApService();

    if (!_pApService->InitApService(_apHost, _apListenPortOwn, _apServerThreadPoolNum)) {
        BGCC_WARN("ap", "Fail to Init ApService!");
        return false;
    }

    BGCC_NOTICE("ap", "Success Start ApServiceThread.");
    return true;
}


int32_t AgentProxy::GetHeartBeatTimeOut() {
    return _apHeartBeatTimeout;
}

bool AgentProxy::CreateClient(std::string Ip, int32_t Port, int32_t connectNum) {
    _pApClient = new(std::nothrow)ApClient(Ip, Port, _apWarnSendmsgTimeout, connectNum);

    if (!_pApClient) {
        BGCC_WARN("ap", "Fail to Alloc ApClient to ACD:IP = %s,Port = %d!", Ip.c_str(), Port);
        return false;
    }

    if (!_pApClient->InitClient()) {
        delete _pApClient;
        _pApClient = NULL;
        BGCC_WARN("ap", "Fail to Init ApClient to ACD:IP = %s,Port = %d!", Ip.c_str(), Port);
        return false;
    }

    return true;
}

bool AgentProxy::CreateAcdCBThread() {
    int32_t i = 0;
    int32_t ret = true;
    BGCC_NOTICE("ap", "CreateAcdCBThread:_CallbackThreadNum = %d", _CallbackThreadNum);

    while (i < _CallbackThreadNum) {
        SharedPointer<Runnable> r(new ApCallbackThread(i));
        Thread* t = new Thread(r);
        ret = t->start();

        if (!ret) {
            BGCC_WARN("ap", "Fail to Start ApCBThread[%d].", i);
            return false;
        }

        BGCC_NOTICE("ap", "Start AcdCBThread[%d]", i);
        _apCallbackThreadVec.push_back(t);
        i++;
    }

    return true;
}
bool AgentProxy::CreateApListenThread() {
    int32_t ret = true;
    SharedPointer<Runnable> r(new ApListenThread());
    Thread* t = new Thread(r);
    ret = t->start();

    if (!ret) {
        BGCC_WARN("ap", "Fail to Start ApListen Thread.");
        return false;
    }

    BGCC_NOTICE("ap", "Start ApListenThread success.");
    _apListenThread = t;
    return true;
}

bool AgentProxy::CreateCheckHBThread() {
    int32_t ret = true;
    SharedPointer<Runnable> r(new ApHeartBeatThread());
    Thread* t = new Thread(r);
    ret = t->start();

    if (!ret) {
        BGCC_WARN("ap", "Fail to Start Ap Check HeartBeat Thread.");
        return false;
    }

    BGCC_NOTICE("ap", "Start AcdCheckHBThread.");
    _apHBCheckThread = t;
    return true;
}

void AgentProxy::Destroy() {
    SetApThreadShutdown();

    if (_pApClient) {
        delete _pApClient;
        _pApClient = NULL;
    }

    if (_pApServer) {
        delete _pApServer;
        _pApServer = NULL;
    }

    if (_pApService) {
        delete _pApService;
        _pApService = NULL;
    }

    //释放回调线程指针
    uint32_t i;

    for (i = 0 ; i < _apCallbackThreadVec.size() ; i++) {
        Thread* p = _apCallbackThreadVec[i];

        if (p) {
            delete p;
            p = NULL;
            BGCC_NOTICE("ap", "Success to erase CallbackThread[%d]", i);
        }
    }

    //释放心跳线程指针
    if (_apListenThread) {
        delete _apListenThread;
        _apListenThread = NULL;
    }

    BGCC_NOTICE("ap", "Success to destroy ApListenThread.");

    //释放心跳线程指针
    if (_apHBCheckThread) {
        delete _apHBCheckThread;
        _apHBCheckThread = NULL;
    }

    BGCC_NOTICE("ap", "Success to destroy _apHeartBeatThread.");

    if (_ApEventQ) {
        delete []_ApEventQ;
        _ApEventQ = NULL;

    }

    return;
}

void AgentProxy::SetApThreadShutdown() {
    ScopeGuard guard(&_threadShutdownMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return;
    }

    _shutdown = true;
}

bool AgentProxy::IsNeedApThreadShutdown() {
    ScopeGuard guard(&_threadShutdownMutex);
    return _shutdown;
}

bool AgentProxy::SetMapAgentIdData(AgentData* agentInfo) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    std::pair<MapAgentIdDataType::iterator, bool> ret;
    ret = _mapAgentIdData.insert(MapAgentIdDataType::value_type(agentInfo->agentId, agentInfo));

    if (!ret.second) {
        BGCC_WARN("ap", "FailInsertMap : AgentId=%s,AgentDn=%s!", agentInfo->agentId.c_str(),
                  agentInfo->agentDn.c_str());
        return false;
    }

    return true;
}

bool AgentProxy::DelMapAgentIdData(const std::string& agentId) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "FailDelMap : Cannot Find AgentId=%s!", agentId.c_str());
        return false;
    } else {
        BGCC_NOTICE("ap", "Deleting AgentData:AgentId = %s, handle = %"int64ld"", agentId.c_str(),
                    it1->second->handle);
    }

    AgentData* p = it1->second;

    if (p) {
        delete p;
        p = NULL;
    }

    _mapAgentIdData.erase(it1);
    return true;
}

bool AgentProxy::ClearMapAgentData() {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.begin();

    while (it1 != _mapAgentIdData.end()) {
        AgentData* p = it1->second;
        delete p;
        p = NULL;
        _mapAgentIdData.erase(it1++);
    }

    return true;
}

bool AgentProxy::ResetProxy(const std::string& agentId, AgentData* agentInfo) {
    (void)DelMapAgentIdData(agentId);
    bool ret = SetMapAgentIdData(agentInfo);

    if (!ret) {
        BGCC_WARN("ap", "ResetProxy Fail.AgentId = %s.", agentId.c_str());
        return false;
    }

    return true;
}

bool AgentProxy::GetAgentData(const std::string& agentId, AgentData& agentInfo) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "FailFindMap : AgentId=%s!", agentId.c_str());
        return false;
    }

    agentInfo.agentId = it1->second->agentId;
    agentInfo.agentDn = it1->second->agentDn;
    agentInfo.agentPwd = it1->second->agentPwd;
    agentInfo.statusChangetype = it1->second->statusChangetype;
    agentInfo.autoAnswer = it1->second->autoAnswer;
    agentInfo.fcSignin = it1->second->fcSignin;
    agentInfo.skill = it1->second->skill;
    agentInfo.handle = it1->second->handle;
    agentInfo.flag = it1->second->flag;
    agentInfo.agentIP = it1->second->agentIP;
    agentInfo.proxyname = it1->second->proxyname;
    agentInfo.proxyname_old = it1->second->proxyname_old;
    return true;
}

bool AgentProxy::GetAgentHandleById(const std::string agentId, int64_t& handle) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "GetAgentHandle fail : AgentId=%s!", agentId.c_str());
        return false;
    }

    handle = it1->second->handle;
    return true;
}

bool AgentProxy::SetAgentHandleById(const std::string agentId, int64_t handle) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "SetAgentHandleById fail : AgentId=%s!", agentId.c_str());
        return false;
    }

    it1->second->handle = handle;
    return true;
}

bool AgentProxy::IsAgentHasExist(const std::string agentId) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "Agent is not Exist : AgentId=%s!", agentId.c_str());
        return false;
    }

    return true;
}

bool AgentProxy::SetAgentOldProxyNull(const std::string agentId, int64_t handle) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "Agent is not exist : AgentId=%s!", agentId.c_str());
        return false;
    }

    it1->second->proxyname_old = "";
    return true;
}

//flag 字段单独函数修改,不在本函数更新
bool AgentProxy::UpdateAgentData(AgentData& agentinfo) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentinfo.agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "Agent is not exist : AgentId=%s!", agentinfo.agentId.c_str());
        return false;
    }

    it1->second->agentId = agentinfo.agentId;
    it1->second->agentDn = agentinfo.agentDn;
    it1->second->agentPwd = agentinfo.agentPwd;
    it1->second->statusChangetype = agentinfo.statusChangetype;
    it1->second->autoAnswer = agentinfo.autoAnswer;
    it1->second->fcSignin = agentinfo.fcSignin;
    it1->second->skill = agentinfo.skill;
    int64_t handle_old = it1->second->handle;
    it1->second->handle = agentinfo.handle;
    it1->second->agentIP = agentinfo.agentIP;
    it1->second->proxyname_old = it1->second->proxyname;
    it1->second->proxyname = agentinfo.proxyname;

    BGCC_NOTICE("ap",
                "UpdateAgentData Success,agentId = %s,Oldhandle = %"int64ld",Newhandle = %"int64ld".",
                agentinfo.agentId.c_str(), handle_old, agentinfo.handle);
    return true;
}

void AgentProxy::SetAgentFlag(const std::string agentId, int32_t flag) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return ;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_WARN("ap", "Agent is not exist : AgentId=%s!", agentId.c_str());
        return ;
    }

    it1->second->flag = flag;
    it1->second->timestamp = TimeUtil::get_timestamp_us();
    return ;
}
bool AgentProxy::AddAcdCallEvent(AgentEventT& event) {
    int32_t i = atol(event.agentId.c_str()) % _CallbackThreadNum;
    bool ret = _ApEventQ[i]._qEventCall.put(event);

    if (ret) {
        BGCC_NOTICE("ap", "AddCallEvent Success,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    } else {
        BGCC_WARN("ap", "AddCallEvent Fail,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    }

    return ret;
}

bool AgentProxy::AddAcdMediaEvent(MediaEventT& event) {
    int32_t i = atol(event.agentId.c_str()) % _CallbackThreadNum;
    bool ret = _ApEventQ[i]._qEventMedia.put(event);

    if (ret) {
        BGCC_NOTICE("ap", "AddMediaEvent Success,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    } else {
        BGCC_WARN("ap", "AddMediaEvent Fail,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    }

    return ret;
}

bool AgentProxy::AddAcdRouteEvent(RouteEventT& event) {
    int32_t i = atol(event.agentId.c_str()) % _CallbackThreadNum;
    bool ret = _ApEventQ[i]._qEventRoute.put(event);

    if (ret) {
        BGCC_NOTICE("ap", "AddRouteEvent Success,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    } else {
        BGCC_WARN("ap", "AddRouteEvent Fail,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    }

    return ret;
}

bool AgentProxy::AddAcdOtherEvent(OtherEventT& event) {
    int32_t i = atol(event.agentId.c_str()) % _CallbackThreadNum;
    bool ret = _ApEventQ[i]._qEventOther.put(event);

    if (ret) {
        BGCC_NOTICE("ap", "AddOtherEvent Success,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    } else {
        BGCC_WARN("ap", "AddOtherEvent Fail,AgentId = %s,QueueId = %d.", event.agentId.c_str(), i);
    }

    return ret;
}

bool AgentProxy::GetAcdCallEvent(AgentEventT& event, const int32_t threadNo) {
    if (threadNo < 0 && threadNo >= _CallbackThreadNum) {
        BGCC_WARN("ap", "GetAcdCallEvent ThreadNo is invalid,ThreadId = %d.", threadNo);
        return false;
    }

    bool ret = _ApEventQ[threadNo]._qEventCall.get(event);

    if (ret) {
        BGCC_NOTICE("ap", "GetCallEvent Success,AgentId = %s,ThreadId = %d.", event.agentId.c_str(),
                    threadNo);
    }

    return ret;
}

bool AgentProxy::GetAcdMediaEvent(MediaEventT& event, const int32_t threadNo) {
    if (threadNo < 0 && threadNo >= _CallbackThreadNum) {
        BGCC_WARN("ap", "GetAcdMediaEvent ThreadNo is invalid,ThreadId = %d.", threadNo);
        return false;
    }

    bool ret = _ApEventQ[threadNo]._qEventMedia.get(event);

    if (ret) {
        BGCC_NOTICE("ap", "GetMediaEvent Success,AgentId = %s,ThreadId = %d.", event.agentId.c_str(),
                    threadNo);
    }

    return ret;
}

bool AgentProxy::GetAcdRouteEvent(RouteEventT& event, const int32_t threadNo) {
    if (threadNo < 0 && threadNo >= _CallbackThreadNum) {
        BGCC_WARN("ap", "GetAcdRouteEvent ThreadNo is invalid,ThreadId = %d.", threadNo);
        return false;
    }

    bool ret = _ApEventQ[threadNo]._qEventRoute.get(event);

    if (ret) {
        BGCC_NOTICE("ap", "GetRouteEvent Success,AgentId = %s,ThreadId = %d.", event.agentId.c_str(),
                    threadNo);
    }

    return ret;
}

bool AgentProxy::GetAcdOtherEvent(OtherEventT& event, const int32_t threadNo) {
    if (threadNo < 0 && threadNo >= _CallbackThreadNum) {
        BGCC_WARN("ap", "GetAcdOtherEvent ThreadNo is invalid,ThreadId = %d.", threadNo);
        return false;
    }

    bool ret = _ApEventQ[threadNo]._qEventOther.get(event);

    if (ret) {
        BGCC_NOTICE("ap", "GetOtherEvent Success,AgentId = %s,ThreadId = %d.", event.agentId.c_str(),
                    threadNo);
    }

    return ret;
}

void AgentProxy::SendCallEvent(const AgentEventT& acdCallEvent, int32_t _threadNo) {
    BGCC_NOTICE("ap", "SendCallEvent In.AgentId = %s.TimeStamp = %"int64ld".",
                acdCallEvent.agentId.c_str(), acdCallEvent.timestamp);
    AgentData agentInfo;

    if (!GetAgentData(acdCallEvent.agentId, agentInfo)) {
        BGCC_NOTICE("ap", "SendCallEvent FailFindMap : AgentId=%s,AgentTimeStamp = %"int64ld"!",
                    acdCallEvent.agentId.c_str(), acdCallEvent.timestamp);
        return;
    }

    int64_t handle = agentInfo.handle;
    int32_t flag = agentInfo.flag;
    std::string proxyname = agentInfo.proxyname;
    std::string proxyname_old = agentInfo.proxyname_old;

    if (!proxyname_old.empty()) { //如果old不为空，则表明该事件发给原坐席
        acdcallbackProxy acdCallbackProxy(proxyname, 0);
        acdcallbackProxy acdCallbackProxy_old(proxyname_old, 0);

        //1.强制签入时 ，必须用oldproxy发送
        if (acdCallEvent.agentStatus == AgentStatusT::AsUnLoginState
                && acdCallEvent.eventId == CallEventTypeT::CeUnKnownEvent
                && acdCallEvent.reason == CallEventReasonT::CerUnloginOtherForceout) {
            BGCC_NOTICE("ap",
                        "Thread[%d]:OldProxy Send Agentbar[%s] CallEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                        _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
            acdCallbackProxy_old.SendAgentEvent(acdCallEvent);
            int32_t err = acdCallbackProxy_old.get_errno();

            if (err != 0) {
                BGCC_WARN("ap", "SendEventError:Proxy.handle = %"int64ld",TimeStamp = %"int64ld",bgcc_ret = %d.",
                          handle, acdCallEvent.timestamp, err);
            }

            BGCC_NOTICE("ap",
                        "Thread[%d]:OldProxy Send Agentbar[%s] CallEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                        _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
        } else { //正常场景下没有，担心异常情况
            BGCC_NOTICE("ap",
                        "Thread[%d]:Proxy Send Agentbar[%s] CallEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                        _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
            acdCallbackProxy.SendAgentEvent(acdCallEvent);
            int32_t err = acdCallbackProxy.get_errno();

            if (err != 0) {
                BGCC_WARN("ap", "SendEventError:Proxy.handle = %"int64ld",TimeStamp = %"int64ld",bgcc_ret = %d.",
                          handle, acdCallEvent.timestamp, err);
            }

            BGCC_NOTICE("ap",
                        "Thread[%d]:Proxy Send Agentbar[%s] CallEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                        _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
        }

        //将old_proxy置空
        (void)SetAgentOldProxyNull(acdCallEvent.agentId, handle);
    } else if (!proxyname.empty()) {
        acdcallbackProxy acdCallbackProxy(proxyname, 0);
        BGCC_NOTICE("ap",
                    "Thread[%d]:NewProxy Send Agentbar[%s] CallEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
        acdCallbackProxy.SendAgentEvent(acdCallEvent);

        BGCC_NOTICE("ap",
                    "Thread[%d]:NewProxy Send Agentbar[%s] CallEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);

        int32_t err = acdCallbackProxy.get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SendEventError:Proxy.handle = %"int64ld",TimeStamp = %"int64ld",bgcc_ret=%d.",
                      handle, acdCallEvent.timestamp, err);
        }

        //此场景为acd踢坐席，需要将坐席信息删除
        if (acdCallEvent.agentStatus == AgentStatusT::AsUnLoginState
                && acdCallEvent.eventId == CallEventTypeT::CeUnKnownEvent
                && acdCallEvent.reason == CallEventReasonT::CerUnloginOtherForceout) {
            BGCC_NOTICE("ap", "SendCallEvent Agent = %s ACD has kick agent and delete the agentinfo.",
                        acdCallEvent.agentId.c_str());
            (void)DelMapAgentIdData(acdCallEvent.agentId);
        }
    } else {
        BGCC_WARN("ap",
                  "SendAgentEvent Fail :Proxy is NULL,AgentId = %sTimeStamp = %"int64ld",handle = %"int64ld".",
                  acdCallEvent.agentId.c_str(), acdCallEvent.timestamp, handle);
    }

    if (acdCallEvent.agentStatus == AgentStatusT::AsUnLoginState
            && acdCallEvent.eventId == CallEventTypeT::CeUnKnownEvent) {
        if (flag == 1) { //表示坐席刚SIGNOUT，需要将该agentinfo删除
            BGCC_NOTICE("ap", "SendCallEvent Agent = %s has SignOut and delete the agentinfo.",
                        acdCallEvent.agentId.c_str());
            (void)DelMapAgentIdData(acdCallEvent.agentId);
        }
    }

    return;
}

void AgentProxy::SendMediaEvent(const MediaEventT& acdMediaEvent, int32_t _threadNo) {
    AgentData agentInfo;

    if (!GetAgentData(acdMediaEvent.agentId, agentInfo)) {
        BGCC_WARN("ap", "SendMediaEvent FailFindMap : AgentId=%s,AgentTimeStamp = %"int64ld"!",
                  acdMediaEvent.agentId.c_str(), acdMediaEvent.timestamp);
        return;
    }

    int64_t handle = agentInfo.handle;
    std::string proxyname = agentInfo.proxyname;

    if (!proxyname.empty()) {
        acdcallbackProxy acdCallbackProxy(proxyname, 0);
        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] MediaEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdMediaEvent.agentId.c_str(), acdMediaEvent.timestamp, handle);

        acdCallbackProxy.SendMediaEvent(acdMediaEvent);
        int32_t err = acdCallbackProxy.get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SendMediaEventError:AgentId = %s,TimeStamp = %"int64ld",bgcc_ret = %d.",
                      acdMediaEvent.agentId.c_str(), acdMediaEvent.timestamp, err);
        }

        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] MediaEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdMediaEvent.agentId.c_str(), acdMediaEvent.timestamp, handle);
    } else {

        BGCC_WARN("ap", "SendMediaEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
                  acdMediaEvent.agentId.c_str(), acdMediaEvent.timestamp);
    }

    return;
}

void AgentProxy::SendRouteEvent(const RouteEventT& acdRouteEvent, int32_t _threadNo) {
    AgentData agentInfo;

    if (!GetAgentData(acdRouteEvent.agentId, agentInfo)) {
        BGCC_WARN("ap", "SendRouteEvent FailFindMap : AgentId=%s,AgentTimeStamp = %"int64ld"!",
                  acdRouteEvent.agentId.c_str(), acdRouteEvent.timestamp);
        return;
    }

    int64_t handle = agentInfo.handle;
    std::string proxyname = agentInfo.proxyname;

    if (!proxyname.empty()) {
        acdcallbackProxy acdCallbackProxy(proxyname, 0);
        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] QueueEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdRouteEvent.agentId.c_str(), acdRouteEvent.timestamp, handle);

        acdCallbackProxy.SendQueueEvent(acdRouteEvent);
        int32_t err = acdCallbackProxy.get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "SendQueueEventError:AgentId = %s,TimeStamp = %"int64ld",bgcc_ret = %d.",
                      acdRouteEvent.agentId.c_str(), acdRouteEvent.timestamp, err);
        }

        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] QueueEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdRouteEvent.agentId.c_str(), acdRouteEvent.timestamp, handle);
    } else {
        BGCC_WARN("ap", "SendQueueEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
                  acdRouteEvent.agentId.c_str(), acdRouteEvent.timestamp);
    }

    return;
}

void AgentProxy::SendOtherEvent(const OtherEventT& acdOtherEvent, int32_t _threadNo) {
    AgentData agentInfo;

    if (!GetAgentData(acdOtherEvent.agentId, agentInfo)) {
        BGCC_WARN("ap", "SendOtherEvent FailFindMap : AgentId=%s,AgentTimeStamp = %"int64ld"!",
                  acdOtherEvent.agentId.c_str(), acdOtherEvent.timestamp);
        return;
    }

    int64_t handle = agentInfo.handle;
    std::string proxyname = agentInfo.proxyname;

    if (!proxyname.empty()) {
        acdcallbackProxy acdCallbackProxy(proxyname, 0);
        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] OtherEvent Begin,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdOtherEvent.agentId.c_str(), acdOtherEvent.timestamp, handle);

        acdCallbackProxy.SendOtherEvent(acdOtherEvent);
        int32_t err = acdCallbackProxy.get_errno();

        if (err != 0) {
            BGCC_WARN("ap", "acdOtherEventError:AgentId = %s,TimeStamp = %"int64ld",bgcc_ret = %d.",
                      acdOtherEvent.agentId.c_str(), acdOtherEvent.timestamp, err);
        }

        BGCC_NOTICE("ap",
                    "Thread[%d]: Send Agentbar[%s] OtherEvent End,TimeStamp = %"int64ld",handle = %"int64ld".",
                    _threadNo, acdOtherEvent.agentId.c_str(), acdOtherEvent.timestamp, handle);
    } else {
        BGCC_WARN("ap", "SendOtherEvent Fail :Proxy is NULL,AgentId = %s,TimeStamp = %"int64ld".",
                  acdOtherEvent.agentId.c_str(), acdOtherEvent.timestamp);
    }

    return;
}

bool AgentProxy::IsQueueEmpty(const int32_t& threadNo) {
    if (_ApEventQ[threadNo]._qEventCall.size()  == 0
            && _ApEventQ[threadNo]._qEventMedia.size() == 0
            && _ApEventQ[threadNo]._qEventRoute.size() == 0
            && _ApEventQ[threadNo]._qEventOther.size() == 0) {
        return true;
    }

    return false;
}

APCONNACDSTATE AgentProxy::GetCtiService() {
    ScopeGuard guard(&_ctiServiceMutex);
    return _ctiService;
}

void AgentProxy::SetCtiService(APCONNACDSTATE State) {
    ScopeGuard guard(&_ctiServiceMutex);
    _ctiService = State;
    return;
}

void AgentProxy::AddHeartBeatCount() {
    ScopeGuard guard(&_HBCountMutex);
    _heartBeatCount++;
    return;
}

void AgentProxy::ClearHeartBeatCount() {
    ScopeGuard guard(&_HBCountMutex);
    _heartBeatCount = 0;
    return;
}

int32_t AgentProxy::GetHeartBeatCount() {
    ScopeGuard guard(&_HBCountMutex);
    return _heartBeatCount;
}

void AgentProxy::HeartBeat() {
    int64_t handle = 0;
    std::string agentId = "0000";
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();
    AcdResultT ret ;

    if (AP_CONNACD_BACKING == GetCtiService()) {
        BGCC_WARN("ap", "Backuping And Cancel Heartbeat.");
        return;
    }

    {
        ScopeGuard guard(&_ApClientMutex);

        if (!guard.is_locked()) {
            BGCC_WARN("ap", "Guard fail.");
            return ;
        }

        if (!_pApClient) {
            BGCC_WARN("ap", "Client is NULL.");
            return;
        }

        ret = _pApClient->Heartbeat(handle, agentId, time_rcv);
    }


    if (ret == AcdResultT::ArNoSignin) {
        ClearHeartBeatCount();
        BGCC_NOTICE("ap", "Success to GetHeartbeat to ACD[%d],CheckHeartBeatCount = %d.", GetCtiService(),
                    GetHeartBeatCount());
    } else if (ret == AcdResultT::ArNotMaster) {
        ClearHeartBeatCount();
        BGCC_WARN("ap", "ACD[%d] Tell me NotMaster And to Backup.", GetCtiService());
        BGCC_WARN("bgcc", "ACD[%d] Tell me NotMaster And to Backup.", GetCtiService());
        // 倒换
        Backup();
        return;
    } else {
        AddHeartBeatCount();
        BGCC_WARN("ap", "ACD[%d] is AbNormal,CheckHeartbeatCount++ = %d,ret = %s.", GetCtiService(),
                  GetHeartBeatCount(), ret.get_desc().c_str());
    }

    if (GetHeartBeatCount() == _apHeartBeatMaxTrytimes) {
        ClearHeartBeatCount();
        BGCC_WARN("ap", "Check Connect to ACD[%d] Fail, CheckCount = %d And to Backup", GetCtiService(),
                  _apHeartBeatMaxTrytimes);
        // 倒换
        Backup();
    }

    return ;
}

bool AgentProxy::SetApClient(ApClient* client) {
    ScopeGuard guard(&_ApClientMutex);

    if (!guard.is_locked()) {
        BGCC_WARN("ap", "Guard fail.");
        return false;
    }

    if (_pApClient) {
        delete _pApClient;
        _pApClient = NULL;
    }

    _pApClient = client;

    return true;
}

bool AgentProxy::TryConnAcd(std::string strIp, int32_t Port, APCONNACDSTATE state) {
    AcdResultT ret ;
    int64_t handle = 0;
    std::string agentId = "0000";
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();

    ApClient* pClientTmp = new(std::nothrow)ApClient(strIp, Port, _apWarnSendmsgTimeout,
            _apClientConnNum);

    if (!pClientTmp) {
        BGCC_WARN("ap", "Fail to Alloc new ApClientTmp to Connect ACD[%d].", state);
        return false;
    }

    if (!pClientTmp->InitClient()) {
        BGCC_WARN("ap", "Fail to Init ApClientTmp to Connect ACD[%d].", state);
        delete pClientTmp;
        return false;
    }

    ret = pClientTmp->Heartbeat(handle, agentId, time_rcv);

    if (ret == AcdResultT::ArNoSignin) {
        SetApClient(pClientTmp);
        ReSignIn(state);
        SetCtiService(state);
        BGCC_NOTICE("ap", "TryConnAcd End:Success connect to ACD[%d].", state);
    } else {
        BGCC_WARN("ap", "TryConnAcd End:Fail connect to ACD[%d]:IP = %s,Port = %d,ret = %s.", state,
                  strIp.c_str(), Port, ret.get_desc().c_str());
        delete pClientTmp;
        return false;
    }

    return true;
}

bool AgentProxy::GetValidAcd() {
    bool ret = true;

    if (!TryConnAcd(_strMainACDIP, _AcdMainPort, AP_CONNACD_MASTER)) {
        BGCC_WARN("ap", "GetValidAcd End:Fail to Get ACD[%d].", AP_CONNACD_MASTER);

        if (!TryConnAcd(_strBackACDIP, _AcdBackupPort, AP_CONNACD_SLAVE)) {
            BGCC_WARN("ap", "GetValidAcd End:Fail to Get ACD[%d].", AP_CONNACD_SLAVE);
            ret = false;
        } else {
            BGCC_NOTICE("ap", "GetValidAcd End:Success Get ACD[%d].", AP_CONNACD_SLAVE);
            ret =  true;
        }
    } else {
        BGCC_NOTICE("ap", "GetValidAcd End:Success Get ACD[%d].", AP_CONNACD_MASTER);
        ret =  true;
    }

    return ret;
}
bool AgentProxy::Backup() {
    AcdResultT ret ;
    int64_t handle = 0;
    std::string agentId = "0000";
    uint64_t time_rcv = TimeUtil::get_timestamp_ms();


    if (GetCtiService() == AP_CONNACD_MASTER) {
        //设置当前状态为倒换中
        SetCtiService(AP_CONNACD_BACKING);

        ApClient* pClientTmp = new(std::nothrow)ApClient(_strBackACDIP, _AcdBackupPort,
                _apWarnSendmsgTimeout, _apClientConnNum);

        if (!pClientTmp) {
            BGCC_WARN("ap", "Fail to Alloc new ApClientTmp to Connect ACD[%d].", AP_CONNACD_SLAVE);
            goto FAIL;
        }

        if (!pClientTmp->InitClient()) {
            BGCC_WARN("ap", "Fail to Init ApClientTmp to Connect ACD[%d].", AP_CONNACD_SLAVE);
            delete pClientTmp;
            goto FAIL;
        }

        // 尝试重连
        int32_t tryTime = _apHeartBeatMaxTrytimes;

        while (tryTime--) {
            ret = pClientTmp->Heartbeat(handle, agentId, time_rcv);

            if (ret == AcdResultT::ArNotMaster) { // 非主
                BGCC_NOTICE("ap", "Backuping:TryTime[%d],Fail connect to ACD[%d],And Tell me NotMaster,Sleep(3)s.",
                            tryTime, AP_CONNACD_SLAVE);
                TimeUtil::safe_sleep_s(3);
            } else {
                break;
            }
        }

        if (ret == AcdResultT::ArNoSignin) {
            SetApClient(pClientTmp);
            ReSignIn(AP_CONNACD_SLAVE);
            SetCtiService(AP_CONNACD_SLAVE);
            BGCC_NOTICE("ap", "BackupEnd:Success connect to ACD[%d].", AP_CONNACD_SLAVE);
            return true;
        } else {
            BGCC_WARN("ap", "Backuping:TryTime[%d],Fail connect to ACD[%d],And Tell me %s.", tryTime,
                      AP_CONNACD_SLAVE, ret.get_desc().c_str());
            delete pClientTmp;
            goto FAIL;
        }

    } else {
        //设置当前状态为倒换中
        SetCtiService(AP_CONNACD_BACKING);

        ApClient* pClientTmp = new(std::nothrow)ApClient(_strMainACDIP, _AcdMainPort, _apWarnSendmsgTimeout,
                _apClientConnNum);

        if (!pClientTmp) {
            BGCC_WARN("ap", "Fail to Alloc new ApClientTmp to Connect ACD[%d].", AP_CONNACD_MASTER);
            goto FAIL;
        }

        if (!pClientTmp->InitClient()) {
            BGCC_WARN("ap", "Fail to Init ApClientTmp to Connect ACD[%d].", AP_CONNACD_MASTER);
            delete pClientTmp;
            goto FAIL;
        }

        // 尝试重连
        int32_t tryTime = _apHeartBeatMaxTrytimes;

        while (tryTime--) {
            //ret = pClientTmp->HeartBeat();
            ret = pClientTmp->Heartbeat(handle, agentId, time_rcv);

            if (ret == AcdResultT::ArNotMaster) { // 非主
                BGCC_NOTICE("ap", "Backuping:TryTime[%d],Fail connect to ACD[%d],And Tell me NotMaster,Sleep(3)s.",
                            tryTime, AP_CONNACD_MASTER);
                TimeUtil::safe_sleep_s(3);
            } else {
                break;
            }
        }

        if (ret == AcdResultT::ArNoSignin) {
            SetApClient(pClientTmp);
            ReSignIn(AP_CONNACD_MASTER);
            SetCtiService(AP_CONNACD_MASTER);
            BGCC_NOTICE("ap", "BackupEnd:Success connect to ACD[%d].", AP_CONNACD_MASTER);
            return true;
        } else {
            BGCC_WARN("ap", "Backuping:TryTime[%d],Fail connect to ACD[%d],And Tell me %s.", tryTime,
                      AP_CONNACD_MASTER, ret.get_desc().c_str());
            delete pClientTmp;
            goto FAIL;
        }
    }

FAIL:

    SetCtiService(AP_CONNACD_UNKNOW);

    while (true) {
        if (ClearMapAgentData()) {
            break;
        }
    }

    // 倒换失败
    while (!GetValidAcd()) {
        BGCC_WARN("ap", "Backuping:Both ACD is Invalid and sleep 3s.");
        TimeUtil::safe_sleep_s(3);
    }

    BGCC_NOTICE("ap", "BackupEnd:Success connect to ACD[%d].", GetCtiService());

    return true;
}

void AgentProxy::ReSignIn(APCONNACDSTATE state) {
    ScopeGuard guard_proxy(&_ApClientMutex);
    ScopeGuard guard_map(&_mapMutex);

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.begin();

    int32_t TotalAgentNum = _mapAgentIdData.size();
    int32_t SuccessAgentNum = 0;
    std::string agentId;
    std::string agentDn;
    std::string agentPwd;
    StatusChangeT statusChangetype;
    bool autoAnswer;
    bool fcSignin;
    std::string skill;
    int64_t handle;
    std::string proxynameTmp;

    while (it1 != _mapAgentIdData.end()) {
        AcdResultT ret;

        agentId = it1->second->agentId;
        agentDn = it1->second->agentDn;
        agentPwd = it1->second->agentPwd;
        statusChangetype = it1->second->statusChangetype;
        autoAnswer = it1->second->autoAnswer;
        fcSignin = it1->second->fcSignin;
        skill = it1->second->skill;
        handle = it1->second->handle;
        proxynameTmp = it1->second->proxyname;

        uint64_t time_rcv = TimeUtil::get_timestamp_ms();
        //重新签入并置闲
        BGCC_NOTICE("ap",
                    "ReSignIning:AgentId = %s,AgentDn = %s,AgentPwd = %s,statusChangetype = %d,autoAnswer = %d,fcSignin = %d,skill = %s,handle = %"int64ld".",
                    agentId.c_str(), agentDn.c_str(), agentPwd.c_str(), statusChangetype.get_value(), autoAnswer,
                    fcSignin, skill.c_str(), handle);

        if (!_pApClient) {
            BGCC_WARN("ap", "Client is NULL.");
            return;
        }

        ret = _pApClient->SignIn(agentId, agentDn, agentPwd, statusChangetype,
                                 autoAnswer, true, skill, handle, time_rcv);

        if (ret == AcdResultT::ArSuccess) {
            SuccessAgentNum++;
            it1->second->handle = handle;
            BGCC_NOTICE("ap", "ReSignIning:Success to ReSignIn to ACD[%d],AgentId = %s,agentDn = %s.",
                        state, agentId.c_str(), agentDn.c_str());
            it1++;
        } else { //重签失败，则删除原信息，agentbar继续重签
            BGCC_WARN("ap", "ReSignIning:Fail to ReSignIn to ACD[%d].ret = %s",
                      state, ret.get_desc().c_str());
            AgentData* p = it1->second;
            delete p;
            p = NULL;
            _mapAgentIdData.erase(it1++);
        }
    }

    BGCC_NOTICE("ap",
                "ReSignInEnd:Success to ReSignIn to ACD[%d],SuccessAgentNum  = %d,TotalAgentNum = %d.",
                state, SuccessAgentNum, TotalAgentNum);
    return;
}

std::string AgentProxy::getProxyName(const std::map<std::string, std::string>& ctx) {
    std::string proxyName;
    std::map<std::string, std::string>::const_iterator citr;

    citr = ctx.find("ProxyName");

    if (citr != ctx.end()) {
        proxyName = citr->second;
    }

    return proxyName;
}

std::string AgentProxy::getProxyIP(const std::map<std::string, std::string>& ctx) {
    std::string peerIP;
    std::map<std::string, std::string>::const_iterator citr;

    citr = ctx.find("PeerIP");

    if (citr != ctx.end()) {
        peerIP = citr->second;
    }

    return peerIP;

}
void AgentProxy::ClearTimeOutAgentInfo(std::string agentId) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_NOTICE("ap", "Guard fail.");
        return ;
    }

    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_NOTICE("ap", "ClearTimeOutAgent:Agent is not exist : AgentId=%s!", agentId.c_str());
        return ;
    }

    uint64_t timestamp = TimeUtil::get_timestamp_us();
    uint64_t timestampBegin = it1->second->timestamp;

    if (it1->second->flag == 1) {
        if (timestamp > timestampBegin + _AgentTimeOut * 1000 * 1000) {
            AgentData* p = it1->second;
            delete p;
            p = NULL;
            _mapAgentIdData.erase(it1++);
            BGCC_NOTICE("ap",
                        "ClearTimeOutAgent:Agent Clear End.AgentId = %s,TimeStamp = %"int64ld",timenow = %"int64ld".",
                        agentId.c_str(), timestampBegin, timestamp);
        } else {
            BGCC_NOTICE("ap",
                        "ClearTimeOutAgent:Agent Clear End and Not to Clear.AgentId = %s,TimeStamp = %"int64ld",timenow = %"int64ld".",
                        agentId.c_str(), timestampBegin, timestamp);
        }
    }

    return ;
}

void AgentProxy::ChangeAgentListIp(AgentInfoListT& agentInfoList) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_NOTICE("ap", "Guard fail.");
        return ;
    }

    AgentInfoListT::iterator it1 = agentInfoList.begin();

    for (; it1 != agentInfoList.end(); it1++) {
        std::string agentId = it1->agentId;
        MapAgentIdDataType::iterator it2 = _mapAgentIdData.find(agentId);

        if (it2 == _mapAgentIdData.end()) {
            continue;
        }

        it1->agentIP = it2->second->agentIP;
    }

    return;
}

void AgentProxy::ChangeAgentIp(AgentInfoT& agentInfo) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_NOTICE("ap", "Guard fail.");
        return ;
    }

    std::string agentId = agentInfo.agentId;
    MapAgentIdDataType::iterator it1 = _mapAgentIdData.find(agentId);

    if (it1 == _mapAgentIdData.end()) {
        BGCC_NOTICE("ap", "ChangeAgentIp Cannot find agentId = %s.", agentId.c_str());
        return ;
    }

    agentInfo.agentIP = it1->second->agentIP;
    return;
}

AcdResultT AgentProxy::SignIn(const std::string& agentId,
                              const std::string& agentDn, const std::string& agentPwd,
                              const StatusChangeT& statusChangetype, bool autoAnswer,
                              bool fcSignin, const std::string& skills, int64_t& handle,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer SignIn PeerIP[%s]:AgentId = %s,AgentDn = %s,AgentPwd = %s,statusChangetype = %d,autoAnswer = %d,fcSignin = %d,skill = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), agentDn.c_str(), agentPwd.c_str(), statusChangetype.get_value(),
                autoAnswer, fcSignin, skills.c_str(), handle);
    AcdResultT ret;
    bool exist = true;
    APCONNACDSTATE state;

    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer SignIn:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    //清空超时的agentinfo
    ClearTimeOutAgentInfo(agentId);

    AgentData agentinfo_old;

    if (IsAgentHasExist(agentId)) {
        AgentData agentinfo_tmp ;

        (void)GetAgentData(agentId, agentinfo_old); //记录原坐席信息

        //同时存在old、new proxy是个暂时状态 但如果事件丢失，则保证新签入客户成功
        if (!agentinfo_old.proxyname_old.empty()) {
            BGCC_WARN("ap", "Transfer:SignIn OldProxyName is not NULL.AgentId = %s,handle=%"int64ld".",
                      agentId.c_str(), handle);
        }

        agentinfo_tmp.agentId = agentId;
        agentinfo_tmp.agentDn = agentDn;
        agentinfo_tmp.agentPwd = agentPwd;
        agentinfo_tmp.statusChangetype = statusChangetype;
        agentinfo_tmp.autoAnswer = autoAnswer;
        agentinfo_tmp.fcSignin = fcSignin;
        agentinfo_tmp.skill = skills;
        agentinfo_tmp.handle = handle;
        agentinfo_tmp.agentIP = peerIP;
        agentinfo_tmp.proxyname = getProxyName(ctx);

        BGCC_NOTICE("ap", "Transfer:SignIn getProxyName = %s.", agentinfo_tmp.proxyname.c_str());

        if (agentinfo_old.flag == 1) {
            BGCC_NOTICE("ap", "Transfer:SignIn flag = 1,and cannot SignIn.AgentId = %s,AgentDn = %s.",
                        agentId.c_str(), agentDn.c_str());
            return AcdResultT::ArApFailed;
        }

        if (agentinfo_tmp.proxyname.empty()) {
            BGCC_WARN("ap", "Transfer:SignIn Get proxyname fail.agentId = %s",
                      agentId.c_str());
            return AcdResultT::ArApFailed;
        }

        bool ret = UpdateAgentData(agentinfo_tmp);

        if (!ret) {
            BGCC_WARN("ap", "Transfer:SignIn Update AgentData fail.agentId = %s",
                      agentId.c_str());
            return AcdResultT::ArApFailed;
        }
    } else {
        exist = false;
        AgentData* agentinfo = new(std::nothrow)AgentData;

        if (!agentinfo) {
            BGCC_WARN("ap",
                      "AgentProxy Transfer:SignIn Cannot Alloc AgentData,AgentId = %s,handle = %"int64ld".",
                      agentId.c_str(), handle);
            return AcdResultT::ArApFailed;
        }

        (void)DelMapAgentIdData(agentId);

        BGCC_NOTICE("ap", "AgentProxy Transfer:SignIn Success to CreateCallbackProxy.");
        agentinfo->agentId = agentId;
        agentinfo->agentDn = agentDn;
        agentinfo->agentPwd = agentPwd;
        agentinfo->statusChangetype = statusChangetype;
        agentinfo->autoAnswer = autoAnswer;
        agentinfo->fcSignin = fcSignin;
        agentinfo->skill = skills;
        agentinfo->handle = handle;
        agentinfo->agentIP = peerIP;
        agentinfo->flag = 0;
        std::string proxyname = getProxyName(ctx);
        BGCC_NOTICE("ap", "AgentProxy Transfer:SignIn Get ProxyName = %s.", proxyname.c_str());
        agentinfo->proxyname = proxyname;
        agentinfo->proxyname_old = "";
        bool setmap_ret = SetMapAgentIdData(agentinfo);

        if (setmap_ret == false) {
            delete agentinfo;
            agentinfo = NULL;
            BGCC_WARN("ap",
                      "AgentProxy Transfer:SignIn Cannot Insert AgentData to HashMap,AgentId = %s,handle = %"int64ld".",
                      agentId.c_str(), handle);
            return AcdResultT::ArApFailed;
        }
    }

    bool fcSignin_tmp = true;

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SignIn(agentId, agentDn, agentPwd, statusChangetype,
                             autoAnswer, fcSignin_tmp, skills, handle, time_rcv); //所有签入都转化为强制签入

    if (ret != AcdResultT::ArSuccess) {
        //BGCC_NOTICE("ap","AgentProxy Transfer:SignIn Acd Return Success and Create ProxyData,AgentId[%s],handle[%ld].",agentId.c_str(),handle);

        (void)DelMapAgentIdData(agentId);

        if (exist) { //还原更新
            AgentData* agentinfo = new(std::nothrow)AgentData;

            if (!agentinfo) {
                BGCC_WARN("ap",
                          "AgentProxy Transfer:SignIn Cannot Alloc AgentData,AgentId = %s,handle = %"int64ld".",
                          agentId.c_str(), handle);
                return AcdResultT::ArApFailed;
            }

            agentinfo->agentId = agentinfo_old.agentId;
            agentinfo->agentDn = agentinfo_old.agentDn;
            agentinfo->agentPwd = agentinfo_old.agentPwd;
            agentinfo->statusChangetype = agentinfo_old.statusChangetype;
            agentinfo->autoAnswer = agentinfo_old.autoAnswer;
            agentinfo->fcSignin = agentinfo_old.fcSignin;
            agentinfo->skill = agentinfo_old.skill;
            agentinfo->handle = agentinfo_old.handle;
            agentinfo->flag = 0;
            agentinfo->agentIP = agentinfo_old.agentIP;
            agentinfo->proxyname = agentinfo_old.proxyname;
            agentinfo->proxyname_old = agentinfo_old.proxyname_old;
            bool setmap_ret = SetMapAgentIdData(agentinfo);

            if (setmap_ret == false) {
                delete agentinfo;
                agentinfo = NULL;
                BGCC_WARN("ap",
                          "AgentProxy Transfer:SignIn Cannot Insert AgentData to HashMap,AgentId = %s,handle = %"int64ld".",
                          agentId.c_str(), handle);
                return AcdResultT::ArApFailed;
            }
        }
    } else { //记录handle
        (void)SetAgentHandleById(agentId, handle);
    }

    BGCC_NOTICE("ap", "Transfer SignIn End:AgentId = %s,handle = %"int64ld",ret = %s.", agentId.c_str(),
                handle, ret.get_desc().c_str());
    return ret;
}


AcdResultT AgentProxy::SignOut(int64_t handle, const std::string& agentId,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer SignOut PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;

    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer SignOut:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer SignOut:Get Agent handle Success,agentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer SignOut:agentinfo is not exist.AgentId = %s", agentId.c_str());
        return AcdResultT::ArApFailed;
    }

    SetAgentFlag(agentId, 1);

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SignOut(handle_tmp, agentId, time_rcv);

    if (ret != AcdResultT::ArSuccess) {
        SetAgentFlag(agentId, 0);
        BGCC_WARN("ap", "Transfer SignOut Acd tell me Signout fail and restore signoutflag.");
    }

    BGCC_NOTICE("ap", "Transfer SignOut End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}

AcdResultT AgentProxy::SetAgentStatus(int64_t handle,
                                      const std::string& agentId,
                                      const AgentStatusT& agentStatus,
                                      const std::string& restReason,
                                      const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer SetAgentStatus PeerIP[%s]:AgentId = %s,handle = %"int64ld",agentStatus = %s,restReason = %s.",
                peerIP.c_str(), agentId.c_str(), handle, agentStatus.get_desc().c_str(), restReason.c_str());
    APCONNACDSTATE state;

    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer SetAgentStatus:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer SetAgentStatus:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer SetAgentStatus:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }


    ret = _pApClient->SetAgentStatus(handle_tmp, agentId, agentStatus, restReason, time_rcv);

    BGCC_NOTICE("ap", "Transfer SetAgentStatus End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetAgentStatus(int64_t handle,
                                      const std::string& agentId,
                                      AgentStatusT& agentStatus,
                                      const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer GetAgentStatus PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentStatus:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer GetAgentStatus:Get Agent handle Success,AgentId = %s ,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer GetAgentStatus:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentStatus(handle_tmp, agentId, agentStatus, time_rcv);

    BGCC_NOTICE("ap", "Transfer GetAgentStatus End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::ResetStatuschangetype(int64_t handle,
        const std::string& agentId,
        const StatusChangeT& statusChangetype,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;

    int64_t handle_tmp;
    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ResetStatuschangetype PeerIP[%s]:AgentId = %s,handle = %"int64ld",statusChangetype = %s.",
                peerIP.c_str(), agentId.c_str(), handle, statusChangetype.get_desc().c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ResetStatuschangetype:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ResetStatuschangetype:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ResetStatuschangetype:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ResetStatuschangetype(handle_tmp, agentId, statusChangetype, time_rcv);
    BGCC_NOTICE("ap", "Transfer ResetStatuschangetype End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}
AcdResultT AgentProxy::ResetAutoAnswer(int64_t handle,
                                       const std::string& agentId,
                                       bool autoAnswer,
                                       const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;
    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ResetAutoAnswer PeerIP[%s]:AgentId = %s,handle = %"int64ld",autoAnswer= %d.",
                peerIP.c_str(), agentId.c_str(), handle, autoAnswer);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ResetAutoAnswer:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ResetAutoAnswer:Get Agent handle Success,AgentId = %s ,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer ResetAutoAnswer:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ResetAutoAnswer(handle_tmp, agentId, autoAnswer, time_rcv);

    BGCC_NOTICE("ap", "Transfer ResetAutoAnswer End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}
AcdResultT AgentProxy::ResetSkill(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& skill,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ResetSkill PeerIP[%s]:AgentId = %s,handle = %"int64ld",skill= %s.",
                peerIP.c_str(), agentId.c_str(), handle, skill.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ResetSkill:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }


    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer ResetSkill:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer ResetSkill:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ResetSkill(handle_tmp, agentId, skill, time_rcv);

    BGCC_NOTICE("ap", "Transfer ResetSkill End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}


AcdResultT AgentProxy::Reset(int64_t handle, const std::string& agentId,
                             const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;

    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer Reset PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Reset:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }


    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer Reset:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer Reset:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }


    SetAgentFlag(agentId, 1);

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        SetAgentFlag(agentId, 0);
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Reset(handle_tmp, agentId, time_rcv);

    BGCC_NOTICE("ap", "Transfer Reset End:AgentId = %s,handle = %"int64ld",ret = %s.", agentId.c_str(),
                handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::OutboundCall(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& callerId,
                                    const std::string& destId,
                                    const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum,
                                    int32_t timeout,
                                    const CallModeT& callMode,
                                    const CallTypeT& callType,
                                    const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer OutboundCall PeerIP[%s]:AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
                forCalleeDispNum.c_str());
    APCONNACDSTATE state;

    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer OutboundCall:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer OutboundCall:Get Agent handle Success,AgentId = %s,DestId = %s,handle = %"int64ld".",
                    agentId.c_str(), destId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer OutboundCall:agentinfo is not exist.AgentId = %s,DestId = %s,handle = %"int64ld".",
                  agentId.c_str(), destId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->OutboundCall(handle_tmp, agentId, callerId, destId, forCallerDispNum,
                                   forCalleeDispNum, timeout, callMode, callType, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer OutboundCall End:AgentId = %s,DestId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::AnswerCall(int64_t handle,
                                  const std::string& agentId,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;
    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer AnswerCall PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer AnswerCall:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer AnswerCall:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer AnswerCall:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->AnswerCall(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer AnswerCall End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::ReleaseCall(int64_t handle,
                                   const std::string& agentId,
                                   const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ReleaseCall PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ReleaseCall:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer ReleaseCall:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer ReleaseCall:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ReleaseCall(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer ReleaseCall End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}

AcdResultT AgentProxy::Hold(int64_t handle,
                            const std::string& agentId,
                            const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer Hold PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Hold:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer Hold:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer Hold:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Hold(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer Hold End:AgentId = %s,handle = %"int64ld",ret = %s.", agentId.c_str(),
                handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::RetrieveHeld(int64_t handle,
                                    const std::string& agentId,
                                    const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer RetrieveHeld PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer RetrieveHeld:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer RetrieveHeld:Get Agent handle Success,AgentId = %s,handle = %"int64ld".", agentId.c_str(),
                    handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer RetrieveHeld:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->RetrieveHeld(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer RetrieveHeld End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::Consult(int64_t handle,
                               const std::string& agentId,
                               const std::string& callerId,
                               const std::string& destId,
                               const std::string& forCallerDispNum,
                               const std::string& forCalleeDispNum,
                               const CallTypeT& callType,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    AgentData agentinfo;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer Consult PeerIP[%s]:AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
                forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Consult:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer Consult:Get Agent handle Success,AgentId = %s,DestId = %s,handle = %"int64ld".",
                    agentId.c_str(), destId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer Consult:agentinfo is not exist.AgentId = %s,DestId = %s,handle = %"int64ld".",
                  agentId.c_str(), destId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Consult(handle_tmp, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum,
                              callType, time_rcv);
    BGCC_NOTICE("ap", "Transfer Consult End:AgentId = %s,DestId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::ConsultReconnect(int64_t handle,
                                        const std::string& agentId,
                                        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ConsultReconnect PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ConsultReconnect:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ConsultReconnect:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ConsultReconnect:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ConsultReconnect(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer ConsultReconnect End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::ConsultTransfer(int64_t handle, const std::string& agentId,
                                       const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ConsultTransfer PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ConsultTransfer:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ConsultTransfer:Get Agent handle Success,AgentId = %s ,handle = %"int64ld"",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer ConsultTransfer:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ConsultTransfer(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer ConsultTransfer End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;

}
AcdResultT AgentProxy::SingleStepTransfer(int64_t handle,
        const std::string& agentId,
        const std::string& callerId,
        const std::string& destId,
        const std::string& forCallerDispNum,
        const std::string& forCalleeDispNum,
        bool isPassthrough,
        const CallTypeT& transferType,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer SingleStepTransfer PeerIP[%s]:AgentId = %s,handle = %"int64ld",callerId = %s,destId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), handle, callerId.c_str(), destId.c_str(), forCallerDispNum.c_str(),
                forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer SingleStepTransfer:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer SingleStepTransfer:Get Agent handle Success,AgentId = %s,DestId = %s,handle = %"int64ld"",
                    agentId.c_str(), destId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer SingleStepTransfer:agentinfo is not exist.AgentId = %s,DestId = %s,handle = %"int64ld".",
                  agentId.c_str(), destId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SingleStepTransfer(handle_tmp, agentId, callerId, destId, forCallerDispNum,
                                         forCalleeDispNum, isPassthrough, transferType, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer SingleStepTransfer End:AgentId = %s,DestId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::ConsultConference(int64_t handle,
        const std::string& agentId,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ConsultConference PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ConsultConference:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ConsultConference:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ConsultConference:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ConsultConference(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer ConsultConference End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;

}
AcdResultT AgentProxy::ConferenceJoin(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& callerId,
                                      const std::string& destAgentId,
                                      const std::string& forCallerDispNum,
                                      const std::string& forCalleeDispNum,
                                      const ConferenceT& conferenceType,
                                      const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ConferenceJoin PeerIP[%s]:AgentId = %s,handle = %"int64ld",callerId = %s,destAgentId = %s,forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), handle, callerId.c_str(), destAgentId.c_str(),
                forCallerDispNum.c_str(), forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ConferenceJoin:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ConferenceJoin:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ConferenceJoin:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ConferenceJoin(handle_tmp, agentId, callerId, destAgentId, forCallerDispNum,
                                     forCalleeDispNum, conferenceType, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer ConferenceJoin End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::SetAssociateData(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& key,
                                        const std::string& value,
                                        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer SetAssociateData PeerIP[%s]:AgentId = %s,handle = %"int64ld",key = %s,value = %s.",
                peerIP.c_str(), agentId.c_str(), handle, key.c_str(), value.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer SetAssociateData:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer SetAssociateData:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer SetAssociateData:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SetAssociateData(handle_tmp, agentId, key, value, time_rcv);
    BGCC_NOTICE("ap", "Transfer SetAssociateData End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::GetAssociateData(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& key,
                                        std::string& value,
                                        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer GetAssociateData PeerIP[%s]:AgentId = %s,handle = %"int64ld",key = %s.",
                peerIP.c_str(), agentId.c_str(), handle, key.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAssociateData:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer GetAssociateData:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAssociateData:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAssociateData(handle_tmp, agentId, key, value, time_rcv);
    BGCC_NOTICE("ap", "Transfer GetAssociateData End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::ForceSignIn(int64_t handle,
                                   const std::string& agentId, const std::string& destAgentId,
                                   const std::string& agentDn, const std::string& agentPwd,
                                   const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin,
                                   const std::string& skills, const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ForceSignIn PeerIP[%s]:AgentId = %s,destAgentId = %s,AgentDn = %s,AgentPwd = %s,statusChangetype = %d,autoAnswer = %d,fcSignin = %d,skill = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), agentDn.c_str(), agentPwd.c_str(),
                statusChangetype.get_value(), autoAnswer, fcSignin, skills.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ForceSignIn:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ForceSignIn:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ForceSignIn:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ForceSignIn(handle_tmp, agentId, destAgentId, agentDn, agentPwd, statusChangetype,
                                  autoAnswer, fcSignin, skills, time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        AgentData* agentinfo = new(std::nothrow)AgentData;

        if (!agentinfo) {
            BGCC_WARN("ap",
                      "AgentProxy Transfer:ForceSignIn Cannot Alloc AgentData,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                      agentId.c_str(), destAgentId.c_str(), handle_tmp);
            return AcdResultT::ArApFailed;
        }


        (void)DelMapAgentIdData(destAgentId);

        std::string proxyname = getProxyName(ctx);

        if (!proxyname.empty()) {
            agentinfo->agentId = destAgentId;
            agentinfo->agentDn = agentDn;
            agentinfo->agentPwd = agentPwd;
            agentinfo->statusChangetype = statusChangetype;
            agentinfo->autoAnswer = autoAnswer;
            agentinfo->fcSignin = fcSignin;
            agentinfo->skill = skills;
            agentinfo->handle = handle_tmp;
            agentinfo->flag = 0;
            agentinfo->agentIP = peerIP;
            agentinfo->proxyname = proxyname;
            agentinfo->proxyname_old = "";

            bool setmap_ret = SetMapAgentIdData(agentinfo);

            if (setmap_ret == false) {
                delete agentinfo;
                agentinfo = NULL;

                BGCC_WARN("ap",
                          "AgentProxy Transfer:ForceSignIn Cannot Insert AgentData to HashMap,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                          agentId.c_str(), destAgentId.c_str(), handle_tmp);
                return AcdResultT::ArApFailed;
            }
        } else {
            BGCC_WARN("ap",
                      "AgentProxy Transfer:ForceSignIn Cannot Alloc AcdCallback Proxy,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                      agentId.c_str(), destAgentId.c_str(), handle_tmp);
            delete agentinfo;
            return AcdResultT::ArApFailed;
        }
    }

    return ret;
}
AcdResultT AgentProxy::ForceSignOut(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& destAgentId,
                                    const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ForceSignOut PeerIP[%s]:AgentId = %s,destAgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ForceSignOut:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ForceSignOut:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ForceSignOut:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    SetAgentFlag(destAgentId, 1);

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        SetAgentFlag(destAgentId, 0);
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ForceSignOut(handle_tmp, agentId, destAgentId, time_rcv);

    if (ret != AcdResultT::ArSuccess) {
        SetAgentFlag(destAgentId, 0);
        BGCC_WARN("ap", "Transfer ForceSignOut Acd tell me Signout fail and restore signoutflag.");
    }

    BGCC_NOTICE("ap",
                "Transfer ForceSignOut End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;

}
AcdResultT AgentProxy::ForceSetAgentStatus(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        const AgentStatusT& agentStatus,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer ForceSetAgentStatus PeerIP[%s]:AgentId = %s,destAgentId = %s,handle = %"int64ld",agentStatus = %s.",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), handle, agentStatus.get_desc().c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer ForceSetAgentStatus:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer ForceSetAgentStatus:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer ForceSetAgentStatus:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ForceSetAgentStatus(handle_tmp, agentId, destAgentId, agentStatus, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer ForceSetAgentStatus End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::Listen(int64_t handle,
                              const std::string& agentId,
                              const std::string& callerId,
                              const std::string& destAgentId,
                              const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer Listen PeerIP[%s]:AgentId = %s,callerId = %s,destAgentId = %s,handle = %"int64ld",forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), callerId.c_str(), destAgentId.c_str(), handle,
                forCallerDispNum.c_str(), forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Listen:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer Listen:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer Listen:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Listen(handle_tmp, agentId, callerId, destAgentId, forCallerDispNum,
                             forCalleeDispNum, time_rcv);
    BGCC_NOTICE("ap", "Transfer Listen End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::StopListen(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer StopListen PeerIP[%s]:AgentId = %s,destAgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer StopListen:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer StopListen:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld"",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer StopListen:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->StopListen(handle_tmp, agentId, destAgentId, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer StopListen End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::Insert(int64_t handle,
                              const std::string& agentId,
                              const std::string& callerId,
                              const std::string& destAgentId,
                              const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer Insert PeerIP[%s]:AgentId = %s,callerId = %s,destAgentId = %s,handle = %"int64ld",forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), callerId.c_str(), destAgentId.c_str(), handle,
                forCallerDispNum.c_str(), forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Insert:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer Insert:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer Insert:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Insert(handle_tmp, agentId, callerId, destAgentId, forCallerDispNum,
                             forCalleeDispNum, time_rcv);
    BGCC_NOTICE("ap", "Transfer Insert End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::StopInsert(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer StopInsert PeerIP[%s]:AgentId = %s,destAgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer StopInsert:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer StopInsert:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld"",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer StopInsert:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->StopInsert(handle_tmp, agentId, destAgentId, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer StopInsert End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::SwitchInsertorListen(int64_t handle,
        const std::string& agentId,
        const std::string& callerId,
        const std::string& destAgentId,
        const std::string& forCallerDispNum,
        const std::string& forCalleeDispNum,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {

    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer SwitchInsertorListen PeerIP[%s]:AgentId = %s,callerId = %s,destAgentId = %s,handle = %"int64ld",forCallerDispNum = %s,forCalleeDispNum = %s.",
                peerIP.c_str(), agentId.c_str(), callerId.c_str(), destAgentId.c_str(), handle,
                forCallerDispNum.c_str(), forCalleeDispNum.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer SwitchInsertorListen:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer SwitchInsertorListen:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld"",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer SwitchInsertorListen:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SwitchInsertorListen(handle_tmp, agentId, callerId, destAgentId, forCallerDispNum,
                                           forCalleeDispNum, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer SwitchInsertorListen End:AgentId = %s,destAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::Break(int64_t handle,
                             const std::string& agentId,
                             const std::string& destAgentId,
                             const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer Break PeerIP[%s]:AgentId = %s,destAgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), destAgentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer Break:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer Break:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer Break:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Break(handle_tmp, agentId, destAgentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer Break End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::SendDTMF(int64_t handle,
                                const std::string& agentId,
                                const std::string& digitals,
                                const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer Break PeerIP[%s]:AgentId = %s,handle = %"int64ld",digitals = %s.",
                peerIP.c_str(), agentId.c_str(), handle, digitals.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer SendDTMF:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer SendDTMF:Get Agent handle Success,AgentId = %s,handle = %"int64ld"",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer SendDTMF:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SendDTMF(handle_tmp, agentId, digitals, time_rcv);
    BGCC_NOTICE("ap", "Transfer SendDTMF End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::StartPlay(int64_t handle,
                                 const std::string& agentId,
                                 const std::string& filename,
                                 const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer StartPlay PeerIP[%s]:AgentId = %s,handle = %"int64ld",filename= %s.",
                peerIP.c_str(), agentId.c_str(), handle, filename.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer StartPlay:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer StartPlay:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer StartPlay:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->StartPlay(handle_tmp, agentId, filename, time_rcv);
    BGCC_NOTICE("ap", "Transfer StartPlay End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::StopPlay(int64_t handle, const std::string& agentId,
                                const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer StopPlay PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer StopPlay:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer StopPlay:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer StopPlay:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->StopPlay(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer StopPlay End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}


AcdResultT AgentProxy::MuteOn(int64_t handle, const std::string& agentId,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer MuteOn PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer MuteOn:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer MuteOn:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer MuteOn:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->MuteOn(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer MuteOn End:AgentId = %s,handle = %"int64ld",ret = %s.", agentId.c_str(),
                handle_tmp, ret.get_desc().c_str());

    return ret;
}
AcdResultT AgentProxy::MuteOff(int64_t handle, const std::string& agentId,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer MuteOff PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer MuteOff:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer MuteOff:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer MuteOff:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->MuteOff(handle_tmp, agentId, time_rcv);
    BGCC_NOTICE("ap", "Transfer MuteOff End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetAgentDetailByAgentID(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentId,
        AgentInfoT& agentInfo,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetAgentDetailByAgentID PeerIP[%s]:AgentId = %s,handle = %"int64ld",destAgentId = %s.",
               peerIP.c_str(), agentId.c_str(), handle, destAgentId.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailByAgentID:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentDetailByAgentID:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailByAgentID:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentDetailByAgentID(handle_tmp, agentId, destAgentId, agentInfo, time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        ChangeAgentIp(agentInfo);
    }

    BGCC_TRACE("ap",
               "Transfer GetAgentDetailByAgentID End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}

AcdResultT AgentProxy::GetAgentDetailByAgentDN(int64_t handle,
        const std::string& agentId,
        const std::string& destAgentDn,
        AgentInfoT& agentInfo,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetAgentDetailByAgentDN PeerIP[%s]:AgentId = %s,handle = %"int64ld",destAgentDn = %s.",
               peerIP.c_str(), agentId.c_str(), handle, destAgentDn.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailByAgentDN:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentDetailByAgentDN:Get Agent handle Success,AgentId = %s,DestAgentDn = %s,handle = %"int64ld".",
                   agentId.c_str(), destAgentDn.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailByAgentDN:agentinfo is not exist.AgentId = %s,DestAgentDn = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentDn.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentDetailByAgentDN(handle_tmp, agentId, destAgentDn, agentInfo, time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        ChangeAgentIp(agentInfo);
    }

    BGCC_TRACE("ap",
               "Transfer GetAgentDetailByAgentDN End:AgentId = %s,DestAgentDn = %s ,handle = %"int64ld",ret = %s.",
               agentId.c_str(), destAgentDn.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}


AcdResultT AgentProxy::GetAgentDetailsByAgentIDs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentIdList,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap", "Transfer GetAgentDetailsByAgentIDs PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
               peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailsByAgentIDs:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentDetailsByAgentIDs:Get Agent handle Success,AgentId = %s,handle = %"int64ld"",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailsByAgentIDs:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentDetailsByAgentIDs(handle_tmp, agentId, destAgentIdList, agentInfoList,
            time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        ChangeAgentListIp(agentInfoList);
    }

    BGCC_TRACE("ap",
               "Transfer GetAgentDetailsByAgentIDs End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetAgentDetailsByAgentDNs(int64_t handle,
        const std::string& agentId,
        const StringListT& destAgentDnList,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap", "Transfer GetAgentDetailsByAgentDNs PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
               peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailsByAgentDNs:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentDetailsByAgentDNs:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailsByAgentDNs:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentDetailsByAgentDNs(handle_tmp, agentId, destAgentDnList, agentInfoList,
            time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        ChangeAgentListIp(agentInfoList);
    }

    BGCC_TRACE("ap",
               "Transfer GetAgentDetailsByAgentDNs End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetRecordFileName(int64_t handle,
        const std::string& agentId,
        std::string& filename,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer GetRecordFileName PeerIP[%s]:AgentId = %s,handle = %"int64ld",filename = %s.",
                peerIP.c_str(), agentId.c_str(), handle, filename.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetRecordFileName:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer GetRecordFileName:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetRecordFileName:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetRecordFileName(handle_tmp, agentId, filename, time_rcv);
    BGCC_NOTICE("ap",
                "Transfer GetRecordFileName End:AgentId = %s,handle = %"int64ld",filename = %s,ret = %s.",
                agentId.c_str(), handle_tmp, filename.c_str(), ret.get_desc().c_str());

    return ret;
}


AcdResultT AgentProxy::GetSkill(
    int64_t handle,
    const std::string& agentId,
    StringListT& skill,
    const std::map<std::string, std::string>& ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer GetSkill PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer GetSkill:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer GetSkill:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer GetSkill:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetSkill(handle_tmp, agentId, skill, time_rcv);
    BGCC_NOTICE("ap", "Transfer GetSkill End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;

}

AcdResultT AgentProxy::GetRestReason(int64_t handle,
                                     const std::string& agentId,
                                     StringListT& restReason,
                                     const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer GetRestReason PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetRestReason:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer GetRestReason:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer GetRestReason:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetRestReason(handle_tmp, agentId, restReason, time_rcv);
    BGCC_NOTICE("ap", "Transfer GetRestReason End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetAgentNumberBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);

    BGCC_TRACE("ap",
               "Transfer GetAgentNumberBySkill PeerIP[%s]:AgentId = %s,handle = %"int64ld",skill = %s.",
               peerIP.c_str(), agentId.c_str(), handle, skill.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentNumberBySkill:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentNumberBySkill:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentNumberBySkill:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentNumberBySkill(handle_tmp, agentId, skill, agentNum, time_rcv);
    BGCC_TRACE("ap", "Transfer GetAgentNumberBySkill End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}

AcdResultT AgentProxy::GetAgentDetailsBySkill(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& agentNum,
        AgentInfoListT& agentInfoList,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetAgentDetailsBySkill PeerIP[%s]:AgentId = %s,handle = %"int64ld",skill = %s.",
               peerIP.c_str(), agentId.c_str(), handle, skill.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetAgentdetailsBySkill:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetAgentDetailsBySkill:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetAgentDetailsBySkill:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetAgentDetailsBySkill(handle_tmp, agentId, skill, agentNum, agentInfoList,
            time_rcv);

    if (ret == AcdResultT::ArSuccess) {
        ChangeAgentListIp(agentInfoList);
        BGCC_TRACE("ap", "Transfer GetAgentDetailsBySkill Change AgentIP End.");
    }

    BGCC_TRACE("ap", "Transfer GetAgentDetailsBySkill End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}


AcdResultT AgentProxy::GetSkillWaitingNumber(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        int32_t& freeNum,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetSkillWaitingNumber PeerIP[%s]:AgentId = %s,handle = %"int64ld",skill = %s.",
               peerIP.c_str(), agentId.c_str(), handle, skill.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetSkillWaitingNumber:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetSkillWaitingNumber:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetSkillWaitingNumber:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetSkillWaitingNumber(handle_tmp, agentId, skill, queueNum, freeNum, time_rcv);
    BGCC_TRACE("ap", "Transfer GetSkillWaitingNumber End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetSkillWaitingCallInfo(int64_t handle,
        const std::string& agentId,
        const std::string& skill,
        int32_t& queueNum,
        QueueInfoListT& queueInfoList,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetSkillWaitingCallInfo PeerIP[%s]:AgentId = %s,handle = %"int64ld",skill = %s.",
               peerIP.c_str(), agentId.c_str(), handle, skill.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetSkillWaitingCallInfo:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetSkillWaitingCallInfo:Get Agent handle Success,AgentId = %s,handle = %"int64ld"",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetSkillWaitingCallInfo:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetSkillWaitingCallInfo(handle_tmp, agentId, skill, queueNum, queueInfoList,
            time_rcv);
    BGCC_TRACE("ap", "Transfer GetSkillWaitingCallInfo End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetPrivateQueue(int64_t handle,
                                       const std::string& agentId,
                                       const std::string& destAgentId,
                                       int32_t& queueNum,
                                       QueueInfoListT& queueInfoList,
                                       const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap",
               "Transfer GetPrivateQueue PeerIP[%s]:AgentId = %s,handle = %"int64ld",destAgentId= %s.",
               peerIP.c_str(), agentId.c_str(), handle, destAgentId.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetPrivateQueue:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer GetPrivateQueue:Get Agent handle Success,AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), destAgentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer GetPrivateQueue:agentinfo is not exist.AgentId = %s,DestAgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), destAgentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetPrivateQueue(handle_tmp, agentId, destAgentId, queueNum, queueInfoList,
                                      time_rcv);
    BGCC_TRACE("ap",
               "Transfer GetPrivateQueue End:AgentId = %s,DestAgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), destAgentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::GetSysInfo(int64_t handle,
                                  const std::string& agentId,
                                  SysInfoT& sysInfo,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap", "Transfer GetSysInfo PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
               peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer GetSysInfo:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap", "Transfer GetSysInfo:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer GetSysInfo:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->GetSysInfo(handle_tmp, agentId, sysInfo, time_rcv);
    BGCC_TRACE("ap", "Transfer GetSysInfo End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}

AcdResultT AgentProxy::SynchronizeCTITime(int64_t handle,
        const std::string& agentId,
        int64_t& timestamp,
        const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_TRACE("ap", "Transfer SynchronizeCTITime PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
               peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer SynchronizeCTITime:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_TRACE("ap",
                   "Transfer SynchronizeCTITime:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                   agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap",
                  "Transfer SynchronizeCTITime:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->SynchronizeCTITime(handle_tmp, agentId, timestamp, time_rcv);
    BGCC_TRACE("ap", "Transfer SynchronizeCTITime End:AgentId = %s,handle = %"int64ld",ret = %s.",
               agentId.c_str(), handle_tmp, ret.get_desc().c_str());

    return ret;
}


AcdResultT AgentProxy::Heartbeat(int64_t handle, const std::string& agentId,
                                 const std::map<std::string, std::string> ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer Heartbeat PeerIP[%s]:AgentId = %s,handle = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer Heartbeat:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap", "Transfer Heartbeat:Get Agent handle Success,AgentId = %s,handle = %"int64ld".",
                    agentId.c_str(), handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer Heartbeat:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->Heartbeat(handle_tmp, agentId, time_rcv);

    if (ret == AcdResultT::ArNoSignin) {
        BGCC_NOTICE("ap",
                    "Transfer Heartbeat ACD return AcdResultT::ArNoSign and to Delete AgentData,AgentId = %s.",
                    agentId.c_str());
        (void)DelMapAgentIdData(agentId);
    }

    BGCC_NOTICE("ap", "Transfer Heartbeat End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}


AcdResultT AgentProxy::ResetConfig(const std::string& password,
                                   const std::map<std::string, std::string>& ctx, uint64_t time_rcv) {
    AcdResultT ret;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap", "Transfer ResetConfig PeerIP[%s]:password= %s.", peerIP.c_str(),
                password.c_str());

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap", "Transfer ResetConfig:NowState = %d,return fail connect to ACD.", state);
        return AcdResultT::ArConnAcdFail;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->ResetConfig(password, time_rcv);

    BGCC_NOTICE("ap", "Transfer ResetConfig End:ret = %s", ret.get_desc().c_str());
    return ret;
}

AcdResultT AgentProxy::JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId,
                                    const std::map<std::string, std::string>& ctx, uint64_t time_rcv) {
    AcdResultT ret;
    int64_t handle_tmp;

    //获取客户端IP地址
    std::string peerIP = getProxyIP(ctx);
    BGCC_NOTICE("ap",
                "Transfer JumptheQueue PeerIP[%s]:agentId= %s,handle = %"int64ld",requestId = %"int64ld".",
                peerIP.c_str(), agentId.c_str(), handle, requestId);

    APCONNACDSTATE state;
    state = GetCtiService();

    if (AP_CONNACD_BACKING == state || AP_CONNACD_UNKNOW == state) {
        BGCC_WARN("ap",
                  "Transfer JumptheQueue:AgentId = %s,NowState = %d,return agentbar fail connect to ACD.",
                  agentId.c_str(), state);
        return AcdResultT::ArConnAcdFail;
    }

    if (GetAgentHandleById(agentId, handle_tmp)) {
        BGCC_NOTICE("ap",
                    "Transfer JumptheQueue:Get Agent handle Success,AgentId = %s,handle = %"int64ld".", agentId.c_str(),
                    handle_tmp);
    } else {
        BGCC_WARN("ap", "Transfer JumptheQueue:agentinfo is not exist.AgentId = %s,handle = %"int64ld".",
                  agentId.c_str(), handle_tmp);
        return AcdResultT::ArApFailed;
    }

    if (!_pApClient) {
        BGCC_WARN("ap", "Client is NULL.");
        return AcdResultT::ArApFailed;
    }

    ret = _pApClient->JumptheQueue(handle_tmp, agentId, requestId, time_rcv);

    BGCC_NOTICE("ap", "Transfer JumptheQueue End:AgentId = %s,handle = %"int64ld",ret = %s.",
                agentId.c_str(), handle_tmp, ret.get_desc().c_str());
    return ret;
}

bool AgentProxy::ReLoadConfig() {
    ConfUnit* root = ConfLoader::load_conf(APCONFIG);

    if (NULL == root) {
        BGCC_WARN("ap", "ConfLoader::load_conf return a NULL ConfUnit pointer.");
        delete root;
        return false;
    }

    ConfUnit* confdevs = (*root)["ap"];

    if (NULL == confdevs) {
        BGCC_WARN("ap", "Not find conf_devices section.");
        delete root;
        return false;
    }

    if (ConfUnit::UT_ARRAY != confdevs->get_type()) {
        BGCC_WARN("ap", "conf_devices is not an array.");
        delete root;
        return false;
    }

    ConfUnit::const_iterator citr;
    int32_t i;

    for (citr = confdevs->begin(), i = 1; citr != confdevs->end(); ++citr, ++i) {
        ConfUnit* dev = *citr;

        if (NULL == dev || ConfUnit::UT_GROUP != dev->get_type()) {
            BGCC_WARN("ap", "counter a non device group in citr");
            delete root;
        }

        ConfUnit* ap_warn_sendmsg_timeout = (*dev)["ap_warn_sendmsg_timeout"];

        if (NULL == ap_warn_sendmsg_timeout || ConfUnit::UT_STRING != ap_warn_sendmsg_timeout->get_type()) {
            BGCC_WARN("ap", "no ap_warn_sendmsg_timeout variable in ApConf");
            delete root;
            return false;
        }

        if (false == StringUtil::str2int32(ap_warn_sendmsg_timeout->to_string().c_str(),
                                           _apWarnSendmsgTimeout)) {
            BGCC_WARN("ap", "string 2 int32 fail.");
            delete root;
            return false;
        }
    }

    BGCC_NOTICE("ap", "Reload Config Success.");
    delete root;

    return true;
}

bool AgentProxy::GetAgents(ApAgentInfoListT& agentInfoList) {
    ScopeGuard guard(&_mapMutex);

    if (!guard.is_locked()) {
        BGCC_NOTICE("ap", "Guard fail.");
        return false;
    }

    BGCC_NOTICE("ap", "GetAgentsInfo Enter.");
    MapAgentIdDataType::iterator it1 = _mapAgentIdData.begin();
    int32_t count = 0;

    while (it1 != _mapAgentIdData.end()) {
        ApAgentInfo agentInfo;
        agentInfo.agentId = it1->second->agentId;
        agentInfo.agentDn = it1->second->agentDn;
        agentInfo.agentPwd = it1->second->agentPwd;
        agentInfo.statusChangetype = it1->second->statusChangetype;
        agentInfo.autoAnswer = it1->second->autoAnswer;
        agentInfo.fcSignin = it1->second->fcSignin;
        agentInfo.skills = it1->second->skill;
        agentInfo.handle = it1->second->handle;
        agentInfo.flag = it1->second->flag;
        agentInfo.proxyname = it1->second->proxyname;
        agentInfo.proxyname_old = it1->second->proxyname_old;


        agentInfoList.push_back(agentInfo);
        count++;
        it1++;
    }

    BGCC_NOTICE("ap", "GetAgentsInfo End.return AgentInfo count = %d.", count);

    return true;
}
