#include "acdcallback.h"

namespace acd {
    acdcallback_SendAgentEvent_args::acdcallback_SendAgentEvent_args() {
    }

    acdcallback_SendAgentEvent_args::~acdcallback_SendAgentEvent_args() {
    }

    bool acdcallback_SendAgentEvent_args::operator==(const acdcallback_SendAgentEvent_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (event != rhs.event) {
            return false;
        }
        return true;
    }

    bool acdcallback_SendAgentEvent_args::operator!=(const acdcallback_SendAgentEvent_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendAgentEvent_args::operator< (const acdcallback_SendAgentEvent_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(event < rhs.event)) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendAgentEvent_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

            switch (fid) {
            case 1:
                {
                    ret = event.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            default:
                break;
            }
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    acdcallback_SendMediaEvent_args::acdcallback_SendMediaEvent_args() {
    }

    acdcallback_SendMediaEvent_args::~acdcallback_SendMediaEvent_args() {
    }

    bool acdcallback_SendMediaEvent_args::operator==(const acdcallback_SendMediaEvent_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (event != rhs.event) {
            return false;
        }
        return true;
    }

    bool acdcallback_SendMediaEvent_args::operator!=(const acdcallback_SendMediaEvent_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendMediaEvent_args::operator< (const acdcallback_SendMediaEvent_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(event < rhs.event)) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendMediaEvent_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

            switch (fid) {
            case 1:
                {
                    ret = event.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            default:
                break;
            }
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    acdcallback_SendQueueEvent_args::acdcallback_SendQueueEvent_args() {
    }

    acdcallback_SendQueueEvent_args::~acdcallback_SendQueueEvent_args() {
    }

    bool acdcallback_SendQueueEvent_args::operator==(const acdcallback_SendQueueEvent_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (event != rhs.event) {
            return false;
        }
        return true;
    }

    bool acdcallback_SendQueueEvent_args::operator!=(const acdcallback_SendQueueEvent_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendQueueEvent_args::operator< (const acdcallback_SendQueueEvent_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(event < rhs.event)) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendQueueEvent_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

            switch (fid) {
            case 1:
                {
                    ret = event.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            default:
                break;
            }
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    acdcallback_SendOtherEvent_args::acdcallback_SendOtherEvent_args() {
    }

    acdcallback_SendOtherEvent_args::~acdcallback_SendOtherEvent_args() {
    }

    bool acdcallback_SendOtherEvent_args::operator==(const acdcallback_SendOtherEvent_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (event != rhs.event) {
            return false;
        }
        return true;
    }

    bool acdcallback_SendOtherEvent_args::operator!=(const acdcallback_SendOtherEvent_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendOtherEvent_args::operator< (const acdcallback_SendOtherEvent_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(event < rhs.event)) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendOtherEvent_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

            switch (fid) {
            case 1:
                {
                    ret = event.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            default:
                break;
            }
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
        }
        ret = proto->readStructEnd();
        if (ret < 0) { return ret; }
        return nread;
    }

    acdcallback_SendAgentEvent_pargs::~acdcallback_SendAgentEvent_pargs() {
    }

    int32_t acdcallback_SendAgentEvent_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendAgentEvent_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("event", bgcc::IDSTRUCT, 1);
        if (ret < 0) { return ret; }
        ret = (*(event)).write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdcallback_SendMediaEvent_pargs::~acdcallback_SendMediaEvent_pargs() {
    }

    int32_t acdcallback_SendMediaEvent_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendMediaEvent_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("event", bgcc::IDSTRUCT, 1);
        if (ret < 0) { return ret; }
        ret = (*(event)).write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdcallback_SendQueueEvent_pargs::~acdcallback_SendQueueEvent_pargs() {
    }

    int32_t acdcallback_SendQueueEvent_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendQueueEvent_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("event", bgcc::IDSTRUCT, 1);
        if (ret < 0) { return ret; }
        ret = (*(event)).write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdcallback_SendOtherEvent_pargs::~acdcallback_SendOtherEvent_pargs() {
    }

    int32_t acdcallback_SendOtherEvent_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendOtherEvent_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("event", bgcc::IDSTRUCT, 1);
        if (ret < 0) { return ret; }
        ret = (*(event)).write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdcallback_SendAgentEvent_result::acdcallback_SendAgentEvent_result() {
    }

    acdcallback_SendAgentEvent_result::~acdcallback_SendAgentEvent_result() {
    }

    bool acdcallback_SendAgentEvent_result::operator==(const acdcallback_SendAgentEvent_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        return true;
    }

    bool acdcallback_SendAgentEvent_result::operator!=(const acdcallback_SendAgentEvent_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendAgentEvent_result::operator< (const acdcallback_SendAgentEvent_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendAgentEvent_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendAgentEvent_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdcallback_SendMediaEvent_result::acdcallback_SendMediaEvent_result() {
    }

    acdcallback_SendMediaEvent_result::~acdcallback_SendMediaEvent_result() {
    }

    bool acdcallback_SendMediaEvent_result::operator==(const acdcallback_SendMediaEvent_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        return true;
    }

    bool acdcallback_SendMediaEvent_result::operator!=(const acdcallback_SendMediaEvent_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendMediaEvent_result::operator< (const acdcallback_SendMediaEvent_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendMediaEvent_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendMediaEvent_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdcallback_SendQueueEvent_result::acdcallback_SendQueueEvent_result() {
    }

    acdcallback_SendQueueEvent_result::~acdcallback_SendQueueEvent_result() {
    }

    bool acdcallback_SendQueueEvent_result::operator==(const acdcallback_SendQueueEvent_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        return true;
    }

    bool acdcallback_SendQueueEvent_result::operator!=(const acdcallback_SendQueueEvent_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendQueueEvent_result::operator< (const acdcallback_SendQueueEvent_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendQueueEvent_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendQueueEvent_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdcallback_SendOtherEvent_result::acdcallback_SendOtherEvent_result() {
    }

    acdcallback_SendOtherEvent_result::~acdcallback_SendOtherEvent_result() {
    }

    bool acdcallback_SendOtherEvent_result::operator==(const acdcallback_SendOtherEvent_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        return true;
    }

    bool acdcallback_SendOtherEvent_result::operator!=(const acdcallback_SendOtherEvent_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdcallback_SendOtherEvent_result::operator< (const acdcallback_SendOtherEvent_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        return true;
    }

    int32_t acdcallback_SendOtherEvent_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdcallback_SendOtherEvent_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdcallback_SendAgentEvent_presult::~acdcallback_SendAgentEvent_presult() {
    }

    int32_t acdcallback_SendAgentEvent_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    acdcallback_SendMediaEvent_presult::~acdcallback_SendMediaEvent_presult() {
    }

    int32_t acdcallback_SendMediaEvent_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    acdcallback_SendQueueEvent_presult::~acdcallback_SendQueueEvent_presult() {
    }

    int32_t acdcallback_SendQueueEvent_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    acdcallback_SendOtherEvent_presult::~acdcallback_SendOtherEvent_presult() {
    }

    int32_t acdcallback_SendOtherEvent_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
            ret = proto->readFieldEnd();
            if (ret < 0) { return ret; }
            nread+=ret; 
        }

        ret=proto->readStructEnd();
        if (ret < 0) { return ret; }
        nread+=ret; 

        return nread;
    }

    acdcallbackProxy::acdcallbackProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
    }

    acdcallbackProxy::acdcallbackProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
    }

    acdcallbackProxy::acdcallbackProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::BaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    void acdcallbackProxy::SendAgentEvent(const AgentEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendAgentEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendAgentEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void acdcallbackProxy::send_SendAgentEvent(const AgentEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendAgentEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendAgentEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void acdcallbackProxy::recv_SendAgentEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendAgentEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendAgentEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void acdcallbackProxy::SendMediaEvent(const MediaEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendMediaEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendMediaEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void acdcallbackProxy::send_SendMediaEvent(const MediaEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendMediaEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendMediaEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void acdcallbackProxy::recv_SendMediaEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendMediaEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendMediaEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void acdcallbackProxy::SendQueueEvent(const RouteEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendQueueEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendQueueEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void acdcallbackProxy::send_SendQueueEvent(const RouteEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendQueueEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendQueueEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void acdcallbackProxy::recv_SendQueueEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendQueueEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendQueueEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void acdcallbackProxy::SendOtherEvent(const OtherEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendOtherEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendOtherEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void acdcallbackProxy::send_SendOtherEvent(const OtherEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendOtherEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendOtherEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void acdcallbackProxy::recv_SendOtherEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendOtherEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendOtherEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    SSLacdcallbackProxy::SSLacdcallbackProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
    }

    SSLacdcallbackProxy::SSLacdcallbackProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
    }

    SSLacdcallbackProxy::SSLacdcallbackProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::SSLBaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.acd.acdcallback";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    void SSLacdcallbackProxy::SendAgentEvent(const AgentEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendAgentEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendAgentEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void SSLacdcallbackProxy::send_SendAgentEvent(const AgentEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendAgentEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendAgentEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void SSLacdcallbackProxy::recv_SendAgentEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendAgentEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendAgentEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void SSLacdcallbackProxy::SendMediaEvent(const MediaEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendMediaEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendMediaEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void SSLacdcallbackProxy::send_SendMediaEvent(const MediaEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendMediaEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendMediaEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void SSLacdcallbackProxy::recv_SendMediaEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendMediaEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendMediaEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void SSLacdcallbackProxy::SendQueueEvent(const RouteEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendQueueEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendQueueEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void SSLacdcallbackProxy::send_SendQueueEvent(const RouteEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendQueueEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendQueueEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void SSLacdcallbackProxy::recv_SendQueueEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendQueueEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendQueueEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    void SSLacdcallbackProxy::SendOtherEvent(const OtherEventT& event, bool /*last*/) {
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendOtherEvent(event, _seqid, conn);
                if(get_errno()==0){
                    recv_SendOtherEvent(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return ;
    }

    void SSLacdcallbackProxy::send_SendOtherEvent(const OtherEventT& event, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendOtherEvent", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdcallback_SendOtherEvent_pargs pargs;
        pargs.event = &event;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    void SSLacdcallbackProxy::recv_SendOtherEvent(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdcallback_SendOtherEvent_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendOtherEvent"){
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return;
    }

    acdcallbackProcessor::acdcallbackProcessor(bgcc::SharedPointer<acdcallback> intf) :
        bgcc::BaseProcessor(), __intf(intf) {
        __fun_map["SendAgentEvent"] = &acdcallbackProcessor::do_SendAgentEvent;
        __fun_map["SendMediaEvent"] = &acdcallbackProcessor::do_SendMediaEvent;
        __fun_map["SendQueueEvent"] = &acdcallbackProcessor::do_SendQueueEvent;
        __fun_map["SendOtherEvent"] = &acdcallbackProcessor::do_SendOtherEvent;
    }

    int32_t acdcallbackProcessor::process(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

    std::string acdcallbackProcessor::get_name() const {
        return "global.acd.acdcallback";
    }

    int32_t acdcallbackProcessor::do_function__(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, 
        const std::string& fname, int32_t seqid) {
        std::map<std::string, do_function_ptr>::iterator it;
        it = __fun_map.find(fname);
        if (it == __fun_map.end()) {
            return bgcc::BaseProcessor::do_function__(request, request_len, proto, fname, seqid);
        }

        return (this->*(it->second))(request, request_len, proto, seqid);
    }

    int32_t acdcallbackProcessor::do_SendAgentEvent(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdcallback_SendAgentEvent_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdcallback_SendAgentEvent_result result;
        __intf->SendAgentEvent(args.event, map);
        ret = proto->writeMessageBegin("global.acd.acdcallback", "SendAgentEvent", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdcallbackProcessor::do_SendMediaEvent(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdcallback_SendMediaEvent_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdcallback_SendMediaEvent_result result;
        __intf->SendMediaEvent(args.event, map);
        ret = proto->writeMessageBegin("global.acd.acdcallback", "SendMediaEvent", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdcallbackProcessor::do_SendQueueEvent(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdcallback_SendQueueEvent_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdcallback_SendQueueEvent_result result;
        __intf->SendQueueEvent(args.event, map);
        ret = proto->writeMessageBegin("global.acd.acdcallback", "SendQueueEvent", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdcallbackProcessor::do_SendOtherEvent(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdcallback_SendOtherEvent_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdcallback_SendOtherEvent_result result;
        __intf->SendOtherEvent(args.event, map);
        ret = proto->writeMessageBegin("global.acd.acdcallback", "SendOtherEvent", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

}


