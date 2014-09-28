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

build()
{
    for d in `dir`; do
        if [ -d $d ]; then
            cd $d && if [ -f build.sh ]; then bash build.sh; else python build.py; fi && cd ..;
        fi
    done
}

clean()
{
    for d in `dir`; do
        if [ -d $d ]; then
            rm -fr $d/$d*;
            rm -fr $d/output;
            rm -fr $d/INSTALL;
        fi
    done
}

case "$1" in
    clean)
        clean
        ;;
    *)
        build
        ;;
esac

