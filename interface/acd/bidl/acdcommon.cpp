#include "acdcommon.h"

namespace acd {

    const struct AcdResultT::desc_t AcdResultT::descs[] = {
        {AcdResultT::ArSuccess, "AcdResultT::ArSuccess"},
        {AcdResultT::ArAgentIdIsEmpty, "AcdResultT::ArAgentIdIsEmpty"},
        {AcdResultT::ArAgentDnIsEmpty, "AcdResultT::ArAgentDnIsEmpty"},
        {AcdResultT::ArSkillIsEmpty, "AcdResultT::ArSkillIsEmpty"},
        {AcdResultT::ArCallerIdIsEmpty, "AcdResultT::ArCallerIdIsEmpty"},
        {AcdResultT::ArDestIdIsEmpty, "AcdResultT::ArDestIdIsEmpty"},
        {AcdResultT::ArDestDnIsEmpty, "AcdResultT::ArDestDnIsEmpty"},
        {AcdResultT::ArKeyIsEmpty, "AcdResultT::ArKeyIsEmpty"},
        {AcdResultT::ArValueIsEmpty, "AcdResultT::ArValueIsEmpty"},
        {AcdResultT::ArDigitalsIsEmpty, "AcdResultT::ArDigitalsIsEmpty"},
        {AcdResultT::ArFilenameIsEmpty, "AcdResultT::ArFilenameIsEmpty"},
        {AcdResultT::ArAgentIdNotExist, "AcdResultT::ArAgentIdNotExist"},
        {AcdResultT::ArAgentPasswordError, "AcdResultT::ArAgentPasswordError"},
        {AcdResultT::ArAgentSkillError, "AcdResultT::ArAgentSkillError"},
        {AcdResultT::ArNotMaster, "AcdResultT::ArNotMaster"},
        {AcdResultT::ArAgentDnBeOccupied, "AcdResultT::ArAgentDnBeOccupied"},
        {AcdResultT::ArHasSigned, "AcdResultT::ArHasSigned"},
        {AcdResultT::ArNoSignin, "AcdResultT::ArNoSignin"},
        {AcdResultT::ArDestAgentIdNotExist, "AcdResultT::ArDestAgentIdNotExist"},
        {AcdResultT::ArDestAgentDnNotExist, "AcdResultT::ArDestAgentDnNotExist"},
        {AcdResultT::ArSkillNotExist, "AcdResultT::ArSkillNotExist"},
        {AcdResultT::ArRouteRequestNotExist, "AcdResultT::ArRouteRequestNotExist"},
        {AcdResultT::ArAgentStatusIsWrong, "AcdResultT::ArAgentStatusIsWrong"},
        {AcdResultT::ArImsError, "AcdResultT::ArImsError"},
        {AcdResultT::ArPasswordError, "AcdResultT::ArPasswordError"},
        {AcdResultT::ArFailed, "AcdResultT::ArFailed"},
        {AcdResultT::ArApFailed, "AcdResultT::ArApFailed"},
        {AcdResultT::ArConnAcdFail, "AcdResultT::ArConnAcdFail"},
        {0, NULL}
    };

    AcdResultT::AcdResultT() : _value(ArSuccess) {
    }

    AcdResultT::AcdResultT(int32_t value) : _value(value) {
    }

    int32_t AcdResultT::get_value() const {
        return _value;
    }

    std::string AcdResultT::get_desc() const {
        const struct desc_t* ptr = AcdResultT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool AcdResultT::operator==(int32_t value) const {
        return _value == value;
    }

    bool AcdResultT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool AcdResultT::operator< (int32_t value) const {
        return _value < value;
    }

    bool AcdResultT::operator==(const AcdResultT& rhs) const {
        return _value == rhs.get_value();
    }

    bool AcdResultT::operator!=(const AcdResultT& rhs) const {
        return _value != rhs.get_value();
    }

    bool AcdResultT::operator< (const AcdResultT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const AcdResultT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const AcdResultT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const AcdResultT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const AcdResultT& e) {
        o << e.get_value();
        return o;
    }


    const struct StatusChangeT::desc_t StatusChangeT::descs[] = {
        {StatusChangeT::ScReady, "StatusChangeT::ScReady"},
        {StatusChangeT::ScBusy, "StatusChangeT::ScBusy"},
        {0, NULL}
    };

    StatusChangeT::StatusChangeT() : _value(ScReady) {
    }

    StatusChangeT::StatusChangeT(int32_t value) : _value(value) {
    }

    int32_t StatusChangeT::get_value() const {
        return _value;
    }

    std::string StatusChangeT::get_desc() const {
        const struct desc_t* ptr = StatusChangeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool StatusChangeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool StatusChangeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool StatusChangeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool StatusChangeT::operator==(const StatusChangeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool StatusChangeT::operator!=(const StatusChangeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool StatusChangeT::operator< (const StatusChangeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const StatusChangeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const StatusChangeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const StatusChangeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const StatusChangeT& e) {
        o << e.get_value();
        return o;
    }


    const struct AgentStatusT::desc_t AgentStatusT::descs[] = {
        {AgentStatusT::AsUnknownState, "AgentStatusT::AsUnknownState"},
        {AgentStatusT::AsUnLoginState, "AgentStatusT::AsUnLoginState"},
        {AgentStatusT::AsReadyState, "AgentStatusT::AsReadyState"},
        {AgentStatusT::AsBusyState, "AgentStatusT::AsBusyState"},
        {AgentStatusT::AsRestState, "AgentStatusT::AsRestState"},
        {AgentStatusT::AsLockState, "AgentStatusT::AsLockState"},
        {AgentStatusT::AsAlertingState, "AgentStatusT::AsAlertingState"},
        {AgentStatusT::AsHalfAlertingState, "AgentStatusT::AsHalfAlertingState"},
        {AgentStatusT::AsConnectingState, "AgentStatusT::AsConnectingState"},
        {AgentStatusT::AsConnectedState, "AgentStatusT::AsConnectedState"},
        {AgentStatusT::AsHalfConnectedState, "AgentStatusT::AsHalfConnectedState"},
        {AgentStatusT::AsInternalConnectedState, "AgentStatusT::AsInternalConnectedState"},
        {AgentStatusT::AsSuspendedState, "AgentStatusT::AsSuspendedState"},
        {AgentStatusT::AsConsultConnectingState, "AgentStatusT::AsConsultConnectingState"},
        {AgentStatusT::AsConsultConnectedState, "AgentStatusT::AsConsultConnectedState"},
        {AgentStatusT::AsConferenceState, "AgentStatusT::AsConferenceState"},
        {AgentStatusT::AsMonitorState, "AgentStatusT::AsMonitorState"},
        {AgentStatusT::AsInsertState, "AgentStatusT::AsInsertState"},
        {AgentStatusT::AsMonitoredState, "AgentStatusT::AsMonitoredState"},
        {AgentStatusT::AsInsertedState, "AgentStatusT::AsInsertedState"},
        {0, NULL}
    };

    AgentStatusT::AgentStatusT() : _value(AsUnknownState) {
    }

    AgentStatusT::AgentStatusT(int32_t value) : _value(value) {
    }

    int32_t AgentStatusT::get_value() const {
        return _value;
    }

    std::string AgentStatusT::get_desc() const {
        const struct desc_t* ptr = AgentStatusT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool AgentStatusT::operator==(int32_t value) const {
        return _value == value;
    }

    bool AgentStatusT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool AgentStatusT::operator< (int32_t value) const {
        return _value < value;
    }

    bool AgentStatusT::operator==(const AgentStatusT& rhs) const {
        return _value == rhs.get_value();
    }

    bool AgentStatusT::operator!=(const AgentStatusT& rhs) const {
        return _value != rhs.get_value();
    }

    bool AgentStatusT::operator< (const AgentStatusT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const AgentStatusT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const AgentStatusT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const AgentStatusT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const AgentStatusT& e) {
        o << e.get_value();
        return o;
    }


    const struct CallModeT::desc_t CallModeT::descs[] = {
        {CallModeT::CmNormal, "CallModeT::CmNormal"},
        {CallModeT::CmOffhook, "CallModeT::CmOffhook"},
        {0, NULL}
    };

    CallModeT::CallModeT() : _value(CmNormal) {
    }

    CallModeT::CallModeT(int32_t value) : _value(value) {
    }

    int32_t CallModeT::get_value() const {
        return _value;
    }

    std::string CallModeT::get_desc() const {
        const struct desc_t* ptr = CallModeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool CallModeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool CallModeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool CallModeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool CallModeT::operator==(const CallModeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool CallModeT::operator!=(const CallModeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool CallModeT::operator< (const CallModeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const CallModeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const CallModeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const CallModeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const CallModeT& e) {
        o << e.get_value();
        return o;
    }


    const struct CallTypeT::desc_t CallTypeT::descs[] = {
        {CallTypeT::CtAgent, "CallTypeT::CtAgent"},
        {CallTypeT::CtOut, "CallTypeT::CtOut"},
        {0, NULL}
    };

    CallTypeT::CallTypeT() : _value(CtAgent) {
    }

    CallTypeT::CallTypeT(int32_t value) : _value(value) {
    }

    int32_t CallTypeT::get_value() const {
        return _value;
    }

    std::string CallTypeT::get_desc() const {
        const struct desc_t* ptr = CallTypeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool CallTypeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool CallTypeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool CallTypeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool CallTypeT::operator==(const CallTypeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool CallTypeT::operator!=(const CallTypeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool CallTypeT::operator< (const CallTypeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const CallTypeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const CallTypeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const CallTypeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const CallTypeT& e) {
        o << e.get_value();
        return o;
    }


    const struct ConferenceT::desc_t ConferenceT::descs[] = {
        {ConferenceT::ConferenceMute, "ConferenceT::ConferenceMute"},
        {ConferenceT::ConferenceSpeak, "ConferenceT::ConferenceSpeak"},
        {ConferenceT::ConferenceAll, "ConferenceT::ConferenceAll"},
        {0, NULL}
    };

    ConferenceT::ConferenceT() : _value(ConferenceMute) {
    }

    ConferenceT::ConferenceT(int32_t value) : _value(value) {
    }

    int32_t ConferenceT::get_value() const {
        return _value;
    }

    std::string ConferenceT::get_desc() const {
        const struct desc_t* ptr = ConferenceT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool ConferenceT::operator==(int32_t value) const {
        return _value == value;
    }

    bool ConferenceT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool ConferenceT::operator< (int32_t value) const {
        return _value < value;
    }

    bool ConferenceT::operator==(const ConferenceT& rhs) const {
        return _value == rhs.get_value();
    }

    bool ConferenceT::operator!=(const ConferenceT& rhs) const {
        return _value != rhs.get_value();
    }

    bool ConferenceT::operator< (const ConferenceT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const ConferenceT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const ConferenceT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const ConferenceT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const ConferenceT& e) {
        o << e.get_value();
        return o;
    }

    AgentInfoT::AgentInfoT() {
    }

    AgentInfoT::~AgentInfoT() {
    }

    bool AgentInfoT::operator==(const AgentInfoT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (agentDn != rhs.agentDn) {
            return false;
        }
        if (loginTime != rhs.loginTime) {
            return false;
        }
        if (currStatus != rhs.currStatus) {
            return false;
        }
        if (currStatusTime != rhs.currStatusTime) {
            return false;
        }
        if (answerTime != rhs.answerTime) {
            return false;
        }
        if (currTime != rhs.currTime) {
            return false;
        }
        if (origCaller != rhs.origCaller) {
            return false;
        }
        if (origCallee != rhs.origCallee) {
            return false;
        }
        if (privQueueNum != rhs.privQueueNum) {
            return false;
        }
        if (callTimes != rhs.callTimes) {
            return false;
        }
        if (answerTimes != rhs.answerTimes) {
            return false;
        }
        if (freeTotalTime != rhs.freeTotalTime) {
            return false;
        }
        if (busyTotalTime != rhs.busyTotalTime) {
            return false;
        }
        if (resetTotalTime != rhs.resetTotalTime) {
            return false;
        }
        if (callTotalTime != rhs.callTotalTime) {
            return false;
        }
        if (answerTotalTime != rhs.answerTotalTime) {
            return false;
        }
        if (agentIP != rhs.agentIP) {
            return false;
        }
        return true;
    }

    bool AgentInfoT::operator!=(const AgentInfoT& rhs) const {
        return !(*this == rhs);
    }

    bool AgentInfoT::operator< (const AgentInfoT& rhs) const {
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

        if (loginTime < rhs.loginTime) {
            return true;
        }
        else if (rhs.loginTime < loginTime) {
            return false;
        }

        if (currStatus < rhs.currStatus) {
            return true;
        }
        else if (rhs.currStatus < currStatus) {
            return false;
        }

        if (currStatusTime < rhs.currStatusTime) {
            return true;
        }
        else if (rhs.currStatusTime < currStatusTime) {
            return false;
        }

        if (answerTime < rhs.answerTime) {
            return true;
        }
        else if (rhs.answerTime < answerTime) {
            return false;
        }

        if (currTime < rhs.currTime) {
            return true;
        }
        else if (rhs.currTime < currTime) {
            return false;
        }

        if (origCaller < rhs.origCaller) {
            return true;
        }
        else if (rhs.origCaller < origCaller) {
            return false;
        }

        if (origCallee < rhs.origCallee) {
            return true;
        }
        else if (rhs.origCallee < origCallee) {
            return false;
        }

        if (privQueueNum < rhs.privQueueNum) {
            return true;
        }
        else if (rhs.privQueueNum < privQueueNum) {
            return false;
        }

        if (callTimes < rhs.callTimes) {
            return true;
        }
        else if (rhs.callTimes < callTimes) {
            return false;
        }

        if (answerTimes < rhs.answerTimes) {
            return true;
        }
        else if (rhs.answerTimes < answerTimes) {
            return false;
        }

        if (freeTotalTime < rhs.freeTotalTime) {
            return true;
        }
        else if (rhs.freeTotalTime < freeTotalTime) {
            return false;
        }

        if (busyTotalTime < rhs.busyTotalTime) {
            return true;
        }
        else if (rhs.busyTotalTime < busyTotalTime) {
            return false;
        }

        if (resetTotalTime < rhs.resetTotalTime) {
            return true;
        }
        else if (rhs.resetTotalTime < resetTotalTime) {
            return false;
        }

        if (callTotalTime < rhs.callTotalTime) {
            return true;
        }
        else if (rhs.callTotalTime < callTotalTime) {
            return false;
        }

        if (answerTotalTime < rhs.answerTotalTime) {
            return true;
        }
        else if (rhs.answerTotalTime < answerTotalTime) {
            return false;
        }

        if (agentIP < rhs.agentIP) {
            return true;
        }
        else if (rhs.agentIP < agentIP) {
            return false;
        }

        return false;
    }

    int32_t AgentInfoT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, loginTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                int32_t ele_var1;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var1);
                if (ret < 0) { return ret; }
                nread += ret;
                currStatus = ele_var1;
                break;
            case 5:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, currStatusTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, answerTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 7:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, currTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, origCaller);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 9:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, origCallee);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 10:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, privQueueNum);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 11:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, callTimes);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 12:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, answerTimes);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 13:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, freeTotalTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 14:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, busyTotalTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 15:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, resetTotalTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 16:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, callTotalTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 17:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, answerTotalTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 18:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentIP);
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

    int32_t AgentInfoT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("AgentInfoT");
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

        ret = proto->writeFieldBegin("loginTime", bgcc::IDINT64, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(loginTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("currStatus", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(currStatus.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("currStatusTime", bgcc::IDINT64, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(currStatusTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("answerTime", bgcc::IDINT64, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(answerTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("currTime", bgcc::IDINT64, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(currTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("origCaller", bgcc::IDSTR, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeString(origCaller);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("origCallee", bgcc::IDSTR, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeString(origCallee);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("privQueueNum", bgcc::IDINT32, 10);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(privQueueNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callTimes", bgcc::IDINT32, 11);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(callTimes);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("answerTimes", bgcc::IDINT32, 12);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(answerTimes);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("freeTotalTime", bgcc::IDINT64, 13);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(freeTotalTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("busyTotalTime", bgcc::IDINT64, 14);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(busyTotalTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("resetTotalTime", bgcc::IDINT64, 15);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(resetTotalTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callTotalTime", bgcc::IDINT64, 16);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(callTotalTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("answerTotalTime", bgcc::IDINT64, 17);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(answerTotalTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentIP", bgcc::IDSTR, 18);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentIP);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }
    QueueInfoT::QueueInfoT() {
    }

    QueueInfoT::~QueueInfoT() {
    }

    bool QueueInfoT::operator==(const QueueInfoT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (callId != rhs.callId) {
            return false;
        }
        if (contactId != rhs.contactId) {
            return false;
        }
        if (requestId != rhs.requestId) {
            return false;
        }
        if (origCaller != rhs.origCaller) {
            return false;
        }
        if (origCallee != rhs.origCallee) {
            return false;
        }
        if (startTime != rhs.startTime) {
            return false;
        }
        if (currTime != rhs.currTime) {
            return false;
        }
        if (changeTime != rhs.changeTime) {
            return false;
        }
        return true;
    }

    bool QueueInfoT::operator!=(const QueueInfoT& rhs) const {
        return !(*this == rhs);
    }

    bool QueueInfoT::operator< (const QueueInfoT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (callId < rhs.callId) {
            return true;
        }
        else if (rhs.callId < callId) {
            return false;
        }

        if (contactId < rhs.contactId) {
            return true;
        }
        else if (rhs.contactId < contactId) {
            return false;
        }

        if (requestId < rhs.requestId) {
            return true;
        }
        else if (rhs.requestId < requestId) {
            return false;
        }

        if (origCaller < rhs.origCaller) {
            return true;
        }
        else if (rhs.origCaller < origCaller) {
            return false;
        }

        if (origCallee < rhs.origCallee) {
            return true;
        }
        else if (rhs.origCallee < origCallee) {
            return false;
        }

        if (startTime < rhs.startTime) {
            return true;
        }
        else if (rhs.startTime < startTime) {
            return false;
        }

        if (currTime < rhs.currTime) {
            return true;
        }
        else if (rhs.currTime < currTime) {
            return false;
        }

        if (changeTime < rhs.changeTime) {
            return true;
        }
        else if (rhs.changeTime < changeTime) {
            return false;
        }

        return false;
    }

    int32_t QueueInfoT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 2:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, contactId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 3:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, requestId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, origCaller);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, origCallee);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, startTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 7:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, currTime);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, changeTime);
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

    int32_t QueueInfoT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("QueueInfoT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(callId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("contactId", bgcc::IDINT64, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(contactId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("requestId", bgcc::IDINT64, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(requestId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("origCaller", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(origCaller);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("origCallee", bgcc::IDSTR, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeString(origCallee);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("startTime", bgcc::IDINT64, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(startTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("currTime", bgcc::IDINT64, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(currTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("changeTime", bgcc::IDINT64, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(changeTime);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }
    SysInfoT::SysInfoT() {
    }

    SysInfoT::~SysInfoT() {
    }

    bool SysInfoT::operator==(const SysInfoT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (totalAgents != rhs.totalAgents) {
            return false;
        }
        if (totalCalls != rhs.totalCalls) {
            return false;
        }
        if (ivrCalls != rhs.ivrCalls) {
            return false;
        }
        if (agentCalls != rhs.agentCalls) {
            return false;
        }
        if (queueCalls != rhs.queueCalls) {
            return false;
        }
        if (privQueueCalls != rhs.privQueueCalls) {
            return false;
        }
        return true;
    }

    bool SysInfoT::operator!=(const SysInfoT& rhs) const {
        return !(*this == rhs);
    }

    bool SysInfoT::operator< (const SysInfoT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (totalAgents < rhs.totalAgents) {
            return true;
        }
        else if (rhs.totalAgents < totalAgents) {
            return false;
        }

        if (totalCalls < rhs.totalCalls) {
            return true;
        }
        else if (rhs.totalCalls < totalCalls) {
            return false;
        }

        if (ivrCalls < rhs.ivrCalls) {
            return true;
        }
        else if (rhs.ivrCalls < ivrCalls) {
            return false;
        }

        if (agentCalls < rhs.agentCalls) {
            return true;
        }
        else if (rhs.agentCalls < agentCalls) {
            return false;
        }

        if (queueCalls < rhs.queueCalls) {
            return true;
        }
        else if (rhs.queueCalls < queueCalls) {
            return false;
        }

        if (privQueueCalls < rhs.privQueueCalls) {
            return true;
        }
        else if (rhs.privQueueCalls < privQueueCalls) {
            return false;
        }

        return false;
    }

    int32_t SysInfoT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, totalAgents);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 2:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, totalCalls);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 3:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ivrCalls);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, agentCalls);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, queueCalls);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, privQueueCalls);
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

    int32_t SysInfoT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("SysInfoT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("totalAgents", bgcc::IDINT32, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(totalAgents);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("totalCalls", bgcc::IDINT32, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(totalCalls);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("ivrCalls", bgcc::IDINT32, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(ivrCalls);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentCalls", bgcc::IDINT32, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(agentCalls);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("queueCalls", bgcc::IDINT32, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(queueCalls);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("privQueueCalls", bgcc::IDINT32, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(privQueueCalls);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    const struct CallEventTypeT::desc_t CallEventTypeT::descs[] = {
        {CallEventTypeT::CeUnKnownEvent, "CallEventTypeT::CeUnKnownEvent"},
        {CallEventTypeT::CeInboundCallInternalCall, "CallEventTypeT::CeInboundCallInternalCall"},
        {CallEventTypeT::CeDestSeizedInternalCall, "CallEventTypeT::CeDestSeizedInternalCall"},
        {CallEventTypeT::CeThisPartyAnsweredInternalCall, "CallEventTypeT::CeThisPartyAnsweredInternalCall"},
        {CallEventTypeT::CeOtherPartyAnsweredInternalCall, "CallEventTypeT::CeOtherPartyAnsweredInternalCall"},
        {CallEventTypeT::CeThisPartyDisconnectedInternalCall, "CallEventTypeT::CeThisPartyDisconnectedInternalCall"},
        {CallEventTypeT::CeOtherPartyDisconnectedInternalCall, "CallEventTypeT::CeOtherPartyDisconnectedInternalCall"},
        {CallEventTypeT::CeInboundCallNormalCall, "CallEventTypeT::CeInboundCallNormalCall"},
        {CallEventTypeT::CeDestSeizedNormalCall, "CallEventTypeT::CeDestSeizedNormalCall"},
        {CallEventTypeT::CeThisPartyAnsweredNormalCall, "CallEventTypeT::CeThisPartyAnsweredNormalCall"},
        {CallEventTypeT::CeOtherPartyAnsweredNormalCall, "CallEventTypeT::CeOtherPartyAnsweredNormalCall"},
        {CallEventTypeT::CeThisPartyDisconnectedNormalCall, "CallEventTypeT::CeThisPartyDisconnectedNormalCall"},
        {CallEventTypeT::CeOtherPartyDisconnectedNormalCall, "CallEventTypeT::CeOtherPartyDisconnectedNormalCall"},
        {CallEventTypeT::CeThisPartySuspendedNormalCall, "CallEventTypeT::CeThisPartySuspendedNormalCall"},
        {CallEventTypeT::CeThisPartyRetrievedNormalCall, "CallEventTypeT::CeThisPartyRetrievedNormalCall"},
        {CallEventTypeT::CeThisPartyTransferredNormalCall, "CallEventTypeT::CeThisPartyTransferredNormalCall"},
        {CallEventTypeT::CeDestSeizedConsultCall, "CallEventTypeT::CeDestSeizedConsultCall"},
        {CallEventTypeT::CeOtherPartyAnsweredConsultCall, "CallEventTypeT::CeOtherPartyAnsweredConsultCall"},
        {CallEventTypeT::CeThisPartyDisconnectedConsultCall, "CallEventTypeT::CeThisPartyDisconnectedConsultCall"},
        {CallEventTypeT::CeOtherPartyDisconnectedConsultCall, "CallEventTypeT::CeOtherPartyDisconnectedConsultCall"},
        {CallEventTypeT::CeThisPartyTransferredConsultCall, "CallEventTypeT::CeThisPartyTransferredConsultCall"},
        {CallEventTypeT::CeOtherPartyTransferredConsultCall, "CallEventTypeT::CeOtherPartyTransferredConsultCall"},
        {CallEventTypeT::CeThisPartyConferencedConferenceCall, "CallEventTypeT::CeThisPartyConferencedConferenceCall"},
        {CallEventTypeT::CeOtherPartyConferencedConferenceCall, "CallEventTypeT::CeOtherPartyConferencedConferenceCall"},
        {CallEventTypeT::CeThisPartyDisconnectConferenceCall, "CallEventTypeT::CeThisPartyDisconnectConferenceCall"},
        {CallEventTypeT::CeOtherPartyDisconnectConferenceCall, "CallEventTypeT::CeOtherPartyDisconnectConferenceCall"},
        {CallEventTypeT::CeThisPartyConferencedMonitorCall, "CallEventTypeT::CeThisPartyConferencedMonitorCall"},
        {CallEventTypeT::CeOtherPartyConferencedMonitorCall, "CallEventTypeT::CeOtherPartyConferencedMonitorCall"},
        {CallEventTypeT::CeThisPartyDisconnectMonitorCall, "CallEventTypeT::CeThisPartyDisconnectMonitorCall"},
        {CallEventTypeT::CeOtherPartyDisconnectMonitorCall, "CallEventTypeT::CeOtherPartyDisconnectMonitorCall"},
        {CallEventTypeT::CeThisPartyConferencedIntrudeCall, "CallEventTypeT::CeThisPartyConferencedIntrudeCall"},
        {CallEventTypeT::CeOtherPartyConferencedIntrudeCall, "CallEventTypeT::CeOtherPartyConferencedIntrudeCall"},
        {CallEventTypeT::CeThisPartyDisconnectIntrudeCall, "CallEventTypeT::CeThisPartyDisconnectIntrudeCall"},
        {CallEventTypeT::CeOtherPartyDisconnectIntrudeCall, "CallEventTypeT::CeOtherPartyDisconnectIntrudeCall"},
        {0, NULL}
    };

    CallEventTypeT::CallEventTypeT() : _value(CeUnKnownEvent) {
    }

    CallEventTypeT::CallEventTypeT(int32_t value) : _value(value) {
    }

    int32_t CallEventTypeT::get_value() const {
        return _value;
    }

    std::string CallEventTypeT::get_desc() const {
        const struct desc_t* ptr = CallEventTypeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool CallEventTypeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool CallEventTypeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool CallEventTypeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool CallEventTypeT::operator==(const CallEventTypeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool CallEventTypeT::operator!=(const CallEventTypeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool CallEventTypeT::operator< (const CallEventTypeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const CallEventTypeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const CallEventTypeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const CallEventTypeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const CallEventTypeT& e) {
        o << e.get_value();
        return o;
    }


    const struct PartyAttributeT::desc_t PartyAttributeT::descs[] = {
        {PartyAttributeT::PaUnknown, "PartyAttributeT::PaUnknown"},
        {PartyAttributeT::PaInternal, "PartyAttributeT::PaInternal"},
        {PartyAttributeT::PaNormal, "PartyAttributeT::PaNormal"},
        {0, NULL}
    };

    PartyAttributeT::PartyAttributeT() : _value(PaUnknown) {
    }

    PartyAttributeT::PartyAttributeT(int32_t value) : _value(value) {
    }

    int32_t PartyAttributeT::get_value() const {
        return _value;
    }

    std::string PartyAttributeT::get_desc() const {
        const struct desc_t* ptr = PartyAttributeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool PartyAttributeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool PartyAttributeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool PartyAttributeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool PartyAttributeT::operator==(const PartyAttributeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool PartyAttributeT::operator!=(const PartyAttributeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool PartyAttributeT::operator< (const PartyAttributeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const PartyAttributeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const PartyAttributeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const PartyAttributeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const PartyAttributeT& e) {
        o << e.get_value();
        return o;
    }


    const struct CallEventReasonT::desc_t CallEventReasonT::descs[] = {
        {CallEventReasonT::CerSuccess, "CallEventReasonT::CerSuccess"},
        {CallEventReasonT::CerInvokeComplete, "CallEventReasonT::CerInvokeComplete"},
        {CallEventReasonT::CerCallDestBusy, "CallEventReasonT::CerCallDestBusy"},
        {CallEventReasonT::CerCallNoAnswer, "CallEventReasonT::CerCallNoAnswer"},
        {CallEventReasonT::CerCallDestUnknown, "CallEventReasonT::CerCallDestUnknown"},
        {CallEventReasonT::CerCallDestInvalid, "CallEventReasonT::CerCallDestInvalid"},
        {CallEventReasonT::CerCallTimeout, "CallEventReasonT::CerCallTimeout"},
        {CallEventReasonT::CerUnloginInitial, "CallEventReasonT::CerUnloginInitial"},
        {CallEventReasonT::CerUnloginLogout, "CallEventReasonT::CerUnloginLogout"},
        {CallEventReasonT::CerUnloginSelfForceout, "CallEventReasonT::CerUnloginSelfForceout"},
        {CallEventReasonT::CerUnloginOtherForceout, "CallEventReasonT::CerUnloginOtherForceout"},
        {CallEventReasonT::CerUnloginBackup, "CallEventReasonT::CerUnloginBackup"},
        {CallEventReasonT::CerUnloginResignin, "CallEventReasonT::CerUnloginResignin"},
        {CallEventReasonT::CerUnloginElse, "CallEventReasonT::CerUnloginElse"},
        {CallEventReasonT::CerIdleSelfLogin, "CallEventReasonT::CerIdleSelfLogin"},
        {CallEventReasonT::CerIdleOtherLogin, "CallEventReasonT::CerIdleOtherLogin"},
        {CallEventReasonT::CerIdleNormalSelfHangup, "CallEventReasonT::CerIdleNormalSelfHangup"},
        {CallEventReasonT::CerIdleNormalOtherHangup, "CallEventReasonT::CerIdleNormalOtherHangup"},
        {CallEventReasonT::CerIdleErrorSelfHangup, "CallEventReasonT::CerIdleErrorSelfHangup"},
        {CallEventReasonT::CerIdleErrorOtherHangup, "CallEventReasonT::CerIdleErrorOtherHangup"},
        {CallEventReasonT::CerIdleUnlock, "CallEventReasonT::CerIdleUnlock"},
        {CallEventReasonT::CerIdleIdle, "CallEventReasonT::CerIdleIdle"},
        {CallEventReasonT::CerIdleSelfSet, "CallEventReasonT::CerIdleSelfSet"},
        {CallEventReasonT::CerIdleOtherSet, "CallEventReasonT::CerIdleOtherSet"},
        {CallEventReasonT::CerIdleElse, "CallEventReasonT::CerIdleElse"},
        {CallEventReasonT::CerTalkSelfCreat, "CallEventReasonT::CerTalkSelfCreat"},
        {CallEventReasonT::CerTalkOtherCreat, "CallEventReasonT::CerTalkOtherCreat"},
        {CallEventReasonT::CerTalkSelfRetrieve, "CallEventReasonT::CerTalkSelfRetrieve"},
        {CallEventReasonT::CerTalkOtherRetrieve, "CallEventReasonT::CerTalkOtherRetrieve"},
        {CallEventReasonT::CerTalkElse, "CallEventReasonT::CerTalkElse"},
        {0, NULL}
    };

    CallEventReasonT::CallEventReasonT() : _value(CerSuccess) {
    }

    CallEventReasonT::CallEventReasonT(int32_t value) : _value(value) {
    }

    int32_t CallEventReasonT::get_value() const {
        return _value;
    }

    std::string CallEventReasonT::get_desc() const {
        const struct desc_t* ptr = CallEventReasonT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool CallEventReasonT::operator==(int32_t value) const {
        return _value == value;
    }

    bool CallEventReasonT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool CallEventReasonT::operator< (int32_t value) const {
        return _value < value;
    }

    bool CallEventReasonT::operator==(const CallEventReasonT& rhs) const {
        return _value == rhs.get_value();
    }

    bool CallEventReasonT::operator!=(const CallEventReasonT& rhs) const {
        return _value != rhs.get_value();
    }

    bool CallEventReasonT::operator< (const CallEventReasonT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const CallEventReasonT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const CallEventReasonT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const CallEventReasonT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const CallEventReasonT& e) {
        o << e.get_value();
        return o;
    }

    AgentEventT::AgentEventT() {
    }

    AgentEventT::~AgentEventT() {
    }

    bool AgentEventT::operator==(const AgentEventT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (eventId != rhs.eventId) {
            return false;
        }
        if (agentDn != rhs.agentDn) {
            return false;
        }
        if (callId != rhs.callId) {
            return false;
        }
        if (sessionId != rhs.sessionId) {
            return false;
        }
        if (agentStatus != rhs.agentStatus) {
            return false;
        }
        if (originalCallid != rhs.originalCallid) {
            return false;
        }
        if (partyNum != rhs.partyNum) {
            return false;
        }
        if (otherParty != rhs.otherParty) {
            return false;
        }
        if (otherAttr != rhs.otherAttr) {
            return false;
        }
        if (originatingParty != rhs.originatingParty) {
            return false;
        }
        if (originalAni != rhs.originalAni) {
            return false;
        }
        if (originalDnis != rhs.originalDnis) {
            return false;
        }
        if (reason != rhs.reason) {
            return false;
        }
        if (timestamp != rhs.timestamp) {
            return false;
        }
        return true;
    }

    bool AgentEventT::operator!=(const AgentEventT& rhs) const {
        return !(*this == rhs);
    }

    bool AgentEventT::operator< (const AgentEventT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (agentId < rhs.agentId) {
            return true;
        }
        else if (rhs.agentId < agentId) {
            return false;
        }

        if (eventId < rhs.eventId) {
            return true;
        }
        else if (rhs.eventId < eventId) {
            return false;
        }

        if (agentDn < rhs.agentDn) {
            return true;
        }
        else if (rhs.agentDn < agentDn) {
            return false;
        }

        if (callId < rhs.callId) {
            return true;
        }
        else if (rhs.callId < callId) {
            return false;
        }

        if (sessionId < rhs.sessionId) {
            return true;
        }
        else if (rhs.sessionId < sessionId) {
            return false;
        }

        if (agentStatus < rhs.agentStatus) {
            return true;
        }
        else if (rhs.agentStatus < agentStatus) {
            return false;
        }

        if (originalCallid < rhs.originalCallid) {
            return true;
        }
        else if (rhs.originalCallid < originalCallid) {
            return false;
        }

        if (partyNum < rhs.partyNum) {
            return true;
        }
        else if (rhs.partyNum < partyNum) {
            return false;
        }

        if (otherParty < rhs.otherParty) {
            return true;
        }
        else if (rhs.otherParty < otherParty) {
            return false;
        }

        if (otherAttr < rhs.otherAttr) {
            return true;
        }
        else if (rhs.otherAttr < otherAttr) {
            return false;
        }

        if (originatingParty < rhs.originatingParty) {
            return true;
        }
        else if (rhs.originatingParty < originatingParty) {
            return false;
        }

        if (originalAni < rhs.originalAni) {
            return true;
        }
        else if (rhs.originalAni < originalAni) {
            return false;
        }

        if (originalDnis < rhs.originalDnis) {
            return true;
        }
        else if (rhs.originalDnis < originalDnis) {
            return false;
        }

        if (reason < rhs.reason) {
            return true;
        }
        else if (rhs.reason < reason) {
            return false;
        }

        if (timestamp < rhs.timestamp) {
            return true;
        }
        else if (rhs.timestamp < timestamp) {
            return false;
        }

        return false;
    }

    int32_t AgentEventT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                int32_t ele_var2;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var2);
                if (ret < 0) { return ret; }
                nread += ret;
                eventId = ele_var2;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, sessionId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                int32_t ele_var3;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var3);
                if (ret < 0) { return ret; }
                nread += ret;
                agentStatus = ele_var3;
                break;
            case 7:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalCallid);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, partyNum);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 9:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, otherParty);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 10:
                int32_t ele_var4;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var4);
                if (ret < 0) { return ret; }
                nread += ret;
                otherAttr = ele_var4;
                break;
            case 11:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originatingParty);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 12:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalAni);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 13:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalDnis);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 14:
                int32_t ele_var5;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var5);
                if (ret < 0) { return ret; }
                nread += ret;
                reason = ele_var5;
                break;
            case 15:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, timestamp);
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

    int32_t AgentEventT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("AgentEventT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("eventId", bgcc::IDINT32, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(eventId.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentDn);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(callId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("sessionId", bgcc::IDINT64, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(sessionId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentStatus", bgcc::IDINT32, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(agentStatus.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalCallid", bgcc::IDSTR, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalCallid);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("partyNum", bgcc::IDINT32, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(partyNum);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("otherParty", bgcc::IDSTR, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeString(otherParty);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("otherAttr", bgcc::IDINT32, 10);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(otherAttr.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originatingParty", bgcc::IDSTR, 11);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originatingParty);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalAni", bgcc::IDSTR, 12);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalAni);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalDnis", bgcc::IDSTR, 13);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalDnis);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("reason", bgcc::IDINT32, 14);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(reason.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timestamp", bgcc::IDINT64, 15);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(timestamp);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    const struct MediaEventTypeT::desc_t MediaEventTypeT::descs[] = {
        {MediaEventTypeT::MeUnKownEvent, "MediaEventTypeT::MeUnKownEvent"},
        {MediaEventTypeT::MeTpRecordStarted, "MediaEventTypeT::MeTpRecordStarted"},
        {MediaEventTypeT::MeOpRecordStarted, "MediaEventTypeT::MeOpRecordStarted"},
        {MediaEventTypeT::MeTpRecordDone, "MediaEventTypeT::MeTpRecordDone"},
        {MediaEventTypeT::MeOpRecordDone, "MediaEventTypeT::MeOpRecordDone"},
        {0, NULL}
    };

    MediaEventTypeT::MediaEventTypeT() : _value(MeUnKownEvent) {
    }

    MediaEventTypeT::MediaEventTypeT(int32_t value) : _value(value) {
    }

    int32_t MediaEventTypeT::get_value() const {
        return _value;
    }

    std::string MediaEventTypeT::get_desc() const {
        const struct desc_t* ptr = MediaEventTypeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool MediaEventTypeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool MediaEventTypeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool MediaEventTypeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool MediaEventTypeT::operator==(const MediaEventTypeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool MediaEventTypeT::operator!=(const MediaEventTypeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool MediaEventTypeT::operator< (const MediaEventTypeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const MediaEventTypeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const MediaEventTypeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const MediaEventTypeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const MediaEventTypeT& e) {
        o << e.get_value();
        return o;
    }


    const struct MediaStateT::desc_t MediaStateT::descs[] = {
        {MediaStateT::MsUnknownState, "MediaStateT::MsUnknownState"},
        {MediaStateT::MsIdleState, "MediaStateT::MsIdleState"},
        {MediaStateT::MsRecordingState, "MediaStateT::MsRecordingState"},
        {0, NULL}
    };

    MediaStateT::MediaStateT() : _value(MsUnknownState) {
    }

    MediaStateT::MediaStateT(int32_t value) : _value(value) {
    }

    int32_t MediaStateT::get_value() const {
        return _value;
    }

    std::string MediaStateT::get_desc() const {
        const struct desc_t* ptr = MediaStateT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool MediaStateT::operator==(int32_t value) const {
        return _value == value;
    }

    bool MediaStateT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool MediaStateT::operator< (int32_t value) const {
        return _value < value;
    }

    bool MediaStateT::operator==(const MediaStateT& rhs) const {
        return _value == rhs.get_value();
    }

    bool MediaStateT::operator!=(const MediaStateT& rhs) const {
        return _value != rhs.get_value();
    }

    bool MediaStateT::operator< (const MediaStateT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const MediaStateT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const MediaStateT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const MediaStateT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const MediaStateT& e) {
        o << e.get_value();
        return o;
    }


    const struct MediaEventReasonT::desc_t MediaEventReasonT::descs[] = {
        {MediaEventReasonT::MerMediaUnknown, "MediaEventReasonT::MerMediaUnknown"},
        {MediaEventReasonT::MerMediaEnd, "MediaEventReasonT::MerMediaEnd"},
        {MediaEventReasonT::MerMediaOther, "MediaEventReasonT::MerMediaOther"},
        {0, NULL}
    };

    MediaEventReasonT::MediaEventReasonT() : _value(MerMediaUnknown) {
    }

    MediaEventReasonT::MediaEventReasonT(int32_t value) : _value(value) {
    }

    int32_t MediaEventReasonT::get_value() const {
        return _value;
    }

    std::string MediaEventReasonT::get_desc() const {
        const struct desc_t* ptr = MediaEventReasonT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool MediaEventReasonT::operator==(int32_t value) const {
        return _value == value;
    }

    bool MediaEventReasonT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool MediaEventReasonT::operator< (int32_t value) const {
        return _value < value;
    }

    bool MediaEventReasonT::operator==(const MediaEventReasonT& rhs) const {
        return _value == rhs.get_value();
    }

    bool MediaEventReasonT::operator!=(const MediaEventReasonT& rhs) const {
        return _value != rhs.get_value();
    }

    bool MediaEventReasonT::operator< (const MediaEventReasonT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const MediaEventReasonT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const MediaEventReasonT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const MediaEventReasonT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const MediaEventReasonT& e) {
        o << e.get_value();
        return o;
    }

    MediaEventT::MediaEventT() {
    }

    MediaEventT::~MediaEventT() {
    }

    bool MediaEventT::operator==(const MediaEventT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (eventType != rhs.eventType) {
            return false;
        }
        if (agentDn != rhs.agentDn) {
            return false;
        }
        if (callId != rhs.callId) {
            return false;
        }
        if (sessionId != rhs.sessionId) {
            return false;
        }
        if (state != rhs.state) {
            return false;
        }
        if (reason != rhs.reason) {
            return false;
        }
        if (otherParty != rhs.otherParty) {
            return false;
        }
        if (buffer != rhs.buffer) {
            return false;
        }
        if (timestamp != rhs.timestamp) {
            return false;
        }
        return true;
    }

    bool MediaEventT::operator!=(const MediaEventT& rhs) const {
        return !(*this == rhs);
    }

    bool MediaEventT::operator< (const MediaEventT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (agentId < rhs.agentId) {
            return true;
        }
        else if (rhs.agentId < agentId) {
            return false;
        }

        if (eventType < rhs.eventType) {
            return true;
        }
        else if (rhs.eventType < eventType) {
            return false;
        }

        if (agentDn < rhs.agentDn) {
            return true;
        }
        else if (rhs.agentDn < agentDn) {
            return false;
        }

        if (callId < rhs.callId) {
            return true;
        }
        else if (rhs.callId < callId) {
            return false;
        }

        if (sessionId < rhs.sessionId) {
            return true;
        }
        else if (rhs.sessionId < sessionId) {
            return false;
        }

        if (state < rhs.state) {
            return true;
        }
        else if (rhs.state < state) {
            return false;
        }

        if (reason < rhs.reason) {
            return true;
        }
        else if (rhs.reason < reason) {
            return false;
        }

        if (otherParty < rhs.otherParty) {
            return true;
        }
        else if (rhs.otherParty < otherParty) {
            return false;
        }

        if (buffer < rhs.buffer) {
            return true;
        }
        else if (rhs.buffer < buffer) {
            return false;
        }

        if (timestamp < rhs.timestamp) {
            return true;
        }
        else if (rhs.timestamp < timestamp) {
            return false;
        }

        return false;
    }

    int32_t MediaEventT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                int32_t ele_var6;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var6);
                if (ret < 0) { return ret; }
                nread += ret;
                eventType = ele_var6;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, sessionId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                int32_t ele_var7;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var7);
                if (ret < 0) { return ret; }
                nread += ret;
                state = ele_var7;
                break;
            case 7:
                int32_t ele_var8;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var8);
                if (ret < 0) { return ret; }
                nread += ret;
                reason = ele_var8;
                break;
            case 8:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, otherParty);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 9:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, buffer);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 10:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, timestamp);
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

    int32_t MediaEventT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("MediaEventT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("eventType", bgcc::IDINT32, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(eventType.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentDn);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(callId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("sessionId", bgcc::IDINT64, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(sessionId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("state", bgcc::IDINT32, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(state.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("reason", bgcc::IDINT32, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(reason.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("otherParty", bgcc::IDSTR, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeString(otherParty);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("buffer", bgcc::IDSTR, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeString(buffer);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timestamp", bgcc::IDINT64, 10);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(timestamp);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    const struct RouteEventTypeT::desc_t RouteEventTypeT::descs[] = {
        {RouteEventTypeT::ReInQueue, "RouteEventTypeT::ReInQueue"},
        {RouteEventTypeT::ReOutQueue, "RouteEventTypeT::ReOutQueue"},
        {0, NULL}
    };

    RouteEventTypeT::RouteEventTypeT() : _value(ReInQueue) {
    }

    RouteEventTypeT::RouteEventTypeT(int32_t value) : _value(value) {
    }

    int32_t RouteEventTypeT::get_value() const {
        return _value;
    }

    std::string RouteEventTypeT::get_desc() const {
        const struct desc_t* ptr = RouteEventTypeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool RouteEventTypeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool RouteEventTypeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool RouteEventTypeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool RouteEventTypeT::operator==(const RouteEventTypeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool RouteEventTypeT::operator!=(const RouteEventTypeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool RouteEventTypeT::operator< (const RouteEventTypeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const RouteEventTypeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const RouteEventTypeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const RouteEventTypeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const RouteEventTypeT& e) {
        o << e.get_value();
        return o;
    }

    RouteEventT::RouteEventT() {
    }

    RouteEventT::~RouteEventT() {
    }

    bool RouteEventT::operator==(const RouteEventT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (eventType != rhs.eventType) {
            return false;
        }
        if (agentDn != rhs.agentDn) {
            return false;
        }
        if (callId != rhs.callId) {
            return false;
        }
        if (sessionId != rhs.sessionId) {
            return false;
        }
        if (requestId != rhs.requestId) {
            return false;
        }
        if (originalAni != rhs.originalAni) {
            return false;
        }
        if (originalDnis != rhs.originalDnis) {
            return false;
        }
        if (timestamp != rhs.timestamp) {
            return false;
        }
        return true;
    }

    bool RouteEventT::operator!=(const RouteEventT& rhs) const {
        return !(*this == rhs);
    }

    bool RouteEventT::operator< (const RouteEventT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (agentId < rhs.agentId) {
            return true;
        }
        else if (rhs.agentId < agentId) {
            return false;
        }

        if (eventType < rhs.eventType) {
            return true;
        }
        else if (rhs.eventType < eventType) {
            return false;
        }

        if (agentDn < rhs.agentDn) {
            return true;
        }
        else if (rhs.agentDn < agentDn) {
            return false;
        }

        if (callId < rhs.callId) {
            return true;
        }
        else if (rhs.callId < callId) {
            return false;
        }

        if (sessionId < rhs.sessionId) {
            return true;
        }
        else if (rhs.sessionId < sessionId) {
            return false;
        }

        if (requestId < rhs.requestId) {
            return true;
        }
        else if (rhs.requestId < requestId) {
            return false;
        }

        if (originalAni < rhs.originalAni) {
            return true;
        }
        else if (rhs.originalAni < originalAni) {
            return false;
        }

        if (originalDnis < rhs.originalDnis) {
            return true;
        }
        else if (rhs.originalDnis < originalDnis) {
            return false;
        }

        if (timestamp < rhs.timestamp) {
            return true;
        }
        else if (rhs.timestamp < timestamp) {
            return false;
        }

        return false;
    }

    int32_t RouteEventT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                int32_t ele_var9;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var9);
                if (ret < 0) { return ret; }
                nread += ret;
                eventType = ele_var9;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, sessionId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, requestId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 7:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalAni);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalDnis);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 9:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, timestamp);
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

    int32_t RouteEventT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("RouteEventT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("eventType", bgcc::IDINT32, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(eventType.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentDn);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(callId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("sessionId", bgcc::IDINT64, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(sessionId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("requestId", bgcc::IDINT64, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(requestId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalAni", bgcc::IDSTR, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalAni);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalDnis", bgcc::IDSTR, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalDnis);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timestamp", bgcc::IDINT64, 9);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(timestamp);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }

    const struct OtherEventTypeT::desc_t OtherEventTypeT::descs[] = {
        {OtherEventTypeT::IMSDisconnect, "OtherEventTypeT::IMSDisconnect"},
        {OtherEventTypeT::IMSMasterChange, "OtherEventTypeT::IMSMasterChange"},
        {OtherEventTypeT::IMSOperationFailed, "OtherEventTypeT::IMSOperationFailed"},
        {OtherEventTypeT::ACDDisconnect, "OtherEventTypeT::ACDDisconnect"},
        {OtherEventTypeT::ACDMasterChange, "OtherEventTypeT::ACDMasterChange"},
        {OtherEventTypeT::ACDOperationFailed, "OtherEventTypeT::ACDOperationFailed"},
        {OtherEventTypeT::ACDReLoginSuccess, "OtherEventTypeT::ACDReLoginSuccess"},
        {OtherEventTypeT::ACDReLoginFailed, "OtherEventTypeT::ACDReLoginFailed"},
        {0, NULL}
    };

    OtherEventTypeT::OtherEventTypeT() : _value(IMSDisconnect) {
    }

    OtherEventTypeT::OtherEventTypeT(int32_t value) : _value(value) {
    }

    int32_t OtherEventTypeT::get_value() const {
        return _value;
    }

    std::string OtherEventTypeT::get_desc() const {
        const struct desc_t* ptr = OtherEventTypeT::descs;
        while (ptr->desc) {
            if (ptr->value == _value) {
                return ptr->desc;
            }
            ++ptr;
        }
        return "Unknown value";
    }

    bool OtherEventTypeT::operator==(int32_t value) const {
        return _value == value;
    }

    bool OtherEventTypeT::operator!=(int32_t value) const {
        return _value != value;
    }

    bool OtherEventTypeT::operator< (int32_t value) const {
        return _value < value;
    }

    bool OtherEventTypeT::operator==(const OtherEventTypeT& rhs) const {
        return _value == rhs.get_value();
    }

    bool OtherEventTypeT::operator!=(const OtherEventTypeT& rhs) const {
        return _value != rhs.get_value();
    }

    bool OtherEventTypeT::operator< (const OtherEventTypeT& rhs) const {
        return _value < rhs.get_value();
    }

    bool operator==(int32_t value, const OtherEventTypeT& rhs) {
        return value == rhs.get_value();
    }

    bool operator!=(int32_t value, const OtherEventTypeT& rhs) {
        return value != rhs.get_value();
    }

    bool operator< (int32_t value, const OtherEventTypeT& rhs) {
        return value < rhs.get_value();
    }

    std::ostream& operator<<(std::ostream& o, const OtherEventTypeT& e) {
        o << e.get_value();
        return o;
    }

    OtherEventT::OtherEventT() {
    }

    OtherEventT::~OtherEventT() {
    }

    bool OtherEventT::operator==(const OtherEventT& rhs) const {
        if (this == &rhs) {
            return true;
        }
        if (agentId != rhs.agentId) {
            return false;
        }
        if (eventType != rhs.eventType) {
            return false;
        }
        if (agentDn != rhs.agentDn) {
            return false;
        }
        if (callId != rhs.callId) {
            return false;
        }
        if (sessionId != rhs.sessionId) {
            return false;
        }
        if (originalAni != rhs.originalAni) {
            return false;
        }
        if (originalDnis != rhs.originalDnis) {
            return false;
        }
        if (timestamp != rhs.timestamp) {
            return false;
        }
        return true;
    }

    bool OtherEventT::operator!=(const OtherEventT& rhs) const {
        return !(*this == rhs);
    }

    bool OtherEventT::operator< (const OtherEventT& rhs) const {
        if (this == &rhs) {
            return false;
        }

        if (agentId < rhs.agentId) {
            return true;
        }
        else if (rhs.agentId < agentId) {
            return false;
        }

        if (eventType < rhs.eventType) {
            return true;
        }
        else if (rhs.eventType < eventType) {
            return false;
        }

        if (agentDn < rhs.agentDn) {
            return true;
        }
        else if (rhs.agentDn < agentDn) {
            return false;
        }

        if (callId < rhs.callId) {
            return true;
        }
        else if (rhs.callId < callId) {
            return false;
        }

        if (sessionId < rhs.sessionId) {
            return true;
        }
        else if (rhs.sessionId < sessionId) {
            return false;
        }

        if (originalAni < rhs.originalAni) {
            return true;
        }
        else if (rhs.originalAni < originalAni) {
            return false;
        }

        if (originalDnis < rhs.originalDnis) {
            return true;
        }
        else if (rhs.originalDnis < originalDnis) {
            return false;
        }

        if (timestamp < rhs.timestamp) {
            return true;
        }
        else if (rhs.timestamp < timestamp) {
            return false;
        }

        return false;
    }

    int32_t OtherEventT::read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto){
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
                int32_t ele_var10;
                ret = proto->readInt32(OFFSET_PTR(request, nread), request_len - nread, ele_var10);
                if (ret < 0) { return ret; }
                nread += ret;
                eventType = ele_var10;
                break;
            case 3:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, agentDn);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 4:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, callId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 5:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, sessionId);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 6:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalAni);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 7:
                ret = proto->readString(OFFSET_PTR(request, nread), request_len - nread, originalDnis);
                if (ret < 0) { return ret; }
                nread += ret;
                break;
            case 8:
                ret = proto->readInt64(OFFSET_PTR(request, nread), request_len - nread, timestamp);
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

    int32_t OtherEventT::write(bgcc::SharedPointer<bgcc::IProtocol> proto) const {
        int32_t ret = 0;

        ret = proto->writeStructBegin("OtherEventT");
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentId", bgcc::IDSTR, 1);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("eventType", bgcc::IDINT32, 2);
        if (ret < 0) { return ret; }
        ret = proto->writeInt32(eventType.get_value());
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("agentDn", bgcc::IDSTR, 3);
        if (ret < 0) { return ret; }
        ret = proto->writeString(agentDn);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("callId", bgcc::IDSTR, 4);
        if (ret < 0) { return ret; }
        ret = proto->writeString(callId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("sessionId", bgcc::IDINT64, 5);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(sessionId);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalAni", bgcc::IDSTR, 6);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalAni);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("originalDnis", bgcc::IDSTR, 7);
        if (ret < 0) { return ret; }
        ret = proto->writeString(originalDnis);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldBegin("timestamp", bgcc::IDINT64, 8);
        if (ret < 0) { return ret; }
        ret = proto->writeInt64(timestamp);
        if (ret < 0) { return ret; }
        ret = proto->writeFieldEnd();
        if (ret < 0) { return ret; }

        ret = proto->writeFieldStop();
        if (ret < 0) { return ret; }

        return proto->writeStructEnd();
    }
}


