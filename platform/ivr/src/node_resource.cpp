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

#include "node_resource.h"

NodeResource::NodeResource(const uint32_t id, const string& name,
                           const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {

}

NodeResource::~NodeResource(void) {
}

bool NodeResource::load_other() {
    return NodeBase::load_other()
           && valid_str(_key_map, PARAM_CALLID, _callid);
}

const char* NodeResource::EXIT_USER_HANGUP = "_userhangup";
const char* NodeResource::EXIT_INTERRUPT = "_userinterrupt";
const char* NodeResource::EXIT_FILENOTFOUND = "_filenotfound";

const char* NodeResource::PARAM_CALLID = "callid";
