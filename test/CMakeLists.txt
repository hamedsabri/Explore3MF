set(TARGET_NAME unit_tests)
add_executable( 
	${TARGET_NAME}
	main.cpp
    Test-Mesh.cpp
)

target_include_directories( ${TARGET_NAME} PRIVATE include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf/f4d873e5
)

if (WIN32)
    target_link_libraries( ${TARGET_NAME} lib3MF gtest_main )
elseif(APPLE)
    target_link_libraries( ${TARGET_NAME} ${MACOS_LIBRARIES} lib3MF gtest_main )
elseif(UNIX AND NOT APPLE)
    target_link_libraries( ${TARGET_NAME} lib3MF uuid gtest_main)
endif()

add_test( NAME ${TARGET_NAME} 
		  COMMAND $<TARGET_FILE:${TARGET_NAME}>
)
