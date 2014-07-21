project(LastEngine)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

aux_source_directory(Modules/ModuleManager MODULE_SRC_LIST)

add_executable(${PROJECT_NAME}
                ${SRC_LIST}
                LICENCE.txt
                VirtualKernel.h
                VirtualModuleManager.h)

add_library("ModuleManager" SHARED ${MODULE_SRC_LIST} )
