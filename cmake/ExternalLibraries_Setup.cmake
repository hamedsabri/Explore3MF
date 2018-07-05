add_subdirectory(${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3MF ${CMAKE_CURRENT_BINARY_DIR}/lib3MF)

# ****************** THIRD LIBRARIES ******************
if(WIN32)
    add_definitions(-D_GLFW_WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    file(GLOB GLFW_SOURCES
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/egl_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/input.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/osmesa_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/vulkan.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/wgl_context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_joystick.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_thread.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_time.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/win32_window.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/window.c
    )

    file(GLOB NATIVE_FILE_DIALOG
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/nfd_common.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/*.cpp
    )

elseif(APPLE)
    add_definitions(-D_GLFW_COCOA)

    file(GLOB GLFW_SOURCES
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/context.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/init.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/input.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/monitor.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/vulkan.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/window.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/posix_tls.c 
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/nsgl_context.m
        
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/cocoa_init.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/cocoa_joystick.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/cocoa_monitor.m
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/cocoa_time.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/src/cocoa_window.m
    )

    file(GLOB NATIVE_FILE_DIALOG
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/nfd_common.c
        ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/*.m
    )
endif()

file(GLOB INCLUDES
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm/*.hpp
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/*.h
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/*.h
)

file(GLOB SOURCES 
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/src/*.c
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/*.cpp
    ${NATIVE_FILE_DIALOG}
    ${GLFW_SOURCES}
)

add_library(thirdPartyLibs STATIC ${SOURCES} ${INCLUDES})

target_include_directories(thirdPartyLibs PRIVATE include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage
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
