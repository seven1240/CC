#!/bin/bash

# Copyright 2002-2014 the original author or authors.

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

# Source function library.

ROOT_DIR=`pwd`

PATH_NEW=$ROOT_DIR/bin/:$PATH
LD_LIBRARY_PATH_NEW=$ROOT_DIR/lib:$LD_LIBRARY_PATH
DESC="FreeSwitch Voice Switching System"
NAME=freeswitch
DAEMON=$ROOT_DIR/bin/$NAME

CONF_DIR=$ROOT_DIR/conf
LOG_DIR=$ROOT_DIR/log
RUN_DIR=$ROOT_DIR/run
DB_DIR=$ROOT_DIR/db
MOD_DIR=$ROOT_DIR/mod
SCRIPTS_DIR=$ROOT_DIR/scripts

do_setlimits() {
    
    #ulimit -c unlimited
    #ulimit -d unlimited
    #ulimit -f unlimited
    #ulimit -i unlimited
    #ulimit -n 999999
    #ulimit -q unlimited
    #ulimit -u unlimited
    #ulimit -v unlimited
    #ulimit -x unlimited
    #ulimit -s 244
    #ulimit -l unlimited

    
    return 0
}


do_start()
{
    do_setlimits
    $DAEMON -nc -core -run $RUN_DIR -log $LOG_DIR -conf $CONF_DIR -db $DB_DIR -mod $MOD_DIR -scripts $SCRIPTS_DIR
    RETVAL=$?
    if [ $RETVAL = 0 ]; then
        echo "success $DAEMON startup"
    else
        echo "failure $DAEMON startup"
    fi
    
    return $RETVAL
}

do_stop()
{
    $DAEMON  -stop -run $RUN_DIR -log $LOG_DIR -conf $CONF_DIR -db $DB_DIR -mod $MOD_DIR -scripts $SCRIPTS_DIR
    RETVAL=$?
    if [ $RETVAL = 0 ]; then
        echo "success $DAEMON shutdown"
    else
        echo "failure $DAEMON shutdown"
    fi
    
    rm -f $RUN_DIR/*
    
    return $RETVAL
}


export PATH=$PATH_NEW
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH_NEW

case "$1" in
    
    start)
        do_start
        ;;
    stop)
        do_stop
        ;;
    restart)
        do_stop
        echo "waiting for daemon to exit..."
        sleep 5
        do_start
        ;;
    *)
        echo $"Usage: $0 {start|stop}"
        exit 2
        ;;
esac

exit $RETVAL

