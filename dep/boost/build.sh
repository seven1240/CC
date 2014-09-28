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

SRCTAR=boost_1_56_0.tar.gz

if [ ! -f ${SRCTAR} ]; then
    wget http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.gz/download;
fi

if [ ! -f ${SRCTAR} ]; then
    echo "can't find ${SRCTAR}, build failed";
    exit 1;
fi

NAME=`ls *.gz *.bz2 2>/dev/null`
echo build $NAME

#安装的路径, 可以根据需要进行修改
INSTALL=$PWD/install

SRC=`basename ${SRCTAR} .tar.gz`
rm -rf $SRC
tar xzf ${SRCTAR}


#进入目录进行编译安装
cd $SRC
sed -i -e 's/\(<toolset>gcc:<cxxflags>-Wno-variadic-macros\)/#\1/' libs/chrono/build/Jamfile.v2
sed -i -e 's/\(<toolset>gcc:<cxxflags>-Wno-variadic-macros\)/#\1/' libs/thread/build/Jamfile.v2

#编译bjam
rm -rf bjam
sh bootstrap.sh

#编译并且安装
./bjam --prefix=$INSTALL --threading=multi --link=static cxxflags='-fPIC -O2' cflags='-fPIC -O2' install
./bjam --prefix=$INSTALL --threading=multi --link=static --with-thread --with-chrono cxxflags='-fPIC -O2' cflags='-fPIC -O2' install
cd $INSTALL/..

#继续其他操作,把最后需要发布的结果放到当前目录下的output中即可
rm -rf output
mkdir output
cp -r $INSTALL/include output
cp -r $INSTALL/lib output
#删除lib下面非.a文件
find output/lib -type f ! -iname "*.a" -exec rm -rf {} \;
#删除lib下面空目录
find output/lib -type d -empty | xargs rm -rf 
#删除lib下面的软链接文件
find output/lib -type l -exec rm -rf {} \;

