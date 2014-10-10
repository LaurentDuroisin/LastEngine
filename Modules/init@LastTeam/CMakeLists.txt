project(init@LastTeam)
cmake_minimum_required(VERSION 2.8)
#set( CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11" )
#make CMake fail
#[ 66%] Built target LastEngine
#[100%] Building CXX object Modules/init@LastTeam/CMakeFiles/MODULE.dir/main.cpp.o
#c++: fatal error: no input files
#compilation terminated.
#Modules/init@LastTeam/CMakeFiles/MODULE.dir/build.make:54: recipe for target 'Modules/init@LastTeam/CMakeFiles/MODULE.dir/main.cpp.o' failed
#/bin/sh: 1: -std=c++11: not found
#make[2]: *** [Modules/init@LastTeam/CMakeFiles/MODULE.dir/main.cpp.o] Error 127
#CMakeFiles/Makefile2:110: recipe for target 'Modules/init@LastTeam/CMakeFiles/MODULE.dir/all' failed

set(CMAKE_CACHEFILE_DIR ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_PATH}Modules/enabled)
include_directories("../../Interfaces")

file(GLOB_RECURSE MOD_SRC_LIST *.h *.cpp)
add_library(${project} MODULE ${MOD_SRC_LIST})
set_target_properties(${project} PROPERTIES PREFIX "" SUFFIX ".lem")
