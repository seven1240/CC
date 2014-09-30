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

#ifndef  __IMS_CONF_H_
#define  __IMS_CONF_H_

#include "ims_core.h"
#include <list>

/**
* @brief 服务类型
*
*/
enum ims_conf_service_type_t {
    ICST_MAIN,        ///<  主服务
    ICST_MONITOR,     ///<  监控服务
    ICST_CONFIG       ///<  配置服务
};

/**
* @brief 服务通用配置参数
*
*/
enum ims_conf_param_type_t {
    ICPT_MAXSESSION,      ///< 最大session数
    ICPT_BGCCPOOLSIZE     ///< bgcc线程池大小
};

/**
* @brief 支持的客户端类型
*
*/
enum ims_conf_client_type_t {
    ICCT_IVR,             ///<  IVR
    ICCT_CONFIG,          ///<  配置
    ICCT_ACD,             ///<  ACD
    ICCT_MONITOR          ///<  监控
};

/**
* @brief 主服务配置信息
*
*/
typedef struct ims_conf_server {
    ims_conf_server(uint32_t ip_, uint32_t port_): ip(ip_), port(port_) {}
    uint32_t ip;
    uint32_t port;
} ims_conf_server_t;

/**
* @brief 授权配置信息
*
*/
typedef struct ims_conf_acl_node {
    ims_conf_acl_node(uint32_t ip_, uint32_t mask_, uint32_t bit_):
        ip(ip_), mask(mask_), bit(bit_) {}
    uint32_t ip;
    uint32_t mask;
    uint32_t bit;
} ims_conf_acl_node_t;

typedef struct ims_conf_log {
    uint32_t level;
    uint32_t size;
    char path[LEN_256 + 1];
    ims_conf_log() {
        level = 0;
        size = 0;
        path[0] = '\0';
        path[LEN_256] = '\0';
    }
} ims_conf_log_t;

/**
* @brief gateway 支持的DTMF类型
*
*/
enum dtmf_type_t {
    DTMF_INBAND,      ///<  带内
    DTMF_OTHER        ///<  带外
};

/**
* @brief Gateway配置信息
*
*/
typedef struct ims_conf_gw_node {
    uint32_t id;    /**< no       */
    uint32_t ip;    /**< ip       */
    uint32_t port;  /**< port     */
    uint32_t max_conn;
    char user[LEN_64 + 1];      /**< auth user*/
    char pswd[LEN_64 + 1];
    dtmf_type_t dtmf;
    ims_conf_gw_node(): id(0), ip(0), port(0), max_conn(0) {
        user[0] = '\0';
        pswd[0] = '\0';

        user[LEN_64] = '\0';
        pswd[LEN_64] = '\0';
        dtmf = DTMF_OTHER;
    }
} ims_conf_gw_node_t;

/**
* @brief 路由类型
*
*/
enum ims_conf_route_type_t {
    ICRT_OUTBOUND,        ///< 外乎路由
    ICRT_INBOUND          ///< 呼入路由
};


/**
* @brief 路由配置信息
*
*/
typedef struct ims_conf_route_node {
    char name[LEN_64 + 1];            ///<  名称
    ims_conf_route_type_t type;       ///<  类型
    char field[LEN_64 + 1];           ///<  识别字段
    char expression[LEN_128 + 1];     ///<  识别的表达式
    char rule_disp_caller[LEN_64 + 1]; ///<  外乎显示主叫
    char rule_call_caller[LEN_64 + 1]; ///<  真实主叫
    char rule_call_called[LEN_64 + 1]; ///<  真实被叫
    ims_conf_route_node() {
        name[0] = '\0';
        field[0] = '\0';
        expression[0] = '\0';
        rule_disp_caller[0] = '\0';
        rule_call_caller[0] = '\0';
        rule_call_called[0] = '\0';

        name[LEN_64] = '\0';
        field[LEN_64] = '\0';
        expression[LEN_128] = '\0';
        rule_disp_caller[LEN_64] = '\0';
        rule_call_caller[LEN_64] = '\0';
        rule_call_called[LEN_64] = '\0';
    }
} ims_conf_route_node_t;

/**
* @brief 整体配置信息
*
*/
struct ims_conf {
    std::map<ims_conf_service_type_t, ims_conf_server_t* > service;                 ///<  支持的服务
    std::map<ims_conf_param_type_t, const char*> param;                             ///<  全局配置参数
    std::map<ims_conf_client_type_t, std::list<ims_conf_acl_node_t*> > clients;     ///<  支持的客户端
    ims_conf_log log;                                 ///<  通用配置信息
    bool gw_log;                                      ///< 是否打印gateway日志
    std::list<ims_conf_gw_node_t*> gateway;           ///< gateway列表
    std::list<ims_conf_route_node_t*> route;          ///< 路由规则列表

    ims_conf() {
        gw_log = false;
    }
    ~ims_conf() {
    }

    /**
     * @brief 获取指定FW的DTMF类型
     *
     * @param [in/out] fsno   : uint32_t
     * @param [in/out] type   : dtmf_type_t&
     * @return  void
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2013/01/09 17:58:20
    **/
    void get_gwdtmftype(uint32_t fsno, dtmf_type_t& type);
};

typedef struct ims_conf ims_conf_t;


#endif  //__IMS_CONF_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
