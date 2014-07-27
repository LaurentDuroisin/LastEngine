file(GLOB_RECURSE LIB_SRC_LIST *.h sqlite3.c)

add_library(${child} STATIC ${LIB_SRC_LIST} )

set_target_properties(${child} PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${BIN_PATH}/lib)
