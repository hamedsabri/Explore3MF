cmake_minimum_required(VERSION 3.5)

project(Explore3D)

set(CMAKE_CXX_STANDARD 14)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( EXTERNAL_LIBRARIES_DIRECTORY_PATH ${CMAKE_SOURCE_DIR}/src/ExternalLibrary )

include( ${CMAKE_SOURCE_DIR}/cmake/ExternalLibraries_Setup.cmake )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

add_subdirectory( src/Apps/ThreeMFApp )
