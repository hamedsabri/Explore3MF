# ---------------------------------------------------------------------------------
# Project name
# ---------------------------------------------------------------------------------
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

# ---------------------------------------------------------------------------------
# Include paths 
# ---------------------------------------------------------------------------------
include_directories( ${CMAKE_CURRENT_LIST_DIR} Core )

# ---------------------------------------------------------------------------------
# Add source files
# ---------------------------------------------------------------------------------
file (GLOB_RECURSE PROJECT_INCLUDES 
    *.hpp
    *.h
)

file (GLOB_RECURSE PROJECT_SOURCES 
    *.cpp
    *.cxx
    *.cc
    *.c
)

# define a grouping for files in IDE
source_group ("include" FILES ${PROJECT_INCLUDES})
source_group ("source" FILES ${PROJECT_SOURCES})

# ---------------------------------------------------------------------------------
# Executable and target include/link libraries 
# ---------------------------------------------------------------------------------
add_executable(${TARGET_NAME} ${PROJECT_INCLUDES} ${PROJECT_SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE include

    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf/f4d873e5
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm/02c4d8b1
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002
)


set( libraries
     lib3MF
     thirdPartyLibs
)
if(APPLE)
    list(APPEND libraries
        ${MACOS_LIBRARIES}
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND libraries
        uuid
        glfw
        ${GLFW_LIBRARIES} 
        ${GTK3_LIBRARIES}
    )
endif()

target_link_libraries(${TARGET_NAME} 
    ${libraries}
)

# ---------------------------------------------------------------------------------
# RESOURCEDIR_PATH definition to be used in C++
# ---------------------------------------------------------------------------------
set ( RESOURCE_DIR_PATH ${CMAKE_SOURCE_DIR}/src/Apps/ThreeMFApp/Resources )
add_definitions(-DRESOURCEDIR_PATH="${RESOURCE_DIR_PATH}/")

# ---------------------------------------------------------------------------------
# INSTALL
# ---------------------------------------------------------------------------------
install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
    DESTINATION
        Explore3MF/bin
)

install(
    DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
    DESTINATION
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

install(TARGETS
    ${TARGET_NAME}
    LIBRARY
        DESTINATION Explore3MF/bin
    RUNTIME
        DESTINATION Explore3MF/bin
)

if(MSVC)
    install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}> DESTINATION Explore3MF/bin OPTIONAL)
endif()
