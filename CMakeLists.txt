project(LastEngine)
cmake_minimum_required(VERSION 2.8)
set( CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-std=c++11" )
set(BIN_PATH "/tmp/${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/" ) # /tmp because of a bug in my computer, remove it.
set(BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM}/${CMAKE_CXX_COMPILER_ID}/" )
set(CMAKE_CACHEFILE_DIR ${BUILD_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
include_directories("Interfaces")

# Modules

set( MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules)
file(GLOB children RELATIVE ${MODULE_DIR} ${MODULE_DIR}/*)
foreach(child ${children})
    add_subdirectory ( ${MODULE_DIR}/${child} )
endforeach()

# Kernel

file(GLOB_RECURSE SRC_LIST Kernel/*.h Kernel/*.cpp)

# show the files in QtCreator
file(GLOB_RECURSE UML_FILES doc/UML/*.dia)
file(GLOB_RECURSE INTERFACES_FILES Interfaces/* )
set(OTHERS_FILES LICENCE.txt doc/Doxyfile)

add_executable(${PROJECT_NAME}
               ${SRC_LIST}
               ${INTERFACES_FILES}
               ${UML_FILES}
               ${OTHERS_FILES}
               )

if( ${UNIX} )
    target_link_libraries(${PROJECT_NAME} dl)
endif()
