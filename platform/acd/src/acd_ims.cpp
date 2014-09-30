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


#include "acd_ims.h"
#include "acd_tool.h"

bool acd_ims::ConnectIMS(bool is_main) {
    if (is_main) {
        p_m_imsapi_prx = &m_imsapi_main;
    } else {
        p_m_imsapi_prx = &m_imsapi_back;
    }

    if (!Register()) {
        return false;
    }

    acd_tool::m_agent_manager.IMSConnect();  // 倒换事件
    return true;
}

void acd_ims::DestroyIMS() {
    acd_tool::m_agent_manager.IMSDisconnect();  // 断链事件
}

void acd_ims::Method() {
    bool is_connected = false;
    bool m_is_main = true;
    uint32_t times = 0;

    while (this->mIsLoop) {
        if (is_connected) {
            if (HeartBeat(acd_tool::p_m_acd_backup->GetIsMaster() ? "master" : "slave")) {
                times = 0;
            } else {
                times++;
            }
        } else {
            is_connected = ConnectIMS(m_is_main);

            if (is_connected) {
                times = 0;
            } else {
                times++;
            }
        }

        if (times == m_times_max) {
            m_is_main = !m_is_main;
            times = 0;
            is_connected = false;
            acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                        "change ims master");
            DestroyIMS();
        }

        bgcc::TimeUtil::safe_sleep_s(m_timespan);
    }
}

acd_ims::acd_ims(const char* main_server_ip, uint32_t main_server_port, const char* back_server_ip,
                 uint32_t back_server_port, uint32_t ims_proxy_num, uint32_t times_max, uint32_t timespan) :
    m_times_max(times_max), m_timespan(timespan),
    m_imsapi_main(bgcc::ServerInfo(main_server_ip, (uint16_t)main_server_port), ims_proxy_num,
                  &m_servicemanager, 1),
    m_imsapi_back(bgcc::ServerInfo(back_server_ip, (uint16_t)back_server_port), ims_proxy_num,
                  &m_servicemanager, 1),
    p_m_imsapi_prx(NULL) {
    m_servicemanager.add_service(bgcc::SharedPointer<bgcc::IProcessor>(new ims::event_callbackProcessor(
                                     bgcc::SharedPointer<ims::event_callback>(new acd_ims_callback()))));
}

acd_ims::~acd_ims() {
}

bool acd_ims::Register() {
    if (p_m_imsapi_prx) {
        ims::CcResultT ret = p_m_imsapi_prx->Register(ims::ServiceTypeT::ServiceACD, m_reqid);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "Communication Error:%d", p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "Return Error:%s",
                                        ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "reqid:%"SHOW_LONG"d ret:%s", m_reqid, ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "p_m_imsapi_prx is null");
        return false;
    }

    return true;
}

bool acd_ims::UnRegister() {
    if (p_m_imsapi_prx) {
        ims::CcResultT ret = p_m_imsapi_prx->UnRegister(m_reqid);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "Communication Error:%d", p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__, "Return Error:%s",
                                        ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "ret:%s",
                                    ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "p_m_imsapi_prx is null");
        return false;
    }

    return true;
}

bool acd_ims::Assign(const string& agentId, const string& agentDn, const ims::DnTypeT& type) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s type:%s", agentId.c_str(), agentDn.c_str(), type.get_desc().c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Assign(m_reqid, agentDn, type);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s type:%s p_m_imsapi_prx is null", agentId.c_str(), agentDn.c_str(),
                                    type.get_desc().c_str());
        return false;
    }

    return true;
}

bool acd_ims::DeAssign(const string& agentId, const string& agentDn, const ims::DnTypeT& type) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s type:%s", agentId.c_str(), agentDn.c_str(), type.get_desc().c_str());
        ims::CcResultT ret = p_m_imsapi_prx->DeAssign(m_reqid, agentDn, type);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s type:%s p_m_imsapi_prx is null", agentId.c_str(), agentDn.c_str(),
                                    type.get_desc().c_str());
        return false;
    }

    return true;
}

bool acd_ims::OutboundCall(const string& agentId, const string& agentDn, const string& destUri,
                           const string& setSrcUri, const string& setDestUri, int32_t timeout, const ims::CallModeT& callmode,
                           ims::SessionIdT& sessionid) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s destUri:%s setSrcUri:%s setDestUri:%s timeout:%d callmode:%s",
                                    agentId.c_str(), agentDn.c_str(), destUri.c_str(), setSrcUri.c_str(), setDestUri.c_str(), timeout,
                                    callmode.get_desc().c_str());
        ims::CcResultT ret = p_m_imsapi_prx->OutboundCall(m_reqid, agentDn, destUri, setSrcUri, setDestUri,
                             timeout, callmode, sessionid);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s sessionid:%"SHOW_LONG"d ret:%s", agentId.c_str(), sessionid, ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s agentDn:%s destUri:%s setSrcUri:%s setDestUri:%s timeout:%d callmode:%s p_m_imsapi_prx is null",
                                    agentId.c_str(), agentDn.c_str(), destUri.c_str(), setSrcUri.c_str(), setDestUri.c_str(), timeout,
                                    callmode.get_desc().c_str());
        return false;
    }

    return true;
}

bool acd_ims::Answer(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Answer(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Release(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Release(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Hold(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Hold(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Retrieve(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Retrieve(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Consult(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                      const string& destUri, const string& setDestUri) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s setDestUri:%s", sessionid,
                                    agentId.c_str(), agentDn.c_str(), destUri.c_str(), setDestUri.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Consult(m_reqid, sessionid, agentDn, destUri, setDestUri);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s setDestUri:%s p_m_imsapi_prx is null",
                                    sessionid, agentId.c_str(), agentDn.c_str(), destUri.c_str(), setDestUri.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Reconnect(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Reconnect(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Transfer(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Transfer(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Conference(ims::SessionIdT sessionid, const string& agentId, const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Conference(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::SingleStepTransfer(ims::SessionIdT sessionid, const string& agentId,
                                 const string& agentDn, const string& destUri, const string& dispForCalled) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s dispForCalled:%s", sessionid,
                                    agentId.c_str(), agentDn.c_str(), destUri.c_str(), dispForCalled.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->SingleStepTransfer(m_reqid, sessionid, agentDn, destUri,
                             dispForCalled);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s dispForCalled:%s p_m_imsapi_prx is null",
                                    sessionid, agentId.c_str(), agentDn.c_str(), destUri.c_str(), dispForCalled.c_str());
        return false;
    }

    return true;
}

bool acd_ims::SingleStepConference(ims::SessionIdT sessionid, const string& agentId,
                                   const string& agentDn, const string& destUri, const string& dispForCalled,
                                   const ims::SsConferenceTypeT& type) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s dispForCalled:%s type:%s", sessionid,
                                    agentId.c_str(), agentDn.c_str(), destUri.c_str(), dispForCalled.c_str(), type.get_desc().c_str());
        ims::CcResultT ret = p_m_imsapi_prx->SingleStepConference(m_reqid, sessionid, agentDn, destUri,
                             dispForCalled, type);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s destUri:%s dispForCalled:%s type:%s p_m_imsapi_prx is null",
                                    sessionid, agentId.c_str(), agentDn.c_str(), destUri.c_str(), dispForCalled.c_str(),
                                    type.get_desc().c_str());
        return false;
    }

    return true;
}

bool acd_ims::SwitchListenAndIntrude(ims::SessionIdT sessionid, const string& agentId,
                                     const string& agentDn) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s", sessionid, agentId.c_str(), agentDn.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->SwitchListenAndIntrude(m_reqid, sessionid, agentDn);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    agentDn.c_str());
        return false;
    }

    return true;
}

bool acd_ims::SetAssociateData(ims::SessionIdT sessionid, const string& agentId, const string& key,
                               const string& val) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s key:%s val:%s", sessionid, agentId.c_str(), key.c_str(),
                                    val.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->SetAssociateData(m_reqid, sessionid, key, val);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s key:%s val:%s p_m_imsapi_prx is null", sessionid,
                                    agentId.c_str(), key.c_str(), val.c_str());
        return false;
    }

    return true;
}

bool acd_ims::GetAssociateData(ims::SessionIdT sessionid, const string& agentId, const string& key,
                               string& val) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s key:%s", sessionid, agentId.c_str(), key.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->GetAssociateData(m_reqid, sessionid, key, val);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s val:%s ret:%s", agentId.c_str(), val.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s key:%s p_m_imsapi_prx is null", sessionid, agentId.c_str(),
                                    key.c_str());
        return false;
    }

    return true;
}

bool acd_ims::RouteRequestRespond(ims::SessionIdT sessionid, ims::RouteRequestIDT requestId,
                                  const ims::RouteEventReasonT& result, const string& targetUri) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d requestId:%"SHOW_LONG"d result:%s targetUri:%s", sessionid, requestId,
                                    result.get_desc().c_str(), targetUri.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->RouteRequestRespond(m_reqid, sessionid, requestId, result,
                             targetUri);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "requestId:%"SHOW_LONG"d Communication Error:%d", requestId, p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "requestId:%"SHOW_LONG"d Return Error:%s", requestId, ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "requestId:%"SHOW_LONG"d ret:%s", requestId, ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d requestId:%"SHOW_LONG"d result:%s targetUri:%s p_m_imsapi_prx is null",
                                    sessionid, requestId, result.get_desc().c_str(), targetUri.c_str());
        return false;
    }

    return true;
}

bool acd_ims::Record(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                     const string& filename, int32_t maxTime, const string& interruptKeys) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s filename:%s maxTime:%d interruptKeys:%s", sessionid,
                                    agentId.c_str(), agentDn.c_str(), filename.c_str(), maxTime, interruptKeys.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->Record(m_reqid, sessionid, agentDn, filename, maxTime,
                             interruptKeys);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s filename:%s maxTime:%d interruptKeys:%s p_m_imsapi_prx is null",
                                    sessionid, agentId.c_str(), agentDn.c_str(), filename.c_str(), maxTime, interruptKeys.c_str());
        return false;
    }

    return true;
}

bool acd_ims::SendDTMF(ims::SessionIdT sessionid, const string& agentId, const string& agentDn,
                       const string& dtmf) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s dtmf:%s", sessionid, agentId.c_str(),
                                    agentDn.c_str(), dtmf.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->SendDTMF(m_reqid, sessionid, agentDn, dtmf);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "sessionid:%"SHOW_LONG"d agentId:%s agentDn:%s dtmf:%s p_m_imsapi_prx is null", sessionid,
                                    agentId.c_str(), agentDn.c_str(), dtmf.c_str());
        return false;
    }

    return true;
}

bool acd_ims::QuerySysInfo(const string& agentId, ims::SysInfoT& sysinfo) {
    if (p_m_imsapi_prx) {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s",
                                    agentId.c_str());
        ims::CcResultT ret = p_m_imsapi_prx->QuerySysInfo(m_reqid, sysinfo);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Communication Error:%d", agentId.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "agentId:%s Return Error:%s", agentId.c_str(), ret.get_desc().c_str());
            return false;
        }

        acd_tool::m_logger.WriteLog(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, "agentId:%s ret:%s",
                                    agentId.c_str(), ret.get_desc().c_str());
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "agentId:%s p_m_imsapi_prx is null", agentId.c_str());
        return false;
    }

    return true;
}

bool acd_ims::HeartBeat(const string& info) {
    if (p_m_imsapi_prx) {
        ims::CcResultT ret = p_m_imsapi_prx->HeartBeat(m_reqid, info);

        if (p_m_imsapi_prx->get_errno() != 0) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "info:%s Communication Error:%d", info.c_str(), p_m_imsapi_prx->get_errno());
            return false;
        }

        if (ret != ims::CcResultT::ResSuccess) {
            acd_tool::m_logger.WriteLog(LOG_LEVEL_WARNING, __FILE__, __LINE__, __FUNCTION__,
                                        "info:%s Return Error:%s", info.c_str(), ret.get_desc().c_str());
            return false;
        }
    } else {
        acd_tool::m_logger.WriteLog(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __FUNCTION__,
                                    "info:%s p_m_imsapi_prx is null", info.c_str());
        return false;
    }

    return true;
}
