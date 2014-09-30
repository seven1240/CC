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

#ifndef _DB_POOL_H_
#define _DB_POOL_H_

#include "common.h"
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "statement.h"

using namespace sql;

class DBContainer {
public:
    DBContainer();
    virtual ~DBContainer();

    int32_t create_container(mysql::MySQL_Driver* driver, string& host, string& user,
                             string& passwd, uint32_t conn_num);

    Connection* get_connection();
    void free_connection(Connection* conn);

private:
    vector<Connection*> _idle_conn_vec;
    set<Connection*> _busy_conn_set;

    sql::ConnectOptionsMap _connection_properties;

    pthread_mutex_t _mutex;
    sem_t _sem_conn;
    uint32_t _conn_num;
};


class DBPool {
public:
    DBPool();
    virtual ~DBPool();

public:
    int32_t create_container_to_pool(uint32_t id, string& host, string& user, string& passwd,
                                     uint32_t conn_num, uint32_t timeout);

    Connection* get_connection(uint32_t id, uint32_t timeout = 0);
    void free_connection(uint32_t id, Connection* conn);

private:
    map<int32_t, DBContainer*> _id_conn_map;
};

#endif
