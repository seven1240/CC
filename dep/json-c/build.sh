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

SRCTAR=json-c-0.10-20120530.tar.gz

if [ ! -f ${SRCTAR} ]; then
    curl --location-trusted -k -O https://github.com/json-c/json-c/archive/${SRCTAR}
fi

if [ ! -f ${SRCTAR} ]; then
    echo "can't find ${SRCTAR}, build failed";
    exit 1;
fi

THIRDSRC=$PWD
SRC=json-c-`basename ${SRCTAR} .tar.gz`
INSTALL=$PWD/install

#解压
cd $THIRDSRC
rm -rf $SRC
tar xzf $SRCTAR
#patch -p0 < patch.REENTRANT	
#进入目录进行编译安装
cd $SRC
CPPFLAGS="-fPIC" ./configure --prefix=$INSTALL
make; make install

cd $INSTALL/..

rm -rf output
mkdir output
mkdir output/include
mkdir output/lib
cp -r $INSTALL/include/ output/
cp $INSTALL/lib/*.a output/lib
cp $THIRDSRC/$SRC/*.h output/include/json/
                                 


