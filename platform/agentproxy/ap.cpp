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

#include "ap.h"

namespace ap {
ApAgentInfo::ApAgentInfo() {
}

ApAgentInfo::~ApAgentInfo() {
}

bool ApAgentInfo::operator==(const ApAgentInfo& rhs) const {
    if (this == &rhs) {
        return true;
    }

    if (agentId != rhs.agentId) {
        return false;
    }

    if (agentDn != rhs.agentDn) {
        return false;
    }

    if (agentPwd != rhs.agentPwd) {
        return false;
    }

    if (statusChangetype != rhs.statusChangetype) {
        return false;
    }

    if (autoAnswer != rhs.autoAnswer) {
        return false;
    }

    if (fcSignin != rhs.fcSignin) {
        return false;
    }

    if (skills != rhs.skills) {
        return false;
    }

    if (proxyname != rhs.proxyname) {
        return false;
    }

    if (proxyname_old != rhs.proxyname_old) {
        return false;
    }

    if (handle != rhs.handle) {
        return false;
    }

    if (flag != rhs.flag) {
        return false;
    }

    return true;
}

bool ApAgentInfo::operator!=(const ApAgentInfo& rhs) const {
    return !(*this == rhs);
}

bool ApAgentInfo::operator< (const ApAgentInfo& rhs) const {
    if (this == &rhs) {
        return false;
    }

    if (agentId < rhs.agentId) {
        return true;
    } else if (rhs.agentId < agentId) {
        return false;
    }

    if (agentDn < rhs.agentDn) {
        return true;
    } else if (rhs.agentDn < agentDn) {
        return false;
    }

    if (agentPwd < rhs.agentPwd) {
        return true;
    } else if (rhs.agentPwd < agentPwd) {
        return false;
    }

    if (statusChangetype < rhs.statusChangetype) {
        return true;
    } else if (rhs.statusChangetype < statusChangetype) {
        return false;
    }

    if (autoAnswer < rhs.autoAnswer) {
        return true;
    } else if (rhs.autoAnswer < autoAnswer) {
        return false;
    }

    if (fcSignin < rhs.fcSignin) {
        return true;
    } else if (rhs.fcSignin < fcSignin) {
        return false;
    }

    if (skills < rhs.skills) {
        return true;
    } else if (rhs.skills < skills) {
        return false;
    }

    if (proxyname < rhs.proxyname) {
        return true;
    } else if (rhs.proxyname < proxyname) {
        return false;
    }

    if (proxyname_old < rhs.proxyname_old) {
        return true;
    } else if (rhs.proxyname_old < proxyname_old) {
        return false;
    }

    if (handle < rhs.handle) {
        return true;
    } else if (rhs.handle < handle) {
        return false;
    }

    if (flag < rhs.flag) {
        return true;
    } else if (rhs.flag < flag) {
        return false;
    }

    return false;
}

int32_t ApAgentInfo::read(bgcc::SharedPointer<bgcc::IProtocol> proto) {
    int32_t ret = 0;
    std::string fname;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(fname);

    if (ret < 0) {
        return ret;
    }

    while (true) {
        ret = proto->readFieldBegin(fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        case 1:
            ret = proto->readString(agentId);

            if (ret < 0) {
                return ret;
            }

            break;

        case 2:
            ret = proto->readString(agentDn);

            if (ret < 0) {
                return ret;
            }

            break;

        case 3:
            ret = proto->readString(agentPwd);

            if (ret < 0) {
                return ret;
            }

            break;

        case 4:
            int32_t ele_var115;
            ret = proto->readInt32(ele_var115);

            if (ret < 0) {
                return ret;
            }

            statusChangetype = ele_var115;
            break;

        case 5:
            ret = proto->readBool(autoAnswer);

            if (ret < 0) {
                return ret;
            }

            break;

        case 6:
            ret = proto->readBool(fcSignin);

            if (ret < 0) {
                return ret;
            }

            break;

        case 7:
            ret = proto->readString(skills);

            if (ret < 0) {
                return ret;
            }

            break;

        case 8:
            ret = proto->readString(proxyname);

            if (ret < 0) {
                return ret;
            }

            break;

        case 9:
            ret = proto->readString(proxyname_old);

            if (ret < 0) {
                return ret;
            }

            break;

        case 10:
            ret = proto->readInt64(handle);

            if (ret < 0) {
                return ret;
            }

            break;

        case 11:
            ret = proto->readInt32(flag);

            if (ret < 0) {
                return ret;
            }

            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    return proto->readStructEnd();
}

int32_t ApAgentInfo::read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request,
                          int32_t request_len) {
    int32_t ret = 0;
    std::string fname;
    int32_t nread = 0;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(request + nread, request_len - nread, fname);

    if (ret < 0) {
        return ret;
    }

    nread += ret;

    while (true) {
        ret = proto->readFieldBegin(request + nread, request_len - nread, fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        nread += ret;

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        case 1:
            ret = proto->readString(request + nread, request_len - nread, agentId);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 2:
            ret = proto->readString(request + nread, request_len - nread, agentDn);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 3:
            ret = proto->readString(request + nread, request_len - nread, agentPwd);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 4:
            int32_t ele_var116;
            ret = proto->readInt32(request + nread, request_len - nread, ele_var116);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            statusChangetype = ele_var116;
            break;

        case 5:
            ret = proto->readBool(request + nread, request_len - nread, autoAnswer);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 6:
            ret = proto->readBool(request + nread, request_len - nread, fcSignin);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 7:
            ret = proto->readString(request + nread, request_len - nread, skills);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 8:
            ret = proto->readString(request + nread, request_len - nread, proxyname);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 9:
            ret = proto->readString(request + nread, request_len - nread, proxyname_old);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 10:
            ret = proto->readInt64(request + nread, request_len - nread, handle);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;

        case 11:
            ret = proto->readInt32(request + nread, request_len - nread, flag);

            if (ret < 0) {
                return ret;
            }

            nread += ret;
            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    ret = proto->readStructEnd();

    if (ret < 0) {
        return ret;
    }

    return nread;
}

int32_t ApAgentInfo::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;

    ret = proto->writeStructBegin("ApAgentInfo");

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(agentId);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 2);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(agentDn);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("agentPwd", bgcc::IDSTR, 3);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(agentPwd);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("statusChangetype", bgcc::IDINT32, 4);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeInt32(statusChangetype.get_value());

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("autoAnswer", bgcc::IDBOOL, 5);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeBool(autoAnswer);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("fcSignin", bgcc::IDBOOL, 6);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeBool(fcSignin);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("skills", bgcc::IDSTR, 7);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(skills);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("proxyname", bgcc::IDSTR, 8);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(proxyname);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("proxyname_old", bgcc::IDSTR, 9);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeString(proxyname_old);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 10);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeInt64(handle);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("flag", bgcc::IDINT32, 11);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeInt32(flag);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldStop();

    if (ret < 0) {
        return ret;
    }

    return proto->writeStructEnd();
}
apapi_ReLoadConfig_args::apapi_ReLoadConfig_args() {
}

apapi_ReLoadConfig_args::~apapi_ReLoadConfig_args() {
}

bool apapi_ReLoadConfig_args::operator==(const apapi_ReLoadConfig_args& rhs) const {
    if (this == &rhs) {
        return true;
    }

    return true;
}

bool apapi_ReLoadConfig_args::operator!=(const apapi_ReLoadConfig_args& rhs) const {
    return !(*this == rhs);
}

bool apapi_ReLoadConfig_args::operator< (const apapi_ReLoadConfig_args& rhs) const {
    if (this == &rhs) {
        return false;
    }

    return true;
}

int32_t apapi_ReLoadConfig_args::read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request,
                                      int32_t request_len) {
    int32_t ret = 0;
    std::string fname;
    int32_t nread = 0;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(request + nread, request_len - nread, fname);

    if (ret < 0) {
        return ret;
    }

    nread += ret;

    while (true) {
        ret = proto->readFieldBegin(request + nread, request_len - nread, fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        nread += ret;

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        default:
            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    ret = proto->readStructEnd();

    if (ret < 0) {
        return ret;
    }

    return nread;
}

apapi_GetAgents_args::apapi_GetAgents_args() {
}

apapi_GetAgents_args::~apapi_GetAgents_args() {
}

bool apapi_GetAgents_args::operator==(const apapi_GetAgents_args& rhs) const {
    if (this == &rhs) {
        return true;
    }

    return true;
}

bool apapi_GetAgents_args::operator!=(const apapi_GetAgents_args& rhs) const {
    return !(*this == rhs);
}

bool apapi_GetAgents_args::operator< (const apapi_GetAgents_args& rhs) const {
    if (this == &rhs) {
        return false;
    }

    return true;
}

int32_t apapi_GetAgents_args::read(bgcc::SharedPointer<bgcc::IProtocol> proto, char* request,
                                   int32_t request_len) {
    int32_t ret = 0;
    std::string fname;
    int32_t nread = 0;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(request + nread, request_len - nread, fname);

    if (ret < 0) {
        return ret;
    }

    nread += ret;

    while (true) {
        ret = proto->readFieldBegin(request + nread, request_len - nread, fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        nread += ret;

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        default:
            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    ret = proto->readStructEnd();

    if (ret < 0) {
        return ret;
    }

    return nread;
}

apapi_ReLoadConfig_pargs::~apapi_ReLoadConfig_pargs() {
}

int32_t apapi_ReLoadConfig_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    ret = proto->writeStructBegin("apapi_ReLoadConfig_pargs");

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldStop();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeStructEnd();

    if (ret < 0) {
        return ret;
    }

    return ret;
};

apapi_GetAgents_pargs::~apapi_GetAgents_pargs() {
}

int32_t apapi_GetAgents_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    ret = proto->writeStructBegin("apapi_GetAgents_pargs");

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldStop();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeStructEnd();

    if (ret < 0) {
        return ret;
    }

    return ret;
};

apapi_ReLoadConfig_result::apapi_ReLoadConfig_result() {
}

apapi_ReLoadConfig_result::~apapi_ReLoadConfig_result() {
}

bool apapi_ReLoadConfig_result::operator==(const apapi_ReLoadConfig_result& rhs) const {
    if (this == &rhs) {
        return true;
    }

    if (return_value != rhs.return_value) {
        return false;
    }

    return true;
}

bool apapi_ReLoadConfig_result::operator!=(const apapi_ReLoadConfig_result& rhs) const {
    return !(*this == rhs);
}

bool apapi_ReLoadConfig_result::operator< (const apapi_ReLoadConfig_result& rhs) const {
    if (this == &rhs) {
        return false;
    }

    if (!(return_value < rhs.return_value)) {
        return false;
    }

    return true;
}

int32_t apapi_ReLoadConfig_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    ret = proto->writeStructBegin("apapi_ReLoadConfig_result");

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("return_value", bgcc::IDBOOL, 0);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeBool(return_value);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldStop();

    if (ret < 0) {
        return ret;
    }

    return proto->writeStructEnd();
}

apapi_GetAgents_result::apapi_GetAgents_result() {
}

apapi_GetAgents_result::~apapi_GetAgents_result() {
}

bool apapi_GetAgents_result::operator==(const apapi_GetAgents_result& rhs) const {
    if (this == &rhs) {
        return true;
    }

    if (return_value != rhs.return_value) {
        return false;
    }

    if (agentInfoList != rhs.agentInfoList) {
        return false;
    }

    return true;
}

bool apapi_GetAgents_result::operator!=(const apapi_GetAgents_result& rhs) const {
    return !(*this == rhs);
}

bool apapi_GetAgents_result::operator< (const apapi_GetAgents_result& rhs) const {
    if (this == &rhs) {
        return false;
    }

    if (!(return_value < rhs.return_value)) {
        return false;
    }

    if (!(agentInfoList < rhs.agentInfoList)) {
        return false;
    }

    return true;
}

int32_t apapi_GetAgents_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    ret = proto->writeStructBegin("apapi_GetAgents_result");

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("return_value", bgcc::IDBOOL, 0);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeBool(return_value);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldBegin("agentInfoList", bgcc::IDLIST, 1);

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeListBegin(bgcc::IDSTRUCT, agentInfoList.size());

    if (ret < 0) {
        return ret;
    }

    std::vector<ApAgentInfo> ::const_iterator citr_var117;

    for (citr_var117 = agentInfoList.begin(); citr_var117 != agentInfoList.end(); ++citr_var117) {
        ret = (*citr_var117).write(proto);

        if (ret < 0) {
            return ret;
        }
    }

    ret = proto->writeListEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldEnd();

    if (ret < 0) {
        return ret;
    }

    ret = proto->writeFieldStop();

    if (ret < 0) {
        return ret;
    }

    return proto->writeStructEnd();
}

apapi_ReLoadConfig_presult::~apapi_ReLoadConfig_presult() {
}

int32_t apapi_ReLoadConfig_presult::read(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    std::string fname;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(fname);

    if (ret < 0) {
        return ret;
    }

    while (true) {
        ret = proto->readFieldBegin(fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        case 0:
            ret = proto->readBool((*(return_value)));

            if (ret < 0) {
                return ret;
            }

            break;

        default:
            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    return proto->readStructEnd();
}

apapi_GetAgents_presult::~apapi_GetAgents_presult() {
}

int32_t apapi_GetAgents_presult::read(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
    int32_t ret = 0;
    std::string fname;
    bgcc::DataTypeID ftype;
    bgcc::FieldIDType fid;

    ret = proto->readStructBegin(fname);

    if (ret < 0) {
        return ret;
    }

    while (true) {
        ret = proto->readFieldBegin(fname, ftype, fid);

        if (ret < 0) {
            return ret;
        }

        if (ftype == bgcc::IDSTOP) {
            break;
        }

        switch (fid) {
        case 0:
            ret = proto->readBool((*(return_value)));

            if (ret < 0) {
                return ret;
            }

            break;

        case 1:
            (*(agentInfoList)).clear();

            int32_t size_var118;
            bgcc::DataTypeID etype_var119;

            ret = proto->readListBegin(etype_var119, size_var118);

            if (ret < 0) {
                return ret;
            }

            (*(agentInfoList)).reserve(size_var118);

            for (int32_t i = 0; i < size_var118; ++i) {
                ApAgentInfo value_var120;
                ret = value_var120.read(proto);

                if (ret < 0) {
                    return ret;
                }

                (*(agentInfoList)).push_back(value_var120);
            }

            ret = proto->readListEnd();

            if (ret < 0) {
                return ret;
            }

            break;

        default:
            break;
        }

        ret = proto->readFieldEnd();

        if (ret < 0) {
            return ret;
        }
    }

    return proto->readStructEnd();
}

apapiProxy::apapiProxy(
    bgcc::ServerInfo serverinfo,
    int32_t nprotocols,
    bgcc::ServiceManager* mgr,
    int32_t tryCount,
    int32_t tryInterval) :
    bgcc::BaseProxy(serverinfo, nprotocols, true, mgr, tryCount, tryInterval),
    _use_existing_socket(false) {
    _whoami = "global.ap.apapi";
}

apapiProxy::apapiProxy(
    bgcc::ServerInfo serverinfo,
    bgcc::ServiceManager* mgr,
    int32_t tryCount,
    int32_t tryInterval) :
    bgcc::BaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval),
    _use_existing_socket(false) {
    _whoami = "global.ap.apapi";
}

apapiProxy::apapiProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
    bgcc::BaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval),
    _proxy_name(proxy_name), _use_existing_socket(true) {
    _whoami = "global.ap.apapi";
}

bool apapiProxy::ReLoadConfig(bool last) {
    bool return_value;
    int32_t __seqid = 0;
    int tryCount = 0;
    bgcc::SharedPointer<bgcc::BinaryProtocol> prot;
    bgcc::SharedPointer<bgcc::BinaryProtocol> prottmp;
    bgcc::SharedPointer<bgcc::ClientSocket> client;
    bgcc::SharedPointer<bgcc::ServerPeerSocket> sock;
    _isclosed = false;
    bool hasCreateConn = false;

    if (!_hasinit) {
        bgcc::Guard <bgcc::Mutex> guard(&_initMutex);

        if (!_hasinit) {
            _hasinit = true;

            if (_service_manager) {
                struct bgcc::callback_thread_arg_t* arg = new bgcc::callback_thread_arg_t;
                arg->proxy_name = get_name();
                arg->server_ip = _serverinfo.getIP();
                arg->server_port = _serverinfo.getPort();
                arg->service_manager = _service_manager;

                _callback_thread = bgcc::SharedPointer<bgcc::Thread>(
                                       new bgcc::Thread(bgcc::call_back_thread_func, arg));

                if (_callback_thread.is_valid()) {
                    _callback_thread->start();
                }
            }

            if (!_use_existing_socket) {
                while (tryCount++ <= _tryCount) {
                    client = bgcc::SharedPointer<bgcc::ClientSocket>(
                                 new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

                    if (client.is_valid()) {
                        client->open();
                        prot = bgcc::SharedPointer<bgcc::BinaryProtocol>(new bgcc::BinaryProtocol(client));
                        break;
                    } else {
                        continue;
                    }
                }

                if (tryCount > _tryCount + 1) {
                    set_errno(bgcc::E_BGCC_OUT_MAX_TRY_COUNT);
                    return return_value;
                    ;
                }

                //if create a new connection, donot try again;
                hasCreateConn = true;
                tryCount = _tryCount;
            }
        } //if(!_hasinit)
    } //if(!_hasinit)

RECON:

    if (tryCount++ > _tryCount) {
        set_errno(bgcc::E_BGCC_OUT_MAX_TRY_COUNT);
        return return_value;
    }

    if (tryCount > 1) {
        bgcc::TimeUtil::safe_sleep_ms(_tryInterval);
    }

    if (_use_existing_socket) {
        sock = bgcc::ConnectionManager::get_instance()->get_connection(_proxy_name);

        if (sock.is_valid()) {
            prot = bgcc::SharedPointer<bgcc::BinaryProtocol>(new bgcc::BinaryProtocol(sock));
        } else {
            goto RECON;
        }
    } else if (!hasCreateConn) {
        if (0 != _protocols.get(prot, 10)) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }

            goto RECON;
        }
    }

    __get_ticket_id("ReLoadConfig", __seqid, last, prot, prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    if (last) {
        __seqid *= -1;
    }

    send_ReLoadConfig(__seqid, prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    return_value = recv_ReLoadConfig(prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    if (!_use_existing_socket) {
        if (!_isclosed) {
            if (0 != _protocols.put(prot)) {
                set_errno(-1);
                return return_value;
            }
        }
    } else {
        bgcc::ConnectionManager::get_instance()->enroll(_proxy_name, sock->get_socket());
    }

    return return_value;
}

void apapiProxy::send_ReLoadConfig(int32_t seqid, bgcc::SharedPointer<bgcc::IProtocol> proto) {
    int32_t ret_code = 0;

    ret_code = proto->writeMessageBegin(_whoami.c_str(), "ReLoadConfig", bgcc::CALL, seqid);

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    ret_code = proto->writeString(get_name());

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    apapi_ReLoadConfig_pargs pargs;
    ret_code = pargs.write(proto);

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    proto->writeMessageEnd();

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }
}

bool apapiProxy::recv_ReLoadConfig(bgcc::SharedPointer<bgcc::IProtocol> proto) {
    bool ret_val = false;
    int32_t ret_code = 0;
    std::string fname;
    bgcc::MsgTypeID  msg_type;
    int32_t msg_seqid;

    apapi_ReLoadConfig_presult presult;
    ret_code = proto->readMessageBegin(fname, msg_type, msg_seqid);

    if (ret_code < 0) {
        goto end;
    }

    if (msg_type == ::bgcc::EXCEPTION) {
        int32_t remote_code = 0;
        ret_code = proto->readInt32(remote_code);

        if (ret_code == 0) {
            ret_code = remote_code;
        }

        goto end;
    }

    if (msg_type != ::bgcc::REPLY) {
        ret_code = proto->skip(bgcc::IDSTRUCT);

        if (ret_code < 0) {
            goto end;
        }

        ret_code = proto->readMessageEnd();

        if (ret_code < 0) {
            goto end;
        }
    }

    if (fname != "ReLoadConfig") {
        ret_code = proto->skip(bgcc::IDSTRUCT);

        if (ret_code < 0) {
            goto end;
        }

        ret_code = proto->readMessageEnd();

        if (ret_code < 0) {
            goto end;
        }
    }

    presult.return_value = &ret_val;
    ret_code = presult.read(proto);

    if (ret_code < 0) {
        goto end;
    }

    ret_code = proto->readMessageEnd();

    if (ret_code < 0) {
        goto end;
    }

end:
    set_errno(ret_code);
    return ret_val;
}

bool apapiProxy::GetAgents(ApAgentInfoListT& agentInfoList, bool last) {
    bool return_value;
    int32_t __seqid = 0;
    int tryCount = 0;
    bgcc::SharedPointer<bgcc::BinaryProtocol> prot;
    bgcc::SharedPointer<bgcc::BinaryProtocol> prottmp;
    bgcc::SharedPointer<bgcc::ClientSocket> client;
    bgcc::SharedPointer<bgcc::ServerPeerSocket> sock;
    _isclosed = false;
    bool hasCreateConn = false;

    if (!_hasinit) {
        bgcc::Guard <bgcc::Mutex> guard(&_initMutex);

        if (!_hasinit) {
            _hasinit = true;

            if (_service_manager) {
                struct bgcc::callback_thread_arg_t* arg = new bgcc::callback_thread_arg_t;
                arg->proxy_name = get_name();
                arg->server_ip = _serverinfo.getIP();
                arg->server_port = _serverinfo.getPort();
                arg->service_manager = _service_manager;

                _callback_thread = bgcc::SharedPointer<bgcc::Thread>(
                                       new bgcc::Thread(bgcc::call_back_thread_func, arg));

                if (_callback_thread.is_valid()) {
                    _callback_thread->start();
                }
            }

            if (!_use_existing_socket) {
                while (tryCount++ <= _tryCount) {
                    client = bgcc::SharedPointer<bgcc::ClientSocket>(
                                 new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

                    if (client.is_valid()) {
                        client->open();
                        prot = bgcc::SharedPointer<bgcc::BinaryProtocol>(new bgcc::BinaryProtocol(client));
                        break;
                    } else {
                        continue;
                    }
                }

                if (tryCount > _tryCount + 1) {
                    set_errno(bgcc::E_BGCC_OUT_MAX_TRY_COUNT);
                    return return_value;
                    ;
                }

                //if create a new connection, donot try again;
                hasCreateConn = true;
                tryCount = _tryCount;
            }
        } //if(!_hasinit)
    } //if(!_hasinit)

RECON:

    if (tryCount++ > _tryCount) {
        set_errno(bgcc::E_BGCC_OUT_MAX_TRY_COUNT);
        return return_value;
    }

    if (tryCount > 1) {
        bgcc::TimeUtil::safe_sleep_ms(_tryInterval);
    }

    if (_use_existing_socket) {
        sock = bgcc::ConnectionManager::get_instance()->get_connection(_proxy_name);

        if (sock.is_valid()) {
            prot = bgcc::SharedPointer<bgcc::BinaryProtocol>(new bgcc::BinaryProtocol(sock));
        } else {
            goto RECON;
        }
    } else if (!hasCreateConn) {
        if (0 != _protocols.get(prot, 10)) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }

            goto RECON;
        }
    }

    __get_ticket_id("GetAgents", __seqid, last, prot, prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    if (last) {
        __seqid *= -1;
    }

    send_GetAgents(__seqid, prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    return_value = recv_GetAgents(agentInfoList, prot);

    if (get_errno() < 0) {
        if (!_use_existing_socket) {
            client = bgcc::SharedPointer<bgcc::ClientSocket>(
                         new bgcc::ClientSocket(_serverinfo.getIP(), _serverinfo.getPort()));

            if (client.is_valid()) {
                client->open();
            }

            prottmp = bgcc::SharedPointer<bgcc::BinaryProtocol>(
                          new bgcc::BinaryProtocol(client));

            if (!_isclosed) {
                _protocols.put(prottmp);
            }
        } else {
#ifndef _WIN32
            ::close(sock->get_socket());
#endif
        }

        goto RECON;
    }

    if (!_use_existing_socket) {
        if (!_isclosed) {
            if (0 != _protocols.put(prot)) {
                set_errno(-1);
                return return_value;
            }
        }
    } else {
        bgcc::ConnectionManager::get_instance()->enroll(_proxy_name, sock->get_socket());
    }

    return return_value;
}

void apapiProxy::send_GetAgents(int32_t seqid, bgcc::SharedPointer<bgcc::IProtocol> proto) {
    int32_t ret_code = 0;

    ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgents", bgcc::CALL, seqid);

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    ret_code = proto->writeString(get_name());

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    apapi_GetAgents_pargs pargs;
    ret_code = pargs.write(proto);

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }

    proto->writeMessageEnd();

    if (ret_code < 0) {
        set_errno(ret_code);
        return;
    }
}

bool apapiProxy::recv_GetAgents(ApAgentInfoListT& agentInfoList,
                                bgcc::SharedPointer<bgcc::IProtocol> proto) {
    bool ret_val = false;
    int32_t ret_code = 0;
    std::string fname;
    bgcc::MsgTypeID  msg_type;
    int32_t msg_seqid;

    apapi_GetAgents_presult presult;
    ret_code = proto->readMessageBegin(fname, msg_type, msg_seqid);

    if (ret_code < 0) {
        goto end;
    }

    if (msg_type == ::bgcc::EXCEPTION) {
        int32_t remote_code = 0;
        ret_code = proto->readInt32(remote_code);

        if (ret_code == 0) {
            ret_code = remote_code;
        }

        goto end;
    }

    if (msg_type != ::bgcc::REPLY) {
        ret_code = proto->skip(bgcc::IDSTRUCT);

        if (ret_code < 0) {
            goto end;
        }

        ret_code = proto->readMessageEnd();

        if (ret_code < 0) {
            goto end;
        }
    }

    if (fname != "GetAgents") {
        ret_code = proto->skip(bgcc::IDSTRUCT);

        if (ret_code < 0) {
            goto end;
        }

        ret_code = proto->readMessageEnd();

        if (ret_code < 0) {
            goto end;
        }
    }

    presult.return_value = &ret_val;
    presult.agentInfoList = &agentInfoList;
    ret_code = presult.read(proto);

    if (ret_code < 0) {
        goto end;
    }

    ret_code = proto->readMessageEnd();

    if (ret_code < 0) {
        goto end;
    }

end:
    set_errno(ret_code);
    return ret_val;
}

apapiProcessor::apapiProcessor(bgcc::SharedPointer<apapi> intf) :
    bgcc::BaseProcessor(), __intf(intf) {
    __fun_map["ReLoadConfig"] = &apapiProcessor::do_ReLoadConfig;
    __fun_map["GetAgents"] = &apapiProcessor::do_GetAgents;
}

int32_t apapiProcessor::process(char* request, int32_t request_len,
                                bgcc::SharedPointer<bgcc::IProtocol> proto) {
    int32_t ret = 0;
    bgcc::MsgTypeID mtype;
    int32_t seqid;
    std::string fname;
    int32_t nread = 0;
    ret = proto->readMessageBegin(request, request_len, fname, mtype, seqid);

    if (ret < 0) {
        return ret;
    }

    nread += ret;

    if (mtype != ::bgcc::CALL) {
        return -1;
    }

    return do_function__(request + nread, request_len - nread, proto, fname, seqid);
}

std::string apapiProcessor::get_name() const {
    return "global.ap.apapi";
}

int32_t apapiProcessor::do_function__(char* request, int32_t request_len,
                                      bgcc::SharedPointer<bgcc::IProtocol> proto,
                                      const std::string& fname, int32_t seqid) {
    int32_t ret = 0;
    std::map<std::string, do_function_ptr>::iterator it;
    it = __fun_map.find(fname);

    if (it == __fun_map.end()) {
        return bgcc::BaseProcessor::do_function__(request, request_len, proto , fname, seqid);
    }

    if (seqid < 0) {
        seqid *= -1;
        void* rdata = NULL;
        int32_t rsize = 0;
        bgcc::Transaction* SharedPtr = bgcc::Transaction::get_instance();
        int32_t ret_code = SharedPtr->retrieveDataCopyByTicketId(seqid, &rdata, rsize);

        if (0 == ret_code) {
            ret = proto->getTransport()->write((void*)rdata, rsize);
            free(rdata);

            if (ret != 0) {
                ret = proto->writeMessageBegin("global.ap.apapi", fname, ::bgcc::EXCEPTION, seqid);

                if (ret < 0) {
                    return ret;
                }

                ret = proto->writeInt32(0);

                if (ret < 0) {
                    return ret;
                }

                ret = proto->writeMessageEnd();
            }

            return ret;
        }
    }

    return (this->*(it->second))(request, request_len, proto, seqid);
}

int32_t apapiProcessor::do_ReLoadConfig(char* request, int32_t request_len,
                                        bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
    int32_t ret = 0;
    std::map<std::string, std::string> map;

    int32_t proxy_name_len = (int32_t)ntohl(*(uint32_t*)request);
    std::string proxy_name(request + 4, proxy_name_len);
    request += 4 + proxy_name_len;
    request_len -= (proxy_name_len + 4);
    typedef bgcc::SharedPointer<bgcc::ITransport> ITransSharedPointer;

    ITransSharedPointer ITransptr = proto->getTransport();
    bgcc::ServerPeerSocket* pServer = dynamic_cast<bgcc::ServerPeerSocket*>(ITransptr.get());

    if (pServer) {
        typedef bgcc::SharedPointer<bgcc::PeerInfo> PeerInfoSharedPointer;
        PeerInfoSharedPointer peerptr = pServer->GetPeerInfo();
        map["PeerIP"] =  peerptr->GetHost();
        std::string strPort;
        std::stringstream stream;
        stream << peerptr->GetPort();
        stream >> strPort;
        map["PeerPort"] = strPort;
    }

    map["ProxyName"] = proxy_name;

    apapi_ReLoadConfig_args args;
    ret = args.read(proto, request, request_len);

    if (ret < 0) {
        return ret;
    }

    request += ret;
    request_len -= ret;

    ret = proto->readMessageEnd(request, request_len);

    if (ret < 0) {
        return ret;
    }

    apapi_ReLoadConfig_result result;
    result.return_value = __intf->ReLoadConfig(map);
    ret = proto->writeMessageBegin("global.ap.apapi", "ReLoadConfig", ::bgcc::REPLY, seqid);

    if (ret < 0) {
        return ret;
    }

    ret = result.write(proto);

    if (ret < 0) {
        return ret;
    }

    bgcc::BinaryProtocol* protoptr = (bgcc::BinaryProtocol*)proto.get();
    void* p;
    int32_t size;
    int32_t retcode = protoptr->getDataCopy(&p, size);

    if (retcode == 0) {
        int32_t body_size;
        body_size = (int32_t)htonl(size - 20);
        memcpy((uint8_t*)p + 16, &body_size, 4);
        bgcc::Transaction::get_instance()->saveDataByTicketId(seqid, p, size);
        free(p);
    }

    ret = proto->writeMessageEnd();
    return ret;
}

int32_t apapiProcessor::do_GetAgents(char* request, int32_t request_len,
                                     bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
    int32_t ret = 0;
    std::map<std::string, std::string> map;

    int32_t proxy_name_len = (int32_t)ntohl(*(uint32_t*)request);
    std::string proxy_name(request + 4, proxy_name_len);
    request += 4 + proxy_name_len;
    request_len -= (proxy_name_len + 4);
    typedef bgcc::SharedPointer<bgcc::ITransport> ITransSharedPointer;

    ITransSharedPointer ITransptr = proto->getTransport();
    bgcc::ServerPeerSocket* pServer = dynamic_cast<bgcc::ServerPeerSocket*>(ITransptr.get());

    if (pServer) {
        typedef bgcc::SharedPointer<bgcc::PeerInfo> PeerInfoSharedPointer;
        PeerInfoSharedPointer peerptr = pServer->GetPeerInfo();
        map["PeerIP"] =  peerptr->GetHost();
        std::string strPort;
        std::stringstream stream;
        stream << peerptr->GetPort();
        stream >> strPort;
        map["PeerPort"] = strPort;
    }

    map["ProxyName"] = proxy_name;

    apapi_GetAgents_args args;
    ret = args.read(proto, request, request_len);

    if (ret < 0) {
        return ret;
    }

    request += ret;
    request_len -= ret;

    ret = proto->readMessageEnd(request, request_len);

    if (ret < 0) {
        return ret;
    }

    apapi_GetAgents_result result;
    result.return_value = __intf->GetAgents(result.agentInfoList, map);
    ret = proto->writeMessageBegin("global.ap.apapi", "GetAgents", ::bgcc::REPLY, seqid);

    if (ret < 0) {
        return ret;
    }

    ret = result.write(proto);

    if (ret < 0) {
        return ret;
    }

    bgcc::BinaryProtocol* protoptr = (bgcc::BinaryProtocol*)proto.get();
    void* p;
    int32_t size;
    int32_t retcode = protoptr->getDataCopy(&p, size);

    if (retcode == 0) {
        int32_t body_size;
        body_size = (int32_t)htonl(size - 20);
        memcpy((uint8_t*)p + 16, &body_size, 4);
        bgcc::Transaction::get_instance()->saveDataByTicketId(seqid, p, size);
        free(p);
    }

    ret = proto->writeMessageEnd();
    return ret;
}

}


