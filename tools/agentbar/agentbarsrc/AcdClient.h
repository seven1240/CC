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

#pragma once

#include <acd.h>
#include <acdcallback.h>
#include "Tool.h"

class AcdCallbackReceiver : public acd::acdcallback
{
public:
	virtual void SendAgentEvent(const acd::AgentEventT &agentEvent, const std::map<std::string, std::string>& ctx);
	virtual void SendMediaEvent(const acd::MediaEventT &mediaEvent, const std::map<std::string, std::string>& ctx);
	virtual void SendQueueEvent(const acd::RouteEventT &routeEvent, const std::map<std::string, std::string>& ctx);
	virtual void SendOtherEvent(const acd::OtherEventT &otherEvent, const std::map<std::string, std::string>& ctx);
};

class AcdClient
{
private:
	bgcc::ServiceManager m_servicemanager;
	acd::acdapiProxy *p_m_mainProxy;
	acd::acdapiProxy *p_m_backProxy;
	string m_MainHost;
	string m_BackHost;
	bool m_isMainHost;
	acd::acdapiProxy *p_m_acdClientProxy;
	LONGLONG m_Handle;

public:
	AcdClient(void);
	~AcdClient(void);

public:
	//**********************【状态设置接口】**********************
	int AcdInitial(const char *mianHost, const char *backHost, int port);
	int AcdUnInitial();
	int AcdSignIn(const char *agentId, const char *agentDn, const char *agentPwd, const acd::StatusChangeT &statusChangetype, bool autoAnswer, bool fcSignin, const char *skill);
	int AcdSignOut(const char *agentId);
	int AcdSetAgentStatus(const char *agentId, const acd::AgentStatusT &agentStatus, const char *restReason = "");
	int AcdGetAgentStatus(const char *agentId, acd::AgentStatusT &agentStatus);
	int AcdResetStatuschangetype(const char *agentId, const acd::StatusChangeT &statusChangetype);
	int AcdResetAutoAnswer(const char *agentId, bool autoAnswer);
	int AcdResetSkill(const char *agentId, const char *skill);
	int AcdReset(const char *agentId);

	//**********************【呼叫控制接口】**********************
	int AcdOutboundCall(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, int timeout, const acd::CallModeT &callMode, const acd::CallTypeT &callType);
	int AcdAnswerCall(const char *agentId);
	int AcdReleaseCall(const char *agentId);
	int AcdHold(const char *agentId);
	int AcdRetrieve(const char *agentId);
	int AcdConsult(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, const acd::CallTypeT &callType);
	int AcdConsultReconnect(const char *agentId);
	int AcdConsultTransfer(const char *agentId);
	int AcdSingleStepTransfer(const char *agentId, const char *callerId, const char *destId, const char *forCallerDispNum, const char *forCalleeDispNum, bool isPassthrough, const acd::CallTypeT &callType);
	int AcdConsultConference(const char *agentId);
	int AcdConferenceJoin(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum, const acd::ConferenceT &conferenceType);
	int AcdSetAssociateData(const char *agentId, const char *key, const char *value);
	int AcdGetAssociateData(const char *agentId, const char *key, string &value);
	int AcdJumptheQueue(const char *agentId, LONGLONG requestId);

	//**********************质检接口**********************
	int AcdForceSignIn(const char *agentId, const char *destAgentId, const char *agentDn, const char *agentPwd, const acd::StatusChangeT &statusChangetype, bool autoAnswer, bool fcSignin, const char *skill);
	int AcdForceSignOut(const char *agentId, const char *destAgentId);
	int AcdForceSetAgentStatus(const char *agentId, const char *destAgentId, const acd::AgentStatusT &agentStatus);
	int AcdListen(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	int AcdStopListen(const char *agentId, const char *destAgentId);
	int AcdInsert(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	int AcdStopInsert(const char *agentId, const char *destAgentId);
	int AcdSwitchInsertorListen(const char *agentId, const char *callerId, const char *destAgentId, const char *forCallerDispNum, const char *forCalleeDispNum);
	int AcdBreak(const char *agentId, const char *destAgentId);

	//**********************媒体接口**********************
	int AcdSendDTMF(const char *agentId, const char *digitals);
	int AcdStartPlay(const char *agentId, const char *filename);
	int AcdStopPlay(const char *agentId);
	int AcdMuteOn(const char *agentId);
	int AcdMuteOff(const char *agentId);

	//**********************查询接口**********************
	int AcdGetAgentDetailByAgentID(const char *agentId, const char *destAgentId, acd::AgentInfoT &agentInfo);
	int AcdGetAgentDetailByAgentDN(const char *agentId, const char *destAgentDn, acd::AgentInfoT &agentInfo);
	int AcdGetAgentDetailsByAgentIDs(const char *agentId, const acd::StringListT &destAgentIdList, acd::AgentInfoListT &agentInfoList);
	int AcdGetAgentDetailsByAgentDNs(const char *agentId, const acd::StringListT &destAgentDnList, acd::AgentInfoListT &agentInfoList);
	int AcdGetRecordFileName(const char *agentId, string &filename);
	int AcdGetRestReason(const char *agentId, acd::StringListT &restReason);
	int AcdGetAgentNumberBySkill(const char *agentId, const char *skill, int &agentNum);
	int AcdGetAgentDetailsBySkill(const char *agentId, const char *skill, int &agentNum, acd::AgentInfoListT &agentInfoList);
	int AcdGetSkillWaitingNumber(const char *agentId, const char *skill, int &queueNum, int &freeNum);
	int AcdGetSkillWaitingCallInfo(const char *agentId, const char *skill, int &queueNum, acd::QueueInfoListT &queueInfoList);
	int AcdGetPrivateQueue(const char *agentId, const char *destAgentId, int &queueNum, acd::QueueInfoListT &queueInfoList);
	int AcdGetSysInfo(const char *agentId, acd::SysInfoT &sysInfo);
	int AcdSynchronizeCTITime(const char *agentId, LONGLONG &timestamp);

	//**********************其他接口**********************
	int AcdHeartbeat(const char *agentId);
	int AcdResetConfig(const char *password);
	int AcdBackup();
};
