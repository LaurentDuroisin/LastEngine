project(LastEngine)
cmake_minimum_required(VERSION 2.8)
set( CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11" )
set(BIN_PATH "/tmp/${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/" ) # /tmp because of a bug in my computer, remove it.
set(BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/" )
set(CMAKE_CACHEFILE_DIR ${BUILD_PATH})


# Modules
# TODO remove

set( MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
FILE(GLOB children RELATIVE ${MODULE_DIR} ${MODULE_DIR}/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${MODULE_DIR}/${child})
        IF( EXISTS ${MODULE_DIR}/${child}/CMakeLists.txt )
            add_subdirectory ( ${MODULE_DIR}/${child} )
        ELSE()
            file(GLOB_RECURSE MOD_SRC_LIST Modules/${child}/*.h Modules/${child}/*.cpp)
            add_library(${child} SHARED ${MOD_SRC_LIST} )
        ENDIF()
    ENDIF()
ENDFOREACH()

# Kernel

file(GLOB_RECURSE SRC_LIST Kernel/*.h Kernel/*.cpp)
file(GLOB_RECURSE UML_FILES doc/UML/*.dia)
set(OTHERS_FILES LICENCE.txt doc/Doxyfile)

add_executable(${PROJECT_NAME}
               ${SRC_LIST}
               ${UML_FILES}
               ${OTHERS_FILES}
               )
