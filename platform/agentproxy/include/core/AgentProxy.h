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

#ifndef AGENTPROXY
#define AGENTPROXY

#ifdef _WIN32
#include <hash_map>

#else
#include <ext/hash_map>
using namespace __gnu_cxx;  //for hash_map
#endif


#include <string>
#include <vector>
#include <time.h>
#include <bgcc.h>


#include "acdcommon.h"
#include "acd.h"
#include "ap.h"

#include "ApCommon.h"
#include "ApClient.h"
#include "ApServer.h"
#include "ApService.h"
#include "Queue.h"
#include "ApCallbackThread.h"
#include "ApHeartBeatThread.h"
#include "ApListenThread.h"

using namespace ap;
using namespace acd;

class ApServer;
class ApClient;
class ApService;

class AgentProxy {
    typedef Guard<Mutex> ScopeGuard;

    /*公有成员接口声明*/
public:
    /**
     * @brief Init:AgentProxy类初始化函数，用于初始化消息队列、hash_map、创建事件线程、读取log、conf配置等功能
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时05分33秒
     */
    bool Init();

    /**
     * @brief SetMapAgentIdData:插入一条新的连接数据agentdata
     *
     * @param agentInfo
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 12时59分09秒
     */
    bool SetMapAgentIdData(AgentData* agentInfo);

    /**
     * @brief DelMapAgentIdData:清除指定工号的连接信息
     * @param agentId
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时07分04秒
     */
    bool DelMapAgentIdData(const std::string& agentId);

    /**
     * @brief ClearMapAgentData:清空hash_map所有存储信息
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时07分04秒
     */
    bool ClearMapAgentData();

    /**
     * @brief ResetProxy:重置指定工号的连接信息
     *
     * @param agentId    指定的工号
     * @param agentInfo  重置的连接信息
     *
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时07分30秒
     */
    bool ResetProxy(const std::string& agentId, AgentData* agentInfo);

    /**
     * @brief GetAgentData 获取指定工号的连接信息
     *
     * @param agentId    指定的工号
     * @param agentInfo  获取的连接信息
     *
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月29日 17时23分25秒
     */
    bool GetAgentData(const std::string& agentId, AgentData& agentInfo);

    /**
     * @brief GetAgentData 根据工号获取handle值
     *
     * @param agentId    指定的工号
     * @param agentInfo  输出参数：获取的handle值
     *
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月29日 17时23分25秒
     */
    bool GetAgentHandleById(const std::string agentId, int64_t& handle);

    /**
     * @brief GetAgentData 根据工号查看坐席信息是否存在
     * @param agentId    指定的工号
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月29日 17时23分25秒
     */
    bool IsAgentHasExist(const std::string agentId);

    /**
     * @brief GetAgentData 更新坐席信息
     * @param agentinfo    指定的更新的坐席信息
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月29日 17时23分25秒
     */
    bool UpdateAgentData(AgentData& agentinfo);

    /**
     * @brief SetAgentOldProxyNull 将oldproxy置空
     * @param agentId          指定的更新的坐席工号
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool SetAgentOldProxyNull(const std::string agentId, int64_t handle);

    /**
     * @brief SetAgentHandleById    更新指定的坐席的handle值
     * @param agentId               指定的坐席工号
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool SetAgentHandleById(const std::string agentId, int64_t handle);

    /**
     * @brief SetAgentFlag          设置指定坐席是否被删除的标志位
     * @param agentId               指定的坐席工号
     * @param flag                  标示是否signout
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SetAgentFlag(const std::string agentId, int32_t flag);

    /**
     * @brief SendCallEvent         发送呼叫事件处理函数
     * @param acdCallEvent          坐席呼叫事件
     * @param threadNo              处理线程ID
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SendCallEvent(const AgentEventT& acdCallEvent, int32_t threadNo);

    /**
     * @brief SendOtherEvent        发送其他事件处理函数
     * @param acdCallEvent          坐席呼叫事件
     * @param threadNo              处理线程ID
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SendOtherEvent(const OtherEventT& acdOtherEvent, int32_t threadNo);

    /**
     * @brief SendOtherEvent        发送路由事件处理函数
     * @param acdCallEvent          坐席呼叫事件
     * @param threadNo              处理线程ID
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SendRouteEvent(const RouteEventT& acdRouteEvent, int32_t threadNo);

    /**
     * @brief SendOtherEvent        发送媒体事件处理函数
     * @param acdCallEvent          坐席呼叫事件
     * @param threadNo              处理线程ID
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SendMediaEvent(const MediaEventT& acdMediaEvent, int32_t threadNo);

    /**
     * @brief GetHeartBeatTimeOut      获取心跳事件间隔
     * @return 心跳时间
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    int32_t GetHeartBeatTimeOut();

    /**
     * @brief AddAcdCallEvent :写呼叫事件进队列
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时08分14秒
     */
    bool AddAcdCallEvent(AgentEventT& event);

    /**
     * @brief AddAcdMediaEvent :写媒体事件进队列
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时08分27秒
     */
    bool AddAcdMediaEvent(MediaEventT& event);

    /**
     * @brief AddAcdRouteEvent :写路由事件进队列
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时08分37秒
     */
    bool AddAcdRouteEvent(RouteEventT& event);

    /**
     * @brief AddAcdOtherEvent :写其他事件进队列
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时08分47秒
     */
    bool AddAcdOtherEvent(OtherEventT& event);

    /**
     * @brief GetAcdCallEvent :从队列读取呼叫事件
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时08分59秒
     */
    bool GetAcdCallEvent(AgentEventT& event, const int32_t threadNo);

    /**
     * @brief GetAcdMediaEvent 从队列读取媒体事件
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时09分11秒
     */
    bool GetAcdMediaEvent(MediaEventT& event, const int32_t threadNo);

    /**
     * @brief GetAcdRouteEvent :从队列读取路由事件
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时09分22秒
     */
    bool GetAcdRouteEvent(RouteEventT& event, const int32_t threadNo);

    /**
     * @brief GetAcdOtherEvent :从队列读取其他事件
     *
     * @param event
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时09分36秒
     */
    bool GetAcdOtherEvent(OtherEventT& event, const int32_t threadNo);

    /**
     * @brief CreateAcdCBThread :创建处理回调消息线程
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时09分54秒
     */
    bool CreateAcdCBThread();

    /**
     * @brief CreateApListenThread     创建监听AP服务的处理线程
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool CreateApListenThread();

    /**
     * @brief IsQueueEmpty :判断事件队列是否为空
     *
     * @param threadNo
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时10分03秒
     */
    bool IsQueueEmpty(const int32_t& threadNo);

    /**
     * @brief HeartBeat :检测ap与ACD之间的心跳状态
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时10分20秒
     */
    void HeartBeat();

    /**
     * @brief Backup:倒换，当心跳异常时且满足条件，client改用备连接
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时10分45秒
     */
    bool Backup();

    /**
     * @brief Instance :返回全局唯一的AgentProxy实例
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时14分28秒
     */
    static AgentProxy* Instance() {
        static AgentProxy agentproxy;
        return &agentproxy;
    }

    /**
     * @brief Destroy 销毁资源
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月29日 13时18分58秒
     */
    void Destroy();
    /**
     * @brief CreateCheckHBThread :创建检查心跳消息线程
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 13时09分54秒
     */
    bool CreateCheckHBThread();

    /**
     * @brief IsNeedApThreadShutdown :杀掉线程
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年07月01日 15时26分48秒
     */
    bool IsNeedApThreadShutdown();

    /**
     * @brief CreateClient            创建连接ACD的客户端实例
     * @param Ip                      ACD的IP地址
     * @param Port                    ACD的端口
     * @param connectNum              连接ACD的连接数
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool CreateClient(std::string Ip, int32_t Port, int32_t connectNum);

    /**
     * @brief ClearHaveSendMsgNum 清空转发消息数
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年07月02日 14时08分36秒
     */
    void ClearHaveSendMsgNum();

    /**
     * @brief StartApListen            开始监听AP的服务
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool StartApListen();

    /**
     * @brief ClearTimeOutAgentInfo       清除已经signout但还存在信息的坐席，防止丢失signout事件
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void ClearTimeOutAgentInfo(std::string agentId);

    void ChangeAgentListIp(AgentInfoListT& agentInfoList);
    void ChangeAgentIp(AgentInfoT& agentInfo);


    /*衔接server和client的公共接口*/
public:

    AcdResultT SignIn(const std::string& agentId,
                      const std::string& agentDn, const std::string& agentPwd,
                      const StatusChangeT& statusChangetype, bool autoAnswer,
                      bool fcSignin, const std::string& skills,
                      int64_t& handle,
                      const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SignOut(int64_t handle, const std::string& agentId,
                       const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SetAgentStatus(int64_t handle, const std::string& agentId,
                              const AgentStatusT& agentStatus, const std::string& restReason,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetAgentStatus(int64_t handle, const std::string& agentId, AgentStatusT& agentStatus,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ResetStatuschangetype(int64_t handle, const std::string& agentId,
                                     const StatusChangeT& statusChangetype, const std::map<std::string, std::string> ctx,
                                     uint64_t time_rcv);
    AcdResultT ResetAutoAnswer(int64_t handle, const std::string& agentId, bool autoAnswer,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ResetSkill(int64_t handle, const std::string& agentId, const std::string& skill,
                          const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Reset(int64_t handle, const std::string& agentId,
                     const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT OutboundCall(int64_t handle, const std::string& agentId, const std::string& callerId,
                            const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum,
                            int32_t timeout, const CallModeT& callMode, const CallTypeT& callType,
                            const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT AnswerCall(int64_t handle, const std::string& agentId,
                          const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ReleaseCall(int64_t handle, const std::string& agentId,
                           const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Hold(int64_t handle, const std::string& agentId,
                    const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT RetrieveHeld(int64_t handle, const std::string& agentId,
                            const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Consult(int64_t handle, const std::string& agentId, const std::string& callerId,
                       const std::string& destId, const std::string& forCallerDispNum, const std::string& forCalleeDispNum,
                       const CallTypeT& callType, const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ConsultReconnect(int64_t handle, const std::string& agentId,
                                const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ConsultTransfer(int64_t handle, const std::string& agentId,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SingleStepTransfer(int64_t handle, const std::string& agentId,
                                  const std::string& callerId, const std::string& destId, const std::string& forCallerDispNum,
                                  const std::string& forCalleeDispNum, bool isPassthrough, const CallTypeT& transferType,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ConsultConference(int64_t handle, const std::string& agentId,
                                 const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ConferenceJoin(int64_t handle, const std::string& agentId, const std::string& callerId,
                              const std::string& destAgentId, const std::string& forCallerDispNum,
                              const std::string& forCalleeDispNum, const ConferenceT& conferenceType,
                              const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SetAssociateData(int64_t handle, const std::string& agentId, const std::string& key,
                                const std::string& value, const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetAssociateData(int64_t handle, const std::string& agentId, const std::string& key,
                                std::string& value, const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ForceSignIn(int64_t handle,
                           const std::string& agentId, const std::string& destAgentId,
                           const std::string& agentDn, const std::string& agentPwd,
                           const StatusChangeT& statusChangetype, bool autoAnswer, bool fcSignin,
                           const std::string& skills, const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ForceSignOut(int64_t handle, const std::string& agentId, const std::string& destAgentId,
                            const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ForceSetAgentStatus(int64_t handle, const std::string& agentId,
                                   const std::string& destAgentId, const AgentStatusT& agentStatus,
                                   const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Listen(int64_t handle, const std::string& agentId, const std::string& callerId,
                      const std::string& destAgentId, const std::string& forCallerDispNum,
                      const std::string& forCalleeDispNum, const std::map<std::string, std::string> ctx,
                      uint64_t time_rcv);
    AcdResultT StopListen(int64_t handle, const std::string& agentId, const std::string& destAgentId,
                          const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Insert(int64_t handle, const std::string& agentId, const std::string& callerId,
                      const std::string& destAgentId, const std::string& forCallerDispNum,
                      const std::string& forCalleeDispNum, const std::map<std::string, std::string> ctx,
                      uint64_t time_rcv);
    AcdResultT StopInsert(int64_t handle, const std::string& agentId, const std::string& destAgentId,
                          const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SwitchInsertorListen(int64_t handle, const std::string& agentId,
                                    const std::string& callerId, const std::string& destAgentId, const std::string& forCallerDispNum,
                                    const std::string& forCalleeDispNum, const std::map<std::string, std::string> ctx,
                                    uint64_t time_rcv);
    AcdResultT Break(int64_t handle, const std::string& agentId, const std::string& destAgentId,
                     const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SendDTMF(int64_t handle, const std::string& agentId, const std::string& digitals,
                        const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT StartPlay(int64_t handle, const std::string& agentId, const std::string& filename,
                         const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT StopPlay(int64_t handle, const std::string& agentId,
                        const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT MuteOn(int64_t handle, const std::string& agentId,
                      const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT MuteOff(int64_t handle, const std::string& agentId,
                       const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetAgentDetailByAgentID(int64_t handle, const std::string& agentId,
                                       const std::string& destAgentId, AgentInfoT& agentInfo, const std::map<std::string, std::string> ctx,
                                       uint64_t time_rcv);
    AcdResultT GetAgentDetailByAgentDN(int64_t handle, const std::string& agentId,
                                       const std::string& destAgentDn, AgentInfoT& agentInfo, const std::map<std::string, std::string> ctx,
                                       uint64_t time_rcv);
    AcdResultT GetAgentDetailsByAgentIDs(int64_t handle, const std::string& agentId,
                                         const StringListT& destAgentIdList, AgentInfoListT& agentInfoList,
                                         const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetAgentDetailsByAgentDNs(int64_t handle, const std::string& agentId,
                                         const StringListT& destAgentDnList, AgentInfoListT& agentInfoList,
                                         const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetRecordFileName(int64_t handle, const std::string& agentId, std::string& filename,
                                 const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetRestReason(int64_t handle, const std::string& agentId, StringListT& restReason,
                             const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetSkill(int64_t handle, const std::string& agentId, StringListT& skill,
                        const std::map<std::string, std::string>& ctx, uint64_t time_rcv);
    AcdResultT GetAgentNumberBySkill(int64_t handle, const std::string& agentId,
                                     const std::string& skill, int32_t& agentNum, const std::map<std::string, std::string> ctx,
                                     uint64_t time_rcv);
    AcdResultT GetAgentDetailsBySkill(int64_t handle, const std::string& agentId,
                                      const std::string& skill, int32_t& agentNum, AgentInfoListT& agentInfoList,
                                      const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetSkillWaitingNumber(int64_t handle, const std::string& agentId,
                                     const std::string& skill, int32_t& queueNum, int32_t& freeNum,
                                     const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetSkillWaitingCallInfo(int64_t handle, const std::string& agentId,
                                       const std::string& skill, int32_t& queueNum, QueueInfoListT& queueInfoList,
                                       const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetPrivateQueue(int64_t handle, const std::string& agentId,
                               const std::string& destAgentId, int32_t& queueNum, QueueInfoListT& queueInfoList,
                               const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT GetSysInfo(int64_t handle, const std::string& agentId, SysInfoT& sysInfo,
                          const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT SynchronizeCTITime(int64_t handle, const std::string& agentId, int64_t& timestamp,
                                  const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT Heartbeat(int64_t handle, const std::string& agentId,
                         const std::map<std::string, std::string> ctx, uint64_t time_rcv);
    AcdResultT ResetConfig(const std::string& password, const std::map<std::string, std::string>& ctx,
                           uint64_t time_rcv);

    AcdResultT JumptheQueue(int64_t handle, const std::string& agentId, int64_t requestId,
                            const std::map<std::string, std::string>& ctx, uint64_t time_rcv);
    bool ReLoadConfig();
    bool GetAgents(ApAgentInfoListT& agentInfoList);


    /*私有成员接口声明*/
private:
    /**
    * @brief readConf :读取配置文件内容
    *
    * @return
    * @see
    * @note
    * @author  caozhenxing(caozhenxing@baidu.com)
    * @date    2013年03月25日
    */
    bool readConf(const char* conf_filepath);

    /**
     * @brief getApCommonConf       获取ap的通用配置
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool getApCommonConf(const char* conf_filepath);

    /**
     * @brief getAcdConf       获取ap的关于acd的连接信息配置
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool getAcdConf(const char* conf_filepath);

    /**
     * @brief getBgccConf       获取ap的关于bgcc的相关配置
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool getBgccConf(const char* conf_filepath);
    /**
     * @brief Init_log :初始化日志模块
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年06月28日 19时55分35秒
     */
    bool Init_log();

    /**
     * @brief SetApThreadShutdown      设置关闭线程标志位
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void SetApThreadShutdown();

    /**
     * @brief GetCtiService 获取当前指向
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年07月09日 15时09分10秒
     */
    APCONNACDSTATE GetCtiService();

    /**
     * @brief SetCtiService 设置当前AP指向
     *
     * @param State
     *
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2012年07月09日 15时09分24秒
     */
    void SetCtiService(APCONNACDSTATE State);

    /**
     * @brief SetApClient       重新设置连接ACD的客户端实例
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool SetApClient(ApClient* client);

    /**
     * @brief AddHeartBeatCount       心跳异常次数+1
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void AddHeartBeatCount();

    /**
     * @brief ClearHeartBeatCount       清空心跳异常次数
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void ClearHeartBeatCount();

    /**
     * @brief GetHeartBeatCount       获取心跳异常次数
     * @return  异常心跳次数
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    int32_t GetHeartBeatCount();

    /**
     * @brief GetValidAcd       获取可用ACD
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool GetValidAcd();

    /**
     * @brief GetValidAcd       尝试连接ACD
     * @return  成功：true;失败：false
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    bool TryConnAcd(std::string strIp, int32_t Port, APCONNACDSTATE state);

    /**
     * @brief ReSignIn       连接ACD后进行坐席重签
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    void ReSignIn(APCONNACDSTATE state);

    /**
     * @brief getProxyName       获取客户端连接的proxyname
     * @return  连接ID
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    std::string getProxyName(const std::map<std::string, std::string>& ctx);

    /**
     * @brief getProxyIP       获取客户端IP地址
     * @return
     * @see
     * @note
     * @author  caozhenxing(caozhenxing@baidu.com)
     * @date    2013年03月26日 21时23分25秒
     */
    std::string getProxyIP(const std::map<std::string, std::string>& ctx);

    /*私有成员变量声明*/
private:

    int32_t              _heartBeatCount;           /** 当前心跳数*/
    int32_t              _apClientHandle;           /** 当前proxy的连接句柄*/
    int32_t              _apListenPort;
    int32_t              _ACDPort;                  /** ACD的端口号*/
    int32_t              _apListenPortOwn;
    int32_t              _apHeartBeatTimeout;
    int32_t              _apHeartBeatMaxTrytimes;
    int32_t              _apWarnSendmsgTimeout;
    int32_t              _apServerThreadPoolNum;    /**bgcc服务的线程数**/
    int32_t              _apClientConnNum;          /**bgcc连接数，配置**/
    int32_t              _CallbackThreadNum;        /**接收回调事件线程数**/
    int32_t              _AcdMainPort;
    int32_t              _AcdBackupPort;
    int32_t              _AgentTimeOut;             /**超时的时间（用于删除未收到signout事件的坐席）**/

    ApServer*            _pApServer;                /** ApServer对象指针*/
    ApService*           _pApService;               /** ApService对象指针*/
    ApClient*            _pApClient;                /** ApClient对象指针*/
    ApEventQ*            _ApEventQ;                 /** 事件队列指针，初始化时赋值*/
    Thread*
    _apHBCheckThread;          /** 心跳检测智能指针数组（继承BGCC）,检测主备ACD心跳*/
    Thread*              _apListenThread;           /** AP监听接口线程指针*/

    std::string          _apHost;
    std::string          _strMainACDIP;             /** 主ACD的IP地址*/
    std::string          _strBackACDIP;             /** 备ACD的IP地址*/
    APCONNACDSTATE       _ctiService;               /** 标示当前连的哪一台ACD*/
    MapAgentIdDataType   _mapAgentIdData;           /** 维护agentbar连接数据的hash_map*/
    std::vector<Thread*> _apCallbackThreadVec;
    ServiceManager       _serviceManager;
    volatile bool        _shutdown;

    Mutex                _mapMutex;                 /*map锁*/
    Mutex                _threadShutdownMutex;
    Mutex                _ctiServiceMutex ;
    Mutex                _HBCountMutex;
    Mutex                _ApClientMutex;            /** proxy锁*/
private:
    AgentProxy() {}
    ~AgentProxy() {}

};

#endif // AGENTPROXY

