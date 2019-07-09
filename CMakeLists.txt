# ---------------------------------------------------------------------------------
# Projects Settings
# ---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(Explore3D)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set( EXTERNAL_LIBRARIES_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/src/ExternalLibrary )

# ---------------------------------------------------------------------------------
# Cmake Modules
# ---------------------------------------------------------------------------------
#include( ${CMAKE_SOURCE_DIR}/cmake/Compiler_Setup.cmake )
#include( ${CMAKE_SOURCE_DIR}/cmake/ExternalLibraries_Setup.cmake )

# ---------------------------------------------------------------------------------
# ThreeMFApp
# ---------------------------------------------------------------------------------
#add_subdirectory( src/Apps/ThreeMFApp )

# ---------------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------------
include(cmake/Googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/Googletest
    )

enable_testing()
add_subdirectory(test)