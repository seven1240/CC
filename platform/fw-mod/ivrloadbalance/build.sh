#!/bin/sh

NOW_PATH=`pwd`

FS_BASE_PATH="../freeswitch/freeswitch-1.0.6"
FS_MOD_CPP_PATH="${FS_BASE_PATH}/src/mod/applications/mod_ivr_loadbalance"
#FS_MOD_CONF_PATH="${FS_BASE_PATH}/conf/dialplan"
#FS_DEFAULTXML_PATH="${FS_BASE_PATH}/conf/dialplan"
#FS_MODULESXML_PATH="${FS_BASE_PATH}/conf/autoload_configs"

#copy code
echo "===== COPY FILE ====="
if [ ! -d ${FS_MOD_CPP_PATH} ]; then
    echo "${FS_MOD_CPP_PATH} not exist, mkdir"
    mkdir -p ${FS_MOD_CPP_PATH}
fi
cp mod_ivr_loadbalance.cpp ${FS_MOD_CPP_PATH}
cp modules.conf ${FS_BASE_PATH}
#cp default.xml ${FS_DEFAULTXML_PATH}
#cp modules.conf.xml ${FS_MODULESXML_PATH}

#make
echo "===== MAKE ====="
#cd ${FS_BASE_PATH}
#./configure
make -C ${FS_BASE_PATH}
#make mod_ivr_loadbalance
#cd ${NOW_PATH}

#output
echo "===== OUTPUT ====="
if [ ! -d output ]; then
    echo "output not exist, mkdir"
    mkdir -p output
fi
echo "cp ${FS_MOD_CPP_PATH}/.libs/mod_ivr_loadbalance.so output"
cp ${FS_MOD_CPP_PATH}/.libs/mod_ivr_loadbalance.so output
echo "cp default.xml output"
cp default.xml output
echo "cp modules.conf.xml output"
cp modules.conf.xml output
echo "cp ivr_loadbalance.conf output"
cp ivr_loadbalance.conf output

