# ---------------------------------------------------------------------------------
# Compiler setups                                                                  
# ---------------------------------------------------------------------------------

# we require C++ 14 or later
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES Debug; Release)

# optimization flag
# set -O0/-Og/-O1/-O2/-O3/-Ofast depending on CMAKE_BUILD_TYPE

if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        message(STATUS "Optimization flag => -02")
        add_compile_options(-O2)
    endif()
endif()

if(APPLE)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        message(STATUS "Optimization flag => -03")
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()
