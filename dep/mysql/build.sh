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


#mysql的源码tar包文件名
MYSQL_SRCTAR=mysql-5.0.51b.tar.gz

if [ ! -f ${MYSQL_SRCTAR} ]; then
    wget http://downloads.mysql.com/archives/get/file/mysql-5.0.51b.tar.gz
fi

if [ ! -f ${MYSQL_SRCTAR} ]; then
    echo "can't find ${MYSQL_SRCTAR}, build failed";
    exit 1;
fi

#指定mysql源码的tar包路径
MYSQL_THIRDSRC=$PWD
#mysql tar包解压后的路径名
MYSQL_SRC=mysql-5.0.51b
#mysql 安装的路径, 可以根据需要进行修改
MYSQL_INSTALL=$PWD/mysql

#解压
cd $MYSQL_THIRDSRC
tar xzf $MYSQL_SRCTAR

#进入目录进行编译安装
cd $MYSQL_SRC
#设置configure参数
#安装到$MYSQL_INSTALL, 可以在这后面继续添加其他编译参数, 
CFLAGS=-fPIC ./configure --prefix=$MYSQL_INSTALL --with-charset=gbk --with--enable-local-infile --with-extra-charset=all --enable-thread-safe-client
#编译并安装
make; make install

cd $MYSQL_INSTALL/..

#继续其他操作,把最后需要发布的结果放到当前目录下的output中即可

mkdir output
mkdir output/include
mkdir output/lib
cp $MYSQL_INSTALL/include/mysql/*.h output/include
cp $MYSQL_INSTALL/lib/mysql/*.a output/lib


