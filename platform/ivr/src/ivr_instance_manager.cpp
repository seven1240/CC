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

#include <utility>
#include <sys/time.h>
#include "ivr_instance_manager.h"
#include "lock.h"
#include "tools.h"
#include "common.h"

pthread_mutex_t IvrInstanceManager::_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t IvrInstanceManager::_uuid_map_mutex = PTHREAD_MUTEX_INITIALIZER;

IvrInstanceManager::IvrInstanceManager() {
}

IvrInstanceManager::~IvrInstanceManager() {
}


IvrInstanceManager* IvrInstanceManager::get_instance() {
    static IvrInstanceManager mgr;
    return &mgr;
}

int32_t IvrInstanceManager::init() {
    return IVR_SUCCESS;
}

int32_t IvrInstanceManager::destroy() {
    iterator itr;

    ::lock_t lock(_mutex);

    if (lock.locked()) {
        for (itr = _sid_dynres_map.begin(); itr != _sid_dynres_map.end(); ++itr) {
            ivr_event_queue_t* queue = itr->second.event_queue;

            if (NULL != queue) {
                ivr_base_event_t* event;

                while (!queue->empty()) {
                    event = queue->front();

                    if (NULL != event) {
                        delete event;
                    } else {
                        IVR_WARN("event should not be null, plese check");
                    }

                    queue->pop();
                }
            } else {
                IVR_WARN("queue should not be null, plese check");
            }

            //  sem_t* sem = itr->second.sem;
            //  if (NULL != sem) {
            //      sem_destroy(sem);
            //      sem_init(sem, 0, 0);
            //  }
        }

        _sid_dynres_map.clear();
        return IVR_SUCCESS;
    } else {
        IVR_WARN("locked failure");
        return -1;
    }
}

int32_t IvrInstanceManager::create_ivr_instance(int32_t type, fw_id_t freeswith_no,
        ivr_session_id_t* id, session_dynamic_resource_t dynmic_resoure, const string& uuid) {
    if (NULL == id) {
        IVR_WARN("ivr_session_id_t pointer `id' is null");
        return -1;
    }

    if (NULL == dynmic_resoure.event_queue) {
        IVR_WARN("dynmic_resource's event_queue pointer should not be null");
        return -1;
    }

    if (NULL == dynmic_resoure.timer) {
        IVR_WARN("dynmic_resoure's timer pointer should not be null");
        return -1;
    }

    //    if (NULL == dynmic_resoure.sem) {
    //        IVR_WARN("dynmic_resoure's sem pointer should not be null");
    //        return -1;
    //    }

    ivr_session_id_t sid = create_ivr_session_id(type, freeswith_no);
    *id = sid;

    {
        ::lock_t lock(_mutex);

        if (lock.locked()) {
            _sid_dynres_map.insert(std::make_pair(sid, dynmic_resoure));
            _transagent_valid.insert(std::make_pair(sid, false));
            IVR_DEBUG("insert a dynamic_resouce. sid %ld, queue size %lu , queue pointer %lu",
                      sid, dynmic_resoure.event_queue->size(), (uint64_t) dynmic_resoure.event_queue);
        } else {
            IVR_WARN("locked failure");
            return -1;
        }
    }
    return IVR_SUCCESS;
}

int32_t IvrInstanceManager::destroy_ivr_instance(ivr_session_id_t id) {
    iterator itr;

    ::lock_t lock(_mutex);

    if (lock.locked()) {
        itr = _sid_dynres_map.find(id);

        if (_sid_dynres_map.end() == itr) {
            return -1; // -1¼ûÏêÉè
        }

        ivr_event_queue_t* queue = itr->second.event_queue;

        if (NULL == queue) {
            IVR_WARN("queue should not be null");
            return -1;
        }

        ivr_base_event_t* event;

        while (!queue->empty()) {
            event = queue->front();

            if (NULL != event) {
                delete event;
            } else {
                IVR_WARN("event should not be null, plese check");
            }

            queue->pop();
        }

        _sid_dynres_map.erase(itr);

        remove_uuid(id);

        remove_tav(id);

        _transagent_valid.erase(id);

        return IVR_SUCCESS;
    } else {
        IVR_WARN("locked failure");
        return -1;
    }
}

bool IvrInstanceManager::search_ivr_instance(ivr_session_id_t id) {
    iterator itr;

    ::lock_t lock(_mutex);

    if (lock.locked()) {
        itr = _sid_dynres_map.find(id);
        return _sid_dynres_map.end() != itr;
    } else {
        IVR_WARN("locked failure");
        return false;
    }
}

int32_t IvrInstanceManager::put_ivr_event(ivr_base_event_t* event) {
    if (NULL == event) {
        IVR_WARN("ivr_base_event_t pointer `event' is null");
        return -1;
    }

    ivr_session_id_t id = event->sessionId;

    iterator itr;
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        //IVR_DEBUG("put_ivr_event session id %ld", id);
        IVR_DEBUG("uuid map size: %lu", _uuid_sid_map.size());
        itr = _sid_dynres_map.find(id);

        if (_sid_dynres_map.end() == itr) {
            IVR_DEBUG("Threre is no session id: %ld in _busy_event_map", id);
            return -1;
        }

        //IVR_DEBUG("put_ivr_event find session id %ld, event queue pointer %p", itr->first, itr->second.event_queue);

        ivr_event_queue_t* queue = itr->second.event_queue;
        //        sem_t *sem = itr->second.sem;

        if (NULL == queue) {
            IVR_WARN("queue should not be null");
            return -1;
        }

        //       if (NULL == sem) {
        //           IVR_WARN("sem should not be null");
        //           return -1;
        //       }

        try {
            IVR_DEBUG("event type: %d", event->evt_type);
            queue->push(event);
            IVR_DEBUG("success to put an ivr event to queue. queue: %p", queue);
            //           sem_post(itr->second.sem);
            return IVR_SUCCESS;
        } catch (std::bad_alloc& e) {
            IVR_WARN("No more momery");
            return -1;
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }
}

int32_t IvrInstanceManager::get_ivr_event(ivr_session_id_t id, ivr_base_event_t** event) {
    if (NULL == event) {
        IVR_WARN("param `event' is null");
        return -1;
    }

    //IVR_DEBUG("before lock");
    iterator itr;
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        //IVR_DEBUG("locked");
        itr = _sid_dynres_map.find(id);

        if (_sid_dynres_map.end() == itr) {
            IVR_DEBUG("Threre is no session id: %ld in _sid_dynres_map", id);
            return -1;
        }

        ivr_event_queue_t* queue = itr->second.event_queue;

        if (NULL == queue) {
            IVR_WARN("queue should not be null");
            return -1;
        }

        //IVR_DEBUG("before get event from queue. queue: %p", queue);
        if (NULL == queue) {
            return -1;
        }

        if (queue->size() > 0) {
            *event = queue->front();
            queue->pop();

            if (NULL == *event) {
                IVR_WARN("ivr event should not be null");
                return -1;
            } else {
                return IVR_SUCCESS;
            }
        } else {
            return -1;
        }
    } else {
        IVR_WARN("locked failure");
        return -1;
    }
}

int32_t IvrInstanceManager::clear_event_queue(ivr_session_id_t id) {
    iterator itr;
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        itr = _sid_dynres_map.find(id);

        if (_sid_dynres_map.end() == itr) {
            IVR_DEBUG("Threre is no session id: %ld in _sid_dynres_map", id);
            return -1;
        }

        ivr_event_queue_t* queue = itr->second.event_queue;

        if (NULL != queue) {
            ivr_base_event_t* event;

            while (!queue->empty()) {
                event = queue->front();

                if (NULL != event) {
                    delete event;
                } else {
                    IVR_WARN("event should not be null, plese check");
                }

                queue->pop();
                return IVR_SUCCESS;
            }
        } else {
            IVR_WARN("queue should not be null");
            return -1;
        }

    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

ivr_session_id_t IvrInstanceManager::create_ivr_session_id(int32_t type, int32_t freeswitch_no) {
    ivr_session_id_t id;

    uint64_t time = ivr_tools_t::get_timestamp_ms();
    id = MAKE_IVR_SESSION_ID(type, freeswitch_no, time);
    return id;
}

bool IvrInstanceManager::check_uuid(const std::string& uuid, ivr_session_id_t& sid) {
    uuid_sid_iterator itr;

    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        itr = _uuid_sid_map.find(uuid);

        if (_uuid_sid_map.end() != itr) {
            sid = itr->second;
            return true;
        } else {
            return false;
        }
    } else {
        IVR_WARN("locked failure");
        return false;
    }
}

int32_t IvrInstanceManager::add_uuid(ivr_session_id_t sid, const std::string& uuid) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        _uuid_sid_map.insert(std::make_pair(uuid, sid));
        return IVR_SUCCESS;
    } else {
        IVR_WARN("locked failure");
        return -1;
    }
}

int32_t IvrInstanceManager::add_channel_info(const std::string& uuid, const channel_info_t& info) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        _uuid_info_map.insert(std::make_pair(uuid, info));
        IVR_TRACE("add channel info of callid(%s): callsource(%s) channel_name(%s) channel_id(%s)",
                  uuid.c_str(), info.callsource.c_str(), info.channel_name.c_str(), info.channel_id.c_str());
        return IVR_SUCCESS;
    } else {
        IVR_WARN("locked failure");
    }

    return -1;
}

int32_t IvrInstanceManager::remove_uuid(const std::string& uuid) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        _uuid_sid_map.erase(uuid);
        return IVR_SUCCESS;
    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

int32_t IvrInstanceManager::remove_uuid(ivr_session_id_t sid) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {

        uuid_sid_iterator itr;
        uuid_sid_iterator tmp;

        itr = _uuid_sid_map.begin();

        while (itr != _uuid_sid_map.end()) {
            tmp = itr;
            ++tmp;
            //            tmp = ++itr;

            if (itr->second == sid) {
                if (_uuid_info_map.erase(itr->first) != 0) {
                    IVR_DEBUG("earse uuid channel information");
                }

                _uuid_sid_map.erase(itr);
                IVR_DEBUG("erase uuid");
            }

            itr = tmp;
        }

    } else {
        IVR_WARN("locked failure");
        return -1;
    }

    return IVR_SUCCESS;
}

void IvrInstanceManager::mark_transagent(ivr_session_id_t sid, bool valid) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        tav_iterator iter = _transagent_valid.find(sid);

        // if found, set value
        if (iter != _transagent_valid.end()) {
            iter->second = valid;
            IVR_TRACE("(%s) ivr session id (%lu)s queue", valid ? "disable" : "enable", sid);
        } else {
            IVR_WARN("not found ivr sessiond id %lu", sid);
        }
    } else {
        IVR_WARN("locked failure");
    }
}

int32_t IvrInstanceManager::get_channel_info(const std::string& uuid, channel_info_t& info) {
    ::lock_t lock(_mutex);

    if (lock.locked()) {
        cinfo_iterator iter = _uuid_info_map.find(uuid);

        if (iter != _uuid_info_map.end()) {
            info = iter->second;
            IVR_TRACE("get callid(%s)'s channel info!", uuid.c_str());
            return IVR_SUCCESS;
        } else {
            IVR_TRACE("not found callid(%s)'s channel information!", uuid.c_str());
        }
    } else {
        IVR_WARN("locked failure");
    }

    return -1;
}

bool IvrInstanceManager::is_transagent(ivr_session_id_t sid) {
    ::lock_t lock(_uuid_map_mutex);

    if (lock.locked()) {
        tav_iterator iter = _transagent_valid.find(sid);

        // if found, retrun value
        if (iter != _transagent_valid.end()) {
            return iter->second;
        } else {
            IVR_WARN("not found ivr sessiond id %lu", sid);
        }
    } else {
        IVR_WARN("locked failure");
    }

    return false;
}

int32_t IvrInstanceManager::remove_tav(ivr_session_id_t sid) {
    tav_iterator iter = _transagent_valid.find(sid);

    if (iter != _transagent_valid.end()) {
        _transagent_valid.erase(iter);
    } else {
        IVR_WARN("not found ivr sessiond id %lu", sid);
        return -1;
    }

    return 0;
}
