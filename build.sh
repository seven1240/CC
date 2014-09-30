#!/bin/bash

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      CC/LICENSE
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ROOT_DIR=`pwd`
PLAT_BASE=platform
PLAT_SVR="acd ivr ims agentproxy"

DEP_BASE=dep

INC_BASE=interface

RELEASE_BASE=`pwd`/release

clean()
{
    if [ -d ${RELEASE_BASE} ]; then 
        rm -fr ${RELEASE_BASE}; 
    fi 
    
    for d in ${PLAT_SVR}; do
        make -C ${PLAT_BASE}/$d clean;
    done
    
    make -C ${INC_BASE} clean
}

build()
{
    # 1. third party component
    # 2. interface
    # 3. platform

    cd ${DEP_BASE} && bash build.sh && cd ..
    
    cd ${ROOT_DIR} && make -C ${INC_BASE}
    
    for d in ${PLAT_SVR}; do
        make -C ${PLAT_BASE}/$d;

        if [ ! -d ${RELEASE_BASE}/$d ]; then 
            mkdir -p ${RELEASE_BASE}/$d; 
        fi

        cp -r ${PLAT_BASE}/$d/output/* ${RELEASE_BASE}/$d/
    done
        
    if [ ! -d ${RELEASE_BASE}/freeswitch ]; then 
        mkdir -p ${RELEASE_BASE}/freeswitch; 
    fi

    cp -r ${DEP_BASE}/freeswitch/output/*  ${RELEASE_BASE}/freeswitch/
}
    
case "$1" in
    build)
        build
        ;;
    clean)
        clean
        ;;
    *)
        echo "Usage: bash $0 {build|clean}"
        exit 1
        ;;
esac

exit 0
