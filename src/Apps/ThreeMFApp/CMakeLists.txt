# ---------------------------------------------------------------------------------
# Project name                                                                  
# ---------------------------------------------------------------------------------
get_filename_component(PROJECTNAME ${CMAKE_CURRENT_LIST_DIR} NAME)

# ---------------------------------------------------------------------------------
# Include paths                                                                 
# ---------------------------------------------------------------------------------
include_directories( ${CMAKE_CURRENT_LIST_DIR} Core )

# ---------------------------------------------------------------------------------
# Add source files                                                                
# ---------------------------------------------------------------------------------
file (GLOB_RECURSE PROJECT_INCLUDES *.hpp
                                    *.h)

file (GLOB_RECURSE PROJECT_SOURCES *.cpp
                                   *.cxx
                                   *.cc
                                   *.c)

# define a grouping for files in IDE
source_group ("include" FILES ${PROJECT_INCLUDES})
source_group ("source" FILES ${PROJECT_SOURCES})

# ---------------------------------------------------------------------------------
# Executable and target include/link libraries                                     
# ---------------------------------------------------------------------------------
add_executable( ${PROJECTNAME} ${PROJECT_INCLUDES} ${PROJECT_SOURCES})

target_include_directories( ${PROJECTNAME} PRIVATE include

    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf/f4d873e5
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/018ab722/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm/02c4d8b1
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui/d4cd121a
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage/e6afb9cb
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/5cfe5002

    ${TBB_INCLUDE_DIR}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TBB_LIB_TYPE ${TBB_LIBRARY_DEBUG})
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(TBB_LIB_TYPE ${TBB_LIBRARY})
endif()

if (WIN32)
    target_link_libraries( ${PROJECTNAME} lib3MF thirdPartyLibs ${TBB_LIB_TYPE} )
elseif(APPLE)
    target_link_libraries( ${PROJECTNAME} ${MACOS_LIBRARIES} lib3MF thirdPartyLibs ${TBB_LIB_TYPE} )
elseif(UNIX AND NOT APPLE)
    target_link_libraries( ${PROJECTNAME} lib3MF uuid thirdPartyLibs glfw ${GLFW_LIBRARIES} ${GTK3_LIBRARIES})
endif()

# ---------------------------------------------------------------------------------
# RESOURCEDIR_PATH definition to be used in C++                                     
# ---------------------------------------------------------------------------------
set ( RESOURCE_DIR_PATH ${CMAKE_SOURCE_DIR}/src/Apps/ThreeMFApp/Resources )
add_definitions(-DRESOURCEDIR_PATH="${RESOURCE_DIR_PATH}/")
