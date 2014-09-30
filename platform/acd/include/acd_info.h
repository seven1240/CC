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

#include "const_define.h"

using namespace std;

class CallDirectT {
public:
    enum {
        UNKNOWN,
        INBOUND,
        OUTBOUND
    };

private:
    int m_value;

public:
    CallDirectT(int32_t value);
    ~CallDirectT();
    void set_value(int32_t value);
    int32_t get_value();
    bool isValid();
};

class ReleaseCauseT {
public:
    enum {
        UNKNOWN,
        THISPARTY,
        OTHERPARTY
    };

private:
    int m_value;

public:
    ReleaseCauseT(int32_t value);
    ~ReleaseCauseT();
    void set_value(int32_t value);
    int32_t get_value();
    bool isValid();
};

class callinfo {
private:
    ims::SessionIdT m_sessionId;
    ims::CallIdT m_callId;
    string m_agentId;
    string m_agentDn;
    string m_skill;
    string m_caller;
    string m_callee;

    time_t m_waitbegin;
    time_t m_waitend;
    time_t m_ackbegin;
    time_t m_ackend;
    time_t m_callbegin;
    time_t m_callend;

    ims::PartyAttributeT m_callType;
    CallDirectT m_callDirect;
    ReleaseCauseT m_releaseCause;
    string m_recordFilename;

    bool m_routecall;

public:
    callinfo();
    ~callinfo();
    void Initial(ims::SessionIdT sessionId, const ims::CallIdT& callId, const string& agentId,
                 const string& agentDn, const string& skill, const string& caller, const string& callee,
                 time_t waitbegin, time_t waitend);
    void SetAniDnis(const string& caller, const string& callee);
    void SetAckBegin(time_t t);
    void SetAckEnd(time_t t);
    void SetCallBegin(time_t t);
    void SetCallEnd(time_t t);
    void SetCallType(const ims::PartyAttributeT& callType);
    void SetCallDirect(int32_t callDirect);
    void SetReleaseCause(int32_t releaseCause);
    void SetRecordFilename(const string& recordFilename);
    void SetRoutecall();
    bool GetRoutecall();
    bool isValid();
    void reset();
    void WriteCallLog();
};
