get_filename_component(PROJECTNAME ${CMAKE_CURRENT_LIST_DIR} NAME)

file( GLOB_RECURSE SRC_FILES *.cpp *.cxx *.cc *.C *.c *.h *.hpp )

add_executable( ${PROJECTNAME} ${SRC_FILES} )

target_include_directories( ${PROJECTNAME} PRIVATE include

    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf

    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glad/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glfw/include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Glm
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/ImGui
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/STBImage
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/TinyFileDialog
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/NativeFileDialog/
)

if (WIN32)
    target_link_libraries( ${PROJECTNAME} lib3MF thirdPartyLibs )
elseif(APPLE)
    target_link_libraries( ${PROJECTNAME} ${MACOS_LIBRARIES} lib3MF thirdPartyLibs )
endif()

set ( THREEMFAPP_DIR_PATH ${CMAKE_SOURCE_DIR}/src/Apps/ThreeMFAPP )
set ( RESOURCE_DIR_PATH ${CMAKE_SOURCE_DIR}/src/Apps/ThreeMFAPP/Resources )

include_directories(
    ${THREEMFAPP_DIR_PATH}
)

add_definitions(-DRESOURCEDIR_PATH="${RESOURCE_DIR_PATH}/")
