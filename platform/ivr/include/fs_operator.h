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

#ifndef  __FS_OPERATOR_H_
#define  __FS_OPERATOR_H_

#include <esl.h>

#include "common.h"

/**
 * @brief fs操作类
 *   detail description
 *
 */
class fs_operator_t {
protected:
    const static uint32_t MAX_DATA_SIZE = 255;
public:
    typedef struct _fs_event_t {
        enum  event_t {
            EV_ANSWER_SUCC,

            EV_HANGUP_SUCC,

            EV_PLAY_SUCC,
            EV_COLLECT_SUCC,

            EV_DISCONNECT,
            EV_DISCONNECT_OTHER,
            EV_DISCONNECT_THIRD,
            EV_BRIDGE_SUCC,
            EV_RECORD_BEGIN_SUCC,
            EV_RECORD_END_SUCC,
            EV_TIMEOUT,
            EV_UNKNOWN        ///<  未知
        };
        enum media_response_t {
            MEDIA_SUCC,
            MEDIA_FILE_NOEXIST,
            MEDIA_ERR
        };
        event_t event;
        media_response_t media_resp;
        char data[MAX_DATA_SIZE + 1];
    } fs_event_t;
public:

    /**
     * @brief 连接fs
     *
     * @param [in/out] handle   : esl_handle_t&
     * @param [in/out] ip   : const char*
     * @param [in/out] port   : uint32_t
     * @param [in/out] user   : const char*
     * @param [in/out] pswd   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/01 10:04:38
    **/
    static bool connect(esl_handle_t& handle,
                        const char* ip, uint32_t port,
                        const char* user, const char* pswd);

    /**
     * @brief 获取变量的值
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] var   : const char*
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/06 18:51:38
    **/
    static std::string get_variable(esl_handle_t* handle, const char* var);

    /**
     * @brief 断开和fs的连接
     *
     * @param [in/out] handle   : esl_handle_t&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/01 10:04:43
    **/
    static inline bool disconnect(esl_handle_t& handle) {
        bool ret = (esl_disconnect(&handle) == ESL_SUCCESS);
        bzero(&handle, sizeof(esl_handle_t));

        return ret;
    }

    /**
     * @brief 订阅事件
     *
     * @param [in/out] handle   : esl_handle_t&
     * @param [in/out] type   : esl_event_type_t
     * @param [in/out] val   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/09/01 10:52:50
    **/
    static inline bool events(esl_handle_t& handle, esl_event_type_t type, const char* val) {
        return esl_events(&handle, type, val) == ESL_SUCCESS;
    }

    /**
     * @brief 应答
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:39:48
     **/
    static bool answer(esl_handle_t* handle, const std::string& callid);

    /**
     * @brief
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] caller   : const std::string&
     * @param [in/out] called   : const std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/10/12 12:06:24
    **/
    static bool bridgeex(esl_handle_t* handle,
                         const std::string& callid,
                         const std::string& caller, const std::string& called,
                         bool external, bool usebgm, const std::string& bgmfile);


    /**
     * @brief inband 的dtmf收号操作
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/10/11 21:20:41
    **/
    static bool startdtmf(esl_handle_t* handle, const std::string& callid);

    /**
     * @brief inband 的dtmf收号操作
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/10/11 21:20:41
    **/
    static bool stopdtmf(esl_handle_t* handle, const std::string& callid);

    /**
     * @brief 挂机
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:40:32
     **/
    static bool hangup(esl_handle_t* handle, const string& callid);
    /**
     * @brief 放音
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const string&
     * @param [in/out] playfile   : const string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:40:38
     **/
    static bool playback(esl_handle_t* handle,
                         const string& callid, const string& playfile);

    /**
     * @brief
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : string&
     * @param [in/out] playfile   : string&
     * @param [in/out] min   : uint32_t
     * @param [in/out] max   : uint32_t
     * @param [in/out] timeout   : uint32_t 以s为单位
     * @param [in/out] term   : string 结束符
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:44:53
    **/
    static bool collect(esl_handle_t* handle,
                        const std::string& callid, const std::string& playfile,
                        uint32_t min, uint32_t max, uint32_t timeout,
                        const std::string term);
    /**
     * @brief 放音收号
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : string&
     * @param [in/out] playfile   : string&
     * @param [in/out] min   : uint32_t
     * @param [in/out] max   : uint32_t
     * @param [in/out] tries   : uint32_t
     * @param [in/out] timeout   : uint32_t
     * @param [in/out] term   : string&
     * @param [in/out] invalidfile   : string&
     * @param [in/out] varname   : string
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:40:49
     **/
    static bool play_and_get_digits(esl_handle_t* handle,
                                    const std::string& callid, const std::string& playfile,
                                    uint32_t min, uint32_t max,
                                    uint32_t tries, uint32_t timeout,
                                    const std::string& term,
                                    const std::string& invalidfile);

    /**
     * @brief 外呼
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : string&
     * @param [in/out] called_number   : string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:42:33
     **/
    static bool dial(esl_handle_t* handle,
                     std::string& callid, const std::string& called,
                     const std::string& caller, uint32_t timeout, bool external);

    /**
     * @brief 电话搭接
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid1   : const std::string&
     * @param [in/out] callid2   : const std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:43:49
     **/
    static bool bridge(esl_handle_t* handle,
                       const std::string& callid1, const std::string& callid2);
    /**
     * @brief 录音
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : const std::string&
     * @param [in/out] recordfile   : const std::string&
     * @return  bool
     * @retval
     * @see
     * @note 目前无创建目录的功能，需要升级
     *       是一个阻塞的函数，record之后无法继续进行其他的操作
     * @author chenyuzhen
     * @date 2011/08/29 11:44:04
     **/
    static bool record(esl_handle_t* handle,
                       const std::string& callid,
                       const std::string& recordpath,
                       const std::string& recordfile);

    /**
     * @brief 获取呼叫数据
     *
     * @param [in/out] handle   : esl_handle_t*
     * @param [in/out] callid   : string&
     * @param [in/out] varname   : string&
     * @return  const char*
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:44:11
     **/
    //static const char* uuid_getvar(esl_handle_t* handle,
    //        const string& callid, const string& varname);

    /**
     * @brief 获取主被叫信息
     *
     * @param [in/out] hdl   : esl_handle_t*
     * @param [in/out] caller   : std::string&
     * @param [in/out] called   : std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/31 14:34:17
    **/
    static bool get_callercalled(esl_handle_t& hdl, std::string& caller, std::string& called);

    /**
     * @brief 获取callid
     *
     *
     * @param [in/out] hdl   : esl_handle_t*
     * @param [in/out] callid   : std::string&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/31 14:40:59
    **/
    static bool get_callid(esl_handle_t& hdl, std::string& callid);

protected:
    const static char* CMD_ANSWER;
    const static char* CMD_HANGUP;
    const static char* CMD_PLAY;
    const static char* CMD_COLLECT;
    const static char* CMD_PLAY_WITH_COLLECT;
    const static char* CMD_DIAL;
    const static char* CMD_RECORD;
    const static char* CMD_BRIDGE;
    const static char* CMD_GETVAR;
    const static char* CMD_END;
    const static char* CMD_UNDEF;
    const static char* CMD_SET;
    const static char* CMD_MKDIR;
    const static char* CMD_CREATEUUID;
    const static char* CMD_STARTDTMF;
    const static char* CMD_STOPDTMF;
    const static char* CMD_FLUSH_DTMF;
    const static char* CMD_BRIDGEEX;

    const static char* RESULT_OK;
    const static char* REPLY_TEXT;
    const static char* CONTENT_TYPE;
    const static char* PLAIN;
    const static char* APPLICATION;
    const static char* APP_RESP;
    const static char* DISCONNECT;

    const static char* MEDIA_FILE_PLAYED;
    const static char* MEDIA_FILE_NOEXIST;

    const static char* CH_ST_HANGUP;
    const static char* CH_ST;

    const static char* FS_VAR_TMP;  ///< 事件临时缓冲区名称

    const static char* FS_VAR_PREFIX;

    const static char* FS_DIGIT_RESULT_SUCC;
    const static char* FS_DIGIT_RESULT_FAIL;
    const static char* FS_DIGIT_RESULT_TO;
    const static char* FS_VAR_DIGIT_READ;

private:
    /**
     * @brief 判断esl的response是否成功
     *
     * @param [in/out] result   : const char*
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 11:38:23
     **/
    static inline bool check_result(const char* result);
public:

    /**
     * @brief
     *
     * @param [in] handle   : esl_handle_t*
     * @param [in] timeout   : int32_t -1:无超时,>0则超时n秒
     * @param [in/out] : fs_event_t 事件类型
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/08/29 14:42:22
    **/
    static bool check_event(esl_handle_t* handle, int32_t timeout, fs_event_t& event);

    /**
     * @brief 创建uuid，外呼的时候用到
     *
     * @param [in/out] handle   : esl_handle_t&
     * @return  std::string
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2011/10/11 20:24:03
    **/
    static std::string create_uuid(esl_handle_t& handle);
};














#endif  //__INCLUDE/FS_OPERATOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
