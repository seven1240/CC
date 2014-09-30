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

#ifndef  __FS_STRUCT_H_
#define  __FS_STRUCT_H_


#include "common.h"

enum fs_call_direction_t {
    FCD_UNKNOWN,
    FCD_OUTBOUND,
    FCD_INBOUND
};

enum fs_call_state_t {
    FCS_UNKNOWN,
    FCS_RING,
    FCS_EARLY,
    FCS_ANSWERED
};

enum fs_event_data_t {
    EDT_UNKNOWN,
    EDT_NORMAL,
    EDT_HEARTBEAT
};

typedef struct event_data_normal {
    char uuid[LEN_64 + 1];
    char caller_no[LEN_64 + 1];
    char called_no[LEN_64 + 1];
    char channel_name[LEN_64 + 1];
    char deviceno[LEN_64 + 1];

    fs_call_direction_t call_direction;
    fs_call_state_t call_state;

    char application[LEN_32 + 1];
    char application_data[LEN_64 + 1];
    char application_resp[LEN_128 + 1];

    char other_uuid[LEN_64 + 1];
    char other_caller_no[LEN_64 + 1];
    char other_called_no[LEN_64 + 1];
    char other_channel_name[LEN_64 + 1];
    char other_deviceno[LEN_64 + 1];

    char ivr_data[LEN_128 + 1];

    char reason[LEN_128 + 1];
} event_data_normal_t;

typedef struct event_data_heartbeat {
    uint32_t cur_session;
    uint32_t all_session;
    uint32_t use_session;
    uint32_t cpu_idle;
} event_data_heartbeat_t;

typedef struct fs_event {
    uint64_t timestamp;
    char name[LEN_64 + 1];
    uint64_t sessionid;       /**< eventrecevier的时候更新*/
    uint64_t callid;          /**< eventrecevier的时候更新*/

    fs_event_data_t datatype;

    union {
        event_data_normal_t normal;
        event_data_heartbeat_t heartbeat;
    } event_data;

    fs_event() {
        timestamp = 0;
        name[0] = '\0';
        datatype = EDT_UNKNOWN;
    }

} fs_event_t;


#endif  //__FS_STRUCT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
