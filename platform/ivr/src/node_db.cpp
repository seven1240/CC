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

#include <exception.h>

#include "node_db.h"
#include "db_pool.h"
#include "common.h"

extern DBPool* g_dbpool;

NodeDB::NodeDB(const uint32_t id, const string& name,
               const string& type, const string& desc, const key_map_t& keymap)
    : NodeBase(id, name, type, desc, keymap) {
}

NodeDB::~NodeDB(void) {
}

NodeBase* NodeDB::run(base_script_t* param) {
    IVR_TRACE("%s", enter(param->name_var_map).c_str());

    Connection* conn = NULL;
    Statement* state = NULL;
    ResultSet* rs = NULL;
    const char* exit = EXIT_FAIL;

    conn = g_dbpool->get_connection(_connectid);

    if (conn) {
        state = conn->createStatement();
    } else {
        IVR_WARN("fetch connect failed");
        goto END;
    }

    if (!state) {
        IVR_WARN("create statement failed");
        goto FREE;
    }

    try {
        string sql;

        if (!parse_all(_sql, param->name_var_map, sql)) {
            IVR_WARN("parse all failed(%s)", _sql.c_str());
            goto FREE;
        }

        IVR_TRACE("sql = %s", sql.c_str());

        bool is_ret_rs = state->execute(sql.c_str());

        if (is_ret_rs) { //表示返回了结果集  select
            rs = state->getResultSet();

            //如果不做以下处理，执行返回结果集的存储过程会有异常：
            //HY000,Commands out of sync; you can't run this command now
            while (state->getMoreResults());

            map<string, variable_t>::iterator it = param->name_var_map.find(_rs_var_name);

            if (it == param->name_var_map.end()) {
                IVR_WARN("变量不存在");
                goto FREE;
            }

            if (it->second.type != RESULTSET) {
                IVR_WARN("变量类型不是RESULTSET");
                goto FREE;
            }

            sql::ResultSet* result = (sql::ResultSet*)(it->second.pvalue);

            if (result) {
                delete result->getStatement();
                delete result;
            }

            it->second.pvalue = rs;//在销毁变量的时候会整体销毁
            exit = EXIT_SUCC;
        } else { //表示未返回结果集  insert update delete
            int32_t num = state->getUpdateCount();

            if (num >= 0) {
                exit = EXIT_SUCC;
            }
        }
    } catch (sql::SQLException ex) {
        IVR_WARN("数据库查询失败(%s,%s)", ex.getSQLStateCStr(), ex.what());
        goto FREE;
    } catch (...) {
        IVR_WARN("数据库查询失败 抛出异常");
        goto FREE;
    }

FREE:
    g_dbpool->free_connection(_connectid, conn);
END:
    IVR_TRACE("%s exit from %s()",
              leave(param->name_var_map).c_str(), exit);
    return _exit_node_map[exit];
}

bool NodeDB::load_other() {
    valid_str(_key_map, PARAM_RSNAME, _rs_var_name); //不关心是否存在
    std::string tmp;

    if (NodeBase::load_other()
            && valid_str(_key_map, PARAM_SQL, _sql, false)
            && valid_str(_key_map, PARAM_CONNID, tmp)) {
        _connectid = atoi(tmp.c_str());

        return true;
    }

    return false;
}


std::string NodeDB::enter(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::enter(vars);
    ostm << "connid:" << _connectid << ",rsname:" << _rs_var_name << ",sql:" << _sql;
    return ostm.str();
}

std::string NodeDB::leave(const map<string, variable_t>& vars)const {
    ostringstream ostm;
    ostm << NodeBase::leave(vars);
    ostm << "connid:" << _connectid;
    return ostm.str();
}

const char* NodeDB::PARAM_CONNID = "connectid";
const char* NodeDB::PARAM_SQL = "sql";
const char* NodeDB::PARAM_RSNAME = "rsvarname";
