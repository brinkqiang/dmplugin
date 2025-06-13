cmake_minimum_required(VERSION 3.21)

PROJECT(dmplugin)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMPLUGIN_VERSION_MAJOR "1")
SET(DMPLUGIN_VERSION_MINOR "0")
SET(DMPLUGIN_VERSION_PATCH "1")
SET(DMPLUGIN_VERSION "${DMPLUGIN_VERSION_MAJOR}.${DMPLUGIN_VERSION_MINOR}.${DMPLUGIN_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMPLUGIN_VERSION}")

OPTION(USE_DMPLUGIN "use dmplugin" OFF)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/dmplugin_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dmplugin_config.h)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

ModuleImportAll("thirdparty")

LibImport("libdmplugin" "src/libdmplugin")


if(PROJECT_IS_TOP_LEVEL)
    ExeImport("test" "libdmplugin;dmtest")
    DllImportDepends("sampleplugin" "plugins/sampleplugin" "libdmplugin")

    ExeImport("loader" "libdmplugin")

endif()

AddInstall("libdmplugin" "${CMAKE_CURRENT_SOURCE_DIR}/include")
