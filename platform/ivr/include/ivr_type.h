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

#ifndef _IVR_TYPE_H_
#define _IVR_TYPE_H_

#define MAKE_IVR_SESSION_ID(type, fw_no, time) \
    uint64_t( \
            ((uint64_t)type) & 0x1 | \
            (((uint64_t)fw_no) & 0x7f) << 1 | \
            (((uint64_t)time) & 0xfffffff) << 8 \
            )

#define IVR_SESSION_ID_TYPE(ivr_session_id) \
    uint64_t(ivr_session_id & 0x1)

#define IVR_SESSION_ID_FWNO(ivr_session_id) \
    uint64_t((ivr_session_id >> 1) & 0x7f)

#define IVR_SESSION_ID_TIME(ivr_session_id) \
    uint64_t((ivr_session_id >> 8) & 0xfffffff)

#endif // _IVR_TYPE_H_

