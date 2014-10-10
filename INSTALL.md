#platform

##建议环境
1. linux内核操作系统，建议内核版本> 2.6.9
2. gcc 3.4 编译工具链 

##依赖项
1. [FreeSWITCH](http://files.freeswitch.org/freeswitch-1.0.6.tar.gz)
2. [OpenSIPS](http://opensips.org/pub/opensips/1.8.5/src/opensips-1.8.5_src.tar.gz/) (可选)
3. [boost](http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.gz/download)
4. [json-c](https://github.com/json-c/json-c/archive/json-c-0.10-20120530.tar.gz)
5. [libxml2](http://xmlsoft.org/sources/old/libxml2-2.6.30.tar.gz)
6. [mysql](http://downloads.mysql.com/archives/get/file/mysql-5.0.51b.tar.gz)
7. [pcre](http://sourceforge.net/projects/pcre/files/pcre/7.7/pcre-7.7.tar.gz/download)
8. [libcurl](http://curl.haxx.se/download/curl-7.21.0.tar.gz)


##编译
- ` $ bash build.sh build `
- 目录**release**目录下有**ims**、**acd**、**agentproxy**、**ivr**、**freeswitch**四个目录，每个目录下有独立的可执行程序

#tools

##建议环境
1. windows系列操作系统，建议版本不低于 windows xp
2. vs2003、vs2010


##编译
1. 各工程目录的vcprj或sln文件打开编译即可