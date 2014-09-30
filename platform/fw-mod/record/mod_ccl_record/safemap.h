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

#ifndef  __SAFEMAP_H_
#define  __SAFEMAP_H_

#include <map>
#include "lock.h"

template <typename key_type, typename val_type>
class safemap_t {

private:
    std::map<key_type, val_type> _m;
    pthread_rwlock_t    _rwlock;
    /**
     * @brief Ìí¼ÓÔªËØ
     *
     * @param [in/out] key   : const key_type&
     * @param [in/out] val   : const val_type&
     * @return  bool
     * @retval
     * @see
     * @note
     * @author chenyuzhen
     * @date 2012/03/06 17:47:29
     **/
public:
    bool put(const key_type& key, const val_type& val) {
        rw_lock_t lock(_rwlock, true);

        if (!lock.locked()) {
            return false;
        }

        if (_m.find(key) != _m.end()) {
            _m.erase(key);
        }

        _m.insert(std::pair<key_type, val_type>(key, val));

        return true;
    }

    bool get(const key_type& key, val_type& val) {
        rw_lock_t lock(_rwlock, true);

        if (!lock.locked()) {
            return false;
        }

        typename std::map<key_type, val_type>::iterator it = _m.find(key);

        if (_m.find(key) == _m.end()) {
            return false;
        }

        val = it->second;

        _m.erase(key);

        return true;
    }

    bool peek(const key_type& key, val_type& val) const {
        rw_lock_t lock(_rwlock);

        if (!lock.locked()) {
            return false;
        }

        typename std::map<key_type, val_type>::iterator it = _m.find(key);

        if (_m.find(key) == _m.end()) {
            return false;
        }

        val = it->second;
        return true;
    }


    size_t size() const {
        rw_lock_t lock(_rwlock);

        if (!lock.locked()) {
            return false;
        }

        return _m.size();
    }

};

#endif  //__SAFEMAP_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
