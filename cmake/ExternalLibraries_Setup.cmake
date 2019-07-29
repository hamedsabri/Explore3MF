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

    file(GLOB GLFW_source
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

    file(GLOB GLFW_source
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

file(GLOB includes
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm/02c4d8b1/*.hpp
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb/*.h
)

file(GLOB source 
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/src/*.c
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a/*.cpp
    ${NATIVE_FILE_DIALOG}
    ${GLFW_source}
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
add_library(thirdPartyLibs STATIC 
    ${source} 
    ${includes}
)

target_include_directories(thirdPartyLibs PRIVATE include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb
)

