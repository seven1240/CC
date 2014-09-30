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

#ifndef APSERVER_H
#define APSERVER_H

#include <bgcc.h>
#include "acd.h"
#include "acdcommon.h"
#include "AgentProxy.h"

using namespace acd;

//服务信息，函数意义参考acd的bidl文件定义
class ApServer: public acdapi {
public:

    bool InitApServer(std::string ApListenIp, int32_t ApListenPort, int32_t threadPoolNum);

    virtual AcdResultT SignIn(
        const std::string& agentId,
        const std::string& agentDn,
        const std::string& agentPwd,
        const StatusChangeT& statusChangetype,
        bool autoAnswer,
        bool fcSignin,
        const std::string& skills,
        int64_t& handle, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SignOut(int64_t handle,
                               const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SetAgentStatus(int64_t handle,
                                      const std::string& agentId,
                                      const AgentStatusT& agentStatus,
                                      const std::string& restReason, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAgentStatus(int64_t handle,
                                      const std::string& agentId,
                                      AgentStatusT& agentStatus, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ResetStatuschangetype(int64_t handle,
            const std::string& agentId,
            const StatusChangeT& statusChangetype, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ResetAutoAnswer(int64_t handle,
                                       const std::string& agentId,
                                       bool autoAnswer, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ResetSkill(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& skills, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Reset(int64_t handle,
                             const std::string& agentId, const std::map<std::string, std::string>& ctx);


    /*
     *********************************************************************************
     *
     * 呼叫控制接口
     *
     *********************************************************************************
     */

    virtual AcdResultT OutboundCall(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& callerId,
                                    const std::string& destId,
                                    const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum,
                                    int32_t timeout,
                                    const CallModeT& callMode,
                                    const CallTypeT& callType, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT AnswerCall(int64_t handle,
                                  const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ReleaseCall(int64_t handle,
                                   const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Hold(int64_t handle,
                            const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Retrieve(int64_t handle,
                                const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Consult(int64_t handle,
                               const std::string& agentId,
                               const std::string& callerId,
                               const std::string& destId,
                               const std::string& forCallerDispNum,
                               const std::string& forCalleeDispNum,
                               const CallTypeT& callType, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ConsultReconnect(int64_t handle,
                                        const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ConsultTransfer(int64_t handle,
                                       const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SingleStepTransfer(int64_t handle,
                                          const std::string& agentId,
                                          const std::string& callerId,
                                          const std::string& destId,
                                          const std::string& forCallerDispNum,
                                          const std::string& forCalleeDispNum,
                                          bool isPassthrough,
                                          const CallTypeT& transferType, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ConsultConference(int64_t handle,
                                         const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ConferenceJoin(int64_t handle,
                                      const std::string& agentId,
                                      const std::string& callerId,
                                      const std::string& destAgentId,
                                      const std::string& forCallerDispNum,
                                      const std::string& forCalleeDispNum,
                                      const ConferenceT& conferenceType, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SetAssociateData(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& key,
                                        const std::string& value, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAssociateData(int64_t handle,
                                        const std::string& agentId,
                                        const std::string& key,
                                        std::string& value, const std::map<std::string, std::string>& ctx);

    /*
     *********************************************************************************
     *
     * 质检接口
     *
     *********************************************************************************
     */

    virtual AcdResultT ForceSignIn(int64_t handle,
                                   const std::string& agentId,
                                   const std::string& destAgentId,
                                   const std::string& agentDn,
                                   const std::string& agentPwd,
                                   const StatusChangeT& statusChangetype,
                                   bool autoAnswer,
                                   bool fcSignin,
                                   const std::string& skills, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ForceSignOut(int64_t handle,
                                    const std::string& agentId,
                                    const std::string& destAgentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ForceSetAgentStatus(int64_t handle,
                                           const std::string& agentId,
                                           const std::string& destAgentId,
                                           const AgentStatusT& agentStatus, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Listen(int64_t handle,
                              const std::string& agentId,
                              const std::string& callerId,
                              const std::string& destAgentId,
                              const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT StopListen(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Insert(int64_t handle,
                              const std::string& agentId,
                              const std::string& callerId,
                              const std::string& destAgentId,
                              const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT StopInsert(int64_t handle,
                                  const std::string& agentId,
                                  const std::string& destAgentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SwitchInsertorListen(int64_t handle,
                                            const std::string& agentId,
                                            const std::string& callerId,
                                            const std::string& destAgentId,
                                            const std::string& forCallerDispNum,
                                            const std::string& forCalleeDispNum, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Break(int64_t handle,
                             const std::string& agentId,
                             const std::string& destAgentId, const std::map<std::string, std::string>& ctx);


    /*
     *********************************************************************************
     *
     * 媒体接口
     *
     *********************************************************************************
     */

    virtual AcdResultT SendDTMF(int64_t handle,
                                const std::string& agentId,
                                const std::string& digitals, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT StartPlay(int64_t handle,
                                 const std::string& agentId,
                                 const std::string& filename, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT StopPlay(int64_t handle,
                                const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT MuteOn(int64_t handle,
                              const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT MuteOff(int64_t handle,
                               const std::string& agentId, const std::map<std::string, std::string>& ctx);

    /*
     *********************************************************************************
     *
     * 查询接口
     *
     *********************************************************************************
     */

    virtual AcdResultT GetAgentDetailByAgentID(int64_t handle,
            const std::string& agentId,
            const std::string& destAgentId,
            AgentInfoT& agentInfo, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAgentDetailByAgentDN(int64_t handle,
            const std::string& agentId,
            const std::string& destAgentDn,
            AgentInfoT& agentInfo, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAgentDetailsByAgentIDs(int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentIdList,
            AgentInfoListT& agentInfoList, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAgentDetailsByAgentDNs(int64_t handle,
            const std::string& agentId,
            const StringListT& destAgentDnList,
            AgentInfoListT& agentInfoList, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetRecordFileName(int64_t handle,
                                         const std::string& agentId,
                                         std::string& filename, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetRestReason(int64_t handle,
                                     const std::string& agentId,
                                     StringListT& restReason, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetSkill(
        int64_t handle,
        const std::string& agentId,
        StringListT& skill,
        const std::map<std::string, std::string>& ctx);



    /*
     *********************************************************************************
     *
     * 技能队列类查询
     *
     *********************************************************************************
     */

    virtual AcdResultT GetAgentNumberBySkill(int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetAgentDetailsBySkill(int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& agentNum,
            AgentInfoListT& agentInfoList, const std::map<std::string, std::string>& ctx);

    /*
     *********************************************************************************
     *
     * 路由请求类查询
     *
     *********************************************************************************
     */


    virtual AcdResultT GetSkillWaitingNumber(int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            int32_t& freeNum, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetSkillWaitingCallInfo(int64_t handle,
            const std::string& agentId,
            const std::string& skill,
            int32_t& queueNum,
            QueueInfoListT& queueInfoList, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT GetPrivateQueue(int64_t handle,
                                       const std::string& agentId,
                                       const std::string& destAgentId,
                                       int32_t& queueNum,
                                       QueueInfoListT& queueInfoList, const std::map<std::string, std::string>& ctx);


    /*
     *********************************************************************************
     *
     * 系统类查询
     *
     *********************************************************************************
     */

    virtual AcdResultT GetSysInfo(int64_t handle,
                                  const std::string& agentId,
                                  SysInfoT& sysInfo, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT SynchronizeCTITime(int64_t handle,
                                          const std::string& agentId,
                                          int64_t& timestamp, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT Heartbeat(int64_t handle,
                                 const std::string& agentId, const std::map<std::string, std::string>& ctx);

    virtual AcdResultT ResetConfig(const std::string& password,
                                   const std::map<std::string, std::string>& ctx);

    virtual AcdResultT JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId,
                                    const std::map<std::string, std::string>& ctx);
private:


    std::string _ApListenIp;
    int32_t _ApListenPort;
    Server* _server;
    int32_t _threadPoolNum;
public:
    /**
     * Default constructor
     */
    ApServer() {
    }

    /**
     * Destructor
     */
    virtual ~ApServer();
}; // end of class ApServer


#endif // APSERVER_H

