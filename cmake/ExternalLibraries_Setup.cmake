# ---------------------------------------------------------------------------------
# Intel Threading Building Blocks (TBB)
# ---------------------------------------------------------------------------------
set( TBB_ROOT_DIR ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5 CACHE PATH "")
set( TBB_INCLUDE_DIR ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/include CACHE PATH "")

if(WIN32)
set( TBB_LIBRARY "${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/lib/tbb.lib" CACHE FILEPATH "")
set( TBB_LIBRARY_DEBUG "${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/lib/tbb_debug.lib" CACHE FILEPATH "")

message(${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (TBB_DLL ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/bin/tbb_debug.dll)
    set (TBB_PDB ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/bin/tbb_debug.pdb)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    set (TBB_DLL ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/bin/tbb.dll)
    set (TBB_PDB ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Win/bin/tbb.pdb)
endif()

# copy *.dll, *.pdb
execute_process(COMMAND cmake -E make_directory ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE})
foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${TBB_DLL}
        ${TBB_PDB}
        ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/
    )
endforeach()
else (APPLE)
    set( TBB_LIBRARY "${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Mac/lib/libtbb.dylib" CACHE FILEPATH "")
    set( TBB_LIBRARY_DEBUG "${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TBB/2018_Update5/binary/Mac/lib/libtbb_debug.dylib" CACHE FILEPATH "")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

find_package(TBB REQUIRED)

# ---------------------------------------------------------------------------------
# Lib3MF                                                                    
# ---------------------------------------------------------------------------------
add_subdirectory(${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3MF/f4d873e5 ${CMAKE_CURRENT_BINARY_DIR}/lib3MF)

# ---------------------------------------------------------------------------------
# Third party library setup                                                                  
# ---------------------------------------------------------------------------------
if (UNIX AND NOT APPLE)
    # GLFW 
    option (GLFW_INSTALL OFF)
    option (GLFW_BUILD_DOCS OFF)
    option (GLFW_BUILD_EXAMPLES OFF)
    option (GLFW_BUILD_TESTS OFF)
    add_subdirectory(${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722 ${CMAKE_CURRENT_BINARY_DIR}/Glfw)
    include_directories( ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include )
    add_definitions(-DGLFW_INCLUDE_NONE )

    # GTK - Native File Dialog
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    add_definitions(${GTK3_CFLAGS_OTHER})

    file(GLOB NATIVE_FILE_DIALOG ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/nfd_common.c
                                 ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/nfd_gtk.c )
endif()

if(WIN32)
    add_definitions(-D_GLFW_WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    file(GLOB GLFW_SOURCES
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/egl_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/input.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/osmesa_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/vulkan.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/wgl_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_joystick.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_thread.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_time.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/win32_window.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/window.c
    )

    file(GLOB NATIVE_FILE_DIALOG
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/nfd_common.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/*.cpp
    )

elseif(APPLE)
    add_definitions(-D_GLFW_COCOA)

    file(GLOB GLFW_SOURCES
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/egl_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/input.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/osmesa_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/vulkan.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/window.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/posix_tls.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/posix_thread.c 
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/nsgl_context.m     
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/cocoa_init.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/cocoa_joystick.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/cocoa_monitor.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/cocoa_time.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/src/cocoa_window.m
    )

    file(GLOB NATIVE_FILE_DIALOG
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/nfd_common.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/*.m
    )
endif()

file(GLOB INCLUDES
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm/02c4d8b1/*.hpp
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb/*.h
)

file(GLOB SOURCES 
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/src/*.c
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a/*.cpp
    ${NATIVE_FILE_DIALOG}
    ${GLFW_SOURCES}
)

if (APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(APPKIT_LIBRARY AppKit) 
    find_library(CF_LIBRARY CoreFoundation)
    find_library(COREVIDEO_LIBRARY CoreVideo)

    set(MACOS_LIBRARIES ${OPENGL_LIBRARY} ${APPKIT_LIBRARY} ${CF_LIBRARY} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

# ---------------------------------------------------------------------------------
# thirdPartyLibs                                                                  
# ---------------------------------------------------------------------------------
add_library(thirdPartyLibs STATIC ${SOURCES} ${INCLUDES})
target_include_directories(thirdPartyLibs PRIVATE include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb
)

