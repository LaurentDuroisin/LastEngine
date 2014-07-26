project(LastEngine)
cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++11")
set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/ )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})


# Modules

set( MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
FILE(GLOB children RELATIVE ${MODULE_DIR} ${MODULE_DIR}/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${MODULE_DIR}/${child})
        file(GLOB_RECURSE MOD_SRC_LIST Modules/${child}/*.h Modules/${child}/*.cpp)
        add_library(${child} SHARED ${MOD_SRC_LIST} )
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
