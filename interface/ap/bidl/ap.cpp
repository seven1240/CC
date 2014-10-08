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
        }
        else if (rhs.agentId < agentId) {
            return false;
        }

        if (agentDn < rhs.agentDn) {
            return true;
        }
        else if (rhs.agentDn < agentDn) {
            return false;
        }

        if (agentPwd < rhs.agentPwd) {
            return true;
        }
        else if (rhs.agentPwd < agentPwd) {
            return false;
        }

        if (statusChangetype < rhs.statusChangetype) {
            return true;
        }
        else if (rhs.statusChangetype < statusChangetype) {
            return false;
        }

        if (autoAnswer < rhs.autoAnswer) {
            return true;
        }
        else if (rhs.autoAnswer < autoAnswer) {
            return false;
        }

        if (fcSignin < rhs.fcSignin) {
            return true;
        }
        else if (rhs.fcSignin < fcSignin) {
            return false;
        }

        if (skills < rhs.skills) {
            return true;
        }
        else if (rhs.skills < skills) {
            return false;
        }

        if (proxyname < rhs.proxyname) {
            return true;
        }
        else if (rhs.proxyname < proxyname) {
            return false;
        }

        if (proxyname_old < rhs.proxyname_old) {
            return true;
        }
        else if (rhs.proxyname_old < proxyname_old) {
            return false;
        }

        if (handle < rhs.handle) {
            return true;
        }
        else if (rhs.handle < handle) {
            return false;
        }

        if (flag < rhs.flag) {
            return true;
        }
        else if (rhs.flag < flag) {
            return false;
        }

        return false;
    }

    int32_t ApAgentInfo::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
        int32_t ret = 0;
        std::string fname;
        int32_t nread = 0;
        bgcc::DataTypeID ftype;
        bgcc::FieldIDType fid;

        ret = proto->readStructBegin(OFFSET_PTR(request, nread), request_len - nread, fname);
        if (ret < 0) { return ret; }
        nread += ret;

        while(true) {
            ret = proto->readFieldBegin(OFFSET_PTR(request, nread), request_len - nread, fname, ftype, fid);
            if(ret < 0) { return ret; }
            nread += ret;

            if(ftype == bgcc::IDSTOP){
                break;
            }

            switch(fid) {
            case 1:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 2:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentPwd);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                int32_t ele_var1;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var1);
                if (ret < 0) { return ret; }
                nread += ret;
                statusChangetype = ele_var1;
                break;
            case 5:
                ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, autoAnswer);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, fcSignin);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 7:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skills);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, proxyname);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 9:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, proxyname_old);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 10:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 11:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, flag);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            }
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }

        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    int32_t ApAgentInfo::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("ApAgentInfo");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentDn);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentPwd", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentPwd);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("statusChangetype", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(statusChangetype.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("autoAnswer", bgcc::IDBOOL, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeBool(autoAnswer);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("fcSignin", bgcc::IDBOOL, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeBool(fcSignin);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skills", bgcc::IDSTR, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeString(skills);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("proxyname", bgcc::IDSTR, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeString(proxyname);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("proxyname_old", bgcc::IDSTR, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeString(proxyname_old);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 10);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(handle);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("flag", bgcc::IDINT32, 11);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(flag);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

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

    int32_t apapi_ReLoadConfig_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
        int32_t ret = 0; 
        std::string fname;
        int32_t nread = 0;
        bgcc::DataTypeID ftype;
        bgcc::FieldIDType fid; 

        ret = proto->readStructBegin(OFFSET_PTR(request, nread), request_len - nread, fname);
        if (ret < 0) { return ret; }
        nread += ret;

        while (true) {
            ret = proto->readFieldBegin(OFFSET_PTR(request, nread), request_len - nread, fname, ftype, fid);
            if (ret < 0) { return ret; }
            nread += ret;

            if (ftype == bgcc::IDSTOP) {
                break;
            }

            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
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

    int32_t apapi_GetAgents_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
        int32_t ret = 0; 
        std::string fname;
        int32_t nread = 0;
        bgcc::DataTypeID ftype;
        bgcc::FieldIDType fid; 

        ret = proto->readStructBegin(OFFSET_PTR(request, nread), request_len - nread, fname);
        if (ret < 0) { return ret; }
        nread += ret;

        while (true) {
            ret = proto->readFieldBegin(OFFSET_PTR(request, nread), request_len - nread, fname, ftype, fid);
            if (ret < 0) { return ret; }
            nread += ret;

            if (ftype == bgcc::IDSTOP) {
                break;
            }

            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    apapi_ReLoadConfig_pargs::~apapi_ReLoadConfig_pargs() {
    }

    int32_t apapi_ReLoadConfig_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("apapi_ReLoadConfig_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    apapi_GetAgents_pargs::~apapi_GetAgents_pargs() {
    }

    int32_t apapi_GetAgents_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("apapi_GetAgents_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
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
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDBOOL, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeBool(return_value);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

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
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDBOOL, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeBool(return_value);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfoList", bgcc::IDLIST, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, agentInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<ApAgentInfo> ::const_iterator citr_var2;
        for (citr_var2 = agentInfoList.begin(); citr_var2 != agentInfoList.end(); ++citr_var2) {
            ret = (*citr_var2).write(proto);
            if (ret < 0) { return ret; }
        }
        ret = proto->writeListEnd();
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    apapi_ReLoadConfig_presult::~apapi_ReLoadConfig_presult() {
    }

    int32_t apapi_ReLoadConfig_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret=0;
        int32_t nread=0;
        std::string fname;
        bgcc::DataTypeID ftype;
        bgcc::FieldIDType fid; 

        ret = proto->readStructBegin(OFFSET_PTR(request, nread), request_len - nread, fname);
        if (ret < 0) { return ret; }
        nread+=ret;

        while(true) {
            ret = proto->readFieldBegin(OFFSET_PTR(request, nread), request_len - nread, fname, ftype, fid);
            if (ret < 0) { return ret; }
            nread+=ret;

            if (ftype == bgcc::IDSTOP) {
                break;
            }
            switch(fid) {
            case 0:
                ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, (*(return_value)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            default:
                break;
            }

            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    apapi_GetAgents_presult::~apapi_GetAgents_presult() {
    }

    int32_t apapi_GetAgents_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret=0;
        int32_t nread=0;
        std::string fname;
        bgcc::DataTypeID ftype;
        bgcc::FieldIDType fid; 

        ret = proto->readStructBegin(OFFSET_PTR(request, nread), request_len - nread, fname);
        if (ret < 0) { return ret; }
        nread+=ret;

        while(true) {
            ret = proto->readFieldBegin(OFFSET_PTR(request, nread), request_len - nread, fname, ftype, fid);
            if (ret < 0) { return ret; }
            nread+=ret;

            if (ftype == bgcc::IDSTOP) {
                break;
            }
            switch(fid) {
            case 0:
                ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, (*(return_value)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 1:
                (*(agentInfoList)).clear();

                int32_t size_var3;
                bgcc::DataTypeID etype_var4;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var4, size_var3);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(agentInfoList)).reserve(size_var3);
                for(int32_t i = 0; i < size_var3; ++i) {
                    ApAgentInfo value_var5;
                    ret = value_var5.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(agentInfoList)).push_back(value_var5);
                }

                ret = proto->readListEnd();
                if (ret < 0) { return ret; }
                break;
            default:
                break;
            }

            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    apapiProxy::apapiProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
    }

    apapiProxy::apapiProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
    }

    apapiProxy::apapiProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::BaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    bool apapiProxy::ReLoadConfig(bool /*last*/) {
        bool return_value = false;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ReLoadConfig(_seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ReLoadConfig(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void apapiProxy::send_ReLoadConfig(int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ReLoadConfig", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        apapi_ReLoadConfig_pargs pargs;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    bool apapiProxy::recv_ReLoadConfig(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bool ret_val = false;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        apapi_ReLoadConfig_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ReLoadConfig"){
            presult.return_value = &ret_val;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    bool apapiProxy::GetAgents(ApAgentInfoListT& agentInfoList, bool /*last*/) {
        bool return_value = false;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgents(_seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgents(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void apapiProxy::send_GetAgents(int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgents", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        apapi_GetAgents_pargs pargs;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    bool apapiProxy::recv_GetAgents(ApAgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bool ret_val = false;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        apapi_GetAgents_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgents"){
            presult.return_value = &ret_val;
            presult.agentInfoList = &agentInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    SSLapapiProxy::SSLapapiProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
    }

    SSLapapiProxy::SSLapapiProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
    }

    SSLapapiProxy::SSLapapiProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::SSLBaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.ap.apapi";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    bool SSLapapiProxy::ReLoadConfig(bool /*last*/) {
        bool return_value = false;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ReLoadConfig(_seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ReLoadConfig(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLapapiProxy::send_ReLoadConfig(int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ReLoadConfig", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        apapi_ReLoadConfig_pargs pargs;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    bool SSLapapiProxy::recv_ReLoadConfig(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bool ret_val = false;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        apapi_ReLoadConfig_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ReLoadConfig"){
            presult.return_value = &ret_val;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    bool SSLapapiProxy::GetAgents(ApAgentInfoListT& agentInfoList, bool /*last*/) {
        bool return_value = false;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgents(_seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgents(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLapapiProxy::send_GetAgents(int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgents", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        apapi_GetAgents_pargs pargs;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    bool SSLapapiProxy::recv_GetAgents(ApAgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bool ret_val = false;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        apapi_GetAgents_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgents"){
            presult.return_value = &ret_val;
            presult.agentInfoList = &agentInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    apapiProcessor::apapiProcessor(bgcc::SharedPointer<apapi> intf) :
        bgcc::BaseProcessor(), __intf(intf) {
        __fun_map["ReLoadConfig"] = &apapiProcessor::do_ReLoadConfig;
        __fun_map["GetAgents"] = &apapiProcessor::do_GetAgents;
    }

    int32_t apapiProcessor::process(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
        int32_t ret = 0;
        bgcc::MsgTypeID mtype;
        int32_t seqid;
        std::string fname;
        int32_t nread = 0;
        ret = proto->readMessageBegin(&request, request_len, fname, mtype, seqid);
        if (ret < 0) { return ret;}
        nread += ret;
        if (mtype != ::bgcc::CALL){
            return -1;
        }
        return do_function__(OFFSET_PTR(request, nread), request_len-nread, proto, fname, seqid);
    }

    std::string apapiProcessor::get_name() const {
        return "global.ap.apapi";
    }

    int32_t apapiProcessor::do_function__(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, 
        const std::string& fname, int32_t seqid) {
        std::map<std::string, do_function_ptr>::iterator it;
        it = __fun_map.find(fname);
        if (it == __fun_map.end()) {
            return bgcc::BaseProcessor::do_function__(request, request_len, proto, fname, seqid);
        }

        return (this->*(it->second))(request, request_len, proto, seqid);
    }

    int32_t apapiProcessor::do_ReLoadConfig(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
        int32_t ret = 0;
        std::map<std::string, std::string> map;

        int32_t proxy_name_len = INT32(request);
        std::string proxy_name(OFFSET_PTR(request, LENGTH_SIZE), proxy_name_len);
        request+=(LENGTH_SIZE+proxy_name_len);
        request_len-=(proxy_name_len+LENGTH_SIZE);
        typedef bgcc::SharedPointer<bgcc::ITransport> ITransSharedPointer;

        ITransSharedPointer ITransptr= proto->getTransport();
        bgcc::ServerPeerSocket* pServer = dynamic_cast<bgcc::ServerPeerSocket*>(ITransptr.get());
        if (pServer) {
            typedef bgcc::SharedPointer<bgcc::PeerInfo> PeerInfoSharedPointer;
            PeerInfoSharedPointer peerptr = pServer->GetPeerInfo();
            map[PEER_IP] =  peerptr->GetHost();
            std::string strPort;
            std::stringstream stream;
            stream<<peerptr->GetPort();
            stream>>strPort;
            map[PEER_PORT]= strPort;
        }
        map[PROXY_NAME] = proxy_name;

        apapi_ReLoadConfig_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        apapi_ReLoadConfig_result result;
        result.return_value = __intf->ReLoadConfig(map);
        ret = proto->writeMessageBegin("global.ap.apapi", "ReLoadConfig", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t apapiProcessor::do_GetAgents(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
        int32_t ret = 0;
        std::map<std::string, std::string> map;

        int32_t proxy_name_len = INT32(request);
        std::string proxy_name(OFFSET_PTR(request, LENGTH_SIZE), proxy_name_len);
        request+=(LENGTH_SIZE+proxy_name_len);
        request_len-=(proxy_name_len+LENGTH_SIZE);
        typedef bgcc::SharedPointer<bgcc::ITransport> ITransSharedPointer;

        ITransSharedPointer ITransptr= proto->getTransport();
        bgcc::ServerPeerSocket* pServer = dynamic_cast<bgcc::ServerPeerSocket*>(ITransptr.get());
        if (pServer) {
            typedef bgcc::SharedPointer<bgcc::PeerInfo> PeerInfoSharedPointer;
            PeerInfoSharedPointer peerptr = pServer->GetPeerInfo();
            map[PEER_IP] =  peerptr->GetHost();
            std::string strPort;
            std::stringstream stream;
            stream<<peerptr->GetPort();
            stream>>strPort;
            map[PEER_PORT]= strPort;
        }
        map[PROXY_NAME] = proxy_name;

        apapi_GetAgents_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        apapi_GetAgents_result result;
        result.return_value = __intf->GetAgents(result.agentInfoList, map);
        ret = proto->writeMessageBegin("global.ap.apapi", "GetAgents", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

}


