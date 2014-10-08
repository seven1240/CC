#include "acd.h"

namespace acd {
    acdapi_SignIn_args::acdapi_SignIn_args() {
    }

    acdapi_SignIn_args::~acdapi_SignIn_args() {
    }

    bool acdapi_SignIn_args::operator==(const acdapi_SignIn_args& rhs) const {
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
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_SignIn_args::operator!=(const acdapi_SignIn_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SignIn_args::operator< (const acdapi_SignIn_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(agentDn < rhs.agentDn)) {
            return false;
        }
        if (!(agentPwd < rhs.agentPwd)) {
            return false;
        }
        if (!(statusChangetype < rhs.statusChangetype)) {
            return false;
        }
        if (!(autoAnswer < rhs.autoAnswer)) {
            return false;
        }
        if (!(fcSignin < rhs.fcSignin)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SignIn_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentPwd);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    int32_t ele_var1;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var1);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    statusChangetype = ele_var1;
                }
                break;
            case 5:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, autoAnswer);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, fcSignin);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 7:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_SignOut_args::acdapi_SignOut_args() {
    }

    acdapi_SignOut_args::~acdapi_SignOut_args() {
    }

    bool acdapi_SignOut_args::operator==(const acdapi_SignOut_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_SignOut_args::operator!=(const acdapi_SignOut_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SignOut_args::operator< (const acdapi_SignOut_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SignOut_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_SetAgentStatus_args::acdapi_SetAgentStatus_args() {
    }

    acdapi_SetAgentStatus_args::~acdapi_SetAgentStatus_args() {
    }

    bool acdapi_SetAgentStatus_args::operator==(const acdapi_SetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (agentStatus != rhs.agentStatus) {
            return false;
        }
        if (restReason != rhs.restReason) {
            return false;
        }
        return true;
    }

    bool acdapi_SetAgentStatus_args::operator!=(const acdapi_SetAgentStatus_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SetAgentStatus_args::operator< (const acdapi_SetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(agentStatus < rhs.agentStatus)) {
            return false;
        }
        if (!(restReason < rhs.restReason)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SetAgentStatus_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    int32_t ele_var2;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var2);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    agentStatus = ele_var2;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, restReason);
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

    acdapi_GetAgentStatus_args::acdapi_GetAgentStatus_args() {
    }

    acdapi_GetAgentStatus_args::~acdapi_GetAgentStatus_args() {
    }

    bool acdapi_GetAgentStatus_args::operator==(const acdapi_GetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentStatus_args::operator!=(const acdapi_GetAgentStatus_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentStatus_args::operator< (const acdapi_GetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentStatus_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_ResetStatuschangetype_args::acdapi_ResetStatuschangetype_args() {
    }

    acdapi_ResetStatuschangetype_args::~acdapi_ResetStatuschangetype_args() {
    }

    bool acdapi_ResetStatuschangetype_args::operator==(const acdapi_ResetStatuschangetype_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (statusChangetype != rhs.statusChangetype) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetStatuschangetype_args::operator!=(const acdapi_ResetStatuschangetype_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetStatuschangetype_args::operator< (const acdapi_ResetStatuschangetype_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(statusChangetype < rhs.statusChangetype)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetStatuschangetype_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    int32_t ele_var3;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var3);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    statusChangetype = ele_var3;
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

    acdapi_ResetAutoAnswer_args::acdapi_ResetAutoAnswer_args() {
    }

    acdapi_ResetAutoAnswer_args::~acdapi_ResetAutoAnswer_args() {
    }

    bool acdapi_ResetAutoAnswer_args::operator==(const acdapi_ResetAutoAnswer_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (autoAnswer != rhs.autoAnswer) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetAutoAnswer_args::operator!=(const acdapi_ResetAutoAnswer_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetAutoAnswer_args::operator< (const acdapi_ResetAutoAnswer_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(autoAnswer < rhs.autoAnswer)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetAutoAnswer_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, autoAnswer);
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

    acdapi_ResetSkill_args::acdapi_ResetSkill_args() {
    }

    acdapi_ResetSkill_args::~acdapi_ResetSkill_args() {
    }

    bool acdapi_ResetSkill_args::operator==(const acdapi_ResetSkill_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetSkill_args::operator!=(const acdapi_ResetSkill_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetSkill_args::operator< (const acdapi_ResetSkill_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetSkill_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_Reset_args::acdapi_Reset_args() {
    }

    acdapi_Reset_args::~acdapi_Reset_args() {
    }

    bool acdapi_Reset_args::operator==(const acdapi_Reset_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_Reset_args::operator!=(const acdapi_Reset_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Reset_args::operator< (const acdapi_Reset_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Reset_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_OutboundCall_args::acdapi_OutboundCall_args() {
    }

    acdapi_OutboundCall_args::~acdapi_OutboundCall_args() {
    }

    bool acdapi_OutboundCall_args::operator==(const acdapi_OutboundCall_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destId != rhs.destId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        if (timeout != rhs.timeout) {
            return false;
        }
        if (callMode != rhs.callMode) {
            return false;
        }
        if (callType != rhs.callType) {
            return false;
        }
        return true;
    }

    bool acdapi_OutboundCall_args::operator!=(const acdapi_OutboundCall_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_OutboundCall_args::operator< (const acdapi_OutboundCall_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destId < rhs.destId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        if (!(timeout < rhs.timeout)) {
            return false;
        }
        if (!(callMode < rhs.callMode)) {
            return false;
        }
        if (!(callType < rhs.callType)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_OutboundCall_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 7:
                {
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, timeout);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 8:
                {
                    int32_t ele_var4;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var4);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    callMode = ele_var4;
                }
                break;
            case 9:
                {
                    int32_t ele_var5;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var5);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    callType = ele_var5;
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

    acdapi_AnswerCall_args::acdapi_AnswerCall_args() {
    }

    acdapi_AnswerCall_args::~acdapi_AnswerCall_args() {
    }

    bool acdapi_AnswerCall_args::operator==(const acdapi_AnswerCall_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_AnswerCall_args::operator!=(const acdapi_AnswerCall_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_AnswerCall_args::operator< (const acdapi_AnswerCall_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_AnswerCall_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_ReleaseCall_args::acdapi_ReleaseCall_args() {
    }

    acdapi_ReleaseCall_args::~acdapi_ReleaseCall_args() {
    }

    bool acdapi_ReleaseCall_args::operator==(const acdapi_ReleaseCall_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_ReleaseCall_args::operator!=(const acdapi_ReleaseCall_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ReleaseCall_args::operator< (const acdapi_ReleaseCall_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ReleaseCall_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_Hold_args::acdapi_Hold_args() {
    }

    acdapi_Hold_args::~acdapi_Hold_args() {
    }

    bool acdapi_Hold_args::operator==(const acdapi_Hold_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_Hold_args::operator!=(const acdapi_Hold_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Hold_args::operator< (const acdapi_Hold_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Hold_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_Retrieve_args::acdapi_Retrieve_args() {
    }

    acdapi_Retrieve_args::~acdapi_Retrieve_args() {
    }

    bool acdapi_Retrieve_args::operator==(const acdapi_Retrieve_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_Retrieve_args::operator!=(const acdapi_Retrieve_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Retrieve_args::operator< (const acdapi_Retrieve_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Retrieve_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_Consult_args::acdapi_Consult_args() {
    }

    acdapi_Consult_args::~acdapi_Consult_args() {
    }

    bool acdapi_Consult_args::operator==(const acdapi_Consult_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destId != rhs.destId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        if (callType != rhs.callType) {
            return false;
        }
        return true;
    }

    bool acdapi_Consult_args::operator!=(const acdapi_Consult_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Consult_args::operator< (const acdapi_Consult_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destId < rhs.destId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        if (!(callType < rhs.callType)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Consult_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 7:
                {
                    int32_t ele_var6;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var6);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    callType = ele_var6;
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

    acdapi_ConsultReconnect_args::acdapi_ConsultReconnect_args() {
    }

    acdapi_ConsultReconnect_args::~acdapi_ConsultReconnect_args() {
    }

    bool acdapi_ConsultReconnect_args::operator==(const acdapi_ConsultReconnect_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultReconnect_args::operator!=(const acdapi_ConsultReconnect_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultReconnect_args::operator< (const acdapi_ConsultReconnect_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultReconnect_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_ConsultTransfer_args::acdapi_ConsultTransfer_args() {
    }

    acdapi_ConsultTransfer_args::~acdapi_ConsultTransfer_args() {
    }

    bool acdapi_ConsultTransfer_args::operator==(const acdapi_ConsultTransfer_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultTransfer_args::operator!=(const acdapi_ConsultTransfer_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultTransfer_args::operator< (const acdapi_ConsultTransfer_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultTransfer_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_SingleStepTransfer_args::acdapi_SingleStepTransfer_args() {
    }

    acdapi_SingleStepTransfer_args::~acdapi_SingleStepTransfer_args() {
    }

    bool acdapi_SingleStepTransfer_args::operator==(const acdapi_SingleStepTransfer_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destId != rhs.destId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        if (isPassthrough != rhs.isPassthrough) {
            return false;
        }
        if (transferType != rhs.transferType) {
            return false;
        }
        return true;
    }

    bool acdapi_SingleStepTransfer_args::operator!=(const acdapi_SingleStepTransfer_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SingleStepTransfer_args::operator< (const acdapi_SingleStepTransfer_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destId < rhs.destId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        if (!(isPassthrough < rhs.isPassthrough)) {
            return false;
        }
        if (!(transferType < rhs.transferType)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SingleStepTransfer_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 7:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, isPassthrough);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 8:
                {
                    int32_t ele_var7;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var7);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    transferType = ele_var7;
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

    acdapi_ConsultConference_args::acdapi_ConsultConference_args() {
    }

    acdapi_ConsultConference_args::~acdapi_ConsultConference_args() {
    }

    bool acdapi_ConsultConference_args::operator==(const acdapi_ConsultConference_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultConference_args::operator!=(const acdapi_ConsultConference_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultConference_args::operator< (const acdapi_ConsultConference_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultConference_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_ConferenceJoin_args::acdapi_ConferenceJoin_args() {
    }

    acdapi_ConferenceJoin_args::~acdapi_ConferenceJoin_args() {
    }

    bool acdapi_ConferenceJoin_args::operator==(const acdapi_ConferenceJoin_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        if (conferenceType != rhs.conferenceType) {
            return false;
        }
        return true;
    }

    bool acdapi_ConferenceJoin_args::operator!=(const acdapi_ConferenceJoin_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConferenceJoin_args::operator< (const acdapi_ConferenceJoin_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        if (!(conferenceType < rhs.conferenceType)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConferenceJoin_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 7:
                {
                    int32_t ele_var8;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var8);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    conferenceType = ele_var8;
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

    acdapi_SetAssociateData_args::acdapi_SetAssociateData_args() {
    }

    acdapi_SetAssociateData_args::~acdapi_SetAssociateData_args() {
    }

    bool acdapi_SetAssociateData_args::operator==(const acdapi_SetAssociateData_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (key != rhs.key) {
            return false;
        }
        if (value != rhs.value) {
            return false;
        }
        return true;
    }

    bool acdapi_SetAssociateData_args::operator!=(const acdapi_SetAssociateData_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SetAssociateData_args::operator< (const acdapi_SetAssociateData_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(key < rhs.key)) {
            return false;
        }
        if (!(value < rhs.value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SetAssociateData_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, key);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, value);
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

    acdapi_GetAssociateData_args::acdapi_GetAssociateData_args() {
    }

    acdapi_GetAssociateData_args::~acdapi_GetAssociateData_args() {
    }

    bool acdapi_GetAssociateData_args::operator==(const acdapi_GetAssociateData_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (key != rhs.key) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAssociateData_args::operator!=(const acdapi_GetAssociateData_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAssociateData_args::operator< (const acdapi_GetAssociateData_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(key < rhs.key)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAssociateData_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, key);
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

    acdapi_JumptheQueue_args::acdapi_JumptheQueue_args() {
    }

    acdapi_JumptheQueue_args::~acdapi_JumptheQueue_args() {
    }

    bool acdapi_JumptheQueue_args::operator==(const acdapi_JumptheQueue_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (requestId != rhs.requestId) {
            return false;
        }
        return true;
    }

    bool acdapi_JumptheQueue_args::operator!=(const acdapi_JumptheQueue_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_JumptheQueue_args::operator< (const acdapi_JumptheQueue_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(requestId < rhs.requestId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_JumptheQueue_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, requestId);
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

    acdapi_ForceSignIn_args::acdapi_ForceSignIn_args() {
    }

    acdapi_ForceSignIn_args::~acdapi_ForceSignIn_args() {
    }

    bool acdapi_ForceSignIn_args::operator==(const acdapi_ForceSignIn_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
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
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSignIn_args::operator!=(const acdapi_ForceSignIn_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSignIn_args::operator< (const acdapi_ForceSignIn_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(agentDn < rhs.agentDn)) {
            return false;
        }
        if (!(agentPwd < rhs.agentPwd)) {
            return false;
        }
        if (!(statusChangetype < rhs.statusChangetype)) {
            return false;
        }
        if (!(autoAnswer < rhs.autoAnswer)) {
            return false;
        }
        if (!(fcSignin < rhs.fcSignin)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSignIn_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentPwd);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    int32_t ele_var9;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var9);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    statusChangetype = ele_var9;
                }
                break;
            case 7:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, autoAnswer);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 8:
                {
                    ret = proto->readBool(OFFSET_PTR(request, nread), request_len - nread, fcSignin);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 9:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_ForceSignOut_args::acdapi_ForceSignOut_args() {
    }

    acdapi_ForceSignOut_args::~acdapi_ForceSignOut_args() {
    }

    bool acdapi_ForceSignOut_args::operator==(const acdapi_ForceSignOut_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSignOut_args::operator!=(const acdapi_ForceSignOut_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSignOut_args::operator< (const acdapi_ForceSignOut_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSignOut_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_ForceSetAgentStatus_args::acdapi_ForceSetAgentStatus_args() {
    }

    acdapi_ForceSetAgentStatus_args::~acdapi_ForceSetAgentStatus_args() {
    }

    bool acdapi_ForceSetAgentStatus_args::operator==(const acdapi_ForceSetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        if (agentStatus != rhs.agentStatus) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSetAgentStatus_args::operator!=(const acdapi_ForceSetAgentStatus_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSetAgentStatus_args::operator< (const acdapi_ForceSetAgentStatus_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(agentStatus < rhs.agentStatus)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSetAgentStatus_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    int32_t ele_var10;
                    ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var10);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    agentStatus = ele_var10;
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

    acdapi_Listen_args::acdapi_Listen_args() {
    }

    acdapi_Listen_args::~acdapi_Listen_args() {
    }

    bool acdapi_Listen_args::operator==(const acdapi_Listen_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        return true;
    }

    bool acdapi_Listen_args::operator!=(const acdapi_Listen_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Listen_args::operator< (const acdapi_Listen_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Listen_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
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

    acdapi_StopListen_args::acdapi_StopListen_args() {
    }

    acdapi_StopListen_args::~acdapi_StopListen_args() {
    }

    bool acdapi_StopListen_args::operator==(const acdapi_StopListen_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_StopListen_args::operator!=(const acdapi_StopListen_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopListen_args::operator< (const acdapi_StopListen_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopListen_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_Insert_args::acdapi_Insert_args() {
    }

    acdapi_Insert_args::~acdapi_Insert_args() {
    }

    bool acdapi_Insert_args::operator==(const acdapi_Insert_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        return true;
    }

    bool acdapi_Insert_args::operator!=(const acdapi_Insert_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Insert_args::operator< (const acdapi_Insert_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Insert_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
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

    acdapi_StopInsert_args::acdapi_StopInsert_args() {
    }

    acdapi_StopInsert_args::~acdapi_StopInsert_args() {
    }

    bool acdapi_StopInsert_args::operator==(const acdapi_StopInsert_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_StopInsert_args::operator!=(const acdapi_StopInsert_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopInsert_args::operator< (const acdapi_StopInsert_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopInsert_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_SwitchInsertorListen_args::acdapi_SwitchInsertorListen_args() {
    }

    acdapi_SwitchInsertorListen_args::~acdapi_SwitchInsertorListen_args() {
    }

    bool acdapi_SwitchInsertorListen_args::operator==(const acdapi_SwitchInsertorListen_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (callerId != rhs.callerId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        if (forCallerDispNum != rhs.forCallerDispNum) {
            return false;
        }
        if (forCalleeDispNum != rhs.forCalleeDispNum) {
            return false;
        }
        return true;
    }

    bool acdapi_SwitchInsertorListen_args::operator!=(const acdapi_SwitchInsertorListen_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SwitchInsertorListen_args::operator< (const acdapi_SwitchInsertorListen_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(callerId < rhs.callerId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        if (!(forCallerDispNum < rhs.forCallerDispNum)) {
            return false;
        }
        if (!(forCalleeDispNum < rhs.forCalleeDispNum)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SwitchInsertorListen_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callerId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 4:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 5:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCallerDispNum);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 6:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, forCalleeDispNum);
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

    acdapi_Break_args::acdapi_Break_args() {
    }

    acdapi_Break_args::~acdapi_Break_args() {
    }

    bool acdapi_Break_args::operator==(const acdapi_Break_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_Break_args::operator!=(const acdapi_Break_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Break_args::operator< (const acdapi_Break_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Break_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_SendDTMF_args::acdapi_SendDTMF_args() {
    }

    acdapi_SendDTMF_args::~acdapi_SendDTMF_args() {
    }

    bool acdapi_SendDTMF_args::operator==(const acdapi_SendDTMF_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (digitals != rhs.digitals) {
            return false;
        }
        return true;
    }

    bool acdapi_SendDTMF_args::operator!=(const acdapi_SendDTMF_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SendDTMF_args::operator< (const acdapi_SendDTMF_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(digitals < rhs.digitals)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SendDTMF_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, digitals);
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

    acdapi_StartPlay_args::acdapi_StartPlay_args() {
    }

    acdapi_StartPlay_args::~acdapi_StartPlay_args() {
    }

    bool acdapi_StartPlay_args::operator==(const acdapi_StartPlay_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (filename != rhs.filename) {
            return false;
        }
        return true;
    }

    bool acdapi_StartPlay_args::operator!=(const acdapi_StartPlay_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StartPlay_args::operator< (const acdapi_StartPlay_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(filename < rhs.filename)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StartPlay_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, filename);
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

    acdapi_StopPlay_args::acdapi_StopPlay_args() {
    }

    acdapi_StopPlay_args::~acdapi_StopPlay_args() {
    }

    bool acdapi_StopPlay_args::operator==(const acdapi_StopPlay_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_StopPlay_args::operator!=(const acdapi_StopPlay_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopPlay_args::operator< (const acdapi_StopPlay_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopPlay_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_MuteOn_args::acdapi_MuteOn_args() {
    }

    acdapi_MuteOn_args::~acdapi_MuteOn_args() {
    }

    bool acdapi_MuteOn_args::operator==(const acdapi_MuteOn_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_MuteOn_args::operator!=(const acdapi_MuteOn_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_MuteOn_args::operator< (const acdapi_MuteOn_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_MuteOn_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_MuteOff_args::acdapi_MuteOff_args() {
    }

    acdapi_MuteOff_args::~acdapi_MuteOff_args() {
    }

    bool acdapi_MuteOff_args::operator==(const acdapi_MuteOff_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_MuteOff_args::operator!=(const acdapi_MuteOff_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_MuteOff_args::operator< (const acdapi_MuteOff_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_MuteOff_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_GetAgentDetailByAgentID_args::acdapi_GetAgentDetailByAgentID_args() {
    }

    acdapi_GetAgentDetailByAgentID_args::~acdapi_GetAgentDetailByAgentID_args() {
    }

    bool acdapi_GetAgentDetailByAgentID_args::operator==(const acdapi_GetAgentDetailByAgentID_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailByAgentID_args::operator!=(const acdapi_GetAgentDetailByAgentID_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailByAgentID_args::operator< (const acdapi_GetAgentDetailByAgentID_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailByAgentID_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_GetAgentDetailByAgentDN_args::acdapi_GetAgentDetailByAgentDN_args() {
    }

    acdapi_GetAgentDetailByAgentDN_args::~acdapi_GetAgentDetailByAgentDN_args() {
    }

    bool acdapi_GetAgentDetailByAgentDN_args::operator==(const acdapi_GetAgentDetailByAgentDN_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentDn != rhs.destAgentDn) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailByAgentDN_args::operator!=(const acdapi_GetAgentDetailByAgentDN_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailByAgentDN_args::operator< (const acdapi_GetAgentDetailByAgentDN_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentDn < rhs.destAgentDn)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailByAgentDN_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentDn);
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

    acdapi_GetAgentDetailsByAgentIDs_args::acdapi_GetAgentDetailsByAgentIDs_args() {
    }

    acdapi_GetAgentDetailsByAgentIDs_args::~acdapi_GetAgentDetailsByAgentIDs_args() {
    }

    bool acdapi_GetAgentDetailsByAgentIDs_args::operator==(const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentIdList != rhs.destAgentIdList) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailsByAgentIDs_args::operator!=(const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsByAgentIDs_args::operator< (const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentIdList < rhs.destAgentIdList)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailsByAgentIDs_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    destAgentIdList.clear();

                    int32_t size_var11;
                    bgcc::DataTypeID etype_var12;

                    ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var12, size_var11);
                    if (ret < 0) { return ret; }
                    nread += ret;

                    destAgentIdList.reserve(size_var11);
                    for(int32_t i = 0; i < size_var11; ++i) {
                        std::string value_var13;
                        ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, value_var13);
                        if (ret < 0) { return ret; }
                        nread += ret;
                        destAgentIdList.push_back(value_var13);
                    }

                    ret = proto->readListEnd();
                    if (ret < 0) { return ret; }
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

    acdapi_GetAgentDetailsByAgentDNs_args::acdapi_GetAgentDetailsByAgentDNs_args() {
    }

    acdapi_GetAgentDetailsByAgentDNs_args::~acdapi_GetAgentDetailsByAgentDNs_args() {
    }

    bool acdapi_GetAgentDetailsByAgentDNs_args::operator==(const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentDnList != rhs.destAgentDnList) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailsByAgentDNs_args::operator!=(const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsByAgentDNs_args::operator< (const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentDnList < rhs.destAgentDnList)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailsByAgentDNs_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    destAgentDnList.clear();

                    int32_t size_var14;
                    bgcc::DataTypeID etype_var15;

                    ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var15, size_var14);
                    if (ret < 0) { return ret; }
                    nread += ret;

                    destAgentDnList.reserve(size_var14);
                    for(int32_t i = 0; i < size_var14; ++i) {
                        std::string value_var16;
                        ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, value_var16);
                        if (ret < 0) { return ret; }
                        nread += ret;
                        destAgentDnList.push_back(value_var16);
                    }

                    ret = proto->readListEnd();
                    if (ret < 0) { return ret; }
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

    acdapi_GetRecordFileName_args::acdapi_GetRecordFileName_args() {
    }

    acdapi_GetRecordFileName_args::~acdapi_GetRecordFileName_args() {
    }

    bool acdapi_GetRecordFileName_args::operator==(const acdapi_GetRecordFileName_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetRecordFileName_args::operator!=(const acdapi_GetRecordFileName_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetRecordFileName_args::operator< (const acdapi_GetRecordFileName_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetRecordFileName_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_GetSkill_args::acdapi_GetSkill_args() {
    }

    acdapi_GetSkill_args::~acdapi_GetSkill_args() {
    }

    bool acdapi_GetSkill_args::operator==(const acdapi_GetSkill_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkill_args::operator!=(const acdapi_GetSkill_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkill_args::operator< (const acdapi_GetSkill_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkill_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_GetRestReason_args::acdapi_GetRestReason_args() {
    }

    acdapi_GetRestReason_args::~acdapi_GetRestReason_args() {
    }

    bool acdapi_GetRestReason_args::operator==(const acdapi_GetRestReason_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetRestReason_args::operator!=(const acdapi_GetRestReason_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetRestReason_args::operator< (const acdapi_GetRestReason_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetRestReason_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_GetAgentNumberBySkill_args::acdapi_GetAgentNumberBySkill_args() {
    }

    acdapi_GetAgentNumberBySkill_args::~acdapi_GetAgentNumberBySkill_args() {
    }

    bool acdapi_GetAgentNumberBySkill_args::operator==(const acdapi_GetAgentNumberBySkill_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentNumberBySkill_args::operator!=(const acdapi_GetAgentNumberBySkill_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentNumberBySkill_args::operator< (const acdapi_GetAgentNumberBySkill_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentNumberBySkill_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_GetAgentDetailsBySkill_args::acdapi_GetAgentDetailsBySkill_args() {
    }

    acdapi_GetAgentDetailsBySkill_args::~acdapi_GetAgentDetailsBySkill_args() {
    }

    bool acdapi_GetAgentDetailsBySkill_args::operator==(const acdapi_GetAgentDetailsBySkill_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailsBySkill_args::operator!=(const acdapi_GetAgentDetailsBySkill_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsBySkill_args::operator< (const acdapi_GetAgentDetailsBySkill_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailsBySkill_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_GetSkillWaitingNumber_args::acdapi_GetSkillWaitingNumber_args() {
    }

    acdapi_GetSkillWaitingNumber_args::~acdapi_GetSkillWaitingNumber_args() {
    }

    bool acdapi_GetSkillWaitingNumber_args::operator==(const acdapi_GetSkillWaitingNumber_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkillWaitingNumber_args::operator!=(const acdapi_GetSkillWaitingNumber_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkillWaitingNumber_args::operator< (const acdapi_GetSkillWaitingNumber_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkillWaitingNumber_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_GetSkillWaitingCallInfo_args::acdapi_GetSkillWaitingCallInfo_args() {
    }

    acdapi_GetSkillWaitingCallInfo_args::~acdapi_GetSkillWaitingCallInfo_args() {
    }

    bool acdapi_GetSkillWaitingCallInfo_args::operator==(const acdapi_GetSkillWaitingCallInfo_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkillWaitingCallInfo_args::operator!=(const acdapi_GetSkillWaitingCallInfo_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkillWaitingCallInfo_args::operator< (const acdapi_GetSkillWaitingCallInfo_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkillWaitingCallInfo_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, skill);
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

    acdapi_GetPrivateQueue_args::acdapi_GetPrivateQueue_args() {
    }

    acdapi_GetPrivateQueue_args::~acdapi_GetPrivateQueue_args() {
    }

    bool acdapi_GetPrivateQueue_args::operator==(const acdapi_GetPrivateQueue_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (destAgentId != rhs.destAgentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetPrivateQueue_args::operator!=(const acdapi_GetPrivateQueue_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetPrivateQueue_args::operator< (const acdapi_GetPrivateQueue_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        if (!(destAgentId < rhs.destAgentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetPrivateQueue_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 3:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, destAgentId);
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

    acdapi_GetSysInfo_args::acdapi_GetSysInfo_args() {
    }

    acdapi_GetSysInfo_args::~acdapi_GetSysInfo_args() {
    }

    bool acdapi_GetSysInfo_args::operator==(const acdapi_GetSysInfo_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSysInfo_args::operator!=(const acdapi_GetSysInfo_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSysInfo_args::operator< (const acdapi_GetSysInfo_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSysInfo_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_SynchronizeCTITime_args::acdapi_SynchronizeCTITime_args() {
    }

    acdapi_SynchronizeCTITime_args::~acdapi_SynchronizeCTITime_args() {
    }

    bool acdapi_SynchronizeCTITime_args::operator==(const acdapi_SynchronizeCTITime_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_SynchronizeCTITime_args::operator!=(const acdapi_SynchronizeCTITime_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SynchronizeCTITime_args::operator< (const acdapi_SynchronizeCTITime_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SynchronizeCTITime_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_Heartbeat_args::acdapi_Heartbeat_args() {
    }

    acdapi_Heartbeat_args::~acdapi_Heartbeat_args() {
    }

    bool acdapi_Heartbeat_args::operator==(const acdapi_Heartbeat_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (handle != rhs.handle) {
            return false;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        return true;
    }

    bool acdapi_Heartbeat_args::operator!=(const acdapi_Heartbeat_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Heartbeat_args::operator< (const acdapi_Heartbeat_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        if (!(agentId < rhs.agentId)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Heartbeat_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, handle);
                    if (ret < 0) { return ret; }
                    nread += ret;
                }
                break;
            case 2:
                {
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentId);
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

    acdapi_ResetConfig_args::acdapi_ResetConfig_args() {
    }

    acdapi_ResetConfig_args::~acdapi_ResetConfig_args() {
    }

    bool acdapi_ResetConfig_args::operator==(const acdapi_ResetConfig_args& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (password != rhs.password) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetConfig_args::operator!=(const acdapi_ResetConfig_args& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetConfig_args::operator< (const acdapi_ResetConfig_args& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(password < rhs.password)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetConfig_args::read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, password);
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

    acdapi_SignIn_pargs::~acdapi_SignIn_pargs() {
    }

    int32_t acdapi_SignIn_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SignIn_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentDn)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentPwd", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentPwd)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("statusChangetype", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(statusChangetype)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("autoAnswer", bgcc::IDBOOL, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(autoAnswer)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("fcSignin", bgcc::IDBOOL, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(fcSignin)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SignOut_pargs::~acdapi_SignOut_pargs() {
    }

    int32_t acdapi_SignOut_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SignOut_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SetAgentStatus_pargs::~acdapi_SetAgentStatus_pargs() {
    }

    int32_t acdapi_SetAgentStatus_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SetAgentStatus_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentStatus", bgcc::IDINT32, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(agentStatus)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("restReason", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(restReason)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentStatus_pargs::~acdapi_GetAgentStatus_pargs() {
    }

    int32_t acdapi_GetAgentStatus_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentStatus_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ResetStatuschangetype_pargs::~acdapi_ResetStatuschangetype_pargs() {
    }

    int32_t acdapi_ResetStatuschangetype_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetStatuschangetype_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("statusChangetype", bgcc::IDINT32, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(statusChangetype)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ResetAutoAnswer_pargs::~acdapi_ResetAutoAnswer_pargs() {
    }

    int32_t acdapi_ResetAutoAnswer_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetAutoAnswer_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("autoAnswer", bgcc::IDBOOL, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(autoAnswer)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ResetSkill_pargs::~acdapi_ResetSkill_pargs() {
    }

    int32_t acdapi_ResetSkill_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetSkill_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Reset_pargs::~acdapi_Reset_pargs() {
    }

    int32_t acdapi_Reset_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Reset_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_OutboundCall_pargs::~acdapi_OutboundCall_pargs() {
    }

    int32_t acdapi_OutboundCall_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_OutboundCall_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timeout", bgcc::IDINT32, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(timeout)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callMode", bgcc::IDINT32, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(callMode)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callType", bgcc::IDINT32, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(callType)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_AnswerCall_pargs::~acdapi_AnswerCall_pargs() {
    }

    int32_t acdapi_AnswerCall_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_AnswerCall_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ReleaseCall_pargs::~acdapi_ReleaseCall_pargs() {
    }

    int32_t acdapi_ReleaseCall_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ReleaseCall_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Hold_pargs::~acdapi_Hold_pargs() {
    }

    int32_t acdapi_Hold_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Hold_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Retrieve_pargs::~acdapi_Retrieve_pargs() {
    }

    int32_t acdapi_Retrieve_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Retrieve_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Consult_pargs::~acdapi_Consult_pargs() {
    }

    int32_t acdapi_Consult_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Consult_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callType", bgcc::IDINT32, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(callType)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ConsultReconnect_pargs::~acdapi_ConsultReconnect_pargs() {
    }

    int32_t acdapi_ConsultReconnect_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultReconnect_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ConsultTransfer_pargs::~acdapi_ConsultTransfer_pargs() {
    }

    int32_t acdapi_ConsultTransfer_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultTransfer_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SingleStepTransfer_pargs::~acdapi_SingleStepTransfer_pargs() {
    }

    int32_t acdapi_SingleStepTransfer_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SingleStepTransfer_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("isPassthrough", bgcc::IDBOOL, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(isPassthrough)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("transferType", bgcc::IDINT32, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(transferType)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ConsultConference_pargs::~acdapi_ConsultConference_pargs() {
    }

    int32_t acdapi_ConsultConference_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultConference_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ConferenceJoin_pargs::~acdapi_ConferenceJoin_pargs() {
    }

    int32_t acdapi_ConferenceJoin_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConferenceJoin_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("conferenceType", bgcc::IDINT32, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(conferenceType)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SetAssociateData_pargs::~acdapi_SetAssociateData_pargs() {
    }

    int32_t acdapi_SetAssociateData_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SetAssociateData_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("key", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(key)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("value", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(value)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAssociateData_pargs::~acdapi_GetAssociateData_pargs() {
    }

    int32_t acdapi_GetAssociateData_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAssociateData_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("key", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(key)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_JumptheQueue_pargs::~acdapi_JumptheQueue_pargs() {
    }

    int32_t acdapi_JumptheQueue_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_JumptheQueue_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("requestId", bgcc::IDINT64, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(requestId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ForceSignIn_pargs::~acdapi_ForceSignIn_pargs() {
    }

    int32_t acdapi_ForceSignIn_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSignIn_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentDn)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentPwd", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentPwd)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("statusChangetype", bgcc::IDINT32, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(statusChangetype)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("autoAnswer", bgcc::IDBOOL, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(autoAnswer)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("fcSignin", bgcc::IDBOOL, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeBool((*(fcSignin)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ForceSignOut_pargs::~acdapi_ForceSignOut_pargs() {
    }

    int32_t acdapi_ForceSignOut_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSignOut_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ForceSetAgentStatus_pargs::~acdapi_ForceSetAgentStatus_pargs() {
    }

    int32_t acdapi_ForceSetAgentStatus_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSetAgentStatus_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentStatus", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32((*(agentStatus)).get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Listen_pargs::~acdapi_Listen_pargs() {
    }

    int32_t acdapi_Listen_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Listen_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_StopListen_pargs::~acdapi_StopListen_pargs() {
    }

    int32_t acdapi_StopListen_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopListen_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Insert_pargs::~acdapi_Insert_pargs() {
    }

    int32_t acdapi_Insert_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Insert_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_StopInsert_pargs::~acdapi_StopInsert_pargs() {
    }

    int32_t acdapi_StopInsert_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopInsert_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SwitchInsertorListen_pargs::~acdapi_SwitchInsertorListen_pargs() {
    }

    int32_t acdapi_SwitchInsertorListen_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SwitchInsertorListen_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callerId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(callerId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCallerDispNum", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCallerDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("forCalleeDispNum", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(forCalleeDispNum)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Break_pargs::~acdapi_Break_pargs() {
    }

    int32_t acdapi_Break_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Break_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SendDTMF_pargs::~acdapi_SendDTMF_pargs() {
    }

    int32_t acdapi_SendDTMF_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SendDTMF_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("digitals", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(digitals)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_StartPlay_pargs::~acdapi_StartPlay_pargs() {
    }

    int32_t acdapi_StartPlay_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StartPlay_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("filename", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(filename)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_StopPlay_pargs::~acdapi_StopPlay_pargs() {
    }

    int32_t acdapi_StopPlay_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopPlay_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_MuteOn_pargs::~acdapi_MuteOn_pargs() {
    }

    int32_t acdapi_MuteOn_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_MuteOn_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_MuteOff_pargs::~acdapi_MuteOff_pargs() {
    }

    int32_t acdapi_MuteOff_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_MuteOff_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentDetailByAgentID_pargs::~acdapi_GetAgentDetailByAgentID_pargs() {
    }

    int32_t acdapi_GetAgentDetailByAgentID_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailByAgentID_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentDetailByAgentDN_pargs::~acdapi_GetAgentDetailByAgentDN_pargs() {
    }

    int32_t acdapi_GetAgentDetailByAgentDN_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailByAgentDN_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentDn", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentDn)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentDetailsByAgentIDs_pargs::~acdapi_GetAgentDetailsByAgentIDs_pargs() {
    }

    int32_t acdapi_GetAgentDetailsByAgentIDs_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsByAgentIDs_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentIdList", bgcc::IDLIST, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTR, (*(destAgentIdList)).size());
        if (ret < 0) { return ret; }
        std::vector<std::string> ::const_iterator citr_var17;
        for (citr_var17 = (*(destAgentIdList)).begin(); citr_var17 != (*(destAgentIdList)).end(); ++citr_var17) {
            ret = proto->writeString((*citr_var17));
            if (ret < 0) { return ret; }
        }
        ret = proto->writeListEnd();
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentDetailsByAgentDNs_pargs::~acdapi_GetAgentDetailsByAgentDNs_pargs() {
    }

    int32_t acdapi_GetAgentDetailsByAgentDNs_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsByAgentDNs_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentDnList", bgcc::IDLIST, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTR, (*(destAgentDnList)).size());
        if (ret < 0) { return ret; }
        std::vector<std::string> ::const_iterator citr_var18;
        for (citr_var18 = (*(destAgentDnList)).begin(); citr_var18 != (*(destAgentDnList)).end(); ++citr_var18) {
            ret = proto->writeString((*citr_var18));
            if (ret < 0) { return ret; }
        }
        ret = proto->writeListEnd();
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetRecordFileName_pargs::~acdapi_GetRecordFileName_pargs() {
    }

    int32_t acdapi_GetRecordFileName_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetRecordFileName_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetSkill_pargs::~acdapi_GetSkill_pargs() {
    }

    int32_t acdapi_GetSkill_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkill_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetRestReason_pargs::~acdapi_GetRestReason_pargs() {
    }

    int32_t acdapi_GetRestReason_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetRestReason_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentNumberBySkill_pargs::~acdapi_GetAgentNumberBySkill_pargs() {
    }

    int32_t acdapi_GetAgentNumberBySkill_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentNumberBySkill_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetAgentDetailsBySkill_pargs::~acdapi_GetAgentDetailsBySkill_pargs() {
    }

    int32_t acdapi_GetAgentDetailsBySkill_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsBySkill_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetSkillWaitingNumber_pargs::~acdapi_GetSkillWaitingNumber_pargs() {
    }

    int32_t acdapi_GetSkillWaitingNumber_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkillWaitingNumber_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetSkillWaitingCallInfo_pargs::~acdapi_GetSkillWaitingCallInfo_pargs() {
    }

    int32_t acdapi_GetSkillWaitingCallInfo_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkillWaitingCallInfo_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(skill)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetPrivateQueue_pargs::~acdapi_GetPrivateQueue_pargs() {
    }

    int32_t acdapi_GetPrivateQueue_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetPrivateQueue_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("destAgentId", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(destAgentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_GetSysInfo_pargs::~acdapi_GetSysInfo_pargs() {
    }

    int32_t acdapi_GetSysInfo_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSysInfo_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SynchronizeCTITime_pargs::~acdapi_SynchronizeCTITime_pargs() {
    }

    int32_t acdapi_SynchronizeCTITime_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SynchronizeCTITime_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_Heartbeat_pargs::~acdapi_Heartbeat_pargs() {
    }

    int32_t acdapi_Heartbeat_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Heartbeat_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64((*(handle)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(agentId)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_ResetConfig_pargs::~acdapi_ResetConfig_pargs() {
    }

    int32_t acdapi_ResetConfig_pargs::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetConfig_pargs");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("password", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString((*(password)));
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }
        ret = proto->writeStructEnd();
        if (ret < 0) { return ret; }
        return ret;
    };

    acdapi_SignIn_result::acdapi_SignIn_result() {
    }

    acdapi_SignIn_result::~acdapi_SignIn_result() {
    }

    bool acdapi_SignIn_result::operator==(const acdapi_SignIn_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (handle != rhs.handle) {
            return false;
        }
        return true;
    }

    bool acdapi_SignIn_result::operator!=(const acdapi_SignIn_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SignIn_result::operator< (const acdapi_SignIn_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(handle < rhs.handle)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SignIn_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SignIn_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("handle", bgcc::IDINT64, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(handle);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SignOut_result::acdapi_SignOut_result() {
    }

    acdapi_SignOut_result::~acdapi_SignOut_result() {
    }

    bool acdapi_SignOut_result::operator==(const acdapi_SignOut_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SignOut_result::operator!=(const acdapi_SignOut_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SignOut_result::operator< (const acdapi_SignOut_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SignOut_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SignOut_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SetAgentStatus_result::acdapi_SetAgentStatus_result() {
    }

    acdapi_SetAgentStatus_result::~acdapi_SetAgentStatus_result() {
    }

    bool acdapi_SetAgentStatus_result::operator==(const acdapi_SetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SetAgentStatus_result::operator!=(const acdapi_SetAgentStatus_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SetAgentStatus_result::operator< (const acdapi_SetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SetAgentStatus_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SetAgentStatus_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAgentStatus_result::acdapi_GetAgentStatus_result() {
    }

    acdapi_GetAgentStatus_result::~acdapi_GetAgentStatus_result() {
    }

    bool acdapi_GetAgentStatus_result::operator==(const acdapi_GetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (agentStatus != rhs.agentStatus) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentStatus_result::operator!=(const acdapi_GetAgentStatus_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentStatus_result::operator< (const acdapi_GetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(agentStatus < rhs.agentStatus)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentStatus_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentStatus_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentStatus", bgcc::IDINT32, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(agentStatus.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ResetStatuschangetype_result::acdapi_ResetStatuschangetype_result() {
    }

    acdapi_ResetStatuschangetype_result::~acdapi_ResetStatuschangetype_result() {
    }

    bool acdapi_ResetStatuschangetype_result::operator==(const acdapi_ResetStatuschangetype_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetStatuschangetype_result::operator!=(const acdapi_ResetStatuschangetype_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetStatuschangetype_result::operator< (const acdapi_ResetStatuschangetype_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetStatuschangetype_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetStatuschangetype_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ResetAutoAnswer_result::acdapi_ResetAutoAnswer_result() {
    }

    acdapi_ResetAutoAnswer_result::~acdapi_ResetAutoAnswer_result() {
    }

    bool acdapi_ResetAutoAnswer_result::operator==(const acdapi_ResetAutoAnswer_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetAutoAnswer_result::operator!=(const acdapi_ResetAutoAnswer_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetAutoAnswer_result::operator< (const acdapi_ResetAutoAnswer_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetAutoAnswer_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetAutoAnswer_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ResetSkill_result::acdapi_ResetSkill_result() {
    }

    acdapi_ResetSkill_result::~acdapi_ResetSkill_result() {
    }

    bool acdapi_ResetSkill_result::operator==(const acdapi_ResetSkill_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetSkill_result::operator!=(const acdapi_ResetSkill_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetSkill_result::operator< (const acdapi_ResetSkill_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetSkill_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetSkill_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Reset_result::acdapi_Reset_result() {
    }

    acdapi_Reset_result::~acdapi_Reset_result() {
    }

    bool acdapi_Reset_result::operator==(const acdapi_Reset_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Reset_result::operator!=(const acdapi_Reset_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Reset_result::operator< (const acdapi_Reset_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Reset_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Reset_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_OutboundCall_result::acdapi_OutboundCall_result() {
    }

    acdapi_OutboundCall_result::~acdapi_OutboundCall_result() {
    }

    bool acdapi_OutboundCall_result::operator==(const acdapi_OutboundCall_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_OutboundCall_result::operator!=(const acdapi_OutboundCall_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_OutboundCall_result::operator< (const acdapi_OutboundCall_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_OutboundCall_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_OutboundCall_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_AnswerCall_result::acdapi_AnswerCall_result() {
    }

    acdapi_AnswerCall_result::~acdapi_AnswerCall_result() {
    }

    bool acdapi_AnswerCall_result::operator==(const acdapi_AnswerCall_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_AnswerCall_result::operator!=(const acdapi_AnswerCall_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_AnswerCall_result::operator< (const acdapi_AnswerCall_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_AnswerCall_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_AnswerCall_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ReleaseCall_result::acdapi_ReleaseCall_result() {
    }

    acdapi_ReleaseCall_result::~acdapi_ReleaseCall_result() {
    }

    bool acdapi_ReleaseCall_result::operator==(const acdapi_ReleaseCall_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ReleaseCall_result::operator!=(const acdapi_ReleaseCall_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ReleaseCall_result::operator< (const acdapi_ReleaseCall_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ReleaseCall_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ReleaseCall_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Hold_result::acdapi_Hold_result() {
    }

    acdapi_Hold_result::~acdapi_Hold_result() {
    }

    bool acdapi_Hold_result::operator==(const acdapi_Hold_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Hold_result::operator!=(const acdapi_Hold_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Hold_result::operator< (const acdapi_Hold_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Hold_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Hold_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Retrieve_result::acdapi_Retrieve_result() {
    }

    acdapi_Retrieve_result::~acdapi_Retrieve_result() {
    }

    bool acdapi_Retrieve_result::operator==(const acdapi_Retrieve_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Retrieve_result::operator!=(const acdapi_Retrieve_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Retrieve_result::operator< (const acdapi_Retrieve_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Retrieve_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Retrieve_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Consult_result::acdapi_Consult_result() {
    }

    acdapi_Consult_result::~acdapi_Consult_result() {
    }

    bool acdapi_Consult_result::operator==(const acdapi_Consult_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Consult_result::operator!=(const acdapi_Consult_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Consult_result::operator< (const acdapi_Consult_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Consult_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Consult_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ConsultReconnect_result::acdapi_ConsultReconnect_result() {
    }

    acdapi_ConsultReconnect_result::~acdapi_ConsultReconnect_result() {
    }

    bool acdapi_ConsultReconnect_result::operator==(const acdapi_ConsultReconnect_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultReconnect_result::operator!=(const acdapi_ConsultReconnect_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultReconnect_result::operator< (const acdapi_ConsultReconnect_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultReconnect_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultReconnect_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ConsultTransfer_result::acdapi_ConsultTransfer_result() {
    }

    acdapi_ConsultTransfer_result::~acdapi_ConsultTransfer_result() {
    }

    bool acdapi_ConsultTransfer_result::operator==(const acdapi_ConsultTransfer_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultTransfer_result::operator!=(const acdapi_ConsultTransfer_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultTransfer_result::operator< (const acdapi_ConsultTransfer_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultTransfer_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultTransfer_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SingleStepTransfer_result::acdapi_SingleStepTransfer_result() {
    }

    acdapi_SingleStepTransfer_result::~acdapi_SingleStepTransfer_result() {
    }

    bool acdapi_SingleStepTransfer_result::operator==(const acdapi_SingleStepTransfer_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SingleStepTransfer_result::operator!=(const acdapi_SingleStepTransfer_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SingleStepTransfer_result::operator< (const acdapi_SingleStepTransfer_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SingleStepTransfer_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SingleStepTransfer_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ConsultConference_result::acdapi_ConsultConference_result() {
    }

    acdapi_ConsultConference_result::~acdapi_ConsultConference_result() {
    }

    bool acdapi_ConsultConference_result::operator==(const acdapi_ConsultConference_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ConsultConference_result::operator!=(const acdapi_ConsultConference_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConsultConference_result::operator< (const acdapi_ConsultConference_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConsultConference_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConsultConference_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ConferenceJoin_result::acdapi_ConferenceJoin_result() {
    }

    acdapi_ConferenceJoin_result::~acdapi_ConferenceJoin_result() {
    }

    bool acdapi_ConferenceJoin_result::operator==(const acdapi_ConferenceJoin_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ConferenceJoin_result::operator!=(const acdapi_ConferenceJoin_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ConferenceJoin_result::operator< (const acdapi_ConferenceJoin_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ConferenceJoin_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ConferenceJoin_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SetAssociateData_result::acdapi_SetAssociateData_result() {
    }

    acdapi_SetAssociateData_result::~acdapi_SetAssociateData_result() {
    }

    bool acdapi_SetAssociateData_result::operator==(const acdapi_SetAssociateData_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SetAssociateData_result::operator!=(const acdapi_SetAssociateData_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SetAssociateData_result::operator< (const acdapi_SetAssociateData_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SetAssociateData_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SetAssociateData_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAssociateData_result::acdapi_GetAssociateData_result() {
    }

    acdapi_GetAssociateData_result::~acdapi_GetAssociateData_result() {
    }

    bool acdapi_GetAssociateData_result::operator==(const acdapi_GetAssociateData_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (value != rhs.value) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAssociateData_result::operator!=(const acdapi_GetAssociateData_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAssociateData_result::operator< (const acdapi_GetAssociateData_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(value < rhs.value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAssociateData_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAssociateData_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("value", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(value);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_JumptheQueue_result::acdapi_JumptheQueue_result() {
    }

    acdapi_JumptheQueue_result::~acdapi_JumptheQueue_result() {
    }

    bool acdapi_JumptheQueue_result::operator==(const acdapi_JumptheQueue_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_JumptheQueue_result::operator!=(const acdapi_JumptheQueue_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_JumptheQueue_result::operator< (const acdapi_JumptheQueue_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_JumptheQueue_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_JumptheQueue_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ForceSignIn_result::acdapi_ForceSignIn_result() {
    }

    acdapi_ForceSignIn_result::~acdapi_ForceSignIn_result() {
    }

    bool acdapi_ForceSignIn_result::operator==(const acdapi_ForceSignIn_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSignIn_result::operator!=(const acdapi_ForceSignIn_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSignIn_result::operator< (const acdapi_ForceSignIn_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSignIn_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSignIn_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ForceSignOut_result::acdapi_ForceSignOut_result() {
    }

    acdapi_ForceSignOut_result::~acdapi_ForceSignOut_result() {
    }

    bool acdapi_ForceSignOut_result::operator==(const acdapi_ForceSignOut_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSignOut_result::operator!=(const acdapi_ForceSignOut_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSignOut_result::operator< (const acdapi_ForceSignOut_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSignOut_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSignOut_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ForceSetAgentStatus_result::acdapi_ForceSetAgentStatus_result() {
    }

    acdapi_ForceSetAgentStatus_result::~acdapi_ForceSetAgentStatus_result() {
    }

    bool acdapi_ForceSetAgentStatus_result::operator==(const acdapi_ForceSetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ForceSetAgentStatus_result::operator!=(const acdapi_ForceSetAgentStatus_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ForceSetAgentStatus_result::operator< (const acdapi_ForceSetAgentStatus_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ForceSetAgentStatus_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ForceSetAgentStatus_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Listen_result::acdapi_Listen_result() {
    }

    acdapi_Listen_result::~acdapi_Listen_result() {
    }

    bool acdapi_Listen_result::operator==(const acdapi_Listen_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Listen_result::operator!=(const acdapi_Listen_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Listen_result::operator< (const acdapi_Listen_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Listen_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Listen_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_StopListen_result::acdapi_StopListen_result() {
    }

    acdapi_StopListen_result::~acdapi_StopListen_result() {
    }

    bool acdapi_StopListen_result::operator==(const acdapi_StopListen_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_StopListen_result::operator!=(const acdapi_StopListen_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopListen_result::operator< (const acdapi_StopListen_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopListen_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopListen_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Insert_result::acdapi_Insert_result() {
    }

    acdapi_Insert_result::~acdapi_Insert_result() {
    }

    bool acdapi_Insert_result::operator==(const acdapi_Insert_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Insert_result::operator!=(const acdapi_Insert_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Insert_result::operator< (const acdapi_Insert_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Insert_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Insert_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_StopInsert_result::acdapi_StopInsert_result() {
    }

    acdapi_StopInsert_result::~acdapi_StopInsert_result() {
    }

    bool acdapi_StopInsert_result::operator==(const acdapi_StopInsert_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_StopInsert_result::operator!=(const acdapi_StopInsert_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopInsert_result::operator< (const acdapi_StopInsert_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopInsert_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopInsert_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SwitchInsertorListen_result::acdapi_SwitchInsertorListen_result() {
    }

    acdapi_SwitchInsertorListen_result::~acdapi_SwitchInsertorListen_result() {
    }

    bool acdapi_SwitchInsertorListen_result::operator==(const acdapi_SwitchInsertorListen_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SwitchInsertorListen_result::operator!=(const acdapi_SwitchInsertorListen_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SwitchInsertorListen_result::operator< (const acdapi_SwitchInsertorListen_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SwitchInsertorListen_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SwitchInsertorListen_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Break_result::acdapi_Break_result() {
    }

    acdapi_Break_result::~acdapi_Break_result() {
    }

    bool acdapi_Break_result::operator==(const acdapi_Break_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Break_result::operator!=(const acdapi_Break_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Break_result::operator< (const acdapi_Break_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Break_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Break_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SendDTMF_result::acdapi_SendDTMF_result() {
    }

    acdapi_SendDTMF_result::~acdapi_SendDTMF_result() {
    }

    bool acdapi_SendDTMF_result::operator==(const acdapi_SendDTMF_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_SendDTMF_result::operator!=(const acdapi_SendDTMF_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SendDTMF_result::operator< (const acdapi_SendDTMF_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SendDTMF_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SendDTMF_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_StartPlay_result::acdapi_StartPlay_result() {
    }

    acdapi_StartPlay_result::~acdapi_StartPlay_result() {
    }

    bool acdapi_StartPlay_result::operator==(const acdapi_StartPlay_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_StartPlay_result::operator!=(const acdapi_StartPlay_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StartPlay_result::operator< (const acdapi_StartPlay_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StartPlay_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StartPlay_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_StopPlay_result::acdapi_StopPlay_result() {
    }

    acdapi_StopPlay_result::~acdapi_StopPlay_result() {
    }

    bool acdapi_StopPlay_result::operator==(const acdapi_StopPlay_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_StopPlay_result::operator!=(const acdapi_StopPlay_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_StopPlay_result::operator< (const acdapi_StopPlay_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_StopPlay_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_StopPlay_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_MuteOn_result::acdapi_MuteOn_result() {
    }

    acdapi_MuteOn_result::~acdapi_MuteOn_result() {
    }

    bool acdapi_MuteOn_result::operator==(const acdapi_MuteOn_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_MuteOn_result::operator!=(const acdapi_MuteOn_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_MuteOn_result::operator< (const acdapi_MuteOn_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_MuteOn_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_MuteOn_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_MuteOff_result::acdapi_MuteOff_result() {
    }

    acdapi_MuteOff_result::~acdapi_MuteOff_result() {
    }

    bool acdapi_MuteOff_result::operator==(const acdapi_MuteOff_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_MuteOff_result::operator!=(const acdapi_MuteOff_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_MuteOff_result::operator< (const acdapi_MuteOff_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_MuteOff_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_MuteOff_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAgentDetailByAgentID_result::acdapi_GetAgentDetailByAgentID_result() {
    }

    acdapi_GetAgentDetailByAgentID_result::~acdapi_GetAgentDetailByAgentID_result() {
    }

    bool acdapi_GetAgentDetailByAgentID_result::operator==(const acdapi_GetAgentDetailByAgentID_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (agentInfo != rhs.agentInfo) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailByAgentID_result::operator!=(const acdapi_GetAgentDetailByAgentID_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailByAgentID_result::operator< (const acdapi_GetAgentDetailByAgentID_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(agentInfo < rhs.agentInfo)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailByAgentID_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailByAgentID_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfo", bgcc::IDSTRUCT, 4);
        if (ret < 0) { return ret; }
        ret = agentInfo.write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAgentDetailByAgentDN_result::acdapi_GetAgentDetailByAgentDN_result() {
    }

    acdapi_GetAgentDetailByAgentDN_result::~acdapi_GetAgentDetailByAgentDN_result() {
    }

    bool acdapi_GetAgentDetailByAgentDN_result::operator==(const acdapi_GetAgentDetailByAgentDN_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (agentInfo != rhs.agentInfo) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailByAgentDN_result::operator!=(const acdapi_GetAgentDetailByAgentDN_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailByAgentDN_result::operator< (const acdapi_GetAgentDetailByAgentDN_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(agentInfo < rhs.agentInfo)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailByAgentDN_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailByAgentDN_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfo", bgcc::IDSTRUCT, 4);
        if (ret < 0) { return ret; }
        ret = agentInfo.write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAgentDetailsByAgentIDs_result::acdapi_GetAgentDetailsByAgentIDs_result() {
    }

    acdapi_GetAgentDetailsByAgentIDs_result::~acdapi_GetAgentDetailsByAgentIDs_result() {
    }

    bool acdapi_GetAgentDetailsByAgentIDs_result::operator==(const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const {
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

    bool acdapi_GetAgentDetailsByAgentIDs_result::operator!=(const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsByAgentIDs_result::operator< (const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const {
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

    int32_t acdapi_GetAgentDetailsByAgentIDs_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsByAgentIDs_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfoList", bgcc::IDLIST, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, agentInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<AgentInfoT> ::const_iterator citr_var19;
        for (citr_var19 = agentInfoList.begin(); citr_var19 != agentInfoList.end(); ++citr_var19) {
            ret = (*citr_var19).write(proto);
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

    acdapi_GetAgentDetailsByAgentDNs_result::acdapi_GetAgentDetailsByAgentDNs_result() {
    }

    acdapi_GetAgentDetailsByAgentDNs_result::~acdapi_GetAgentDetailsByAgentDNs_result() {
    }

    bool acdapi_GetAgentDetailsByAgentDNs_result::operator==(const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const {
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

    bool acdapi_GetAgentDetailsByAgentDNs_result::operator!=(const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsByAgentDNs_result::operator< (const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const {
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

    int32_t acdapi_GetAgentDetailsByAgentDNs_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsByAgentDNs_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfoList", bgcc::IDLIST, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, agentInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<AgentInfoT> ::const_iterator citr_var20;
        for (citr_var20 = agentInfoList.begin(); citr_var20 != agentInfoList.end(); ++citr_var20) {
            ret = (*citr_var20).write(proto);
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

    acdapi_GetRecordFileName_result::acdapi_GetRecordFileName_result() {
    }

    acdapi_GetRecordFileName_result::~acdapi_GetRecordFileName_result() {
    }

    bool acdapi_GetRecordFileName_result::operator==(const acdapi_GetRecordFileName_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (filename != rhs.filename) {
            return false;
        }
        return true;
    }

    bool acdapi_GetRecordFileName_result::operator!=(const acdapi_GetRecordFileName_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetRecordFileName_result::operator< (const acdapi_GetRecordFileName_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(filename < rhs.filename)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetRecordFileName_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetRecordFileName_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("filename", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(filename);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetSkill_result::acdapi_GetSkill_result() {
    }

    acdapi_GetSkill_result::~acdapi_GetSkill_result() {
    }

    bool acdapi_GetSkill_result::operator==(const acdapi_GetSkill_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (skill != rhs.skill) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkill_result::operator!=(const acdapi_GetSkill_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkill_result::operator< (const acdapi_GetSkill_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(skill < rhs.skill)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkill_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkill_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("skill", bgcc::IDLIST, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTR, skill.size());
        if (ret < 0) { return ret; }
        std::vector<std::string> ::const_iterator citr_var21;
        for (citr_var21 = skill.begin(); citr_var21 != skill.end(); ++citr_var21) {
            ret = proto->writeString((*citr_var21));
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

    acdapi_GetRestReason_result::acdapi_GetRestReason_result() {
    }

    acdapi_GetRestReason_result::~acdapi_GetRestReason_result() {
    }

    bool acdapi_GetRestReason_result::operator==(const acdapi_GetRestReason_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (restReason != rhs.restReason) {
            return false;
        }
        return true;
    }

    bool acdapi_GetRestReason_result::operator!=(const acdapi_GetRestReason_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetRestReason_result::operator< (const acdapi_GetRestReason_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(restReason < rhs.restReason)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetRestReason_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetRestReason_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("restReason", bgcc::IDLIST, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTR, restReason.size());
        if (ret < 0) { return ret; }
        std::vector<std::string> ::const_iterator citr_var22;
        for (citr_var22 = restReason.begin(); citr_var22 != restReason.end(); ++citr_var22) {
            ret = proto->writeString((*citr_var22));
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

    acdapi_GetAgentNumberBySkill_result::acdapi_GetAgentNumberBySkill_result() {
    }

    acdapi_GetAgentNumberBySkill_result::~acdapi_GetAgentNumberBySkill_result() {
    }

    bool acdapi_GetAgentNumberBySkill_result::operator==(const acdapi_GetAgentNumberBySkill_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (agentNum != rhs.agentNum) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentNumberBySkill_result::operator!=(const acdapi_GetAgentNumberBySkill_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentNumberBySkill_result::operator< (const acdapi_GetAgentNumberBySkill_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(agentNum < rhs.agentNum)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentNumberBySkill_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentNumberBySkill_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentNum", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(agentNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetAgentDetailsBySkill_result::acdapi_GetAgentDetailsBySkill_result() {
    }

    acdapi_GetAgentDetailsBySkill_result::~acdapi_GetAgentDetailsBySkill_result() {
    }

    bool acdapi_GetAgentDetailsBySkill_result::operator==(const acdapi_GetAgentDetailsBySkill_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (agentNum != rhs.agentNum) {
            return false;
        }
        if (agentInfoList != rhs.agentInfoList) {
            return false;
        }
        return true;
    }

    bool acdapi_GetAgentDetailsBySkill_result::operator!=(const acdapi_GetAgentDetailsBySkill_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetAgentDetailsBySkill_result::operator< (const acdapi_GetAgentDetailsBySkill_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(agentNum < rhs.agentNum)) {
            return false;
        }
        if (!(agentInfoList < rhs.agentInfoList)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetAgentDetailsBySkill_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetAgentDetailsBySkill_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentNum", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(agentNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentInfoList", bgcc::IDLIST, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, agentInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<AgentInfoT> ::const_iterator citr_var23;
        for (citr_var23 = agentInfoList.begin(); citr_var23 != agentInfoList.end(); ++citr_var23) {
            ret = (*citr_var23).write(proto);
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

    acdapi_GetSkillWaitingNumber_result::acdapi_GetSkillWaitingNumber_result() {
    }

    acdapi_GetSkillWaitingNumber_result::~acdapi_GetSkillWaitingNumber_result() {
    }

    bool acdapi_GetSkillWaitingNumber_result::operator==(const acdapi_GetSkillWaitingNumber_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (queueNum != rhs.queueNum) {
            return false;
        }
        if (freeNum != rhs.freeNum) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkillWaitingNumber_result::operator!=(const acdapi_GetSkillWaitingNumber_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkillWaitingNumber_result::operator< (const acdapi_GetSkillWaitingNumber_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(queueNum < rhs.queueNum)) {
            return false;
        }
        if (!(freeNum < rhs.freeNum)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkillWaitingNumber_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkillWaitingNumber_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueNum", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(queueNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("freeNum", bgcc::IDINT32, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(freeNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_GetSkillWaitingCallInfo_result::acdapi_GetSkillWaitingCallInfo_result() {
    }

    acdapi_GetSkillWaitingCallInfo_result::~acdapi_GetSkillWaitingCallInfo_result() {
    }

    bool acdapi_GetSkillWaitingCallInfo_result::operator==(const acdapi_GetSkillWaitingCallInfo_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (queueNum != rhs.queueNum) {
            return false;
        }
        if (queueInfoList != rhs.queueInfoList) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSkillWaitingCallInfo_result::operator!=(const acdapi_GetSkillWaitingCallInfo_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSkillWaitingCallInfo_result::operator< (const acdapi_GetSkillWaitingCallInfo_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(queueNum < rhs.queueNum)) {
            return false;
        }
        if (!(queueInfoList < rhs.queueInfoList)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSkillWaitingCallInfo_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSkillWaitingCallInfo_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueNum", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(queueNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueInfoList", bgcc::IDLIST, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, queueInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<QueueInfoT> ::const_iterator citr_var24;
        for (citr_var24 = queueInfoList.begin(); citr_var24 != queueInfoList.end(); ++citr_var24) {
            ret = (*citr_var24).write(proto);
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

    acdapi_GetPrivateQueue_result::acdapi_GetPrivateQueue_result() {
    }

    acdapi_GetPrivateQueue_result::~acdapi_GetPrivateQueue_result() {
    }

    bool acdapi_GetPrivateQueue_result::operator==(const acdapi_GetPrivateQueue_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (queueNum != rhs.queueNum) {
            return false;
        }
        if (queueInfoList != rhs.queueInfoList) {
            return false;
        }
        return true;
    }

    bool acdapi_GetPrivateQueue_result::operator!=(const acdapi_GetPrivateQueue_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetPrivateQueue_result::operator< (const acdapi_GetPrivateQueue_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(queueNum < rhs.queueNum)) {
            return false;
        }
        if (!(queueInfoList < rhs.queueInfoList)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetPrivateQueue_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetPrivateQueue_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueNum", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(queueNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueInfoList", bgcc::IDLIST, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeListBegin(bgcc::IDSTRUCT, queueInfoList.size());
        if (ret < 0) { return ret; }
        std::vector<QueueInfoT> ::const_iterator citr_var25;
        for (citr_var25 = queueInfoList.begin(); citr_var25 != queueInfoList.end(); ++citr_var25) {
            ret = (*citr_var25).write(proto);
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

    acdapi_GetSysInfo_result::acdapi_GetSysInfo_result() {
    }

    acdapi_GetSysInfo_result::~acdapi_GetSysInfo_result() {
    }

    bool acdapi_GetSysInfo_result::operator==(const acdapi_GetSysInfo_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (sysInfo != rhs.sysInfo) {
            return false;
        }
        return true;
    }

    bool acdapi_GetSysInfo_result::operator!=(const acdapi_GetSysInfo_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_GetSysInfo_result::operator< (const acdapi_GetSysInfo_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(sysInfo < rhs.sysInfo)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_GetSysInfo_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_GetSysInfo_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("sysInfo", bgcc::IDSTRUCT, 3);
        if (ret < 0) { return ret; }
        ret = sysInfo.write(proto);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SynchronizeCTITime_result::acdapi_SynchronizeCTITime_result() {
    }

    acdapi_SynchronizeCTITime_result::~acdapi_SynchronizeCTITime_result() {
    }

    bool acdapi_SynchronizeCTITime_result::operator==(const acdapi_SynchronizeCTITime_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        if (timestamp != rhs.timestamp) {
            return false;
        }
        return true;
    }

    bool acdapi_SynchronizeCTITime_result::operator!=(const acdapi_SynchronizeCTITime_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_SynchronizeCTITime_result::operator< (const acdapi_SynchronizeCTITime_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        if (!(timestamp < rhs.timestamp)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_SynchronizeCTITime_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_SynchronizeCTITime_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timestamp", bgcc::IDINT64, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(timestamp);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_Heartbeat_result::acdapi_Heartbeat_result() {
    }

    acdapi_Heartbeat_result::~acdapi_Heartbeat_result() {
    }

    bool acdapi_Heartbeat_result::operator==(const acdapi_Heartbeat_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_Heartbeat_result::operator!=(const acdapi_Heartbeat_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_Heartbeat_result::operator< (const acdapi_Heartbeat_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_Heartbeat_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_Heartbeat_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_ResetConfig_result::acdapi_ResetConfig_result() {
    }

    acdapi_ResetConfig_result::~acdapi_ResetConfig_result() {
    }

    bool acdapi_ResetConfig_result::operator==(const acdapi_ResetConfig_result& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (return_value != rhs.return_value) {
            return false;
        }
        return true;
    }

    bool acdapi_ResetConfig_result::operator!=(const acdapi_ResetConfig_result& rhs) const {
        return !(*this == rhs);
    }

    bool acdapi_ResetConfig_result::operator< (const acdapi_ResetConfig_result& rhs) const {
        if (this == &rhs) {
            return false;
        }
        if (!(return_value < rhs.return_value)) {
            return false;
        }
        return true;
    }

    int32_t acdapi_ResetConfig_result::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;
        ret = proto->writeStructBegin("acdapi_ResetConfig_result");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("return_value", bgcc::IDINT32, 0);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(return_value.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    acdapi_SignIn_presult::~acdapi_SignIn_presult() {
    }

    int32_t acdapi_SignIn_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var26;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var26);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var26;
                break;
            case 8:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, (*(handle)));
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

    acdapi_SignOut_presult::~acdapi_SignOut_presult() {
    }

    int32_t acdapi_SignOut_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var27;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var27);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var27;
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

    acdapi_SetAgentStatus_presult::~acdapi_SetAgentStatus_presult() {
    }

    int32_t acdapi_SetAgentStatus_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var28;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var28);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var28;
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

    acdapi_GetAgentStatus_presult::~acdapi_GetAgentStatus_presult() {
    }

    int32_t acdapi_GetAgentStatus_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var29;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var29);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var29;
                break;
            case 3:
                int32_t ele_var30;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var30);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(agentStatus)) = ele_var30;
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

    acdapi_ResetStatuschangetype_presult::~acdapi_ResetStatuschangetype_presult() {
    }

    int32_t acdapi_ResetStatuschangetype_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var31;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var31);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var31;
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

    acdapi_ResetAutoAnswer_presult::~acdapi_ResetAutoAnswer_presult() {
    }

    int32_t acdapi_ResetAutoAnswer_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var32;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var32);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var32;
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

    acdapi_ResetSkill_presult::~acdapi_ResetSkill_presult() {
    }

    int32_t acdapi_ResetSkill_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var33;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var33);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var33;
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

    acdapi_Reset_presult::~acdapi_Reset_presult() {
    }

    int32_t acdapi_Reset_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var34;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var34);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var34;
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

    acdapi_OutboundCall_presult::~acdapi_OutboundCall_presult() {
    }

    int32_t acdapi_OutboundCall_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var35;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var35);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var35;
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

    acdapi_AnswerCall_presult::~acdapi_AnswerCall_presult() {
    }

    int32_t acdapi_AnswerCall_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var36;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var36);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var36;
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

    acdapi_ReleaseCall_presult::~acdapi_ReleaseCall_presult() {
    }

    int32_t acdapi_ReleaseCall_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var37;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var37);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var37;
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

    acdapi_Hold_presult::~acdapi_Hold_presult() {
    }

    int32_t acdapi_Hold_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var38;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var38);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var38;
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

    acdapi_Retrieve_presult::~acdapi_Retrieve_presult() {
    }

    int32_t acdapi_Retrieve_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var39;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var39);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var39;
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

    acdapi_Consult_presult::~acdapi_Consult_presult() {
    }

    int32_t acdapi_Consult_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var40;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var40);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var40;
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

    acdapi_ConsultReconnect_presult::~acdapi_ConsultReconnect_presult() {
    }

    int32_t acdapi_ConsultReconnect_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var41;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var41);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var41;
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

    acdapi_ConsultTransfer_presult::~acdapi_ConsultTransfer_presult() {
    }

    int32_t acdapi_ConsultTransfer_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var42;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var42);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var42;
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

    acdapi_SingleStepTransfer_presult::~acdapi_SingleStepTransfer_presult() {
    }

    int32_t acdapi_SingleStepTransfer_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var43;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var43);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var43;
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

    acdapi_ConsultConference_presult::~acdapi_ConsultConference_presult() {
    }

    int32_t acdapi_ConsultConference_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var44;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var44);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var44;
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

    acdapi_ConferenceJoin_presult::~acdapi_ConferenceJoin_presult() {
    }

    int32_t acdapi_ConferenceJoin_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var45;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var45);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var45;
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

    acdapi_SetAssociateData_presult::~acdapi_SetAssociateData_presult() {
    }

    int32_t acdapi_SetAssociateData_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var46;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var46);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var46;
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

    acdapi_GetAssociateData_presult::~acdapi_GetAssociateData_presult() {
    }

    int32_t acdapi_GetAssociateData_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var47;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var47);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var47;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, (*(value)));
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

    acdapi_JumptheQueue_presult::~acdapi_JumptheQueue_presult() {
    }

    int32_t acdapi_JumptheQueue_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var48;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var48);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var48;
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

    acdapi_ForceSignIn_presult::~acdapi_ForceSignIn_presult() {
    }

    int32_t acdapi_ForceSignIn_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var49;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var49);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var49;
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

    acdapi_ForceSignOut_presult::~acdapi_ForceSignOut_presult() {
    }

    int32_t acdapi_ForceSignOut_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var50;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var50);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var50;
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

    acdapi_ForceSetAgentStatus_presult::~acdapi_ForceSetAgentStatus_presult() {
    }

    int32_t acdapi_ForceSetAgentStatus_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var51;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var51);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var51;
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

    acdapi_Listen_presult::~acdapi_Listen_presult() {
    }

    int32_t acdapi_Listen_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var52;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var52);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var52;
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

    acdapi_StopListen_presult::~acdapi_StopListen_presult() {
    }

    int32_t acdapi_StopListen_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var53;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var53);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var53;
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

    acdapi_Insert_presult::~acdapi_Insert_presult() {
    }

    int32_t acdapi_Insert_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var54;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var54);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var54;
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

    acdapi_StopInsert_presult::~acdapi_StopInsert_presult() {
    }

    int32_t acdapi_StopInsert_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var55;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var55);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var55;
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

    acdapi_SwitchInsertorListen_presult::~acdapi_SwitchInsertorListen_presult() {
    }

    int32_t acdapi_SwitchInsertorListen_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var56;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var56);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var56;
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

    acdapi_Break_presult::~acdapi_Break_presult() {
    }

    int32_t acdapi_Break_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var57;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var57);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var57;
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

    acdapi_SendDTMF_presult::~acdapi_SendDTMF_presult() {
    }

    int32_t acdapi_SendDTMF_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var58;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var58);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var58;
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

    acdapi_StartPlay_presult::~acdapi_StartPlay_presult() {
    }

    int32_t acdapi_StartPlay_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var59;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var59);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var59;
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

    acdapi_StopPlay_presult::~acdapi_StopPlay_presult() {
    }

    int32_t acdapi_StopPlay_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var60;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var60);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var60;
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

    acdapi_MuteOn_presult::~acdapi_MuteOn_presult() {
    }

    int32_t acdapi_MuteOn_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var61;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var61);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var61;
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

    acdapi_MuteOff_presult::~acdapi_MuteOff_presult() {
    }

    int32_t acdapi_MuteOff_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var62;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var62);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var62;
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

    acdapi_GetAgentDetailByAgentID_presult::~acdapi_GetAgentDetailByAgentID_presult() {
    }

    int32_t acdapi_GetAgentDetailByAgentID_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var63;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var63);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var63;
                break;
            case 4:
                ret = (*(agentInfo)).read(OFFSET_PTR(request, nread), request_len - nread, proto);
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

    acdapi_GetAgentDetailByAgentDN_presult::~acdapi_GetAgentDetailByAgentDN_presult() {
    }

    int32_t acdapi_GetAgentDetailByAgentDN_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var64;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var64);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var64;
                break;
            case 4:
                ret = (*(agentInfo)).read(OFFSET_PTR(request, nread), request_len - nread, proto);
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

    acdapi_GetAgentDetailsByAgentIDs_presult::~acdapi_GetAgentDetailsByAgentIDs_presult() {
    }

    int32_t acdapi_GetAgentDetailsByAgentIDs_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var65;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var65);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var65;
                break;
            case 4:
                (*(agentInfoList)).clear();

                int32_t size_var66;
                bgcc::DataTypeID etype_var67;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var67, size_var66);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(agentInfoList)).reserve(size_var66);
                for(int32_t i = 0; i < size_var66; ++i) {
                    AgentInfoT value_var68;
                    ret = value_var68.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(agentInfoList)).push_back(value_var68);
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

    acdapi_GetAgentDetailsByAgentDNs_presult::~acdapi_GetAgentDetailsByAgentDNs_presult() {
    }

    int32_t acdapi_GetAgentDetailsByAgentDNs_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var69;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var69);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var69;
                break;
            case 4:
                (*(agentInfoList)).clear();

                int32_t size_var70;
                bgcc::DataTypeID etype_var71;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var71, size_var70);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(agentInfoList)).reserve(size_var70);
                for(int32_t i = 0; i < size_var70; ++i) {
                    AgentInfoT value_var72;
                    ret = value_var72.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(agentInfoList)).push_back(value_var72);
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

    acdapi_GetRecordFileName_presult::~acdapi_GetRecordFileName_presult() {
    }

    int32_t acdapi_GetRecordFileName_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var73;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var73);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var73;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, (*(filename)));
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

    acdapi_GetSkill_presult::~acdapi_GetSkill_presult() {
    }

    int32_t acdapi_GetSkill_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var74;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var74);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var74;
                break;
            case 3:
                (*(skill)).clear();

                int32_t size_var75;
                bgcc::DataTypeID etype_var76;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var76, size_var75);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(skill)).reserve(size_var75);
                for(int32_t i = 0; i < size_var75; ++i) {
                    std::string value_var77;
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, value_var77);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(skill)).push_back(value_var77);
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

    acdapi_GetRestReason_presult::~acdapi_GetRestReason_presult() {
    }

    int32_t acdapi_GetRestReason_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var78;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var78);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var78;
                break;
            case 3:
                (*(restReason)).clear();

                int32_t size_var79;
                bgcc::DataTypeID etype_var80;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var80, size_var79);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(restReason)).reserve(size_var79);
                for(int32_t i = 0; i < size_var79; ++i) {
                    std::string value_var81;
                    ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, value_var81);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(restReason)).push_back(value_var81);
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

    acdapi_GetAgentNumberBySkill_presult::~acdapi_GetAgentNumberBySkill_presult() {
    }

    int32_t acdapi_GetAgentNumberBySkill_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var82;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var82);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var82;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(agentNum)));
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

    acdapi_GetAgentDetailsBySkill_presult::~acdapi_GetAgentDetailsBySkill_presult() {
    }

    int32_t acdapi_GetAgentDetailsBySkill_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var83;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var83);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var83;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(agentNum)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                (*(agentInfoList)).clear();

                int32_t size_var84;
                bgcc::DataTypeID etype_var85;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var85, size_var84);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(agentInfoList)).reserve(size_var84);
                for(int32_t i = 0; i < size_var84; ++i) {
                    AgentInfoT value_var86;
                    ret = value_var86.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(agentInfoList)).push_back(value_var86);
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

    acdapi_GetSkillWaitingNumber_presult::~acdapi_GetSkillWaitingNumber_presult() {
    }

    int32_t acdapi_GetSkillWaitingNumber_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var87;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var87);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var87;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(queueNum)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(freeNum)));
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

    acdapi_GetSkillWaitingCallInfo_presult::~acdapi_GetSkillWaitingCallInfo_presult() {
    }

    int32_t acdapi_GetSkillWaitingCallInfo_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var88;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var88);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var88;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(queueNum)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                (*(queueInfoList)).clear();

                int32_t size_var89;
                bgcc::DataTypeID etype_var90;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var90, size_var89);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(queueInfoList)).reserve(size_var89);
                for(int32_t i = 0; i < size_var89; ++i) {
                    QueueInfoT value_var91;
                    ret = value_var91.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(queueInfoList)).push_back(value_var91);
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

    acdapi_GetPrivateQueue_presult::~acdapi_GetPrivateQueue_presult() {
    }

    int32_t acdapi_GetPrivateQueue_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var92;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var92);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var92;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, (*(queueNum)));
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                (*(queueInfoList)).clear();

                int32_t size_var93;
                bgcc::DataTypeID etype_var94;

                ret = proto->readListBegin(OFFSET_PTR(request, nread), request_len - nread, etype_var94, size_var93);
                if (ret < 0) { return ret; }
                nread += ret;

                (*(queueInfoList)).reserve(size_var93);
                for(int32_t i = 0; i < size_var93; ++i) {
                    QueueInfoT value_var95;
                    ret = value_var95.read(OFFSET_PTR(request, nread), request_len - nread, proto);
                    if (ret < 0) { return ret; }
                    nread += ret;
                    (*(queueInfoList)).push_back(value_var95);
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

    acdapi_GetSysInfo_presult::~acdapi_GetSysInfo_presult() {
    }

    int32_t acdapi_GetSysInfo_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var96;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var96);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var96;
                break;
            case 3:
                ret = (*(sysInfo)).read(OFFSET_PTR(request, nread), request_len - nread, proto);
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

    acdapi_SynchronizeCTITime_presult::~acdapi_SynchronizeCTITime_presult() {
    }

    int32_t acdapi_SynchronizeCTITime_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var97;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var97);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var97;
                break;
            case 3:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, (*(timestamp)));
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

    acdapi_Heartbeat_presult::~acdapi_Heartbeat_presult() {
    }

    int32_t acdapi_Heartbeat_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var98;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var98);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var98;
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

    acdapi_ResetConfig_presult::~acdapi_ResetConfig_presult() {
    }

    int32_t acdapi_ResetConfig_presult::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const {
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
                int32_t ele_var99;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var99);
                if (ret < 0) { return ret; }
                nread += ret;
                (*(return_value)) = ele_var99;
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

    acdapiProxy::acdapiProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
    }

    acdapiProxy::acdapiProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::BaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
    }

    acdapiProxy::acdapiProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::BaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    AcdResultT acdapiProxy::SignIn(const std::string& agentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const std::string& skill, int64_t& handle, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SignIn(agentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SignIn(handle, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SignIn(const std::string& agentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, const bool& autoAnswer, const bool& fcSignin, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SignIn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SignIn_pargs pargs;
        pargs.agentId = &agentId;
        pargs.agentDn = &agentDn;
        pargs.agentPwd = &agentPwd;
        pargs.statusChangetype = &statusChangetype;
        pargs.autoAnswer = &autoAnswer;
        pargs.fcSignin = &fcSignin;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SignIn(int64_t& handle, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SignIn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SignIn"){
            presult.return_value = &ret_val;
            presult.handle = &handle;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::SignOut(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SignOut(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SignOut(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SignOut(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SignOut", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SignOut_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SignOut(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SignOut_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SignOut"){
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

    AcdResultT acdapiProxy::SetAgentStatus(int64_t handle, const std::string& agentId, const AgentStatusT& agentStatus, const std::string& restReason, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SetAgentStatus(handle, agentId, agentStatus, restReason, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SetAgentStatus(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SetAgentStatus(const int64_t& handle, const std::string& agentId, const AgentStatusT& agentStatus, const std::string& restReason, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.agentStatus = &agentStatus;
        pargs.restReason = &restReason;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SetAgentStatus(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SetAgentStatus"){
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

    AcdResultT acdapiProxy::GetAgentStatus(int64_t handle, const std::string& agentId, AgentStatusT& agentStatus, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentStatus(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentStatus(agentStatus, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentStatus(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentStatus(AgentStatusT& agentStatus, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentStatus"){
            presult.return_value = &ret_val;
            presult.agentStatus = &agentStatus;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::ResetStatuschangetype(int64_t handle, const std::string& agentId, const StatusChangeT& statusChangetype, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetStatuschangetype(handle, agentId, statusChangetype, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetStatuschangetype(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ResetStatuschangetype(const int64_t& handle, const std::string& agentId, const StatusChangeT& statusChangetype, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetStatuschangetype", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetStatuschangetype_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.statusChangetype = &statusChangetype;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ResetStatuschangetype(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetStatuschangetype_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetStatuschangetype"){
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

    AcdResultT acdapiProxy::ResetAutoAnswer(int64_t handle, const std::string& agentId, bool autoAnswer, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetAutoAnswer(handle, agentId, autoAnswer, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetAutoAnswer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ResetAutoAnswer(const int64_t& handle, const std::string& agentId, const bool& autoAnswer, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetAutoAnswer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetAutoAnswer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.autoAnswer = &autoAnswer;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ResetAutoAnswer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetAutoAnswer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetAutoAnswer"){
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

    AcdResultT acdapiProxy::ResetSkill(int64_t handle, const std::string& agentId, const std::string& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetSkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetSkill(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ResetSkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetSkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetSkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ResetSkill(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetSkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetSkill"){
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

    AcdResultT acdapiProxy::Reset(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Reset(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Reset(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Reset(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Reset", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Reset_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Reset(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Reset_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Reset"){
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

    AcdResultT acdapiProxy::OutboundCall(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t timeout, const CallModeT& callMode, const CallTypeT& callType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_OutboundCall(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, timeout, callMode, callType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_OutboundCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_OutboundCall(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const int32_t& timeout, const CallModeT& callMode, const CallTypeT& callType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "OutboundCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_OutboundCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.timeout = &timeout;
        pargs.callMode = &callMode;
        pargs.callType = &callType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_OutboundCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_OutboundCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="OutboundCall"){
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

    AcdResultT acdapiProxy::AnswerCall(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_AnswerCall(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_AnswerCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_AnswerCall(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "AnswerCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_AnswerCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_AnswerCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_AnswerCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="AnswerCall"){
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

    AcdResultT acdapiProxy::ReleaseCall(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ReleaseCall(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ReleaseCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ReleaseCall(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ReleaseCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ReleaseCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ReleaseCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ReleaseCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ReleaseCall"){
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

    AcdResultT acdapiProxy::Hold(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Hold(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Hold(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Hold(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Hold", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Hold_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Hold(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Hold_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Hold"){
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

    AcdResultT acdapiProxy::Retrieve(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Retrieve(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Retrieve(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Retrieve(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Retrieve", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Retrieve_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Retrieve(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Retrieve_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Retrieve"){
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

    AcdResultT acdapiProxy::Consult(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const CallTypeT& callType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Consult(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, callType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Consult(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Consult(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const CallTypeT& callType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Consult", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Consult_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.callType = &callType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Consult(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Consult_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Consult"){
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

    AcdResultT acdapiProxy::ConsultReconnect(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultReconnect(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultReconnect(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ConsultReconnect(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultReconnect", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultReconnect_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ConsultReconnect(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultReconnect_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultReconnect"){
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

    AcdResultT acdapiProxy::ConsultTransfer(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultTransfer(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultTransfer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ConsultTransfer(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultTransfer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultTransfer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ConsultTransfer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultTransfer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultTransfer"){
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

    AcdResultT acdapiProxy::SingleStepTransfer(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool isPassthrough, const CallTypeT& transferType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SingleStepTransfer(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, isPassthrough, transferType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SingleStepTransfer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SingleStepTransfer(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const bool& isPassthrough, const CallTypeT& transferType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SingleStepTransfer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SingleStepTransfer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.isPassthrough = &isPassthrough;
        pargs.transferType = &transferType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SingleStepTransfer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SingleStepTransfer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SingleStepTransfer"){
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

    AcdResultT acdapiProxy::ConsultConference(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultConference(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultConference(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ConsultConference(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultConference", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultConference_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ConsultConference(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultConference_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultConference"){
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

    AcdResultT acdapiProxy::ConferenceJoin(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const ConferenceT& conferenceType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConferenceJoin(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, conferenceType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConferenceJoin(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ConferenceJoin(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const ConferenceT& conferenceType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConferenceJoin", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConferenceJoin_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.conferenceType = &conferenceType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ConferenceJoin(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConferenceJoin_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConferenceJoin"){
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

    AcdResultT acdapiProxy::SetAssociateData(int64_t handle, const std::string& agentId, const std::string& key, const std::string& value, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SetAssociateData(handle, agentId, key, value, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SetAssociateData(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SetAssociateData(const int64_t& handle, const std::string& agentId, const std::string& key, const std::string& value, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SetAssociateData", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SetAssociateData_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.key = &key;
        pargs.value = &value;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SetAssociateData(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SetAssociateData_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SetAssociateData"){
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

    AcdResultT acdapiProxy::GetAssociateData(int64_t handle, const std::string& agentId, const std::string& key, std::string& value, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAssociateData(handle, agentId, key, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAssociateData(value, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAssociateData(const int64_t& handle, const std::string& agentId, const std::string& key, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAssociateData", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAssociateData_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.key = &key;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAssociateData(std::string& value, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAssociateData_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAssociateData"){
            presult.return_value = &ret_val;
            presult.value = &value;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_JumptheQueue(handle, agentId, requestId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_JumptheQueue(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_JumptheQueue(const int64_t& handle, const std::string& agentId, const int64_t& requestId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "JumptheQueue", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_JumptheQueue_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.requestId = &requestId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_JumptheQueue(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_JumptheQueue_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="JumptheQueue"){
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

    AcdResultT acdapiProxy::ForceSignIn(int64_t handle, const std::string& agentId, const std::string& destAgentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const std::string& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSignIn(handle, agentId, destAgentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSignIn(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ForceSignIn(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, const bool& autoAnswer, const bool& fcSignin, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSignIn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSignIn_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        pargs.agentDn = &agentDn;
        pargs.agentPwd = &agentPwd;
        pargs.statusChangetype = &statusChangetype;
        pargs.autoAnswer = &autoAnswer;
        pargs.fcSignin = &fcSignin;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ForceSignIn(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSignIn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSignIn"){
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

    AcdResultT acdapiProxy::ForceSignOut(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSignOut(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSignOut(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ForceSignOut(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSignOut", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSignOut_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ForceSignOut(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSignOut_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSignOut"){
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

    AcdResultT acdapiProxy::ForceSetAgentStatus(int64_t handle, const std::string& agentId, const std::string& destAgentId, const AgentStatusT& agentStatus, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSetAgentStatus(handle, agentId, destAgentId, agentStatus, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSetAgentStatus(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ForceSetAgentStatus(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, const AgentStatusT& agentStatus, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        pargs.agentStatus = &agentStatus;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ForceSetAgentStatus(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSetAgentStatus"){
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

    AcdResultT acdapiProxy::Listen(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Listen(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Listen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Listen(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Listen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Listen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Listen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Listen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Listen"){
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

    AcdResultT acdapiProxy::StopListen(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopListen(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopListen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_StopListen(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopListen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopListen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_StopListen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopListen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopListen"){
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

    AcdResultT acdapiProxy::Insert(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Insert(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Insert(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Insert(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Insert", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Insert_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Insert(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Insert_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Insert"){
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

    AcdResultT acdapiProxy::StopInsert(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopInsert(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopInsert(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_StopInsert(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopInsert", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopInsert_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_StopInsert(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopInsert_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopInsert"){
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

    AcdResultT acdapiProxy::SwitchInsertorListen(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SwitchInsertorListen(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SwitchInsertorListen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SwitchInsertorListen(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SwitchInsertorListen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SwitchInsertorListen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SwitchInsertorListen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SwitchInsertorListen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SwitchInsertorListen"){
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

    AcdResultT acdapiProxy::Break(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Break(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Break(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Break(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Break", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Break_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Break(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Break_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Break"){
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

    AcdResultT acdapiProxy::SendDTMF(int64_t handle, const std::string& agentId, const std::string& digitals, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendDTMF(handle, agentId, digitals, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SendDTMF(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SendDTMF(const int64_t& handle, const std::string& agentId, const std::string& digitals, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendDTMF", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SendDTMF_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.digitals = &digitals;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SendDTMF(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SendDTMF_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendDTMF"){
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

    AcdResultT acdapiProxy::StartPlay(int64_t handle, const std::string& agentId, const std::string& filename, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StartPlay(handle, agentId, filename, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StartPlay(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_StartPlay(const int64_t& handle, const std::string& agentId, const std::string& filename, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StartPlay", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StartPlay_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.filename = &filename;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_StartPlay(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StartPlay_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StartPlay"){
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

    AcdResultT acdapiProxy::StopPlay(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopPlay(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopPlay(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_StopPlay(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopPlay", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopPlay_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_StopPlay(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopPlay_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopPlay"){
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

    AcdResultT acdapiProxy::MuteOn(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_MuteOn(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_MuteOn(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_MuteOn(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "MuteOn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_MuteOn_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_MuteOn(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_MuteOn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="MuteOn"){
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

    AcdResultT acdapiProxy::MuteOff(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_MuteOff(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_MuteOff(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_MuteOff(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "MuteOff", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_MuteOff_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_MuteOff(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_MuteOff_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="MuteOff"){
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

    AcdResultT acdapiProxy::GetAgentDetailByAgentID(int64_t handle, const std::string& agentId, const std::string& destAgentId, AgentInfoT& agentInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailByAgentID(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailByAgentID(agentInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentDetailByAgentID(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailByAgentID", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailByAgentID_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentDetailByAgentID(AgentInfoT& agentInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailByAgentID_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailByAgentID"){
            presult.return_value = &ret_val;
            presult.agentInfo = &agentInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetAgentDetailByAgentDN(int64_t handle, const std::string& agentId, const std::string& destAgentDn, AgentInfoT& agentInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailByAgentDN(handle, agentId, destAgentDn, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailByAgentDN(agentInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentDetailByAgentDN(const int64_t& handle, const std::string& agentId, const std::string& destAgentDn, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailByAgentDN", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailByAgentDN_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentDn = &destAgentDn;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentDetailByAgentDN(AgentInfoT& agentInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailByAgentDN_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailByAgentDN"){
            presult.return_value = &ret_val;
            presult.agentInfo = &agentInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetAgentDetailsByAgentIDs(int64_t handle, const std::string& agentId, const StringListT& destAgentIdList, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsByAgentIDs(handle, agentId, destAgentIdList, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsByAgentIDs(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentDetailsByAgentIDs(const int64_t& handle, const std::string& agentId, const StringListT& destAgentIdList, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsByAgentIDs", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsByAgentIDs_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentIdList = &destAgentIdList;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentDetailsByAgentIDs(AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsByAgentIDs_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsByAgentIDs"){
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

    AcdResultT acdapiProxy::GetAgentDetailsByAgentDNs(int64_t handle, const std::string& agentId, const StringListT& destAgentDnList, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsByAgentDNs(handle, agentId, destAgentDnList, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsByAgentDNs(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentDetailsByAgentDNs(const int64_t& handle, const std::string& agentId, const StringListT& destAgentDnList, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsByAgentDNs", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsByAgentDNs_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentDnList = &destAgentDnList;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentDetailsByAgentDNs(AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsByAgentDNs_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsByAgentDNs"){
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

    AcdResultT acdapiProxy::GetRecordFileName(int64_t handle, const std::string& agentId, std::string& filename, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetRecordFileName(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetRecordFileName(filename, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetRecordFileName(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetRecordFileName", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetRecordFileName_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetRecordFileName(std::string& filename, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetRecordFileName_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetRecordFileName"){
            presult.return_value = &ret_val;
            presult.filename = &filename;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetSkill(int64_t handle, const std::string& agentId, StringListT& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkill(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkill(skill, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetSkill(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetSkill(StringListT& skill, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkill"){
            presult.return_value = &ret_val;
            presult.skill = &skill;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetRestReason(int64_t handle, const std::string& agentId, StringListT& restReason, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetRestReason(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetRestReason(restReason, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetRestReason(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetRestReason", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetRestReason_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetRestReason(StringListT& restReason, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetRestReason_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetRestReason"){
            presult.return_value = &ret_val;
            presult.restReason = &restReason;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetAgentNumberBySkill(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& agentNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentNumberBySkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentNumberBySkill(agentNum, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentNumberBySkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentNumberBySkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentNumberBySkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentNumberBySkill(int32_t& agentNum, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentNumberBySkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentNumberBySkill"){
            presult.return_value = &ret_val;
            presult.agentNum = &agentNum;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetAgentDetailsBySkill(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& agentNum, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsBySkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsBySkill(agentNum, agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetAgentDetailsBySkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsBySkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsBySkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetAgentDetailsBySkill(int32_t& agentNum, AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsBySkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsBySkill"){
            presult.return_value = &ret_val;
            presult.agentNum = &agentNum;
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

    AcdResultT acdapiProxy::GetSkillWaitingNumber(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& queueNum, int32_t& freeNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkillWaitingNumber(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkillWaitingNumber(queueNum, freeNum, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetSkillWaitingNumber(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkillWaitingNumber", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkillWaitingNumber_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetSkillWaitingNumber(int32_t& queueNum, int32_t& freeNum, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkillWaitingNumber_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkillWaitingNumber"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.freeNum = &freeNum;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetSkillWaitingCallInfo(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& queueNum, QueueInfoListT& queueInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkillWaitingCallInfo(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkillWaitingCallInfo(queueNum, queueInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetSkillWaitingCallInfo(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkillWaitingCallInfo", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkillWaitingCallInfo_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetSkillWaitingCallInfo(int32_t& queueNum, QueueInfoListT& queueInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkillWaitingCallInfo_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkillWaitingCallInfo"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.queueInfoList = &queueInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetPrivateQueue(int64_t handle, const std::string& agentId, const std::string& destAgentId, int32_t& queueNum, QueueInfoListT& queueInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetPrivateQueue(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetPrivateQueue(queueNum, queueInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetPrivateQueue(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetPrivateQueue", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetPrivateQueue_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetPrivateQueue(int32_t& queueNum, QueueInfoListT& queueInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetPrivateQueue_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetPrivateQueue"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.queueInfoList = &queueInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::GetSysInfo(int64_t handle, const std::string& agentId, SysInfoT& sysInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSysInfo(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSysInfo(sysInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_GetSysInfo(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSysInfo", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSysInfo_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_GetSysInfo(SysInfoT& sysInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSysInfo_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSysInfo"){
            presult.return_value = &ret_val;
            presult.sysInfo = &sysInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::SynchronizeCTITime(int64_t handle, const std::string& agentId, int64_t& timestamp, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SynchronizeCTITime(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SynchronizeCTITime(timestamp, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_SynchronizeCTITime(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SynchronizeCTITime", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SynchronizeCTITime_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_SynchronizeCTITime(int64_t& timestamp, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SynchronizeCTITime_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SynchronizeCTITime"){
            presult.return_value = &ret_val;
            presult.timestamp = &timestamp;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT acdapiProxy::Heartbeat(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Heartbeat(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Heartbeat(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_Heartbeat(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Heartbeat", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Heartbeat_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_Heartbeat(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Heartbeat_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Heartbeat"){
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

    AcdResultT acdapiProxy::ResetConfig(const std::string& password, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetConfig(password, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetConfig(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void acdapiProxy::send_ResetConfig(const std::string& password, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetConfig", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetConfig_pargs pargs;
        pargs.password = &password;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT acdapiProxy::recv_ResetConfig(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetConfig_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetConfig"){
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

    SSLacdapiProxy::SSLacdapiProxy(
        bgcc::ServerInfo serverinfo,
        int32_t maxConn,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, maxConn, true, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
    }

    SSLacdapiProxy::SSLacdapiProxy(
        bgcc::ServerInfo serverinfo,
        bgcc::ServiceManager* mgr,
        int32_t tryCount,
        int32_t tryInterval) :
        bgcc::SSLBaseProxy(serverinfo, 1, false, mgr, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
    }

    SSLacdapiProxy::SSLacdapiProxy(const std::string& proxy_name, int32_t tryCount, int32_t tryInterval) :
        bgcc::SSLBaseProxy(bgcc::ServerInfo("", 0), 0, true, NULL, tryCount, tryInterval){
            _whoami = "global.acd.acdapi";
            _use_existing_socket  = true;
            _name=proxy_name;
    }

    AcdResultT SSLacdapiProxy::SignIn(const std::string& agentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const std::string& skill, int64_t& handle, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SignIn(agentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SignIn(handle, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SignIn(const std::string& agentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, const bool& autoAnswer, const bool& fcSignin, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SignIn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SignIn_pargs pargs;
        pargs.agentId = &agentId;
        pargs.agentDn = &agentDn;
        pargs.agentPwd = &agentPwd;
        pargs.statusChangetype = &statusChangetype;
        pargs.autoAnswer = &autoAnswer;
        pargs.fcSignin = &fcSignin;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SignIn(int64_t& handle, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SignIn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SignIn"){
            presult.return_value = &ret_val;
            presult.handle = &handle;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::SignOut(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SignOut(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SignOut(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SignOut(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SignOut", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SignOut_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SignOut(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SignOut_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SignOut"){
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

    AcdResultT SSLacdapiProxy::SetAgentStatus(int64_t handle, const std::string& agentId, const AgentStatusT& agentStatus, const std::string& restReason, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SetAgentStatus(handle, agentId, agentStatus, restReason, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SetAgentStatus(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SetAgentStatus(const int64_t& handle, const std::string& agentId, const AgentStatusT& agentStatus, const std::string& restReason, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.agentStatus = &agentStatus;
        pargs.restReason = &restReason;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SetAgentStatus(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SetAgentStatus"){
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

    AcdResultT SSLacdapiProxy::GetAgentStatus(int64_t handle, const std::string& agentId, AgentStatusT& agentStatus, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentStatus(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentStatus(agentStatus, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentStatus(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentStatus(AgentStatusT& agentStatus, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentStatus"){
            presult.return_value = &ret_val;
            presult.agentStatus = &agentStatus;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::ResetStatuschangetype(int64_t handle, const std::string& agentId, const StatusChangeT& statusChangetype, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetStatuschangetype(handle, agentId, statusChangetype, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetStatuschangetype(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ResetStatuschangetype(const int64_t& handle, const std::string& agentId, const StatusChangeT& statusChangetype, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetStatuschangetype", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetStatuschangetype_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.statusChangetype = &statusChangetype;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ResetStatuschangetype(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetStatuschangetype_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetStatuschangetype"){
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

    AcdResultT SSLacdapiProxy::ResetAutoAnswer(int64_t handle, const std::string& agentId, bool autoAnswer, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetAutoAnswer(handle, agentId, autoAnswer, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetAutoAnswer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ResetAutoAnswer(const int64_t& handle, const std::string& agentId, const bool& autoAnswer, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetAutoAnswer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetAutoAnswer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.autoAnswer = &autoAnswer;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ResetAutoAnswer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetAutoAnswer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetAutoAnswer"){
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

    AcdResultT SSLacdapiProxy::ResetSkill(int64_t handle, const std::string& agentId, const std::string& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetSkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetSkill(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ResetSkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetSkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetSkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ResetSkill(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetSkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetSkill"){
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

    AcdResultT SSLacdapiProxy::Reset(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Reset(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Reset(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Reset(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Reset", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Reset_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Reset(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Reset_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Reset"){
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

    AcdResultT SSLacdapiProxy::OutboundCall(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t timeout, const CallModeT& callMode, const CallTypeT& callType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_OutboundCall(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, timeout, callMode, callType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_OutboundCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_OutboundCall(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const int32_t& timeout, const CallModeT& callMode, const CallTypeT& callType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "OutboundCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_OutboundCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.timeout = &timeout;
        pargs.callMode = &callMode;
        pargs.callType = &callType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_OutboundCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_OutboundCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="OutboundCall"){
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

    AcdResultT SSLacdapiProxy::AnswerCall(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_AnswerCall(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_AnswerCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_AnswerCall(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "AnswerCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_AnswerCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_AnswerCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_AnswerCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="AnswerCall"){
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

    AcdResultT SSLacdapiProxy::ReleaseCall(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ReleaseCall(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ReleaseCall(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ReleaseCall(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ReleaseCall", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ReleaseCall_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ReleaseCall(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ReleaseCall_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ReleaseCall"){
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

    AcdResultT SSLacdapiProxy::Hold(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Hold(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Hold(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Hold(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Hold", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Hold_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Hold(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Hold_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Hold"){
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

    AcdResultT SSLacdapiProxy::Retrieve(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Retrieve(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Retrieve(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Retrieve(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Retrieve", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Retrieve_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Retrieve(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Retrieve_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Retrieve"){
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

    AcdResultT SSLacdapiProxy::Consult(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const CallTypeT& callType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Consult(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, callType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Consult(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Consult(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const CallTypeT& callType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Consult", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Consult_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.callType = &callType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Consult(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Consult_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Consult"){
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

    AcdResultT SSLacdapiProxy::ConsultReconnect(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultReconnect(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultReconnect(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ConsultReconnect(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultReconnect", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultReconnect_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ConsultReconnect(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultReconnect_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultReconnect"){
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

    AcdResultT SSLacdapiProxy::ConsultTransfer(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultTransfer(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultTransfer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ConsultTransfer(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultTransfer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultTransfer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ConsultTransfer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultTransfer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultTransfer"){
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

    AcdResultT SSLacdapiProxy::SingleStepTransfer(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool isPassthrough, const CallTypeT& transferType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SingleStepTransfer(handle, agentId, callerId, destId, forCallerDispNum, forCalleeDispNum, isPassthrough, transferType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SingleStepTransfer(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SingleStepTransfer(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const bool& isPassthrough, const CallTypeT& transferType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SingleStepTransfer", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SingleStepTransfer_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destId = &destId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.isPassthrough = &isPassthrough;
        pargs.transferType = &transferType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SingleStepTransfer(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SingleStepTransfer_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SingleStepTransfer"){
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

    AcdResultT SSLacdapiProxy::ConsultConference(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConsultConference(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConsultConference(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ConsultConference(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConsultConference", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConsultConference_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ConsultConference(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConsultConference_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConsultConference"){
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

    AcdResultT SSLacdapiProxy::ConferenceJoin(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const ConferenceT& conferenceType, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ConferenceJoin(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, conferenceType, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ConferenceJoin(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ConferenceJoin(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, const ConferenceT& conferenceType, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ConferenceJoin", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ConferenceJoin_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        pargs.conferenceType = &conferenceType;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ConferenceJoin(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ConferenceJoin_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ConferenceJoin"){
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

    AcdResultT SSLacdapiProxy::SetAssociateData(int64_t handle, const std::string& agentId, const std::string& key, const std::string& value, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SetAssociateData(handle, agentId, key, value, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SetAssociateData(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SetAssociateData(const int64_t& handle, const std::string& agentId, const std::string& key, const std::string& value, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SetAssociateData", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SetAssociateData_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.key = &key;
        pargs.value = &value;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SetAssociateData(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SetAssociateData_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SetAssociateData"){
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

    AcdResultT SSLacdapiProxy::GetAssociateData(int64_t handle, const std::string& agentId, const std::string& key, std::string& value, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAssociateData(handle, agentId, key, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAssociateData(value, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAssociateData(const int64_t& handle, const std::string& agentId, const std::string& key, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAssociateData", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAssociateData_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.key = &key;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAssociateData(std::string& value, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAssociateData_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAssociateData"){
            presult.return_value = &ret_val;
            presult.value = &value;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_JumptheQueue(handle, agentId, requestId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_JumptheQueue(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_JumptheQueue(const int64_t& handle, const std::string& agentId, const int64_t& requestId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "JumptheQueue", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_JumptheQueue_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.requestId = &requestId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_JumptheQueue(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_JumptheQueue_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="JumptheQueue"){
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

    AcdResultT SSLacdapiProxy::ForceSignIn(int64_t handle, const std::string& agentId, const std::string& destAgentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin, const std::string& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSignIn(handle, agentId, destAgentId, agentDn, agentPwd, statusChangetype, autoAnswer, fcSignin, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSignIn(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ForceSignIn(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, const std::string& agentDn, const std::string& agentPwd, const StatusChangeT& statusChangetype, const bool& autoAnswer, const bool& fcSignin, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSignIn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSignIn_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        pargs.agentDn = &agentDn;
        pargs.agentPwd = &agentPwd;
        pargs.statusChangetype = &statusChangetype;
        pargs.autoAnswer = &autoAnswer;
        pargs.fcSignin = &fcSignin;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ForceSignIn(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSignIn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSignIn"){
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

    AcdResultT SSLacdapiProxy::ForceSignOut(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSignOut(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSignOut(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ForceSignOut(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSignOut", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSignOut_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ForceSignOut(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSignOut_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSignOut"){
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

    AcdResultT SSLacdapiProxy::ForceSetAgentStatus(int64_t handle, const std::string& agentId, const std::string& destAgentId, const AgentStatusT& agentStatus, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ForceSetAgentStatus(handle, agentId, destAgentId, agentStatus, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ForceSetAgentStatus(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ForceSetAgentStatus(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, const AgentStatusT& agentStatus, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ForceSetAgentStatus", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ForceSetAgentStatus_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        pargs.agentStatus = &agentStatus;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ForceSetAgentStatus(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ForceSetAgentStatus_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ForceSetAgentStatus"){
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

    AcdResultT SSLacdapiProxy::Listen(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Listen(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Listen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Listen(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Listen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Listen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Listen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Listen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Listen"){
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

    AcdResultT SSLacdapiProxy::StopListen(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopListen(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopListen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_StopListen(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopListen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopListen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_StopListen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopListen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopListen"){
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

    AcdResultT SSLacdapiProxy::Insert(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Insert(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Insert(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Insert(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Insert", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Insert_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Insert(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Insert_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Insert"){
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

    AcdResultT SSLacdapiProxy::StopInsert(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopInsert(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopInsert(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_StopInsert(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopInsert", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopInsert_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_StopInsert(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopInsert_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopInsert"){
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

    AcdResultT SSLacdapiProxy::SwitchInsertorListen(int64_t handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SwitchInsertorListen(handle, agentId, callerId, destAgentId, forCallerDispNum, forCalleeDispNum, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SwitchInsertorListen(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SwitchInsertorListen(const int64_t& handle, const std::string& agentId, const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SwitchInsertorListen", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SwitchInsertorListen_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.callerId = &callerId;
        pargs.destAgentId = &destAgentId;
        pargs.forCallerDispNum = &forCallerDispNum;
        pargs.forCalleeDispNum = &forCalleeDispNum;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SwitchInsertorListen(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SwitchInsertorListen_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SwitchInsertorListen"){
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

    AcdResultT SSLacdapiProxy::Break(int64_t handle, const std::string& agentId, const std::string& destAgentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Break(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Break(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Break(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Break", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Break_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Break(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Break_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Break"){
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

    AcdResultT SSLacdapiProxy::SendDTMF(int64_t handle, const std::string& agentId, const std::string& digitals, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SendDTMF(handle, agentId, digitals, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SendDTMF(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SendDTMF(const int64_t& handle, const std::string& agentId, const std::string& digitals, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SendDTMF", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SendDTMF_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.digitals = &digitals;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SendDTMF(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SendDTMF_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SendDTMF"){
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

    AcdResultT SSLacdapiProxy::StartPlay(int64_t handle, const std::string& agentId, const std::string& filename, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StartPlay(handle, agentId, filename, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StartPlay(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_StartPlay(const int64_t& handle, const std::string& agentId, const std::string& filename, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StartPlay", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StartPlay_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.filename = &filename;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_StartPlay(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StartPlay_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StartPlay"){
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

    AcdResultT SSLacdapiProxy::StopPlay(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_StopPlay(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_StopPlay(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_StopPlay(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "StopPlay", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_StopPlay_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_StopPlay(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_StopPlay_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="StopPlay"){
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

    AcdResultT SSLacdapiProxy::MuteOn(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_MuteOn(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_MuteOn(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_MuteOn(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "MuteOn", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_MuteOn_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_MuteOn(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_MuteOn_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="MuteOn"){
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

    AcdResultT SSLacdapiProxy::MuteOff(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_MuteOff(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_MuteOff(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_MuteOff(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "MuteOff", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_MuteOff_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_MuteOff(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_MuteOff_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="MuteOff"){
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

    AcdResultT SSLacdapiProxy::GetAgentDetailByAgentID(int64_t handle, const std::string& agentId, const std::string& destAgentId, AgentInfoT& agentInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailByAgentID(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailByAgentID(agentInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentDetailByAgentID(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailByAgentID", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailByAgentID_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentDetailByAgentID(AgentInfoT& agentInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailByAgentID_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailByAgentID"){
            presult.return_value = &ret_val;
            presult.agentInfo = &agentInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetAgentDetailByAgentDN(int64_t handle, const std::string& agentId, const std::string& destAgentDn, AgentInfoT& agentInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailByAgentDN(handle, agentId, destAgentDn, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailByAgentDN(agentInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentDetailByAgentDN(const int64_t& handle, const std::string& agentId, const std::string& destAgentDn, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailByAgentDN", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailByAgentDN_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentDn = &destAgentDn;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentDetailByAgentDN(AgentInfoT& agentInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailByAgentDN_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailByAgentDN"){
            presult.return_value = &ret_val;
            presult.agentInfo = &agentInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetAgentDetailsByAgentIDs(int64_t handle, const std::string& agentId, const StringListT& destAgentIdList, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsByAgentIDs(handle, agentId, destAgentIdList, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsByAgentIDs(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentDetailsByAgentIDs(const int64_t& handle, const std::string& agentId, const StringListT& destAgentIdList, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsByAgentIDs", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsByAgentIDs_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentIdList = &destAgentIdList;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentDetailsByAgentIDs(AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsByAgentIDs_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsByAgentIDs"){
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

    AcdResultT SSLacdapiProxy::GetAgentDetailsByAgentDNs(int64_t handle, const std::string& agentId, const StringListT& destAgentDnList, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsByAgentDNs(handle, agentId, destAgentDnList, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsByAgentDNs(agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentDetailsByAgentDNs(const int64_t& handle, const std::string& agentId, const StringListT& destAgentDnList, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsByAgentDNs", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsByAgentDNs_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentDnList = &destAgentDnList;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentDetailsByAgentDNs(AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsByAgentDNs_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsByAgentDNs"){
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

    AcdResultT SSLacdapiProxy::GetRecordFileName(int64_t handle, const std::string& agentId, std::string& filename, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetRecordFileName(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetRecordFileName(filename, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetRecordFileName(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetRecordFileName", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetRecordFileName_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetRecordFileName(std::string& filename, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetRecordFileName_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetRecordFileName"){
            presult.return_value = &ret_val;
            presult.filename = &filename;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetSkill(int64_t handle, const std::string& agentId, StringListT& skill, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkill(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkill(skill, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetSkill(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetSkill(StringListT& skill, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkill"){
            presult.return_value = &ret_val;
            presult.skill = &skill;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetRestReason(int64_t handle, const std::string& agentId, StringListT& restReason, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetRestReason(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetRestReason(restReason, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetRestReason(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetRestReason", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetRestReason_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetRestReason(StringListT& restReason, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetRestReason_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetRestReason"){
            presult.return_value = &ret_val;
            presult.restReason = &restReason;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetAgentNumberBySkill(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& agentNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentNumberBySkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentNumberBySkill(agentNum, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentNumberBySkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentNumberBySkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentNumberBySkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentNumberBySkill(int32_t& agentNum, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentNumberBySkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentNumberBySkill"){
            presult.return_value = &ret_val;
            presult.agentNum = &agentNum;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetAgentDetailsBySkill(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& agentNum, AgentInfoListT& agentInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetAgentDetailsBySkill(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetAgentDetailsBySkill(agentNum, agentInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetAgentDetailsBySkill(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetAgentDetailsBySkill", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetAgentDetailsBySkill_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetAgentDetailsBySkill(int32_t& agentNum, AgentInfoListT& agentInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetAgentDetailsBySkill_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetAgentDetailsBySkill"){
            presult.return_value = &ret_val;
            presult.agentNum = &agentNum;
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

    AcdResultT SSLacdapiProxy::GetSkillWaitingNumber(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& queueNum, int32_t& freeNum, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkillWaitingNumber(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkillWaitingNumber(queueNum, freeNum, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetSkillWaitingNumber(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkillWaitingNumber", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkillWaitingNumber_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetSkillWaitingNumber(int32_t& queueNum, int32_t& freeNum, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkillWaitingNumber_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkillWaitingNumber"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.freeNum = &freeNum;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetSkillWaitingCallInfo(int64_t handle, const std::string& agentId, const std::string& skill, int32_t& queueNum, QueueInfoListT& queueInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSkillWaitingCallInfo(handle, agentId, skill, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSkillWaitingCallInfo(queueNum, queueInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetSkillWaitingCallInfo(const int64_t& handle, const std::string& agentId, const std::string& skill, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSkillWaitingCallInfo", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSkillWaitingCallInfo_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.skill = &skill;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetSkillWaitingCallInfo(int32_t& queueNum, QueueInfoListT& queueInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSkillWaitingCallInfo_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSkillWaitingCallInfo"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.queueInfoList = &queueInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetPrivateQueue(int64_t handle, const std::string& agentId, const std::string& destAgentId, int32_t& queueNum, QueueInfoListT& queueInfoList, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetPrivateQueue(handle, agentId, destAgentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetPrivateQueue(queueNum, queueInfoList, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetPrivateQueue(const int64_t& handle, const std::string& agentId, const std::string& destAgentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetPrivateQueue", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetPrivateQueue_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        pargs.destAgentId = &destAgentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetPrivateQueue(int32_t& queueNum, QueueInfoListT& queueInfoList, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetPrivateQueue_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetPrivateQueue"){
            presult.return_value = &ret_val;
            presult.queueNum = &queueNum;
            presult.queueInfoList = &queueInfoList;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::GetSysInfo(int64_t handle, const std::string& agentId, SysInfoT& sysInfo, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_GetSysInfo(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_GetSysInfo(sysInfo, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_GetSysInfo(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "GetSysInfo", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_GetSysInfo_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_GetSysInfo(SysInfoT& sysInfo, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_GetSysInfo_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="GetSysInfo"){
            presult.return_value = &ret_val;
            presult.sysInfo = &sysInfo;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::SynchronizeCTITime(int64_t handle, const std::string& agentId, int64_t& timestamp, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_SynchronizeCTITime(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_SynchronizeCTITime(timestamp, conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_SynchronizeCTITime(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "SynchronizeCTITime", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_SynchronizeCTITime_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_SynchronizeCTITime(int64_t& timestamp, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_SynchronizeCTITime_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="SynchronizeCTITime"){
            presult.return_value = &ret_val;
            presult.timestamp = &timestamp;
            ret_code = presult.read(OFFSET_PTR(read_buf, ret_code), read_buf_len - ret_code, proto);
            if(ret_code>0) { ret_code=proto->readMessageEnd();}
        }
        else{
            ret_code=-1;
        }
        set_errno(ret_code);
        return ret_val;
    }

    AcdResultT SSLacdapiProxy::Heartbeat(int64_t handle, const std::string& agentId, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_Heartbeat(handle, agentId, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_Heartbeat(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_Heartbeat(const int64_t& handle, const std::string& agentId, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "Heartbeat", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_Heartbeat_pargs pargs;
        pargs.handle = &handle;
        pargs.agentId = &agentId;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_Heartbeat(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_Heartbeat_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="Heartbeat"){
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

    AcdResultT SSLacdapiProxy::ResetConfig(const std::string& password, bool /*last*/) {
        AcdResultT return_value;
        int tryCount = 0;
        do{
            bgcc::SharedPointer<bgcc::ConnInfo> conn=get_Conn();
            if(conn.is_valid()&&conn->proto.is_valid()){
                send_ResetConfig(password, _seqid, conn);
                if(get_errno()==0){
                    return_value = recv_ResetConfig(conn);
                    free_Conn(conn, get_errno());
                }
            }
            else{
                set_errno(-1);
            }
        }while(!_use_existing_socket&&tryCount++<_tryCount&&get_errno()!=0);

        return return_value;
    }

    void SSLacdapiProxy::send_ResetConfig(const std::string& password, int32_t seqid, bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        bgcc::SharedPointer<bgcc::IProtocol> proto = conn->proto;
        int32_t ret_code = 0;
        set_errno(ret_code);

        ret_code = proto->writeMessageBegin(_whoami.c_str(), "ResetConfig", bgcc::CALL, seqid);
        if (ret_code < 0) { set_errno(ret_code); return;}

        ret_code = proto->writeString(get_name());
        if (ret_code < 0) { set_errno(ret_code); return;}

        acdapi_ResetConfig_pargs pargs;
        pargs.password = &password;
        ret_code = pargs.write(proto);
        if (ret_code < 0) { set_errno(ret_code); return;}

        proto->writeMessageEnd();
        if (ret_code < 0) { set_errno(ret_code); return;}
    }

    AcdResultT SSLacdapiProxy::recv_ResetConfig(bgcc::SharedPointer<bgcc::ConnInfo> conn) {
        AcdResultT ret_val;
        bgcc::SharedPointer<bgcc::IProtocol> proto=conn->proto;
        int32_t ret_code=0;
        std::string fname;
        bgcc::MsgTypeID  msg_type=bgcc::CALL;
        int32_t msg_seqid=0;
        char *read_buf=NULL;
        int32_t read_buf_len = 0;
        acdapi_ResetConfig_presult presult;
        set_errno(ret_code);

        if((ret_code=proto->readMessageBegin(&read_buf, read_buf_len, fname, msg_type, msg_seqid, conn->param))>HEAD_SIZE
            &&msg_type==bgcc::REPLY
            &&fname=="ResetConfig"){
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

    acdapiProcessor::acdapiProcessor(bgcc::SharedPointer<acdapi> intf) :
        bgcc::BaseProcessor(), __intf(intf) {
        __fun_map["SignIn"] = &acdapiProcessor::do_SignIn;
        __fun_map["SignOut"] = &acdapiProcessor::do_SignOut;
        __fun_map["SetAgentStatus"] = &acdapiProcessor::do_SetAgentStatus;
        __fun_map["GetAgentStatus"] = &acdapiProcessor::do_GetAgentStatus;
        __fun_map["ResetStatuschangetype"] = &acdapiProcessor::do_ResetStatuschangetype;
        __fun_map["ResetAutoAnswer"] = &acdapiProcessor::do_ResetAutoAnswer;
        __fun_map["ResetSkill"] = &acdapiProcessor::do_ResetSkill;
        __fun_map["Reset"] = &acdapiProcessor::do_Reset;
        __fun_map["OutboundCall"] = &acdapiProcessor::do_OutboundCall;
        __fun_map["AnswerCall"] = &acdapiProcessor::do_AnswerCall;
        __fun_map["ReleaseCall"] = &acdapiProcessor::do_ReleaseCall;
        __fun_map["Hold"] = &acdapiProcessor::do_Hold;
        __fun_map["Retrieve"] = &acdapiProcessor::do_Retrieve;
        __fun_map["Consult"] = &acdapiProcessor::do_Consult;
        __fun_map["ConsultReconnect"] = &acdapiProcessor::do_ConsultReconnect;
        __fun_map["ConsultTransfer"] = &acdapiProcessor::do_ConsultTransfer;
        __fun_map["SingleStepTransfer"] = &acdapiProcessor::do_SingleStepTransfer;
        __fun_map["ConsultConference"] = &acdapiProcessor::do_ConsultConference;
        __fun_map["ConferenceJoin"] = &acdapiProcessor::do_ConferenceJoin;
        __fun_map["SetAssociateData"] = &acdapiProcessor::do_SetAssociateData;
        __fun_map["GetAssociateData"] = &acdapiProcessor::do_GetAssociateData;
        __fun_map["JumptheQueue"] = &acdapiProcessor::do_JumptheQueue;
        __fun_map["ForceSignIn"] = &acdapiProcessor::do_ForceSignIn;
        __fun_map["ForceSignOut"] = &acdapiProcessor::do_ForceSignOut;
        __fun_map["ForceSetAgentStatus"] = &acdapiProcessor::do_ForceSetAgentStatus;
        __fun_map["Listen"] = &acdapiProcessor::do_Listen;
        __fun_map["StopListen"] = &acdapiProcessor::do_StopListen;
        __fun_map["Insert"] = &acdapiProcessor::do_Insert;
        __fun_map["StopInsert"] = &acdapiProcessor::do_StopInsert;
        __fun_map["SwitchInsertorListen"] = &acdapiProcessor::do_SwitchInsertorListen;
        __fun_map["Break"] = &acdapiProcessor::do_Break;
        __fun_map["SendDTMF"] = &acdapiProcessor::do_SendDTMF;
        __fun_map["StartPlay"] = &acdapiProcessor::do_StartPlay;
        __fun_map["StopPlay"] = &acdapiProcessor::do_StopPlay;
        __fun_map["MuteOn"] = &acdapiProcessor::do_MuteOn;
        __fun_map["MuteOff"] = &acdapiProcessor::do_MuteOff;
        __fun_map["GetAgentDetailByAgentID"] = &acdapiProcessor::do_GetAgentDetailByAgentID;
        __fun_map["GetAgentDetailByAgentDN"] = &acdapiProcessor::do_GetAgentDetailByAgentDN;
        __fun_map["GetAgentDetailsByAgentIDs"] = &acdapiProcessor::do_GetAgentDetailsByAgentIDs;
        __fun_map["GetAgentDetailsByAgentDNs"] = &acdapiProcessor::do_GetAgentDetailsByAgentDNs;
        __fun_map["GetRecordFileName"] = &acdapiProcessor::do_GetRecordFileName;
        __fun_map["GetSkill"] = &acdapiProcessor::do_GetSkill;
        __fun_map["GetRestReason"] = &acdapiProcessor::do_GetRestReason;
        __fun_map["GetAgentNumberBySkill"] = &acdapiProcessor::do_GetAgentNumberBySkill;
        __fun_map["GetAgentDetailsBySkill"] = &acdapiProcessor::do_GetAgentDetailsBySkill;
        __fun_map["GetSkillWaitingNumber"] = &acdapiProcessor::do_GetSkillWaitingNumber;
        __fun_map["GetSkillWaitingCallInfo"] = &acdapiProcessor::do_GetSkillWaitingCallInfo;
        __fun_map["GetPrivateQueue"] = &acdapiProcessor::do_GetPrivateQueue;
        __fun_map["GetSysInfo"] = &acdapiProcessor::do_GetSysInfo;
        __fun_map["SynchronizeCTITime"] = &acdapiProcessor::do_SynchronizeCTITime;
        __fun_map["Heartbeat"] = &acdapiProcessor::do_Heartbeat;
        __fun_map["ResetConfig"] = &acdapiProcessor::do_ResetConfig;
    }

    int32_t acdapiProcessor::process(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) {
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

    std::string acdapiProcessor::get_name() const {
        return "global.acd.acdapi";
    }

    int32_t acdapiProcessor::do_function__(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, 
        const std::string& fname, int32_t seqid) {
        std::map<std::string, do_function_ptr>::iterator it;
        it = __fun_map.find(fname);
        if (it == __fun_map.end()) {
            return bgcc::BaseProcessor::do_function__(request, request_len, proto, fname, seqid);
        }

        return (this->*(it->second))(request, request_len, proto, seqid);
    }

    int32_t acdapiProcessor::do_SignIn(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SignIn_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SignIn_result result;
        result.return_value = __intf->SignIn(args.agentId, args.agentDn, args.agentPwd, args.statusChangetype, args.autoAnswer, args.fcSignin, args.skill, result.handle, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SignIn", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SignOut(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SignOut_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SignOut_result result;
        result.return_value = __intf->SignOut(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SignOut", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SetAgentStatus(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SetAgentStatus_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SetAgentStatus_result result;
        result.return_value = __intf->SetAgentStatus(args.handle, args.agentId, args.agentStatus, args.restReason, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SetAgentStatus", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentStatus(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentStatus_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentStatus_result result;
        result.return_value = __intf->GetAgentStatus(args.handle, args.agentId, result.agentStatus, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentStatus", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ResetStatuschangetype(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ResetStatuschangetype_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ResetStatuschangetype_result result;
        result.return_value = __intf->ResetStatuschangetype(args.handle, args.agentId, args.statusChangetype, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ResetStatuschangetype", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ResetAutoAnswer(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ResetAutoAnswer_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ResetAutoAnswer_result result;
        result.return_value = __intf->ResetAutoAnswer(args.handle, args.agentId, args.autoAnswer, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ResetAutoAnswer", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ResetSkill(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ResetSkill_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ResetSkill_result result;
        result.return_value = __intf->ResetSkill(args.handle, args.agentId, args.skill, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ResetSkill", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Reset(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Reset_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Reset_result result;
        result.return_value = __intf->Reset(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Reset", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_OutboundCall(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_OutboundCall_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_OutboundCall_result result;
        result.return_value = __intf->OutboundCall(args.handle, args.agentId, args.callerId, args.destId, args.forCallerDispNum, args.forCalleeDispNum, args.timeout, args.callMode, args.callType, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "OutboundCall", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_AnswerCall(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_AnswerCall_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_AnswerCall_result result;
        result.return_value = __intf->AnswerCall(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "AnswerCall", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ReleaseCall(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ReleaseCall_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ReleaseCall_result result;
        result.return_value = __intf->ReleaseCall(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ReleaseCall", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Hold(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Hold_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Hold_result result;
        result.return_value = __intf->Hold(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Hold", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Retrieve(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Retrieve_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Retrieve_result result;
        result.return_value = __intf->Retrieve(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Retrieve", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Consult(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Consult_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Consult_result result;
        result.return_value = __intf->Consult(args.handle, args.agentId, args.callerId, args.destId, args.forCallerDispNum, args.forCalleeDispNum, args.callType, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Consult", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ConsultReconnect(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ConsultReconnect_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ConsultReconnect_result result;
        result.return_value = __intf->ConsultReconnect(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ConsultReconnect", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ConsultTransfer(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ConsultTransfer_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ConsultTransfer_result result;
        result.return_value = __intf->ConsultTransfer(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ConsultTransfer", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SingleStepTransfer(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SingleStepTransfer_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SingleStepTransfer_result result;
        result.return_value = __intf->SingleStepTransfer(args.handle, args.agentId, args.callerId, args.destId, args.forCallerDispNum, args.forCalleeDispNum, args.isPassthrough, args.transferType, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SingleStepTransfer", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ConsultConference(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ConsultConference_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ConsultConference_result result;
        result.return_value = __intf->ConsultConference(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ConsultConference", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ConferenceJoin(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ConferenceJoin_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ConferenceJoin_result result;
        result.return_value = __intf->ConferenceJoin(args.handle, args.agentId, args.callerId, args.destAgentId, args.forCallerDispNum, args.forCalleeDispNum, args.conferenceType, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ConferenceJoin", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SetAssociateData(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SetAssociateData_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SetAssociateData_result result;
        result.return_value = __intf->SetAssociateData(args.handle, args.agentId, args.key, args.value, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SetAssociateData", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAssociateData(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAssociateData_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAssociateData_result result;
        result.return_value = __intf->GetAssociateData(args.handle, args.agentId, args.key, result.value, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAssociateData", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_JumptheQueue(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_JumptheQueue_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_JumptheQueue_result result;
        result.return_value = __intf->JumptheQueue(args.handle, args.agentId, args.requestId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "JumptheQueue", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ForceSignIn(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ForceSignIn_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ForceSignIn_result result;
        result.return_value = __intf->ForceSignIn(args.handle, args.agentId, args.destAgentId, args.agentDn, args.agentPwd, args.statusChangetype, args.autoAnswer, args.fcSignin, args.skill, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ForceSignIn", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ForceSignOut(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ForceSignOut_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ForceSignOut_result result;
        result.return_value = __intf->ForceSignOut(args.handle, args.agentId, args.destAgentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ForceSignOut", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ForceSetAgentStatus(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ForceSetAgentStatus_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ForceSetAgentStatus_result result;
        result.return_value = __intf->ForceSetAgentStatus(args.handle, args.agentId, args.destAgentId, args.agentStatus, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ForceSetAgentStatus", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Listen(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Listen_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Listen_result result;
        result.return_value = __intf->Listen(args.handle, args.agentId, args.callerId, args.destAgentId, args.forCallerDispNum, args.forCalleeDispNum, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Listen", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_StopListen(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_StopListen_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_StopListen_result result;
        result.return_value = __intf->StopListen(args.handle, args.agentId, args.destAgentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "StopListen", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Insert(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Insert_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Insert_result result;
        result.return_value = __intf->Insert(args.handle, args.agentId, args.callerId, args.destAgentId, args.forCallerDispNum, args.forCalleeDispNum, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Insert", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_StopInsert(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_StopInsert_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_StopInsert_result result;
        result.return_value = __intf->StopInsert(args.handle, args.agentId, args.destAgentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "StopInsert", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SwitchInsertorListen(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SwitchInsertorListen_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SwitchInsertorListen_result result;
        result.return_value = __intf->SwitchInsertorListen(args.handle, args.agentId, args.callerId, args.destAgentId, args.forCallerDispNum, args.forCalleeDispNum, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SwitchInsertorListen", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Break(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Break_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Break_result result;
        result.return_value = __intf->Break(args.handle, args.agentId, args.destAgentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Break", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SendDTMF(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SendDTMF_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SendDTMF_result result;
        result.return_value = __intf->SendDTMF(args.handle, args.agentId, args.digitals, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SendDTMF", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_StartPlay(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_StartPlay_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_StartPlay_result result;
        result.return_value = __intf->StartPlay(args.handle, args.agentId, args.filename, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "StartPlay", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_StopPlay(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_StopPlay_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_StopPlay_result result;
        result.return_value = __intf->StopPlay(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "StopPlay", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_MuteOn(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_MuteOn_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_MuteOn_result result;
        result.return_value = __intf->MuteOn(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "MuteOn", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_MuteOff(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_MuteOff_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_MuteOff_result result;
        result.return_value = __intf->MuteOff(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "MuteOff", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentDetailByAgentID(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentDetailByAgentID_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentDetailByAgentID_result result;
        result.return_value = __intf->GetAgentDetailByAgentID(args.handle, args.agentId, args.destAgentId, result.agentInfo, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentDetailByAgentID", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentDetailByAgentDN(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentDetailByAgentDN_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentDetailByAgentDN_result result;
        result.return_value = __intf->GetAgentDetailByAgentDN(args.handle, args.agentId, args.destAgentDn, result.agentInfo, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentDetailByAgentDN", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentDetailsByAgentIDs(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentDetailsByAgentIDs_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentDetailsByAgentIDs_result result;
        result.return_value = __intf->GetAgentDetailsByAgentIDs(args.handle, args.agentId, args.destAgentIdList, result.agentInfoList, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentDetailsByAgentIDs", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentDetailsByAgentDNs(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentDetailsByAgentDNs_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentDetailsByAgentDNs_result result;
        result.return_value = __intf->GetAgentDetailsByAgentDNs(args.handle, args.agentId, args.destAgentDnList, result.agentInfoList, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentDetailsByAgentDNs", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetRecordFileName(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetRecordFileName_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetRecordFileName_result result;
        result.return_value = __intf->GetRecordFileName(args.handle, args.agentId, result.filename, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetRecordFileName", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetSkill(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetSkill_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetSkill_result result;
        result.return_value = __intf->GetSkill(args.handle, args.agentId, result.skill, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetSkill", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetRestReason(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetRestReason_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetRestReason_result result;
        result.return_value = __intf->GetRestReason(args.handle, args.agentId, result.restReason, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetRestReason", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentNumberBySkill(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentNumberBySkill_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentNumberBySkill_result result;
        result.return_value = __intf->GetAgentNumberBySkill(args.handle, args.agentId, args.skill, result.agentNum, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentNumberBySkill", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetAgentDetailsBySkill(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetAgentDetailsBySkill_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetAgentDetailsBySkill_result result;
        result.return_value = __intf->GetAgentDetailsBySkill(args.handle, args.agentId, args.skill, result.agentNum, result.agentInfoList, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetAgentDetailsBySkill", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetSkillWaitingNumber(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetSkillWaitingNumber_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetSkillWaitingNumber_result result;
        result.return_value = __intf->GetSkillWaitingNumber(args.handle, args.agentId, args.skill, result.queueNum, result.freeNum, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetSkillWaitingNumber", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetSkillWaitingCallInfo(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetSkillWaitingCallInfo_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetSkillWaitingCallInfo_result result;
        result.return_value = __intf->GetSkillWaitingCallInfo(args.handle, args.agentId, args.skill, result.queueNum, result.queueInfoList, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetSkillWaitingCallInfo", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetPrivateQueue(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetPrivateQueue_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetPrivateQueue_result result;
        result.return_value = __intf->GetPrivateQueue(args.handle, args.agentId, args.destAgentId, result.queueNum, result.queueInfoList, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetPrivateQueue", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_GetSysInfo(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_GetSysInfo_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_GetSysInfo_result result;
        result.return_value = __intf->GetSysInfo(args.handle, args.agentId, result.sysInfo, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "GetSysInfo", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_SynchronizeCTITime(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_SynchronizeCTITime_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_SynchronizeCTITime_result result;
        result.return_value = __intf->SynchronizeCTITime(args.handle, args.agentId, result.timestamp, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "SynchronizeCTITime", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_Heartbeat(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_Heartbeat_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_Heartbeat_result result;
        result.return_value = __intf->Heartbeat(args.handle, args.agentId, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "Heartbeat", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

    int32_t acdapiProcessor::do_ResetConfig(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto, int32_t seqid) {
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

        acdapi_ResetConfig_args args;
        ret = args.read(request, request_len, proto);
        if (ret < 0) { return ret;}

        request += ret;
        request_len -= ret;

        ret = proto->readMessageEnd();
        if (ret < 0) { return ret; }

        acdapi_ResetConfig_result result;
        result.return_value = __intf->ResetConfig(args.password, map);
        ret = proto->writeMessageBegin("global.acd.acdapi", "ResetConfig", ::bgcc::REPLY, seqid);
        if (ret < 0) { return ret;}
        ret = result.write(proto);
        if (ret < 0) { return ret; }

        ret = proto->writeMessageEnd();
        return ret;
    }

}


