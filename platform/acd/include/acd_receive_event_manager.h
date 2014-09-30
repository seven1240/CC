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

#include "safe_queue.h"
#include "thread.h"

class acd_callevent_receiver : public Thread {
private:
    SafeQueue<ims::CallEventT*> m_event_queue;
protected:
    virtual void Method();
public:
    acd_callevent_receiver();
    ~acd_callevent_receiver();
    void push_event(const ims::CallEventT& event);
};

class acd_mediaevent_receiver : public Thread {
private:
    SafeQueue<ims::MediaEventT*> m_event_queue;
protected:
    virtual void Method();
public:
    acd_mediaevent_receiver();
    ~acd_mediaevent_receiver();
    void push_event(const ims::MediaEventT& event);
};

class acd_routeevent_receiver : public Thread {
private:
    SafeQueue<ims::RouteEventT*> m_event_queue;
protected:
    virtual void Method();
public:
    acd_routeevent_receiver();
    ~acd_routeevent_receiver();
    void push_event(const ims::RouteEventT& event);
};

class acd_otherevent_receiver : public Thread {
private:
    SafeQueue<ims::OtherEventT*> m_event_queue;
protected:
    virtual void Method();
public:
    acd_otherevent_receiver();
    ~acd_otherevent_receiver();
    void push_event(const ims::OtherEventT& event);
};

class acd_receive_event_manager {
private:
    acd_callevent_receiver m_callevent_receiver;
    acd_mediaevent_receiver m_mediaevent_receiver;
    acd_routeevent_receiver m_routeevent_receiver;
    acd_otherevent_receiver m_otherevent_receiver;
public:
    acd_receive_event_manager();
    ~acd_receive_event_manager();
    void Initialize();
    void Uninitialize();
    void push_event(const ims::CallEventT& event);
    void push_event(const ims::MediaEventT& event);
    void push_event(const ims::RouteEventT& event);
    void push_event(const ims::OtherEventT& event);
};
