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

source DIST_VERSION.inc


ROOT=`pwd`
PREFIX=$ROOT/output
VOICE_DIR=$ROOT/voice

echo "prepare build..."

if [ -z "$DIST_VERSION" ]; then
    echo "errno: no DIST_VERSION info"
    exit 1
fi

DIRNAME=$ROOT/$DIST_VERSION
if [ -d "$DIRNAME" ]; then  
    rm -rf $DIRNAME
fi

if [ -d "$PREFIX" ]; then
    rm -fr $PREFIX
fi

file=$DIST_VERSION.tar.gz

if [ ! -f $file ]; then
    wget http://files.freeswitch.org/freeswitch-1.0.6.tar.gz
fi

if [ ! -f "$file" ]; then    
    echo "can't find ${file}, build failed";
    exit 1;
fi

echo "tar xzf $file..."
tar xzf $file

if [ ! -d "$DIRNAME" ]; then  
    echo "error: no $DIRNAME"   
    exit 1
fi
    

cd $DIRNAME
rm -fr $DIRNAME/libs/esl
cp -fr $ROOT/patch/esl libs/
cp -fr $ROOT/patch/mod_http_cache src/mod/applications/
cp -fr $ROOT/patch/modules.conf ./

cp -r $ROOT/patch/autoload_configs/* conf/autoload_configs/

cp -r $ROOT/patch/mod_http_cache src/mod/applications/

cp -r ../../../platform/fw-mod/record/mod_ccl_record  src/mod/applications/
mkdir -p src/mod/applications/mod_ivr_loadbalance
cp ../../../platform/fw-mod/ivrloadbalance/mod_ivr_loadbalance.cpp src/mod/applications/mod_ivr_loadbalance/

patch_files=`ls $ROOT/patch/*.patch`
if [ $? = 0 ] ; then
	for f in $patch_files
	do
		patch -p1 < $f
	done
fi

echo "begin to build..."

CFLAGS="-fPIC" CXXFLAGS="-fPIC" ./configure --prefix=$PREFIX

echo "begin compiling libedit library..."
make -C libs/libedit/ 
echo "end compiling libedit library..."

echo "begin compiling curl library..."
make -C libs/curl/ 
echo "end compiling curl library..."

echo "begin compiling esl library..."
make -C libs/esl/ 
echo "end compiling esl library..."

make -j 8
make install

if [ ! -f "$PREFIX/bin/freeswitch" ]; then
    echo "error: no freeswitch"
    exit 1
fi

if [ -d "$PREFIX/conf" ]; then
    cp ../../../platform/fw-mod/record/mod_ccl_record/conf/ccl_record.conf.xml $PREFIX/conf/autoload_configs/
    cp ../../../platform/fw-mod/ivrloadbalance/ivr_loadbalance.conf $PREFIX/conf/autoload_configs/
    cp $ROOT/patch/autoload_configs/event_socket.conf.xml $PREFIX/conf/autoload_configs/
    cp $ROOT/patch/autoload_configs/logfile.conf.xml $PREFIX/conf/autoload_configs/

    mv $PREFIX/conf $PREFIX/conf.old
    mkdir -p $PREFIX/conf-new/autoload_configs
    cp $ROOT/patch/autoload_configs/modules.conf.xml $PREFIX/conf-new/autoload_configs/
fi


if [ -d "$PREFIX/htdocs" ]; then
    rm -fr $PREFIX/htdocs
fi


cd $VOICE_DIR
if [ ! -d $PREFIX/voice ]; then
    mkdir -p $PREFIX/voice
fi

cp *.wav $PREFIX/voice/

cd $PREFIX
cp ../freeswitch.sh .
tar cvzf $DIST_VERSION.tgz *
mv $DIST_VERSION.tgz $PREFIX/../$DIST_VERSION.tgz
cd -
rm -rf $PREFIX
mkdir -p $PREFIX
mv $PREFIX/../$DIST_VERSION.tgz $PREFIX/

#dist esl library
if [ ! -d "$PREFIX/libs/esl" ]; then
    mkdir -p $PREFIX/libs/esl/
fi

cp -r $PREFIX/../$DIST_VERSION/libs/esl/src/include $PREFIX/libs/esl/
cp $PREFIX/../$DIST_VERSION/libs/esl/libesl.a $PREFIX/libs/esl/

if [ ! -f "$PREFIX/$DIST_VERSION.tgz" ]; then
    echo "error: no $PREFIX/$DIST_VERSION.tgz"
    exit 1
fi

echo "build binary done success"
