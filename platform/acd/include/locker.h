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


#pragma once

#include "const_define.h"

class SingleRWLocker {
private:
    bgcc::RWLock* m_pRWLock;
    bool m_isLocked;  // ÊÇ·ñ¼ÓËø

public:
    inline SingleRWLocker(bgcc::RWLock* pRWLock, bool isWriteLock = false);
    inline ~SingleRWLocker();
    inline bool isLocked();
};

SingleRWLocker::SingleRWLocker(bgcc::RWLock* pRWLock, bool isWriteLock) : m_pRWLock(pRWLock),
    m_isLocked(false) {
    if (isWriteLock) {
        m_isLocked = (0 == m_pRWLock->get_wrlock());
    } else {
        m_isLocked = (0 == m_pRWLock->get_rdlock());
    }
}

SingleRWLocker::~SingleRWLocker() {
    m_pRWLock->unlock();
    m_isLocked = false;
}

bool SingleRWLocker::isLocked() {
    return m_isLocked;
}
