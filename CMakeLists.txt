# ---------------------------------------------------------------------------------
# Projects Settings
# ---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(Explore3D)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( EXTERNAL_LIBRARIES_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/src/ExternalLibrary )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

if( NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE Debug )
endif()

# ---------------------------------------------------------------------------------
# Cmake Modules
# ---------------------------------------------------------------------------------
include( ${CMAKE_SOURCE_DIR}/cmake/Compiler_Setup.cmake )
include( ${CMAKE_SOURCE_DIR}/cmake/ExternalLibraries_Setup.cmake )

# ---------------------------------------------------------------------------------
# ThreeMFApp
# ---------------------------------------------------------------------------------
add_subdirectory( src/Apps/ThreeMFApp )
