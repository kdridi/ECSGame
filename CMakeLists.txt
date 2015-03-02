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

#SET(CMAKE_EXE_LINKER_FLAGS "-bind_at_load -framework Foundation -framework CoreFoundation -framework Quartz -w")

# Define sources and executable
set(EXECUTABLE_NAME "arykow")
add_executable(${EXECUTABLE_NAME}
	src/arkanoid.cpp
	src/arkanoid.h
	src/tilemap.cpp
	src/tilemap.h
	src/main.cpp
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/prefix/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
	include_directories(${CMAKE_SOURCE_DIR}/prefix/include)
	target_link_libraries(${EXECUTABLE_NAME}
		${CMAKE_SOURCE_DIR}/prefix/lib/libsfml-audio-d.dylib 
		${CMAKE_SOURCE_DIR}/prefix/lib/libsfml-graphics-d.dylib 
		${CMAKE_SOURCE_DIR}/prefix/lib/libsfml-network-d.dylib 
		${CMAKE_SOURCE_DIR}/prefix/lib/libsfml-system-d.dylib 
		${CMAKE_SOURCE_DIR}/prefix/lib/libsfml-window-d.dylib
	)
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${arykow_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${arykow_VERSION_MINOR}")
include(CPack)