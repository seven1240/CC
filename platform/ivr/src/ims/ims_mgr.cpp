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

#include <ims/ims_mgr.h>


ims_mgr_t::ims_mgr_t()
    : _default_ims((uint32_t) - 1) {
}

ims_mgr_t::~ims_mgr_t() {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        _imsinfo.clear();
    } else {
        IVR_WARN("locked failure");
    }
}

ims_mgr_t* ims_mgr_t::get_instance() {
    static ims_mgr_t __instance;
    return &__instance;
}

int32_t ims_mgr_t::add_ims(const ims_info_t& ims) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        ims_map::iterator iter = _imsinfo.find(ims.get_imsno());

        if (iter != _imsinfo.end()) {
            ims_info tmp(new ims_info_t(ims));
            iter->second = tmp;
            IVR_TRACE("update ims[%d] info!", ims.get_imsno());
        } else {
            _imsinfo.insert(std::make_pair(ims.get_imsno(), ims_info(new ims_info_t(ims))));
            IVR_TRACE("add new ims[%d]", ims.get_imsno());
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::del_ims(uint32_t imsno) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");

        // delete ims info
        ims_map::iterator iterfind = _imsinfo.find(imsno);

        if (iterfind != _imsinfo.end()) {
            _imsinfo.erase(iterfind);
            IVR_TRACE("ims_mgr_t remove ims[%d]!", imsno);

            if (imsno == _default_ims) {
                if (_imsinfo.empty()) {
                    // reset default ims
                    _default_ims = (uint32_t) - 1;
                } else {
                    // switch to next ims
                    _switch_default_ims();
                }
            }
        } else {
            IVR_WARN("ims_mgr_t not found ims[%d]", imsno);
            return IVR_FAIL_IMS_NOTEXIST;
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::set_default_ims(uint32_t imsno) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        ims_map::iterator iterfind = _imsinfo.find(imsno);

        if (iterfind != _imsinfo.end()) {
            _default_ims = imsno;
            IVR_TRACE("set default ims[%d]", imsno);
        } else {
            IVR_WARN("not found ims[%d]", imsno);
            return IVR_FAIL_IMS_NOTEXIST;
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

uint32_t ims_mgr_t::get_default_ims() const {
    return _default_ims;
}

int32_t ims_mgr_t::switch_default_ims() {
    return _switch_default_ims(_default_ims);
}

int32_t  ims_mgr_t::_switch_default_ims(uint32_t imsno) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");

        if (_imsinfo.empty()) {
            IVR_TRACE("no ims!");
            return IVR_FAIL_NOIMS;
        } else if (imsno != _default_ims) {
            IVR_TRACE("some one must had switched default ims, want to switch ims %u, default ims is %u", imsno,
                      _default_ims);
            return IVR_SUCCESS; // switch successed
        } else {
            uint32_t orgno = _default_ims;
            _switch_default_ims();

            IVR_TRACE("switch default ims %u -> %u", orgno, _default_ims);
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::_get_ims(uint32_t imsno, ims_info& ims) {
    // get ims
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");

        if (_imsinfo.empty()) {
            IVR_TRACE("no ims!");
            return IVR_FAIL_NOIMS;
        } else if (_imsinfo.find(imsno) == _imsinfo.end()) {
            IVR_TRACE("not found ims %u!", imsno);
            return IVR_FAIL_IMS_NOTEXIST;
        } else {
            ims = _imsinfo[imsno];

            if (ims.get() == NULL) {
                IVR_WARN("ims[%d] information is NULL", imsno);
                return IVR_FAIL_IMS_INFOINVALIDATE;
            }
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::create_session(const std::string& callsource,
                                  const std::string& channel_id,
                                  const std::string& channel_name,
                                  const std::string& oricalled,
                                  ims_session_id_t& imssid,
                                  uint32_t& out_imsno) {
    IVR_TRACE("[ims_mgr_t::create_session], callsource(%s) channel_id(%s) channel_name(%s) oricalled(%s)",
              callsource.c_str(), channel_id.c_str(), channel_name.c_str(), oricalled.c_str());

    int rcode = -1;
    std::set<uint32_t> usedims;

    while (true) {
        uint32_t imsno = (uint32_t) - 1;
        {
            // get default ims
            locker_t lock(&_info_mutex);

            if (lock.is_locked()) {
                IVR_DEBUG("locked");
                imsno = _default_ims;
            } else {
                return IVR_FAIL_LOCK;
            }
        }

        if (usedims.find(imsno) != usedims.end()) {
            // this ims has used
            rcode = IVR_FAIL_IMS_CREATESESSION;
            break;
        }

        // get ims
        ims_info ims;
        int32_t ret = _get_ims(imsno, ims);
        ims_reqid_t reqid = 0;

        if (IVR_FAIL_NOIMS == ret) {
            rcode = IVR_FAIL_NOIMS;
            break;
        } else if (IVR_SUCCESS != ret) {
            // switch to next ims
        } else if (NULL == ims.get()) {
            IVR_WARN("ims[%d] information is NULL", imsno);
        } else {
            imsapi_proxy_pointer proxy;

            if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
                ims_session_id_t sid;
                ims_ccresult_t ccrt = proxy->CreateSession(reqid, callsource, channel_id, oricalled, sid);
                int32_t ret = _check_result(ccrt, proxy->get_errno(), "CreateSession");

                if (IVR_SUCCESS == ret) {
                    IVR_TRACE("ims_mgr_t create session done, default imsno(%u), session_id(%ld)", imsno, sid);
                    imssid = sid;
                    out_imsno = imsno;
                    return IVR_SUCCESS;
                } else if (IVR_FAIL_IMS_REQIDINVALIDATE == ret) {
                    IVR_DEBUG("ims [%u] reqid(%ld) error!", imsno, reqid);
                    int32_t upres = ims->update(reqid);

                    if (IVR_SUCCESS == upres || IVR_FAIL_IMS_REINIT == upres) {
                        IVR_TRACE("ims [%u] reinit success!", imsno);
                        // re createsession again
                        //return -1;
                        continue;
                    } else {
                        // failed, switch to next ims
                        IVR_TRACE("reinit ims [%u] failed!", imsno);
                    }
                } else if (IVR_FAIL_IMS_PROXY_FAILED == ret || IVR_FAIL_IMS_AGENTNOTASSIGNED == ret) {
                    IVR_DEBUG("proxy error or ims[%u] is not main ims, default ims need switch.", imsno);
                } else {
                    IVR_WARN("ims_mgr_t create session failed!, imsno(%u)", imsno);
                    rcode = ret;
                    break;
                }
            } else { // get proxy failed, switch to next ims
                IVR_WARN("ims_mgr_t create session failed, no opr!, imsno(%u)", imsno);
            }
        }

        usedims.insert(imsno);
        // switch to next ims
        _switch_default_ims(imsno);
    }

    IVR_WARN("ims_mgr_t not found a good ims to create session!");

    return rcode;
}

int32_t ims_mgr_t::route_request(uint32_t imsno, ims_session_id_t imssid,
                                 ims_routerequest_id_t& requestid,
                                 ims_servicetype_t destService, int32_t timeout, int32_t valid_time,
                                 ims_routerequest_type_t reqType, const std::string& reqArgs,
                                 int32_t level, const std::string& caller_uri, const std::string& callee_uri,
                                 const std::string& buffer) {
    IVR_TRACE("[ims_mgr_t::route_request] imsno(%u), ims session id(%ld), destService(%s),"
              "timeout(%ds), validtime(%ds), reqType(%s), reqArgs(%s), level(%d),"
              "caller(%s), callee(%s), buffer(%s)", imsno, imssid, destService.get_desc().c_str(),
              timeout, valid_time, reqType.get_desc().c_str(), reqArgs.c_str(), level, caller_uri.c_str(),
              callee_uri.c_str(), buffer.c_str());
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_ccresult_t ccrt = proxy->RouteRequest(reqid, imssid,
                              destService, timeout, valid_time,
                              reqType, reqArgs, level, caller_uri,
                              callee_uri, buffer, requestid);
        int32_t ret = _check_result(ccrt, proxy->get_errno(), "RouteRequest");

        if (IVR_SUCCESS == ret) {
            IVR_TRACE("ims_mgr_t route request done, imsno(%u), session_id(%ld), requestid(%ld)",
                      imsno, imssid, requestid);
        } else if (IVR_FAIL_IMS_REQIDINVALIDATE == ret) {
            IVR_WARN("ims_mgr_t route request failed! imsno(%u), session_id(%ld)", imsno, imssid);
            return IVR_FAIL_IMS_REQIDINVALIDATE;
        } else if (IVR_FAIL_IMS_SESSIONINVALIDATE == ret) {
            IVR_WARN("ims_mgr_t route request failed! imsno(%u), session_id(%ld)", imsno, imssid);
            return IVR_FAIL_IMS_SESSIONINVALIDATE;
        } else if (IVR_FAIL_IMS_ROUTEREQUEST_REPEATED == ret) {
            IVR_WARN("ims_mgr_t route request failed! imsno(%u), session_id(%ld)", imsno, imssid);
            return IVR_FAIL_IMS_ROUTEREQUEST_REPEATED;
        } else {
            IVR_WARN("ims_mgr_t route request failed! imsno(%u), session_id(%ld)", imsno, imssid);
            return IVR_FAIL_IMS_ROUTEREQUEST;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t route request failed, no opr! imsno(%u)", imsno);
        return IVR_FAIL_IMS_ROUTEREQUEST;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::cancel_route_request(uint32_t imsno, ims_session_id_t imssid,
                                        ims_routerequest_id_t requestId) {
    IVR_TRACE("[ims_mgr_t::cancel_route_request] imsno(%u), ims sesionid(%ld), requestID(%ld)",
              imsno, imssid, requestId);
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_ccresult_t ccrt = proxy->CancelRouteRequest(reqid, imssid, requestId);

        if (IVR_SUCCESS == _check_result(ccrt, proxy->get_errno(), "CancelRouteRequest")) {
            IVR_TRACE("ims_mgr_t cancel route request done, imsno(%u), session_id(%ld), requestid(%ld)",
                      imsno, imssid, requestId);
        } else {
            // todo: log error reseaon here.
            IVR_WARN("ims_mgr_t cancel route request failed! imsno(%u), sessionid(%ld), requestid(%ld)",
                     imsno, imssid, requestId);
            return IVR_FAIL_IMS_CANCELROUTEREQUEST;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t cancel route request failed, no opr!, imsno(%u)", imsno);
        return IVR_FAIL_IMS_CANCELROUTEREQUEST;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::trans_agent(uint32_t imsno, ims_session_id_t imssid,
                               ims_routerequest_id_t requestid, ims_transtype_t transType) {
    IVR_TRACE("[ims_mgr_t::trans_agent] imsno(%u), ims sesionid(%ld), requestID(%ld), transtype(%s)",
              imsno, imssid, requestid, transType.get_desc().c_str());
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_ccresult_t ccrt = proxy->TransferAgent(reqid, imssid, requestid, transType);

        if (IVR_SUCCESS == _check_result(ccrt, proxy->get_errno(), "TransferAgent")) {
            IVR_TRACE("ims_mgr_t trans agent done, imsno(%u), session_id(%ld), requestid(%ld)",
                      imsno, imssid, requestid);
        } else {
            // todo: log error reseaon here.
            IVR_WARN("ims_mgr_t trans agent failed! imsno(%u), session_id(%ld), requestid(%ld)",
                     imsno, imssid, requestid);
            return IVR_FAIL_IMS_TRANSAGENT;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t trans agent failed, no opr!, imsno(%u)", imsno);
        return IVR_FAIL_IMS_TRANSAGENT;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::set_associatedata(uint32_t imsno, ims_session_id_t imssid, const string& key,
                                     const string& value) {
    IVR_TRACE("[ims_mgr_t::set_associatedata] imsno(%u), ims sesionid(%ld), key(%s), value(%s)",
              imsno, imssid, key.c_str(), value.c_str());
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_ccresult_t ccrt = proxy->SetAssociateData(reqid, imssid, key, value);

        if (IVR_SUCCESS == _check_result(ccrt, proxy->get_errno(), "SetAssociateData")) {
            IVR_TRACE("ims_mgr_t set associatedata done, imsno(%u), session_id(%ld)",
                      imsno, imssid);
        } else {
            // todo: log error reseaon here.
            IVR_WARN("ims_mgr_t set associatedata failed! imsno(%u), session_id(%ld)",
                     imsno, imssid);
            return IVR_FAIL_IMS_SETASSOCIATEDATA;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t set associdatedata failed, no opr! imsno(%u)", imsno);
        return IVR_FAIL_IMS_SETASSOCIATEDATA;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::get_associatedata(uint32_t imsno, ims_session_id_t imssid, const string& key,
                                     string& value) {
    IVR_TRACE("[ims_mgr_t::get_associatedata] imsno(%u), ims sesionid(%ld), key(%s)",
              imsno, imssid, key.c_str());
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_ccresult_t ccrt = proxy->GetAssociateData(reqid, imssid, key, value);

        if (IVR_SUCCESS == _check_result(ccrt, proxy->get_errno(), "GetAssociateData")) {
            IVR_TRACE("ims_mgr_t get associatedata done, imsno(%u), session_id(%ld), value(%s)",
                      imsno, imssid, value.c_str());
        } else {
            // todo: log error reseaon here.
            IVR_WARN("ims_mgr_t get associatedata failed! imsno(%u), session_id(%ld)",
                     imsno, imssid);
            return IVR_FAIL_IMS_GETASSOCIATEDATA;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t get associdatedata failed, no opr! imsno(%u)", imsno);
        return IVR_FAIL_IMS_GETASSOCIATEDATA;
    }

    return IVR_SUCCESS;
}

int32_t ims_mgr_t::makecall(uint32_t imsno, const std::string& caller, const std::string& callee,
                            const std::string& showani,
                            const std::string& showdest, int32_t timeout, int32_t callmode, ims_session_id_t& imssid) {
    IVR_TRACE("[ims_mgr_t::makecall] imsno(%u), caller(%s), callee(%s), showani(%s), showdest(%s)"
              "timeout(%d), callmode(%d), ims_sid(%ld)", imsno, caller.c_str(), callee.c_str(),
              showani.c_str(), showdest.c_str(), timeout, callmode, imssid);
    // get ims
    ims_info ims;
    int32_t ret = _get_ims(imsno, ims);

    if (IVR_SUCCESS != ret) {
        return ret;
    }

    ims_reqid_t reqid = 0;
    imsapi_proxy_pointer proxy;

    if (IVR_SUCCESS == ims->get_info(proxy, reqid) && proxy.get() != NULL) {
        ims_session_id_t sid = imssid;
        ims_ccresult_t ccrt = proxy->OutboundCall(reqid, caller, callee, showani, showdest,
                              timeout, callmode, sid);

        if (IVR_SUCCESS == _check_result(ccrt, proxy->get_errno(), "OutboundCall")) {
            imssid = sid;
            IVR_TRACE("ims_mgr_t makecall done, imsno(%u), session_id(%ld)",
                      imsno, sid);
        } else {
            // todo: log error reseaon here.
            IVR_WARN("ims_mgr_t makecall failed! imsno(%u), session_id(%ld)",
                     imsno, imssid);
            return IVR_FAIL_IMS_MAKECALL;
        }
    } else { // get proxy failed
        IVR_WARN("ims_mgr_t makecall failed, no opr! imsno(%u)", imsno);
        return IVR_FAIL_IMS_MAKECALL;
    }

    return 0;
}

void ims_mgr_t::bind_session_id(ims_session_id_t imssid, ivr_session_id_t ivrsid) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        _session_map[imssid] = ivrsid;
        IVR_TRACE("binding session id ims(%ld) -> ivr(%lu), map size(%d)", imssid, ivrsid,
                  (int)_session_map.size());
    } else {
        IVR_WARN("locked failure");
    }
}

void ims_mgr_t::unbind_session_id(ivr_session_id_t ivrsid) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        typedef std::map<ims_session_id_t, ivr_session_id_t>::iterator sessionmap_iterator;
        std::deque<sessionmap_iterator> toremoves;

        for (sessionmap_iterator iter = _session_map.begin(); iter != _session_map.end(); ++ iter) {
            if (iter->second == ivrsid) {
                toremoves.push_back(iter);
            }
        }

        for (std::deque<sessionmap_iterator>::iterator iiter = toremoves.begin(); iiter != toremoves.end();
                ++ iiter) {
            _session_map.erase(*iiter);
        }

        IVR_TRACE("ims_mgr_t unbinding ivr session id %lu, map size(%d)", ivrsid, (int)_session_map.size());
    } else {
        IVR_WARN("locked failure");
    }
}

bool ims_mgr_t::get_map_session_id(ims_session_id_t imssid, ivr_session_id_t& ivrsid) {
    locker_t lock(&_info_mutex);

    if (lock.is_locked()) {
        IVR_DEBUG("locked");
        typedef std::map<ims_session_id_t, ivr_session_id_t>::iterator sessionmap_iterator;
        sessionmap_iterator iterfind = _session_map.find(imssid);

        if (iterfind != _session_map.end()) {
            IVR_TRACE("ims_mgr_t get ivr session id (%lu) of ims session id (%ld)", iterfind->second, imssid);
            ivrsid = iterfind->second;
        } else {
            //IVR_WARN("ims_mgr_t no ims session (%lld) found!", imssid);
            return false;
        }
    } else {
        IVR_WARN("locked failure, failed get map ims session id %ld", imssid);
        return false;
    }

    return true;
}

bool ims_mgr_t::is_ims_valid() const {
    return !_imsinfo.empty() && _imsinfo.find(_default_ims) != _imsinfo.end();
}

bgcc::ServiceManager* ims_mgr_t::getCallbackService() {
    return &_event_sm;
}

void ims_mgr_t::_switch_default_ims() {
    ims_map::iterator iterfind = _imsinfo.find(_default_ims);
    ims_map::iterator iternext = _imsinfo.end();

    if (iterfind != _imsinfo.end()) {
        iternext = iterfind;

        // if current is last ims, first ims is the next ims
        if (++ iternext == _imsinfo.end()) {
            iternext = _imsinfo.begin();
        }

        _default_ims = iternext->first;
    } else {
        // using first ims
        uint32_t imsno = _default_ims;
        _default_ims = _imsinfo.begin()->first;
        IVR_WARN("not found ims[%d], using first ims[%d] as default ims", imsno, _default_ims);
    }
}

int32_t ims_mgr_t::_check_result(ims::CcResultT retcode, int32_t proxy_code,
                                 const std::string& info) {
    using namespace ims;

    if (proxy_code != 0) {
        IVR_TRACE("%s failed, lost connection, proxy recode (%d)", info.c_str(), proxy_code);
        return IVR_FAIL_IMS_PROXY_FAILED;
    } else {
        switch (retcode.get_value()) {
        case CcResultT::ResSuccess:
            IVR_TRACE("%s successed!", info.c_str());
            return IVR_SUCCESS; // return success here

        case CcResultT::ResFailed:
        case CcResultT::ResInvalidParam:
        case CcResultT::ResNotSupport:
        case CcResultT::ResNoEnoughResource:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            break;

        case CcResultT::ResInvalidReqId:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            return IVR_FAIL_IMS_REQIDINVALIDATE;

        case CcResultT::ResSessionNotFound:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            return IVR_FAIL_IMS_SESSIONINVALIDATE;

        case CcResultT::ResInvalidDn:
        case CcResultT::ResInvalidState:
        case CcResultT::ResInvalidFile:
        case CcResultT::ResCallSourceNotFound:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            break;

        case CcResultT::ResRouteRequestRepeated:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            return IVR_FAIL_IMS_ROUTEREQUEST_REPEATED;

        case CcResultT::ResNoAgentAssigned:
            IVR_TRACE("%s failed, error reason(%s)", info.c_str(), retcode.get_desc().c_str());
            return IVR_FAIL_IMS_AGENTNOTASSIGNED;

        default:
            IVR_TRACE("%s unknown error", info.c_str());
            break;
        }
    }

    return -1;
}
