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

#ifndef _IVR_IMS_MGR_H_
#define _IVR_IMS_MGR_H_

#include "ims_struct.h"
#include "ims_info.h"
#include <common.h>

class ims_mgr_t {
    typedef std::map<uint32_t, ims_info> ims_map;
    typedef bgcc::Mutex mutex_t;
private:
    ims_mgr_t();
    ~ims_mgr_t();
public:
    // singleton object
    static ims_mgr_t* get_instance();

public:
    // add a new ims, if existed an ims with same imsno, will update ims info
    int32_t add_ims(const ims_info_t& ims);

    // remove the ims from map
    int32_t del_ims(uint32_t ims_no);

    // set main ims no
    int32_t set_default_ims(uint32_t imsno);

    // get main ims no
    uint32_t get_default_ims() const;

    // set next ims as main ims
    int32_t switch_default_ims();

    // get callback service
    bgcc::ServiceManager* getCallbackService();
public:
    // ims operations (using main ims)

    // create_session
    int32_t create_session(const std::string& callsource, const std::string& channel_id,
                           const std::string& channel_name,
                           const std::string& oricalled, ims_session_id_t& imssid, uint32_t& imsno);

    // route request: request agent
    int32_t route_request(uint32_t imsno, ims_session_id_t imssid, ims_routerequest_id_t& requestid,
                          ims_servicetype_t destService,
                          int32_t timeout, int32_t valid_time, ims_routerequest_type_t reqType, const std::string& reqArgs,
                          int32_t level, const std::string& caller_uri, const std::string& callee_uri,
                          const std::string& buffer);

    // cancel request agent
    int32_t cancel_route_request(uint32_t imsno, ims_session_id_t imssid,
                                 ims_routerequest_id_t requestId);

    // trans agent
    int32_t trans_agent(uint32_t imsno, ims_session_id_t sessionid, ims_routerequest_id_t requestid,
                        ims_transtype_t transType);

    // set associate data
    int32_t set_associatedata(uint32_t imsno, ims_session_id_t sessionid, const string& key,
                              const string& value);

    // get associate data of given key
    int32_t get_associatedata(uint32_t imsno, ims_session_id_t sessionid, const string& key,
                              string& value);

    int32_t makecall(uint32_t imsno, const std::string& caller, const std::string& callee,
                     const std::string& showani,
                     const std::string& showdest, int32_t timeout, int32_t callmode, ims_session_id_t& imssid);
protected:
    // if _default_ims == imsno, switch to next ims
    // else some one have switch it, do nothing
    int32_t _switch_default_ims(uint32_t imsno);
private:
    bool is_ims_valid() const;

    // switch to next ims, make sure _imsinfo.size() != 0
    void _switch_default_ims();

    // using given imsno, return matched ims
    int32_t _get_ims(uint32_t imsno, ims_info& ims);

    // check ims call result, if ok, return IVR_SUCCESS
    int32_t _check_result(ims_ccresult_t retcode, int32_t proxy_code, const std::string& info);
public:
    // binding ims_sessiond_id and ivr_session_id
    void bind_session_id(ims_session_id_t imssid, ivr_session_id_t ivrsid);

    void unbind_session_id(ivr_session_id_t ivrsid);

    bool get_map_session_id(ims_session_id_t imssid, ivr_session_id_t& ivrsid);
public:
    // swap
    //void swap(ims_map& other_imsinfo);
protected:
    ims_map _imsinfo;
    uint32_t _default_ims;
    mutex_t _info_mutex;

    std::map<ims_session_id_t, ivr_session_id_t> _session_map;
    bgcc::ServiceManager _event_sm;
};

#endif
