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

#ifndef _CONF_MANAGER_H_
#define _CONF_MANAGER_H_

#include "common.h"
#include "flow_manager.h"

/**
* @brief 配置加载类
*   detail description
*
*/
class ConfManager {
public:
    /**
     * @brief 构造函数
     *
     * @param [in/out] sys_file   : const std::string
     * @param [in/out] in_file   : const std::string
     * @param [in/out] auto_file   : const std::string
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:20:39
    **/
    ConfManager(const std::string sys_file,
                const std::string in_file,
                const std::string auto_file);
    /**
     * @brief 析构函数
     *
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:20:43
    **/
    virtual ~ConfManager();
    /**
     * @brief 加载系统配置配置
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:20:23
    **/
    int32_t load_conf();
    /**
     * @brief 计算呼入+呼出的通道数
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:20:12
    **/
    int32_t load_max_chan_num();
    /**
     * @brief 配置文件卸载
     *
     * @return  void
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:20:32
    **/
    void unload_conf();

    // reload conf file(inboud/autorun/threadcount/esllog)
    int32_t reload_conf(conf_reload_flag_t flag);
private:
    /**
     * @brief 加载系统配置
     *
     * @return  int32_t
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/26 15:19:56
    **/
    int32_t load_system_conf();
    /**
     * @brief 加载呼入相关的参数
     *
     * @return  int32_t
     * @retval
     * @see
     * @note 依赖于load_max_chan_num的提前调用去初始化文件
     * @author chenyuzhen
     * @date 2011/08/26 15:18:46
    **/
    int32_t load_inbound_conf(FlowManager& fm, inbound_conf_t& inconf);
    /**
     * @brief 加载自动呼出相关的参数
     *
     * @return  int32_t
     * @retval
     * @see
     * @note 依赖于load_max_chan_num的提前调用去初始化文件
     * @author chenyuzhen
     * @date 2011/08/26 15:19:15
    **/
    int32_t load_autorun_conf(FlowManager& fm, autorun_conf_t& autoconf);

    // load esllog flag
    int32_t load_esllog_conf(int32_t& enable);

    // load max count
    int32_t load_max_chan_num(uint32_t& max_inbound, uint32_t& max_autorun, uint32_t& max_autodial);
private:
    std::string _sys_file;        ///<  系统配置文件
    std::string _in_file;         ///<  呼入流程配置文件
    std::string _auto_file;       ///<  自启动流程配置文件
public:
    const static char* SCRIPT;    ///<  script常量
    const static char* FREESWITCH;///<  freeswitch常量
    const static char* CONN;      ///<  connection常量
    const static char* IMS;       ///<  ims
};

#endif
