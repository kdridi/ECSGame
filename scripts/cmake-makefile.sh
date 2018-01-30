#!/usr/bin/env bash

set -e

cd $(dirname $0)/..
ROOT_DIR=$(pwd)

cd ${ROOT_DIR}
rm -rf work/makefile
mkdir work/makefile
cd work/makefile
WORK_DIR=$(pwd)

cmake ${ROOT_DIR} \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_PREFIX=$(pwd)/TARGET \
	-G "Unix Makefiles"
make VERBOSE=1