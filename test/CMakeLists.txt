set(TARGET_NAME unit_tests)

add_executable( 
    ${TARGET_NAME}
    main.cpp
    testMesh.cpp
)

target_include_directories( ${TARGET_NAME} PRIVATE include
    ${EXTERNAL_LIBRARIES_DIRECTORY_PATH}/Lib3mf/f4d873e5
)

set( libraries
     lib3MF
     gtest_main
)

if(APPLE)
    list(APPEND libraries
        ${MACOS_LIBRARIES}
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND libraries
        uuid
    )
endif()

target_link_libraries(${TARGET_NAME} 
    ${libraries}
)

add_test( NAME ${TARGET_NAME} 
          COMMAND $<TARGET_FILE:${TARGET_NAME}>
)
