project(LastEngine)
cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Modules

FILE(GLOB children Modules/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${child})
        file(GLOB_RECURSE MOD_SRC_LIST ${child}/*.h ${child}/*.cpp)
        add_library("ModuleManager" SHARED ${MOD_SRC_LIST} )
    ENDIF()
ENDFOREACH()

# Kernel

file(GLOB_RECURSE SRC_LIST Kernel/*.h Kernel/*.cpp)
set(OTHERS_FILES LICENCE.txt doc/Doxyfile)

add_executable(${PROJECT_NAME}
               ${SRC_LIST}
               ${OTHERS_FILES}
               )
