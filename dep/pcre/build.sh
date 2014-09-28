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

SRCTAR=pcre-7.7.tar.gz

if [ ! -f ${SRCTAR} ]; then
    wget http://sourceforge.net/projects/pcre/files/pcre/7.7/pcre-7.7.tar.gz/download
fi

if [ ! -f ${SRCTAR} ]; then
    echo "can't find ${SRCTAR}, build failed";
    exit 1;
fi

#specify where to install by PREFIX or COMMAND-LINE ARG1
PREFIX="$PWD/output"
if [ -n "$1" ]; then
	PREFIX=$1
fi

LIBNAME="pcre-7.7"
DIRNAME=$LIBNAME

#remove older dir
if [ -d "$DIRNAME" ]; then
	rm -rf $DIRNAME
fi

#extract archive
file=$LIBNAME.tar.gz
if [ ! -f "$file" ]; then
	echo "error: no $file"
	exit 1
fi
tar xvzf $file
if [ ! -d "$DIRNAME" ]; then
	echo "error: no $DIRNAME"
	exit 1
fi
cd $DIRNAME


#######special#######
chmod +x configure;
./configure --prefix=$PREFIX --disable-shared --with-pic;
if [ -z "`find ./ -iname Makefile`" ]; then
	echo "error: no Makefile"
	exit 1
fi
#####end of special#######

#build
make && make install
cd ..
rm -rf $DIRNAME

#check
if [ ! -f "$PREFIX/bin/pcre-config" ]; then
	echo "error: no pcre-config"
	exit 1
fi

rm -f $PREFIX/lib/*.la

echo "done!"

