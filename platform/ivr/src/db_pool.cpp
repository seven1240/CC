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

#include "db_pool.h"
#include "lock.h"
#include "exception.h"

DBPool::DBPool() {
    _id_conn_map.clear();
}

DBPool::~DBPool() {
    map<int32_t, DBContainer*>::iterator it = _id_conn_map.begin();

    for (; it != _id_conn_map.end(); ++it) {
        DBContainer* container = it->second;
        delete container;
        container = NULL;
        it->second = NULL;
    }

    _id_conn_map.clear();
}

int32_t DBPool::create_container_to_pool(uint32_t id, string& host, string& user, string& passwd,
        uint32_t conn_num, uint32_t timeout) {
    static mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    if (_id_conn_map.find(id) != _id_conn_map.end()) {
        //已经存在相同的标识，则直接返回
        return FAILURE;
    }

    std::auto_ptr<DBContainer> db_container(new(std::nothrow) DBContainer());

    if (db_container.get() != NULL
            && db_container->create_container(driver, host, user, passwd, conn_num) == SUCCESS) {
        _id_conn_map[id] = db_container.release();
        return SUCCESS;
    }

    return FAILURE;
}

Connection* DBPool::get_connection(uint32_t id, uint32_t timeout) {
    map<int32_t, DBContainer*>::iterator it = _id_conn_map.find(id);

    if (it != _id_conn_map.end() && NULL != it->second) {
        return it->second->get_connection();
    }

    return NULL;
}

void DBPool::free_connection(uint32_t id, Connection* conn) {
    map<int32_t, DBContainer*>::iterator it = _id_conn_map.find(id);

    if (it != _id_conn_map.end() && NULL != it->second) {
        it->second->free_connection(conn);
    }
}

DBContainer::DBContainer() {
    _idle_conn_vec.clear();
    _busy_conn_set.clear();
    _conn_num = 0;

    pthread_mutex_init(&_mutex, NULL);
}

DBContainer::~DBContainer() {
    {
        ::lock_t lock(_mutex);

        if (lock.locked()) {
            int32_t len = _idle_conn_vec.size() - 1;

            while (len >= 0) {
                Connection* conn = _idle_conn_vec[len];

                if (conn) {
                    if (!conn->isClosed()) {
                        conn->close();
                    }

                    delete conn;
                    conn = NULL;
                }

                _idle_conn_vec[len] = NULL;

                --len;
            }

            _idle_conn_vec.clear();

            for (set<Connection*>::iterator it = _busy_conn_set.begin();
                    it != _busy_conn_set.end(); ++it) {

                Connection* conn = *it;

                if (conn) {
                    if (!conn->isClosed()) {
                        conn->close();
                    }

                    delete conn;
                    conn = NULL;
                }
            }

            _busy_conn_set.clear();

            _conn_num = 0;
        }
    }
    pthread_mutex_destroy(&_mutex);
}

int32_t DBContainer::create_container(mysql::MySQL_Driver* driver, string& host, string& user,
                                      string& passwd, uint32_t conn_num) {
    _conn_num = 0;
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        _connection_properties["hostName"] = host;
        _connection_properties["userName"] = user;
        _connection_properties["password"] = passwd;
        _connection_properties["CLIENT_MULTI_RESULTS"] = true; //支持存储过程返回数据集

        for (uint32_t i = 0; i < conn_num; i++) {
            Connection* conn = NULL;

            try {
                conn = driver->connect(_connection_properties);  // 创建数据库连接
                _idle_conn_vec.push_back(conn);
                ++_conn_num;
            } catch (...) {
                IVR_FATAL("Connect db failure host=%s user=%s pwd=%s",
                          host.c_str(), user.c_str(), passwd.c_str());
                return FAILURE;
            }
        }

        if (_conn_num == conn_num) {
            sem_init(&_sem_conn, 0, conn_num);
        }

        return ((_conn_num == conn_num) ? SUCCESS : FAILURE);
    } else {
        return FAILURE;
    }
}

Connection* DBContainer::get_connection() {
    Connection* conn = NULL;

    sem_lock_t lock_conn(_sem_conn);

    if (!lock_conn.wait()) {
        return NULL;
    }

    ::lock_t lock(_mutex);

    if (!lock.locked()) {
        return NULL;
    }

    if (_idle_conn_vec.size() > 0) {
        conn = _idle_conn_vec.back();
        _idle_conn_vec.pop_back();

        if (NULL == conn || conn->isClosed()) {
            try {
                mysql::MySQL_Driver* driver = (mysql::MySQL_Driver*)(conn->getDriver());
                delete conn;
                conn = driver->connect(_connection_properties);
            } catch (...) {
                conn = NULL;
                _busy_conn_set.insert(conn);
                IVR_WARN("Connect db failure !");
                return NULL;
            }
        }

        _busy_conn_set.insert(conn);
    } else {
        return NULL;
    }

    return conn;
}

void DBContainer::free_connection(Connection* conn) {
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        _busy_conn_set.erase(conn);
        _idle_conn_vec.push_back(conn);
    }

    sem_lock_t lock_conn(_sem_conn);
    lock_conn.post();
}
