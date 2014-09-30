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


#include "ims_core.h"


/**
* @brief 呼叫方向
*
*
*/
enum fs_call_direction_t {
    FCD_UNKNOWN,
    FCD_OUTBOUND,         /**< 呼出       */
    FCD_INBOUND           /**< 呼入       */
};

/**
* @brief 呼叫状态
*
*/
enum fs_call_state_t {
    FCS_UNKNOWN,
    FCS_RING,         /**< 振铃       */
    FCS_EARLY,        /**< 彩铃       */
    FCS_ANSWERED      /**< 应答       */
};

/**
* @brief fw 事件类型
*
*/
enum fs_event_data_t {
    EDT_UNKNOWN,
    EDT_NORMAL,       /**< 呼叫相关事件       */
    EDT_HEARTBEAT     /**< 心跳事件           */
};

/**
* @brief 呼叫相关事件
*
*/
typedef struct event_data_normal {
    char uuid[LEN_64 + 1];            /**< FW channel id  */
    char caller_no[LEN_64 + 1];       /**< 主叫号码       */
    char called_no[LEN_64 + 1];       /**< 被叫号码       */
    char channel_name[LEN_64 + 1];    /**< channel name   */
    char deviceno[LEN_64 + 1];        /**< 设备号码       */

    fs_call_direction_t call_direction; /**< 呼叫方向       */
    fs_call_state_t call_state;         /**< 呼叫状态       */

    char application[LEN_32 + 1];       /**< 产生事件的操作       */
    char application_data[LEN_64 + 1];  /**< 产生事件的参数       */
    char application_resp[LEN_128 + 1]; /**< 产生事件的操作结果   */

    char other_uuid[LEN_64 + 1];        /**< FW other channel id      */
    char other_caller_no[LEN_64 + 1];   /**< other channel 主叫号码   */
    char other_called_no[LEN_64 + 1];   /**< other channel 被叫号码   */
    char other_channel_name[LEN_64 + 1]; /**< other channel name       */
    char other_deviceno[LEN_64 + 1];    /**< other channel 设备号码   */

    char ims_data[LEN_128 + 1];         /**< IMS 在FW设置的数据 */

    char reason[LEN_128 + 1];           /**<  事件产生原因      */
} event_data_normal_t;

/**
* @brief 心跳事件
*
*/
typedef struct event_data_heartbeat {
    uint32_t cur_session;         /**< 当前会话个数     */
    uint32_t all_session;         /**< 累积会话个数     */
    uint32_t cpu_idle;            /**< 当前CPU IDLE     */
    volatile uint32_t used_times;               /**< used times between two heartbeats   */
} event_data_heartbeat_t;

/**
* @brief FreeSWITCH 事件
*   detail description
*
*/
typedef struct fs_event {
    uint64_t timestamp;       /**< 产生时间       */
    char name[LEN_64 + 1];    /**< 事件名称       */
    uint64_t sessionid;       /**< eventrecevier的时候更新*/
    uint64_t callid;          /**< eventrecevier的时候更新*/

    fs_event_data_t datatype; /**< 事件类型       */

    union {
        event_data_normal_t normal;       /**< type为 呼叫类 有效      */
        event_data_heartbeat_t heartbeat; /**< type 为 heatbeat 有效   */
    } event_data;

    fs_event() {
        timestamp = 0;
        name[0] = '\0';
        datatype = EDT_UNKNOWN;
    }

} fs_event_t;


#endif  //__FS_STRUCT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
