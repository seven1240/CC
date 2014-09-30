#!/bin/sh

NOW_PATH=`pwd`

FS_BASE_PATH="../../../../../thirdsrc/freeswitch/freeswitch-1.0.6"
FS_MOD_CPP_PATH="${FS_BASE_PATH}/src/mod/applications/mod_ivr_loadbalance"

#copy code
all:
	if [ ! -d ${FS_MOD_CPP_PATH} ]; then \
	    mkdir -p ${FS_MOD_CPP_PATH}; \
	fi

	cp mod_ivr_loadbalance.cpp ${FS_MOD_CPP_PATH}
	cp modules.conf ${FS_BASE_PATH}

#make
	make -C ${FS_BASE_PATH}

#output
	if [ ! -d output ]; then \
	    mkdir -p output; \
	fi
	cp ${FS_MOD_CPP_PATH}/.libs/mod_ivr_loadbalance.so output
	cp default.xml output
	cp modules.conf.xml output
	cp ivr_loadbalance.conf output

clean:
	rm -rf output
