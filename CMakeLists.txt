# ---------------------------------------------------------------------------------
# Projects Settings
# ---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(ThreeMFViewer)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set( EXTERNAL_LIBRARIES_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/src/ExternalLibrary )

option(BUILD_TESTS "Build unit tests" ON)

# ---------------------------------------------------------------------------------
# Cmake Modules
# ---------------------------------------------------------------------------------
include( ${CMAKE_SOURCE_DIR}/cmake/Compiler_Setup.cmake )
include( ${CMAKE_SOURCE_DIR}/cmake/ExternalLibraries_Setup.cmake )

# ---------------------------------------------------------------------------------
# ThreeMFApp
# ---------------------------------------------------------------------------------
add_subdirectory( src/Apps/ThreeMFApp )

# ---------------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------------
if (BUILD_TESTS)
    # google test
    include(cmake/Googletest.cmake)
    fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/Googletest
        )
    
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

# ---------------------------------------------------------------------------------
# PACKAGE
# ---------------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME "ThreeMFViewer")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ThreeMFViewer - Package")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Package")

include(CPack)