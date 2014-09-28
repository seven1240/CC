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

SRCTAR=curl-7.21.0.tar.gz

if [ ! -f ${SRCTAR} ]; then
    wget http://curl.haxx.se/download/${SRCTAR}
fi

if [ ! -f ${SRCTAR} ]; then
    echo "can't find ${SRCTAR}, build failed";
    exit 1;
fi

INSTALL=$PWD/install
PREFIX="$PWD/output"
if [ -n "$1" ]; then
	PREFIX=$1
fi

LIBNAME=`basename ${SRCTAR} .tar.gz`
DIRNAME=$LIBNAME

if [ -d "$DIRNAME" ]; then
	rm -rf $DIRNAME
fi

file=$LIBNAME.tar.gz
if [ ! -f "$file" ]; then
	echo "error: no $file"
	exit 1
fi
tar xzf $file
if [ ! -d "$DIRNAME" ]; then
	echo "error: no $DIRNAME"
	exit 1
fi
cd $DIRNAME


chmod +x configure;
CONFIG="./configure --prefix=$INSTALL --enable-shared=no --enable-static=yes --with-pic=yes"
CPPFLAGS="-fPIC" $CONFIG
make && make install

cd $INSTALL/..

rm -rf $PREFIX
mkdir $PREFIX
cp -r $INSTALL/include $PREFIX
cp -r $INSTALL/lib $PREFIX

find $PREFIX/lib -type f ! -iname "*.a" -exec rm -rf {} \;
find $PREFIX/lib -type d -empty | xargs rm -rf 
find $PREFIX/lib -type l -exec rm -rf {} \;

echo "done!"

