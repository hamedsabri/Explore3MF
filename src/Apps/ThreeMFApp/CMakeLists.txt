get_filename_component(PROJECTNAME ${CMAKE_CURRENT_LIST_DIR} NAME)

file( GLOB_RECURSE SRC_FILES *.cpp *.cxx *.cc *.C *.c *.h *.hpp )

add_executable( ${PROJECTNAME} ${SRC_FILES} )

target_include_directories( ${PROJECTNAME} PRIVATE include ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf )

target_link_libraries( ${PROJECTNAME} lib3MF )
