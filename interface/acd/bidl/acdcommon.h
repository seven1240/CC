#ifndef _BIDL2SL_ACDCOMMON_H_
#define _BIDL2SL_ACDCOMMON_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <bgcc.h>

namespace acd {

    class AcdResultT {
    public:
        enum {
            ArSuccess = 0,
            ArAgentIdIsEmpty = 1,
            ArAgentDnIsEmpty = 2,
            ArSkillIsEmpty = 3,
            ArCallerIdIsEmpty = 4,
            ArDestIdIsEmpty = 5,
            ArDestDnIsEmpty = 6,
            ArKeyIsEmpty = 7,
            ArValueIsEmpty = 8,
            ArDigitalsIsEmpty = 9,
            ArFilenameIsEmpty = 10,
            ArAgentIdNotExist = 11,
            ArAgentPasswordError = 12,
            ArAgentSkillError = 13,
            ArNotMaster = 14,
            ArAgentDnBeOccupied = 15,
            ArHasSigned = 16,
            ArNoSignin = 17,
            ArDestAgentIdNotExist = 18,
            ArDestAgentDnNotExist = 19,
            ArSkillNotExist = 20,
            ArRouteRequestNotExist = 21,
            ArAgentStatusIsWrong = 22,
            ArImsError = 23,
            ArPasswordError = 24,
            ArFailed = 25,
            ArApFailed = 26,
            ArConnAcdFail = 27
        };

        AcdResultT();
        AcdResultT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const AcdResultT& rhs) const;
        bool operator==(const AcdResultT& rhs) const;
        bool operator< (const AcdResultT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const AcdResultT&);
    bool operator!=(int32_t value, const AcdResultT&);
    bool operator< (int32_t value, const AcdResultT&);
    std::ostream& operator<<(std::ostream& o, const AcdResultT&);


    class StatusChangeT {
    public:
        enum {
            ScReady = 0,
            ScBusy = 1
        };

        StatusChangeT();
        StatusChangeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const StatusChangeT& rhs) const;
        bool operator==(const StatusChangeT& rhs) const;
        bool operator< (const StatusChangeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const StatusChangeT&);
    bool operator!=(int32_t value, const StatusChangeT&);
    bool operator< (int32_t value, const StatusChangeT&);
    std::ostream& operator<<(std::ostream& o, const StatusChangeT&);


    class AgentStatusT {
    public:
        enum {
            AsUnknownState = 0,
            AsUnLoginState = 1,
            AsReadyState = 2,
            AsBusyState = 3,
            AsRestState = 4,
            AsLockState = 5,
            AsAlertingState = 6,
            AsHalfAlertingState = 7,
            AsConnectingState = 8,
            AsConnectedState = 9,
            AsHalfConnectedState = 10,
            AsInternalConnectedState = 11,
            AsSuspendedState = 12,
            AsConsultConnectingState = 13,
            AsConsultConnectedState = 14,
            AsConferenceState = 15,
            AsMonitorState = 16,
            AsInsertState = 17,
            AsMonitoredState = 18,
            AsInsertedState = 19
        };

        AgentStatusT();
        AgentStatusT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const AgentStatusT& rhs) const;
        bool operator==(const AgentStatusT& rhs) const;
        bool operator< (const AgentStatusT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const AgentStatusT&);
    bool operator!=(int32_t value, const AgentStatusT&);
    bool operator< (int32_t value, const AgentStatusT&);
    std::ostream& operator<<(std::ostream& o, const AgentStatusT&);


    class CallModeT {
    public:
        enum {
            CmNormal = 0,
            CmOffhook = 1
        };

        CallModeT();
        CallModeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const CallModeT& rhs) const;
        bool operator==(const CallModeT& rhs) const;
        bool operator< (const CallModeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const CallModeT&);
    bool operator!=(int32_t value, const CallModeT&);
    bool operator< (int32_t value, const CallModeT&);
    std::ostream& operator<<(std::ostream& o, const CallModeT&);


    class CallTypeT {
    public:
        enum {
            CtAgent = 0,
            CtOut = 1
        };

        CallTypeT();
        CallTypeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const CallTypeT& rhs) const;
        bool operator==(const CallTypeT& rhs) const;
        bool operator< (const CallTypeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const CallTypeT&);
    bool operator!=(int32_t value, const CallTypeT&);
    bool operator< (int32_t value, const CallTypeT&);
    std::ostream& operator<<(std::ostream& o, const CallTypeT&);


    class ConferenceT {
    public:
        enum {
            ConferenceMute = 0,
            ConferenceSpeak = 1,
            ConferenceAll = 2
        };

        ConferenceT();
        ConferenceT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const ConferenceT& rhs) const;
        bool operator==(const ConferenceT& rhs) const;
        bool operator< (const ConferenceT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const ConferenceT&);
    bool operator!=(int32_t value, const ConferenceT&);
    bool operator< (int32_t value, const ConferenceT&);
    std::ostream& operator<<(std::ostream& o, const ConferenceT&);

    class AgentInfoT {
    public:
        AgentInfoT();
        ~AgentInfoT();

        std::string agentId;
        std::string agentDn;
        int64_t loginTime;
        AgentStatusT currStatus;
        int64_t currStatusTime;
        int64_t answerTime;
        int64_t currTime;
        std::string origCaller;
        std::string origCallee;
        int32_t privQueueNum;
        int32_t callTimes;
        int32_t answerTimes;
        int64_t freeTotalTime;
        int64_t busyTotalTime;
        int64_t resetTotalTime;
        int64_t callTotalTime;
        int64_t answerTotalTime;
        std::string agentIP;

        bool operator==(const AgentInfoT& rhs) const;
        bool operator!=(const AgentInfoT& rhs) const;
        bool operator< (const AgentInfoT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    typedef std::vector<std::string>  StringListT;
    typedef std::vector<AgentInfoT>  AgentInfoListT;
    class QueueInfoT {
    public:
        QueueInfoT();
        ~QueueInfoT();

        std::string callId;
        int64_t contactId;
        int64_t requestId;
        std::string origCaller;
        std::string origCallee;
        int64_t startTime;
        int64_t currTime;
        int64_t changeTime;

        bool operator==(const QueueInfoT& rhs) const;
        bool operator!=(const QueueInfoT& rhs) const;
        bool operator< (const QueueInfoT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    typedef std::vector<QueueInfoT>  QueueInfoListT;
    class SysInfoT {
    public:
        SysInfoT();
        ~SysInfoT();

        int32_t totalAgents;
        int32_t totalCalls;
        int32_t ivrCalls;
        int32_t agentCalls;
        int32_t queueCalls;
        int32_t privQueueCalls;

        bool operator==(const SysInfoT& rhs) const;
        bool operator!=(const SysInfoT& rhs) const;
        bool operator< (const SysInfoT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };


    class CallEventTypeT {
    public:
        enum {
            CeUnKnownEvent = 0,
            CeInboundCallInternalCall = 1,
            CeDestSeizedInternalCall = 2,
            CeThisPartyAnsweredInternalCall = 3,
            CeOtherPartyAnsweredInternalCall = 4,
            CeThisPartyDisconnectedInternalCall = 5,
            CeOtherPartyDisconnectedInternalCall = 6,
            CeInboundCallNormalCall = 7,
            CeDestSeizedNormalCall = 8,
            CeThisPartyAnsweredNormalCall = 9,
            CeOtherPartyAnsweredNormalCall = 10,
            CeThisPartyDisconnectedNormalCall = 11,
            CeOtherPartyDisconnectedNormalCall = 12,
            CeThisPartySuspendedNormalCall = 13,
            CeThisPartyRetrievedNormalCall = 14,
            CeThisPartyTransferredNormalCall = 15,
            CeDestSeizedConsultCall = 16,
            CeOtherPartyAnsweredConsultCall = 17,
            CeThisPartyDisconnectedConsultCall = 18,
            CeOtherPartyDisconnectedConsultCall = 19,
            CeThisPartyTransferredConsultCall = 20,
            CeOtherPartyTransferredConsultCall = 21,
            CeThisPartyConferencedConferenceCall = 22,
            CeOtherPartyConferencedConferenceCall = 23,
            CeThisPartyDisconnectConferenceCall = 24,
            CeOtherPartyDisconnectConferenceCall = 25,
            CeThisPartyConferencedMonitorCall = 26,
            CeOtherPartyConferencedMonitorCall = 27,
            CeThisPartyDisconnectMonitorCall = 28,
            CeOtherPartyDisconnectMonitorCall = 29,
            CeThisPartyConferencedIntrudeCall = 30,
            CeOtherPartyConferencedIntrudeCall = 31,
            CeThisPartyDisconnectIntrudeCall = 32,
            CeOtherPartyDisconnectIntrudeCall = 33
        };

        CallEventTypeT();
        CallEventTypeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const CallEventTypeT& rhs) const;
        bool operator==(const CallEventTypeT& rhs) const;
        bool operator< (const CallEventTypeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const CallEventTypeT&);
    bool operator!=(int32_t value, const CallEventTypeT&);
    bool operator< (int32_t value, const CallEventTypeT&);
    std::ostream& operator<<(std::ostream& o, const CallEventTypeT&);


    class PartyAttributeT {
    public:
        enum {
            PaUnknown = 0,
            PaInternal = 1,
            PaNormal = 2
        };

        PartyAttributeT();
        PartyAttributeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const PartyAttributeT& rhs) const;
        bool operator==(const PartyAttributeT& rhs) const;
        bool operator< (const PartyAttributeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const PartyAttributeT&);
    bool operator!=(int32_t value, const PartyAttributeT&);
    bool operator< (int32_t value, const PartyAttributeT&);
    std::ostream& operator<<(std::ostream& o, const PartyAttributeT&);


    class CallEventReasonT {
    public:
        enum {
            CerSuccess = 0,
            CerInvokeComplete = 1,
            CerCallDestBusy = 2,
            CerCallNoAnswer = 3,
            CerCallDestUnknown = 4,
            CerCallDestInvalid = 5,
            CerCallTimeout = 6,
            CerUnloginInitial = 7,
            CerUnloginLogout = 8,
            CerUnloginSelfForceout = 9,
            CerUnloginOtherForceout = 10,
            CerUnloginBackup = 11,
            CerUnloginResignin = 12,
            CerUnloginElse = 13,
            CerIdleSelfLogin = 14,
            CerIdleOtherLogin = 15,
            CerIdleNormalSelfHangup = 16,
            CerIdleNormalOtherHangup = 17,
            CerIdleErrorSelfHangup = 18,
            CerIdleErrorOtherHangup = 19,
            CerIdleUnlock = 20,
            CerIdleIdle = 21,
            CerIdleSelfSet = 22,
            CerIdleOtherSet = 23,
            CerIdleElse = 24,
            CerTalkSelfCreat = 25,
            CerTalkOtherCreat = 26,
            CerTalkSelfRetrieve = 27,
            CerTalkOtherRetrieve = 28,
            CerTalkElse = 29
        };

        CallEventReasonT();
        CallEventReasonT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const CallEventReasonT& rhs) const;
        bool operator==(const CallEventReasonT& rhs) const;
        bool operator< (const CallEventReasonT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const CallEventReasonT&);
    bool operator!=(int32_t value, const CallEventReasonT&);
    bool operator< (int32_t value, const CallEventReasonT&);
    std::ostream& operator<<(std::ostream& o, const CallEventReasonT&);

    class AgentEventT {
    public:
        AgentEventT();
        ~AgentEventT();

        std::string agentId;
        CallEventTypeT eventId;
        std::string agentDn;
        std::string callId;
        int64_t sessionId;
        AgentStatusT agentStatus;
        std::string originalCallid;
        int32_t partyNum;
        std::string otherParty;
        PartyAttributeT otherAttr;
        std::string originatingParty;
        std::string originalAni;
        std::string originalDnis;
        CallEventReasonT reason;
        int64_t timestamp;

        bool operator==(const AgentEventT& rhs) const;
        bool operator!=(const AgentEventT& rhs) const;
        bool operator< (const AgentEventT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };


    class MediaEventTypeT {
    public:
        enum {
            MeUnKownEvent = 0,
            MeTpRecordStarted = 1,
            MeOpRecordStarted = 2,
            MeTpRecordDone = 3,
            MeOpRecordDone = 4
        };

        MediaEventTypeT();
        MediaEventTypeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const MediaEventTypeT& rhs) const;
        bool operator==(const MediaEventTypeT& rhs) const;
        bool operator< (const MediaEventTypeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const MediaEventTypeT&);
    bool operator!=(int32_t value, const MediaEventTypeT&);
    bool operator< (int32_t value, const MediaEventTypeT&);
    std::ostream& operator<<(std::ostream& o, const MediaEventTypeT&);


    class MediaStateT {
    public:
        enum {
            MsUnknownState = 0,
            MsIdleState = 1,
            MsRecordingState = 2
        };

        MediaStateT();
        MediaStateT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const MediaStateT& rhs) const;
        bool operator==(const MediaStateT& rhs) const;
        bool operator< (const MediaStateT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const MediaStateT&);
    bool operator!=(int32_t value, const MediaStateT&);
    bool operator< (int32_t value, const MediaStateT&);
    std::ostream& operator<<(std::ostream& o, const MediaStateT&);


    class MediaEventReasonT {
    public:
        enum {
            MerMediaUnknown = 0,
            MerMediaEnd = 1,
            MerMediaOther = 2
        };

        MediaEventReasonT();
        MediaEventReasonT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const MediaEventReasonT& rhs) const;
        bool operator==(const MediaEventReasonT& rhs) const;
        bool operator< (const MediaEventReasonT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const MediaEventReasonT&);
    bool operator!=(int32_t value, const MediaEventReasonT&);
    bool operator< (int32_t value, const MediaEventReasonT&);
    std::ostream& operator<<(std::ostream& o, const MediaEventReasonT&);

    class MediaEventT {
    public:
        MediaEventT();
        ~MediaEventT();

        std::string agentId;
        MediaEventTypeT eventType;
        std::string agentDn;
        std::string callId;
        int64_t sessionId;
        MediaStateT state;
        MediaEventReasonT reason;
        std::string otherParty;
        std::string buffer;
        int64_t timestamp;

        bool operator==(const MediaEventT& rhs) const;
        bool operator!=(const MediaEventT& rhs) const;
        bool operator< (const MediaEventT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };


    class RouteEventTypeT {
    public:
        enum {
            ReInQueue = 0,
            ReOutQueue = 1
        };

        RouteEventTypeT();
        RouteEventTypeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const RouteEventTypeT& rhs) const;
        bool operator==(const RouteEventTypeT& rhs) const;
        bool operator< (const RouteEventTypeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const RouteEventTypeT&);
    bool operator!=(int32_t value, const RouteEventTypeT&);
    bool operator< (int32_t value, const RouteEventTypeT&);
    std::ostream& operator<<(std::ostream& o, const RouteEventTypeT&);

    class RouteEventT {
    public:
        RouteEventT();
        ~RouteEventT();

        std::string agentId;
        RouteEventTypeT eventType;
        std::string agentDn;
        std::string callId;
        int64_t sessionId;
        int64_t requestId;
        std::string originalAni;
        std::string originalDnis;
        int64_t timestamp;

        bool operator==(const RouteEventT& rhs) const;
        bool operator!=(const RouteEventT& rhs) const;
        bool operator< (const RouteEventT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };


    class OtherEventTypeT {
    public:
        enum {
            IMSDisconnect = 0,
            IMSMasterChange = 1,
            IMSOperationFailed = 2,
            ACDDisconnect = 3,
            ACDMasterChange = 4,
            ACDOperationFailed = 5,
            ACDReLoginSuccess = 6,
            ACDReLoginFailed = 7
        };

        OtherEventTypeT();
        OtherEventTypeT(int32_t value);

        int32_t get_value() const;
        std::string get_desc() const;

        bool operator==(int32_t value) const;
        bool operator!=(int32_t value) const;
        bool operator< (int32_t value) const;
        bool operator!=(const OtherEventTypeT& rhs) const;
        bool operator==(const OtherEventTypeT& rhs) const;
        bool operator< (const OtherEventTypeT& rhs) const;

    private:
        int32_t _value;

        static const struct desc_t {
            int32_t value;
            const char* desc;
        } descs[];
    };
    bool operator==(int32_t value, const OtherEventTypeT&);
    bool operator!=(int32_t value, const OtherEventTypeT&);
    bool operator< (int32_t value, const OtherEventTypeT&);
    std::ostream& operator<<(std::ostream& o, const OtherEventTypeT&);

    class OtherEventT {
    public:
        OtherEventT();
        ~OtherEventT();

        std::string agentId;
        OtherEventTypeT eventType;
        std::string agentDn;
        std::string callId;
        int64_t sessionId;
        std::string originalAni;
        std::string originalDnis;
        int64_t timestamp;

        bool operator==(const OtherEventT& rhs) const;
        bool operator!=(const OtherEventT& rhs) const;
        bool operator< (const OtherEventT& rhs) const;
        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

}


#endif
