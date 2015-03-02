#!/usr/bin/env bash

set -e

cd $(dirname $0)/..
ROOT_DIR=$(pwd)

cd ${ROOT_DIR}
rm -rf work/xcode
mkdir work/xcode
cd work/xcode
WORK_DIR=$(pwd)

cmake ${ROOT_DIR} \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_PREFIX=$(pwd)/TARGET \
	-DCMAKE_OSX_ARCHITECTURES=x86_64\;i386 \
	-G "Xcode"
open *.xcodeproj