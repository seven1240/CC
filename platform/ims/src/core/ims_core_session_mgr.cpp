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

#include "fs_mgr.h"
#include "ims_lock.h"
#include "ims_log.h"
#include "event_handler.h"
#include "ims_core_session_mgr.h"
using namespace ims;
using namespace bgcc;

ims_request_t* ims_session_manager_t::get_request(ims::ReqIdT reqid) {
    rw_lock_t lock(runtime.req_mgr_lock);

    if (!lock.locked()) {
        WARNING_LOG("get request (reqid=%lu) failed(request table lock error)", reqid);
        return NULL;
    }

    req_info_t* reqinfo = NULL;
    std::map<ims::ReqIdT, req_info_t*>::const_iterator cit = runtime.req_mgr.find(reqid);

    if (cit == runtime.req_mgr.end() || NULL == cit->second || NULL == cit->second->thread) {
        WARNING_LOG("get request (id=%lu) failed(request not exist)", reqid);
        return NULL;
    }

    reqinfo = cit->second;

    return dynamic_cast<ims_request_t*>(reqinfo->thread->get_runner().get());
}

bool ims_session_manager_t::create_session(uint32_t fs_no,
        ims::ReqIdT reqid,
        ims_session_create_reason_t reason,
        ims::session_thread_ptr thrd,
        const char* oricaller,
        const char* oricalled,
        ims::SessionIdT& id) {

    uint64_t curr = get_sessioncount();
    uint64_t max = maxsession();

    if (curr >= max) {
        WARNING_LOG("create session(curr:%lu>=max:%lu), try clear dead session", curr, max);
        clear_dead_session();
        curr = get_sessioncount();

        if (curr >= max) {
            WARNING_LOG("create session failed.(curr:%lu>=max:%lu)after clear dead session", curr, max);
            return false;
        }
    }

    //ims_session_t *session= new(std::nothrow) ims_session_t(fs_no,reqid,reason,thrd);
    ims_session_t* session = session_pool.get();

    if (!session) {
        WARNING_LOG("create session(fs_no=%u,reqid=%lu) failed(memory error)", fs_no, reqid);
        return false;
    }

    session->init(fs_no, reqid, reason, thrd);

    strncpy(session->oricaller, oricaller ? oricaller : "", LEN_64);
    strncpy(session->oricalled, oricalled ? oricalled : "", LEN_64);
    id = session->id;

    rw_lock_t lock(session_table_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("create session(fs_no=%u,reqid=%lu) failed(session table lock error)"
                    , fs_no, reqid);
        session->uninit();
        session_pool.put(&session);
        return false;
    }

    session_table[id] = session;

    if (session_table.count(id) == 0) {
        WARNING_LOG("create session(fs_no=%u,reqid=%lu) failed(insert to hash error)"
                    , fs_no, reqid);
        session->uninit();
        session_pool.put(&session);
        return false;
    }

    if (!runtime.inc_session()) {
        WARNING_LOG("inc concurrency count failed");
    }

    NOTICE_LOG("create session(fs_no=%u,reqid=%lu,id=%lu) success", fs_no, reqid, id);

    return true;
}


bool ims_session_manager_t::remove_session(ims::SessionIdT id) {
    ims_session_t* session = NULL;
    rw_lock_t lock(session_table_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("remove session(id=%lu) failed(session table lock error)", id);
        return false;
    }

    if (session_table.find(id) == session_table.end()) {
        WARNING_LOG("remove session(id=%lu) failed(sessionid error)", id);
        return false;
    }

    session = session_table[id];

    session_table.erase(id);

    if (session) {
        session->uninit();
        session_pool.put(&session);
    }

    if (!runtime.dec_session()) {
        WARNING_LOG("dec concurrency count failed");
    }

    rt_del_session_route(id);
    NOTICE_LOG("remove session(id=%lu) success", id);

    return true;

}

bool ims_session_manager_t::destroy_session(ims::SessionIdT id) {
    ims_session_t* session = NULL;
    {
        rw_lock_t lock(session_table_lock);

        if (!lock.locked()) {
            WARNING_LOG("destroy session(id=%lu) failed(session table lock error)", id);
            return false;
        }

        if (session_table.find(id) == session_table.end()) {
            TRACE_LOG("destroy session(id=%lu) sessionid not exist, do nothing, return true.", id);
            return true;
        }

        session = session_table[id];
    }

    if (session && get_channels_size(id) > 0) {
        // destroy all the calls and channels inside and then remove session
        TRACE_LOG("in destroy_session(id=%lu) session isn't empry, destroy channels and calls inside.", id);
        fs_tool_t opr(ims_tool_t::get_fsno(id));

        if (!opr.valid()) {
            WARNING_LOG("destroy session(%lu) failed, fetch_opr error.", id);
            return false;
        }

        std::list<const char*> chls;

        if (!get_channelsbysession(id, chls)) {
            WARNING_LOG("destroy session(id=%lu) failed. getchannelsbysession failed.", id);
            return false;
        }

        // session not locked, so the actuall channels in session may be changed by other thread,
        // Don't care it, because it's sematically impossible.
        for (std::list<const char*>::iterator it = chls.begin(); it != chls.end(); ++it) {
            opr.opr().hangup(*it);

            callid_t callid = 0;

            if (!locate_call(*it, callid)) {
                WARNING_LOG("destroy session(%lu) failed locate call error.", id);
                return false;
            }

            remove_channelfromcall(id, callid, *it);
            destroy_channel(*it);
        }

        return true;
    } else {
        return remove_session(id);
    }
}

bool ims_session_manager_t::locate_sessionbyname(const char* channelname, ims::SessionIdT& id) {
    if (NULL == channelname) {
        WARNING_LOG("locate_sessionbyname(channelname=%s) failed(param error)", channelname);
        return false;
    }

    rw_lock_t lock(channel_table_lock);

    if (!lock.locked()) {
        WARNING_LOG("locate_sessionbyname(channelname=%s) failed(channel table lock error)", channelname);
        return false;
    }

    if (channelname_table.find(channelname) == channelname_table.end()) {
        WARNING_LOG("locate_sessionbyname(channelname=%s) failed(channel not exist)", channelname);
        return false;
    }

    id = channelname_table[channelname];
    TRACE_LOG("locate_sessionbyname(channelname=%s) success(sid=%lu)", channelname, id);

    return true;
}
bool ims_session_manager_t::locate_session(const char* channelid, ims::SessionIdT& id) {
    if (NULL == channelid) {
        WARNING_LOG("locate session(channelid=%s) failed(param error)", channelid);
        return false;
    }

    rw_lock_t lock(channel_table_lock);

    if (!lock.locked()) {
        WARNING_LOG("locate session(channelid=%s) failed(channel table lock error)", channelid);
        return false;
    }

    if (channel_table.find(channelid) == channel_table.end()) {
        WARNING_LOG("locate session(channelid=%s) failed(channel not exist)", channelid);
        return false;
    }

    id = channel_table[channelid];
    return true;
}

bool ims_session_manager_t::update_session_operation(ims::SessionIdT id,
        ims_session_operation_t operation,
        const char* opr) {

    lock_session("update_session_operation");
    session->cur_operation = operation;

    if (opr) {
        strncpy(session->cur_opr, opr, LEN_64);
    }

    return true;
}

bool ims_session_manager_t::get_session_operation(ims::SessionIdT id,
        ims_session_operation_t& operation, char* opr, uint32_t len) {

    operation = SOPR_UNKNOWN;

    lock_session("get_session_operation");
    operation = session->cur_operation;

    if (opr && len > 0) {
        strncpy(opr, session->cur_opr, len);
    }

    return true;
}

bool ims_session_manager_t::get_session_operator(ims::SessionIdT id, std::string& opr) {
    lock_session("get_session_operator");
    opr = session->cur_opr;
    return true;
}


bool ims_session_manager_t::add_event(ims::SessionIdT id, fs_event_t& event) {
    lock_session("add_event");
    event_handler_ptr handler(dynamic_cast<event_handler_t*>(session->thrd->get_runner().get()));
    handler->push_event(event);
    return true;
}

bool ims_session_manager_t::save_session_data(ims::SessionIdT id, const char* key,
        const char* val) {
    if (NULL == key || NULL == val || '\0' == key[0] || '\0' == val[0]) {
        WARNING_LOG("save session data (id=%lu,key=%s,val=%s) failed(param error)", id, key, val);
        return false;
    }

    lock_session("save_session_data");

    const char* key_ = ims_tool_t::strdup(key, session->pstring_pool);
    const char* val_ = ims_tool_t::strdup(val, session->pstring_pool);

    if (NULL == key_ || NULL == val_) {
        WARNING_LOG("save session data (id=%lu,newkey=%s,newval=%s)failed(insert hash error)"
                    , id, key_, val_);
        return false;
    }

    session->calldata[key_] = val_;

    NOTICE_LOG("save session data (id=%lu,key=%s,val=%s) success", id, key, val);
    return true;
}


bool ims_session_manager_t::get_session_data(ims::SessionIdT id, const char* key, char* val,
        uint32_t val_len) {
    if (NULL == key || (val && val_len < 2)) {
        WARNING_LOG("get_session_data(id=%lu,key=%s,val=%s,val_len=%u) failed(param error)", id, key, val,
                    val_len);
        return false;
    }

    lock_session("get_session_data");

    const char* sztmp = NULL;

    if (session->calldata.count(key) == 0) {
        WARNING_LOG("get_session_data(id=%lu,key=%s,val=%s,val_len=%u) failed(key not found)", id, key, val,
                    val_len);
        return false;
    }

    sztmp = session->calldata[key];

    if (val && val_len > 2 && sztmp) {
        strncpy(val, sztmp, val_len);
    }

    NOTICE_LOG("get_session_data(id=%lu,key=%s,val=%s) success", id, key, val);
    return true;
}

void ims_session_manager_t::clear_dead_session() {
    std::vector<ims::SessionIdT> dead_sids;
    {
        rw_lock_t lock(session_table_lock);

        if (!lock.locked()) {
            WARNING_LOG("clear dead session failed(session table lock error)");
            return;
        }

        for (std::map<ims::SessionIdT, ims_session_t*>::iterator it = session_table.begin();
                it != session_table.end(); ++it) {
            if (it->second) {
                ims_session_t* session = it->second;
                // only read, don't need guard session->mutex
                uint64_t duration = ims_tool_t::get_timestamp_ms() - session->create_time;

                if (session->channels.size() == 0 && duration > ims_global_data::MAX_EMPTY_SESSION_LIFETIME) {
                    dead_sids.push_back(it->first);
                } else if (duration > ims_global_data::MAX_SESSION_LIFETIME) {
                    dead_sids.push_back(it->first);
                }
            }
        }
    }
    TRACE_LOG("in clear_dead_session, dead_session.size() = %ld", dead_sids.size());

    // remove session; try push CancelRouteRequest event before remove
    for (std::vector<ims::SessionIdT>::iterator it = dead_sids.begin();
            it != dead_sids.end(); ++it) {
        ims_tool_t::push_cancel_route_event(*it);
        destroy_session(*it);
    }
}

bool ims_session_manager_t::create_channel(ims::SessionIdT id,
        const char* cid, const char* name,
        ims::CallStateT callstate, ims::MediaStateT mediastate) {

    if (NULL == cid || NULL == name) {
        WARNING_LOG("create_channel(sid=%lu,cid=%s,name=%s)failed(param error)", id, cid, name);
        return false;
    }

    ims_channel_t* channel = NULL;
    {
        lock_session("create_channel");
        lock_channel_table("create_channel", true);

        if (channel_table.count(cid) != 0) {
            WARNING_LOG("create_channel(sid=%lu,cid=%s,name=%s)failed(channelid error,alreay create)", id, cid,
                        name);
            return false;
        }

        //channel=session->pool.createp<ims_channel_t,const char*,const char*,
        //    ims::CallStateT,ims::MediaStateT>(name,cid,callstate,mediastate);
        channel = session->pims_channel_pool->construct(name, cid, callstate);

        if (!channel) {
            WARNING_LOG("create_channel(sid=%lu,cid=%s,name=%s)failed(memory error)", id, cid, name);
            return false;
        }

        channel->mediastate = mediastate;

        session->channels[channel->id] = channel;

        if (session->channels.count(channel->id) == 0) {
            WARNING_LOG("create_channel(sid=%lu,cid=%s,name=%s)failed(insert session hash)", id, cid, name);
            return false;
        }

        channel_table[channel->id] = id;

        if (channel_table.count(channel->id) == 0) {
            WARNING_LOG("create_channel(sid=%lu,cid=%s,name=%s)failed(insert channel hash)", id, cid, name);
            return false;
        }

        channelname_table[channel->name] = id;
    }

    return true;
}

bool ims_session_manager_t::destroy_channel(const char* channelid) {
    if (NULL == channelid) {
        WARNING_LOG("destroy_channel(cid=%s)failed(param error)", channelid);
        return false;
    }

    ims::SessionIdT id = 0;
    {
        lock_channel_table("destroy_channel", true);

        if (channel_table.count(channelid) == 0) {
            WARNING_LOG("destroy_channel(cid=%s)failed(invalid channelid)", channelid);
            return false;
        }

        id = channel_table.at(channelid);
        channel_table.erase(channelid);

        if (channel_table.count(channelid) != 0) {
            WARNING_LOG("!!!hashmap erase channelid(=%s) error", channelid);
            return false;
        }
    }

    {
        lock_session("destroy_channel");
        ims_channel_t* channel = session->channels.find(channelid)->second;

        if (!channel) {
            WARNING_LOG("destroy_channel(cid=%s,sid=%lu)failed(invalid channelid)",
                        channelid, id);
            return false;
        }

        session->channels.erase(channelid);

        lock_channel_table("destroy_channel", true);
        channelname_table.erase(channel->name);

        if (channelname_table.count(channel->name) != 0) {
            WARNING_LOG("!!!hashmap erase channename(=%s) error", channel->name);
            return false;
        }
    }

    if (get_channels_size(id) == 0) {
        remove_session(id);
        NOTICE_LOG("destroy_channel(cid=%s,sid=%lu) success,(no channels,destroy session)"
                   , channelid, id);
        return true;
    }

    NOTICE_LOG("destroy_channel(cid=%s,sid=%lu) success", channelid, id);
    return true;
}

bool ims_session_manager_t::locate_channel(ims::SessionIdT id, const char* channel_name,
        char* channelid, uint32_t channelid_len) {
    if (NULL == channel_name || '\0' == channel_name[0] || NULL == channelid || channelid_len < 2) {
        WARNING_LOG("locate_channel(sid=%lu,name=%s,len=%u)failed(invalid param)", id, channel_name,
                    channelid_len);
        return false;
    }

    lock_session("locate_channel");

    for (ims_session_t::map_str2chl_t::iterator it = session->channels.begin();
            it != session->channels.end(); ++it) {
        if (strcasecmp(channel_name, (it->second->name)) == 0) {
            strncpy(channelid, it->first, channelid_len);
            return true;
        }
    }

    WARNING_LOG("locate_channel(sid=%lu,name=%s)failed(invalid channelname)", id, channel_name);
    return false;
}


bool ims_session_manager_t::locate_otherchannel(ims::SessionIdT id, callid_t callid,
        const char* my_id, std::list<const char*>& other_ids) {
    other_ids.clear();

    if (!get_channelsbycall(id, callid, other_ids)) {
        WARNING_LOG("locate_otherchannel(sid=%lu,chlid=%s,callid=%lu)failed(get channels error)"
                    , id, my_id, callid);
        return false;
    }

    for (std::list<const char*>::iterator it = other_ids.begin(); it != other_ids.end(); ++it) {
        if (strcasecmp(*it, my_id) == 0) {
            other_ids.erase(it);
            break;
        }
    }

    return (other_ids.size() != 0);

}

bool ims_session_manager_t::locate_otherchannel(ims::SessionIdT id, const char* my_name,
        std::list<const char*>& other_ids,
        callid_t callid,
        char* my_id,
        uint32_t myid_len) {
    if (NULL == my_name || 0 == callid) {
        WARNING_LOG("locate_otherchannel(sid=%lu,name=%s,callid=%lu)failed(invalid param)"
                    , id, my_name, callid);
        return false;
    }

    char chlid[LEN_64] = {0};

    if (!locate_channel(id, my_name, chlid, LEN_64)) {
        WARNING_LOG("locate_otherchannel(sid=%lu,name=%s,callid=%lu)failed(locate channel error)"
                    , id, my_name, callid);
        return false;
    }

    std::list<callid_t> calls;

    if (!locate_call(chlid, calls) || calls.size() == 0) {
        WARNING_LOG("locate_otherchannel(sid=%lu,name=%s,callid=%lu)failed(locate call error)"
                    , id, my_name, callid);
        return false;
    }

    if (!get_channelsbycall(id, callid, other_ids)) {
        WARNING_LOG("locate_otherchannel(sid=%lu,name=%s,callid=%lu)failed(get channels error)"
                    , id, my_name, callid);
        return false;
    }

    for (std::list<const char*>::iterator it = other_ids.begin(); it != other_ids.end(); ++it) {
        if (strcasecmp(*it, chlid) == 0) {
            other_ids.erase(it);
            break;
        }
    }

    if (NULL != my_id) {
        strncpy(my_id, chlid, myid_len);
    }

    return true;
}

bool ims_session_manager_t::locate_callbyname(ims::SessionIdT id, const char* chlname,
        std::list<callid_t>& calls, char* self_id, uint32_t len) {
    if (NULL == chlname || 0 == id) {
        WARNING_LOG("locate_callbyname (sid=%lu,chlname=%s) failed invalid param)", id, chlname);
        return false;
    }

    char chlid[LEN_64] = {0};

    if (!locate_channel(id, chlname, chlid, LEN_64)) {
        WARNING_LOG("locate_callbyname (sid=%lu,chlname=%s) failed locate channel)", id, chlname);
        return false;
    }

    if (self_id && len > 0) {
        strncpy(self_id, chlid, len);
    }

    return locate_call(chlid, calls);
}

bool ims_session_manager_t::update_channel_call(const char* channelid, callid_t callid) {
    get_channel("update_channel_call", channelid, false);

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || NULL == cit->second) {
        WARNING_LOG("update_channel_call(cid=%s,sid=%lu,callid=%lu)failed(invalid callid)", channelid, id,
                    callid);
        return false;
    }

    pcall = cit->second;

    pcall->chls.push_back(channel->id);

    NOTICE_LOG("update_channel_call(cid=%s,sid=%lu,callid=%lu) success", channelid, id, callid);
    return true;

}
bool ims_session_manager_t::update_channel_callstate(const char* channelid, ims::CallStateT state) {
    get_channel("update_channel_callstate", channelid, false);
    channel->callstate = state;
    return true;
}
bool ims_session_manager_t::get_channel_callstate(const char* channelid, ims::CallStateT& state) {
    get_channel("get_channel_callstate", channelid, false);
    state = channel->callstate;
    return true;
}
bool ims_session_manager_t::get_channel_mediastate(const char* channelid, ims::MediaStateT& state) {
    get_channel("get_channel_mediastate", channelid, false);
    state = channel->mediastate;
    return true;
}

bool ims_session_manager_t::update_channel_mediastate(const char* channelid,
        ims::MediaStateT state) {
    get_channel("update_channel_mediastate", channelid, false);
    channel->mediastate = state;
    return true;
}

bool ims_session_manager_t::get_channelsbysession(ims::SessionIdT id,
        std::list<const char*>& chls) {
    chls.clear();
    lock_session("get_channelsbysession");

    for (ims_session_t::map_str2chl_t::iterator it = session->channels.begin();
            it != session->channels.end(); ++it) {
        chls.push_back(it->first);
    }

    return true;
}

bool ims_session_manager_t::get_channelsbycall(ims::SessionIdT id, callid_t callid,
        std::list<const char*>& chls) {
    chls.clear();
    lock_session("get_channelsbycall");
    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || NULL == cit->second) {
        WARNING_LOG("get_channelsbycall(call=%lu)failed(callid not exist)", callid);
        return false;
    }

    pcall = cit->second;

    chls = pcall->chls;

    return true;
}

bool ims_session_manager_t::create_call(ims::SessionIdT id, const char* channelid1,
                                        const char* channelid2, callid_t& callid) {
    ims::SessionIdT sid1 = 0, sid2 = 0;

    locate_session(channelid1, sid1)&& !locate_session(channelid2, sid2);
    locate_session(channelid1, sid1)&& !locate_session(channelid2, sid2);

    if (0 == sid1 && 0 == sid2) {
        WARNING_LOG("create_call(cid1=%s,cid2=%s)failed(both channel locate session error)",
                    channelid1, channelid2);
        return false;
    }

    if (sid1 != 0 && sid1 != id) {
        WARNING_LOG("create_call(cid1=%s,actualid=%lu,inputid=%lu)failed(not same session)",
                    channelid1, sid1, id);
        return false;
    }

    if (sid2 != 0 && sid2 != id) {
        WARNING_LOG("create_call(cid2=%s,catualid=%lu,inputid=%lu)failed(not same session)",
                    channelid2, sid2, id);
        return false;
    }

    lock_session("create_call");
    callid = ims_tool_t::get_timestamp_ms();

    ims_call_t* pcall = session->pims_call_pool->construct();

    if (pcall == NULL) {
        WARNING_LOG("create_call(cid1=%s,cid2=%s)failed(memory error)", channelid1, channelid2);
        return false;
    }

    if (sid1 != 0) {
        pcall->chls.push_back(ims_tool_t::strdup(channelid1, session->pstring_pool));
    }

    if (sid2 != 0) {
        pcall->chls.push_back(ims_tool_t::strdup(channelid2, session->pstring_pool));
    }

    session->calls[callid] = pcall;

    if (session->calls.count(callid) == 0) {
        WARNING_LOG("create_call(cid1=%s,cid2=%s)failed(insert hash error)", channelid1, channelid2);
        return false;
    }

    NOTICE_LOG("create_call(cid1=%s,cid2=%s,callid=%lu) success", channelid1, channelid2, callid);
    return true;
}
bool ims_session_manager_t::destroy_call(ims::SessionIdT id, callid_t callid) {
    lock_session("destroy_call");

    if (session->calls.erase(callid) != 1u) {
        WARNING_LOG("destroy_call(sid=%lu,callid=%lu)failed(invalid callid error)", id, callid);
        return false;
    }

    NOTICE_LOG("destroy_call(sid=%lu,callid=%lu) success", id, callid);
    return true;
}

bool ims_session_manager_t::locate_othercall(ims::SessionIdT id, callid_t callid,
        callid_t& other_callid) {
    lock_session("locate_othercall");

    for (std::map<callid_t, ims_call_t* >::iterator it = session->calls.begin();
            it != session->calls.end(); ++it) {
        if (it->first != callid) {
            other_callid = it->first;
            return true;
        }
    }

    return false;
}
bool ims_session_manager_t::locate_call(ims::SessionIdT id, std::list<callid_t>& calls) {
    calls.clear();
    lock_session("locate_call");

    for (std::map<callid_t, ims_call_t* >::iterator it = session->calls.begin();
            it != session->calls.end(); ++it) {
        calls.push_back(it->first);
    }

    return true;
}
bool ims_session_manager_t::locate_call(const char* channelid, callid_t& callid) {
    std::list<callid_t> calls;

    if (locate_call(channelid, calls)) {
        callid = calls.front();
        return true;
    }

    return false;
}
bool ims_session_manager_t::locate_call(const char* channelid, std::list<callid_t>& calls) {
    calls.clear();
    ims::SessionIdT id;

    if (locate_session(channelid, id)) {
        lock_session("locate_call");

        for (std::map<callid_t, ims_call_t* >::iterator it = session->calls.begin();
                it != session->calls.end(); ++it) {
            if (it->second) {
                std::list<const char*>& chls = it->second->chls;

                for (std::list<const char*>::iterator it_call = chls.begin();
                        it_call != chls.end(); ++it_call) {
                    if (strcasecmp(channelid, *it_call) == 0) {
                        calls.push_back(it->first);
                        break;
                    }
                }
            }
        }

        return calls.size() != 0;
    }

    WARNING_LOG("locate_call(cid=%s)failed(invalid channelid)", channelid);
    return false;
}

bool ims_session_manager_t::rt_add_dn(const char* dn, ims::DnTypeT type, ims::ReqIdT reqid) {
    if (NULL == dn || '\0' == dn[0]) {
        WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%ld)failed(invalid param)",
                    dn, type.get_desc().c_str(), reqid);
        return false;
    }

    rw_lock_t lock_req(runtime.req_mgr_lock, true);

    if (!lock_req.locked()) {
        WARNING_LOG("rt_add_dn(reqid=%lu)failed(lock reqmgr error)", reqid);
        return false;
    }

    req_info_t* reqinfo = NULL;

    if (runtime.req_mgr.count(reqid) == 0) {
        WARNING_LOG("rt_add_dn(reqid=%lu)failed(reqid not exist)", reqid);
        return false;
    }

    reqinfo = runtime.req_mgr.find(reqid)->second;
    char(*dn_copy)[global_data_t::DN_SIZE] = dn_pool.get();

    if (!dn_copy) {
        WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(memory error)",
                    dn, type.get_desc().c_str(), reqid);
        return false;
    }

    strncpy(*dn_copy, dn, global_data_t::DN_SIZE);

    if (type == ims::DnTypeT::AgentDn) {
        rw_lock_t lock(runtime.monitord_dn_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(lock error)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }

        if (runtime.monitord_dn.count(*dn_copy) != 0) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(dn already exist)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }

        runtime.monitord_dn[*dn_copy] = reqid;

        if (runtime.monitord_dn.count(*dn_copy) == 0) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(insert hash error)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }
    } else if (type == ims::DnTypeT::IvrANI) {
        rw_lock_t lock(runtime.monitord_accessno_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(lock error)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }

        if (runtime.monitord_accessno.count(*dn_copy) != 0) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(dn already exist)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }

        runtime.monitord_accessno[*dn_copy] = reqid;

        if (runtime.monitord_accessno.count(*dn_copy) == 0) {
            WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(insert hash error)",
                        dn, type.get_desc().c_str(), reqid);
            dn_pool.put(&dn_copy);
            return false;
        }
    } else {
        WARNING_LOG("rt_add_dn(dn=%s,type=%s,reqid=%lu)failed(invalid type)",
                    dn, type.get_desc().c_str(), reqid);
        dn_pool.put(&dn_copy);
        return false;
    }

    if (reqinfo) {
        if (type == ims::DnTypeT::IvrANI) {
            reqinfo->accessno[(const char*)(*dn_copy)] = dn_copy;
        } else if (type == ims::DnTypeT::AgentDn) {
            reqinfo->agent_dn[(const char*)(*dn_copy)] = dn_copy;
        }
    }

    return true;
}

bool ims_session_manager_t::rt_del_dn(const char* dn, ims::DnTypeT type) {
    if (NULL == dn) {
        WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(invalid param)",
                    dn, type.get_desc().c_str());
        return false;
    }

    ims::ReqIdT reqid = 0;

    char(*dn_copy)[global_data_t::DN_SIZE] = NULL;

    if (type == ims::DnTypeT::AgentDn) {
        rw_lock_t lock(runtime.monitord_dn_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(lock error)",
                        dn, type.get_desc().c_str());
            return false;
        }

        reqid = runtime.monitord_dn[dn];

        if (runtime.monitord_dn.erase(dn) != 1u) {
            WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(dn not exist)",
                        dn, type.get_desc().c_str());
            return false;
        }


    } else if (type == ims::DnTypeT::IvrANI) {
        rw_lock_t lock(runtime.monitord_accessno_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(lock error)",
                        dn, type.get_desc().c_str());
            return false;
        }

        reqid = runtime.monitord_accessno[dn];

        if (runtime.monitord_accessno.erase(dn) != 1u) {
            WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(dn not exist)",
                        dn, type.get_desc().c_str());
            return false;
        }
    } else {
        WARNING_LOG("rt_del_dn(dn=%s,type=%s)failed(invalid type)",
                    dn, type.get_desc().c_str());

        return false;
    }

    rw_lock_t lock(runtime.req_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_del_dn(reqid=%lu)failed(lock reqmgr error)", reqid);
        return false;
    }

    req_info_t* reqinfo = NULL;

    if (runtime.req_mgr.count(reqid) == 0) {
        WARNING_LOG("rt_del_dn(reqid=%lu)failed(reqid not exist)", reqid);
        return false;
    }

    reqinfo = runtime.req_mgr.find(reqid)->second;

    if (reqinfo) {
        if (type == ims::DnTypeT::IvrANI) {
            if (reqinfo->accessno.count(dn) != 0) {
                dn_copy = reqinfo->accessno[dn];
                reqinfo->accessno.erase(dn);
                //printf("erase dn success(%lu)\n",(unsigned long)(char*)dn_copy);
                TRACE_LOG("erase dn success(%lu)\n", (unsigned long)(char*)dn_copy);
            }
        } else if (type == ims::DnTypeT::AgentDn) {
            if (reqinfo->agent_dn.count(dn) != 0) {
                dn_copy = reqinfo->agent_dn[dn];
                reqinfo->agent_dn.erase(dn);
            }
        }
    }

    dn_pool.put(&dn_copy);

    return true;
}
bool ims_session_manager_t::rt_query_dn(const char* dn, ims::DnTypeT type, ims::ReqIdT* reqid) {
    if (NULL == dn) {
        WARNING_LOG("rt_query_dn(dn=%s,type=%s)failed(invalid param)",
                    dn, type.get_desc().c_str());
        return false;
    }

    if (type == ims::DnTypeT::AgentDn) {
        rw_lock_t lock(runtime.monitord_dn_lock);

        if (!lock.locked()) {
            WARNING_LOG("rt_query_dn(dn=%s,type=%s)failed(lock error)", dn,
                        type.get_desc().c_str());
            return false;
        }

        if (runtime.monitord_dn.find(dn) == runtime.monitord_dn.end()) {
            DEBUG_LOG("rt_query_dn(dn=%s,type=%s)failed(dn not exist)",
                      dn, type.get_desc().c_str());
            return false;
        }

        if (reqid != NULL) {
            *reqid = runtime.monitord_dn.at(dn);
        }
    } else if (type == ims::DnTypeT::IvrANI) {
        rw_lock_t lock(runtime.monitord_accessno_lock);

        if (!lock.locked()) {
            WARNING_LOG("rt_query_dn(dn=%s,type=%s)failed(lock error)",
                        dn, type.get_desc().c_str());
            return false;
        }

        if (runtime.monitord_accessno.count(dn) == 0) {
            DEBUG_LOG("rt_query_dn(dn=%s,type=%s)failed(dn not exist)",
                      dn, type.get_desc().c_str());
            return false;
        }

        if (reqid != NULL) {
            *reqid = runtime.monitord_accessno.at(dn);
        }
    } else {
        WARNING_LOG("rt_query_dn(dn=%s,type=%s)failed(invalid type)",
                    dn, type.get_desc().c_str());
        return false;
    }

    return true;
}


bool ims_session_manager_t::rt_add_req(ims::ReqIdT reqid, const std::string& conninfo) {
    if (conninfo.size() == 0) {
        WARNING_LOG("rt_add_req(reqid=%lu,conninfo=%s)failed(invalid param)", reqid, conninfo.c_str());
        return false;
    }

    ims::ReqIdT repeat_reqid = 0;
    {
        rw_lock_t lock(runtime.req_mgr_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_add_req(reqid=%lu)failed(lock error)", reqid);
            return false;
        }

        for (std::map<ims::ReqIdT, req_info_t*>::iterator it = runtime.req_mgr.begin();
                it != runtime.req_mgr.end(); ++it) {
            if (it->second && conninfo == it->second->conn_info) {
                repeat_reqid = it->first;
                break;
            }
        }
    }

    if (repeat_reqid) {
        WARNING_LOG("rt_add_req(reqid=%lu)warning(%s is already be callbacked by %lu) auto to unregister",
                    reqid, conninfo.c_str(), repeat_reqid);

        if (!rt_del_req(repeat_reqid)) {
            WARNING_LOG("auto unregister %lu failed", repeat_reqid);
            return false;
        }
    }

    req_info_t* reqinfo = NULL;
    {
        Guard<Mutex> lock(&runtime.mutex);

        if (lock.is_locked()) {

            reqinfo = runtime.pool.req_info_pool.construct();
            ims_thread_t* thrd = runtime.pool.ims_thread_obj_pool.construct(
                                     SharedPointer<Runnable>(new ims_request_t(reqid, conninfo)));

            if (NULL == thrd || NULL == reqinfo) {
                WARNING_LOG("rt_add_req(reqid=%lu)failed(memory error)", reqid);
                return false;
            }

            reqinfo->thread = thrd;
        } else {
            WARNING_LOG("rt_add_req(reqid=%lu)failed(lock runtime error)",
                        reqid);
            return false;
        }
    }

    rw_lock_t lock(runtime.req_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_add_req(reqid=%lu)failed(lock error)", reqid);
        return false;
    }

    if (runtime.req_mgr.count(reqid) != 0) {
        WARNING_LOG("rt_add_req(reqid=%lu,conninfo=%s)failed(reqid already exist)", reqid,
                    conninfo.c_str());
        return false;
    }

    //启动事件处理线程
    reqinfo->conn_info = conninfo;
    reqinfo->thread->start();
    runtime.req_mgr[reqid] = reqinfo;

    if (runtime.req_mgr.count(reqid) == 0) {
        WARNING_LOG("rt_add_req(reqid=%lu,conninfo=%s)failed(insert hash error)", reqid, conninfo.c_str());
        return false;
    }

    return true;
}

bool ims_session_manager_t::rt_query_req(ims::ReqIdT reqid) {

    rw_lock_t lock(runtime.req_mgr_lock, false);

    if (!lock.locked()) {
        WARNING_LOG("rt_query_req(reqid=%lu)failed(lock error)", reqid);
        return false;
    }

    if (runtime.req_mgr.count(reqid) == 0) {
        return false;
    }

    return true;
}

bool ims_session_manager_t::rt_del_req(ims::ReqIdT reqid) {
    req_info_t* reqinfo = NULL;
    {
        rw_lock_t lock(runtime.req_mgr_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_del_req(reqid=%lu)failed(lock error)", reqid);
            return false;
        }

        if (runtime.req_mgr.count(reqid) == 0) {
            WARNING_LOG("rt_del_req(reqid=%lu)failed(reqid not exist)", reqid);
            return false;
        }

        reqinfo = runtime.req_mgr.find(reqid)->second;
    }

    if (reqinfo && reqinfo->thread) {
        if (reqinfo->thread) {
            ims_request_t* req = dynamic_cast<ims_request_t*>(reqinfo->thread->get_runner().get());

            if (req) {
                req->stop(); //thread is detached mode, don't need to join
            }
        }

        for (string_map::iterator it = reqinfo->agent_dn.begin(); it != reqinfo->agent_dn.end(); ++it) {
            rt_del_dn(it->first, ims::DnTypeT::AgentDn);
        }

        for (string_map::iterator it = reqinfo->accessno.begin(); it != reqinfo->accessno.end(); ++it) {
            rt_del_dn(it->first, ims::DnTypeT::IvrANI);
        }

        //destroy hashmap to release memory
        reqinfo->agent_dn.clear();
        reqinfo->accessno.clear();
    }

    //delete ims_route_info
    for (std::map<ims::RouteRequestIDT, ims_route_info_t>::iterator it = runtime.route_mgr.begin();
            it != runtime.route_mgr.end(); ++it) {
        if (reqid == it->second.reqid || reqid == it->second.dest_reqid) {
            rt_del_route(it->first);
        }
    }

    TRACE_LOG("delete reqid[%ld] related ims_route_info.", reqid);

    {
        rw_lock_t lock(runtime.req_mgr_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_del_req(reqid=%lu)failed(lock error)", reqid);
            return false;
        }

        if (runtime.req_mgr.erase(reqid) != 1u) {
            WARNING_LOG("rt_del_req(reqid=%lu)failed(reqid not exist)", reqid);
            return false;
        }
    }

    return true;
}

bool ims_session_manager_t::rt_update_reqstate(ims::ReqIdT reqid, const std::string& info) {
    {
        rw_lock_t lock(runtime.req_mgr_lock);

        if (!lock.locked()) {
            WARNING_LOG("rt_update_reqstate(reqid=%lu, info=%s)failed(lock error)"
                        , reqid, info.c_str());
            return false;
        }

        req_info_t* reqinfo = NULL;
        std::map<ims::ReqIdT, req_info_t*>::const_iterator cit = runtime.req_mgr.find(reqid);

        if (cit == runtime.req_mgr.end() || NULL == cit->second) {
            WARNING_LOG("get request (id=%lu) failed(request not exist)", reqid);
            return false;
        }

        reqinfo = cit->second;

        if (("master" == info && reqinfo->is_master) || ("slave" == info && !reqinfo->is_master)) {
            //TRACE_LOG("rt_update_reqstate as %s done, with no change", info.c_str());
            return true;
        }
    }

    {
        rw_lock_t lock(runtime.req_mgr_lock, true);

        if (!lock.locked()) {
            WARNING_LOG("rt_update_reqstate(reqid=%lu, info=%s)failed(lock error)"
                        , reqid, info.c_str());
            return false;
        }

        req_info_t* reqinfo = NULL;
        std::map<ims::ReqIdT, req_info_t*>::const_iterator cit = runtime.req_mgr.find(reqid);

        if (cit == runtime.req_mgr.end() || NULL == cit->second) {
            WARNING_LOG("get request (id=%lu) failed(request not exist)", reqid);
            return false;
        }

        reqinfo = cit->second;

        if ("master" == info) {
            reqinfo->is_master = true;
            TRACE_LOG("rt_update_reqstate(reqid=%lu) update as master done!", reqid);
        } else if ("slave" == info) {
            reqinfo->is_master = false;
            TRACE_LOG("rt_update_reqstate(reqid=%lu) update as slave done!", reqid);
        } else {
            WARNING_LOG("rt_update_reqstate(reqid=%lu), info(%s) is invalid.", reqid, info.c_str());
            return false;
        }
    }
    return true;
}

bool ims_session_manager_t::rt_query_register_service(ims::ServiceTypeT type, ims::ReqIdT& reqid) {
    rw_lock_t lock(runtime.req_mgr_lock);

    if (!lock.locked()) {
        WARNING_LOG("rt_query_register_service(servicetype=%s)failed(lock error)"
                    , type.get_desc().c_str());
        return false;
    }

    if (ims::ServiceTypeT::ServiceACD != type.get_value()) {
        WARNING_LOG("rt_query_register_service(servicetype=%s)failed(not support servicetype.)",
                    type.get_desc().c_str());
        return false;
    }

    for (std::map<ims::ReqIdT, req_info_t*>::iterator it = runtime.req_mgr.begin();
            it != runtime.req_mgr.end(); ++it) {
        if (it->second) {
            if ((it->first >> 56) == type.get_value() && it->second->is_master) {
                reqid = it->first;
                return true;
            }
        }
    }

    WARNING_LOG("rt_query_register_service(servicetype=%s)failed(no suitable service)",
                type.get_desc().c_str());

    return false;

}

bool ims_session_manager_t::add_imsevent_media(ims::SessionIdT id, ims::MediaEventT& event) {
    ims::ReqIdT reqid = 0;
    ims_request_t* req = NULL;

    std::string monitor_dn = ims_tool_t::get_assigned_caller(event.device, event.device);

    if (rt_query_dn(monitor_dn.c_str(), ims::DnTypeT::AgentDn , &reqid)
            && NULL != (req = get_request(reqid))) {
        return req->add_mediaevent(event);
    } else {
        WARNING_LOG("add_imsevent_media(sid=%lu,event=%s,device=%s)failed(can't locate request)",
                    id, event.eventType.get_desc().c_str(), event.device.c_str());
        return false;
    }
}
bool ims_session_manager_t::add_imsevent_call(ims::SessionIdT id, ims::CallEventT& event) {
    ims::ReqIdT reqid = 0;
    ims_request_t* req = NULL;

    std::string monitor_dn = ims_tool_t::get_assigned_caller(event.device, event.device);

    if (rt_query_dn(monitor_dn.c_str(), ims::DnTypeT::AgentDn , &reqid)
            && NULL != (req = get_request(reqid))) {
        return req->add_callevent(event);
    } else {
        WARNING_LOG("add_imsevent_call(sid=%lu,event=%s,device=%s)failed(can't locate request)",
                    id, event.eventType.get_desc().c_str(), event.device.c_str());

        return false;
    }
}
bool ims_session_manager_t::add_imsevent_other(ims::SessionIdT id, ims::OtherEventT& event) {
    ims::ReqIdT reqid = 0;
    ims_request_t* req = NULL;

    if (event.eventType == ims::OtherEventTypeT::OG_SessionCreate) {
        if (rt_query_dn(event.device.c_str(), ims::DnTypeT::IvrANI , &reqid)
                && NULL != (req = get_request(reqid))) {
            return req->add_otherevent(event);
        } else {
            WARNING_LOG("add_imsevent_other(sid=%lu,event=%s,device=%s)failed(can't locate request)",
                        id, event.eventType.get_desc().c_str(), event.device.c_str());
            return false;
        }
    } else if (event.eventType == ims::OtherEventTypeT::OG_OperationFailed) {
        if (rt_query_dn(ims_tool_t::get_assigned_caller(event.device, event.device).c_str(),
                        ims::DnTypeT::AgentDn, &reqid)
                && NULL != (req = get_request(reqid))) {
            return req->add_otherevent(event);
        } else {
            WARNING_LOG("add_imsevent_other(sid=%lu,event=%s,device=%s)failed(can't locate request)",
                        id, event.eventType.get_desc().c_str(), event.device.c_str());
            return false;
        }
    }

    WARNING_LOG("add_imsevent_other(sid=%lu,event=%s,device=%s)failed(unknown event)",
                id, event.eventType.get_desc().c_str(), event.device.c_str());
    return false;
}

bool ims_session_manager_t::rt_add_imsevent_route(ims::ReqIdT id, ims::RouteEventT& event) {

    ims_request_t* req = get_request(id);

    if (NULL == req) {
        WARNING_LOG("rt_add_imsevent_route reqid=%lu) failed(request not exist)", id);
        return false;
    }

    return req->add_routeevent(event);
}


bool ims_session_manager_t::rt_add_route(ims::RouteRequestIDT id, const ims_route_info_t& info) {
    rw_lock_t lock(runtime.route_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_add_route(requestId=%ld,reqid=%ld) failed(route table lock error)", id, info.reqid);
        return false;
    }

    if (runtime.route_mgr.count(id) != 0) {
        WARNING_LOG("rt_add_route(requestId=%ld,reqid=%ld) failed(requestid exist.)", id, info.reqid);
        return false;
    }

    runtime.route_mgr[id] = info;

    if (runtime.route_mgr.count(id) == 0) {
        WARNING_LOG("rt_add_route(requestId=%ld,reqid=%ld) failed(insert hash)", id, info.reqid);
        return false;
    }

    runtime.sessionId2requestId[info.sessionid] = id;

    if (runtime.sessionId2requestId.count(info.sessionid) == 0) {
        WARNING_LOG("rt_add_route(requestId=%ld,reqid=%ld) failed(insert hash)", id, info.reqid);
        return false;
    }

    TRACE_LOG("rt_add_route(requestId=%ld,reqid=%ld) success", id, info.reqid);
    return true;
}

bool ims_session_manager_t::rt_update_route(ims::RouteRequestIDT id, const ims_route_info_t& info) {
    rw_lock_t lock(runtime.route_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_update_route(requestId=%ld,reqid=%ld) failed(route table lockerror)", id,
                    info.reqid);
        return false;
    }

    if (runtime.route_mgr.count(id) == 0) {
        WARNING_LOG("rt_update_route(requestId=%ld) failed(requestid not exist.)", id);
        return false;
    }

    runtime.route_mgr.erase(id);

    if (runtime.route_mgr.count(id) != 0) {
        WARNING_LOG("rt_update_route(requestId=%ld) failed(hash del error)", id);
        return false;
    }

    runtime.route_mgr[id] = info;

    if (runtime.route_mgr.count(id) == 0) {
        WARNING_LOG("rt_update_route(routeid=%lu,reqid=%lu) failed(insert hash)", id, info.reqid);
        return false;
    }

    NOTICE_LOG("rt_update_route(routeid=%lu,reqid=%lu) success", id, info.reqid);
    return true;
}

bool ims_session_manager_t::rt_query_route(ims::RouteRequestIDT id, ims_route_info_t& info,
        bool del) {
    rw_lock_t lock(runtime.route_mgr_lock, del);

    if (!lock.locked()) {
        WARNING_LOG("rt_query_route(routeid=%lu) failed(route table lock error)", id);
        return false;
    }

    if (runtime.route_mgr.count(id) == 0) {
        WARNING_LOG("rt_query_route(routeid=%lu) failed(routeid not exist)", id);
        return false;
    }

    info = runtime.route_mgr[id];

    if (del) {
        runtime.route_mgr.erase(id);
    }

    return true;
}

bool ims_session_manager_t::rt_query_session_route(ims::SessionIdT id, ims_route_info_t& info,
        bool del) {
    rw_lock_t lock(runtime.route_mgr_lock, del);

    if (!lock.locked()) {
        WARNING_LOG("rt_query_session_route(sessionid=%ld) failed(route table lock error)", id);
        return false;
    }

    ims::RouteRequestIDT requestId = 0;

    if (runtime.sessionId2requestId.count(id) == 0) {
        WARNING_LOG("rt_query_session_route(routeid=%ld) failed(sessionid not exist)", id);
        return false;
    }

    requestId = runtime.sessionId2requestId[id];

    if (runtime.route_mgr.count(requestId) == 0) {
        WARNING_LOG("rt_query_session_route(requestid=%ld) failed(requestid not exist)", requestId);
        return false;
    }

    info = runtime.route_mgr[requestId];

    if (del) {
        runtime.route_mgr.erase(id);
    }

    TRACE_LOG("rt_query_session_route success.");
    return true;
}

bool ims_session_manager_t::rt_del_route(ims::RouteRequestIDT id) {
    rw_lock_t lock(runtime.route_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_del_route(requestId=%ld) failed(route table lock error)", id);
        return false;
    }

    ims_route_info_t route_info;

    if (runtime.route_mgr.count(id) == 0) {
        WARNING_LOG("rt_del_route(requestId=%ld) failed(requestId not exist)", id);
        return false;
    }

    route_info = runtime.route_mgr[id];

    if (runtime.route_mgr.erase(id) != 1u ||
            runtime.sessionId2requestId.erase(route_info.sessionid) != 1u) {
        WARNING_LOG("rt_del_route(requestId=%ld) failed(hash erase error)", id);
        return false;
    }

    return true;
}

bool ims_session_manager_t::rt_del_session_route(ims::SessionIdT id) {
    rw_lock_t lock(runtime.route_mgr_lock, true);

    if (!lock.locked()) {
        WARNING_LOG("rt_del_session_route(sessionid=%ld) failed(route table lock error)", id);
        return false;
    }

    ims::RouteRequestIDT requestId = 0;

    if (runtime.sessionId2requestId.count(id) != 0) {
        requestId = runtime.sessionId2requestId[id];

        if (runtime.route_mgr.erase(requestId) == 1u
                && runtime.sessionId2requestId.erase(id) == 1u) {
            return true;
        } else {
            WARNING_LOG("rt_del_session_route(sessionid=%ld) failed(route table delete error)", id);
            return false;
        }
    }

    return false;
}
int32_t ims_session_manager_t::get_channels_size(ims::SessionIdT id) {
    lock_session("get_channels_size");
    return session->channels.size();
}
bool ims_session_manager_t::get_callercalled(
    ims::SessionIdT id, std::string& first_dn, std::string& second_dn) {
    lock_session("get_callercalled");

    first_dn = session->oricaller;
    second_dn = session->oricalled;

    return true;
}

bool ims_session_manager_t::set_callercalled(ims::SessionIdT id, const std::string& fist_dn,
        const std::string& second_dn) {
    lock_session("get_callercalled");

    if (fist_dn.size() != 0) {
        strncpy(session->oricaller, fist_dn.c_str(), LEN_64);
    }

    if (second_dn.size() != 0) {
        strncpy(session->oricalled, second_dn.c_str(), LEN_64);
    }

    return true;
}
bool ims_session_manager_t::locate_lastchannel(ims::SessionIdT id, std::string& chl_name) {
    lock_session("locate_lastchannel");
    uint64_t max = 0;
    std::string tmp = "";

    for (ims_session_t::map_str2chl_t::iterator it = (session->channels).begin();
            it != (session->channels).end(); ++it) {
        if (it->second && it->second->create_time > max) {
            max = it->second->create_time;
            tmp = it->second->name;
        }
    }

    if (0 != max) {
        chl_name = tmp;
        return true;
    } else {
        return false;
    }
}

bool ims_session_manager_t::get_channelnamebyid(ims::SessionIdT id, const char* chlid,
        std::string& name) {

    if (NULL == chlid) {
        WARNING_LOG("get_channelnamebyid failed(sid=%lu,chlid is null)", id);
        return false;
    }

    lock_session("get_channelnamebyid");
    ims_channel_t* channel = session->channels[chlid];

    if (!channel) {
        WARNING_LOG("get_channelnamebyid(sid=%lu,cid=%s)failed(invalid channelid)", id, chlid);
        return false;
    }

    name = channel->name;

    return true;
}

bool ims_session_manager_t::remove_channelfromcall(ims::SessionIdT id, callid_t callid,
        const char* chlid) {
    lock_session("remove_channelfromcall");
    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (NULL == chlid
            || cit == session->calls.end()
            || NULL == cit->second
            || cit->second->chls.size() == 0) {
        WARNING_LOG("remove_channelfromcall(sid=%lu,callid=%lu,cid=%s)failed"
                    "(invalid callid or channelid)", id, callid, chlid);
        return false;
    }

    pcall = cit->second;

    std::list<const char*>& chls = pcall->chls;

    for (std::list<const char*>::iterator it = chls.begin(); it != chls.end(); ++it) {
        if (strcasecmp(*it, chlid) == 0) {
            chls.erase(it);

            if (chls.size() == 0) {
                session->calls.erase(callid);
                NOTICE_LOG("remove_channelfromcall(sid=%lu,call=%lu,cid=%s)"
                           "(no channel in call,destroy call)", id, callid, chlid);
            } else {
                NOTICE_LOG("remove_channelfromcall(sid=%lu,call=%lu,cid=%s)", id, callid, chlid);
            }

            return true;
        }
    }

    WARNING_LOG("remove_channelfromcall(sid=%lu,callid=%lu,cid=%s)failed(invalid chlid)",
                id, callid, chlid);
    return false;
}


bool ims_session_manager_t::update_call_ani(ims::SessionIdT id, callid_t callid, const char* ani) {
    if (NULL == ani || '\0' == ani[0]) {
        return false;
    }

    lock_session("update_call_ani");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("update_call_ani(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return false;
    }

    pcall = cit->second;

    strncpy(pcall->ani, ani, LEN_32);
    TRACE_LOG("update call ani success(sid=%lu,callid=%lu,ani=%s)", id, callid, ani);

    return true;
}
bool ims_session_manager_t::update_call_dnis(ims::SessionIdT id, callid_t callid,
        const char* dnis) {
    if (NULL == dnis || '\0' == dnis[0]) {
        return false;
    }

    lock_session("update_call_dnis");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("update_call_dnis(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return false;
    }

    pcall = cit->second;

    strncpy(pcall->dnis, dnis, LEN_32);
    TRACE_LOG("update call dnis success(sid=%lu,callid=%lu,dnis=%s)", id, callid, dnis);


    return true;
}
bool ims_session_manager_t::get_call_info(ims::SessionIdT id, callid_t callid,
        std::string& ani, std::string& dnis) {
    lock_session("get_call_info");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("update_call_dnis(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return false;
    }

    pcall = cit->second;

    ani = pcall->ani;
    dnis = pcall->dnis;

    return true;
}

bool ims_session_manager_t::update_call_internal(ims::SessionIdT id, callid_t callid,
        bool internal) {
    lock_session("update_call_internal");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("update_call_internal(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return false;
    }

    pcall = cit->second;

    pcall->internal = internal;

    return true;
}

bool ims_session_manager_t::is_dead_call(ims::SessionIdT id, callid_t callid) {
    lock_session("is_dead_call");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        TRACE_LOG("is_dead_call(sid=%lu,callid=%lu)(invalid callid)", id, callid);
        return true;
    }

    pcall = cit->second;

    for (std::list<const char*>::iterator it = pcall->chls.begin(); it != pcall->chls.end(); ++it) {
        ims_channel_t* channel = session->channels[*it];

        if (NULL != channel && channel->callstate != ims::CallStateT::SG_IdleState) {
            TRACE_LOG("%s is not idle(%s)", *it, channel->callstate.get_desc().c_str());
            return false;
        }
    }

    TRACE_LOG("all channel in session %ld call %ld is idle", id, callid);

    return true;
}

bool ims_session_manager_t::is_internal_call(ims::SessionIdT id, callid_t callid) {
    lock_session("is_internal_call");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("is_internal_call(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return false;
    }

    pcall = cit->second;

    return pcall->internal;
}

uint32_t ims_session_manager_t::get_call_size(ims::SessionIdT id, callid_t callid) {
    lock_session("get_call_size");

    ims_call_t* pcall = NULL;
    std::map<callid_t, ims_call_t*>::const_iterator cit = session->calls.find(callid);

    if (cit == session->calls.end() || cit->second == NULL) {
        WARNING_LOG("get_call_size(sid=%lu,callid=%lu)failed(invalid callid)", id, callid);
        return 0;
    }

    pcall = cit->second;
    return pcall->chls.size();

}

bool ims_session_manager_t::update_create_reason(ims::SessionIdT id,
        ims_session_create_reason_t reason) {
    lock_session("update_create_reason");
    session->create_reason = reason;
    return true;
}

bool ims_session_manager_t::is_inbound_session(ims::SessionIdT id) {
    lock_session("is_inbound_session");

    return (SCRT_INBOUND_IVR == session->create_reason
            || SCRT_INBOUND_NORMAL == session->create_reason);
}

bool ims_session_manager_t::is_IVRinbound_session(ims::SessionIdT id) {
    lock_session("is_IVRinbound_session");

    return  SCRT_INBOUND_IVR == session->create_reason;
}

bool ims_session_manager_t::is_IVRoutbound_session(ims::SessionIdT id) {
    lock_session("is_IVRoutbound_session");

    return  SCRT_OUTBOUND_IVR == session->create_reason;
}

bool ims_session_manager_t::is_valid_request(ims::SessionIdT id) {
    rw_lock_t lock(runtime.route_mgr_lock);

    if (!lock.locked()) {
        WARNING_LOG("is_repeat_request(sid=%ld) failed(route table lock error)", id);
        return false;
    }

    if (runtime.sessionId2requestId.count(id) != 0) {
        WARNING_LOG("is_repeat_request(sid=%ld) failed(exist route request)", id);
        return false;
    }

    return true;
}
bool ims_session_manager_t::find_other_hangup(ims::SessionIdT id, callid_t callid,
        const char* self_chlid) {

    std::list<const char*> chls;

    if (get_channelsbycall(id, callid, chls)) {
        uint32_t fsno = ims_tool_t::get_fsno(id);
        fs_tool_t opr(fsno);

        if (!opr.valid()) {
            WARNING_LOG("[0x%lx] find_other_hangup failed(fetch opr err)", id);
            return false;
        }

        for (std::list<const char*>::iterator it = chls.begin(); it != chls.end(); ++it) {
            if (strcasecmp(*it, self_chlid) == 0) {
                continue;
            }

            if (opr.opr().hangup(*it) != IMS_SUCCESS) {
                WARNING_LOG("[0x%lx] find_other_hangup(hangup other [%s] error)", id, *it);
            }
        }
    } else {
        TRACE_LOG("find_other_hangup failed(find channels in call %lu failed)", callid);
        return false;
    }

    return true;
}

bool ims_session_manager_t::add_rundata(ims::SessionIdT id, const char* key, const char* val) {

    if (NULL == key || NULL == val || '\0' == key[0] || '\0' == val[0]) {
        WARNING_LOG("add rundata (id=%lu,key=%s,val=%s) failed(param error)", id, key, val);
        return false;
    }

    lock_session("add_rundata");

    const char* key_ = ims_tool_t::strdup(key, session->pstring_pool);
    const char* val_ = ims_tool_t::strdup(val, session->pstring_pool);

    if (session->self_rundata.count(key_) != 0) {
        WARNING_LOG("add_rundata (id=%lu,newkey=%s,newval=%s)failed(key already exist)"
                    , id, key_, val_);
        return false;
    }

    if (NULL == key_ || NULL == val_) {
        WARNING_LOG("add_rundata (id=%lu,newkey=%s,newval=%s)failed(insert hash error)"
                    , id, key_, val_);
        return false;
    }

    session->self_rundata[key_] = val_;

    return true;
}

bool ims_session_manager_t::get_rundata(ims::SessionIdT id, const char* key, char* val,
                                        uint32_t val_len) {

    if (NULL == key || '\0' == key[0]) {
        WARNING_LOG("get_rundata (id=%lu,key=%s,val=%s) failed(param error)", id, key, val);
        return false;
    }

    lock_session("get_rundata");

    const char* sztmp = NULL;

    if (session->self_rundata.count(key) == 0) {
        WARNING_LOG("get_rundata (id=%lu,key=%s)failed(fetch hash error)", id, key);
        return false;
    }

    sztmp = session->self_rundata.find(key)->second;

    if (val && val_len > 2 && sztmp) {
        strncpy(val, sztmp, val_len);
    }

    return true;
}

bool ims_session_manager_t::on_fw_disconn(uint32_t fw_no, std::vector<ims::SessionIdT>& ids) {
    rw_lock_t lock_table(session_table_lock);

    if (!lock_table.locked()) {
        WARNING_LOG("on_fw_disconn (fw_no=%u) failed(session table lock error)", fw_no);
        return false;
    }

    ids.clear();

    for (std::map<ims::SessionIdT, ims_session_t*>::iterator it = session_table.begin();
            it != session_table.end(); ++it) {
        if (it->second && fw_no == it->second->fs_no) {
            ids.push_back(it->first);
        }
    }

    return true;
}

uint32_t ims_session_manager_t::get_monitord_dn_size() {
    rw_lock_t lock(runtime.monitord_dn_lock);

    if (!lock.locked()) {
        WARNING_LOG("get monitord dn size failed(lock error)");
        return 0;
    }

    return runtime.monitord_dn.size();
}

bool ims_session_manager_t::del_rundata(ims::SessionIdT id, const char* key) {

    if (NULL == key || '\0' == key[0]) {
        WARNING_LOG("del_rundata (id=%lu,key=%s) failed(param error)", id, key);
        return false;
    }

    lock_session("get_rundata");

    if (session->self_rundata.count(key) == 0) {
        WARNING_LOG("del_rundata (id=%lu,key=%s)failed(fetch hash error)", id, key);
        return false;
    }

    session->self_rundata.erase(key);
    return true;
}

bool ims_session_manager_t::add_event(ims::SessionIdT id, const char* event) {
    //理论上来说，调用此函数的时候，已经不从对应的FW获取相关事件，因此，不会修改此FW对饮的CHANNEL_TABLE
    //因此，以下对channel table的处理，都没有进行加锁
    if (!event || (strncmp("CHANNEL_HANGUP", event, 14) && strncmp("CHANNEL_DESTROY", event, 15))) {
        WARNING_LOG("add_event(sid=%lu,event=%s) failed(event not accepted)", id, event);
        return false;
    }

    lock_session("add_event");

    fs_event_t evt;
    bzero(&evt, sizeof(evt));

    evt.timestamp = ims_tool_t::get_timestamp_ms();
    strncpy(evt.name, event, LEN_64);
    evt.sessionid = id;
    evt.datatype = EDT_NORMAL;

    event_data_normal_t& data = evt.event_data.normal;
    event_handler_ptr handler(dynamic_cast<event_handler_t*>(session->thrd->get_runner().get()));

    for (ims_session_t::map_str2chl_t::iterator it = session->channels.begin();
            it != session->channels.end(); ++it) {

        for (std::map<callid_t, ims_call_t* >::iterator it_call = session->calls.begin();
                it_call != session->calls.end(); ++it_call) {
            if (it_call->second) {
                std::list<const char*>& chls = it_call->second->chls;

                for (std::list<const char*>::iterator it_chl = chls.begin();
                        it_chl != chls.end(); ++it_chl) {
                    if (strcasecmp(it->first, *it_chl) == 0) {
                        evt.callid = (it_call->first);
                        break;
                    }
                }
            }

            if (evt.callid) {
                break;
            }
        }

        if (!(it->second)) {
            continue;
        }

        std::string tmp = ims_tool_t::chlname2no(it->second->name);
        strncpy(data.deviceno, tmp.c_str(), LEN_64);
        strncpy(data.uuid, it->first, LEN_64);
        strncpy(data.channel_name, it->second->name, LEN_64);

        data.call_direction = ((SCRT_OUTBOUND_NORMAL == session->create_reason
                                || SCRT_OUTBOUND_IVR == session->create_reason)
                               ? FCD_OUTBOUND : FCD_INBOUND);
        strncpy(data.reason, "GATEWAY_DISCONN", LEN_128);

        session->cur_operation = SOPR_MAKECALL;
        handler->push_event(evt);

        std::ostringstream ostm;
        ostm << std::endl;
        ostm << "========================FS EVENT(manual)=========================" << std::endl;
        ostm << "Time          : " << evt.timestamp << std::endl;
        ostm << "SessionID     : " << evt.sessionid << std::endl;
        ostm << "IMSDATA       : " << data.ims_data << std::endl;
        ostm << "Name          : " << evt.name << std::endl;
        ostm << "Type          : Normal" << std::endl;
        ostm << "Uuid          : " << data.uuid << std::endl;;
        ostm << "CallerNo      : " << data.caller_no << std::endl;;
        ostm << "CalledNo      : " << data.called_no << std::endl;
        ostm << "ChannelName   : " << data.channel_name << std::endl;
        ostm << "Direction     : " << data.call_direction << std::endl;
        ostm << "CallState     : " << data.call_state << std::endl;
        ostm << "Reason        : " << data.reason << std::endl;
        ostm << "============================End Event============================" << std::endl;
        BGCC_TRACE("fsevent", "%s", ostm.str().c_str());

        TRACE_LOG("manual add %s to sid:%lu,callid:%lu,chlid:%s,chlname:%s",
                  event, id, evt.callid, it->first, it->second->name);

        break;
    }

    return true;
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
