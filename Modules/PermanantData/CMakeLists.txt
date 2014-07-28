set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
file(GLOB_RECURSE MOD_SRC_LIST *.h *.cpp)

add_library(${child} SHARED ${MOD_SRC_LIST} )

target_link_libraries(${child} SQLite)
