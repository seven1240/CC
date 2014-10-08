#ifndef _BIDL2SL_ACD_H_
#define _BIDL2SL_ACD_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <bgcc.h>

#include "acdcommon.h"
namespace acd {
    class acdapi : public bgcc::Shareable {
    public:
        virtual ~acdapi() { }

        virtual AcdResultT SignIn(
            const std::string & agentId,
            const std::string & agentDn,
            const std::string & agentPwd,
            const StatusChangeT & statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string & skill,
            int64_t & handle,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SignOut(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SetAgentStatus(
            int64_t handle,
            const std::string & agentId,
            const AgentStatusT & agentStatus,
            const std::string & restReason,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentStatus(
            int64_t handle,
            const std::string & agentId,
            AgentStatusT & agentStatus,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ResetStatuschangetype(
            int64_t handle,
            const std::string & agentId,
            const StatusChangeT & statusChangetype,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ResetAutoAnswer(
            int64_t handle,
            const std::string & agentId,
            bool autoAnswer,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ResetSkill(
            int64_t handle,
            const std::string & agentId,
            const std::string & skill,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Reset(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT OutboundCall(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            int32_t timeout,
            const CallModeT & callMode,
            const CallTypeT & callType,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT AnswerCall(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ReleaseCall(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Hold(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Retrieve(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Consult(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            const CallTypeT & callType,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ConsultReconnect(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ConsultTransfer(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SingleStepTransfer(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            bool isPassthrough,
            const CallTypeT & transferType,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ConsultConference(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ConferenceJoin(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destAgentId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            const ConferenceT & conferenceType,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SetAssociateData(
            int64_t handle,
            const std::string & agentId,
            const std::string & key,
            const std::string & value,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAssociateData(
            int64_t handle,
            const std::string & agentId,
            const std::string & key,
            std::string & value,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT JumptheQueue(
            int64_t handle,
            const std::string & agentId,
            int64_t requestId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ForceSignIn(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const std::string & agentDn,
            const std::string & agentPwd,
            const StatusChangeT & statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string & skill,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ForceSignOut(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ForceSetAgentStatus(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const AgentStatusT & agentStatus,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Listen(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destAgentId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT StopListen(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Insert(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destAgentId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT StopInsert(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SwitchInsertorListen(
            int64_t handle,
            const std::string & agentId,
            const std::string & callerId,
            const std::string & destAgentId,
            const std::string & forCallerDispNum,
            const std::string & forCalleeDispNum,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Break(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SendDTMF(
            int64_t handle,
            const std::string & agentId,
            const std::string & digitals,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT StartPlay(
            int64_t handle,
            const std::string & agentId,
            const std::string & filename,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT StopPlay(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT MuteOn(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT MuteOff(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentDetailByAgentID(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            AgentInfoT & agentInfo,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentDetailByAgentDN(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentDn,
            AgentInfoT & agentInfo,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentDetailsByAgentIDs(
            int64_t handle,
            const std::string & agentId,
            const StringListT & destAgentIdList,
            AgentInfoListT & agentInfoList,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentDetailsByAgentDNs(
            int64_t handle,
            const std::string & agentId,
            const StringListT & destAgentDnList,
            AgentInfoListT & agentInfoList,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetRecordFileName(
            int64_t handle,
            const std::string & agentId,
            std::string & filename,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetSkill(
            int64_t handle,
            const std::string & agentId,
            StringListT & skill,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetRestReason(
            int64_t handle,
            const std::string & agentId,
            StringListT & restReason,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentNumberBySkill(
            int64_t handle,
            const std::string & agentId,
            const std::string & skill,
            int32_t & agentNum,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetAgentDetailsBySkill(
            int64_t handle,
            const std::string & agentId,
            const std::string & skill,
            int32_t & agentNum,
            AgentInfoListT & agentInfoList,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetSkillWaitingNumber(
            int64_t handle,
            const std::string & agentId,
            const std::string & skill,
            int32_t & queueNum,
            int32_t & freeNum,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetSkillWaitingCallInfo(
            int64_t handle,
            const std::string & agentId,
            const std::string & skill,
            int32_t & queueNum,
            QueueInfoListT & queueInfoList,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetPrivateQueue(
            int64_t handle,
            const std::string & agentId,
            const std::string & destAgentId,
            int32_t & queueNum,
            QueueInfoListT & queueInfoList,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT GetSysInfo(
            int64_t handle,
            const std::string & agentId,
            SysInfoT & sysInfo,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT SynchronizeCTITime(
            int64_t handle,
            const std::string & agentId,
            int64_t & timestamp,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT Heartbeat(
            int64_t handle,
            const std::string & agentId,
            const std::map<std::string, std::string>& ctx) = 0;

        virtual AcdResultT ResetConfig(
            const std::string & password,
            const std::map<std::string, std::string>& ctx) = 0;

    };

    class acdapi_SignIn_args {
    public:
        acdapi_SignIn_args();
        virtual ~acdapi_SignIn_args();

        std::string agentId;
        std::string agentDn;
        std::string agentPwd;
        StatusChangeT statusChangetype;
        bool autoAnswer;
        bool fcSignin;
        std::string skill;

        bool operator==(const acdapi_SignIn_args& rhs) const;
        bool operator!=(const acdapi_SignIn_args& rhs) const;
        bool operator< (const acdapi_SignIn_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SignOut_args {
    public:
        acdapi_SignOut_args();
        virtual ~acdapi_SignOut_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_SignOut_args& rhs) const;
        bool operator!=(const acdapi_SignOut_args& rhs) const;
        bool operator< (const acdapi_SignOut_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SetAgentStatus_args {
    public:
        acdapi_SetAgentStatus_args();
        virtual ~acdapi_SetAgentStatus_args();

        int64_t handle;
        std::string agentId;
        AgentStatusT agentStatus;
        std::string restReason;

        bool operator==(const acdapi_SetAgentStatus_args& rhs) const;
        bool operator!=(const acdapi_SetAgentStatus_args& rhs) const;
        bool operator< (const acdapi_SetAgentStatus_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentStatus_args {
    public:
        acdapi_GetAgentStatus_args();
        virtual ~acdapi_GetAgentStatus_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_GetAgentStatus_args& rhs) const;
        bool operator!=(const acdapi_GetAgentStatus_args& rhs) const;
        bool operator< (const acdapi_GetAgentStatus_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ResetStatuschangetype_args {
    public:
        acdapi_ResetStatuschangetype_args();
        virtual ~acdapi_ResetStatuschangetype_args();

        int64_t handle;
        std::string agentId;
        StatusChangeT statusChangetype;

        bool operator==(const acdapi_ResetStatuschangetype_args& rhs) const;
        bool operator!=(const acdapi_ResetStatuschangetype_args& rhs) const;
        bool operator< (const acdapi_ResetStatuschangetype_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ResetAutoAnswer_args {
    public:
        acdapi_ResetAutoAnswer_args();
        virtual ~acdapi_ResetAutoAnswer_args();

        int64_t handle;
        std::string agentId;
        bool autoAnswer;

        bool operator==(const acdapi_ResetAutoAnswer_args& rhs) const;
        bool operator!=(const acdapi_ResetAutoAnswer_args& rhs) const;
        bool operator< (const acdapi_ResetAutoAnswer_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ResetSkill_args {
    public:
        acdapi_ResetSkill_args();
        virtual ~acdapi_ResetSkill_args();

        int64_t handle;
        std::string agentId;
        std::string skill;

        bool operator==(const acdapi_ResetSkill_args& rhs) const;
        bool operator!=(const acdapi_ResetSkill_args& rhs) const;
        bool operator< (const acdapi_ResetSkill_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Reset_args {
    public:
        acdapi_Reset_args();
        virtual ~acdapi_Reset_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_Reset_args& rhs) const;
        bool operator!=(const acdapi_Reset_args& rhs) const;
        bool operator< (const acdapi_Reset_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_OutboundCall_args {
    public:
        acdapi_OutboundCall_args();
        virtual ~acdapi_OutboundCall_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;
        int32_t timeout;
        CallModeT callMode;
        CallTypeT callType;

        bool operator==(const acdapi_OutboundCall_args& rhs) const;
        bool operator!=(const acdapi_OutboundCall_args& rhs) const;
        bool operator< (const acdapi_OutboundCall_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_AnswerCall_args {
    public:
        acdapi_AnswerCall_args();
        virtual ~acdapi_AnswerCall_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_AnswerCall_args& rhs) const;
        bool operator!=(const acdapi_AnswerCall_args& rhs) const;
        bool operator< (const acdapi_AnswerCall_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ReleaseCall_args {
    public:
        acdapi_ReleaseCall_args();
        virtual ~acdapi_ReleaseCall_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_ReleaseCall_args& rhs) const;
        bool operator!=(const acdapi_ReleaseCall_args& rhs) const;
        bool operator< (const acdapi_ReleaseCall_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Hold_args {
    public:
        acdapi_Hold_args();
        virtual ~acdapi_Hold_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_Hold_args& rhs) const;
        bool operator!=(const acdapi_Hold_args& rhs) const;
        bool operator< (const acdapi_Hold_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Retrieve_args {
    public:
        acdapi_Retrieve_args();
        virtual ~acdapi_Retrieve_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_Retrieve_args& rhs) const;
        bool operator!=(const acdapi_Retrieve_args& rhs) const;
        bool operator< (const acdapi_Retrieve_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Consult_args {
    public:
        acdapi_Consult_args();
        virtual ~acdapi_Consult_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;
        CallTypeT callType;

        bool operator==(const acdapi_Consult_args& rhs) const;
        bool operator!=(const acdapi_Consult_args& rhs) const;
        bool operator< (const acdapi_Consult_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ConsultReconnect_args {
    public:
        acdapi_ConsultReconnect_args();
        virtual ~acdapi_ConsultReconnect_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_ConsultReconnect_args& rhs) const;
        bool operator!=(const acdapi_ConsultReconnect_args& rhs) const;
        bool operator< (const acdapi_ConsultReconnect_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ConsultTransfer_args {
    public:
        acdapi_ConsultTransfer_args();
        virtual ~acdapi_ConsultTransfer_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_ConsultTransfer_args& rhs) const;
        bool operator!=(const acdapi_ConsultTransfer_args& rhs) const;
        bool operator< (const acdapi_ConsultTransfer_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SingleStepTransfer_args {
    public:
        acdapi_SingleStepTransfer_args();
        virtual ~acdapi_SingleStepTransfer_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;
        bool isPassthrough;
        CallTypeT transferType;

        bool operator==(const acdapi_SingleStepTransfer_args& rhs) const;
        bool operator!=(const acdapi_SingleStepTransfer_args& rhs) const;
        bool operator< (const acdapi_SingleStepTransfer_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ConsultConference_args {
    public:
        acdapi_ConsultConference_args();
        virtual ~acdapi_ConsultConference_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_ConsultConference_args& rhs) const;
        bool operator!=(const acdapi_ConsultConference_args& rhs) const;
        bool operator< (const acdapi_ConsultConference_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ConferenceJoin_args {
    public:
        acdapi_ConferenceJoin_args();
        virtual ~acdapi_ConferenceJoin_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destAgentId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;
        ConferenceT conferenceType;

        bool operator==(const acdapi_ConferenceJoin_args& rhs) const;
        bool operator!=(const acdapi_ConferenceJoin_args& rhs) const;
        bool operator< (const acdapi_ConferenceJoin_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SetAssociateData_args {
    public:
        acdapi_SetAssociateData_args();
        virtual ~acdapi_SetAssociateData_args();

        int64_t handle;
        std::string agentId;
        std::string key;
        std::string value;

        bool operator==(const acdapi_SetAssociateData_args& rhs) const;
        bool operator!=(const acdapi_SetAssociateData_args& rhs) const;
        bool operator< (const acdapi_SetAssociateData_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAssociateData_args {
    public:
        acdapi_GetAssociateData_args();
        virtual ~acdapi_GetAssociateData_args();

        int64_t handle;
        std::string agentId;
        std::string key;

        bool operator==(const acdapi_GetAssociateData_args& rhs) const;
        bool operator!=(const acdapi_GetAssociateData_args& rhs) const;
        bool operator< (const acdapi_GetAssociateData_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_JumptheQueue_args {
    public:
        acdapi_JumptheQueue_args();
        virtual ~acdapi_JumptheQueue_args();

        int64_t handle;
        std::string agentId;
        int64_t requestId;

        bool operator==(const acdapi_JumptheQueue_args& rhs) const;
        bool operator!=(const acdapi_JumptheQueue_args& rhs) const;
        bool operator< (const acdapi_JumptheQueue_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ForceSignIn_args {
    public:
        acdapi_ForceSignIn_args();
        virtual ~acdapi_ForceSignIn_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;
        std::string agentDn;
        std::string agentPwd;
        StatusChangeT statusChangetype;
        bool autoAnswer;
        bool fcSignin;
        std::string skill;

        bool operator==(const acdapi_ForceSignIn_args& rhs) const;
        bool operator!=(const acdapi_ForceSignIn_args& rhs) const;
        bool operator< (const acdapi_ForceSignIn_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ForceSignOut_args {
    public:
        acdapi_ForceSignOut_args();
        virtual ~acdapi_ForceSignOut_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_ForceSignOut_args& rhs) const;
        bool operator!=(const acdapi_ForceSignOut_args& rhs) const;
        bool operator< (const acdapi_ForceSignOut_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ForceSetAgentStatus_args {
    public:
        acdapi_ForceSetAgentStatus_args();
        virtual ~acdapi_ForceSetAgentStatus_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;
        AgentStatusT agentStatus;

        bool operator==(const acdapi_ForceSetAgentStatus_args& rhs) const;
        bool operator!=(const acdapi_ForceSetAgentStatus_args& rhs) const;
        bool operator< (const acdapi_ForceSetAgentStatus_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Listen_args {
    public:
        acdapi_Listen_args();
        virtual ~acdapi_Listen_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destAgentId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;

        bool operator==(const acdapi_Listen_args& rhs) const;
        bool operator!=(const acdapi_Listen_args& rhs) const;
        bool operator< (const acdapi_Listen_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_StopListen_args {
    public:
        acdapi_StopListen_args();
        virtual ~acdapi_StopListen_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_StopListen_args& rhs) const;
        bool operator!=(const acdapi_StopListen_args& rhs) const;
        bool operator< (const acdapi_StopListen_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Insert_args {
    public:
        acdapi_Insert_args();
        virtual ~acdapi_Insert_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destAgentId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;

        bool operator==(const acdapi_Insert_args& rhs) const;
        bool operator!=(const acdapi_Insert_args& rhs) const;
        bool operator< (const acdapi_Insert_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_StopInsert_args {
    public:
        acdapi_StopInsert_args();
        virtual ~acdapi_StopInsert_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_StopInsert_args& rhs) const;
        bool operator!=(const acdapi_StopInsert_args& rhs) const;
        bool operator< (const acdapi_StopInsert_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SwitchInsertorListen_args {
    public:
        acdapi_SwitchInsertorListen_args();
        virtual ~acdapi_SwitchInsertorListen_args();

        int64_t handle;
        std::string agentId;
        std::string callerId;
        std::string destAgentId;
        std::string forCallerDispNum;
        std::string forCalleeDispNum;

        bool operator==(const acdapi_SwitchInsertorListen_args& rhs) const;
        bool operator!=(const acdapi_SwitchInsertorListen_args& rhs) const;
        bool operator< (const acdapi_SwitchInsertorListen_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Break_args {
    public:
        acdapi_Break_args();
        virtual ~acdapi_Break_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_Break_args& rhs) const;
        bool operator!=(const acdapi_Break_args& rhs) const;
        bool operator< (const acdapi_Break_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SendDTMF_args {
    public:
        acdapi_SendDTMF_args();
        virtual ~acdapi_SendDTMF_args();

        int64_t handle;
        std::string agentId;
        std::string digitals;

        bool operator==(const acdapi_SendDTMF_args& rhs) const;
        bool operator!=(const acdapi_SendDTMF_args& rhs) const;
        bool operator< (const acdapi_SendDTMF_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_StartPlay_args {
    public:
        acdapi_StartPlay_args();
        virtual ~acdapi_StartPlay_args();

        int64_t handle;
        std::string agentId;
        std::string filename;

        bool operator==(const acdapi_StartPlay_args& rhs) const;
        bool operator!=(const acdapi_StartPlay_args& rhs) const;
        bool operator< (const acdapi_StartPlay_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_StopPlay_args {
    public:
        acdapi_StopPlay_args();
        virtual ~acdapi_StopPlay_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_StopPlay_args& rhs) const;
        bool operator!=(const acdapi_StopPlay_args& rhs) const;
        bool operator< (const acdapi_StopPlay_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_MuteOn_args {
    public:
        acdapi_MuteOn_args();
        virtual ~acdapi_MuteOn_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_MuteOn_args& rhs) const;
        bool operator!=(const acdapi_MuteOn_args& rhs) const;
        bool operator< (const acdapi_MuteOn_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_MuteOff_args {
    public:
        acdapi_MuteOff_args();
        virtual ~acdapi_MuteOff_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_MuteOff_args& rhs) const;
        bool operator!=(const acdapi_MuteOff_args& rhs) const;
        bool operator< (const acdapi_MuteOff_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentDetailByAgentID_args {
    public:
        acdapi_GetAgentDetailByAgentID_args();
        virtual ~acdapi_GetAgentDetailByAgentID_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_GetAgentDetailByAgentID_args& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailByAgentID_args& rhs) const;
        bool operator< (const acdapi_GetAgentDetailByAgentID_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentDetailByAgentDN_args {
    public:
        acdapi_GetAgentDetailByAgentDN_args();
        virtual ~acdapi_GetAgentDetailByAgentDN_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentDn;

        bool operator==(const acdapi_GetAgentDetailByAgentDN_args& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailByAgentDN_args& rhs) const;
        bool operator< (const acdapi_GetAgentDetailByAgentDN_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentDetailsByAgentIDs_args {
    public:
        acdapi_GetAgentDetailsByAgentIDs_args();
        virtual ~acdapi_GetAgentDetailsByAgentIDs_args();

        int64_t handle;
        std::string agentId;
        StringListT destAgentIdList;

        bool operator==(const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsByAgentIDs_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentDetailsByAgentDNs_args {
    public:
        acdapi_GetAgentDetailsByAgentDNs_args();
        virtual ~acdapi_GetAgentDetailsByAgentDNs_args();

        int64_t handle;
        std::string agentId;
        StringListT destAgentDnList;

        bool operator==(const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsByAgentDNs_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetRecordFileName_args {
    public:
        acdapi_GetRecordFileName_args();
        virtual ~acdapi_GetRecordFileName_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_GetRecordFileName_args& rhs) const;
        bool operator!=(const acdapi_GetRecordFileName_args& rhs) const;
        bool operator< (const acdapi_GetRecordFileName_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetSkill_args {
    public:
        acdapi_GetSkill_args();
        virtual ~acdapi_GetSkill_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_GetSkill_args& rhs) const;
        bool operator!=(const acdapi_GetSkill_args& rhs) const;
        bool operator< (const acdapi_GetSkill_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetRestReason_args {
    public:
        acdapi_GetRestReason_args();
        virtual ~acdapi_GetRestReason_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_GetRestReason_args& rhs) const;
        bool operator!=(const acdapi_GetRestReason_args& rhs) const;
        bool operator< (const acdapi_GetRestReason_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentNumberBySkill_args {
    public:
        acdapi_GetAgentNumberBySkill_args();
        virtual ~acdapi_GetAgentNumberBySkill_args();

        int64_t handle;
        std::string agentId;
        std::string skill;

        bool operator==(const acdapi_GetAgentNumberBySkill_args& rhs) const;
        bool operator!=(const acdapi_GetAgentNumberBySkill_args& rhs) const;
        bool operator< (const acdapi_GetAgentNumberBySkill_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetAgentDetailsBySkill_args {
    public:
        acdapi_GetAgentDetailsBySkill_args();
        virtual ~acdapi_GetAgentDetailsBySkill_args();

        int64_t handle;
        std::string agentId;
        std::string skill;

        bool operator==(const acdapi_GetAgentDetailsBySkill_args& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsBySkill_args& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsBySkill_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetSkillWaitingNumber_args {
    public:
        acdapi_GetSkillWaitingNumber_args();
        virtual ~acdapi_GetSkillWaitingNumber_args();

        int64_t handle;
        std::string agentId;
        std::string skill;

        bool operator==(const acdapi_GetSkillWaitingNumber_args& rhs) const;
        bool operator!=(const acdapi_GetSkillWaitingNumber_args& rhs) const;
        bool operator< (const acdapi_GetSkillWaitingNumber_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetSkillWaitingCallInfo_args {
    public:
        acdapi_GetSkillWaitingCallInfo_args();
        virtual ~acdapi_GetSkillWaitingCallInfo_args();

        int64_t handle;
        std::string agentId;
        std::string skill;

        bool operator==(const acdapi_GetSkillWaitingCallInfo_args& rhs) const;
        bool operator!=(const acdapi_GetSkillWaitingCallInfo_args& rhs) const;
        bool operator< (const acdapi_GetSkillWaitingCallInfo_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetPrivateQueue_args {
    public:
        acdapi_GetPrivateQueue_args();
        virtual ~acdapi_GetPrivateQueue_args();

        int64_t handle;
        std::string agentId;
        std::string destAgentId;

        bool operator==(const acdapi_GetPrivateQueue_args& rhs) const;
        bool operator!=(const acdapi_GetPrivateQueue_args& rhs) const;
        bool operator< (const acdapi_GetPrivateQueue_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_GetSysInfo_args {
    public:
        acdapi_GetSysInfo_args();
        virtual ~acdapi_GetSysInfo_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_GetSysInfo_args& rhs) const;
        bool operator!=(const acdapi_GetSysInfo_args& rhs) const;
        bool operator< (const acdapi_GetSysInfo_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SynchronizeCTITime_args {
    public:
        acdapi_SynchronizeCTITime_args();
        virtual ~acdapi_SynchronizeCTITime_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_SynchronizeCTITime_args& rhs) const;
        bool operator!=(const acdapi_SynchronizeCTITime_args& rhs) const;
        bool operator< (const acdapi_SynchronizeCTITime_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_Heartbeat_args {
    public:
        acdapi_Heartbeat_args();
        virtual ~acdapi_Heartbeat_args();

        int64_t handle;
        std::string agentId;

        bool operator==(const acdapi_Heartbeat_args& rhs) const;
        bool operator!=(const acdapi_Heartbeat_args& rhs) const;
        bool operator< (const acdapi_Heartbeat_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_ResetConfig_args {
    public:
        acdapi_ResetConfig_args();
        virtual ~acdapi_ResetConfig_args();

        std::string password;

        bool operator==(const acdapi_ResetConfig_args& rhs) const;
        bool operator!=(const acdapi_ResetConfig_args& rhs) const;
        bool operator< (const acdapi_ResetConfig_args& rhs) const;
        int32_t read(char* request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto);
    };

    class acdapi_SignIn_pargs {
    public:
        virtual ~acdapi_SignIn_pargs();

        const std::string* agentId;
        const std::string* agentDn;
        const std::string* agentPwd;
        const StatusChangeT* statusChangetype;
        const bool* autoAnswer;
        const bool* fcSignin;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SignOut_pargs {
    public:
        virtual ~acdapi_SignOut_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAgentStatus_pargs {
    public:
        virtual ~acdapi_SetAgentStatus_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const AgentStatusT* agentStatus;
        const std::string* restReason;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentStatus_pargs {
    public:
        virtual ~acdapi_GetAgentStatus_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetStatuschangetype_pargs {
    public:
        virtual ~acdapi_ResetStatuschangetype_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const StatusChangeT* statusChangetype;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetAutoAnswer_pargs {
    public:
        virtual ~acdapi_ResetAutoAnswer_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const bool* autoAnswer;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetSkill_pargs {
    public:
        virtual ~acdapi_ResetSkill_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Reset_pargs {
    public:
        virtual ~acdapi_Reset_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_OutboundCall_pargs {
    public:
        virtual ~acdapi_OutboundCall_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;
        const int32_t* timeout;
        const CallModeT* callMode;
        const CallTypeT* callType;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_AnswerCall_pargs {
    public:
        virtual ~acdapi_AnswerCall_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ReleaseCall_pargs {
    public:
        virtual ~acdapi_ReleaseCall_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Hold_pargs {
    public:
        virtual ~acdapi_Hold_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Retrieve_pargs {
    public:
        virtual ~acdapi_Retrieve_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Consult_pargs {
    public:
        virtual ~acdapi_Consult_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;
        const CallTypeT* callType;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultReconnect_pargs {
    public:
        virtual ~acdapi_ConsultReconnect_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultTransfer_pargs {
    public:
        virtual ~acdapi_ConsultTransfer_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SingleStepTransfer_pargs {
    public:
        virtual ~acdapi_SingleStepTransfer_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;
        const bool* isPassthrough;
        const CallTypeT* transferType;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultConference_pargs {
    public:
        virtual ~acdapi_ConsultConference_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConferenceJoin_pargs {
    public:
        virtual ~acdapi_ConferenceJoin_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destAgentId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;
        const ConferenceT* conferenceType;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAssociateData_pargs {
    public:
        virtual ~acdapi_SetAssociateData_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* key;
        const std::string* value;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAssociateData_pargs {
    public:
        virtual ~acdapi_GetAssociateData_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* key;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_JumptheQueue_pargs {
    public:
        virtual ~acdapi_JumptheQueue_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const int64_t* requestId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignIn_pargs {
    public:
        virtual ~acdapi_ForceSignIn_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;
        const std::string* agentDn;
        const std::string* agentPwd;
        const StatusChangeT* statusChangetype;
        const bool* autoAnswer;
        const bool* fcSignin;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignOut_pargs {
    public:
        virtual ~acdapi_ForceSignOut_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSetAgentStatus_pargs {
    public:
        virtual ~acdapi_ForceSetAgentStatus_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;
        const AgentStatusT* agentStatus;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Listen_pargs {
    public:
        virtual ~acdapi_Listen_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destAgentId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopListen_pargs {
    public:
        virtual ~acdapi_StopListen_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Insert_pargs {
    public:
        virtual ~acdapi_Insert_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destAgentId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopInsert_pargs {
    public:
        virtual ~acdapi_StopInsert_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SwitchInsertorListen_pargs {
    public:
        virtual ~acdapi_SwitchInsertorListen_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* callerId;
        const std::string* destAgentId;
        const std::string* forCallerDispNum;
        const std::string* forCalleeDispNum;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Break_pargs {
    public:
        virtual ~acdapi_Break_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SendDTMF_pargs {
    public:
        virtual ~acdapi_SendDTMF_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* digitals;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StartPlay_pargs {
    public:
        virtual ~acdapi_StartPlay_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* filename;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopPlay_pargs {
    public:
        virtual ~acdapi_StopPlay_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOn_pargs {
    public:
        virtual ~acdapi_MuteOn_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOff_pargs {
    public:
        virtual ~acdapi_MuteOff_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentID_pargs {
    public:
        virtual ~acdapi_GetAgentDetailByAgentID_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentDN_pargs {
    public:
        virtual ~acdapi_GetAgentDetailByAgentDN_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentDn;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentIDs_pargs {
    public:
        virtual ~acdapi_GetAgentDetailsByAgentIDs_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const StringListT* destAgentIdList;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentDNs_pargs {
    public:
        virtual ~acdapi_GetAgentDetailsByAgentDNs_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const StringListT* destAgentDnList;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRecordFileName_pargs {
    public:
        virtual ~acdapi_GetRecordFileName_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkill_pargs {
    public:
        virtual ~acdapi_GetSkill_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRestReason_pargs {
    public:
        virtual ~acdapi_GetRestReason_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentNumberBySkill_pargs {
    public:
        virtual ~acdapi_GetAgentNumberBySkill_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsBySkill_pargs {
    public:
        virtual ~acdapi_GetAgentDetailsBySkill_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingNumber_pargs {
    public:
        virtual ~acdapi_GetSkillWaitingNumber_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingCallInfo_pargs {
    public:
        virtual ~acdapi_GetSkillWaitingCallInfo_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* skill;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetPrivateQueue_pargs {
    public:
        virtual ~acdapi_GetPrivateQueue_pargs();

        const int64_t* handle;
        const std::string* agentId;
        const std::string* destAgentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSysInfo_pargs {
    public:
        virtual ~acdapi_GetSysInfo_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SynchronizeCTITime_pargs {
    public:
        virtual ~acdapi_SynchronizeCTITime_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Heartbeat_pargs {
    public:
        virtual ~acdapi_Heartbeat_pargs();

        const int64_t* handle;
        const std::string* agentId;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetConfig_pargs {
    public:
        virtual ~acdapi_ResetConfig_pargs();

        const std::string* password;

        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SignIn_result {
    public:
        acdapi_SignIn_result();
        virtual ~acdapi_SignIn_result();

        AcdResultT return_value;
        int64_t handle;

        bool operator==(const acdapi_SignIn_result& rhs) const;
        bool operator!=(const acdapi_SignIn_result& rhs) const;
        bool operator< (const acdapi_SignIn_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SignOut_result {
    public:
        acdapi_SignOut_result();
        virtual ~acdapi_SignOut_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SignOut_result& rhs) const;
        bool operator!=(const acdapi_SignOut_result& rhs) const;
        bool operator< (const acdapi_SignOut_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAgentStatus_result {
    public:
        acdapi_SetAgentStatus_result();
        virtual ~acdapi_SetAgentStatus_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SetAgentStatus_result& rhs) const;
        bool operator!=(const acdapi_SetAgentStatus_result& rhs) const;
        bool operator< (const acdapi_SetAgentStatus_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentStatus_result {
    public:
        acdapi_GetAgentStatus_result();
        virtual ~acdapi_GetAgentStatus_result();

        AcdResultT return_value;
        AgentStatusT agentStatus;

        bool operator==(const acdapi_GetAgentStatus_result& rhs) const;
        bool operator!=(const acdapi_GetAgentStatus_result& rhs) const;
        bool operator< (const acdapi_GetAgentStatus_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetStatuschangetype_result {
    public:
        acdapi_ResetStatuschangetype_result();
        virtual ~acdapi_ResetStatuschangetype_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ResetStatuschangetype_result& rhs) const;
        bool operator!=(const acdapi_ResetStatuschangetype_result& rhs) const;
        bool operator< (const acdapi_ResetStatuschangetype_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetAutoAnswer_result {
    public:
        acdapi_ResetAutoAnswer_result();
        virtual ~acdapi_ResetAutoAnswer_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ResetAutoAnswer_result& rhs) const;
        bool operator!=(const acdapi_ResetAutoAnswer_result& rhs) const;
        bool operator< (const acdapi_ResetAutoAnswer_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetSkill_result {
    public:
        acdapi_ResetSkill_result();
        virtual ~acdapi_ResetSkill_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ResetSkill_result& rhs) const;
        bool operator!=(const acdapi_ResetSkill_result& rhs) const;
        bool operator< (const acdapi_ResetSkill_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Reset_result {
    public:
        acdapi_Reset_result();
        virtual ~acdapi_Reset_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Reset_result& rhs) const;
        bool operator!=(const acdapi_Reset_result& rhs) const;
        bool operator< (const acdapi_Reset_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_OutboundCall_result {
    public:
        acdapi_OutboundCall_result();
        virtual ~acdapi_OutboundCall_result();

        AcdResultT return_value;

        bool operator==(const acdapi_OutboundCall_result& rhs) const;
        bool operator!=(const acdapi_OutboundCall_result& rhs) const;
        bool operator< (const acdapi_OutboundCall_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_AnswerCall_result {
    public:
        acdapi_AnswerCall_result();
        virtual ~acdapi_AnswerCall_result();

        AcdResultT return_value;

        bool operator==(const acdapi_AnswerCall_result& rhs) const;
        bool operator!=(const acdapi_AnswerCall_result& rhs) const;
        bool operator< (const acdapi_AnswerCall_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ReleaseCall_result {
    public:
        acdapi_ReleaseCall_result();
        virtual ~acdapi_ReleaseCall_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ReleaseCall_result& rhs) const;
        bool operator!=(const acdapi_ReleaseCall_result& rhs) const;
        bool operator< (const acdapi_ReleaseCall_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Hold_result {
    public:
        acdapi_Hold_result();
        virtual ~acdapi_Hold_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Hold_result& rhs) const;
        bool operator!=(const acdapi_Hold_result& rhs) const;
        bool operator< (const acdapi_Hold_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Retrieve_result {
    public:
        acdapi_Retrieve_result();
        virtual ~acdapi_Retrieve_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Retrieve_result& rhs) const;
        bool operator!=(const acdapi_Retrieve_result& rhs) const;
        bool operator< (const acdapi_Retrieve_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Consult_result {
    public:
        acdapi_Consult_result();
        virtual ~acdapi_Consult_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Consult_result& rhs) const;
        bool operator!=(const acdapi_Consult_result& rhs) const;
        bool operator< (const acdapi_Consult_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultReconnect_result {
    public:
        acdapi_ConsultReconnect_result();
        virtual ~acdapi_ConsultReconnect_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ConsultReconnect_result& rhs) const;
        bool operator!=(const acdapi_ConsultReconnect_result& rhs) const;
        bool operator< (const acdapi_ConsultReconnect_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultTransfer_result {
    public:
        acdapi_ConsultTransfer_result();
        virtual ~acdapi_ConsultTransfer_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ConsultTransfer_result& rhs) const;
        bool operator!=(const acdapi_ConsultTransfer_result& rhs) const;
        bool operator< (const acdapi_ConsultTransfer_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SingleStepTransfer_result {
    public:
        acdapi_SingleStepTransfer_result();
        virtual ~acdapi_SingleStepTransfer_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SingleStepTransfer_result& rhs) const;
        bool operator!=(const acdapi_SingleStepTransfer_result& rhs) const;
        bool operator< (const acdapi_SingleStepTransfer_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultConference_result {
    public:
        acdapi_ConsultConference_result();
        virtual ~acdapi_ConsultConference_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ConsultConference_result& rhs) const;
        bool operator!=(const acdapi_ConsultConference_result& rhs) const;
        bool operator< (const acdapi_ConsultConference_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConferenceJoin_result {
    public:
        acdapi_ConferenceJoin_result();
        virtual ~acdapi_ConferenceJoin_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ConferenceJoin_result& rhs) const;
        bool operator!=(const acdapi_ConferenceJoin_result& rhs) const;
        bool operator< (const acdapi_ConferenceJoin_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAssociateData_result {
    public:
        acdapi_SetAssociateData_result();
        virtual ~acdapi_SetAssociateData_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SetAssociateData_result& rhs) const;
        bool operator!=(const acdapi_SetAssociateData_result& rhs) const;
        bool operator< (const acdapi_SetAssociateData_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAssociateData_result {
    public:
        acdapi_GetAssociateData_result();
        virtual ~acdapi_GetAssociateData_result();

        AcdResultT return_value;
        std::string value;

        bool operator==(const acdapi_GetAssociateData_result& rhs) const;
        bool operator!=(const acdapi_GetAssociateData_result& rhs) const;
        bool operator< (const acdapi_GetAssociateData_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_JumptheQueue_result {
    public:
        acdapi_JumptheQueue_result();
        virtual ~acdapi_JumptheQueue_result();

        AcdResultT return_value;

        bool operator==(const acdapi_JumptheQueue_result& rhs) const;
        bool operator!=(const acdapi_JumptheQueue_result& rhs) const;
        bool operator< (const acdapi_JumptheQueue_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignIn_result {
    public:
        acdapi_ForceSignIn_result();
        virtual ~acdapi_ForceSignIn_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ForceSignIn_result& rhs) const;
        bool operator!=(const acdapi_ForceSignIn_result& rhs) const;
        bool operator< (const acdapi_ForceSignIn_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignOut_result {
    public:
        acdapi_ForceSignOut_result();
        virtual ~acdapi_ForceSignOut_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ForceSignOut_result& rhs) const;
        bool operator!=(const acdapi_ForceSignOut_result& rhs) const;
        bool operator< (const acdapi_ForceSignOut_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSetAgentStatus_result {
    public:
        acdapi_ForceSetAgentStatus_result();
        virtual ~acdapi_ForceSetAgentStatus_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ForceSetAgentStatus_result& rhs) const;
        bool operator!=(const acdapi_ForceSetAgentStatus_result& rhs) const;
        bool operator< (const acdapi_ForceSetAgentStatus_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Listen_result {
    public:
        acdapi_Listen_result();
        virtual ~acdapi_Listen_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Listen_result& rhs) const;
        bool operator!=(const acdapi_Listen_result& rhs) const;
        bool operator< (const acdapi_Listen_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopListen_result {
    public:
        acdapi_StopListen_result();
        virtual ~acdapi_StopListen_result();

        AcdResultT return_value;

        bool operator==(const acdapi_StopListen_result& rhs) const;
        bool operator!=(const acdapi_StopListen_result& rhs) const;
        bool operator< (const acdapi_StopListen_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Insert_result {
    public:
        acdapi_Insert_result();
        virtual ~acdapi_Insert_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Insert_result& rhs) const;
        bool operator!=(const acdapi_Insert_result& rhs) const;
        bool operator< (const acdapi_Insert_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopInsert_result {
    public:
        acdapi_StopInsert_result();
        virtual ~acdapi_StopInsert_result();

        AcdResultT return_value;

        bool operator==(const acdapi_StopInsert_result& rhs) const;
        bool operator!=(const acdapi_StopInsert_result& rhs) const;
        bool operator< (const acdapi_StopInsert_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SwitchInsertorListen_result {
    public:
        acdapi_SwitchInsertorListen_result();
        virtual ~acdapi_SwitchInsertorListen_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SwitchInsertorListen_result& rhs) const;
        bool operator!=(const acdapi_SwitchInsertorListen_result& rhs) const;
        bool operator< (const acdapi_SwitchInsertorListen_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Break_result {
    public:
        acdapi_Break_result();
        virtual ~acdapi_Break_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Break_result& rhs) const;
        bool operator!=(const acdapi_Break_result& rhs) const;
        bool operator< (const acdapi_Break_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SendDTMF_result {
    public:
        acdapi_SendDTMF_result();
        virtual ~acdapi_SendDTMF_result();

        AcdResultT return_value;

        bool operator==(const acdapi_SendDTMF_result& rhs) const;
        bool operator!=(const acdapi_SendDTMF_result& rhs) const;
        bool operator< (const acdapi_SendDTMF_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StartPlay_result {
    public:
        acdapi_StartPlay_result();
        virtual ~acdapi_StartPlay_result();

        AcdResultT return_value;

        bool operator==(const acdapi_StartPlay_result& rhs) const;
        bool operator!=(const acdapi_StartPlay_result& rhs) const;
        bool operator< (const acdapi_StartPlay_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopPlay_result {
    public:
        acdapi_StopPlay_result();
        virtual ~acdapi_StopPlay_result();

        AcdResultT return_value;

        bool operator==(const acdapi_StopPlay_result& rhs) const;
        bool operator!=(const acdapi_StopPlay_result& rhs) const;
        bool operator< (const acdapi_StopPlay_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOn_result {
    public:
        acdapi_MuteOn_result();
        virtual ~acdapi_MuteOn_result();

        AcdResultT return_value;

        bool operator==(const acdapi_MuteOn_result& rhs) const;
        bool operator!=(const acdapi_MuteOn_result& rhs) const;
        bool operator< (const acdapi_MuteOn_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOff_result {
    public:
        acdapi_MuteOff_result();
        virtual ~acdapi_MuteOff_result();

        AcdResultT return_value;

        bool operator==(const acdapi_MuteOff_result& rhs) const;
        bool operator!=(const acdapi_MuteOff_result& rhs) const;
        bool operator< (const acdapi_MuteOff_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentID_result {
    public:
        acdapi_GetAgentDetailByAgentID_result();
        virtual ~acdapi_GetAgentDetailByAgentID_result();

        AcdResultT return_value;
        AgentInfoT agentInfo;

        bool operator==(const acdapi_GetAgentDetailByAgentID_result& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailByAgentID_result& rhs) const;
        bool operator< (const acdapi_GetAgentDetailByAgentID_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentDN_result {
    public:
        acdapi_GetAgentDetailByAgentDN_result();
        virtual ~acdapi_GetAgentDetailByAgentDN_result();

        AcdResultT return_value;
        AgentInfoT agentInfo;

        bool operator==(const acdapi_GetAgentDetailByAgentDN_result& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailByAgentDN_result& rhs) const;
        bool operator< (const acdapi_GetAgentDetailByAgentDN_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentIDs_result {
    public:
        acdapi_GetAgentDetailsByAgentIDs_result();
        virtual ~acdapi_GetAgentDetailsByAgentIDs_result();

        AcdResultT return_value;
        AgentInfoListT agentInfoList;

        bool operator==(const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsByAgentIDs_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentDNs_result {
    public:
        acdapi_GetAgentDetailsByAgentDNs_result();
        virtual ~acdapi_GetAgentDetailsByAgentDNs_result();

        AcdResultT return_value;
        AgentInfoListT agentInfoList;

        bool operator==(const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsByAgentDNs_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRecordFileName_result {
    public:
        acdapi_GetRecordFileName_result();
        virtual ~acdapi_GetRecordFileName_result();

        AcdResultT return_value;
        std::string filename;

        bool operator==(const acdapi_GetRecordFileName_result& rhs) const;
        bool operator!=(const acdapi_GetRecordFileName_result& rhs) const;
        bool operator< (const acdapi_GetRecordFileName_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkill_result {
    public:
        acdapi_GetSkill_result();
        virtual ~acdapi_GetSkill_result();

        AcdResultT return_value;
        StringListT skill;

        bool operator==(const acdapi_GetSkill_result& rhs) const;
        bool operator!=(const acdapi_GetSkill_result& rhs) const;
        bool operator< (const acdapi_GetSkill_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRestReason_result {
    public:
        acdapi_GetRestReason_result();
        virtual ~acdapi_GetRestReason_result();

        AcdResultT return_value;
        StringListT restReason;

        bool operator==(const acdapi_GetRestReason_result& rhs) const;
        bool operator!=(const acdapi_GetRestReason_result& rhs) const;
        bool operator< (const acdapi_GetRestReason_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentNumberBySkill_result {
    public:
        acdapi_GetAgentNumberBySkill_result();
        virtual ~acdapi_GetAgentNumberBySkill_result();

        AcdResultT return_value;
        int32_t agentNum;

        bool operator==(const acdapi_GetAgentNumberBySkill_result& rhs) const;
        bool operator!=(const acdapi_GetAgentNumberBySkill_result& rhs) const;
        bool operator< (const acdapi_GetAgentNumberBySkill_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsBySkill_result {
    public:
        acdapi_GetAgentDetailsBySkill_result();
        virtual ~acdapi_GetAgentDetailsBySkill_result();

        AcdResultT return_value;
        int32_t agentNum;
        AgentInfoListT agentInfoList;

        bool operator==(const acdapi_GetAgentDetailsBySkill_result& rhs) const;
        bool operator!=(const acdapi_GetAgentDetailsBySkill_result& rhs) const;
        bool operator< (const acdapi_GetAgentDetailsBySkill_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingNumber_result {
    public:
        acdapi_GetSkillWaitingNumber_result();
        virtual ~acdapi_GetSkillWaitingNumber_result();

        AcdResultT return_value;
        int32_t queueNum;
        int32_t freeNum;

        bool operator==(const acdapi_GetSkillWaitingNumber_result& rhs) const;
        bool operator!=(const acdapi_GetSkillWaitingNumber_result& rhs) const;
        bool operator< (const acdapi_GetSkillWaitingNumber_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingCallInfo_result {
    public:
        acdapi_GetSkillWaitingCallInfo_result();
        virtual ~acdapi_GetSkillWaitingCallInfo_result();

        AcdResultT return_value;
        int32_t queueNum;
        QueueInfoListT queueInfoList;

        bool operator==(const acdapi_GetSkillWaitingCallInfo_result& rhs) const;
        bool operator!=(const acdapi_GetSkillWaitingCallInfo_result& rhs) const;
        bool operator< (const acdapi_GetSkillWaitingCallInfo_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetPrivateQueue_result {
    public:
        acdapi_GetPrivateQueue_result();
        virtual ~acdapi_GetPrivateQueue_result();

        AcdResultT return_value;
        int32_t queueNum;
        QueueInfoListT queueInfoList;

        bool operator==(const acdapi_GetPrivateQueue_result& rhs) const;
        bool operator!=(const acdapi_GetPrivateQueue_result& rhs) const;
        bool operator< (const acdapi_GetPrivateQueue_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSysInfo_result {
    public:
        acdapi_GetSysInfo_result();
        virtual ~acdapi_GetSysInfo_result();

        AcdResultT return_value;
        SysInfoT sysInfo;

        bool operator==(const acdapi_GetSysInfo_result& rhs) const;
        bool operator!=(const acdapi_GetSysInfo_result& rhs) const;
        bool operator< (const acdapi_GetSysInfo_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SynchronizeCTITime_result {
    public:
        acdapi_SynchronizeCTITime_result();
        virtual ~acdapi_SynchronizeCTITime_result();

        AcdResultT return_value;
        int64_t timestamp;

        bool operator==(const acdapi_SynchronizeCTITime_result& rhs) const;
        bool operator!=(const acdapi_SynchronizeCTITime_result& rhs) const;
        bool operator< (const acdapi_SynchronizeCTITime_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Heartbeat_result {
    public:
        acdapi_Heartbeat_result();
        virtual ~acdapi_Heartbeat_result();

        AcdResultT return_value;

        bool operator==(const acdapi_Heartbeat_result& rhs) const;
        bool operator!=(const acdapi_Heartbeat_result& rhs) const;
        bool operator< (const acdapi_Heartbeat_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetConfig_result {
    public:
        acdapi_ResetConfig_result();
        virtual ~acdapi_ResetConfig_result();

        AcdResultT return_value;

        bool operator==(const acdapi_ResetConfig_result& rhs) const;
        bool operator!=(const acdapi_ResetConfig_result& rhs) const;
        bool operator< (const acdapi_ResetConfig_result& rhs) const;
        int32_t write(bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SignIn_presult {
    public:
        virtual ~acdapi_SignIn_presult();

        AcdResultT* return_value;
        int64_t* handle;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SignOut_presult {
    public:
        virtual ~acdapi_SignOut_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAgentStatus_presult {
    public:
        virtual ~acdapi_SetAgentStatus_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentStatus_presult {
    public:
        virtual ~acdapi_GetAgentStatus_presult();

        AcdResultT* return_value;
        AgentStatusT* agentStatus;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetStatuschangetype_presult {
    public:
        virtual ~acdapi_ResetStatuschangetype_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetAutoAnswer_presult {
    public:
        virtual ~acdapi_ResetAutoAnswer_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetSkill_presult {
    public:
        virtual ~acdapi_ResetSkill_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Reset_presult {
    public:
        virtual ~acdapi_Reset_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_OutboundCall_presult {
    public:
        virtual ~acdapi_OutboundCall_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_AnswerCall_presult {
    public:
        virtual ~acdapi_AnswerCall_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ReleaseCall_presult {
    public:
        virtual ~acdapi_ReleaseCall_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Hold_presult {
    public:
        virtual ~acdapi_Hold_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Retrieve_presult {
    public:
        virtual ~acdapi_Retrieve_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Consult_presult {
    public:
        virtual ~acdapi_Consult_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultReconnect_presult {
    public:
        virtual ~acdapi_ConsultReconnect_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultTransfer_presult {
    public:
        virtual ~acdapi_ConsultTransfer_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SingleStepTransfer_presult {
    public:
        virtual ~acdapi_SingleStepTransfer_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConsultConference_presult {
    public:
        virtual ~acdapi_ConsultConference_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ConferenceJoin_presult {
    public:
        virtual ~acdapi_ConferenceJoin_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SetAssociateData_presult {
    public:
        virtual ~acdapi_SetAssociateData_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAssociateData_presult {
    public:
        virtual ~acdapi_GetAssociateData_presult();

        AcdResultT* return_value;
        std::string* value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_JumptheQueue_presult {
    public:
        virtual ~acdapi_JumptheQueue_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignIn_presult {
    public:
        virtual ~acdapi_ForceSignIn_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSignOut_presult {
    public:
        virtual ~acdapi_ForceSignOut_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ForceSetAgentStatus_presult {
    public:
        virtual ~acdapi_ForceSetAgentStatus_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Listen_presult {
    public:
        virtual ~acdapi_Listen_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopListen_presult {
    public:
        virtual ~acdapi_StopListen_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Insert_presult {
    public:
        virtual ~acdapi_Insert_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopInsert_presult {
    public:
        virtual ~acdapi_StopInsert_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SwitchInsertorListen_presult {
    public:
        virtual ~acdapi_SwitchInsertorListen_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Break_presult {
    public:
        virtual ~acdapi_Break_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SendDTMF_presult {
    public:
        virtual ~acdapi_SendDTMF_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StartPlay_presult {
    public:
        virtual ~acdapi_StartPlay_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_StopPlay_presult {
    public:
        virtual ~acdapi_StopPlay_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOn_presult {
    public:
        virtual ~acdapi_MuteOn_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_MuteOff_presult {
    public:
        virtual ~acdapi_MuteOff_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentID_presult {
    public:
        virtual ~acdapi_GetAgentDetailByAgentID_presult();

        AcdResultT* return_value;
        AgentInfoT* agentInfo;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailByAgentDN_presult {
    public:
        virtual ~acdapi_GetAgentDetailByAgentDN_presult();

        AcdResultT* return_value;
        AgentInfoT* agentInfo;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentIDs_presult {
    public:
        virtual ~acdapi_GetAgentDetailsByAgentIDs_presult();

        AcdResultT* return_value;
        AgentInfoListT* agentInfoList;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsByAgentDNs_presult {
    public:
        virtual ~acdapi_GetAgentDetailsByAgentDNs_presult();

        AcdResultT* return_value;
        AgentInfoListT* agentInfoList;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRecordFileName_presult {
    public:
        virtual ~acdapi_GetRecordFileName_presult();

        AcdResultT* return_value;
        std::string* filename;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkill_presult {
    public:
        virtual ~acdapi_GetSkill_presult();

        AcdResultT* return_value;
        StringListT* skill;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetRestReason_presult {
    public:
        virtual ~acdapi_GetRestReason_presult();

        AcdResultT* return_value;
        StringListT* restReason;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentNumberBySkill_presult {
    public:
        virtual ~acdapi_GetAgentNumberBySkill_presult();

        AcdResultT* return_value;
        int32_t* agentNum;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetAgentDetailsBySkill_presult {
    public:
        virtual ~acdapi_GetAgentDetailsBySkill_presult();

        AcdResultT* return_value;
        int32_t* agentNum;
        AgentInfoListT* agentInfoList;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingNumber_presult {
    public:
        virtual ~acdapi_GetSkillWaitingNumber_presult();

        AcdResultT* return_value;
        int32_t* queueNum;
        int32_t* freeNum;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSkillWaitingCallInfo_presult {
    public:
        virtual ~acdapi_GetSkillWaitingCallInfo_presult();

        AcdResultT* return_value;
        int32_t* queueNum;
        QueueInfoListT* queueInfoList;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetPrivateQueue_presult {
    public:
        virtual ~acdapi_GetPrivateQueue_presult();

        AcdResultT* return_value;
        int32_t* queueNum;
        QueueInfoListT* queueInfoList;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_GetSysInfo_presult {
    public:
        virtual ~acdapi_GetSysInfo_presult();

        AcdResultT* return_value;
        SysInfoT* sysInfo;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_SynchronizeCTITime_presult {
    public:
        virtual ~acdapi_SynchronizeCTITime_presult();

        AcdResultT* return_value;
        int64_t* timestamp;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_Heartbeat_presult {
    public:
        virtual ~acdapi_Heartbeat_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapi_ResetConfig_presult {
    public:
        virtual ~acdapi_ResetConfig_presult();

        AcdResultT* return_value;

        int32_t read(char *request, int32_t request_len, bgcc::SharedPointer<bgcc::IProtocol> proto) const;
    };

    class acdapiProxy : public bgcc::BaseProxy {
    public:
        acdapiProxy(
            bgcc::ServerInfo serverinfo,
            int32_t maxConn,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        acdapiProxy(
            bgcc::ServerInfo serverinfo,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        acdapiProxy(
            const std::string& proxy_name,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        AcdResultT SignIn(
            const std::string& agentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string& skill,
            int64_t& handle,
            bool last = false);

        AcdResultT SignOut(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT SetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            const AgentStatusT& agentStatus,
            const std::string& restReason,
            bool last = false);

        AcdResultT GetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            AgentStatusT& agentStatus,
            bool last = false);

        AcdResultT ResetStatuschangetype(
            int64_t handle,
            const std::string& agentId,
            const StatusChangeT& statusChangetype,
            bool last = false);

        AcdResultT ResetAutoAnswer(
            int64_t handle,
            const std::string& agentId,
            bool autoAnswer,
            bool last = false);

        AcdResultT ResetSkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            bool last = false);

        AcdResultT Reset(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT OutboundCall(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t timeout,
            const CallModeT& callMode,
            const CallTypeT& callType,
            bool last = false);

        AcdResultT AnswerCall(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ReleaseCall(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Hold(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Retrieve(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Consult(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const CallTypeT& callType,
            bool last = false);

        AcdResultT ConsultReconnect(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ConsultTransfer(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT SingleStepTransfer(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool isPassthrough,
            const CallTypeT& transferType,
            bool last = false);

        AcdResultT ConsultConference(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ConferenceJoin(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const ConferenceT& conferenceType,
            bool last = false);

        AcdResultT SetAssociateData(
            int64_t handle,
            const std::string& agentId,
            const std::string& key,
            const std::string& value,
            bool last = false);

        AcdResultT GetAssociateData(
            int64_t handle,
            const std::string& agentId,
            const std::string& key,
            std::string& value,
            bool last = false);

        AcdResultT JumptheQueue(
            int64_t handle,
            const std::string& agentId,
            int64_t requestId,
            bool last = false);

        AcdResultT ForceSignIn(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string& skill,
            bool last = false);

        AcdResultT ForceSignOut(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT ForceSetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const AgentStatusT& agentStatus,
            bool last = false);

        AcdResultT Listen(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT StopListen(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT Insert(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT StopInsert(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT SwitchInsertorListen(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT Break(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT SendDTMF(
            int64_t handle,
            const std::string& agentId,
            const std::string& digitals,
            bool last = false);

        AcdResultT StartPlay(
            int64_t handle,
            const std::string& agentId,
            const std::string& filename,
            bool last = false);

        AcdResultT StopPlay(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT MuteOn(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT MuteOff(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT GetAgentDetailByAgentID(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            AgentInfoT& agentInfo,
            bool last = false);

        AcdResultT GetAgentDetailByAgentDN(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentDn,
            AgentInfoT& agentInfo,
            bool last = false);

        AcdResultT GetAgentDetailsByAgentIDs(
            int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentIdList,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetAgentDetailsByAgentDNs(
            int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentDnList,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetRecordFileName(
            int64_t handle,
            const std::string& agentId,
            std::string& filename,
            bool last = false);

        AcdResultT GetSkill(
            int64_t handle,
            const std::string& agentId,
            StringListT& skill,
            bool last = false);

        AcdResultT GetRestReason(
            int64_t handle,
            const std::string& agentId,
            StringListT& restReason,
            bool last = false);

        AcdResultT GetAgentNumberBySkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum,
            bool last = false);

        AcdResultT GetAgentDetailsBySkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetSkillWaitingNumber(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            int32_t& freeNum,
            bool last = false);

        AcdResultT GetSkillWaitingCallInfo(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bool last = false);

        AcdResultT GetPrivateQueue(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bool last = false);

        AcdResultT GetSysInfo(
            int64_t handle,
            const std::string& agentId,
            SysInfoT& sysInfo,
            bool last = false);

        AcdResultT SynchronizeCTITime(
            int64_t handle,
            const std::string& agentId,
            int64_t& timestamp,
            bool last = false);

        AcdResultT Heartbeat(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ResetConfig(
            const std::string& password,
            bool last = false);

    private:
        void send_SignIn(
            const std::string& agentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            const bool& autoAnswer,
            const bool& fcSignin,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SignIn(
            int64_t& handle,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SignOut(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SignOut(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            const AgentStatusT& agentStatus,
            const std::string& restReason,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SetAgentStatus(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentStatus(
            AgentStatusT& agentStatus,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetStatuschangetype(
            const int64_t& handle,
            const std::string& agentId,
            const StatusChangeT& statusChangetype,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetStatuschangetype(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetAutoAnswer(
            const int64_t& handle,
            const std::string& agentId,
            const bool& autoAnswer,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetAutoAnswer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetSkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetSkill(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Reset(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Reset(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_OutboundCall(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const int32_t& timeout,
            const CallModeT& callMode,
            const CallTypeT& callType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_OutboundCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_AnswerCall(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_AnswerCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ReleaseCall(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ReleaseCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Hold(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Hold(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Retrieve(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Retrieve(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Consult(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const CallTypeT& callType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Consult(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultReconnect(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultReconnect(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultTransfer(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultTransfer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SingleStepTransfer(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const bool& isPassthrough,
            const CallTypeT& transferType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SingleStepTransfer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultConference(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultConference(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConferenceJoin(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const ConferenceT& conferenceType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConferenceJoin(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SetAssociateData(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& key,
            const std::string& value,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SetAssociateData(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAssociateData(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& key,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAssociateData(
            std::string& value,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_JumptheQueue(
            const int64_t& handle,
            const std::string& agentId,
            const int64_t& requestId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_JumptheQueue(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSignIn(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            const bool& autoAnswer,
            const bool& fcSignin,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSignIn(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSignOut(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSignOut(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const AgentStatusT& agentStatus,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSetAgentStatus(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Listen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Listen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopListen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopListen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Insert(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Insert(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopInsert(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopInsert(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SwitchInsertorListen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SwitchInsertorListen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Break(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Break(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendDTMF(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& digitals,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SendDTMF(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StartPlay(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& filename,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StartPlay(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopPlay(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopPlay(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_MuteOn(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_MuteOn(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_MuteOff(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_MuteOff(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailByAgentID(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailByAgentID(
            AgentInfoT& agentInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailByAgentDN(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentDn,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailByAgentDN(
            AgentInfoT& agentInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsByAgentIDs(
            const int64_t& handle,
            const std::string& agentId,
            const StringListT& destAgentIdList,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsByAgentIDs(
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsByAgentDNs(
            const int64_t& handle,
            const std::string& agentId,
            const StringListT& destAgentDnList,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsByAgentDNs(
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetRecordFileName(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetRecordFileName(
            std::string& filename,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkill(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkill(
            StringListT& skill,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetRestReason(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetRestReason(
            StringListT& restReason,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentNumberBySkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentNumberBySkill(
            int32_t& agentNum,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsBySkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsBySkill(
            int32_t& agentNum,
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkillWaitingNumber(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkillWaitingNumber(
            int32_t& queueNum,
            int32_t& freeNum,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkillWaitingCallInfo(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkillWaitingCallInfo(
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetPrivateQueue(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetPrivateQueue(
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSysInfo(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSysInfo(
            SysInfoT& sysInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SynchronizeCTITime(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SynchronizeCTITime(
            int64_t& timestamp,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Heartbeat(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Heartbeat(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetConfig(
            const std::string& password,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetConfig(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

    };

    class SSLacdapiProxy : public bgcc::SSLBaseProxy {
    public:
        SSLacdapiProxy(
            bgcc::ServerInfo serverinfo,
            int32_t maxConn,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        SSLacdapiProxy(
            bgcc::ServerInfo serverinfo,
            bgcc::ServiceManager* mgr = NULL,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        SSLacdapiProxy(
            const std::string& proxy_name,
            int32_t tryCount = 5,
            int32_t tryInterval = 500);

        AcdResultT SignIn(
            const std::string& agentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string& skill,
            int64_t& handle,
            bool last = false);

        AcdResultT SignOut(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT SetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            const AgentStatusT& agentStatus,
            const std::string& restReason,
            bool last = false);

        AcdResultT GetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            AgentStatusT& agentStatus,
            bool last = false);

        AcdResultT ResetStatuschangetype(
            int64_t handle,
            const std::string& agentId,
            const StatusChangeT& statusChangetype,
            bool last = false);

        AcdResultT ResetAutoAnswer(
            int64_t handle,
            const std::string& agentId,
            bool autoAnswer,
            bool last = false);

        AcdResultT ResetSkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            bool last = false);

        AcdResultT Reset(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT OutboundCall(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t timeout,
            const CallModeT& callMode,
            const CallTypeT& callType,
            bool last = false);

        AcdResultT AnswerCall(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ReleaseCall(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Hold(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Retrieve(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT Consult(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const CallTypeT& callType,
            bool last = false);

        AcdResultT ConsultReconnect(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ConsultTransfer(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT SingleStepTransfer(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool isPassthrough,
            const CallTypeT& transferType,
            bool last = false);

        AcdResultT ConsultConference(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ConferenceJoin(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const ConferenceT& conferenceType,
            bool last = false);

        AcdResultT SetAssociateData(
            int64_t handle,
            const std::string& agentId,
            const std::string& key,
            const std::string& value,
            bool last = false);

        AcdResultT GetAssociateData(
            int64_t handle,
            const std::string& agentId,
            const std::string& key,
            std::string& value,
            bool last = false);

        AcdResultT JumptheQueue(
            int64_t handle,
            const std::string& agentId,
            int64_t requestId,
            bool last = false);

        AcdResultT ForceSignIn(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            bool autoAnswer,
            bool fcSignin,
            const std::string& skill,
            bool last = false);

        AcdResultT ForceSignOut(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT ForceSetAgentStatus(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const AgentStatusT& agentStatus,
            bool last = false);

        AcdResultT Listen(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT StopListen(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT Insert(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT StopInsert(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT SwitchInsertorListen(
            int64_t handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            bool last = false);

        AcdResultT Break(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            bool last = false);

        AcdResultT SendDTMF(
            int64_t handle,
            const std::string& agentId,
            const std::string& digitals,
            bool last = false);

        AcdResultT StartPlay(
            int64_t handle,
            const std::string& agentId,
            const std::string& filename,
            bool last = false);

        AcdResultT StopPlay(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT MuteOn(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT MuteOff(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT GetAgentDetailByAgentID(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            AgentInfoT& agentInfo,
            bool last = false);

        AcdResultT GetAgentDetailByAgentDN(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentDn,
            AgentInfoT& agentInfo,
            bool last = false);

        AcdResultT GetAgentDetailsByAgentIDs(
            int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentIdList,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetAgentDetailsByAgentDNs(
            int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentDnList,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetRecordFileName(
            int64_t handle,
            const std::string& agentId,
            std::string& filename,
            bool last = false);

        AcdResultT GetSkill(
            int64_t handle,
            const std::string& agentId,
            StringListT& skill,
            bool last = false);

        AcdResultT GetRestReason(
            int64_t handle,
            const std::string& agentId,
            StringListT& restReason,
            bool last = false);

        AcdResultT GetAgentNumberBySkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum,
            bool last = false);

        AcdResultT GetAgentDetailsBySkill(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum,
            AgentInfoListT& agentInfoList,
            bool last = false);

        AcdResultT GetSkillWaitingNumber(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            int32_t& freeNum,
            bool last = false);

        AcdResultT GetSkillWaitingCallInfo(
            int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bool last = false);

        AcdResultT GetPrivateQueue(
            int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bool last = false);

        AcdResultT GetSysInfo(
            int64_t handle,
            const std::string& agentId,
            SysInfoT& sysInfo,
            bool last = false);

        AcdResultT SynchronizeCTITime(
            int64_t handle,
            const std::string& agentId,
            int64_t& timestamp,
            bool last = false);

        AcdResultT Heartbeat(
            int64_t handle,
            const std::string& agentId,
            bool last = false);

        AcdResultT ResetConfig(
            const std::string& password,
            bool last = false);

    private:
        void send_SignIn(
            const std::string& agentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            const bool& autoAnswer,
            const bool& fcSignin,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SignIn(
            int64_t& handle,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SignOut(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SignOut(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            const AgentStatusT& agentStatus,
            const std::string& restReason,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SetAgentStatus(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentStatus(
            AgentStatusT& agentStatus,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetStatuschangetype(
            const int64_t& handle,
            const std::string& agentId,
            const StatusChangeT& statusChangetype,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetStatuschangetype(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetAutoAnswer(
            const int64_t& handle,
            const std::string& agentId,
            const bool& autoAnswer,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetAutoAnswer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetSkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetSkill(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Reset(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Reset(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_OutboundCall(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const int32_t& timeout,
            const CallModeT& callMode,
            const CallTypeT& callType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_OutboundCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_AnswerCall(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_AnswerCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ReleaseCall(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ReleaseCall(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Hold(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Hold(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Retrieve(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Retrieve(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Consult(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const CallTypeT& callType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Consult(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultReconnect(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultReconnect(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultTransfer(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultTransfer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SingleStepTransfer(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const bool& isPassthrough,
            const CallTypeT& transferType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SingleStepTransfer(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConsultConference(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConsultConference(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ConferenceJoin(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            const ConferenceT& conferenceType,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ConferenceJoin(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SetAssociateData(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& key,
            const std::string& value,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SetAssociateData(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAssociateData(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& key,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAssociateData(
            std::string& value,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_JumptheQueue(
            const int64_t& handle,
            const std::string& agentId,
            const int64_t& requestId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_JumptheQueue(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSignIn(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const std::string& agentDn,
            const std::string& agentPwd,
            const StatusChangeT& statusChangetype,
            const bool& autoAnswer,
            const bool& fcSignin,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSignIn(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSignOut(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSignOut(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ForceSetAgentStatus(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            const AgentStatusT& agentStatus,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ForceSetAgentStatus(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Listen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Listen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopListen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopListen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Insert(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Insert(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopInsert(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopInsert(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SwitchInsertorListen(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& callerId,
            const std::string& destAgentId,
            const std::string& forCallerDispNum,
            const std::string& forCalleeDispNum,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SwitchInsertorListen(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Break(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Break(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SendDTMF(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& digitals,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SendDTMF(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StartPlay(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& filename,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StartPlay(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_StopPlay(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_StopPlay(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_MuteOn(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_MuteOn(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_MuteOff(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_MuteOff(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailByAgentID(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailByAgentID(
            AgentInfoT& agentInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailByAgentDN(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentDn,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailByAgentDN(
            AgentInfoT& agentInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsByAgentIDs(
            const int64_t& handle,
            const std::string& agentId,
            const StringListT& destAgentIdList,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsByAgentIDs(
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsByAgentDNs(
            const int64_t& handle,
            const std::string& agentId,
            const StringListT& destAgentDnList,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsByAgentDNs(
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetRecordFileName(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetRecordFileName(
            std::string& filename,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkill(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkill(
            StringListT& skill,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetRestReason(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetRestReason(
            StringListT& restReason,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentNumberBySkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentNumberBySkill(
            int32_t& agentNum,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetAgentDetailsBySkill(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetAgentDetailsBySkill(
            int32_t& agentNum,
            AgentInfoListT& agentInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkillWaitingNumber(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkillWaitingNumber(
            int32_t& queueNum,
            int32_t& freeNum,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSkillWaitingCallInfo(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSkillWaitingCallInfo(
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetPrivateQueue(
            const int64_t& handle,
            const std::string& agentId,
            const std::string& destAgentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetPrivateQueue(
            int32_t& queueNum,
            QueueInfoListT& queueInfoList,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_GetSysInfo(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_GetSysInfo(
            SysInfoT& sysInfo,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_SynchronizeCTITime(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_SynchronizeCTITime(
            int64_t& timestamp,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_Heartbeat(
            const int64_t& handle,
            const std::string& agentId,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_Heartbeat(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        void send_ResetConfig(
            const std::string& password,
            int32_t seqid,
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

        AcdResultT recv_ResetConfig(
            bgcc::SharedPointer<bgcc::ConnInfo> conn);

    };

    class acdapiProcessor : public bgcc::BaseProcessor {
    public:
        acdapiProcessor(bgcc::SharedPointer<acdapi> intf);

        virtual ~acdapiProcessor(){ }

        virtual int32_t process(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto);

        virtual std::string get_name() const;

    protected:
        virtual int32_t do_function__(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            const std::string& fname, int32_t seqid);

        bgcc::SharedPointer<acdapi> __intf;

    private:
        int32_t do_SignIn(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SignOut(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SetAgentStatus(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentStatus(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ResetStatuschangetype(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ResetAutoAnswer(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ResetSkill(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Reset(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_OutboundCall(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_AnswerCall(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ReleaseCall(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Hold(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Retrieve(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Consult(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ConsultReconnect(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ConsultTransfer(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SingleStepTransfer(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ConsultConference(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ConferenceJoin(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SetAssociateData(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAssociateData(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_JumptheQueue(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ForceSignIn(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ForceSignOut(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ForceSetAgentStatus(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Listen(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_StopListen(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Insert(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_StopInsert(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SwitchInsertorListen(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Break(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SendDTMF(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_StartPlay(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_StopPlay(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_MuteOn(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_MuteOff(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentDetailByAgentID(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentDetailByAgentDN(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentDetailsByAgentIDs(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentDetailsByAgentDNs(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetRecordFileName(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetSkill(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetRestReason(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentNumberBySkill(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetAgentDetailsBySkill(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetSkillWaitingNumber(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetSkillWaitingCallInfo(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetPrivateQueue(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_GetSysInfo(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_SynchronizeCTITime(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_Heartbeat(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        int32_t do_ResetConfig(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        typedef int32_t (acdapiProcessor::* do_function_ptr)(
            char* request,
            int32_t request_len,
            bgcc::SharedPointer<bgcc::IProtocol> proto,
            int32_t seqid);

        std::map<std::string, do_function_ptr> __fun_map;
    };
}


#endif
