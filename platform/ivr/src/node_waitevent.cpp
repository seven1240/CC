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

#include "node_waitevent.h"
#include "ivr_timer.h"
#include "common.h"
#include "ivr_instance_manager.h"

extern map<string, flow_t*> g_flow_name_info_map;

const NodeWaitEvent::exits_t NodeWaitEvent::exits[] = {
    {ivr_call_event_t::IVR_EVT_ANSWER, "_answer"},
    {ivr_call_event_t::IVR_EVT_ALERT, "_alert"},
    {ivr_call_event_t::IVR_EVT_HANGUP, "_hangup"},
    {ivr_call_event_t::IVR_EVT_BRIDGE, "_bridge"},
    {ivr_call_event_t::IVR_EVT_UNBRIDGE, "_unbridge"},
    {ivr_call_event_t::IVR_EVT_CHANLE_DESTORY, "_chanle_destory"},
    {ivr_call_event_t::IVR_EVT_CALLFAIL, "_failure"},
    {ivr_media_event_t::IVR_EVT_PLAY_END, "_play_end"},
    {ivr_media_event_t::IVR_EVT_FILENOTEXIST, "_filenotexist"},
    {ivr_media_event_t::IVR_EVT_GETDIGIT_SUCC, "_getdigit_succ"},
    {ivr_media_event_t::IVR_EVT_GETDIGIT_FAIL, "_getdigit_fail"},
    {ivr_media_event_t::IVR_EVT_DTMF, "_dtmf"},
    {ivr_media_event_t::IVR_EVT_RECORD_START, "_record_start"},
    {ivr_media_event_t::IVR_EVT_RECORD_END, "_record_end"},
    {ivr_other_event_t::IVR_EVT_TIMEOUT, "_timeout"},
    {ivr_other_event_t::IVR_EVT_UNKNOW, "_unknown"},
    {ivr_ims_event_t::IVR_EVT_IMS_ROUTE_RESPONSE, "_imsrouteresponse"},
    {ivr_ims_event_t::IVR_EVT_IMS_NOT_RESPONSE, "_imsrouteresponse"},
    {ivr_ims_event_t::IVR_EVT_IMS_UNKNOW, "_imsrouteresponse"},
    { -1, NULL}
};

NodeWaitEvent::NodeWaitEvent(const uint32_t id, const string& name,
                             const string& type, const string& desc, const key_map_t& keymap) :
    NodeBase(id, name, type, desc, keymap) {
}

NodeWaitEvent::~NodeWaitEvent(void) {
}

NodeBase* NodeWaitEvent::run(base_script_t* param) {
    if (NULL == param) {
        IVR_WARN("base_script_t pointer should not be null");
        return NULL;
    }

    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    const char* exit = EXIT_FAIL;
    IvrTimer* timer;
    ivr_base_event_t* event;
    ivr_session_id_t sid;
    int32_t ret;
    map<string, variable_t>::iterator it;
    string uuid_result;
    string data_result;


    timer = param->timer;
    sid = param->session_id;

    IVR_DEBUG("before do while");

    do {
        //IVR_TRACE("before check timer");
        timer->check_timer(sid);
        //IVR_TRACE("end check timer");
        ret = IvrInstanceManager::get_instance()->get_ivr_event(sid, &event);
        //IVR_TRACE("end get ivr event");
        ivr_tools_t::safe_sleepms(200);
    } while (IVR_SUCCESS != ret);

    int32_t type = event->evt_type;

    if (ivr_base_event_t::CALL_EVENT == type) {
        exit = get_exit(((ivr_call_event_t*)event)->evt_name, param);
    } else if (ivr_base_event_t::MEDIA_EVENT == type) {
        exit = get_exit(((ivr_media_event_t*)event)->evt_name, param);
    } else if (ivr_base_event_t::OTHER_EVENT == type) {
        exit = get_exit(((ivr_other_event_t*)event)->evt_name, param);
    } else if (ivr_base_event_t::IMS_EVENT == type) {
        IVR_TRACE("ims event %d", ((ivr_ims_event_t*)event)->evt_name);
        exit = get_exit(((ivr_ims_event_t*)event)->evt_name, param);

        // kill timer here
        if (param->requestId != 0 && param->timer != NULL) {
            param->timer->delete_timer(param->requestId, ims_transagent);
        }
    } else {
        IVR_WARN("Unknow other event(%d)", type);
        return NULL;
    }

    if (strcasecmp(exit, EXIT_FAIL) == 0 &&
            ((ivr_call_event_t*)event)->evt_name != ivr_call_event_t::IVR_EVT_CALLFAIL) {
        goto END;
    }

    it = param->name_var_map.find(_uuid);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到需要赋值的变量 %s", _uuid.c_str());
        exit = EXIT_FAIL;
        goto END;
    } else {
        IVR_TRACE("找到需要赋值的变量 %s", _uuid.c_str());

        if (INT32 != it->second.type && STRING != it->second.type) {
            IVR_WARN("变量%s 的类型不能被赋值", _uuid.c_str());
            exit = EXIT_FAIL;
            goto END;
        } else {
            IVR_TRACE("找到的变量 %s 可以被赋值", _uuid.c_str());

            if (ivr_base_event_t::CALL_EVENT == type) {
                ivr_call_event_t* e = (ivr_call_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_call_event_t::IVR_EVT_ANSWER == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_call_event_t::IVR_EVT_ALERT == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_call_event_t::IVR_EVT_HANGUP == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_call_event_t::IVR_EVT_BRIDGE == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_call_event_t::IVR_EVT_UNBRIDGE == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_call_event_t::IVR_EVT_CALLFAIL == evt_name) {
                    *(string*)it->second.pvalue = e->other_callid;
                } else {
                    *(string*)it->second.pvalue = e->callid;
                }
            } else if (ivr_base_event_t::MEDIA_EVENT == type) {
                ivr_media_event_t* e = (ivr_media_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_media_event_t::IVR_EVT_PLAY_END == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_media_event_t::IVR_EVT_FILENOTEXIST == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_media_event_t::IVR_EVT_GETDIGIT_SUCC == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_media_event_t::IVR_EVT_GETDIGIT_FAIL == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_media_event_t::IVR_EVT_DTMF == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else if (ivr_media_event_t::IVR_EVT_RECORD_START == evt_name) {
                    *(string*)it->second.pvalue = e->callid;
                } else {
                    *(string*)it->second.pvalue = e->callid;
                }
            } else if (ivr_base_event_t::IMS_EVENT == type) {
                ivr_ims_event_t* e = (ivr_ims_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_ims_event_t::IVR_EVT_IMS_ROUTE_RESPONSE == evt_name) {
                    // ims response event
                    *(string*)it->second.pvalue = param->callid;
                } else {
                }
            } else {
                ivr_other_event_t* e = (ivr_other_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_other_event_t::IVR_EVT_TIMEOUT == evt_name) {
                } else {
                }
            }

            uuid_result = *(string*)it->second.pvalue;
        }
    }

    it = param->name_var_map.find(_data);

    if (it == param->name_var_map.end()) {
        IVR_WARN("未找到需要赋值的变量 %s", _data.c_str());
        exit = EXIT_FAIL;
        goto END;
    } else {
        if (INT32 != it->second.type && STRING != it->second.type) {
            IVR_WARN("变量%s 的类型不能被赋值", _data.c_str());
            exit = EXIT_FAIL;
            goto END;
        } else {
            int32_t type = event->evt_type;

            if (ivr_base_event_t::CALL_EVENT == type) {
                ivr_call_event_t* e = (ivr_call_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_call_event_t::IVR_EVT_ANSWER == evt_name) {
                    *(string*)it->second.pvalue = e->dnis;
                    //Update answer time
                    *(string*)param->name_var_map[SYS_VAR[sys_var_t::CALL_ANSWER_TIME]].pvalue =
                        ivr_tools_t::get_current_second();
                } else if (ivr_call_event_t::IVR_EVT_ALERT == evt_name) {
                    *(string*)it->second.pvalue = e->dnis;
                } else if (ivr_call_event_t::IVR_EVT_HANGUP == evt_name) {
                    //TODO:挂断的电话号码 意义待确定,暂写ani
                    *(string*)it->second.pvalue = e->ani;
                } else if (ivr_call_event_t::IVR_EVT_BRIDGE == evt_name) {
                    *(string*)it->second.pvalue = e->other_callid;
                } else if (ivr_call_event_t::IVR_EVT_UNBRIDGE == evt_name) {
                    *(string*)it->second.pvalue = e->other_callid;
                } else if (ivr_call_event_t::IVR_EVT_CALLFAIL == evt_name) {
                    *(string*)it->second.pvalue = e->other_dnis;
                    /*if(e->evt_reason==ivr_call_event_t::CALL_USER_NOT_REGISTERED)
                    {
                        *(string*)it->second.pvalue = "CALL_USER_NOT_REGISTERED";
                    }
                    else if(e->evt_reason==ivr_call_event_t::CALL_SUBSCRIBER_ABSENT)
                    {
                        *(string*)it->second.pvalue = "CALL_SUBSCRIBER_ABSENT";
                    }
                    else
                    {
                        *(string*)it->second.pvalue = "CALL_FAIL";
                    }*/
                } else {
                    *(string*)it->second.pvalue = "";
                }

                delete e;
            } else if (ivr_base_event_t::MEDIA_EVENT == type) {

                IVR_DEBUG("media");
                ivr_media_event_t* e = (ivr_media_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_media_event_t::IVR_EVT_PLAY_END == evt_name) {
                    *(string*)it->second.pvalue = e->media_data;
                } else if (ivr_media_event_t::IVR_EVT_FILENOTEXIST == evt_name) {
                    *(string*)it->second.pvalue = e->media_data;
                } else if (ivr_media_event_t::IVR_EVT_GETDIGIT_SUCC == evt_name) {
                    *(string*)it->second.pvalue = e->digits;
                } else if (ivr_media_event_t::IVR_EVT_GETDIGIT_FAIL == evt_name) {
                    //data字段对此消息无意义
                } else if (ivr_media_event_t::IVR_EVT_DTMF == evt_name) {
                    *(string*)it->second.pvalue = e->digits;
                    IVR_DEBUG("DTMF:%s", e->digits.c_str());
                } else if (ivr_media_event_t::IVR_EVT_RECORD_START == evt_name) {
                    *(string*)it->second.pvalue = e->media_data;
                    //Update record path
                    *(string*)param->name_var_map[SYS_VAR[sys_var_t::RECORD_FILE]].pvalue = e->media_data;
                } else {
                    *(string*)it->second.pvalue = e->media_data;
                }

                delete e;

                IVR_DEBUG("media end");
            } else if (ivr_base_event_t::IMS_EVENT == type) {
                ivr_ims_event_t* e = (ivr_ims_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_ims_event_t::IVR_EVT_IMS_ROUTE_RESPONSE == evt_name) {
                    // ims response event
                    string_build strb;
                    string res = e->data.reason.get_desc();
                    size_t prelen = strlen("RouteEventReasonT::");
                    res = res.substr(prelen);
                    strb + "{\"requestID\":\"" + e->data.requstid +
                    "\",\"RequestResult\":\"" + res +
                    "\",\"Agent\":\"" + e->data.targetDevice + "\"}";
                    *(string*)it->second.pvalue = strb.str();
                } else if (ivr_ims_event_t::IVR_EVT_IMS_NOT_RESPONSE == evt_name) {
                    string_build strb;
                    strb + "{\"requestID\":\"" + e->data.requstid +
                    "\",\"RequestResult\":\"" + "RouteReasonNotResponse" +
                    "\",\"Agent\":\"" + e->data.targetDevice + "\"}";
                    *(string*)it->second.pvalue = strb.str();
                } else {
                    string_build strb;
                    strb + "{\"requestID\":\"" + e->data.requstid +
                    "\",\"RequestResult\":\"" + "Unknown" +
                    "\",\"Agent\":\"" + e->data.targetDevice + "\"}";
                    *(string*)it->second.pvalue = strb.str();
                }

                delete e;
            } else {
                ivr_other_event_t* e = (ivr_other_event_t*)event;
                int32_t evt_name = e->evt_name;

                if (ivr_other_event_t::IVR_EVT_TIMEOUT == evt_name) {
                    *(string*)it->second.pvalue = e->data;
                } else {
                    //data字段对此消息无意义
                }

                delete e;
            }

            data_result = *(string*)it->second.pvalue;
        }
    }

END:
    NodeBase* exit_node_ptr = NULL;
    std::map<std::string, NodeBase*>::iterator citr;
    citr = _exit_node_map.find(exit);

    if (citr != _exit_node_map.end()) {
        exit_node_ptr = citr->second;

        IVR_TRACE("%s exit from %s, uuid: %s, data: %s", leave(param->name_var_map).c_str(), exit,
                  uuid_result.c_str(), data_result.c_str());
    } else {
        IVR_WARN("Can not find exit %s in _exit_node_map", exit);
    }

    return exit_node_ptr;
}

bool NodeWaitEvent::load_other() {
    check_exit("_answer");
    check_exit("_alert");
    check_exit("_hangup");
    check_exit("_bridge");
    check_exit("_unbridge");
    check_exit("_chanle_destory");
    check_exit("_play_end");
    check_exit("_filenotexist");
    check_exit("_getdigit_succ");
    check_exit("_getdigit_fail");
    check_exit("_dtmf");
    check_exit("_record_start");
    check_exit("_record_end");
    check_exit("_timeout");
    check_exit("_unknown");
    check_exit("_imsrouteresponse");
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_UUID, _uuid)
           && valid_str(_key_map, PARAM_DATA, _data);
}

std::string NodeWaitEvent::enter(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "Uuid: " << _uuid << ", data: " << _data;
    return ostm.str();
}

std::string NodeWaitEvent::leave(const map<string, variable_t>& vars) const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "Uuid: " << _uuid << ", data: " << _data;
    return ostm.str();
}

const char* NodeWaitEvent::get_exit(int32_t type, base_script_t* script) {
    const char* exit = EXIT_SUCC;
    const struct exits_t* pexit;
    int32_t i;

    i = 0;

    while (true) {
        pexit = exits + i;

        if (pexit->exit_name == NULL) {
            break;
        }

        if (type == pexit->type) {
            exit = pexit->exit_name;
            break;
        }

        ++i;
    }

    if (is_exit_configure(exit, script) == false) {
        exit = EXIT_SUCC;
    }

    IVR_TRACE("waiteventnode get_exit res %s", exit == NULL ? "" : exit);
    return exit;
}

bool NodeWaitEvent::is_exit_configure(const char* exit_name, base_script_t* script) {
    if (NULL == exit_name || NULL == script) {
        return false;
    }

    flow_t* flow = script->flow;
    NodeBase* node = flow->id_node_map.find(_id)->second;

    std::string tmp(exit_name);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    key_map_t::iterator itr = node->_key_map.find(tmp.c_str());
    return itr != node->_key_map.end();
}

const char* NodeWaitEvent::PARAM_UUID = "uuid";
const char* NodeWaitEvent::PARAM_DATA = "data";
