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

#include "node_factory.h"

#include "node_answer.h"
#include "node_hangup.h"
#include "node_play.h"
#include "node_getdigits.h"
#include "node_record.h"
#include "node_dial.h"
#include "node_bridge.h"

#include "node_assign.h"
#include "node_compare.h"
#include "node_readini.h"
#include "node_http.h"
#include "node_db.h"
#include "node_bridgeex.h"
#include "node_jsonget.h"
#include "node_playnum.h"

#include "node_waitevent.h"
#include "node_regtimer.h"
#include "node_stoptimer.h"
#include "node_writelog.h"
#include "node_stopmedia.h"
#include "node_stoprecord.h"
#include "node_jsonget_array.h"
#include "node_jsonget_arraylen.h"

#include "node_requestagent.h"
#include "node_transagent.h"
#include "node_cancelagent.h"
#include "node_imsresponsecmp.h"
#include "node_setassociatedata.h"
#include "node_getassociatedata.h"
#include "node_whatweekday.h"
#include "node_makecall.h"

const char* node_factory::NODE_ANSWER = "answer";
const char* node_factory::NODE_HANGUP = "hangup";
const char* node_factory::NODE_PLAY = "play";
const char* node_factory::NODE_RECORD = "record";
const char* node_factory::NODE_DIGIT = "getdigits";
const char* node_factory::NODE_DIAL = "dial";
const char* node_factory::NODE_BRIDGE = "bridge";
const char* node_factory::NODE_ASSIGN = "assign";
const char* node_factory::NODE_COMP = "compare";
const char* node_factory::NODE_DB = "db";
const char* node_factory::NODE_HTTP = "http";
const char* node_factory::NODE_INI = "readini";
const char* node_factory::NODE_BRIDGEEX = "bridgeex";
const char* node_factory::NODE_JSONGET = "jsonget";
const char* node_factory::NODE_PLAYNUM = "playnumber";

const char* node_factory::NODE_WAITEVENT = "waitevent";
const char* node_factory::NODE_REGTIMER = "regtimer";
const char* node_factory::NODE_WRITELOG = "writelog";
const char* node_factory::NODE_STOPTIMER = "stoptimer";
const char* node_factory::NODE_STOPMEDIA = "stopmedia";
const char* node_factory::NODE_STOPRECORD = "stoprecord";
const char* node_factory::NODE_JSONGET_ARRAY = "jsongetarray";
const char* node_factory::NODE_JSONGET_ARRAYLEN = "jsongetarraylen";

const char* node_factory::NODE_REQUEST_AGENT = "requestagent";
const char* node_factory::NODE_TRANS_AGENT = "transagent";
const char* node_factory::NODE_CANCEL_AGENT = "cancelagent";
const char* node_factory::NODE_SET_ASSOCIATEDATA = "setassociatedata";
const char* node_factory::NODE_GET_ASSOCIATEDATA = "getassociatedata";
const char* node_factory::NODE_REQUEST_RESULT = "requestresponsecompare";

const char* node_factory::NODE_WHATWEEKDAY = "whatweekday";
const char* node_factory::NODE_MAKECALL = "makecall";

NodeBase* node_factory::create_node(const uint32_t id,
                                    const string& name, const string& type,
                                    const string& desc, const key_map_t& keymap) {
    NodeBase* node = NULL;

    if (strcasecmp(type.c_str(), NODE_ANSWER) == 0) {
        node = new(std::nothrow) NodeAnswer(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_HANGUP) == 0) {
        node = new(std::nothrow) NodeHangup(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_PLAY) == 0) {
        node = new(std::nothrow) NodePlay(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_RECORD) == 0) {
        node = new(std::nothrow) NodeRecord(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_DIGIT) == 0) {
        node = new(std::nothrow) NodeGetDigits(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_DIAL) == 0) {
        node = new(std::nothrow) NodeDial(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_BRIDGE) == 0) {
        node = new(std::nothrow) NodeBridge(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_ASSIGN) == 0) {
        node = new(std::nothrow) NodeAssign(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_COMP) == 0) {
        node = new(std::nothrow) NodeCompare(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_DB) == 0) {
        node = new(std::nothrow) NodeDB(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_HTTP) == 0) {
        node = new(std::nothrow) NodeHttp(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_INI) == 0) {
        node = new(std::nothrow) NodeReadIni(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_BRIDGEEX) == 0) {
        node = new(std::nothrow) node_bridgeex_t(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_JSONGET) == 0) {
        node = new(std::nothrow) NodeJsonGet(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_PLAYNUM) == 0) {
        node = new(std::nothrow) NodePlayNum(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_WAITEVENT) == 0) {
        node = new(std::nothrow) NodeWaitEvent(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_REGTIMER) == 0) {
        node = new(std::nothrow) NodeRegTimer(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_STOPTIMER) == 0) {
        node = new(std::nothrow) NodeStopTimer(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_WRITELOG) == 0) {
        node = new(std::nothrow) NodeWriteLog(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_STOPMEDIA) == 0) {
        node = new(std::nothrow) NodeStopMedia(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_STOPRECORD) == 0) {
        node = new(std::nothrow) NodeStopRecord(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_JSONGET_ARRAY) == 0) {
        node = new(std::nothrow) NodeJsonGetArray(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_JSONGET_ARRAYLEN) == 0) {
        node = new(std::nothrow) NodeJsonGetArrayLen(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_REQUEST_AGENT) == 0) {
        node = new(std::nothrow) NodeRequestAgent(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_TRANS_AGENT) == 0) {
        node = new(std::nothrow) NodeTransAgent(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_CANCEL_AGENT) == 0) {
        node = new(std::nothrow) NodeCancelAgent(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_SET_ASSOCIATEDATA) == 0) {
        node = new(std::nothrow) NodeSetAssociateData(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_GET_ASSOCIATEDATA) == 0) {
        node = new(std::nothrow) NodeGetAssociateData(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_REQUEST_RESULT) == 0) {
        node = new(std::nothrow) NodeRequestResponseCompare(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_WHATWEEKDAY) == 0) {
        node = new(std::nothrow) NodeWhatWeekday(id, name, type, desc, keymap);
    } else if (strcasecmp(type.c_str(), NODE_MAKECALL) == 0) {
        node = new(std::nothrow) NodeMakeCall(id, name, type, desc, keymap);
    }

    if (node && (!node->load_other())) {
        delete node;
        node = NULL;
    }

    return node;
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
