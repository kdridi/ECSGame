#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(arykow)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(arykow_VERSION_MAJOR 1)
set(arykow_VERSION_MINOR 0)
set(arykow_DATA_PATH ${PROJECT_SOURCE_DIR}/data/)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

################################################################################
# EXECUTABLE
################################################################################
set(EXECUTABLE_NAME "arykow")

################################################################################
# SOURCES
################################################################################
add_executable(${EXECUTABLE_NAME}
	src/arkanoid.cpp
	src/arkanoid.h
	src/tilemap.cpp
	src/tilemap.h
	src/ecs.cpp
	src/ecs.h
	src/main.cpp
)

################################################################################
# SFML
################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/prefix/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/prefix")
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

################################################################################
# ENTITYX
################################################################################
set(entityx_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/prefix/include")
set(entityx_LIBRARIES
	"${CMAKE_SOURCE_DIR}/prefix/lib/libentityx-d.a"
)
include_directories(${entityx_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_NAME} ${entityx_LIBRARIES})

################################################################################
# TARGETS
################################################################################
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${arykow_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${arykow_VERSION_MINOR}")
include(CPack)