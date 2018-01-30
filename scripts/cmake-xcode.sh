#!/usr/bin/env bash

set -e

cd $(dirname $0)/..
ROOT_DIR=$(pwd)

cd ${ROOT_DIR}
rm -rf work/xcode
mkdir work/xcode
cd work/xcode
WORK_DIR=$(pwd)

export PKG_CONFIG_PATH="${ROOT_DIR}/prefix/lib/pkgconfig"

cmake ${ROOT_DIR} \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_PREFIX=$(pwd)/TARGET \
	-G "Xcode"
open *.xcodeproj