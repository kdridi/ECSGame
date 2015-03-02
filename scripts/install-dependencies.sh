#!/usr/bin/env bash

set -e

cd $(dirname $0)/..
ROOT_DIR=$(pwd)

cd ${ROOT_DIR}
rm -rf prefix
mkdir prefix
cd prefix
PREFIX_DIR=$(pwd)

################################################################################
# EntityX
################################################################################
cd ${ROOT_DIR}
rm -rf work
mkdir work
cd work
WORK_DIR=$(pwd)

cmake ${ROOT_DIR}/submodules/github.com/alecthomas/entityx.git \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_PREFIX=${PREFIX_DIR} \
	-DCMAKE_OSX_ARCHITECTURES=x86_64\;i386 \
	-DENTITYX_BUILD_SHARED=ON \
	-DENTITYX_BUILD_TESTING=OFF \
	-DENTITYX_DT_TYPE=double \
	-DENTITYX_MAX_COMPONENTS=64 \
	-DENTITYX_RUN_BENCHMARKS=OFF
make -j12
make install

################################################################################
# SFML
################################################################################
cd ${ROOT_DIR}
rm -rf work
mkdir work
cd work
WORK_DIR=$(pwd)

cmake ${ROOT_DIR}/submodules/github.com/LaurentGomila/SFML.git \
	-DBUILD_SHARED_LIBS=ON \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_FRAMEWORK_PREFIX=${PREFIX_DIR}/Frameworks \
	-DCMAKE_INSTALL_PREFIX=${PREFIX_DIR} \
	-DCMAKE_OSX_ARCHITECTURES=x86_64\;i386 \
	-DSFML_BUILD_DOC=OFF \
	-DSFML_BUILD_EXAMPLES=OFF \
	-DSFML_BUILD_FRAMEWORKS=OFF \
	-DSFML_INSTALL_XCODE_TEMPLATES=OFF \
	-DSFML_OPENGL_ES=OFF
make -j12
make install