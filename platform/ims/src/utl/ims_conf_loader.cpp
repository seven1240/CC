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

#include "ims_conf_loader.h"
#include "ims_tool.h"
#include <iostream>
#include "ims_log.h"
#include "ims_lock.h"
#include "ims_core_session_mgr.h"
#include "fs_mgr.h"

bool ims_conf_loader_t::load_conf(runtime_pool_t& pool, ims_conf_t& conf, bool isreload) {

    ims_session_manager_t* pmgr = ims_session_manager_t::instance();
    rw_lock_t  lock(pmgr->config_lock(), true);

    if (!lock.locked()) {
        WARNING_LOG("lock config_lock failed!");
        return false;
    }

    const char* doc_name = "conf/ims.conf.xml";
    xmlDocPtr doc;
    xmlNodePtr cur_node;

    doc = xmlReadFile(doc_name, "UTF-8", XML_PARSE_RECOVER);

    if (!doc) {
        WARNING_LOG("get config file failed!");
        return false;
    }

    cur_node = xmlDocGetRootElement(doc);

    if (!cur_node) {
        WARNING_LOG("config file has no root element!");
        xmlFreeDoc(doc);
        return false;
    }

    if (xmlStrcmp(cur_node->name, BAD_CAST "document") != 0) {
        xmlFreeDoc(doc);
        WARNING_LOG("the root element of config file isn't document!");
        return false;
    }

    cur_node = cur_node->xmlChildrenNode;

    while (cur_node != NULL) {
        xmlChar* type_name = xmlGetProp(cur_node, BAD_CAST"type");

        if (!type_name) {
            cur_node = cur_node->next;
            continue;
        }

        if (xmlStrcmp(cur_node->name, BAD_CAST "section") == 0) { //<section/>

            if (xmlStrcmp(type_name,  BAD_CAST"service") == 0 && !isreload) { // <section type="service"/>
                if (!this->load_service(cur_node, pool, conf)) {
                    WARNING_LOG("load serivce failed!\n");
                    xmlFreeDoc(doc);
                    return false;
                }
            } else if (xmlStrcmp(type_name, BAD_CAST"param") == 0 && !isreload) { // <section type="param"/>
                if (!this->load_param(cur_node , pool, conf)) {
                    WARNING_LOG("load param failed!\n");
                    xmlFreeDoc(doc);
                    return false;
                }
            } else if (xmlStrcmp(type_name, BAD_CAST"client") == 0) { //<section type="client"/>
                if (isreload) {
                    conf.clients.clear();
                }

                if (!this->load_client(cur_node, pool, conf)) {
                    WARNING_LOG("load clients failed!\n");
                    xmlFreeDoc(doc);
                    return false;
                }
            } else if (xmlStrcmp(type_name, BAD_CAST"gateway") == 0) { // <section type="gateway"/>
                if (isreload) {
                    conf.gateway.clear();
                }

                char* islog = (char*)xmlGetProp(cur_node, BAD_CAST"log");

                if (islog && strcasecmp(islog, "true") == 0) {
                    conf.gw_log = true;
                } else {
                    conf.gw_log = false;
                }

                if (islog) {
                    free(islog);
                    islog = NULL;
                }

                if (!this->load_gateway(cur_node, pool, conf)) {
                    WARNING_LOG("load gateway failed!\n");
                    xmlFreeDoc(doc);
                    return false;
                }
            } else if (xmlStrcmp(type_name, BAD_CAST"route") == 0) { // <section type="route"/>
                if (isreload) {
                    conf.route.clear();
                }

                if (!this->load_route(cur_node, pool, conf)) {
                    WARNING_LOG("load route failed!");
                    xmlFreeDoc(doc);
                    return false;
                }
            }
        }

        xmlFree(type_name);

        cur_node = cur_node->next;
    } // end while

    xmlFreeDoc(doc);

    fs_mgr_t::instance()->update_log(conf.gw_log);
    return true;
}


bool ims_conf_loader_t::load_service(xmlNodePtr cur_node, runtime_pool_t& pool, ims_conf_t& conf) {

    xmlNodePtr low_node = cur_node->xmlChildrenNode;

    while (low_node) {
        if (xmlStrcmp(low_node->name, BAD_CAST "service") == 0) { //<service/>
            xmlChar* low_type_name = xmlGetProp(low_node, BAD_CAST"type");

            if (!low_type_name) {
                low_node = low_node->next;
                continue;
            }

            char* cip = (char*) xmlGetProp(low_node, BAD_CAST"ip");
            char* cport = (char*) xmlGetProp(low_node, BAD_CAST"port");
            uint32_t ip;
            uint32_t port;

            if (!ims_tool_t::pa_chkport(cport, port) || !ims_tool_t::pa_chkip(cip, ip)) {
                low_node = low_node->next;

                xmlFree(cip);
                xmlFree(cport);
                xmlFree(low_type_name);

                WARNING_LOG(" config  <service> is wrong, ip or port is wrong!");
                continue;
            }

            xmlFree(cip);
            xmlFree(cport);

            if (xmlStrcmp(low_type_name, BAD_CAST"main") == 0) { //<service type="main"/>
                //ims_conf_server_t *server_main=pool.createp<ims_conf_server_t,uint32_t,uint32_t>(ip, port);
                ims_conf_server_t* server_main = pool.conf_server_pool.construct(ip, port);
                conf.service[ICST_MAIN] = server_main;

                if (conf.service.count(ICST_MAIN) == 0) {
                    xmlFree(low_type_name);
                    return false;
                }

            } else if (xmlStrcmp(low_type_name, BAD_CAST"monitor") == 0) { //<service type="monitor"/>
                //ims_conf_server_t *server_monitor=pool.createp<ims_conf_server_t,uint32_t,uint32_t>(ip, port);
                ims_conf_server_t* server_monitor = pool.conf_server_pool.construct(ip, port);
                conf.service[ICST_MONITOR] = server_monitor;

                if (conf.service.count(ICST_MONITOR) == 0) {
                    xmlFree(low_type_name);
                    return false;
                }

            } else if (xmlStrcmp(low_type_name, BAD_CAST"config") == 0) { //<service type="config"/>
                //ims_conf_server_t *server_config=pool.createp<ims_conf_server_t,uint32_t,uint32_t>(ip,port);
                ims_conf_server_t* server_config = pool.conf_server_pool.construct(ip, port);
                conf.service[ICST_CONFIG] = server_config;

                if (conf.service.count(ICST_CONFIG) == 0) {
                    xmlFree(low_type_name);
                    return false;
                }
            }

            xmlFree(low_type_name);
        }

        low_node = low_node->next;
    }//end while

    return true;
}

bool ims_conf_loader_t::load_param(xmlNodePtr cur_node, runtime_pool_t& pool, ims_conf_t& conf) {
    xmlNodePtr low_node = cur_node->xmlChildrenNode;

    while (low_node) {
        if (xmlStrcmp(low_node->name, BAD_CAST "param") == 0) { // <param/>
            xmlChar* low_type_name = xmlGetProp(low_node, BAD_CAST"name");

            if (!low_type_name) {
                low_node = low_node->next;
                continue;
            }

            if (xmlStrcmp(low_type_name, BAD_CAST"max-session") == 0) { //<param name="max-session"/>
                char* scount = (char*) xmlGetProp(low_node, BAD_CAST"value");

                if (scount == NULL) {
                    scount = (char*) malloc(sizeof(char) * 10);
                    strncpy(scount, "2000", 9);
                }

                const char* param1 = ims_tool_t::strdup(scount, &pool.string_pool);
                free(scount);
                scount = NULL;

                if (!param1) {
                    return false;
                }

                conf.param[ICPT_MAXSESSION] = param1;
            } else if (xmlStrcmp(low_type_name, BAD_CAST"bgcc-poolsize") == 0) { //<param name="bgcc-poolsize"/>
                char* scount = (char*) xmlGetProp(low_node, BAD_CAST"value");

                if (scount == NULL) {
                    scount = (char*) malloc(sizeof(char) * 10);
                    strncpy(scount, "500", 9);
                }

                const char* param1 = ims_tool_t::strdup(scount, &pool.string_pool);
                free(scount);
                scount = NULL;

                if (!param1) {
                    return false;
                }

                conf.param[ICPT_BGCCPOOLSIZE] =  param1;
            }

            xmlFree(low_type_name);
        }

        low_node = low_node->next;
    }//end while

    return true;
}

bool ims_conf_loader_t::load_client(xmlNodePtr cur_node, runtime_pool_t& pool, ims_conf_t& conf) {
    xmlNodePtr low_node = cur_node->xmlChildrenNode;

    while (low_node != NULL) {

        if (xmlStrcmp(low_node->name, BAD_CAST "client") == 0) { // <client/>
            xmlChar* low_type_name = xmlGetProp(low_node, BAD_CAST"type");

            if (!low_type_name) {
                low_node = low_node->next;
                continue;
            }

            if (xmlStrcmp(low_type_name, BAD_CAST"ivr") == 0
                    || xmlStrcmp(low_type_name, BAD_CAST"config") == 0
                    || xmlStrcmp(low_type_name, BAD_CAST"acd") == 0
                    || xmlStrcmp(low_type_name, BAD_CAST"monitor") ==
                    0) {// <client type="ivr">, //<client type="config">, <client type="acd">, <client type="monitor">

                xmlNodePtr lower_node = low_node->xmlChildrenNode;
                std::list<ims_conf_acl_node_t*> acls;

                while (lower_node != NULL) {

                    if (xmlStrcmp(lower_node->name, BAD_CAST "allow") == 0) { // <allow/>
                        char* data = (char*) xmlGetProp(lower_node, BAD_CAST"data");
                        uint32_t ip;
                        uint32_t mask;
                        uint32_t bit;
                        bool result = ims_tool_t::ip_mask_parse(data, ip, mask, bit);
                        free(data);
                        data = NULL;

                        if (result == true) {

                            //ims_conf_acl_node_t *node=pool.createp<ims_conf_acl_node_t,uint32_t,uint32_t,uint32_t>(ip,mask,bit);
                            ims_conf_acl_node_t* node = pool.conf_acl_pool.construct(ip, mask, bit);

                            if (node == NULL) {
                                return false;
                            }

                            acls.push_back(node);
                        } else {
                            WARNING_LOG("config <allow> is wrong!");
                        }
                    }

                    lower_node = lower_node->next;
                }//end while

                if (xmlStrcmp(low_type_name, BAD_CAST"ivr") == 0) {
                    conf.clients[ICCT_IVR] = acls;
                } else if (xmlStrcmp(low_type_name, BAD_CAST"config") == 0) {
                    conf.clients[ICCT_CONFIG] = acls;
                } else if (xmlStrcmp(low_type_name, BAD_CAST"acd") == 0) {
                    conf.clients[ICCT_ACD] = acls;
                } else if (xmlStrcmp(low_type_name, BAD_CAST"monitor") == 0) {
                    conf.clients[ICCT_MONITOR] = acls;
                }
            }

            xmlFree(low_type_name);
        }

        low_node = low_node->next;
    }//end while


    return true;
}


bool ims_conf_loader_t::load_gateway(xmlNodePtr cur_node, runtime_pool_t& pool, ims_conf_t& conf) {
    xmlNodePtr  low_node = cur_node->xmlChildrenNode;

    while (low_node) {
        if (xmlStrcmp(low_node->name, BAD_CAST "gateway") == 0) { // <gateway/>
            xmlChar* low_type_name = xmlGetProp(low_node, BAD_CAST"type");

            if (!low_type_name) {
                low_node = low_node->next;
                continue;
            }

            if (xmlStrcmp(low_type_name, BAD_CAST"freeswitch") == 0) { // <gateway type="freeswitch">
                //ims_conf_gw_node_t* gw=pool.createp<ims_conf_gw_node_t>();
                ims_conf_gw_node_t* gw = pool.conf_gw_pool.construct();

                if (!gw) {
                    return false;
                }

                char* cid = (char*) xmlGetProp(low_node, BAD_CAST"id");
                char* cip = (char*) xmlGetProp(low_node, BAD_CAST"ip");
                char* cport = (char*) xmlGetProp(low_node, BAD_CAST"port");
                char* cpwsd = (char*) xmlGetProp(low_node, BAD_CAST"pswd");
                char* cuser = (char*) xmlGetProp(low_node, BAD_CAST"user");
                char* cmax = (char*) xmlGetProp(low_node, BAD_CAST"max_conn");
                char* dtmf = (char*) xmlGetProp(low_node, BAD_CAST"dtmf");

                if (NULL == cid || NULL == cip || NULL == cport || NULL == cpwsd || NULL == cuser || NULL == dtmf) {
                    free(cid);
                    cid = NULL;
                    free(cip);
                    cip = NULL;
                    free(cport);
                    cport = NULL;
                    free(cpwsd);
                    cpwsd = NULL;
                    free(cuser);
                    cuser = NULL;
                    free(cmax);
                    cmax = NULL;
                    free(dtmf);
                    dtmf = NULL;
                    low_node = low_node->next;
                    WARNING_LOG("config <gateway type=\"freeswitch\"> is wrong!");
                    continue;
                }

                uint32_t ip, port;

                if (ims_tool_t::pa_chkip(cip, ip) && ims_tool_t::pa_chkport(cport, port)) {
                    uint32_t id = ims_tool_t::str_to_uint32(cid);
                    uint32_t max = 2000;

                    if (cmax != NULL) {
                        max = ims_tool_t::str_to_uint32(cmax);
                    }

                    free(cmax);
                    cmax = NULL;
                    gw->id = id;
                    gw->ip = ip;
                    gw->port = port;
                    gw->max_conn = max;
                    gw->dtmf = (strcasecmp(dtmf, "inband") == 0 ? DTMF_INBAND : DTMF_OTHER);
                    strncpy(gw->user, cuser, LEN_64);
                    strncpy(gw->pswd, cpwsd, LEN_64);
                    free(cid);
                    cid = NULL;
                    free(cip);
                    cip = NULL;
                    free(cport);
                    cport = NULL;
                    free(cpwsd);
                    cpwsd = NULL;
                    free(cuser);
                    cuser = NULL;
                    free(cmax);
                    cmax = NULL;
                    free(dtmf);
                    dtmf = NULL;
                    conf.gateway.push_back(gw);
                }
            }

            xmlFree(low_type_name);
        }

        low_node = low_node->next;
    }//end while

    return true;
}

bool ims_conf_loader_t::load_route(xmlNodePtr  cur_node, runtime_pool_t& pool, ims_conf_t& conf) {
    xmlNodePtr  low_node = cur_node->xmlChildrenNode;

    while (low_node) {
        if (xmlStrcmp(low_node->name, BAD_CAST "route") == 0) { // <route/>
            xmlChar* ctype = xmlGetProp(low_node, BAD_CAST"type");

            ims_conf_route_type_t type;

            if (xmlStrcmp(ctype, BAD_CAST"outbound") == 0) { //<route tpye = "**">
                type = ICRT_OUTBOUND;
            } else if (xmlStrcmp(ctype, BAD_CAST"inbound") == 0) {
                type = ICRT_INBOUND;
            } else {
                xmlFree(ctype);
                WARNING_LOG("config route's type is wrong!");
                low_node = low_node->next;
                continue;
            }

            char* cname = (char*)xmlGetProp(low_node, BAD_CAST"name");
            xmlNodePtr  low_node1 = low_node->xmlChildrenNode;

            while (low_node1 != NULL) {
                if (xmlStrcmp(low_node1->name, BAD_CAST "condition") == 0) { //<condition/>
                    //ims_conf_route_node_t *route=pool.createp<ims_conf_route_node_t>();
                    ims_conf_route_node_t* route = pool.conf_route_pool.construct();

                    if (!route) {
                        free(cname);
                        cname = NULL;
                        xmlFree(ctype);
                        ctype = NULL;
                        return false;
                    }

                    route->type = type;

                    if (cname == NULL) {
                        strncpy(route->name, "", LEN_64);
                    } else {
                        strncpy(route->name, cname, LEN_64);
                    }

                    char* cfield = (char*) xmlGetProp(low_node1, BAD_CAST"field");
                    char* cexpression = (char*) xmlGetProp(low_node1, BAD_CAST"expression");

                    if (cfield == NULL || cexpression == NULL) {
                        free(cfield);
                        cfield = NULL;
                        free(cexpression);
                        cexpression = NULL;
                        free(cname);
                        cname = NULL;
                        xmlFree(ctype);
                        ctype = NULL;
                        WARNING_LOG("config route <condition field= expression=>, field or expression wrong!");
                        low_node1 = low_node1->next;
                        continue;
                    }

                    strncpy(route->field, cfield, LEN_64);
                    strncpy(route->expression, cexpression, LEN_128);
                    free(cexpression);
                    cexpression = NULL;
                    free(cfield);
                    cfield = NULL;

                    char* disp = NULL;
                    char* caller = NULL;
                    char* called = NULL;

                    xmlNodePtr  low_node2 = low_node1->xmlChildrenNode;

                    while (low_node2 != NULL) {
                        if (xmlStrcmp(low_node2->name, BAD_CAST "set") == 0) {
                            if (disp == NULL) {
                                disp = (char*) xmlGetProp(low_node2, BAD_CAST"disp_callerno");
                            }

                            if (caller == NULL) {
                                caller = (char*) xmlGetProp(low_node2, BAD_CAST"call_callerno");
                            }

                            if (called == NULL) {
                                called = (char*) xmlGetProp(low_node2, BAD_CAST"call_calledno");
                            }
                        }

                        low_node2 = low_node2->next;
                    }

                    if (disp != NULL && caller != NULL && called != NULL) {
                        strncpy(route->rule_disp_caller, disp, LEN_64);
                        strncpy(route->rule_call_caller, caller, LEN_64);
                        strncpy(route->rule_call_called, called, LEN_64);
                    } else {
                        free(disp);
                        disp = NULL;
                        free(caller);
                        caller = NULL;
                        free(called);
                        called = NULL;
                        free(cname);
                        cname = NULL;
                        xmlFree(ctype);
                        ctype = NULL;
                        WARNING_LOG("config route <set> miss disp_rule_caller or rule_call_caller or rule_call_called!");
                        low_node1 = low_node1->next;
                        continue;
                    }

                    free(disp);
                    disp = NULL;
                    free(caller);
                    caller = NULL;
                    free(called);
                    called = NULL;

                    conf.route.push_back(route);

                }

                low_node1 = low_node1->next;
            }

            free(cname);
            cname = NULL;
            xmlFree(ctype);
            ctype = NULL;
        }

        low_node = low_node->next;
    }

    return true;
}

void ims_conf::get_gwdtmftype(uint32_t fsno, dtmf_type_t& type) {
    type = DTMF_INBAND;
    ims_session_manager_t* pmgr = ims_session_manager_t::instance();

    rw_lock_t  lock(pmgr->config_lock());

    if (!lock.locked()) {
        WARNING_LOG("lock config_lock failed!");
        return;
    }

    for (std::list<ims_conf_gw_node_t*>::iterator it = gateway.begin(); it != gateway.end(); ++it) {
        if (*it && fsno == (*it)->id) {
            type = (*it)->dtmf;
            break;
        }
    }
}


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
