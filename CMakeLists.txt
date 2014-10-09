# http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
# http://www.adp-gmbh.ch/sqlite/bind_insert.html
# http://truc2geek.wordpress.com/2012/04/24/sqlite-part-3-creer-une-vue-modes-daffichage/
project(LastEngine)
cmake_minimum_required(VERSION 2.8)
SET( CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11" )
set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/ )
set(BULD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/ )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})

# TODO : CMake must put all his files in build directory

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/srclib)

# custom targets
add_custom_target(Doxygen COMMAND doxygen WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)

#libraries

set( LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/srclib)
FILE(GLOB children RELATIVE ${LIB_SRC_DIR} ${LIB_SRC_DIR}/*)
FOREACH(child ${children})
    IF(IS_DIRECTORY ${LIB_SRC_DIR}/${child})
        add_subdirectory ( ${LIB_SRC_DIR}/${child} )
    ENDIF()
ENDFOREACH()

# Modules

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
