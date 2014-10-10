project(init@LastTeam)
cmake_minimum_required(VERSION 2.8)
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

set(CMAKE_CACHEFILE_DIR ${BUILD_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_PATH}Modules/enabled)
include_directories("../../Interfaces")

file(GLOB_RECURSE MOD_SRC_LIST *.h *.cpp)
add_library(${PROJECT_NAME} MODULE ${MOD_SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".lem")

# use it as default init.lem module.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_NAME}.lem" "${BIN_PATH}/init.lem"
)
