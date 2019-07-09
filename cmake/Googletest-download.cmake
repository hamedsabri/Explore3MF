cmake_minimum_required(VERSION 3.5)

project(googletest-download NONE)

include(ExternalProject)

set(FORCE_SHARED_CRT "")
if(MSVC)
    set(FORCE_SHARED_CRT -DFORCE_SHARED_CRT=OFF)
endif()

ExternalProject_Add(
    googletest
    SOURCE_DIR "@GOOGLETEST_DOWNLOAD_ROOT@/googletest-src"
    BINARY_DIR "@GOOGLETEST_DOWNLOAD_ROOT@/googletest-build"
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
    CMAKE_ARGS "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" "-Dgtest_force_shared_crt=ON" "-DCMAKE_POSITION_INDEPENDENT_CODE=ON" -DFORCE_SHARED_CRT=OFF ${FORCE_SHARED_CRT}
)
